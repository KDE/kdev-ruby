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


// KTextEditor + KDevelop
#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <language/duchain/ducontext.h>
#include <language/codecompletion/codecompletionmodel.h>

// Ruby
#include <completion/items/keyworditem.h>
#include <completion/helpers.h>


using namespace KTextEditor;
using namespace KDevelop;

namespace Ruby
{

KeywordItem::KeywordItem(KSharedPtr<KDevelop::CodeCompletionContext> ctx, const QString &keyword,
                         const QString &customReplacement, bool line)
    : NormalDeclarationCompletionItem(DeclarationPointer(), ctx)
    , m_keyword(keyword), m_replacement(customReplacement), m_wholeLine(line)
{
    /* There's nothing to do here */
}

void KeywordItem::execute(Document *document, const Range &word)
{
    if (!m_replacement.isEmpty()) {
        QString replacement = m_replacement;
        replacement = replacement.replace("%END%", getIndendation(document->line(word.start().line())) + "end");
        int cursor = replacement.indexOf("%CURSOR%");
        int selectionEnd = -1;

        if (cursor != -1)
            replacement.remove("%CURSOR%");
        else {
            cursor = replacement.indexOf("%SELECT%");
            if ( cursor != -1 ) {
                replacement.remove("%SELECT%");
                selectionEnd = replacement.indexOf("%ENDSELECT%", cursor + 1);
                if (selectionEnd == -1)
                    selectionEnd = replacement.length();
                replacement.remove("%ENDSELECT%");
            }
        }

        if (m_wholeLine) {
            Range newRange(Cursor(word.start().line(), 0), word.end());
            document->replaceText(newRange, m_keyword);
        } else
            document->replaceText(word, replacement);

        if (cursor != -1) {
            if (KTextEditor::View *view = document->activeView()) {
                replacement = replacement.left(cursor);
                KTextEditor::Cursor newPos(
                    word.start().line() + replacement.count('\n'),
                    word.start().column() + replacement.length() - replacement.lastIndexOf('\n') - 1
                );
                view->setCursorPosition(newPos);
                if ( selectionEnd != -1 ) {
                    view->setSelection(
                        KTextEditor::Range(
                            newPos,
                            KTextEditor::Cursor(
                                newPos.line(),
                                newPos.column() + selectionEnd - cursor
                            )
                        )
                    );
                }
            }
        }
    } else
        document->replaceText(word, m_keyword);
}

QVariant KeywordItem::data(const QModelIndex &index, int role, const KDevelop::CodeCompletionModel *model) const
{
    switch (role) {
    case KDevelop::CodeCompletionModel::IsExpandable:
        return QVariant(false);
    case Qt::DisplayRole:
        if (index.column() == KTextEditor::CodeCompletionModel::Name)
            return QVariant(m_keyword);
        else if (m_wholeLine && index.column() == KTextEditor::CodeCompletionModel::Prefix)
            return QVariant(m_replacement);
        else
            return QVariant("");
    case KTextEditor::CodeCompletionModel::ItemSelected:
        return QVariant("");
    case KTextEditor::CodeCompletionModel::InheritanceDepth:
        return QVariant(0);
    default:
        break;
    }

    return NormalDeclarationCompletionItem::data(index, role, model);
}

} // End of namespace Ruby

