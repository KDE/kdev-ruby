/* This file is part of KDevelop
 *
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#ifndef RUBYCOMPLETION_H
#define RUBYCOMPLETION_H


#include <duchain/tests/duchaintestbase.h>


namespace ruby {

/**
 * @class TestCompletion
 * The Code completion test suite.
 */
class TestCompletion : public DUChainTestBase
{
    Q_OBJECT

public:
    /// Constructor.
    TestCompletion();

protected:
    /// Re-implemented from DUChainTestBase.
    virtual KDevelop::TopDUContext * parse(const QByteArray &code, const QString &id);

private:
    /// Verify that all the items in @p shoulda are contained in @p list.
    void shouldContain(const QStringList &list, const QStringList &shoulda, bool sameSize = false);

private slots:
    void standardAccess();
    void baseClass();
    void moduleMixins();
    void memberAccess();
    void checkSubclassing();
    void classMemberAccess();
    void fileChoose();
};

}


#endif // RUBYCOMPLETION_H
