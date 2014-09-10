/* This file is part of KDevelop
 *
 * Copyright 2006 Hamish Rodda <rodda@kde.org>
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


#include <duchain/editorintegrator.h>
#include <parser/parser.h>


namespace Ruby
{

EditorIntegrator::EditorIntegrator()
{
    /* There's nothing to do here! */
}

const KDevelop::CursorInRevision EditorIntegrator::findPosition(const Node *node, Edge edge) const
{
    Q_ASSERT(node);

    if (edge == BackEdge) {
        return KDevelop::CursorInRevision(node->pos.end_line - 1, node->pos.end_col);
    } else {
        return KDevelop::CursorInRevision(node->pos.start_line - 1, node->pos.start_col);
    }
}

const KDevelop::RangeInRevision EditorIntegrator::findRange(const Node *from, const Node *to) const
{
    KDevelop::CursorInRevision c_from = findPosition(from, FrontEdge);
    KDevelop::CursorInRevision c_to = findPosition(to, BackEdge);

    return KDevelop::RangeInRevision(c_from, c_to);
}

const KDevelop::RangeInRevision EditorIntegrator::findRange(const Node *node) const
{
    KDevelop::CursorInRevision c_from = findPosition(node, FrontEdge);
    KDevelop::CursorInRevision c_to = findPosition(node, BackEdge);

    return KDevelop::RangeInRevision(c_from, c_to);
}

const KDevelop::IndexedString EditorIntegrator::url() const
{
    return m_session->currentDocument();
}

void EditorIntegrator::setParseSession(Parser *session)
{
    m_session = session;
}

Parser * EditorIntegrator::parseSession() const
{
    return m_session;
}

const QString EditorIntegrator::tokenToString(const Node *node) const
{
    return m_session->symbol(node);
}

} // End of namespace Ruby
