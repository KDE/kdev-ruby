/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef RUBY_TESTDUCHAIN_H
#define RUBY_TESTDUCHAIN_H


#include <duchain/tests/duchaintestbase.h>
#include <language/duchain/types/typepointer.h>


namespace KDevelop {
    class UnsureType;
}

namespace ruby {

/**
 * @class TestDUChain
 * The DUChain test suite.
 */
class TestDUChain : public DUChainTestBase
{
    Q_OBJECT

public:
    /// Constructor.
    TestDUChain();

protected:
    /// Re-implemented from DUChainTestBase.
    KDevelop::TopDUContext * parse(const QByteArray &code, const QString &id) override;

private:
    /**
     * Given an unsure @p type, compare its possible types with the given
     * @p list of class identifiers.
     * @note that the order of the @p list items is important.
     */
    void testUnsureTypes(KDevelop::TypePtr<KDevelop::UnsureType> type,
                         const QStringList &list);

    /**
     * Given a top context @p ctx, get all the encountered problems and
     * compare their descriptions to the given @p list of problem descriptions.
     * @note that the order of the @p list items is important.
     */
    void testProblems(KDevelop::TopDUContext *ctx, const QStringList &list);

private slots:
    // Builtin classes
    void numeric();
    void range();
    void stringAndRegexp();
    void booleanAndNil();
    void lineFileEncoding();
    void symbol();
    void lambda();
    void self();

    // Statements
    void alias();
    void aliasGlobal1();
    void aliasGlobal2();
    void yield1();
    void yield2();
    void yield3();
    void ifStatement();
    void caseStatement();
    void forStatement();
    void hereDoc();
    void exceptions();
    void method();
    void classStatement();

    // Assignments
    void simpleUnsure();
    void unsureHash();
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
    void withMethodCallAndBlock();

    // ClassType
    void assignFromArrayItem1();
    void assignFromArrayItem2();
    void assignFromHashItem();
    void assignToArrayItem();
    void arrayInstanceVariable();

    // Declarations
    void checkVariableKind();
    void instanceClassMethodDeclaration();
    void reopenMethodDeclaration();
    void singletonMethods();
    void singletonClass1();
    void singletonClass2();
    void singletonClass3();
    void singletonMethodVisibility();
    void accessPolicyMethodInClass();
    void accessPolicyMethodInModule();
    void accessPolicyOnBlock();
    void nestedAccessPolicy();
    void checkSubClassing1();
    void checkSubClassing2();
    void checkSubClassingErrors();
    void errorOnInvalidRedeclaration1();
    void errorOnInvalidRedeclaration2();
    void instanceVariable();
    void classVariable();
    void classModulesScopes();
    void globals1();
    void globals2();

    // Returning values
    void multipleReturns();
    void implicitReturn();
    void mixedExplicitAndImplicitReturn();
    void nilReturn();
    void instanceClassMethodsReturn();

    // Methods
    void callingToInstanceMethod();
    void chainedCalls1();
    void chainedCalls2();
    void chainedCalls3();
    void super();
    void guessArgumentsType1();
    void guessArgumentsType2();
    void guessArgumentsType3();
    void showErrorOnTooFewArguments();
    void showErrorOnTooManyArguments();
    void hashArgument();
    void setUnsureArgument();
    void conflictOnSpecialMethods();

    // Include & Extend
    void include1();
    void include2();
    void extend();
    void problemOnInvalidMixin();
    void rspecIncludeIsNormalFunction();
};

}


#endif /* RUBY_TESTDUCHAIN_H */
