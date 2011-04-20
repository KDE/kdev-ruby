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
    /* There's nothing to do here! */
}

RubyParser::~RubyParser()
{
    /* There's nothing to do here! */
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
    RubyAst * result = rb_compile_file(m_currentDocument.c_str());

    if (result->valid_error) {
        appendProblems(result->errors);
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

void RubyParser::appendProblems(char ** errors)
{
    char ** ptr;

    for (ptr = errors; *ptr != NULL; ptr++) {
        ProblemPointer problem(new Problem);
        problem->setDescription(QString(strdup(*ptr)));
        problem->setSource(KDevelop::ProblemData::Parser);
        m_problems << problem;
    }
}

} // End of namespace: Ruby

