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


#ifndef RUBY_TESTDUCHAIN_H
#define RUBY_TESTDUCHAIN_H


#include <duchain/tests/duchaintestbase.h>


namespace Ruby
{

/// The DUChain test suite.
class TestDUChain : public DUChainTestBase
{
    Q_OBJECT

public:
    TestDUChain();

protected:
    /// Re-implemented from DUChainTestBase.
    virtual KDevelop::TopDUContext * parse(const QByteArray &code, const QString &id);

private slots:
    // Builtin classes
    void fixnum();
    void range();
    void stringAndRegexp();
    void booleanAndNilAndSelf();
    void lineFileEncoding();
    void symbol();

    // Simple Statements
    void alias();

    // Assignments
    void multipleAssignment1();
    void multipleAssignment2();
    void multipleAssignmentLeft();
    void multipleAssignmentRight1();
    void multipleAssignmentRight2();
    void multipleAssignmentStar();
    void multipleAssignmentNamedStar();
    void unpackArray();
    void aliasedAssignment();

    // Variable Length Container
    void assignFromArrayItem1();
    void assignFromArrayItem2();
    void assignFromHashItem();
    void assignToArrayItem();

    // Declarations
    void methodDeclaration();
};

} // End of namespace Ruby


#endif /* RUBY_TESTDUCHAIN_H */
