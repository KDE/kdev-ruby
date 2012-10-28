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


/*
 * TODO: Cache Rails classes ¿ and paths ?
 */


#include <QtCore/QList> // TODO
#include <KUrl>
#include <duchain/duchainexport.h>
#include <duchain/loader.h>

class KUrl;

namespace KDevelop {
    class IndexedString;
}

namespace Rails
{

class KDEVRUBYDUCHAIN_EXPORT AutoLoader : public Ruby::Loader
{
public:
    static QList<KDevelop::IndexedString> computePaths(const KDevelop::IndexedString &path);

    inline static void setProjectRoot(const KUrl &url)
    {
        m_root = url;
    }

    inline static KDevelop::IndexedString appController()
    {
        return KDevelop::IndexedString(m_root.path(KUrl::AddTrailingSlash) +
               "app/controllers/application_controller.rb");
    }

private:
    static QList<KDevelop::IndexedString> getDir(const QString &path);

private:
    static KUrl m_root;
};

} // End of namespace Rails


#endif /* RAILS_AUTOLOADER_H */
