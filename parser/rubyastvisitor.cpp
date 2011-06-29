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
            visitFunctionStatement(node);
            break;
        case token_object: case token_numeric: case token_symbol:
        case token_break: case token_next: case token_redo: case token_retry:
            return;
    }
    visitChilds(node);
}

void RubyAstVisitor::visitChilds(RubyAst *node)
{
    Node *n = node->tree;
    RubyAst *child = new RubyAst(NULL, node->context);

    child->tree = n->next;
    visitNode(child);
    child->tree = n->l;
    visitNode(child);
    child->tree = n->r;
    visitNode(child);
    child->tree = n->cond;
    visitNode(child);
    child->tree = n->ensure;
    visitNode(child);
    delete child;
}

void RubyAstVisitor::visitModuleStatement(RubyAst *node)
{
    visitChilds(node);
}

void RubyAstVisitor::visitClassStatement(RubyAst *node)
{
    visitChilds(node);
}

void RubyAstVisitor::visitFunctionStatement(RubyAst *node)
{
    visitChilds(node);
}


}


