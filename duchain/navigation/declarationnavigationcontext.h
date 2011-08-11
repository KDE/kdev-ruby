/* This file is part of KDevelop
 *
 * Copyright (C) 2011  Miquel Sabaté <mikisabate@gmail.com>
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


#ifndef DECLARATIONNAVIGATIONWIDGET_H
#define DECLARATIONNAVIGATIONWIDGET_H


#include <duchain/duchainexport.h>
#include <language/duchain/navigation/abstractdeclarationnavigationcontext.h>


namespace Ruby
{

/**
 * @class DeclarationNavigationContext
 *
 * This class extends KDevelop::AbstractDeclarationNavigationContext so we
 * can also show to the user some extra information.
 */
class KDEVRUBYDUCHAIN_EXPORT DeclarationNavigationContext
    : public KDevelop::AbstractDeclarationNavigationContext
{
public:
    /**
     * Constructor.
     *
     * @param decl The declaration pointer.
     * @param topContext The top context where this declaration is.
     * @param prevContext A pointer to the previous context.
     */
    DeclarationNavigationContext(KDevelop::DeclarationPointer decl,
                                 KDevelop::TopDUContextPointer topContext,
                                 KDevelop::AbstractNavigationContext *prevContext = 0);

protected:
    /**
     * Re-implemented from KDevelop::AbstractDeclarationNavigationContext so
     * we can improve the html to be rendered with Ruby-specific stuff.
     */
    virtual void htmlClass();

    /**
     * Re-implemented from KDevelop::AbstractNavigationContext so we can also
     * show to the user if he's looking at an internal (kernel) structure.
     *
     * @param name The given name.
     * @param declaration The involved declaration.
     * @param actionType Important if this is a JumpToSource action.
     */
    virtual void makeLink(const QString &name, KDevelop::DeclarationPointer declaration,
                          KDevelop::NavigationAction::Type actionType);

    /**
     * Re-implemented from KDevelop::AbstractNavigationContext so we can also
     * show to the user if this declaration has some special meaning for
     * the Ruby interpreter.
     *
     * @param decl The involved declaration.
     */
    virtual QString declarationKind(KDevelop::DeclarationPointer decl);

    /**
     * Re-implemented from KDevelop::AbstractDeclarationNavigationContext so
     * we can add some extra information about the identified type.
     */
    virtual void htmlIdentifiedType(KDevelop::AbstractType::Ptr type,
                                    const KDevelop::IdentifiedType *idType);
};

}


#endif /* DECLARATIONNAVIGATIONWIDGET_H */

