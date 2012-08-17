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


// KDE
#include <KLocale>

// KDevelop
#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <language/backgroundparser/backgroundparser.h>

// Ruby
#include <rubydefs.h>
#include <duchain/helpers.h>
#include <duchain/loader.h>
#include <duchain/rubyducontext.h>
#include <duchain/editorintegrator.h>
#include <duchain/builders/contextbuilder.h>


using namespace KDevelop;
namespace Ruby
{

ContextBuilder::ContextBuilder()
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
        debug() << "Re-compiling" << url.str();
        DUChainWriteLocker lock(DUChain::lock());
        updateContext->clearImportedParentContexts();
        updateContext->parsingEnvironmentFile()->clearModificationRevisions();
        updateContext->clearProblems();
    } else
        debug() << "Compiling";
    return ContextBuilderBase::build(url, node, updateContext);
}

void ContextBuilder::setEditor(EditorIntegrator *editor)
{
    m_editor = editor;
}

EditorIntegrator * ContextBuilder::editor() const
{
    return m_editor;
}

void ContextBuilder::setContextOnNode(RubyAst *node, KDevelop::DUContext *ctx)
{
    if (node->tree)
        node->tree->context = ctx;
    node->context = ctx;
}

KDevelop::DUContext * ContextBuilder::contextFromNode(RubyAst *node)
{
    if (node->tree) {
        DUContext *ctx = (DUContext *) node->tree->context;
        return ctx;
    }
    return node->context;
}

DUContext * ContextBuilder::newContext(const RangeInRevision &range)
{
    return new RubyNormalDUContext(range, currentContext());
}

KDevelop::TopDUContext * ContextBuilder::newTopContext(const RangeInRevision &range,
                                                       ParsingEnvironmentFile *file)
{
    KDevelop::IndexedString doc(m_editor->url());
    if (!file) {
        file = new KDevelop::ParsingEnvironmentFile(doc);
        file->setLanguage(KDevelop::IndexedString("Ruby"));
    }
    TopDUContext *top = new RubyDUContext<TopDUContext>(doc, range, file);
    top->setType(DUContext::Global);
    return top;
}

KDevelop::CursorInRevision ContextBuilder::startPos(RubyAst *node) const
{
    return m_editor->findPosition(node->tree, EditorIntegrator::FrontEdge);
}

KDevelop::RangeInRevision ContextBuilder::editorFindRange(RubyAst *fromRange, RubyAst *toRange)
{
    return m_editor->findRange(fromRange->tree, toRange->tree);
}

DocumentRange ContextBuilder::getDocumentRange(Node *node) const
{
    SimpleRange range(node->startLine - 1, node->startCol,
                      node->endLine - 1, node->endCol);
    return DocumentRange(m_editor->url(), range);
}

DocumentRange ContextBuilder::getDocumentRange(const RangeInRevision &range) const
{
    return DocumentRange(m_editor->url(), range.castToSimpleRange());
}

KDevelop::QualifiedIdentifier ContextBuilder::identifierForNode(NameAst *name)
{
    if (!name)
        return KDevelop::QualifiedIdentifier();
    return KDevelop::QualifiedIdentifier(name->value);
}

void ContextBuilder::startVisiting(RubyAst *node)
{
    IndexedString doc_url = internalBuiltinsFile();

    if (compilingContexts() && m_editor->url() != doc_url) {
        TopDUContext *internal;
        {
            DUChainReadLocker rlock(DUChain::lock());
            internal = DUChain::self()->chainForDocument(doc_url);
        }
        if (!internal) {
            m_unresolvedImports.append(doc_url.toUrl());
            DUChain::self()->updateContextForUrl(doc_url, TopDUContext::AllDeclarationsContextsAndUses);
        } else {
            debug() << "Adding kernel context";
            DUChainWriteLocker wlock(DUChain::lock());
            currentContext()->addImportedParentContext(internal);
            m_builtinsContext = KDevelop::TopDUContextPointer(internal);

            // include Kernel
            Declaration *kernel = currentContext()->findDeclarations(QualifiedIdentifier("Kernel")).first();
            currentContext()->addImportedParentContext(kernel->internalContext());
        }
    }
    RubyAstVisitor::visitCode(node);
}

void ContextBuilder::visitModuleStatement(RubyAst *node)
{
    if (!node->foundProblems)
        RubyAstVisitor::visitModuleStatement(node);
}

void ContextBuilder::visitClassStatement(RubyAst *node)
{
    if (!node->foundProblems)
        RubyAstVisitor::visitClassStatement(node);
}

void ContextBuilder::visitMethodStatement(RubyAst *node)
{
    Node *aux = node->tree;
    NameAst name(node);
    DUContext *params = NULL;

    node->tree = aux->r;
    if (node->tree) {
      RangeInRevision range = rangeForMethodArguments(node);
      params = openContext(node, range, DUContext::Function, &name);
      visitMethodArguments(node);
      closeContext();
    }

    node->tree = aux->l;
    if (node->tree && is_valid(node->tree)) {
        DUContext *body = openContext(node, DUContext::Other, &name);
        if (compilingContexts()) {
            DUChainWriteLocker wlock(DUChain::lock());
            if (params)
              body->addImportedParentContext(params);
            body->setInSymbolTable(false);
        }
        visitBody(node);
        closeContext();
    }
    node->tree = aux;
}

void ContextBuilder::visitRequire(RubyAst *node, bool relative)
{
    RubyAstVisitor::visitRequire(node);
    require(node->tree->r, relative);
}

void ContextBuilder::appendProblem(Node *node, const QString &msg,
                                   ProblemData::Severity sev)
{
    KDevelop::Problem *p = new KDevelop::Problem();
    p->setFinalLocation(getDocumentRange(node));
    p->setSource(KDevelop::ProblemData::SemanticAnalysis);
    p->setDescription(msg);
    p->setSeverity(sev);
    {
        DUChainWriteLocker lock(DUChain::lock());
        topContext()->addProblem(ProblemPointer(p));
    }
}

void ContextBuilder::appendProblem(const RangeInRevision &range, const QString &msg,
                                   ProblemData::Severity sev)
{
    KDevelop::Problem *p = new KDevelop::Problem();
    p->setFinalLocation(getDocumentRange(range));
    p->setSource(KDevelop::ProblemData::SemanticAnalysis);
    p->setDescription(msg);
    p->setSeverity(sev);
    {
        DUChainWriteLocker lock(DUChain::lock());
        topContext()->addProblem(ProblemPointer(p));
    }
}

RangeInRevision ContextBuilder::rangeForMethodArguments(RubyAst *node)
{
    if (!node->tree)
        return RangeInRevision();

    RubyAst last(get_last_expr(node->tree), node->context);
    return editorFindRange(node, &last);
}

void ContextBuilder::require(Node *node, bool local)
{
    KUrl path = Loader::getRequiredFile(node, m_editor, local);
    if (path.isEmpty()) {
        QString msg = i18n("LoadError: cannot load such file");
        appendProblem(node, msg, ProblemData::Warning);
        return;
    }

    DUChainWriteLocker lock(DUChain::lock());
    ReferencedTopDUContext ctx = DUChain::self()->chainForDocument(IndexedString(path));
    lock.unlock();

    if (!ctx) {
        /*
         * Schedule the required file for parsing, and schedule the current one
         * for reparsing after that is done.
         */
        m_unresolvedImports.append(path);
        if (KDevelop::ICore::self()->languageController()->backgroundParser()->isQueued(path))
            KDevelop::ICore::self()->languageController()->backgroundParser()->removeDocument(path);
        KDevelop::ICore::self()->languageController()->backgroundParser()
                                    ->addDocument(path, TopDUContext::ForceUpdate, m_priority - 1,
                                                    0, ParseJob::FullSequentialProcessing);
        return;
    } else {
        lock.lock();
        currentContext()->addImportedParentContext(ctx);
    }
}

} // End of namespace Ruby
