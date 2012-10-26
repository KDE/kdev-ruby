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


#include <duchain/duchainexport.h>
#include <duchain/declarations/moduledeclaration.h>


namespace Ruby
{

/**
 * @class ClassDeclarationData
 *
 * The data for the ClassDeclaration class.
 */
class KDEVRUBYDUCHAIN_EXPORT ClassDeclarationData : public ModuleDeclarationData
{
public:
    /// Constructor
    ClassDeclarationData() : ModuleDeclarationData()
    {
        /* There's nothing to do here */
    }

    /// Copy constructor.
    ClassDeclarationData(const ClassDeclarationData &rhs)
        : ModuleDeclarationData(rhs)
    {
        m_baseClass = rhs.m_baseClass;
    }

    /// Destructor.
    ~ClassDeclarationData()
    {
        /* There's nothing to do here */
    }

public:
    /// The base class for this class.
    KDevelop::IndexedType m_baseClass;
};

/**
 * @class ClassDeclaration
 *
 * This is class represents a class declaration. It's a subclass of the
 * ModuleDeclaration. This way, it has access of the moduleMixins list from
 * the ModuleDeclaration class.
 */
class KDEVRUBYDUCHAIN_EXPORT ClassDeclaration : public ModuleDeclaration
{
public:
    ClassDeclaration(ClassDeclarationData &data, const KDevelop::RangeInRevision &range);

    /**
     * Constructor.
     * @param range The range of this declaration.
     * @param ctx The context of this declaration.
     */
    ClassDeclaration(const KDevelop::RangeInRevision &range, KDevelop::DUContext *ctx);

    /// Copy constructor.
    ClassDeclaration(const ClassDeclaration &rhs);

    /// Set the type @p base as the new base class for this class declaration.
    void setBaseClass(KDevelop::IndexedType base);

    /// Invalidate the current base class.
    void clearBaseClass();

    /// @returns the base class for this class declaration.
    KDevelop::IndexedType baseClass() const;

    /// Re-implemented from ModuleDeclaration.
    QString toString() const;

    enum { Identity = 46 /** The id of this Type. */ };

private:
    /// Re-implemented from KDevelop::Declaration.
    virtual KDevelop::Declaration * clonePrivate() const;

private:
    DUCHAIN_DECLARE_DATA(ClassDeclaration)
};

} // End of namespace Ruby


#endif // RUBY_CLASSDECLARATION_H
