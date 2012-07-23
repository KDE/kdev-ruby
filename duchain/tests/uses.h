/*
 * This file is part of KDevelop
 * Copyright 2012  Miquel Sabaté <mikisabate@gmail.com>
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


#ifndef RUBY_USES_H
#define RUBY_USES_H


#include <duchain/tests/duchaintestbase.h>


namespace Ruby
{

/// Test the UseBuilder class from the DUChain.
class TestUseBuilder : public DUChainTestBase
{
    Q_OBJECT

public:
    TestUseBuilder();

protected:
    /// Re-implemented from DUChainTestBase.
    virtual KDevelop::TopDUContext * parse(const QByteArray &code, const QString &id);

private:
    /// Compare the uses of the given declaration @p dec with the given @p range.
    void compareUses(KDevelop::Declaration *dec, const KDevelop::RangeInRevision &range);

    /**
     * Let's compare the uses of the given declaration @p dec with the given
     * @p ranges that we expect these uses are enclosed to.
     */
    void compareUses(KDevelop::Declaration *dec, QList<KDevelop::RangeInRevision> ranges);

    /**
     * Get a builtin method declaration.
     *
     * @param name The name of the method in a format such as "String#bytesize"
     * @param top The TopDUContext that we've got from parsing.
     * @param ctx Optional DUContext. Set this when you don't want a child
     * context from the @p top to be used.
     * @returns the Declaration of the required builtin method.
     */
    KDevelop::Declaration * getBuiltinDeclaration(const QString &name, KDevelop::TopDUContext *top,
                                                  KDevelop::DUContext *ctx = NULL);

private slots:
    // Basic stuff
    void stringInterpolation();
    void alias();
    void assignment();
    void checkSubClassing();
    void checkMethodArgumentsContext();
    void instanceVariable();
    void classVariable();

    // Method calls
    void builtinUses();
    void chained();
};

}


#endif /* RUBY_USES_H */
