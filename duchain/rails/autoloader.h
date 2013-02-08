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


#ifndef RAILS_AUTOLOADER_H
#define RAILS_AUTOLOADER_H


#include <duchain/loader.h>


namespace Rails
{

/**
 * @class AutoLoader
 *
 * This class implements de "auto-require" feature. That is, it does all the
 * requiring for Rails projects. It's implemented in a way as it's as optimal
 * as possible.
 */
class KDEVRUBYDUCHAIN_EXPORT AutoLoader : public Ruby::Loader
{
public:
    /**
     * Compute all the paths to require for the given path.
     *
     * @param path The given path.
     * @returns a QList of KDevelop::IndexedString containing all the paths
     * to be required later on.
     */
    static QList<KDevelop::IndexedString> computePaths(const KDevelop::IndexedString &path);

    /// Set the project root to the given @p url.
    inline static void setProjectRoot(const KUrl &url)
    {
        m_root = url;
    }

private:
    /// @returns the absoulte path to the application controller.
    inline static KDevelop::IndexedString appController()
    {
        return KDevelop::IndexedString(m_root.path(KUrl::AddTrailingSlash) +
               "app/controllers/application_controller.rb");
    }

    /**
     * Get all the files inside the given directory path. Note that this
     * is a recursive function, and files inside subdirectories will
     * also be retrieved.
     *
     * @param path The directory path.
     * @returns recursively all the files inside the given directory path.
     */
    static QList<KDevelop::IndexedString> getDir(const QString &path);

private:
    /// The root directory for the project.
    static KUrl m_root;
};

} // End of namespace Rails


#endif /* RAILS_AUTOLOADER_H */
