/*****************************************************************************
 * Copyright (c) 2006 Alexander Dymo <adymo@kdevelop.org>                    *
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

#ifndef RUBY_PARSEJOB_H
#define RUBY_PARSEJOB_H

#include <kurl.h>
#include <kdevparsejob.h>

// from the parser subdirectory
#include <ruby_ast.h>
#include <ruby_codemodel.h>

class KDevelop::CodeModel;
class RubyLanguageSupport;

namespace ruby
{

class ParseSession;


class ParseJob : public KDevelop::ParseJob
{
    Q_OBJECT

public:
    ParseJob( const KUrl &url, RubyLanguageSupport* parent );
    ParseJob( KDevelop::Document* document, RubyLanguageSupport* parent );

    virtual ~ParseJob();

    RubyLanguageSupport* ruby() const;

    ParseSession* parseSession() const;

    bool wasReadFromDisk() const;

    virtual KDevelop::AST *AST() const;
    virtual KDevelop::CodeModel *codeModel() const;

protected:
    virtual void run();

private:
    ParseSession *m_session;
    program_ast *m_AST;
    CodeModel *m_model;
    bool m_readFromDisk;
};

} // end of namespace ruby

#endif

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
