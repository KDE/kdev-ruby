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
#include <language/duchain/types/functiontype.h>
#include <duchain/navigation/navigationwidget.h>
#include <duchain/declarations/classdeclaration.h>
#include <duchain/declarations/methoddeclaration.h>

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

    Declaration* dec = const_cast<Declaration*>(m_declaration.data());
    switch (role) {
    case CodeCompletionModel::ItemSelected:
        return QVariant(NavigationWidget::shortDescription(dec));
    case Qt::DisplayRole:
        switch (index.column()) {
        case CodeCompletionModel::Postfix:
            return QVariant();
        case CodeCompletionModel::Prefix:
            MethodDeclaration *mDec = dynamic_cast<MethodDeclaration *>(dec);
            if (mDec) {
                FunctionType::Ptr ftype = mDec->type<FunctionType>();
                if (ftype && ftype->returnType())
                    return ftype->returnType()->toString();
                else
                    return "<no type>";
            } else {
                ClassDeclaration *classDec = dynamic_cast<ClassDeclaration *>(dec);
                ModuleDeclaration *moDec = dynamic_cast<ModuleDeclaration *>(dec);
                if (classDec)
                    return "class";
                else if (moDec)
                    return "module";
            }
            return QVariant();
        }
        break;
    }
    rlock.unlock();

    return NormalDeclarationCompletionItem::data(index, role, model);
}

} // End of namespace Ruby
