/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#ifndef R_METHOD_DECLARATION_H
#define R_METHOD_DECLARATION_H


#include <duchain/duchainexport.h>
#include <language/duchain/appendedlist.h>
#include <language/duchain/functiondeclaration.h>


namespace Ruby
{

/// Struct used in the appended list.
struct KDEVRUBYDUCHAIN_EXPORT YieldType {
    KDevelop::IndexedType type;
};

KDEVRUBYDUCHAIN_EXPORT DECLARE_LIST_MEMBER_HASH(MethodDeclarationData, yieldTypes, YieldType)

/**
 * @class MethodDeclarationData
 *
 * Private data structure for MethodDeclaration.
 */
class KDEVRUBYDUCHAIN_EXPORT MethodDeclarationData : public KDevelop::FunctionDeclarationData
{
public:
    /// Constructor.
    explicit MethodDeclarationData()
        : KDevelop::FunctionDeclarationData(), classMethod(false)
        , m_accessPolicy(KDevelop::Declaration::Public)
    {
        initializeAppendedLists();
    }

    /**
     * Copy constructor.
     * @param rhs data to copy.
     */
    explicit MethodDeclarationData(const MethodDeclarationData &rhs)
        : KDevelop::FunctionDeclarationData(rhs)
    {
        initializeAppendedLists();
        copyListsFrom(rhs);
        classMethod = rhs.classMethod;
        m_accessPolicy = rhs.m_accessPolicy;
    }

    /// Destructor
    ~MethodDeclarationData()
    {
        freeAppendedLists();
    }

    /// True if this is a Class method
    bool classMethod;

    /// The access policy for this method.
    KDevelop::Declaration::AccessPolicy m_accessPolicy;

    /// The list of yield types.
    START_APPENDED_LISTS_BASE(MethodDeclarationData, KDevelop::DeclarationData);
    APPENDED_LIST_FIRST(MethodDeclarationData, YieldType, yieldTypes);
    END_APPENDED_LISTS(MethodDeclarationData, yieldTypes);
};

/**
 * @class MethodDeclaration
 *
 * In Ruby there are class methods (methods that belong to a class) and
 * instance methods (methods that belong to instances). This class stores
 * this information and, therefore, this is the one to be used instead
 * of the regular KDevelop::FunctionDeclaration.
 */
class KDEVRUBYDUCHAIN_EXPORT MethodDeclaration : public KDevelop::FunctionDeclaration
{
public:
    /**
     * Constructor.
     * @param range The range of this declaration.
     * @param ctx The context of this declaration.
     */
    explicit MethodDeclaration(const KDevelop::RangeInRevision &range,
                               KDevelop::DUContext *ctx);

    /// Copy constructor.
    explicit MethodDeclaration(const MethodDeclaration &rhs);

    /**
     * Copy constructor.
     * @param data The data to be copied.
     */
    explicit MethodDeclaration(MethodDeclarationData &data);

    /**
     * Set if this is a class or an instance method.
     * @param isClass True if this is a class method, false otherwise.
     */
    void setClassMethod(const bool isClass);

    /// @returns true if this is a class method, false otherwise.
    bool isClassMethod() const;

    /// Set the access policy to this methods according to the given @p policy.
    void setAccessPolicy(const KDevelop::Declaration::AccessPolicy &policy);

    /// @returns the access policy for this method.
    KDevelop::Declaration::AccessPolicy accessPolicy() const;

    /// Clear the list of yield types.
    void clearYieldTypes();

    /// @returns the size of the yield types list.
    uint yieldTypesSize();

    /// @returns the list of the yield types
    const YieldType * yieldTypes() const;

    /**
     * Replace the nth element of the yield list with the given one. If the
     * given n is greater or equal than the size of the list, the element will
     * be appended instead.
     * @param yield The new yield type.
     * @param n The index on the yield list where the given element should be
     * placed.
     */
    void replaceYieldTypes(YieldType yield, uint n);

    enum { Identity = 42 /** The id of this Type. */ };

private:
    /// Re-implemented from KDevelop::Declaration.
    virtual KDevelop::Declaration * clonePrivate() const override;

private:
    DUCHAIN_DECLARE_DATA(MethodDeclaration)
};

} // End of namespace Ruby


#endif /* R_METHOD_DECLARATION_H */
