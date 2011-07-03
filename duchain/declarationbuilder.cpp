/* This file is part of KDevelop
 *
 * Copyright 2010 Niko Sams <niko.sams@gmail.com>
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright 2011 Miquel Sabaté <mikisabate@gmail.com>
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


#include <duchain/declarationbuilder.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>


namespace Ruby
{

DeclarationBuilder::DeclarationBuilder()
    : DeclarationBuilderBase()
{
    /* There's nothing to do here! */
}

DeclarationBuilder::DeclarationBuilder(EditorIntegrator *editor):
    DeclarationBuilderBase()
{
    setEditor(editor);
}

DeclarationBuilder::~DeclarationBuilder()
{
    /* There's nothing to do here! */
}

void DeclarationBuilder::visitClassStatement(RubyAst *node)
{
    openClassDeclaration(node, true);
    RubyAstVisitor::visitClassStatement(node);

    {
        DUChainWriteLocker wlock(DUChain::lock());
        closeContext();
    }
    closeType();
    closeDeclaration();
}

void DeclarationBuilder::visitModuleStatement(RubyAst* node)
{
    openClassDeclaration(node, false);
    RubyAstVisitor::visitModuleStatement(node);

    {
        DUChainWriteLocker wlock(DUChain::lock());
        closeContext();
    }
    closeType();
    closeDeclaration();
}

void DeclarationBuilder::visitFunctionStatement(RubyAst *node)
{
    openMethodDeclaration(node);
    /* TODO
     * The following (thread-safe) steps have to be done:
     *  - Visit Method arguments.
     *  - Visit Method Body.
     */
    closeType();
    closeDeclaration();
}

void DeclarationBuilder::openMethodDeclaration(RubyAst* node)
{
    FunctionDeclaration *decl = openDeclaration<FunctionDeclaration>(new NameAst(node), node);
    FunctionType::Ptr type = FunctionType::Ptr(new FunctionType());
    type->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid)));
    {
        DUChainWriteLocker lock(DUChain::lock());
        decl->setType(type);
    }
    openType(type);
}

void DeclarationBuilder::openClassDeclaration(RubyAst *node, bool isClass)
{
    DUChainWriteLocker wlock(DUChain::lock());
    StructureType::Ptr type = StructureType::Ptr(new StructureType());
    ClassDeclaration *decl = openDeclaration<ClassDeclaration>(new NameAst(node), node);
    eventuallyAssignInternalContext();

    if (isClass) {
        decl->setKind(KDevelop::Declaration::Type);
        decl->setClassType(ClassDeclarationData::Class);
    } else {
        decl->setKind(KDevelop::Declaration::Namespace);
        decl->setClassType(ClassDeclarationData::Interface);
    }
    decl->clearBaseClasses();
    type->setDeclaration(decl);
    decl->setType(type);
    openType(type);
    openContextForClassDefinition(node);
    decl->setInternalContext(currentContext());
}

KDevelop::QualifiedIdentifier DeclarationBuilder::identifierForNode(NameAst *node)
{
    if (!node)
        return KDevelop::QualifiedIdentifier();
    return KDevelop::QualifiedIdentifier(node->value);
}

void DeclarationBuilder::closeDeclaration()
{
    if (currentDeclaration() && lastType()) {
        DUChainWriteLocker wlock(DUChain::lock());
        currentDeclaration()->setType(lastType());
    }
    eventuallyAssignInternalContext();
    DeclarationBuilderBase::closeDeclaration();
}

void DeclarationBuilder::updateCurrentType()
{
    DUChainWriteLocker lock(DUChain::lock());
    currentDeclaration()->setAbstractType(currentAbstractType());
}

}
