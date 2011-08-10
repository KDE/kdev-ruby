/* This file is part of KDevelop
 *
 * Copyright (C) 2011  Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H


#include <duchain/duchainexport.h>
#include <language/duchain/navigation/abstractnavigationwidget.h>

/*
 * WARNING: this file is under development
 */

namespace KDevelop { struct IncludeItem; }

namespace Ruby
{

class KDEVRUBYDUCHAIN_EXPORT NavigationWidget : public KDevelop::AbstractNavigationWidget
{
    Q_OBJECT

public:
    NavigationWidget(KDevelop::DeclarationPointer decl,
                     KDevelop::TopDUContextPointer topContext,
                     const QString &htmlPrefix = QString(),
                     const QString &htmlSuffix = QString());

    NavigationWidget(const KDevelop::IncludeItem &item,
                     KDevelop::TopDUContextPointer topContext,
                     const QString &htmlPrefix = QString(),
                     const QString &htmlSuffix = QString());

    /*
     * TODO: I find interesting the way that the PHP plugin
     * handles "magic" constants :D
     */

    static QString shortDescription(KDevelop::Declaration *decl);
    static QString shortDescription(KDevelop::IncludeItem &item);
};

}


#endif // NAVIGATIONWIDGET_H

