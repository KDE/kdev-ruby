/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#include <kio/global.h>
#include <language/duchain/topducontextdata.h>
#include <language/duchain/duchainregister.h>
#include <language/util/includeitem.h>
#include <duchain/rubyducontext.h>
#include <duchain/navigation/navigationwidget.h>


namespace Ruby
{
using namespace KDevelop;

REGISTER_DUCHAIN_ITEM_WITH_DATA(RubyTopDUContext, TopDUContextData);
REGISTER_DUCHAIN_ITEM_WITH_DATA(RubyNormalDUContext, DUContextData);

template<>
QWidget * RubyTopDUContext::createNavigationWidget(Declaration *decl, TopDUContext *topContext,
                                                   const QString &htmlPrefix, const QString &htmlSuffix) const
{
    if (!decl) {
        QUrl u = QUrl::fromLocalFile(url().str());
        IncludeItem i;
        i.pathNumber = -1;
        i.name = u.fileName();
        i.isDirectory = false;
        i.basePath = KIO::upUrl(u);
        return new NavigationWidget(i, TopDUContextPointer(topContext), htmlPrefix, htmlSuffix);
    }
    return new NavigationWidget(DeclarationPointer(decl), TopDUContextPointer(topContext), htmlPrefix, htmlSuffix);
}

template<>
QWidget * RubyNormalDUContext::createNavigationWidget(Declaration *decl, TopDUContext *topContext,
                                                      const QString &htmlPrefix, const QString &htmlSuffix) const
{
    if (!decl) {
        if (owner())
            return new NavigationWidget(DeclarationPointer(owner()), TopDUContextPointer(topContext), htmlPrefix, htmlSuffix);
        return nullptr;
    }
    return new NavigationWidget(DeclarationPointer(decl), TopDUContextPointer(topContext), htmlPrefix, htmlSuffix);
}

};

