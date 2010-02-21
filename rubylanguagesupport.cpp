/*
* This file is part of KDevelop
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
#include "rubylanguagesupport.h"

#include <kdebug.h>
#include <klocale.h>
#include <kaction.h>
#include <kcomponentdata.h>
#include <kstandarddirs.h>
#include <kpluginfactory.h>
#include <kpluginloader.h>
#include <kactioncollection.h>

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
#include <language/backgroundparser/backgroundparser.h>

#include <QExtensionFactory>

#include "parsejob.h"
#include "navigation/railsswitchers.h"
#include "navigation/railsdataprovider.h"

using namespace Ruby;

#define RUBY_FILE_LAUNCH_CONFIGURATION_NAME i18n("Current Ruby File")

K_PLUGIN_FACTORY(KDevRubySupportFactory, registerPlugin<RubyLanguageSupport>(); )
K_EXPORT_PLUGIN(KDevRubySupportFactory("kdevrubysupport"))

RubyLanguageSupport* RubyLanguageSupport::m_self = 0;

RubyLanguageSupport::RubyLanguageSupport( QObject* parent,
                                          const QVariantList& /*args*/ )
        : KDevelop::IPlugin( KDevRubySupportFactory::componentData(), parent )
        , KDevelop::ILanguageSupport()
        , m_railsSwitchers(new Ruby::RailsSwitchers(this))
        , m_rubyFileLaunchConfiguration(0)
{
    KDEV_USE_EXTENSION_INTERFACE( KDevelop::ILanguageSupport )
    setXMLFile( "kdevrubysupport.rc" );

    m_self = this;

    connect( core()->documentController(), SIGNAL( documentLoaded( KDevelop::IDocument* ) ),
             this, SLOT( documentLoaded( KDevelop::IDocument* ) ) );
    connect( core()->documentController(), SIGNAL( documentClosed( KDevelop::IDocument* ) ),
             this, SLOT( documentClosed( KDevelop::IDocument* ) ) );
    connect( core()->documentController(), SIGNAL( documentStateChanged( KDevelop::IDocument* ) ),
             this, SLOT( documentChanged( KDevelop::IDocument* ) ) );
    connect( core()->documentController(), SIGNAL( documentContentChanged( KDevelop::IDocument* ) ),
             this, SLOT( documentChanged( KDevelop::IDocument* ) ) );
    connect( core()->documentController(), SIGNAL( documentActivated( KDevelop::IDocument* ) ),
             this, SLOT( documentActivated( KDevelop::IDocument* ) ) );
    connect( core()->projectController(), SIGNAL( projectOpened( KDevelop::IProject* ) ),
             this, SLOT( projectOpened( KDevelop::IProject* ) ) );
    connect( core()->projectController(), SIGNAL( projectClosing( KDevelop::IProject* ) ),
             this, SLOT( projectClosing( KDevelop::IProject* ) ) );

    KActionCollection* actions = actionCollection();
    KAction *action = actions->addAction("ruby_switch_to_controller");
    action->setText(i18n("Switch To Controller"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_1);
    connect(action, SIGNAL(triggered(bool)), m_railsSwitchers, SLOT(switchToController()));

    action = actions->addAction("ruby_switch_to_model");
    action->setText(i18n("Switch To Model"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_2);
    connect(action, SIGNAL(triggered(bool)), m_railsSwitchers, SLOT(switchToModel()));

    action = actions->addAction("ruby_switch_to_view");
    action->setText(i18n("Switch To View"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_3);
    connect(action, SIGNAL(triggered(bool)), m_railsSwitchers, SLOT(switchToView()));

    action = actions->addAction("ruby_switch_to_test");
    action->setText(i18n("Switch To Test"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_4);
    connect(action, SIGNAL(triggered(bool)), m_railsSwitchers, SLOT(switchToTest()));

    action = actions->addAction("ruby_run_current_file");
    action->setText(i18n("Run Current File"));
    action->setShortcut(Qt::META | Qt::Key_F9);
    connect(action, SIGNAL(triggered(bool)), this, SLOT(runCurrentFile()));

    m_viewsQuickOpenDataProvider = new RailsDataProvider(Ruby::RailsDataProvider::Views);
    m_testsQuickOpenDataProvider = new RailsDataProvider(Ruby::RailsDataProvider::Tests);

    KDevelop::IQuickOpen* quickOpen = core()->pluginController()->extensionForPlugin<KDevelop::IQuickOpen>("org.kdevelop.IQuickOpen");
    if (quickOpen) {
        quickOpen->registerProvider(RailsDataProvider::scopes(), QStringList(i18n("Rails Views")), m_viewsQuickOpenDataProvider);
        quickOpen->registerProvider(RailsDataProvider::scopes(), QStringList(i18n("Rails Tests")), m_testsQuickOpenDataProvider);
    }
}

RubyLanguageSupport::~RubyLanguageSupport()
{
}

RubyLanguageSupport* RubyLanguageSupport::self()
{
    return m_self;
}

KDevelop::ParseJob* RubyLanguageSupport::createParseJob(const KUrl &url)
{
    return new SimpleParseJob(url, this);
}

QString RubyLanguageSupport::name() const
{
    return "Ruby";
}

QStringList RubyLanguageSupport::extensions() const
{
    return QStringList() << "ILanguageSupport";
}

void RubyLanguageSupport::documentActivated(KDevelop::IDocument * document)
{
    Q_UNUSED(document)
}

void RubyLanguageSupport::documentLoaded(KDevelop::IDocument *document)
{
    kDebug() << "loaded document";
    core()->languageController()->backgroundParser()->addDocument(document->url());
}

void RubyLanguageSupport::documentClosed(KDevelop::IDocument *document)
{
    Q_UNUSED(document)
}

void RubyLanguageSupport::projectOpened(KDevelop::IProject *project)
{
    //parse project files
    KDevelop::BackgroundParser *parser = core()->languageController()->backgroundParser();
    foreach (const KDevelop::ProjectFileItem *file, project->files())
        parser->addDocument(file->url());
}

void RubyLanguageSupport::projectClosing(KDevelop::IProject *project)
{
    Q_UNUSED(project)
}

void RubyLanguageSupport::documentChanged(KDevelop::IDocument *document)
{
    kDebug() << "loaded document";
    core()->languageController()->backgroundParser()->addDocument(document->url());
}

void RubyLanguageSupport::runCurrentFile()
{
    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!activeDocument) return;

    //todo: adymo: check that this file is actually a ruby source
    //todo: adymo: disable this action in the UI if current file is not a ruby source

    if (!m_rubyFileLaunchConfiguration) {
        foreach (KDevelop::ILaunchConfiguration *config, core()->runController()->launchConfigurations()) {
            if (config->name() == RUBY_FILE_LAUNCH_CONFIGURATION_NAME) {
                m_rubyFileLaunchConfiguration = config;
                break;
            }
        }
        if (!m_rubyFileLaunchConfiguration) {
            IExecutePlugin* executePlugin = core()->pluginController()->pluginForExtension("org.kdevelop.IExecutePlugin")->extension<IExecutePlugin>();
            KDevelop::LaunchConfigurationType* type = core()->runController()->launchConfigurationTypeForId(executePlugin->nativeAppConfigTypeId());
            if (!type) return;

            KDevelop::ILaunchMode* mode = core()->runController()->launchModeForId("execute");
            if (!mode) return;

            KDevelop::ILauncher *launcher = 0;
            foreach (KDevelop::ILauncher *l, type->launchers()) {
                if (l->supportedModes().contains("execute"))
                    launcher = l;
            }
            if (!launcher) return;

            m_rubyFileLaunchConfiguration = core()->runController()->createLaunchConfiguration(
                type, qMakePair( mode->id(), launcher->id() ), 0, RUBY_FILE_LAUNCH_CONFIGURATION_NAME);

            KConfigGroup cfg = m_rubyFileLaunchConfiguration->config();
            cfg.writeEntry("isExecutable", true);
            cfg.writeEntry("Executable", "ruby");
            cfg.sync();
        }

    }
    KConfigGroup cfg = m_rubyFileLaunchConfiguration->config();
    KUrl railsRoot = RailsSwitchers::findRailsRoot(activeDocument->url());
    if (!railsRoot.isEmpty())
        cfg.writeEntry("Working Directory", railsRoot);
    else
        cfg.writeEntry("Working Directory", activeDocument->url().directory());
    cfg.writeEntry("Arguments", QStringList() << activeDocument->url().toLocalFile());
    cfg.sync();

    core()->runController()->execute("execute", m_rubyFileLaunchConfiguration);
}

#include "rubylanguagesupport.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
