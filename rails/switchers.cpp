/*
* This file is part of KDevelop
*
* Copyright 2007-2010 Alexander Dymo <adymo@kdevelop.org>
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

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

#include <KLocalizedString>

#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/iplugincontroller.h>
#include <language/interfaces/iquickopen.h>

#include <languagesupport.h>
#include <rails/switchers.h>
#include <rails/helpers.h>

using namespace KDevelop;
using namespace ruby::rails;

namespace {

bool isViewExtension(const QString &extension)
{
    return (extension == QStringLiteral("rjs") ||
            extension == QStringLiteral("rxml") ||
            extension == QStringLiteral("rhtml") ||
            extension == QStringLiteral("js.rjs") ||
            extension == QStringLiteral("xml.builder") ||
            extension == QStringLiteral("html.erb") ||
            extension == QStringLiteral("erb") ||
            extension == QStringLiteral("haml"));
}

}

Switchers::Switchers(ruby::LanguageSupport *language)
    : QObject(language)
{
}

QVector<Path> Switchers::viewsToSwitch()
{
    QVector<Path> urls;

    auto doc = ICore::self()->documentController()->activeDocument();
    if (!doc) {
        return urls;
    }

    const QUrl &url = doc->url();
    QFileInfo file(url.toLocalFile());
    if (!file.exists()) {
        return urls;
    }

    const QString &ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    if (isViewExtension(ext)) {
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

    Path root = Helpers::findRailsRoot(url);
    if (!root.isValid()) {
        return urls;
    }

    Path viewsUrl(root, QStringLiteral("app/views"));
    Path viewsUrlS(viewsUrl, switchTo);
    Path viewsUrlP(viewsUrl, switchTo + "s");

    if (QFile::exists(viewsUrlS.toLocalFile())) {
        viewsUrl = viewsUrlS;
    } else if (QFile::exists(viewsUrlP.toLocalFile())) {
        viewsUrl = viewsUrlP;
    } else {
        return urls;
    }

    QDir viewsDir(viewsUrl.toLocalFile());
    const QStringList &views = viewsDir.entryList();
    const Path base(viewsDir.absolutePath());

    foreach (const QString &name, views) {
        if (!(name.endsWith("~") || name == "." || name == "..")) {
            urls << KDevelop::Path(base, name);
        }
    }
    return urls;
}

QVector<Path> Switchers::testsToSwitch()
{
    QVector<KDevelop::Path> urls;

    auto doc = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!doc) {
        return urls;
    }

    QFileInfo file(doc->url().toLocalFile());
    if (!file.exists()) {
        return urls;
    }

    const QString &ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    if (isViewExtension(ext)) {
        switchTo = file.dir().dirName();
    } else if (ext == "rb") {
        switchTo = name.remove(QRegExp("_controller$")).
            remove(QRegExp("_controller_test$")).remove(QRegExp("_test$"));
    }
    if (switchTo.isEmpty()) {
        return urls;
    }
    if (switchTo.endsWith("s")) {
        switchTo = switchTo.mid(0, switchTo.length() - 1);
    }

    Path testsUrl(Helpers::findRailsRoot(doc->url()), "test");
    Path functionalTestsUrlS(testsUrl, "functional/" + switchTo +
        "_controller_test.rb");
    if (QFile::exists(functionalTestsUrlS.toLocalFile())) {
        urls << functionalTestsUrlS;
    }

    Path functionalTestsUrlP(testsUrl, "functional/" + switchTo +
        "s_controller_test.rb");
    if (QFile::exists(functionalTestsUrlP.toLocalFile())) {
        urls << functionalTestsUrlP;
    }

    Path integrationTestsUrlS(testsUrl, "integration/" + switchTo + "_test.rb");
    if (QFile::exists(integrationTestsUrlS.toLocalFile())) {
        urls << integrationTestsUrlS;
    }

    Path integrationTestsUrlP(testsUrl, "integration/" + switchTo + "s_test.rb");
    if (QFile::exists(integrationTestsUrlP.toLocalFile())) {
        urls << integrationTestsUrlP;
    }

    Path unitTestsUrlS(testsUrl, "unit/" + switchTo + "_test.rb");
    if (QFile::exists(unitTestsUrlS.toLocalFile())) {
        urls << unitTestsUrlS;
    }

    Path unitTestsUrlP(testsUrl, "unit/" + switchTo + "s_test.rb");
    if (QFile::exists(unitTestsUrlP.toLocalFile())) {
        urls << unitTestsUrlP;
    }

    return urls;
}

void Switchers::switchToController()
{
    auto doc = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!doc) {
        return;
    }

    QFileInfo file(doc->url().toLocalFile());
    if (!file.exists()) {
        return;
    }

    const QString &ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";
    Path root = Helpers::findRailsRoot(doc->url());
    if (!root.isValid()) {
        return;
    }

    if (ext == QStringLiteral("rb") &&
        !name.endsWith(QStringLiteral("_controller"))) {

        if (name.endsWith("_test")) {
            switchTo = name.remove(QRegExp("_test$"));
            switchTo = name.remove(QRegExp("_controller$"));
        } else {
            switchTo = name;
        }
    } else if (isViewExtension(ext)) {
        switchTo = file.dir().dirName();
    }

    if (!switchTo.isEmpty()) {
        Path url(root, "app/controllers");

        if (switchTo.endsWith("s")) {
            switchTo = switchTo.mid(0, switchTo.length() - 1);
        }
        Path singular(url, switchTo + "_controller.rb");
        Path plural(url, switchTo + "s_controller.rb");

        QUrl docUrl;
        if (QFile::exists(singular.toLocalFile())) {
            docUrl = singular.toUrl();
        } else {
            docUrl = plural.toUrl();
        }
        ICore::self()->documentController()->openDocument(docUrl);
    }
}

void Switchers::switchToModel()
{
    auto doc = ICore::self()->documentController()->activeDocument();
    if (!doc) {
        return;
    }

    QFileInfo file(doc->url().toLocalFile());
    if (!file.exists()) {
        return;
    }

    const QString &ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    Path root = Helpers::findRailsRoot(doc->url());
    if (!root.isValid()) {
        return;
    }

    if (isViewExtension(ext)) {
        switchTo = file.dir().dirName();
    } else if (ext == QStringLiteral("rb") &&
                (name.endsWith(QStringLiteral("_controller")) ||
                 name.endsWith(QStringLiteral("_test")))) {

        switchTo = name.remove(QRegExp("_controller$"));
        switchTo = switchTo.remove(QRegExp("_controller_test$"));
        switchTo = switchTo.remove(QRegExp("_test$"));
    }
    if (switchTo.isEmpty()) {
        return;
    }

    Path url(root, QStringLiteral("app/models"));
    if (switchTo.endsWith("s")) {
        switchTo = switchTo.mid(0, switchTo.length() - 1);
    }
    url.addPath(switchTo + ".rb");
    ICore::self()->documentController()->openDocument(url.toUrl());
}

void Switchers::switchToView()
{
    if (viewsToSwitch().isEmpty()) {
        return;
    }

    auto quickOpen = ICore::self()->pluginController()->
        extensionForPlugin<IQuickOpen>("org.kdevelop.IQuickOpen");

    Q_ASSERT(quickOpen);
    quickOpen->showQuickOpen(QStringList{ i18n("Rails Views") });
}

void Switchers::switchToTest()
{
    if (testsToSwitch().isEmpty()) {
        return;
    }

    auto quickOpen = ICore::self()->pluginController()->
        extensionForPlugin<IQuickOpen>("org.kdevelop.IQuickOpen");

    Q_ASSERT(quickOpen);
    quickOpen->showQuickOpen(QStringList{ i18n("Rails Tests") });
}

