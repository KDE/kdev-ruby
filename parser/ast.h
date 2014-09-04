/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#ifndef RUBY_AST_H
#define RUBY_AST_H


#include <language/duchain/ducontext.h>
#include <parser/export.h>
#include <parser/node.h>


namespace Ruby
{

/**
 * @class RubyAst
 *
 * This class represents a Ruby AST (Abstract Syntax Tree). It contains
 * the code (tree) and the associated KDevelop::DUContext.
 */
class KDEVRUBYPARSER_EXPORT Ast
{
public:
    /**
     * Constructor.
     *
     * @param n the code that this RubAst represents.
     * @param ctx the KDevelop::DUContext associated with it.
     */
    Ast(Node *n, KDevelop::DUContext *ctx = nullptr);

public:
    /// The tree of this AST.
    Node *tree;

    /// The DUContext for this AST.
    KDevelop::DUContext *context;

    /// Used when we find a problem.
    bool foundProblems;
};

/**
 * @class NameAst
 *
 * Extends the RubyAst class to easily obtain the identifier for
 * a RubyAst.
 */
class KDEVRUBYPARSER_EXPORT NameAst : public Ast
{
public:
    /**
     * Constructor.
     *
     * @param ast the RubyAst this class extends.
     */
    NameAst(const Ast *ast);

public:
    /// The QString that represents this class.
    QString value;
};

}

#endif // RUBY_AST_H
