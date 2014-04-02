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


#ifndef RUBY_EXPRESSIONVISITOR_H
#define RUBY_EXPRESSIONVISITOR_H


#include <parser/rubyastvisitor.h>
#include <duchain/helpers.h>
#include <duchain/duchainexport.h>
#include <duchain/types/classtype.h>


namespace Ruby
{

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
class KDEVRUBYDUCHAIN_EXPORT ExpressionVisitor : public RubyAstVisitor
{
public:
    /**
     * Constructor.
     * @param ctx The DUContext this visitor is related to.
     * @param editor The EditorIntegrator for this visitor.
     */
    explicit ExpressionVisitor(KDevelop::DUContext *ctx, EditorIntegrator *editor);

    /**
     * Constructor.
     * @param parent The ExpressionVisitor this instance is parented to.
     */
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
    inline const DeclarationPointer & lastDeclaration() const
    {
        return m_lastDeclaration;
    }

    /// Set the internal context to @p ctx and reset all the other attributes.
    void setContext(KDevelop::DUContext *ctx);

    /// Set whether the type for the last declaration.
    void setIsClassMethod(bool isClassMethod);

    /// Re-implemented from RubyAstVisitor.
    virtual void visitParameter(RubyAst *node) override;

protected:
    /// Visitor methods re-implemented from RubyAstVisitor.

    virtual void visitString(RubyAst *node) override;
    virtual void visitRegexp(RubyAst *node) override;
    virtual void visitNumeric(RubyAst *node) override;
    virtual void visitTrue(RubyAst *node) override;
    virtual void visitFalse(RubyAst *node) override;
    virtual void visitNil(RubyAst *node) override;
    virtual void visitLine(RubyAst *node) override;
    virtual void visitFile(RubyAst *node) override;
    virtual void visitEncoding(RubyAst *node) override;
    virtual void visitSelf(RubyAst *node) override;
    virtual void visitRange(RubyAst *node) override;
    virtual void visitSymbol(RubyAst *node) override;
    virtual void visitName(RubyAst *node) override;
    virtual void visitArray(RubyAst *node) override;
    virtual void visitHash(RubyAst *node) override;
    virtual void visitArrayValue(RubyAst *node) override;
    virtual void visitMethodCall(RubyAst *node) override;
    virtual void visitSuper(RubyAst *node) override;
    virtual void visitLambda(RubyAst *node) override;
    virtual void visitWhileStatement(RubyAst *node) override;
    virtual void visitForStatement(RubyAst *node) override;
    virtual void visitBinary(RubyAst *node) override;
    virtual void visitBoolean(RubyAst *node) override;
    virtual void visitIfStatement(RubyAst *node) override;
    virtual void visitCaseStatement(RubyAst *node) override;

private:
    /// Set the last type seen to @p type.
    template<typename T> void encounter(TypePtr<T> type);

    /// Set the last AbstractType seen to @p type.
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
    ClassType::Ptr getContainer(AbstractType::Ptr ptr, const RubyAst *node,
                                bool hasKey = false);

    /// Visit the last statement from @p node. Used for the implicit return.
    void visitLastStatement(RubyAst *node);

    /// Visit the method call members from @p node.
    void visitMethodCallMembers(RubyAst *node);

private:
    /// The DUContext that the visitor will use to find declarations.
    KDevelop::DUContext *m_ctx;

    /// The EditorIntegrator used to mess with the document.
    EditorIntegrator *m_editor;

    /// The last found DUContext. Used by the method call visitor.
    KDevelop::DUContext *m_lastCtx;

    /// The last AbstractType that has been found.
    AbstractType::Ptr m_lastType;

    /// The last DeclarationPointer that has been found.
    DeclarationPointer m_lastDeclaration;

    /// Tells us whether the last found declaration was an alias or not.
    bool m_alias;

    /// The kind for the last declaration.
    DeclarationKind m_declarationKind;
};

} // End of namespace Ruby


#endif /* RUBY_EXPRESSIONVISITOR_H */
