/*
 * This file is part of KDevelop
 *
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright (C) 2014-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#include <rails/dataprovider.h>

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

#include <klocalizedstring.h>

#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>

#include <rails/helpers.h>
#include <rails/switchers.h>

using namespace KDevelop;
using namespace ruby::rails;

DataProvider::DataProvider(Kind kind) : m_kind(kind)
{
    reset();
}

QStringList DataProvider::scopes()
{
    return QStringList{ QStringLiteral("Project") };
}

void DataProvider::setFilterText(const QString &text)
{
    setFilter(text.split('/'));
}

void DataProvider::reset()
{
    clearFilter();

    auto doc = ICore::self()->documentController()->activeDocument();

    QVector<Path> urlsToSwitch;
    if (m_kind == Kind::Views) {
        urlsToSwitch = Switchers::viewsToSwitch();
    } else if (m_kind == Kind::Tests) {
        urlsToSwitch = Switchers::testsToSwitch();
    }

    QVector<QuickOpenItem> items;
    items.reserve(urlsToSwitch.size());
    foreach (const Path &url, urlsToSwitch) {
        QuickOpenItem item;
        item.url = url.toUrl();
        if (doc) {
            item.originUrl = Path(doc->url()).toUrl();
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
    QString s;
    QuickOpenItem item(filteredItems()[row]);

    if (m_kind == Kind::Views) {
        s = i18n("View for:");
    } else {
        s = i18n("Test for:");
    }
    return QuickOpenDataPointer(new QuickOpenData(item, s));
}

void DataProvider::enableData(const QStringList &items,
                              const QStringList &scopes)
{
    QuickOpenDataProviderBase::enableData(items, scopes);
}

