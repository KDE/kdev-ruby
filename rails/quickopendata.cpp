/*
* This file is part of KDevelop
*
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


#include <QIcon>
#include <QTextCharFormat>

#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>

#include <rails/quickopendata.h>
#include <rails/helpers.h>


namespace Rails
{

QuickOpenData::QuickOpenData(const QuickOpenItem &item, const QString &explanation)
    : QuickOpenDataBase(), m_item(item), m_explanation(explanation)
{
    /* There's nothing to do here. */
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
    QTextCharFormat normalFormat;

    const QString &txt = text();
    int fileNameLength = m_item.url.fileName().length();

    QList<QVariant> ret;
    ret << 0;
    ret << txt.length() - fileNameLength;
    ret << QVariant(normalFormat);
    ret << txt.length() - fileNameLength;
    ret << fileNameLength;
    ret << QVariant(boldFormat);
    return ret;
}

}

