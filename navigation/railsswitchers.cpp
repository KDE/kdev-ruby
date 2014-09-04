/*
* This file is part of KDevelop
*
* Copyright 2007-2010 Alexander Dymo <adymo@kdevelop.org>
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


#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <kio/global.h>

#include <interfaces/icore.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/idocumentcontroller.h>
#include <language/interfaces/iquickopen.h>

#include <navigation/railsswitchers.h>

/*
 * TODO: add tests + style.
 */

namespace Rails
{

Switchers::Switchers(Ruby::LanguageSupport *language) : QObject(language)
{
    /* There's nothing to do here. */
}

KDevelop::Path Switchers::findRailsRoot(const QUrl &url)
{
    KDevelop::Path current(url.toString());
    KDevelop::Path upUrl(current.parent());

    while (upUrl != current) {
        KDevelop::Path aux = upUrl.parent();
        if (aux.lastPathSegment() == "app") {
            const QString &dir = upUrl.lastPathSegment();
            if (dir == "controllers" || dir == "models" || dir == "views") {
                return aux.parent();
            }
        } else if (upUrl.lastPathSegment() == "test") {
            return aux;
        }
        current = upUrl;
        upUrl = aux;
    }
    return KDevelop::Path();
}

void Switchers::switchToController()
{
    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) {
        return;
    }

    QFileInfo file(activeDocument->url().toLocalFile());
    if (!file.exists()) {
        return;
    }

    QString ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";
    QUrl railsRoot = findRailsRoot(activeDocument->url()).toUrl();
    if (railsRoot.isEmpty()) {
        return;
    }

    if ((ext == "rb") && !name.endsWith("_controller")) {
        if (name.endsWith("_test")) {
            switchTo = name.remove(QRegExp("_test$"));
            switchTo = name.remove(QRegExp("_controller$"));
        } else {
            switchTo = name;
        }
    } else if (ext == "rjs" || ext == "rxml" || ext == "rhtml" || ext == "js.rjs" ||
                ext == "xml.builder" || ext == "html.erb" || ext == "erb" ) {

        /*
         * This is a view, we need to find the directory of this view and try
         * to find the controller basing on the directory information
         */
        switchTo = file.dir().dirName();
    }

    if (!switchTo.isEmpty()) {
        QUrl controllerUrl = railsRoot;
        controllerUrl.setPath(controllerUrl.path() + "/app/controllers");

        if (switchTo.endsWith("s")) {
            switchTo = switchTo.mid(0, switchTo.length()-1);
        }
        QUrl singular = controllerUrl;
        singular.setPath(singular.path() + switchTo + "_controller.rb");
        QUrl plural = controllerUrl;
        plural.setPath(plural.path() + switchTo + "s_controller.rb");

        QUrl url = QUrl::fromLocalFile(QFile::exists(singular.toLocalFile()) ? singular.path() : plural.path());
        KDevelop::ICore::self()->documentController()->openDocument(url);
    }
}

void Switchers::switchToModel()
{
    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) {
        return;
    }

    QFileInfo file(activeDocument->url().toLocalFile());
    if (!file.exists()) {
        return;
    }

    QString ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    QUrl railsRoot = findRailsRoot(activeDocument->url()).toUrl();
    if (railsRoot.isEmpty()) {
        return;
    }

    if (ext == "rjs" || ext == "rxml" || ext == "rhtml" || ext == "js.rjs" || ext == "xml.builder"
        || ext == "html.erb" || ext == "erb") {
        // This is a view already, let's show the list of all views for this model
        switchTo = file.dir().dirName();
    } else if (ext == "rb" && (name.endsWith("_controller") || name.endsWith("_test"))) {
        switchTo = name.remove(QRegExp("_controller$")).remove(QRegExp("_controller_test$")).remove(QRegExp("_test$"));
    }

    if (switchTo.isEmpty()) {
        return;
    }

    QUrl modelUrl = QUrl::fromLocalFile(railsRoot.path() + "/app/models");
    if (switchTo.endsWith("s")) {
        switchTo = switchTo.mid(0, switchTo.length()-1);
    }
    modelUrl.setPath(modelUrl.path() + "/" + switchTo + ".rb");
    KDevelop::ICore::self()->documentController()->openDocument(modelUrl);
}

void Switchers::switchToView()
{
    if (viewsToSwitch().isEmpty()) {
        return;
    }

    KDevelop::IQuickOpen *quickOpen = KDevelop::ICore::self()->pluginController()
        ->extensionForPlugin<KDevelop::IQuickOpen>("org.kdevelop.IQuickOpen");
    if (quickOpen) {
        quickOpen->showQuickOpen(QStringList() << i18n("Rails Views"));
    }
}

QList<QUrl> Switchers::viewsToSwitch()
{
    QList<QUrl> urls;

    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) {
        return urls;
    }

    QFileInfo file(activeDocument->url().toLocalFile());
    if (!file.exists()) {
        return urls;
    }

    QString ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    if (ext == "rjs" || ext == "rxml" || ext == "rhtml" || ext == "js.rjs"
            || ext == "xml.builder" || ext == "html.erb") {
        /*
         * This is a view already, let's show the list of all views
         * for this model.
         */
        switchTo = file.dir().dirName();
    } else if (ext == "rb") {
        switchTo = name.remove(QRegExp("_controller$")).remove(QRegExp("_controller_test$")).remove(QRegExp("_test$"));
    }

    if (switchTo.isEmpty()) {
        return urls;
    }
    if (switchTo.endsWith("s")) {
        switchTo = switchTo.mid(0, switchTo.length() - 1);
    }

    QUrl railsRoot = findRailsRoot(activeDocument->url()).toUrl();
    if (railsRoot.isEmpty()) {
        return urls;
    }

    QUrl viewsUrl = QUrl::fromLocalFile(railsRoot.path() + "/app/views");
    QUrl viewsUrlS = QUrl::fromLocalFile(viewsUrl.path() + switchTo);
    QUrl viewsUrlP = QUrl::fromLocalFile(viewsUrl.path() + switchTo + "s");

    if (QFile::exists(viewsUrlS.toLocalFile())) {
        viewsUrl = viewsUrlS;
    } else if (QFile::exists(viewsUrlP.toLocalFile())) {
        viewsUrl = viewsUrlP;
    } else {
        return urls;
    }

    QDir viewsDir(viewsUrl.toLocalFile());
    QStringList views = viewsDir.entryList();

    foreach (const QString &viewName, views) {
        if (!(viewName.endsWith("~") || viewName == "." || viewName == "..")) {
            QUrl viewUrl = QUrl::fromLocalFile(viewsDir.absolutePath() + "/" + viewName);
            urls << viewUrl;
        }
    }
    return urls;
}

QList<QUrl> Switchers::testsToSwitch()
{
    QList<QUrl> urls;

    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) {
        return urls;
    }

    QFileInfo file(activeDocument->url().toLocalFile());
    if (!file.exists()) {
        return urls;
    }

    QString ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    if (ext == "rjs" || ext == "rxml" || ext == "rhtml" || ext == "js.rjs"
            || ext == "xml.builder" || ext == "html.erb" || ext == "erb") {
        switchTo = file.dir().dirName();
    } else if (ext == "rb") {
        switchTo = name.remove(QRegExp("_controller$")).remove(QRegExp("_controller_test$")).remove(QRegExp("_test$"));
    }

    if (switchTo.isEmpty()) {
        return urls;
    }
    if (switchTo.endsWith("s")) {
        switchTo = switchTo.mid(0, switchTo.length() - 1);
    }

    QUrl testsUrl = findRailsRoot(activeDocument->url()).toUrl();
    testsUrl.setPath(testsUrl.path() + "/test");

    QUrl functionalTestsUrlS = QUrl::fromLocalFile(testsUrl.path() + "/functional/" +
                                    switchTo + "_controller_test.rb");
    if (QFile::exists(functionalTestsUrlS.toLocalFile())) {
        urls << functionalTestsUrlS;
    }

    QUrl functionalTestsUrlP = QUrl::fromLocalFile(testsUrl.path() + "/functional/" +
                                    switchTo + "s_controller_test.rb");
    if (QFile::exists(functionalTestsUrlP.toLocalFile())) {
        urls << functionalTestsUrlP;
    }

    QUrl integrationTestsUrlS = QUrl::fromLocalFile(testsUrl.path() + "/integration/" +
                                    switchTo + "_test.rb");
    if (QFile::exists(integrationTestsUrlS.toLocalFile())) {
        urls << integrationTestsUrlS;
    }

    QUrl integrationTestsUrlP = QUrl::fromLocalFile(testsUrl.path() + "/integration/" +
                                    switchTo + "s_test.rb");
    if (QFile::exists(integrationTestsUrlP.toLocalFile())) {
        urls << integrationTestsUrlP;
    }

    QUrl unitTestsUrlS = QUrl::fromLocalFile(testsUrl.path() + "/unit/" +
                                                switchTo + "_test.rb");
    if (QFile::exists(unitTestsUrlS.toLocalFile())) {
        urls << unitTestsUrlS;
    }

    QUrl unitTestsUrlP = QUrl::fromLocalFile(testsUrl.path() + "/unit/" +
                                                switchTo + "s_test.rb");
    if (QFile::exists(unitTestsUrlP.toLocalFile())) {
        urls << unitTestsUrlP;
    }

    return urls;
}

void Switchers::switchToTest()
{
    if (testsToSwitch().isEmpty()) {
        return;
    }

    KDevelop::IQuickOpen *quickOpen = KDevelop::ICore::self()->pluginController()
        ->extensionForPlugin<KDevelop::IQuickOpen>("org.kdevelop.IQuickOpen");
    if (quickOpen) {
        quickOpen->showQuickOpen(QStringList() << i18n("Rails Tests"));
    }
}

}

