/*
* This file is part of KDevelop
*
* Copyright 2007-2010 Alexander Dymo <adymo@kdevelop.org>
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

#include <rails/helpers.h>

using namespace KDevelop;
using namespace ruby::rails;

Path Helpers::findRailsRoot(const QUrl &url)
{
    Path current(url.toString());
    Path upUrl(current.parent());

    while (upUrl != current) {
        Path aux = upUrl.parent();
        if (aux.lastPathSegment() == QStringLiteral("app")) {
            const QString &dir = upUrl.lastPathSegment();
            if (dir == QStringLiteral("controllers") ||
                dir == QStringLiteral("models") ||
                dir == QStringLiteral("views")) {
                return aux.parent();
            }
        } else if (upUrl.lastPathSegment() == QStringLiteral("test")) {
            return aux;
        }
        current = upUrl;
        upUrl = aux;
    }
    return Path();
}

