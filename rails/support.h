/* This file is part of KDevelop
 *
 * Copyright (C) 2014-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#ifndef RUBY_RAILS_H
#define RUBY_RAILS_H

#include <KActionCollection>
#include <rails/export.h>

namespace ruby {

class LanguageSupport;

namespace rails {

class Switchers;
class DataProvider;

/**
 * @class Support
 *
 * This class gathers together anything that has to do with Rails support. This
 * includes setting up Quick open, the main window actions, etc.
 */
class KDEVRUBYRAILS_EXPORT Support : public QObject
{
    Q_OBJECT

public:
    explicit Support(ruby::LanguageSupport *language);
    virtual ~Support();

    /**
     * Setup the Main Window actions.
     *
     * @param actions The main window actions to be modified.
     */
    void setupActions(KActionCollection &actions);

private:
    void setupQuickOpen();

private:
    ruby::LanguageSupport *m_support;
    Switchers *m_switchers;
    DataProvider *m_views;
    DataProvider *m_tests;
};

}
}

#endif // RUBY_RAILS_H

