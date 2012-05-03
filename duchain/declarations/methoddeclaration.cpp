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


#include <duchain/declarations/methoddeclaration.h>


namespace Ruby
{

MethodDeclaration::MethodDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *ctx)
    : KDevelop::FunctionDeclaration(range, ctx), m_isClassMethod(false)
{

}

MethodDeclaration::MethodDeclaration(const KDevelop::FunctionDeclaration &rhs)
    : KDevelop::FunctionDeclaration(rhs), m_isClassMethod(false)
{

}

MethodDeclaration::MethodDeclaration(KDevelop::FunctionDeclarationData &data)
    : KDevelop::FunctionDeclaration(data), m_isClassMethod(false)
{

}

MethodDeclaration::MethodDeclaration(KDevelop::FunctionDeclarationData &data, const KDevelop::RangeInRevision &range)
    : KDevelop::FunctionDeclaration(data, range), m_isClassMethod(false)
{

}

bool MethodDeclaration::isClassMethod() const
{
    return m_isClassMethod;
}

void MethodDeclaration::setClassMethod(const bool isClass)
{
    m_isClassMethod = isClass;
}

}

