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


#ifndef RUBYAST_H
#define RUBYAST_H


// KDevelop + Ruby
#include <language/duchain/ducontext.h>
#include <parser/node.h>


namespace Ruby
{

/**
 * @class RubyAst
 *
 * This class represents a Ruby AST (Abstract Syntax Tree). It contains
 * the code (tree) and the associated KDevelop::DUContext.
 */
class RubyAst
{
public:
    /**
     * Constructor.
     * @param n the code that this RubAst represents.
     * @param ctx the KDevelop::DUContext associated with it.
     */
    RubyAst(Node *n, KDevelop::DUContext *ctx = NULL) : tree (n), context(ctx)
    {
        /* There's nothing to do here! */
    };
    
public:
    /// The tree of this AST.
    Node *tree;

    /// The DUContext for this AST.
    KDevelop::DUContext *context;
};


/**
 * @class NameAst
 *
 * Extends the RubyAst class to easily obtain the identifier for
 * a RubyAst.
 */
class NameAst : public RubyAst
{
public:
    /**
     * Constructor.
     * @param ast the RubyAst this class extends.
     */
    NameAst(const RubyAst *ast) : RubyAst(ast->tree, ast->context)
    {
        if (tree == NULL)
            value = "nil";
        else if (tree->kind == token_class || tree->kind == token_module)
            value = QString(rb_name_node(tree)->name);
        else if (tree->kind == token_function)
            value = QString(rb_name_node(tree)->name);
        else
            value = QString(tree->name);
    };

public:
    /// The QString that represents this class.
    QString value;
};

} // End of namespace Ruby


#endif // RUBYAST_H

