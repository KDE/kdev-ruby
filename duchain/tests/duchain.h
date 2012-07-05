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


namespace KDevelop {
    class UnsureType;
}

namespace Ruby
{

/// The DUChain test suite.
class TestDUChain : public DUChainTestBase
{
    Q_OBJECT

public:
    /// Constructor.
    TestDUChain();

protected:
    /// Re-implemented from DUChainTestBase.
    virtual KDevelop::TopDUContext * parse(const QByteArray &code, const QString &id);

private:
    /**
     * Given an unsure @p type, compare its possible types with the given
     * @p list of class identifiers.
     * @note that the order of the @p list items is important.
     */
    void testUnsureTypes(TypePtr<KDevelop::UnsureType> type, QList<QString> list);

    /**
     * Given a top context @p ctx, get all the encountered problems and
     * compare their descriptions to the given @p list of problem descriptions.
     * @note that the order of the @p list items is important.
     */
    void testProblems(KDevelop::TopDUContext *ctx, const QList<QString> &list);

private slots:
    // Builtin classes
    void numeric();
    void range();
    void stringAndRegexp();
    void booleanAndNilAndSelf();
    void lineFileEncoding();
    void symbol();
    void lambda();

    // Simple Statements
    void alias();
    void aliasGlobal1();
    void aliasGlobal2();
    void yield1();
    void yield2();

    // Compound Statements
    void ifStatement();
    void caseStatement();

    // Assignments
    void multipleAssignment1();
    void multipleAssignment2();
    void multipleAssignmentLeft();
    void multipleAssignmentRight1();
    void multipleAssignmentRight2();
    void multipleAssignmentStar();
    void multipleAssignmentNamedStar();
    void starAtTheBeginning();
    void starAtTheEnd();
    void emptyStar();
    void unpackArray1();
    void unpackArray2();
    void unpackArray3();
    void aliasedAssignment();

    // ClassType
    void assignFromArrayItem1();
    void assignFromArrayItem2();
    void assignFromHashItem();
    void assignToArrayItem();

    // Declarations
    void checkVariableKind();
    void instanceClassMethodDeclaration();
    void accessPolicyMethodInClass();
    void accessPolicyMethodInModule();
    void checkSubClassing();
    void checkDeclarationsOnSubClass();
    void errorOnInvalidRedeclaration();

    // Returning values
    void multipleReturns();
    void implicitReturn();
    void mixedExplicitAndImplicitReturn();

    // Methods
    void callingToInstanceMethod();
    void optionalMethodArguments();
    void specialMethodArguments();
    void guessMethodArgumentTypes1();
    void guessMethodArgumentTypes2();
    void setUnsureArgument();

    // Include & Extend
    void include1();
    void include2();
    void extend();
};

} // End of namespace Ruby


#endif /* RUBY_TESTDUCHAIN_H */
