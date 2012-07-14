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
    virtual KDevelop::QualifiedIdentifier identifierForNode(NameAst *node);
    virtual void closeDeclaration();
    virtual void startVisiting(RubyAst *node);
    virtual void visitClassStatement(RubyAst *node);
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
    void appendProblem(Node *node, const QString &msg);
    void appendProblem(const RangeInRevision &range, const QString &msg);
    KDevelop::RangeInRevision getNameRange(const RubyAst *node);
    ModuleDeclaration * getModuleDeclaration(const RubyAst *module); // NOTE: read comment at the implementation of this method
    Declaration *lastClassModule; // TODO: pair it with insideClassModule and give it a proper name. TODO: by default point to the Kernel module
    Declaration *m_lastMethodCall;
    bool insideClassModule; // TODO: maybe it can be removed because of m_classDeclarations ?

    template<typename T> T * reopenDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range);

    inline KDevelop::Declaration::AccessPolicy currentAccessPolicy()
    {
        if (m_accessPolicyStack.isEmpty())
            return KDevelop::Declaration::Public;
        else
            return m_accessPolicyStack.top();
    }

    inline void setAccessPolicy(KDevelop::Declaration::AccessPolicy policy)
    {
        m_accessPolicyStack.top() = policy;
    }

    QStack<KDevelop::Declaration::AccessPolicy> m_accessPolicyStack;

    void registerModuleMixin(ModuleDeclaration *decl, bool include);

    bool validReDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range, bool isClass = true);

    /**
     * @returns the declared methods inside the given declaration @p decl,
     * which is a class or a module.
     * @note This method already acquires a read lock for the DUChain.
     */
    QList<MethodDeclaration *> getDeclaredMethods(Declaration *decl);

    void visitMethodCallArgs(RubyAst *mc, const QVector<Declaration *> &args);

private:
    EditorIntegrator *m_editor;
    QStack<DeclarationPointer> m_classDeclarations; // TODO: there's probably a more fancy way to achieve this ...
};

} // End of namespace Ruby


#endif // DECLARATIONBUILDER_H
