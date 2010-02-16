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
#include "simpleparsejob.h"

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

using namespace KDevelop;

namespace ruby
{

SimpleParseJob::SimpleParseJob( const KUrl &url, RubyLanguageSupport *parent )
        : KDevelop::ParseJob( url )
        , m_readFromDisk( false )
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

    kDebug() << "1";

    if ( abortRequested() )
        return abortJob();

    kDebug() << "2";

    KDevelop::UrlParseLock urlLock(document());

    kDebug() << "3";

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

    kDebug() << "4";

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
    QRegExp classre("^\\s*(class|module)\\s+([A-Z][A-Za-z0-9_]+::)*([A-Z][A-Za-z0-9_]+)\\s*(<\\s*([A-Z][A-Za-z0-9_:]+))?$");
    QRegExp methodre("^(\\s*)def\\s+(([A-Z][A-Za-z0-9_:]+|self)\\.)?([A-Za-z0-9_]+[!?=]?|\\[\\]=?|\\*\\*||\\-|[!~+*/%&|><^]|>>|<<||<=>|<=|>=|==|===|!=|=~|!~).*$");
    QRegExp accessre("^\\s*(private|protected|public)\\s*((:([A-Za-z0-9_]+[!?=]?|\\[\\]=?|\\*\\*||\\-|[!~+*/%&|><^]|>>|<<||<=>|<=|>=|==|===|!=|=~|!~),?\\s*)*)$");
    QRegExp attr_accessorre("^\\s*(attr_accessor|attr_reader|attr_writer)\\s*((:([A-Za-z0-9_]+),?\\s*)*)$");
    QRegExp symbolre(":([^,]+),?");
    QRegExp line_contre(",\\s*$");
    QRegExp slot_signalre("^\\s*(slots|signals|k_dcop|k_dcop_signals)\\s*(('[^)]+\\)',?\\s*)*)$");
    QRegExp memberre("'([A-Za-z0-9_ &*]+\\s)?([A-Za-z0-9_]+)\\([^)]*\\)',?");
    QRegExp begin_commentre("^*=begin");
    QRegExp end_commentre("^*=end");
    QRegExp variablere("(@@?[A-Za-z0-9_]+)\\s*=\\s*((?:([A-Za-z0-9_:.]+)\\.new)|[\\[\"'%:/\\?\\{]|%r|<<|true|false|^\\?|0[0-7]+|[-+]?0b[01]+|[-+]?0x[1-9a-fA-F]+|[-+]?[0-9_\\.e]+|nil)?");
    QRegExp endre("^(\\s*)end\\s*$");


    DUChainWriteLocker lock( DUChain::lock() );
    EditorIntegrator editor;
    editor.setCurrentUrl(document());

    if (TopDUContext * const topContext = DUChain::self()->chainForDocument(document()))
    {       
        DUChain::self()->removeDocumentChain(topContext);
    }
    TopDUContext * const topContext = new TopDUContext(document(), SimpleRange( editor.smart().currentDocument()->documentRange() ));

    QStringList lines = contents.split("\n");
    int i = 0;
    foreach (const QString &rawline, lines)
    {
        QString line = rawline.trimmed();

        if (classre.indexIn(line) != -1) {
            //create class declaration
//            Declaration * const decl = new Declaration(document(), SimpleRange(i, 0, i, rawline.length()),
//                Declaration::ClassScope, 0);
            Declaration * const decl = new Declaration(SimpleRange(i, 0, i, rawline.length()), topContext);

            decl->setDeclarationIsDefinition(true);
            decl->setKind(Declaration::Type);
            decl->setIdentifier(Identifier(classre.cap(3)));
//            decl->setContext(topContext);
        }

        i+=1;
    }
    DUChain::self()->addDocumentChain(topContext);
}

} // end of namespace ruby

#include "simpleparsejob.moc"
