/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef RUBY_VARIABLEDECLARATION_H
#define RUBY_VARIABLEDECLARATION_H


#include <language/duchain/declaration.h>
#include <language/duchain/declarationdata.h>
#include <parser/node.h>
#include <duchain/duchainexport.h>


namespace Ruby
{

/**
 * @class VariableDeclarationData
 * Private data structure for VariableDeclaration.
 */
class KDEVRUBYDUCHAIN_EXPORT VariableDeclarationData : public KDevelop::DeclarationData
{
public:
    /// Constructor
    explicit VariableDeclarationData()
        : KDevelop::DeclarationData(), m_kind(2)
    {
        /* There's nothing to do here */
    }

    /// Copy constructor.
    explicit VariableDeclarationData(const VariableDeclarationData &rhs)
        : KDevelop::DeclarationData(rhs)
    {
        m_kind = rhs.m_kind;
    }

    /// Destructor.
    ~VariableDeclarationData()
    {
        /* There's nothing to do here */
    }

public:
    /// The kind of a variable declaration (i.e. constant, ivar, ...)
    int m_kind;
};

/**
 * @class VariableDeclaration
 *
 * Represents the declaration of a variable in ruby.
 */
class KDEVRUBYDUCHAIN_EXPORT VariableDeclaration : public KDevelop::Declaration
{
public:
    /**
     * Constructor.
     * @param range The range of this declaration.
     * @param ctx The context of this declaration.
     */
    explicit VariableDeclaration(const KDevelop::RangeInRevision &range,
                                 KDevelop::DUContext *context);

    /**
     * Constructor.
     * @param data The data to be copied.
     * @param range The range of this declaration.
     */
    explicit VariableDeclaration(VariableDeclarationData &data,
                                 const KDevelop::RangeInRevision &range);

    /// Copy constructor
    explicit VariableDeclaration(const VariableDeclaration &rhs);

    /// Copy constructor.
    explicit VariableDeclaration(VariableDeclarationData &data);

    /**
     * Copy constructor.
     * @param data The data to be copied.
     */
    explicit VariableDeclaration(KDevelop::DeclarationData &data);

    /// Given a @p node, set the variable kind.
    void setVariableKind(const Node *node);

    /// Force the variable kind to the given @p kind.
    void setVariableKind(int kind);

    /// @returns the kind of this variable declaration.
    int variableKind() const;

    // Helper methods

    inline bool isNormal() const { return d_func()->m_kind == flags_t::var; }
    inline bool isGlobal() const { return d_func()->m_kind == flags_t::global; }
    inline bool isIvar() const { return d_func()->m_kind == flags_t::ivar; }
    inline bool isCvar() const { return d_func()->m_kind == flags_t::cvar; }
    inline bool isConstant() const { return d_func()->m_kind == flags_t::constant; }

    // Arguments

    inline bool hasStar() const { return d_func()->m_kind == flags_t::kwrest; }
    inline bool isBlock() const { return d_func()->m_kind == flags_t::block; }
    inline bool isOpt() const { return d_func()->m_kind == flags_t::opt; }

    enum { Identity = 47 /** The id of this Type. */ };

private:
    DUCHAIN_DECLARE_DATA(VariableDeclaration)
};

} // End of namespace: Ruby


#endif // RUBY_VARIABLEDECLARATION_H
