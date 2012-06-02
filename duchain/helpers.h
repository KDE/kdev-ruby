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


// KDevelop
#include <language/duchain/declaration.h>

// Ruby
#include <duchain/duchainexport.h>
#include <parser/rubyast.h>


namespace Ruby
{

class MethodDeclaration;
class EditorIntegrator;
using namespace KDevelop;

    /**
     * Get the url of the Ruby builtins file.
     *
     * @return A KDevelop::IndexedString that contains the url of the Ruby
     * builtins file.
     */
    KDEVRUBYDUCHAIN_EXPORT const IndexedString & internalBuiltinsFile();

    /**
     * Given a RubyAst, return its name.
     *
     * @param ast The given RubyAst.
     * @return A QString containing the name of the given RubyAst.
     */
    KDEVRUBYDUCHAIN_EXPORT const QString getName(RubyAst *ast);

    /**
     * Given a RubyAst, return the documentation comment.
     *
     * @param ast The given RubyAst.
     * @return a QByteArray containing the documentation comment for a
     * class/module/method definition if it's available. It will return
     * an empty QByteArray otherwise, or if the AST does not represent
     * the situations described above.
     */
    KDEVRUBYDUCHAIN_EXPORT const QByteArray getComment(RubyAst *ast);

    /**
     * Find the declaration for a specified node. If no declaration was found,
     * it will return NULL.
     *
     * @param id The qualified identifier that identifies our node.
     * @param range The range for this node.
     * @param context A pointer to the DUContext of this node.
     */
    KDEVRUBYDUCHAIN_EXPORT Declaration * getDeclaration(const QualifiedIdentifier &id,
                                                        const RangeInRevision &range,
                                                        DUContextPointer context);

    /**
     * Get the url of the file specified by a require statement.
     *
     * @param node The node containing the file to be required.
     * @param editor The EditorIntegrator from the current builder.
     * @param local Set to true if the required file is relative to the current
     * document (used for the require_relative statement).
     * @return a KUrl containing the path to the required file.
     */
    KDEVRUBYDUCHAIN_EXPORT KUrl getRequiredFile(Node *node, const EditorIntegrator *editor, bool local);

    /**
     * @return the list of urls available from ruby through $:
     */
    KDEVRUBYDUCHAIN_EXPORT QPair<QList<KUrl>, QList<KUrl> > getSearchPaths();

    /**
     * @returns the declared methods inside the given declaration @p decl,
     * which is a class or a module.
     */
    KDEVRUBYDUCHAIN_EXPORT QList<MethodDeclaration *> getDeclaredMethods(Declaration *decl);

    /**
     * @returns true if the given @p type is useful, and false otherwise.
     */
    KDEVRUBYDUCHAIN_EXPORT bool isUsefulType(AbstractType::Ptr type);

    /**
     * @returns a new type which is a merge of the two given types @p type
     * and @p newType.
     */
    KDEVRUBYDUCHAIN_EXPORT AbstractType::Ptr mergeTypes(AbstractType::Ptr type, AbstractType::Ptr newType);

    /// @returns the number of nodes that are next to the given @p node.
    KDEVRUBYDUCHAIN_EXPORT int nodeListSize(Node *node);

} // End of namespace Ruby


#endif /* RUBYDUCHAINHELPERS_H_ */

