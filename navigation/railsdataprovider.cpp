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
#include "railsdataprovider.h"

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

RailsQuickOpenData::RailsQuickOpenData(const RailsQuickOpenItem& item, const QString &explanation)
    : QuickOpenDataBase(), m_item(item), m_explanation(explanation)
{
}

QString RailsQuickOpenData::text() const
{
    KUrl u(m_item.url.url());
    return KUrl::relativeUrl( RailsSwitchers::findRailsRoot(m_item.url.url()), u );
}

QString RailsQuickOpenData::htmlDescription() const
{
    return "<small><small>" + m_explanation + ' ' + m_item.originUrl.fileName() + "</small></small>";
}

bool RailsQuickOpenData::execute(QString& filterText)
{
    KDevelop::ICore::self()->documentController()->openDocument( m_item.url );
    return true;
}

bool RailsQuickOpenData::isExpandable() const
{
    return false;
}

QWidget* RailsQuickOpenData::expandingWidget() const
{
    return KDevelop::QuickOpenDataBase::expandingWidget();
}

QIcon RailsQuickOpenData::icon() const
{
    return KDevelop::QuickOpenDataBase::icon();
}

QList<QVariant> RailsQuickOpenData::highlighting() const
{
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    QTextCharFormat normalFormat;

    QString txt = text();

    QList<QVariant> ret;

    int fileNameLength = m_item.url.fileName().length();

    ret << 0;
    ret << txt.length() - fileNameLength;
    ret << QVariant(normalFormat);
    ret << txt.length() - fileNameLength;
    ret << fileNameLength;
    ret << QVariant(boldFormat);

    return ret;
}



RailsDataProvider::RailsDataProvider(Ruby::RailsDataProvider::Kind kind): m_kind(kind)
{
    reset();
}

QList<KDevelop::QuickOpenDataPointer> RailsDataProvider::data(uint start, uint end) const
{
    if( end > (uint)Base::filteredItems().count() )
        end = Base::filteredItems().count();

    QList<KDevelop::QuickOpenDataPointer> ret;

    for( uint a = start; a < end; a++ ) {
        RailsQuickOpenItem f( Base::filteredItems()[a] );
        QString dataExplanation = m_kind == Views ? i18n("View for:") : i18n("Test for:");
        ret << KDevelop::QuickOpenDataPointer( new RailsQuickOpenData( Base::filteredItems()[a], dataExplanation ) );
    }

    return ret;
}

void RailsDataProvider::enableData(const QStringList& items, const QStringList& scopes)
{
    KDevelop::QuickOpenDataProviderBase::enableData(items, scopes);
}

uint RailsDataProvider::itemCount() const
{
    return Base::filteredItems().count();
}

void RailsDataProvider::reset()
{
    Base::clearFilter();

    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();

    QList<RailsQuickOpenItem> items;
    KUrl::List urlsToSwitch;
    if (m_kind == Views)
        urlsToSwitch = RailsSwitchers::viewsToSwitch();
    else if (m_kind == Tests)
        urlsToSwitch = RailsSwitchers::testsToSwitch();
    foreach (const KUrl &url, urlsToSwitch) {
        RailsQuickOpenItem item;
        item.url = url;
        if (activeDocument)
            item.originUrl = activeDocument->url();
        items << item;
    }
    setItems(items);
}

QStringList RailsDataProvider::scopes()
{
    return QStringList() << "Project";
}

void RailsDataProvider::setFilterText(const QString& text)
{
    Base::setFilter( text.split('/'), QChar('/') );
}

QString RailsDataProvider::itemText(const RailsQuickOpenItem& data) const
{
    return data.url.fileName();
}

QSet< KDevelop::IndexedString > RailsDataProvider::files() const
{
    return QSet< KDevelop::IndexedString >();
}

}
