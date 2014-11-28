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

#include <parser/ast.h>

using namespace ruby;

Ast::Ast(Node *n, KDevelop::DUContext *ctx)
    : tree(n)
    , context(ctx)
    , foundProblems(false)
{
}

NameAst::NameAst(const Ast *ast) : Ast(ast->tree, ast->context)
{
    if (tree == nullptr) {
        value = "nil";
    } else if (tree->kind == token_class || tree->kind == token_module) {
        value = QString(rb_name_node(tree)->name);
    } else if (tree->kind == token_function) {
        value = QString(rb_name_node(tree)->name);
    } else {
        value = QString(tree->name);
    }
}

