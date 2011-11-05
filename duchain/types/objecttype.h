/* This file is part of KDevelop
 *
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright 2011 Miquel Sabaté <mikisabate@gmail.com>
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


#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H


#include <language/duchain/types/structuretype.h>
#include <duchain/duchainexport.h>


namespace Ruby
{

/**
 * @class ObjectTypeData
 *
 * The Data for the ObjectType class. It extends the
 * KDevelop::StructureTypeData class although it does nothing really
 * interesting.
 */
class KDEVRUBYDUCHAIN_EXPORT ObjectTypeData: public KDevelop::StructureTypeData
{
public:
    /**
     * Default constructor.
     */
    ObjectTypeData() : KDevelop::StructureTypeData()
    {
        /* There's nothing to do here! */
    }

    /**
     * Copy constructor.
     *
     * @param rhs data to copy.
     */
    ObjectTypeData(const ObjectTypeData & rhs)
        : KDevelop::StructureTypeData(rhs)
    {
        /* There's nothing to do here! */
    }
};


/**
 * @class ObjectType
 *
 * This is a basic type used across this plugin. It represents a Ruby Object.
 * It extends the KDevelop::StructureType class.
 */
class KDEVRUBYDUCHAIN_EXPORT ObjectType: public KDevelop::StructureType
{
public:
    /**
     * Default constructor.
     */
    ObjectType();

    /**
     * Copy constructor.
     *
     * @param rhs type to copy.
     */
    ObjectType(const ObjectType &rhs);

    /**
     * Constructor using raw data.
     *
     * @param data internal data.
     */
    ObjectType(ObjectTypeData& data);

    /**
     * Re-implemented from KDevelop::StructureType.
     *
     * @return A clone of this instance.
     */
    virtual AbstractType * clone() const;

    /**
     * Re-implemented from KDevelop::StructureType.
     *
     * @return A QString that describes this class.
     */
    virtual QString toString() const;

    /**
     * Re-implemented from KDevelop::StructureType.
     *
     * @return An unsigned integer used for hashing.
     */
    virtual uint hash() const;

    /**
     * Re-implemented from KDevelop::StructureType. Compares the given
     * parameter with this instance.
     *
     * @param rhs The type to compare.
     * @return True if both types are the same, false otherwise.
     */
    virtual bool equals(const AbstractType *rhs) const;

    
    enum { Identity = 40 /** The id of this Type. */ };

    /// A TypePtr of the ObjectType class.
    typedef TypePtr<ObjectType> Ptr;

    /// Yet another convenient typedef.
    typedef ObjectTypeData Data;

    /// Yet another convenient typedef.
    typedef KDevelop::StructureType BaseType;

protected:
    TYPE_DECLARE_DATA(ObjectType);
};

} // End of namespace ruby


#endif /* OBJECTTYPE_H */

