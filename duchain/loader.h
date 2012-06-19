/* This file is part of KDevelop
 *
 * Copyright (C) 2012  Miquel Sabaté <mikisabate@gmail.com>
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


// KDevelop
#include <language/duchain/declaration.h>

// Ruby
#include <duchain/duchainexport.h>
#include <parser/rubyast.h>


/*
 * TODO: this class is still under construction.
 */


namespace Ruby
{

class MethodDeclaration;
class EditorIntegrator;
using namespace KDevelop;

/**
 * @class Loader
 *
 * This class handles the ruby's require/require_relative statements. Ideally,
 * the programmer only wants to use the @p getRequiredFile() method in order
 * to require a file. This class implements a caching system to keep the
 * whole as optimal as possible.
 */
class KDEVRUBYDUCHAIN_EXPORT Loader
{
public:
    /**
     * Get the url of the file specified by a require statement.
     *
     * @param node The node containing the file to be required.
     * @param editor The EditorIntegrator from the current builder.
     * @param local Set to true if the required file is relative to the current
     * document (used for the require_relative statement).
     * @return a KUrl containing the path to the required file.
     */
    static KUrl getRequiredFile(Node *node, const EditorIntegrator *editor, bool local);

private:
    /// @return the list of urls available from ruby through $:
    static QPair<QList<KUrl>, QList<KUrl> > getSearchPaths();

    /// @returns true if the url cache has been filled with search paths.
    static inline bool urlsCached()
    {
        return !m_urlCache.first.isEmpty() || !m_urlCache.second.isEmpty();
    }

private:
    static QPair<QList<KUrl>, QList<KUrl> > m_urlCache;
};

} // End of namespace Ruby


#endif /* RUBY_LOADER_H */
