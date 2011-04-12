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
    /* There's nothing to do here */
}

RubyParser::~RubyParser()
{
    /* There's nothing to do here */
}

void RubyParser::setContents (const QString & contents)
{
    m_contents = contents;
}

QString RubyParser::contents() const
{
    return m_contents;
}

void RubyParser::setCurrentDocument (KUrl & fileName)
{
    m_currentDocument = IndexedString(fileName);
}

IndexedString RubyParser::currentDocument()
{
    return m_currentDocument;
}

RubyAst * RubyParser::parse()
{ /* TODO: Under construction */
    kDebug() << "PARSER: " << m_currentDocument.c_str() << "\n";
    return rb_compile_file(m_currentDocument.c_str());
    kDebug() << "It's working!\n";
    return NULL;
}

} // End of namespace: Ruby

