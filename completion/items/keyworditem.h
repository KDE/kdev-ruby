/* This file is part of KDevelop
 *
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#ifndef RUBY_KEYWORD_ITEM_H
#define RUBY_KEYWORD_ITEM_H

#include <language/codecompletion/normaldeclarationcompletionitem.h>
#include <completion/completionexport.h>

namespace ruby {

/**
 * @class KeywordItem
 *
 * A completion item for a ruby keyword. Depending on how it's initialized
 * this class, it will add some extra code.
 */
class KDEVRUBYCOMPLETION_EXPORT KeywordItem
    : public KDevelop::NormalDeclarationCompletionItem
{
public:
    /**
     * Constructor.
     * @param ctx The code completion context.
     * @param keyword The keyword that this item is representing.
     * @param customReplacement If the \p line is set to false, it can be used
     * for additional power on how the keyword gets replaced. To place the
     * cursor, use %CURSOR%. You can select a word with
     * %SELECT%word%ENDSELECT%. Finally, use %END% to place an end keyword
     * indented to the indentation level of the line we execute the item on.
     * If the \p line is set to true, this parameter only acts as a descriptor.
     * @param line Set to true if you want that the whole line gets replaced.
     * False by default.
     */
    explicit KeywordItem(KDevelop::CodeCompletionContext::Ptr ctx,
                         const QString &keyword,
                         const QString &customReplacement = QString(""),
                         bool line = false);

    /// Re-implemented from KDevelop::NormalDeclarationCompletionItem.
    virtual void execute(KTextEditor::View *view,
                         const KTextEditor::Range &word) override;

    /// Re-implemented from KDevelop::NormalDeclarationCompletionItem.
    virtual QVariant data(const QModelIndex &index,
                          int role,
                          const KDevelop::CodeCompletionModel *model) const override;

private:
    QString m_keyword;
    QString m_replacement;
    bool m_wholeLine;
};

}

#endif // RUBY_KEYWORD_ITEM_H
