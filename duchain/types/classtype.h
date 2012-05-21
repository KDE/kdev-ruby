/*
 * This file is part of KDevelop
 * Copyright 2012  Miquel Sabaté <mikisabate@gmail.com>
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

class KDEVRUBYDUCHAIN_EXPORT ClassTypeData: public KDevelop::StructureTypeData
{
public:
    /**
     * Default constructor.
     */
    ClassTypeData() : KDevelop::StructureTypeData(), m_contentType(0)
    {
        /* There's nothing to do here! */
    }

    /**
     * Copy constructor.
     *
     * @param rhs data to copy.
     */
    ClassTypeData(const ClassTypeData &rhs)
        : KDevelop::StructureTypeData(rhs), m_contentType(rhs.m_contentType)
    {
        /* There's nothing to do here! */
    }

    /// The type of the content.
    KDevelop::IndexedType m_contentType;
};

class KDEVRUBYDUCHAIN_EXPORT ClassType : public KDevelop::StructureType
{
public:
    typedef TypePtr<ClassType> Ptr;

    /// Constructor.
    ClassType();

    /**
     * Copy constructor.
     * @param rhs data to copy.
     */
    ClassType(const ClassType &rhs);

    /**
     * Copy constructor.
     * @param data data to copy.
     */
    ClassType(ClassTypeData &data);

    /// Add the given type @p typeToAdd to the contents.
    void addContentType(AbstractType::Ptr typeToAdd);

    /// @returns the content type.
    const KDevelop::IndexedType & contentType() const;

    /// Create a clone of this type.
    virtual AbstractType * clone() const;

    /// The hash-value for this type.
    virtual uint hash() const;

    /// @returns this type as a string.
    virtual QString toString() const;

    /// @returns the container's type as a string.
    QString containerToString() const;

    enum { Identity = 43 /** The id of this Type. */ };

    typedef ClassTypeData Data;
    typedef KDevelop::StructureType BaseType;

protected:
    TYPE_DECLARE_DATA(ClassType);
};

} // End of namespace Ruby


#endif // CLASSTYPE_H
