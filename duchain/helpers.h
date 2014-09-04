/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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
#include <parser/ast.h>


namespace Ruby
{

class MethodDeclaration;
class EditorIntegrator;
using namespace KDevelop;

    /**
     * The kind for the declaration to be fetched in the getDeclaration
     * and the getDeclarationFromPST methods.
     */
    enum DeclarationKind {
        Unknown         = 0, /// We don't care about the declaration kind.
        ClassMethod     = 1, /// It has to be a class method.
        InstanceMethod  = 2, /// It has to be an instance method.
        Module          = 3, /// It has to be a module.
        Class           = 4, /// It has to be a class.
        Local           = 5, /// Anything that is local (imported included).
    };

    /**
     * Get the url of the Ruby builtins file.
     *
     * @return A KDevelop::IndexedString that contains the url of the Ruby
     * builtins file.
     */
    KDEVRUBYDUCHAIN_EXPORT const IndexedString & internalBuiltinsFile();

    /**
     * Given a Ast, return its name.
     *
     * @param ast The given Ast.
     * @return A QString containing the name of the given Ast.
     */
    KDEVRUBYDUCHAIN_EXPORT const QString getName(Ast *ast);

     /**
      * Given a Ast, return the documentation comment.
      *
      * @param ast The given Ast.
      * @return a QByteArray containing the documentation comment for a
      * class/module/method definition if it's available. It will return
      * an empty QByteArray otherwise, or if the AST does not represent
      * the situations described above.
      */
    KDEVRUBYDUCHAIN_EXPORT const QByteArray getComment(Ast *ast);

    /**
     * Find a specified declaration.
     *
     * @param id The qualified identifier of the declaration.
     * @param range The range of the declaration.
     * @param context The current context.
     * @param kind The kind of the declaration.
     * @note The given context has to be valid.
     * @note This method already acquires a read lock for the DUChain.
     */
    KDEVRUBYDUCHAIN_EXPORT DeclarationPointer getDeclaration(const QualifiedIdentifier &id,
                                                             const RangeInRevision &range,
                                                             const DUContextPointer &context,
                                                             DeclarationKind kind = DeclarationKind::Unknown);

    /**
     * Find a declaration from the Persistent Symbol Table.
     *
     * @param id The qualified indentifier of the declaration.
     * @param context The current context.
     * @param kind The kind of the declaration.
     * @returns the first declaration that matches the given parameters from
     * the Persistent Symbol Table.
     * @note The given context has to be valid.
     * @note This method already acquires a write lock for the DUChain.
     */
    KDEVRUBYDUCHAIN_EXPORT DeclarationPointer getDeclarationFromPST(const QualifiedIdentifier &id,
                                                                    const DUContextPointer &context,
                                                                    DeclarationKind kind = DeclarationKind::Unknown);

    /**
     * Get the required builtin type.
     *
     * @param desc The name of the builtin type.
     * @param ctx The context where this type is available.
     * @returns a TypePtr< AbstractType > containing the required type or null
     * if it was not found.
     * @note The given context has to be valid.
     * @note This method already acquires a read lock for the DUChain.
     */
    KDEVRUBYDUCHAIN_EXPORT TypePtr<AbstractType> getBuiltinsType(const QString &desc, const DUContext *ctx);

    /**
     * Get the context of the Class class.
     *
     * @param ctx The current context.
     * @returns a KDevelop::DUContext containing the Class class.
     * @note The given context has to be valid.
     * @note This method already acquires a read lock for the DUChain.
     */
    KDEVRUBYDUCHAIN_EXPORT KDevelop::DUContext * getClassContext(const DUContext *ctx);

    /**
     * @returns true if the given @p type is useful, and false otherwise.
     */
    KDEVRUBYDUCHAIN_EXPORT bool isUsefulType(const AbstractType::Ptr &type);

    /**
     * @returns a new type which is a merge of the two given types @p type
     * and @p newType.
     */
    KDEVRUBYDUCHAIN_EXPORT AbstractType::Ptr mergeTypes(AbstractType::Ptr type, AbstractType::Ptr newType);

    /**
     * @returns the number of nodes that are next to the given @p node.o
     * @note Try to avoid this function since it iterates over all the list.
     */
    KDEVRUBYDUCHAIN_EXPORT int nodeListSize(Node *node);

    /// @returns the QualifiedIdentifier of the given @p ast.
    KDEVRUBYDUCHAIN_EXPORT const KDevelop::QualifiedIdentifier getIdentifier(const Ast *ast);

}


#endif /* RUBYDUCHAINHELPERS_H_ */
