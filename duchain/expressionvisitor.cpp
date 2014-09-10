/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


namespace Ruby
{

using namespace KDevelop;

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
    if (isClassMethod) {
        m_declarationKind = DeclarationKind::ClassMethod;
    } else {
        m_declarationKind = DeclarationKind::InstanceMethod;
    }
}

void ExpressionVisitor::setDeclarationKind(const DeclarationKind kind)
{
    m_declarationKind = kind;
}

void ExpressionVisitor::visitParameter(Ast *node)
{
    AbstractType::Ptr obj;

    if (is_block_arg(node->tree)) {
        obj = getBuiltinsType(QStringLiteral("Proc"), m_ctx);
    } else if (is_rest_arg(node->tree)) {
        obj = getBuiltinsType(QStringLiteral("Array"), m_ctx);
    } else if (node->tree->r != nullptr) {
        ExpressionVisitor da(this);
        Node *n = node->tree;
        node->tree = node->tree->r;
        da.visitNode(node);
        node->tree = n;
        obj = da.lastType();
    } else {
        obj = getBuiltinsType(QStringLiteral("Object"), m_ctx);
    }
    encounter(obj);
}

void ExpressionVisitor::visitName(Ast *node)
{
    if (!node->tree) {
        return;
    }

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

void ExpressionVisitor::visitTrue(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("TrueClass"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitFalse(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("FalseClass"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitNil(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("NilClass"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitFile(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("String"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitLine(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("Fixnum"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitEncoding(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("Encoding"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitSelf(Ast *)
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
        if (!ctx) {
            break;
        }
        decl = ctx->owner();
    }

    if (!ctx || !decl) {
        obj = getBuiltinsType(QStringLiteral("Object"), m_ctx);
    }
    encounter(obj);
}

void ExpressionVisitor::visitRange(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("Range"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitString(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("String"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitNumeric(Ast *node)
{
    QString type;

    switch (node->tree->flags) {
    case float_l: type = QStringLiteral("Float"); break;
    case rational_l: type = QStringLiteral("Rational"); break;
    case imaginary_l: type = QStringLiteral("Complex"); break;
    default: type = QStringLiteral("Fixnum"); break;
    }
    AbstractType::Ptr obj = getBuiltinsType(type, m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitRegexp(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("Regexp"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitSymbol(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("Symbol"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitArray(Ast *node)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("Array"), m_ctx);
    ClassType::Ptr ptr = getContainer(obj, node);
    encounter<ClassType>(ptr);
}

void ExpressionVisitor::visitHash(Ast *node)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("Hash"), m_ctx);
    ClassType::Ptr ptr = getContainer(obj, node, true);
    encounter<ClassType>(ptr);
}

void ExpressionVisitor::visitArrayValue(Ast *node)
{
    Ast *child = new Ast(node->tree->l, node->context);
    QualifiedIdentifier id = getIdentifier(child);
    RangeInRevision range = m_editor->findRange(child->tree);
    DeclarationPointer decl = getDeclaration(id, range, DUContextPointer(m_ctx));

    if (decl) {
        ClassType::Ptr vc = decl->abstractType().cast<ClassType>();
        if (vc) {
            encounter(vc->contentType().abstractType());
        }
    }
    delete child;
}

void ExpressionVisitor::visitMethodCall(Ast *node)
{
    Node *n = node->tree;

    // Handle recursive method calls here.
    node->tree = n->l;
    if (node->tree->kind == token_method_call) {
        visitMethodCall(node);
    }

    // Let's evaluate now the members of the current method call.
    DeclarationKind oldKind = m_declarationKind;
    m_declarationKind = DeclarationKind::InstanceMethod;
    visitMethodCallMembers(node);
    m_declarationKind = oldKind;
    node->tree = n;
}

void ExpressionVisitor::visitSuper(Ast *)
{
    DUChainReadLocker lock;
    ModuleDeclaration *mDecl = nullptr;
    DUContext *ctx = m_ctx->parentContext();
    Declaration *md = m_ctx->owner();

    if (!dynamic_cast<MethodDeclaration *>(md)) {
        return;
    }

    while (ctx) {
        Declaration *d = ctx->owner();
        mDecl = dynamic_cast<ModuleDeclaration *>(d);
        if (mDecl && !mDecl->isModule()) {
            break;
        }
        ctx = ctx->parentContext();
    }
    if (!mDecl || mDecl->isModule()) {
        return;
    }

    StructureType::Ptr type = mDecl->baseClass().abstractType().cast<StructureType>();
    if (!type) {
        return;
    }
    ctx = type->internalContext(m_ctx->topContext());
    if (!ctx) {
        return;
    }

    foreach (Declaration *d, ctx->findLocalDeclarations(md->identifier())) {
        if (d->type<FunctionType>()) {
            encounter(d->type<FunctionType>()->returnType());
            break;
        }
    }
}

void ExpressionVisitor::visitLambda(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("Proc"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitWhileStatement(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("NilClass"), m_ctx);
    encounter(obj);
}

void ExpressionVisitor::visitForStatement(Ast *node)
{
    ExpressionVisitor ev(this);
    Node *n = node->tree;
    node->tree = n->l;
    AstVisitor::visitNode(node);
    node->tree = n->cond;
    ev.visitNode(node);
    node->tree = n;
    encounter(ev.lastType());
}

void ExpressionVisitor::visitBinary(Ast *node)
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

void ExpressionVisitor::visitBoolean(Ast *)
{
    AbstractType::Ptr truthy = getBuiltinsType(QStringLiteral("TrueClass"), m_ctx);
    AbstractType::Ptr falsy = getBuiltinsType(QStringLiteral("FalseClass"), m_ctx);
    encounter(mergeTypes(truthy, falsy));
}

void ExpressionVisitor::visitIfStatement(Ast *node)
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

void ExpressionVisitor::visitCaseStatement(Ast *node)
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

void ExpressionVisitor::visitMethodStatement(Ast *)
{
    AbstractType::Ptr obj = getBuiltinsType(QStringLiteral("Symbol"), m_ctx);
    encounter(obj);
}

template <typename T> void ExpressionVisitor::encounter(TypePtr<T> type)
{
    encounter(AbstractType::Ptr::staticCast(type));
}

ClassType::Ptr ExpressionVisitor::getContainer(AbstractType::Ptr ptr, const Ast *node, bool hasKey)
{
    ClassType::Ptr ct = ptr.cast<ClassType>();

    if (ct) {
        ExpressionVisitor ev(this);
        Ast *ast = new Ast(node->tree->l, node->context);
        for (Node *n = ast->tree; n != nullptr; n = n->next) {
            if (hasKey) {
                Node *aux = ast->tree;
                ast->tree = ast->tree->r;
                ev.visitNode(ast);
                ast->tree = aux;
            } else {
                ev.visitNode(ast);
            }
            ct->addContentType(ev.lastType());
            ast->tree = n->next;
        }
        delete ast;
    }
    return ct;
}

void ExpressionVisitor::visitLastStatement(Ast *node)
{
    if (!node->tree) {
        return;
    }

    Node *n = node->tree;
    if (n->last) {
        node->tree = n->last;
    }
    ExpressionVisitor::visitNode(node);
    node->tree = n;
}

void ExpressionVisitor::visitMethodCallMembers(Ast *node)
{
    DUChainReadLocker rlock;
    RangeInRevision range;
    DUContext *ctx = (m_lastCtx) ? m_lastCtx : m_ctx;
    ExpressionVisitor ev(this);

    /*
     * Go to the next element since we're coming from a recursion and we've
     * already checked its children nodes.
     */
    if (node->tree->kind == token_method_call) {
        node->tree = node->tree->next;
    }

    // And this is the loop that does the dirty job.
    for (Node *aux = node->tree; aux; aux = aux->next) {
        node->tree = aux;
        range = m_editor->findRange(node->tree);
        ev.setContext(ctx);
        ev.setDeclarationKind(m_declarationKind);
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
            if (!fType) {
                ctx = (m_lastDeclaration) ? m_lastDeclaration->internalContext() : nullptr;
            } else {
                StructureType::Ptr rType = StructureType::Ptr::dynamicCast(fType->returnType());
                if (rType) {
                    encounter(fType->returnType());
                    ctx = rType->internalContext(ctx->topContext());
                } else {
                    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(fType->returnType());
                    if (ut) {
                        encounter<UnsureType>(ut);
                    }
                    ctx = nullptr;
                }
            }
            // TODO
            // m_declarationKind = InstanceMethod;
        } else {
            encounter(ev.lastType());
            m_declarationKind = ClassMethod;
            ctx = sType->internalContext(ctx->topContext());
        }

        // No context found, we can't go any further.
        if (!ctx) {
            return;
        }
    }
    m_lastCtx = ctx;
}

}
