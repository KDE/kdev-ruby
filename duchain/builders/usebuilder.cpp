/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <duchain/builders/usebuilder.h>

#include <language/duchain/types/functiontype.h>

#include <parser/parser.h>
#include <duchain/editorintegrator.h>
#include <duchain/expressionvisitor.h>
#include <duchain/declarations/moduledeclaration.h>

using namespace KDevelop;
using namespace ruby;

UseBuilder::UseBuilder(EditorIntegrator *editor) : UseBuilderBase()
{
    m_editor = editor;
    m_lastCtx = nullptr;
    m_depth = 0;
    m_classMethod = false;
}

bool UseBuilder::declaredInContext(const QByteArray &name) const
{
    return declaredIn(name, DUContextPointer(currentContext()));
}

void UseBuilder::visitName(Ast *node)
{
    const QualifiedIdentifier &id = getIdentifier(node);
    const RangeInRevision &range = editorFindRange(node, node);
    auto decl = getDeclaration(id, range, DUContextPointer(currentContext()));

    if (!decl || decl->range() == range) {
        return;
    }
    UseBuilderBase::newUse(range, decl);
}

void UseBuilder::visitClassName(Ast *node)
{
    Node *aux = node->tree;
    Node *last = node->tree->last;
    ExpressionVisitor ev(currentContext(), m_editor);

    for (Node *n = aux; n && last; n = n->next) {
        node->tree = n;
        ev.visitNode(node);
        const DeclarationPointer d = ev.lastDeclaration();
        if (d.data()) {
            UseBuilderBase::newUse(editorFindRange(node, node), d);
            ev.setContext(d->internalContext());
        } else {
            break;
        }
    }
    node->tree = aux;
}

void UseBuilder::visitMixin(Ast *node, bool include)
{
    Q_UNUSED(include);

    ExpressionVisitor ev(currentContext(), m_editor);
    Node *aux = node->tree;
    Node *n = (aux->r->l) ? aux->r->l : aux->r;

    for (; n; n = n->next) {
        node->tree = n;
        ev.visitNode(node);
        const DeclarationPointer d = ev.lastDeclaration();
        if (d) {
            UseBuilderBase::newUse(m_editor->findRange(n), d);
            // TODO: is this context useful for something actually? If it is, I guess we need to create it.
            auto context = d->internalContext();
            // Setting invalid context doesn’t make sense and just causes fail in helpers.cpp’s context assert
            // TODO: maybe visitClassName() & co. needs this too?
            if(context) {
                Q_ASSERT(context);
                ev.setContext(context);
            }
        } else {
            break;
        }
    }
    node->tree = aux;
}

void UseBuilder::visitMethodCall(Ast *node)
{
    Node *n = node->tree;

    /* Visit the method call members */
    node->tree = n->l;
    if (node->tree->kind == token_method_call) {
        m_depth++;
        visitMethodCall(node);
        m_depth--;
    }
    m_classMethod = true;
    visitMethodCallMembers(node);
    if (!m_depth) {
        m_lastCtx = nullptr;
    }

    /* Visit the method arguments */
    node->tree = n->r;
    for (Node *aux = n->r; aux; aux = aux->next) {
        visitNode(node);
        node->tree = aux->next;
    }

    /* Vist method call block */
    node->tree = n->cond;
    visitBlock(node);
    node->tree = n;
}

void UseBuilder::visitMethodCallMembers(Ast *node)
{
    RangeInRevision range;
    DUContext *ctx = (m_lastCtx) ? m_lastCtx : currentContext();
    Declaration *last;
    ExpressionVisitor ev(ctx, editor());

    // Go to the next element since we're coming from a recursion and we've
    // already checked its children nodes.
    if (node->tree->kind == token_method_call) {
        node->tree = node->tree->next;
    }

    // And this is the loop that does the dirty job.
    for (Node *aux = node->tree; aux && ctx; aux = aux->next) {
        node->tree = aux;
        if (node->tree->kind != token_object) {
            // i.e. visit "a" and "b" from (a - b).bytesize
            UseBuilderBase::visitNode(node);
        }
        range = editorFindRange(node, node);
        ev.setContext(ctx);
        ev.setIsClassMethod(m_classMethod);
        ev.visitNode(node);
        if (!ev.lastType()) {
            DUChainReadLocker lock;
            ModuleDeclaration *cdeclaration = dynamic_cast<ModuleDeclaration *>(ctx->owner());
            lock.unlock();
            if (cdeclaration && !cdeclaration->isModule()) {
                ev.setContext(getClassContext(currentContext()));
                ev.visitNode(node);
            }
        }
        last = ev.lastDeclaration().data();
        StructureType::Ptr sType = StructureType::Ptr::dynamicCast(ev.lastType());

        // Handle the difference between instance & class methods.
        if (dynamic_cast<ModuleDeclaration *>(ev.lastDeclaration().data())) {
            m_classMethod = true;
        } else {
            m_classMethod = false;
        }

        // Mark a new use if possible
        if (last && node->tree->kind != token_self) {
            UseBuilderBase::newUse(range, DeclarationPointer(last));
        }

        // If this is a StructureType, it means that we're in a case like;
        // "A::B::" and therefore the next context should be A::B.
        if (!sType) {
            // It's not a StructureType, therefore it's a variable or a method.
            FunctionType::Ptr fType = FunctionType::Ptr::dynamicCast(ev.lastType());
            if (!fType) {
                ctx = (last) ? last->internalContext() : nullptr;
            } else {
                DUChainReadLocker lock;
                StructureType::Ptr rType = StructureType::Ptr::dynamicCast(fType->returnType());
                ctx = (rType) ? rType->internalContext(topContext()) : nullptr;
            }
        } else {
            DUChainReadLocker lock;
            ctx = sType->internalContext(topContext());
        }
    }
    m_lastCtx = ctx;
}

void UseBuilder::visitRequire(Ast *node, bool relative)
{
    Q_UNUSED(node);
    Q_UNUSED(relative);
}

