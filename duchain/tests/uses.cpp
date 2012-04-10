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


// Qt + KDevelop
#include <QtTest/QtTest>
#include <language/duchain/declaration.h>

// Ruby
#include <duchain/tests/uses.h>
#include <rubydefs.h>


QTEST_MAIN(Ruby::TestUseBuilder)

using namespace KDevelop;
namespace Ruby
{

TestUseBuilder::TestUseBuilder()
{
    /* There's nothing do here! */
}

TopDUContext * TestUseBuilder::parse(const QByteArray &code, const QString &id)
{
    const QString &name = "uses_" + id;
    return DUChainTestBase::parse(code, name);
}

void TestUseBuilder::compareUses(Declaration *dec, QList<RangeInRevision> ranges)
{
    QCOMPARE(dec->uses().keys().count(), 1);
    QCOMPARE(dec->uses().values().count(), 1);
    QCOMPARE(dec->uses().values().first().count(), ranges.count());
    for (int i = 0; i < ranges.count(); ++i)
        QCOMPARE(dec->uses().values().first().at(i), ranges.at(i));
}

//BEGIN: Interpolation

void TestUseBuilder::stringInterpolation()
{
    //               0          1
    //               01234567 89012 34
    QByteArray code("a = 1; \"#{a}\"");
    TopDUContext *top = parse(code, "stringInterpolation");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());
    QList<RangeInRevision> ranges;
    ranges << RangeInRevision(0, 10, 0, 11);
    compareUses(top->localDeclarations().at(0), ranges);
}

//END: Interpolation

} // End of namespace Ruby


#include "uses.moc"
