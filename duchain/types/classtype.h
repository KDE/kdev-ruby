/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RUBY_CLASS_TYPE_H
#define RUBY_CLASS_TYPE_H

#include <duchain/duchainexport.h>
#include <language/duchain/types/structuretype.h>

namespace ruby {

struct KDEVRUBYDUCHAIN_EXPORT ClassTypeData : public KDevelop::StructureTypeData
{
    ClassTypeData() : KDevelop::StructureTypeData(), contentType()
    {
    }

    /// Copy constructor. @param rhs data to copy.
    explicit ClassTypeData(const ClassTypeData &rhs)
        : KDevelop::StructureTypeData(rhs)
        , contentType(rhs.contentType)
    {
    }

    /// The type of the content.
    KDevelop::IndexedType contentType;
};

/**
 * @class ClassType
 *
 * This is the type to be used when declaring classes in this plugin. It's
 * similar to the Python's VariableLengthContainer in that in Ruby, every class
 * can potentially become a container. The contained type can be accessed
 * through the methods addContentType(newType) and contentType().
 */
struct KDEVRUBYDUCHAIN_EXPORT ClassType : public KDevelop::StructureType
{
    using BaseType = KDevelop::StructureType;
    using Data = ClassTypeData;
    using Ptr = KDevelop::TypePtr<ClassType>;

    /// The different constructors.
    ClassType();
    explicit ClassType(const ClassType &rhs);
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

protected:
    TYPE_DECLARE_DATA(ClassType);
};

}

#endif // CLASSTYPE_H
