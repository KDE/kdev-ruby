/* This file is part of KDevelop
 *
 * Copyright 2010 Niko Sams <niko.sams@gmail.com>
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright 2011 Miquel Sabaté <mikisabate@gmail.com>
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


#ifndef DECLARATIONBUILDER_H
#define DECLARATIONBUILDER_H


#include <language/duchain/builders/abstractdeclarationbuilder.h>
#include <duchain/builders/typebuilder.h>


namespace Ruby
{

class ModuleDeclaration;
class MethodDeclaration;

typedef KDevelop::AbstractDeclarationBuilder<RubyAst, NameAst, TypeBuilder> DeclarationBuilderBase;

/**
 * @class DeclarationBuilder
 *
 * The DeclarationBuilder iterates a RubyAst to build declarations.
 */
class KDEVRUBYDUCHAIN_EXPORT DeclarationBuilder : public DeclarationBuilderBase
{
public:
    /// Constructor.
    DeclarationBuilder();

    /**
     * Constructor.
     * @param editor The EditorIntegrator to be used.
     */
    DeclarationBuilder(EditorIntegrator *editor);

    /// Destructor.
    virtual ~DeclarationBuilder();

protected:
    /// Re-implemented from KDevelop::AbstractDeclarationBuilder.
    virtual void closeDeclaration();
    virtual void closeContext();

    /// Re-implemented from the ContextBuilder.
    virtual void startVisiting(RubyAst *node);

    /// Methods re-implemented from RubyAstVisitor.

    virtual void visitClassStatement(RubyAst *node);
    virtual void visitSingletonClass(RubyAst *node);
    virtual void visitModuleStatement(RubyAst *node);
    virtual void visitMethodStatement(RubyAst *node);
    virtual void visitParameter(RubyAst *node);
    virtual void visitVariable(RubyAst *node);
    virtual void visitBlock(RubyAst *node);
    virtual void visitBlockVariables(RubyAst *node);
    virtual void visitReturnStatement(RubyAst *node);
    virtual void visitAssignmentStatement(RubyAst *node);
    virtual void visitAliasStatement(RubyAst *node);
    virtual void visitMethodCall(RubyAst *node);
    virtual void visitMixin(RubyAst *node, bool include);
    virtual void visitForStatement(RubyAst *node);
    virtual void visitAccessSpecifier(short int policy);
    virtual void visitYieldStatement(RubyAst *node);

private:
    /// @returns the range of the name of the given @p node.
    KDevelop::RangeInRevision getNameRange(const RubyAst *node);

    /// Given a @param node, open a context for a class definition.
    void openContextForClassDefinition(RubyAst *node);

    /**
     * Open or re-open if already exists a declaration in the current context.
     *
     * @param id The qualified identifier for the declaration.
     * @param range The range in which the declaration is contained.
     * @returns an opened declaration.
     */
    template<typename T> T * reopenDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range);

    /**
     * Specialized version of the more generic reopenDeclaration for
     * MethodDeclaration's. It takes an extra argument @p classMethod. Set to
     * true to specify that a class method is being opened, set to false otherwise.
     */
    MethodDeclaration * reopenDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range, bool classMethod);

    /**
     * Declare a variable in the current context.
     *
     * @param id The qualified identifier of the new variable declaration.
     * @param type The type of the new variable declaration.
     * @param node The node that contains this variable declaration.
     */
    void declareVariable(const KDevelop::QualifiedIdentifier &id, KDevelop::AbstractType::Ptr type, RubyAst *node);

    /**
     * Alias a method declaration.
     *
     * @param id The id of the new method.
     * @param range The range of the new method.
     * @param decl The MethodDeclaration that it's being aliased.
     */
    void aliasMethodDeclaration(const KDevelop::QualifiedIdentifier &id,
                                const KDevelop::RangeInRevision &range,
                                MethodDeclaration *decl);

    /// @returns the current access policy.
    inline KDevelop::Declaration::AccessPolicy currentAccessPolicy() const
    {
        if (m_accessPolicy.isEmpty())
            return KDevelop::Declaration::Public;
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
     * @param module The include/extend AST.
     * @returns the ModuleDeclaration that is being mixed-in.
     */
    ModuleDeclaration * getModuleDeclaration(RubyAst *module);

    /**
     * @returns the declared methods inside the given declaration @p decl,
     * which is a class or a module.
     * @note This method already acquires a read lock for the DUChain.
     */
    QList<MethodDeclaration *> getDeclaredMethods(Declaration *decl);

    /// other stuff.

    /**
     * This is a helper method that tells us if this is a valid re-declaration.
     * @param id The identifier of the declaration.
     * @param range The range of this declaration.
     * @param isClass Optional parameter, set to false if this is a module. The
     * default value is true, meaning that this is expected to be a class.
     * @returns false if we expected this to be a Class/Module and it's
     * something else, true otherwise.
     * @note If it returns false, it'll also append a new problem (TypeError).
     */
    bool validReDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range,
                            bool isClass = true);

    /**
     * This is a helper method that iterates over the call args of a method
     * call in order to update the type of each parameter accordingly.
     * @param mc A list of call args.
     * @param lastMethod The last encountered method call.
     */
    void visitMethodCallArgs(RubyAst *mc, DeclarationPointer lastMethod);

    /**
     * @returns true if we're inside a class/module, false otherwise.
     */
    inline bool insideClassModule() const
    {
        return m_classDeclarations.size() > 0;
    }

    /**
     * @returns the last class/module.
     */
    inline Declaration * lastClassModule() const
    {
        return m_classDeclarations.top().data();
    }

private:
    EditorIntegrator *m_editor;
    QStack<KDevelop::Declaration::AccessPolicy> m_accessPolicy;
    QStack<DeclarationPointer> m_classDeclarations;
    bool m_injected;
    bool m_instance;
    Declaration *m_lastMethodCall;
};

} // End of namespace Ruby


#endif // DECLARATIONBUILDER_H
