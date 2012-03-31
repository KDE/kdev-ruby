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


// KDevelop
#include <tests/autotestshell.h>
#include <tests/testcore.h>
#include <language/duchain/duchain.h>
#include <language/codegen/coderepresentation.h>

// Ruby
#include <duchain/tests/duchaintestbase.h>
#include <duchain/editorintegrator.h>
#include <duchain/builders/declarationbuilder.h>
#include <parser/rubyparser.h>
#include <parser/rubyast.h>
#include <rubydefs.h>


using namespace KDevelop;
namespace Ruby
{

TopDUContext *DUChainTestBase::parse(const QByteArray &code)
{
    static int testNumber = 0;
    QString url = QString("file:///internal/%1").arg(testNumber++);

    RubyParser *parser = new RubyParser();
    parser->setContents(code);
    parser->setCurrentDocument(KUrl(url));
    RubyAst *ast = parser->parse();

    if (ast == NULL || ast->tree == NULL) {
        debug() << "Parse failed!";
        return NULL;
    }
    EditorIntegrator editor;
    editor.setParseSession(parser);
    DeclarationBuilder declarationBuilder;
    TopDUContext *top = declarationBuilder.build(IndexedString(url), ast);

    return top;
}

void DUChainTestBase::initTestCase()
{
  AutoTestShell::init();
  TestCore::initialize(Core::NoUi);

  DUChain::self()->disablePersistentStorage();
  KDevelop::CodeRepresentation::setDiskChangesForbidden(true);
}

void DUChainTestBase::cleanupTestCase()
{
    TestCore::shutdown();
}

}
