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


#ifndef RUBYASTVISITOR_H
#define RUBYASTVISITOR_H


// Ruby
#include <parser/parserexport.h>
#include <parser/rubyast.h>


using namespace KDevelop;

namespace Ruby
{

/**
 * @class RubyAstVisitor
 *
 * This class represents the Visitor of the RubyAst class.
 */
class KDEVRUBYPARSER_EXPORT RubyAstVisitor
{
public:
    /**
     * Constructor.
     */
    RubyAstVisitor();

    /**
     * Destructor.
     */
    virtual ~RubyAstVisitor();

    /**
     * This is the entry point of the visitor. It means that to visit a
     * valid RubyAst we should call this method.
     *
     * @param node The root of the AST.
     */
    void visitCode(RubyAst *node);

protected:
    // TODO: The methods below lack of documentation right now :(

    virtual void visitVariable(RubyAst *node);
    virtual void visitBody(RubyAst *node);
    virtual void visitBinary(RubyAst *node);
    virtual void visitBoolean(RubyAst *node);
    virtual void visitUnary(RubyAst *node);
    virtual void visitArray(RubyAst *node);
    virtual void visitHash(RubyAst *node);
    virtual void visitReturnStatement(RubyAst *node);
    virtual void visitUndefStatement(RubyAst *node);
    virtual void visitAliasStatement(RubyAst *node);
    virtual void visitYieldStatement(RubyAst *node);
    virtual void visitAssignmentStatement(RubyAst *node);
    virtual void visitIfStatement(RubyAst *node);
    virtual void visitCaseStatement(RubyAst *node);
    virtual void visitBeginStatement(RubyAst *node);
    virtual void visitUpBeginEndStatement(RubyAst *node);
    virtual void visitWhileStatement(RubyAst *node);
    virtual void visitForStatement(RubyAst *node);
    virtual void visitMethodStatement(RubyAst *node);
    virtual void visitMethodArguments(RubyAst *node);
    virtual void visitParameter(RubyAst *node);
    virtual void visitClassStatement(RubyAst *node); // TODO: And singleton?
    virtual void visitModuleStatement(RubyAst *node);
    virtual void visitMethodCall(RubyAst *node);
    virtual void visitBlock(RubyAst *node);

private:
    /**
     * @internal Given a node, it calls the appropiate method in order to
     * successfully visit this node.
     *
     * @param node The given node.
     */
    void visitNode(RubyAst *node);

    /**
     * @internal Helper method useful to visit a list of statements.
     *
     * @param list A node that is the first item of a list of nodes.
     */
    void visitStatements(RubyAst *list);

    /**
     * @internal Helper method used for the visitIfStatement method. Its
     * goal is to visit a tail of an if statement.
     *
     * @param tail The tail of an if statement.
     */
    void visitIfTail(RubyAst *tail);

    /**
     * @internal Helper method that goes through a list of when statements.
     * Obviously, this method is used by the visitCaseStatement method.
     *
     * @param list A node that is the first item of a list of when statements.
     */
    void visitWhenStatements(RubyAst *list);
};

} // End of namespace Ruby


#endif // RUBYASTVISITOR_H

