/* This file is part of KDevelop
 *
 * Copyright (C) 2012  Miquel Sabaté <mikisabate@gmail.com>
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


#include <QtTest/QtTest>
#include <completion/tests/completion.h>
#include <completion/context.h>
#include <language/codecompletion/codecompletiontesthelper.h>


QTEST_MAIN(Ruby::TestCompletion)

using namespace KDevelop;
namespace Ruby
{

//BEGIN: Helper structures
typedef CodeCompletionItemTester<CodeCompletionContext> BaseRubyCompletionTester;

class RubyCompletionTester : public BaseRubyCompletionTester
{
public:
    RubyCompletionTester(DUContext *context, QString text = "; ", QString followingText = "",
                         CursorInRevision position = CursorInRevision::invalid())
        : BaseRubyCompletionTester(context, text, followingText, position)
    {
        /* There's nothing to do here */
    }
};

const QByteArray testBase(
    "class Base\n"
    "   def somewhere; end\n"
    "   def over; end\n"
    "   protected\n"
    "   def the; end\n"
    "   private\n"
    "   def rainbow; end\n"
    "end\n"
);

const QByteArray testKlass(
    "class Klass < Base\n"
    "end\n"
);
//END: Helper structures

TestCompletion::TestCompletion()
{
    /* There's nothing to do here */
}

KDevelop::TopDUContext * TestCompletion::parse(const QByteArray &code, const QString &id)
{
    const QString &name = "completion_" + id;
    return DUChainTestBase::parse(code, name);
}

void TestCompletion::shouldContain(const QStringList &list, const QStringList &shoulda, bool sameSize)
{
    if (sameSize)
        QCOMPARE(list.size(), shoulda.size());
    foreach (const QString &str, shoulda)
        QVERIFY(list.contains(str, Qt::CaseSensitive));
}

void TestCompletion::standardAccess()
{
    QByteArray code("obj = 1; ");
    TopDUContext *top = parse(code, "standardAccess");
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    {
        RubyCompletionTester tester(top, "");
        shouldContain(tester.names, QStringList() << "obj" << "Kernel" << "while");
    }
}

void TestCompletion::baseClass()
{
    QByteArray code("class BaseClass; end;");
    TopDUContext *top = parse(code, "baseClass");
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    {
        RubyCompletionTester tester(top, "class Klass < ");
        shouldContain(tester.names, QStringList() << "BaseClass" << "Object" << "String");
    }
}

void TestCompletion::moduleMixins()
{
    QByteArray code("module Awesome; end; ");
    TopDUContext *top = parse(code, "moduleMixins");
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    {
        RubyCompletionTester tester(top, "module MyModule; include ");
        shouldContain(tester.names, QStringList() << "Awesome" << "Kernel" << "Enumerable");
    }

    {
        RubyCompletionTester tester(top, "module MyModule; extend ");
        shouldContain(tester.names, QStringList() << "Awesome" << "Kernel" << "Enumerable");
    }
}

void TestCompletion::memberAccess()
{
    QByteArray code(testBase);
    TopDUContext *top = parse(code, "memberAccess");
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    {
        RubyCompletionTester tester(top, "obj = Base.new; obj.");
        shouldContain(tester.names, QStringList() << "somewhere" << "over", true);
    }
}

void TestCompletion::checkSubclassing()
{
    QByteArray code(testBase + testKlass);
    TopDUContext *top = parse(code, "checkSubclassing");
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    {
        RubyCompletionTester tester(top, "obj = Klass.new; obj.");
        shouldContain(tester.names, QStringList() << "somewhere" << "over", true);
    }
}

void TestCompletion::classMemberAccess()
{
    QByteArray code("module MyModule; class Klass; end; end\n");
    TopDUContext *top = parse(code, "classMemberAccess");
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    {
        RubyCompletionTester tester(top, "MyModule::");
        shouldContain(tester.names, QStringList() << "Klass", true);
    }
}

void TestCompletion::fileChoose()
{
    QByteArray code("a = 0\n");
    TopDUContext *top = parse(code, "fileChoose");
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    {
        // Using the stdlib. It's ok if you've installed ruby 1.8.x or 1.9.x
        RubyCompletionTester tester(top, "require 'rss/");
        shouldContain(tester.names, QStringList() << "maker/" << "0.9.rb" << "utils.rb");
    }

    {
        // The name used to check if it works is the file containing this same test.
        RubyCompletionTester tester(top, "require_relative '");
        shouldContain(tester.names, QStringList() << "kdevruby_completion_fileChoose.rb");
    }

    PENDING("Test for the require of a gem");
}

} // End of namespace Ruby

