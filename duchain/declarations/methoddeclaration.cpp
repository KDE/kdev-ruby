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


#include <language/duchain/duchainregister.h>
#include <duchain/declarations/methoddeclaration.h>
#include <duchain/helpers.h>


namespace Ruby
{
REGISTER_DUCHAIN_ITEM(MethodDeclaration);
DEFINE_LIST_MEMBER_HASH(MethodDeclarationData, yieldTypes, YieldType)


MethodDeclaration::MethodDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *ctx)
    : KDevelop::FunctionDeclaration(*new MethodDeclarationData)
{
    setRange(range);
    d_func_dynamic()->setClassId(this);
    if (ctx)
        setContext(ctx);
}

MethodDeclaration::MethodDeclaration(const MethodDeclaration &rhs)
    : KDevelop::FunctionDeclaration(*new MethodDeclarationData(*rhs.d_func()))
{
    /* There's nothing to do here */
}

MethodDeclaration::MethodDeclaration(MethodDeclarationData &data)
    : KDevelop::FunctionDeclaration(data)
{
    /* There's nothing to do here */
}

bool MethodDeclaration::isClassMethod() const
{
    return d_func()->classMethod;
}

void MethodDeclaration::setClassMethod(const bool isClass)
{
    d_func_dynamic()->classMethod = isClass;
}

KDevelop::Declaration::AccessPolicy MethodDeclaration::accessPolicy() const
{
    return d_func()->m_accessPolicy;
}

void MethodDeclaration::setAccessPolicy(const KDevelop::Declaration::AccessPolicy &policy)
{
    d_func_dynamic()->m_accessPolicy = policy;
}

void MethodDeclaration::clearYieldTypes()
{
    bool wasInSymbolTable = inSymbolTable();
    setInSymbolTable(false);
    d_func_dynamic()->yieldTypesList().clear();
    setInSymbolTable(wasInSymbolTable);
}

void MethodDeclaration::replaceYieldTypes(YieldType yield, uint n)
{
    bool wasInSymbolTable = inSymbolTable();

    setInSymbolTable(false);
    if (n < d_func()->yieldTypesSize()) {
        IndexedType old = d_func_dynamic()->yieldTypesList()[n].type;
        YieldType res;
        AbstractType::Ptr merged = mergeTypes(old.abstractType(), yield.type.abstractType());
        res.type = merged.unsafeData()->indexed();
        d_func_dynamic()->yieldTypesList()[n] = res;
    } else
        d_func_dynamic()->yieldTypesList().append(yield);
    setInSymbolTable(wasInSymbolTable);
}

const YieldType* MethodDeclaration::yieldTypes() const
{
    return d_func()->yieldTypes();
}

uint MethodDeclaration::yieldTypesSize()
{
    return d_func()->yieldTypesSize();
}

KDevelop::Declaration* MethodDeclaration::clonePrivate() const
{
    return new MethodDeclaration(*this);
}

} // End of namespace Ruby
