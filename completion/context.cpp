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

// KDE + KDevelop
#include <language/duchain/duchainlock.h>
#include <language/duchain/duchain.h>
#include <language/duchain/types/unsuretype.h>

// Ruby
#include <completiondebug.h>
#include <parser/parser.h>
#include <duchain/loader.h>
#include <duchain/editorintegrator.h>
#include <duchain/expressionvisitor.h>
#include <duchain/declarations/moduledeclaration.h>
#include <duchain/declarations/methoddeclaration.h>
#include <completion/context.h>
#include <completion/items/keyworditem.h>
#include <completion/items/normalitem.h>
#include <completion/items/requirefileitem.h>

#define ADD_KEYWORD(name) list << CompletionTreeItemPointer(new KeywordItem(KDevelop::CodeCompletionContext::Ptr(this), name))
#define ADD_KEYWORD2(name, desc) list << CompletionTreeItemPointer(new KeywordItem(KDevelop::CodeCompletionContext::Ptr(this), name, desc))
#define ADD_ONE_LINER(name, desc) list << CompletionTreeItemPointer(new KeywordItem(KDevelop::CodeCompletionContext::Ptr(this), name, desc, true))
#define ADD_NORMAL(decl, depth) list << CompletionTreeItemPointer(new NormalItem(DeclarationPointer(decl), KDevelop::CodeCompletionContext::Ptr(this), depth));

using namespace KDevelop;

namespace ruby
{

const QSet<QString> MEMBER_STRINGS = QString(". :: < include extend").split(' ').toSet();
const int MEMBER_STRINGS_MAX = 7; // include

/**
 * The diferent types of contexts in code completion.
 */
enum class ContextType {
    NoMemberAccess,         /// A global completion should be done.
    MemberAccess,           /// obj.
    ModuleMemberAccess,     /// MyModule::
    BaseClassAccess,        /// After "class Klass <".
    ModuleMixinAccess,      /// After "include" or "extend".
    FileChoose              /// Autocompletion for files.
};

/**
 * It compresses the given @p text by removing spaces.
 */
void compressText(QString &text)
{
    for (int i = text.length() - 1; i >= 0; --i) {
        if (!text[i].isSpace()) {
            break;
        }
        text.remove(i, 1);
    }
}

/**
 * Get the ending string from the set of members for the given text.
 *
 * @param str The completion context text.
 * @returns the required ending string.
 */
QString getEndingFromSet(const QString &str)
{
    QString end;

    for (int i = qMin(str.length(), MEMBER_STRINGS_MAX); i > 0; --i) {
        end = str.right(i);
        if (MEMBER_STRINGS.contains(end)) {
            return end;
        }
    }
    return QString();
}

/**
 * Ugly method that tells if the given text is inside a class.
 *
 * @param text The given text.
 * @returns true if we're inside a class, false otherwise.
 */
bool insideClass(const QString &text)
{
    int idx = text.lastIndexOf(QStringLiteral("<"));
    int classIdx = text.lastIndexOf(QStringLiteral("class"), idx);
    int semicolon = text.lastIndexOf(QStringLiteral(";"), idx);
    return  (classIdx != -1 && (classIdx > semicolon));
}

/**
 * Returns the last n lines from the given text.
 *
 * @param str The given text.
 * @param n The number of lines to retrieve.
 */
QString lastNLines(const QString &str, int n)
{
    int curNewLine = str.lastIndexOf('\n');
    int nthLine = curNewLine;

    for (int i = 0; i < n; ++i) {
        if (curNewLine == -1) {
            break;
        } else {
            nthLine = curNewLine;
        }
        curNewLine = str.lastIndexOf('\n', curNewLine - 1);
    }

    // return the position after the newline, or whole str if no newline
    return str.mid(nthLine + 1);
}

/**
 * Guess the access kind depending on the given parameter.
 *
 * @param original The original text from the completion context.
 * @returns the proper CodeCompletionContext::CompletionContextType.
 */
ContextType findAccessKind(const QString &original)
{
    const QString text = getEndingFromSet(original);

    if (text == QStringLiteral(".")) {
        return ContextType::MemberAccess;
    }
    if (text == QStringLiteral("::")) {
        return ContextType::ModuleMemberAccess;
    }
    if (text == QStringLiteral("<") && insideClass(original)) {
        return ContextType::BaseClassAccess;
    }
    if (text == QStringLiteral("include") || text == QStringLiteral("extend")) {
        return ContextType::ModuleMixinAccess;
    }
    return ContextType::NoMemberAccess;
}

CodeCompletionContext::CodeCompletionContext(DUContextPointer ctxt, const QString &text,
                                             const QString &followingText,
                                             const CursorInRevision &pos, int depth)
    : KDevelop::CodeCompletionContext(ctxt, text, pos, depth)
    , m_valid(true), m_kind(ContextType::NoMemberAccess)
{
    if (!m_duContext || !isValidPosition()) {
        m_valid = false;
        return;
    }

    m_following = followingText;
    m_closing = 0;
    if (doRequireCompletion()) {
        return;
    }

    compressText(m_text);
    m_kind = findAccessKind(m_text);
}

CodeCompletionContext::~CodeCompletionContext()
{
}

QList<KDevelop::CompletionTreeItemPointer> CodeCompletionContext::completionItems(bool &abort, bool fullCompletion)
{
    QList<CompletionTreeItemPointer> items;
    if (!m_valid) {
        return items;
    }

    switch(m_kind) {
    case ContextType::MemberAccess:
        items += memberAccessItems();
        break;
    case ContextType::ModuleMemberAccess:
        items += moduleMemberAccessItems();
        break;
    case ContextType::BaseClassAccess:
        items += baseClassItems();
        break;
    case ContextType::ModuleMixinAccess:
        items += moduleMixinItems();
        break;
    case ContextType::FileChoose:
        items += fileChooseItems();
        break;
    default:
        items += standardAccessItems();
        addRubyKeywords();
        addRubySpecialBuiltins();
    }

    if (shouldAddParentItems(fullCompletion)) {
        items.append(parentContext()->completionItems(abort, fullCompletion));
    }
    return items;
}

QList<CompletionTreeElementPointer> CodeCompletionContext::ungroupedElements()
{
    return m_ungroupedItems;
}

bool CodeCompletionContext::isValidPosition()
{
    if (m_text.isEmpty()) {
        return true;
    }

    for (QString::iterator it = m_text.end(); it != m_text.begin(); --it) {
        if (*it == '\n') {
            break;
        }
        if (*it == '#') {
            return false;
        }
    }
    return true;
}

bool CodeCompletionContext::doRequireCompletion()
{
    QString line = lastNLines(m_text, 1).trimmed();
    KDevelop::Path relative;
    int idx = 8;

    if (!line.startsWith(QStringLiteral("require "))) {
        if (!line.startsWith(QStringLiteral("require_relative "))) {
            return false;
        }
        idx += 9;
        relative = KDevelop::Path(m_duContext->url().toUrl()).parent();
    }
    line = line.mid(idx).trimmed();
    m_closing = '\'';
    if ((idx = line.indexOf(QStringLiteral("'"))) < 0) {
        m_closing = '"';
        if ((idx = line.indexOf(QStringLiteral("\")")) < 0)) {
            m_closing = 0;
            return false;
        }
    }
    line = line.mid(idx + 1);

    m_includeItems = Loader::getFilesInSearchPath(line, m_following, relative);
    m_kind = ContextType::FileChoose;
    return true;
}

AbstractType::Ptr CodeCompletionContext::getExpressionType(const QString &token)
{
    AbstractType::Ptr res;
    QString expr = m_text.left(m_text.lastIndexOf(token));
    EditorIntegrator e;
    ExpressionVisitor ev(m_duContext.data(), &e);

    DUChainReadLocker lock;
    Parser parser(IndexedString(), expr.toUtf8());
    Ast *ast = parser.parse();
    if (!ast || !ast->tree) {
        return AbstractType::Ptr(nullptr);
    }
    lock.unlock();
    ev.visitCode(ast);
    res = ev.lastType();
    lock.lock();

    return res;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::getCompletionItemsFromType(AbstractType::Ptr type, bool scoped)
{
    QList<CompletionTreeItemPointer> res;
    if (type->whichType() == AbstractType::TypeUnsure) {
        auto unsure = type.staticCast<UnsureType>();
        int count = unsure->typesSize();
        for (int i = 0; i < count; i++) {
            res.append(getCompletionItemsForOneType(unsure->types()[i].abstractType(), scoped));
        }
    } else {
        res = getCompletionItemsForOneType(type, scoped);
    }
    return res;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::getCompletionItemsForOneType(AbstractType::Ptr type, bool scoped)
{
    QList<CompletionTreeItemPointer> list;
    QVector<DeclarationPair> decls;
    auto sType = type.dynamicCast<StructureType>();

    {
        DUChainReadLocker lock;
        if (!sType || !sType->internalContext(m_duContext->topContext())) {
            return QList<CompletionTreeItemPointer>();
        }
        DUContext *current = sType->internalContext(m_duContext->topContext());
        decls = current->allDeclarations(CursorInRevision::invalid(), m_duContext->topContext(), false);
    }

    foreach (DeclarationPair d, decls) {
        MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(d.first);
        if (md && md->accessPolicy() == Declaration::Public) {
            if (!scoped || (scoped && md->isClassMethod())) {

                ADD_NORMAL(d.first, d.second);
            }
        } else if (scoped && dynamic_cast<ModuleDeclaration *>(d.first)) {
            ADD_NORMAL(d.first, d.second);
        }
    }
    return list;
}

bool CodeCompletionContext::shouldAddParentItems(bool fullCompletion)
{
    return (m_parentContext && fullCompletion);
}

QList<CompletionTreeItemPointer> CodeCompletionContext::memberAccessItems()
{
    QList<CompletionTreeItemPointer> list;
    AbstractType::Ptr type = getExpressionType(QStringLiteral("."));
    if (type) {
        list << getCompletionItemsFromType(type);
    } else {
        qCDebug(COMPLETION) << "Oops: cannot access at the member";
    }
    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::moduleMemberAccessItems()
{
    QList<CompletionTreeItemPointer> list;
    AbstractType::Ptr type = getExpressionType(QStringLiteral("::"));
    if (type) {
        list << getCompletionItemsFromType(type, true);
    } else {
        qCDebug(COMPLETION) << "Oops: cannot access at the member";
    }

    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::baseClassItems()
{
    QList<CompletionTreeItemPointer> list;
    QVector<DeclarationPair> decls;

    {
        DUChainReadLocker lock;
        decls = m_duContext->allDeclarations(m_position, m_duContext->topContext());
    }

    foreach (DeclarationPair d, decls) {
        ModuleDeclaration *mDecl = dynamic_cast<ModuleDeclaration *>(d.first);
        if (mDecl && !mDecl->isModule()) {
            ADD_NORMAL(d.first, d.second);
        }
    }
    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::moduleMixinItems()
{
    QList<CompletionTreeItemPointer> list;
    QVector<DeclarationPair> decls;

    {
        DUChainReadLocker lock;
        decls = m_duContext->allDeclarations(m_position, m_duContext->topContext());
    }

    foreach (DeclarationPair d, decls) {
        if (dynamic_cast<ModuleDeclaration *>(d.first)) {
            ADD_NORMAL(d.first, d.second);
        }
    }
    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::fileChooseItems()
{
    QList<CompletionTreeItemPointer> list;

    foreach (const KDevelop::IncludeItem &item, m_includeItems) {
        list << CompletionTreeItemPointer(new RequireFileItem(item, m_closing));
    }
    return list;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::standardAccessItems()
{
    QList<CompletionTreeItemPointer> list;
    QVector<DeclarationPair> decls;

    // Add one-liners (i.e. shebang)
    if (m_position.line == 0 && (m_text.startsWith(QStringLiteral("#"))
                || m_text.isEmpty())) {
        ADD_ONE_LINER(QStringLiteral("#!/usr/bin/env ruby"), i18n("insert Shebang line"));
        ADD_ONE_LINER(QStringLiteral("# encoding: UTF-8"), i18n("insert encoding line"));
    }

    // Find everything that is accessible at this point
    {
        DUChainReadLocker lock;
        decls = m_duContext->allDeclarations(m_position, m_duContext->topContext());
    }
    foreach (DeclarationPair d, decls) {
        ADD_NORMAL(d.first, d.second);
    }
    return list;
}

void CodeCompletionContext::eventuallyAddGroup(const QString &name, int priority,
                                               QList<CompletionTreeItemPointer> items)
{
    KDevelop::CompletionCustomGroupNode *node = new KDevelop::CompletionCustomGroupNode(name, priority);
    node->appendChildren(items);
    m_ungroupedItems << CompletionTreeElementPointer(node);
}

void CodeCompletionContext::addRubyKeywords()
{
    QList<CompletionTreeItemPointer> list;

    // "Ultra-simple" statements. Some of them may not be *that* useful.
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
    ADD_KEYWORD("__FILE__");
    ADD_KEYWORD("__LINE__");
    ADD_KEYWORD("__ENCODING__");

    // Simple statements
    ADD_KEYWORD2("alias", "alias ");
    ADD_KEYWORD2("undef", "undef ");
    ADD_KEYWORD2("rescue", "%UNINDENT%rescue ");
    ADD_KEYWORD2("ensure", "%UNINDENT%ensure%INDENT%%CURSOR%\n");
    ADD_KEYWORD2("BEGIN", "BEGIN {\n%INDENT%%CURSOR%\n}");

    // Take care of complex statements that can be just statement modifiers
    if (lastNLines(m_text, 1).isEmpty()) {
        ADD_KEYWORD2("if", "if %SELECT%condition%ENDSELECT%\n%END%");
        ADD_KEYWORD2("unless", "unless %SELECT%condition%ENDSELECT%\n%END%");
        ADD_KEYWORD2("while", "while %SELECT%condition%ENDSELECT%\n%END%");
        ADD_KEYWORD2("until", "until %SELECT%condition%ENDSELECT%\n%END%");
    } else {
        ADD_KEYWORD2("if", "if %SELECT%condition%ENDSELECT%");
        ADD_KEYWORD2("unless", "unless %SELECT%condition%ENDSELECT%");
        ADD_KEYWORD2("while", "while %SELECT%condition%ENDSELECT%");
        ADD_KEYWORD2("until", "until %SELECT%condition%ENDSELECT%");
    }

    // Complex constructions
    ADD_KEYWORD2("elsif", "%UNINDENT%elsif %SELECT%condition%ENDSELECT%");
    ADD_KEYWORD2("else", "%UNINDENT%else\n%INDENT%%CURSOR%");
    ADD_KEYWORD2("for", "for %SELECT%condition%ENDSELECT% in \n%END%");
    ADD_KEYWORD2("def", "def %SELECT%name%ENDSELECT%\n%END%");
    ADD_KEYWORD2("class", "class %SELECT%Name%ENDSELECT%\n%END%");
    ADD_KEYWORD2("module", "module %SELECT%Name%ENDSELECT%\n%END%");
    ADD_KEYWORD2("case", "case %SELECT%condition%ENDSELECT%\n%END%");
    ADD_KEYWORD2("when", "%UNINDENT%when %SELECT%condition%ENDSELECT%");
    ADD_KEYWORD2("begin", "begin\n%INDENT%%CURSOR%\n%END%");
    ADD_KEYWORD2("do", "do %SELECT%||%ENDSELECT%\n%END%");

    // Group all these keywords into the "Ruby Keyword" group.
    eventuallyAddGroup(i18n("Ruby Keyword"), 800, list);
}

void CodeCompletionContext::addRubySpecialBuiltins()
{
    QList<CompletionTreeItemPointer> list;

    // Not really keywords, but who cares? ;)
    ADD_KEYWORD2("include", "include %SELECT%MyModule%ENDSELECT%");
    ADD_KEYWORD2("extend", "extend %SELECT%MyModule%ENDSELECT%");
    ADD_KEYWORD2("require", "require '%CURSOR%'");
    ADD_KEYWORD2("require_relative", "require_relative '%CURSOR%'");

    // Group all these special builtins
    eventuallyAddGroup(i18n("Ruby Builtins"), 800, list);
}

}
