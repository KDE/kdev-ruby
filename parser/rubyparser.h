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

/*
 * TODO:
 *  - In appendProblems, we have to store ranges.
 */


#ifndef RUBYPARSER_H
#define RUBYPARSER_H


#include <language/interfaces/iproblem.h>
#include <parser/parserexport.h>
#include "node.h"


using namespace KDevelop;

namespace Ruby {

/**
 * @class RubyParser
 *
 * This class represents an interface to the "pure" parser and it may
 * be used across the plugin.
 */
class KDEVRUBYPARSER_EXPORT RubyParser
{
public:
    /**
     * Constructor.
     */
    RubyParser();

    /**
     * Destructor.
     */
    ~RubyParser();

    /**
     * Set the current document.
     *
     * @param fileName the name of the current document.
     */
    void setCurrentDocument(const KUrl & fileName);

    /**
     * @return the name of the current document.
     */
    const IndexedString & currentDocument() const;

    /**
     * This method parses the current document.
     *
     * @return the generated Ast.
     */
    RubyAst * parse();

    /**
     * This method frees the RubyAst if necessary.
     *
     * @param ast the RubyAst to free.
     */
    void freeAst(RubyAst * ast);

private:
    /**
     * @internal called when there are errors in the current
     * document and we want to append them in a list of
     * ProblemPointer's.
     *
     * @param errors the errors that the parser has provided.
     */
    void appendProblems(char ** errors);

public:
    QList<KDevelop::ProblemPointer> m_problems;

private:
    IndexedString m_currentDocument;
};


} // End of namespace: Ruby


#endif // RUBYPARSER_H

