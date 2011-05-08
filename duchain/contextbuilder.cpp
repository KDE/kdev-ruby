/* This file is part of KDevelop
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


#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/icompletionsettings.h>
#include <duchain/contextbuilder.h>
#include <duchain/editorintegrator.h>


using namespace KDevelop;
namespace Ruby
{

ContextBuilder::ContextBuilder() : m_reportErrors(true)
{
    /* There's nothing to do here! */
}

ContextBuilder::~ContextBuilder()
{
    /* There's nothing to do here! */
}

ReferencedTopDUContext ContextBuilder::build(const IndexedString & url, Node * node,
                                                ReferencedTopDUContext updateContext)
{
    if ( KDevelop::ICore::self() ) {
        m_reportErrors = KDevelop::ICore::self()->languageController()->completionSettings()->highlightSemanticProblems();
    }
    return ContextBuilderBase::build(url, node, updateContext);
}

void ContextBuilder::setEditor(EditorIntegrator* editor)
{
    m_editor = editor;
}

void ContextBuilder::startVisiting(Node * node)
{
    /* TODO */
    Q_UNUSED(node) // NOTE: Avoid warnings by now, should be removed in the future
//     ProgramNode *ast = static_cast<ProgramNode*>(node);
//     visitProgram(ast);
}

KDevelop::TopDUContext* ContextBuilder::newTopContext(const KDevelop::RangeInRevision& range, KDevelop::ParsingEnvironmentFile* file)
{
    if (!file) {
        file = new KDevelop::ParsingEnvironmentFile(KDevelop::IndexedString(m_editor->url()));
        file->setLanguage(KDevelop::IndexedString("Ruby"));
    }
    return new KDevelop::TopDUContext(KDevelop::IndexedString(m_editor->url()), range, file);
}

void ContextBuilder::setContextOnNode(Node* /*node*/, KDevelop::DUContext* /*ctx*/)
{
    /* TODO */
}

KDevelop::DUContext* ContextBuilder::contextFromNode(Node* /*node*/)
{
    /* TODO */
    return 0;
}

EditorIntegrator* ContextBuilder::editor() const
{
    return m_editor;
}

KDevelop::RangeInRevision ContextBuilder::editorFindRange(Node* fromRange, Node* toRange)
{
    return m_editor->findRange(fromRange, toRange);
}

KDevelop::CursorInRevision ContextBuilder::startPos(Node * node)
{
    return m_editor->findPosition(node, EditorIntegrator::FrontEdge);
}

KDevelop::QualifiedIdentifier ContextBuilder::identifierForNode(Node * id)
{
    if (!id)
        return KDevelop::QualifiedIdentifier();
    return KDevelop::QualifiedIdentifier(id->name);
}

}

