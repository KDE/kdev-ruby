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
#include "declarations/variabledeclaration.h"
#include <duchain/editorintegrator.h>
#include <rubydefs.h>
#include <duchain/types/objecttype.h>


namespace Ruby
{

DeclarationBuilder::DeclarationBuilder()
    : DeclarationBuilderBase()
{
    /* There's nothing to do here! */
}

DeclarationBuilder::DeclarationBuilder(EditorIntegrator *editor)
    : DeclarationBuilderBase(), m_editor(editor)
{
    setEditor(editor);
}

DeclarationBuilder::~DeclarationBuilder()
{
    /* There's nothing to do here! */
}

ReferencedTopDUContext DeclarationBuilder::build(const IndexedString &url, RubyAst *node, ReferencedTopDUContext updateContext)
{
    return DeclarationBuilderBase::build(url, node, updateContext);
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

void DeclarationBuilder::visitMethodStatement(RubyAst *node)
{
    openMethodDeclaration(node);
    RubyAstVisitor::visitMethodStatement(node);

    {
        DUChainWriteLocker wlock(DUChain::lock());
        closeContext();
    }
    closeType();
    closeDeclaration();
}

void DeclarationBuilder::visitVariable(RubyAst *node)
{
//BEGIN Old implementation
//     DUChainWriteLocker wlock(DUChain::lock());
//     RangeInRevision range = editorFindRange(node, node);
//     QualifiedIdentifier id = identifierForNode(new NameAst(node));
//     Declaration *decl = openDefinition<VariableDeclaration>(id, range);
//     IntegralType::Ptr type(new IntegralType(IntegralType::TypeNull));
//
//     decl->setKind(Declaration::Instance);
//     decl->setType(type);
//     eventuallyAssignInternalContext();
//     closeDeclaration();
//END Old Implementation
//BEGIN New implementation
    Q_ASSERT(node);
    DUChainWriteLocker lock(DUChain::lock());
    Declaration *dec = 0;
    RangeInRevision range = editorFindRange(node, node);
    QualifiedIdentifier id = identifierForNode(new NameAst(node));
    QList<Declaration *> existing = currentContext()->findDeclarations(id.last(),
                                                                    CursorInRevision::invalid(), 0,
                                                                    DUContext::DontSearchInParent);

    QList<Declaration *> remaining;
    foreach (Declaration *d, existing) {
        if (!wasEncountered(d)) {
            openDeclarationInternal(d);
            d->setRange(editorFindRange(node, node));
            setEncountered(d);
            dec = d;
        } else
           remaining << d;
    }

    //BEGIN Debug, Remove me when everything is fine ;)
    foreach (const Declaration *decla, remaining) {
        debug() << "REMAINING: " << decla->qualifiedIdentifier();
    }
    //END Debug

    if (remaining.isEmpty()) {
        //TODO
        dec = openDeclaration<VariableDeclaration>(id, range);
        ObjectType::Ptr type(new ObjectType());

        dec->setKind(Declaration::Instance);
        dec->setType(type);
        eventuallyAssignInternalContext();
        closeDeclaration();
    } else {
        //TODO: too dumb
//         IntegralType::Ptr type(new IntegralType(IntegralType::TypeNull));
//         dec->setType(type);
    }

//END New implementation
}

void DeclarationBuilder::openMethodDeclaration(RubyAst* node)
{
    DUChainWriteLocker lock(DUChain::lock());
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = identifierForNode(new NameAst(node));
    FunctionDeclaration *decl = openDeclaration<FunctionDeclaration>(id, range);
    FunctionType::Ptr type = FunctionType::Ptr(new FunctionType());

    type->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid)));
    decl->setType(type);
    openType(type);
    openContextForMethodDefinition(node);
    decl->setInternalContext(currentContext());
}

void DeclarationBuilder::openClassDeclaration(RubyAst *node, bool isClass)
{
    DUChainWriteLocker wlock(DUChain::lock());
    StructureType::Ptr type = StructureType::Ptr(new StructureType());
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = identifierForNode(new NameAst(node));
    ClassDeclaration *decl = openDeclaration<ClassDeclaration>(id, range);
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

KDevelop::RangeInRevision DeclarationBuilder::getNameRange(RubyAst *node)
{
    return m_editor->findRange(getNameNode(node->tree));
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
