/* This file is part of KDevelop
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


#ifndef TYPEBUILDER_H
#define TYPEBUILDER_H


// KDevelop + Ruby
#include <language/duchain/builders/abstracttypebuilder.h>
#include <duchain/builders/contextbuilder.h>


namespace Ruby
{

typedef KDevelop::AbstractTypeBuilder<RubyAst, NameAst, ContextBuilder> TypeBuilderBase;

/**
 * @class TypeBuilder
 *
 * Create types from a RubyAst.
 */
class KDEVRUBYDUCHAIN_EXPORT TypeBuilder: public TypeBuilderBase
{
public:
    /**
     * Constructor.
     */
    TypeBuilder();

protected:
    /**
     * The DeclarationBuilder implements this method in order update
     * the type of the current declaration.
     */
    virtual void updateCurrentType();
};

}


#endif // TYPEBUILDER_H

