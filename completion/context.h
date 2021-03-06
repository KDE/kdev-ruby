/*
 * This file is part of KDevelop
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


#ifndef RUBY_COMPLETION_CONTEXT_H
#define RUBY_COMPLETION_CONTEXT_H


#include <language/codecompletion/codecompletioncontext.h>
#include <language/duchain/types/abstracttype.h>
#include <completion/completionexport.h>


namespace KDevelop {
    class IncludeItem;
}

namespace ruby {

enum class ContextType;

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
    using DeclarationPair = QPair<KDevelop::Declaration *, int>;
    using Ptr = QExplicitlySharedDataPointer<CodeCompletionContext>;

public:
    CodeCompletionContext(KDevelop::DUContextPointer ctxt,
                          const QString &text,
                          const QString &followingText,
                          const KDevelop::CursorInRevision &pos,
                          int depth = 0);

    ~CodeCompletionContext() override;

    /// Re-implemented from KDevelop::CodeCompletionContext.
    QList<KDevelop::CompletionTreeItemPointer> completionItems(bool &abort,
                                                               bool fullCompletion = true) override;

    /// Re-implemented from KDevelop::CodeCompletionContext.
    QList<KDevelop::CompletionTreeElementPointer> ungroupedElements() override;

private:
    /**
     * @returns true if it's ok to offer code completion in the current
     * position. Returns false otherwise.
     */
    bool isValidPosition();

    /**
     * @returns true if this is a require/require_relative completion. If so,
     * it then fills the m_includeItems attribute with the requirable files.
     */
    bool doRequireCompletion();

    /**
     * @returns the type of the last expression from m_text that is at the
     * left side of the given @p token.
     */
    KDevelop::AbstractType::Ptr getExpressionType(const QString &token);

    /**
     * @returns the completion items for the given @p type. Set @p scoped to
     * true if you want to handle the case of MyModule::. Otherwise, it will
     * assume the case of obj.method.
     * @note that the type can be anything, even unsure.
     */
    QList<KDevelop::CompletionTreeItemPointer> getCompletionItemsFromType(KDevelop::AbstractType::Ptr type,
                                                                          bool scoped = false);

    /**
     * @returns the completion items for the given @p type which is not unsure.
     * @note this is just a helper method for the previous one, so you
     * shouldn't call this directly.
     */
    QList<KDevelop::CompletionTreeItemPointer> getCompletionItemsForOneType(KDevelop::AbstractType::Ptr type,
                                                                            bool scoped);

    /// @returns true if the parent items should be added to this one.
    bool shouldAddParentItems(bool fullCompletion);

    /// Item creation methods for various completion types.

    QList<KDevelop::CompletionTreeItemPointer> memberAccessItems();
    QList<KDevelop::CompletionTreeItemPointer> moduleMemberAccessItems();
    QList<KDevelop::CompletionTreeItemPointer> baseClassItems();
    QList<KDevelop::CompletionTreeItemPointer> moduleMixinItems();
    QList<KDevelop::CompletionTreeItemPointer> classMemberItems();
    QList<KDevelop::CompletionTreeItemPointer> fileChooseItems();
    QList<KDevelop::CompletionTreeItemPointer> standardAccessItems();

    /**
     * Creates the group and adds it to m_ungroupedItems.
     * @param name The name of the group. You should call i18n() first.
     * @param priority The given priority for this new group.
     * @param items The items that should constitute this new group.
     */
    void eventuallyAddGroup(const QString &name, int priority,
                            QList<KDevelop::CompletionTreeItemPointer> items);

    /// Group adding methods.
    void addRubyKeywords();
    void addRubySpecialBuiltins();

private:
    bool m_valid;
    char m_closing;
    QString m_following;
    ContextType m_kind;
    QVector<KDevelop::IncludeItem> m_includeItems;
    QList<KDevelop::CompletionTreeElementPointer> m_ungroupedItems;
};

}


#endif /* RUBY_COMPLETION_CONTEXT_H */
