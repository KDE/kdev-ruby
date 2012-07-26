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
#include <language/duchain/types/unsuretype.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/duchainutils.h>

// Ruby
#include <duchain/tests/duchain.h>
#include <duchain/types/classtype.h>
#include <duchain/declarations/methoddeclaration.h>
#include <duchain/declarations/classdeclaration.h>
#include <duchain/declarations/moduledeclaration.h>
#include <duchain/declarations/variabledeclaration.h>


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

void TestDUChain::testUnsureTypes(TypePtr<UnsureType> type, QList<QString> list)
{
    for (uint i = 0; i < type->typesSize(); i++) {
        QualifiedIdentifier qi = type->types()[i].type<StructureType>()->qualifiedIdentifier();
        QCOMPARE(qi, QualifiedIdentifier(list.at(i)));
    }
}

void TestDUChain::testProblems(TopDUContext *ctx, const QList<QString> &list)
{
    int i = 0;
    QList<ProblemPointer> problems = ctx->problems();
    QVERIFY(problems.size() == list.size());
    foreach (ProblemPointer pp, problems) {
        Problem *p = pp.data();
        QCOMPARE(p->description(), list.at(i));
        i++;
    }
}

//BEGIN: Builtin classes

void TestDUChain::numeric()
{
    QByteArray code("a = 1; b = 1.2");
    TopDUContext *top = parse(code, "numeric");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec1 = top->localDeclarations().at(0);
    QVERIFY(dec1->type<StructureType>());
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    Declaration *dec2 = top->localDeclarations().at(1);
    QVERIFY(dec2->type<StructureType>());
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Float"));
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

void TestDUChain::lambda()
{
    QByteArray code("a = ->(a) { puts a }");
    TopDUContext *top = parse(code, "lambda");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec = top->localDeclarations().at(0);
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Proc"));
}

//END: Builtin classes

//BEGIN: Simple Statements

void TestDUChain::alias()
{
    QByteArray code("def foo; 'a' end; alias asd foo");
    TopDUContext *top = parse(code, "alias");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    /* def foo; end */
    Declaration *dec1 = top->localDeclarations().at(0);
    QVERIFY(dec1->isFunctionDeclaration());
    QCOMPARE(dec1->qualifiedIdentifier(), QualifiedIdentifier("foo"));

    /* alias asd foo */
    Declaration *dec2 = top->localDeclarations().at(1);
    QVERIFY(dec2->isFunctionDeclaration());
    QCOMPARE(dec2->qualifiedIdentifier(), QualifiedIdentifier("asd"));

    /* The return type of asd is also a String */
    AbstractType::Ptr rt = dec2->type<FunctionType>()->returnType();
    StructureType::Ptr structT = rt.cast<StructureType>();
    QCOMPARE(structT->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

void TestDUChain::aliasGlobal1()
{
    QByteArray code("$a = 0; alias $b $a");
    TopDUContext *top = parse(code, "aliasGlobal1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 2);

    Declaration *dec1 = top->localDeclarations().at(0);
    Declaration *dec2 = top->localDeclarations().at(1);

    QCOMPARE(dec1->qualifiedIdentifier(), QualifiedIdentifier("$a"));
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
    QCOMPARE(dec2->qualifiedIdentifier(), QualifiedIdentifier("$b"));
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::aliasGlobal2()
{
    QByteArray code("alias $b $a");
    TopDUContext *top = parse(code, "aliasGlobal2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 2);

    Declaration *dec1 = top->localDeclarations().at(0);
    Declaration *dec2 = top->localDeclarations().at(1);

    QCOMPARE(dec1->qualifiedIdentifier(), QualifiedIdentifier("$b"));
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("NilClass"));
    QCOMPARE(dec2->qualifiedIdentifier(), QualifiedIdentifier("$a"));
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("NilClass"));
}

void TestDUChain::yield1()
{
    QByteArray code("def foo; yield; end; foo { |a, b| puts a + b }");
    TopDUContext *top = parse(code, "yield1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 3);

    Declaration *dec1 = top->localDeclarations().at(1);
    Declaration *dec2 = top->localDeclarations().at(2);

    QCOMPARE(dec1->qualifiedIdentifier(), QualifiedIdentifier("a"));
    QCOMPARE(dec1->type<IntegralType>()->dataType(), (uint) IntegralType::TypeMixed);
    QCOMPARE(dec2->qualifiedIdentifier(), QualifiedIdentifier("b"));
    QCOMPARE(dec2->type<IntegralType>()->dataType(), (uint) IntegralType::TypeMixed);
}

void TestDUChain::yield2()
{
    QByteArray code("def foo; yield 1, 2; yield 'a', 'b'; end; foo { |a, b| puts a + b }");
    TopDUContext *top = parse(code, "yield2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 3);

    Declaration *dec = top->localDeclarations().at(1);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier("a"));
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(dec->abstractType());
    QList<QString> list;
    list << "Fixnum" << "String";
    testUnsureTypes(ut, list);

    dec = top->localDeclarations().at(2);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier("b"));
    ut = UnsureType::Ptr::dynamicCast(dec->abstractType());
    testUnsureTypes(ut, list);
}

//END: Simple Statements

//BEGIN: Compound Statements

void TestDUChain::ifStatement()
{
    QByteArray code("a = if d; 1; elsif b; nil; else; 'asd'; end");
    TopDUContext *top = parse(code, "ifStatement");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec = top->localDeclarations().at(0);
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(dec->abstractType());
    QList<QString> list;
    list << "NilClass" << "String" << "Fixnum";
    testUnsureTypes(ut, list);
}

void TestDUChain::caseStatement()
{
    QByteArray code("f = case a; when 1; 2; nil; when 2; 1; else; 'asd'; end");
    TopDUContext *top = parse(code, "caseStatement");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec = top->localDeclarations().at(0);
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(dec->abstractType());
    QList<QString> list;
    list << "NilClass" << "Fixnum" << "String";
    testUnsureTypes(ut, list);
}

//END: Compound Statements

//BEGIN: Assignments

void TestDUChain::simpleUnsure()
{
    QByteArray code("a = 1; a = 'string'");
    TopDUContext *top = parse(code, "simpleUnsure");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 1);
    Declaration *d = top->localDeclarations().first();
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(d->abstractType());
    QList<QString> list;
    list << "Fixnum" << "String";
    testUnsureTypes(unsure, list);
}

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
    TopDUContext *top = parse(code, "multipleAssignment2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 2);

    // a
    Declaration *dec = top->localDeclarations().at(0);
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    /* b */
    dec = top->localDeclarations().at(1);
    QCOMPARE(dec->type<ClassType>()->toString(), QString("Array of Fixnum"));
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
    QByteArray code("b = 0; a, *, c = b, nil, 3, 4, 5, 'asd'");
    TopDUContext *top = parse(code, "multipleAssignmentStar");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 3);

    Declaration *dec1 = top->localDeclarations().at(1);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    Declaration *dec2 = top->localDeclarations().at(2);
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

void TestDUChain::multipleAssignmentNamedStar()
{
    QByteArray code("a, *b, c = nil, nil, 3, 4, 5, 'asd'");
    TopDUContext *top = parse(code, "multipleAssignmentNamedStar");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 3);

    Declaration *dec1 = top->localDeclarations().at(0);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("NilClass"));

    Declaration *dec2 = top->localDeclarations().at(1);
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Array"));
    QVERIFY(dec2->type<ClassType>()->contentType());
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(dec2->type<ClassType>()->contentType().abstractType());
    QList<QString> list;
    list << "NilClass" << "Fixnum";
    testUnsureTypes(unsure, list);

    Declaration *dec3 = top->localDeclarations().at(2);
    QCOMPARE(dec3->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

void TestDUChain::starAtTheBeginning()
{
    QByteArray code("*, i = 1, 2, nil");
    TopDUContext *top = parse(code, "starAtTheBeginning");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec1 = top->localDeclarations().at(0);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("NilClass"));
}

void TestDUChain::starAtTheEnd()
{
    QByteArray code("q, * = //, 1, 2");
    TopDUContext *top = parse(code, "starAtTheEnd");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *dec1 = top->localDeclarations().at(0);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Regexp"));
}

void TestDUChain::emptyStar()
{
    QByteArray code("r, *t, w = 1, 'as'");
    TopDUContext *top = parse(code, "emptyStar");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 3);

    Declaration *dec1 = top->localDeclarations().at(0);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    Declaration *dec2 = top->localDeclarations().at(1);
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Array"));

    Declaration *dec3 = top->localDeclarations().at(2);
    QCOMPARE(dec3->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

void TestDUChain::unpackArray1()
{
    QByteArray code("a, b = [1, 2]");
    TopDUContext *top = parse(code, "unpackArray1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 2);

    Declaration *dec1 = top->localDeclarations().at(0);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    Declaration *dec2 = top->localDeclarations().at(1);
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::unpackArray2()
{
    QByteArray code("a = [1, 2, 3]; b, c, d = a");
    TopDUContext *top = parse(code, "unpackArray2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 4);

    Declaration *dec1 = top->localDeclarations().at(1);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    Declaration *dec2 = top->localDeclarations().at(2);
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    Declaration *dec3 = top->localDeclarations().at(3);
    QCOMPARE(dec3->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::unpackArray3()
{
    QByteArray code("a, b = [1, 2], 1");
    TopDUContext *top = parse(code, "unpackArray3");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 2);

    Declaration *dec1 = top->localDeclarations().at(0);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Array"));

    Declaration *dec2 = top->localDeclarations().at(1);
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::aliasedAssignment()
{
    QByteArray code("a = 1..2; b = 1; c, d = a, b");
    TopDUContext *top = parse(code, "aliasedAssignment");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 4);

    Declaration *dec3 = top->localDeclarations().at(2);
    QVERIFY(dec3->type<StructureType>());
    QCOMPARE(dec3->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Range"));

    Declaration *dec4 = top->localDeclarations().at(3);
    QVERIFY(dec4->type<StructureType>());
    QCOMPARE(dec4->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

//END: Assignments

//BEGIN: ClassType

void TestDUChain::assignFromArrayItem1()
{
    QByteArray code("a = [1, 2, 3]; b = a[0]");
    TopDUContext *top = parse(code, "assignFromArrayItem1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 2);

    // a
    Declaration *d = top->localDeclarations().at(0);
    QCOMPARE(d->type<ClassType>()->toString(), QString("Array of Fixnum"));

    // b
    d = top->localDeclarations().at(1);
    QCOMPARE(d->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::assignFromArrayItem2()
{
    QByteArray code("a = [1, '2']; b = a[0]");
    TopDUContext *top = parse(code, "assignFromArrayItem2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 2);

    // a
    Declaration *d = top->localDeclarations().at(0);
    QCOMPARE(d->type<ClassType>()->toString(), QString("Array of unsure (Fixnum, String)"));

    // b
    d = top->localDeclarations().at(1);
    QList<QString> list;
    list << "Fixnum" << "String";
    testUnsureTypes(d->type<UnsureType>(), list);
}

void TestDUChain::assignFromHashItem()
{
    QByteArray code("a = { :a => 'a', b: 1 }; b = a[:a]");
    TopDUContext *top = parse(code, "assignFromHashItem");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QVERIFY(top->localDeclarations().size() == 2);

    // a
    Declaration *d = top->localDeclarations().at(0);
    QCOMPARE(d->type<ClassType>()->toString(), QString("Hash of unsure (String, Fixnum)"));

    // b
    d = top->localDeclarations().at(1);
    QList<QString> list;
    list << "String" << "Fixnum";
    testUnsureTypes(d->type<UnsureType>(), list);
}

void TestDUChain::assignToArrayItem()
{
    QByteArray code("a = [1, nil]; a[1] = 'asd'");
    TopDUContext *top = parse(code, "assignToArrayItem");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *d = top->localDeclarations().at(0);
    UnsureType::Ptr cont = d->type<ClassType>()->contentType().type<UnsureType>();
    QList<QString> list;
    list << "Fixnum" << "NilClass" << "String";
    testUnsureTypes(cont, list);
}

//END: ClassType

//BEGIN: Declarations

void TestDUChain::checkVariableKind()
{
    QByteArray code("$a = 0; @a = 0; @@a = 0; a = 0; A = 0");
    TopDUContext *top = parse(code, "checkVariableKind");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    VariableDeclaration *obj = dynamic_cast<VariableDeclaration *>(top->localDeclarations().at(0));
    QVERIFY(obj->isGlobal());

    obj = dynamic_cast<VariableDeclaration *>(top->localDeclarations().at(1));
    QVERIFY(obj->isIvar());

    obj = dynamic_cast<VariableDeclaration *>(top->localDeclarations().at(2));
    QVERIFY(obj->isCvar());

    obj = dynamic_cast<VariableDeclaration *>(top->localDeclarations().at(3));
    QVERIFY(obj->isNormal());

    obj = dynamic_cast<VariableDeclaration *>(top->localDeclarations().at(4));
    QVERIFY(obj->isConstant());
}

void TestDUChain::instanceClassMethodDeclaration()
{
    QByteArray code("class Klass; def foo(a, b); end; def asd; end; ");
    code += "def self.selfish; end; def Klass.selfis; end; end";
    TopDUContext *top = parse(code, "instanceClassMethodDeclaration");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVector<Declaration *> decs = top->childContexts().first()->localDeclarations();

    // Instance methods
    MethodDeclaration *d1 = dynamic_cast<MethodDeclaration *>(decs.first());
    QVERIFY(!d1->isClassMethod());

    MethodDeclaration *d2 = dynamic_cast<MethodDeclaration *>(decs.at(1));
    QVERIFY(!d2->isClassMethod());

    // Class methods
    MethodDeclaration *d3 = dynamic_cast<MethodDeclaration *>(decs.at(2));
    QVERIFY(d3->isClassMethod());

    MethodDeclaration *d4 = dynamic_cast<MethodDeclaration *>(decs.at(3));
    QVERIFY(d4->isClassMethod());
}

void TestDUChain::accessPolicyMethodInClass()
{
    QByteArray code("class Klass; def foo; end; protected; def asd; end; ");
    code += "private; def zxc; end; public; def iop; end; end";
    TopDUContext *top = parse(code, "accessPolicyMethodInClass");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVector<Declaration *> decs = top->childContexts().first()->localDeclarations();

    MethodDeclaration *d1 = dynamic_cast<MethodDeclaration *>(decs.first());
    QVERIFY(d1->accessPolicy() == Declaration::Public);

    MethodDeclaration *d2 = dynamic_cast<MethodDeclaration *>(decs.at(1));
    QVERIFY(d2->accessPolicy() == Declaration::Protected);

    MethodDeclaration *d3 = dynamic_cast<MethodDeclaration *>(decs.at(2));
    QVERIFY(d3->accessPolicy() == Declaration::Private);

    MethodDeclaration *d4 = dynamic_cast<MethodDeclaration *>(decs.at(3));
    QVERIFY(d4->accessPolicy() == Declaration::Public);
}

void TestDUChain::accessPolicyMethodInModule()
{
    QByteArray code("module Klass; def foo; end; protected; def asd; end; ");
    code += "private; def zxc; end; public; def iop; end; end";
    TopDUContext *top = parse(code, "accessPolicyMethodInClass");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVector<Declaration *> decs = top->childContexts().first()->localDeclarations();

    MethodDeclaration *d1 = dynamic_cast<MethodDeclaration *>(decs.first());
    QVERIFY(d1->accessPolicy() == Declaration::Public);

    MethodDeclaration *d2 = dynamic_cast<MethodDeclaration *>(decs.at(1));
    QVERIFY(d2->accessPolicy() == Declaration::Protected);

    MethodDeclaration *d3 = dynamic_cast<MethodDeclaration *>(decs.at(2));
    QVERIFY(d3->accessPolicy() == Declaration::Private);

    MethodDeclaration *d4 = dynamic_cast<MethodDeclaration *>(decs.at(3));
    QVERIFY(d4->accessPolicy() == Declaration::Public);
}

void TestDUChain::nestedAccessPolicy()
{
    QByteArray code("class Outer; class Inner; private; def innerFoo; end; ");
    code += "end; def outerFoo; end; end";
    TopDUContext *top = parse(code, "nestedAccessPolicy");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());
    QVector<Declaration *> decs = top->childContexts().first()->localDeclarations();

    // innerFoo
    Declaration *d = decs.first()->internalContext()->localDeclarations().first();
    QVERIFY(dynamic_cast<MethodDeclaration *>(d)->accessPolicy() == Declaration::Private);

    // outerFoo
    d = decs.last();
    QVERIFY(dynamic_cast<MethodDeclaration *>(d)->accessPolicy() == Declaration::Public);
}

void TestDUChain::checkSubClassing()
{
    QByteArray code("class Base; end; class Final < Base; end");
    TopDUContext *top = parse(code, "checkSubClassing");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // Base
    ClassDeclaration *base = dynamic_cast<ClassDeclaration *>(top->localDeclarations().first());
    QVERIFY(base);
    QCOMPARE(base->internalContext()->childContexts().count(), 0);
    QCOMPARE(base->internalContext()->importedParentContexts().count(), 0);
    QCOMPARE(base->internalContext()->localScopeIdentifier(), QualifiedIdentifier("Base"));

    // Final
    ClassDeclaration *final = dynamic_cast<ClassDeclaration *>(top->localDeclarations().last());
    QVERIFY(final);
    QCOMPARE(final->internalContext()->childContexts().count(), 0);
    QCOMPARE(final->internalContext()->importedParentContexts().count(), 1);
    QCOMPARE(final->internalContext()->localScopeIdentifier(), QualifiedIdentifier("Final"));
    QVERIFY(final->baseClass());
    QCOMPARE(final->baseClass(), base->indexedType());
}

void TestDUChain::errorOnInvalidRedeclaration()
{
    QByteArray code("class Klass; end; module Module; end; class Kernel; end");
    TopDUContext *top = parse(code, "errorOnInvalidRedeclaration");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QStringList errors;
    errors << "TypeError: Module is not a module"
            << "TypeError: Kernel is not a class";
    testProblems(top, errors);
}

void TestDUChain::instanceVariable()
{
    QByteArray code("class Klass; def foo; @lala = 1; end; def asd; @lala = 'asd'; end; end");
    TopDUContext *top = parse(code, "instanceVariable");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList<Declaration *> ds;
    foreach (Declaration *d, top->childContexts().first()->localDeclarations())
        if (dynamic_cast<VariableDeclaration *>(d))
            ds << d;
    QCOMPARE(ds.size(), 1);

    Declaration *decl = ds.first();
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(decl->abstractType());
    QList<QString> list;
    list << "Fixnum" << "String";
    testUnsureTypes(ut, list);
}

void TestDUChain::classVariable()
{
    QByteArray code("class Base; @@lala = 1; end; class Klass < Base; @@lala; end");
    TopDUContext *top = parse(code, "classVariable");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList<Declaration *> ds;
    foreach (Declaration *d, top->childContexts().first()->localDeclarations())
        if (dynamic_cast<VariableDeclaration *>(d))
            ds << d;
    QCOMPARE(ds.size(), 1);

    // @@lala = 1
    Declaration *decl = ds.first();
    QCOMPARE(decl->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    // Check that the @@lala inside Klass is the same as the Base one
    QCOMPARE(top->childContexts().last()->localDeclarations().size(), 0);
    QVector<DUContext::Import> aux = top->childContexts().last()->importedParentContexts();
    ds.clear();
    foreach (Declaration *d, aux.first().context(top)->localDeclarations())
        if (dynamic_cast<VariableDeclaration *>(d))
            ds << d;
    QCOMPARE(ds.size(), 1);
    decl = ds.first();
    QCOMPARE(decl->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

//END: Declarations

//BEGIN: Returning Values

void TestDUChain::multipleReturns()
{
    QByteArray code("def foo(a, b); return nil if a.nil?; return 'a'; end");
    TopDUContext *top = parse(code, "multipleReturns");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *decl = top->localDeclarations().first();
    FunctionType::Ptr ft = decl->type<FunctionType>();
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(ft->returnType());
    QList<QString> list;
    list << "String" << "NilClass";
    testUnsureTypes(ut, list);
}

void TestDUChain::implicitReturn()
{
    QByteArray code("def foo; 'a'; end");
    TopDUContext *top = parse(code, "implicitReturn");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *decl = top->localDeclarations().first();
    FunctionType::Ptr ft = decl->type<FunctionType>();
    StructureType::Ptr st = StructureType::Ptr::dynamicCast(ft->returnType());
    QCOMPARE(st->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

void TestDUChain::mixedExplicitAndImplicitReturn()
{
    QByteArray code("def foo(a); return nil if a.nil?; 'a'; end");
    TopDUContext *top = parse(code, "mixedExplicitAndImplicitReturn");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *decl = top->localDeclarations().first();
    FunctionType::Ptr ft = decl->type<FunctionType>();
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(ft->returnType());
    QList<QString> list;
    list << "String" << "NilClass";
    testUnsureTypes(ut, list);
}

//END: Returning Values

//BEGIN: Methods

void TestDUChain::callingToInstanceMethod()
{
    QByteArray code("class Klass; def foo; 1; end; end; obj = Klass.new; a = obj.foo");
    TopDUContext *top = parse(code, "callingToInstanceMethod");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *obj = top->localDeclarations().at(1);
    QCOMPARE(obj->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Klass"));

    obj = top->localDeclarations().at(2);
    QCOMPARE(obj->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::chainedCalls1()
{
    QByteArray code("module Modul; class Klass; def self.selfish(a, b); ");
    code += "'str'; end; end; end; a = Modul::Klass.selfish(1, 2)";
    TopDUContext *top = parse(code, "chainedCalls1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *d = top->localDeclarations().last();
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("a"));
    QCOMPARE(d->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

void TestDUChain::chainedCalls2()
{
    QByteArray code("class Base; def foo; 'asd'; end; end; class Klass; ");
    code += "def foo1; a = Base.new; a.foo; end; end; b = Klass.new; c = b.foo1";
    TopDUContext *top = parse(code, "chainedCalls2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    PENDING("This test is expected to fail, since the feature is covering is still under construction");

    // b
    Declaration *d = top->localDeclarations().at(2);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("b"));
    QCOMPARE(d->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Klass"));

    // c
    d = top->localDeclarations().last();
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("c"));
    QCOMPARE(d->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

void TestDUChain::chainedCalls3()
{
    QByteArray code("module A; class B; def foo; //; end; end; a = B.new.foo;");
    code += "end; b = A::B.new.foo";
    TopDUContext *top = parse(code, "chainedCalls3");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    PENDING("This test is expected to fail, since the feature is covering is still under construction");

    // a
    Declaration *d = top->localDeclarations().first();
    d = d->internalContext()->localDeclarations().last();
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("A::a"));
    QCOMPARE(d->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Regexp"));

    // b
    d = top->localDeclarations().last();
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("b"));
    QCOMPARE(d->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Regexp"));
}

// Defines a method with an amazing list of arguments
const QByteArray foo("def foo(a, b = 0, c = 0, *d, e, f, &blk); end; ");

void TestDUChain::guessArgumentsType1()
{
    QByteArray code(foo + "foo 1, 'str', //");
    TopDUContext *top = parse(code, "guessArgumentsType1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *d = top->localDeclarations().first();
    QVector<Declaration *> args = DUChainUtils::getArgumentContext(d)->localDeclarations();
    QCOMPARE(args.size(), 7);

    // a, b and c are just Fixnum
    QCOMPARE(args.first()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
    QCOMPARE(args.at(1)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
    QCOMPARE(args.at(2)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    // d is an empty array
    QCOMPARE(args.at(3)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Array"));
    QVERIFY(! args.at(3)->type<ClassType>()->contentType());

    // e is a String and f is a Regexp
    QCOMPARE(args.at(4)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));
    QCOMPARE(args.at(5)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Regexp"));

    // blk is just a Proc
    QCOMPARE(args.last()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Proc"));
}

void TestDUChain::guessArgumentsType2()
{
    QByteArray code(foo + "foo 1, 'str', 1.2, //");
    TopDUContext *top = parse(code, "guessArgumentsType2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *d = top->localDeclarations().first();
    QVector<Declaration *> args = DUChainUtils::getArgumentContext(d)->localDeclarations();
    QCOMPARE(args.size(), 7);

    // a is just a Fixnum
    QCOMPARE(args.first()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    // b is an Unsure of Fixnum and String
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(args.at(1)->abstractType());
    QList<QString> list;
    list << "Fixnum" << "String";
    testUnsureTypes(unsure, list);

    // c is just a Fixnum
    QCOMPARE(args.at(2)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    // d is an empty array
    QCOMPARE(args.at(3)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Array"));
    QVERIFY(! args.at(3)->type<ClassType>()->contentType());

    // e is a Float and f is a Regexp
    QCOMPARE(args.at(4)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Float"));
    QCOMPARE(args.at(5)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Regexp"));

    // blk is just a Proc
    QCOMPARE(args.last()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Proc"));
}

void TestDUChain::guessArgumentsType3()
{
    QByteArray code(foo + "foo 1, 'str', 1, 2, 'str', 1.2, //");
    TopDUContext *top = parse(code, "guessArgumentsType3");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *d = top->localDeclarations().first();
    QVector<Declaration *> args = DUChainUtils::getArgumentContext(d)->localDeclarations();
    QCOMPARE(args.size(), 7);

    // a is just a Fixnum
    QCOMPARE(args.first()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    // b is an Unsure of Fixnum and String
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(args.at(1)->abstractType());
    QList<QString> list;
    list << "Fixnum" << "String";
    testUnsureTypes(unsure, list);

    // c is just a Fixnum
    QCOMPARE(args.at(2)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    // d is an empty array
    QCOMPARE(args.at(3)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Array"));
    unsure = UnsureType::Ptr::dynamicCast(args.at(3)->type<ClassType>()->contentType().abstractType());
    list.clear();
    list << "Fixnum" << "String";
    testUnsureTypes(unsure, list);

    // e is a Float and f is a Regexp
    QCOMPARE(args.at(4)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Float"));
    QCOMPARE(args.at(5)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Regexp"));

    // blk is just a Proc
    QCOMPARE(args.last()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Proc"));
}

void TestDUChain::showErrorOnTooFewArguments()
{
    QByteArray code("def foo(a, b = 0, c = 0, *d, e, f, &blk); end; foo 1, 2");
    TopDUContext *top = parse(code, "showErrorOnTooFewArguments");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList<QString> errors;
    errors << "wrong number of arguments (2 for 3) (ArgumentError)";
    testProblems(top, errors);
}

void TestDUChain::showErrorOnTooManyArguments()
{
    QByteArray code("def foo(a, b); end; foo 1, 2, 3");
    TopDUContext *top = parse(code, "showErrorOnTooManyArguments");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList<QString> errors;
    errors << "wrong number of arguments (3 for 2) (ArgumentError)";
    testProblems(top, errors);
}

void TestDUChain::hashArgument()
{
    QByteArray code("def foo(a, *b, c); end; foo 1, 2, 'string', :a => 'a', :b => 1");
    TopDUContext *top = parse(code, "hashArgument");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *d = top->localDeclarations().first();
    QVector<Declaration *> args = DUChainUtils::getArgumentContext(d)->localDeclarations();
    QCOMPARE(args.size(), 3);

    // a
    QCOMPARE(args.first()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    // b
    QCOMPARE(args.at(1)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Array"));
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(args.at(1)->type<ClassType>()->contentType().abstractType());
    QList<QString> list;
    list << "Fixnum" << "String";
    testUnsureTypes(unsure, list);

    // c
    QCOMPARE(args.last()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Hash"));
    unsure = UnsureType::Ptr::dynamicCast(args.last()->type<ClassType>()->contentType().abstractType());
    list.clear();
    list << "String" << "Fixnum";
    testUnsureTypes(unsure, list);
}

void TestDUChain::setUnsureArgument()
{
    QByteArray code("def foo(a, b); end; foo 1, 2; foo 'asd', 2");
    TopDUContext *top = parse(code, "setUnsureArgument");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(top->localDeclarations().first());
    QVERIFY(md);
    QVector<Declaration *> args = DUChainUtils::getArgumentContext(md)->localDeclarations();
    QVERIFY(args.size() == 2);
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(args.first()->indexedType().abstractType());
    QList<QString> list;
    list << "Fixnum" << "String";
    testUnsureTypes(unsure, list);
    QCOMPARE(args.last()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

//END: Methods

//BEGIN: Include & Extend

void TestDUChain::include1()
{
    /*
     * The class Klass includes the module AA::BB that has the instance
     * method foo.
     */
    QByteArray code("module AA; module BB; def foo; end; def self.selfish; end;");
    code += "end; end; class Klass; include AA::BB; end";
    TopDUContext *top = parse(code, "include1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *obj = top->findLocalDeclarations(Identifier("Klass")).first();
    ModuleDeclaration *md = dynamic_cast<ModuleDeclaration *>(obj);
    QVERIFY(md);

    // Check for the moduleMixins list of the class Klass
    QCOMPARE(md->internalContext()->localDeclarations(md->topContext()).size(), 1);
    QCOMPARE(md->moduleMixinsSize(), 1u);
    QVERIFY(md->moduleMixins()[0].included);
    QCOMPARE(md->moduleMixins()[0].module.type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("AA::BB"));
    QCOMPARE(md->mixersSize(), 0u);

    // Check for the mixers list of the module AA::BB
    obj = top->localDeclarations().at(0)->internalContext()->localDeclarations().first();
    md = dynamic_cast<ModuleDeclaration *>(obj);
    QVERIFY(md);
    QCOMPARE(md->moduleMixinsSize(), 0u);
    QCOMPARE(md->mixersSize(), 1u);
    QCOMPARE(md->mixers()[0].module.type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Klass"));
}

void TestDUChain::include2()
{
    /*
     * The module AA::CC includes the module AA::BB, that has the instance
     * method foo. Finally, the class Klass includes the module AA::CC.
     */
    QByteArray code("module AA; module BB; def foo; end; end; module CC; ");
    code += "include ::AA::BB; end; end; class Klass; include AA::CC; end";
    TopDUContext *top = parse(code, "include2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *obj = top->findLocalDeclarations(Identifier("Klass")).first();
    ModuleDeclaration *md = dynamic_cast<ModuleDeclaration *>(obj);
    QVERIFY(md);
    QCOMPARE(md->internalContext()->localDeclarations(md->topContext()).size(), 1);
    QCOMPARE(md->moduleMixinsSize(), 1u);
    QVERIFY(md->moduleMixins()[0].included);
    QCOMPARE(md->moduleMixins()[0].module.type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("AA::CC"));
}

void TestDUChain::extend()
{
    /* Same as include1 but with extend and a class method */
    QByteArray code("module AA; module BB; def foo; end; def self.selfish; end;");
    code += "end; end; class Klass; extend AA::BB; end";
    TopDUContext *top = parse(code, "extend");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // Check for the moduleMixins list of the class Klass
    Declaration *obj = top->findLocalDeclarations(Identifier("Klass")).first();
    ModuleDeclaration *md = dynamic_cast<ModuleDeclaration *>(obj);
    QVERIFY(md);
    QCOMPARE(md->internalContext()->localDeclarations(md->topContext()).size(), 1);
    QCOMPARE(md->moduleMixinsSize(), 1u);
    QVERIFY(!md->moduleMixins()[0].included);
    QCOMPARE(md->moduleMixins()[0].module.type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("AA::BB"));

    // Check for the mixers list of the module AA::BB
    obj = top->localDeclarations().at(0)->internalContext()->localDeclarations().first();
    md = dynamic_cast<ModuleDeclaration *>(obj);
    QVERIFY(md);
    QCOMPARE(md->moduleMixinsSize(), 0u);
    QCOMPARE(md->mixersSize(), 1u);
    QCOMPARE(md->mixers()[0].module.type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Klass"));
}

void TestDUChain::problemOnInvalidMixin()
{
    QByteArray code("class Lala; end; class Klass; include Lala; end");
    TopDUContext *top = parse(code, "problemOnInvalidMixin");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QList<QString> list;
    list << "TypeError: wrong argument type (expected Module)";
    testProblems(top, list);
}

//END: Include & Extend

} // End of namespace Ruby


#include "duchain.moc"
