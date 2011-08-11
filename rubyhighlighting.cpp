/* This file is part of KDevelop
 *
 * Copyright (C) 2011  Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


//KDevelop
#include <language/duchain/declaration.h>

//Ruby
#include <rubyhighlighting.h>
#include <duchain/declarations/variabledeclaration.h>


namespace Ruby
{

//BEGIN RubyHighlightingInstance

HighlightingInstance::HighlightingInstance(const KDevelop::CodeHighlighting *highlighting)
    : CodeHighlightingInstance(highlighting)
{
    /* There's nothing to do here */
}

KDevelop::HighlightingEnumContainer::Types HighlightingInstance::typeForDeclaration(KDevelop::Declaration *decl,
                                                                                    KDevelop::DUContext *context) const
{
    if (decl && !decl->isFunctionDeclaration() && decl->abstractType()
        && !dynamic_cast<VariableDeclaration*>(decl))
    {
        return EnumType;
    } else
        return CodeHighlightingInstance::typeForDeclaration(decl, context);
}

bool HighlightingInstance::useRainbowColor(KDevelop::Declaration *dec) const
{
    return dynamic_cast<VariableDeclaration *>(dec);
}

//END RubyHighlightingInstance

//BEGIN RubyHighlighting

Ruby::Highlighting::Highlighting(QObject *parent)
    : CodeHighlighting(parent)
{
    /* There's nothing to do here! */
}

KDevelop::CodeHighlightingInstance* Highlighting::createInstance() const
{
    return new HighlightingInstance(this);
}

//END RubyHighlighting

} // End of namespace Ruby


#include "rubyhighlighting.moc"

