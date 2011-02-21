/*
* This file is part of KDevelop
*
* Copyright 2008-2010 Alexander Dymo <adymo@kdevelop.org>
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
#include "parser/parser.h"
#include "duchain/declarationbuilder.h"
#include "duchain/editorintegrator.h"

using namespace KDevelop;

namespace Ruby
{

SimpleParseJob::SimpleParseJob( const KUrl &url, RubyLanguageSupport *parent )
        : KDevelop::ParseJob( url ), m_parser(new Parser), m_readFromDisk( false )
{}

SimpleParseJob::~SimpleParseJob()
{}

RubyLanguageSupport *SimpleParseJob::ruby() const
{
    return RubyLanguageSupport::self();
}

bool SimpleParseJob::wasReadFromDisk() const
{
    return m_readFromDisk;
}

void SimpleParseJob::run()
{
    kDebug() << "Trying to run ruby parse job";

    //Happens during shutdown
    if (!ruby())
        return abortJob();

    if ( abortRequested() )
        return abortJob();

    KDevelop::UrlParseLock urlLock(document());

    {
        DUChainReadLocker lock(DUChain::lock());
        bool needsUpdate = true;
        static const IndexedString langString("Ruby");                                                                      
        foreach(const ParsingEnvironmentFilePointer &file, DUChain::self()->allEnvironmentFiles(document())) {
            if (file->language() != langString)
                continue;
            if (file->needsUpdate()) {
                needsUpdate = true;
                break;
            } else {
                needsUpdate = false;
            }
        }
        if (!(minimumFeatures() & TopDUContext::ForceUpdate || minimumFeatures() & Resheduled) && !needsUpdate) {
            kDebug() << "Already up to date" << document().str();
            return;
        }
    }

    KDevelop::ProblemPointer p = readContents();
    if (p)
        return abortJob();
  
    QString c = contents().contents;

    kDebug() << "===-- PARSING --===> "
             << document().str()
             << " <== readFromDisk: " << m_readFromDisk
             << " size: " << c.size()
             << endl;

    if ( abortRequested() )
        return abortJob();

    parse(c);

    if ( abortRequested() )
        return abortJob();
}

void SimpleParseJob::parse(const QString &c)
{
    ProgramAST *programAST = m_parser->parse(c);

    KDevelop::ReferencedTopDUContext top;
    {
        KDevelop::DUChainReadLocker lock(KDevelop::DUChain::lock());
        top = KDevelop::DUChain::self()->chainForDocument(document());
    }
    if (top) {
        kDebug() << "re-compiling" << document().str();
        KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
        top->clearImportedParentContexts();
        top->parsingEnvironmentFile()->clearModificationRevisions();
        top->clearProblems();
    } else {
        kDebug() << "compiling" << document().str();
    }

    QReadLocker parseLock(ruby()->language()->parseLock());

    EditorIntegrator editor;
    editor.setUrl(document());
    DeclarationBuilder builder;
    builder.setEditor(&editor);
    top = builder.build(document(), programAST, top);
    delete programAST;

    setDuChain(top);

    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());

    top->setFeatures(minimumFeatures());
    KDevelop::ParsingEnvironmentFilePointer file = top->parsingEnvironmentFile();
    
    file->setModificationRevision(contents().modification);
    KDevelop::DUChain::self()->updateContextEnvironment( top->topContext(), file.data() );

}

} // end of namespace ruby

#include "parsejob.moc"
