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
#include <QByteArray>

#include <kdebug.h>
#include <klocale.h>

#include <ilanguage.h>

// from the parser subdirectory
#include <parsesession.h>
#include <ruby_parser.h>

#include "rubylanguagesupport.h"

namespace ruby
{

SimpleParseJob::SimpleParseJob( const KUrl &url, RubyLanguageSupport *parent )
        : KDevelop::ParseJob( url, parent )
        , m_readFromDisk( false )
{}

SimpleParseJob::~SimpleParseJob()
{}

RubyLanguageSupport *SimpleParseJob::ruby() const
{
    return static_cast<RubyLanguageSupport*>(const_cast<QObject*>(parent()));
}

bool SimpleParseJob::wasReadFromDisk() const
{
    return m_readFromDisk;
}

void SimpleParseJob::run()
{
    if ( abortRequested() )
        return abortJob();

    QMutexLocker lock(ruby()->language()->parseMutex(QThread::currentThread()));
    m_readFromDisk = !contentsAvailableFromEditor();

    QString contents;
    if ( m_readFromDisk )
    {
        QFile file( m_document.str() );
        if ( !file.open( QIODevice::ReadOnly ) )
        {
            m_errorMessage = i18n( "Could not open file '%1'", m_document.str() );
            kWarning( 9007 ) << "Could not open file " << m_document.str()
                             << " (path " << m_document.str() << ")" << endl;
            return ;
        }

        contents = file.readAll();
        file.close();
    }
    else
    {
        contents = contentsFromEditor().toAscii();
    }

    kDebug() << "===-- PARSING --===> "
             << m_document.str()
             << " <== readFromDisk: " << m_readFromDisk
             << " size: " << contents.size()
             << endl;

    if ( abortRequested() )
        return abortJob();

    //TODO: parse

    if ( abortRequested() )
        return abortJob();

    //TODO: bind declarations to the code model
}

} // end of namespace ruby

#include "simpleparsejob.moc"
