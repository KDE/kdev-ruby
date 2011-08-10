/* This file is part of KDevelop
 *
 * Copyright (C) 2011 Miquel Sabaté <mikisabate@gmail.com>
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

#include "rubyastvisitor.h"
#include <rubydefs.h>


/* TODO: Under construction */

namespace Ruby
{

RubyAstVisitor::RubyAstVisitor()
{
    /* There's nothing to do here */
}

RubyAstVisitor::~RubyAstVisitor()
{
    /* There's nothing to do here */
}

void RubyAstVisitor::visitCode(RubyAst *node)
{
    debug() << "Visiting Code...";
    RubyAst *child = new RubyAst(node->tree, node->context);

    for (Node *n = node->tree; n != NULL; n = n->next) {
        visitNode(child);
        child->tree = n->next;
    }
    delete child;
}

void RubyAstVisitor::visitNode(RubyAst *node)
{
    Node *n = node->tree;
    int kind;

    /* This is not a valid node */
    if (!n || n->kind == token_invalid)
        return;

    kind = n->kind;
    switch (kind) {
        case token_class:
        case token_singleton_class:
            visitClassStatement(node);
            break;
        case token_module:
            visitModuleStatement(node);
            break;
        case token_function:
            visitMethodStatement(node);
            break;
        case token_assign: case token_op_assign:
            visitAssignmentStatement(node);
            break;
        case token_object:
            visitVariable(node);
            break;
        case token_numeric: case token_symbol:
        case token_break: case token_next: case token_redo: case token_retry:
            return;
    }
}

void RubyAstVisitor::visitModuleStatement(RubyAst *node)
{
    Node *n = node->tree;
    RubyAst *child = new RubyAst(n->l, node->context);
    visitBody(child);
    delete child;
}

void RubyAstVisitor::visitClassStatement(RubyAst *node)
{
    Node *n = node->tree;
    RubyAst *child = new RubyAst(n->cond, node->context);
    visitNode(child);
    child->tree = n->l;
    visitBody(child);
    delete child;
}

void RubyAstVisitor::visitMethodStatement(RubyAst *node)
{
    Node *n = node->tree;
    RubyAst *child = new RubyAst(n->r, node->context);
    visitMethodArguments(child);
    child->tree = n->l;
    visitBody(child);
    delete child;
}

void RubyAstVisitor::visitMethodArguments(RubyAst *node)
{
    RubyAst *child = new RubyAst(node->tree, node->context);
    for (Node *n = node->tree; n != NULL; n = n->next) {
        RubyAstVisitor::visitNode(child);
        child->tree = n->next;
    }
    delete child;
}

void RubyAstVisitor::visitBody(RubyAst *node)
{
    RubyAst *child = new RubyAst(node->tree, node->context);
    for (Node *n = node->tree; n != NULL; n = n->next) {
        RubyAstVisitor::visitNode(child);
        child->tree = n->next;
    }
    delete child;
}

void RubyAstVisitor::visitVariable(RubyAst* node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitAssignmentStatement(RubyAst *node)
{
    RubyAst *child = new RubyAst(node->tree->l, node->context);
    for (Node *n = child->tree; n != NULL; n = n->next) {
        RubyAstVisitor::visitNode(child);
        child->tree = n->next;
    }
    child->tree = node->tree->r;
    for (Node *n = child->tree; n != NULL; n = n->next) {
        RubyAstVisitor::visitNode(child);
        child->tree = n->next;
    }
    delete child;
}


}


