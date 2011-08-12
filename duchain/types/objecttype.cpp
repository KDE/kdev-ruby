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


#include <language/duchain/types/typeregister.h>
#include <duchain/types/objecttype.h>


namespace Ruby
{
using namespace KDevelop;

REGISTER_TYPE(ObjectType);

ObjectType::ObjectType() : StructureType(createData<ObjectType>())
{
    /* There's nothing to do here */
}

ObjectType::ObjectType(const ObjectType &rhs)
    : StructureType(copyData<ObjectType>(*rhs.d_func()))
{
    /* There's nothing to do here */
}

ObjectType::ObjectType(ObjectTypeData& data)
    : StructureType(data)
{
    /* There's nothing to do here */
}

AbstractType * ObjectType::clone() const
{
    return new ObjectType(*this);
}

QString ObjectType::toString() const
{
    return "Object";
}

uint ObjectType::hash() const
{
    return 8 * StructureType::hash();
}

bool ObjectType::equals(const AbstractType *rhs) const
{
    if ( this == rhs )
        return true;
    if (!AbstractType::equals(rhs))
        return false;
    return true;
}

} // End of namespace ruby

