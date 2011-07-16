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

#include "variabledeclaration.h"


namespace Ruby
{

RubyVariableDeclaration::RubyVariableDeclaration(const KDevelop::RangeInRevision& range, KDevelop::DUContext* ctx)
    : KDevelop::Declaration(range, ctx)
{

}

RubyVariableDeclaration::RubyVariableDeclaration(const RubyVariableDeclaration& rhs)
    : KDevelop::Declaration(rhs)
{

}

RubyVariableDeclaration::RubyVariableDeclaration(KDevelop::DeclarationData& data)
    : KDevelop::Declaration(data)
{

}

RubyVariableDeclaration::RubyVariableDeclaration(KDevelop::DeclarationData& data, const KDevelop::RangeInRevision& range)
    : KDevelop::Declaration(data, range)
{

}

}
