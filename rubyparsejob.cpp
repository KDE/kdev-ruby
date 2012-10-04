/* This file is part of KDevelop
 *
 * Copyright 2008-2010 Alexander Dymo <adymo@kdevelop.org>
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


// Qt + KDE
#include <QReadLocker>
#include <KDebug>

// KDevelop
#include <interfaces/ilanguage.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/icore.h>
#include <language/backgroundparser/backgroundparser.h>
#include <language/interfaces/icodehighlighting.h>
#include <language/backgroundparser/urlparselock.h>
#include <language/duchain/duchainutils.h>

// Ruby
#include <rubydefs.h>
#include <rubyparsejob.h>
#include <rubylanguagesupport.h>
#include <parser/rubyparser.h>
#include <duchain/builders/declarationbuilder.h>
#include <duchain/builders/usebuilder.h>
#include <duchain/editorintegrator.h>
#include <duchain/helpers.h>


using namespace KDevelop;

namespace Ruby
{

ParseJob::ParseJob(const KUrl &url)
    : KDevelop::ParseJob(url)
    , m_parser (new RubyParser)
    , m_duContext (NULL)
{
    m_url = url;
}

ParseJob::~ParseJob()
{
    delete m_parser;
}

LanguageSupport * ParseJob::ruby() const
{
    return LanguageSupport::self();
}

inline bool ParseJob::canHighlight() const
{
    return ruby() && ruby()->codeHighlighting() &&
        ICore::self()->languageController()->backgroundParser()->trackerForUrl(document());
}

void ParseJob::run()
{
    if (!ruby() || abortRequested())
        return abortJob();

    /* Make sure that the builtins file is already loaded */
    if (!ruby()->builtinsLoaded() && document() != internalBuiltinsFile()) {
        debug() << "waiting for builtins file to finish parsing";
        QReadLocker(ruby()->builtinsLock());
    }

    KDevelop::UrlParseLock urlLock(document());
    if (!(minimumFeatures() & TopDUContext::ForceUpdate || minimumFeatures() & Rescheduled)) {
        DUChainReadLocker lock(DUChain::lock());
        static const IndexedString langString("Ruby");                                                                      
        foreach(const ParsingEnvironmentFilePointer &file, 
                DUChain::self()->allEnvironmentFiles(document())) {
            if (file->language() != langString)
                continue;
            if (!file->needsUpdate() && file->featuresSatisfied(minimumFeatures())) {
                debug() << "Already up to date" << document().str();
                setDuChain(file->topContext());
                if (canHighlight()) {
                    lock.unlock();
                    ruby()->codeHighlighting()->highlightDUChain(duChain());
                }
                return;
            }
            break;
        }
    }

    QReadLocker parseLock(ruby()->language()->parseLock());
    KDevelop::ProblemPointer p = readContents();
    if (p || abortRequested())
        return abortJob();

    /*
     * NOTE: Although the parser can retrieve the contents on its own,
     * it's better to use contents().contents because this way the contents
     * are converted in utf8 format always.
     */
    m_parser->setContents(contents().contents);
    m_parser->setCurrentDocument(m_url);
    RubyAst * ast = m_parser->parse();

    /* Setting up the TopDUContext features */
    KDevelop::ReferencedTopDUContext toUpdate;
    {
        KDevelop::DUChainReadLocker duchainlock(KDevelop::DUChain::lock());
        toUpdate = KDevelop::DUChainUtils::standardContextForUrl(document().toUrl());
    }

    KDevelop::TopDUContext::Features newFeatures = minimumFeatures();
    if (toUpdate)
        newFeatures = (KDevelop::TopDUContext::Features)(newFeatures | toUpdate->features());

    /* Remove update-flags like 'Recursive' or 'ForceUpdate' */
    newFeatures = static_cast<KDevelop::TopDUContext::Features>(newFeatures & KDevelop::TopDUContext::AllDeclarationsContextsUsesAndAST);

    /*
     * And finally we do all the work if parsing was successful. Otherwise,
     * we have to add a new problem
     */
    if (ast) {
        // Empty document, do nothing
        if (!ast->tree)
            return;

        if (abortRequested())
            return abortJob();

        EditorIntegrator editor;
        editor.setParseSession(m_parser);
        DeclarationBuilder builder(&editor);
        builder.setPriority(parsePriority());
        m_duContext = builder.build(editor.url(), ast, toUpdate);
        setDuChain(m_duContext);

        if (abortRequested())
            return abortJob();

        if (newFeatures & TopDUContext::AllDeclarationsContextsAndUses
                && document() != internalBuiltinsFile())
        {
            UseBuilder useBuilder(&editor);
            useBuilder.buildUses(ast);
        }

        if (abortRequested())
            return abortJob();

        const QList<KUrl> unresolvedImports = builder.unresolvedImports();
        if (!unresolvedImports.isEmpty()) {
            // TODO: review this ! Right now this is shamelessly taken from the Python plugin.

            // check whether one of the imports is queued for parsing, this is to avoid deadlocks
            bool dependencyInQueue = false;
            foreach (const KUrl &url, unresolvedImports) {
                dependencyInQueue = KDevelop::ICore::self()->languageController()->backgroundParser()->isQueued(url);
                if ( dependencyInQueue ) {
                    break;
                }
            }
            // we check whether this document already has been re-scheduled once and abort if that is the case
            // this prevents infinite loops in case something goes wrong (optimally, shouldn't reach here if
            // the document was already rescheduled, but there's many cases where this might still happen)
            if ( ! ( minimumFeatures() & Rescheduled ) && dependencyInQueue ) {
                DUChainWriteLocker lock(DUChain::lock());
                KDevelop::ICore::self()->languageController()->backgroundParser()->addDocument(document().toUrl(),
                                     static_cast<TopDUContext::Features>(TopDUContext::ForceUpdate | Rescheduled), parsePriority(),
                                     0, ParseJob::FullSequentialProcessing);
            }
        }

        if (abortRequested())
            return abortJob();

        {
            DUChainWriteLocker lock(DUChain::lock());
            m_duContext->setFeatures(newFeatures);
            KDevelop::ParsingEnvironmentFilePointer file = m_duContext->parsingEnvironmentFile();
            file->setModificationRevision(contents().modification);
            KDevelop::DUChain::self()->updateContextEnvironment(m_duContext, file.data());
        }
        m_parser->freeAst(ast);

        if (canHighlight())
            ruby()->codeHighlighting()->highlightDUChain(m_duContext);
        debug() << "**** Parsing Succeeded ****";
    } else {
        kWarning() << "**** Parsing Failed ****";
        DUChainWriteLocker lock(DUChain::lock());
        m_duContext = DUChain::self()->chainForDocument(document());
        if (m_duContext) {
            m_duContext->parsingEnvironmentFile()->clearModificationRevisions();
            m_duContext->clearProblems();
        } else {
            ParsingEnvironmentFile *file = new ParsingEnvironmentFile(document());
            static const IndexedString langString("Ruby");
            file->setLanguage(langString);
            m_duContext = new TopDUContext(document(), RangeInRevision(0, 0, INT_MAX, INT_MAX), file);
            DUChain::self()->addDocumentChain(m_duContext);
        }

        foreach (ProblemPointer p, m_parser->m_problems) {
            debug() << "Added problem to context";
            m_duContext->addProblem(p);
        }
        setDuChain(m_duContext);
    }
}

} // End of namespace ruby


#include "rubyparsejob.moc"

