/* This file is part of KDevelop
 *
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright 2011 Miquel Sabaté <mikisabate@gmail.com>
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


#include <QtTest/QtTest>

#include <parser/rubyparser.h>
#include <duchain/editorintegrator.h>
#include <duchain/declarationbuilder.h>
#include <duchain/tests/duchain.h>


QTEST_MAIN(Ruby::TestDUChain)
using namespace KDevelop;

namespace Ruby
{

TestDUChain::TestDUChain()
    :QObject()
{
    /* There's nothing to do here */
}

TopDUContext * TestDUChain::parse(const QString & input)
{
    RubyParser * parser = new RubyParser;
    parser->setCurrentDocument(KUrl("internal"));
    parser->setContents(input.toUtf8());
    
    RubyAst * ast = parser->parse();
    EditorIntegrator editor;
    DeclarationBuilder builder;
    builder.setEditor(&editor);
    TopDUContext * top = builder.build(IndexedString("file:///internal"), ast->tree);
    parser->freeAst(ast);
    return top;
}

void TestDUChain::declareFunction()
{
    /* TODO: Under construction */
}

void TestDUChain::declareInstanceFunction()
{
    /* TODO: Under construction */
}

} // End of namespace ruby


#include "duchain.moc"

