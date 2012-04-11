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
#include <language/duchain/aliasdeclaration.h>

// Ruby
#include <rubydefs.h>
#include <duchain/editorintegrator.h>
#include <duchain/expressionvisitor.h>
#include <duchain/types/objecttype.h>


using namespace KDevelop;
namespace Ruby
{

ExpressionVisitor::ExpressionVisitor(DUContext *ctx, EditorIntegrator *editor)
    : m_ctx(ctx), m_editor(editor), m_lastDeclaration(NULL), m_alias(false)
{
    /* There's nothing to do here! */
}

void ExpressionVisitor::visitVariable(RubyAst *node)
{
    debug() << "HERE !!! " << node->tree->name;
}

void ExpressionVisitor::visitName(RubyAst *node)
{
    QualifiedIdentifier id = QualifiedIdentifier(QString(node->tree->name));
    const CursorInRevision cursor = m_editor->findPosition(node->tree, EditorIntegrator::FrontEdge);
    QList<Declaration *> decls = m_ctx->findDeclarations(id.first(), cursor, 0, DUContext::DontSearchInParent);
    if (!decls.isEmpty()) {
        Declaration *d = decls.last();
        m_alias = dynamic_cast<AliasDeclaration *>(d);
        m_lastDeclaration = d;
        encounter(d->abstractType());
    } else {
        debug() << "Declaration NOT FOUND";
    }
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

void ExpressionVisitor::visitString(RubyAst *node)
{
    debug() << "EXPRESSION";
    RubyAstVisitor::visitString(node);
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

void ExpressionVisitor::visitSymbol(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("Symbol", m_ctx);
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
