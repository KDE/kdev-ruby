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
}

void ExpressionVisitor::visitVariable(RubyAst* node)
{
    debug() << "HERE !!! " << node->tree->name;
}

void ExpressionVisitor::visitTrue(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("TrueClass", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitFalse(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("FalseClass", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitNil(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("NilClass", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitFile(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("String", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitLine(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("Fixnum", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitEncoding(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("Encoding", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitSelf(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("Object", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitRange(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("Range", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitString(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("String", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitNumeric(RubyAst *)
{
    // TODO: what about Float ?
    AbstractType::Ptr obj = getBuiltinsType("Fixnum", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitRegexp(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("Regexp", m_ctx);
    encounter(obj);
}

TypePtr<AbstractType> ExpressionVisitor::getBuiltinsType(const QString &desc, DUContext *ctx)
{
    QList<Declaration *> decls = ctx->topContext()->findDeclarations(QualifiedIdentifier(desc));
    Declaration *dec = (decls.isEmpty()) ? NULL : decls.first();
    AbstractType::Ptr type = dec ? dec->abstractType() : AbstractType::Ptr(NULL);
    return type;
}

void ExpressionVisitor::encounter(AbstractType::Ptr type)
{
    m_lastType.push(type);
}

} // End of namespace Ruby
