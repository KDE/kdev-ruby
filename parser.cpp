/*
* This file is part of KDevelop
*
* Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
* Copyright 2006 Richard Dale <rdale@foton.es>
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
#include "parser.h"

#include <QStringList>

namespace ruby {

Parser::Parser()
{
    classre.setPattern("^\\s*(class|module)\\s+([A-Z][A-Za-z0-9_]+::)*([A-Z][A-Za-z0-9_]+)\\s*(<\\s*([A-Z][A-Za-z0-9_:]+))?$");
    methodre.setPattern("^(\\s*)def\\s+(([A-Z][A-Za-z0-9_:]+|self)\\.)?([A-Za-z0-9_]+[!?=]?|\\[\\]=?|\\*\\*||\\-|[!~+*/%&|><^]|>>|<<||<=>|<=|>=|==|===|!=|=~|!~).*$");
    accessre.setPattern("^\\s*(private|protected|public)\\s*((:([A-Za-z0-9_]+[!?=]?|\\[\\]=?|\\*\\*||\\-|[!~+*/%&|><^]|>>|<<||<=>|<=|>=|==|===|!=|=~|!~),?\\s*)*)$");
    attr_accessorre.setPattern("^\\s*(attr_accessor|attr_reader|attr_writer)\\s*((:([A-Za-z0-9_]+),?\\s*)*)$");
    symbolre.setPattern(":([^,]+),?");
    line_contre.setPattern(",\\s*$");
    slot_signalre.setPattern("^\\s*(slots|signals|k_dcop|k_dcop_signals)\\s*(('[^)]+\\)',?\\s*)*)$");
    memberre.setPattern("'([A-Za-z0-9_ &*]+\\s)?([A-Za-z0-9_]+)\\([^)]*\\)',?");
    begin_commentre.setPattern("^*=begin");
    end_commentre.setPattern("^*=end");
    variablere.setPattern("(@@?[A-Za-z0-9_]+)\\s*=\\s*((?:([A-Za-z0-9_:.]+)\\.new)|[\\[\"'%:/\\?\\{]|%r|<<|true|false|^\\?|0[0-7]+|[-+]?0b[01]+|[-+]?0x[1-9a-fA-F]+|[-+]?[0-9_\\.e]+|nil)?");
    endre.setPattern("^(\\s*)end\\s*$");

}

ProgramAST* Parser::parse(const QString& contents)
{
    ProgramAST *programAST = new ProgramAST;

    //for now just parse classes
    QStringList lines = contents.split("\n");
    int i = 0;
    foreach (const QString &rawline, lines)
    {
        QString line = rawline.trimmed();

        if (classre.indexIn(line) != -1) {
            ClassAST *klass = new ClassAST;
            NameAST *name = new NameAST;
            name->name = classre.cap(3);
            klass->name = name;
            klass->start = KDevelop::SimpleCursor(i, 0);
            klass->end = KDevelop::SimpleCursor(i, rawline.length());
            programAST->classes << klass;
        }

        i+=1;
    }
    return programAST;
}

}
