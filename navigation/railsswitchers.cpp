/*
* This file is part of KDevelop
*
* Copyright 2007-2010 Alexander Dymo <adymo@kdevelop.org>
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
#include "railsswitchers.h"

#include <QDir>
#include <QFileInfo>

#include <language/interfaces/iquickopen.h>

#include "interfaces/icore.h"
#include "interfaces/iplugincontroller.h"
#include "interfaces/idocumentcontroller.h"

namespace Ruby {

RailsSwitchers::RailsSwitchers(RubyLanguageSupport* language)
    :QObject(language), m_language(language)
{
}

KUrl RailsSwitchers::findRailsRoot(const KUrl& url)
{
    KUrl currentUrl = url;
    KUrl upUrl = currentUrl.upUrl();
    kDebug(9047) << "starting:" << upUrl;
    while (upUrl != currentUrl) {
        kDebug(9047) << "checking:" << upUrl;
        if ( (upUrl.fileName() == "controllers" and upUrl.upUrl().fileName() == "app")
             || (upUrl.fileName() == "models" and upUrl.upUrl().fileName() == "app")
             || (upUrl.fileName() == "views" and upUrl.upUrl().fileName() == "app") )
            return upUrl.upUrl().upUrl();
        else if (upUrl.fileName() == "test")
            return upUrl.upUrl();

        currentUrl = upUrl;
        upUrl = currentUrl.upUrl();
    }
    return KUrl();
}

void RailsSwitchers::switchToController()
{
    kDebug(9047) << "switching to controller";
    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) return;

    QFileInfo file(activeDocument->url().toLocalFile());
    if (!file.exists()) return;

    QString ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";
    KUrl railsRoot = findRailsRoot(activeDocument->url());
    kDebug(9047) << "   rails root found:" << railsRoot;
    if (railsRoot.isEmpty()) return;

    if ((ext == "rb") && !name.endsWith("_controller"))
    {
        if (name.endsWith("_test"))
        {
            switchTo = name.remove(QRegExp("_test$"));  //the file is the test
            switchTo = name.remove(QRegExp("_controller$"));  //remove functional test name parts
        }
        else
            switchTo = name;
    }
    else if (ext == "rjs" || ext == "rxml" || ext == "rhtml" || ext == "js.rjs" ||
        ext == "xml.builder" || ext == "html.erb" || ext == "erb" )
    {
        //this is a view, we need to find the directory of this view and try to find
        //the controller basing on the directory information
        switchTo = file.dir().dirName();
    }
    kDebug(9047) << "   switching to:" << switchTo;

    if (!switchTo.isEmpty())
    {
        KUrl controllerUrl = railsRoot;
        controllerUrl.addPath("app");
        controllerUrl.addPath("controllers");

        if (switchTo.endsWith("s"))
            switchTo = switchTo.mid(0, switchTo.length()-1);
        KUrl singular = controllerUrl;
        singular.addPath(switchTo + "_controller.rb");
        KUrl plural = controllerUrl;
        plural.addPath(switchTo + "s_controller.rb");

        kDebug(9047) << "   plural:" << plural;
        kDebug(9047) << "   singular:" << singular;

        KUrl url = KUrl(QFile::exists(singular.toLocalFile()) ? singular : plural);
        KDevelop::ICore::self()->documentController()->openDocument(url);
    }
}

void RailsSwitchers::switchToModel()
{
    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) return;

    QFileInfo file(activeDocument->url().toLocalFile());
    if (!file.exists()) return;

    QString ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    KUrl railsRoot = findRailsRoot(activeDocument->url());
    kDebug(9047) << "   rails root found:" << railsRoot;
    if (railsRoot.isEmpty()) return;

    if (ext == "rjs" || ext == "rxml" || ext == "rhtml" || ext == "js.rjs" || ext == "xml.builder"
        || ext == "html.erb" || ext == "erb")
    {
        //this is a view already, let's show the list of all views for this model
        switchTo = file.dir().dirName();
    }
    else if (ext == "rb" && (name.endsWith("_controller") || name.endsWith("_test")))
    {
        switchTo = name.remove(QRegExp("_controller$")).remove(QRegExp("_controller_test$")).remove(QRegExp("_test$"));
    }

    if (switchTo.isEmpty())
        return;

    KUrl modelUrl = railsRoot;
    modelUrl.addPath("app");
    modelUrl.addPath("models");

    if (switchTo.endsWith("s"))
        switchTo = switchTo.mid(0, switchTo.length()-1);
    modelUrl.addPath(switchTo + ".rb");

    KDevelop::ICore::self()->documentController()->openDocument(modelUrl);
}

void RailsSwitchers::switchToView()
{
    if (viewsToSwitch().isEmpty())
        return;

    KDevelop::IQuickOpen* quickOpen = KDevelop::ICore::self()->pluginController()
        ->extensionForPlugin<KDevelop::IQuickOpen>("org.kdevelop.IQuickOpen");
    if (quickOpen) {
        kDebug(9047) << "   showing quickopen";
        quickOpen->showQuickOpen(QStringList() << i18n("Rails Views"));
    }
}

KUrl::List RailsSwitchers::viewsToSwitch()
{
    KUrl::List urls;

    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) return urls;

    QFileInfo file(activeDocument->url().toLocalFile());
    if (!file.exists()) return urls;

    QString ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    if (ext == "rjs" || ext == "rxml" || ext == "rhtml" || ext == "js.rjs" || ext == "xml.builder" || ext == "html.erb")
    {
        //this is a view already, let's show the list of all views for this model
        switchTo = file.dir().dirName();
    }
    else if (ext == "rb")
        switchTo = name.remove(QRegExp("_controller$")).remove(QRegExp("_controller_test$")).remove(QRegExp("_test$"));

    if (switchTo.isEmpty())
        return urls;

    if (switchTo.endsWith("s"))
        switchTo = switchTo.mid(0, switchTo.length() - 1);

    KUrl railsRoot = findRailsRoot(activeDocument->url());
    kDebug(9047) << "   rails root found:" << railsRoot;
    if (railsRoot.isEmpty()) return urls;

    KUrl viewsUrl = railsRoot;
    viewsUrl.addPath("app");
    viewsUrl.addPath("views");
    KUrl viewsUrlS = viewsUrl;
    viewsUrlS.addPath(switchTo);
    KUrl viewsUrlP = viewsUrl;
    viewsUrlP.addPath(switchTo + "s");

    if (QFile::exists(viewsUrlS.toLocalFile()))
        viewsUrl = viewsUrlS;
    else if (QFile::exists(viewsUrlP.toLocalFile()))
        viewsUrl = viewsUrlP;
    else
        return urls;

    QDir viewsDir(viewsUrl.toLocalFile());
    QStringList views = viewsDir.entryList();

    foreach (const QString &viewName, views) {
        if ( !(viewName.endsWith("~") || viewName == "." || viewName == "..") ) {
            KUrl viewUrl(viewsDir.absolutePath());
            viewUrl.addPath(viewName);
            urls << viewUrl;
        }
    }
    kDebug(9047) << "   views found:" << urls;

    return urls;
}

KUrl::List RailsSwitchers::testsToSwitch()
{
    KUrl::List urls;

    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) return urls;

    QFileInfo file(activeDocument->url().toLocalFile());
    if (!file.exists()) return urls;

    QString ext = file.completeSuffix();
    QString name = file.baseName();
    QString switchTo = "";

    if (ext == "rjs" || ext == "rxml" || ext == "rhtml" || ext == "js.rjs" || ext == "xml.builder"
        || ext == "html.erb" || ext == "erb")
        switchTo = file.dir().dirName();
    else if (ext == "rb")
        switchTo = name.remove(QRegExp("_controller$")).remove(QRegExp("_controller_test$")).remove(QRegExp("_test$"));

    if (switchTo.isEmpty())
        return urls;

    if (switchTo.endsWith("s"))
        switchTo = switchTo.mid(0, switchTo.length() - 1);

    KUrl testsUrl = findRailsRoot(activeDocument->url());
    testsUrl.addPath("test");

    KUrl functionalTestsUrlS = testsUrl;
    functionalTestsUrlS.addPath("functional");
    functionalTestsUrlS.addPath(switchTo + "_controller_test.rb");
    if (QFile::exists(functionalTestsUrlS.toLocalFile()))
        urls << functionalTestsUrlS;

    KUrl functionalTestsUrlP = testsUrl;
    functionalTestsUrlP.addPath("functional");
    functionalTestsUrlP.addPath(switchTo + "s_controller_test.rb");
    if (QFile::exists(functionalTestsUrlP.toLocalFile()))
        urls << functionalTestsUrlP;

    KUrl integrationTestsUrlS = testsUrl;
    integrationTestsUrlS.addPath("integration");
    integrationTestsUrlS.addPath(switchTo + "_test.rb");
    if (QFile::exists(integrationTestsUrlS.toLocalFile()))
        urls << integrationTestsUrlS;

    KUrl integrationTestsUrlP = testsUrl;
    integrationTestsUrlP.addPath("integration");
    integrationTestsUrlP.addPath(switchTo + "s_test.rb");
    if (QFile::exists(integrationTestsUrlP.toLocalFile()))
        urls << integrationTestsUrlP;

    KUrl unitTestsUrlS = testsUrl;
    unitTestsUrlS.addPath("unit");
    unitTestsUrlS.addPath(switchTo + "_test.rb");
    if (QFile::exists(unitTestsUrlS.toLocalFile()))
        urls << unitTestsUrlS;

    KUrl unitTestsUrlP = testsUrl;
    unitTestsUrlP.addPath("unit");
    unitTestsUrlP.addPath(switchTo + "s_test.rb");
    if (QFile::exists(unitTestsUrlP.toLocalFile()))
        urls << unitTestsUrlP;

    return urls;
}

void RailsSwitchers::switchToTest()
{
    if (testsToSwitch().isEmpty())
        return;

    KDevelop::IQuickOpen* quickOpen = KDevelop::ICore::self()->pluginController()
        ->extensionForPlugin<KDevelop::IQuickOpen>("org.kdevelop.IQuickOpen");
    if (quickOpen) {
        kDebug(9047) << "   showing quickopen";
        quickOpen->showQuickOpen(QStringList() << i18n("Rails Tests"));
    }
}

}

#include "railsswitchers.moc"
