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
#include <language/duchain/duchain.h>
#include <language/duchain/declaration.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/types/structuretype.h>

// Ruby
#include <duchain/tests/duchain.h>
#include <rubydefs.h>


QTEST_MAIN(Ruby::TestDUChain)

using namespace KDevelop;
namespace Ruby
{

TestDUChain::TestDUChain()
{
    /* There's nothing to do here */
}

TopDUContext * TestDUChain::parse(const QByteArray &code, const QString &id)
{
    const QString &name = "duchain_" + id;
    return DUChainTestBase::parse(code, name);
}

//BEGIN: Builtin classes

void TestDUChain::fixnum()
{
    QByteArray code("a = 1");
    TopDUContext *top = parse(code, "fixnum");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec = top->localDeclarations().at(0);
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::range()
{
    QByteArray code("a = 1..42");
    TopDUContext *top = parse(code, "range");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec1 = top->localDeclarations().at(0);
    QVERIFY(dec1->type<StructureType>());
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Range"));
}

void TestDUChain::stringAndRegexp()
{
    QByteArray code("a = 'string'; b = //");
    TopDUContext *top = parse(code, "stringAndRegexp");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 2);

    /* a = 'string' */
    Declaration *dec1 = top->localDeclarations().at(0);
    QVERIFY(dec1->type<StructureType>());
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));

    /* b = // */
    Declaration *dec2 = top->localDeclarations().at(1);
    QVERIFY(dec2->type<StructureType>());
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Regexp"));
}

void TestDUChain::booleanAndNilAndSelf()
{
    QByteArray code("a = true; b = false; c = nil; d = self");
    TopDUContext *top = parse(code, "booleanAndNilAndSelf");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 4);

    /* a = true */
    Declaration *dec1 = top->localDeclarations().at(0);
    QVERIFY(dec1->type<StructureType>());
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("TrueClass"));

    /* b = false */
    Declaration *dec2 = top->localDeclarations().at(1);
    QVERIFY(dec2->type<StructureType>());
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("FalseClass"));

    /* c = nil */
    Declaration *dec3 = top->localDeclarations().at(2);
    QVERIFY(dec3->type<StructureType>());
    QCOMPARE(dec3->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("NilClass"));

    /* d = self */
    Declaration *dec4 = top->localDeclarations().at(3);
    QVERIFY(dec4->type<StructureType>());
    QCOMPARE(dec4->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Object"));
}

void TestDUChain::lineFileEncoding()
{
    QByteArray code("a = __LINE__; b = __FILE__; c = __ENCODING__");
    TopDUContext *top = parse(code, "lineFileEncoding");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 3);

    /* a = __LINE__ */
    Declaration *dec1 = top->localDeclarations().at(0);
    QVERIFY(dec1->type<StructureType>());
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    /* b = __FILE__ */
    Declaration *dec2 = top->localDeclarations().at(1);
    QVERIFY(dec2->type<StructureType>());
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));

    /* c = __ENCODING__ */
    Declaration *dec3 = top->localDeclarations().at(2);
    QVERIFY(dec3->type<StructureType>());
    QCOMPARE(dec3->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Encoding"));
}

void TestDUChain::symbol()
{
    QByteArray code("a = :a");
    TopDUContext *top = parse(code, "symbol");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec = top->localDeclarations().at(0);
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Symbol"));
}

//END: Builtin classes

//BEGIN: Assignments

void TestDUChain::multipleAssignment1()
{
    QByteArray code("a, b = 1, 'a'");
    TopDUContext *top = parse(code, "multipleAssignment1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 2);

    /* a */
    Declaration *dec1 = top->localDeclarations().at(0);
    QVERIFY(dec1->type<StructureType>());
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    /* b */
    Declaration *dec2 = top->localDeclarations().at(1);
    QVERIFY(dec2->type<StructureType>());
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

void TestDUChain::multipleAssignment2()
{
    QByteArray code("a, b = 1, [1, 2, 3]");

    /* TODO: pending */
    QVERIFY(true);
}

void TestDUChain::multipleAssignmentLeft()
{
    QByteArray code("a, b, c = 1, 2");
    TopDUContext *top = parse(code, "multipleAssignmentLeft");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 3);

    /* a */
    Declaration *dec1 = top->localDeclarations().at(0);
    QVERIFY(dec1->type<StructureType>());
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    /* b */
    Declaration *dec2 = top->localDeclarations().at(1);
    QVERIFY(dec2->type<StructureType>());
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    /* c */
    Declaration *dec3 = top->localDeclarations().at(2);
    QVERIFY(dec3->type<StructureType>());
    QCOMPARE(dec3->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("NilClass"));
}

void TestDUChain::multipleAssignmentRight1()
{
    QByteArray code("a = 1, 2, 3");
    TopDUContext *top = parse(code, "multipleAssignmentRight1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 1);

    Declaration *dec = top->localDeclarations().at(0);
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::multipleAssignmentRight2()
{
    QByteArray code("a, = 1, 2, 3");
    TopDUContext *top = parse(code, "multipleAssignmentRight2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 1);

    Declaration *dec = top->localDeclarations().at(0);
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::multipleAssignmentStar()
{
    QByteArray code("a, *, b = 1, 2, 3, 4, 5, 'a'");

    /* TODO: pending */
    QVERIFY(true);
}

void TestDUChain::multipleAssignmentNamedStar()
{
    QByteArray code("a, *b, c = 1, 2, 3, 4, 5, 'a'");

    /* TODO: pending */
    QVERIFY(true);
}

void TestDUChain::unpackArray()
{
    QByteArray code("a, b, c = [1, 2]");

    /* TODO: pending */
    QVERIFY(true);
}

//END: Assignments

} // End of namespace Ruby


#include "duchain.moc"
