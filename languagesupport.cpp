/* This file is part of KDevelop
 *
 * Copyright 2006-2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright (C) 2014-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#include <languagesupport.h>

#include <QProcess>
#include <QStandardPaths>

#include <KPluginFactory>

#include <interfaces/contextmenuextension.h>
#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/iplugincontroller.h>
#include <language/codecompletion/codecompletion.h>
#include <language/interfaces/editorcontext.h>

#include <completion/model.h>
#include <codegen/refactoring.h>
#include <debug.h>
#include <duchain/helpers.h>
#include <highlighting.h>
#include <launcher.h>
#include <parsejob.h>
#include <rails/helpers.h>
#include <rails/support.h>

K_PLUGIN_FACTORY_WITH_JSON(KDevRubySupportFactory, "kdevrubylanguagesupport.json", registerPlugin<ruby::LanguageSupport>();)

Q_LOGGING_CATEGORY(KDEV_RUBY, "kdevelop.languages.ruby")

using namespace ruby;
using namespace KDevelop;

LanguageSupport::LanguageSupport(QObject *parent, const QVariantList &)
    : IPlugin(QStringLiteral("kdevrubysupport"), parent)
    , ILanguageSupport()
{
    KDEV_USE_EXTENSION_INTERFACE(ILanguageSupport)

    // TODO: this should be removed once KDE knows how to handle categories.
    QLoggingCategory::setFilterRules(QStringLiteral("kdevelop.languages.ruby.debug = true"));

    m_rails = new rails::Support(this);
    m_launcher = new Launcher(this);

    setXMLFile("kdevrubysupport.rc");
    m_highlighting = new Highlighting(this);
    m_refactoring = new Refactoring(this);
    CodeCompletionModel *rModel = new CodeCompletionModel(this);
    new CodeCompletion(this, rModel, "Ruby");

    /* Retrieving Ruby version */
    QString path = QStandardPaths::findExecutable("ruby");
    if (!path.isEmpty()) {
        QProcess ruby;
        ruby.start(path, QStringList{ "--version" });
        ruby.waitForFinished(3000);
        QList<QByteArray> byteArr = ruby.readAllStandardOutput().split(' ');
        if (byteArr.size() > 1) {
            const QString &output = byteArr[1];
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
    } else {
        qWarning() << "ruby might not be installed!";
    }
}

LanguageSupport::~LanguageSupport()
{
}

QString LanguageSupport::name() const
{
    return QStringLiteral("Ruby");
}

KDevelop::ParseJob * LanguageSupport::createParseJob(const IndexedString &url)
{
    return new ruby::ParseJob(url, this);
}

ICodeHighlighting * LanguageSupport::codeHighlighting() const
{
    return m_highlighting;
}

ContextMenuExtension LanguageSupport::contextMenuExtension(Context *context)
{
    ContextMenuExtension cm;
    EditorContext *ed = dynamic_cast<EditorContext *>(context);

    if (ed && ICore::self()->languageController()->languagesForUrl(ed->url()).
            contains(this)) {
        // It's safe to add our own ContextMenuExtension.
        m_refactoring->fillContextMenu(cm, context);
    }
    return cm;
}

enum ruby_version LanguageSupport::version() const
{
    return m_version;
}

void LanguageSupport::createActionsForMainWindow(Sublime::MainWindow *,
                                                 QString &_xmlFile,
                                                 KActionCollection &actions)
{
    _xmlFile = xmlFile();

    m_rails->setupActions(actions);
    m_launcher->setupActions(actions);
}

#include "languagesupport.moc"

