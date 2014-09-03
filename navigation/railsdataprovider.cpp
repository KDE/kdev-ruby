/*
* This file is part of KDevelop
*
* Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
* Copyright 2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#include <QDir>
#include <QIcon>
#include <QFileInfo>
#include <QTextCharFormat>
#include <KLocale>

#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>

#include <navigation/railsswitchers.h>
#include <navigation/railsdataprovider.h>


namespace Ruby {

RailsQuickOpenData::RailsQuickOpenData(const RailsQuickOpenItem& item, const QString &explanation)
    : QuickOpenDataBase(), m_item(item), m_explanation(explanation)
{
}

QString RailsQuickOpenData::text() const
{
    QUrl u = m_item.url.path();
    QUrl base = RailsSwitchers::findRailsRoot(m_item.url);
    return base.path() + "/" + u.path();
}

QString RailsQuickOpenData::htmlDescription() const
{
    return "<small><small>" + m_explanation + ' ' + m_item.originUrl.fileName() + "</small></small>";
}

/* TODO: to adymo from mssola: what is this parameter ? */
bool RailsQuickOpenData::execute(QString & filterText)
{
    Q_UNUSED(filterText);
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

KDevelop::QuickOpenDataPointer RailsDataProvider::data(uint row) const
{
    RailsQuickOpenItem item( filteredItems()[row] );
    QString dataExplanation = m_kind == Views ? i18n("View for:") : i18n("Test for:");
    return KDevelop::QuickOpenDataPointer( new RailsQuickOpenData( item, dataExplanation ) );
}

void RailsDataProvider::enableData(const QStringList& items, const QStringList& scopes)
{
    KDevelop::QuickOpenDataProviderBase::enableData(items, scopes);
}

uint RailsDataProvider::itemCount() const
{
    return filteredItems().count();
}

uint RailsDataProvider::unfilteredItemCount() const
{
    return items().count();
}

void RailsDataProvider::reset()
{
    clearFilter();

    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();

    QList<RailsQuickOpenItem> items;
    QList<QUrl> urlsToSwitch;
    if (m_kind == Views) {
        urlsToSwitch = RailsSwitchers::viewsToSwitch();
    } else if (m_kind == Tests) {
        urlsToSwitch = RailsSwitchers::testsToSwitch();
    }
    foreach (const QUrl &url, urlsToSwitch) {
        RailsQuickOpenItem item;
        item.url = url;
        if (activeDocument) {
            item.originUrl = activeDocument->url();
        }
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
    setFilter( text.split('/') );
}

QString RailsDataProvider::itemText(const RailsQuickOpenItem& data) const
{
    return data.url.fileName();
}

}
