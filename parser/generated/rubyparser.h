// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GENERATED_RUBY_H_INCLUDED
#define GENERATED_RUBY_H_INCLUDED

#include "generated/rubyast.h"
#include <kdev-pg-memory-pool.h>
#include <kdev-pg-allocator.h>
#include <kdev-pg-token-stream.h>

namespace ruby
{

class  Parser
{
public:
    typedef KDevPG::TokenStream::Token Token;
    KDevPG::TokenStream *tokenStream;
    int yytoken;

    inline Token LA(qint64 k = 1) const
    {
        return tokenStream->token(tokenStream->index() - 1 + k - 1);
    }
    inline int yylex()
    {
        return (yytoken = tokenStream->nextToken());
    }
    inline void rewind(qint64 index)
    {
        tokenStream->rewind(index);
        yylex();
    }

// token stream
    void setTokenStream(KDevPG::TokenStream *s)
    {
        tokenStream = s;
    }

// error handling
    void expectedSymbol(int kind, const QString& name);
    void expectedToken(int kind, qint64 token, const QString& name);

    bool mBlockErrors;
    inline bool blockErrors(bool block)
    {
        bool previous = mBlockErrors;
        mBlockErrors = block;
        return previous;
    }

// memory pool
    typedef KDevPG::MemoryPool memoryPoolType;

    KDevPG::MemoryPool *memoryPool;
    void setMemoryPool(KDevPG::MemoryPool *p)
    {
        memoryPool = p;
    }
    template <class T>
    inline T *create()
    {
        T *node = new (memoryPool->allocate(sizeof(T))) T();
        node->kind = T::KIND;
        return node;
    }

    enum TokenType
    {
        Token_ALIAS = 1000,
        Token_AND = 1001,
        Token_ASCII_VALUE = 1002,
        Token_ASSIGN = 1003,
        Token_ASSIGN_WITH_NO_LEADING_SPACE = 1004,
        Token_ASSOC = 1005,
        Token_BAND = 1006,
        Token_BAND_ASSIGN = 1007,
        Token_BEGIN = 1008,
        Token_BEGIN_UPCASE = 1009,
        Token_BINARY = 1010,
        Token_BLOCK_ARG_PREFIX = 1011,
        Token_BNOT = 1012,
        Token_BOR = 1013,
        Token_BOR_ASSIGN = 1014,
        Token_BREAK = 1015,
        Token_BXOR = 1016,
        Token_BXOR_ASSIGN = 1017,
        Token_CASE = 1018,
        Token_CASE_EQUAL = 1019,
        Token_CLASS = 1020,
        Token_CLASS_VARIABLE = 1021,
        Token_COLON = 1022,
        Token_COLON_WITH_NO_FOLLOWING_SPACE = 1023,
        Token_COMMA = 1024,
        Token_COMMAND_OUTPUT = 1025,
        Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION = 1026,
        Token_COMMENT = 1027,
        Token_COMPARE = 1028,
        Token_CONSTANT = 1029,
        Token_DEF = 1030,
        Token_DEFINED = 1031,
        Token_DIV = 1032,
        Token_DIV_ASSIGN = 1033,
        Token_DO = 1034,
        Token_DOT = 1035,
        Token_DOUBLE_QUOTED_STRING = 1036,
        Token_DO_IN_CONDITION = 1037,
        Token_ELSE = 1038,
        Token_ELSIF = 1039,
        Token_END = 1040,
        Token_END_UPCASE = 1041,
        Token_ENSURE = 1042,
        Token_EOF = 1043,
        Token_EQUAL = 1044,
        Token_EXCLUSIVE_RANGE = 1045,
        Token_FALSE = 1046,
        Token_FILE = 1047,
        Token_FLOAT = 1048,
        Token_FOR = 1049,
        Token_FUNCTION = 1050,
        Token_GLOBAL_VARIABLE = 1051,
        Token_GREATER_OR_EQUAL = 1052,
        Token_GREATER_THAN = 1053,
        Token_HERE_DOC_BEGIN = 1054,
        Token_HEX = 1055,
        Token_IDENTIFIER = 1056,
        Token_IF = 1057,
        Token_IF_MODIFIER = 1058,
        Token_IN = 1059,
        Token_INCLUSIVE_RANGE = 1060,
        Token_INSTANCE_VARIABLE = 1061,
        Token_INTEGER = 1062,
        Token_KEYWORD_NOT = 1063,
        Token_LBRACK = 1064,
        Token_LBRACK_ARRAY_ACCESS = 1065,
        Token_LCURLY = 1066,
        Token_LCURLY_BLOCK = 1067,
        Token_LCURLY_HASH = 1068,
        Token_LEADING_TWO_COLON = 1069,
        Token_LEFT_SHIFT = 1070,
        Token_LEFT_SHIFT_ASSIGN = 1071,
        Token_LESS_OR_EQUAL = 1072,
        Token_LESS_THAN = 1073,
        Token_LINE = 1074,
        Token_LINE_BREAK = 1075,
        Token_LOGICAL_AND = 1076,
        Token_LOGICAL_AND_ASSIGN = 1077,
        Token_LOGICAL_OR = 1078,
        Token_LOGICAL_OR_ASSIGN = 1079,
        Token_LPAREN = 1080,
        Token_MATCH = 1081,
        Token_MINUS = 1082,
        Token_MINUS_ASSIGN = 1083,
        Token_MOD = 1084,
        Token_MODULE = 1085,
        Token_MOD_ASSIGN = 1086,
        Token_NEXT = 1087,
        Token_NIL = 1088,
        Token_NOT = 1089,
        Token_NOT_EQUAL = 1090,
        Token_NOT_MATCH = 1091,
        Token_OCTAL = 1092,
        Token_OR = 1093,
        Token_PLUS = 1094,
        Token_PLUS_ASSIGN = 1095,
        Token_POWER = 1096,
        Token_POWER_ASSIGN = 1097,
        Token_QUESTION = 1098,
        Token_RBRACK = 1099,
        Token_RCURLY = 1100,
        Token_RCURLY_BLOCK = 1101,
        Token_REDO = 1102,
        Token_REGEX = 1103,
        Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION = 1104,
        Token_RESCUE = 1105,
        Token_RESCUE_MODIFIER = 1106,
        Token_REST_ARG_PREFIX = 1107,
        Token_RETRY = 1108,
        Token_RETURN = 1109,
        Token_RIGHT_SHIFT = 1110,
        Token_RIGHT_SHIFT_ASSIGN = 1111,
        Token_RPAREN = 1112,
        Token_SELF = 1113,
        Token_SEMI = 1114,
        Token_SINGLE_QUOTE = 1115,
        Token_SINGLE_QUOTED_STRING = 1116,
        Token_STAR = 1117,
        Token_STAR_ASSIGN = 1118,
        Token_STRING_AFTER_EXPRESSION_SUBSTITUTION = 1119,
        Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION = 1120,
        Token_STRING_BETWEEN_EXPRESSION_SUBSTITUTION = 1121,
        Token_STUB_A = 1122,
        Token_STUB_B = 1123,
        Token_STUB_C = 1124,
        Token_SUPER = 1125,
        Token_THEN = 1126,
        Token_TRUE = 1127,
        Token_TWO_COLON = 1128,
        Token_UNARY_MINUS = 1129,
        Token_UNARY_PLUS = 1130,
        Token_UNARY_PLUS_MINUS_METHOD_NAME = 1131,
        Token_UNDEF = 1132,
        Token_UNLESS = 1133,
        Token_UNLESS_MODIFIER = 1134,
        Token_UNTIL = 1135,
        Token_UNTIL_MODIFIER = 1136,
        Token_WHEN = 1137,
        Token_WHILE = 1138,
        Token_WHILE_MODIFIER = 1139,
        Token_W_ARRAY = 1140,
        Token_YIELD = 1141,
        TokenTypeSize
    }; // TokenType

// user defined declarations:
public:

    /**
     * Transform the raw input into tokens.
     * When this method returns, the parser's token stream has been filled
     * and any parse_*() method can be called.
     */
    void tokenize( char *contents );

    enum problem_type
    {
        error,
        warning,
        info
    };

    void report_problem( Parser::problem_type type, const char* message );
    void report_problem( Parser::problem_type type, std::string message );
    char* tokenText(std::size_t begin);

protected:

    void expectedSymbol(ruby::AstNode::AstNodeKind kind, const QString& name)
    {
        kWarning() << "In AstNode " << kind << ": Expected symbol " << name;
    }
    void expectedToken(int kind, enum TokenType token, const QString& name)
    {
        kWarning() << "In AstNode " << kind << ": Expected token " << name << " (" << token << ")";
    }

private:

    struct ParserState { };
    ParserState m_state;

    //state modifiers
    bool seen_star;
    bool seen_star_or_band;
    bool seen_rparen;

    bool expect_array_or_block_arguments;

    Lexer *m_lexer;
    char* m_contents;


public:
// The copyCurrentState() and restoreState() methods are only declared
// if you are using try blocks in your grammar, and have to be
// implemented by yourself, and you also have to define a
// "struct ParserState" inside a %parserclass directive.

// This method should create a new ParserState object and return it,
// or return 0 if no state variables need to be saved.
    ParserState *copyCurrentState();

// This method is only called for ParserState objects != 0
// and should restore the parser state given as argument.
    void restoreState(ParserState *state);
    Parser()
    {
        memoryPool = 0;
        tokenStream = 0;
        yytoken = Token_EOF;
        mBlockErrors = false;
    }

    virtual ~Parser() {}

    bool parseAdditiveExpression(AdditiveExpressionAst **yynode);
    bool parseAliasParameter(AliasParameterAst **yynode);
    bool parseAndExpression(AndExpressionAst **yynode);
    bool parseAndorExpression(AndorExpressionAst **yynode);
    bool parseArrayAccess(ArrayAccessAst **yynode);
    bool parseArrayExpression(ArrayExpressionAst **yynode);
    bool parseArrayReferenceArgument(ArrayReferenceArgumentAst **yynode);
    bool parseAssignmentExpression(AssignmentExpressionAst **yynode);
    bool parseBlockContent(BlockContentAst **yynode);
    bool parseBlockMethodDefinitionArgument(BlockMethodDefinitionArgumentAst **yynode);
    bool parseBlockMethodInvocationArgument(BlockMethodInvocationArgumentAst **yynode);
    bool parseBlock_var(Block_varAst **yynode);
    bool parseBlock_vars(Block_varsAst **yynode);
    bool parseBodyStatement(BodyStatementAst **yynode);
    bool parseCaseExpression(CaseExpressionAst **yynode);
    bool parseClassDefinition(ClassDefinitionAst **yynode);
    bool parseClassName(ClassNameAst **yynode);
    bool parseCodeBlock(CodeBlockAst **yynode);
    bool parseColonAccess(ColonAccessAst **yynode);
    bool parseCommand(CommandAst **yynode);
    bool parseCommandOutput(CommandOutputAst **yynode);
    bool parseCompoundStatement(CompoundStatementAst **yynode);
    bool parseDoOrTerminalOrColon(DoOrTerminalOrColonAst **yynode);
    bool parseDotAccess(DotAccessAst **yynode);
    bool parseElementReference(ElementReferenceAst **yynode);
    bool parseEqualityExpression(EqualityExpressionAst **yynode);
    bool parseExceptionHandlingExpression(ExceptionHandlingExpressionAst **yynode);
    bool parseExceptionList(ExceptionListAst **yynode);
    bool parseExpression(ExpressionAst **yynode);
    bool parseExpressionSubstitution(ExpressionSubstitutionAst **yynode);
    bool parseForExpression(ForExpressionAst **yynode);
    bool parseHashExpression(HashExpressionAst **yynode);
    bool parseIfExpression(IfExpressionAst **yynode);
    bool parseKeyValuePair(KeyValuePairAst **yynode);
    bool parseKeyword(KeywordAst **yynode);
    bool parseKeywordAlias(KeywordAliasAst **yynode);
    bool parseKeywordAnd(KeywordAndAst **yynode);
    bool parseKeywordAsMethodName(KeywordAsMethodNameAst **yynode);
    bool parseKeywordBeginUpcase(KeywordBeginUpcaseAst **yynode);
    bool parseKeywordBreak(KeywordBreakAst **yynode);
    bool parseKeywordClass(KeywordClassAst **yynode);
    bool parseKeywordDef(KeywordDefAst **yynode);
    bool parseKeywordDefined(KeywordDefinedAst **yynode);
    bool parseKeywordDo(KeywordDoAst **yynode);
    bool parseKeywordEndUpcase(KeywordEndUpcaseAst **yynode);
    bool parseKeywordFor(KeywordForAst **yynode);
    bool parseKeywordIn(KeywordInAst **yynode);
    bool parseKeywordModule(KeywordModuleAst **yynode);
    bool parseKeywordNot(KeywordNotAst **yynode);
    bool parseKeywordOr(KeywordOrAst **yynode);
    bool parseKeywordUndef(KeywordUndefAst **yynode);
    bool parseKeywordUntil(KeywordUntilAst **yynode);
    bool parseKeywordWhen(KeywordWhenAst **yynode);
    bool parseKeywordWhile(KeywordWhileAst **yynode);
    bool parseLiteral(LiteralAst **yynode);
    bool parseLogicalAndExpression(LogicalAndExpressionAst **yynode);
    bool parseLogicalOrExpression(LogicalOrExpressionAst **yynode);
    bool parseMethodCall(MethodCallAst **yynode);
    bool parseMethodDefinition(MethodDefinitionAst **yynode);
    bool parseMethodDefinitionArgument(MethodDefinitionArgumentAst **yynode);
    bool parseMethodDefinitionArgumentWithoutParen(MethodDefinitionArgumentWithoutParenAst **yynode);
    bool parseMethodInvocationArgumentWithParen(MethodInvocationArgumentWithParenAst **yynode);
    bool parseMethodInvocationArgumentWithoutParen(MethodInvocationArgumentWithoutParenAst **yynode);
    bool parseMethodName(MethodNameAst **yynode);
    bool parseMethodNameSupplement(MethodNameSupplementAst **yynode);
    bool parseMlhs_item(Mlhs_itemAst **yynode);
    bool parseModuleDefinition(ModuleDefinitionAst **yynode);
    bool parseModuleName(ModuleNameAst **yynode);
    bool parseMrhs(MrhsAst **yynode);
    bool parseMultiplicativeExpression(MultiplicativeExpressionAst **yynode);
    bool parseNormalMethodDefinitionArgument(NormalMethodDefinitionArgumentAst **yynode);
    bool parseNormalMethodInvocationArgument(NormalMethodInvocationArgumentAst **yynode);
    bool parseNotExpression(NotExpressionAst **yynode);
    bool parseNumeric(NumericAst **yynode);
    bool parseOperatorAsMethodname(OperatorAsMethodnameAst **yynode);
    bool parseOperatorAssign(OperatorAssignAst **yynode);
    bool parseOperatorBAnd(OperatorBAndAst **yynode);
    bool parseOperatorBAndAssign(OperatorBAndAssignAst **yynode);
    bool parseOperatorBNot(OperatorBNotAst **yynode);
    bool parseOperatorBOr(OperatorBOrAst **yynode);
    bool parseOperatorBXor(OperatorBXorAst **yynode);
    bool parseOperatorBXorAssign(OperatorBXorAssignAst **yynode);
    bool parseOperatorBorAssign(OperatorBorAssignAst **yynode);
    bool parseOperatorCaseEqual(OperatorCaseEqualAst **yynode);
    bool parseOperatorColon(OperatorColonAst **yynode);
    bool parseOperatorCompare(OperatorCompareAst **yynode);
    bool parseOperatorDiv(OperatorDivAst **yynode);
    bool parseOperatorDivAssign(OperatorDivAssignAst **yynode);
    bool parseOperatorEqual(OperatorEqualAst **yynode);
    bool parseOperatorExclusiveRange(OperatorExclusiveRangeAst **yynode);
    bool parseOperatorGreaterOrEqual(OperatorGreaterOrEqualAst **yynode);
    bool parseOperatorGreaterThan(OperatorGreaterThanAst **yynode);
    bool parseOperatorInclusiveRange(OperatorInclusiveRangeAst **yynode);
    bool parseOperatorLeftShift(OperatorLeftShiftAst **yynode);
    bool parseOperatorLeftShiftAssign(OperatorLeftShiftAssignAst **yynode);
    bool parseOperatorLessOrEqual(OperatorLessOrEqualAst **yynode);
    bool parseOperatorLessThan(OperatorLessThanAst **yynode);
    bool parseOperatorLogicalAnd(OperatorLogicalAndAst **yynode);
    bool parseOperatorLogicalAndAssign(OperatorLogicalAndAssignAst **yynode);
    bool parseOperatorLogicalOr(OperatorLogicalOrAst **yynode);
    bool parseOperatorLogicalOrAssign(OperatorLogicalOrAssignAst **yynode);
    bool parseOperatorMatch(OperatorMatchAst **yynode);
    bool parseOperatorMinus(OperatorMinusAst **yynode);
    bool parseOperatorMinusAssign(OperatorMinusAssignAst **yynode);
    bool parseOperatorMod(OperatorModAst **yynode);
    bool parseOperatorModAssign(OperatorModAssignAst **yynode);
    bool parseOperatorNot(OperatorNotAst **yynode);
    bool parseOperatorNotEqual(OperatorNotEqualAst **yynode);
    bool parseOperatorNotMatch(OperatorNotMatchAst **yynode);
    bool parseOperatorPlus(OperatorPlusAst **yynode);
    bool parseOperatorPlusAssign(OperatorPlusAssignAst **yynode);
    bool parseOperatorPower(OperatorPowerAst **yynode);
    bool parseOperatorPowerAssign(OperatorPowerAssignAst **yynode);
    bool parseOperatorQuestion(OperatorQuestionAst **yynode);
    bool parseOperatorRightShift(OperatorRightShiftAst **yynode);
    bool parseOperatorRightShiftAssign(OperatorRightShiftAssignAst **yynode);
    bool parseOperatorStar(OperatorStarAst **yynode);
    bool parseOperatorStarAssign(OperatorStarAssignAst **yynode);
    bool parseOperatorUnaryMinus(OperatorUnaryMinusAst **yynode);
    bool parseOperatorUnaryPlus(OperatorUnaryPlusAst **yynode);
    bool parseOrExpression(OrExpressionAst **yynode);
    bool parseParallelAssignmentLeftOver(ParallelAssignmentLeftOverAst **yynode);
    bool parsePowerExpression(PowerExpressionAst **yynode);
    bool parsePredefinedValue(PredefinedValueAst **yynode);
    bool parsePrimaryExpression(PrimaryExpressionAst **yynode);
    bool parseProgram(ProgramAst **yynode);
    bool parseRangeExpression(RangeExpressionAst **yynode);
    bool parseRegex(RegexAst **yynode);
    bool parseRelationalExpression(RelationalExpressionAst **yynode);
    bool parseRestMethodDefinitionArgument(RestMethodDefinitionArgumentAst **yynode);
    bool parseRestMethodInvocationArgument(RestMethodInvocationArgumentAst **yynode);
    bool parseShiftExpression(ShiftExpressionAst **yynode);
    bool parseStatement(StatementAst **yynode);
    bool parseStatementWithoutModifier(StatementWithoutModifierAst **yynode);
    bool parseStatements(StatementsAst **yynode);
    bool parseString(StringAst **yynode);
    bool parseSymbol(SymbolAst **yynode);
    bool parseTerminal(TerminalAst **yynode);
    bool parseTernaryIfThenElseExpression(TernaryIfThenElseExpressionAst **yynode);
    bool parseThenOrTerminalOrColon(ThenOrTerminalOrColonAst **yynode);
    bool parseUnaryExpression(UnaryExpressionAst **yynode);
    bool parseUndefParameter(UndefParameterAst **yynode);
    bool parseUnlessExpression(UnlessExpressionAst **yynode);
    bool parseUntilExpression(UntilExpressionAst **yynode);
    bool parseVariable(VariableAst **yynode);
    bool parseWhileExpression(WhileExpressionAst **yynode);
};

} // end of namespace ruby

#endif

