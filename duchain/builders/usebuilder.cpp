/* This file is part of KDevelop
 *
 * Copyright (C) 2011  Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


// KDE + KDevelop
#include <KDebug>
#include <KLocale>
#include <language/duchain/types/functiontype.h>

// Ruby
#include <rubydefs.h>
#include <duchain/helpers.h>
#include <duchain/editorintegrator.h>
#include <duchain/expressionvisitor.h>
#include <duchain/builders/usebuilder.h>
#include <duchain/declarations/classdeclaration.h>


namespace Ruby
{

UseBuilder::UseBuilder(EditorIntegrator *editor) : UseBuilderBase()
{
    m_editor = editor;
    m_lastCtx = NULL;
    mcDepth = 0;
}

void UseBuilder::visitName(RubyAst *node)
{
    const QualifiedIdentifier &id = getIdentifier(node);
    const RangeInRevision &range = editorFindRange(node, node);
    Declaration *decl = getDeclaration(id, range, DUContextPointer(currentContext()));

    if (decl && decl->range() == range)
        return;

    debug() << "New use: " << id << " at " << range;
    UseBuilderBase::newUse(node, range, DeclarationPointer(decl));
}

void UseBuilder::visitMethodCall(RubyAst *node)
{
    Node *n = node->tree;

    /* Visit the method call members */
    node->tree = n->l;
    if (node->tree->kind == token_method_call) {
        mcDepth++;
        visitMethodCall(node);
        mcDepth--;
    }
    visitMethodCallMembers(node);
    if (!mcDepth)
        m_lastCtx = NULL;

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

void UseBuilder::visitMethodCallMembers(RubyAst *node)
{
    RangeInRevision range;
    DUChainWriteLocker wlock(DUChain::lock());
    DUContext *ctx = (m_lastCtx) ? m_lastCtx : currentContext();
    Declaration *last;
    ExpressionVisitor ev(ctx, editor());

    /*
     * Go to the next element since we're coming from a recursion and we've
     * already checked its children nodes.
     */
    if (node->tree->kind == token_method_call)
        node->tree = node->tree->next;

    // And this is the loop that does the dirty job.
    for (Node *aux = node->tree; aux; aux = aux->next) {
        node->tree = aux;
        range = editorFindRange(node, node);
        ev.setContext(ctx);
        ev.visitNode(node);
        if (!ev.lastType()) {
            ClassDeclaration *cdecl = dynamic_cast<ClassDeclaration *>(ctx->owner());
            if (cdecl) {
                ev.setContext(getClassContext(currentContext()));
                ev.visitNode(node);
            }
        }
        last = ev.lastDeclaration().data();
        StructureType::Ptr sType = StructureType::Ptr::dynamicCast(ev.lastType());

        // Mark a new use if possible
        if (last)
            UseBuilderBase::newUse(node, range, DeclarationPointer(last));

        /*
         * If this is a StructureType, it means that we're in a case like;
         * "A::B::" and therefore the next context should be A::B.
         */
        if (!sType) {
            // It's not a StructureType, therefore it's a variable or a method.
            FunctionType::Ptr fType = FunctionType::Ptr::dynamicCast(ev.lastType());
            if (!fType)
                ctx = (last) ? last->internalContext() : NULL;
            else {
                StructureType::Ptr rType = StructureType::Ptr::dynamicCast(fType->returnType());
                ctx = (rType) ? rType->internalContext(topContext()) : NULL;
            }
        } else
            ctx = sType->internalContext(topContext());

        // No context found, we can't go any further.
        if (!ctx)
            return;
    }
    m_lastCtx = ctx;
}

} // End of namespace Ruby
