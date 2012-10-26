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

#include <KTemporaryFile>

#include <codegen/rubynewclass.h>
#include <language/codegen/documentchangeset.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>

#include <rubydefs.h>


namespace Ruby
{
using namespace KDevelop;

RubyClassHelper::RubyClassHelper()
    :ICreateClassHelper()
{
}

RubyClassHelper::~RubyClassHelper()
{
}

TemplateClassGenerator* RubyClassHelper::createGenerator(const KUrl& baseUrl)
{
    return new RubyNewClass(baseUrl);
}

QList<DeclarationPointer> RubyClassHelper::defaultMethods(const QString& name) const
{
    KTemporaryFile file;
    file.setSuffix(".rb");
    file.setAutoRemove(false);
    file.open();
    QTextStream stream(&file);
    stream << "class " << name << "\n"
        // constructor
        << "  def initialize\n  end\n"
        // serializer to string
        << "  def to_s\n  end\nend";
    file.close();

    ReferencedTopDUContext context(DUChain::self()->waitForUpdate(
        IndexedString(file.fileName()),
        KDevelop::TopDUContext::AllDeclarationsAndContexts));
    DUChainReadLocker lock;

    QList<DeclarationPointer> methods;

    if (!context || !context->childContexts().size() == 1) {
        kWarning() << "invalid context for generated ruby file with default methods" << file.fileName();
    } else {
        foreach (Declaration* declaration, context->childContexts().first()->localDeclarations()) {
            methods << DeclarationPointer(declaration);
        }
    }

    file.remove();
    return methods;
}


RubyNewClass::RubyNewClass(KUrl url)
    :TemplateClassGenerator(url)
{
}

KDevelop::DocumentChangeSet RubyNewClass::generate()
{
    return TemplateClassGenerator::generate();
}

}
