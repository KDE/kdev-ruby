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
#ifndef TYPEBUILDER_H
#define TYPEBUILDER_H

#include "contextbuilder.h"

#include <language/duchain/builders/abstracttypebuilder.h>

namespace Ruby {

typedef KDevelop::AbstractTypeBuilder<AST, NameAST, ContextBuilder> TypeBuilderBase;

class TypeBuilder: public TypeBuilderBase {
public:
    TypeBuilder();

protected:
    virtual void visitClass(ClassAST* ast);
    virtual void visitFunction(FunctionAST* ast);
    virtual void visitFunctionArgument(FunctionArgumentAST* ast);

    virtual void updateCurrentType();

};

}

#endif
