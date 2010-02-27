/*
* This file is part of KDevelop
*
* Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
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
#include "duchain.h"

#include <QtTest/QtTest>

#include <language/duchain/types/structuretype.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>

#include "parser/parser.h"
#include "duchain/editorintegrator.h"
#include "duchain/declarationbuilder.h"

using namespace KDevelop;

QTEST_MAIN(Ruby::TestDUChain)

namespace Ruby {

TestDUChain::TestDUChain()
    :QObject()
{
}

TopDUContext* TestDUChain::parse(const QString& input)
{
    Parser *parser = new Parser();
    ProgramAST *programAST = parser->parse(input);
    EditorIntegrator editor;
    DeclarationBuilder builder;
    builder.setEditor(&editor);
    TopDUContext* top = builder.build(IndexedString("file:///internal"), programAST);
    delete programAST;
    return top;
}

void TestDUChain::declareFunction()
{
    QString input = "\
        def foo(a, b)\n\
        end\n\
    ";

    TopDUContext* top = parse(input);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    QCOMPARE(top->childContexts().count(), 1);
    QCOMPARE(top->localDeclarations().count(), 1);

    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec);
    QCOMPARE(dec->context(), top);

    QCOMPARE(dec->toString(), QString(" foo (mixed, mixed)"));

    FunctionType::Ptr ftype = FunctionType::Ptr::dynamicCast(dec->abstractType());
    QVERIFY(ftype);
    QCOMPARE(ftype->arguments().length(), 2);

    QCOMPARE(top->childContexts().at(0)->type(), DUContext::Function);
}

void TestDUChain::declareInstanceFunction()
{
    QString input = "\
    class Foo\n\
        def foo(a, b)\n\
        end\n\
    end\n\
    ";

    TopDUContext* top = parse(input);
    DUChainReleaser releaseTop(top);
    DUChainWriteLocker lock(DUChain::lock());

    //check class
    QCOMPARE(top->childContexts().count(), 1);
    QCOMPARE(top->localDeclarations().count(), 1);

    Declaration* dec = top->localDeclarations().at(0);
    QVERIFY(dec);
    QCOMPARE(dec->context(), top);
    QCOMPARE(top->childContexts().at(0)->type(), DUContext::Class);

    StructureType::Ptr stype = StructureType::Ptr::dynamicCast(dec->abstractType());
    QVERIFY(stype);

    //check instance function
    DUContext *functionContext = top->childContexts().at(0);
    QVERIFY(functionContext);

    Declaration* funDec = functionContext->localDeclarations().at(0);
    QVERIFY(funDec);
    QCOMPARE(funDec->context(), functionContext);
    QCOMPARE(functionContext->type(), DUContext::Class);
    QCOMPARE(functionContext->childContexts().at(0)->type(), DUContext::Function);

    QCOMPARE(funDec->toString(), QString(" foo (mixed, mixed)"));

    //check function arguments
    FunctionType::Ptr ftype = FunctionType::Ptr::dynamicCast(funDec->abstractType());
    QVERIFY(ftype);
    QCOMPARE(ftype->arguments().length(), 2);
}

}

#include "duchain.moc"
