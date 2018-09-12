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


#ifndef INCLUDENAVIGATIONCONTEXT_H
#define INCLUDENAVIGATIONCONTEXT_H


#include <duchain/duchainexport.h>
#include <language/duchain/navigation/abstractincludenavigationcontext.h>


namespace ruby {

/**
 * @class IncludeNavigationContext
 *
 * The include navigation context for Ruby scripts.
 */
class KDEVRUBYDUCHAIN_EXPORT IncludeNavigationContext
    : public KDevelop::AbstractIncludeNavigationContext
{
public:
    /**
     * Constructor.
     *
     * @param item The include item in which we want to retrieve the info.
     * @param topContext The top context associated with the given item.
     */
    explicit IncludeNavigationContext(const KDevelop::IncludeItem &item,
                                      KDevelop::TopDUContextPointer topContext);

protected:
    /// Re-implemented from KDevelop::AbstractIncludeNavigationContext
    void getFileInfo(KDevelop::TopDUContext *duchain) override;

    /**
     * Re-implemented from KDevelop::AbstractIncludeNavigationContext to
     * prevent variable declarations to appear on the widget.
     */
    bool filterDeclaration(KDevelop::Declaration *decl) override;

    /**
     * Re-implemented from KDevelop::AbstractNavigationContext so we can also
     * show to the user if this declaration has some special meaning for
     * the Ruby interpreter.
     */
    QString declarationKind(const KDevelop::DeclarationPointer& decl) override;
};

}


#endif /* INCLUDENAVIGATIONCONTEXT_H */
