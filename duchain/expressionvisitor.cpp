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
#include <language/duchain/types/functiontype.h>

// Ruby
#include <rubydefs.h>
#include <duchain/helpers.h>
#include <duchain/editorintegrator.h>
#include <duchain/expressionvisitor.h>
#include <duchain/declarations/methoddeclaration.h>
#include <duchain/declarations/classdeclaration.h>


using namespace KDevelop;
namespace Ruby
{

ExpressionVisitor::ExpressionVisitor(DUContext *ctx, EditorIntegrator *editor)
    : m_ctx(ctx), m_editor(editor), m_lastDeclaration(NULL), m_alias(false)
{
    m_lastType = AbstractType::Ptr(NULL);
    m_lastCtx = NULL;
}

ExpressionVisitor::ExpressionVisitor(ExpressionVisitor *parent)
    : m_ctx(parent->m_ctx), m_editor(parent->m_editor),
        m_lastDeclaration(NULL), m_alias(false)
{
    m_lastType = AbstractType::Ptr(NULL);
    m_lastCtx = NULL;
}

void ExpressionVisitor::setContext(DUContext *ctx)
{
    m_ctx = ctx;
    m_lastType = AbstractType::Ptr(NULL);
    m_lastDeclaration = NULL;
    m_alias = false;
    m_lastCtx = NULL;
}

void ExpressionVisitor::visitParameter(RubyAst *node)
{
    AbstractType::Ptr obj;

    if (is_block_arg(node->tree)) {
        obj = getBuiltinsType("Proc", m_ctx);
    } else if (is_rest_arg(node->tree)) {
        obj = getBuiltinsType("Array", m_ctx);
        obj.cast<ClassType>();
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

void ExpressionVisitor::visitName(RubyAst *node)
{
    if (!node->tree)
        return;

    DUChainReadLocker lock(DUChain::lock());
    QualifiedIdentifier id = getIdentifier(node);
    RangeInRevision range = m_editor->findRange(node->tree);
    Declaration * decl = getDeclaration(id, range, DUContextPointer(m_ctx));

    if (decl) {
        m_alias = dynamic_cast<AliasDeclaration *>(decl);
        m_lastDeclaration = decl;
        encounter(decl->abstractType());
    } else
        debug() << "Declaration NOT FOUND";
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
    AbstractType::Ptr obj;
    if (m_ctx->owner()) {
        obj = m_ctx->owner()->abstractType();
        m_lastDeclaration = DeclarationPointer(m_ctx->owner());
    } else
        obj = getBuiltinsType("Object", m_ctx);
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
    ClassType::Ptr ptr = getContainer(obj, node);
    encounter<ClassType>(ptr);
}

void ExpressionVisitor::visitHash(RubyAst *node)
{
    RubyAstVisitor::visitHash(node);
    AbstractType::Ptr obj = getBuiltinsType("Hash", m_ctx);
    ClassType::Ptr ptr = getContainer(obj, node, true);
    encounter<ClassType>(ptr);
}

void ExpressionVisitor::visitArrayValue(RubyAst *node)
{
    DUChainReadLocker lock(DUChain::lock());
    RubyAstVisitor::visitArrayValue(node);
    RubyAst *child = new RubyAst(node->tree->l, node->context);
    QualifiedIdentifier id = getIdentifier(child);
    const CursorInRevision cursor = m_editor->findPosition(child->tree, EditorIntegrator::FrontEdge);
    QList<Declaration *> decls = m_ctx->findDeclarations(id.first(), cursor, 0, DUContext::DontSearchInParent);
    if (!decls.isEmpty()) {
        Declaration *d = decls.first();
        ClassType::Ptr vc = d->abstractType().cast<ClassType>();
        if (vc)
            encounter(vc->contentType().abstractType());
    }
    delete child;
}

void ExpressionVisitor::visitMethodCall(RubyAst *node)
{
    DUChainReadLocker rlock(DUChain::lock());
    Node *n = node->tree;

    node->tree = n->l;
    if (node->tree->kind == token_method_call)
        visitMethodCall(node);
    visitMethodCallMembers(node);
    node->tree = n;
}

void ExpressionVisitor::visitSuper(RubyAst *node)
{
    // TODO
}

void ExpressionVisitor::visitLambda(RubyAst *node)
{
    RubyAstVisitor::visitLambda(node);
    AbstractType::Ptr obj = getBuiltinsType("Proc", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitWhileStatement(RubyAst *)
{
    AbstractType::Ptr obj = getBuiltinsType("NilClass", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitForStatement(RubyAst *node)
{
    ExpressionVisitor ev(this);
    Node *n = node->tree;
    node->tree = n->l;
    RubyAstVisitor::visitNode(node);
    node->tree = n->cond;
    ev.visitNode(node);
    node->tree = n;
    encounter(ev.lastType());
}

void ExpressionVisitor::visitBinary(RubyAst *node)
{
    Node *n = node->tree;
    node->tree = node->tree->l;
    ExpressionVisitor ev(this);
    ev.visitNode(node);
    AbstractType::Ptr left = ev.lastType();
    node->tree = n->r;
    ev.visitNode(node);
    node->tree = n;
    encounter(mergeTypes(left, ev.lastType()));
}

void ExpressionVisitor::visitBoolean(RubyAst *)
{
    AbstractType::Ptr truthy = getBuiltinsType("TrueClass", m_ctx);
    AbstractType::Ptr falsy = getBuiltinsType("FalseClass", m_ctx);
    encounter(mergeTypes(truthy, falsy));
}

void ExpressionVisitor::visitIfStatement(RubyAst *node)
{
    RubyAstVisitor::visitIfStatement(node);
    Node *aux = node->tree;
    node->tree = aux->l;
    ExpressionVisitor::visitLastStatement(node);
    AbstractType::Ptr res = lastType();

    for (Node *n = aux->r; n != NULL; n = n->r) {
        node->tree = n;
        ExpressionVisitor::visitLastStatement(node);
        res = mergeTypes(res, lastType());
    }
    encounter(res);
    node->tree = aux;
}

void ExpressionVisitor::visitCaseStatement(RubyAst *node)
{
    RubyAstVisitor::visitCaseStatement(node);
    Node *aux = node->tree;
    AbstractType::Ptr res;

    for (Node *n = aux->l; n != NULL; n = n->r) {
        node->tree = n->l;
        ExpressionVisitor::visitLastStatement(node);
        res = mergeTypes(res, lastType());
    }
    encounter(res);
    node->tree = aux;
}

template <typename T> void ExpressionVisitor::encounter(TypePtr<T> type)
{
    encounter(AbstractType::Ptr::staticCast(type));
}

ClassType::Ptr ExpressionVisitor::getContainer(AbstractType::Ptr ptr, const RubyAst *node, bool hasKey)
{
    ClassType::Ptr ct = ptr.cast<ClassType>();
    if (ct) {
        ExpressionVisitor ev(this);
        RubyAst *ast = new RubyAst(node->tree->l, node->context);
        for (Node *n = ast->tree; n != NULL; n = n->next) {
            if (hasKey) {
                Node *aux = ast->tree;
                ast->tree = ast->tree->r;
                ev.visitNode(ast);
                ast->tree = aux;
            } else
                ev.visitNode(ast);
            ct->addContentType(ev.lastType());
            ast->tree = n->next;
        }
        delete ast;
    } else
        kWarning() << "Something went wrong! Fix code...";
    return ct;
}

void ExpressionVisitor::visitLastStatement(RubyAst *node)
{
    if (!node->tree)
        return;

    Node *n = node->tree;
    if (n->last)
        node->tree = n->last;
    ExpressionVisitor::visitNode(node);
    node->tree = n;
}

void ExpressionVisitor::visitMethodCallMembers(RubyAst *node)
{
    RangeInRevision range;
    DUContext *ctx = (m_lastCtx) ? m_lastCtx : m_ctx;
    ExpressionVisitor ev(this);

    /*
     * Go to the next element since we're coming from a recursion and we've
     * already checked its children nodes.
     */
    if (node->tree->kind == token_method_call)
        node->tree = node->tree->next;

    // And this is the loop that does the dirty job.
    for (Node *aux = node->tree; aux; aux = aux->next) {
        node->tree = aux;
        range = m_editor->findRange(node->tree);
        ev.setContext(ctx);
        ev.visitNode(node);
        m_lastDeclaration = ev.lastDeclaration().data();
        StructureType::Ptr sType = StructureType::Ptr::dynamicCast(ev.lastType());

        /*
         * If this is a StructureType, it means that we're in a case like;
         * "A::B::" and therefore the next context should be A::B.
         */
        if (!sType) {
            // It's not a StructureType, therefore it's a variable or a method.
            FunctionType::Ptr fType = FunctionType::Ptr::dynamicCast(ev.lastType());
            if (!fType)
                ctx = (m_lastDeclaration) ? m_lastDeclaration->internalContext() : NULL;
            else {
                StructureType::Ptr rType = StructureType::Ptr::dynamicCast(fType->returnType());
                if (rType) {
                    encounter(fType->returnType());
                    ctx = rType->internalContext(ctx->topContext());
                } else
                    ctx = NULL;
            }
        } else {
            encounter(ev.lastType());
            ctx = sType->internalContext(ctx->topContext());
        }

        // No context found, we can't go any further.
        if (!ctx)
            return;
    }
    m_lastCtx = ctx;
}

} // End of namespace Ruby
