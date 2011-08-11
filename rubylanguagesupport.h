/* This file is part of KDevelop
 *
 * Copyright 2006-2010 Alexander Dymo <adymo@kdevelop.org>
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


#ifndef KDEVRUBYLANGUAGESUPPORT_H
#define KDEVRUBYLANGUAGESUPPORT_H


#include <interfaces/iplugin.h>
#include <language/interfaces/ilanguagesupport.h>

/*
 * WARNING: This file (and class) is a complete mess. It should be properly
 * polished as soon as possible.
 */

class KConfigGroup;

namespace KDevelop {
    class IDocument;
    class IProject;
    class ILaunchConfiguration;
    class ICodeHighlighting;
}

namespace Ruby
{

class RailsSwitchers;
class RailsDataProvider;
class Highlighting;

class LanguageSupport : public KDevelop::IPlugin, public KDevelop::ILanguageSupport
{
    Q_OBJECT
    Q_INTERFACES( KDevelop::ILanguageSupport )

public:
    LanguageSupport(QObject * parent, const QVariantList &args = QVariantList());
    virtual ~LanguageSupport();

    static LanguageSupport * self();
    virtual QString name() const;
    virtual KDevelop::ParseJob * createParseJob(const KUrl &);
    virtual KDevelop::ILanguage * language();
    virtual KDevelop::ICodeHighlighting* codeHighlighting() const;

    QStringList extensions() const;

private Q_SLOTS:
    void documentLoaded(KDevelop::IDocument * document);
    void documentClosed(KDevelop::IDocument * document);
    void projectOpened(KDevelop::IProject * project);
    void projectClosing(KDevelop::IProject * project);
    void documentChanged( KDevelop::IDocument * document );
    void documentActivated( KDevelop::IDocument * document );

    void runCurrentFile();
    void runCurrentTestFunction();

private:
    KDevelop::ILaunchConfiguration *findOrCreateLaunchConfiguration(const QString &name);
    void setUpLaunchConfigurationBeforeRun(KConfigGroup &cfg, KDevelop::IDocument *activeDocument);
    QString findFunctionUnderCursor(KDevelop::IDocument *doc);

    static LanguageSupport* m_self;
    Ruby::Highlighting *m_highlighting;

    RailsSwitchers *m_railsSwitchers;
    RailsDataProvider *m_viewsQuickOpenDataProvider;
    RailsDataProvider *m_testsQuickOpenDataProvider;
    KDevelop::ILaunchConfiguration *m_rubyFileLaunchConfiguration;
    KDevelop::ILaunchConfiguration *m_rubyCurrentFunctionLaunchConfiguration;

};

} // End of namespace Ruby


#endif

