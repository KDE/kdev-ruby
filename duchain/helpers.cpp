/* This file is part of KDevelop
 *
 * Copyright (C) 2011 Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


// Qt + KDE
#include <QtCore/QProcess>
#include <KStandardDirs>

// KDevelop
#include <language/duchain/identifier.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/types/unsuretype.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/parsingenvironment.h>
#include <language/duchain/persistentsymboltable.h>

// Ruby
#include <duchain/helpers.h>
#include <duchain/editorintegrator.h>
#include <duchain/declarations/methoddeclaration.h>
#include <duchain/declarations/variabledeclaration.h>
#include <duchain/types/classtype.h>


namespace Ruby
{
using namespace KDevelop;

const IndexedString & internalBuiltinsFile()
{
    static IndexedString doc_url(KStandardDirs::locate("data",
                                "kdevrubysupport/documentation/builtins.rb"));
    return doc_url;
}

const QString getName(RubyAst *ast)
{
    return QString(rb_name_node(ast->tree)->name);
}

const QByteArray getComment(RubyAst *ast)
{
    char *m_comment = ast->tree->comment;
    return (m_comment) ? QByteArray(m_comment) : QByteArray("");
}

DeclarationPointer getDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range,
                                  const DUContextPointer &context, DeclarationKind kind)
{
    QList<Declaration *> decls;

    // As specified by the documentation, the context *has* to be valid.
    Q_ASSERT(context);

    {
        DUChainReadLocker lock;

        /*
         * Search first for local declarations. If no local declarations have
         * been found, then take a look at imported contexts (e.g. method
         * arguments). Otherwise, we'll search for global declarations. If
         * we're still failing at getting a valid declaration, then we check
         * the PST. The PST will only go for classes, modules and methods.
         */
        decls = context->findLocalDeclarations(id.last(), range.end);
        if (decls.isEmpty()) {
            decls = context->findDeclarations(id.last(), range.end);
            if (decls.isEmpty()) {
                if (context.data() == context->topContext())
                    decls = context->topContext()->findDeclarations(id, range.end);
                else
                    decls = context->topContext()->findDeclarations(id);

                // If it's empty, then we're going for some PST time!
                if (decls.isEmpty()) {
                    lock.unlock();
                    return getDeclarationFromPST(id, context, kind);
                }
            }
        }
    }

    // Filter out unwanted class/instance methods.
    if (kind == ClassMethod || kind == InstanceMethod) {
        foreach (Declaration *d, decls) {
            MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(d);
            if (md && ((md->isClassMethod() && kind == ClassMethod) ||
                (!md->isClassMethod() && kind == InstanceMethod))) {
                return DeclarationPointer(d);
            }
        }
    }

    if (decls.isEmpty())
        return DeclarationPointer();
    return DeclarationPointer(decls.last());
}

DeclarationPointer getDeclarationFromPST(const QualifiedIdentifier &id,
                                         const DUContextPointer &context,
                                         DeclarationKind kind)
{
    // As specified by the documentation, the context *has* to be valid.
    Q_ASSERT(context);
    DUChainWriteLocker lock;

    uint nr;
    static const IndexedString lang("Ruby");
    const IndexedDeclaration *decls = nullptr;
    PersistentSymbolTable::self().declarations(id, nr, decls);

    for (uint i = 0; i < nr; ++i) {
        // Check that the file matches the environment.
        ParsingEnvironmentFilePointer env = DUChain::self()->environmentFileForDocument(decls[i].indexedTopContext());
        if(!env || env->language() != lang)
            continue;

        // It doesn't have a declaration, skipping.
        Declaration *d = decls[i].declaration();
        if (!d)
            continue;

        /*
         * Only global variables should be available for other files, but
         * global variables are always fetched by the getDeclaration method.
         * Therefore, at this point, we discard variable declarations.
         */
        if (dynamic_cast<VariableDeclaration *>(d))
            continue;

        // If it's a method declaration, check that we've got the proper one.
        if (kind != Unknown) {
            MethodDeclaration *mDecl = dynamic_cast<MethodDeclaration *>(d);
            if (mDecl) {
                if ((mDecl->isClassMethod() && kind != ClassMethod) ||
                    (!mDecl->isClassMethod() && kind != InstanceMethod)) {
                    continue;
                }
            }
        }

        // Get the declaration and add its top context to the current one.
        TopDUContext *top = decls[i].declaration()->context()->topContext();
        context->topContext()->addImportedParentContext(top);
        context->topContext()->parsingEnvironmentFile()
            ->addModificationRevisions(top->parsingEnvironmentFile()->allModificationRevisions());
        context->topContext()->updateImportsCache();
        return DeclarationPointer(decls[i].declaration());
    }
    return DeclarationPointer();
}

TypePtr<AbstractType> getBuiltinsType(const QString &desc, const DUContext *ctx)
{
    // As specified by the documentation, the context *has* to be valid.
    Q_ASSERT(ctx);

    DUChainReadLocker lock;
    QList<Declaration *> decls = ctx->topContext()->findDeclarations(QualifiedIdentifier(desc));
    Declaration *dec = (decls.isEmpty()) ? nullptr : decls.first();
    AbstractType::Ptr type = dec ? dec->abstractType() : AbstractType::Ptr(nullptr);
    return type;
}

DUContext * getClassContext(const DUContext *ctx)
{
    // As specified by the documentation, the context *has* to be valid.
    Q_ASSERT(ctx);

    DUChainReadLocker lock;
    StructureType::Ptr klass = StructureType::Ptr::dynamicCast(getBuiltinsType("Class", ctx));
    if (klass)
        return klass->declaration(ctx->topContext())->internalContext();
    return nullptr;
}

bool isUsefulType(const AbstractType::Ptr &type)
{
    if (!type)
        return false;
    if (type->whichType() != AbstractType::TypeIntegral) {
        ClassType::Ptr ct = ClassType::Ptr::dynamicCast(type);
        if (ct)
            return ct->isUseful();
        return true;
    }
    QList<uint> skipTypes;
    skipTypes << IntegralType::TypeMixed << IntegralType::TypeNone << IntegralType::TypeNull;
    if (!skipTypes.contains(type.cast<IntegralType>()->dataType()))
        return true;
    return false;
}

AbstractType::Ptr mergeTypes(AbstractType::Ptr type, AbstractType::Ptr newType)
{
    DUChainReadLocker lock;
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(type);
    UnsureType::Ptr newUnsure = UnsureType::Ptr::dynamicCast(newType);
    UnsureType::Ptr res;

    if (unsure && newUnsure) {
        int len = newUnsure->typesSize();
        for (int i = 0; i < len; i++)
            unsure->addType(newUnsure->types()[i]);
        res = unsure;
    } else if (unsure) {
        if (isUsefulType(newType))
            unsure->addType(newType->indexed());
        res = unsure;
    } else if (newUnsure) {
        UnsureType::Ptr cloned = UnsureType::Ptr(static_cast<UnsureType *>(newUnsure->clone()));
        if (isUsefulType(type))
            cloned->addType(type->indexed());
        res = cloned;
    } else {
        unsure = UnsureType::Ptr(new UnsureType());
        if (isUsefulType(type))
            unsure->addType(type->indexed());
        if (isUsefulType(newType))
            unsure->addType(newType->indexed());
        res = unsure;
    }

    if (res->typesSize() == 0)
        return type;
    if (res->typesSize() == 1)
        return res->types()[0].abstractType();
    return AbstractType::Ptr::staticCast(res);
}

int nodeListSize(Node *node)
{
    int i = 0;
    for (Node *n = node; n != nullptr; n = n->next, i++);
    return i;
}

const QualifiedIdentifier getIdentifier(const RubyAst *ast)
{
    NameAst nameAst(ast);
    return KDevelop::QualifiedIdentifier(nameAst.value);
}


} // End of namespace Ruby
