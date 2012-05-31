/* This file is part of KDevelop
 *
 * Copyright (C) 2011  Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include <duchain/declarations/classdeclaration.h>
#include <language/duchain/identifier.h>
#include <language/duchain/declaration.h>
#include <language/duchain/appendedlist.h>
#include <language/duchain/duchainregister.h>


namespace Ruby
{

// REGISTER_DUCHAIN_ITEM(ClassDeclaration);


ClassDeclaration::ClassDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *ctx)
    : ModuleDeclaration(range, ctx)
{
}

ClassDeclaration::ClassDeclaration(const ClassDeclaration &rhs)
    : ModuleDeclaration(rhs)
{
    m_baseClass = rhs.baseClass();
}

ClassDeclaration::ClassDeclaration(ModuleDeclarationData &data)
    : ModuleDeclaration(data)
{

}

void ClassDeclaration::setBaseClass(KDevelop::IndexedType base)
{
    m_baseClass = base;
}

void ClassDeclaration::clearBaseClass()
{
    m_baseClass = KDevelop::IndexedType(0);
}

KDevelop::IndexedType ClassDeclaration::baseClass() const
{
    return m_baseClass;
}

KDevelop::Declaration * ClassDeclaration::clonePrivate() const
{
    return new ClassDeclaration(*this);
}
/*
QString ClassDeclaration::toString() const
{
    return "class " + identifier().toString();
}*/
/*
void ClassDeclaration::clearModuleMixins()
{
    bool wasInSymbolTable = inSymbolTable();
    setInSymbolTable(false);
    d_func_dynamic()->moduleMixinsList().clear();
    setInSymbolTable(wasInSymbolTable);
}

uint ClassDeclaration::moduleMixinsSize()
{
    return d_func()->moduleMixinsSize();
}

const ModuleMixin * ClassDeclaration::moduleMixins() const
{
    return d_func()->moduleMixins();
}

void ClassDeclaration::addModuleMixin(ModuleMixin module)
{
    bool wasInSymbolTable = inSymbolTable();
    setInSymbolTable(false);
    d_func_dynamic()->moduleMixinsList().append(module);
    setInSymbolTable(wasInSymbolTable);
}*/

} // End of namespace Ruby

