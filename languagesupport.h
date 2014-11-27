/* This file is part of KDevelop
 *
 * Copyright 2006-2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright 2014 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef RUBY_LANGUAGE_SUPPORT_H
#define RUBY_LANGUAGE_SUPPORT_H

#include <interfaces/iplugin.h>
#include <language/interfaces/ilanguagesupport.h>

#include <parser/node.h>

namespace ruby {

class Highlighting;
class Launcher;
class Refactoring;

namespace rails {
    class Support;
}

/**
 * @class LanguageSupport
 *
 * This is the class that represents the KDevelop Ruby Plugin. This class
 * also connects all the actions related to Rails navigation. And last, but
 * not least, this class also enables the plugin to execute the current Ruby
 * file or test functions.
 */
class LanguageSupport
    : public KDevelop::IPlugin
    , public KDevelop::ILanguageSupport
{
    Q_OBJECT
    Q_INTERFACES(KDevelop::ILanguageSupport)

public:
    explicit LanguageSupport(QObject *parent, const QVariantList &args = {});
    virtual ~LanguageSupport();

    /**
     * @return an instance of this LanguageSupport.
     */
    static LanguageSupport * self();

    /**
     * @return the name of the language.
     */
    virtual QString name() const override;

    /**
     * @return the ParseJob that is going to be used by the Background
     * parser to parse the given @p url.
     */
    virtual KDevelop::ParseJob * createParseJob(const KDevelop::IndexedString &url) override;

    /**
     * @return the language for this support.
     */
    virtual KDevelop::ILanguage * language() override;

    /**
     * @return the Code Highlighting for the Ruby language.
     */
    virtual KDevelop::ICodeHighlighting * codeHighlighting() const override;

    /**
     * @returns the ContextMenuExtension for the Php plugin.
     */
    virtual KDevelop::ContextMenuExtension contextMenuExtension(KDevelop::Context *context) override;

    /**
     * @return the version of Ruby to be picked.
     */
    enum ruby_version version() const;

    /**
     * Setup the actions defined by this plugin.
     */
    virtual void createActionsForMainWindow(Sublime::MainWindow *window,
                                            QString &xmlFile,
                                            KActionCollection &actions) override;

private:
    Highlighting *m_highlighting;
    Refactoring *m_refactoring;
    Launcher *m_launcher;
    enum ruby_version m_version;

    rails::Support *m_rails;
};

}

#endif // RUBY_LANGUAGE_SUPPORT_H

