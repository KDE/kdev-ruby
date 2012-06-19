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
    QCOMPARE(dec2->qualifiedIdentifier(), QualifiedIdentifier("b"));
    // TODO: types must be NilClass
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

    PENDING("Waiting for the ClassType to be supported");
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
    list << "Fixnum" << "NilClass";
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

void TestDUChain::hashAssignment()
{
    QByteArray code("a = { :a => 1, :b => 'b' }; b = a[:b]");
    TopDUContext *top = parse(code, "hashAssignment");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    PENDING("Waiting for the ClassType to be supported");

    QVERIFY(top->localDeclarations().size() == 2);

    Declaration *dec1 = top->localDeclarations().at(0);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Hash"));

    Declaration *dec2 = top->localDeclarations().at(1);
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(dec2->abstractType());
    QVERIFY(ut);
    QList<QString> list;
    list << "Fixnum" << "String";
    testUnsureTypes(ut, list);
}

//END: Assignments

//BEGIN: Variable Length Container

void TestDUChain::assignFromArrayItem1()
{
    QByteArray code("a = [1, 2, 3]; b = a[0]");

    PENDING("Waiting for the ClassType to be supported");
}

void TestDUChain::assignFromArrayItem2()
{
    QByteArray code("a = [1, '2']; b = a[0]");

    PENDING("Waiting for the ClassType to be supported");
}

void TestDUChain::assignFromHashItem()
{
    QByteArray code("a = { :a => 'a', b: 1 }; b = a[:a]");

    PENDING("Waiting for the ClassType to be supported");
}

void TestDUChain::assignToArrayItem()
{
    QByteArray code("a = [1, nil]; a[1] = 2");

    PENDING("Waiting for the ClassType to be supported");
}

//END: Variable Length Container

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
    code += "def self.selfish; end; def Klass.selfish; end; end";
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

void TestDUChain::checkDeclarationsOnSubClass()
{
    /*
     * The class Base defines a public instance method and a public class
     * method. Then it defines a protected instance method and a private one.
     * Finally, the class Final gets defined, and it subclasses the Base class.
     */
    QByteArray code("class Base; def foo; end; def self.selfish; end; ");
    code += "protected; def protected_foo; end; private; def private_foo;";
    code += "end; end; class Final < Base; end";
    TopDUContext *top = parse(code, "checkDeclarationsOnSubClass");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    PENDING("Still hacking on the subclassing code");
}

void TestDUChain::errorOnInvalidRedeclaration()
{
    QByteArray code("module Module; end; class Kernel; end");
    TopDUContext *top = parse(code, "errorOnInvalidRedeclaration");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    QStringList errors;
    errors << "TypeError: Module is not a module"
            << "TypeError: Kernel is not a class";
    testProblems(top, errors);
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

//BEGIN: Method Calls

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

void TestDUChain::setMethodArgumentTypes1()
{
    QByteArray code("def foo(a, b); end; foo 1, 2");
    TopDUContext *top = parse(code, "setMethodArgumentTypes1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(top->localDeclarations().first());
    QVERIFY(md);
    QVector<Declaration *> args = DUChainUtils::getArgumentContext(md)->localDeclarations();
    QVERIFY(args.size() == 2);
    foreach (const Declaration *d, args)
        QCOMPARE(d->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::setMethodArgumentTypes2()
{
    QByteArray code("def foo(a, b); end; c = 1.2; foo c, 2");
    TopDUContext *top = parse(code, "setMethodArgumentTypes2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(top->localDeclarations().first());
    QVERIFY(md);
    QVector<Declaration *> args = DUChainUtils::getArgumentContext(md)->localDeclarations();
    QVERIFY(args.size() == 2);
    QCOMPARE(args.first()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Float"));
    QCOMPARE(args.last()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
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

//END: Method Calls

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
    TopDUContext *top = parse(code, "extend1");
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

//END: Include & Extend

} // End of namespace Ruby


#include "duchain.moc"
