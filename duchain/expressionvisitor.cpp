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
#include <language/duchain/declaration.h>

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
    AbstractType::Ptr obj = getBuiltinsType("String", m_ctx);
    if (obj != AbstractType::Ptr(NULL))
        debug() << obj->toString();
    else
        debug() << "OOPS";
    encounter(obj);
}

void ExpressionVisitor::visitNumeric(RubyAst *)
{
    // TODO: what about Float ?
    debug() << "==== Is a Numeric";
    AbstractType::Ptr obj = getBuiltinsType("Fixnum", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitRegexp(RubyAst *)
{
    debug() << "==== Is a Regexp";
    AbstractType::Ptr obj = getBuiltinsType("Regexp", m_ctx);
    encounter(obj);
}

TypePtr<AbstractType> ExpressionVisitor::getBuiltinsType(const QString &desc, DUContext *ctx)
{
    QList<Declaration *> decls = ctx->topContext()->findDeclarations(QualifiedIdentifier(desc));
    Declaration *dec = (decls.isEmpty()) ? NULL : decls.first();
    if (!dec)
        debug() << "EMPTY";
    else
        debug() << "** It exists " << dec->toString();
    AbstractType::Ptr type = dec ? dec->abstractType() : AbstractType::Ptr(NULL);
    if (!type)
        debug() << "NO TYPE";
    else
        debug() << "HERE WE GO " << type->toString();
//     debug() << "Builtins: " << type->toString();
    return type;
}

void ExpressionVisitor::encounter(AbstractType::Ptr type)
{
    m_lastType.push(type);
}

} // End of namespace Ruby
