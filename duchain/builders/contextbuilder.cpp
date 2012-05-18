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
#include <language/backgroundparser/backgroundparser.h>
#include <duchain/builders/contextbuilder.h>
#include <duchain/editorintegrator.h>
#include <duchain/rubyducontext.h>
#include <duchain/helpers.h>
#include <KStandardDirs>
#include <rubydefs.h>


using namespace KDevelop;
namespace Ruby
{

ContextBuilder::ContextBuilder() 
    : m_reportErrors(true)
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

DUContext * ContextBuilder::newContext(const RangeInRevision &range)
{
    return new RubyNormalDUContext(range, currentContext());
}

KDevelop::TopDUContext* ContextBuilder::newTopContext(const KDevelop::RangeInRevision &range,
                                                      KDevelop::ParsingEnvironmentFile *file)
{
    KDevelop::IndexedString doc(m_editor->url());
    if (!file) {
        file = new KDevelop::ParsingEnvironmentFile(doc);
        file->setLanguage(KDevelop::IndexedString("Ruby"));
    }
    TopDUContext *top = new RubyTopDUContext(doc, range, file);
    top->setType(DUContext::Global);
    m_topContext = ReferencedTopDUContext(top);
    return top;
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
        }
    }
    RubyAstVisitor::visitCode(node);
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

KDevelop::QualifiedIdentifier ContextBuilder::identifierForNode(NameAst *name)
{
    if (!name)
        return KDevelop::QualifiedIdentifier();
    return KDevelop::QualifiedIdentifier(name->value);
}

void ContextBuilder::visitModuleStatement(RubyAst *node)
{
    node->tree = node->tree->l;
    visitBody(node);
}

void ContextBuilder::visitClassStatement(RubyAst *node)
{
    node->tree = node->tree->l;
    visitBody(node);
}

void ContextBuilder::visitMethodStatement(RubyAst *node)
{
    DUChainWriteLocker lock(DUChain::lock());
    QualifiedIdentifier name = getIdentifier(node);
    Node *aux = node->tree;
    node->tree = node->tree->r;
    RangeInRevision rg = rangeForMethodArguments(node);

    /* Check the parameters */
    DUContext *params = openContext(node, rg, DUContext::Function, name);
    RubyAstVisitor::visitMethodArguments(node);
    closeContext();

    /* And now take care of the method body */
    node->tree = aux->l;
    if (node->tree && is_valid(node->tree)) {
        RangeInRevision range = editorFindRange(node, node);
        DUContext *body = openContext(node, range, DUContext::Other, name);
        if (compilingContexts()) {
            body->addImportedParentContext(params);
            body->setInSymbolTable(false);
        }
        RubyAstVisitor::visitBody(node);
        closeContext();
    }
}

void ContextBuilder::visitRequire(RubyAst *node)
{
    RubyAstVisitor::visitRequire(node);
    require(node->tree->r, false);
}

void ContextBuilder::visitRequireRelative(RubyAst *node)
{
    RubyAstVisitor::visitRequireRelative(node);
    require(node->tree->r, true);
}

void ContextBuilder::openContextForClassDefinition(RubyAst *node)
{
    DUChainWriteLocker wlock(DUChain::lock());
    RangeInRevision range = editorFindRange(node, node);
    KDevelop::QualifiedIdentifier className(getName(node));

    openContext(node, range, DUContext::Class, className);
    currentContext()->setLocalScopeIdentifier(className);
    wlock.unlock();
    addImportedContexts();
}

DocumentRange ContextBuilder::getDocumentRange(Node *node)
{
    IndexedString ind(m_editor->url());
    SimpleRange range(node->startLine - 1, node->startCol,
                      node->endLine - 1, node->endCol);
    return DocumentRange(ind, range);
}

const QualifiedIdentifier ContextBuilder::getIdentifier(const RubyAst *ast)
{
    NameAst nameAst(ast);
    QualifiedIdentifier name = identifierForNode(&nameAst);
    return name;
}

RangeInRevision ContextBuilder::rangeForMethodArguments(RubyAst *node)
{
    if (!node->tree)
        return RangeInRevision();

    RubyAst *last = new RubyAst(node->tree->last, node->context);
    if (!node->tree->last)
        last->tree = node->tree;
    RangeInRevision range = editorFindRange(node, last);
    delete last;

    return range;
}

void ContextBuilder::addImportedContexts()
{
    if (compilingContexts() && !m_importedParentContexts.isEmpty()) {
        DUChainWriteLocker wlock(DUChain::lock());
        foreach (KDevelop::DUContext *imported, m_importedParentContexts)
            currentContext()->addImportedParentContext(imported);
        m_importedParentContexts.clear();
    }
}

void ContextBuilder::require(Node *node, bool local)
{
    KUrl path = getRequiredFile(node, m_editor, local);
    if (path.isEmpty()) {
        KDevelop::Problem *p = new KDevelop::Problem();
        p->setFinalLocation(getDocumentRange(node));
        p->setSource(KDevelop::ProblemData::SemanticAnalysis);
        p->setDescription("LoadError: cannot load such file");
        p->setSeverity(KDevelop::ProblemData::Warning);
        {
            DUChainWriteLocker wlock(DUChain::lock());
            topContext()->addProblem(ProblemPointer(p));
        }
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
        if (KDevelop::ICore::self()->languageController()->backgroundParser()->isQueued(path)) {
            KDevelop::ICore::self()->languageController()->backgroundParser()->removeDocument(path);
        }
        KDevelop::ICore::self()->languageController()->backgroundParser()
                                    ->addDocument(path, TopDUContext::ForceUpdate, m_priority - 1,
                                                    0, ParseJob::FullSequentialProcessing);
        return;
    } else {
        lock.lock();
        currentContext()->addImportedParentContext(ctx);
    }
}

}

