/*
* This file is part of KDevelop
*
* Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU Library General Public License as
* published by the Free Software Foundation; either version 2 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public
* License along with this program; if not, write to the
* Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/
#include "rubyast.h"

namespace Ruby {

ProgramAST::~ProgramAST()
{
    foreach (ClassAST *klass, classes)
        delete klass;
    foreach (FunctionAST *fun, functions)
        delete fun;
}

AST::Kind ProgramAST::kind()
{
    return AST::Program;
}

AST::Kind ClassAST::kind()
{
    return AST::Class;
}

ClassAST::~ClassAST()
{
    foreach (FunctionAST *fun, functions)
        delete fun;
    delete name;
}

ClassAST* ProgramAST::findClass(const QString& name)
{
    foreach (ClassAST *klass, classes) {
        if (klass->name->name == name)
            return klass;
    }
    return 0;
}

AST::Kind NameAST::kind()
{
    return AST::Name;
}

AST::Kind FunctionAST::kind()
{
    return AST::Function;
}

FunctionAST::~FunctionAST()
{
    delete name;
}

FunctionAST* ClassAST::findFunction(const QString &name)
{
    foreach (FunctionAST *fun, functions) {
        if (fun->name->name == name)
            return fun;
    }
    return 0;
}

}
