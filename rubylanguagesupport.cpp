/*****************************************************************************
 * Copyright (c) 2006 Alexander Dymo <adymo@kdevelop.org>                    *
 *                                                                           *
 * Permission is hereby granted, free of charge, to any person obtaining     *
 * a copy of this software and associated documentation files (the           *
 * "Software"), to deal in the Software without restriction, including       *
 * without limitation the rights to use, copy, modify, merge, publish,       *
 * distribute, sublicense, and/or sell copies of the Software, and to        *
 * permit persons to whom the Software is furnished to do so, subject to     *
 * the following conditions:                                                 *
 *                                                                           *
 * The above copyright notice and this permission notice shall be            *
 * included in all copies or substantial portions of the Software.           *
 *                                                                           *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,           *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF        *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                     *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE    *
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION    *
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION     *
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.           *
 *****************************************************************************/

#include "rubylanguagesupport.h"

#include <kdebug.h>
#include <kcomponentdata.h>
#include <kstandarddirs.h>
#include <kpluginfactory.h>
#include <kpluginloader.h>

#include <interfaces/icore.h>
#include <interfaces/iproject.h>
#include <interfaces/idocument.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/ilanguagecontroller.h>
#include <project/projectmodel.h>
#include <language/backgroundparser/backgroundparser.h>

#include <QExtensionFactory>

#include "parsejob.h"

using namespace Ruby;

K_PLUGIN_FACTORY(KDevRubySupportFactory, registerPlugin<RubyLanguageSupport>(); )
K_EXPORT_PLUGIN(KDevRubySupportFactory("kdevrubysupport"))

RubyLanguageSupport* RubyLanguageSupport::m_self = 0;

RubyLanguageSupport::RubyLanguageSupport( QObject* parent,
                                          const QVariantList& /*args*/ )
        : KDevelop::IPlugin( KDevRubySupportFactory::componentData(), parent )
        , KDevelop::ILanguageSupport()
{
    KDEV_USE_EXTENSION_INTERFACE( KDevelop::ILanguageSupport )

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
