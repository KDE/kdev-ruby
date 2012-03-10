/* This file is part of KDevelop
 *
 * Copyright 2010 Niko Sams <niko.sams@gmail.com>
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright (C) 2011 Miquel Sabaté <mikisabate@gmail.com>
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


#ifndef CONTEXTBUILDER_H
#define CONTEXTBUILDER_H


/*
 * TODO: This file is still under construction.
 */


#include <language/duchain/builders/abstractcontextbuilder.h>
#include <language/duchain/topducontext.h>
#include <duchain/duchainexport.h>
#include <parser/rubyast.h>
#include <parser/rubyastvisitor.h>


namespace Ruby
{

class EditorIntegrator;
typedef KDevelop::AbstractContextBuilder<RubyAst, NameAst> ContextBuilderBase;

class KDEVRUBYDUCHAIN_EXPORT ContextBuilder: public ContextBuilderBase, public RubyAstVisitor
{
public:
    ContextBuilder();
    virtual ~ContextBuilder();

    void setEditor(EditorIntegrator *editor);
    virtual KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, RubyAst * node,
        KDevelop::ReferencedTopDUContext updateContext = KDevelop::ReferencedTopDUContext());
    
    bool hasUnresolvedImports() const;

protected:
    EditorIntegrator * editor() const;

    virtual KDevelop::DUContext* newContext(const KDevelop::RangeInRevision &range);
    virtual KDevelop::TopDUContext* newTopContext(const KDevelop::RangeInRevision &range,
                                                  KDevelop::ParsingEnvironmentFile *file = 0);

    virtual void startVisiting(RubyAst *node);
    virtual void setContextOnNode(RubyAst *node, KDevelop::DUContext *ctx);
    virtual KDevelop::DUContext* contextFromNode(RubyAst *node);

    virtual KDevelop::RangeInRevision editorFindRange(RubyAst *fromRange, RubyAst *toRange);
    KDevelop::CursorInRevision startPos(RubyAst *node);

    virtual KDevelop::QualifiedIdentifier identifierForNode(NameAst *name);

    /* Re-implementing from RubyAstVistor */
    virtual void visitClassStatement(RubyAst *node);
    virtual void visitModuleStatement(RubyAst *node);
    virtual void visitMethodStatement(RubyAst *node);

    void openContextForClassDefinition(RubyAst *node);

    bool m_mapAst; // AbstractUseBuilder requires this :S
    bool m_reportErrors;
    bool m_hasUnresolvedImports;
    EditorIntegrator *m_editor;
    KDevelop::ReferencedTopDUContext m_topContext;
    KDevelop::TopDUContextPointer m_builtinsContext;

private:
    RangeInRevision rangeForMethodArguments(RubyAst *node);
    void addImportedContexts();

private:
    QList<KDevelop::DUContext *> m_importedParentContexts;
};

} // End of namespace Ruby


#endif // CONTEXTBUILDER_H

