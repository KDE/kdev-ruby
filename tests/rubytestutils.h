/*****************************************************************************
 * Copyright (c) 2007  Michaël Larouche <larouche@kde.org>                   *
 *                                                                           *
 * Permission is hereby granted, free of charge, to any person obtaining     *
 * a copy of this software and associated documentation files (the           *
 * "Software"), to deal in the Software without restriction, including       *
 * without limitation the rights to use, copy, modify, merge, publish,       *
 * distribute, sublicense, and/or sell copies of the Software, and to        *
 * permit persons to whom the Software is furnished to do so, subject to     *
 * the following conditions:                                                 *
 *                                                                           *
 * The above copyright notice and this permission notice shall be            *
 * included in all copies or substantial portions of the Software.           *
 *                                                                           *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,           *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF        *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                     *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE    *
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION    *
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION     *
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.           *
 *****************************************************************************/
#ifndef RUBYTESTUTILS_H
#define RUBYTESTUTILS_H

// Qt includes
#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QFile>

// Ruby parser
#include <ruby_parser.h>

using namespace ruby;

/**
 * @brief Read a test ruby file from tests dir
 *
 * This function use the RUBY_TESTDIR define to load a test file
 * from tests subdir. You just need to pass the filename and not
 * the full path of the test.
 *
 * @param baseFile Test filename (ex: ruby_test.rb)
 * @return The file contents as a QByteArray
 */
inline static QByteArray RubyTest_readFile(const QString &baseFile)
{
    QFile file( QString(RUBY_TESTDIR) + baseFile );
    if( file.open( QIODevice::ReadOnly ) )
    {
        QByteArray contents = file.readAll();
        file.close();

        return contents;
    }

    return QByteArray();
}

/**
 * @brief Parse a file
 *
 * Utility function to setup the parser and return true
 * if the parser parsed the file correctly.
 *
 * @param contents The file contents
 * @return true if the parsing went well
 */
inline static bool RubyTest_parseFile(const QByteArray &contents)
{
    // Setup parser
    parser::token_stream_type token_stream;
    parser::memory_pool_type memory_pool;

    parser ruby_parser;
    ruby_parser.set_token_stream(&token_stream);
    ruby_parser.set_memory_pool(&memory_pool);

    // Create the tokens
    ruby_parser.tokenize( const_cast<char*>( contents.data() ));

    // Start the parsing process
    program_ast *ast = 0;
    bool matched = ruby_parser.parse_program(&ast);

    return matched;
}
#endif

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
