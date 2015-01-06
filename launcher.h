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

#ifndef RUBY_LAUNCHER_H
#define RUBY_LAUNCHER_H

#include <kactioncollection.h>

namespace KDevelop {
    class IDocument;
    class ILaunchConfiguration;
}

namespace ruby {

class LanguageSupport;

/**
 * @class Launcher
 *
 * The class responsible for all the default launcher for this plugin. It's
 * only used by the LanguageSupport class, but I rather have this functionality
 * in this separate class than having a bloated LanguageSupport class.
 */
class Launcher : public QObject
{
public:
    explicit Launcher(LanguageSupport *support);

    /**
     * Setup the Main Window actions.
     *
     * @param actions The main window actions to be modified.
     */
    void setupActions(KActionCollection &actions);

private:
    /**
     * @internal Find or create a launch for a the given @p name.
     * @return the launch configuration for the given @p name.
     */
    KDevelop::ILaunchConfiguration * launchConfiguration(const QString &name);

private slots:
    /// The slot that allows this plugin to run the current Ruby file.
    void runCurrentFile();

    /// The slot that allows this plugin to run the current test function.
    void runCurrentTest();

private:
    LanguageSupport *m_support;
    KDevelop::ILaunchConfiguration *m_file;
    KDevelop::ILaunchConfiguration *m_function;
};

}

#endif // RUBY_LAUNCHER_H

