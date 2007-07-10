// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef ruby_DEFAULT_VISITOR_H_INCLUDED
#define ruby_DEFAULT_VISITOR_H_INCLUDED

#include "ruby_visitor.h"

namespace ruby
  {

  class default_visitor:  public visitor
    {

    public:
      virtual void visit_additiveExpression(additiveExpression_ast *node);
      virtual void visit_aliasParameter(aliasParameter_ast *node);
      virtual void visit_andExpression(andExpression_ast *node);
      virtual void visit_andorExpression(andorExpression_ast *node);
      virtual void visit_arrayAccess(arrayAccess_ast *node);
      virtual void visit_arrayExpression(arrayExpression_ast *node);
      virtual void visit_arrayReferenceArgument(arrayReferenceArgument_ast *node);
      virtual void visit_assignmentExpression(assignmentExpression_ast *node);
      virtual void visit_blockContent(blockContent_ast *node);
      virtual void visit_blockMethodDefinitionArgument(blockMethodDefinitionArgument_ast *node);
      virtual void visit_blockMethodInvocationArgument(blockMethodInvocationArgument_ast *node);
      virtual void visit_block_var(block_var_ast *node);
      virtual void visit_block_vars(block_vars_ast *node);
      virtual void visit_bodyStatement(bodyStatement_ast *node);
      virtual void visit_caseExpression(caseExpression_ast *node);
      virtual void visit_classDefinition(classDefinition_ast *node);
      virtual void visit_className(className_ast *node);
      virtual void visit_codeBlock(codeBlock_ast *node);
      virtual void visit_colonAccess(colonAccess_ast *node);
      virtual void visit_command(command_ast *node);
      virtual void visit_commandOutput(commandOutput_ast *node);
      virtual void visit_compoundStatement(compoundStatement_ast *node);
      virtual void visit_doOrTerminalOrColon(doOrTerminalOrColon_ast *node);
      virtual void visit_dotAccess(dotAccess_ast *node);
      virtual void visit_elementReference(elementReference_ast *node);
      virtual void visit_equalityExpression(equalityExpression_ast *node);
      virtual void visit_exceptionHandlingExpression(exceptionHandlingExpression_ast *node);
      virtual void visit_exceptionList(exceptionList_ast *node);
      virtual void visit_expression(expression_ast *node);
      virtual void visit_expressionSubstitution(expressionSubstitution_ast *node);
      virtual void visit_forExpression(forExpression_ast *node);
      virtual void visit_hashExpression(hashExpression_ast *node);
      virtual void visit_ifExpression(ifExpression_ast *node);
      virtual void visit_keyValuePair(keyValuePair_ast *node);
      virtual void visit_keyword(keyword_ast *node);
      virtual void visit_keywordAlias(keywordAlias_ast *node);
      virtual void visit_keywordAnd(keywordAnd_ast *node);
      virtual void visit_keywordAsMethodName(keywordAsMethodName_ast *node);
      virtual void visit_keywordBeginUpcase(keywordBeginUpcase_ast *node);
      virtual void visit_keywordBreak(keywordBreak_ast *node);
      virtual void visit_keywordClass(keywordClass_ast *node);
      virtual void visit_keywordDef(keywordDef_ast *node);
      virtual void visit_keywordDefined(keywordDefined_ast *node);
      virtual void visit_keywordDo(keywordDo_ast *node);
      virtual void visit_keywordEndUpcase(keywordEndUpcase_ast *node);
      virtual void visit_keywordFor(keywordFor_ast *node);
      virtual void visit_keywordIn(keywordIn_ast *node);
      virtual void visit_keywordModule(keywordModule_ast *node);
      virtual void visit_keywordNot(keywordNot_ast *node);
      virtual void visit_keywordOr(keywordOr_ast *node);
      virtual void visit_keywordUndef(keywordUndef_ast *node);
      virtual void visit_keywordUntil(keywordUntil_ast *node);
      virtual void visit_keywordWhen(keywordWhen_ast *node);
      virtual void visit_keywordWhile(keywordWhile_ast *node);
      virtual void visit_literal(literal_ast *node);
      virtual void visit_logicalAndExpression(logicalAndExpression_ast *node);
      virtual void visit_logicalOrExpression(logicalOrExpression_ast *node);
      virtual void visit_methodCall(methodCall_ast *node);
      virtual void visit_methodDefinition(methodDefinition_ast *node);
      virtual void visit_methodDefinitionArgument(methodDefinitionArgument_ast *node);
      virtual void visit_methodDefinitionArgumentWithoutParen(methodDefinitionArgumentWithoutParen_ast *node);
      virtual void visit_methodInvocationArgumentWithParen(methodInvocationArgumentWithParen_ast *node);
      virtual void visit_methodInvocationArgumentWithoutParen(methodInvocationArgumentWithoutParen_ast *node);
      virtual void visit_methodName(methodName_ast *node);
      virtual void visit_methodNameSupplement(methodNameSupplement_ast *node);
      virtual void visit_mlhs_item(mlhs_item_ast *node);
      virtual void visit_moduleDefinition(moduleDefinition_ast *node);
      virtual void visit_moduleName(moduleName_ast *node);
      virtual void visit_mrhs(mrhs_ast *node);
      virtual void visit_multiplicativeExpression(multiplicativeExpression_ast *node);
      virtual void visit_normalMethodDefinitionArgument(normalMethodDefinitionArgument_ast *node);
      virtual void visit_normalMethodInvocationArgument(normalMethodInvocationArgument_ast *node);
      virtual void visit_notExpression(notExpression_ast *node);
      virtual void visit_numeric(numeric_ast *node);
      virtual void visit_operatorAsMethodname(operatorAsMethodname_ast *node);
      virtual void visit_operatorAssign(operatorAssign_ast *node);
      virtual void visit_operatorBAnd(operatorBAnd_ast *node);
      virtual void visit_operatorBAndAssign(operatorBAndAssign_ast *node);
      virtual void visit_operatorBNot(operatorBNot_ast *node);
      virtual void visit_operatorBOr(operatorBOr_ast *node);
      virtual void visit_operatorBXor(operatorBXor_ast *node);
      virtual void visit_operatorBXorAssign(operatorBXorAssign_ast *node);
      virtual void visit_operatorBorAssign(operatorBorAssign_ast *node);
      virtual void visit_operatorCaseEqual(operatorCaseEqual_ast *node);
      virtual void visit_operatorColon(operatorColon_ast *node);
      virtual void visit_operatorCompare(operatorCompare_ast *node);
      virtual void visit_operatorDiv(operatorDiv_ast *node);
      virtual void visit_operatorDivAssign(operatorDivAssign_ast *node);
      virtual void visit_operatorEqual(operatorEqual_ast *node);
      virtual void visit_operatorExclusiveRange(operatorExclusiveRange_ast *node);
      virtual void visit_operatorGreaterOrEqual(operatorGreaterOrEqual_ast *node);
      virtual void visit_operatorGreaterThan(operatorGreaterThan_ast *node);
      virtual void visit_operatorInclusiveRange(operatorInclusiveRange_ast *node);
      virtual void visit_operatorLeftShift(operatorLeftShift_ast *node);
      virtual void visit_operatorLeftShiftAssign(operatorLeftShiftAssign_ast *node);
      virtual void visit_operatorLessOrEqual(operatorLessOrEqual_ast *node);
      virtual void visit_operatorLessThan(operatorLessThan_ast *node);
      virtual void visit_operatorLogicalAnd(operatorLogicalAnd_ast *node);
      virtual void visit_operatorLogicalAndAssign(operatorLogicalAndAssign_ast *node);
      virtual void visit_operatorLogicalOr(operatorLogicalOr_ast *node);
      virtual void visit_operatorLogicalOrAssign(operatorLogicalOrAssign_ast *node);
      virtual void visit_operatorMatch(operatorMatch_ast *node);
      virtual void visit_operatorMinus(operatorMinus_ast *node);
      virtual void visit_operatorMinusAssign(operatorMinusAssign_ast *node);
      virtual void visit_operatorMod(operatorMod_ast *node);
      virtual void visit_operatorModAssign(operatorModAssign_ast *node);
      virtual void visit_operatorNot(operatorNot_ast *node);
      virtual void visit_operatorNotEqual(operatorNotEqual_ast *node);
      virtual void visit_operatorNotMatch(operatorNotMatch_ast *node);
      virtual void visit_operatorPlus(operatorPlus_ast *node);
      virtual void visit_operatorPlusAssign(operatorPlusAssign_ast *node);
      virtual void visit_operatorPower(operatorPower_ast *node);
      virtual void visit_operatorPowerAssign(operatorPowerAssign_ast *node);
      virtual void visit_operatorQuestion(operatorQuestion_ast *node);
      virtual void visit_operatorRightShift(operatorRightShift_ast *node);
      virtual void visit_operatorRightShiftAssign(operatorRightShiftAssign_ast *node);
      virtual void visit_operatorStar(operatorStar_ast *node);
      virtual void visit_operatorStarAssign(operatorStarAssign_ast *node);
      virtual void visit_operatorUnaryMinus(operatorUnaryMinus_ast *node);
      virtual void visit_operatorUnaryPlus(operatorUnaryPlus_ast *node);
      virtual void visit_orExpression(orExpression_ast *node);
      virtual void visit_parallelAssignmentLeftOver(parallelAssignmentLeftOver_ast *node);
      virtual void visit_powerExpression(powerExpression_ast *node);
      virtual void visit_predefinedValue(predefinedValue_ast *node);
      virtual void visit_primaryExpression(primaryExpression_ast *node);
      virtual void visit_program(program_ast *node);
      virtual void visit_rangeExpression(rangeExpression_ast *node);
      virtual void visit_regex(regex_ast *node);
      virtual void visit_relationalExpression(relationalExpression_ast *node);
      virtual void visit_restMethodDefinitionArgument(restMethodDefinitionArgument_ast *node);
      virtual void visit_restMethodInvocationArgument(restMethodInvocationArgument_ast *node);
      virtual void visit_shiftExpression(shiftExpression_ast *node);
      virtual void visit_statement(statement_ast *node);
      virtual void visit_statementWithoutModifier(statementWithoutModifier_ast *node);
      virtual void visit_statements(statements_ast *node);
      virtual void visit_string(string_ast *node);
      virtual void visit_symbol(symbol_ast *node);
      virtual void visit_terminal(terminal_ast *node);
      virtual void visit_ternaryIfThenElseExpression(ternaryIfThenElseExpression_ast *node);
      virtual void visit_thenOrTerminalOrColon(thenOrTerminalOrColon_ast *node);
      virtual void visit_unaryExpression(unaryExpression_ast *node);
      virtual void visit_undefParameter(undefParameter_ast *node);
      virtual void visit_unlessExpression(unlessExpression_ast *node);
      virtual void visit_untilExpression(untilExpression_ast *node);
      virtual void visit_variable(variable_ast *node);
      virtual void visit_whileExpression(whileExpression_ast *node);
    };

} // end of namespace ruby

#endif


