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


namespace Ruby
{

/**
 * @class VariableDeclaration
 *
 * Represents the declaration of a variable in ruby.
 */
class KDEVRUBYDUCHAIN_EXPORT VariableDeclaration : public KDevelop::Declaration
{
public:
    /**
     * Constructor.
     * @param range The range of this declaration.
     * @param ctx The context of this declaration.
     */
    VariableDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *ctx);

    /**
     * Constructor.
     * @param data The data to be copied.
     * @param range The range of this declaration.
     */
    VariableDeclaration(KDevelop::DeclarationData &data, const KDevelop::RangeInRevision &range);

    /// Copy constructor.
    VariableDeclaration(const VariableDeclaration &rhs);

    /**
     * Copy constructor.
     * @param data The data to be copied.
     */
    VariableDeclaration(KDevelop::DeclarationData &data);
};

} // End of namespace: Ruby


#endif // RUBY_VARIABLEDECLARATION_H

