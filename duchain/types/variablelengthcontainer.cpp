/*
 * This file is part of KDevelop
 * Copyright (C) 2011 Sven Brauch <svenbrauch@googlemail.com>
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


// KDE + KDevelop
#include <KLocalizedString>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/types/typeregister.h>

// Ruby
#include <duchain/helpers.h>
#include <duchain/types/variablelengthcontainer.h>


using namespace KDevelop;

namespace Ruby
{

REGISTER_TYPE(VariableLengthContainer);

VariableLengthContainer::VariableLengthContainer()
    : StructureType(createData<VariableLengthContainer>())
{
    /* There's nothing to do here */
}

VariableLengthContainer::VariableLengthContainer(const VariableLengthContainer &rhs)
    : StructureType(copyData<VariableLengthContainer>(*rhs.d_func()))
{
    /* There's nothing to do here */
}

VariableLengthContainer::VariableLengthContainer(StructureTypeData &data)
    : StructureType(data)
{
    /* There's nothing to do here */
}

void VariableLengthContainer::addContentType(AbstractType::Ptr typeToAdd)
{
    AbstractType::Ptr type = mergeTypes(contentType().abstractType(), typeToAdd);
    d_func_dynamic()->m_contentType = type->indexed();
}

const IndexedType & VariableLengthContainer::contentType() const
{
    return d_func()->m_contentType;
}

AbstractType* VariableLengthContainer::clone() const
{
    VariableLengthContainer *n = new VariableLengthContainer(*this);
    DUChainReadLocker lock(DUChain::lock());
    return n;
}

uint VariableLengthContainer::hash() const
{
    uint shash = contentType().abstractType() ? contentType().abstractType()->hash() : 0;
    return (KDevelop::StructureType::hash() << 3) + shash;
}

bool VariableLengthContainer::equals(const AbstractType *rhs) const
{
    if (this == rhs)
        return true;
    if (!KDevelop::StructureType::equals(rhs))
        return false;

    const VariableLengthContainer *c = dynamic_cast<const VariableLengthContainer *>(rhs);
    if (!c || c->contentType() != d_func()->m_contentType)
        return false;
    return true;
}

QString VariableLengthContainer::toString() const
{
    QString prefix = KDevelop::StructureType::toString();
    AbstractType::Ptr content = contentType().abstractType();
    return content ? i18n("%1 of %2", prefix, content->toString()) : prefix;
}

QString VariableLengthContainer::containerToString() const
{
    return KDevelop::StructureType::toString();
}

} // End of namespace Ruby
