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


#include <parser/rubyparser.h>


using namespace KDevelop;

namespace Ruby
{

RubyParser::RubyParser()
{
    m_contents = NULL;
    m_version = ruby20;
}

RubyParser::~RubyParser()
{
    /* There's nothing to do here! */
}

void RubyParser::setContents(const QByteArray &contents)
{
    m_contents = contents;
}

void RubyParser::setCurrentDocument(const KUrl &fileName)
{
    m_currentDocument = IndexedString(fileName);
}

void RubyParser::setRubyVersion(enum ruby_version version)
{
    m_version = version;
}

const IndexedString & RubyParser::currentDocument() const
{
    return m_currentDocument;
}

RubyAst * RubyParser::parse()
{
    struct options_t opts;
    struct error_t *aux;
    opts.path = m_currentDocument.str().toAscii();
    opts.contents = m_contents.data();
    opts.version = m_version;

    /* Let's call the parser ;) */
    struct ast_t *res = rb_compile_file(&opts);
    RubyAst *ra = new RubyAst(res->tree);
    if (res->errors) {
        for (aux = res->errors; aux; aux = aux->next)
            appendProblem(aux);
        rb_free(res);
        return NULL;
    } else {
        free_errors(res);
        free(res);
        m_problems.clear();
    }
    return ra;
}

void RubyParser::freeAst(RubyAst *ast)
{
    if (ast != NULL)
        free_ast(ast->tree);
}

QString RubyParser::symbol(Node *node) const
{
    int len = node->pos.end_col - node->pos.start_col;
    return m_contents.mid(node->pos.offset - len, len);
}

void RubyParser::appendProblem(struct error_t *error)
{
    int col = (error->column > 0) ? error->column - 1 : 0;
    ProblemPointer problem(new Problem);

    SimpleCursor cursor(error->line - 1, col);
    SimpleRange range(cursor, cursor);
    DocumentRange location(m_currentDocument, range);
    problem->setFinalLocation(location);
    problem->setDescription(QString(error->msg));
    problem->setSource(KDevelop::ProblemData::Parser);
    if (error->warning)
        problem->setSeverity(KDevelop::ProblemData::Error);
    else
        problem->setSeverity(KDevelop::ProblemData::Warning);
    m_problems << problem;
}

} // End of namespace: Ruby

