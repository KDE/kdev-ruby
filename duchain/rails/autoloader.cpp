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


#include <QtCore/QDir>
#include <language/duchain/indexedstring.h>
#include <duchain/rails/autoloader.h>


namespace Rails
{

KUrl AutoLoader::m_root;


QList<KDevelop::IndexedString> AutoLoader::computePaths(const KDevelop::IndexedString &path)
{
    QList<KDevelop::IndexedString> urls;
    QStringList dirs = path.str().split("/");
    const QString &name = dirs.last();

    fillUrlCache();
    dirs.removeLast();
    for (int i = dirs.size() - 1; i >= 0; --i) {
        if (dirs.at(i) == "models") {
            urls << KDevelop::IndexedString(getGem("active_record/base"));
            urls << getDir(m_root.path(KUrl::AddTrailingSlash) + "lib");
            return urls;
        } else if (dirs.at(i) == "controllers") {
            if (name == "application_controller.rb")
                urls << KDevelop::IndexedString(getGem("action_controller/base"));
            else
                urls << appController();
            urls << getDir(m_root.path(KUrl::AddTrailingSlash) + "lib");
            urls << getDir(m_root.path(KUrl::AddTrailingSlash) + "app/models");
            return urls;
        }
    }

    return urls;
}

QList<KDevelop::IndexedString> AutoLoader::getDir(const QString &path)
{
    QList<KDevelop::IndexedString> files;
    QDir dir(path);
    QStringList list = dir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    foreach (const QString &entry, list) {
        const QString &real = path + "/" + entry;
        QFileInfo info(real);
        if (info.isDir())
            files << getDir(real);
        else
            files << KDevelop::IndexedString(real);
    }
    return files;
}


} // End of namespace Rails
