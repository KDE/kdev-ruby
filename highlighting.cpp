/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#include <highlighting.h>

#include <language/duchain/declaration.h>
#include <duchain/declarations/variabledeclaration.h>

using namespace ruby;

using namespace KDevelop;

//BEGIN RubyHighlightingInstance

HighlightingInstance::HighlightingInstance(const CodeHighlighting *h)
    : CodeHighlightingInstance(h)
{
}

HighlightingEnumContainer::Types HighlightingInstance::typeForDeclaration(
    Declaration *decl, DUContext *ctx) const
{
    VariableDeclaration *vd = dynamic_cast<VariableDeclaration *>(decl);
    if (decl && !decl->isFunctionDeclaration() &&
        decl->abstractType() && !vd) {
        return EnumType;
    }
    return CodeHighlightingInstance::typeForDeclaration(decl, ctx);
}

bool HighlightingInstance::useRainbowColor(KDevelop::Declaration *dec) const
{
    return dynamic_cast<VariableDeclaration *>(dec);
}

//END RubyHighlightingInstance

//BEGIN RubyHighlighting

ruby::Highlighting::Highlighting(QObject *parent)
    : CodeHighlighting(parent)
{
}

KDevelop::CodeHighlightingInstance* Highlighting::createInstance() const
{
    return new HighlightingInstance(this);
}

//END RubyHighlighting
