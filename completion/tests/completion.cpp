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

void TestCompletion::baseClass()
{
    PENDING("Leave it as pending by now");
}

} // End of namespace Ruby

