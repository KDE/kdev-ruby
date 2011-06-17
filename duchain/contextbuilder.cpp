/* This file is part of KDevelop
 *
 * Copyright 2010 Niko Sams <niko.sams@gmail.com>
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright (C) 2011 Miquel Sabaté <mikisabate@gmail.com>
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
#include "rubyducontext.h"


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

ReferencedTopDUContext ContextBuilder::build(const IndexedString &url, RubyAst *node,
                                                ReferencedTopDUContext updateContext)
{
	if (!updateContext) {
		DUChainReadLocker lock(DUChain::lock());
		updateContext = DUChain::self()->chainForDocument(url);
	}
	if (updateContext) {
		kDebug() << "Re-compiling" << url.str();
		DUChainWriteLocker lock(DUChain::lock());
		updateContext->clearImportedParentContexts();
		updateContext->parsingEnvironmentFile()->clearModificationRevisions();
		updateContext->clearProblems();
	} else
		kDebug() << "Compiling";
    return ContextBuilderBase::build(url, node, updateContext);
}

void ContextBuilder::setEditor(EditorIntegrator *editor)
{
    m_editor = editor;
}

DUContext * ContextBuilder::newContext(const RangeInRevision &range)
{
    return new RubyDUContext<DUContext>(range, currentContext());
}

KDevelop::TopDUContext* ContextBuilder::newTopContext(const KDevelop::RangeInRevision &range,
                                                      KDevelop::ParsingEnvironmentFile *file)
{
    KDevelop::IndexedString doc(m_editor->url());
    if (!file) {
        file = new KDevelop::ParsingEnvironmentFile(doc);
        file->setLanguage(KDevelop::IndexedString("Ruby"));
    }
    TopDUContext *top = new RubyDUContext<TopDUContext>(doc, range, file);
    top->setType(DUContext::Global);
    ReferencedTopDUContext ref(top); //TODO: Not sure :S
    m_topContext = ref;
    return top;
}

void ContextBuilder::startVisiting(RubyAst *node)
{
    /* TODO */
    Q_UNUSED(node) // NOTE: Avoid warnings by now, should be removed in the future
//     ProgramNode *ast = static_cast<ProgramNode*>(node);
//     visitProgram(ast);
}

void ContextBuilder::setContextOnNode(RubyAst *node, KDevelop::DUContext *ctx)
{
    node->context = ctx;
}

KDevelop::DUContext * ContextBuilder::contextFromNode(RubyAst *node)
{
    return node->context;
}

EditorIntegrator * ContextBuilder::editor() const
{
    return m_editor;
}

KDevelop::RangeInRevision ContextBuilder::editorFindRange(RubyAst *fromRange, RubyAst *toRange)
{
    return m_editor->findRange(fromRange->tree, toRange->tree);
}

KDevelop::CursorInRevision ContextBuilder::startPos(RubyAst *node)
{
    return m_editor->findPosition(node->tree, EditorIntegrator::FrontEdge);
}

KDevelop::QualifiedIdentifier ContextBuilder::identifierForNode(Node *id)
{
    if (!id)
        return KDevelop::QualifiedIdentifier();
    return KDevelop::QualifiedIdentifier(id->name);
}

}

