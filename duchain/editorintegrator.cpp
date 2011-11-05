/* This file is part of KDevelop
 *
 * Copyright 2006 Hamish Rodda <rodda@kde.org>
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


#include <duchain/editorintegrator.h>


using namespace KTextEditor;
using namespace Ruby;


EditorIntegrator::EditorIntegrator()
{
    /* There's nothing to do here! */
}

KDevelop::CursorInRevision EditorIntegrator::findPosition(Node *node, Edge edge) const
{
    Q_ASSERT(node);

    if (edge == BackEdge)
        return KDevelop::CursorInRevision(node->endLine - 1, node->endCol);
    else
        return KDevelop::CursorInRevision(node->startLine - 1, node->startCol);
}

KDevelop::RangeInRevision EditorIntegrator::findRange(Node *from, Node *to)
{
    KDevelop::CursorInRevision c_from = findPosition(from, FrontEdge);
    KDevelop::CursorInRevision c_to = findPosition(to, BackEdge);

    return KDevelop::RangeInRevision(c_from, c_to);
}

KDevelop::RangeInRevision EditorIntegrator::findRange(Node *node)
{
    KDevelop::CursorInRevision c_from = findPosition(node, FrontEdge);
    KDevelop::CursorInRevision c_to = findPosition(node, BackEdge);

    return KDevelop::RangeInRevision(c_from, c_to);
}

KDevelop::IndexedString EditorIntegrator::url() const
{
    return m_session->currentDocument();
}

void EditorIntegrator::setParseSession(RubyParser *session)
{
    m_session = session;
}

RubyParser* EditorIntegrator::parseSession()
{
    return m_session;
}

