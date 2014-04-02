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
#include <language/duchain/types/unsuretype.h>

// Ruby
#include <duchain/helpers.h>
#include <duchain/editorintegrator.h>
#include <duchain/expressionvisitor.h>
#include <duchain/declarations/methoddeclaration.h>
#include <duchain/declarations/moduledeclaration.h>


using namespace KDevelop;
namespace Ruby
{

ExpressionVisitor::ExpressionVisitor(DUContext *ctx, EditorIntegrator *editor)
    : m_ctx(ctx), m_editor(editor), m_lastDeclaration(nullptr), m_alias(false)
{
    m_lastType = AbstractType::Ptr(nullptr);
    m_lastCtx = nullptr;
    m_declarationKind = DeclarationKind::Unknown;
}

ExpressionVisitor::ExpressionVisitor(ExpressionVisitor *parent)
    : m_ctx(parent->m_ctx), m_editor(parent->m_editor),
        m_lastDeclaration(nullptr), m_alias(false)
{
    m_lastType = AbstractType::Ptr(nullptr);
    m_lastCtx = nullptr;
    m_declarationKind = DeclarationKind::Unknown;
}

void ExpressionVisitor::setContext(DUContext *ctx)
{
    m_ctx = ctx;
    m_lastType = AbstractType::Ptr(nullptr);
    m_lastDeclaration = nullptr;
    m_alias = false;
    m_lastCtx = nullptr;
    m_declarationKind = DeclarationKind::Unknown;
}

void ExpressionVisitor::setIsClassMethod(bool isClassMethod)
{
    if (isClassMethod)
        m_declarationKind = DeclarationKind::ClassMethod;
    else
        m_declarationKind = DeclarationKind::InstanceMethod;
}

void ExpressionVisitor::visitParameter(RubyAst *node)
{
    AbstractType::Ptr obj;

    if (is_block_arg(node->tree)) {
        obj = getBuiltinsType("Proc", m_ctx);
    } else if (is_rest_arg(node->tree)) {
        obj = getBuiltinsType("Array", m_ctx);
    } else if (node->tree->r != nullptr) {
        ExpressionVisitor da(this);
        Node *n = node->tree;
        node->tree = node->tree->r;
        da.visitNode(node);
        node->tree = n;
        obj = da.lastType();
    } else
        obj = getBuiltinsType("Object", m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitName(RubyAst *node)
{
    if (!node->tree)
        return;

    QualifiedIdentifier id = getIdentifier(node);
    RangeInRevision range = m_editor->findRange(node->tree);
    DeclarationPointer decl = getDeclaration(id, range, DUContextPointer(m_ctx), m_declarationKind);
    DUChainReadLocker lock;

    if (decl) {
        m_alias = dynamic_cast<AliasDeclaration *>(decl.data());
        m_lastDeclaration = decl;
        encounter(decl->abstractType());
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
    DUChainReadLocker lock;
    AbstractType::Ptr obj;
    DUContext *ctx = m_ctx;

    Declaration *decl = ctx->owner();
    while (decl) {
        if (dynamic_cast<ModuleDeclaration *>(decl)) {
            obj = ctx->owner()->abstractType();
            m_lastDeclaration = DeclarationPointer(ctx->owner());
            break;
        }

        ctx = ctx->parentContext();
        if (!ctx)
            break;
        decl = ctx->owner();
    }

    if (!ctx || !decl)
        obj = getBuiltinsType("Object", m_ctx);
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

void ExpressionVisitor::visitNumeric(RubyAst *node)
{
    const char *type;

    switch (node->tree->flags) {
    case float_l: type = "Float"; break;
    case rational_l: type = "Rational"; break;
    case imaginary_l: type = "Complex"; break;
    default: type = "Fixnum"; break;
    }
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
    AbstractType::Ptr obj = getBuiltinsType("Array", m_ctx);
    ClassType::Ptr ptr = getContainer(obj, node);
    encounter<ClassType>(ptr);
}

void ExpressionVisitor::visitHash(RubyAst *node)
{
    AbstractType::Ptr obj = getBuiltinsType("Hash", m_ctx);
    ClassType::Ptr ptr = getContainer(obj, node, true);
    encounter<ClassType>(ptr);
}

void ExpressionVisitor::visitArrayValue(RubyAst *node)
{
    RubyAst *child = new RubyAst(node->tree->l, node->context);
    QualifiedIdentifier id = getIdentifier(child);
    RangeInRevision range = m_editor->findRange(child->tree);
    DeclarationPointer decl = getDeclaration(id, range, DUContextPointer(m_ctx));

    if (decl) {
        ClassType::Ptr vc = decl->abstractType().cast<ClassType>();
        if (vc)
            encounter(vc->contentType().abstractType());
    }
    delete child;
}

void ExpressionVisitor::visitMethodCall(RubyAst *node)
{
    Node *n = node->tree;

    node->tree = n->l;
    if (node->tree->kind == token_method_call)
        visitMethodCall(node);
    visitMethodCallMembers(node);
    node->tree = n;
}

void ExpressionVisitor::visitSuper(RubyAst *)
{
    DUChainReadLocker lock;
    ModuleDeclaration *mDecl = nullptr;
    DUContext *ctx = m_ctx->parentContext();
    Declaration *md = m_ctx->owner();

    if (!dynamic_cast<MethodDeclaration *>(md))
        return;

    while (ctx) {
        Declaration *d = ctx->owner();
        mDecl = dynamic_cast<ModuleDeclaration *>(d);
        if (mDecl && !mDecl->isModule())
            break;
        ctx = ctx->parentContext();
    }
    if (!mDecl || mDecl->isModule())
        return;

    StructureType::Ptr type = mDecl->baseClass().abstractType().cast<StructureType>();
    if (!type)
        return;
    ctx = type->internalContext(m_ctx->topContext());
    if (!ctx)
        return;

    foreach (Declaration *d, ctx->findLocalDeclarations(md->identifier())) {
        if (d->type<FunctionType>()) {
            encounter(d->type<FunctionType>()->returnType());
            break;
        }
    }
}

void ExpressionVisitor::visitLambda(RubyAst *)
{
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
    Node *aux = node->tree;
    node->tree = aux->l;
    ExpressionVisitor::visitLastStatement(node);
    AbstractType::Ptr res = lastType();
    node->tree = aux->r;
    ExpressionVisitor::visitLastStatement(node);
    res = mergeTypes(res, lastType());

    encounter(res);
    node->tree = aux;
}

void ExpressionVisitor::visitCaseStatement(RubyAst *node)
{
    Node *aux = node->tree;
    AbstractType::Ptr res;

    for (Node *n = aux->l; n != nullptr; n = n->r) {
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
        for (Node *n = ast->tree; n != nullptr; n = n->next) {
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
    }
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
    DUChainReadLocker rlock;
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
        rlock.unlock();
        ev.visitNode(node);
        m_lastDeclaration = ev.lastDeclaration().data();
        StructureType::Ptr sType = StructureType::Ptr::dynamicCast(ev.lastType());
        rlock.lock();

        /*
         * If this is a StructureType, it means that we're in a case like;
         * "A::B::" and therefore the next context should be A::B.
         */
        if (!sType) {
            // It's not a StructureType, therefore it's a variable or a method.
            FunctionType::Ptr fType = FunctionType::Ptr::dynamicCast(ev.lastType());
            if (!fType)
                ctx = (m_lastDeclaration) ? m_lastDeclaration->internalContext() : nullptr;
            else {
                StructureType::Ptr rType = StructureType::Ptr::dynamicCast(fType->returnType());
                if (rType) {
                    encounter(fType->returnType());
                    ctx = rType->internalContext(ctx->topContext());
                } else {
                    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(fType->returnType());
                    if (ut)
                        encounter<UnsureType>(ut);
                    ctx = nullptr;
                }
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
