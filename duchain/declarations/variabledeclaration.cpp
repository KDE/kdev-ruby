/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#include <duchain/declarations/variabledeclaration.h>
#include <language/duchain/duchainregister.h>

namespace ruby {

REGISTER_DUCHAIN_ITEM(VariableDeclaration);

VariableDeclaration::VariableDeclaration(VariableDeclarationData &data)
    : KDevelop::Declaration(data)
{
}

VariableDeclaration::VariableDeclaration(VariableDeclarationData &data,
                                         const KDevelop::RangeInRevision &range)
    : KDevelop::Declaration(data, range)
{
}

VariableDeclaration::VariableDeclaration(const VariableDeclaration &rhs)
    : KDevelop::Declaration(*new VariableDeclarationData(*rhs.d_func()))
{
}

VariableDeclaration::VariableDeclaration(const KDevelop::RangeInRevision &range,
                                         KDevelop::DUContext *context)
    : KDevelop::Declaration(*new VariableDeclarationData, range)
{
    d_func_dynamic()->setClassId(this);
    if (context) {
        setContext(context);
    }
}

void VariableDeclaration::setVariableKind(const Node *node)
{
    if (node) {
        d_func_dynamic()->kind = node->flags;
    }
}

void VariableDeclaration::setVariableKind(int kind)
{
    d_func_dynamic()->kind = kind;
}

int VariableDeclaration::variableKind() const
{
    return d_func()->kind;
}

}
