/* This file is part of KDevelop
 *
 * Copyright (C) 2011  Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "rubyparser.h"


using namespace KDevelop;

namespace Ruby
{

RubyParser::RubyParser()
{
    m_contents = NULL;
}

RubyParser::~RubyParser()
{
    /* There's nothing to do here! */
}

void RubyParser::setContents(const QByteArray & contents)
{
    m_contents = contents.data();
}

void RubyParser::setCurrentDocument(const KUrl & fileName)
{
    m_currentDocument = IndexedString(fileName);
}

const IndexedString & RubyParser::currentDocument() const
{
    return m_currentDocument;
}

RubyAst * RubyParser::parse()
{
    /* Let's call the parser ;) */
    RubyAst * result = rb_compile_file(m_currentDocument.str().toAscii(),
                                       m_contents);
    if (result->errors[0].valid) {
        appendProblem(result->errors[0]);
        if (result->errors[1].valid)
            appendProblem(result->errors[1]);
        return NULL;
    } else
        m_problems.clear();
    return result;
}

void RubyParser::freeAst(RubyAst * ast)
{
    if (ast != NULL)
        rb_free(ast);
}

void RubyParser::appendProblem(struct error_t givenError)
{
    int col = (givenError.col > 0) ? givenError.col - 1 : 0;
    ProblemPointer problem(new Problem);

    SimpleCursor cursor(givenError.line - 1, col);
    SimpleRange range(cursor, cursor);
    DocumentRange location(m_currentDocument, range);
    problem->setFinalLocation(location);
    problem->setDescription(QString(givenError.msg));
    problem->setSource(KDevelop::ProblemData::Parser);
    problem->setSeverity(KDevelop::ProblemData::Error);
    m_problems << problem;
}

} // End of namespace: Ruby

