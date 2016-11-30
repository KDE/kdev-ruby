/* This file is part of KDevelop
 *
 * Copyright 2010 Niko Sams <niko.sams@gmail.com>
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright (C) 2011-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#include <duchain/builders/contextbuilder.h>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <language/backgroundparser/backgroundparser.h>

#include <duchain/debug.h>
#include <duchain/editorintegrator.h>
#include <duchain/helpers.h>
#include <duchain/loader.h>
#include <duchain/rubyducontext.h>

Q_LOGGING_CATEGORY(DUCHAIN, "kdevelop.languages.ruby.duchain")

using namespace KDevelop;
using namespace ruby;

ContextBuilder::ContextBuilder()
{
    m_mapAst = false;
}

ContextBuilder::~ContextBuilder()
{
}

ReferencedTopDUContext ContextBuilder::build(const IndexedString &url,
                                             Ast *node,
                                             ReferencedTopDUContext updateContext)
{
    if (!updateContext) {
        DUChainReadLocker lock;
        updateContext = DUChain::self()->chainForDocument(url);
    }
    if (updateContext) {
        rDebug() << "Re-compiling" << url.str();
        DUChainWriteLocker lock;
        updateContext->clearImportedParentContexts();
        updateContext->parsingEnvironmentFile()->clearModificationRevisions();
        updateContext->clearProblems();
        updateContext->updateImportsCache();
    } else {
        rDebug() << "Compiling";
    }

    auto top = ContextBuilderBase::build(url, node, updateContext);
    {
        DUChainWriteLocker lock(DUChain::lock());
        top->updateImportsCache();
    }
    return top;
}

void ContextBuilder::setEditor(EditorIntegrator *editor)
{
    m_editor = editor;
}

EditorIntegrator * ContextBuilder::editor() const
{
    return m_editor;
}

void ContextBuilder::setContextOnNode(Ast *node, KDevelop::DUContext *ctx)
{
    if (node->tree) {
        node->tree->context = ctx;
    }
    node->context = ctx;
}

KDevelop::DUContext * ContextBuilder::contextFromNode(Ast *node)
{
    if (node->tree) {
        DUContext *ctx = static_cast<DUContext *>(node->tree->context);
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

const KDevelop::CursorInRevision ContextBuilder::startPos(const Ast *node) const
{
    return m_editor->findPosition(node->tree, Edge::FrontEdge);
}

KDevelop::RangeInRevision ContextBuilder::editorFindRange(Ast *fromRange,
                                                          Ast *toRange)
{
    return m_editor->findRange(fromRange->tree, toRange->tree);
}

const DocumentRange ContextBuilder::getDocumentRange(const Node *node) const
{
    KTextEditor::Range range(node->pos.start_line - 1, node->pos.start_col,
                             node->pos.end_line - 1, node->pos.end_col);
    return DocumentRange(m_editor->url(), range);
}

const DocumentRange ContextBuilder::getDocumentRange(const RangeInRevision &range) const
{
    return DocumentRange(m_editor->url(), range.castToSimpleRange());
}

KDevelop::QualifiedIdentifier ContextBuilder::identifierForNode(NameAst *name)
{
    if (!name) {
        return QualifiedIdentifier();
    }
    return QualifiedIdentifier(name->value);
}

void ContextBuilder::startVisiting(Ast *node)
{
    const auto &builtins = builtinsFile();

    if (compilingContexts()) {
        TopDUContext *top = dynamic_cast<TopDUContext *>(currentContext());
        {
            // Mark that we will use a cached import-structure.
            DUChainWriteLocker lock;
            top->updateImportsCache();
        }

        Q_ASSERT(top);
        bool hasImports;
        {
            DUChainReadLocker rlock;
            hasImports = !top->importedParentContexts().isEmpty();
        }
        if (!hasImports && top->url() != builtins) {
            DUChainWriteLocker wlock;
            TopDUContext *import = DUChain::self()->chainForDocument(builtins);
            if (!import) {
                rDebug() << "importing the builtins file failed";
                Q_ASSERT(false);
            } else {
                top->addImportedParentContext(import);
                top->updateImportsCache();
            }
        }
    }
    AstVisitor::visitCode(node);
}

void ContextBuilder::visitModuleStatement(Ast *node)
{
    if (!node->foundProblems) {
        AstVisitor::visitModuleStatement(node);
    }
}

void ContextBuilder::visitClassStatement(Ast *node)
{
    if (!node->foundProblems) {
        AstVisitor::visitClassStatement(node);
    }
}

void ContextBuilder::visitMethodStatement(Ast *node)
{
    Node *aux = node->tree;
    NameAst name(node);
    DUContext *params = nullptr;

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
        DUChainWriteLocker wlock;
        if (params) {
            body->addImportedParentContext(params);
        }
        body->setInSymbolTable(false);
    }
    visitBody(node);
    closeContext();
    node->tree = aux;
}

void ContextBuilder::visitBlock(Ast *node)
{
    if (!node->tree) {
        return;
    }

    DUContext *block = openContext(node, DUContext::Other);
    if (compilingContexts()) {
        DUChainWriteLocker wlock;
        block->setInSymbolTable(false);
    }
    AstVisitor::visitBlock(node);
    closeContext();
}

void ContextBuilder::visitRequire(Ast *node, bool relative)
{
    AstVisitor::visitRequire(node);
    Node *aux = node->tree->r;

    /* If this is not a string, don't even care about it. */
    if (aux->kind != token_string) {
        return;
    }

    Path path = Loader::getRequiredFile(aux, m_editor, relative);
    if (!path.isValid()) {
        appendProblem(
            aux,
            i18n("LoadError: cannot load such file: %1", path.path()),
            IProblem::Warning
        );
        return;
    }
    require(path);
}

void ContextBuilder::require(const KDevelop::Path &path)
{
    DUChainWriteLocker lock;
    const IndexedString idx(path.path());
    ReferencedTopDUContext ctx = DUChain::self()->chainForDocument(idx);

    if (!ctx) {
        /*
         * Schedule the required file for parsing, and schedule the current one
         * for reparsing after that is done.
         */
        m_unresolvedImports.append(idx);
        auto parser = ICore::self()->languageController()->backgroundParser();
        if (parser->isQueued(idx)) {
            parser->removeDocument(idx);
        }
        parser->addDocument(idx, TopDUContext::ForceUpdate, m_priority - 1,
                            nullptr, ParseJob::FullSequentialProcessing);
    } else {
        currentContext()->addImportedParentContext(ctx);
    }
}

void ContextBuilder::appendProblem(const Node *node, const QString &msg,
                                   IProblem::Severity sev)
{
    ProblemPointer p(new Problem());
    p->setFinalLocation(getDocumentRange(node));
    p->setSource(IProblem::SemanticAnalysis);
    p->setDescription(msg);
    p->setSeverity(sev);

    {
        DUChainWriteLocker lock;
        topContext()->addProblem(p);
    }
}

void ContextBuilder::appendProblem(const RangeInRevision &range, const QString &msg,
                                   IProblem::Severity sev)
{
    ProblemPointer p(new Problem());
    p->setFinalLocation(getDocumentRange(range));
    p->setSource(IProblem::SemanticAnalysis);
    p->setDescription(msg);
    p->setSeverity(sev);

    {
        DUChainWriteLocker lock;
        topContext()->addProblem(p);
    }
}

const RangeInRevision ContextBuilder::rangeForMethodArguments(Ast *node)
{
    if (!node->tree) {
        return RangeInRevision();
    }

    Ast last(get_last_expr(node->tree), node->context);
    return editorFindRange(node, &last);
}

