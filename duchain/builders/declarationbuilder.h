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
    DeclarationBuilder();
    DeclarationBuilder(EditorIntegrator *editor);
    virtual ~DeclarationBuilder();

protected:
    virtual void closeDeclaration();
    virtual void startVisiting(RubyAst *node);
    virtual void visitClassStatement(RubyAst *node);
    virtual void visitSingletonClass(RubyAst *node);
    virtual void visitModuleStatement(RubyAst *node);
    virtual void visitMethodStatement(RubyAst *node);
    virtual void visitParameter(RubyAst *node);
    virtual void visitVariable(RubyAst *node);
    virtual void visitBlockVariables(RubyAst *node);
    virtual void visitReturnStatement(RubyAst *node);
    virtual void visitAssignmentStatement(RubyAst *node);
    virtual void visitAliasStatement(RubyAst *node);
    virtual void visitMethodCall(RubyAst *node);
    virtual void visitInclude(RubyAst *node);
    virtual void visitExtend(RubyAst *node);
    virtual void visitLambda(RubyAst *node);
    virtual void visitForStatement(RubyAst *node);
    virtual void visitAccessSpecifier(short int policy);
    virtual void visitYieldStatement(RubyAst *node);

private:
    void declareVariable(const KDevelop::QualifiedIdentifier& id, KDevelop::AbstractType::Ptr type, RubyAst *node);
    void aliasMethodDeclaration(const KDevelop::QualifiedIdentifier &id,
                                const KDevelop::RangeInRevision &range,
                                KDevelop::Declaration *decl); // TODO: change to MethodDeclaration
    KDevelop::RangeInRevision getNameRange(const RubyAst *node);
    Declaration *lastClassModule; // TODO: pair it with insideClassModule and give it a proper name. TODO: by default point to the Kernel module
    Declaration *m_lastMethodCall;
    bool insideClassModule; // TODO: maybe it can be removed because of m_classDeclarations ?

    template<typename T> T * reopenDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range);

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
     * Register a module mixin.
     * @param module The include/extend AST.
     * @param include Set to true if this is an include, false otherwise.
     */
    void registerModuleMixin(RubyAst *module, bool include);

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
     * @param args The arguments of the method that is being called.
     */
    void visitMethodCallArgs(RubyAst *mc, const QVector<Declaration *> &args);

private:
    EditorIntegrator *m_editor;
    QStack<KDevelop::Declaration::AccessPolicy> m_accessPolicy;
    QStack<DeclarationPointer> m_classDeclarations; // TODO: there's probably a more fancy way to achieve this ...
    bool m_injected;
    bool m_instance;
};

} // End of namespace Ruby


#endif // DECLARATIONBUILDER_H
