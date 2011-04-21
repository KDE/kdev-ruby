/* This file is part of KDevelop
 *
 * Copyright 2008-2010 Alexander Dymo <adymo@kdevelop.org>
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


#ifndef RUBY_PARSEJOB_H
#define RUBY_PARSEJOB_H


#include <KUrl>
#include <language/backgroundparser/parsejob.h>
#include <parser/node.h>


class RubyLanguageSupport;

namespace Ruby
{

class RubyParser;

class ParseJob : public KDevelop::ParseJob
{
    Q_OBJECT

public:
    enum { Resheduled = KDevelop::TopDUContext::LastFeature };

    /**
     * Constructor.
     *
     * @param url the url of the file to parse.
     * @param parent the RubyLanguageSupport this ParseJob is parented to.
     */
    ParseJob(const KUrl & url, RubyLanguageSupport * parent);

    /**
     * Destructor.
     */
    virtual ~ParseJob();

    /**
     * @return static accessor to avoid casting.
     */
    RubyLanguageSupport * ruby() const;

protected:
    /**
     * Runs this ParseJob.
     */
    virtual void run();

private:
    /**
     * @internal Called by the run() method. It's used to do the
     * parsing magic.
     */
    void parse();

private:
    const RubyLanguageSupport * m_parent;
    KUrl m_url;
    RubyParser * m_parser;
    RubyAst * m_lastAst;
};

} // end of namespace ruby


#endif

