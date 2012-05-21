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
#include <language/duchain/types/integraltype.h>

// Ruby
#include <rubydefs.h>
#include <duchain/editorintegrator.h>
#include <duchain/expressionvisitor.h>
#include <duchain/declarations/methoddeclaration.h>
#include <duchain/declarations/classdeclaration.h>
#include <duchain/helpers.h>


using namespace KDevelop;
namespace Ruby
{

ExpressionVisitor::ExpressionVisitor(DUContext *ctx, EditorIntegrator *editor)
    : m_ctx(ctx), m_editor(editor), m_lastDeclaration(NULL), m_alias(false)
{
    m_lastType = AbstractType::Ptr(NULL);
}

ExpressionVisitor::ExpressionVisitor(ExpressionVisitor *parent)
    : m_ctx(parent->m_ctx), m_editor(parent->m_editor),
        m_lastDeclaration(NULL), m_alias(false)
{
    m_lastType = AbstractType::Ptr(NULL);
}

void ExpressionVisitor::visitVariable(RubyAst *node)
{
    debug() << "HERE !!! " << node->tree->name;
}

void ExpressionVisitor::visitName(RubyAst *node)
{
    if (!node->tree) // TODO: clean, it shouldn't happen, but it does :(
        return;
    QualifiedIdentifier id = getIdentifier(node);
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
    RubyAstVisitor::visitString(node);
    AbstractType::Ptr obj = getBuiltinsType("String", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitNumeric(RubyAst *node)
{
    const char * type = is_float(node->tree) ? "Float" : "Fixnum";
    AbstractType::Ptr obj = getBuiltinsType(type, m_ctx);
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

void ExpressionVisitor::visitArray(RubyAst *node)
{
    RubyAstVisitor::visitArray(node);
    AbstractType::Ptr obj = getBuiltinsType("Array", m_ctx);
    VariableLengthContainer::Ptr ptr = getContainer(obj, node);
    encounter<VariableLengthContainer>(ptr);
}

void ExpressionVisitor::visitHash(RubyAst *node)
{
    RubyAstVisitor::visitHash(node);
    AbstractType::Ptr obj = getBuiltinsType("Hash", m_ctx);
    VariableLengthContainer::Ptr ptr = getContainer(obj, node, true);
    encounter<VariableLengthContainer>(ptr);
}

void ExpressionVisitor::visitArrayValue(RubyAst *node)
{
    RubyAstVisitor::visitArrayValue(node);
    RubyAst *child = new RubyAst(node->tree->l, node->context);
    QualifiedIdentifier id = getIdentifier(child);
    const CursorInRevision cursor = m_editor->findPosition(child->tree, EditorIntegrator::FrontEdge);
    QList<Declaration *> decls = m_ctx->findDeclarations(id.first(), cursor, 0, DUContext::DontSearchInParent);
    if (!decls.isEmpty()) {
        Declaration *d = decls.first();
        VariableLengthContainer::Ptr vc = d->abstractType().cast<VariableLengthContainer>();
        if (vc)
            encounter(vc->contentType().type<AbstractType>());
    }
    delete child;
}

void ExpressionVisitor::visitMethodCall(RubyAst *node)
{
    RubyAstVisitor::visitMethodCall(node);
    // TODO: visit parameters ?

    Declaration *decl = findDeclarationForCall(node, m_ctx);
    if (decl) {
        AbstractType::Ptr type;
        ClassDeclaration *cd = dynamic_cast<ClassDeclaration *>(decl);
        MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(decl);
        m_lastDeclaration = decl;
        if (md) {
            // TODO
        } else if (cd) {
            type = cd->abstractType();
            encounter(type);
        } else
            debug() << "Found declaration is not callable";
    } else
        debug() << "Declaration not found";
}

void ExpressionVisitor::visitLambda(RubyAst *node)
{
    RubyAstVisitor::visitLambda(node);
    AbstractType::Ptr obj = getBuiltinsType("Proc", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitParameter(RubyAst *node)
{
    AbstractType::Ptr obj;

    if (is_block_arg(node->tree)) {
        obj = getBuiltinsType("Proc", m_ctx);
    } else if (is_rest_arg(node->tree)) {
        obj = getBuiltinsType("Array", m_ctx);
        obj.cast<VariableLengthContainer>();
    } else if (node->tree->r != NULL) {
        ExpressionVisitor da(this);
        Node *n = node->tree;
        node->tree = node->tree->r;
        da.visitNode(node);
        node->tree = n;
        obj = da.lastType();
    } else
        obj = AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed));
    encounter(obj);
}

TypePtr<AbstractType> ExpressionVisitor::getBuiltinsType(const QString &desc, DUContext *ctx)
{
    QList<Declaration *> decls = ctx->topContext()->findDeclarations(QualifiedIdentifier(desc));
    Declaration *dec = (decls.isEmpty()) ? NULL : decls.first();
    AbstractType::Ptr type = dec ? dec->abstractType() : AbstractType::Ptr(NULL);
    return type;
}

template <typename T> void ExpressionVisitor::encounter(TypePtr<T> type)
{
    encounter(AbstractType::Ptr::staticCast(type));
}

VariableLengthContainer::Ptr ExpressionVisitor::getContainer(AbstractType::Ptr ptr, const RubyAst *node, bool hasKey)
{
    VariableLengthContainer::Ptr vc = ptr.cast<VariableLengthContainer>();
    if (vc) {
        ExpressionVisitor ev(this);
        RubyAst *ast = new RubyAst(node->tree->l, node->context);
        for (Node *n = ast->tree; n != NULL; n = n->next) {
            (hasKey) ? ev.visitBinary(ast) : ev.visitNode(ast);
            vc->addContentType(ev.lastType());
            ast->tree = n->next;
        }
        delete ast;
    } else
        kWarning() << "Something went wrong! Fix code...";
    return vc;
}

Declaration * ExpressionVisitor::findDeclarationForCall(RubyAst *ast, DUContext *ctx)
{
    DUChainReadLocker lock(DUChain::lock());
    DUContext *lastCtx = ctx;
    QList<Declaration *> stack, aux;
    RubyAst *left = new RubyAst(ast->tree->l, ast->context);

    for (Node *n = ast->tree->l; n != NULL; n = n->next) {
        left->tree = n;
        QualifiedIdentifier id = getIdentifier(left);
        aux = lastCtx->findDeclarations(id.last());
        aux << findInternalDeclaration(lastCtx, id.last()); // TODO: clean this
        if (!aux.empty() && aux.last()) {
            stack << aux.last();
            if (aux.last()->internalContext())
                lastCtx = aux.last()->internalContext();
        } else
            debug() << "Something went wrong : " << getIdentifier(left).toString();
    }

    // TODO: should be handled in a more formal way
    if (stack.size() > 1 && stack.last()->identifier().toString() == "new")
        return stack.at(stack.size() - 2);
    return (!stack.isEmpty()) ? stack.last() : NULL;
}

const QualifiedIdentifier ExpressionVisitor::getIdentifier(const RubyAst *ast)
{
    NameAst nameAst(ast);
    QualifiedIdentifier name = QualifiedIdentifier(nameAst.value);
    return name;
}

Declaration * ExpressionVisitor::findInternalDeclaration(DUContext *ctx, const KDevelop::Identifier &id)
{
    DUChainReadLocker lock(DUChain::lock());
    foreach (Declaration *d, ctx->localDeclarations())
        if (d->identifier() == id)
            return d;
    return NULL;
}

} // End of namespace Ruby
