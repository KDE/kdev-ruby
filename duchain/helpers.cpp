/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// Qt + KDE
#include <QtCore/QProcess>
#include <QtCore/QStandardPaths>

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
#include <duchain/declarations/moduledeclaration.h>
#include <duchain/declarations/variabledeclaration.h>
#include <duchain/types/classtype.h>

using namespace KDevelop;
namespace ruby {

// The following anonymous namespace contains helper functions that should not
// be exported outside.
namespace {

/**
 * @returns true if the given @p type is useful, and false otherwise.
 */
bool isUsefulType(const AbstractType::Ptr &type)
{
    if (!type) {
        return false;
    }
    if (type->whichType() != AbstractType::TypeIntegral) {
        auto ct = type.dynamicCast<ClassType>();
        if (ct) {
            return ct->isUseful();
        }
        return true;
    }

    const auto &data = type.staticCast<IntegralType>()->dataType();
    return data == IntegralType::TypeMixed ||
           data == IntegralType::TypeNone ||
           data == IntegralType::TypeNull;
}

/**
 * Find a declaration from the Persistent Symbol Table.
 *
 * @param id The qualified indentifier of the declaration.
 * @param context The current context.
 * @param kind The kind of the declaration.
 * @returns the first declaration that matches the given parameters from
 * the Persistent Symbol Table.
 * @note The given context has to be valid.
 * @note This method already acquires a write lock for the DUChain.
 */
DeclarationPointer getDeclarationFromPST(const QualifiedIdentifier &id,
                                         const DUContextPointer &context,
                                         DeclarationKind kind)
{
    DeclarationPointer ret;

    // As specified by the documentation, the context *has* to be valid.
    Q_ASSERT(context);

    DUChainWriteLocker lock;
    auto visitor = [&](const IndexedDeclaration &indexedDeclaration) {
        // Check that the file matches the environment.
        auto env = DUChain::self()->environmentFileForDocument(indexedDeclaration.indexedTopContext());
        if(!env || env->language() != languageString()) {
            return PersistentSymbolTable::VisitorState::Continue;
        }

        // It doesn't have a declaration, skipping.
        Declaration *d = indexedDeclaration.declaration();
        if (!d) {
            return PersistentSymbolTable::VisitorState::Continue;
        }

        /*
         * Only global variables should be available for other files, but
         * global variables are always fetched by the getDeclaration method.
         * Therefore, at this point, we discard variable declarations.
         */
        if (dynamic_cast<VariableDeclaration *>(d)) {
            return PersistentSymbolTable::VisitorState::Continue;
        }

        // If it's a method declaration, check that we've got the proper one.
        if (kind != DeclarationKind::Unknown) {
            MethodDeclaration *mDecl = dynamic_cast<MethodDeclaration *>(d);
            if (mDecl) {
                // TODO: remove this.
                if ((mDecl->isClassMethod() && kind != DeclarationKind::ClassMethod) ||
                    (!mDecl->isClassMethod() && kind != DeclarationKind::InstanceMethod)) {
                    return PersistentSymbolTable::VisitorState::Continue;
                }
            }
        }

        // Get the declaration and add its top context to the current one.
        TopDUContext *top = d->context()->topContext();
        auto mods = top->parsingEnvironmentFile()->allModificationRevisions();
        context->topContext()->addImportedParentContext(top);
        context->topContext()->parsingEnvironmentFile()->addModificationRevisions(mods);
        context->topContext()->updateImportsCache();
        ret = d;
        return PersistentSymbolTable::VisitorState::Break;
    };
    PersistentSymbolTable::self().visitDeclarations(id, visitor);

    return ret;
}

}

const IndexedString & languageString()
{
    static const IndexedString lang("Ruby");
    return lang;
}

const IndexedString & builtinsFile()
{
    const auto &rb = QStringLiteral("kdevrubysupport/documentation/builtins.rb");
    static IndexedString doc(QStandardPaths::locate(
                                QStandardPaths::GenericDataLocation, rb));
    return doc;
}

const QString getName(Ast *ast)
{
    return QString(rb_name_node(ast->tree)->name);
}

const QByteArray getComment(Ast *ast)
{
    char *m_comment = ast->tree->comment;
    return (m_comment) ? QByteArray(m_comment) : QByteArray("");
}

DeclarationPointer getDeclaration(const QualifiedIdentifier &id,
                                  const RangeInRevision &range,
                                  const DUContextPointer &context,
                                  DeclarationKind kind)
{
    QList<Declaration *> decls;

    // As specified by the documentation, the context *has* to be valid.
    Q_ASSERT(context);

    {
        DUChainReadLocker lock;

        // If this is a class method, look at the eigen class and get out.
        if (kind == DeclarationKind::ClassMethod ||
            kind == DeclarationKind::Unknown) {

            Declaration *d = context->owner();
            ModuleDeclaration *md = dynamic_cast<ModuleDeclaration *>(d);
            if (md) {
                DUContext *ctx = md->eigenClass();
                if (ctx) {
                    decls = ctx->findLocalDeclarations(id.last(), range.end);
                    if (!decls.isEmpty()) {
                        return DeclarationPointer(decls.last());
                    }
                }
            }
            kind = DeclarationKind::Unknown;
        }

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
            if (decls.isEmpty() && kind != DeclarationKind::Local) {
                if (context.data() == context->topContext()) {
                    decls = context->topContext()->findDeclarations(id, range.end);
                } else {
                    decls = context->topContext()->findDeclarations(id);
                }

                // If it's empty, then we're going for some PST time!
                if (decls.isEmpty() && kind != DeclarationKind::ClassMethod) {
                    lock.unlock();
                    return getDeclarationFromPST(id, context, kind);
                }
            }
        }
    }

    if (decls.isEmpty()) {
        return DeclarationPointer();
    }
    return DeclarationPointer(decls.last());
}

TypePtr<AbstractType> getBuiltinsType(const QString &desc,
                                      const DUContext *ctx)
{
    // As specified by the documentation, the context *has* to be valid.
    Q_ASSERT(ctx);

    DUChainReadLocker lock;
    auto decls = ctx->topContext()->findDeclarations(QualifiedIdentifier(desc));
    Declaration *dec = (decls.isEmpty()) ? nullptr : decls.first();
    AbstractType::Ptr type = dec ? dec->abstractType() : AbstractType::Ptr(nullptr);
    return type;
}

DUContext * getClassContext(const DUContext *ctx)
{
    // As specified by the documentation, the context *has* to be valid.
    Q_ASSERT(ctx);

    DUChainReadLocker lock;
    const auto &type = getBuiltinsType(QStringLiteral("Class"), ctx);
    auto klass = type.dynamicCast<StructureType>();
    if (klass) {
        return klass->declaration(ctx->topContext())->internalContext();
    }
    return nullptr;
}

AbstractType::Ptr mergeTypes(AbstractType::Ptr type, AbstractType::Ptr newType)
{
    DUChainReadLocker lock;
    auto unsure = type.dynamicCast<UnsureType>();
    auto newUnsure = newType.dynamicCast<UnsureType>();
    UnsureType::Ptr res;

    if (unsure && newUnsure) {
        int len = newUnsure->typesSize();
        for (int i = 0; i < len; i++) {
            unsure->addType(newUnsure->types()[i]);
        }
        res = unsure;
    } else if (unsure) {
        if (isUsefulType(newType)) {
            unsure->addType(newType->indexed());
        }
        res = unsure;
    } else if (newUnsure) {
        UnsureType::Ptr cloned = UnsureType::Ptr(static_cast<UnsureType *>(newUnsure->clone()));
        if (isUsefulType(type)) {
            cloned->addType(type->indexed());
        }
        res = cloned;
    } else {
        unsure = UnsureType::Ptr(new UnsureType());
        if (isUsefulType(type)) {
            unsure->addType(type->indexed());
        } if (isUsefulType(newType)) {
            unsure->addType(newType->indexed());
        }
        res = unsure;
    }

    if (res->typesSize() == 0) {
        return type;
    }
    if (res->typesSize() == 1) {
        return res->types()[0].abstractType();
    }
    return res;
}

int nodeListSize(Node *node)
{
    int i = 0;
    for (Node *n = node; n; n = n->next, i++);
    return i;
}

const QualifiedIdentifier getIdentifier(const Ast *ast)
{
    NameAst nameAst(ast);
    return KDevelop::QualifiedIdentifier(nameAst.value);
}

bool declaredIn(const QByteArray &name, DUContextPointer context)
{
    DUChainReadLocker lock;
    KDevelop::QualifiedIdentifier id = QualifiedIdentifier(QString(name));
    QList<Declaration *> decls = context->findLocalDeclarations(id.last());
    return !decls.empty();
}

}
