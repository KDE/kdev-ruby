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


/*
 * TODO: This file is still under construction
 */


#include "node.h"
#include <language/duchain/ducontext.h>


class RubyAst
{
public:
    RubyAst(Node *n) : tree (n), context(0) {};
    
public:
    Node *tree;
    KDevelop::DUContext *context;
};


#endif // RUBYAST_H

