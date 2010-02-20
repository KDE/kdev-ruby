/*
* This file is part of KDevelop
*
* Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
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
#ifndef VIEWSDATAPROVIDER_H
#define VIEWSDATAPROVIDER_H

#include <language/interfaces/quickopenfilter.h>
#include <language/interfaces/quickopendataprovider.h>

namespace Ruby {

class RailsSwitchers;

struct ViewItem {
    //the url of the view
    KUrl url;
    //the url of the file for which we show views
    KUrl originUrl;
};

class ViewData : public KDevelop::QuickOpenDataBase {
public:
    ViewData( const ViewItem& view );

    virtual QString text() const;
    virtual QString htmlDescription() const;

    bool execute( QString& filterText );

    virtual bool isExpandable() const;
    virtual QWidget* expandingWidget() const;

    virtual QIcon icon() const;

    QList<QVariant> highlighting() const;

private:
    ViewItem m_view;
};

class ViewsDataProvider: public KDevelop::QuickOpenDataProviderBase,
        public KDevelop::FilterWithSeparator<ViewItem>, public KDevelop::QuickOpenFileSetInterface {
public:
    ViewsDataProvider();
    virtual void setFilterText( const QString& text );
    virtual void reset();
    virtual uint itemCount() const;
    virtual QList<KDevelop::QuickOpenDataPointer> data( uint start, uint end ) const;
    virtual void enableData( const QStringList& items, const QStringList& scopes );

    virtual QString itemText( const ViewItem& data ) const;

    virtual QSet<KDevelop::IndexedString> files() const;

    ///Returns all scopes supported by this data-provider
    static QStringList scopes();
};

}

#endif
