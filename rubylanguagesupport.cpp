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

#include <QExtensionFactory>
// from the parser subdirectory
#include <ruby_parser.h>

using namespace ruby;

K_PLUGIN_FACTORY(KDevRubySupportFactory, registerPlugin<RubyLanguageSupport>(); )
K_EXPORT_PLUGIN(KDevRubySupportFactory("kdevrubysupport"))

RubyLanguageSupport::RubyLanguageSupport( QObject* parent,
                                          const QVariantList& /*args*/ )
        : KDevelop::IPlugin( KDevRubySupportFactory::componentData(), parent )
        , KDevelop::ILanguageSupport()
{
    KDEV_USE_EXTENSION_INTERFACE( KDevelop::ILanguageSupport )
}

RubyLanguageSupport::~RubyLanguageSupport()
{
}

KDevelop::ParseJob* RubyLanguageSupport::createParseJob(const KUrl &/*url*/)
{
    // TODO
    return 0;
}

KDevelop::ILanguage* RubyLanguageSupport::language()
{
    return 0;
}

QString RubyLanguageSupport::name() const
{
    return "Ruby";
}

QStringList RubyLanguageSupport::extensions() const
{
    return QStringList() << "ILanguageSupport";
}

#include "rubylanguagesupport.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
