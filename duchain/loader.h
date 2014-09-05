/* This file is part of KDevelop
 *
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#ifndef RUBY_LOADER_H
#define RUBY_LOADER_H


#include <util/path.h>
#include <language/duchain/declaration.h>
#include <language/util/includeitem.h>
#include <duchain/duchainexport.h>


namespace Ruby
{

class EditorIntegrator;

/**
 * @class Loader
 *
 * This class handles the ruby's require/require_relative statements. This
 * class implements a caching system to keep the whole thing as
 * optimal as possible.
 */
class KDEVRUBYDUCHAIN_EXPORT Loader
{
public:
    /**
     * Get the url of the file specified by a require statement.
     *
     * @param node The node containing the file to be required. Note that the
     * node's kind *must* be token_string.
     * @param editor The EditorIntegrator from the current builder.
     * @param local Set to true if the required file is relative to the current
     * document (used for the require_relative statement).
     * @returns a KDevelop::Path containing the path to the required file.
     */
    static KDevelop::Path getRequiredFile(Node *node,
                                          const EditorIntegrator *editor,
                                          bool local);

    /**
     * Get all the files/directories inside the given directory except for
     * (UNIX) hidden files, backup files (that end with ~) and .so files.
     *
     * @param url the url where to search.
     * @param hint The following text on the Completion context.
     * @param relative the absolute path of the directory that contains the
     * current file. If set, all the items returned are relative to the given
     * path.
     * @returns a list of IncludeItem's containing all the files/directories
     * that fit the given parameters.
     */
    static QList<KDevelop::IncludeItem> getFilesInSearchPath(const QString &url,
                                                             const QString &hint,
                                                             const QUrl &relative = QUrl());

protected:
    /**
     * Get the path for the given gem name.
     *
     * @param name The given gem name.
     * @returns the path for the given gem name.
     * @note that it assumes that it does not end with ".rb".
     */
    static KDevelop::Path getGem(const QString &name);

    /**
     * Fill the m_urlCache attribute with the urls available from Ruby
     * through $:
     */
    static void fillUrlCache();

private:
    /// @returns true if the url cache has been filled with search paths.
    static inline bool urlsCached()
    {
        return !m_rubyPath.isEmpty() || !m_gemPath.isEmpty();
    }

protected:
    /**
     * The cache of search paths. The m_rubyPath attribute is the list of
     * search paths for the Ruby standard library. The m_gemPath attribute
     * is the list of search paths for the gems.
     */
    static QList<KDevelop::Path> m_rubyPath;
    static QList<KDevelop::Path> m_gemPath;
};

} // End of namespace Ruby


#endif /* RUBY_LOADER_H */
