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


#include <codegen/rubynewclass.h>
#include <language/codegen/documentchangeset.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <KTemporaryFile>
#include <KLocale>
#include <QTreeWidgetItem>
#include <rubydefs.h>


namespace Ruby
{
using namespace KDevelop;

RubyNewClass::RubyNewClass(KDevelop::ProjectBaseItem *parentItem)
    : m_parentItem(parentItem)
{
    /* There's nothing to do here */
}

KDevelop::DocumentChangeSet RubyNewClass::generate()
{
    /* TODO */
    KDevelop::DocumentChangeSet changes;
    return changes;
}

KDevelop::StructureType::Ptr RubyNewClass::objectType() const
{
    /* TODO: fix this */
    return KDevelop::StructureType::Ptr(NULL);
}

const KDevelop::ProjectBaseItem * RubyNewClass::parentItem() const
{
    return m_parentItem;
}

RubyNewClassAssistant::RubyNewClassAssistant(QWidget *parent, RubyNewClass *gen, KUrl baseUrl)
    : KDevelop::CreateClassAssistant(parent, gen, baseUrl)
{
    setup();
}

KDevelop::ClassIdentifierPage* RubyNewClassAssistant::newIdentifierPage()
{
    /* TODO: Under construction */
    return new KDevelop::ClassIdentifierPage(this);
}

KDevelop::OverridesPage* RubyNewClassAssistant::newOverridesPage()
{
    return new RubyOverridesPage(generator(), this);
}

RubyOverridesPage::RubyOverridesPage(KDevelop::ClassGenerator *gen, QWidget *parent)
    : KDevelop::OverridesPage(gen, parent)
{
    /* There's nothing to do here */
}

void RubyOverridesPage::populateOverrideTree(const QList<KDevelop::DeclarationPointer> & baseList)
{
    /* TODO: read the TODO from the RubyOverridesPage class declaration */
    OverridesPage::populateOverrideTree(baseList);

    // Generate ruby code with some default methods
    const QString newClass = generator()->name();
    KTemporaryFile file;
    file.setSuffix(".rb");
    file.setAutoRemove(false);
    file.open();
    QTextStream stream(&file);
    stream << "class " << newClass << "\n"
        << "  def initialize\n  end\n" << "  def to_s\n  end\nend";
    file.close();

    ReferencedTopDUContext context(DUChain::self()->waitForUpdate(IndexedString(file.fileName()),
                                                                KDevelop::TopDUContext::AllDeclarationsAndContexts));
    DUChainReadLocker lock;
    if (!context || !context->childContexts().size() == 1) {
        kWarning() << "invalid context for generated ruby file with default methods" << file.fileName();
        file.remove();
        return;
    }

    QTreeWidgetItem *items = new QTreeWidgetItem(overrideTree(), QStringList() << i18n("Default methods"));
    foreach (Declaration *decl, context->childContexts().first()->localDeclarations())
        OverridesPage::addPotentialOverride(items, DeclarationPointer(decl));

    file.remove();
}

}

