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


// KDE
#include <KDebug>
#include <KLocale>

// Ruby
#include <rubydefs.h>
#include <duchain/helpers.h>
#include <duchain/editorintegrator.h>
#include <duchain/builders/usebuilder.h>
#include <duchain/expressionvisitor.h>


namespace Ruby
{

UseBuilder::UseBuilder(EditorIntegrator *editor) : UseBuilderBase()
{
    m_editor = editor;
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
//     debug() << "BEFORE";
//     UseBuilderBase::visitMethodCall(node);
//     debug() << "AFTER";
    Node *n = node->tree;
//     DUContext *ctx = currentContext();
//     StructureType::Ptr sType;
//     DUChainReadLocker rlock(DUChain::lock());
//     debug() << "BEFORE LOOP";
//     for (Node *aux = n; aux; aux = aux->next) {
//         node->tree = aux;
//         ExpressionVisitor ev(ctx, m_editor);
//         ev.visitNode(node);
//         sType = StructureType::Ptr::dynamicCast(ev.lastType());
//         debug() << "HERE";
//         if (!sType)
//             continue;
//         debug() << "LAL : " << getIdentifier(node) << " :type: " << sType->toString();
//         ctx = sType->internalContext(topContext());
//         if (!ctx) {
//             debug() << "GTFO";
//             break;
//         }
//         debug() << "Let's loop";
//     }
//     node->tree = n;

    /* Visit the method call members */
    node->tree = n->l;
    visitMethodCallMembers(node);

    /* Visit the method arguments */
//     node->tree = n->r;
//     for (Node *aux = n->r; aux; aux = aux->next) {
//         visitNode(node);
//         node->tree = aux->next;
//     }

    /* Vist method call block */
//     node->tree = n->cond;
//     visitBlock(node);
    node->tree = n;
//     debug() << "END";
}

void UseBuilder::visitMethodCallMembers(RubyAst *node)
{
    QualifiedIdentifier id;
    RangeInRevision range;
    DUChainWriteLocker rlock(DUChain::lock());
    DUContext *ctx = currentContext();
    Declaration * last;
    ExpressionVisitor ev(ctx, editor());

    debug() << "VISITING METHOD CALL MEMBERS";

    for (Node *aux = node->tree; aux; aux = aux->next) {
        id = getIdentifier(node); // TODO: remove
        range = editorFindRange(node, node);
        ev.setContext(ctx);
        ev.visitNode(node);
        last = ev.lastDeclaration().data();
        StructureType::Ptr sType = StructureType::Ptr::dynamicCast(ev.lastType());
//         last = getDeclaration(id, range, DUContextPointer(ctx));
        debug() << "ID: " << id << " RANGE : " << range;
//         if (!last) {
//             debug()d << "NOPE";
//             last = sType->declaration(topContext());
//             if (!last) {
                
//                 return;
//             }
//             return;
//         }
//         debug() << "Got it!";
        if (last) {
            debug() << "Marking use, originally from: " << last->range() << " " << last->url().byteArray();
            UseBuilderBase::newUse(node, range, DeclarationPointer(last));
        }
//         StructureType::Ptr sType = StructureType::Ptr::dynamicCast(ev.lastType());
        if (!sType) {
            debug() << "StructureType";
            if (!last)
                return;
            ctx = last->internalContext();
        } else {
            debug() << "NO TYPE";
            ctx = sType->internalContext(topContext());
        }
        if (!ctx)
            return;
        node->tree = aux->next;
    }

    debug() << "BYE BYE";
}

} // End of namespace Ruby
