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
#include <duchain/types/classtype.h>


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
    DUChainReadLocker lock(DUChain::lock());
    QualifiedIdentifier id = getIdentifier(node);
//     const CursorInRevision cursor = m_editor->findPosition(node->tree, EditorIntegrator::FrontEdge);
    Declaration * decl = getDeclaration(id, m_editor->findRange(node->tree), DUContextPointer(m_ctx));
//     QList<Declaration *> decls = m_ctx->findDeclarations(id.first(), cursor, 0, DUContext::DontSearchInParent);
    if (decl) {
//         Declaration *d = decls.last();
        m_alias = dynamic_cast<AliasDeclaration *>(decl);
        m_lastDeclaration = decl;
        encounter(decl->abstractType());
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
//     DeclarationPointer test = getDeclarationForCall(node, m_ctx);
//     DUChainReadLocker lock(DUChain::lock());
    Node *n = node->tree;
    node->tree = n->l;
    visitNode(node);
    node->tree = n;
//     if (test) {
//         AbstractType::Ptr type;
//         ClassDeclaration *cd = dynamic_cast<ClassDeclaration *>(test.data());
//         MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(test.data());
//         if (md && md->type<FunctionType>()) {
//             type = md->type<FunctionType>()->returnType();
//             encounter(type);
//         } else if (cd) {
//             type = cd->abstractType();
//             encounter(type);
//         } else
//             debug() << "Found declaration is not callable";
//     } else
//         debug() << "Declaration not found";
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

DeclarationPointer ExpressionVisitor::getDeclarationForCall(RubyAst *ast, DUContext *ctx)
{
    DUChainReadLocker lock(DUChain::lock());
    DUContext *aux, *lastCtx = ctx;
    RubyAst *left = new RubyAst(ast->tree->l, ast->context);
    // HACK: this makes the Klass.new case to work. It should be implemented
    // in a way that the "new" method is already inside a class definition
    // without defining it.
    DeclarationPointer last;

    for (Node *n = ast->tree->l; n != NULL; n = n->next) {
        left->tree = n;
        QualifiedIdentifier id = getIdentifier(left);
        aux = getDeclarationInternalContext(id, lastCtx);
        if (!aux)
            return (m_lastDeclaration) ? m_lastDeclaration : last;
        last = m_lastDeclaration;
        lastCtx = aux;
    }
    return DeclarationPointer(NULL);
}

DUContext * ExpressionVisitor::getDeclarationInternalContext(const QualifiedIdentifier &id, DUContext *ctx)
{
    QList<Declaration *> aux = ctx->findDeclarations(id);
    m_lastDeclaration = NULL;
    if (aux.isEmpty())
        return NULL;

    Declaration * last = aux.last();
    // HACK: should be the last instruction before "return NULL", but in this way
    // the hack from getDeclarationForCall works.
    m_lastDeclaration = last;
    ClassType::Ptr ct = last->type<ClassType>();
    if (ct) {
        IdentifiedType *it = dynamic_cast<IdentifiedType *>(ct.unsafeData());
        return it->declaration(ctx->topContext())->internalContext();
    }
    return NULL;
}

} // End of namespace Ruby
