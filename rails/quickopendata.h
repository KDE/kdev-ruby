/*
 * This file is part of KDevelop
 *
 * Copyright 2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#ifndef RAILS_QUICKOPEN_DATA_H
#define RAILS_QUICKOPEN_DATA_H

#include <language/interfaces/quickopendataprovider.h>
#include <language/interfaces/quickopenfilter.h>

#include <rails/export.h>

namespace ruby {
namespace rails {

/*
 * TODO: maybe KDevPlatform will pick KDevelop::Path when moving away
 * from KUrl. If this is the case, these two attributes will be of type
 * KDevelop::Path too.
 */
struct KDEVRUBYRAILS_EXPORT QuickOpenItem {
    // The path of the view or test
    QUrl url;

    // The path of the file for which we show views/tests
    QUrl originUrl;
};

/**
 * @class QuickOpenData
 *
 * The class being used to feed data to QuickOpen regarding Rails stuff.
 */
class KDEVRUBYRAILS_EXPORT QuickOpenData : public KDevelop::QuickOpenDataBase
{
public:
    QuickOpenData(const QuickOpenItem &item, const QString &explanation);

protected:
    virtual QString text() const override;
    virtual QString htmlDescription() const override;

    bool execute(QString &filterText) override;

    virtual bool isExpandable() const override;
    virtual QWidget * expandingWidget() const override;

    virtual QIcon icon() const override;

    QList<QVariant> highlighting() const override;

private:
    QuickOpenItem m_item;
    QString m_explanation;
};

}
}

#endif // RAILS_QUICKOPEN_DATA_H

