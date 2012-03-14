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


// Qt
#include <QReadLocker>

// KDevelop
#include <interfaces/iplugin.h>
#include <language/interfaces/ilanguagesupport.h>
#include <language/duchain/indexedstring.h>
#include <language/duchain/topducontext.h>


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

/**
 * @class LanguageSupport
 *
 * This is the class that represents the KDevelop Ruby Plugin. This class
 * also connects all the actions related to Rails navigation. And last, but
 * not least, this class also enables the plugin to execute the current Ruby
 * file or test functions.
 */
class LanguageSupport : public KDevelop::IPlugin, public KDevelop::ILanguageSupport
{
    Q_OBJECT
    Q_INTERFACES(KDevelop::ILanguageSupport)

public:
    /**
     * Constructor.
     *
     * @param parent The QObject this LanguageSupport is parented to.
     * @param args A QVariantList that can be passed to this plugin as parameters.
     */
    LanguageSupport(QObject *parent, const QVariantList &args = QVariantList());

    /**
     * Destructor.
     */
    virtual ~LanguageSupport();

    /**
     * @return an instance of this LanguageSupport.
     */
    static LanguageSupport * self();

    /**
     * @return the name of the language.
     */
    virtual QString name() const;

    /**
     * @return the ParseJob that is going to be used by the Background
     * parser to parse the given @p url.
     */
    virtual KDevelop::ParseJob * createParseJob(const KUrl &url);

    /**
     * @return the language for this support.
     */
    virtual KDevelop::ILanguage * language();

    /**
     * @return the Code Highlighting for the Ruby language.
     */
    virtual KDevelop::ICodeHighlighting * codeHighlighting() const;

    /**
     * Override from KDevelop::IPlugin so it can @return an extension
     * of the context menu.
     */
    KDevelop::ContextMenuExtension contextMenuExtension(KDevelop::Context *ctx);

private:
    /**
     * @internal Find or create a launch for a the given @p name.
     * @return the launcj configuration for the given @p name.
     */
    KDevelop::ILaunchConfiguration *findOrCreateLaunchConfiguration(const QString &name);

    /**
     * @internal Set up the launch configuration before the run occurs.
     * @param cfg the KConfigGroup for this launch.
     * @param activeDocument the currently active document.
     */
    void setUpLaunchConfigurationBeforeRun(KConfigGroup &cfg, KDevelop::IDocument *activeDocument);

    /**
     * @internal Find the method under the cursor in the given \p doc. It's
     * used by the runCurrentTestFunction() slot.
     */
    QString findFunctionUnderCursor(KDevelop::IDocument *doc);

    /**
     * @internal Setup the actions defined by this plugin.
     */
    void setupActions();

    /**
     * @internal Setup IQuickOpen so it registers Rails data providers.
     */
    void setupQuickOpen();

public slots:
    /// The slot for the Create New Class dialog.
    void createNewClass();

private Q_SLOTS:
     /// The slot that allows this plugin to run the current Ruby file.
    void runCurrentFile();

    /// The slot that allows this plugin to run the current test function.
    void runCurrentTestFunction();

private:
    static LanguageSupport* m_self;
    Ruby::Highlighting *m_highlighting;

    RailsSwitchers *m_railsSwitchers;
    RailsDataProvider *m_viewsQuickOpenDataProvider;
    RailsDataProvider *m_testsQuickOpenDataProvider;
    KDevelop::ILaunchConfiguration *m_rubyFileLaunchConfiguration;
    KDevelop::ILaunchConfiguration *m_rubyCurrentFunctionLaunchConfiguration;
};

} // End of namespace Ruby


#endif // KDEVRUBYLANGUAGESUPPORT_H

