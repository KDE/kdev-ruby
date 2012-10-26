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


namespace Ruby
{

ClassDeclaration::ClassDeclaration(ClassDeclarationData& data, const KDevelop::RangeInRevision& range)
    : ModuleDeclaration(data, range)
{
    /* There's nothing to do here */
}

ClassDeclaration::ClassDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *ctx)
    : ModuleDeclaration(*new ClassDeclarationData, range)
{
    d_func_dynamic()->setClassId(this);
    if (ctx)
        setContext(ctx);
}

ClassDeclaration::ClassDeclaration(const ClassDeclaration &rhs)
    : ModuleDeclaration(*new ClassDeclarationData(*rhs.d_func()))
{
    /* There's nothing to do here */
}

void ClassDeclaration::setBaseClass(KDevelop::IndexedType base)
{
    d_func_dynamic()->m_baseClass = base;
}

void ClassDeclaration::clearBaseClass()
{
    bool wasInSymbolTable = inSymbolTable();
    setInSymbolTable(false);
    d_func_dynamic()->m_baseClass = KDevelop::IndexedType(0);
    setInSymbolTable(wasInSymbolTable);
}

KDevelop::IndexedType ClassDeclaration::baseClass() const
{
    return d_func()->m_baseClass;
}

QString ClassDeclaration::toString() const
{
    return "class " + identifier().toString();
}

KDevelop::Declaration * ClassDeclaration::clonePrivate() const
{
    return new ClassDeclaration(*this);
}

} // End of namespace Ruby

