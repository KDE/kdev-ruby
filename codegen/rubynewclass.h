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


#ifndef RUBY_NEWCLASS_H
#define RUBY_NEWCLASS_H


#include <project/projectmodel.h>
#include <language/duchain/types/structuretype.h>
#include <language/codegen/createclass.h>
#include <language/codegen/overridespage.h>


namespace Ruby
{

class RubyNewClass : public KDevelop::ClassGenerator
{
public:
    RubyNewClass(KDevelop::ProjectBaseItem* parentItem);
    virtual KDevelop::DocumentChangeSet generate();

    virtual KDevelop::StructureType::Ptr objectType() const;

    const KDevelop::ProjectBaseItem * parentItem() const;

private:
    KDevelop::ProjectBaseItem *m_parentItem;
};

class RubyNewClassWizard : public KDevelop::CreateClassWizard
{
public:
    RubyNewClassWizard(QWidget *parent, RubyNewClass *gen, KUrl baseUrl = KUrl());

    virtual KDevelop::ClassIdentifierPage * newIdentifierPage();
    virtual KDevelop::OverridesPage * newOverridesPage();
};

class RubyOverridesPage : public KDevelop::OverridesPage
{
  Q_OBJECT

public:
    RubyOverridesPage(KDevelop::ClassGenerator *gen, QWizard *parent);

    virtual void populateOverrideTree(const QList<KDevelop::DeclarationPointer> & baseList);
};


}


#endif /* RUBY_NEWCLASS_H */
