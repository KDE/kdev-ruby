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


#include <duchain/duchainexport.h>
#include <parser/rubyastvisitor.h>
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
 */
class KDEVRUBYDUCHAIN_EXPORT ExpressionVisitor : public RubyAstVisitor
{
public:
    /**
     * Constructor.
     * @param ctx The DUContext this visitor is related to.
     * @param editor The EditorIntegrator for this visitor.
     */
    ExpressionVisitor(KDevelop::DUContext *ctx, EditorIntegrator *editor);

    /**
     * Constructor.
     * @param parent The ExpressionVisitor this instance is parented to.
     */
    ExpressionVisitor(ExpressionVisitor *parent);

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

    /// Re-implemented from RubyAstVisitor.
    virtual void visitParameter(RubyAst *node);

protected:
    /// Visitor method re-implemented from RubyAstVisitor.

    virtual void visitString(RubyAst *node);
    virtual void visitRegexp(RubyAst *node);
    virtual void visitNumeric(RubyAst *node);
    virtual void visitTrue(RubyAst *node);
    virtual void visitFalse(RubyAst *node);
    virtual void visitNil(RubyAst *node);
    virtual void visitLine(RubyAst *node);
    virtual void visitFile(RubyAst *node);
    virtual void visitEncoding(RubyAst *node);
    virtual void visitSelf(RubyAst *node);
    virtual void visitRange(RubyAst *node);
    virtual void visitSymbol(RubyAst *node);
    virtual void visitName(RubyAst *node);
    virtual void visitArray(RubyAst *node);
    virtual void visitHash(RubyAst *node);
    virtual void visitArrayValue(RubyAst *node);
    virtual void visitMethodCall(RubyAst *node);
    virtual void visitLambda(RubyAst *node);
    virtual void visitWhileStatement(RubyAst *node);
    virtual void visitForStatement(RubyAst *node);
    virtual void visitBinary(RubyAst *node);
    virtual void visitBoolean(RubyAst *node);
    virtual void visitIfStatement(RubyAst *node);
    virtual void visitCaseStatement(RubyAst *node);

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
     * @return the ClassType retrieved from the given parameters or NULL.
     */
    ClassType::Ptr getContainer(AbstractType::Ptr ptr, const RubyAst *node,
                                bool hasKey = false);

    /// Visit the last statement from @p node. Used for the implicit return.
    void visitLastStatement(RubyAst *node);

    /// Visit the method call members from @p node.
    void visitMethodCallMembers(RubyAst *node);

private:
    KDevelop::DUContext *m_ctx;
    KDevelop::DUContext *m_lastCtx;
    EditorIntegrator *m_editor;
    AbstractType::Ptr m_lastType;
    DeclarationPointer m_lastDeclaration;
    bool m_alias;
};

} // End of namespace Ruby


#endif /* RUBY_EXPRESSIONVISITOR_H */
