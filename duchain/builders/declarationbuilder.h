/* This file is part of KDevelop
 *
 * Copyright 2010 Niko Sams <niko.sams@gmail.com>
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright (C) 2011-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#ifndef DECLARATION_BUILDER_H
#define DECLARATION_BUILDER_H


#include <language/duchain/builders/abstractdeclarationbuilder.h>
#include <duchain/builders/typebuilder.h>
#include <duchain/helpers.h>


namespace Ruby
{

class ModuleDeclaration;
class MethodDeclaration;

typedef KDevelop::AbstractDeclarationBuilder<Ast, NameAst, TypeBuilder> DeclarationBuilderBase;

/**
 * @class DeclarationBuilder
 *
 * The DeclarationBuilder iterates a Ast to build declarations.
 */
class KDEVRUBYDUCHAIN_EXPORT DeclarationBuilder : public DeclarationBuilderBase
{
public:
    /**
     * Constructor.
     * @param editor The EditorIntegrator to be used.
     */
    explicit DeclarationBuilder(EditorIntegrator *editor);

    /// Destructor.
    virtual ~DeclarationBuilder();

protected:
    /// Re-implemented from KDevelop::AbstractDeclarationBuilder.
    virtual void closeDeclaration() override;
    virtual void closeContext() override;

    /// Re-implemented from the ContextBuilder.
    virtual void startVisiting(Ast *node) override;

    /// Methods re-implemented from AstVisitor.

    virtual bool declaredInContext(const QByteArray &name) const override;

    virtual void visitClassStatement(Ast *node) override;
    virtual void visitSingletonClass(Ast *node) override;
    virtual void visitModuleStatement(Ast *node) override;
    virtual void visitMethodStatement(Ast *node) override;
    virtual void visitParameter(Ast *node) override;
    virtual void visitBlock(Ast *node) override;
    virtual void visitBlockVariables(Ast *node) override;
    virtual void visitReturnStatement(Ast *node) override;
    virtual void visitAssignmentStatement(Ast *node) override;
    virtual void visitAliasStatement(Ast *node) override;
    virtual void visitMethodCall(Ast *node) override;
    virtual void visitMixin(Ast *node, bool include) override;
    virtual void visitForStatement(Ast *node) override;
    virtual void visitAccessSpecifier(const access_t policy) override;
    virtual void visitYieldStatement(Ast *node) override;
    virtual void visitRescueArg(Ast *node) override;

private:
    /// @returns the range of the name of the given @p node.
    const KDevelop::RangeInRevision getNameRange(const Ast *node) const;

    /**
     * Open a context for a class/module declaration. It will also open the
     * context for the eigen class.
     *
     * @param decl The declaration itself.
     * @param node The node where the declaration resides.
     */
    void openContextForClassDefinition(ModuleDeclaration *decl, Ast *node);

    /**
     * Open or re-open if already exists a declaration in the current context.
     *
     * @param id The qualified identifier for the declaration.
     * @param range The range in which the declaration is contained.
     * @param context The context in which the declaration is being performed.
     * @returns an opened declaration. It returns nullptr if something
     * went wrong.
     */
    template<typename T> T * reopenDeclaration(const KDevelop::QualifiedIdentifier &id,
                                               const KDevelop::RangeInRevision &range,
                                               KDevelop::DUContext *context,
                                               DeclarationKind kind = DeclarationKind::Unknown);

    /**
     * Open or re-open a method declaration in the current context. This is,
     * indeed, an specialization of the reopenDeclaration method.
     *
     * @param id The qualified identifier for the declaration.
     * @param range The range in which the declaration is contained.
     * @param classMethod Set to true of this is a class method, otherwise set
     * false if this is an instance method.
     * @returns an opened method declaration. It returns nullptr if something
     * went wrong.
     */
    MethodDeclaration * reopenDeclaration(const KDevelop::QualifiedIdentifier &id,
                                          const KDevelop::RangeInRevision &range,
                                          bool classMethod);

    /**
     * Declare a variable in the current context.
     *
     * @param id The qualified identifier of the new variable declaration.
     * @param type The type of the new variable declaration.
     * @param node The node that contains this variable declaration.
     */
    void declareVariable(const KDevelop::QualifiedIdentifier &id,
                         const KDevelop::AbstractType::Ptr &type,
                         Ast *node,
                         KDevelop::DUContext::SearchFlag flags = KDevelop::DUContext::NoSearchFlags);

    /**
     * Alias a method declaration.
     *
     * @param id The id of the new method.
     * @param range The range of the new method.
     * @param decl The MethodDeclaration that it's being aliased.
     * @note the DUChain *must* be locked before calling this method.
     */
    void aliasMethodDeclaration(const KDevelop::QualifiedIdentifier &id,
                                const KDevelop::RangeInRevision &range,
                                const MethodDeclaration *decl);

    /// @returns the current access policy.
    inline KDevelop::Declaration::AccessPolicy currentAccessPolicy() const
    {
        if (m_accessPolicy.isEmpty()) {
            return KDevelop::Declaration::Public;
        }
        return m_accessPolicy.top();
    }

    /// Sets the current access policy to the given @p policy.
    inline void setAccessPolicy(KDevelop::Declaration::AccessPolicy policy)
    {
        m_accessPolicy.top() = policy;
    }

    /// Module mixins helper methods.

    /**
     * Get the module declaration that is being mixed-in.
     *
     * @param module The include/extend AST.
     * @returns the ModuleDeclaration that is being mixed-in, or nullptr if this
     * module doesn't actually exist.
     */
    ModuleDeclaration * getModuleDeclaration(Ast *module) const;

    /**
     * @returns the declared methods inside the given declaration @p decl,
     * which is a class or a module.
     */
    QList<MethodDeclaration *> getDeclaredMethods(const KDevelop::Declaration *decl);

    /// other stuff.

    /**
     * Check whether the given declaration can be redeclared or not.
     *
     * @param decl The declaration to be redeclared.
     * @param id The id of the declaration.
     * @param range The range of the declaration.
     * @param kind The kind that the declaration has to have.
     * @returns true if it's a valid re-declaration, and false otherwise.
     */
    bool validReDeclaration(KDevelop::Declaration *decl,
                            const KDevelop::QualifiedIdentifier &id,
                            const KDevelop::RangeInRevision &range,
                            DeclarationKind kind);

    /**
     * Get the context that contains the name of the class/module being
     * declared. If the container of the name does not exist, then the
     * current context is returned. For example, for the following declaration:
     *
     *   class; A::B; end
     *
     * The returned context will be the internal context of A. In this same
     * example, if A does not exist, then the current context would've been
     * returned.
     * @param node The node of the class/module declaration.
     */
    KDevelop::DUContext * getContainedNameContext(Ast *node);

    /**
     * This is a helper method that iterates over the call args of a method
     * call in order to update the type of each parameter accordingly.
     * @param mc A list of call args.
     * @param lastMethod The last encountered method call.
     */
    void visitMethodCallArgs(const Ast *mc,
                             const KDevelop::DeclarationPointer &lastMethod);

    /// @returns true if we're inside a class/module, false otherwise.
    inline bool insideClassModule() const
    {
        return m_classDeclarations.size() > 0;
    }

    /// @returns the last class/module.
    inline KDevelop::Declaration * lastClassModule() const
    {
        return m_classDeclarations.top().data();
    }

private:
    EditorIntegrator *m_editor;
    QStack<KDevelop::Declaration::AccessPolicy> m_accessPolicy;
    QStack<KDevelop::DeclarationPointer> m_classDeclarations;
    bool m_injected;
    bool m_instance;
    KDevelop::Declaration *m_lastMethodCall;
};

} // End of namespace Ruby

#endif // DECLARATION_BUILDER_H
