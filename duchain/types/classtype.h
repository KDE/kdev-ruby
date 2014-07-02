/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#ifndef CLASSTYPE_H
#define CLASSTYPE_H


#include <language/duchain/types/structuretype.h>
#include <duchain/duchainexport.h>


namespace Ruby
{

/**
 * @class ClassTypeData
 *
 * The data class for the ClassType class.
 */
class KDEVRUBYDUCHAIN_EXPORT ClassTypeData: public KDevelop::StructureTypeData
{
public:
    /// Default constructor.
    explicit ClassTypeData()
        : KDevelop::StructureTypeData(), m_contentType()
    {
        /* There's nothing to do here! */
    }

    /// Copy constructor. @param rhs data to copy.
    explicit ClassTypeData(const ClassTypeData &rhs)
        : KDevelop::StructureTypeData(rhs), m_contentType(rhs.m_contentType)
    {
        /* There's nothing to do here! */
    }

    /// The type of the content.
    KDevelop::IndexedType m_contentType;
};

/**
 * @class ClassType
 *
 * This is the type to be used when declaring classes in this plugin. It's
 * similar to the Python's VariableLengthContainer in that in Ruby, every class
 * can potentially become a container. The contained type can be accessed
 * through the methods addContentType(newType) and contentType().
 */
class KDEVRUBYDUCHAIN_EXPORT ClassType : public KDevelop::StructureType
{
public:
    typedef TypePtr<ClassType> Ptr;

    /// Constructor.
    explicit ClassType();

    /**
     * Copy constructor.
     * @param rhs data to copy.
     */
    explicit ClassType(const ClassType &rhs);

    /**
     * Copy constructor.
     * @param data data to copy.
     */
    explicit ClassType(ClassTypeData &data);

    /// Add the given type @p typeToAdd to the contents.
    void addContentType(AbstractType::Ptr typeToAdd);

    /// @returns the content type.
    const KDevelop::IndexedType & contentType() const;

    /// Get if this class is useful.
    bool isUseful() const;

    /// Create a clone of this type.
    virtual AbstractType * clone() const override;

    /// The hash-value for this type.
    virtual uint hash() const override;

    /// @returns this type as a string.
    virtual QString toString() const override;

    /// @returns true if @p rhs is the same as this type
    virtual bool equals(const AbstractType *rhs) const override;

    /// @returns the container's type as a string.
    QString containerToString() const;

    enum { Identity = 41 /** The id of this Type. */ };

    typedef ClassTypeData Data;
    typedef KDevelop::StructureType BaseType;

protected:
    TYPE_DECLARE_DATA(ClassType);
};

} // End of namespace Ruby


#endif // CLASSTYPE_H
