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


#ifndef RUBY_REQUIREFILEITEM_H
#define RUBY_REQUIREFILEITEM_H


#include <language/codecompletion/abstractincludefilecompletionitem.h>
#include <duchain/navigation/navigationwidget.h>


namespace Ruby
{

typedef KDevelop::AbstractIncludeFileCompletionItem<Ruby::NavigationWidget> BaseIncludeFileItem;

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
    virtual void execute(KTextEditor::Document *document, const KTextEditor::Range &word);

private:
    /// The character that may enclose this item.
    char m_closing;
};

} // End of namespace Ruby


#endif /* RUBY_REQUIREFILEITEM_H */
