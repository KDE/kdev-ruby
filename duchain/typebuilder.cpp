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
#include "typebuilder.h"

#include <language/duchain/types/unsuretype.h>
#include <language/duchain/types/structuretype.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>

namespace Ruby  {

TypeBuilder::TypeBuilder(): TypeBuilderBase()
{
}

void TypeBuilder::visitClass(ClassAST* ast)
{
    KDevelop::StructureType::Ptr classType = KDevelop::StructureType::Ptr(new KDevelop::StructureType());
    openType(classType);
    TypeBuilderBase::visitClass(ast);
    updateCurrentType();
    closeType();
}

void TypeBuilder::visitFunction(FunctionAST* ast)
{
    KDevelop::FunctionType::Ptr functionType = KDevelop::FunctionType::Ptr(new KDevelop::FunctionType());
    openType(functionType);

    TypeBuilderBase::visitFunction(ast);
    updateCurrentType();

    closeType();
}

void TypeBuilder::visitFunctionArgument(FunctionArgumentAST* ast)
{
    KDevelop::AbstractType::Ptr type(new KDevelop::IntegralType(KDevelop::IntegralType::TypeMixed));
    openAbstractType(type);
    TypeBuilderBase::visitFunctionArgument(ast);
    closeType();

    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
    currentType<KDevelop::FunctionType>()->addArgument(type);
}

void TypeBuilder::updateCurrentType()
{
    //reimplemented in DeclarationBuilder
}

}
