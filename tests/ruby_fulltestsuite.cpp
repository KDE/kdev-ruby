/*****************************************************************************
 * Copyright (c) 2007  Michaël Larouche <larouche@kde.org>                   *
 *                                                                           *
 * Permission is hereby granted, free of charge, to any person obtaining     *
 * a copy of this software and associated documentation files (the           *
 * "Software"), to deal in the Software without restriction, including       *
 * without limitation the rights to use, copy, modify, merge, publish,       *
 * distribute, sublicense, and/or sell copies of the Software, and to        *
 * permit persons to whom the Software is furnished to do so, subject to     *
 * the following conditions:                                                 *
 *                                                                           *
 * The above copyright notice and this permission notice shall be            *
 * included in all copies or substantial portions of the Software.           *
 *                                                                           *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,           *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF        *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                     *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE    *
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION    *
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION     *
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.           *
 *****************************************************************************/
#include "ruby_fulltestsuite.h"

// Qt includes
#include <QtCore/QLatin1String>
#include <QtCore/QDebug>

#include "rubytestutils.h"

void Ruby_FullTestSuite::testRuby186TestFile()
{
    QByteArray fileContents = RubyTest_readFile( QLatin1String("ruby186-test.rb") );

    bool hasParsedCorrectly = RubyTest_parseFile(fileContents);

    QVERIFY(hasParsedCorrectly);
}

void Ruby_FullTestSuite::testHelloWorld()
{
    QByteArray fileContents = RubyTest_readFile( QLatin1String("test_helloworld.rb") );

    bool hasParsedCorrectly = RubyTest_parseFile(fileContents);
    QVERIFY(hasParsedCorrectly);
}

QTEST_MAIN(Ruby_FullTestSuite)

#include "ruby_fulltestsuite.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
