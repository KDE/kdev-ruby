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

#ifndef KDEVRUBYLANGUAGESUPPORT_H
#define KDEVRUBYLANGUAGESUPPORT_H

#include <interfaces/iplugin.h>
#include <language/interfaces/ilanguagesupport.h>

namespace KDevelop {
    class IDocument;
    class IProject;
}

class RubyLanguageSupport : public KDevelop::IPlugin, public KDevelop::ILanguageSupport
{
Q_OBJECT
Q_INTERFACES( KDevelop::ILanguageSupport )
public:
    RubyLanguageSupport( QObject *parent, const QVariantList& args = QVariantList() );
    virtual ~RubyLanguageSupport();

    virtual KDevelop::ParseJob* createParseJob(const KUrl&);

    virtual QString name() const;

    QStringList extensions() const;

private Q_SLOTS:
    void documentLoaded(KDevelop::IDocument *document);
    void documentClosed(KDevelop::IDocument *document);
    void projectOpened(KDevelop::IProject *project);
    void projectClosing(KDevelop::IProject *project);
    void documentChanged( KDevelop::IDocument* document );
    void documentActivated( KDevelop::IDocument* document );
};

#endif

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
