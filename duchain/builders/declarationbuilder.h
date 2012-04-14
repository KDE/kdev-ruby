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


/*
 * TODO: This class is under construction.
 */


#include <language/duchain/builders/abstractdeclarationbuilder.h>
#include <duchain/builders/typebuilder.h>
#include <parser/rubyast.h>
#include <duchain/declarations/classdeclaration.h>


namespace KDevelop {
    class Declaration;
}

namespace Ruby
{
class EditorIntegrator;

typedef KDevelop::AbstractDeclarationBuilder<RubyAst, NameAst, TypeBuilder> DeclarationBuilderBase;

class KDEVRUBYDUCHAIN_EXPORT DeclarationBuilder : public DeclarationBuilderBase
{
public:
    DeclarationBuilder();
    DeclarationBuilder(EditorIntegrator *editor);
    virtual ~DeclarationBuilder();

    virtual KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, RubyAst * node,
        KDevelop::ReferencedTopDUContext updateContext = KDevelop::ReferencedTopDUContext());

protected:
    virtual KDevelop::QualifiedIdentifier identifierForNode(NameAst *node);
    virtual void closeDeclaration();
    virtual void updateCurrentType();
    virtual void startVisiting(RubyAst *node);
    virtual void visitClassStatement(RubyAst *node);
    virtual void visitModuleStatement(RubyAst *node);
    virtual void visitMethodStatement(RubyAst *node);
    virtual void visitParameter(RubyAst *node);
    virtual void visitVariable(RubyAst *node);
    virtual void visitBlockVariable(RubyAst *node);
    virtual void visitReturnStatement(RubyAst *node);
    virtual void visitAssignmentStatement(RubyAst *node);
    virtual void visitAliasStatement(RubyAst *node);

private:
    void declareVariable(KDevelop::DUContext *ctx, KDevelop::AbstractType::Ptr type,
                        const KDevelop::QualifiedIdentifier& id, RubyAst *node);
    void aliasMethodDeclaration(const KDevelop::QualifiedIdentifier &id,
                                const KDevelop::RangeInRevision &range,
                                KDevelop::Declaration *decl);
    void appendProblem(Node* node, const QString &msg);
    KDevelop::RangeInRevision getNameRange(RubyAst *node);
    KDevelop::DocumentRange getDocumentRange(Node* node);

private:
    EditorIntegrator *m_editor;
};

} // End of namespace Ruby


#endif // DECLARATIONBUILDER_H

