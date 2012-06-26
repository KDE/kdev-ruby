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
#include <rubydefs.h>
#include <duchain/declarations/classdeclaration.h>


#define LOCKDUCHAIN DUChainReadLocker rlock(DUChain::lock())
#define ADD_KEYWORD(name) list << CompletionTreeItemPointer(new KeywordItem(KDevelop::CodeCompletionContext::Ptr(this), name))
#define ADD_KEYWORD2(name, desc) list << CompletionTreeItemPointer(new KeywordItem(KDevelop::CodeCompletionContext::Ptr(this), name, desc))
#define ADD_ONE_LINER(name, desc) list << CompletionTreeItemPointer(new KeywordItem(KDevelop::CodeCompletionContext::Ptr(this), name, desc, true))


using namespace KDevelop;

namespace Ruby
{

const QSet<QString> MEMBER_STRINGS = QString(". :: < include extend require require_relative").split(' ').toSet();
const int MEMBER_STRINGS_MAX = 16; // require_relative

void compressText(QString &text)
{
    for (int i = text.length() - 1; i >= 0; --i) {
        if (!text[i].isSpace())
            break;
        text.remove(i, 1);
    }
}

QString getEndingFromSet(const QString &str, const QSet<QString> &set, int maxMatchLen)
{
    QString end;

    for (int i = qMin(str.length(), maxMatchLen); i > 0; --i) {
        end = str.right(i);
        if (set.contains(end))
            return end;
    }
    return QString();
}

bool insideClass(const QString &text)
{
    int idx = text.lastIndexOf("<");
    int classIdx = text.lastIndexOf("class", idx);
    int semicolon = text.lastIndexOf(";", idx);
    return  (classIdx != -1 && (classIdx > semicolon));
}

CodeCompletionContext::CompletionContextType findAccessKind(const QString &original)
{
    QString text = getEndingFromSet(original, MEMBER_STRINGS, MEMBER_STRINGS_MAX);

    if (text == ".")
        return CodeCompletionContext::MemberAccess;
    if (text == "::")
        return CodeCompletionContext::ModuleMemberAccess;
    if (text == "<" && insideClass(original))
        return CodeCompletionContext::BaseClassAccess;
    if (text == "include" || text == "extend")
        return CodeCompletionContext::ModuleMixinAccess;
    if (text == "require" || text == "require_relative")
        return CodeCompletionContext::FileChoose;
    return CodeCompletionContext::NoMemberAccess;
}

CodeCompletionContext::CodeCompletionContext(DUContextPointer ctxt, const QString &text,
                                             const QString &followingText,
                                             const CursorInRevision &pos, int depth)
    : KDevelop::CodeCompletionContext(ctxt, text, pos, depth)
    , m_kind(NoMemberAccess), m_valid(true)
{
    if (!m_duContext) {
        m_valid = false;
        return;
    }

    compressText(m_text);
    m_kind = findAccessKind(m_text);
}

CodeCompletionContext::~CodeCompletionContext()
{
    /* There's nothing to do here */
}

QList<KDevelop::CompletionTreeItemPointer> CodeCompletionContext::completionItems(bool &abort, bool fullCompletion)
{
    QList<CompletionTreeItemPointer> items;
    if (!m_valid)
        return items;

    switch(m_kind) {
        case MemberAccess:
            items += memberAccessItems();
            break;
        case ModuleMemberAccess:
            items += moduleMemberAccessItems();
            break;
        case BaseClassAccess:
            items += baseClassItems();
            break;
        case ModuleMixinAccess:
            items += moduleMixinItems();
            break;
        case ClassMemberChoose:
            items += classMemberItems();
            break;
        case FileChoose:
            items += fileChooseItems();
            break;
        default:
            items += standardAccessItems();
            addRubyKeywords();
    }

    if (shouldAddParentItems(fullCompletion))
        items.append(parentContext()->completionItems(abort, fullCompletion));

    return items;
}

QList<CompletionTreeElementPointer> CodeCompletionContext::ungroupedElements()
{
    return m_ungroupedItems;
}

bool CodeCompletionContext::shouldAddParentItems(bool fullCompletion)
{
    return (m_parentContext && fullCompletion);
}

QList<CompletionTreeItemPointer> CodeCompletionContext::memberAccessItems()
{
    QList<CompletionTreeItemPointer> list;

    // TODO
    debug() << "Inside MemberAccessItems";

    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::moduleMemberAccessItems()
{
    QList<CompletionTreeItemPointer> list;

    // TODO
    debug() << "Inside ModuleMemberAccessItems";

    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::baseClassItems()
{
    QList<CompletionTreeItemPointer> list;
    LOCKDUCHAIN;

    QList<DeclarationPair> decls = m_duContext->allDeclarations(m_position, m_duContext->topContext());
    foreach(DeclarationPair d, decls) {
        if (dynamic_cast<ClassDeclaration *>(d.first)) {
            list << CompletionTreeItemPointer(new NormalDeclarationCompletionItem(DeclarationPointer(d.first), KDevelop::CodeCompletionContext::Ptr(this)));
        }
    }

    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::moduleMixinItems()
{
    QList<CompletionTreeItemPointer> list;

    // TODO
    debug() << "Inside ModuleMixinItems";

    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::classMemberItems()
{
    QList<CompletionTreeItemPointer> list;

    // TODO
    debug() << "Inside ClassMemberItems";

    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::fileChooseItems()
{
    QList<CompletionTreeItemPointer> list;

    // TODO
    debug() << "Inside FileChooseItems";

    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::standardAccessItems()
{
    QList<CompletionTreeItemPointer> list;

    if (m_position.line == 0 && (m_text.startsWith("#") || m_text.isEmpty())) {
        ADD_ONE_LINER("#!/usr/bin/env ruby", i18n("insert Shebang line"));
        ADD_ONE_LINER("# encoding: UTF-8", i18n("insert encoding line"));
    }

    // TODO
    debug() << "Inside StandardAccessItems";

    return list;
}

void CodeCompletionContext::eventuallyAddGroup(const QString &name, int priority,
                                               QList<KSharedPtr<CompletionTreeItem> > items)
{
    KDevelop::CompletionCustomGroupNode *node = new KDevelop::CompletionCustomGroupNode(name, priority);
    node->appendChildren(items);
    m_ungroupedItems << CompletionTreeElementPointer(node);
}

void CodeCompletionContext::addRubyKeywords()
{
    QList<CompletionTreeItemPointer> list;

    // TODO: pick user's indentation level
    // TODO: statement modifiers
    // TODO: be careful with the 4 kinds of tDO's
    // TODO: complete | | from bracket blocks ?
    // TODO: unindent things like rescue, ensure,...

    ADD_KEYWORD("next");
    ADD_KEYWORD("break");
    ADD_KEYWORD("true");
    ADD_KEYWORD("false");
    ADD_KEYWORD("self");
    ADD_KEYWORD("then");
    ADD_KEYWORD("redo");
    ADD_KEYWORD("retry");
    ADD_KEYWORD("yield");
    ADD_KEYWORD("super");
    ADD_KEYWORD("return");
    ADD_KEYWORD("defined?");
    ADD_KEYWORD("ensure");
    ADD_KEYWORD("__FILE__");
    ADD_KEYWORD("__LINE__");
    ADD_KEYWORD("__ENCODING__");

    ADD_KEYWORD2("alias", "alias ");
    ADD_KEYWORD2("undef", "undef ");
    ADD_KEYWORD2("rescue", "rescue ");
    ADD_KEYWORD2("BEGIN", "BEGIN {\n  %CURSOR%\n}");
    ADD_KEYWORD2("END", "END {\n  %CURSOR%\n}");

    ADD_KEYWORD2("if", "if %SELECT%condition%ENDSELECT%\n%END%");
    ADD_KEYWORD2("unless", "unless %SELECT%condition%ENDSELECT%\n%END%");
    ADD_KEYWORD2("elsif", "elsif %SELECT%condition%ENDSELECT%");
    ADD_KEYWORD2("while", "while %SELECT%condition%ENDSELECT%\n%END%");
    ADD_KEYWORD2("until", "until %SELECT%condition%ENDSELECT%\n%END%");
    ADD_KEYWORD2("for", "for %SELECT%condition%ENDSELECT% in \n%END%");
    ADD_KEYWORD2("def", "def %SELECT%name%ENDSELECT%\n%END%");
    ADD_KEYWORD2("class", "class %SELECT%Name%ENDSELECT%\n%END%");
    ADD_KEYWORD2("module", "module %SELECT%Name%ENDSELECT%\n%END%");
    ADD_KEYWORD2("case", "case %SELECT%condition%ENDSELECT%\n%END%");
    ADD_KEYWORD2("when", "when %SELECT%condition%ENDSELECT%");
    ADD_KEYWORD2("begin", "begin\n  %CURSOR%\n%END%");
    ADD_KEYWORD2("do", "do |%CURSOR%|\n%END%");

    eventuallyAddGroup(i18n("Ruby Keyword"), 800, list);
}

}
