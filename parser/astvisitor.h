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

#ifndef RUBY_AST_VISITOR_H
#define RUBY_AST_VISITOR_H

#include <parser/ast.h>
#include <parser/export.h>

namespace ruby {

/**
 * @class AstVisitor
 *
 * This class represents the Visitor of the Ast class.
 */
class KDEVRUBYPARSER_EXPORT AstVisitor
{
public:
    virtual ~AstVisitor();

    /**
     * This is the entry point of the visitor. It means that to visit a
     * valid Ast we should call this method.
     *
     * @param node The root of the AST.
     */
    void visitCode(Ast *node);

    /**
     * Given a node, it calls the appropiate method in order to successfully
     * visit this node.
     *
     * @param node The given node.
     */
    void visitNode(Ast *node);

protected:
    /**
     * @returns true if the given name identifies an variable/method/... that
     * has already been declared in the current context. This method will be
     * called when it's needed to resolve the ambiguity of special methods like:
     * require, include, ...
     */
    virtual bool declaredInContext(const QByteArray &name) const = 0;

protected:
    /// And the following is a list of virtual methods that can be overriden.

    virtual void visitName(Ast *node);
    virtual void visitString(Ast *node);
    virtual void visitRegexp(Ast *node);
    virtual void visitNumeric(Ast *node);
    virtual void visitSymbol(Ast *node);
    virtual void visitBody(Ast *node);
    virtual void visitBinary(Ast *node);
    virtual void visitBoolean(Ast *node);
    virtual void visitRange(Ast *node);
    virtual void visitUnary(Ast *node);
    virtual void visitArray(Ast *node);
    virtual void visitArrayValue(Ast *node);
    virtual void visitHash(Ast *node);
    virtual void visitReturnStatement(Ast *node);
    virtual void visitUndefStatement(Ast *node);
    virtual void visitAliasStatement(Ast *node);
    virtual void visitYieldStatement(Ast *node);
    virtual void visitAssignmentStatement(Ast *node);
    virtual void visitIfStatement(Ast *node);
    virtual void visitCaseStatement(Ast *node);
    virtual void visitBeginStatement(Ast *node);
    virtual void visitUpBeginEndStatement(Ast *node);
    virtual void visitWhileStatement(Ast *node);
    virtual void visitForStatement(Ast *node);
    virtual void visitMethodStatement(Ast *node);
    virtual void visitMethodArguments(Ast *node);
    virtual void visitParameter(Ast *node);
    virtual void visitClassStatement(Ast *node);
    virtual void visitSingletonClass(Ast *node);
    virtual void visitModuleStatement(Ast *node);
    virtual void visitMethodCall(Ast *node);
    virtual void visitSuper(Ast *node);
    virtual void visitLambda(Ast *node);
    virtual void visitBlock(Ast *node);
    virtual void visitBlockVariables(Ast *node);
    virtual void visitRequire(Ast *node, bool relative = false);
    virtual void visitMixin(Ast *node, bool include);
    virtual void visitDefined(Ast *node);
    virtual void visitTrue(Ast *node);
    virtual void visitFalse(Ast *node);
    virtual void visitNil(Ast *node);
    virtual void visitLine(Ast *node);
    virtual void visitFile(Ast *node);
    virtual void visitEncoding(Ast *node);
    virtual void visitSelf(Ast *node);
    virtual void visitAccessSpecifier(const access_t policy);
    virtual void visitClassName(Ast *node);
    virtual void visitRescue(Ast *node);
    virtual void visitRescueArg(Ast *node);
    virtual void visitEnsure(Ast *node);

private:
    /**
     * @internal Helper method useful to visit a list of statements.
     *
     * @param list A node that is the first item of a list of nodes.
     */
    void visitStatements(Ast *list);

    /**
     * @internal Helper method used for the visitIfStatement method. Its
     * goal is to visit a tail of an if statement.
     *
     * @param tail The tail of an if statement.
     */
    void visitIfTail(Ast *tail);

    /**
     * @internal Helper method that goes through a list of when statements.
     * Obviously, this method is used by the visitCaseStatement method.
     *
     * @param list A node that is the first item of a list of when statements.
     */
    void visitWhenStatements(Ast *list);

    /**
     * @internal Helper method that checks if this is either a require, an
     * include/extend or just a regular method call.
     *
     * @param mc The given method call node.
     */
    void checkMethodCall(Ast *mc);
};

}

#endif // RUBY_ASTVISITOR_H

