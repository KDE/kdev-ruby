/*
* This file is part of KDevelop
*
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
#ifndef RUBY_AST_H
#define RUBY_AST_H

#include <QList>
#include <QString>

#include <language/editor/rangeinrevision.h>                                                                          
#include <language/duchain/declaration.h>

#include "parserexport.h"

namespace Ruby {

class KDEVRUBYPARSER_EXPORT AST {
public:
    virtual ~AST() {}
    enum Kind { Program, Class, Name, Function, FunctionArgument };
    virtual Kind kind() = 0;

    KDevelop::CursorInRevision start;
    KDevelop::CursorInRevision end;
};

class KDEVRUBYPARSER_EXPORT NameAST: public AST {
public:
    virtual ~NameAST() {}
    virtual Kind kind();
    QString name;
};

class KDEVRUBYPARSER_EXPORT FunctionArgumentAST: public AST {
public:
    FunctionArgumentAST() {}
    virtual ~FunctionArgumentAST();
    virtual Kind kind();
    NameAST *name;
};

class KDEVRUBYPARSER_EXPORT FunctionAST: public AST {
public:
    FunctionAST(): isStatic(false), isMember(false) {}
    virtual ~FunctionAST();
    virtual Kind kind();

    NameAST *name;
    QList<FunctionArgumentAST*> arguments;
    bool isStatic;
    bool isMember;
    KDevelop::Declaration::AccessPolicy access;
};

class KDEVRUBYPARSER_EXPORT ClassAST: public AST {
public:
    virtual ~ClassAST();
    virtual Kind kind();

    NameAST *name;
    QList<FunctionAST*> functions;
    QString baseClass;

    FunctionAST *findFunction(const QString &name);
};

class KDEVRUBYPARSER_EXPORT ProgramAST: public AST {
public:
    virtual ~ProgramAST();
    virtual Kind kind();

    QList<ClassAST*> classes;
    QList<FunctionAST*> functions;

    ClassAST *findClass(const QString &name);
};

}

#endif
