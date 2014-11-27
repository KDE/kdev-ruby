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


//BEGIN Includes
// Qt + KDE
#include <QtCore/QTimer>
#include <QtCore/QProcess>
#include <QtWidgets/QAction>

//KDevelop
#include <interfaces/icore.h>
#include <interfaces/iproject.h>
#include <interfaces/idocument.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/iruncontroller.h>
#include <interfaces/ilauncher.h>
#include <interfaces/ilaunchmode.h>
#include <interfaces/ilaunchconfiguration.h>
#include <interfaces/launchconfigurationtype.h>
#include <execute/iexecuteplugin.h>
#include <project/projectmodel.h>
#include <language/interfaces/iquickopen.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/duchainutils.h>
#include <language/backgroundparser/backgroundparser.h>
#include <language/codecompletion/codecompletion.h>
#include <interfaces/contextmenuextension.h>
#include <language/interfaces/editorcontext.h>

//Ruby plugin
#include <languagesupport.h>
#include <parsejob.h>
#include <highlighting.h>
#include <rails/helpers.h>
#include <rails/support.h>
#include <duchain/helpers.h>
#include <completion/model.h>
#include <codegen/refactoring.h>
#include <debug.h>
#include <launcher.h>
//END Includes

K_PLUGIN_FACTORY(KDevRubySupportFactory, registerPlugin<ruby::LanguageSupport>();)

Q_LOGGING_CATEGORY(KDEV_RUBY, "kdev.ruby")

using namespace ruby;

LanguageSupport::LanguageSupport(QObject *parent, const QVariantList &)
    : KDevelop::IPlugin(QStringLiteral("kdevrubysupport"), parent)
    , KDevelop::ILanguageSupport()
{
    KDEV_USE_EXTENSION_INTERFACE(KDevelop::ILanguageSupport)

    // TODO: this should be removed once KDE knows how to handle categories.
    QLoggingCategory::setFilterRules(QStringLiteral("kdev.ruby.debug = true"));

    m_rails = new rails::Support(this);
    m_launcher = new Launcher(this);

    setXMLFile("kdevrubysupport.rc");
    m_highlighting = new ruby::Highlighting(this);
    m_refactoring = new ruby::Refactoring(this);
    CodeCompletionModel *rModel = new CodeCompletionModel(this);
    new KDevelop::CodeCompletion(this, rModel, "Ruby");

    /* Retrieving Ruby version */
    QProcess ruby;
    ruby.start("/usr/bin/env", QStringList() << "ruby" << "--version");
    ruby.waitForFinished();
    QString output = ruby.readAllStandardOutput().split(' ')[1];
    QStringList version = output.split('.');
    if (version.size() > 1) {
        if (version[0] == "1") {
            m_version = (version[1] == "8") ? ruby18 : ruby19;
        } else if (version[1] == "0") {
            m_version = ruby20;
        } else {
            m_version = ruby21;
        }
    }
}

LanguageSupport::~LanguageSupport()
{
}

QString LanguageSupport::name() const
{
    return QStringLiteral("Ruby");
}

KDevelop::ParseJob * LanguageSupport::createParseJob(const KDevelop::IndexedString &url)
{
    return new ParseJob(url, this);
}

KDevelop::ILanguage * LanguageSupport::language()
{
    return core()->languageController()->language(name());
}

KDevelop::ICodeHighlighting * LanguageSupport::codeHighlighting() const
{
    return m_highlighting;
}

KDevelop::ContextMenuExtension LanguageSupport::contextMenuExtension(KDevelop::Context *context)
{
    KDevelop::ContextMenuExtension cm;
    KDevelop::EditorContext *ed = dynamic_cast<KDevelop::EditorContext *>(context);

    if (ed && KDevelop::ICore::self()->languageController()->languagesForUrl(ed->url()).contains(language())) {
        // It's safe to add our own ContextMenuExtension.
        m_refactoring->fillContextMenu(cm, context);
    }
    return cm;
}

enum ruby_version LanguageSupport::version() const
{
    return m_version;
}

void LanguageSupport::createActionsForMainWindow(Sublime::MainWindow * /*window*/,
                                                 QString &_xmlFile,
                                                 KActionCollection &actions)
{
    _xmlFile = xmlFile();

    m_rails->setupActions(actions);
    m_launcher->setupActions(actions);
}

#include "languagesupport.moc"

