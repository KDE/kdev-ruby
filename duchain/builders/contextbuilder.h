/* This file is part of KDevelop
 *
 * Copyright 2010 Niko Sams <niko.sams@gmail.com>
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright (C) 2011 Miquel Sabaté <mikisabate@gmail.com>
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


#ifndef CONTEXTBUILDER_H
#define CONTEXTBUILDER_H


// KDevelop
#include <language/duchain/builders/abstractcontextbuilder.h>

// Ruby
#include <duchain/duchainexport.h>
#include <parser/rubyastvisitor.h>


namespace Ruby
{

class EditorIntegrator;
typedef KDevelop::AbstractContextBuilder<RubyAst, NameAst> ContextBuilderBase;

/**
 * @class ContextBuilder
 *
 * The ContextBuilder is a convenient class to handle contexts on the AST.
 * The other builders have this class as a base class.
 */
class KDEVRUBYDUCHAIN_EXPORT ContextBuilder : public ContextBuilderBase, public RubyAstVisitor
{
public:
    /// Constructor
    ContextBuilder();

    /// Destructor
    virtual ~ContextBuilder();

    /// Re-implemented from KDevelop::AbstractContextBuilder.
    virtual KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString &url, RubyAst *node,
        KDevelop::ReferencedTopDUContext updateContext = KDevelop::ReferencedTopDUContext());

    /// @returns a list of unresolved imports.
    inline const QVector<IndexedString> unresolvedImports() const
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

    virtual void setContextOnNode(RubyAst *node, DUContext *ctx);
    virtual KDevelop::DUContext * contextFromNode(RubyAst *node);
    virtual KDevelop::DUContext * newContext(const RangeInRevision &range);
    virtual KDevelop::TopDUContext * newTopContext(const RangeInRevision &range,
                                                   ParsingEnvironmentFile *file = 0);

    /// And now methods that deal with nodes, documents and ranges.

    /// @returns KDevelop::CursorInRevision at the start of @param node.
    KDevelop::CursorInRevision startPos(RubyAst *node) const;

    /// Re-implemented from KDevelop::AbstractContextBuilder.
    virtual KDevelop::RangeInRevision editorFindRange(RubyAst *fromRange, RubyAst *toRange);

    /// Given a @param node, it @returns a KDevelop::DocumentRange.
    KDevelop::DocumentRange getDocumentRange(Node *node) const;

    /// Given a @param range, it @returns a KDevelop::DocumentRange.
    KDevelop::DocumentRange getDocumentRange(const KDevelop::RangeInRevision &range) const;

    /// Re-implemented from KDevelop::AbstractContextBuilder.
    virtual KDevelop::QualifiedIdentifier identifierForNode(NameAst *name);

    /// Methods re-implemented from RubyAstVisitor or mere helpers.

    virtual void startVisiting(RubyAst *node);
    virtual void visitModuleStatement(RubyAst *node);
    virtual void visitClassStatement(RubyAst *node);
    virtual void visitMethodStatement(RubyAst *node);
    virtual void visitRequire(RubyAst *node, bool relative = false);

    /**
     * Append a new problem that appeared at the given @p node with @p msg
     * as its description. The @p sev is the severity of the problem, which
     * is ProblemData::Error by default.
     * @note that you should call i18n() first.
     */
    void appendProblem(Node *node, const QString &msg,
                       ProblemData::Severity sev = ProblemData::Error);

    /**
     * Append a new problem that appeared at the given @p range with @p msg
     * as its description. The @p sev is the severity of the problem, which
     * is ProblemData::Error by default.
     * @note that you should call i18n() first.
     */
    void appendProblem(const RangeInRevision &range, const QString &msg,
                       ProblemData::Severity sev = ProblemData::Error);

protected:
    bool m_mapAst; // make KDevelop::AbstractContextBuilder happy.
    EditorIntegrator *m_editor;
    QVector<IndexedString> m_unresolvedImports;

private:
    /**
     * @returns the range that contains the method arguments
     * contained in @param node.
     */
    RangeInRevision rangeForMethodArguments(RubyAst *node);

    /**
     * Issue a require. The required file will be scheduled for parsing
     * if it's the first time that is loaded.
     *
     * @param node The node with the require call.
     * @param local True if this is a require_relative, false otherwise.
     */
    void require(Node *node, bool local);

private:
    int m_priority;
    KDevelop::TopDUContextPointer m_builtinsContext;
};

} // End of namespace Ruby


#endif // CONTEXTBUILDER_H
