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
#include <language/duchain/types/unsuretype.h>
#include <KLocale>


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

void DeclarationBuilder::startVisiting(RubyAst* node)
{
    m_hasUnresolvedImports = false;
    DeclarationBuilderBase::startVisiting(node);
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
    QualifiedIdentifier id = identifierForNode(new NameAst(node));
    AbstractType::Ptr type(new ObjectType());
    declareVariable(currentContext(), type, id, node);
}

void DeclarationBuilder::visitReturnStatement(RubyAst *node)
{
    RubyAstVisitor::visitReturnStatement(node);
    if (node->tree->l != NULL) {
        if (!hasCurrentType()) {
            appendProblem(node->tree->l, "Return statement not within"
                                         " function declaration");
            return;
        }
        TypePtr<FunctionType> t = currentType<FunctionType>();
        AbstractType::Ptr encountered(new ObjectType()); // TODO: Should be the last type
        t->setReturnType(encountered);
    }
    setLastType(AbstractType::Ptr(0));
}

void DeclarationBuilder::declareVariable(DUContext *ctx, AbstractType::Ptr type,
                                         const QualifiedIdentifier &id, RubyAst *node)
{
    DUChainWriteLocker wlock(DUChain::lock());
    const RangeInRevision range = editorFindRange(node, node);

    /* Let's check if this variable is already declared */
    QList<Declaration *> decs = ctx->findDeclarations(id.first(), startPos(node), 0, DUContext::DontSearchInParent);
    if (!decs.isEmpty()) {
        QList< Declaration* >::const_iterator it = decs.constEnd() - 1;
        for (;; --it) {
           debug() << "Here";
            if (dynamic_cast<VariableDeclaration *>(*it)) {
                debug() << "Variable Declaration";
                if (!wasEncountered(*it)) {
                    setEncountered(*it); //TODO: can be improved
                    (*it)->setRange(range);
                }
                if ((*it)->abstractType() && !(*it)->abstractType()->equals(type.unsafeData())) {
                    // TODO: there are some validations to do here. Right now, just take this as an Unsure

                    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast((*it)->abstractType());
                    if ( !unsure ) {
                        unsure = UnsureType::Ptr(new UnsureType());
                        unsure->addType((*it)->indexedType());
                    }
                    unsure->addType(type->indexed());
                    (*it)->setType(unsure);
                    debug() << "Unsure: " << (*it)->qualifiedIdentifier();
                }
                return;
            }
            if (it == decs.constBegin())
                break;
        }
    }

    VariableDeclaration *dec = openDefinition<VariableDeclaration>(id, range);
    dec->setKind(Declaration::Instance);
    dec->setType(type);
    eventuallyAssignInternalContext();
    DeclarationBuilderBase::closeDeclaration();
}

void DeclarationBuilder::openMethodDeclaration(RubyAst* node)
{
    DUChainWriteLocker lock(DUChain::lock());
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = identifierForNode(new NameAst(node));
    FunctionDeclaration *decl = openDeclaration<FunctionDeclaration>(id, range);
    FunctionType::Ptr type = FunctionType::Ptr(new FunctionType());

    type->setReturnType(AbstractType::Ptr(new ObjectType));
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
        decl->setKind(KDevelop::Declaration::Type);
        decl->setClassType(ClassDeclarationData::Interface);
    }
    decl->clearBaseClasses();
    type->setDeclaration(decl);
    decl->setType(type);
    openType(type);
    openContextForClassDefinition(node);
    decl->setInternalContext(currentContext());
}

void DeclarationBuilder::appendProblem(Node *node, const QByteArray &msg)
{
    DUChainWriteLocker lock(DUChain::lock());
    KDevelop::Problem *p = new KDevelop::Problem();

    p->setFinalLocation(getDocumentRange(node));
    p->setSource(KDevelop::ProblemData::SemanticAnalysis);
    p->setDescription(i18n(msg));
    p->setSeverity(KDevelop::ProblemData::Error);
    topContext()->addProblem(ProblemPointer(p));
}

KDevelop::RangeInRevision DeclarationBuilder::getNameRange(RubyAst *node)
{
    return m_editor->findRange(getNameNode(node->tree));
}

DocumentRange DeclarationBuilder::getDocumentRange(Node *node)
{
    IndexedString ind(m_editor->url());
    SimpleRange range(node->startLine - 1, node->startCol,
                      node->endLine - 1, node->endCol - 1);
    return DocumentRange(ind, range);
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
