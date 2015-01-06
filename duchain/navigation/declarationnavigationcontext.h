/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef DECLARATIONNAVIGATIONWIDGET_H
#define DECLARATIONNAVIGATIONWIDGET_H


#include <duchain/duchainexport.h>
#include <language/duchain/navigation/abstractdeclarationnavigationcontext.h>


namespace ruby {

class ModuleDeclaration;

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
    explicit DeclarationNavigationContext(KDevelop::DeclarationPointer decl,
                                          KDevelop::TopDUContextPointer topContext,
                                          KDevelop::AbstractNavigationContext *prevContext = nullptr);

protected:
    /**
     * Re-implemented from KDevelop::AbstractDeclarationNavigationContext
     * because the default implementation is just to "C++ centric".
     */
    virtual QString html(bool shorten = false) override;

    /**
     * Re-implemented from KDevelop::AbstractDeclarationNavigationContext
     * because the default implementation assumes that default arguments
     * are always at the end, and in Ruby this is not true.
     */
    virtual void htmlFunction() override;

    /**
     * Re-implemented from KDevelop::AbstractDeclarationNavigationContext so
     * we can improve the html to be rendered with Ruby-specific stuff.
     */
    virtual void htmlClass() override;

    /**
     * Re-implemented from KDevelop::AbstractNavigationContext so we can also
     * show to the user if he's looking at an internal (kernel) structure.
     *
     * @param name The given name.
     * @param declaration The involved declaration.
     * @param actionType Important if this is a JumpToSource action.
     */
    virtual void makeLink(const QString &name,
                          KDevelop::DeclarationPointer declaration,
                          KDevelop::NavigationAction::Type actionType) override;

private:
    /**
     * Add to the html all the info about module mixins that can be extracted
     * from the given declaration @p decl.
     */
    void addModuleMixins(ModuleDeclaration *decl);

    /**
     * Add to the html all the modules/classes that extend/include the
     * given module declaration @p decl.
     */
    void addMixers(ModuleDeclaration *decl);
};

}


#endif /* DECLARATIONNAVIGATIONWIDGET_H */
