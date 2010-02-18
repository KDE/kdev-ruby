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
#include <language/duchain/declaration.h>

namespace Ruby {

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
    ClassAST *lastClass = 0;
    FunctionAST *lastFunction = 0;
    QString lastMethodIndentation;
    KDevelop::Declaration::AccessPolicy lastAccess = KDevelop::Declaration::Public;
    bool skipMultilineComment = false;

    //for now just parse classes and methods
    /*
    also todo:
    - base classes
    - method access control
    - functions vs methods (check)
    */
    QStringList lines = contents.split("\n");
    int lineNo = 0;
    foreach (const QString &rawline, lines)
    {
        QString line = rawline; //.trimmed();

        if (skipMultilineComment) {
            if (end_commentre.indexIn(line) != -1)
                skipMultilineComment = false;
            else
                continue;
        }

        if (classre.indexIn(line) != -1) {
            QString className = classre.cap(3);
            lastClass = programAST->findClass(className);
            if (!lastClass) {
                lastClass = new ClassAST;
                NameAST *name = new NameAST;
                name->name = className;
                lastClass->name = name;
                lastClass->start = KDevelop::SimpleCursor(lineNo, 0);
                lastClass->end = KDevelop::SimpleCursor(lineNo, rawline.length());
                programAST->classes << lastClass;
            }

            QString parent = classre.cap(5);
            if (!parent.isEmpty()) {
                lastClass->baseClass = parent;
            }

            lastAccess = KDevelop::Declaration::Public;

        } else if (methodre.indexIn(line) != -1) {
            QString functionName = methodre.cap(4);

            FunctionAST *fun = 0;

            if ( lastClass != 0 && lastClass->findFunction(functionName) ) {
                fun = lastClass->findFunction(functionName);
            } else {
                fun = new FunctionAST;
                NameAST *name = new NameAST;
                name->name = functionName;
                name->start = KDevelop::SimpleCursor(lineNo, methodre.pos(4));
                name->end = KDevelop::SimpleCursor(lineNo, methodre.pos(4) + functionName.length() - 1);
                fun->name = name;
                fun->start = KDevelop::SimpleCursor(lineNo, 0);
            }

            if (functionName == "initialize") {
                // Ruby constructors are alway private
                fun->access = KDevelop::Declaration::Private;
            } else {
                fun->access = lastAccess;
            }

            if (methodre.cap(2) != "") {
                // A ruby class/singleton method of the form <classname>.<methodname>
                fun->isStatic = true;
            }

            lastMethodIndentation = methodre.cap(1);
            lastFunction = fun;

            if (lastClass != 0) {
                fun->isMember = true;
                lastClass->functions << fun;
            } else {
                fun->isMember = false;
                programAST->functions << fun;
            }
        } else if (endre.indexIn(line) != -1 && lastFunction != 0 && endre.cap(1) == lastMethodIndentation ) {
            if (lastFunction->end.line == 0) {
                //hack to set end position of the previous method to the line
                //where its corresponding "end" is found
                //there's an assumption that method's "def" statement will have the same
                //indentation level as method's "end"
                lastFunction->end = KDevelop::SimpleCursor(lineNo, endre.matchedLength());
            }
        } else if (begin_commentre.indexIn(line) != -1) {
            skipMultilineComment = true;
        }

        lineNo += 1;
    }
    return programAST;
}

}
