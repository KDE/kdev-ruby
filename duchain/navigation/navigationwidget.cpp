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


#include <duchain/navigation/navigationwidget.h>
#include <duchain/navigation/declarationnavigationcontext.h>
#include <duchain/navigation/includenavigationcontext.h>


namespace ruby
{
using namespace KDevelop;

NavigationWidget::NavigationWidget( KDevelop::DeclarationPointer decl,
                                    KDevelop::TopDUContextPointer topContext,
                                    KDevelop::AbstractNavigationWidget::DisplayHints hints)
{
    setDisplayHints(hints);
    initBrowser(200);

    auto context = NavigationContextPointer(new DeclarationNavigationContext(decl, topContext));
    setContext(context);
}

NavigationWidget::NavigationWidget(const KDevelop::IncludeItem &item,
                                   KDevelop::TopDUContextPointer topContext,
                                   KDevelop::AbstractNavigationWidget::DisplayHints hints)
{
    setDisplayHints(hints);
    initBrowser(200);

    auto context = NavigationContextPointer(new IncludeNavigationContext(item, topContext));
    setContext(context);
}

QString NavigationWidget::shortDescription(KDevelop::Declaration *decl)
{
    NavigationContextPointer ctx(new DeclarationNavigationContext(DeclarationPointer(decl), TopDUContextPointer()));
    return ctx->html(true);
}

QString NavigationWidget::shortDescription(const KDevelop::IncludeItem &item)
{
    NavigationContextPointer ctx(new IncludeNavigationContext(item, TopDUContextPointer()));
    return ctx->html(true);
}

}
