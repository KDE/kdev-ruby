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
#include <QtTest/QTest>
#include <tests/autotestshell.h>
#include <tests/testcore.h>
#include <language/duchain/duchain.h>
#include <language/codegen/coderepresentation.h>
#include <kcomponentdata.h>

// Ruby
#include <duchain/helpers.h>
#include <duchain/tests/duchaintestbase.h>
#include <duchain/editorintegrator.h>
#include <duchain/builders/declarationbuilder.h>
#include <parser/rubyparser.h>
#include <parser/rubyast.h>
#include <rubydefs.h>


using namespace KDevelop;
namespace Ruby
{

DUChainTestBase::DUChainTestBase()
{
    /* There's nothing to do here */
}

TopDUContext * DUChainTestBase::parse(const QByteArray &code, const QString &id)
{
    KUrl url = "/tmp/kdevruby_" + id + ".rb";
    QFile f(url.path());
    f.open(QIODevice::WriteOnly);
    f.write(code);
    f.close();

    RubyParser *parser = new RubyParser();
    parser->setContents(code);
    parser->setCurrentDocument(IndexedString(url));
    RubyAst *ast = parser->parse();

    if (ast == NULL || ast->tree == NULL) {
        debug() << "Parse failed!";
        return NULL;
    }
    return DUChain::self()->waitForUpdate(KDevelop::IndexedString(url),
                                            static_cast<TopDUContext::Features>(TopDUContext::AllDeclarationsContextsAndUses | TopDUContext::ForceUpdate));
}

Declaration * DUChainTestBase::getBuiltinDeclaration(const QString &name, TopDUContext *top, DUContext *ctx)
{
    QStringList list = name.split("#");
    DUContext *context = (ctx) ? ctx : top->childContexts().first();
    AbstractType::Ptr type = getBuiltinsType(list.first(), context);
    StructureType::Ptr sType = StructureType::Ptr::dynamicCast(type);
    Declaration *d = sType->declaration(top);

    QualifiedIdentifier id(list.first() + "::" + list.last());
    QList<Declaration *> decls = d->internalContext()->findDeclarations(id);
    return (decls.isEmpty()) ? NULL : decls.last();
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
