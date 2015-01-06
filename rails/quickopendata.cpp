/*
 * This file is part of KDevelop
 *
 * Copyright (C) 2014-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <rails/quickopendata.h>

#include <QtGui/QIcon>
#include <QtGui/QTextCharFormat>

#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>

#include <rails/helpers.h>

using namespace ruby::rails;

QuickOpenData::QuickOpenData(const QuickOpenItem &item,
                             const QString &explanation)
    : QuickOpenDataBase()
    , m_item(item), m_explanation(explanation)
{
}

QString QuickOpenData::text() const
{
    const QString &item = m_item.url.toString();
    return KDevelop::Path(Helpers::findRailsRoot(m_item.url), item).path();
}

QString QuickOpenData::htmlDescription() const
{
    return "<small><small>" + m_explanation + ' '
            + m_item.originUrl.fileName() + "</small></small>";
}

bool QuickOpenData::execute(QString &filterText)
{
    Q_UNUSED(filterText);

    KDevelop::ICore::self()->documentController()->openDocument(m_item.url);
    return true;
}

bool QuickOpenData::isExpandable() const
{
    return false;
}

QWidget * QuickOpenData::expandingWidget() const
{
    return KDevelop::QuickOpenDataBase::expandingWidget();
}

QIcon QuickOpenData::icon() const
{
    return KDevelop::QuickOpenDataBase::icon();
}

QList<QVariant> QuickOpenData::highlighting() const
{
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);

    const QString &txt = text();
    int fileNameLength = m_item.url.fileName().length();

    return QList<QVariant>{
        0,
        txt.length() - fileNameLength,
        QVariant(QTextCharFormat()),
        txt.length() - fileNameLength,
        fileNameLength,
        QVariant(boldFormat)
    };
}

