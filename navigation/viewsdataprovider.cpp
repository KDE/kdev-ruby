/*
* This file is part of KDevelop
*
* Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
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
#include "viewsdataprovider.h"

#include <QDir>
#include <QIcon>
#include <QFileInfo>
#include <QTextCharFormat>

#include <klocale.h>

#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>
#include <language/duchain/indexedstring.h>

#include "railsswitchers.h"

namespace Ruby {

ViewData::ViewData(const ViewItem& view)
    : QuickOpenDataBase(), m_view(view)
{
}

QString ViewData::text() const
{
    KUrl u(m_view.url.url());
    return KUrl::relativeUrl( RailsSwitchers::findRailsRoot(m_view.url.url()), u );
}

QString ViewData::htmlDescription() const
{
    return "<small><small>" + i18n("View for ") + ' ' + m_view.originUrl.fileName() + "</small></small>";
}

bool ViewData::execute(QString& filterText)
{
    KDevelop::ICore::self()->documentController()->openDocument( m_view.url );
    return true;
}

bool ViewData::isExpandable() const
{
    return false;
}

QWidget* ViewData::expandingWidget() const
{
    return KDevelop::QuickOpenDataBase::expandingWidget();
}

QIcon ViewData::icon() const
{
    return KDevelop::QuickOpenDataBase::icon();
}

QList<QVariant> ViewData::highlighting() const
{
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    QTextCharFormat normalFormat;

    QString txt = text();

    QList<QVariant> ret;

    int fileNameLength = m_view.url.fileName().length();

    ret << 0;
    ret << txt.length() - fileNameLength;
    ret << QVariant(normalFormat);
    ret << txt.length() - fileNameLength;
    ret << fileNameLength;
    ret << QVariant(boldFormat);

    return ret;
}



ViewsDataProvider::ViewsDataProvider()
{
    reset();
}

QList<KDevelop::QuickOpenDataPointer> ViewsDataProvider::data(uint start, uint end) const
{
    if( end > (uint)KDevelop::FilterWithSeparator<ViewItem>::filteredItems().count() )
        end = KDevelop::FilterWithSeparator<ViewItem>::filteredItems().count();

    QList<KDevelop::QuickOpenDataPointer> ret;

    for( uint a = start; a < end; a++ ) {
        ViewItem f( KDevelop::FilterWithSeparator<ViewItem>::filteredItems()[a] );
        ret << KDevelop::QuickOpenDataPointer( new ViewData( KDevelop::FilterWithSeparator<ViewItem>::filteredItems()[a] ) );
    }

    return ret;


    return QList<KDevelop::QuickOpenDataPointer>();
}

void ViewsDataProvider::enableData(const QStringList& items, const QStringList& scopes)
{
    KDevelop::QuickOpenDataProviderBase::enableData(items, scopes);
}

uint ViewsDataProvider::itemCount() const
{
    return KDevelop::FilterWithSeparator<ViewItem>::filteredItems().count();
}

void ViewsDataProvider::reset()
{
    KDevelop::FilterWithSeparator<ViewItem>::clearFilter();

    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();

    QList<ViewItem> views;
    foreach (const KUrl &url, RailsSwitchers::viewsToSwitch()) {
        ViewItem viewItem;
        viewItem.url = url;
        if (activeDocument)
            viewItem.originUrl = activeDocument->url();
        views << viewItem;
    }
    setItems(views);
}

QStringList ViewsDataProvider::scopes()
{
    return QStringList() << "Project";
}

void ViewsDataProvider::setFilterText(const QString& text)
{
    KDevelop::FilterWithSeparator<ViewItem>::setFilter( text.split('/'), QChar('/') );
}

QString ViewsDataProvider::itemText(const ViewItem& data) const
{
    return data.url.fileName();
}

QSet< KDevelop::IndexedString > ViewsDataProvider::files() const
{
    return QSet< KDevelop::IndexedString >();
}

}
