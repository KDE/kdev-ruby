// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GENERATED_RUBY_AST_H_INCLUDED
#define GENERATED_RUBY_AST_H_INCLUDED

#include <QtCore/QList>
#include <kdev-pg-list.h>



#include "rubyparserexport.h"

namespace ruby
{
class Lexer;
}

#include <QtCore/QString>
#include <kdebug.h>


namespace ruby
{

struct AdditiveExpressionAst;
struct AliasParameterAst;
struct AndExpressionAst;
struct AndorExpressionAst;
struct ArrayAccessAst;
struct ArrayExpressionAst;
struct ArrayReferenceArgumentAst;
struct AssignmentExpressionAst;
struct BlockContentAst;
struct BlockMethodDefinitionArgumentAst;
struct BlockMethodInvocationArgumentAst;
struct Block_varAst;
struct Block_varsAst;
struct BodyStatementAst;
struct CaseExpressionAst;
struct ClassDefinitionAst;
struct ClassNameAst;
struct CodeBlockAst;
struct ColonAccessAst;
struct CommandAst;
struct CommandOutputAst;
struct CompoundStatementAst;
struct DoOrTerminalOrColonAst;
struct DotAccessAst;
struct ElementReferenceAst;
struct EqualityExpressionAst;
struct ExceptionHandlingExpressionAst;
struct ExceptionListAst;
struct ExpressionAst;
struct ExpressionSubstitutionAst;
struct ForExpressionAst;
struct HashExpressionAst;
struct IfExpressionAst;
struct KeyValuePairAst;
struct KeywordAst;
struct KeywordAliasAst;
struct KeywordAndAst;
struct KeywordAsMethodNameAst;
struct KeywordBeginUpcaseAst;
struct KeywordBreakAst;
struct KeywordClassAst;
struct KeywordDefAst;
struct KeywordDefinedAst;
struct KeywordDoAst;
struct KeywordEndUpcaseAst;
struct KeywordForAst;
struct KeywordInAst;
struct KeywordModuleAst;
struct KeywordNotAst;
struct KeywordOrAst;
struct KeywordUndefAst;
struct KeywordUntilAst;
struct KeywordWhenAst;
struct KeywordWhileAst;
struct LiteralAst;
struct LogicalAndExpressionAst;
struct LogicalOrExpressionAst;
struct MethodCallAst;
struct MethodDefinitionAst;
struct MethodDefinitionArgumentAst;
struct MethodDefinitionArgumentWithoutParenAst;
struct MethodInvocationArgumentWithParenAst;
struct MethodInvocationArgumentWithoutParenAst;
struct MethodNameAst;
struct MethodNameSupplementAst;
struct Mlhs_itemAst;
struct ModuleDefinitionAst;
struct ModuleNameAst;
struct MrhsAst;
struct MultiplicativeExpressionAst;
struct NormalMethodDefinitionArgumentAst;
struct NormalMethodInvocationArgumentAst;
struct NotExpressionAst;
struct NumericAst;
struct OperatorAsMethodnameAst;
struct OperatorAssignAst;
struct OperatorBAndAst;
struct OperatorBAndAssignAst;
struct OperatorBNotAst;
struct OperatorBOrAst;
struct OperatorBXorAst;
struct OperatorBXorAssignAst;
struct OperatorBorAssignAst;
struct OperatorCaseEqualAst;
struct OperatorColonAst;
struct OperatorCompareAst;
struct OperatorDivAst;
struct OperatorDivAssignAst;
struct OperatorEqualAst;
struct OperatorExclusiveRangeAst;
struct OperatorGreaterOrEqualAst;
struct OperatorGreaterThanAst;
struct OperatorInclusiveRangeAst;
struct OperatorLeftShiftAst;
struct OperatorLeftShiftAssignAst;
struct OperatorLessOrEqualAst;
struct OperatorLessThanAst;
struct OperatorLogicalAndAst;
struct OperatorLogicalAndAssignAst;
struct OperatorLogicalOrAst;
struct OperatorLogicalOrAssignAst;
struct OperatorMatchAst;
struct OperatorMinusAst;
struct OperatorMinusAssignAst;
struct OperatorModAst;
struct OperatorModAssignAst;
struct OperatorNotAst;
struct OperatorNotEqualAst;
struct OperatorNotMatchAst;
struct OperatorPlusAst;
struct OperatorPlusAssignAst;
struct OperatorPowerAst;
struct OperatorPowerAssignAst;
struct OperatorQuestionAst;
struct OperatorRightShiftAst;
struct OperatorRightShiftAssignAst;
struct OperatorStarAst;
struct OperatorStarAssignAst;
struct OperatorUnaryMinusAst;
struct OperatorUnaryPlusAst;
struct OrExpressionAst;
struct ParallelAssignmentLeftOverAst;
struct PowerExpressionAst;
struct PredefinedValueAst;
struct PrimaryExpressionAst;
struct ProgramAst;
struct RangeExpressionAst;
struct RegexAst;
struct RelationalExpressionAst;
struct RestMethodDefinitionArgumentAst;
struct RestMethodInvocationArgumentAst;
struct ShiftExpressionAst;
struct StatementAst;
struct StatementWithoutModifierAst;
struct StatementsAst;
struct StringAst;
struct SymbolAst;
struct TerminalAst;
struct TernaryIfThenElseExpressionAst;
struct ThenOrTerminalOrColonAst;
struct UnaryExpressionAst;
struct UndefParameterAst;
struct UnlessExpressionAst;
struct UntilExpressionAst;
struct VariableAst;
struct WhileExpressionAst;


struct  AstNode
{
    enum AstNodeKind
    {
        AdditiveExpressionKind = 1000,
        AliasParameterKind = 1001,
        AndExpressionKind = 1002,
        AndorExpressionKind = 1003,
        ArrayAccessKind = 1004,
        ArrayExpressionKind = 1005,
        ArrayReferenceArgumentKind = 1006,
        AssignmentExpressionKind = 1007,
        BlockContentKind = 1008,
        BlockMethodDefinitionArgumentKind = 1009,
        BlockMethodInvocationArgumentKind = 1010,
        Block_varKind = 1011,
        Block_varsKind = 1012,
        BodyStatementKind = 1013,
        CaseExpressionKind = 1014,
        ClassDefinitionKind = 1015,
        ClassNameKind = 1016,
        CodeBlockKind = 1017,
        ColonAccessKind = 1018,
        CommandKind = 1019,
        CommandOutputKind = 1020,
        CompoundStatementKind = 1021,
        DoOrTerminalOrColonKind = 1022,
        DotAccessKind = 1023,
        ElementReferenceKind = 1024,
        EqualityExpressionKind = 1025,
        ExceptionHandlingExpressionKind = 1026,
        ExceptionListKind = 1027,
        ExpressionKind = 1028,
        ExpressionSubstitutionKind = 1029,
        ForExpressionKind = 1030,
        HashExpressionKind = 1031,
        IfExpressionKind = 1032,
        KeyValuePairKind = 1033,
        KeywordKind = 1034,
        KeywordAliasKind = 1035,
        KeywordAndKind = 1036,
        KeywordAsMethodNameKind = 1037,
        KeywordBeginUpcaseKind = 1038,
        KeywordBreakKind = 1039,
        KeywordClassKind = 1040,
        KeywordDefKind = 1041,
        KeywordDefinedKind = 1042,
        KeywordDoKind = 1043,
        KeywordEndUpcaseKind = 1044,
        KeywordForKind = 1045,
        KeywordInKind = 1046,
        KeywordModuleKind = 1047,
        KeywordNotKind = 1048,
        KeywordOrKind = 1049,
        KeywordUndefKind = 1050,
        KeywordUntilKind = 1051,
        KeywordWhenKind = 1052,
        KeywordWhileKind = 1053,
        LiteralKind = 1054,
        LogicalAndExpressionKind = 1055,
        LogicalOrExpressionKind = 1056,
        MethodCallKind = 1057,
        MethodDefinitionKind = 1058,
        MethodDefinitionArgumentKind = 1059,
        MethodDefinitionArgumentWithoutParenKind = 1060,
        MethodInvocationArgumentWithParenKind = 1061,
        MethodInvocationArgumentWithoutParenKind = 1062,
        MethodNameKind = 1063,
        MethodNameSupplementKind = 1064,
        Mlhs_itemKind = 1065,
        ModuleDefinitionKind = 1066,
        ModuleNameKind = 1067,
        MrhsKind = 1068,
        MultiplicativeExpressionKind = 1069,
        NormalMethodDefinitionArgumentKind = 1070,
        NormalMethodInvocationArgumentKind = 1071,
        NotExpressionKind = 1072,
        NumericKind = 1073,
        OperatorAsMethodnameKind = 1074,
        OperatorAssignKind = 1075,
        OperatorBAndKind = 1076,
        OperatorBAndAssignKind = 1077,
        OperatorBNotKind = 1078,
        OperatorBOrKind = 1079,
        OperatorBXorKind = 1080,
        OperatorBXorAssignKind = 1081,
        OperatorBorAssignKind = 1082,
        OperatorCaseEqualKind = 1083,
        OperatorColonKind = 1084,
        OperatorCompareKind = 1085,
        OperatorDivKind = 1086,
        OperatorDivAssignKind = 1087,
        OperatorEqualKind = 1088,
        OperatorExclusiveRangeKind = 1089,
        OperatorGreaterOrEqualKind = 1090,
        OperatorGreaterThanKind = 1091,
        OperatorInclusiveRangeKind = 1092,
        OperatorLeftShiftKind = 1093,
        OperatorLeftShiftAssignKind = 1094,
        OperatorLessOrEqualKind = 1095,
        OperatorLessThanKind = 1096,
        OperatorLogicalAndKind = 1097,
        OperatorLogicalAndAssignKind = 1098,
        OperatorLogicalOrKind = 1099,
        OperatorLogicalOrAssignKind = 1100,
        OperatorMatchKind = 1101,
        OperatorMinusKind = 1102,
        OperatorMinusAssignKind = 1103,
        OperatorModKind = 1104,
        OperatorModAssignKind = 1105,
        OperatorNotKind = 1106,
        OperatorNotEqualKind = 1107,
        OperatorNotMatchKind = 1108,
        OperatorPlusKind = 1109,
        OperatorPlusAssignKind = 1110,
        OperatorPowerKind = 1111,
        OperatorPowerAssignKind = 1112,
        OperatorQuestionKind = 1113,
        OperatorRightShiftKind = 1114,
        OperatorRightShiftAssignKind = 1115,
        OperatorStarKind = 1116,
        OperatorStarAssignKind = 1117,
        OperatorUnaryMinusKind = 1118,
        OperatorUnaryPlusKind = 1119,
        OrExpressionKind = 1120,
        ParallelAssignmentLeftOverKind = 1121,
        PowerExpressionKind = 1122,
        PredefinedValueKind = 1123,
        PrimaryExpressionKind = 1124,
        ProgramKind = 1125,
        RangeExpressionKind = 1126,
        RegexKind = 1127,
        RelationalExpressionKind = 1128,
        RestMethodDefinitionArgumentKind = 1129,
        RestMethodInvocationArgumentKind = 1130,
        ShiftExpressionKind = 1131,
        StatementKind = 1132,
        StatementWithoutModifierKind = 1133,
        StatementsKind = 1134,
        StringKind = 1135,
        SymbolKind = 1136,
        TerminalKind = 1137,
        TernaryIfThenElseExpressionKind = 1138,
        ThenOrTerminalOrColonKind = 1139,
        UnaryExpressionKind = 1140,
        UndefParameterKind = 1141,
        UnlessExpressionKind = 1142,
        UntilExpressionKind = 1143,
        VariableKind = 1144,
        WhileExpressionKind = 1145,
        AST_NODE_KIND_COUNT
    };

    int kind;
    qint64 startToken;
    qint64 endToken;

};

struct  AdditiveExpressionAst: public AstNode
{
    enum { KIND = AdditiveExpressionKind };

};

struct  AliasParameterAst: public AstNode
{
    enum { KIND = AliasParameterKind };

};

struct  AndExpressionAst: public AstNode
{
    enum { KIND = AndExpressionKind };

};

struct  AndorExpressionAst: public AstNode
{
    enum { KIND = AndorExpressionKind };

};

struct  ArrayAccessAst: public AstNode
{
    enum { KIND = ArrayAccessKind };

};

struct  ArrayExpressionAst: public AstNode
{
    enum { KIND = ArrayExpressionKind };

};

struct  ArrayReferenceArgumentAst: public AstNode
{
    enum { KIND = ArrayReferenceArgumentKind };

};

struct  AssignmentExpressionAst: public AstNode
{
    enum { KIND = AssignmentExpressionKind };

};

struct  BlockContentAst: public AstNode
{
    enum { KIND = BlockContentKind };

};

struct  BlockMethodDefinitionArgumentAst: public AstNode
{
    enum { KIND = BlockMethodDefinitionArgumentKind };

};

struct  BlockMethodInvocationArgumentAst: public AstNode
{
    enum { KIND = BlockMethodInvocationArgumentKind };

};

struct  Block_varAst: public AstNode
{
    enum { KIND = Block_varKind };

};

struct  Block_varsAst: public AstNode
{
    enum { KIND = Block_varsKind };

};

struct  BodyStatementAst: public AstNode
{
    enum { KIND = BodyStatementKind };

};

struct  CaseExpressionAst: public AstNode
{
    enum { KIND = CaseExpressionKind };

};

struct  ClassDefinitionAst: public AstNode
{
    enum { KIND = ClassDefinitionKind };

};

struct  ClassNameAst: public AstNode
{
    enum { KIND = ClassNameKind };

};

struct  CodeBlockAst: public AstNode
{
    enum { KIND = CodeBlockKind };

};

struct  ColonAccessAst: public AstNode
{
    enum { KIND = ColonAccessKind };

};

struct  CommandAst: public AstNode
{
    enum { KIND = CommandKind };

};

struct  CommandOutputAst: public AstNode
{
    enum { KIND = CommandOutputKind };

};

struct  CompoundStatementAst: public AstNode
{
    enum { KIND = CompoundStatementKind };

    StatementsAst *statements;
};

struct  DoOrTerminalOrColonAst: public AstNode
{
    enum { KIND = DoOrTerminalOrColonKind };

};

struct  DotAccessAst: public AstNode
{
    enum { KIND = DotAccessKind };

};

struct  ElementReferenceAst: public AstNode
{
    enum { KIND = ElementReferenceKind };

};

struct  EqualityExpressionAst: public AstNode
{
    enum { KIND = EqualityExpressionKind };

};

struct  ExceptionHandlingExpressionAst: public AstNode
{
    enum { KIND = ExceptionHandlingExpressionKind };

};

struct  ExceptionListAst: public AstNode
{
    enum { KIND = ExceptionListKind };

};

struct  ExpressionAst: public AstNode
{
    enum { KIND = ExpressionKind };

};

struct  ExpressionSubstitutionAst: public AstNode
{
    enum { KIND = ExpressionSubstitutionKind };

};

struct  ForExpressionAst: public AstNode
{
    enum { KIND = ForExpressionKind };

};

struct  HashExpressionAst: public AstNode
{
    enum { KIND = HashExpressionKind };

};

struct  IfExpressionAst: public AstNode
{
    enum { KIND = IfExpressionKind };

};

struct  KeyValuePairAst: public AstNode
{
    enum { KIND = KeyValuePairKind };

};

struct  KeywordAst: public AstNode
{
    enum { KIND = KeywordKind };

};

struct  KeywordAliasAst: public AstNode
{
    enum { KIND = KeywordAliasKind };

};

struct  KeywordAndAst: public AstNode
{
    enum { KIND = KeywordAndKind };

};

struct  KeywordAsMethodNameAst: public AstNode
{
    enum { KIND = KeywordAsMethodNameKind };

};

struct  KeywordBeginUpcaseAst: public AstNode
{
    enum { KIND = KeywordBeginUpcaseKind };

};

struct  KeywordBreakAst: public AstNode
{
    enum { KIND = KeywordBreakKind };

};

struct  KeywordClassAst: public AstNode
{
    enum { KIND = KeywordClassKind };

};

struct  KeywordDefAst: public AstNode
{
    enum { KIND = KeywordDefKind };

};

struct  KeywordDefinedAst: public AstNode
{
    enum { KIND = KeywordDefinedKind };

};

struct  KeywordDoAst: public AstNode
{
    enum { KIND = KeywordDoKind };

};

struct  KeywordEndUpcaseAst: public AstNode
{
    enum { KIND = KeywordEndUpcaseKind };

};

struct  KeywordForAst: public AstNode
{
    enum { KIND = KeywordForKind };

};

struct  KeywordInAst: public AstNode
{
    enum { KIND = KeywordInKind };

};

struct  KeywordModuleAst: public AstNode
{
    enum { KIND = KeywordModuleKind };

};

struct  KeywordNotAst: public AstNode
{
    enum { KIND = KeywordNotKind };

};

struct  KeywordOrAst: public AstNode
{
    enum { KIND = KeywordOrKind };

};

struct  KeywordUndefAst: public AstNode
{
    enum { KIND = KeywordUndefKind };

};

struct  KeywordUntilAst: public AstNode
{
    enum { KIND = KeywordUntilKind };

};

struct  KeywordWhenAst: public AstNode
{
    enum { KIND = KeywordWhenKind };

};

struct  KeywordWhileAst: public AstNode
{
    enum { KIND = KeywordWhileKind };

};

struct  LiteralAst: public AstNode
{
    enum { KIND = LiteralKind };

};

struct  LogicalAndExpressionAst: public AstNode
{
    enum { KIND = LogicalAndExpressionKind };

};

struct  LogicalOrExpressionAst: public AstNode
{
    enum { KIND = LogicalOrExpressionKind };

};

struct  MethodCallAst: public AstNode
{
    enum { KIND = MethodCallKind };

};

struct  MethodDefinitionAst: public AstNode
{
    enum { KIND = MethodDefinitionKind };

};

struct  MethodDefinitionArgumentAst: public AstNode
{
    enum { KIND = MethodDefinitionArgumentKind };

};

struct  MethodDefinitionArgumentWithoutParenAst: public AstNode
{
    enum { KIND = MethodDefinitionArgumentWithoutParenKind };

};

struct  MethodInvocationArgumentWithParenAst: public AstNode
{
    enum { KIND = MethodInvocationArgumentWithParenKind };

};

struct  MethodInvocationArgumentWithoutParenAst: public AstNode
{
    enum { KIND = MethodInvocationArgumentWithoutParenKind };

};

struct  MethodNameAst: public AstNode
{
    enum { KIND = MethodNameKind };

};

struct  MethodNameSupplementAst: public AstNode
{
    enum { KIND = MethodNameSupplementKind };

};

struct  Mlhs_itemAst: public AstNode
{
    enum { KIND = Mlhs_itemKind };

};

struct  ModuleDefinitionAst: public AstNode
{
    enum { KIND = ModuleDefinitionKind };

};

struct  ModuleNameAst: public AstNode
{
    enum { KIND = ModuleNameKind };

};

struct  MrhsAst: public AstNode
{
    enum { KIND = MrhsKind };

};

struct  MultiplicativeExpressionAst: public AstNode
{
    enum { KIND = MultiplicativeExpressionKind };

};

struct  NormalMethodDefinitionArgumentAst: public AstNode
{
    enum { KIND = NormalMethodDefinitionArgumentKind };

};

struct  NormalMethodInvocationArgumentAst: public AstNode
{
    enum { KIND = NormalMethodInvocationArgumentKind };

};

struct  NotExpressionAst: public AstNode
{
    enum { KIND = NotExpressionKind };

};

struct  NumericAst: public AstNode
{
    enum { KIND = NumericKind };

};

struct  OperatorAsMethodnameAst: public AstNode
{
    enum { KIND = OperatorAsMethodnameKind };

};

struct  OperatorAssignAst: public AstNode
{
    enum { KIND = OperatorAssignKind };

};

struct  OperatorBAndAst: public AstNode
{
    enum { KIND = OperatorBAndKind };

};

struct  OperatorBAndAssignAst: public AstNode
{
    enum { KIND = OperatorBAndAssignKind };

};

struct  OperatorBNotAst: public AstNode
{
    enum { KIND = OperatorBNotKind };

};

struct  OperatorBOrAst: public AstNode
{
    enum { KIND = OperatorBOrKind };

};

struct  OperatorBXorAst: public AstNode
{
    enum { KIND = OperatorBXorKind };

};

struct  OperatorBXorAssignAst: public AstNode
{
    enum { KIND = OperatorBXorAssignKind };

};

struct  OperatorBorAssignAst: public AstNode
{
    enum { KIND = OperatorBorAssignKind };

};

struct  OperatorCaseEqualAst: public AstNode
{
    enum { KIND = OperatorCaseEqualKind };

};

struct  OperatorColonAst: public AstNode
{
    enum { KIND = OperatorColonKind };

};

struct  OperatorCompareAst: public AstNode
{
    enum { KIND = OperatorCompareKind };

};

struct  OperatorDivAst: public AstNode
{
    enum { KIND = OperatorDivKind };

};

struct  OperatorDivAssignAst: public AstNode
{
    enum { KIND = OperatorDivAssignKind };

};

struct  OperatorEqualAst: public AstNode
{
    enum { KIND = OperatorEqualKind };

};

struct  OperatorExclusiveRangeAst: public AstNode
{
    enum { KIND = OperatorExclusiveRangeKind };

};

struct  OperatorGreaterOrEqualAst: public AstNode
{
    enum { KIND = OperatorGreaterOrEqualKind };

};

struct  OperatorGreaterThanAst: public AstNode
{
    enum { KIND = OperatorGreaterThanKind };

};

struct  OperatorInclusiveRangeAst: public AstNode
{
    enum { KIND = OperatorInclusiveRangeKind };

};

struct  OperatorLeftShiftAst: public AstNode
{
    enum { KIND = OperatorLeftShiftKind };

};

struct  OperatorLeftShiftAssignAst: public AstNode
{
    enum { KIND = OperatorLeftShiftAssignKind };

};

struct  OperatorLessOrEqualAst: public AstNode
{
    enum { KIND = OperatorLessOrEqualKind };

};

struct  OperatorLessThanAst: public AstNode
{
    enum { KIND = OperatorLessThanKind };

};

struct  OperatorLogicalAndAst: public AstNode
{
    enum { KIND = OperatorLogicalAndKind };

};

struct  OperatorLogicalAndAssignAst: public AstNode
{
    enum { KIND = OperatorLogicalAndAssignKind };

};

struct  OperatorLogicalOrAst: public AstNode
{
    enum { KIND = OperatorLogicalOrKind };

};

struct  OperatorLogicalOrAssignAst: public AstNode
{
    enum { KIND = OperatorLogicalOrAssignKind };

};

struct  OperatorMatchAst: public AstNode
{
    enum { KIND = OperatorMatchKind };

};

struct  OperatorMinusAst: public AstNode
{
    enum { KIND = OperatorMinusKind };

};

struct  OperatorMinusAssignAst: public AstNode
{
    enum { KIND = OperatorMinusAssignKind };

};

struct  OperatorModAst: public AstNode
{
    enum { KIND = OperatorModKind };

};

struct  OperatorModAssignAst: public AstNode
{
    enum { KIND = OperatorModAssignKind };

};

struct  OperatorNotAst: public AstNode
{
    enum { KIND = OperatorNotKind };

};

struct  OperatorNotEqualAst: public AstNode
{
    enum { KIND = OperatorNotEqualKind };

};

struct  OperatorNotMatchAst: public AstNode
{
    enum { KIND = OperatorNotMatchKind };

};

struct  OperatorPlusAst: public AstNode
{
    enum { KIND = OperatorPlusKind };

};

struct  OperatorPlusAssignAst: public AstNode
{
    enum { KIND = OperatorPlusAssignKind };

};

struct  OperatorPowerAst: public AstNode
{
    enum { KIND = OperatorPowerKind };

};

struct  OperatorPowerAssignAst: public AstNode
{
    enum { KIND = OperatorPowerAssignKind };

};

struct  OperatorQuestionAst: public AstNode
{
    enum { KIND = OperatorQuestionKind };

};

struct  OperatorRightShiftAst: public AstNode
{
    enum { KIND = OperatorRightShiftKind };

};

struct  OperatorRightShiftAssignAst: public AstNode
{
    enum { KIND = OperatorRightShiftAssignKind };

};

struct  OperatorStarAst: public AstNode
{
    enum { KIND = OperatorStarKind };

};

struct  OperatorStarAssignAst: public AstNode
{
    enum { KIND = OperatorStarAssignKind };

};

struct  OperatorUnaryMinusAst: public AstNode
{
    enum { KIND = OperatorUnaryMinusKind };

};

struct  OperatorUnaryPlusAst: public AstNode
{
    enum { KIND = OperatorUnaryPlusKind };

};

struct  OrExpressionAst: public AstNode
{
    enum { KIND = OrExpressionKind };

};

struct  ParallelAssignmentLeftOverAst: public AstNode
{
    enum { KIND = ParallelAssignmentLeftOverKind };

};

struct  PowerExpressionAst: public AstNode
{
    enum { KIND = PowerExpressionKind };

};

struct  PredefinedValueAst: public AstNode
{
    enum { KIND = PredefinedValueKind };

};

struct  PrimaryExpressionAst: public AstNode
{
    enum { KIND = PrimaryExpressionKind };

};

struct  ProgramAst: public AstNode
{
    enum { KIND = ProgramKind };

    CompoundStatementAst *compoundStatement;
};

struct  RangeExpressionAst: public AstNode
{
    enum { KIND = RangeExpressionKind };

};

struct  RegexAst: public AstNode
{
    enum { KIND = RegexKind };

};

struct  RelationalExpressionAst: public AstNode
{
    enum { KIND = RelationalExpressionKind };

};

struct  RestMethodDefinitionArgumentAst: public AstNode
{
    enum { KIND = RestMethodDefinitionArgumentKind };

};

struct  RestMethodInvocationArgumentAst: public AstNode
{
    enum { KIND = RestMethodInvocationArgumentKind };

};

struct  ShiftExpressionAst: public AstNode
{
    enum { KIND = ShiftExpressionKind };

};

struct  StatementAst: public AstNode
{
    enum { KIND = StatementKind };

    StatementWithoutModifierAst *statementBody;
};

struct  StatementWithoutModifierAst: public AstNode
{
    enum { KIND = StatementWithoutModifierKind };

    ExpressionAst *expression;
};

struct  StatementsAst: public AstNode
{
    enum { KIND = StatementsKind };

    const KDevPG::ListNode<StatementAst *> *statementSequence;
};

struct  StringAst: public AstNode
{
    enum { KIND = StringKind };

};

struct  SymbolAst: public AstNode
{
    enum { KIND = SymbolKind };

};

struct  TerminalAst: public AstNode
{
    enum { KIND = TerminalKind };

};

struct  TernaryIfThenElseExpressionAst: public AstNode
{
    enum { KIND = TernaryIfThenElseExpressionKind };

};

struct  ThenOrTerminalOrColonAst: public AstNode
{
    enum { KIND = ThenOrTerminalOrColonKind };

};

struct  UnaryExpressionAst: public AstNode
{
    enum { KIND = UnaryExpressionKind };

};

struct  UndefParameterAst: public AstNode
{
    enum { KIND = UndefParameterKind };

};

struct  UnlessExpressionAst: public AstNode
{
    enum { KIND = UnlessExpressionKind };

};

struct  UntilExpressionAst: public AstNode
{
    enum { KIND = UntilExpressionKind };

};

struct  VariableAst: public AstNode
{
    enum { KIND = VariableKind };

};

struct  WhileExpressionAst: public AstNode
{
    enum { KIND = WhileExpressionKind };

};



} // end of namespace ruby

#endif

