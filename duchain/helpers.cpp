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

// Ruby
#include <duchain/helpers.h>
#include <duchain/editorintegrator.h>
#include <duchain/declarations/methoddeclaration.h>
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
    return (m_comment != NULL) ? QByteArray(m_comment) : QByteArray("");
}

Declaration * getDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range, DUContextPointer context)
{
    QList<Declaration *> decls;

    {
        /*
         * Find the declarations at the topContext(). If no declaration was
         * found, we have to look for local declarations. If this fails, we
         * should find for global declarations.
         */
        DUChainReadLocker lock(DUChain::lock());
        if (context.data() == context->topContext())
            decls = context->topContext()->findDeclarations(id, range.end);
        else
            decls = context->topContext()->findDeclarations(id, CursorInRevision::invalid());
        if (!decls.length()) {
            decls = context->findLocalDeclarations(id.last(), range.end);
            if (!decls.length())
                decls = context->findDeclarations(id.last(), range.end);
        }
    }
    return (decls.length()) ? decls.last() : NULL;
}

TypePtr<AbstractType> getBuiltinsType(const QString &desc, DUContext *ctx)
{
    DUChainReadLocker lock(DUChain::lock());
    QList<Declaration *> decls = ctx->topContext()->findDeclarations(QualifiedIdentifier(desc));
    Declaration *dec = (decls.isEmpty()) ? NULL : decls.first();
    AbstractType::Ptr type = dec ? dec->abstractType() : AbstractType::Ptr(NULL);
    return type;
}

bool isUsefulType(AbstractType::Ptr type)
{
    if (!type)
        return false;
    if (type->whichType() != AbstractType::TypeIntegral)
        return true;
    QList<uint> skipTypes;
    skipTypes << IntegralType::TypeMixed << IntegralType::TypeNone << IntegralType::TypeNull;
    if (!skipTypes.contains(type.cast<IntegralType>()->dataType()))
        return true;
    return false;
}

AbstractType::Ptr mergeTypes(AbstractType::Ptr type, AbstractType::Ptr newType)
{
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

    if (res->typesSize() == 1)
        return res->types()[0].abstractType();
    return AbstractType::Ptr::staticCast(res);
}

int nodeListSize(Node *node)
{
    int i = 0;
    for (Node *n = node; n != NULL; n = n->next, i++);
    return i;
}

const QualifiedIdentifier getIdentifier(const RubyAst *ast)
{
    NameAst nameAst(ast);
    return KDevelop::QualifiedIdentifier(nameAst.value);
}

} // End of namespace Ruby

