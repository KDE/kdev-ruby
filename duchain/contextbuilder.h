/***************************************************************************
 *   This file is part of KDevelop                                         *
 *   Copyright 2010 Niko Sams <niko.sams@gmail.com>                        *
 *   Copyright 2010 Alexander Dymo <adymo@kdevelop.org>                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef CONTEXTBUILDER_H
#define CONTEXTBUILDER_H

#include <language/duchain/builders/abstractcontextbuilder.h>

namespace ruby
{
class AST;
class ProgramAST;
class NameAST;
class ClassAST;
class EditorIntegrator;
class ParseSession;

typedef KDevelop::AbstractContextBuilder<AST, NameAST> ContextBuilderBase;

class ContextBuilder: public ContextBuilderBase {
public:
    ContextBuilder();
    virtual ~ContextBuilder();

    void setEditor(EditorIntegrator* editor);
    virtual KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, AST* node,
        KDevelop::ReferencedTopDUContext updateContext = KDevelop::ReferencedTopDUContext(), bool useSmart = true);

protected:
    EditorIntegrator* editor() const;

    virtual KDevelop::TopDUContext* newTopContext(const KDevelop::SimpleRange& range, KDevelop::ParsingEnvironmentFile* file = 0);

    virtual void startVisiting(AST* node);
    virtual void setContextOnNode(AST* node, KDevelop::DUContext* ctx);
    virtual KDevelop::DUContext* contextFromNode(AST* node);

    virtual KTextEditor::Range editorFindRange(AST* fromRange, AST* toRange);
    /// Find Cursor for start of a node, useful to limit findLocalDeclarations() searches.
    KDevelop::SimpleCursor startPos(AST* node);

    virtual KDevelop::QualifiedIdentifier identifierForNode(NameAST* id);

    virtual void visitProgram(ProgramAST* ast);
    virtual void visitClass(ClassAST* ast);

    bool m_reportErrors;
};

}

#endif
