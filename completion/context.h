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


#ifndef RUBY_COMPLETION_CONTEXT_H
#define RUBY_COMPLETION_CONTEXT_H


#include <language/codecompletion/codecompletioncontext.h>
#include <language/codecompletion/codecompletionitem.h>
#include <completion/completionexport.h>


namespace KDevelop {
  typedef KSharedPtr<CompletionTreeItem> CompletionTreeItemPointer;
}

namespace Ruby
{

/**
 * @class CodeCompletionContext
 *
 * This class handles the completion context for the Ruby language support.
 * It's responsible for finding out what kind of completion is needed, what
 * expression should be evaluated for the container-class of the completion,
 * what conversion will be applied to the result of the completion, etc.
 */
class KDEVRUBYCOMPLETION_EXPORT CodeCompletionContext : public KDevelop::CodeCompletionContext
{
public:
    typedef KSharedPtr<CodeCompletionContext> Ptr;

    CodeCompletionContext(KDevelop::DUContextPointer ctxt, const QString &text, const QString &followingText,
                          const KDevelop::CursorInRevision &pos, int depth = 0);
    virtual ~CodeCompletionContext();

    virtual QList<KDevelop::CompletionTreeItemPointer> completionItems(bool &abort, bool fullCompletion = true);
    virtual QList<KDevelop::CompletionTreeElementPointer> ungroupedElements();

public:
    enum CompletionContextType {
        NoMemberAccess,
        NoCompletion
    };

private:
    void eventuallyAddGroup(const QString &name, int priority, QList<KSharedPtr<KDevelop::CompletionTreeItem> > items);
    void addRubyKeywords();

private:
    CompletionContextType m_kind;
    QList<KDevelop::CompletionTreeElementPointer> m_ungroupedItems;
};

} // End of namespace Ruby

#endif /* RUBY_COMPLETION_CONTEXT_H */
