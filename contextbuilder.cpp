/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2010 Niko Sams <niko.sams@gmail.com>                        *
 *   Copyright 2010 Alexander Dymo <adymo@kdevelop.org>                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "contextbuilder.h"

#include <language/duchain/duchain.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/declaration.h>
#include <language/duchain/classdeclaration.h>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/icompletionsettings.h>

#include <klocalizedstring.h>

#include "rubyast.h"
#include "editorintegrator.h"

namespace ruby
{

ContextBuilder::ContextBuilder() : m_reportErrors(true)
{
}

ContextBuilder::~ContextBuilder()
{
}

KDevelop::ReferencedTopDUContext ContextBuilder::build(const KDevelop::IndexedString& url, AST* node,
    KDevelop::ReferencedTopDUContext updateContext, bool useSmart)
{
    if ( KDevelop::ICore::self() ) {
        m_reportErrors = KDevelop::ICore::self()->languageController()->completionSettings()->highlightSemanticProblems();
    }
    return ContextBuilderBase::build(url, node, updateContext, useSmart);
}

void ContextBuilder::setEditor(EditorIntegrator* editor)
{
    ContextBuilderBase::setEditor(editor, false);
}

void ContextBuilder::startVisiting(AST* node)
{
    ProgramAST *ast = static_cast<ProgramAST*>(node);
    visitProgram(ast);
}

void ContextBuilder::visitProgram(ProgramAST* ast)
{
    foreach (ClassAST *klass, ast->classes) {
        visitClass(klass);
    }
}

void ContextBuilder::visitClass(ClassAST* ast)
{
    openContext(ast, editorFindRange(ast, ast), KDevelop::DUContext::Class, ast->name);
    closeContext();
}

KDevelop::TopDUContext* ContextBuilder::newTopContext(const KDevelop::SimpleRange& range, KDevelop::ParsingEnvironmentFile* file)
{
    if (!file) {
        file = new KDevelop::ParsingEnvironmentFile(editor()->currentUrl());
        file->setLanguage(KDevelop::IndexedString("Ruby"));
    }
    return new KDevelop::TopDUContext(editor()->currentUrl(), range, file);
}

void ContextBuilder::setContextOnNode(AST* /*node*/, KDevelop::DUContext* /*ctx*/)
{
}

KDevelop::DUContext* ContextBuilder::contextFromNode(AST* /*node*/)
{
    return 0;
}

EditorIntegrator* ContextBuilder::editor() const
{
    return static_cast<EditorIntegrator*>(ContextBuilderBase::editor());
}

KTextEditor::Range ContextBuilder::editorFindRange(AST* fromRange, AST* toRange)
{
    return editor()->findRange(fromRange, toRange).textRange();
}

KDevelop::SimpleCursor ContextBuilder::startPos(AST* node)
{
    return editor()->findPosition(node, KDevelop::EditorIntegrator::FrontEdge);
}

KDevelop::QualifiedIdentifier ContextBuilder::identifierForNode(NameAST* id)
{
    if (!id)
        return KDevelop::QualifiedIdentifier();
    return KDevelop::QualifiedIdentifier(id->name);
}

}
