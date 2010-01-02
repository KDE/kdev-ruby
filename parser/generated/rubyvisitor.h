// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GENERATED_RUBY_VISITOR_H_INCLUDED
#define GENERATED_RUBY_VISITOR_H_INCLUDED

#include "generated/rubyast.h"

namespace ruby
{

class  Visitor
{
    typedef void (Visitor::*ParserFuncType)(AstNode *);
    static ParserFuncType sParserTable[];

public:
    virtual ~Visitor() {}
    virtual void visitNode(AstNode *node)
    {
        if (node) (this->*sParserTable[node->kind - 1000])(node);
    }
    virtual void visitAdditiveExpression(AdditiveExpressionAst *) {}
    virtual void visitAliasParameter(AliasParameterAst *) {}
    virtual void visitAndExpression(AndExpressionAst *) {}
    virtual void visitAndorExpression(AndorExpressionAst *) {}
    virtual void visitArrayAccess(ArrayAccessAst *) {}
    virtual void visitArrayExpression(ArrayExpressionAst *) {}
    virtual void visitArrayReferenceArgument(ArrayReferenceArgumentAst *) {}
    virtual void visitAssignmentExpression(AssignmentExpressionAst *) {}
    virtual void visitBlockContent(BlockContentAst *) {}
    virtual void visitBlockMethodDefinitionArgument(BlockMethodDefinitionArgumentAst *) {}
    virtual void visitBlockMethodInvocationArgument(BlockMethodInvocationArgumentAst *) {}
    virtual void visitBlock_var(Block_varAst *) {}
    virtual void visitBlock_vars(Block_varsAst *) {}
    virtual void visitBodyStatement(BodyStatementAst *) {}
    virtual void visitCaseExpression(CaseExpressionAst *) {}
    virtual void visitClassDefinition(ClassDefinitionAst *) {}
    virtual void visitClassName(ClassNameAst *) {}
    virtual void visitCodeBlock(CodeBlockAst *) {}
    virtual void visitColonAccess(ColonAccessAst *) {}
    virtual void visitCommand(CommandAst *) {}
    virtual void visitCommandOutput(CommandOutputAst *) {}
    virtual void visitCompoundStatement(CompoundStatementAst *) {}
    virtual void visitDoOrTerminalOrColon(DoOrTerminalOrColonAst *) {}
    virtual void visitDotAccess(DotAccessAst *) {}
    virtual void visitElementReference(ElementReferenceAst *) {}
    virtual void visitEqualityExpression(EqualityExpressionAst *) {}
    virtual void visitExceptionHandlingExpression(ExceptionHandlingExpressionAst *) {}
    virtual void visitExceptionList(ExceptionListAst *) {}
    virtual void visitExpression(ExpressionAst *) {}
    virtual void visitExpressionSubstitution(ExpressionSubstitutionAst *) {}
    virtual void visitForExpression(ForExpressionAst *) {}
    virtual void visitHashExpression(HashExpressionAst *) {}
    virtual void visitIfExpression(IfExpressionAst *) {}
    virtual void visitKeyValuePair(KeyValuePairAst *) {}
    virtual void visitKeyword(KeywordAst *) {}
    virtual void visitKeywordAlias(KeywordAliasAst *) {}
    virtual void visitKeywordAnd(KeywordAndAst *) {}
    virtual void visitKeywordAsMethodName(KeywordAsMethodNameAst *) {}
    virtual void visitKeywordBeginUpcase(KeywordBeginUpcaseAst *) {}
    virtual void visitKeywordBreak(KeywordBreakAst *) {}
    virtual void visitKeywordClass(KeywordClassAst *) {}
    virtual void visitKeywordDef(KeywordDefAst *) {}
    virtual void visitKeywordDefined(KeywordDefinedAst *) {}
    virtual void visitKeywordDo(KeywordDoAst *) {}
    virtual void visitKeywordEndUpcase(KeywordEndUpcaseAst *) {}
    virtual void visitKeywordFor(KeywordForAst *) {}
    virtual void visitKeywordIn(KeywordInAst *) {}
    virtual void visitKeywordModule(KeywordModuleAst *) {}
    virtual void visitKeywordNot(KeywordNotAst *) {}
    virtual void visitKeywordOr(KeywordOrAst *) {}
    virtual void visitKeywordUndef(KeywordUndefAst *) {}
    virtual void visitKeywordUntil(KeywordUntilAst *) {}
    virtual void visitKeywordWhen(KeywordWhenAst *) {}
    virtual void visitKeywordWhile(KeywordWhileAst *) {}
    virtual void visitLiteral(LiteralAst *) {}
    virtual void visitLogicalAndExpression(LogicalAndExpressionAst *) {}
    virtual void visitLogicalOrExpression(LogicalOrExpressionAst *) {}
    virtual void visitMethodCall(MethodCallAst *) {}
    virtual void visitMethodDefinition(MethodDefinitionAst *) {}
    virtual void visitMethodDefinitionArgument(MethodDefinitionArgumentAst *) {}
    virtual void visitMethodDefinitionArgumentWithoutParen(MethodDefinitionArgumentWithoutParenAst *) {}
    virtual void visitMethodInvocationArgumentWithParen(MethodInvocationArgumentWithParenAst *) {}
    virtual void visitMethodInvocationArgumentWithoutParen(MethodInvocationArgumentWithoutParenAst *) {}
    virtual void visitMethodName(MethodNameAst *) {}
    virtual void visitMethodNameSupplement(MethodNameSupplementAst *) {}
    virtual void visitMlhs_item(Mlhs_itemAst *) {}
    virtual void visitModuleDefinition(ModuleDefinitionAst *) {}
    virtual void visitModuleName(ModuleNameAst *) {}
    virtual void visitMrhs(MrhsAst *) {}
    virtual void visitMultiplicativeExpression(MultiplicativeExpressionAst *) {}
    virtual void visitNormalMethodDefinitionArgument(NormalMethodDefinitionArgumentAst *) {}
    virtual void visitNormalMethodInvocationArgument(NormalMethodInvocationArgumentAst *) {}
    virtual void visitNotExpression(NotExpressionAst *) {}
    virtual void visitNumeric(NumericAst *) {}
    virtual void visitOperatorAsMethodname(OperatorAsMethodnameAst *) {}
    virtual void visitOperatorAssign(OperatorAssignAst *) {}
    virtual void visitOperatorBAnd(OperatorBAndAst *) {}
    virtual void visitOperatorBAndAssign(OperatorBAndAssignAst *) {}
    virtual void visitOperatorBNot(OperatorBNotAst *) {}
    virtual void visitOperatorBOr(OperatorBOrAst *) {}
    virtual void visitOperatorBXor(OperatorBXorAst *) {}
    virtual void visitOperatorBXorAssign(OperatorBXorAssignAst *) {}
    virtual void visitOperatorBorAssign(OperatorBorAssignAst *) {}
    virtual void visitOperatorCaseEqual(OperatorCaseEqualAst *) {}
    virtual void visitOperatorColon(OperatorColonAst *) {}
    virtual void visitOperatorCompare(OperatorCompareAst *) {}
    virtual void visitOperatorDiv(OperatorDivAst *) {}
    virtual void visitOperatorDivAssign(OperatorDivAssignAst *) {}
    virtual void visitOperatorEqual(OperatorEqualAst *) {}
    virtual void visitOperatorExclusiveRange(OperatorExclusiveRangeAst *) {}
    virtual void visitOperatorGreaterOrEqual(OperatorGreaterOrEqualAst *) {}
    virtual void visitOperatorGreaterThan(OperatorGreaterThanAst *) {}
    virtual void visitOperatorInclusiveRange(OperatorInclusiveRangeAst *) {}
    virtual void visitOperatorLeftShift(OperatorLeftShiftAst *) {}
    virtual void visitOperatorLeftShiftAssign(OperatorLeftShiftAssignAst *) {}
    virtual void visitOperatorLessOrEqual(OperatorLessOrEqualAst *) {}
    virtual void visitOperatorLessThan(OperatorLessThanAst *) {}
    virtual void visitOperatorLogicalAnd(OperatorLogicalAndAst *) {}
    virtual void visitOperatorLogicalAndAssign(OperatorLogicalAndAssignAst *) {}
    virtual void visitOperatorLogicalOr(OperatorLogicalOrAst *) {}
    virtual void visitOperatorLogicalOrAssign(OperatorLogicalOrAssignAst *) {}
    virtual void visitOperatorMatch(OperatorMatchAst *) {}
    virtual void visitOperatorMinus(OperatorMinusAst *) {}
    virtual void visitOperatorMinusAssign(OperatorMinusAssignAst *) {}
    virtual void visitOperatorMod(OperatorModAst *) {}
    virtual void visitOperatorModAssign(OperatorModAssignAst *) {}
    virtual void visitOperatorNot(OperatorNotAst *) {}
    virtual void visitOperatorNotEqual(OperatorNotEqualAst *) {}
    virtual void visitOperatorNotMatch(OperatorNotMatchAst *) {}
    virtual void visitOperatorPlus(OperatorPlusAst *) {}
    virtual void visitOperatorPlusAssign(OperatorPlusAssignAst *) {}
    virtual void visitOperatorPower(OperatorPowerAst *) {}
    virtual void visitOperatorPowerAssign(OperatorPowerAssignAst *) {}
    virtual void visitOperatorQuestion(OperatorQuestionAst *) {}
    virtual void visitOperatorRightShift(OperatorRightShiftAst *) {}
    virtual void visitOperatorRightShiftAssign(OperatorRightShiftAssignAst *) {}
    virtual void visitOperatorStar(OperatorStarAst *) {}
    virtual void visitOperatorStarAssign(OperatorStarAssignAst *) {}
    virtual void visitOperatorUnaryMinus(OperatorUnaryMinusAst *) {}
    virtual void visitOperatorUnaryPlus(OperatorUnaryPlusAst *) {}
    virtual void visitOrExpression(OrExpressionAst *) {}
    virtual void visitParallelAssignmentLeftOver(ParallelAssignmentLeftOverAst *) {}
    virtual void visitPowerExpression(PowerExpressionAst *) {}
    virtual void visitPredefinedValue(PredefinedValueAst *) {}
    virtual void visitPrimaryExpression(PrimaryExpressionAst *) {}
    virtual void visitProgram(ProgramAst *) {}
    virtual void visitRangeExpression(RangeExpressionAst *) {}
    virtual void visitRegex(RegexAst *) {}
    virtual void visitRelationalExpression(RelationalExpressionAst *) {}
    virtual void visitRestMethodDefinitionArgument(RestMethodDefinitionArgumentAst *) {}
    virtual void visitRestMethodInvocationArgument(RestMethodInvocationArgumentAst *) {}
    virtual void visitShiftExpression(ShiftExpressionAst *) {}
    virtual void visitStatement(StatementAst *) {}
    virtual void visitStatementWithoutModifier(StatementWithoutModifierAst *) {}
    virtual void visitStatements(StatementsAst *) {}
    virtual void visitString(StringAst *) {}
    virtual void visitSymbol(SymbolAst *) {}
    virtual void visitTerminal(TerminalAst *) {}
    virtual void visitTernaryIfThenElseExpression(TernaryIfThenElseExpressionAst *) {}
    virtual void visitThenOrTerminalOrColon(ThenOrTerminalOrColonAst *) {}
    virtual void visitUnaryExpression(UnaryExpressionAst *) {}
    virtual void visitUndefParameter(UndefParameterAst *) {}
    virtual void visitUnlessExpression(UnlessExpressionAst *) {}
    virtual void visitUntilExpression(UntilExpressionAst *) {}
    virtual void visitVariable(VariableAst *) {}
    virtual void visitWhileExpression(WhileExpressionAst *) {}
};

} // end of namespace ruby

#endif

