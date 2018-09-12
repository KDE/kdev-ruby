/* This file is part of KDevelop
 *
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


#ifndef RUBY_NORMALITEM_H
#define RUBY_NORMALITEM_H


#include <completion/completionexport.h>
#include <language/codecompletion/normaldeclarationcompletionitem.h>


namespace ruby {

/**
 * @class NormalItem
 * This is the NormalDeclarationCompletionItem to be used for this plugin.
 */
class KDEVRUBYCOMPLETION_EXPORT NormalItem : public KDevelop::NormalDeclarationCompletionItem
{
public:
    /// Constructor.
    explicit NormalItem(KDevelop::DeclarationPointer decl = KDevelop::DeclarationPointer(),
                        KDevelop::CodeCompletionContext::Ptr context = KDevelop::CodeCompletionContext::Ptr(),
                        int inheritanceDepth = 0);

    /// Re-implemented from KDevelop::NormalDeclarationCompletionItem.
    QVariant data(const QModelIndex &index,
                  int role,
                  const KDevelop::CodeCompletionModel *model) const override;

protected:
    /// Re-implemented from KDevelop::NormalDeclarationCompletionItem.
    QWidget * createExpandingWidget(const KDevelop::CodeCompletionModel *model) const override;

    /// Re-implemented from KDevelop::NormalDeclarationCompletionItem.
    bool createsExpandingWidget() const override;
};

}


#endif // RUBYNORMALITEM_H
