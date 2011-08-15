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


#include <parser/rubyastvisitor.h>
#include <rubydefs.h> //TODO: Should be removed in the future

/*
 * TODO: Write in each visitor method a comment that describes the format
 * of the AST for the specific situation.
 */


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

void RubyAstVisitor::visitVariable(RubyAst* node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitBody(RubyAst *node)
{
    if (node->tree == NULL)
        return;
    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitStatements(child);
    child->tree = node->tree->r;
    visitNode(child);
    child->tree = node->tree->cond;
    visitNode(child);
    child->tree = node->tree->ensure;
    visitNode(child);
    delete child;
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

void RubyAstVisitor::visitIfStatement(RubyAst *node)
{
    RubyAst *child = new RubyAst(node->tree->cond, node->context);
    visitNode(child);
    child->tree = node->tree->l;
    visitStatements(child);
    child->tree = node->tree->r;
    visitIfTail(child);
    delete child;
}

void RubyAstVisitor::visitCaseStatement(RubyAst *node)
{
    RubyAst *child = new RubyAst(node->tree->cond, node->context);
    visitNode(child);
    child->tree = node->tree->l;
    visitWhenStatements(child);
    delete child;
}

void RubyAstVisitor::visitBeginStatement(RubyAst *node)
{
    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitBody(child);
    delete child;
}

void RubyAstVisitor::visitUpBeginEndStatement(RubyAst *node)
{
    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitStatements(child);
    delete child;
}

void RubyAstVisitor::visitWhileStatement(RubyAst *node)
{
    RubyAst *child = new RubyAst(node->tree->cond, node->context);
    visitNode(child);
    child->tree = node->tree->l;
    visitStatements(child);
    delete child;
}

void RubyAstVisitor::visitForStatement(RubyAst *node)
{
    RubyAst *child = new RubyAst(node->tree->r, node->context);
    visitStatements(child);
    child->tree = node->tree->cond;
    visitNode(child);
    child->tree = node->tree->l;
    visitStatements(child);
    delete child;
}

void RubyAstVisitor::visitMethodStatement(RubyAst *node)
{
    Node *n = node->tree;
    if (n == NULL)
        return;

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
        visitNode(child);
        child->tree = n->next;
    }
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

void RubyAstVisitor::visitModuleStatement(RubyAst *node)
{
    Node *n = node->tree;
    RubyAst *child = new RubyAst(n->l, node->context);
    visitBody(child);
    delete child;
}

void RubyAstVisitor::visitNode(RubyAst *node)
{
    Node *n = node->tree;

    /* This is not a valid node */
    if (!n || n->kind == token_invalid)
        return;
    switch (n->kind) {
        case token_if: case token_unless:
            visitIfStatement(node);
            break;
        case token_exception:
            visitBeginStatement(node);
            break;
        case token_up_begin: case token_up_end:
            visitUpBeginEndStatement(node);
            break;
        case token_case:
            visitCaseStatement(node);
            break;
        case token_while: case token_until:
            visitWhileStatement(node);
            break;
        case token_for:
            visitForStatement(node);
            break;
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

void RubyAstVisitor::visitStatements(RubyAst *list)
{
    RubyAst *child = new RubyAst(list->tree, list->context);
    for (Node *n = child->tree; n != NULL; n = n->next) {
        RubyAstVisitor::visitNode(child);
        child->tree = n->next;
    }
    delete child;
}

void RubyAstVisitor::visitIfTail(RubyAst *tail)
{
    Node *n = tail->tree;
    if (n == NULL)
        return;

    /* Check if this is an elsif or an else statement */
    if (n->cond == NULL) {
        tail->tree = n->l;
        visitStatements(tail);
    } else
        visitIfStatement(tail);
}

void RubyAstVisitor::visitWhenStatements(RubyAst *list)
{
    Node *n = list->tree;
    if (n == NULL)
        return;

    /* Check whether this is a when or an else statement */
    if (n->kind == token_when) {
        RubyAst *child = new RubyAst(n->cond, list->context);
        visitNode(child);
        child->tree = n->l;
        visitStatements(child);
        child->tree = n->r;
        visitWhenStatements(child);
        delete child;
    } else {
        list->tree = n->l;
        visitStatements(list);
    }
}


} // End of namespace Ruby

