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


#include <QReadLocker>
#include <KDebug>

#include <interfaces/ilanguage.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/icore.h>
#include <language/backgroundparser/backgroundparser.h>
#include <language/interfaces/icodehighlighting.h>
#include <language/backgroundparser/urlparselock.h>

#include <rubyparsejob.h>
#include <rubylanguagesupport.h>
#include <parser/rubyparser.h>
#include <duchain/declarationbuilder.h>
#include <duchain/usebuilder.h>
#include <duchain/editorintegrator.h>


using namespace KDevelop;

namespace Ruby
{

ParseJob::ParseJob(const KUrl & url, LanguageSupport * parent)
    : KDevelop::ParseJob(url)
    , m_parser (new RubyParser)
    , m_duContext (NULL)
{
    m_parent = parent;
    m_url = url;
}

ParseJob::~ParseJob()
{
    /* There's nothing to do here */
}

LanguageSupport * ParseJob::ruby() const
{
    return LanguageSupport::self();
}

void ParseJob::run()
{
    if (!ruby() || abortRequested())
        return abortJob();

    KDevelop::UrlParseLock urlLock(document());
    {
        DUChainReadLocker lock(DUChain::lock());
        bool needsUpdate = true;
        static const IndexedString langString("Ruby");                                                                      
        foreach(const ParsingEnvironmentFilePointer &file, 
                DUChain::self()->allEnvironmentFiles(document())) {
            if (file->language() != langString)
                continue;
            if (file->needsUpdate()) {
                needsUpdate = true;
                break;
            } else
                needsUpdate = false;
        }
        if (!(minimumFeatures() & TopDUContext::ForceUpdate || minimumFeatures() & Resheduled) && !needsUpdate) {
            kDebug() << "Already up to date" << document().str();
            return;
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

    if (ast != NULL) {
        if (abortRequested())
            return abortJob();

        EditorIntegrator editor;
        editor.setUrl(IndexedString(m_url));
        DeclarationBuilder builder(&editor);
        m_duContext = builder.build(document(), ast, m_duContext);
        bool needsReparse = builder.hasUnresolvedImports();
        setDuChain(m_duContext);
        if (abortRequested())
            return abortJob();

        UseBuilder useBuilder(&editor);
        useBuilder.buildUses(ast);

        if (abortRequested())
            return abortJob();

        if (needsReparse) {
            //TODO
        }

        {
            DUChainWriteLocker lock(DUChain::lock());
            m_duContext->setFeatures(minimumFeatures());
            KDevelop::ParsingEnvironmentFilePointer file = m_duContext->parsingEnvironmentFile();
            file->setModificationRevision(contents().modification);
            KDevelop::DUChain::self()->updateContextEnvironment(m_duContext, file.data());
        }
        m_parser->freeAst(ast);

        if (m_parent && m_parent->codeHighlighting() &&
            ICore::self()->languageController()->backgroundParser()->trackerForUrl(document())) {
            ruby()->codeHighlighting()->highlightDUChain(m_duContext);
        }
        kDebug() << "**** Parsing Succeeded ****";
    } else {
        kWarning() << "**** Parsing Failed ****";
        DUChainWriteLocker lock;
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
        setDuChain(m_duContext);
    }
    DUChainWriteLocker lock(DUChain::lock());
    foreach (ProblemPointer p, m_parser->m_problems) {
        kDebug() << "Added problem to context";
        m_duContext->addProblem(p);
    }
    setDuChain(m_duContext);
}

} // End of namespace ruby


#include "rubyparsejob.moc"

