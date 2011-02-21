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
#ifndef RUBYEDITORINTEGRATOR_H
#define RUBYEDITORINTEGRATOR_H

#include <language/duchain/indexedstring.h>                                                                          
#include <language/editor/rangeinrevision.h>                                                                          
#include "duchainexport.h"

namespace Ruby
{

class AST;

class KDEVRUBYDUCHAIN_EXPORT EditorIntegrator {
public:
    EditorIntegrator();

    enum Edge {                                                                                                       
      FrontEdge,                                                                                                      
      BackEdge                                                                                                        
    };                                                                                                                
                                                                                                                      
    KDevelop::CursorInRevision findPosition(AST *node, Edge edge = BackEdge) const;

    KDevelop::RangeInRevision findRange(AST* from, AST* to);
    KDevelop::RangeInRevision findRange(AST* node, Edge edge = BackEdge);
    
    void setUrl(const KDevelop::IndexedString &url);
    KDevelop::IndexedString url() const;
    
private:
    KDevelop::IndexedString m_url;
};

}

#endif

