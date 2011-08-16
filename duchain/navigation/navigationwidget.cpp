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


#include <duchain/navigation/navigationwidget.h>
#include <duchain/navigation/declarationnavigationcontext.h>
#include <duchain/navigation/includenavigationcontext.h>


namespace Ruby
{
using namespace KDevelop;

NavigationWidget::NavigationWidget( KDevelop::DeclarationPointer decl,
                                    KDevelop::TopDUContextPointer topContext,
                                    const QString &htmlPrefix,
                                    const QString &htmlSuffix)
{
    m_topContext = topContext;
    initBrowser(200);

    m_startContext = NavigationContextPointer(new DeclarationNavigationContext(decl, topContext));
    m_startContext->setPrefixSuffix(htmlPrefix, htmlSuffix);
    setContext(m_startContext);
}

NavigationWidget::NavigationWidget(const KDevelop::IncludeItem &item,
                                   KDevelop::TopDUContextPointer topContext,
                                   const QString &htmlPrefix,
                                   const QString &htmlSuffix)
{
    m_topContext = topContext;
    initBrowser(200);

    m_startContext = NavigationContextPointer(new IncludeNavigationContext(item, topContext));
    m_startContext->setPrefixSuffix(htmlPrefix, htmlSuffix);
    setContext(m_startContext);
}

QString NavigationWidget::shortDescription(KDevelop::Declaration *decl)
{
    NavigationContextPointer ctx(new DeclarationNavigationContext(DeclarationPointer(decl), TopDUContextPointer()));
    return ctx->html(true);
}

QString NavigationWidget::shortDescription(KDevelop::IncludeItem &item)
{
    NavigationContextPointer ctx(new IncludeNavigationContext(item, TopDUContextPointer()));
    return ctx->html(true);
}


} // End of namespace Ruby

