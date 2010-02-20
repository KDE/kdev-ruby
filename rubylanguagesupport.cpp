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
#include <project/projectmodel.h>
#include <language/interfaces/iquickopen.h>
#include <language/backgroundparser/backgroundparser.h>

#include <QExtensionFactory>

#include "parsejob.h"
#include "navigation/railsswitchers.h"
#include "navigation/viewsdataprovider.h"

using namespace Ruby;

K_PLUGIN_FACTORY(KDevRubySupportFactory, registerPlugin<RubyLanguageSupport>(); )
K_EXPORT_PLUGIN(KDevRubySupportFactory("kdevrubysupport"))

RubyLanguageSupport* RubyLanguageSupport::m_self = 0;

RubyLanguageSupport::RubyLanguageSupport( QObject* parent,
                                          const QVariantList& /*args*/ )
        : KDevelop::IPlugin( KDevRubySupportFactory::componentData(), parent )
        , KDevelop::ILanguageSupport()
        , m_railsSwitchers(new Ruby::RailsSwitchers(this))
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

    m_viewsQuickOpenDataProvider = new ViewsDataProvider();

    KDevelop::IQuickOpen* quickOpen = core()->pluginController()->extensionForPlugin<KDevelop::IQuickOpen>("org.kdevelop.IQuickOpen");
    if (quickOpen)
        quickOpen->registerProvider(ViewsDataProvider::scopes(), QStringList(i18n("Rails Views")), m_viewsQuickOpenDataProvider);
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

#include "rubylanguagesupport.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
