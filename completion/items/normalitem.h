/* This file is part of KDevelop
 *
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#ifndef RUBYNORMALITEM_H
#define RUBYNORMALITEM_H


#include <completion/completionexport.h>
#include <language/codecompletion/normaldeclarationcompletionitem.h>


namespace Ruby
{

/**
 * @class NormalItem
 * This is the NormalDeclarationCompletionItem to be used for this plugin.
 */
class KDEVRUBYCOMPLETION_EXPORT NormalItem : public KDevelop::NormalDeclarationCompletionItem
{
public:
    /// Constructor.
    explicit NormalItem(KDevelop::DeclarationPointer decl = KDevelop::DeclarationPointer(),
                        QExplicitlySharedDataPointer<KDevelop::CodeCompletionContext> context = QExplicitlySharedDataPointer<KDevelop::CodeCompletionContext>(),
                        int inheritanceDepth = 0);

    /// Re-implemented from KDevelop::NormalDeclarationCompletionItem.
    virtual QVariant data(const QModelIndex &index,
                          int role,
                          const KDevelop::CodeCompletionModel *model) const override;

protected:
    /// Re-implemented from KDevelop::NormalDeclarationCompletionItem.
    virtual QWidget * createExpandingWidget(const KDevelop::CodeCompletionModel *model) const;

    /// Re-implemented from KDevelop::NormalDeclarationCompletionItem.
    virtual bool createsExpandingWidget() const;
};

} // End of namespace Ruby


#endif // RUBYNORMALITEM_H
