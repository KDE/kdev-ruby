/*
 * This file is part of KDevelop
 * Copyright (C) 2011 Sven Brauch <svenbrauch@googlemail.com>
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


/*
 * NOTE: the VariableLengthContainer is used extensively in the Python plugin
 * and it's designed & implemented by Sven Brauch. It appears that it's also
 * useful for the Ruby plugin. Moreover, it's probably an interesting idea
 * for future language support plugins. Maybe this type should go
 * directly to KDevPlatform so everyone benefits from it ?¿
 */



#ifndef RUBY_VARIABLELENGTHCONTAINER_H
#define RUBY_VARIABLELENGTHCONTAINER_H


#include <duchain/duchainexport.h>
#include <language/duchain/types/structuretype.h>


using namespace KDevelop;

namespace Ruby
{

/**
 * @class VariableLengthContainerData
 *
 * Private data structure for VariableLengthContainer.
 */
class KDEVRUBYDUCHAIN_EXPORT VariableLengthContainerData : public KDevelop::StructureTypeData
{
public:
    /// Constructor
    VariableLengthContainerData()
        : StructureTypeData(), m_contentType(0)
    {
        /* There's nothing to do here */
    }

    /**
     * Copy constructor.
     * @param rhs data to copy.
     */
    VariableLengthContainerData(const VariableLengthContainerData &rhs)
        : StructureTypeData(rhs), m_contentType(rhs.m_contentType)
    {
        /* There's nothing to do here */
    }

    /**
     * Copy constructor.
     * @param rhs data to copy.
     */
    VariableLengthContainerData(const StructureTypeData &rhs)
        : StructureTypeData(rhs), m_contentType(0)
    {
        /* There's nothing to do here */
    };

    /// The type of the content.
    KDevelop::IndexedType m_contentType;
};

/**
 * @class VariableLengthContainer
 *
 * Describes a container that has a variable length and a second type,
 * which is the type of its contents (i.e. "List of Integers").
 */
class KDEVRUBYDUCHAIN_EXPORT VariableLengthContainer : public KDevelop::StructureType
{
public:
    /// Constructor.
    VariableLengthContainer();

    /**
     * Copy constructor.
     * @param rhs data to copy.
     */
    VariableLengthContainer(const VariableLengthContainer &rhs);

    /**
     * Copy constructor.
     * @param data data to copy.
     */
    VariableLengthContainer(StructureTypeData &data);

    void addContentType(AbstractType::Ptr typeToAdd);
    const IndexedType & contentType() const;

    /// Create a clone of this type.
    virtual AbstractType * clone() const;

    /// The hash-value for this type.
    virtual uint hash() const;

    /// Check if the given type equals to this one.
    virtual bool equals(const AbstractType *rhs) const;

    /// @returns this type as a string.
    virtual QString toString() const;

    /// @returns the container's type as a string.
    QString containerToString() const;

    enum { Identity = 41 /** The id of this Type. */ };

    typedef TypePtr<VariableLengthContainer> Ptr;
    typedef VariableLengthContainerData Data;
    typedef KDevelop::StructureType BaseType;

protected:
    TYPE_DECLARE_DATA(VariableLengthContainer);
};

} // End of namespace Ruby


#endif /* RUBY_VARIABLELENGTHCONTAINER_H */
