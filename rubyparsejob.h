/* This file is part of KDevelop
 *
 * Copyright 2008-2010 Alexander Dymo <adymo@kdevelop.org>
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


#ifndef RUBY_PARSEJOB_H
#define RUBY_PARSEJOB_H


#include <language/backgroundparser/parsejob.h>


namespace Ruby
{

class LanguageSupport;
class RubyParser;

/**
 * @class ParseJob
 *
 * This is a subclass of KDevelop::ParseJob and does the parse
 * job for the Ruby language.
 */
class ParseJob : public KDevelop::ParseJob
{
    Q_OBJECT

public:
    enum { Rescheduled = KDevelop::TopDUContext::LastFeature };

    /**
     * Constructor.
     *
     * @param url the url of the file to parse.
     */
    explicit ParseJob(const KDevelop::IndexedString &url,
                      KDevelop::ILanguageSupport *languageSupport);

    /**
     * Destructor.
     */
    virtual ~ParseJob();

protected:
    /**
     * Runs this ParseJob.
     */
    virtual void run(ThreadWeaver::JobPointer pointer,
                     ThreadWeaver::Thread *thread) override;

private:
    /**
     * @return static accessor to avoid casting.
     */
    LanguageSupport * ruby() const;

private:
    /**
     * Ruby parser.
     */
    RubyParser *m_parser;

    /**
     * A reference to the current TopDUContext.
     */
    KDevelop::ReferencedTopDUContext m_duContext;
};

} // End of namespace ruby

#endif /* RUBY_PARSEJOB_H */
