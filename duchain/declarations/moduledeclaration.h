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


#ifndef MODULE_DECLARATION_H
#define MODULE_DECLARATION_H


#include <duchain/duchainexport.h>
#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>


namespace Ruby
{

struct KDEVRUBYDUCHAIN_EXPORT ModuleMixin {
    KDevelop::IndexedType module;
    bool included;
};

KDEVPLATFORMLANGUAGE_EXPORT DECLARE_LIST_MEMBER_HASH(ModuleDeclarationData, moduleMixins, ModuleMixin)

class KDEVRUBYDUCHAIN_EXPORT ModuleDeclarationData : public KDevelop::DeclarationData
{
public:
    ModuleDeclarationData()
    {
        initializeAppendedLists();
    }

    ModuleDeclarationData(const ModuleDeclarationData &rhs) : KDevelop::DeclarationData(rhs)
    {
        initializeAppendedLists();
        copyListsFrom(rhs);
    }

    ~ModuleDeclarationData()
    {
        freeAppendedLists();
    }

    START_APPENDED_LISTS_BASE(ModuleDeclarationData, KDevelop::DeclarationData);
    APPENDED_LIST_FIRST(ModuleDeclarationData, ModuleMixin, moduleMixins);
    END_APPENDED_LISTS(ModuleDeclarationData, moduleMixins);
};


class KDEVRUBYDUCHAIN_EXPORT ModuleDeclaration : public KDevelop::Declaration
{
public:
    ModuleDeclaration(const ModuleDeclaration &rhs);
    ModuleDeclaration(ModuleDeclarationData &data);
    ModuleDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *context);
    ~ModuleDeclaration();

    void clearModuleMixins();
    uint moduleMixinsSize();
    const ModuleMixin * moduleMixins() const;
    void addModuleMixin(ModuleMixin module);

    QString toString() const;

    enum { Identity = 44 };

private:
    virtual KDevelop::Declaration * clonePrivate() const;
    DUCHAIN_DECLARE_DATA(ModuleDeclaration)
};

} // End of namespace Ruby


Q_DECLARE_TYPEINFO(Ruby::ModuleMixin, Q_MOVABLE_TYPE); // TODO: check this


#endif /* MODULE_DECLARATION_H */
