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

#ifndef RUBY_EXPRESSION_VISITOR_H
#define RUBY_EXPRESSION_VISITOR_H

#include <duchain/duchainexport.h>
#include <duchain/helpers.h>
#include <duchain/types/classtype.h>
#include <parser/astvisitor.h>

namespace ruby {

class EditorIntegrator;

/**
 * @class ExpressionVisitor
 *
 * This class is used almost everywhere in the DUChain & Code Completion parts.
 * It's a visitor specialized in retrieving the types that can be extracted
 * for a particular AST. It also retrieves the last declaration that has been
 * found for a given expression.
 *
 * @note The DUChain should *never* be locked when calling a visit method of
 * this class. This class already takes care of locking issues.
 */
class KDEVRUBYDUCHAIN_EXPORT ExpressionVisitor : public AstVisitor
{
public:
    ExpressionVisitor(KDevelop::DUContext *ctx, EditorIntegrator *editor);
    explicit ExpressionVisitor(ExpressionVisitor *parent);

    /// @returns the last type seen.
    inline KDevelop::AbstractType::Ptr lastType() const
    {
        return m_lastType;
    }

    /// @returns true if the last expression was an alias, false otherwise.
    inline const bool & lastAlias() const
    {
        return m_alias;
    }

    /// @returns the last declaration seen.
    inline const KDevelop::DeclarationPointer & lastDeclaration() const
    {
        return m_lastDeclaration;
    }

    /// Set the internal context to @p ctx and reset all the other attributes.
    void setContext(KDevelop::DUContext *ctx);

    /// Set whether the type for the last declaration.
    void setIsClassMethod(bool isClassMethod);

    /// Set the declaration kind to @param kind.
    void setDeclarationKind(const DeclarationKind kind);

    /// Re-implemented from AstVisitor.
    void visitParameter(Ast *node) override;

protected:
    /// Visitor methods re-implemented from AstVisitor.

    bool declaredInContext(const QByteArray &name) const override;

    void visitString(Ast *node) override;
    void visitRegexp(Ast *node) override;
    void visitNumeric(Ast *node) override;
    void visitTrue(Ast *node) override;
    void visitFalse(Ast *node) override;
    void visitNil(Ast *node) override;
    void visitLine(Ast *node) override;
    void visitFile(Ast *node) override;
    void visitEncoding(Ast *node) override;
    void visitSelf(Ast *node) override;
    void visitRange(Ast *node) override;
    void visitSymbol(Ast *node) override;
    void visitName(Ast *node) override;
    void visitArray(Ast *node) override;
    void visitHash(Ast *node) override;
    void visitArrayValue(Ast *node) override;
    void visitMethodCall(Ast *node) override;
    void visitSuper(Ast *node) override;
    void visitLambda(Ast *node) override;
    void visitWhileStatement(Ast *node) override;
    void visitForStatement(Ast *node) override;
    void visitBinary(Ast *node) override;
    void visitBoolean(Ast *node) override;
    void visitIfStatement(Ast *node) override;
    void visitCaseStatement(Ast *node) override;
    void visitMethodStatement(Ast *node) override;

private:
    /// Set the last type seen to @p type.
    inline void encounter(KDevelop::AbstractType::Ptr type)
    {
        m_lastType = type;
    }

    /**
     * Get the ClassType that can be guessed from the given parameters.
     * @param ptr The container type.
     * @param node The container. Used to retrieve the contents type.
     * @param hasKey False by default. Set to true if the container has
     * key values (i.e. Hash).
     * @return the ClassType retrieved from the given parameters or nullptr.
     */
    ClassType::Ptr getContainer(KDevelop::AbstractType::Ptr ptr,
                                const Ast *node,
                                bool hasKey = false);

    /// Visit the last statement from @p node. Used for the implicit return.
    void visitLastStatement(Ast *node);

    /// Visit the method call members from @p node.
    void visitMethodCallMembers(Ast *node);

private:
    /// The DUContext that the visitor will use to find declarations.
    KDevelop::DUContext *m_ctx;

    /// The EditorIntegrator used to mess with the document.
    EditorIntegrator *m_editor;

    /// The last found DUContext. Used by the method call visitor.
    KDevelop::DUContext *m_lastCtx;

    /// The last AbstractType that has been found.
    KDevelop::AbstractType::Ptr m_lastType;

    /// The last DeclarationPointer that has been found.
    KDevelop::DeclarationPointer m_lastDeclaration;

    /// Tells us whether the last found declaration was an alias or not.
    bool m_alias;

    /// The kind for the last declaration.
    DeclarationKind m_declarationKind;
};

}

#endif // RUBY_EXPRESSION_VISITOR_H
