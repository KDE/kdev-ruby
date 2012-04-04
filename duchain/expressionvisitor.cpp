/*
 * This file is part of KDevelop
 * Copyright 2012  Miquel Sabaté <mikisabate@gmail.com>
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


// KDevelop
#include <language/duchain/topducontext.h>

// Ruby
#include <rubydefs.h>
#include <duchain/expressionvisitor.h>
#include <duchain/types/objecttype.h>


using namespace KDevelop;
namespace Ruby
{

ExpressionVisitor::ExpressionVisitor(DUContext *ctx, EditorIntegrator *editor)
    : m_ctx(ctx)
{
    /* TODO */
    Q_UNUSED(editor)
    /* TODO */
}

void ExpressionVisitor::visitString(RubyAst *)
{
    debug() << "==== Is a string!!";
    ObjectType::Ptr obj = getBuiltinsType("String", m_ctx);
    encounter(obj);
}

TypePtr<ObjectType> ExpressionVisitor::getBuiltinsType(const QString &desc, DUContext *ctx)
{
    debug() << "TOP CONTEXT AT: " << ctx->topContext()->topContext()->url().byteArray();
    QList<Declaration *> decls = ctx->topContext()->findDeclarations(QualifiedIdentifier(desc));
    debug() << "GET BUILTINS";
    if (decls.isEmpty()) {
        debug() << "IS EMPTY";
    } else
        debug() << "getBuiltinsType: " << decls.first();
    /* TODO */
    Q_UNUSED(desc)
    Q_UNUSED(ctx)
    ObjectType::Ptr type = ObjectType::Ptr(new ObjectType());
    return type;
    /* TODO */
}

void ExpressionVisitor::encounter(AbstractType::Ptr type)
{
    m_lastType.push(type);
}

void ExpressionVisitor::encounter(TypePtr<ObjectType> type)
{
    encounter(AbstractType::Ptr::staticCast(type));
}

} // End of namespace Ruby
