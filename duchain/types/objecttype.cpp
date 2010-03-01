/*
* This file is part of KDevelop
*
* Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
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
#include "objecttype.h"

#include <language/duchain/types/typeregister.h>

using namespace KDevelop;

namespace Ruby {

REGISTER_TYPE(ObjectType);

ObjectType::ObjectType()
    :KDevelop::StructureType(createData<ObjectType>())
{
}

ObjectType::ObjectType(const ObjectType& rhs)
    :KDevelop::StructureType(copyData<ObjectType>(*rhs.d_func()))
{
}

ObjectType::ObjectType(ObjectTypeData& data)
    :KDevelop::StructureType(data)
{
}

KDevelop::AbstractType* ObjectType::clone() const
{
    return new ObjectType(*this);
}

uint ObjectType::hash() const
{
    return 8 * KDevelop::StructureType::hash();
}

QString ObjectType::toString() const
{
    return "Object";
}

}
