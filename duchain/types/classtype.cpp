/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#include <klocalizedstring.h>

#include <duchain/helpers.h>
#include <duchain/types/classtype.h>
#include <language/duchain/types/typeregister.h>

using namespace KDevelop;
using namespace ruby;

REGISTER_TYPE(ClassType);

ClassType::ClassType() : KDevelop::StructureType(createData<ClassType>())
{
}

ClassType::ClassType(const ClassType &rhs)
    : KDevelop::StructureType(copyData<ClassType>(*rhs.d_func()))
{
}

ClassType::ClassType(ClassTypeData &data)
    : KDevelop::StructureType(data)
{
}

void ClassType::addContentType(AbstractType::Ptr typeToAdd)
{
    if (!typeToAdd) { // TODO: not sure :/
        return;
    }
    auto type = mergeTypes(contentType().abstractType(), typeToAdd);
    d_func_dynamic()->contentType = IndexedType(type);
}

const IndexedType & ClassType::contentType() const
{
    return d_func()->contentType;
}

bool ClassType::isUseful() const
{
    // TODO: this is utter crap.
    return KDevelop::StructureType::toString() != QStringLiteral("Object");
}

AbstractType * ClassType::clone() const
{
    return new ClassType(*this);
}

uint ClassType::hash() const
{
    return KDevHash(StructureType::hash()) <<
        (contentType().abstractType() ? contentType().abstractType()->hash() : 0);
}

bool ClassType::equals(const AbstractType *rhs) const
{
    if (!KDevelop::StructureType::equals(rhs)) {
        return false;
    }

    if (const ClassType *rhsClass = dynamic_cast<const ClassType *>(rhs)) {
        return rhsClass->contentType() == contentType();
    }
    return false;
}

QString ClassType::toString() const
{
    QString prefix = StructureType::toString();
    AbstractType::Ptr content = contentType().abstractType();
    return content ? i18n("%1 of %2", prefix, content->toString()) : prefix;
}

QString ClassType::containerToString() const
{
    return KDevelop::StructureType::toString();
}

