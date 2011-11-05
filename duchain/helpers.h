/* This file is part of KDevelop
 *
 * Copyright (C) 2011 Miquel Sabaté <mikisabate@gmail.com>
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


#ifndef RUBYDUCHAINHELPERS_H_
#define RUBYDUCHAINHELPERS_H_


#include <language/duchain/declaration.h>

#include <duchain/duchainexport.h>
#include <parser/rubyast.h>


namespace Ruby
{
    using namespace KDevelop;

    /**
     * Get the url of the Ruby builtins file.
     *
     * @return A KDevelop::IndexedString that contains the url of the Ruby
     * builtins file.
     */
    KDEVRUBYDUCHAIN_EXPORT const IndexedString &internalBuiltinsFile();

    /**
     * Given a RubyAst, return its name.
     *
     * @param ast The given RubyAst.
     * @return A QString containing the name of the given RubyAst.
     */
    KDEVRUBYDUCHAIN_EXPORT const QString getName(RubyAst *ast);

    /**
     * Find the declaration for a specified node. If no declaration was found,
     * it will return NULL.
     *
     * @param id The qualified identifier that identifies our node.
     * @param range The range for this node.
     * @param context A pointer to the DUContext of this node.
     */
    KDEVRUBYDUCHAIN_EXPORT Declaration *declarationForNode(const QualifiedIdentifier &id,
                                                           const RangeInRevision &range,
                                                           DUContextPointer context);

} // End of namespace Ruby


#endif /* RUBYDUCHAINHELPERS_H_ */

