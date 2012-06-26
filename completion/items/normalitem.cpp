/* This file is part of KDevelop
 *
 * Copyright (C) 2012  Miquel Sabaté <mikisabate@gmail.com>
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


#include <language/codecompletion/codecompletionmodel.h>
#include <completion/items/normalitem.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>

using namespace KDevelop;

namespace Ruby
{

NormalItem::NormalItem(DeclarationPointer decl, KSharedPtr<CodeCompletionContext> context, int inheritanceDepth)
    : NormalDeclarationCompletionItem(decl, context, inheritanceDepth)
{
    /* There's nothing to do here */
}

QVariant NormalItem::data(const QModelIndex &index, int role, const CodeCompletionModel *model) const
{
    if (!m_declaration)
        return QVariant();
    DUChainReadLocker rlock(DUChain::lock());

    // TODO

    return NormalDeclarationCompletionItem::data(index, role, model);
}

} // End of namespace Ruby
