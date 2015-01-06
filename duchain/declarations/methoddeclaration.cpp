/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <duchain/declarations/methoddeclaration.h>

#include <duchain/helpers.h>
#include <language/duchain/duchainregister.h>

namespace ruby {

REGISTER_DUCHAIN_ITEM(MethodDeclaration);
DEFINE_LIST_MEMBER_HASH(MethodDeclarationData, yieldTypes, YieldType)

MethodDeclaration::MethodDeclaration(const KDevelop::RangeInRevision &range,
                                     KDevelop::DUContext *ctx)
    : KDevelop::FunctionDeclaration(*new MethodDeclarationData)
{
    setRange(range);
    d_func_dynamic()->setClassId(this);
    if (ctx) {
        setContext(ctx);
    }
}

MethodDeclaration::MethodDeclaration(const MethodDeclaration &rhs)
    : KDevelop::FunctionDeclaration(*new MethodDeclarationData(*rhs.d_func()))
{
}

MethodDeclaration::MethodDeclaration(MethodDeclarationData &data)
    : KDevelop::FunctionDeclaration(data)
{
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
    return d_func()->accessPolicy;
}

void MethodDeclaration::setAccessPolicy(const KDevelop::Declaration::AccessPolicy &policy)
{
    d_func_dynamic()->accessPolicy = policy;
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
        KDevelop::IndexedType old = d_func_dynamic()->yieldTypesList()[n].type;
        YieldType res;
        KDevelop::AbstractType::Ptr merged = mergeTypes(old.abstractType(), yield.type.abstractType());
        res.type = merged.data()->indexed();
        d_func_dynamic()->yieldTypesList()[n] = res;
    } else {
        d_func_dynamic()->yieldTypesList().append(yield);
    }
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

KDevelop::Declaration * MethodDeclaration::clonePrivate() const
{
    return new MethodDeclaration(*this);
}

}
