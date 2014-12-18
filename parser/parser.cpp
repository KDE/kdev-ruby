/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <parser/parser.h>

using namespace KDevelop;

namespace ruby
{

Parser::Parser()
{
    m_contents = nullptr;
    m_version = ruby21;
    ast = nullptr;
}

Parser::Parser(const IndexedString &fileName, const QByteArray &contents)
{
    currentDocument = fileName;
    m_contents = contents;
    m_version = ruby21;
    ast = nullptr;
}

Parser::~Parser()
{
    if (ast) {
        free_ast(ast->tree);
        delete ast;
    }
}

void Parser::setContents(const QByteArray &contents)
{
    m_contents = contents;
}

void Parser::setRubyVersion(enum ruby_version version)
{
    m_version = version;
}

Ast * Parser::parse()
{
    struct options_t opts;
    struct error_t *aux;
    opts.path = currentDocument.str().toUtf8();
    opts.contents = m_contents.data();
    opts.version = m_version;

    // Let's call the parser ;)
    struct ast_t *res = rb_compile_file(&opts);
    ast = new Ast(res->tree);
    if (res->unrecoverable) {
        for (aux = res->errors; aux; aux = aux->next) {
            appendProblem(aux);
        }
        rb_free(res);
        return nullptr;
    } else {
        problems.clear();
        for (aux = res->errors; aux; aux = aux->next) {
            appendProblem(aux);
        }
        free_errors(res);
        free(res);
    }
    return ast;
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
    ProblemPointer problem(new KDevelop::Problem);

    KTextEditor::Cursor cursor(error->line - 1, col);
    KTextEditor::Range range(cursor, cursor);
    DocumentRange location(currentDocument, range);
    problem->setFinalLocation(location);
    problem->setDescription(QString(error->msg));
    problem->setSource(ProblemData::Parser);
    if (error->warning) {
        problem->setSeverity(ProblemData::Error);
    } else {
        problem->setSeverity(ProblemData::Warning);
    }
    problems << problem;
}

}

