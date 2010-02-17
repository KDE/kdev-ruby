/*
* This file is part of KDevelop
*
* Copyright 2006 Hamish Rodda <rodda@kde.org>
* Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
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
#include "editorintegrator.h"

#include <ktexteditor/document.h>
#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include <language/editor/documentrange.h>
#include <language/editor/documentrangeobject.h>

#include "parser/rubyast.h"

using namespace KTextEditor;
using namespace Ruby;

EditorIntegrator::EditorIntegrator()
{
}

KDevelop::SimpleCursor EditorIntegrator::findPosition(AST *node, Edge edge) const
{
    if (edge == BackEdge) {
        // Apparently KTE expects a range to go until _after_ the last character that should be included
        // however the parser calculates endCol as the index _before_ the last included character, so adjust here
        KDevelop::SimpleCursor cursor = node->end;
        cursor.column += 1;
        return cursor;
    } else {
        return node->start;
    }
}

KDevelop::SimpleRange EditorIntegrator::findRange(AST* from, AST* to)
{
    return KDevelop::SimpleRange(findPosition(from, FrontEdge), findPosition(to, BackEdge));
}

KDevelop::SimpleRange EditorIntegrator::findRange(AST* ast)
{
    return KDevelop::SimpleRange(findPosition(ast, FrontEdge), findPosition(ast, BackEdge));
}
