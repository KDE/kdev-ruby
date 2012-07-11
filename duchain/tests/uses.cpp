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
#include <language/duchain/types/structuretype.h>
#include <language/duchain/duchainutils.h>

// Ruby
#include <duchain/tests/uses.h>


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

void TestUseBuilder::compareUses(Declaration *dec, const RangeInRevision &range)
{
    QList<RangeInRevision> ranges;
    ranges << range;
    compareUses(dec, ranges);
}

void TestUseBuilder::compareUses(Declaration *dec, QList<RangeInRevision> ranges)
{
    QCOMPARE(dec->uses().keys().count(), 1);
    QCOMPARE(dec->uses().values().count(), 1);
    QCOMPARE(dec->uses().values().first().count(), ranges.count());
    for (int i = 0; i < ranges.count(); ++i)
        QCOMPARE(dec->uses().values().first().at(i), ranges.at(i));
}

void TestUseBuilder::stringInterpolation()
{
    //               0          1
    //               01234567 89012 34
    QByteArray code("a = 1; \"#{a}\"");
    TopDUContext *top = parse(code, "stringInterpolation");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec = top->localDeclarations().at(0);
    compareUses(dec, RangeInRevision(0, 10, 0, 11));

    /* Make sure that types are not screwed up after building this new use */
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestUseBuilder::alias()
{
    //               0          1        2
    //               0123456789012345678901234567
    QByteArray code("def foo; end; alias asd foo");
    TopDUContext *top = parse(code, "alias");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec = top->localDeclarations().at(0);
    compareUses(dec, RangeInRevision(0, 24, 0, 27));
}

void TestUseBuilder::assignment()
{
    //               0          1        2         3
    //               01234567890123456789012345678901234567
    QByteArray code("b = 0; a, *, c = b, nil, 3, 4, 5, 'asd'");
    TopDUContext *top = parse(code, "alias");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec = top->localDeclarations().at(0);
    compareUses(dec, RangeInRevision(0, 17, 0, 18));
}

void TestUseBuilder::checkSubClassing()
{
    //               0          1        2         3
    //               0123456789012345678901234567890123456789
    QByteArray code("class Base; end; class Final < Base; end");
    TopDUContext *top = parse(code, "checkSubClassing");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *d = top->localDeclarations().first();
    QCOMPARE(d->uses().count(), 1);
    compareUses(d, RangeInRevision(0, 31, 0, 35));
}

void TestUseBuilder::checkMethodArgumentsContext()
{
    //               0          1        2
    //               0123456789012345678901234
    QByteArray code("def foo(a, b); a; end; a");
    TopDUContext *top = parse(code, "checkMethodArgumentsContext");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // Check that exists a method declaration and that it has a proper
    // context for its parameters
    QCOMPARE(top->localDeclarations().count(), 1);
    Declaration *d = dynamic_cast<Declaration *>(top->localDeclarations().first());
    QVERIFY(d);
    DUContext *params = DUChainUtils::getArgumentContext(d);
    QVERIFY(params);
    QCOMPARE(params->range(), RangeInRevision(0, 8, 0, 12));

    // Check that there's a context for the method body and that it imports
    // the context of the parameters
    DUContext *body = d->internalContext();
    QVERIFY(body);
    QCOMPARE(body->range(), RangeInRevision(0, 15, 0, 16));
    QCOMPARE(body->importedParentContexts().count(), 1);
    QCOMPARE(body->importedParentContexts().first().context(top), params);

    // And finally check the uses of the parameters. There's only one use of a,
    // but it's in the method's body. not the a that is outside.
    QCOMPARE(params->localDeclarations().count(), 2);
    Declaration *a = params->localDeclarations().first();
    QCOMPARE(a->qualifiedIdentifier(), QualifiedIdentifier("foo::a"));
    QCOMPARE(a->uses().count(), 1);
    compareUses(a, RangeInRevision(0, 15, 0, 16));
}

void TestUseBuilder::instanceVariable()
{
    QByteArray code("class Klass; def foo; @lala = 1; end; def asd; @lala = 'asd'; end; end");
    TopDUContext *top = parse(code, "instanceVariable");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    PENDING("Not implemented yet");
}

void TestUseBuilder::classVariable()
{
    QByteArray code("class Base; @@lala = 1; end; class Klass < Base; @@lala; end");
    TopDUContext *top = parse(code, "classVariable");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    PENDING("Not implemented yet");
}

} // End of namespace Ruby


#include "uses.moc"
