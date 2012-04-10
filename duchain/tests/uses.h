/*
 * This file is part of KDevelop
 * Copyright 2012  Miquel Sabaté <mikisabate@gmail.com>
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


#ifndef RUBY_USES_H
#define RUBY_USES_H


#include <duchain/tests/duchaintestbase.h>


namespace Ruby
{

/// Test the UseBuilder class from the DUChain.
class TestUseBuilder : public DUChainTestBase
{
    Q_OBJECT

public:
    TestUseBuilder();

protected:
    /// Re-implemented from DUChainTestBase.
    virtual KDevelop::TopDUContext * parse(const QByteArray &code, const QString &id);

private:
    /**
     * Let's compare the uses of the given declaration @p dec with the given
     * @p ranges that we expect these uses are enclosed to.
     */
    void compareUses(KDevelop::Declaration *dec, QList<KDevelop::RangeInRevision> ranges);

private slots:
    // Interpolation
    void stringInterpolation();
};

}


#endif /* RUBY_USES_H */
