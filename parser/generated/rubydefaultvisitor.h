// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GENERATED_RUBY_DEFAULT_VISITOR_H_INCLUDED
#define GENERATED_RUBY_DEFAULT_VISITOR_H_INCLUDED

#include "generated/rubyvisitor.h"

namespace ruby
{

class  DefaultVisitor: public Visitor
{
public:
    virtual void visitAdditiveExpression(AdditiveExpressionAst *node);
    virtual void visitAliasParameter(AliasParameterAst *node);
    virtual void visitAndExpression(AndExpressionAst *node);
    virtual void visitAndorExpression(AndorExpressionAst *node);
    virtual void visitArrayAccess(ArrayAccessAst *node);
    virtual void visitArrayExpression(ArrayExpressionAst *node);
    virtual void visitArrayReferenceArgument(ArrayReferenceArgumentAst *node);
    virtual void visitAssignmentExpression(AssignmentExpressionAst *node);
    virtual void visitBlockContent(BlockContentAst *node);
    virtual void visitBlockMethodDefinitionArgument(BlockMethodDefinitionArgumentAst *node);
    virtual void visitBlockMethodInvocationArgument(BlockMethodInvocationArgumentAst *node);
    virtual void visitBlock_var(Block_varAst *node);
    virtual void visitBlock_vars(Block_varsAst *node);
    virtual void visitBodyStatement(BodyStatementAst *node);
    virtual void visitCaseExpression(CaseExpressionAst *node);
    virtual void visitClassDefinition(ClassDefinitionAst *node);
    virtual void visitClassName(ClassNameAst *node);
    virtual void visitCodeBlock(CodeBlockAst *node);
    virtual void visitColonAccess(ColonAccessAst *node);
    virtual void visitCommand(CommandAst *node);
    virtual void visitCommandOutput(CommandOutputAst *node);
    virtual void visitCompoundStatement(CompoundStatementAst *node);
    virtual void visitDoOrTerminalOrColon(DoOrTerminalOrColonAst *node);
    virtual void visitDotAccess(DotAccessAst *node);
    virtual void visitElementReference(ElementReferenceAst *node);
    virtual void visitEqualityExpression(EqualityExpressionAst *node);
    virtual void visitExceptionHandlingExpression(ExceptionHandlingExpressionAst *node);
    virtual void visitExceptionList(ExceptionListAst *node);
    virtual void visitExpression(ExpressionAst *node);
    virtual void visitExpressionSubstitution(ExpressionSubstitutionAst *node);
    virtual void visitForExpression(ForExpressionAst *node);
    virtual void visitHashExpression(HashExpressionAst *node);
    virtual void visitIfExpression(IfExpressionAst *node);
    virtual void visitKeyValuePair(KeyValuePairAst *node);
    virtual void visitKeyword(KeywordAst *node);
    virtual void visitKeywordAlias(KeywordAliasAst *node);
    virtual void visitKeywordAnd(KeywordAndAst *node);
    virtual void visitKeywordAsMethodName(KeywordAsMethodNameAst *node);
    virtual void visitKeywordBeginUpcase(KeywordBeginUpcaseAst *node);
    virtual void visitKeywordBreak(KeywordBreakAst *node);
    virtual void visitKeywordClass(KeywordClassAst *node);
    virtual void visitKeywordDef(KeywordDefAst *node);
    virtual void visitKeywordDefined(KeywordDefinedAst *node);
    virtual void visitKeywordDo(KeywordDoAst *node);
    virtual void visitKeywordEndUpcase(KeywordEndUpcaseAst *node);
    virtual void visitKeywordFor(KeywordForAst *node);
    virtual void visitKeywordIn(KeywordInAst *node);
    virtual void visitKeywordModule(KeywordModuleAst *node);
    virtual void visitKeywordNot(KeywordNotAst *node);
    virtual void visitKeywordOr(KeywordOrAst *node);
    virtual void visitKeywordUndef(KeywordUndefAst *node);
    virtual void visitKeywordUntil(KeywordUntilAst *node);
    virtual void visitKeywordWhen(KeywordWhenAst *node);
    virtual void visitKeywordWhile(KeywordWhileAst *node);
    virtual void visitLiteral(LiteralAst *node);
    virtual void visitLogicalAndExpression(LogicalAndExpressionAst *node);
    virtual void visitLogicalOrExpression(LogicalOrExpressionAst *node);
    virtual void visitMethodCall(MethodCallAst *node);
    virtual void visitMethodDefinition(MethodDefinitionAst *node);
    virtual void visitMethodDefinitionArgument(MethodDefinitionArgumentAst *node);
    virtual void visitMethodDefinitionArgumentWithoutParen(MethodDefinitionArgumentWithoutParenAst *node);
    virtual void visitMethodInvocationArgumentWithParen(MethodInvocationArgumentWithParenAst *node);
    virtual void visitMethodInvocationArgumentWithoutParen(MethodInvocationArgumentWithoutParenAst *node);
    virtual void visitMethodName(MethodNameAst *node);
    virtual void visitMethodNameSupplement(MethodNameSupplementAst *node);
    virtual void visitMlhs_item(Mlhs_itemAst *node);
    virtual void visitModuleDefinition(ModuleDefinitionAst *node);
    virtual void visitModuleName(ModuleNameAst *node);
    virtual void visitMrhs(MrhsAst *node);
    virtual void visitMultiplicativeExpression(MultiplicativeExpressionAst *node);
    virtual void visitNormalMethodDefinitionArgument(NormalMethodDefinitionArgumentAst *node);
    virtual void visitNormalMethodInvocationArgument(NormalMethodInvocationArgumentAst *node);
    virtual void visitNotExpression(NotExpressionAst *node);
    virtual void visitNumeric(NumericAst *node);
    virtual void visitOperatorAsMethodname(OperatorAsMethodnameAst *node);
    virtual void visitOperatorAssign(OperatorAssignAst *node);
    virtual void visitOperatorBAnd(OperatorBAndAst *node);
    virtual void visitOperatorBAndAssign(OperatorBAndAssignAst *node);
    virtual void visitOperatorBNot(OperatorBNotAst *node);
    virtual void visitOperatorBOr(OperatorBOrAst *node);
    virtual void visitOperatorBXor(OperatorBXorAst *node);
    virtual void visitOperatorBXorAssign(OperatorBXorAssignAst *node);
    virtual void visitOperatorBorAssign(OperatorBorAssignAst *node);
    virtual void visitOperatorCaseEqual(OperatorCaseEqualAst *node);
    virtual void visitOperatorColon(OperatorColonAst *node);
    virtual void visitOperatorCompare(OperatorCompareAst *node);
    virtual void visitOperatorDiv(OperatorDivAst *node);
    virtual void visitOperatorDivAssign(OperatorDivAssignAst *node);
    virtual void visitOperatorEqual(OperatorEqualAst *node);
    virtual void visitOperatorExclusiveRange(OperatorExclusiveRangeAst *node);
    virtual void visitOperatorGreaterOrEqual(OperatorGreaterOrEqualAst *node);
    virtual void visitOperatorGreaterThan(OperatorGreaterThanAst *node);
    virtual void visitOperatorInclusiveRange(OperatorInclusiveRangeAst *node);
    virtual void visitOperatorLeftShift(OperatorLeftShiftAst *node);
    virtual void visitOperatorLeftShiftAssign(OperatorLeftShiftAssignAst *node);
    virtual void visitOperatorLessOrEqual(OperatorLessOrEqualAst *node);
    virtual void visitOperatorLessThan(OperatorLessThanAst *node);
    virtual void visitOperatorLogicalAnd(OperatorLogicalAndAst *node);
    virtual void visitOperatorLogicalAndAssign(OperatorLogicalAndAssignAst *node);
    virtual void visitOperatorLogicalOr(OperatorLogicalOrAst *node);
    virtual void visitOperatorLogicalOrAssign(OperatorLogicalOrAssignAst *node);
    virtual void visitOperatorMatch(OperatorMatchAst *node);
    virtual void visitOperatorMinus(OperatorMinusAst *node);
    virtual void visitOperatorMinusAssign(OperatorMinusAssignAst *node);
    virtual void visitOperatorMod(OperatorModAst *node);
    virtual void visitOperatorModAssign(OperatorModAssignAst *node);
    virtual void visitOperatorNot(OperatorNotAst *node);
    virtual void visitOperatorNotEqual(OperatorNotEqualAst *node);
    virtual void visitOperatorNotMatch(OperatorNotMatchAst *node);
    virtual void visitOperatorPlus(OperatorPlusAst *node);
    virtual void visitOperatorPlusAssign(OperatorPlusAssignAst *node);
    virtual void visitOperatorPower(OperatorPowerAst *node);
    virtual void visitOperatorPowerAssign(OperatorPowerAssignAst *node);
    virtual void visitOperatorQuestion(OperatorQuestionAst *node);
    virtual void visitOperatorRightShift(OperatorRightShiftAst *node);
    virtual void visitOperatorRightShiftAssign(OperatorRightShiftAssignAst *node);
    virtual void visitOperatorStar(OperatorStarAst *node);
    virtual void visitOperatorStarAssign(OperatorStarAssignAst *node);
    virtual void visitOperatorUnaryMinus(OperatorUnaryMinusAst *node);
    virtual void visitOperatorUnaryPlus(OperatorUnaryPlusAst *node);
    virtual void visitOrExpression(OrExpressionAst *node);
    virtual void visitParallelAssignmentLeftOver(ParallelAssignmentLeftOverAst *node);
    virtual void visitPowerExpression(PowerExpressionAst *node);
    virtual void visitPredefinedValue(PredefinedValueAst *node);
    virtual void visitPrimaryExpression(PrimaryExpressionAst *node);
    virtual void visitProgram(ProgramAst *node);
    virtual void visitRangeExpression(RangeExpressionAst *node);
    virtual void visitRegex(RegexAst *node);
    virtual void visitRelationalExpression(RelationalExpressionAst *node);
    virtual void visitRestMethodDefinitionArgument(RestMethodDefinitionArgumentAst *node);
    virtual void visitRestMethodInvocationArgument(RestMethodInvocationArgumentAst *node);
    virtual void visitShiftExpression(ShiftExpressionAst *node);
    virtual void visitStatement(StatementAst *node);
    virtual void visitStatementWithoutModifier(StatementWithoutModifierAst *node);
    virtual void visitStatements(StatementsAst *node);
    virtual void visitString(StringAst *node);
    virtual void visitSymbol(SymbolAst *node);
    virtual void visitTerminal(TerminalAst *node);
    virtual void visitTernaryIfThenElseExpression(TernaryIfThenElseExpressionAst *node);
    virtual void visitThenOrTerminalOrColon(ThenOrTerminalOrColonAst *node);
    virtual void visitUnaryExpression(UnaryExpressionAst *node);
    virtual void visitUndefParameter(UndefParameterAst *node);
    virtual void visitUnlessExpression(UnlessExpressionAst *node);
    virtual void visitUntilExpression(UntilExpressionAst *node);
    virtual void visitVariable(VariableAst *node);
    virtual void visitWhileExpression(WhileExpressionAst *node);
};

} // end of namespace ruby

#endif

