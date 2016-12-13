/* This file is part of KDevelop
 *
 * Copyright 2010 Niko Sams <niko.sams@gmail.com>
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright (C) 2011-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#ifndef RUBY_CONTEXT_BUILDER_H
#define RUBY_CONTEXT_BUILDER_H

#include <duchain/duchainexport.h>
#include <language/duchain/builders/abstractcontextbuilder.h>
#include <language/duchain/problem.h>
#include <parser/astvisitor.h>
#include <util/path.h>

namespace ruby {

class EditorIntegrator;
using ContextBuilderBase = KDevelop::AbstractContextBuilder<Ast, NameAst>;

/**
 * @class ContextBuilder
 *
 * The ContextBuilder is a convenient class to handle contexts on the AST.
 * The other builders have this class as a base class.
 */
class KDEVRUBYDUCHAIN_EXPORT ContextBuilder
    : public ContextBuilderBase
    , public AstVisitor
{
public:
    ContextBuilder();
    virtual ~ContextBuilder();

    /// Re-implemented from KDevelop::AbstractContextBuilder.
    virtual KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString &url,
                                                   Ast *node,
                                                   KDevelop::ReferencedTopDUContext updateContext = {}) override;

    /// @returns a list of unresolved imports.
    inline const QVector<KDevelop::IndexedString> unresolvedImports() const
    {
        return m_unresolvedImports;
    }

    /// Set the priority of the build to the given @p priority.
    inline void setPriority(int priority)
    {
        m_priority = priority;
    }

protected:
    /// Set the given @p editor as the EditorIntegrator for this class.
    void setEditor(EditorIntegrator *editor);

    /**
     * @returns the editor used by the builder.
     * @note Used by KDevelop::AbstractContextBuilder.
     */
    EditorIntegrator * editor() const;

    /**
     * The following are methods re-implemented from
     * KDevelop::AbstractContextBuilder that deal with contexts and nodes.
     */

    void setContextOnNode(Ast *node, KDevelop::DUContext *ctx) override;
    KDevelop::DUContext * contextFromNode(Ast *node) override;
    KDevelop::DUContext * newContext(const KDevelop::RangeInRevision &range) override;
    virtual KDevelop::TopDUContext * newTopContext(const KDevelop::RangeInRevision &range,
                                                   KDevelop::ParsingEnvironmentFile *file = nullptr) override;

    /// And now methods that deal with nodes, documents and ranges.

    /// @returns KDevelop::CursorInRevision at the start of @param node.
    const KDevelop::CursorInRevision startPos(const Ast *node) const;

    /// Re-implemented from KDevelop::AbstractContextBuilder.
    KDevelop::RangeInRevision editorFindRange(Ast *fromRange, Ast *toRange) override;

    /// Given a @param node, it @returns a KDevelop::DocumentRange.
    const KDevelop::DocumentRange getDocumentRange(const Node *node) const;

    /// Given a @param range, it @returns a KDevelop::DocumentRange.
    const KDevelop::DocumentRange getDocumentRange(const KDevelop::RangeInRevision &range) const;

    /// Re-implemented from KDevelop::AbstractContextBuilder.
    KDevelop::QualifiedIdentifier identifierForNode(NameAst *name) override;

    /// Methods re-implemented from AstVisitor or mere helpers.

    void startVisiting(Ast *node) override;
    void visitModuleStatement(Ast *node) override;
    void visitClassStatement(Ast *node) override;
    void visitMethodStatement(Ast *node) override;
    void visitBlock(Ast *node) override;
    void visitRequire(Ast *node, bool relative = false) override;

    /**
     * Issue a require. The required file will be scheduled for parsing
     * if it's the first time that is loaded.
     *
     * @param path The path where the required file is located.
     */
    void require(const KDevelop::Path &path);

    /**
     * Append a new problem that appeared at the given @p node with @p msg
     * as its description. The @p sev is the severity of the problem, which
     * is IProblem::Error by default.
     * @note that you should call i18n() first.
     */
    void appendProblem(const Node *node, const QString &msg,
                       KDevelop::IProblem::Severity sev = KDevelop::IProblem::Error);

    /**
     * Append a new problem that appeared at the given @p range with @p msg
     * as its description. The @p sev is the severity of the problem, which
     * is IProblem::Error by default.
     * @note that you should call i18n() first.
     */
    void appendProblem(const KDevelop::RangeInRevision &range,
                       const QString &msg,
                       KDevelop::IProblem::Severity sev = KDevelop::IProblem::Error);

protected:
    bool m_mapAst; // make KDevelop::AbstractContextBuilder happy.
    EditorIntegrator *m_editor;
    QVector<KDevelop::IndexedString> m_unresolvedImports;

private:
    /**
     * @returns the range that contains the method arguments
     * contained in @param node.
     */
    const KDevelop::RangeInRevision rangeForMethodArguments(Ast *node);

private:
    int m_priority;
    KDevelop::TopDUContextPointer m_builtinsContext;
};

}

#endif // RUBY_CONTEXT_BUILDER_H
