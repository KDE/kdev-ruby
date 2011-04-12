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

/* TODO: Clean This mess */

#include "parsejob.h"

#include <cassert>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "Thread.h"

#include <QFile>
#include <QRegExp>
#include <QByteArray>
#include <QReadLocker>

#include <kdebug.h>
#include <klocale.h>

#include <ktexteditor/document.h>

#include <interfaces/ilanguage.h>

#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/declaration.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/parsingenvironment.h>
#include <language/duchain/persistentsymboltable.h>

#include <language/backgroundparser/urlparselock.h>

#include "rubylanguagesupport.h"
// #include "parser/parser.h"
#include <parser/rubyparser.h>
#include <parser/node.h>
#include "duchain/declarationbuilder.h"
#include "duchain/editorintegrator.h"

using namespace KDevelop;

namespace Ruby
{

ParseJob::ParseJob(const KUrl & url, RubyLanguageSupport * parent)
    : KDevelop::ParseJob(url)
    , m_parser (new RubyParser)
    , m_url (url)
    , m_readFromDisk(false)
{
    /* There's nothing to do here */
}

ParseJob::~ParseJob()
{
    /* There's nothing to do here */
}

RubyLanguageSupport * ParseJob::ruby() const
{
    return RubyLanguageSupport::self();
}

bool ParseJob::wasReadFromDisk() const
{
    return m_readFromDisk;
}

void ParseJob::run()
{
    //Happens during shutdown
    if (!ruby())
        return abortJob();

    if (abortRequested())
        return abortJob();

    KDevelop::UrlParseLock urlLock(document());
    {
        DUChainReadLocker lock(DUChain::lock());
        bool needsUpdate = true;
        static const IndexedString langString("Ruby");                                                                      
        foreach(const ParsingEnvironmentFilePointer & file, DUChain::self()->allEnvironmentFiles(document())) {
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

    KDevelop::ProblemPointer p = readContents();
    if (p)
        return abortJob();
    QString cont = contents().contents;

    if (abortRequested())
        return abortJob();

    m_parser->setCurrentDocument(m_url);
    m_parser->setContents(cont);
    parse();

    if ( abortRequested() )
        return abortJob();
}

void ParseJob::parse()
{
    RubyAst * ast = m_parser->parse();
    kDebug() << "C code has been executed!\n";

    if (ast != NULL) {
        /* Everything is fine */
    } else {
        /* Failed */
    }
//     KDevelop::ReferencedTopDUContext top;
//     {
//         KDevelop::DUChainReadLocker lock(KDevelop::DUChain::lock());
//         top = KDevelop::DUChain::self()->chainForDocument(document());
//     }
//     if (top) {
//         kDebug() << "re-compiling" << document().str();
//         KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
//         top->clearImportedParentContexts();
//         top->parsingEnvironmentFile()->clearModificationRevisions();
//         top->clearProblems();
//     } else
//         kDebug() << "compiling" << document().str();
// 
//     QReadLocker parseLock(ruby()->language()->parseLock());
// 
//     EditorIntegrator editor;
//     editor.setUrl(document());
//     DeclarationBuilder builder;
//     builder.setEditor(&editor);
//     top = builder.build(document(), programAST, top);
//     delete programAST;
// 
//     setDuChain(top);
// 
//     KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
// 
//     top->setFeatures(minimumFeatures());
//     KDevelop::ParsingEnvironmentFilePointer file = top->parsingEnvironmentFile();
//     
//     file->setModificationRevision(contents().modification);
//     KDevelop::DUChain::self()->updateContextEnvironment( top->topContext(), file.data() );

}

} // end of namespace ruby

#include "parsejob.moc"
