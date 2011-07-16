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


/* TODO: Under construction */

#include <parser/parserexport.h>
// #include "node.h"
#include "rubyast.h"


/* TODO: Document: The following are based on the enum node_t from parser/node.h */


using namespace KDevelop;

namespace Ruby
{

class KDEVRUBYPARSER_EXPORT RubyAstVisitor
{
public:
    RubyAstVisitor();
    virtual ~RubyAstVisitor();

    void visitCode(RubyAst *node);
    void visitNode(RubyAst *node);

    virtual void visitModuleStatement(RubyAst *node);
    virtual void visitClassStatement(RubyAst *node); // TODO: And singleton?
    virtual void visitMethodStatement(RubyAst *node); //TODO rename to Method
    virtual void visitMethodArguments(RubyAst *node);
    virtual void visitBody(RubyAst *node);
    virtual void visitVariable(RubyAst *node);
    virtual void visitAssignmentStatement(RubyAst *node);
};

}


#endif // RUBYASTVISITOR_H

