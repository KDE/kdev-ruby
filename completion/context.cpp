/*
 * This file is part of KDevelop
 * Copyright 2012  Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#include <completion/context.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/duchain.h>
#include <completion/items/keyworditem.h>
#include <KLocale>


#define LOCKDUCHAIN DUChainReadLocker rlock(DUChain::lock())
#define ADD_KEYWORD(list, name) list << CompletionTreeItemPointer(new KeywordItem(KDevelop::CodeCompletionContext::Ptr(this), name))
#define ADD_KEYWORD2(list, name, desc) list << CompletionTreeItemPointer(new KeywordItem(KDevelop::CodeCompletionContext::Ptr(this), name, desc))
#define ADD_ONE_LINER(list, name, desc) list << CompletionTreeItemPointer(new KeywordItem(KDevelop::CodeCompletionContext::Ptr(this), name, desc, true))


using namespace KDevelop;

namespace Ruby
{

CodeCompletionContext::CodeCompletionContext(DUContextPointer ctxt, const QString &text,
                                             const QString &followingText,
                                             const CursorInRevision &pos, int depth)
    : KDevelop::CodeCompletionContext(ctxt, text, pos, depth)
    , m_kind(NoMemberAccess)
{
    /* TODO */
    Q_UNUSED(followingText)
}

CodeCompletionContext::~CodeCompletionContext()
{
    /* There's nothing to do here */
}

QList<KDevelop::CompletionTreeItemPointer> CodeCompletionContext::completionItems(bool &abort, bool fullCompletion)
{
    QList<CompletionTreeItemPointer> list;
    LOCKDUCHAIN;

    // TODO: check for m_kind to be some value to enter at the following block
    {
        if (m_position.line == 0 && (m_text.startsWith("#") || m_text.isEmpty())) {
            ADD_ONE_LINER(list, "#!/usr/bin/env ruby", i18n("insert Shebang line"));
            ADD_ONE_LINER(list, "# encoding: UTF-8", i18n("insert encoding line"));
        }
    }

    ADD_KEYWORD2(list, "while", "while %SELECT%condition%ENDSELECT%\n%END%");


    return list;
}

}
