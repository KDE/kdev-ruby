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

    inline KDevelop::AbstractType::Ptr lastType() const
    {
        return (m_lastType.isEmpty()) ? KDevelop::AbstractType::Ptr(new ObjectType()) : m_lastType.last();
    }

protected:
    virtual void visitString(RubyAst *node);

private:
    TypePtr<ObjectType> getBuiltinsType(const QString &desc, KDevelop::DUContext *ctx);
    void encounter(KDevelop::AbstractType::Ptr type);
    void encounter(TypePtr<ObjectType> type);

private:
    KDevelop::DUContext *m_ctx;
    QStack<KDevelop::AbstractType::Ptr> m_lastType; // TODO: just a pointer to the last one ?
};

}


#endif /* RUBY_EXPRESSIONVISITOR_H */
