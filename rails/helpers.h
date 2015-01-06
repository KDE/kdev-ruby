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

#ifndef RAILS_HELPERS_H
#define RAILS_HELPERS_H

#include <rails/export.h>
#include <util/path.h>

namespace ruby {
namespace rails {

/**
 * @class Helpers
 *
 * This class contains common utilities for all the code across the
 * Rails namespace.
 */
class KDEVRUBYRAILS_EXPORT Helpers
{
public:
    /**
     * Finds the root directory of the Rails application. Not all the paths are
     * being looked up by this method, only the ones that the different
     * switchers might use: controllers, models, views and tests.
     *
     * @param url The current file or directory that is included inside a
     * Rails application.
     * @returns an invalid Path if an error has been found. Otherwise this
     * method returns a valid Path that points to the root of the Rails
     * application.
     */
    static KDevelop::Path findRailsRoot(const QUrl &url);
};

}
}

#endif // RAILS_HELPERS_H

