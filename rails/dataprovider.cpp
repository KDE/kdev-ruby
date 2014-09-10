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
#include <QFileInfo>

#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>

#include <rails/switchers.h>
#include <rails/dataprovider.h>
#include <rails/helpers.h>


namespace Rails
{

DataProvider::DataProvider(Rails::DataProvider::Kind kind) : m_kind(kind)
{
    reset();
}

QStringList DataProvider::scopes()
{
    return QStringList() << QStringLiteral("Project");
}

void DataProvider::setFilterText(const QString &text)
{
    setFilter(text.split('/'));
}

void DataProvider::reset()
{
    clearFilter();

    KDevelop::IDocument *activeDocument = KDevelop::ICore::self()->documentController()->activeDocument();

    QVector<KDevelop::Path> urlsToSwitch;
    if (m_kind == Views) {
        urlsToSwitch = Switchers::viewsToSwitch();
    } else if (m_kind == Tests) {
        urlsToSwitch = Switchers::testsToSwitch();
    }

    QList<QuickOpenItem> items;
    foreach (const KDevelop::Path &url, urlsToSwitch) {
        QuickOpenItem item;
        item.url = url.toUrl();;
        if (activeDocument) {
            item.originUrl = KDevelop::Path(activeDocument->url()).toUrl();
        }
        items << item;
    }
    setItems(items);
}


uint DataProvider::itemCount() const
{
    return filteredItems().count();
}

uint DataProvider::unfilteredItemCount() const
{
    return items().count();
}

KDevelop::QuickOpenDataPointer DataProvider::data(uint row) const
{
    QuickOpenItem item(filteredItems()[row]);
    const QString &s = (m_kind == Views) ? i18n("View for:") : i18n("Test for:");
    return KDevelop::QuickOpenDataPointer(new QuickOpenData(item, s));
}

void DataProvider::enableData(const QStringList &items, const QStringList &scopes)
{
    KDevelop::QuickOpenDataProviderBase::enableData(items, scopes);
}

}

