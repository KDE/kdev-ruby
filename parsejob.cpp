/*****************************************************************************
 * Copyright (c) 2008 Alexander Dymo <adymo@kdevelop.org>                    *
 *                                                                           *
 * Permission is hereby granted, free of charge, to any person obtaining     *
 * a copy of this software and associated documentation files (the           *
 * "Software"), to deal in the Software without restriction, including       *
 * without limitation the rights to use, copy, modify, merge, publish,       *
 * distribute, sublicense, and/or sell copies of the Software, and to        *
 * permit persons to whom the Software is furnished to do so, subject to     *
 * the following conditions:                                                 *
 *                                                                           *
 * The above copyright notice and this permission notice shall be            *
 * included in all copies or substantial portions of the Software.           *
 *                                                                           *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,           *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF        *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                     *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE    *
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION    *
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION     *
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.           *
 *****************************************************************************/
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

#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>
#include <ktexteditor/document.h>

#include <interfaces/ilanguage.h>

#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/declaration.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/parsingenvironment.h>
#include <language/duchain/smartconverter.h>
#include <language/duchain/persistentsymboltable.h>

#include <language/editor/hashedstring.h>
#include <language/editor/editorintegrator.h>

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
        foreach(const ParsingEnvironmentFilePointer &file, DUChain::self()->allEnvironmentFiles(document())) {
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

    m_readFromDisk = !contentsAvailableFromEditor();

    QString contents;
    if ( m_readFromDisk ) {
        QFile file( document().str() );
        if ( !file.open( QIODevice::ReadOnly ) )
        {
            kDebug() << "Could not open file " << document().str()
                     << " (path " << document().str() << ")" << endl;
            return abortJob();
        }

        contents = file.readAll();
        file.close();
    } else {
        contents = contentsFromEditor();
    }

    kDebug() << "===-- PARSING --===> "
             << document().str()
             << " <== readFromDisk: " << m_readFromDisk
             << " size: " << contents.size()
             << endl;

    if ( abortRequested() )
        return abortJob();

    parse(contents);

    if ( abortRequested() )
        return abortJob();
}

void SimpleParseJob::parse(const QString &contents)
{
    ProgramAST *programAST = m_parser->parse(contents);

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
    DeclarationBuilder builder;
    builder.setEditor(&editor);
    top = builder.build(document(), programAST, top);
    delete programAST;

    setDuChain(top);

    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());

    top->setFeatures(minimumFeatures());
    KDevelop::ParsingEnvironmentFilePointer file = top->parsingEnvironmentFile();

    QFileInfo fileInfo(document().str());
    QDateTime lastModified = fileInfo.lastModified();
    if (m_readFromDisk) {
        file->setModificationRevision(KDevelop::ModificationRevision(lastModified));
    } else {
        file->setModificationRevision(KDevelop::ModificationRevision(lastModified, revisionToken()));
    }
    KDevelop::DUChain::self()->updateContextEnvironment( top->topContext(), file.data() );

}

} // end of namespace ruby

#include "parsejob.moc"
