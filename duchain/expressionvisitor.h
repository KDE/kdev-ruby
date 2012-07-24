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
#include <duchain/types/objecttype.h>
#include <duchain/types/classtype.h>


namespace Ruby
{

class EditorIntegrator;


/**
 * TODO: Under construction
 */
class KDEVRUBYDUCHAIN_EXPORT ExpressionVisitor : public RubyAstVisitor
{
public:
    ExpressionVisitor(KDevelop::DUContext *ctx, EditorIntegrator *editor = NULL);
    ExpressionVisitor(ExpressionVisitor *parent);

    inline KDevelop::AbstractType::Ptr lastType() const
    {
        return m_lastType;
    }

    inline const bool & lastAlias() const
    {
        return m_alias;
    }

    inline const DeclarationPointer & lastDeclaration() const
    {
        return m_lastDeclaration;
    }

    inline const KDevelop::DUContext * lastContext() const
    {
        return m_lastCtx;
    }

    virtual void visitParameter(RubyAst *node);

    /// Set the internal context to @p ctx and reset all the other attributes.
    void setContext(KDevelop::DUContext *ctx);

protected:
    virtual void visitString(RubyAst *node);
    virtual void visitRegexp(RubyAst *node);
    virtual void visitNumeric(RubyAst *node);
    virtual void visitVariable(RubyAst *node);
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
    template<typename T> void encounter(TypePtr<T> type);
    inline void encounter(KDevelop::AbstractType::Ptr type)
    {
        m_lastType = type;
    }
    ClassType::Ptr getContainer(AbstractType::Ptr ptr, const RubyAst *node, bool hasKey = false);
    void visitLastStatement(RubyAst *node);


    void visitMethodCallMembers(RubyAst *node);

private:
    KDevelop::DUContext *m_ctx;
    EditorIntegrator *m_editor;
    AbstractType::Ptr m_lastType;
    DeclarationPointer m_lastDeclaration;
    bool m_alias;

    KDevelop::DUContext *m_lastCtx;
};

}


#endif /* RUBY_EXPRESSIONVISITOR_H */
