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

#include <interfaces/icore.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/idocumentcontroller.h>
#include <language/interfaces/iquickopen.h>

#include <rails/railsswitchers.h>
#include <rails/helpers.h>


namespace Rails
{

Switchers::Switchers(Ruby::LanguageSupport *language) : QObject(language)
{
    /* There's nothing to do here. */
}

QVector<KDevelop::Path> Switchers::viewsToSwitch()
{
    QVector<KDevelop::Path> urls;

    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) {
        return urls;
    }

    const QUrl &url = activeDocument->url();
    QFileInfo file(url.toLocalFile());
    if (!file.exists()) {
        return urls;
    }

    const QString &ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    if (Helpers::isViewExtension(ext)) {
        switchTo = file.dir().dirName();
    } else if (ext == "rb") {
        switchTo = name.remove(QRegExp("_controller$"));
        switchTo = switchTo.remove(QRegExp("_controller_test$"));
        switchTo = switchTo.remove(QRegExp("_test$"));
    }

    if (switchTo.isEmpty()) {
        return urls;
    }
    if (switchTo.endsWith("s")) {
        switchTo = switchTo.mid(0, switchTo.length() - 1);
    }

    KDevelop::Path root = Helpers::findRailsRoot(url);
    if (!root.isValid()) {
        return urls;
    }

    KDevelop::Path viewsUrl(root, QString("app/views"));
    KDevelop::Path viewsUrlS(viewsUrl, switchTo);
    KDevelop::Path viewsUrlP(viewsUrl, switchTo + "s");

    if (QFile::exists(viewsUrlS.toLocalFile())) {
        viewsUrl = viewsUrlS;
    } else if (QFile::exists(viewsUrlP.toLocalFile())) {
        viewsUrl = viewsUrlP;
    } else {
        return urls;
    }

    QDir viewsDir(viewsUrl.toLocalFile());
    const QStringList &views = viewsDir.entryList();
    const KDevelop::Path base(viewsDir.absolutePath());

    foreach (const QString &name, views) {
        if (!(name.endsWith("~") || name == "." || name == "..")) {
            urls << KDevelop::Path(base, name);
        }
    }
    return urls;
}

QVector<KDevelop::Path> Switchers::testsToSwitch()
{
    QVector<KDevelop::Path> urls;

    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) {
        return urls;
    }

    QFileInfo file(activeDocument->url().toLocalFile());
    if (!file.exists()) {
        return urls;
    }

    const QString &ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    if (Helpers::isViewExtension(ext)) {
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

    KDevelop::Path testsUrl(Helpers::findRailsRoot(activeDocument->url()), "test");
    KDevelop::Path functionalTestsUrlS(testsUrl, "functional/" + switchTo + "_controller_test.rb");
    if (QFile::exists(functionalTestsUrlS.toLocalFile())) {
        urls << functionalTestsUrlS;
    }

    KDevelop::Path functionalTestsUrlP(testsUrl, "functional/" + switchTo + "s_controller_test.rb");
    if (QFile::exists(functionalTestsUrlP.toLocalFile())) {
        urls << functionalTestsUrlP;
    }

    KDevelop::Path integrationTestsUrlS(testsUrl, "integration/" + switchTo + "_test.rb");
    if (QFile::exists(integrationTestsUrlS.toLocalFile())) {
        urls << integrationTestsUrlS;
    }

    KDevelop::Path integrationTestsUrlP(testsUrl, "integration/" + switchTo + "s_test.rb");
    if (QFile::exists(integrationTestsUrlP.toLocalFile())) {
        urls << integrationTestsUrlP;
    }

    KDevelop::Path unitTestsUrlS(testsUrl, "unit/" + switchTo + "_test.rb");
    if (QFile::exists(unitTestsUrlS.toLocalFile())) {
        urls << unitTestsUrlS;
    }

    KDevelop::Path unitTestsUrlP(testsUrl, "unit/" + switchTo + "s_test.rb");
    if (QFile::exists(unitTestsUrlP.toLocalFile())) {
        urls << unitTestsUrlP;
    }

    return urls;
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
    KDevelop::Path root = Helpers::findRailsRoot(activeDocument->url());
    if (!root.isValid()) {
        return;
    }

    if ((ext == "rb") && !name.endsWith("_controller")) {
        if (name.endsWith("_test")) {
            switchTo = name.remove(QRegExp("_test$"));
            switchTo = name.remove(QRegExp("_controller$"));
        } else {
            switchTo = name;
        }
    } else if (Helpers::isViewExtension(ext)) {
        switchTo = file.dir().dirName();
    }

    if (!switchTo.isEmpty()) {
        KDevelop::Path url(root, "app/controllers");

        if (switchTo.endsWith("s")) {
            switchTo = switchTo.mid(0, switchTo.length() - 1);
        }
        KDevelop::Path singular(url, switchTo + "_controller.rb");
        KDevelop::Path plural(url, switchTo + "s_controller.rb");

        QUrl doc;
        if (QFile::exists(singular.toLocalFile())) {
            doc = singular.toUrl();
        } else {
            doc = plural.toUrl();
        }
        KDevelop::ICore::self()->documentController()->openDocument(doc);
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

    KDevelop::Path root = Helpers::findRailsRoot(activeDocument->url());
    if (!root.isValid()) {
        return;
    }

    if (Helpers::isViewExtension(ext)) {
        switchTo = file.dir().dirName();
    } else if (ext == "rb" && (name.endsWith("_controller") || name.endsWith("_test"))) {
        switchTo = name.remove(QRegExp("_controller$"));
        switchTo = switchTo.remove(QRegExp("_controller_test$"));
        switchTo = switchTo.remove(QRegExp("_test$"));
    }
    if (switchTo.isEmpty()) {
        return;
    }

    KDevelop::Path url(root, "app/models");
    if (switchTo.endsWith("s")) {
        switchTo = switchTo.mid(0, switchTo.length() - 1);
    }
    url.addPath(switchTo + ".rb");
    KDevelop::ICore::self()->documentController()->openDocument(url.toUrl());
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

