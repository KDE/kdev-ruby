/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#include <duchain/declarations/moduledeclaration.h>
#include <language/duchain/duchainregister.h>


namespace Ruby
{

REGISTER_DUCHAIN_ITEM(ModuleDeclaration);
DEFINE_LIST_MEMBER_HASH(ModuleDeclarationData, moduleMixins, ModuleMixin)
DEFINE_LIST_MEMBER_HASH(ModuleDeclarationData, mixers, ModuleMixin)

ModuleDeclaration::ModuleDeclaration(ModuleDeclarationData &data, const KDevelop::RangeInRevision &range)
    : KDevelop::Declaration(data, range)
{
    /* There's nothing to do here */
}

ModuleDeclaration::ModuleDeclaration(const ModuleDeclaration &rhs)
    : KDevelop::Declaration(*new ModuleDeclarationData(*rhs.d_func()))
{
    /* There's nothing to do here */
}

ModuleDeclaration::ModuleDeclaration(ModuleDeclarationData &data)
    : KDevelop::Declaration(data)
{
    /* There's nothing to do here */
}

ModuleDeclaration::ModuleDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *context)
    : KDevelop::Declaration(*new ModuleDeclarationData, range)
{
    d_func_dynamic()->setClassId(this);
    if (context) {
        setContext(context);
    }
}

void ModuleDeclaration::clearModuleMixins()
{
    bool wasInSymbolTable = inSymbolTable();
    setInSymbolTable(false);
    d_func_dynamic()->moduleMixinsList().clear();
    setInSymbolTable(wasInSymbolTable);
}

uint ModuleDeclaration::moduleMixinsSize()
{
    return d_func()->moduleMixinsSize();
}

const ModuleMixin * ModuleDeclaration::moduleMixins() const
{
    return d_func()->moduleMixins();
}

void ModuleDeclaration::addModuleMixin(ModuleMixin module)
{
    bool wasInSymbolTable = inSymbolTable();
    setInSymbolTable(false);
    if (!mixinExists(module, false))
        d_func_dynamic()->moduleMixinsList().append(module);
    setInSymbolTable(wasInSymbolTable);
}

void ModuleDeclaration::clearMixers()
{
    bool wasInSymbolTable = inSymbolTable();
    setInSymbolTable(false);
    d_func_dynamic()->mixersList().clear();
    setInSymbolTable(wasInSymbolTable);
}

uint ModuleDeclaration::mixersSize()
{
    return d_func()->mixersSize();
}

const ModuleMixin* ModuleDeclaration::mixers() const
{
    return d_func()->mixers();
}

void ModuleDeclaration::addMixer(ModuleMixin module)
{
    bool wasInSymbolTable = inSymbolTable();
    setInSymbolTable(false);
    if (!mixinExists(module, true)) {
        d_func_dynamic()->mixersList().append(module);
    }
    setInSymbolTable(wasInSymbolTable);
}

bool ModuleDeclaration::isModule() const
{
    return d_func()->isModule;
}

void ModuleDeclaration::setIsModule(bool isModule)
{
    d_func_dynamic()->isModule = isModule;
}

void ModuleDeclaration::setBaseClass(KDevelop::IndexedType base)
{
    d_func_dynamic()->baseClass = base;
}

void ModuleDeclaration::setEigenClass(KDevelop::DUContext *ctx)
{
    d_func_dynamic()->eigenClass = ctx;
}

void ModuleDeclaration::clearBaseClass()
{
    bool wasInSymbolTable = inSymbolTable();
    setInSymbolTable(false);
    d_func_dynamic()->baseClass = KDevelop::IndexedType();
    setInSymbolTable(wasInSymbolTable);
}

KDevelop::IndexedType ModuleDeclaration::baseClass() const
{
    return d_func()->baseClass;
}

KDevelop::DUContext * ModuleDeclaration::eigenClass() const
{
    return d_func()->eigenClass;
}

QString ModuleDeclaration::toString() const
{
    return ((isModule()) ? "module " : "class ") + identifier().toString();
}

bool ModuleDeclaration::mixinExists(ModuleMixin module, bool who)
{
    const ModuleMixin *list;
    uint size;
    if (who) {
        list = d_func()->mixers();
        size = d_func()->mixersSize();
    } else {
        list = d_func()->moduleMixins();
        size = d_func()->moduleMixinsSize();
    }

    for (uint i = 0; i < size; i++) {
        if (list[i].module == module.module) {
            return true;
        }
    }
    return false;
}

KDevelop::Declaration * ModuleDeclaration::clonePrivate() const
{
    return new ModuleDeclaration(*this);
}

} // End of namespace Ruby
