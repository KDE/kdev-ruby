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


#ifndef RUBY_CLASSDECLARATION_H
#define RUBY_CLASSDECLARATION_H


#include <duchain/declarations/moduledeclaration.h>
#include <duchain/duchainexport.h>


namespace Ruby
{

class KDEVRUBYDUCHAIN_EXPORT ClassDeclarationData : public ModuleDeclarationData
{
public:
    /// Constructor.
    ClassDeclarationData() : ModuleDeclarationData()
    {
        /* There's nothing to do here */
    }

    /**
     * Copy constructor.
     * @param rhs data to copy.
     */
    ClassDeclarationData(const ClassDeclarationData &rhs) : ModuleDeclarationData(rhs)
    {
        
    }
};

class KDEVRUBYDUCHAIN_EXPORT ClassDeclaration : public ModuleDeclaration
{
public:
    /**
     * Constructor.
     * @param range The range of this declaration.
     * @param ctx The context of this declaration.
     */
    ClassDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *ctx);

    /// Copy constructor.
    ClassDeclaration(const ClassDeclaration &rhs);

    /**
     * Copy constructor.
     * @param data The data to be copied.
     */
    ClassDeclaration(ModuleDeclarationData &data);

    void setBaseClass(KDevelop::IndexedType base);

    void clearBaseClass();

    KDevelop::IndexedType baseClass() const;

    enum { Identity = 45 /** The id of this Type. */ };

private:
    DUCHAIN_DECLARE_DATA(ClassDeclaration)
    KDevelop::IndexedType m_baseClass;
};

} // End of namespace Ruby


#endif // RUBY_CLASSDECLARATION_H

