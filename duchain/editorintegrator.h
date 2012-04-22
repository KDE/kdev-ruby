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


#ifndef RUBYEDITORINTEGRATOR_H
#define RUBYEDITORINTEGRATOR_H


#include <language/duchain/indexedstring.h>
#include <language/editor/rangeinrevision.h>
#include <duchain/duchainexport.h>
#include <parser/node.h>
#include <parser/rubyparser.h>


namespace Ruby
{


/**
 * @class EditorIntegrator
 *
 * The EditorIntegrator for the Ruby plugin.
 */
class KDEVRUBYDUCHAIN_EXPORT EditorIntegrator
{
public:
    /**
     * Constructor.
     */
    EditorIntegrator();

    enum Edge { FrontEdge, BackEdge };

    /**
     * Find the position of the given node at the given edge.
     *
     * @param node the node to localize.
     * @param edge the edge this method has to look at.
     */
    KDevelop::CursorInRevision findPosition(Node * node, Edge edge = BackEdge) const;

    /**
     * Find the range between the given nodes.
     *
     * @param from the former node.
     * @param to the latter node.
     */
    KDevelop::RangeInRevision findRange(Node * from, Node * to);

    /**
     * Get the range of the given node.
     *
     * @param node the node to get its range.
     */
    KDevelop::RangeInRevision findRange(Node * node);

    /**
     * Set the parse session (parser) for this EditorIntegrator.
     *
     * @param session the given RubyParser.
     */
    void setParseSession(RubyParser *session);

    /**
     * Get the url of the document we are editing.
     *
     * @return the url of the document we are editing.
     */
    KDevelop::IndexedString url() const;

    /**
     * @return Get the parse session for this EditorIntegrator.
     */
    RubyParser *parseSession();

    /**
     * @return a QString that represents the value of the token
     * (not the node's name).
     */
    QString tokenToString(Node *node) const;

private:
    /**
     * The parse session for this EditorIntegrator.
     */
    RubyParser *m_session;
};

}


#endif // RUBYEDITORINTEGRATOR_H

