/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#include <parser/parser.h>


namespace Ruby
{

Parser::Parser()
{
    m_contents = nullptr;
    m_version = ruby21;
}

Parser::~Parser()
{
    /* There's nothing to do here! */
}

void Parser::setContents(const QByteArray &contents)
{
    m_contents = contents;
}

void Parser::setCurrentDocument(const KDevelop::IndexedString &fileName)
{
    m_currentDocument = fileName;
}

void Parser::setRubyVersion(enum ruby_version version)
{
    m_version = version;
}

const KDevelop::IndexedString & Parser::currentDocument() const
{
    return m_currentDocument;
}

Ast * Parser::parse()
{
    struct options_t opts;
    struct error_t *aux;
    opts.path = m_currentDocument.str().toUtf8();
    opts.contents = m_contents.data();
    opts.version = m_version;

    /* Let's call the parser ;) */
    struct ast_t *res = rb_compile_file(&opts);
    Ast *ra = new Ast(res->tree);
    if (res->unrecoverable) {
        for (aux = res->errors; aux; aux = aux->next) {
            appendProblem(aux);
        }
        rb_free(res);
        return nullptr;
    } else {
        m_problems.clear();
        for (aux = res->errors; aux; aux = aux->next) {
            appendProblem(aux);
        }
        free_errors(res);
        free(res);
    }
    return ra;
}

void Parser::freeAst(const Ast *ast)
{
    if (ast) {
        free_ast(ast->tree);
    }
}

void Parser::mapAstUse(Ast *node, const SimpleUse &use)
{
    Q_UNUSED(node);
    Q_UNUSED(use);
}

const QString Parser::symbol(const Node *node) const
{
    int len = node->pos.end_col - node->pos.start_col;
    return m_contents.mid(node->pos.offset - len, len);
}

void Parser::appendProblem(const struct error_t *error)
{
    int col = (error->column > 0) ? error->column - 1 : 0;
    KDevelop::ProblemPointer problem(new KDevelop::Problem);

    KTextEditor::Cursor cursor(error->line - 1, col);
    KTextEditor::Range range(cursor, cursor);
    KDevelop::DocumentRange location(m_currentDocument, range);
    problem->setFinalLocation(location);
    problem->setDescription(QString(error->msg));
    problem->setSource(KDevelop::ProblemData::Parser);
    if (error->warning) {
        problem->setSeverity(KDevelop::ProblemData::Error);
    } else {
        problem->setSeverity(KDevelop::ProblemData::Warning);
    }
    m_problems << problem;
}

}

