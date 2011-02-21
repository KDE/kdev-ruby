/*
* This file is part of KDevelop
*
* Copyright 2010 Niko Sams <niko.sams@gmail.com>
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
#include "declarationbuilder.h"

#include <interfaces/icore.h>
#include <language/duchain/classdeclaration.h>
#include <language/duchain/functiondeclaration.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/types/functiontype.h>

#include "parser/rubyast.h"
#include "editorintegrator.h"

namespace Ruby
{

DeclarationBuilder::DeclarationBuilder(EditorIntegrator* editor):
    DeclarationBuilderBase()
{
    setEditor(editor);
}

void DeclarationBuilder::closeDeclaration()
{
    eventuallyAssignInternalContext();
    DeclarationBuilderBase::closeDeclaration();
}

void DeclarationBuilder::visitClass(ClassAST* ast)
{
    {
        KDevelop::RangeInRevision range = editor()->findRange(ast);
        KDevelop::QualifiedIdentifier id(KDevelop::Identifier(KDevelop::IndexedString(ast->name->name)));

        KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());

        KDevelop::ClassDeclaration* decl = openDefinition<KDevelop::ClassDeclaration>(id, range);
        decl->setDeclarationIsDefinition(true);
        decl->setKind(KDevelop::Declaration::Type);
        decl->clearBaseClasses();
        decl->setClassType(KDevelop::ClassDeclarationData::Class);
    }
    DeclarationBuilderBase::visitClass(ast);
    closeDeclaration();
}

void DeclarationBuilder::visitFunction(FunctionAST* ast)
{
    {
        KDevelop::RangeInRevision range = editor()->findRange(ast->name);
        KDevelop::QualifiedIdentifier id(KDevelop::Identifier(KDevelop::IndexedString(ast->name->name)));

        KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());

        if (ast->isMember) {
            KDevelop::ClassFunctionDeclaration *decl = openDefinition<KDevelop::ClassFunctionDeclaration>(id, range);
            decl->setAccessPolicy(ast->access);
            decl->setDeclarationIsDefinition(true);
            decl->setKind(KDevelop::Declaration::Type);
        } else {
            KDevelop::FunctionDeclaration *decl = openDefinition<KDevelop::FunctionDeclaration>(id, range);
            decl->setDeclarationIsDefinition(true);
            decl->setKind(KDevelop::Declaration::Type);
        }
    }
    DeclarationBuilderBase::visitFunction(ast);
    closeDeclaration();
}

void DeclarationBuilder::visitFunctionArgument(FunctionArgumentAST* ast)
{
    {
        // create variable declaration for argument
        KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
        KDevelop::RangeInRevision range = editor()->findRange(ast->name);
        KDevelop::QualifiedIdentifier id(KDevelop::Identifier(KDevelop::IndexedString(ast->name->name)));

        openDefinition<KDevelop::Declaration>(id, range);
        currentDeclaration()->setKind(KDevelop::Declaration::Instance);
    }
    DeclarationBuilderBase::visitFunctionArgument(ast);
    closeDeclaration();
}

void DeclarationBuilder::updateCurrentType()
{
    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
    currentDeclaration()->setAbstractType(currentAbstractType());
}

}
