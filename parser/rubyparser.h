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


#ifndef RUBYPARSER_H
#define RUBYPARSER_H

#include <QString>
#include <KUrl>

#include <language/interfaces/iproblem.h>
#include <parser/parserexport.h>

#include "node.h"
#include "parser.h"


using namespace KDevelop;

namespace Ruby {

class KDEVRUBYPARSER_EXPORT RubyParser
{
public:
    RubyParser();
    ~RubyParser();

    void setCurrentDocument(KUrl & fileName);
    IndexedString currentDocument();

    RubyAst * parse();
    QList<KDevelop::ProblemPointer> m_problems;

private:
    void appendProblems(char ** errors);

private:
    QString m_contents;
    IndexedString m_currentDocument;
};


} // End of namespace: Ruby

#endif // RUBYPARSER_H
