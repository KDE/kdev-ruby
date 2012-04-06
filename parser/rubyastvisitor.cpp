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
#include <rubydefs.h>


/*
 * Note that each visitor method has a comment that explains how the AST
 * is structured for the specific statement. Only the following attributes
 * will be considered: l, r, cond and ensure. If any of these pointers are not
 * specified, it means that its value is just NULL.
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

void RubyAstVisitor::visitNumeric(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitRegexp(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitString(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitBody(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     * r -> optional rescue statement.
     * cond -> optional else statement.
     * ensure -> optional ensure statement.
     */

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

void RubyAstVisitor::visitBinary(RubyAst *node)
{
    /*
     * l -> left operator.
     * r -> right operator.
     */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitNode(child);
    child->tree = node->tree->r;
    visitNode(child);
    delete child;
}

void RubyAstVisitor::visitBoolean(RubyAst *node)
{
    /* Same as for the visitBinary method  */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitNode(child);
    child->tree = node->tree->r;
    visitNode(child);
    delete child;
}

void RubyAstVisitor::visitRange(RubyAst *node)
{
    /* Same as for the visitBinary method  */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitNode(child);
    child->tree = node->tree->r;
    visitNode(child);
    delete child;
}

void RubyAstVisitor::visitUnary(RubyAst *node)
{
    /*
     * l -> the operator.
     */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitNode(child);
    delete child;
}

void RubyAstVisitor::visitArray(RubyAst *node)
{
    /*
     * l -> list of statements (the items of the array).
     */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitStatements(child);
    delete child;
}

void RubyAstVisitor::visitArrayValue(RubyAst *node)
{
    /*
     * l -> the node containing the Array object.
     * r -> the index expression.
     */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitNode(child);
    child->tree = node->tree->r;
    visitStatements(child);
    delete child;
}

void RubyAstVisitor::visitHash(RubyAst *node)
{
    /*
     * l -> list of hash items.
     */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    for (; child->tree != NULL; child->tree = child->tree->next)
        visitBinary(child);
    delete child;
}

void RubyAstVisitor::visitReturnStatement(RubyAst *node)
{
    /*
     * l -> the return expression.
     */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitNode(child);
    delete child;
}

void RubyAstVisitor::visitUndefStatement(RubyAst *node)
{
    /*
     * l -> list of undef items.
     */

    RubyAst *child = new RubyAst(node->tree->r, node->context);
    visitStatements(child);
    delete child;
}

void RubyAstVisitor::visitAliasStatement(RubyAst *node)
{
    /* Same as for the visitBinary method. */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitNode(child);
    child->tree = node->tree->r;
    visitNode(child);
    delete child;
}

void RubyAstVisitor::visitYieldStatement(RubyAst *node)
{
    /*
     * l -> the yield expression.
     */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitNode(child);
    delete child;    
}

void RubyAstVisitor::visitAssignmentStatement(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitIfStatement(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     * r -> the "tail": optional list of elsif's and an optional else.
     * cond -> the condition expression.
     */

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
    /*
     * l -> the case body: list of when statements and an optional else
     * statement at the end.
     * cond -> the condition expression.
     */

    RubyAst *child = new RubyAst(node->tree->cond, node->context);
    visitNode(child);
    child->tree = node->tree->l;
    visitWhenStatements(child);
    delete child;
}

void RubyAstVisitor::visitBeginStatement(RubyAst *node)
{
    /*
     * l -> the body of the begin statement. Note that this body is not just
     * a list of "regular" statement, check the visitBody method for more info.
     */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitBody(child);
    delete child;
}

void RubyAstVisitor::visitUpBeginEndStatement(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     */

    RubyAst *child = new RubyAst(node->tree->l, node->context);
    visitStatements(child);
    delete child;
}

void RubyAstVisitor::visitWhileStatement(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     * cond -> the condition expression.
     */

    RubyAst *child = new RubyAst(node->tree->cond, node->context);
    visitNode(child);
    child->tree = node->tree->l;
    visitStatements(child);
    delete child;
}

void RubyAstVisitor::visitForStatement(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     * r -> list of variables declared before the "in" keyword.
     * cond -> the expression after the "in" keyword.
     */

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
    /*
     * l -> list of inner statements.
     * r -> list of method arguments.
     */

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
    /* Just iterate over the "next" pointer. */

    RubyAst *child = new RubyAst(node->tree, node->context);
    for (Node *n = node->tree; n != NULL; n = n->next) {
        visitParameter(child);
        child->tree = n->next;
    }
    delete child;
}

void RubyAstVisitor::visitParameter(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitClassStatement(RubyAst *node)
{
    /*
     * l -> the body of the class statement. Note that this body is not just
     * a list of "regular" statement, check the visitBody method for more info.
     * cond -> the superclass node.
     */

    Node *n = node->tree;
    RubyAst *child = new RubyAst(n->cond, node->context);
    visitVariable(child);
    child->tree = n->l;
    visitBody(child);
    delete child;
}

void RubyAstVisitor::visitSingletonClass(RubyAst *node)
{
    /*
     * l -> the body of the class statement. Note that this body is not just
     * a list of "regular" statement, check the visitBody method for more info.
     * r -> the expression after the lshift ("<<") operator.
     */

    Node *n = node->tree;
    RubyAst *child = new RubyAst(n->l, node->context);
    visitBody(child);
    child->tree = n->r;
    visitNode(child);
    delete child;
}

void RubyAstVisitor::visitModuleStatement(RubyAst *node)
{
    /*
     * l -> the body of the class statement. Note that this body is not just
     * a list of "regular" statement, check the visitBody method for more info.
     */

    Node *n = node->tree;
    RubyAst *child = new RubyAst(n->l, node->context);
    visitBody(child);
    delete child;
}

void RubyAstVisitor::visitMethodCall(RubyAst *node)
{
    /*
     * l -> the caller (note that it's a list, i.e. A::B::foo).
     * r -> the arguments for this method call.
     * cond -> an optional Ruby block.
     */

    Node *aux, *n = node->tree;
    RubyAst *child = new RubyAst(node->tree->l, node->context);
    for (aux = n->l; aux != NULL; aux = aux->next) {
        visitNode(child);
        child->tree = aux->next;
    }

    /* Visit the method arguments */
    for (aux = n->r; aux != NULL; aux = aux->next) {
        visitNode(child);
        child->tree = aux->next;
    }

    /* Vist method call block */
    child->tree = n->cond;
    visitBlock(child);
    delete child;
}

void RubyAstVisitor::visitBlock(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     * r -> list of block variables.
     */

    Node *n;
    if (node->tree == NULL)
        return;
    RubyAst *child = new RubyAst(node->tree->r, node->context);
    for (n = node->tree->r; n != NULL; n = n->next) {
        visitBlockVariable(child);
        child->tree = n->next;
    }
    child->tree = node->tree->l;
    visitStatements(child);
    delete child;
}

void RubyAstVisitor::visitBlockVariable(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitExtend(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitInclude(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitRequire(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitDefined(RubyAst *node)
{
    /*
     * l -> the expression from the "defined" statement.
     */

    Node *n = node->tree;
    RubyAst *child = new RubyAst(n->l, node->context);
    visitNode(child);
    delete child;
}

void RubyAstVisitor::visitTrue(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitFalse(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitNil(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitFile(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitLine(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitEncoding(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitSelf(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitNode(RubyAst *node)
{
    Node *n = node->tree;

    /* This is not a valid node */
    if (!n || n->kind == token_invalid)
        return;
    switch (n->kind) {
        case token_return: visitReturnStatement(node); break;
        case token_yield: visitYieldStatement(node); break;
        case token_alias: visitAliasStatement(node); break;
        case token_undef: visitUndefStatement(node); break;
        case token_if: case token_unless: case token_ternary:
          visitIfStatement(node);
          break;
        case token_begin: visitBeginStatement(node); break;
        case token_up_begin:
        case token_up_end: visitUpBeginEndStatement(node); break;
        case token_case: visitCaseStatement(node); break;
        case token_while: case token_until: visitWhileStatement(node); break;
        case token_for: visitForStatement(node); break;
        case token_class: visitClassStatement(node); break;
        case token_singleton_class: visitSingletonClass(node); break;
        case token_module: visitModuleStatement(node); break;
        case token_function: visitMethodStatement(node); break;
        case token_method_call: checkMethodCall(node); break;
        case token_assign:
        case token_op_assign: visitAssignmentStatement(node); break;
        case token_object: visitVariable(node); break;
        case token_hash: visitHash(node); break;
        case token_array: visitArray(node); break;
        case token_array_value: visitArrayValue(node); break;
        case token_defined: visitDefined(node); break;
        case token_unary_plus: case token_unary_minus: case token_neg:
        case token_not:
            visitUnary(node);
            break;
        case token_cmp: case token_eq: case token_eqq: case token_match:
        case token_nmatch: case token_greater: case  token_geq:
        case token_lesser:  case token_leq:
        case token_plus: case token_minus: case token_mul: case token_div:
        case token_mod: case token_lshift: case token_rshift: case token_pow:
            visitBinary(node);
            break;
        case token_dot2: case token_dot3:
            visitRange(node);
            break;
        case token_or: case token_and: case token_kw_and:
        case token_kw_not: case token_kw_or:
            visitBoolean(node);
            break;
        case token_numeric: visitNumeric(node); break;
        case token_string: visitString(node); break;
        case token_regexp: case token_heredoc: visitRegexp(node); break;
        case token_nil: visitNil(node); break;
        case token_true: visitTrue(node); break;
        case token_false: visitFalse(node); break;
        case token_line: visitLine(node); break;
        case token_file: visitFile(node); break;
        case token_encoding: visitEncoding(node); break;
        case token_symbol: case token_key: case token_break:
        case token_next: case token_redo: case token_retry:
        case token__end__:
            return;
    }
}

void RubyAstVisitor::visitStatements(RubyAst *list)
{
    RubyAst *child = new RubyAst(list->tree, list->context);
    for (Node *n = child->tree; n != NULL; n = n->next) {
        visitNode(child);
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

void RubyAstVisitor::checkMethodCall(RubyAst *mc)
{
    /*
     * The method call body resides in the left child. Check if this
     * is either a require, an include/extend or just a normal method call.
     */
    if (mc->tree->l != NULL) {
      const QByteArray & name = QByteArray(mc->tree->l->name);
      if (name == "require")
          visitRequire(mc);
      else if (name == "include")
          visitInclude(mc);
      else if (name == "extend")
          visitExtend(mc);
      else
          visitMethodCall(mc);
    } else
        visitMethodCall(mc);
}

} // End of namespace Ruby

