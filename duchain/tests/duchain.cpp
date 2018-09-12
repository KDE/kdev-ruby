/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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


// Qt + KDevelop
#include <QtTest/QtTest>
#include <language/duchain/duchain.h>
#include <language/duchain/declaration.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/types/structuretype.h>
#include <language/duchain/types/unsuretype.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/duchainutils.h>
#include <language/duchain/problem.h>

// Ruby
#include <duchain/tests/duchain.h>
#include <duchain/helpers.h>
#include <duchain/types/classtype.h>
#include <duchain/declarations/methoddeclaration.h>
#include <duchain/declarations/moduledeclaration.h>
#include <duchain/declarations/variabledeclaration.h>

QTEST_MAIN(ruby::TestDUChain)

using namespace KDevelop;
namespace ruby
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

void TestDUChain::testUnsureTypes(TypePtr<UnsureType> type, const QStringList &list)
{
    for (uint i = 0; i < type->typesSize(); i++) {
        QualifiedIdentifier qi = type->types()[i].type<StructureType>()->qualifiedIdentifier();
        qDebug() << qi.toString() << " " << list[i];
        QCOMPARE(qi, QualifiedIdentifier(list[i]));
    }
}

void TestDUChain::testProblems(TopDUContext *ctx, const QStringList &list)
{
    int i = 0;
    QList<ProblemPointer> problems = ctx->problems();
    QVERIFY(problems.size() == list.size());
    foreach (ProblemPointer pp, problems) {
        Problem *p = pp.data();
        QCOMPARE(p->description(), list[i]);
        i++;
    }
}

//BEGIN: Builtin classes

void TestDUChain::numeric()
{
    QByteArray code("a = 1; b = 1.2; c = 12i; d = 34r");
    TopDUContext *top = parse(code, "numeric");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *dec1 = top->localDeclarations().at(0);
    QVERIFY(dec1->type<StructureType>());
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    Declaration *dec2 = top->localDeclarations().at(1);
    QVERIFY(dec2->type<StructureType>());
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Float"));

    Declaration *dec3 = top->localDeclarations().at(2);
    QVERIFY(dec3->type<StructureType>());
    QCOMPARE(dec3->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Complex"));

    Declaration *dec4 = top->localDeclarations().at(3);
    QVERIFY(dec4->type<StructureType>());
    QCOMPARE(dec4->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Rational"));
}

void TestDUChain::range()
{
    QByteArray code("a = 1..42");
    TopDUContext *top = parse(code, "range");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *dec1 = top->localDeclarations().at(0);
    QVERIFY(dec1->type<StructureType>());
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Range"));
}

void TestDUChain::stringAndRegexp()
{
    QByteArray code("a = 'string'; b = //");
    TopDUContext *top = parse(code, "stringAndRegexp");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

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

void TestDUChain::booleanAndNil()
{
    QByteArray code("a = true; b = false; c = nil");
    TopDUContext *top = parse(code, "booleanAndNil");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QVERIFY(top->localDeclarations().size() == 3);

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
}

void TestDUChain::lineFileEncoding()
{
    QByteArray code("a = __LINE__; b = __FILE__; c = __ENCODING__");
    TopDUContext *top = parse(code, "lineFileEncoding");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

    Declaration *dec = top->localDeclarations().at(0);
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Symbol"));
}

void TestDUChain::lambda()
{
    QByteArray code("a = ->(a) { puts a }; b = lambda { |x| return x + 1 }");
    TopDUContext *top = parse(code, "lambda");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *dec = top->localDeclarations().at(0);
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Proc"));

    dec = top->localDeclarations().at(1);
    QVERIFY(dec->type<StructureType>());
    QCOMPARE(dec->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Proc"));
}

void TestDUChain::self()
{
    QByteArray code("module Modul; a = self; class Klass; b = self; end; end; c = self; def foo; self; end");
    TopDUContext *top = parse(code, "self");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    // a
    Declaration *d = top->localDeclarations().first();
    Declaration *obj = d->internalContext()->localDeclarations().first();
    QCOMPARE(obj->qualifiedIdentifier(), QualifiedIdentifier("Modul::a"));
    QCOMPARE(obj->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Modul"));

    // b
    obj = d->internalContext()->localDeclarations().last()->internalContext()->localDeclarations().first();
    QCOMPARE(obj->qualifiedIdentifier(), QualifiedIdentifier("Modul::Klass::b"));
    QCOMPARE(obj->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Modul::Klass"));

    // c
    d = top->localDeclarations().at(1);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("c"));
    QCOMPARE(d->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Object"));

    // Return type for foo
    d = top->localDeclarations().last();
    AbstractType::Ptr rType = d->type<FunctionType>()->returnType();
    StructureType::Ptr structT = rType.cast<StructureType>();
    QCOMPARE(structT->qualifiedIdentifier(), QualifiedIdentifier("Object"));
}

//END: Builtin classes

//BEGIN: Statements

void TestDUChain::alias()
{
    QByteArray code("def foo; 'a' end; alias asd foo");
    TopDUContext *top = parse(code, "alias");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

    QVector<Declaration *> decls = top->childContexts().last()->localDeclarations();

    QCOMPARE(decls.size(), 2);
    Declaration *dec1 = decls.at(0);
    Declaration *dec2 = decls.at(1);

    QCOMPARE(dec1->qualifiedIdentifier(), QualifiedIdentifier("a"));
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Object"));
    QCOMPARE(dec2->qualifiedIdentifier(), QualifiedIdentifier("b"));
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Object"));
}

void TestDUChain::yield2()
{
    QByteArray code("def foo; yield 1, 2; yield 'a', 'b'; end; foo { |a, b| puts a + b }");
    TopDUContext *top = parse(code, "yield2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QVector<Declaration *> decls = top->childContexts().last()->localDeclarations();
    QVERIFY(decls.size() == 2);

    Declaration *dec = decls.at(0);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier("a"));
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(dec->abstractType());
    QStringList list;
    list << "Fixnum" << "String";
    testUnsureTypes(ut, list);

    dec = decls.at(1);
    QCOMPARE(dec->qualifiedIdentifier(), QualifiedIdentifier("b"));
    ut = UnsureType::Ptr::dynamicCast(dec->abstractType());
    testUnsureTypes(ut, list);
}

void TestDUChain::yield3()
{
    QByteArray code("foo { |a, b| puts a + b }");
    TopDUContext *top = parse(code, "yield3");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QVector<Declaration *> decls = top->childContexts().last()->localDeclarations();

    QCOMPARE(decls.size(), 2);
    Declaration *dec1 = decls.at(0);
    Declaration *dec2 = decls.at(1);

    QCOMPARE(dec1->qualifiedIdentifier(), QualifiedIdentifier("a"));
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Object"));
    QCOMPARE(dec2->qualifiedIdentifier(), QualifiedIdentifier("b"));
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Object"));
}

void TestDUChain::ifStatement()
{
    QByteArray code("a = if d; 1; elsif b; nil; else; 'asd'; end");
    TopDUContext *top = parse(code, "ifStatement");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *dec = top->localDeclarations().at(0);
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(dec->abstractType());
    QStringList list;
    list << "NilClass" << "String" << "Fixnum";
    testUnsureTypes(ut, list);
}

void TestDUChain::caseStatement()
{
    QByteArray code("f = case a; when 1; 2; nil; when 2; 1; else; 'asd'; end");
    TopDUContext *top = parse(code, "caseStatement");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *dec = top->localDeclarations().at(0);
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(dec->abstractType());
    QStringList list;
    list << "NilClass" << "Fixnum" << "String";
    testUnsureTypes(ut, list);
}

void TestDUChain::forStatement()
{
    QByteArray code("for i in [1, 'str'] do; end");
    TopDUContext *top = parse(code, "forStatement");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QCOMPARE(top->localDeclarations().size(), 1);
    Declaration *d = top->localDeclarations().first();
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(d->abstractType());
    QStringList list;
    list << "Fixnum" << "String";
    testUnsureTypes(ut, list);
}

void TestDUChain::hereDoc()
{
    // heredoc should be a string and should not be parsed as ruby code
    QByteArray code("execute <<EOS\n\
foo (\n\
EOS\n\
");
    parse(code, "hereDoc");

    DOES_NOT_CRASH;
}

void TestDUChain::exceptions()
{
    QByteArray code("begin; 1 / 0; rescue ZeroDivisionError, LoadError => e; end");

    {
        TopDUContext *top = parse(code, "exceptions");
        DUChainReleaser releaser(top);
        DUChainWriteLocker lock;
        Declaration *d = top->localDeclarations().first();
        QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("e"));
        UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(d->abstractType());
        QStringList list;
        list << "ZeroDivisionError" << "LoadError";
        testUnsureTypes(unsure, list);
    }

    {
        code = "begin; 1 / 0; rescue ZeroDivisionError, LoadError; end";
        TopDUContext *top = parse(code, "exceptions");
        DUChainReleaser releaser(top);
        DUChainWriteLocker lock;
        DOES_NOT_CRASH;
    }
}

void TestDUChain::method()
{
    QByteArray code("a = def foo; 0; end");
    TopDUContext *top = parse(code, "method");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *d = top->localDeclarations().first();
    QVERIFY(d);
    QCOMPARE(d->abstractType()->toString(), QString("Symbol"));
}

void TestDUChain::classStatement()
{
    QByteArray code("a = class Klass; 0; ''; end");
    TopDUContext *top = parse(code, "classStatement");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *d = top->localDeclarations().first();
    QVERIFY(d);
    QCOMPARE(d->abstractType()->toString(), QString("String"));
}

//END: Statements

//BEGIN: Assignments

void TestDUChain::simpleUnsure()
{
    QByteArray code("a = 1; a = 'string'");
    TopDUContext *top = parse(code, "simpleUnsure");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QVERIFY(top->localDeclarations().size() == 1);
    Declaration *d = top->localDeclarations().first();
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(d->abstractType());
    QStringList list;
    list << "Fixnum" << "String";
    testUnsureTypes(unsure, list);
}

void TestDUChain::unsureHash()
{
    // this test (when run separately from other tests) crashes
    // when storing Hash of unsure (Bar::Foo, String) in the item repository
    QByteArray code("class Bar; class Foo; end; x = [ Foo.new, 'test' ]; end");
    parse(code, "unsureTypeStorage");

    DOES_NOT_CRASH;
}

void TestDUChain::multipleAssignment1()
{
    QByteArray code("a, b = 1, 'a'");
    TopDUContext *top = parse(code, "multipleAssignment1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

    QVERIFY(top->localDeclarations().size() == 3);

    Declaration *dec1 = top->localDeclarations().at(0);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("NilClass"));

    Declaration *dec2 = top->localDeclarations().at(1);
    QCOMPARE(dec2->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Array"));
    QVERIFY(dec2->type<ClassType>()->contentType());
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(dec2->type<ClassType>()->contentType().abstractType());
    QStringList list;
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
    DUChainWriteLocker lock;

    Declaration *dec1 = top->localDeclarations().at(0);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("NilClass"));
}

void TestDUChain::starAtTheEnd()
{
    QByteArray code("q, * = //, 1, 2");
    TopDUContext *top = parse(code, "starAtTheEnd");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *dec1 = top->localDeclarations().at(0);
    QCOMPARE(dec1->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Regexp"));
}

void TestDUChain::emptyStar()
{
    QByteArray code("r, *t, w = 1, 'as'");
    TopDUContext *top = parse(code, "emptyStar");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

    QVERIFY(top->localDeclarations().size() == 4);

    Declaration *dec3 = top->localDeclarations().at(2);
    QVERIFY(dec3->type<StructureType>());
    QCOMPARE(dec3->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Range"));

    Declaration *dec4 = top->localDeclarations().at(3);
    QVERIFY(dec4->type<StructureType>());
    QCOMPARE(dec4->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::withMethodCallAndBlock()
{
    QByteArray code("a = Class.new do; def foo; b = 0; end; end.foo(1, 2)");
    TopDUContext *top = parse(code, "withMethodCallAndBlock");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    DOES_NOT_CRASH;
}

//END: Assignments

//BEGIN: ClassType

void TestDUChain::assignFromArrayItem1()
{
    QByteArray code("a = [1, 2, 3]; b = a[0]");
    TopDUContext *top = parse(code, "assignFromArrayItem1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

    QVERIFY(top->localDeclarations().size() == 2);

    // a
    Declaration *d = top->localDeclarations().at(0);
    QCOMPARE(d->type<ClassType>()->toString(), QString("Array of unsure (Fixnum, String)"));

    // b
    d = top->localDeclarations().at(1);
    QStringList list;
    list << "Fixnum" << "String";
    testUnsureTypes(d->type<UnsureType>(), list);
}

void TestDUChain::assignFromHashItem()
{
    QByteArray code("a = { :a => 'a', b: 1 }; b = a[:a]");
    TopDUContext *top = parse(code, "assignFromHashItem");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QVERIFY(top->localDeclarations().size() == 2);

    // a
    Declaration *d = top->localDeclarations().at(0);
    QCOMPARE(d->type<ClassType>()->toString(), QString("Hash of unsure (String, Fixnum)"));

    // b
    d = top->localDeclarations().at(1);
    QStringList list;
    list << "String" << "Fixnum";
    testUnsureTypes(d->type<UnsureType>(), list);
}

void TestDUChain::assignToArrayItem()
{
    QByteArray code("a = [1, nil]; a[1] = 'asd'");
    TopDUContext *top = parse(code, "assignToArrayItem");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *d = top->localDeclarations().at(0);
    UnsureType::Ptr cont = d->type<ClassType>()->contentType().type<UnsureType>();
    QStringList list;
    list << "Fixnum" << "NilClass" << "String";
    testUnsureTypes(cont, list);
}

void TestDUChain::arrayInstanceVariable()
{
    QByteArray code("class Klass; def foo; @var = [1, 'str']; @var[0]; end; end");
    TopDUContext *top = parse(code, "arrayInstanceVariable");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *d = top->localDeclarations().first();
    d = d->internalContext()->localDeclarations().first();
    QVERIFY(d);
    FunctionType::Ptr fType = d->type<FunctionType>();
    QVERIFY(fType);
    UnsureType::Ptr ut = fType->returnType().cast<UnsureType>();
    QVERIFY(ut);
    QCOMPARE(ut->typesSize(), (uint) 2);
    QStringList list;
    list << "Fixnum" << "String";
    testUnsureTypes(ut, list);
}

//END: ClassType

//BEGIN: Declarations

void TestDUChain::checkVariableKind()
{
    QByteArray code("$a = 0; @a = 0; @@a = 0; a = 0; A = 0");
    TopDUContext *top = parse(code, "checkVariableKind");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

    ModuleDeclaration *mod = dynamic_cast<ModuleDeclaration *>(top->localDeclarations().first());
    QVERIFY(mod);

    // Instance methods
    QVector<Declaration *> decs = mod->internalContext()->localDeclarations();
    QCOMPARE(decs.size(), 2);

    MethodDeclaration *d = dynamic_cast<MethodDeclaration *>(decs.first());
    QCOMPARE(d->qualifiedIdentifier().toString(), QString("Klass::foo"));
    d = dynamic_cast<MethodDeclaration *>(decs.last());
    QCOMPARE(d->qualifiedIdentifier().toString(), QString("Klass::asd"));

    // Class methods
    decs = mod->eigenClass()->localDeclarations();
    QCOMPARE(decs.size(), 2);

    d = dynamic_cast<MethodDeclaration *>(decs.first());
    QCOMPARE(d->qualifiedIdentifier().toString(), QString("Klass::Klass::selfish"));
    d = dynamic_cast<MethodDeclaration *>(decs.last());
    QCOMPARE(d->qualifiedIdentifier().toString(), QString("Klass::Klass::selfis"));
}

void TestDUChain::reopenMethodDeclaration()
{
    QByteArray code("class Klass; def foo; ''; end; end; def foo; 'str'; end; def foo; 0; end");
    TopDUContext *top = parse(code, "reopenMethodDeclaration");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QVector<Declaration *> decls = top->localDeclarations();
    QCOMPARE(decls.size(), 2);

    Declaration *d = decls.first()->internalContext()->localDeclarations().first();
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("Klass::foo"));
    MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(d);
    AbstractType::Ptr type = md->type<FunctionType>()->returnType();
    QCOMPARE(type->toString(), QString("String"));

    d = decls.last();
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("foo"));
    md = dynamic_cast<MethodDeclaration *>(d);
    type = md->type<FunctionType>()->returnType();
    QCOMPARE(type->toString(), QString("Fixnum"));
}

void TestDUChain::singletonMethods()
{
    QByteArray code("def Hash.foo; end; a = 0; def a.lala; end");
    TopDUContext *top = parse(code, "singletonMethods");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    // Hash.foo
    Declaration *d = getBuiltinDeclaration("Hash#foo", top, top);
    MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(d);
    QVERIFY(md);
    QVERIFY(md->isClassMethod());

    // a.lala
    d = getBuiltinDeclaration("Fixnum#lala", top, top);
    md = dynamic_cast<MethodDeclaration *>(d);
    QVERIFY(md);
    QVERIFY(!md->isClassMethod());
}

void TestDUChain::singletonClass1()
{
    QByteArray code("a = 0; class << a; def foo; 'string'; end; end");
    TopDUContext *top = parse(code, "singletonClass1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *d = getBuiltinDeclaration("Fixnum#foo", top, top);
    MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(d);
    QVERIFY(md);
    QVERIFY(!md->isClassMethod());

    AbstractType::Ptr type = md->type<FunctionType>()->returnType();
    QCOMPARE(type.cast<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

void TestDUChain::singletonClass2()
{
    QSKIP("It crashes right now since I'm not done with the eigenclass thing");

    QByteArray code("class Klass; class << self; def foo; 'string'; end; end; end");
    TopDUContext *top = parse(code, "singletonClass2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    DUContext *ctx = top->localDeclarations().first()->internalContext();
    Declaration *d = ctx->findDeclarations(QualifiedIdentifier("foo")).first();
    MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(d);
    QVERIFY(md);
    QVERIFY(md->isClassMethod());

    StructureType::Ptr type = StructureType::Ptr::dynamicCast(md->type<FunctionType>()->returnType());
    QCOMPARE(type->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

void TestDUChain::singletonClass3()
{
    QByteArray code("a = 0; a = 'str'; class << a; end");
    TopDUContext *top = parse(code, "singletonClass3");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    DOES_NOT_CRASH;
}

void TestDUChain::singletonMethodVisibility()
{
    QByteArray code("class << Foo; private; def foo; end; end");
    parse(code, "singletonMethodVisibility");

    DOES_NOT_CRASH;
}

void TestDUChain::accessPolicyMethodInClass()
{
    QByteArray code("class Klass; def foo; end; protected; def asd; end; ");
    code += "private; def zxc; end; public; def iop; end; end";
    TopDUContext *top = parse(code, "accessPolicyMethodInClass");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;
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
    DUChainWriteLocker lock;
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

void TestDUChain::accessPolicyOnBlock()
{
    QByteArray code("class Klass; end; Klass.class_eval { private; def foo; end }");
    TopDUContext *top = parse(code, "accessPolicyOnBlock");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    DOES_NOT_CRASH;
}

void TestDUChain::nestedAccessPolicy()
{
    QByteArray code("class Outer; class Inner; private; def innerFoo; end; ");
    code += "end; def outerFoo; end; end";
    TopDUContext *top = parse(code, "nestedAccessPolicy");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;
    QVector<Declaration *> decs = top->childContexts().first()->localDeclarations();

    // innerFoo
    Declaration *d = decs.first()->internalContext()->localDeclarations().first();
    QVERIFY(dynamic_cast<MethodDeclaration *>(d)->accessPolicy() == Declaration::Private);

    // outerFoo
    d = decs.last();
    QVERIFY(dynamic_cast<MethodDeclaration *>(d)->accessPolicy() == Declaration::Public);
}

void TestDUChain::checkSubClassing1()
{
    QByteArray code("class Base; end; class Final < Base; end");
    TopDUContext *top = parse(code, "checkSubClassing1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    // Base
    ModuleDeclaration *base = dynamic_cast<ModuleDeclaration *>(top->localDeclarations().first());
    QVERIFY(base);
    QCOMPARE(base->internalContext()->childContexts().count(), 0);
    QCOMPARE(base->internalContext()->importedParentContexts().count(), 0);
    QCOMPARE(base->internalContext()->localScopeIdentifier(), QualifiedIdentifier("Base"));

    // Final
    ModuleDeclaration *final = dynamic_cast<ModuleDeclaration *>(top->localDeclarations().last());
    QVERIFY(final);
    QCOMPARE(final->internalContext()->childContexts().count(), 0);
    QCOMPARE(final->internalContext()->importedParentContexts().count(), 1);
    QCOMPARE(final->internalContext()->localScopeIdentifier(), QualifiedIdentifier("Final"));
    QVERIFY(final->baseClass());
    QCOMPARE(final->baseClass(), base->indexedType());
}

void TestDUChain::checkSubClassing2()
{
    QByteArray code("module A; class B; end; end; class C < A::B; end");
    TopDUContext *top = parse(code, "checkSubClassing2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    // B
    Declaration *decl = top->localDeclarations().first(); // A
    decl = decl->internalContext()->localDeclarations().first(); // B
    QVERIFY(decl);
    QCOMPARE(decl->internalContext()->childContexts().count(), 0);
    QCOMPARE(decl->internalContext()->importedParentContexts().count(), 0);
    QCOMPARE(decl->qualifiedIdentifier(), QualifiedIdentifier("A::B"));

    // C
    ModuleDeclaration *cDecl = dynamic_cast<ModuleDeclaration *>(top->localDeclarations().last());
    QVERIFY(cDecl);
    QCOMPARE(cDecl->internalContext()->childContexts().count(), 0);
    QCOMPARE(cDecl->internalContext()->importedParentContexts().count(), 1);
    QCOMPARE(cDecl->qualifiedIdentifier(), QualifiedIdentifier("C"));
    QVERIFY(cDecl->baseClass());
    QCOMPARE(cDecl->baseClass(), decl->indexedType());
}

void TestDUChain::checkSubClassingErrors()
{
    QStringList errors;
    errors << "TypeError: wrong argument type (expected Class)";

    {
        QByteArray code("module A; end; class B < A; end;");
        TopDUContext *top = parse(code, "checkSubClassingErrors");
        DUChainReleaser releaser(top);
        DUChainWriteLocker lock;
        testProblems(top, errors);
    }

    {
        QByteArray code("A = 0; class B < A; end;");
        TopDUContext *top = parse(code, "checkSubClassingErrors");
        DUChainReleaser releaser(top);
        DUChainWriteLocker lock;
        testProblems(top, errors);
    }
}

void TestDUChain::errorOnInvalidRedeclaration1()
{
    QByteArray code("class Klass; end; module Module; end; class Kernel; end");
    TopDUContext *top = parse(code, "errorOnInvalidRedeclaration1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QStringList errors;
    errors << "TypeError: Module is not a module"
            << "TypeError: Kernel is not a class";
    testProblems(top, errors);
}

void TestDUChain::errorOnInvalidRedeclaration2()
{
    QByteArray code("module Klass; end; module Mod; class Klass; end; end");
    TopDUContext *top = parse(code, "errorOnInvalidRedeclaration2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    /*
     * This test just checks that no problems are being raised, since the
     * second class Klass is inside the module Mod, so it's not the same
     * as the first Klass, which is a module.
     */

    QStringList errors;
    testProblems(top, errors);
}

void TestDUChain::instanceVariable()
{
    // class Klass
    //   @asd = 1
    //
    //   def foo
    //     @asd = 'asd'
    //     @asd
    //   end
    //
    //   class Mod
    //     def lala
    //       @asd = 12i
    //       @asd
    //     end
    //   end
    // end
    //
    // a = Klass.new
    // b = a.foo
    // c = Klass::Mod.new
    // d = c.lala

    QByteArray code("class Klass; @asd = 1; def foo; @asd = 'asd'; @asd; end;");
    code += " class Mod; def lala; @asd = 12i; @asd; end; end; end;";
    code += " a = Klass.new; b = a.foo; c = Klass::Mod.new; d = c.lala";
    TopDUContext *top = parse(code, "instanceVariable1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QList<Declaration *> ds;
    foreach (Declaration *d, top->childContexts().first()->localDeclarations())
        if (dynamic_cast<VariableDeclaration *>(d))
            ds << d;
    QCOMPARE(ds.size(), 1);
    QCOMPARE(ds.first()->qualifiedIdentifier(), QualifiedIdentifier("Klass::@asd"));
    QVERIFY(ds.first()->isAutoDeclaration());

    // It's an unsure(Fixnum, String, Complex)
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(ds.first()->abstractType());
    QStringList list;
    list << "Fixnum" << "String" << "Complex";
    testUnsureTypes(ut, list);

    // b is an unsure(Fixnum, String, Complex)
    QVector<Declaration *> decls = top->localDeclarations();
    Declaration *d = decls.at(2);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("b"));
    ut = UnsureType::Ptr::dynamicCast(d->abstractType());
    QVERIFY(ut);
    testUnsureTypes(ut, list);

    // d is also an unsure(Fixnum, String, Complex)
    QCOMPARE(decls.at(4)->qualifiedIdentifier(), QualifiedIdentifier("d"));
    ut = UnsureType::Ptr::dynamicCast(decls.at(4)->abstractType());
    QVERIFY(ut);
    testUnsureTypes(ut, list);
}

void TestDUChain::classVariable()
{
    QByteArray code("class Base; @@lala = 1; end; class Klass < Base; @@lala; end");
    TopDUContext *top = parse(code, "classVariable");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QList<Declaration *> ds;
    foreach (Declaration *d, top->childContexts().first()->localDeclarations())
        if (dynamic_cast<VariableDeclaration *>(d))
            ds << d;
    QCOMPARE(ds.size(), 1);

    // @@lala = 1
    Declaration *decl = ds.first();
    QVERIFY(decl->isAutoDeclaration());
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

void TestDUChain::classModulesScopes()
{
    QByteArray code("module Klass; end; module Modul; end; class Modul::Klass;");
    code += " ::Klass; module Thing; Klass; ::Klass; end; end;";
    TopDUContext *top = parse(code, "classModulesScopes");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QVector<Declaration *> decls = top->localDeclarations();
    QCOMPARE(decls.size(), 2);

    QCOMPARE(decls.first()->qualifiedIdentifier(), QualifiedIdentifier("Klass"));
    QCOMPARE(decls.at(1)->qualifiedIdentifier(), QualifiedIdentifier("Modul"));

    decls = decls.at(1)->internalContext()->localDeclarations();
    QCOMPARE(decls.size(), 1);

    QCOMPARE(decls.first()->qualifiedIdentifier(), QualifiedIdentifier("Modul::Klass"));

    decls = decls.first()->internalContext()->localDeclarations();
    QCOMPARE(decls.size(), 1);

    QCOMPARE(decls.first()->qualifiedIdentifier(), QualifiedIdentifier("Klass::Thing"));
}

void TestDUChain::globals1()
{
    QByteArray code("$asd = 1234; class Klass; a = $asd; $asd = 1; class Sub;");
    code += " $asd = 'asd'; end; end";
    TopDUContext *top = parse(code, "globals1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    // The goal of this test is to check that there's only 3 declarations:
    // $asd, Klass and Sub. All assignments of $asd correspond to the same
    // global variable.

    // Only 2 declarations: $asd and Klass.
    QVector<Declaration *> decls = top->localDeclarations();
    Declaration *asd;
    QCOMPARE(decls.size(), 2);
    asd = decls.first();
    QCOMPARE(asd->qualifiedIdentifier(), QualifiedIdentifier("$asd"));
    QCOMPARE(decls.last()->qualifiedIdentifier(), QualifiedIdentifier("Klass"));

    // Only 2 declarations: a and Sub.
    decls = decls.last()->internalContext()->localDeclarations();
    QCOMPARE(decls.first()->qualifiedIdentifier(), QualifiedIdentifier("Klass::a"));
    QCOMPARE(decls.last()->qualifiedIdentifier(), QualifiedIdentifier("Klass::Sub"));

    // No declarations.
    decls = decls.last()->internalContext()->localDeclarations();
    QVERIFY(decls.empty());

    // Check that $asd is an unsure(Fixnum, String)
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(asd->abstractType());
    QStringList list;
    list << "Fixnum" << "String";
    testUnsureTypes(ut, list);
}

void TestDUChain::globals2()
{
    QByteArray code("class Klass; $asd = 1; end; module Mod; $asd = 'asd'; end");
    TopDUContext *top = parse(code, "globals2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    // The point of this test is to check that the $asd global variable is set
    // in the top DUContext, so there's just one single $asd declaration.
    // This $asd variable is expected to be in the top.

    QVector<Declaration *> decls = top->localDeclarations();
    QCOMPARE(decls.size(), 3);
    Declaration *d = decls.at(1);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("$asd"));

    // Check that there's no new declaration inside the Mod module.
    decls = decls.last()->internalContext()->localDeclarations();
    QVERIFY(decls.empty());

    // Check that $asd is an unsure(Fixnum, String)
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(d->abstractType());
    QStringList list;
    list << "Fixnum" << "String";
    testUnsureTypes(ut, list);
}

//END: Declarations

//BEGIN: Returning Values

void TestDUChain::multipleReturns()
{
    QByteArray code("def foo(a, b); return nil if a.nil?; return 'a'; end");
    TopDUContext *top = parse(code, "multipleReturns");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *decl = top->localDeclarations().first();
    FunctionType::Ptr ft = decl->type<FunctionType>();
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(ft->returnType());
    QStringList list;
    list << "String" << "NilClass";
    testUnsureTypes(ut, list);
}

void TestDUChain::implicitReturn()
{
    QByteArray code("class Klass; def item; @list = [1, 'str']; @list[0]; end; end;");
    code += "a = Klass.new; b = a.item";
    TopDUContext *top = parse(code, "returnFromInstanceMethod");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *d = top->localDeclarations().last();
    UnsureType::Ptr ut = d->type<UnsureType>();
    QVERIFY(ut);
    QStringList list;
    list << "Fixnum" << "String";
    testUnsureTypes(ut, list);
}

void TestDUChain::mixedExplicitAndImplicitReturn()
{
    QByteArray code("def foo(a); return nil if a.nil?; 'a'; end");
    TopDUContext *top = parse(code, "mixedExplicitAndImplicitReturn");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *decl = top->localDeclarations().first();
    FunctionType::Ptr ft = decl->type<FunctionType>();
    UnsureType::Ptr ut = UnsureType::Ptr::dynamicCast(ft->returnType());
    QStringList list;
    list << "String" << "NilClass";
    testUnsureTypes(ut, list);
}

void TestDUChain::nilReturn()
{
    QByteArray code("def foo; end");
    TopDUContext *top = parse(code, "nilReturn");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *decl = top->localDeclarations().first();
    FunctionType::Ptr ft = decl->type<FunctionType>();
    StructureType::Ptr rt = ft->returnType().cast<StructureType>();
    QCOMPARE(rt->qualifiedIdentifier(), QualifiedIdentifier("NilClass"));
}

void TestDUChain::instanceClassMethodsReturn()
{
    QByteArray code("class Klass; def self.foo; 0; end; def foo; ''; end; end; a = Klass.new; b = a.foo; c = Klass.foo");
    TopDUContext *top = parse(code, "instanceClassMethodsReturn");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    qDebug() << top->localDeclarations().size();

    Declaration *d = top->localDeclarations().at(2);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("b"));
    QCOMPARE(d->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("String"));

    d = top->localDeclarations().last();
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("c"));
    qDebug() << d->type<StructureType>()->qualifiedIdentifier().toString();
    QCOMPARE(d->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

//END: Returning Values

//BEGIN: Methods

void TestDUChain::callingToInstanceMethod()
{
    QByteArray code("class Klass; def foo; 1; end; end; obj = Klass.new; a = obj.foo");
    TopDUContext *top = parse(code, "callingToInstanceMethod");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    // TODO
    QSKIP("There's still some work to do before getting this test to pass");

    QByteArray code("module A; class B; def foo; //; end; end; a = B.new.foo;");
    code += "end; b = A::B.new.foo";
    TopDUContext *top = parse(code, "chainedCalls3");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

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

void TestDUChain::super()
{
    QByteArray code("class Base; def foo; 'string'; end; end; class Klass < ");
    code += "Base; def foo; super; end; end";
    TopDUContext *top = parse(code, "super");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    DUContext *ctx = top->localDeclarations().last()->internalContext();
    Declaration *d = ctx->findDeclarations(QualifiedIdentifier("foo")).first();
    QVERIFY(d);
    StructureType::Ptr sType = d->type<FunctionType>()->returnType().cast<StructureType>();
    QVERIFY(sType);
    QCOMPARE(sType->qualifiedIdentifier(), QualifiedIdentifier("String"));
}

// Defines a method with an amazing list of arguments
const QByteArray foo("def foo(a, b = 0, c = 0, *d, e, f, &blk); end; ");

void TestDUChain::guessArgumentsType1()
{
    QByteArray code(foo + "foo 1, 'str', //");
    TopDUContext *top = parse(code, "guessArgumentsType1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *d = top->localDeclarations().first();
    QVector<Declaration *> args = DUChainUtils::argumentContext(d)->localDeclarations();
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
    DUChainWriteLocker lock;

    Declaration *d = top->localDeclarations().first();
    QVector<Declaration *> args = DUChainUtils::argumentContext(d)->localDeclarations();
    QCOMPARE(args.size(), 7);

    // a is just a Fixnum
    QCOMPARE(args.first()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    // b is an Unsure of Fixnum and String
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(args.at(1)->abstractType());
    QStringList list;
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
    DUChainWriteLocker lock;

    Declaration *d = top->localDeclarations().first();
    QVector<Declaration *> args = DUChainUtils::argumentContext(d)->localDeclarations();
    QCOMPARE(args.size(), 7);

    // a is just a Fixnum
    QCOMPARE(args.first()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    // b is an Unsure of Fixnum and String
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(args.at(1)->abstractType());
    QStringList list;
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
    DUChainWriteLocker lock;

    QStringList errors;
    errors << "wrong number of arguments (2 for 3) (ArgumentError)";
    testProblems(top, errors);
}

void TestDUChain::showErrorOnTooManyArguments()
{
    QByteArray code("def foo(a, b); end; foo 1, 2, 3");
    TopDUContext *top = parse(code, "showErrorOnTooManyArguments");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QStringList errors;
    errors << "wrong number of arguments (3 for 2) (ArgumentError)";
    testProblems(top, errors);
}

void TestDUChain::hashArgument()
{
    QByteArray code("def foo(a, *b, c); end; foo 1, 2, 'string', :a => 'a', :b => 1");
    TopDUContext *top = parse(code, "hashArgument");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    Declaration *d = top->localDeclarations().first();
    QVector<Declaration *> args = DUChainUtils::argumentContext(d)->localDeclarations();
    QCOMPARE(args.size(), 3);

    // a
    QCOMPARE(args.first()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));

    // b
    QCOMPARE(args.at(1)->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Array"));
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(args.at(1)->type<ClassType>()->contentType().abstractType());
    QStringList list;
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
    DUChainWriteLocker lock;

    MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(top->localDeclarations().first());
    QVERIFY(md);
    QVector<Declaration *> args = DUChainUtils::argumentContext(md)->localDeclarations();
    QVERIFY(args.size() == 2);
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(args.first()->indexedType().abstractType());
    QStringList list;
    list << "Fixnum" << "String";
    testUnsureTypes(unsure, list);
    QCOMPARE(args.last()->type<StructureType>()->qualifiedIdentifier(), QualifiedIdentifier("Fixnum"));
}

void TestDUChain::conflictOnSpecialMethods()
{
    QByteArray code("module Modul; end; class Klass; extend Modul; ");
    code += "def include; end; private = 1; end";
    TopDUContext *top = parse(code, "conflictOnSpecialMethods");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    QVector<Declaration *> decls = top->localDeclarations();
    ModuleDeclaration *modul = dynamic_cast<ModuleDeclaration *>(decls.first());
    ModuleDeclaration *klass = dynamic_cast<ModuleDeclaration *>(decls.last());
    QVERIFY(modul);
    QVERIFY(klass);

    /*
     * First check that special methods that have been re-declared are being
     * properly handled.
     */

    decls = klass->internalContext()->localDeclarations();
    QCOMPARE(decls.size(), 2);

    MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(decls.first());
    VariableDeclaration *vd = dynamic_cast<VariableDeclaration *>(decls.last());
    QVERIFY(md);
    QVERIFY(vd);
    QCOMPARE(md->qualifiedIdentifier(), QualifiedIdentifier("Klass::include"));
    QCOMPARE(vd->qualifiedIdentifier(), QualifiedIdentifier("Klass::private"));

    /*
     * Finally, check that since the "extend" method hasn't been touched, it
     * should've extended the Klass class as expected.
     */

    QCOMPARE(klass->moduleMixinsSize(), 1u);
    QVERIFY(!klass->moduleMixins()[0].included);
    QCOMPARE(klass->moduleMixins()[0].module.type<StructureType>()->qualifiedIdentifier(), modul->qualifiedIdentifier());
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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

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
    DUChainWriteLocker lock;

    QStringList list;
    list << "TypeError: wrong argument type (expected Module)";
    testProblems(top, list);
}

//END: Include & Extend

}

