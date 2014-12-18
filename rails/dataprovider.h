/*
 * This file is part of KDevelop
 *
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright 2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#ifndef RAILS_DATA_PROVIDER_H
#define RAILS_DATA_PROVIDER_H

#include <language/interfaces/quickopendataprovider.h>
#include <rails/export.h>
#include <rails/quickopendata.h>

namespace ruby {
namespace rails {

/**
 * The kind of providers available.
 */
enum class Kind { Views, Tests };

/**
 * @class DataProvider.
 *
 * This class takes the rails::QuickOpenData class to provide all the
 * data that we need to feed the QuickOpen.
 */
class KDEVRUBYRAILS_EXPORT DataProvider
    : public KDevelop::QuickOpenDataProviderBase
    , public KDevelop::PathFilter<QuickOpenItem, DataProvider>
{
public:
    explicit DataProvider(const Kind kind);

    /// @returns the item as a KDevelop::Path.
    /// NOTE: currently we use QUrl internally because KDevPlatform hasn't
    /// moved away from KUrl yet.
    inline KDevelop::Path itemPath(const QuickOpenItem &data) const
    {
        return KDevelop::Path(data.url);
    }

    /// @returns all scopes supported by this data-provider.
    static QStringList scopes();

protected:
    virtual void setFilterText(const QString &text) override;
    virtual void reset() override;
    virtual uint itemCount() const override;
    virtual uint unfilteredItemCount() const override;
    virtual KDevelop::QuickOpenDataPointer data(uint row) const override;
    virtual void enableData(const QStringList &items,
                            const QStringList &scopes) override;

private:
    Kind m_kind;
};

}
}

#endif // RAILS_DATA_PROVIDER_H

