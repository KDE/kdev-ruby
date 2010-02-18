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

#include "interfaces/icore.h"
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

void RailsSwitchers::switchToTest()
{

}

void RailsSwitchers::switchToView()
{

}

}

#include "railsswitchers.moc"
