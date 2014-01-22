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
    m_mapAst = false;
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

const KDevelop::CursorInRevision ContextBuilder::startPos(const RubyAst *node) const
{
    return m_editor->findPosition(node->tree, EditorIntegrator::FrontEdge);
}

KDevelop::RangeInRevision ContextBuilder::editorFindRange(RubyAst *fromRange, RubyAst *toRange)
{
    return m_editor->findRange(fromRange->tree, toRange->tree);
}

const DocumentRange ContextBuilder::getDocumentRange(const Node *node) const
{
    SimpleRange range(node->pos.start_line - 1, node->pos.start_col,
                      node->pos.end_line - 1, node->pos.end_col);
    return DocumentRange(m_editor->url(), range);
}

const DocumentRange ContextBuilder::getDocumentRange(const RangeInRevision &range) const
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
    IndexedString builtins = internalBuiltinsFile();

    if (compilingContexts()) {
        TopDUContext *top = dynamic_cast<TopDUContext *>(currentContext());
        Q_ASSERT(top);
        bool hasImports;
        {
            DUChainReadLocker rlock(DUChain::lock());
            hasImports = !top->importedParentContexts().isEmpty();
        }
        if (!hasImports && top->url() != builtins) {
            DUChainWriteLocker wlock(DUChain::lock());
            TopDUContext* import = DUChain::self()->chainForDocument(builtins);
            if (!import) {
                debug() << "importing the builtins file failed";
                Q_ASSERT(false);
            } else
                top->addImportedParentContext(import);
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
    DUContext *body = openContext(node, DUContext::Other, &name);
    if (compilingContexts()) {
        DUChainWriteLocker wlock(DUChain::lock());
        if (params)
            body->addImportedParentContext(params);
        body->setInSymbolTable(false);
    }
    visitBody(node);
    closeContext();
    node->tree = aux;
}

void ContextBuilder::visitBlock(RubyAst *node)
{
    if (!node->tree)
        return;

    DUContext *block = openContext(node, DUContext::Other);
    if (compilingContexts()) {
        DUChainWriteLocker wlock(DUChain::lock());
        block->setInSymbolTable(false);
    }
    RubyAstVisitor::visitBlock(node);
    closeContext();
}

void ContextBuilder::visitRequire(RubyAst *node, bool relative)
{
    RubyAstVisitor::visitRequire(node);
    Node *aux = node->tree->r;

    /* If this is not a string, don't even care about it. */
    if (aux->kind != token_string)
        return;

    KUrl path = Loader::getRequiredFile(aux, m_editor, relative);
    if (path.isEmpty()) {
        QString msg = i18n("LoadError: cannot load such file: %1", path.pathOrUrl());
        appendProblem(aux, msg, ProblemData::Warning);
        return;
    }

    const IndexedString indexedPath(path); // TODO: return IndexedString
    require(indexedPath);
}

void ContextBuilder::require(const IndexedString &path)
{
    DUChainWriteLocker lock;
    ReferencedTopDUContext ctx = DUChain::self()->chainForDocument(path);

    if (!ctx) {
        /*
         * Schedule the required file for parsing, and schedule the current one
         * for reparsing after that is done.
         */
        m_unresolvedImports.append(path);
        BackgroundParser *backgroundParser = KDevelop::ICore::self()->languageController()->backgroundParser();
        if (backgroundParser->isQueued(path))
            backgroundParser->removeDocument(path);
        backgroundParser->addDocument(path, TopDUContext::ForceUpdate,
            m_priority - 1, 0, ParseJob::FullSequentialProcessing);
        return;
    } else
        currentContext()->addImportedParentContext(ctx);
}

void ContextBuilder::appendProblem(const Node *node, const QString &msg,
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

const RangeInRevision ContextBuilder::rangeForMethodArguments(RubyAst *node)
{
    if (!node->tree)
        return RangeInRevision();

    RubyAst last(get_last_expr(node->tree), node->context);
    return editorFindRange(node, &last);
}

} // End of namespace Ruby
