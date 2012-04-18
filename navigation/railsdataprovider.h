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
#ifndef RAILSDATAPROVIDER_H
#define RAILSDATAPROVIDER_H

#include <language/interfaces/quickopenfilter.h>
#include <language/interfaces/quickopendataprovider.h>

#include "navigationexport.h"

namespace Ruby {

class RailsSwitchers;

struct KDEVRUBYNAVIGATION_EXPORT RailsQuickOpenItem {
    //the url of the view or test
    KUrl url;
    //the url of the file for which we show views/tests
    KUrl originUrl;
};

class KDEVRUBYNAVIGATION_EXPORT RailsQuickOpenData : public KDevelop::QuickOpenDataBase {
public:
    RailsQuickOpenData( const RailsQuickOpenItem& item, const QString &explanation );

    virtual QString text() const;
    virtual QString htmlDescription() const;

    bool execute( QString& filterText );

    virtual bool isExpandable() const;
    virtual QWidget* expandingWidget() const;

    virtual QIcon icon() const;

    QList<QVariant> highlighting() const;

private:
    RailsQuickOpenItem m_item;
    QString m_explanation;
};

typedef KDevelop::FilterWithSeparator<RailsQuickOpenItem> Base;

class KDEVRUBYNAVIGATION_EXPORT RailsDataProvider: public KDevelop::QuickOpenDataProviderBase,
        public Base, public KDevelop::QuickOpenFileSetInterface {
public:
    enum Kind { Views, Tests };

    RailsDataProvider(Kind kind);
    virtual void setFilterText( const QString& text );
    virtual void reset();
    virtual uint itemCount() const;
    virtual uint unfilteredItemCount() const;
    virtual QList<KDevelop::QuickOpenDataPointer> data( uint start, uint end ) const;
    virtual void enableData( const QStringList& items, const QStringList& scopes );

    virtual QString itemText( const RailsQuickOpenItem& data ) const;

    virtual QSet<KDevelop::IndexedString> files() const;

    ///Returns all scopes supported by this data-provider
    static QStringList scopes();

private:
    Kind m_kind;
};

}

#endif
