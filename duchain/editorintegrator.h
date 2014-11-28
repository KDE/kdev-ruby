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

#ifndef RUBY_EDITOR_INTEGRATOR_H
#define RUBY_EDITOR_INTEGRATOR_H

#include <language/editor/rangeinrevision.h>
#include <serialization/indexedstring.h>

#include <duchain/duchainexport.h>

namespace ruby {

class Parser;
struct Node;

/**
 * The different positions around a Node.
 */
enum class Edge { FrontEdge, BackEdge };

/**
 * @class EditorIntegrator
 *
 * The EditorIntegrator for the Ruby plugin.
 */
class KDEVRUBYDUCHAIN_EXPORT EditorIntegrator
{
public:
    EditorIntegrator();

    /**
     * Find the position of the given node at the given edge.
     *
     * @param node the node to localize.
     * @param edge the edge this method has to look at.
     */
    const KDevelop::CursorInRevision findPosition(const Node *node,
                                                  Edge edge = Edge::BackEdge) const;

    /**
     * Find the range between the given nodes.
     *
     * @param from the former node.
     * @param to the latter node.
     */
    const KDevelop::RangeInRevision findRange(const Node *from,
                                              const Node *to) const;

    /**
     * Get the range of the given node.
     *
     * @param node the node to get its range.
     */
    const KDevelop::RangeInRevision findRange(const Node *node) const;

    /**
     * Get the url of the document we are editing.
     *
     * @return the url of the document we are editing.
     */
    const KDevelop::IndexedString & url() const;

    /**
     * Set the parse session (parser) for this EditorIntegrator.
     *
     * @param session the given RubyParser.
     */
    void setParseSession(Parser *session);

    /**
     * Implemented to make the AbstractUseBuilder happy.
     *
     * @return Get the parse session for this EditorIntegrator.
     */
    Parser * parseSession() const;

    /**
     * @return a QString that represents the value of the token
     * (not the node's name).
     */
    const QString tokenToString(const Node *node) const;

private:
    Parser *m_session;
};

}

#endif // RUBY_EDITOR_INTEGRATOR_H
