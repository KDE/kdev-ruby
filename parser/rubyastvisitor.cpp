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
    Node *aux = node->tree;

    for (Node *n = aux; n != NULL; n = n->next) {
        visitNode(node);
        node->tree = n->next;
    }
    node->tree = aux;
}

void RubyAstVisitor::visitVariable(RubyAst *node)
{
    Q_UNUSED(node)
}

void RubyAstVisitor::visitName(RubyAst *node)
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
    /*
     * l -> list of variables contained inside the string (by using #{var}).
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitStatements(node);
    node->tree = n;
}

void RubyAstVisitor::visitSymbol(RubyAst *node)
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

    Node *n = node->tree;
    if (!n)
        return;

    node->tree = n->l;
    visitStatements(node);
    node->tree = n->r;
    visitNode(node);
    node->tree = n->cond;
    visitNode(node);
    node->tree = n->ensure;
    visitNode(node);
    node->tree = n;
}

void RubyAstVisitor::visitBinary(RubyAst *node)
{
    /*
     * l -> left operator.
     * r -> right operator.
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitNode(node);
    node->tree = n->r;
    visitNode(node);
    node->tree = n;
}

void RubyAstVisitor::visitBoolean(RubyAst *node)
{
    /* Same as for the visitBinary method  */

    Node *n = node->tree;
    node->tree = n->l;
    visitNode(node);
    node->tree = n->r;
    visitNode(node);
    node->tree = n;
}

void RubyAstVisitor::visitRange(RubyAst *node)
{
    /* Same as for the visitBinary method  */

    Node *n = node->tree;
    node->tree = n->l;
    visitNode(node);
    node->tree = n->r;
    visitNode(node);
    node->tree = n;
}

void RubyAstVisitor::visitUnary(RubyAst *node)
{
    /*
     * l -> the operator.
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitNode(node);
    node->tree = n;
}

void RubyAstVisitor::visitArray(RubyAst *node)
{
    /*
     * l -> list of statements (the items of the array).
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitStatements(node);
    node->tree = n;
}

void RubyAstVisitor::visitArrayValue(RubyAst *node)
{
    /*
     * l -> the node containing the Array object.
     * r -> the index expression.
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitNode(node);
    node->tree = n->r;
    visitStatements(node);
    node->tree = n;
}

void RubyAstVisitor::visitHash(RubyAst *node)
{
    /*
     * l -> list of hash items.
     */

    Node *n = node->tree;
    node->tree = n->l;
    for (; node->tree != NULL; node->tree = node->tree->next)
        visitBinary(node);
    node->tree = n;
}

void RubyAstVisitor::visitReturnStatement(RubyAst *node)
{
    /*
     * l -> the return expression.
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitNode(node);
    node->tree = n;
}

void RubyAstVisitor::visitUndefStatement(RubyAst *node)
{
    /*
     * l -> list of undef items.
     */

    Node *n = node->tree;
    node->tree = n->r;
    visitStatements(node);
    node->tree = n;
}

void RubyAstVisitor::visitAliasStatement(RubyAst *node)
{
    /* Same as for the visitBinary method. */

    Node *n = node->tree;
    node->tree = n->l;
    visitNode(node);
    node->tree = n->r;
    visitNode(node);
    node->tree = n;
}

void RubyAstVisitor::visitYieldStatement(RubyAst *node)
{
    /*
     * l -> the yield expression.
     */
    Node *n = node->tree;
    node->tree = n->l;
    visitNode(node);
    node->tree = n;
}

void RubyAstVisitor::visitAssignmentStatement(RubyAst *node)
{
    /*
     * l -> the left side of the assignment.
     * r -> the right side of the assignment.
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitStatements(node);
    node->tree = n->r;
    visitStatements(node);
    node->tree = n;
}

void RubyAstVisitor::visitIfStatement(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     * r -> the "tail": optional list of elsif's and an optional else.
     * cond -> the condition expression.
     */

    Node *n = node->tree;
    node->tree = n->cond;
    visitNode(node);
    node->tree = n->l;
    visitStatements(node);
    node->tree = n->r;
    visitIfTail(node);
    node->tree = n;
}

void RubyAstVisitor::visitCaseStatement(RubyAst *node)
{
    /*
     * l -> the case body: list of when statements and an optional else
     * statement at the end.
     * cond -> the condition expression.
     */

    Node *n = node->tree;
    node->tree = n->cond;
    visitNode(node);
    node->tree = n->l;
    visitWhenStatements(node);
    node->tree = n;
}

void RubyAstVisitor::visitBeginStatement(RubyAst *node)
{
    /*
     * l -> the body of the begin statement. Note that this body is not just
     * a list of "regular" statement, check the visitBody method for more info.
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitBody(node);
    node->tree = n;
}

void RubyAstVisitor::visitUpBeginEndStatement(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitStatements(node);
    node->tree = n;
}

void RubyAstVisitor::visitWhileStatement(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     * cond -> the condition expression.
     */

    Node *n = node->tree;
    node->tree = n->cond;
    visitNode(node);
    node->tree = n->l;
    visitStatements(node);
    node->tree = n;
}

void RubyAstVisitor::visitForStatement(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     * r -> list of variables declared before the "in" keyword.
     * cond -> the expression after the "in" keyword.
     */

    Node *n = node->tree;
    node->tree = n->r;
    visitStatements(node);
    node->tree = n->cond;
    visitNode(node);
    node->tree = n->l;
    visitStatements(node);
    node->tree = n;
}

void RubyAstVisitor::visitMethodStatement(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     * r -> list of method arguments.
     */

    Node *n = node->tree;
    if (!n)
        return;

    node->tree = n->r;
    visitMethodArguments(node);
    node->tree = n->l;
    visitBody(node);
    node->tree = n;
}

void RubyAstVisitor::visitMethodArguments(RubyAst *node)
{
    /* Just iterate over the "next" pointer. */

    Node *aux = node->tree;
    for (Node *n = aux; n != NULL; n = n->next) {
        visitParameter(node);
        node->tree = n->next;
    }
    node->tree = aux;
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
     * r -> the name of the class.
     * cond -> the superclass node.
     */

    Node *n = node->tree;
    node->tree = n->cond;
    visitNode(node);
    node->tree = n->l;
    visitBody(node);
    node->tree = n->r;
    visitClassName(node);
    node->tree = n;
}

void RubyAstVisitor::visitSingletonClass(RubyAst *node)
{
    /*
     * l -> the body of the class statement. Note that this body is not just
     * a list of "regular" statement, check the visitBody method for more info.
     * r -> the expression after the lshift ("<<") operator.
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitBody(node);
    node->tree = n->r;
    visitNode(node);
    node->tree = n;
}

void RubyAstVisitor::visitModuleStatement(RubyAst *node)
{
    /*
     * l -> the body of the class statement. Note that this body is not just
     * a list of "regular" statement, check the visitBody method for more info.
     * r -> the name of the module.
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitBody(node);
    node->tree = n->r;
    visitClassName(node);
    node->tree = n;
}

void RubyAstVisitor::visitMethodCall(RubyAst *node)
{
    /*
     * l -> the caller (note that it's a list, i.e. A::B::foo).
     * r -> the arguments for this method call.
     * cond -> an optional Ruby block.
     */

    /*
     * Note that the l pointer can contain again another method call.
     * This happens for example here:
     *  Class.new { def foo(a, b); end }.new.foo(1, 2)
     * In order to get everything straight, all builders end up
     * re-implementing this method. This is why this method has no
     * implementation by default.
     */
    Q_UNUSED(node);
}

void RubyAstVisitor::visitSuper(RubyAst *node)
{
    /*
     * r -> the arguments passed to the super call.
     */

    Node *n = node->tree;
    node->tree = n->r;
    for (Node *aux = n->r; aux != NULL; aux = aux->next) {
        visitNode(node);
        node->tree = aux->next;
    }
    node->tree = n;
}

void RubyAstVisitor::visitLambda(RubyAst *node)
{
    /*
     * cond -> the block of this lambda expression.
     */

    Node *n = node->tree;
    node->tree = n->cond;
    visitBlock(node);
    node->tree = n;
}

void RubyAstVisitor::visitBlock(RubyAst *node)
{
    /*
     * l -> list of inner statements.
     * r -> list of block variables.
     */

    Node *aux = node->tree;
    if (!aux)
        return;
    node->tree = aux->r;
    visitBlockVariables(node);
    node->tree = aux->l;
    visitStatements(node);
    node->tree = aux;
}

void RubyAstVisitor::visitBlockVariables(RubyAst *node)
{
    /*
     * Just iterate over the next pointer.
     */

    Node *aux = node->tree;
    for (Node *n = node->tree; n != NULL; n = n->next) {
        visitNode(node);
        node->tree = n->next;
    }
    node->tree = aux;
}

void RubyAstVisitor::visitRequire(RubyAst *node, bool relative)
{
    Q_UNUSED(node)
    Q_UNUSED(relative)
}

void RubyAstVisitor::visitMixin(RubyAst *node, bool include)
{
    Q_UNUSED(node);
    Q_UNUSED(include);
}

void RubyAstVisitor::visitDefined(RubyAst *node)
{
    /*
     * l -> the expression from the "defined" statement.
     */

    Node *n = node->tree;
    node->tree = n->l;
    visitNode(node);
    node->tree = n;
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

void RubyAstVisitor::visitAccessSpecifier(short int policy)
{
    Q_UNUSED(policy)
}

void RubyAstVisitor::visitClassName(RubyAst *node)
{
    Q_UNUSED(node);
}

void RubyAstVisitor::visitNode(RubyAst *node)
{
    Node *n = node->tree;
    QByteArray name;

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
        case token_super: visitSuper(node); break;
        case token_method_call: checkMethodCall(node); break;
        case token_assign:
        case token_op_assign: visitAssignmentStatement(node); break;
        case token_object:
            name = QByteArray(node->tree->name);
            if (name == "public")
                visitAccessSpecifier(0);
            else if (name == "protected")
                visitAccessSpecifier(1);
            else if (name == "private")
                visitAccessSpecifier(2);
            else
                visitName(node);
            break;
        case token_hash: visitHash(node); break;
        case token_array: visitArray(node); break;
        case token_array_value: visitArrayValue(node); break;
        case token_defined: visitDefined(node); break;
        case token_unary_plus: case token_unary_minus: case token_neg:
        case token_not:
            visitUnary(node);
            break;
        case token_plus: case token_minus: case token_mul: case token_div:
        case token_mod: case token_lshift: case token_rshift: case token_pow:
            visitBinary(node);
            break;
        case token_dot2: case token_dot3:
            visitRange(node);
            break;
        case token_cmp: case token_eq: case token_eqq: case token_match:
        case token_nmatch: case token_greater: case  token_geq:
        case token_lesser:  case token_leq:
        case token_or: case token_and: case token_kw_and:
        case token_kw_not: case token_kw_or:
            visitBoolean(node);
            break;
        case token_numeric: visitNumeric(node); break;
        case token_string: case token_heredoc: visitString(node); break;
        case token_regexp: visitRegexp(node); break;
        case token_nil: visitNil(node); break;
        case token_true: visitTrue(node); break;
        case token_false: visitFalse(node); break;
        case token_line: visitLine(node); break;
        case token_file: visitFile(node); break;
        case token_encoding: visitEncoding(node); break;
        case token_self: visitSelf(node); break;
        case token_symbol: case token_key: visitSymbol(node); break;
        case token_break: case token__end__: case token_next:
        case token_redo: case token_retry:
            return;
    }
}

void RubyAstVisitor::visitStatements(RubyAst *list)
{
    Node *aux = list->tree;
    for (Node *n = aux; n != NULL; n = n->next) {
        visitNode(list);
        list->tree = n->next;
    }
    list->tree = aux;
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
    tail->tree = n;
}

void RubyAstVisitor::visitWhenStatements(RubyAst *list)
{
    Node *n = list->tree;
    if (!n)
        return;

    /* Check whether this is a when or an else statement */
    if (n->kind == token_when) {
        list->tree = n->cond;
        visitNode(list);
        list->tree = n->l;
        visitStatements(list);
        list->tree = n->r;
        visitWhenStatements(list);
    } else {
        list->tree = n->l;
        visitStatements(list);
    }
    list->tree = n;
}

void RubyAstVisitor::checkMethodCall(RubyAst *mc)
{
    /*
     * The method call body resides in the left child. Check if this
     * is either a require, an include/extend or just a normal method call.
     * If the left child is NULL, this is not a method call but a lambda
     * expression.
     */
    if (mc->tree->l != NULL) {
        const QByteArray &name = QByteArray(mc->tree->l->name);
        if (name == "require")
            visitRequire(mc);
        else if (name == "include")
            visitMixin(mc, true);
        else if (name == "extend")
            visitMixin(mc, false);
        else if (name == "require_relative")
            visitRequire(mc, true);
        else
            visitMethodCall(mc);
    } else
        visitLambda(mc);
}

} // End of namespace Ruby
