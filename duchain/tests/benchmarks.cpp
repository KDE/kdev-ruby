/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


// Qt + KDE
#include <QtTest/QtTest>
#include <KDebug>

// Ruby
#include <duchain/helpers.h>
#include <duchain/editorintegrator.h>
#include <duchain/builders/declarationbuilder.h>
#include <duchain/tests/benchmarks.h>
#include <parser/rubyparser.h>


QTEST_MAIN(Ruby::Benchmarks)

namespace Ruby
{

Benchmarks::Benchmarks()
{
    /* There's nothing to do here */
}

const QByteArray Benchmarks::getBuiltinsFile()
{
    const QString fileName = internalBuiltinsFile().str();
    QFile file(fileName);
    bool opened = file.open(QIODevice::ReadOnly);
    Q_ASSERT(opened);
    const QByteArray &txt = file.readAll();
    file.close();
    return txt;
}

void Benchmarks::parser()
{
    const QByteArray &contents = getBuiltinsFile();

    QBENCHMARK {
        RubyParser parser;
        parser.setContents(contents);
        parser.parse();
    }
}

void Benchmarks::declarationBuilder()
{
    const QByteArray &contents = getBuiltinsFile();
    RubyParser *parser = new RubyParser();
    parser->setContents(contents);
    parser->setCurrentDocument(internalBuiltinsFile());
    RubyAst * ast = parser->parse();
    EditorIntegrator editor;
    editor.setParseSession(parser);

    QBENCHMARK {
        DeclarationBuilder builder(&editor);
        ReferencedTopDUContext top = builder.build(internalBuiltinsFile(), ast);
    }
}

} // End of namespace Ruby

