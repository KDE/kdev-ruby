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
#include <duchain/helpers.h>
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

//BEGIN: Basic stuff

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
    QByteArray code("def foo; end; alias asd foo ");
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

void TestUseBuilder::instanceVariable()
{
    //               0         1         2         3         4         5         6         7
    //               012345678901234567890123456789012345678901234567890123456789012345678901
    QByteArray code("class Klass; def foo; @lala = 1; end; def asd; @lala = 'asd'; end; end; ");
    //               8         9         10
    //       23456789012345678901234567890123456
    code += "class SubClass < Klass; @lala; end";
    TopDUContext *top = parse(code, "instanceVariable");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *decl = top->localDeclarations().first();
    decl = decl->internalContext()->findDeclarations(QualifiedIdentifier("@lala")).first();
    QVERIFY(decl);
    QList<RangeInRevision> list;
    list << RangeInRevision(0, 22, 0, 27) << RangeInRevision(0, 47, 0, 52)
         << RangeInRevision(0, 96, 0, 101);
    compareUses(decl, list);
}

void TestUseBuilder::classVariable()
{
    //               0         1         2         3         4         5         6
    //               0123456789012345678901234567890123456789012345678901234567890
    QByteArray code("class Base; @@lala = 1; end; class Klass < Base; @@lala; end");
    TopDUContext *top = parse(code, "classVariable");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *decl = top->localDeclarations().first();
    decl = decl->internalContext()->findDeclarations(QualifiedIdentifier("@@lala")).first();
    QVERIFY(decl);
    QList<RangeInRevision> list;
    list << RangeInRevision(0, 12, 0, 18) << RangeInRevision(0, 49, 0, 55);
    compareUses(decl, list);
}

void TestUseBuilder::exceptions()
{
    //               0         1         2         3         4         5         6
    //               012345678901234567890123456789012345678901234567890123456789012
    QByteArray code("def defas; a = 1; 1 / 0; rescue ZeroDivisionError; puts a; end");
    TopDUContext *top = parse(code, "exceptions");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // a
    Declaration *decl = top->localDeclarations().first();
    Declaration *a = decl->internalContext()->localDeclarations().first();
    compareUses(a, RangeInRevision(0, 56, 0, 57));

    // ZeroDivisionError
    QualifiedIdentifier id("ZeroDivisionError");
    Declaration *zero = decl->topContext()->findDeclarations(id).first();
    compareUses(zero, RangeInRevision(0, 32, 0, 49));
}

//END: Basic stuff

//BEGIN: Contexts

void TestUseBuilder::block()
{
    //               0         1         2         3         4
    //               01234567890123456789012345678901234567890123456
    QByteArray code("a = ''; 5.times do |a, b|; puts a; puts b; end");
    TopDUContext *top = parse(code, "block");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // Outer "a" has no uses
    Declaration *a = top->localDeclarations().first();
    QCOMPARE(a->uses().count(), 0);

    // Inner a
    DUContext *block = top->topContext()->childContexts().first();
    a = block->localDeclarations().first();
    QCOMPARE(a->range(), RangeInRevision(0, 20, 0, 21));
    compareUses(a, RangeInRevision(0, 32, 0, 33));
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

void TestUseBuilder::checkMethodLocalDeclarations()
{
    //               0         1         2
    //               01234567890123456789012345
    QByteArray code("a = 0; def foo(a); a; end");
    TopDUContext *top = parse(code, "checkMethodLocalDeclarations");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // Outer "a" has no uses
    Declaration *a = top->localDeclarations().first();
    QCOMPARE(a->uses().count(), 0);

    // Inner a
    DUContext *method = top->topContext()->childContexts().first();
    a = method->localDeclarations().first();
    QCOMPARE(a->range(), RangeInRevision(0, 15, 0, 16));
    compareUses(a, RangeInRevision(0, 19, 0, 20));
}

void TestUseBuilder::globals()
{
    //               0         1         2         3         4         5         6         7         8
    //               01234567890123456789012345678901234567890123456789012345678901234567890123456789012
    QByteArray code("$a = 1; def foo; $a; end; class Klass; def foo; $a; end; end; module Modul; $a; end");
    TopDUContext *top = parse(code, "globals");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    // Let there be the $a variable.
    Declaration *a = top->localDeclarations().first();
    QVERIFY(a);
    QCOMPARE(a->qualifiedIdentifier(), QualifiedIdentifier("$a"));

    // Let there be uses.
    QList<RangeInRevision> ranges;
    ranges << RangeInRevision(0, 17, 0, 19) << RangeInRevision(0, 48, 0, 50)
           << RangeInRevision(0, 76, 0, 78);
    compareUses(a, ranges);
}

void TestUseBuilder::defaultGlobals()
{
    //               0         1
    //               01234567890123456789
    QByteArray code("def foo; $stdin; end");
    TopDUContext *top = parse(code, "defaultGlobals");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    // Get the declaration of the $stdin default global variable.
    QList<Declaration *> decls = top->findDeclarations(QualifiedIdentifier("$stdin"));
    QCOMPARE(decls.size(), 1);

    QList<RangeInRevision> ranges;
    ranges << RangeInRevision(0, 9, 0, 15);
    compareUses(decls.first(), ranges);
}

void TestUseBuilder::classModulesScopes()
{
    // module Klass
    // end
    //
    // module Modul
    // end
    //
    // class Modul::Klass
    //   ::Klass
    //
    //   module Thing
    //     Klass
    //     ::Klass
    //   end
    // end
    //
    // ::Klass
    // Modul::Klass

    // TODO: it's failing !!!!

    //               0         1         2         3         4         5
    //               012345678901234567890123456789012345678901234567890123456
    QByteArray code("module Klass; end; module Modul; end; class Modul::Klass;");
    //          6         7         8         9        10        11        12
    //       78901234567890123456789012345678901234567890123456789012345678901234567
    code += " ::Klass; module Thing; Klass; ::Klass; end; end; ::Klass; Modul::Klass";
    TopDUContext *top = parse(code, "classModulesScopes");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    // Klass
    Declaration *d = top->localDeclarations().first();
    QVERIFY(d);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("Klass"));
    QList<RangeInRevision> ranges;
    ranges << RangeInRevision(0, 60, 0, 65) << RangeInRevision(0, 90, 0, 95);
    ranges << RangeInRevision(0, 109, 0, 114);
    compareUses(d, ranges);

    // Modul
    d = top->localDeclarations().at(1);
    QVERIFY(d);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("Modul"));
    ranges.clear();
    ranges << RangeInRevision(0, 44, 0, 49) << RangeInRevision(0, 116, 0, 121);
    compareUses(d, ranges);

    // Modul::Klass
    d = d->internalContext()->localDeclarations().first();
    QVERIFY(d);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("Modul::Klass"));
    ranges.clear();
    ranges << RangeInRevision(0, 81, 0, 86) << RangeInRevision(0, 123, 0, 128);
    compareUses(d, ranges);
}

//END: Contexts

//BEGIN: Method calls

void TestUseBuilder::builtinUses()
{
    //               0          1        2
    //               012345678901234567890123
    QByteArray code("a = 0; a.zero?; 1.zero?");
    TopDUContext *top = parse(code, "builtinUses");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // a
    Declaration *d = top->localDeclarations().first();
    QVERIFY(d);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("a"));
    compareUses(d, RangeInRevision(0, 7, 0, 8));

    // zero?
    d = getBuiltinDeclaration("Fixnum#zero?", top, d->context());
    QVERIFY(d);
    QList<RangeInRevision> ranges;
    ranges << RangeInRevision(0, 9, 0, 14) << RangeInRevision(0, 18, 0, 23);
    compareUses(d, ranges);
}

void TestUseBuilder::chained()
{
    //               0         1         2         3         4         5
    //               012345678901234567890123456789012345678901234567890
    QByteArray code("module Modul; class Klass; def self.selfish(a, b); ");
    //                6         7         8         9         0         1
    //       12345678901234567890123456789012345678901234567890123456789012345678
    code += "'string'; end; end; end; a = 0; Modul::Klass.selfish(a, 1).bytesize ";
    TopDUContext *top = parse(code, "chained");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // Module
    Declaration *d = top->localDeclarations().first();
    QVERIFY(d);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("Modul"));
    QCOMPARE(d->uses().count(), 1);
    compareUses(d, RangeInRevision(0, 83, 0, 88));

    // Modul::Klass
    d = d->internalContext()->localDeclarations().first();
    QVERIFY(d);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("Modul::Klass"));
    QCOMPARE(d->uses().count(), 1);
    compareUses(d, RangeInRevision(0, 90, 0, 95));

    // Modul::Klass.selfish
    d = d->internalContext()->localDeclarations().first();
    QVERIFY(d);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("Modul::Klass::selfish"));
    QCOMPARE(d->uses().count(), 1);
    compareUses(d, RangeInRevision(0, 96, 0, 103));

    // a
    d = top->localDeclarations().last();
    QVERIFY(d);
    QCOMPARE(d->qualifiedIdentifier(), QualifiedIdentifier("a"));
    QCOMPARE(d->uses().count(), 1);
    compareUses(d, RangeInRevision(0, 104, 0, 105));

    // String#bytesize
    d = getBuiltinDeclaration("String#bytesize", top);
    QVERIFY(d);
    QCOMPARE(d->uses().count(), 1);
    compareUses(d, RangeInRevision(0, 110, 0, 118));
}

void TestUseBuilder::fromClassAndAbove()
{
    //               0         1         2         3
    //               01234567890123456789012345678901234
    QByteArray code("class Klass; attr_reader :asd; end");
    TopDUContext *top = parse(code, "fromClassAndAbove");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // Module#attr_reader
    Declaration *d = getBuiltinDeclaration("Module#attr_reader", top);
    QVERIFY(d);
    compareUses(d, RangeInRevision(0, 13, 0, 24));
}

void TestUseBuilder::super()
{
    //               0         1         2         3         4         5
    //               0123456789012345678901234567890123456789012345678901234
    QByteArray code("class Base; def foo; 'string'; end; end; class Klass < ");
    //            6         7         8         9
    //       5678901234567890123456789012345678901234
    code += "Base; def foo; super.bytesize; end; end";
    TopDUContext *top = parse(code, "super");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *d = getBuiltinDeclaration("String#bytesize", top);
    QVERIFY(d);
    compareUses(d, RangeInRevision(0, 76, 0, 84));
}

void TestUseBuilder::moduleMixins1()
{
    //               0         1         2         3         4         5
    //               0123456789012345678901234567890123456789012345678901234567890
    QByteArray code("module A; end; class Klass; include Enumerable; extend A; end");
    TopDUContext *top = parse(code, "moduleMixins1");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *d = top->localDeclarations().first();
    QVERIFY(d);
    compareUses(d, RangeInRevision(0, 55, 0, 56));

    AbstractType::Ptr type = getBuiltinsType(QString("Enumerable"), top);
    StructureType::Ptr sType = type.cast<StructureType>();
    QVERIFY(sType);
    d = sType->declaration(top);
    QVERIFY(d);
    compareUses(d, RangeInRevision(0, 36, 0, 46));
}

void TestUseBuilder::moduleMixins2()
{
    //               0         1         2         3         4         5
    //               012345678901234567890123456789012345678901234567890123456
    QByteArray code("module A; module B; end; end; module C; include A::B; end");
    TopDUContext *top = parse(code, "moduleMixins2");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock;

    // module A
    Declaration *d = top->localDeclarations().first();
    QVERIFY(d);
    compareUses(d, RangeInRevision(0, 48, 0, 49));

    // module B
    d = d->internalContext()->localDeclarations().first();
    QVERIFY(d);
    compareUses(d, RangeInRevision(0, 51, 0, 52));
}

void TestUseBuilder::exprIsCalling()
{
    //               0         1         2
    //               012345678901234567890123456
    QByteArray code("a = 0; b = 0; (a - b).to_s ");
    TopDUContext *top = parse(code, "exprIsCalling");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // a
    Declaration *d = top->localDeclarations().first();
    QVERIFY(d);
    compareUses(d, RangeInRevision(0, 15, 0, 16));

    // b
    d = top->localDeclarations().last();
    QVERIFY(d);
    compareUses(d, RangeInRevision(0, 19, 0, 20));

    // to_s
    d = getBuiltinDeclaration("Fixnum#to_s", top, d->context());
    QVERIFY(d);
    compareUses(d, RangeInRevision(0, 22, 0, 26));
}

void TestUseBuilder::stringCalling()
{
    //               0         1         2         3
    //               0123456789012345678901234567890123456789
    QByteArray code("calling = 0; `String is #{calling}`.foo");
    TopDUContext *top = parse(code, "stringCalling");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    // calling
    Declaration *d = top->localDeclarations().first();
    QVERIFY(d);
    compareUses(d, RangeInRevision(0, 26, 0, 33));
}

//END: Method calls

//BEGIN: Others

void TestUseBuilder::nestedIdentifier()
{
    //               0         1         2         3         4         5         6
    //               0123456789012345678901234567890123456789012345678901234567890123456789
    QByteArray code("module Modul; end; class Modul::Klass; end; module Modul::Nodule; end");
    TopDUContext *top = parse(code, "nestedIdentifier");
    DUChainReleaser releaser(top);
    DUChainWriteLocker lock(DUChain::lock());

    Declaration *d = top->localDeclarations().first();
    QVERIFY(d);
    QList<RangeInRevision> list;
    list << RangeInRevision(0, 25, 0, 30) << RangeInRevision(0, 51, 0, 56);
    compareUses(d, list);
}

//END: Others

} // End of namespace Ruby


#include "uses.moc"
