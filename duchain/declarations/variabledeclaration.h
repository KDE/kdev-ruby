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


#ifndef RUBY_VARIABLEDECLARATION_H
#define RUBY_VARIABLEDECLARATION_H


#include <language/duchain/declaration.h>
#include <duchain/duchainexport.h>


/*
 * WARNING: This file is under development.
 */
/*
 * TODO
 *  - Define a set of variable kinds
 */

namespace Ruby
{

class KDEVRUBYDUCHAIN_EXPORT RubyVariableDeclaration : public KDevelop::Declaration
{
public:
    RubyVariableDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *ctx);
    RubyVariableDeclaration(const RubyVariableDeclaration &rhs);
    RubyVariableDeclaration(KDevelop::DeclarationData &data);
    RubyVariableDeclaration(KDevelop::DeclarationData &data, const KDevelop::RangeInRevision &range);
};

typedef RubyVariableDeclaration VariableDeclaration;

} // End of namespace: Ruby


#endif // RUBY_VARIABLEDECLARATION_H

