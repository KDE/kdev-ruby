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


#ifndef RUBY_FUNCTIONDECLARATION_H
#define RUBY_FUNCTIONDECLARATION_H

/*
 * WARNING: This files is under development.
 */

#include <language/duchain/functiondeclaration.h>
#include <duchain/duchainexport.h>


namespace Ruby
{

class KDEVRUBYDUCHAIN_EXPORT RubyFunctionDeclaration : public KDevelop::FunctionDeclaration
{
public:
    RubyFunctionDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *ctx);
    RubyFunctionDeclaration(const FunctionDeclaration &rhs);
    RubyFunctionDeclaration(KDevelop::FunctionDeclarationData &data);
    RubyFunctionDeclaration(KDevelop::FunctionDeclarationData &data, const KDevelop::RangeInRevision &range);
};

typedef RubyFunctionDeclaration FunctionDeclaration;

} // End of namespace Ruby


#endif // FUNCTIONDECLARATION_H

