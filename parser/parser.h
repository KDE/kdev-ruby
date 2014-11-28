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

#ifndef RUBY_PARSER_H
#define RUBY_PARSER_H

#include <language/duchain/problem.h>

#include <parser/ast.h>
#include <parser/export.h>

namespace ruby {

/**
 * @class Parser
 *
 * This class represents an interface to the "pure" parser and it may
 * be used across the plugin.
 */
class KDEVRUBYPARSER_EXPORT Parser
{
    /// Convenient alias that packs a DUContextPointer and a RangeInRevision.
    using SimpleUse = QPair<KDevelop::DUContextPointer,
                            KDevelop::RangeInRevision>;

public:
    Parser();
    Parser(const KDevelop::IndexedString &fileName, const QByteArray &contents);
    virtual ~Parser();

    /**
     * Set the contents of the document.
     *
     * @param contents the contents of the file to parse.
     */
    void setContents(const QByteArray &contents);

    /**
     * Set the version of the Ruby interpreter.
     */
    void setRubyVersion(enum ruby_version version);

    /**
     * This method parses the current document.
     *
     * @return the generated Ast.
     */
    Ast * parse();

    /**
     * Implemented to make the AbstractUseBuilder happy.
     */
    void mapAstUse(Ast *node, const SimpleUse &use);

    /**
     * @return a QString that represents the value of the node
     * (not the node's name).
     */
    const QString symbol(const Node *node) const;

private:
    /**
     * @internal called when there are errors in the current document and we
     * want to append one of them in a list of ProblemPointer's.
     *
     * @param error the error provided to this method.
     */
    void appendProblem(const struct error_t *error);

public:
    QVector<KDevelop::ProblemPointer> problems;
    KDevelop::IndexedString currentDocument;
    Ast *ast;

private:
    QByteArray m_contents;
    enum ruby_version m_version;
};

}

#endif // RUBY_PARSER_H

