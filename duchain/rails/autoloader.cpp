/*
 * This file is part of KDevelop
 *
 * Copyright 2012 Miquel Sabaté <mikisabate@gmail.com>
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


#include <duchain/rails/autoloader.h>
#include <language/duchain/indexedstring.h>

#include <KUrl> // TODO: remove ?
#include <QtCore/QStringList>
#include <KDebug>
#include <duchain/loader.h>
#include <rubydefs.h>

namespace Rails
{

KUrl AutoLoader::m_projectRoot;


QList<KDevelop::IndexedString> AutoLoader::computePaths(const KDevelop::IndexedString &path)
{
    QList<KDevelop::IndexedString> urls;
    QStringList dirs = path.str().split("/");

    fillUrlCache();

    dirs.removeLast();
    // TODO: can be optimized to leave earlier.
    for (int i = dirs.size() - 1; i >= 0; --i) {
        if (dirs.at(i) == "models") {
            // TODO: provisional hack
            urls << KDevelop::IndexedString(getGem("active_record/base"));
            return urls;
        } else if (dirs.at(i) == "controllers") {
            debug() << "It's a controller";
        }
    }
//     foreach (const QString &str, dirs) {
//         if (str ==
//     }

    // TODO: do magic.

    return urls;
}

} // End of namespace Rails
