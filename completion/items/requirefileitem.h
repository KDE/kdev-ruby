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


#ifndef RUBY_REQUIREFILEITEM_H
#define RUBY_REQUIREFILEITEM_H

#include <language/codecompletion/abstractincludefilecompletionitem.h>
#include <duchain/navigation/navigationwidget.h>

namespace ruby {

using BaseIncludeFileItem =
    KDevelop::AbstractIncludeFileCompletionItem<ruby::NavigationWidget>;

/**
 * @class RequireFileItem
 * This class is the completion item for completing required files.
 */
class RequireFileItem : public BaseIncludeFileItem
{
public:
    /// Constructor
    RequireFileItem(const KDevelop::IncludeItem &include, const char closing);

    /// Re-implemented from KDevelop::AbstractIncludeFileCompletionItem
    void execute(KTextEditor::View *View,
                 const KTextEditor::Range &word) override;

private:
    /// The character that may enclose this item.
    char m_closing;
};

}

#endif /* RUBY_REQUIREFILEITEM_H */
