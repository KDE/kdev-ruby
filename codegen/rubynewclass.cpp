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
#include <duchain/types/objecttype.h>
#include <language/codegen/documentchangeset.h>
#include <KTemporaryFile>


namespace Ruby
{

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
    /* TODO: let it be ObjectType for now */
    return KDevelop::StructureType::Ptr(new ObjectType);
}

const KDevelop::ProjectBaseItem * RubyNewClass::parentItem() const
{
    return m_parentItem;
}

RubyNewClassWizard::RubyNewClassWizard(QWidget *parent, RubyNewClass *gen, KUrl baseUrl)
    : KDevelop::CreateClassWizard(parent, gen, baseUrl)
{
    setup();
}

KDevelop::ClassIdentifierPage* RubyNewClassWizard::newIdentifierPage()
{
    /*
     * TODO: Idea:
     *  - The user can somehow tell KDevelop that this is a class
     *  following Rails conventions so we can:
     *    -> Autocomplete the name of the class somehow :P
     *    -> Guess the superclass
     *    -> Guess the url
     */
    return NULL;
}

KDevelop::OverridesPage* RubyNewClassWizard::newOverridesPage()
{
    return new RubyOverridesPage(generator(), this);
}

RubyOverridesPage::RubyOverridesPage(KDevelop::ClassGenerator *gen, QWizard *parent)
    : KDevelop::OverridesPage(gen, parent)
{
    /* There's nothing to do here */
}

void RubyOverridesPage::populateOverrideTree(const QList<KDevelop::DeclarationPointer> & baseList)
{
    KDevelop::OverridesPage::populateOverrideTree(baseList);

    // Generate ruby code with some default methods
    const QString newClass = generator()->name();
    KTemporaryFile file;
    file.setSuffix(".rb");
    file.setAutoRemove(false);
    file.open();
    QTextStream stream(&file);
    stream << "class " << newClass << "\n"
        << "def initialize; end\n" << "def to_s; end\n end";
    file.close();

    /* TODO: get context, declarations and populate the tree */

    file.remove();
}

}

