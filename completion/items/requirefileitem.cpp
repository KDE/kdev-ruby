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


// KDE
#include <KTextEditor/Document>
#include <KTextEditor/View>

// Ruby
#include <completion/items/requirefileitem.h>


using namespace KTextEditor;

namespace Ruby
{

RequireFileItem::RequireFileItem(const KDevelop::IncludeItem &include, const char closing)
    : BaseIncludeFileItem(include), m_closing(closing)
{
    /* There's nothing to do here */
}

void RequireFileItem::execute(View *view, const Range &word)
{
    KTextEditor::Document *document = view->document();

    QString text = includeItem.name;
    if (includeItem.isDirectory)
        text += "/";
    else if (text.endsWith(".rb"))
        text.chop(3); // .rb

    // Close the item if needed.
    const QString textAfter = document->text(Range(word.end(), document->documentEnd()));
    bool found = false;
    for (int i = 0; textAfter[i] != '\n' && i < textAfter.length(); i++) {
        if (textAfter[i] == m_closing) {
            found = true;
            break;
        }
    }
    if (!found)
        text += m_closing;

    document->replaceText(word, text);
}

} // End of namespace Ruby
