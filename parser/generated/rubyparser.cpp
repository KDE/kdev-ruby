// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "generated/rubyparser.h"



#include "ruby_lexer.h"

namespace ruby
{

void Parser::tokenize( char *contents )
{
    m_contents = contents;
    m_lexer = new Lexer( this, contents );

    int kind = Parser::Token_EOF;
    do
    {
        kind = m_lexer->yylex();
        std::cerr << m_lexer->YYText() << " of kind " << kind << std::endl; //" "; // debug output

        if ( !kind ) // when the lexer returns 0, the end of file is reached
            kind = Parser::Token_EOF;

        Parser::token_type &t = this->token_stream->next();
        t.kind = kind;
        t.begin = m_lexer->tokenBegin();
        t.end = m_lexer->tokenEnd();
    }
    while (kind != Parser::Token_EOF);

    this->yylex(); // produce the look ahead token
    delete m_lexer;
    m_lexer = 0;
}

Parser::ParserState *Parser::copyCurrentState()
{
    ParserState *state = new ParserState();
    // (copy any member variables from m_state to state)
    return state;
}

void Parser::restoreState( Parser::ParserState *state )
{
    // (copy any member variables from state to m_state)
}


char* Parser::tokenText(std::size_t begin)
{
    return &m_contents[begin];
}

} // end of namespace ruby


namespace ruby
{

bool Parser::parseAdditiveExpression(AdditiveExpressionAst **yynode)
{
    *yynode = create<AdditiveExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        MultiplicativeExpressionAst *__node_0 = 0;
        if (!parseMultiplicativeExpression(&__node_0))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::MultiplicativeExpressionKind, "multiplicativeExpression");
            }
            return false;
        }
        while (yytoken == Token_MINUS
               || yytoken == Token_PLUS)
        {
            if (yytoken == Token_PLUS)
            {
                OperatorPlusAst *__node_1 = 0;
                if (!parseOperatorPlus(&__node_1))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorPlusKind, "operatorPlus");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_MINUS)
            {
                OperatorMinusAst *__node_2 = 0;
                if (!parseOperatorMinus(&__node_2))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorMinusKind, "operatorMinus");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
            MultiplicativeExpressionAst *__node_3 = 0;
            if (!parseMultiplicativeExpression(&__node_3))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MultiplicativeExpressionKind, "multiplicativeExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAliasParameter(AliasParameterAst **yynode)
{
    *yynode = create<AliasParameterAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_AND
        || yytoken == Token_BAND
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BNOT
        || yytoken == Token_BOR
        || yytoken == Token_BREAK
        || yytoken == Token_BXOR
        || yytoken == Token_CASE
        || yytoken == Token_CASE_EQUAL
        || yytoken == Token_CLASS
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMPARE
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DIV
        || yytoken == Token_DO
        || yytoken == Token_ELSE
        || yytoken == Token_ELSIF
        || yytoken == Token_END
        || yytoken == Token_END_UPCASE
        || yytoken == Token_ENSURE
        || yytoken == Token_EQUAL
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_GREATER_OR_EQUAL
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_IN
        || yytoken == Token_LBRACK
        || yytoken == Token_LBRACK_ARRAY_ACCESS
        || yytoken == Token_LEFT_SHIFT
        || yytoken == Token_LESS_OR_EQUAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_MATCH
        || yytoken == Token_MINUS
        || yytoken == Token_MOD
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NOT
        || yytoken == Token_OR
        || yytoken == Token_PLUS
        || yytoken == Token_POWER
        || yytoken == Token_REDO
        || yytoken == Token_RESCUE
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_RIGHT_SHIFT
        || yytoken == Token_SINGLE_QUOTE
        || yytoken == Token_STAR
        || yytoken == Token_SUPER
        || yytoken == Token_THEN
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHEN
        || yytoken == Token_WHILE
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_ALIAS
            || yytoken == Token_AND
            || yytoken == Token_BAND
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BNOT
            || yytoken == Token_BOR
            || yytoken == Token_BREAK
            || yytoken == Token_BXOR
            || yytoken == Token_CASE
            || yytoken == Token_CASE_EQUAL
            || yytoken == Token_CLASS
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMPARE
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DIV
            || yytoken == Token_DO
            || yytoken == Token_ELSE
            || yytoken == Token_ELSIF
            || yytoken == Token_END
            || yytoken == Token_END_UPCASE
            || yytoken == Token_ENSURE
            || yytoken == Token_EQUAL
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GREATER_OR_EQUAL
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_IN
            || yytoken == Token_LBRACK
            || yytoken == Token_LBRACK_ARRAY_ACCESS
            || yytoken == Token_LEFT_SHIFT
            || yytoken == Token_LESS_OR_EQUAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_MATCH
            || yytoken == Token_MINUS
            || yytoken == Token_MOD
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NOT
            || yytoken == Token_OR
            || yytoken == Token_PLUS
            || yytoken == Token_POWER
            || yytoken == Token_REDO
            || yytoken == Token_RESCUE
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_RIGHT_SHIFT
            || yytoken == Token_SINGLE_QUOTE
            || yytoken == Token_STAR
            || yytoken == Token_SUPER
            || yytoken == Token_THEN
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHEN
            || yytoken == Token_WHILE
            || yytoken == Token_YIELD)
        {
            UndefParameterAst *__node_4 = 0;
            if (!parseUndefParameter(&__node_4))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UndefParameterKind, "undefParameter");
                }
                return false;
            }
        }
        else if (yytoken == Token_GLOBAL_VARIABLE)
        {
            if (yytoken != Token_GLOBAL_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GLOBAL_VARIABLE, "global variable");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAndExpression(AndExpressionAst **yynode)
{
    *yynode = create<AndExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        ShiftExpressionAst *__node_5 = 0;
        if (!parseShiftExpression(&__node_5))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ShiftExpressionKind, "shiftExpression");
            }
            return false;
        }
        while (yytoken == Token_BAND)
        {
            OperatorBAndAst *__node_6 = 0;
            if (!parseOperatorBAnd(&__node_6))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorBAndKind, "operatorBAnd");
                }
                return false;
            }
            ShiftExpressionAst *__node_7 = 0;
            if (!parseShiftExpression(&__node_7))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ShiftExpressionKind, "shiftExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAndorExpression(AndorExpressionAst **yynode)
{
    *yynode = create<AndorExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        NotExpressionAst *__node_8 = 0;
        if (!parseNotExpression(&__node_8))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::NotExpressionKind, "notExpression");
            }
            return false;
        }
        while (yytoken == Token_AND
               || yytoken == Token_OR)
        {
            if (yytoken == Token_AND)
            {
                KeywordAndAst *__node_9 = 0;
                if (!parseKeywordAnd(&__node_9))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::KeywordAndKind, "keywordAnd");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_OR)
            {
                KeywordOrAst *__node_10 = 0;
                if (!parseKeywordOr(&__node_10))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::KeywordOrKind, "keywordOr");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
            NotExpressionAst *__node_11 = 0;
            if (!parseNotExpression(&__node_11))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::NotExpressionKind, "notExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseArrayAccess(ArrayAccessAst **yynode)
{
    *yynode = create<ArrayAccessAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACK_ARRAY_ACCESS)
    {
        if (yytoken != Token_LBRACK_ARRAY_ACCESS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACK_ARRAY_ACCESS, "[");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            ArrayReferenceArgumentAst *__node_12 = 0;
            if (!parseArrayReferenceArgument(&__node_12))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ArrayReferenceArgumentKind, "arrayReferenceArgument");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RBRACK)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACK, "]");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseArrayExpression(ArrayExpressionAst **yynode)
{
    *yynode = create<ArrayExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACK)
    {
        if (yytoken != Token_LBRACK)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACK, "[");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            ArrayReferenceArgumentAst *__node_13 = 0;
            if (!parseArrayReferenceArgument(&__node_13))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ArrayReferenceArgumentKind, "arrayReferenceArgument");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RBRACK)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACK, "]");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseArrayReferenceArgument(ArrayReferenceArgumentAst **yynode)
{
    *yynode = create<ArrayReferenceArgumentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            KeyValuePairAst *__node_14 = 0;
            if (!parseKeyValuePair(&__node_14))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeyValuePairKind, "keyValuePair");
                }
                return false;
            }
            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                if ((yytoken == Token_ASSIGN) || (yytoken == Token_RBRACK)) break;
                if (yytoken == Token_REST_ARG_PREFIX)
                {
                    if (yytoken != Token_REST_ARG_PREFIX)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_REST_ARG_PREFIX, "*");
                        }
                        return false;
                    }
                    yylex();

                    seen_star = true;
                }
                else if (true /*epsilon*/)
                {
                    seen_star = false;
                }
                else
                {
                    return false;
                }
                KeyValuePairAst *__node_15 = 0;
                if (!parseKeyValuePair(&__node_15))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::KeyValuePairKind, "keyValuePair");
                    }
                    return false;
                }
                if (seen_star) break;
            }
        }
        else if (yytoken == Token_REST_ARG_PREFIX)
        {
            if (yytoken != Token_REST_ARG_PREFIX)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REST_ARG_PREFIX, "*");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_16 = 0;
            if (!parseExpression(&__node_16))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            if (yytoken == Token_LINE_BREAK)
            {
                if (yytoken != Token_LINE_BREAK)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LINE_BREAK, "line break");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAssignmentExpression(AssignmentExpressionAst **yynode)
{
    *yynode = create<AssignmentExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        RangeExpressionAst *__node_17 = 0;
        if (!parseRangeExpression(&__node_17))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::RangeExpressionKind, "rangeExpression");
            }
            return false;
        }
        while (yytoken == Token_ASSIGN
               || yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE
               || yytoken == Token_BAND_ASSIGN
               || yytoken == Token_BOR_ASSIGN
               || yytoken == Token_BXOR_ASSIGN
               || yytoken == Token_DIV_ASSIGN
               || yytoken == Token_LEFT_SHIFT_ASSIGN
               || yytoken == Token_LOGICAL_AND_ASSIGN
               || yytoken == Token_LOGICAL_OR_ASSIGN
               || yytoken == Token_MINUS_ASSIGN
               || yytoken == Token_MOD_ASSIGN
               || yytoken == Token_PLUS_ASSIGN
               || yytoken == Token_POWER_ASSIGN
               || yytoken == Token_RIGHT_SHIFT_ASSIGN
               || yytoken == Token_STAR_ASSIGN)
        {
            if (yytoken == Token_ASSIGN
                || yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                OperatorAssignAst *__node_18 = 0;
                if (!parseOperatorAssign(&__node_18))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorAssignKind, "operatorAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_PLUS_ASSIGN)
            {
                OperatorPlusAssignAst *__node_19 = 0;
                if (!parseOperatorPlusAssign(&__node_19))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorPlusAssignKind, "operatorPlusAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_MINUS_ASSIGN)
            {
                OperatorMinusAssignAst *__node_20 = 0;
                if (!parseOperatorMinusAssign(&__node_20))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorMinusAssignKind, "operatorMinusAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_STAR_ASSIGN)
            {
                OperatorStarAssignAst *__node_21 = 0;
                if (!parseOperatorStarAssign(&__node_21))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorStarAssignKind, "operatorStarAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_DIV_ASSIGN)
            {
                OperatorDivAssignAst *__node_22 = 0;
                if (!parseOperatorDivAssign(&__node_22))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorDivAssignKind, "operatorDivAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_MOD_ASSIGN)
            {
                OperatorModAssignAst *__node_23 = 0;
                if (!parseOperatorModAssign(&__node_23))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorModAssignKind, "operatorModAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_POWER_ASSIGN)
            {
                OperatorPowerAssignAst *__node_24 = 0;
                if (!parseOperatorPowerAssign(&__node_24))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorPowerAssignKind, "operatorPowerAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_BAND_ASSIGN)
            {
                OperatorBAndAssignAst *__node_25 = 0;
                if (!parseOperatorBAndAssign(&__node_25))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorBAndAssignKind, "operatorBAndAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_BXOR_ASSIGN)
            {
                OperatorBXorAssignAst *__node_26 = 0;
                if (!parseOperatorBXorAssign(&__node_26))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorBXorAssignKind, "operatorBXorAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_BOR_ASSIGN)
            {
                OperatorBorAssignAst *__node_27 = 0;
                if (!parseOperatorBorAssign(&__node_27))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorBorAssignKind, "operatorBorAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_LEFT_SHIFT_ASSIGN)
            {
                OperatorLeftShiftAssignAst *__node_28 = 0;
                if (!parseOperatorLeftShiftAssign(&__node_28))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorLeftShiftAssignKind, "operatorLeftShiftAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_RIGHT_SHIFT_ASSIGN)
            {
                OperatorRightShiftAssignAst *__node_29 = 0;
                if (!parseOperatorRightShiftAssign(&__node_29))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorRightShiftAssignKind, "operatorRightShiftAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_LOGICAL_AND_ASSIGN)
            {
                OperatorLogicalAndAssignAst *__node_30 = 0;
                if (!parseOperatorLogicalAndAssign(&__node_30))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorLogicalAndAssignKind, "operatorLogicalAndAssign");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_LOGICAL_OR_ASSIGN)
            {
                OperatorLogicalOrAssignAst *__node_31 = 0;
                if (!parseOperatorLogicalOrAssign(&__node_31))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorLogicalOrAssignKind, "operatorLogicalOrAssign");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
            if (yytoken == Token_REST_ARG_PREFIX)
            {
                if (yytoken != Token_REST_ARG_PREFIX)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_REST_ARG_PREFIX, "*");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            RangeExpressionAst *__node_32 = 0;
            if (!parseRangeExpression(&__node_32))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::RangeExpressionKind, "rangeExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBlockContent(BlockContentAst **yynode)
{
    *yynode = create<BlockContentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BOR
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_END_UPCASE
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LINE_BREAK
        || yytoken == Token_LOGICAL_OR
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SEMI
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD || yytoken == Token_END
        || yytoken == Token_EOF
        || yytoken == Token_RCURLY)
    {
        if (yytoken == Token_BOR)
        {
            if (yytoken != Token_BOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BOR, "|");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BINARY
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                Block_varsAst *__node_33 = 0;
                if (!parseBlock_vars(&__node_33))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Block_varsKind, "block_vars");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_BOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BOR, "|");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LOGICAL_OR)
        {
            if (yytoken != Token_LOGICAL_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LOGICAL_OR, "||");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_ALIAS
            || yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_END_UPCASE
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LINE_BREAK
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SEMI
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            CompoundStatementAst *__node_34 = 0;
            if (!parseCompoundStatement(&__node_34))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBlockMethodDefinitionArgument(BlockMethodDefinitionArgumentAst **yynode)
{
    *yynode = create<BlockMethodDefinitionArgumentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if ((yytoken == Token_BAND) && ( expect_array_or_block_arguments ))
    {
        if (yytoken != Token_BAND)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BAND, "&");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FUNCTION)
        {
            if (yytoken != Token_FUNCTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNCTION, "function");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        expect_array_or_block_arguments = false;
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBlockMethodInvocationArgument(BlockMethodInvocationArgumentAst **yynode)
{
    *yynode = create<BlockMethodInvocationArgumentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BLOCK_ARG_PREFIX)
    {
        if (yytoken != Token_BLOCK_ARG_PREFIX)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BLOCK_ARG_PREFIX, "block argument prefix");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_35 = 0;
        if (!parseExpression(&__node_35))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBlock_var(Block_varAst **yynode)
{
    *yynode = create<Block_varAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        bool blockErrors_1 = blockErrors(true);
        qint64 try_startToken_1 = tokenStream->index() - 1;
        ParserState *try_startState_1 = copyCurrentState();
        {
            if (yytoken != Token_LPAREN)
                goto __catch_1;
            yylex();

            ElementReferenceAst *__node_36 = 0;
            if (!parseElementReference(&__node_36))
            {
                goto __catch_1;
            }
            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                    goto __catch_1;
                yylex();

                if (yytoken == Token_RPAREN) break;
                if (yytoken == Token_REST_ARG_PREFIX)
                {
                    if (yytoken != Token_REST_ARG_PREFIX)
                        goto __catch_1;
                    yylex();

                    seen_star = true;
                }
                else if (true /*epsilon*/)
                {
                    seen_star = false;
                }
                else
                {
                    goto __catch_1;
                }
                ElementReferenceAst *__node_37 = 0;
                if (!parseElementReference(&__node_37))
                {
                    goto __catch_1;
                }
                if (seen_star) break;
            }
            if (yytoken != Token_RPAREN)
                goto __catch_1;
            yylex();

        }
        blockErrors(blockErrors_1);
        if (try_startState_1)
            delete try_startState_1;

        if (false) // the only way to enter here is using goto
        {
__catch_1:
            if (try_startState_1)
            {
                restoreState(try_startState_1);
                delete try_startState_1;
            }
            blockErrors(blockErrors_1);
            rewind(try_startToken_1);

            if (yytoken == Token_REST_ARG_PREFIX)
            {
                if (yytoken != Token_REST_ARG_PREFIX)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_REST_ARG_PREFIX, "*");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_ASCII_VALUE
                    || yytoken == Token_BEGIN
                    || yytoken == Token_BINARY
                    || yytoken == Token_BREAK
                    || yytoken == Token_CASE
                    || yytoken == Token_CLASS
                    || yytoken == Token_CLASS_VARIABLE
                    || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                    || yytoken == Token_COMMAND_OUTPUT
                    || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                    || yytoken == Token_COMMENT
                    || yytoken == Token_CONSTANT
                    || yytoken == Token_DEF
                    || yytoken == Token_DEFINED
                    || yytoken == Token_DOUBLE_QUOTED_STRING
                    || yytoken == Token_FALSE
                    || yytoken == Token_FILE
                    || yytoken == Token_FLOAT
                    || yytoken == Token_FOR
                    || yytoken == Token_FUNCTION
                    || yytoken == Token_GLOBAL_VARIABLE
                    || yytoken == Token_HERE_DOC_BEGIN
                    || yytoken == Token_HEX
                    || yytoken == Token_IDENTIFIER
                    || yytoken == Token_IF
                    || yytoken == Token_INSTANCE_VARIABLE
                    || yytoken == Token_INTEGER
                    || yytoken == Token_LBRACK
                    || yytoken == Token_LCURLY_HASH
                    || yytoken == Token_LEADING_TWO_COLON
                    || yytoken == Token_LINE
                    || yytoken == Token_LPAREN
                    || yytoken == Token_MODULE
                    || yytoken == Token_NEXT
                    || yytoken == Token_NIL
                    || yytoken == Token_OCTAL
                    || yytoken == Token_REDO
                    || yytoken == Token_REGEX
                    || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                    || yytoken == Token_RETRY
                    || yytoken == Token_RETURN
                    || yytoken == Token_SELF
                    || yytoken == Token_SINGLE_QUOTED_STRING
                    || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                    || yytoken == Token_SUPER
                    || yytoken == Token_TRUE
                    || yytoken == Token_UNLESS
                    || yytoken == Token_UNTIL
                    || yytoken == Token_WHILE
                    || yytoken == Token_W_ARRAY
                    || yytoken == Token_YIELD)
                {
                    ElementReferenceAst *__node_38 = 0;
                    if (!parseElementReference(&__node_38))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::ElementReferenceKind, "elementReference");
                        }
                        return false;
                    }
                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
            }
            else if (yytoken == Token_ASCII_VALUE
                     || yytoken == Token_BEGIN
                     || yytoken == Token_BINARY
                     || yytoken == Token_BREAK
                     || yytoken == Token_CASE
                     || yytoken == Token_CLASS
                     || yytoken == Token_CLASS_VARIABLE
                     || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                     || yytoken == Token_COMMAND_OUTPUT
                     || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                     || yytoken == Token_COMMENT
                     || yytoken == Token_CONSTANT
                     || yytoken == Token_DEF
                     || yytoken == Token_DEFINED
                     || yytoken == Token_DOUBLE_QUOTED_STRING
                     || yytoken == Token_FALSE
                     || yytoken == Token_FILE
                     || yytoken == Token_FLOAT
                     || yytoken == Token_FOR
                     || yytoken == Token_FUNCTION
                     || yytoken == Token_GLOBAL_VARIABLE
                     || yytoken == Token_HERE_DOC_BEGIN
                     || yytoken == Token_HEX
                     || yytoken == Token_IDENTIFIER
                     || yytoken == Token_IF
                     || yytoken == Token_INSTANCE_VARIABLE
                     || yytoken == Token_INTEGER
                     || yytoken == Token_LBRACK
                     || yytoken == Token_LCURLY_HASH
                     || yytoken == Token_LEADING_TWO_COLON
                     || yytoken == Token_LINE
                     || yytoken == Token_LPAREN
                     || yytoken == Token_MODULE
                     || yytoken == Token_NEXT
                     || yytoken == Token_NIL
                     || yytoken == Token_OCTAL
                     || yytoken == Token_REDO
                     || yytoken == Token_REGEX
                     || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                     || yytoken == Token_RETRY
                     || yytoken == Token_RETURN
                     || yytoken == Token_SELF
                     || yytoken == Token_SINGLE_QUOTED_STRING
                     || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                     || yytoken == Token_SUPER
                     || yytoken == Token_TRUE
                     || yytoken == Token_UNLESS
                     || yytoken == Token_UNTIL
                     || yytoken == Token_WHILE
                     || yytoken == Token_W_ARRAY
                     || yytoken == Token_YIELD)
            {
                ElementReferenceAst *__node_39 = 0;
                if (!parseElementReference(&__node_39))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ElementReferenceKind, "elementReference");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBlock_vars(Block_varsAst **yynode)
{
    *yynode = create<Block_varsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        Block_varAst *__node_40 = 0;
        if (!parseBlock_var(&__node_40))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Block_varKind, "block_var");
            }
            return false;
        }
        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            if ((yytoken == Token_BOR) || (yytoken == Token_IN)) break;
            Block_varAst *__node_41 = 0;
            if (!parseBlock_var(&__node_41))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Block_varKind, "block_var");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBodyStatement(BodyStatementAst **yynode)
{
    *yynode = create<BodyStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_ELSE
        || yytoken == Token_END_UPCASE
        || yytoken == Token_ENSURE
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LINE_BREAK
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RESCUE
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SEMI
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD || yytoken == Token_END
        || yytoken == Token_EOF)
    {
        if (yytoken == Token_ALIAS
            || yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_END_UPCASE
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LINE_BREAK
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SEMI
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            CompoundStatementAst *__node_42 = 0;
            if (!parseCompoundStatement(&__node_42))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        while (yytoken == Token_RESCUE)
        {
            if (yytoken != Token_RESCUE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RESCUE, "rescue");
                }
                return false;
            }
            yylex();

            ExceptionListAst *__node_43 = 0;
            if (!parseExceptionList(&__node_43))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExceptionListKind, "exceptionList");
                }
                return false;
            }
            ThenOrTerminalOrColonAst *__node_44 = 0;
            if (!parseThenOrTerminalOrColon(&__node_44))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ThenOrTerminalOrColonKind, "thenOrTerminalOrColon");
                }
                return false;
            }
            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LINE_BREAK
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SEMI
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                CompoundStatementAst *__node_45 = 0;
                if (!parseCompoundStatement(&__node_45))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        if (yytoken == Token_ELSE)
        {
            if (yytoken != Token_ELSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELSE, "else");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LINE_BREAK
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SEMI
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                CompoundStatementAst *__node_46 = 0;
                if (!parseCompoundStatement(&__node_46))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_ENSURE)
        {
            if (yytoken != Token_ENSURE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ENSURE, "ensure");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LINE_BREAK
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SEMI
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                CompoundStatementAst *__node_47 = 0;
                if (!parseCompoundStatement(&__node_47))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCaseExpression(CaseExpressionAst **yynode)
{
    *yynode = create<CaseExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CASE)
    {
        if (yytoken != Token_CASE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CASE, "case");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ALIAS
            || yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_END_UPCASE
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LINE_BREAK
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SEMI
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            CompoundStatementAst *__node_48 = 0;
            if (!parseCompoundStatement(&__node_48))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        do
        {
            KeywordWhenAst *__node_49 = 0;
            if (!parseKeywordWhen(&__node_49))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordWhenKind, "keywordWhen");
                }
                return false;
            }
            MrhsAst *__node_50 = 0;
            if (!parseMrhs(&__node_50))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MrhsKind, "mrhs");
                }
                return false;
            }
            ThenOrTerminalOrColonAst *__node_51 = 0;
            if (!parseThenOrTerminalOrColon(&__node_51))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ThenOrTerminalOrColonKind, "thenOrTerminalOrColon");
                }
                return false;
            }
            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LINE_BREAK
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SEMI
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                CompoundStatementAst *__node_52 = 0;
                if (!parseCompoundStatement(&__node_52))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        while (yytoken == Token_WHEN);
        if (yytoken == Token_ELSE)
        {
            if (yytoken != Token_ELSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELSE, "else");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LINE_BREAK
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SEMI
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                CompoundStatementAst *__node_53 = 0;
                if (!parseCompoundStatement(&__node_53))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassDefinition(ClassDefinitionAst **yynode)
{
    *yynode = create<ClassDefinitionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CLASS)
    {
        KeywordClassAst *__node_54 = 0;
        if (!parseKeywordClass(&__node_54))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::KeywordClassKind, "keywordClass");
            }
            return false;
        }
        if (yytoken == Token_CONSTANT
            || yytoken == Token_FUNCTION
            || yytoken == Token_LEADING_TWO_COLON)
        {
            ClassNameAst *__node_55 = 0;
            if (!parseClassName(&__node_55))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassNameKind, "className");
                }
                return false;
            }
            if (yytoken == Token_LESS_THAN)
            {
                if (yytoken != Token_LESS_THAN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LESS_THAN, "<");
                    }
                    return false;
                }
                yylex();

                ExpressionAst *__node_56 = 0;
                if (!parseExpression(&__node_56))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_LEFT_SHIFT)
        {
            if (yytoken != Token_LEFT_SHIFT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LEFT_SHIFT, "<<");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_57 = 0;
            if (!parseExpression(&__node_57))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
        TerminalAst *__node_58 = 0;
        if (!parseTerminal(&__node_58))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TerminalKind, "terminal");
            }
            return false;
        }
        BodyStatementAst *__node_59 = 0;
        if (!parseBodyStatement(&__node_59))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BodyStatementKind, "bodyStatement");
            }
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassName(ClassNameAst **yynode)
{
    *yynode = create<ClassNameAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CONSTANT
        || yytoken == Token_FUNCTION
        || yytoken == Token_LEADING_TWO_COLON)
    {
        if (yytoken == Token_CONSTANT)
        {
            if (yytoken != Token_CONSTANT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONSTANT, "constant");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FUNCTION)
        {
            if (yytoken != Token_FUNCTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNCTION, "function");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LEADING_TWO_COLON)
        {
            if (yytoken != Token_LEADING_TWO_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LEADING_TWO_COLON, "::");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_FUNCTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNCTION, "function");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        while (yytoken == Token_TWO_COLON)
        {
            if (yytoken != Token_TWO_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TWO_COLON, "::");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_FUNCTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNCTION, "function");
                }
                return false;
            }
            yylex();

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCodeBlock(CodeBlockAst **yynode)
{
    *yynode = create<CodeBlockAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DO
        || yytoken == Token_LCURLY_BLOCK)
    {
        if (yytoken == Token_DO)
        {
            KeywordDoAst *__node_60 = 0;
            if (!parseKeywordDo(&__node_60))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordDoKind, "keywordDo");
                }
                return false;
            }
            BlockContentAst *__node_61 = 0;
            if (!parseBlockContent(&__node_61))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockContentKind, "blockContent");
                }
                return false;
            }
            if (yytoken != Token_END)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_END, "end");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LCURLY_BLOCK)
        {
            if (yytoken != Token_LCURLY_BLOCK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LCURLY_BLOCK, "{");
                }
                return false;
            }
            yylex();

            BlockContentAst *__node_62 = 0;
            if (!parseBlockContent(&__node_62))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockContentKind, "blockContent");
                }
                return false;
            }
            if (yytoken != Token_RCURLY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RCURLY, "}");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseColonAccess(ColonAccessAst **yynode)
{
    *yynode = create<ColonAccessAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NIL
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        MethodCallAst *__node_63 = 0;
        if (!parseMethodCall(&__node_63))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::MethodCallKind, "methodCall");
            }
            return false;
        }
        while (yytoken == Token_TWO_COLON)
        {
            if (yytoken != Token_TWO_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TWO_COLON, "::");
                }
                return false;
            }
            yylex();

            MethodCallAst *__node_64 = 0;
            if (!parseMethodCall(&__node_64))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MethodCallKind, "methodCall");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCommand(CommandAst **yynode)
{
    *yynode = create<CommandAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NIL
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_RETRY
            || yytoken == Token_SELF
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            ColonAccessAst *__node_65 = 0;
            if (!parseColonAccess(&__node_65))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ColonAccessKind, "colonAccess");
                }
                return false;
            }
            if ((yytoken == Token_ASCII_VALUE
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BINARY
                 || yytoken == Token_BLOCK_ARG_PREFIX
                 || yytoken == Token_BNOT
                 || yytoken == Token_BREAK
                 || yytoken == Token_CASE
                 || yytoken == Token_CLASS
                 || yytoken == Token_CLASS_VARIABLE
                 || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                 || yytoken == Token_COMMAND_OUTPUT
                 || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_COMMENT
                 || yytoken == Token_CONSTANT
                 || yytoken == Token_DEF
                 || yytoken == Token_DEFINED
                 || yytoken == Token_DOUBLE_QUOTED_STRING
                 || yytoken == Token_FALSE
                 || yytoken == Token_FILE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_FOR
                 || yytoken == Token_FUNCTION
                 || yytoken == Token_GLOBAL_VARIABLE
                 || yytoken == Token_HERE_DOC_BEGIN
                 || yytoken == Token_HEX
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_IF
                 || yytoken == Token_INSTANCE_VARIABLE
                 || yytoken == Token_INTEGER
                 || yytoken == Token_KEYWORD_NOT
                 || yytoken == Token_LBRACK
                 || yytoken == Token_LCURLY_HASH
                 || yytoken == Token_LEADING_TWO_COLON
                 || yytoken == Token_LINE
                 || yytoken == Token_LPAREN
                 || yytoken == Token_MODULE
                 || yytoken == Token_NEXT
                 || yytoken == Token_NIL
                 || yytoken == Token_NOT
                 || yytoken == Token_OCTAL
                 || yytoken == Token_REDO
                 || yytoken == Token_REGEX
                 || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_REST_ARG_PREFIX
                 || yytoken == Token_RETRY
                 || yytoken == Token_RETURN
                 || yytoken == Token_SELF
                 || yytoken == Token_SINGLE_QUOTED_STRING
                 || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_SUPER
                 || yytoken == Token_TRUE
                 || yytoken == Token_UNARY_MINUS
                 || yytoken == Token_UNARY_PLUS
                 || yytoken == Token_UNLESS
                 || yytoken == Token_UNTIL
                 || yytoken == Token_WHILE
                 || yytoken == Token_W_ARRAY
                 || yytoken == Token_YIELD) && ( !seen_rparen ))
            {
                MethodInvocationArgumentWithoutParenAst *__node_66 = 0;
                if (!parseMethodInvocationArgumentWithoutParen(&__node_66))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::MethodInvocationArgumentWithoutParenKind, "methodInvocationArgumentWithoutParen");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken == Token_DO
                || yytoken == Token_LCURLY_BLOCK)
            {
                CodeBlockAst *__node_67 = 0;
                if (!parseCodeBlock(&__node_67))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CodeBlockKind, "codeBlock");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            seen_rparen = false;
        }
        else if (yytoken == Token_BREAK
                 || yytoken == Token_NEXT
                 || yytoken == Token_RETURN)
        {
            if (yytoken == Token_RETURN)
            {
                if (yytoken != Token_RETURN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RETURN, "return");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_BREAK)
            {
                if (yytoken != Token_BREAK)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_BREAK, "break");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_NEXT)
            {
                if (yytoken != Token_NEXT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_NEXT, "next");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            if (yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BINARY
                || yytoken == Token_BLOCK_ARG_PREFIX
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                MethodInvocationArgumentWithoutParenAst *__node_68 = 0;
                if (!parseMethodInvocationArgumentWithoutParen(&__node_68))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::MethodInvocationArgumentWithoutParenKind, "methodInvocationArgumentWithoutParen");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            seen_rparen = false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCommandOutput(CommandOutputAst **yynode)
{
    *yynode = create<CommandOutputAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION)
    {
        if (yytoken == Token_COMMAND_OUTPUT)
        {
            if (yytoken != Token_COMMAND_OUTPUT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMAND_OUTPUT, "command output");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION)
        {
            if (yytoken != Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION, "command output before expression substitution");
                }
                return false;
            }
            yylex();

            ExpressionSubstitutionAst *__node_69 = 0;
            if (!parseExpressionSubstitution(&__node_69))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionSubstitutionKind, "expressionSubstitution");
                }
                return false;
            }
            while (yytoken == Token_STRING_BETWEEN_EXPRESSION_SUBSTITUTION)
            {
                if (yytoken != Token_STRING_BETWEEN_EXPRESSION_SUBSTITUTION)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STRING_BETWEEN_EXPRESSION_SUBSTITUTION, "string between expression substitution");
                    }
                    return false;
                }
                yylex();

                ExpressionSubstitutionAst *__node_70 = 0;
                if (!parseExpressionSubstitution(&__node_70))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionSubstitutionKind, "expressionSubstitution");
                    }
                    return false;
                }
            }
            if (yytoken != Token_STRING_AFTER_EXPRESSION_SUBSTITUTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING_AFTER_EXPRESSION_SUBSTITUTION, "string after expression substitution");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCompoundStatement(CompoundStatementAst **yynode)
{
    *yynode = create<CompoundStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_END_UPCASE
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LINE_BREAK
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SEMI
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_LINE_BREAK
            || yytoken == Token_SEMI)
        {
            TerminalAst *__node_71 = 0;
            if (!parseTerminal(&__node_71))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TerminalKind, "terminal");
                }
                return false;
            }
            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                StatementsAst *__node_72 = 0;
                if (!parseStatements(&__node_72))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::StatementsKind, "statements");
                    }
                    return false;
                }
                (*yynode)->statements = __node_72;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_ALIAS
                 || yytoken == Token_ASCII_VALUE
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BEGIN_UPCASE
                 || yytoken == Token_BINARY
                 || yytoken == Token_BNOT
                 || yytoken == Token_BREAK
                 || yytoken == Token_CASE
                 || yytoken == Token_CLASS
                 || yytoken == Token_CLASS_VARIABLE
                 || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                 || yytoken == Token_COMMAND_OUTPUT
                 || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_COMMENT
                 || yytoken == Token_CONSTANT
                 || yytoken == Token_DEF
                 || yytoken == Token_DEFINED
                 || yytoken == Token_DOUBLE_QUOTED_STRING
                 || yytoken == Token_END_UPCASE
                 || yytoken == Token_FALSE
                 || yytoken == Token_FILE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_FOR
                 || yytoken == Token_FUNCTION
                 || yytoken == Token_GLOBAL_VARIABLE
                 || yytoken == Token_HERE_DOC_BEGIN
                 || yytoken == Token_HEX
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_IF
                 || yytoken == Token_INSTANCE_VARIABLE
                 || yytoken == Token_INTEGER
                 || yytoken == Token_KEYWORD_NOT
                 || yytoken == Token_LBRACK
                 || yytoken == Token_LCURLY_HASH
                 || yytoken == Token_LEADING_TWO_COLON
                 || yytoken == Token_LINE
                 || yytoken == Token_LPAREN
                 || yytoken == Token_MODULE
                 || yytoken == Token_NEXT
                 || yytoken == Token_NIL
                 || yytoken == Token_NOT
                 || yytoken == Token_OCTAL
                 || yytoken == Token_REDO
                 || yytoken == Token_REGEX
                 || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_REST_ARG_PREFIX
                 || yytoken == Token_RETRY
                 || yytoken == Token_RETURN
                 || yytoken == Token_SELF
                 || yytoken == Token_SINGLE_QUOTED_STRING
                 || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_SUPER
                 || yytoken == Token_TRUE
                 || yytoken == Token_UNARY_MINUS
                 || yytoken == Token_UNARY_PLUS
                 || yytoken == Token_UNDEF
                 || yytoken == Token_UNLESS
                 || yytoken == Token_UNTIL
                 || yytoken == Token_WHILE
                 || yytoken == Token_W_ARRAY
                 || yytoken == Token_YIELD)
        {
            StatementsAst *__node_73 = 0;
            if (!parseStatements(&__node_73))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementsKind, "statements");
                }
                return false;
            }
            (*yynode)->statements = __node_73;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDoOrTerminalOrColon(DoOrTerminalOrColonAst **yynode)
{
    *yynode = create<DoOrTerminalOrColonAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COLON
        || yytoken == Token_DO_IN_CONDITION
        || yytoken == Token_LINE_BREAK
        || yytoken == Token_SEMI)
    {
        if (yytoken == Token_DO_IN_CONDITION)
        {
            if (yytoken != Token_DO_IN_CONDITION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DO_IN_CONDITION, "do in condition");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LINE_BREAK
                 || yytoken == Token_SEMI)
        {
            TerminalAst *__node_74 = 0;
            if (!parseTerminal(&__node_74))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TerminalKind, "terminal");
                }
                return false;
            }
        }
        else if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDotAccess(DotAccessAst **yynode)
{
    *yynode = create<DotAccessAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        ElementReferenceAst *__node_75 = 0;
        if (!parseElementReference(&__node_75))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ElementReferenceKind, "elementReference");
            }
            return false;
        }
        while (yytoken == Token_DOT)
        {
            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            ElementReferenceAst *__node_76 = 0;
            if (!parseElementReference(&__node_76))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ElementReferenceKind, "elementReference");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseElementReference(ElementReferenceAst **yynode)
{
    *yynode = create<ElementReferenceAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        CommandAst *__node_77 = 0;
        if (!parseCommand(&__node_77))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::CommandKind, "command");
            }
            return false;
        }
        while (yytoken == Token_LBRACK_ARRAY_ACCESS)
        {
            ArrayAccessAst *__node_78 = 0;
            if (!parseArrayAccess(&__node_78))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ArrayAccessKind, "arrayAccess");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEqualityExpression(EqualityExpressionAst **yynode)
{
    *yynode = create<EqualityExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        RelationalExpressionAst *__node_79 = 0;
        if (!parseRelationalExpression(&__node_79))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::RelationalExpressionKind, "relationalExpression");
            }
            return false;
        }
        while (yytoken == Token_CASE_EQUAL
               || yytoken == Token_COMPARE
               || yytoken == Token_EQUAL
               || yytoken == Token_MATCH
               || yytoken == Token_NOT_EQUAL
               || yytoken == Token_NOT_MATCH)
        {
            if (yytoken == Token_COMPARE)
            {
                OperatorCompareAst *__node_80 = 0;
                if (!parseOperatorCompare(&__node_80))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorCompareKind, "operatorCompare");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_EQUAL)
            {
                OperatorEqualAst *__node_81 = 0;
                if (!parseOperatorEqual(&__node_81))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorEqualKind, "operatorEqual");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_CASE_EQUAL)
            {
                OperatorCaseEqualAst *__node_82 = 0;
                if (!parseOperatorCaseEqual(&__node_82))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorCaseEqualKind, "operatorCaseEqual");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_NOT_EQUAL)
            {
                OperatorNotEqualAst *__node_83 = 0;
                if (!parseOperatorNotEqual(&__node_83))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorNotEqualKind, "operatorNotEqual");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_MATCH)
            {
                OperatorMatchAst *__node_84 = 0;
                if (!parseOperatorMatch(&__node_84))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorMatchKind, "operatorMatch");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_NOT_MATCH)
            {
                OperatorNotMatchAst *__node_85 = 0;
                if (!parseOperatorNotMatch(&__node_85))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorNotMatchKind, "operatorNotMatch");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
            RelationalExpressionAst *__node_86 = 0;
            if (!parseRelationalExpression(&__node_86))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::RelationalExpressionKind, "relationalExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExceptionHandlingExpression(ExceptionHandlingExpressionAst **yynode)
{
    *yynode = create<ExceptionHandlingExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BEGIN)
    {
        if (yytoken != Token_BEGIN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BEGIN, "begin");
            }
            return false;
        }
        yylex();

        BodyStatementAst *__node_87 = 0;
        if (!parseBodyStatement(&__node_87))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BodyStatementKind, "bodyStatement");
            }
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExceptionList(ExceptionListAst **yynode)
{
    *yynode = create<ExceptionListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASSOC
        || yytoken == Token_CONSTANT
        || yytoken == Token_FUNCTION
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_LEADING_TWO_COLON || yytoken == Token_COLON
        || yytoken == Token_EOF
        || yytoken == Token_LINE_BREAK
        || yytoken == Token_SEMI
        || yytoken == Token_THEN)
    {
        if (yytoken == Token_CONSTANT
            || yytoken == Token_FUNCTION
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_LEADING_TWO_COLON)
        {
            if (yytoken == Token_CONSTANT
                || yytoken == Token_FUNCTION
                || yytoken == Token_LEADING_TWO_COLON)
            {
                ClassNameAst *__node_88 = 0;
                if (!parseClassName(&__node_88))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassNameKind, "className");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_INSTANCE_VARIABLE)
            {
                if (yytoken != Token_INSTANCE_VARIABLE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_INSTANCE_VARIABLE, "instance variable");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_CONSTANT
                    || yytoken == Token_FUNCTION
                    || yytoken == Token_LEADING_TWO_COLON)
                {
                    ClassNameAst *__node_89 = 0;
                    if (!parseClassName(&__node_89))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::ClassNameKind, "className");
                        }
                        return false;
                    }
                }
                else if (yytoken == Token_INSTANCE_VARIABLE)
                {
                    if (yytoken != Token_INSTANCE_VARIABLE)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_INSTANCE_VARIABLE, "instance variable");
                        }
                        return false;
                    }
                    yylex();

                }
                else
                {
                    return false;
                }
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_ASSOC)
        {
            if (yytoken != Token_ASSOC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSOC, "=>");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_IDENTIFIER)
            {
                if (yytoken != Token_IDENTIFIER)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_FUNCTION)
            {
                if (yytoken != Token_FUNCTION)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FUNCTION, "function");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpression(ExpressionAst **yynode)
{
    *yynode = create<ExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        AndorExpressionAst *__node_90 = 0;
        if (!parseAndorExpression(&__node_90))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AndorExpressionKind, "andorExpression");
            }
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpressionSubstitution(ExpressionSubstitutionAst **yynode)
{
    *yynode = create<ExpressionSubstitutionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_LCURLY_BLOCK)
    {
        if (yytoken == Token_LCURLY_BLOCK)
        {
            if (yytoken != Token_LCURLY_BLOCK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LCURLY_BLOCK, "{");
                }
                return false;
            }
            yylex();

            CompoundStatementAst *__node_91 = 0;
            if (!parseCompoundStatement(&__node_91))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
            if (yytoken != Token_RCURLY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RCURLY, "}");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_GLOBAL_VARIABLE)
        {
            if (yytoken != Token_GLOBAL_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GLOBAL_VARIABLE, "global variable");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_INSTANCE_VARIABLE)
        {
            if (yytoken != Token_INSTANCE_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INSTANCE_VARIABLE, "instance variable");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CLASS_VARIABLE)
        {
            if (yytoken != Token_CLASS_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CLASS_VARIABLE, "class variable");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForExpression(ForExpressionAst **yynode)
{
    *yynode = create<ForExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_FOR)
    {
        KeywordForAst *__node_92 = 0;
        if (!parseKeywordFor(&__node_92))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::KeywordForKind, "keywordFor");
            }
            return false;
        }
        Block_varsAst *__node_93 = 0;
        if (!parseBlock_vars(&__node_93))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Block_varsKind, "block_vars");
            }
            return false;
        }
        KeywordInAst *__node_94 = 0;
        if (!parseKeywordIn(&__node_94))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::KeywordInKind, "keywordIn");
            }
            return false;
        }
        ExpressionAst *__node_95 = 0;
        if (!parseExpression(&__node_95))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        DoOrTerminalOrColonAst *__node_96 = 0;
        if (!parseDoOrTerminalOrColon(&__node_96))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::DoOrTerminalOrColonKind, "doOrTerminalOrColon");
            }
            return false;
        }
        if (yytoken == Token_ALIAS
            || yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_END_UPCASE
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LINE_BREAK
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SEMI
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            CompoundStatementAst *__node_97 = 0;
            if (!parseCompoundStatement(&__node_97))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseHashExpression(HashExpressionAst **yynode)
{
    *yynode = create<HashExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LCURLY_HASH)
    {
        if (yytoken != Token_LCURLY_HASH)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LCURLY_HASH, "{");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            KeyValuePairAst *__node_98 = 0;
            if (!parseKeyValuePair(&__node_98))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeyValuePairKind, "keyValuePair");
                }
                return false;
            }
            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                KeyValuePairAst *__node_99 = 0;
                if (!parseKeyValuePair(&__node_99))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::KeyValuePairKind, "keyValuePair");
                    }
                    return false;
                }
            }
            if (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RCURLY)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RCURLY, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseIfExpression(IfExpressionAst **yynode)
{
    *yynode = create<IfExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IF)
    {
        if (yytoken != Token_IF)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_IF, "if");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_100 = 0;
        if (!parseExpression(&__node_100))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        ThenOrTerminalOrColonAst *__node_101 = 0;
        if (!parseThenOrTerminalOrColon(&__node_101))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ThenOrTerminalOrColonKind, "thenOrTerminalOrColon");
            }
            return false;
        }
        if (yytoken == Token_ALIAS
            || yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_END_UPCASE
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LINE_BREAK
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SEMI
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            CompoundStatementAst *__node_102 = 0;
            if (!parseCompoundStatement(&__node_102))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        while (yytoken == Token_ELSIF)
        {
            if (yytoken != Token_ELSIF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELSIF, "elsif");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                ExpressionAst *__node_103 = 0;
                if (!parseExpression(&__node_103))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            ThenOrTerminalOrColonAst *__node_104 = 0;
            if (!parseThenOrTerminalOrColon(&__node_104))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ThenOrTerminalOrColonKind, "thenOrTerminalOrColon");
                }
                return false;
            }
            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LINE_BREAK
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SEMI
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                CompoundStatementAst *__node_105 = 0;
                if (!parseCompoundStatement(&__node_105))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        if (yytoken == Token_ELSE)
        {
            if (yytoken != Token_ELSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELSE, "else");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LINE_BREAK
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SEMI
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                CompoundStatementAst *__node_106 = 0;
                if (!parseCompoundStatement(&__node_106))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeyValuePair(KeyValuePairAst **yynode)
{
    *yynode = create<KeyValuePairAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        ExpressionAst *__node_107 = 0;
        if (!parseExpression(&__node_107))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        if (yytoken == Token_ASSOC)
        {
            if (yytoken != Token_ASSOC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSOC, "=>");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_108 = 0;
            if (!parseExpression(&__node_108))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeyword(KeywordAst **yynode)
{
    *yynode = create<KeywordAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_AND
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DO
        || yytoken == Token_ELSE
        || yytoken == Token_ELSIF
        || yytoken == Token_END
        || yytoken == Token_END_UPCASE
        || yytoken == Token_ENSURE
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FOR
        || yytoken == Token_IF
        || yytoken == Token_IN
        || yytoken == Token_LINE
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OR
        || yytoken == Token_REDO
        || yytoken == Token_RESCUE
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SUPER
        || yytoken == Token_THEN
        || yytoken == Token_TRUE
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHEN
        || yytoken == Token_WHILE
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_ALIAS
            || yytoken == Token_AND
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DO
            || yytoken == Token_ELSE
            || yytoken == Token_ELSIF
            || yytoken == Token_END
            || yytoken == Token_END_UPCASE
            || yytoken == Token_ENSURE
            || yytoken == Token_FOR
            || yytoken == Token_IF
            || yytoken == Token_IN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NOT
            || yytoken == Token_OR
            || yytoken == Token_REDO
            || yytoken == Token_RESCUE
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SUPER
            || yytoken == Token_THEN
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHEN
            || yytoken == Token_WHILE
            || yytoken == Token_YIELD)
        {
            KeywordAsMethodNameAst *__node_109 = 0;
            if (!parseKeywordAsMethodName(&__node_109))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordAsMethodNameKind, "keywordAsMethodName");
                }
                return false;
            }
        }
        else if (yytoken == Token_NIL)
        {
            if (yytoken != Token_NIL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_NIL, "nil");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SELF)
        {
            if (yytoken != Token_SELF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SELF, "self");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_TRUE)
        {
            if (yytoken != Token_TRUE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TRUE, "true");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FALSE)
        {
            if (yytoken != Token_FALSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FALSE, "false");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FILE)
        {
            if (yytoken != Token_FILE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FILE, "__FILE__");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LINE)
        {
            if (yytoken != Token_LINE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE, "__LINE__");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordAlias(KeywordAliasAst **yynode)
{
    *yynode = create<KeywordAliasAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS)
    {
        if (yytoken != Token_ALIAS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ALIAS, "alias");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordAnd(KeywordAndAst **yynode)
{
    *yynode = create<KeywordAndAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND)
    {
        if (yytoken != Token_AND)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_AND, "and");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordAsMethodName(KeywordAsMethodNameAst **yynode)
{
    *yynode = create<KeywordAsMethodNameAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_AND
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DO
        || yytoken == Token_ELSE
        || yytoken == Token_ELSIF
        || yytoken == Token_END
        || yytoken == Token_END_UPCASE
        || yytoken == Token_ENSURE
        || yytoken == Token_FOR
        || yytoken == Token_IF
        || yytoken == Token_IN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NOT
        || yytoken == Token_OR
        || yytoken == Token_REDO
        || yytoken == Token_RESCUE
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SUPER
        || yytoken == Token_THEN
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHEN
        || yytoken == Token_WHILE
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_AND)
        {
            if (yytoken != Token_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_AND, "and");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DEF)
        {
            if (yytoken != Token_DEF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DEF, "def");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_END)
        {
            if (yytoken != Token_END)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_END, "end");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IN)
        {
            if (yytoken != Token_IN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IN, "in");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_OR)
        {
            if (yytoken != Token_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OR, "or");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_UNLESS)
        {
            if (yytoken != Token_UNLESS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNLESS, "unless");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BEGIN)
        {
            if (yytoken != Token_BEGIN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BEGIN, "begin");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DEFINED)
        {
            if (yytoken != Token_DEFINED)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DEFINED, "defined?");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ENSURE)
        {
            if (yytoken != Token_ENSURE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ENSURE, "ensure");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MODULE)
        {
            if (yytoken != Token_MODULE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MODULE, "module");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_REDO)
        {
            if (yytoken != Token_REDO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REDO, "redo");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SUPER)
        {
            if (yytoken != Token_SUPER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SUPER, "super");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_UNTIL)
        {
            if (yytoken != Token_UNTIL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNTIL, "until");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BEGIN_UPCASE)
        {
            if (yytoken != Token_BEGIN_UPCASE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BEGIN_UPCASE, "BEGIN");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BREAK)
        {
            if (yytoken != Token_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BREAK, "break");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DO)
        {
            if (yytoken != Token_DO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DO, "do");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_NEXT)
        {
            if (yytoken != Token_NEXT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_NEXT, "next");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_RESCUE)
        {
            if (yytoken != Token_RESCUE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RESCUE, "rescue");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_THEN)
        {
            if (yytoken != Token_THEN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_THEN, "then");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_WHEN)
        {
            if (yytoken != Token_WHEN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_WHEN, "when");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_END_UPCASE)
        {
            if (yytoken != Token_END_UPCASE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_END_UPCASE, "END");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CASE)
        {
            if (yytoken != Token_CASE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CASE, "case");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ELSE)
        {
            if (yytoken != Token_ELSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELSE, "else");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FOR)
        {
            if (yytoken != Token_FOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FOR, "for");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_RETRY)
        {
            if (yytoken != Token_RETRY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RETRY, "retry");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_WHILE)
        {
            if (yytoken != Token_WHILE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_WHILE, "while");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ALIAS)
        {
            if (yytoken != Token_ALIAS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ALIAS, "alias");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CLASS)
        {
            if (yytoken != Token_CLASS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CLASS, "class");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ELSIF)
        {
            if (yytoken != Token_ELSIF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELSIF, "elsif");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IF)
        {
            if (yytoken != Token_IF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IF, "if");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_NOT)
        {
            if (yytoken != Token_NOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_NOT, "!");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_RETURN)
        {
            if (yytoken != Token_RETURN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RETURN, "return");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_UNDEF)
        {
            if (yytoken != Token_UNDEF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNDEF, "undef");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_YIELD)
        {
            if (yytoken != Token_YIELD)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_YIELD, "yield");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordBeginUpcase(KeywordBeginUpcaseAst **yynode)
{
    *yynode = create<KeywordBeginUpcaseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BEGIN_UPCASE)
    {
        if (yytoken != Token_BEGIN_UPCASE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BEGIN_UPCASE, "BEGIN");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordBreak(KeywordBreakAst **yynode)
{
    *yynode = create<KeywordBreakAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BREAK)
    {
        if (yytoken != Token_BREAK)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BREAK, "break");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordClass(KeywordClassAst **yynode)
{
    *yynode = create<KeywordClassAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CLASS)
    {
        if (yytoken != Token_CLASS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CLASS, "class");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordDef(KeywordDefAst **yynode)
{
    *yynode = create<KeywordDefAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DEF)
    {
        if (yytoken != Token_DEF)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DEF, "def");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordDefined(KeywordDefinedAst **yynode)
{
    *yynode = create<KeywordDefinedAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DEFINED)
    {
        if (yytoken != Token_DEFINED)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DEFINED, "defined?");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordDo(KeywordDoAst **yynode)
{
    *yynode = create<KeywordDoAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DO)
    {
        if (yytoken != Token_DO)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DO, "do");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordEndUpcase(KeywordEndUpcaseAst **yynode)
{
    *yynode = create<KeywordEndUpcaseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_END_UPCASE)
    {
        if (yytoken != Token_END_UPCASE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END_UPCASE, "END");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordFor(KeywordForAst **yynode)
{
    *yynode = create<KeywordForAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_FOR)
    {
        if (yytoken != Token_FOR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_FOR, "for");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordIn(KeywordInAst **yynode)
{
    *yynode = create<KeywordInAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IN)
    {
        if (yytoken != Token_IN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_IN, "in");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordModule(KeywordModuleAst **yynode)
{
    *yynode = create<KeywordModuleAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MODULE)
    {
        if (yytoken != Token_MODULE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_MODULE, "module");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordNot(KeywordNotAst **yynode)
{
    *yynode = create<KeywordNotAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_KEYWORD_NOT)
    {
        if (yytoken != Token_KEYWORD_NOT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_KEYWORD_NOT, "not");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordOr(KeywordOrAst **yynode)
{
    *yynode = create<KeywordOrAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_OR)
    {
        if (yytoken != Token_OR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_OR, "or");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordUndef(KeywordUndefAst **yynode)
{
    *yynode = create<KeywordUndefAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNDEF)
    {
        if (yytoken != Token_UNDEF)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_UNDEF, "undef");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordUntil(KeywordUntilAst **yynode)
{
    *yynode = create<KeywordUntilAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNTIL)
    {
        if (yytoken != Token_UNTIL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_UNTIL, "until");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordWhen(KeywordWhenAst **yynode)
{
    *yynode = create<KeywordWhenAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_WHEN)
    {
        if (yytoken != Token_WHEN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_WHEN, "when");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseKeywordWhile(KeywordWhileAst **yynode)
{
    *yynode = create<KeywordWhileAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_WHILE)
    {
        if (yytoken != Token_WHILE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_WHILE, "while");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLiteral(LiteralAst **yynode)
{
    *yynode = create<LiteralAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_W_ARRAY)
    {
        if (yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION)
        {
            RegexAst *__node_110 = 0;
            if (!parseRegex(&__node_110))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::RegexKind, "regex");
                }
                return false;
            }
        }
        else if (yytoken == Token_DOUBLE_QUOTED_STRING
                 || yytoken == Token_SINGLE_QUOTED_STRING
                 || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION)
        {
            do
            {
                StringAst *__node_111 = 0;
                if (!parseString(&__node_111))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::StringKind, "string");
                    }
                    return false;
                }
            }
            while (yytoken == Token_DOUBLE_QUOTED_STRING
                   || yytoken == Token_SINGLE_QUOTED_STRING
                   || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION);
        }
        else if (yytoken == Token_HERE_DOC_BEGIN)
        {
            if (yytoken != Token_HERE_DOC_BEGIN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_HERE_DOC_BEGIN, "here document beginning");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_COMMAND_OUTPUT
                 || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION)
        {
            CommandOutputAst *__node_112 = 0;
            if (!parseCommandOutput(&__node_112))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CommandOutputKind, "commandOutput");
                }
                return false;
            }
        }
        else if (yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE)
        {
            SymbolAst *__node_113 = 0;
            if (!parseSymbol(&__node_113))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SymbolKind, "symbol");
                }
                return false;
            }
        }
        else if (yytoken == Token_W_ARRAY)
        {
            if (yytoken != Token_W_ARRAY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_W_ARRAY, "%w{} array");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLogicalAndExpression(LogicalAndExpressionAst **yynode)
{
    *yynode = create<LogicalAndExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        EqualityExpressionAst *__node_114 = 0;
        if (!parseEqualityExpression(&__node_114))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::EqualityExpressionKind, "equalityExpression");
            }
            return false;
        }
        while (yytoken == Token_LOGICAL_AND)
        {
            OperatorLogicalAndAst *__node_115 = 0;
            if (!parseOperatorLogicalAnd(&__node_115))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorLogicalAndKind, "operatorLogicalAnd");
                }
                return false;
            }
            EqualityExpressionAst *__node_116 = 0;
            if (!parseEqualityExpression(&__node_116))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EqualityExpressionKind, "equalityExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLogicalOrExpression(LogicalOrExpressionAst **yynode)
{
    *yynode = create<LogicalOrExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        LogicalAndExpressionAst *__node_117 = 0;
        if (!parseLogicalAndExpression(&__node_117))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LogicalAndExpressionKind, "logicalAndExpression");
            }
            return false;
        }
        while (yytoken == Token_LOGICAL_OR)
        {
            OperatorLogicalOrAst *__node_118 = 0;
            if (!parseOperatorLogicalOr(&__node_118))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorLogicalOrKind, "operatorLogicalOr");
                }
                return false;
            }
            LogicalAndExpressionAst *__node_119 = 0;
            if (!parseLogicalAndExpression(&__node_119))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::LogicalAndExpressionKind, "logicalAndExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodCall(MethodCallAst **yynode)
{
    *yynode = create<MethodCallAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NIL
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        PrimaryExpressionAst *__node_120 = 0;
        if (!parsePrimaryExpression(&__node_120))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::PrimaryExpressionKind, "primaryExpression");
            }
            return false;
        }
        if (yytoken == Token_LPAREN)
        {
            MethodInvocationArgumentWithParenAst *__node_121 = 0;
            if (!parseMethodInvocationArgumentWithParen(&__node_121))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MethodInvocationArgumentWithParenKind, "methodInvocationArgumentWithParen");
                }
                return false;
            }
            seen_rparen = true;
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodDefinition(MethodDefinitionAst **yynode)
{
    *yynode = create<MethodDefinitionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DEF)
    {
        KeywordDefAst *__node_122 = 0;
        if (!parseKeywordDef(&__node_122))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::KeywordDefKind, "keywordDef");
            }
            return false;
        }
        MethodNameAst *__node_123 = 0;
        if (!parseMethodName(&__node_123))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::MethodNameKind, "methodName");
            }
            return false;
        }
        MethodDefinitionArgumentAst *__node_124 = 0;
        if (!parseMethodDefinitionArgument(&__node_124))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::MethodDefinitionArgumentKind, "methodDefinitionArgument");
            }
            return false;
        }
        BodyStatementAst *__node_125 = 0;
        if (!parseBodyStatement(&__node_125))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BodyStatementKind, "bodyStatement");
            }
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodDefinitionArgument(MethodDefinitionArgumentAst **yynode)
{
    *yynode = create<MethodDefinitionArgumentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BAND
        || yytoken == Token_FUNCTION
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LINE_BREAK
        || yytoken == Token_LPAREN
        || yytoken == Token_SEMI
        || yytoken == Token_STAR)
    {
        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_BAND
                || yytoken == Token_FUNCTION
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_STAR)
            {
                MethodDefinitionArgumentWithoutParenAst *__node_126 = 0;
                if (!parseMethodDefinitionArgumentWithoutParen(&__node_126))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::MethodDefinitionArgumentWithoutParenKind, "methodDefinitionArgumentWithoutParen");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_LINE_BREAK
                || yytoken == Token_SEMI)
            {
                TerminalAst *__node_127 = 0;
                if (!parseTerminal(&__node_127))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::TerminalKind, "terminal");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_BAND
                 || yytoken == Token_FUNCTION
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_LINE_BREAK
                 || yytoken == Token_SEMI
                 || yytoken == Token_STAR)
        {
            if (yytoken == Token_BAND
                || yytoken == Token_FUNCTION
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_STAR)
            {
                MethodDefinitionArgumentWithoutParenAst *__node_128 = 0;
                if (!parseMethodDefinitionArgumentWithoutParen(&__node_128))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::MethodDefinitionArgumentWithoutParenKind, "methodDefinitionArgumentWithoutParen");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            TerminalAst *__node_129 = 0;
            if (!parseTerminal(&__node_129))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TerminalKind, "terminal");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodDefinitionArgumentWithoutParen(MethodDefinitionArgumentWithoutParenAst **yynode)
{
    *yynode = create<MethodDefinitionArgumentWithoutParenAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BAND
        || yytoken == Token_FUNCTION
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_STAR)
    {
        if (yytoken == Token_FUNCTION
            || yytoken == Token_IDENTIFIER)
        {
            NormalMethodDefinitionArgumentAst *__node_130 = 0;
            if (!parseNormalMethodDefinitionArgument(&__node_130))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::NormalMethodDefinitionArgumentKind, "normalMethodDefinitionArgument");
                }
                return false;
            }
            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                if (Token_STAR == yytoken || Token_BAND == yytoken)
                {
                    expect_array_or_block_arguments = true;
                    break;
                }
                NormalMethodDefinitionArgumentAst *__node_131 = 0;
                if (!parseNormalMethodDefinitionArgument(&__node_131))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::NormalMethodDefinitionArgumentKind, "normalMethodDefinitionArgument");
                    }
                    return false;
                }
            }
            if ((yytoken == Token_STAR) && ( expect_array_or_block_arguments ))
            {
                RestMethodDefinitionArgumentAst *__node_132 = 0;
                if (!parseRestMethodDefinitionArgument(&__node_132))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::RestMethodDefinitionArgumentKind, "restMethodDefinitionArgument");
                    }
                    return false;
                }
            }
            else if ((yytoken == Token_BAND) && ( expect_array_or_block_arguments ))
            {
                BlockMethodDefinitionArgumentAst *__node_133 = 0;
                if (!parseBlockMethodDefinitionArgument(&__node_133))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::BlockMethodDefinitionArgumentKind, "blockMethodDefinitionArgument");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if ((yytoken == Token_STAR) && ( (expect_array_or_block_arguments = true) ))
        {
            RestMethodDefinitionArgumentAst *__node_134 = 0;
            if (!parseRestMethodDefinitionArgument(&__node_134))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::RestMethodDefinitionArgumentKind, "restMethodDefinitionArgument");
                }
                return false;
            }
        }
        else if ((yytoken == Token_BAND) && ( (expect_array_or_block_arguments = true) ))
        {
            BlockMethodDefinitionArgumentAst *__node_135 = 0;
            if (!parseBlockMethodDefinitionArgument(&__node_135))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockMethodDefinitionArgumentKind, "blockMethodDefinitionArgument");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodInvocationArgumentWithParen(MethodInvocationArgumentWithParenAst **yynode)
{
    *yynode = create<MethodInvocationArgumentWithParenAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY
            || yytoken == Token_BLOCK_ARG_PREFIX
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            MethodInvocationArgumentWithoutParenAst *__node_136 = 0;
            if (!parseMethodInvocationArgumentWithoutParen(&__node_136))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MethodInvocationArgumentWithoutParenKind, "methodInvocationArgumentWithoutParen");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodInvocationArgumentWithoutParen(MethodInvocationArgumentWithoutParenAst **yynode)
{
    *yynode = create<MethodInvocationArgumentWithoutParenAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BLOCK_ARG_PREFIX
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            NormalMethodInvocationArgumentAst *__node_137 = 0;
            if (!parseNormalMethodInvocationArgument(&__node_137))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::NormalMethodInvocationArgumentKind, "normalMethodInvocationArgument");
                }
                return false;
            }
            std::cout << "normal" << std::endl;
            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                std::cout << "asking for another arg" << std::endl;
                if ((yytoken == Token_STAR) || (yytoken == Token_BAND)) break;
                NormalMethodInvocationArgumentAst *__node_138 = 0;
                if (!parseNormalMethodInvocationArgument(&__node_138))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::NormalMethodInvocationArgumentKind, "normalMethodInvocationArgument");
                    }
                    return false;
                }
                std::cout << "arg is done" << std::endl;
            }
            if (yytoken == Token_REST_ARG_PREFIX)
            {
                RestMethodInvocationArgumentAst *__node_139 = 0;
                if (!parseRestMethodInvocationArgument(&__node_139))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::RestMethodInvocationArgumentKind, "restMethodInvocationArgument");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_BLOCK_ARG_PREFIX)
            {
                BlockMethodInvocationArgumentAst *__node_140 = 0;
                if (!parseBlockMethodInvocationArgument(&__node_140))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::BlockMethodInvocationArgumentKind, "blockMethodInvocationArgument");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_REST_ARG_PREFIX)
        {
            RestMethodInvocationArgumentAst *__node_141 = 0;
            if (!parseRestMethodInvocationArgument(&__node_141))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::RestMethodInvocationArgumentKind, "restMethodInvocationArgument");
                }
                return false;
            }
        }
        else if (yytoken == Token_BLOCK_ARG_PREFIX)
        {
            BlockMethodInvocationArgumentAst *__node_142 = 0;
            if (!parseBlockMethodInvocationArgument(&__node_142))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockMethodInvocationArgumentKind, "blockMethodInvocationArgument");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodName(MethodNameAst **yynode)
{
    *yynode = create<MethodNameAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_AND
        || yytoken == Token_BAND
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BNOT
        || yytoken == Token_BOR
        || yytoken == Token_BREAK
        || yytoken == Token_BXOR
        || yytoken == Token_CASE
        || yytoken == Token_CASE_EQUAL
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COMPARE
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DIV
        || yytoken == Token_DO
        || yytoken == Token_ELSE
        || yytoken == Token_ELSIF
        || yytoken == Token_END
        || yytoken == Token_END_UPCASE
        || yytoken == Token_ENSURE
        || yytoken == Token_EQUAL
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_GREATER_OR_EQUAL
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_IN
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_LBRACK
        || yytoken == Token_LBRACK_ARRAY_ACCESS
        || yytoken == Token_LEFT_SHIFT
        || yytoken == Token_LESS_OR_EQUAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MATCH
        || yytoken == Token_MINUS
        || yytoken == Token_MOD
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OR
        || yytoken == Token_PLUS
        || yytoken == Token_POWER
        || yytoken == Token_REDO
        || yytoken == Token_RESCUE
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_RIGHT_SHIFT
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTE
        || yytoken == Token_STAR
        || yytoken == Token_SUPER
        || yytoken == Token_THEN
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_PLUS_MINUS_METHOD_NAME
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHEN
        || yytoken == Token_WHILE
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_BAND
            || yytoken == Token_BNOT
            || yytoken == Token_BOR
            || yytoken == Token_BXOR
            || yytoken == Token_CASE_EQUAL
            || yytoken == Token_COMPARE
            || yytoken == Token_DIV
            || yytoken == Token_EQUAL
            || yytoken == Token_GREATER_OR_EQUAL
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_LBRACK
            || yytoken == Token_LBRACK_ARRAY_ACCESS
            || yytoken == Token_LEFT_SHIFT
            || yytoken == Token_LESS_OR_EQUAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_MATCH
            || yytoken == Token_MINUS
            || yytoken == Token_MOD
            || yytoken == Token_PLUS
            || yytoken == Token_POWER
            || yytoken == Token_RIGHT_SHIFT
            || yytoken == Token_SINGLE_QUOTE
            || yytoken == Token_STAR)
        {
            OperatorAsMethodnameAst *__node_143 = 0;
            if (!parseOperatorAsMethodname(&__node_143))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorAsMethodnameKind, "operatorAsMethodname");
                }
                return false;
            }
        }
        else if (yytoken == Token_ALIAS
                 || yytoken == Token_AND
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BEGIN_UPCASE
                 || yytoken == Token_BREAK
                 || yytoken == Token_CASE
                 || yytoken == Token_CLASS
                 || yytoken == Token_DEF
                 || yytoken == Token_DEFINED
                 || yytoken == Token_DO
                 || yytoken == Token_ELSE
                 || yytoken == Token_ELSIF
                 || yytoken == Token_END
                 || yytoken == Token_END_UPCASE
                 || yytoken == Token_ENSURE
                 || yytoken == Token_FOR
                 || yytoken == Token_IF
                 || yytoken == Token_IN
                 || yytoken == Token_MODULE
                 || yytoken == Token_NEXT
                 || yytoken == Token_NOT
                 || yytoken == Token_OR
                 || yytoken == Token_REDO
                 || yytoken == Token_RESCUE
                 || yytoken == Token_RETRY
                 || yytoken == Token_RETURN
                 || yytoken == Token_SUPER
                 || yytoken == Token_THEN
                 || yytoken == Token_UNDEF
                 || yytoken == Token_UNLESS
                 || yytoken == Token_UNTIL
                 || yytoken == Token_WHEN
                 || yytoken == Token_WHILE
                 || yytoken == Token_YIELD)
        {
            KeywordAsMethodNameAst *__node_144 = 0;
            if (!parseKeywordAsMethodName(&__node_144))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordAsMethodNameKind, "keywordAsMethodName");
                }
                return false;
            }
        }
        else if (yytoken == Token_CONSTANT
                 || yytoken == Token_FUNCTION
                 || yytoken == Token_IDENTIFIER)
        {
            if (yytoken == Token_IDENTIFIER)
            {
                if (yytoken != Token_IDENTIFIER)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_FUNCTION)
            {
                if (yytoken != Token_FUNCTION)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FUNCTION, "function");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_CONSTANT)
            {
                if (yytoken != Token_CONSTANT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_CONSTANT, "constant");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            if (yytoken == Token_DOT
                || yytoken == Token_TWO_COLON)
            {
                MethodNameSupplementAst *__node_145 = 0;
                if (!parseMethodNameSupplement(&__node_145))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::MethodNameSupplementKind, "methodNameSupplement");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_146 = 0;
            if (!parseExpression(&__node_146))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            if (yytoken == Token_LINE_BREAK)
            {
                if (yytoken != Token_LINE_BREAK)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LINE_BREAK, "line break");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            MethodNameSupplementAst *__node_147 = 0;
            if (!parseMethodNameSupplement(&__node_147))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MethodNameSupplementKind, "methodNameSupplement");
                }
                return false;
            }
        }
        else if (yytoken == Token_CLASS_VARIABLE
                 || yytoken == Token_GLOBAL_VARIABLE
                 || yytoken == Token_INSTANCE_VARIABLE)
        {
            if (yytoken == Token_INSTANCE_VARIABLE)
            {
                if (yytoken != Token_INSTANCE_VARIABLE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_INSTANCE_VARIABLE, "instance variable");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_CLASS_VARIABLE)
            {
                if (yytoken != Token_CLASS_VARIABLE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_CLASS_VARIABLE, "class variable");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_GLOBAL_VARIABLE)
            {
                if (yytoken != Token_GLOBAL_VARIABLE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_GLOBAL_VARIABLE, "global variable");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            MethodNameSupplementAst *__node_148 = 0;
            if (!parseMethodNameSupplement(&__node_148))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MethodNameSupplementKind, "methodNameSupplement");
                }
                return false;
            }
        }
        else if (yytoken == Token_FALSE
                 || yytoken == Token_FILE
                 || yytoken == Token_LINE
                 || yytoken == Token_NIL
                 || yytoken == Token_SELF
                 || yytoken == Token_TRUE)
        {
            if (yytoken == Token_NIL)
            {
                if (yytoken != Token_NIL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_NIL, "nil");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_SELF)
            {
                if (yytoken != Token_SELF)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SELF, "self");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_TRUE)
            {
                if (yytoken != Token_TRUE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_TRUE, "true");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_FALSE)
            {
                if (yytoken != Token_FALSE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FALSE, "false");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_FILE)
            {
                if (yytoken != Token_FILE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FILE, "__FILE__");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_LINE)
            {
                if (yytoken != Token_LINE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LINE, "__LINE__");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            MethodNameSupplementAst *__node_149 = 0;
            if (!parseMethodNameSupplement(&__node_149))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MethodNameSupplementKind, "methodNameSupplement");
                }
                return false;
            }
        }
        else if (yytoken == Token_UNARY_PLUS_MINUS_METHOD_NAME)
        {
            if (yytoken != Token_UNARY_PLUS_MINUS_METHOD_NAME)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNARY_PLUS_MINUS_METHOD_NAME, "+/- method");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodNameSupplement(MethodNameSupplementAst **yynode)
{
    *yynode = create<MethodNameSupplementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DOT
        || yytoken == Token_TWO_COLON)
    {
        if (yytoken == Token_DOT)
        {
            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_TWO_COLON)
        {
            if (yytoken != Token_TWO_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TWO_COLON, "::");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_FUNCTION)
        {
            if (yytoken != Token_FUNCTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNCTION, "function");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_CONSTANT)
        {
            if (yytoken != Token_CONSTANT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONSTANT, "constant");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_BAND
                 || yytoken == Token_BNOT
                 || yytoken == Token_BOR
                 || yytoken == Token_BXOR
                 || yytoken == Token_CASE_EQUAL
                 || yytoken == Token_COMPARE
                 || yytoken == Token_DIV
                 || yytoken == Token_EQUAL
                 || yytoken == Token_GREATER_OR_EQUAL
                 || yytoken == Token_GREATER_THAN
                 || yytoken == Token_LBRACK
                 || yytoken == Token_LBRACK_ARRAY_ACCESS
                 || yytoken == Token_LEFT_SHIFT
                 || yytoken == Token_LESS_OR_EQUAL
                 || yytoken == Token_LESS_THAN
                 || yytoken == Token_MATCH
                 || yytoken == Token_MINUS
                 || yytoken == Token_MOD
                 || yytoken == Token_PLUS
                 || yytoken == Token_POWER
                 || yytoken == Token_RIGHT_SHIFT
                 || yytoken == Token_SINGLE_QUOTE
                 || yytoken == Token_STAR)
        {
            OperatorAsMethodnameAst *__node_150 = 0;
            if (!parseOperatorAsMethodname(&__node_150))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorAsMethodnameKind, "operatorAsMethodname");
                }
                return false;
            }
        }
        else if (yytoken == Token_ALIAS
                 || yytoken == Token_AND
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BEGIN_UPCASE
                 || yytoken == Token_BREAK
                 || yytoken == Token_CASE
                 || yytoken == Token_CLASS
                 || yytoken == Token_DEF
                 || yytoken == Token_DEFINED
                 || yytoken == Token_DO
                 || yytoken == Token_ELSE
                 || yytoken == Token_ELSIF
                 || yytoken == Token_END
                 || yytoken == Token_END_UPCASE
                 || yytoken == Token_ENSURE
                 || yytoken == Token_FALSE
                 || yytoken == Token_FILE
                 || yytoken == Token_FOR
                 || yytoken == Token_IF
                 || yytoken == Token_IN
                 || yytoken == Token_LINE
                 || yytoken == Token_MODULE
                 || yytoken == Token_NEXT
                 || yytoken == Token_NIL
                 || yytoken == Token_NOT
                 || yytoken == Token_OR
                 || yytoken == Token_REDO
                 || yytoken == Token_RESCUE
                 || yytoken == Token_RETRY
                 || yytoken == Token_RETURN
                 || yytoken == Token_SELF
                 || yytoken == Token_SUPER
                 || yytoken == Token_THEN
                 || yytoken == Token_TRUE
                 || yytoken == Token_UNDEF
                 || yytoken == Token_UNLESS
                 || yytoken == Token_UNTIL
                 || yytoken == Token_WHEN
                 || yytoken == Token_WHILE
                 || yytoken == Token_YIELD)
        {
            KeywordAst *__node_151 = 0;
            if (!parseKeyword(&__node_151))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordKind, "keyword");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMlhs_item(Mlhs_itemAst **yynode)
{
    *yynode = create<Mlhs_itemAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        bool blockErrors_2 = blockErrors(true);
        qint64 try_startToken_2 = tokenStream->index() - 1;
        ParserState *try_startState_2 = copyCurrentState();
        {
            if (yytoken != Token_LPAREN)
                goto __catch_2;
            yylex();

            DotAccessAst *__node_152 = 0;
            if (!parseDotAccess(&__node_152))
            {
                goto __catch_2;
            }
            do
            {
                if (yytoken != Token_COMMA)
                    goto __catch_2;
                yylex();

                DotAccessAst *__node_153 = 0;
                if (!parseDotAccess(&__node_153))
                {
                    goto __catch_2;
                }
            }
            while (yytoken == Token_COMMA);
            if (yytoken != Token_RPAREN)
                goto __catch_2;
            yylex();

        }
        blockErrors(blockErrors_2);
        if (try_startState_2)
            delete try_startState_2;

        if (false) // the only way to enter here is using goto
        {
__catch_2:
            if (try_startState_2)
            {
                restoreState(try_startState_2);
                delete try_startState_2;
            }
            blockErrors(blockErrors_2);
            rewind(try_startToken_2);

            DotAccessAst *__node_154 = 0;
            if (!parseDotAccess(&__node_154))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DotAccessKind, "dotAccess");
                }
                return false;
            }
        }

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseModuleDefinition(ModuleDefinitionAst **yynode)
{
    *yynode = create<ModuleDefinitionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MODULE)
    {
        KeywordModuleAst *__node_155 = 0;
        if (!parseKeywordModule(&__node_155))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::KeywordModuleKind, "keywordModule");
            }
            return false;
        }
        ModuleNameAst *__node_156 = 0;
        if (!parseModuleName(&__node_156))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ModuleNameKind, "moduleName");
            }
            return false;
        }
        TerminalAst *__node_157 = 0;
        if (!parseTerminal(&__node_157))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TerminalKind, "terminal");
            }
            return false;
        }
        BodyStatementAst *__node_158 = 0;
        if (!parseBodyStatement(&__node_158))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BodyStatementKind, "bodyStatement");
            }
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseModuleName(ModuleNameAst **yynode)
{
    *yynode = create<ModuleNameAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CONSTANT)
    {
        if (yytoken != Token_CONSTANT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CONSTANT, "constant");
            }
            return false;
        }
        yylex();

        while (yytoken == Token_TWO_COLON)
        {
            if (yytoken != Token_TWO_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TWO_COLON, "::");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_CONSTANT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONSTANT, "constant");
                }
                return false;
            }
            yylex();

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMrhs(MrhsAst **yynode)
{
    *yynode = create<MrhsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            ExpressionAst *__node_159 = 0;
            if (!parseExpression(&__node_159))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                if ((yytoken == Token_ASSIGN) || (yytoken == Token_RBRACK)) break;
                if (yytoken == Token_REST_ARG_PREFIX)
                {
                    if (yytoken != Token_REST_ARG_PREFIX)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_REST_ARG_PREFIX, "*");
                        }
                        return false;
                    }
                    yylex();

                    seen_star = true;
                }
                else if (true /*epsilon*/)
                {
                    seen_star = false;
                }
                else
                {
                    return false;
                }
                ExpressionAst *__node_160 = 0;
                if (!parseExpression(&__node_160))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
                if (seen_star) break;
            }
        }
        else if (yytoken == Token_REST_ARG_PREFIX)
        {
            if (yytoken != Token_REST_ARG_PREFIX)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REST_ARG_PREFIX, "*");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_161 = 0;
            if (!parseExpression(&__node_161))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMultiplicativeExpression(MultiplicativeExpressionAst **yynode)
{
    *yynode = create<MultiplicativeExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        PowerExpressionAst *__node_162 = 0;
        if (!parsePowerExpression(&__node_162))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::PowerExpressionKind, "powerExpression");
            }
            return false;
        }
        while (yytoken == Token_DIV
               || yytoken == Token_MOD
               || yytoken == Token_STAR)
        {
            if (yytoken == Token_STAR)
            {
                OperatorStarAst *__node_163 = 0;
                if (!parseOperatorStar(&__node_163))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorStarKind, "operatorStar");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_DIV)
            {
                OperatorDivAst *__node_164 = 0;
                if (!parseOperatorDiv(&__node_164))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorDivKind, "operatorDiv");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_MOD)
            {
                OperatorModAst *__node_165 = 0;
                if (!parseOperatorMod(&__node_165))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorModKind, "operatorMod");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
            PowerExpressionAst *__node_166 = 0;
            if (!parsePowerExpression(&__node_166))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::PowerExpressionKind, "powerExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNormalMethodDefinitionArgument(NormalMethodDefinitionArgumentAst **yynode)
{
    *yynode = create<NormalMethodDefinitionArgumentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_FUNCTION
        || yytoken == Token_IDENTIFIER)
    {
        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FUNCTION)
        {
            if (yytoken != Token_FUNCTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNCTION, "function");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        if (yytoken == Token_ASSIGN
            || yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
        {
            if (yytoken == Token_ASSIGN)
            {
                if (yytoken != Token_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            ExpressionAst *__node_167 = 0;
            if (!parseExpression(&__node_167))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNormalMethodInvocationArgument(NormalMethodInvocationArgumentAst **yynode)
{
    *yynode = create<NormalMethodInvocationArgumentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        ExpressionAst *__node_168 = 0;
        if (!parseExpression(&__node_168))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        if (yytoken == Token_ASSOC)
        {
            if (yytoken != Token_ASSOC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSOC, "=>");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_169 = 0;
            if (!parseExpression(&__node_169))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNotExpression(NotExpressionAst **yynode)
{
    *yynode = create<NotExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_KEYWORD_NOT)
        {
            KeywordNotAst *__node_170 = 0;
            if (!parseKeywordNot(&__node_170))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordNotKind, "keywordNot");
                }
                return false;
            }
            NotExpressionAst *__node_171 = 0;
            if (!parseNotExpression(&__node_171))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::NotExpressionKind, "notExpression");
                }
                return false;
            }
        }
        else if (yytoken == Token_ASCII_VALUE
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BINARY
                 || yytoken == Token_BNOT
                 || yytoken == Token_BREAK
                 || yytoken == Token_CASE
                 || yytoken == Token_CLASS
                 || yytoken == Token_CLASS_VARIABLE
                 || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                 || yytoken == Token_COMMAND_OUTPUT
                 || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_COMMENT
                 || yytoken == Token_CONSTANT
                 || yytoken == Token_DEF
                 || yytoken == Token_DEFINED
                 || yytoken == Token_DOUBLE_QUOTED_STRING
                 || yytoken == Token_FALSE
                 || yytoken == Token_FILE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_FOR
                 || yytoken == Token_FUNCTION
                 || yytoken == Token_GLOBAL_VARIABLE
                 || yytoken == Token_HERE_DOC_BEGIN
                 || yytoken == Token_HEX
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_IF
                 || yytoken == Token_INSTANCE_VARIABLE
                 || yytoken == Token_INTEGER
                 || yytoken == Token_LBRACK
                 || yytoken == Token_LCURLY_HASH
                 || yytoken == Token_LEADING_TWO_COLON
                 || yytoken == Token_LINE
                 || yytoken == Token_LPAREN
                 || yytoken == Token_MODULE
                 || yytoken == Token_NEXT
                 || yytoken == Token_NIL
                 || yytoken == Token_NOT
                 || yytoken == Token_OCTAL
                 || yytoken == Token_REDO
                 || yytoken == Token_REGEX
                 || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_RETRY
                 || yytoken == Token_RETURN
                 || yytoken == Token_SELF
                 || yytoken == Token_SINGLE_QUOTED_STRING
                 || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_SUPER
                 || yytoken == Token_TRUE
                 || yytoken == Token_UNARY_MINUS
                 || yytoken == Token_UNARY_PLUS
                 || yytoken == Token_UNLESS
                 || yytoken == Token_UNTIL
                 || yytoken == Token_WHILE
                 || yytoken == Token_W_ARRAY
                 || yytoken == Token_YIELD)
        {
            TernaryIfThenElseExpressionAst *__node_172 = 0;
            if (!parseTernaryIfThenElseExpression(&__node_172))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TernaryIfThenElseExpressionKind, "ternaryIfThenElseExpression");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNumeric(NumericAst **yynode)
{
    *yynode = create<NumericAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BINARY
        || yytoken == Token_FLOAT
        || yytoken == Token_HEX
        || yytoken == Token_INTEGER
        || yytoken == Token_OCTAL)
    {
        if (yytoken == Token_INTEGER)
        {
            if (yytoken != Token_INTEGER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INTEGER, "integer number");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_HEX)
        {
            if (yytoken != Token_HEX)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_HEX, "hexadecimal number");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BINARY)
        {
            if (yytoken != Token_BINARY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BINARY, "binary number");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_OCTAL)
        {
            if (yytoken != Token_OCTAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OCTAL, "octal number");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FLOAT)
        {
            if (yytoken != Token_FLOAT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FLOAT, "float number");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ASCII_VALUE)
        {
            if (yytoken != Token_ASCII_VALUE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASCII_VALUE, "ascii value");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorAsMethodname(OperatorAsMethodnameAst **yynode)
{
    *yynode = create<OperatorAsMethodnameAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BAND
        || yytoken == Token_BNOT
        || yytoken == Token_BOR
        || yytoken == Token_BXOR
        || yytoken == Token_CASE_EQUAL
        || yytoken == Token_COMPARE
        || yytoken == Token_DIV
        || yytoken == Token_EQUAL
        || yytoken == Token_GREATER_OR_EQUAL
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_LBRACK
        || yytoken == Token_LBRACK_ARRAY_ACCESS
        || yytoken == Token_LEFT_SHIFT
        || yytoken == Token_LESS_OR_EQUAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_MATCH
        || yytoken == Token_MINUS
        || yytoken == Token_MOD
        || yytoken == Token_PLUS
        || yytoken == Token_POWER
        || yytoken == Token_RIGHT_SHIFT
        || yytoken == Token_SINGLE_QUOTE
        || yytoken == Token_STAR)
    {
        if (yytoken == Token_LEFT_SHIFT)
        {
            if (yytoken != Token_LEFT_SHIFT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LEFT_SHIFT, "<<");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_RIGHT_SHIFT)
        {
            if (yytoken != Token_RIGHT_SHIFT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RIGHT_SHIFT, ">>");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_EQUAL)
        {
            if (yytoken != Token_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EQUAL, "==");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CASE_EQUAL)
        {
            if (yytoken != Token_CASE_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CASE_EQUAL, "===");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_GREATER_THAN)
        {
            if (yytoken != Token_GREATER_THAN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GREATER_THAN, ">");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_GREATER_OR_EQUAL)
        {
            if (yytoken != Token_GREATER_OR_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GREATER_OR_EQUAL, ">=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LESS_THAN)
        {
            if (yytoken != Token_LESS_THAN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LESS_THAN, "<");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LESS_OR_EQUAL)
        {
            if (yytoken != Token_LESS_OR_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LESS_OR_EQUAL, "<=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_PLUS)
        {
            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_STAR)
        {
            if (yytoken != Token_STAR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STAR, "*");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DIV)
        {
            if (yytoken != Token_DIV)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DIV, "/");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MOD)
        {
            if (yytoken != Token_MOD)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MOD, "%");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_POWER)
        {
            if (yytoken != Token_POWER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_POWER, "**");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BAND)
        {
            if (yytoken != Token_BAND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BAND, "&");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BOR)
        {
            if (yytoken != Token_BOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BOR, "|");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BXOR)
        {
            if (yytoken != Token_BXOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BXOR, "^");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LBRACK
                 || yytoken == Token_LBRACK_ARRAY_ACCESS)
        {
            if (yytoken == Token_LBRACK)
            {
                if (yytoken != Token_LBRACK)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LBRACK, "[");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_LBRACK_ARRAY_ACCESS)
            {
                if (yytoken != Token_LBRACK_ARRAY_ACCESS)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LBRACK_ARRAY_ACCESS, "[");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            if (yytoken != Token_RBRACK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACK, "]");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_MATCH)
        {
            if (yytoken != Token_MATCH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MATCH, "=~");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_COMPARE)
        {
            if (yytoken != Token_COMPARE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMPARE, "<=>");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BNOT)
        {
            if (yytoken != Token_BNOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BNOT, "~");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SINGLE_QUOTE)
        {
            if (yytoken != Token_SINGLE_QUOTE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SINGLE_QUOTE, "'");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorAssign(OperatorAssignAst **yynode)
{
    *yynode = create<OperatorAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASSIGN
        || yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
    {
        if (yytoken == Token_ASSIGN)
        {
            if (yytoken != Token_ASSIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSIGN, "=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
        {
            if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorBAnd(OperatorBAndAst **yynode)
{
    *yynode = create<OperatorBAndAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BAND)
    {
        if (yytoken != Token_BAND)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BAND, "&");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorBAndAssign(OperatorBAndAssignAst **yynode)
{
    *yynode = create<OperatorBAndAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BAND_ASSIGN)
    {
        if (yytoken != Token_BAND_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BAND_ASSIGN, "&=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorBNot(OperatorBNotAst **yynode)
{
    *yynode = create<OperatorBNotAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BNOT)
    {
        if (yytoken != Token_BNOT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BNOT, "~");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorBOr(OperatorBOrAst **yynode)
{
    *yynode = create<OperatorBOrAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BOR)
    {
        if (yytoken != Token_BOR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BOR, "|");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorBXor(OperatorBXorAst **yynode)
{
    *yynode = create<OperatorBXorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BXOR)
    {
        if (yytoken != Token_BXOR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BXOR, "^");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorBXorAssign(OperatorBXorAssignAst **yynode)
{
    *yynode = create<OperatorBXorAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BXOR_ASSIGN)
    {
        if (yytoken != Token_BXOR_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BXOR_ASSIGN, "^=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorBorAssign(OperatorBorAssignAst **yynode)
{
    *yynode = create<OperatorBorAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BOR_ASSIGN)
    {
        if (yytoken != Token_BOR_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BOR_ASSIGN, "|=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorCaseEqual(OperatorCaseEqualAst **yynode)
{
    *yynode = create<OperatorCaseEqualAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CASE_EQUAL)
    {
        if (yytoken != Token_CASE_EQUAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CASE_EQUAL, "===");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorColon(OperatorColonAst **yynode)
{
    *yynode = create<OperatorColonAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COLON
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE)
    {
        if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE)
        {
            if (yytoken != Token_COLON_WITH_NO_FOLLOWING_SPACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON_WITH_NO_FOLLOWING_SPACE, ":");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorCompare(OperatorCompareAst **yynode)
{
    *yynode = create<OperatorCompareAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COMPARE)
    {
        if (yytoken != Token_COMPARE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COMPARE, "<=>");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorDiv(OperatorDivAst **yynode)
{
    *yynode = create<OperatorDivAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DIV)
    {
        if (yytoken != Token_DIV)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DIV, "/");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorDivAssign(OperatorDivAssignAst **yynode)
{
    *yynode = create<OperatorDivAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DIV_ASSIGN)
    {
        if (yytoken != Token_DIV_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DIV_ASSIGN, "/=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorEqual(OperatorEqualAst **yynode)
{
    *yynode = create<OperatorEqualAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_EQUAL)
    {
        if (yytoken != Token_EQUAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_EQUAL, "==");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorExclusiveRange(OperatorExclusiveRangeAst **yynode)
{
    *yynode = create<OperatorExclusiveRangeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_EXCLUSIVE_RANGE)
    {
        if (yytoken != Token_EXCLUSIVE_RANGE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_EXCLUSIVE_RANGE, "...");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorGreaterOrEqual(OperatorGreaterOrEqualAst **yynode)
{
    *yynode = create<OperatorGreaterOrEqualAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_GREATER_OR_EQUAL)
    {
        if (yytoken != Token_GREATER_OR_EQUAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_GREATER_OR_EQUAL, ">=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorGreaterThan(OperatorGreaterThanAst **yynode)
{
    *yynode = create<OperatorGreaterThanAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_GREATER_THAN)
    {
        if (yytoken != Token_GREATER_THAN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_GREATER_THAN, ">");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorInclusiveRange(OperatorInclusiveRangeAst **yynode)
{
    *yynode = create<OperatorInclusiveRangeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_INCLUSIVE_RANGE)
    {
        if (yytoken != Token_INCLUSIVE_RANGE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_INCLUSIVE_RANGE, "..");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorLeftShift(OperatorLeftShiftAst **yynode)
{
    *yynode = create<OperatorLeftShiftAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LEFT_SHIFT)
    {
        if (yytoken != Token_LEFT_SHIFT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LEFT_SHIFT, "<<");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorLeftShiftAssign(OperatorLeftShiftAssignAst **yynode)
{
    *yynode = create<OperatorLeftShiftAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LEFT_SHIFT_ASSIGN)
    {
        if (yytoken != Token_LEFT_SHIFT_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LEFT_SHIFT_ASSIGN, "<<=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorLessOrEqual(OperatorLessOrEqualAst **yynode)
{
    *yynode = create<OperatorLessOrEqualAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LESS_OR_EQUAL)
    {
        if (yytoken != Token_LESS_OR_EQUAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LESS_OR_EQUAL, "<=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorLessThan(OperatorLessThanAst **yynode)
{
    *yynode = create<OperatorLessThanAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LESS_THAN)
    {
        if (yytoken != Token_LESS_THAN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LESS_THAN, "<");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorLogicalAnd(OperatorLogicalAndAst **yynode)
{
    *yynode = create<OperatorLogicalAndAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LOGICAL_AND)
    {
        if (yytoken != Token_LOGICAL_AND)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LOGICAL_AND, "&");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorLogicalAndAssign(OperatorLogicalAndAssignAst **yynode)
{
    *yynode = create<OperatorLogicalAndAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LOGICAL_AND_ASSIGN)
    {
        if (yytoken != Token_LOGICAL_AND_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LOGICAL_AND_ASSIGN, "&&=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorLogicalOr(OperatorLogicalOrAst **yynode)
{
    *yynode = create<OperatorLogicalOrAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LOGICAL_OR)
    {
        if (yytoken != Token_LOGICAL_OR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LOGICAL_OR, "||");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorLogicalOrAssign(OperatorLogicalOrAssignAst **yynode)
{
    *yynode = create<OperatorLogicalOrAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LOGICAL_OR_ASSIGN)
    {
        if (yytoken != Token_LOGICAL_OR_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LOGICAL_OR_ASSIGN, "||=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorMatch(OperatorMatchAst **yynode)
{
    *yynode = create<OperatorMatchAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MATCH)
    {
        if (yytoken != Token_MATCH)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_MATCH, "=~");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorMinus(OperatorMinusAst **yynode)
{
    *yynode = create<OperatorMinusAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MINUS)
    {
        if (yytoken != Token_MINUS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_MINUS, "-");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorMinusAssign(OperatorMinusAssignAst **yynode)
{
    *yynode = create<OperatorMinusAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MINUS_ASSIGN)
    {
        if (yytoken != Token_MINUS_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_MINUS_ASSIGN, "-=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorMod(OperatorModAst **yynode)
{
    *yynode = create<OperatorModAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MOD)
    {
        if (yytoken != Token_MOD)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_MOD, "%");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorModAssign(OperatorModAssignAst **yynode)
{
    *yynode = create<OperatorModAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MOD_ASSIGN)
    {
        if (yytoken != Token_MOD_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_MOD_ASSIGN, "%=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorNot(OperatorNotAst **yynode)
{
    *yynode = create<OperatorNotAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_NOT)
    {
        if (yytoken != Token_NOT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_NOT, "!");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorNotEqual(OperatorNotEqualAst **yynode)
{
    *yynode = create<OperatorNotEqualAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_NOT_EQUAL)
    {
        if (yytoken != Token_NOT_EQUAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_NOT_EQUAL, "!=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorNotMatch(OperatorNotMatchAst **yynode)
{
    *yynode = create<OperatorNotMatchAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_NOT_MATCH)
    {
        if (yytoken != Token_NOT_MATCH)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_NOT_MATCH, "!~");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorPlus(OperatorPlusAst **yynode)
{
    *yynode = create<OperatorPlusAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PLUS)
    {
        if (yytoken != Token_PLUS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_PLUS, "+");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorPlusAssign(OperatorPlusAssignAst **yynode)
{
    *yynode = create<OperatorPlusAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PLUS_ASSIGN)
    {
        if (yytoken != Token_PLUS_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_PLUS_ASSIGN, "+=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorPower(OperatorPowerAst **yynode)
{
    *yynode = create<OperatorPowerAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_POWER)
    {
        if (yytoken != Token_POWER)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_POWER, "**");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorPowerAssign(OperatorPowerAssignAst **yynode)
{
    *yynode = create<OperatorPowerAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_POWER_ASSIGN)
    {
        if (yytoken != Token_POWER_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_POWER_ASSIGN, "**=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorQuestion(OperatorQuestionAst **yynode)
{
    *yynode = create<OperatorQuestionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_QUESTION)
    {
        if (yytoken != Token_QUESTION)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_QUESTION, "?");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorRightShift(OperatorRightShiftAst **yynode)
{
    *yynode = create<OperatorRightShiftAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_RIGHT_SHIFT)
    {
        if (yytoken != Token_RIGHT_SHIFT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RIGHT_SHIFT, ">>");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorRightShiftAssign(OperatorRightShiftAssignAst **yynode)
{
    *yynode = create<OperatorRightShiftAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_RIGHT_SHIFT_ASSIGN)
    {
        if (yytoken != Token_RIGHT_SHIFT_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RIGHT_SHIFT_ASSIGN, ">>=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorStar(OperatorStarAst **yynode)
{
    *yynode = create<OperatorStarAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STAR)
    {
        if (yytoken != Token_STAR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_STAR, "*");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorStarAssign(OperatorStarAssignAst **yynode)
{
    *yynode = create<OperatorStarAssignAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STAR_ASSIGN)
    {
        if (yytoken != Token_STAR_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_STAR_ASSIGN, "*=");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorUnaryMinus(OperatorUnaryMinusAst **yynode)
{
    *yynode = create<OperatorUnaryMinusAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNARY_MINUS)
    {
        if (yytoken != Token_UNARY_MINUS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_UNARY_MINUS, "-");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOperatorUnaryPlus(OperatorUnaryPlusAst **yynode)
{
    *yynode = create<OperatorUnaryPlusAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNARY_PLUS)
    {
        if (yytoken != Token_UNARY_PLUS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_UNARY_PLUS, "+");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOrExpression(OrExpressionAst **yynode)
{
    *yynode = create<OrExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        AndExpressionAst *__node_173 = 0;
        if (!parseAndExpression(&__node_173))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AndExpressionKind, "andExpression");
            }
            return false;
        }
        while (yytoken == Token_BOR
               || yytoken == Token_BXOR)
        {
            if (yytoken == Token_BXOR)
            {
                OperatorBXorAst *__node_174 = 0;
                if (!parseOperatorBXor(&__node_174))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorBXorKind, "operatorBXor");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_BOR)
            {
                OperatorBOrAst *__node_175 = 0;
                if (!parseOperatorBOr(&__node_175))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorBOrKind, "operatorBOr");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
            AndExpressionAst *__node_176 = 0;
            if (!parseAndExpression(&__node_176))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AndExpressionKind, "andExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseParallelAssignmentLeftOver(ParallelAssignmentLeftOverAst **yynode)
{
    *yynode = create<ParallelAssignmentLeftOverAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COMMA)
    {
        do
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            if ((yytoken == Token_ASSIGN) || (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)) break;
            if (yytoken == Token_REST_ARG_PREFIX)
            {
                if (yytoken != Token_REST_ARG_PREFIX)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_REST_ARG_PREFIX, "*");
                    }
                    return false;
                }
                yylex();

                seen_star = true;
            }
            else if (true /*epsilon*/)
            {
                seen_star = false;
            }
            else
            {
                return false;
            }
            if (yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BINARY
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                Mlhs_itemAst *__node_177 = 0;
                if (!parseMlhs_item(&__node_177))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Mlhs_itemKind, "mlhs_item");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (seen_star) break;
        }
        while (yytoken == Token_COMMA);
        if (yytoken == Token_ASSIGN
            || yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
        {
            OperatorAssignAst *__node_178 = 0;
            if (!parseOperatorAssign(&__node_178))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorAssignKind, "operatorAssign");
                }
                return false;
            }
            MrhsAst *__node_179 = 0;
            if (!parseMrhs(&__node_179))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MrhsKind, "mrhs");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePowerExpression(PowerExpressionAst **yynode)
{
    *yynode = create<PowerExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        UnaryExpressionAst *__node_180 = 0;
        if (!parseUnaryExpression(&__node_180))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
            }
            return false;
        }
        while (yytoken == Token_POWER)
        {
            OperatorPowerAst *__node_181 = 0;
            if (!parseOperatorPower(&__node_181))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorPowerKind, "operatorPower");
                }
                return false;
            }
            UnaryExpressionAst *__node_182 = 0;
            if (!parseUnaryExpression(&__node_182))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePredefinedValue(PredefinedValueAst **yynode)
{
    *yynode = create<PredefinedValueAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_LINE
        || yytoken == Token_NIL
        || yytoken == Token_TRUE)
    {
        if (yytoken == Token_NIL)
        {
            if (yytoken != Token_NIL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_NIL, "nil");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_TRUE)
        {
            if (yytoken != Token_TRUE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TRUE, "true");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FALSE)
        {
            if (yytoken != Token_FALSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FALSE, "false");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FILE)
        {
            if (yytoken != Token_FILE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FILE, "__FILE__");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LINE)
        {
            if (yytoken != Token_LINE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE, "__LINE__");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePrimaryExpression(PrimaryExpressionAst **yynode)
{
    *yynode = create<PrimaryExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NIL
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_LEADING_TWO_COLON)
        {
            if (yytoken != Token_LEADING_TWO_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LEADING_TWO_COLON, "::");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_FUNCTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNCTION, "function");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CLASS_VARIABLE
                 || yytoken == Token_CONSTANT
                 || yytoken == Token_FALSE
                 || yytoken == Token_FILE
                 || yytoken == Token_FUNCTION
                 || yytoken == Token_GLOBAL_VARIABLE
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_INSTANCE_VARIABLE
                 || yytoken == Token_LINE
                 || yytoken == Token_NIL
                 || yytoken == Token_SELF
                 || yytoken == Token_SUPER
                 || yytoken == Token_TRUE)
        {
            VariableAst *__node_183 = 0;
            if (!parseVariable(&__node_183))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableKind, "variable");
                }
                return false;
            }
        }
        else if (yytoken == Token_ASCII_VALUE
                 || yytoken == Token_BINARY
                 || yytoken == Token_FLOAT
                 || yytoken == Token_HEX
                 || yytoken == Token_INTEGER
                 || yytoken == Token_OCTAL)
        {
            NumericAst *__node_184 = 0;
            if (!parseNumeric(&__node_184))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::NumericKind, "numeric");
                }
                return false;
            }
        }
        else if (yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                 || yytoken == Token_COMMAND_OUTPUT
                 || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_DOUBLE_QUOTED_STRING
                 || yytoken == Token_HERE_DOC_BEGIN
                 || yytoken == Token_REGEX
                 || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_SINGLE_QUOTED_STRING
                 || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_W_ARRAY)
        {
            LiteralAst *__node_185 = 0;
            if (!parseLiteral(&__node_185))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::LiteralKind, "literal");
                }
                return false;
            }
        }
        else if (yytoken == Token_LBRACK)
        {
            ArrayExpressionAst *__node_186 = 0;
            if (!parseArrayExpression(&__node_186))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ArrayExpressionKind, "arrayExpression");
                }
                return false;
            }
        }
        else if (yytoken == Token_LCURLY_HASH)
        {
            HashExpressionAst *__node_187 = 0;
            if (!parseHashExpression(&__node_187))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::HashExpressionKind, "hashExpression");
                }
                return false;
            }
        }
        else if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            CompoundStatementAst *__node_188 = 0;
            if (!parseCompoundStatement(&__node_188))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IF)
        {
            IfExpressionAst *__node_189 = 0;
            if (!parseIfExpression(&__node_189))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IfExpressionKind, "ifExpression");
                }
                return false;
            }
        }
        else if (yytoken == Token_UNLESS)
        {
            UnlessExpressionAst *__node_190 = 0;
            if (!parseUnlessExpression(&__node_190))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnlessExpressionKind, "unlessExpression");
                }
                return false;
            }
        }
        else if (yytoken == Token_WHILE)
        {
            WhileExpressionAst *__node_191 = 0;
            if (!parseWhileExpression(&__node_191))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::WhileExpressionKind, "whileExpression");
                }
                return false;
            }
        }
        else if (yytoken == Token_UNTIL)
        {
            UntilExpressionAst *__node_192 = 0;
            if (!parseUntilExpression(&__node_192))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UntilExpressionKind, "untilExpression");
                }
                return false;
            }
        }
        else if (yytoken == Token_CASE)
        {
            CaseExpressionAst *__node_193 = 0;
            if (!parseCaseExpression(&__node_193))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CaseExpressionKind, "caseExpression");
                }
                return false;
            }
        }
        else if (yytoken == Token_FOR)
        {
            ForExpressionAst *__node_194 = 0;
            if (!parseForExpression(&__node_194))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ForExpressionKind, "forExpression");
                }
                return false;
            }
        }
        else if (yytoken == Token_BEGIN)
        {
            ExceptionHandlingExpressionAst *__node_195 = 0;
            if (!parseExceptionHandlingExpression(&__node_195))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExceptionHandlingExpressionKind, "exceptionHandlingExpression");
                }
                return false;
            }
        }
        else if (yytoken == Token_MODULE)
        {
            ModuleDefinitionAst *__node_196 = 0;
            if (!parseModuleDefinition(&__node_196))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ModuleDefinitionKind, "moduleDefinition");
                }
                return false;
            }
        }
        else if (yytoken == Token_CLASS)
        {
            ClassDefinitionAst *__node_197 = 0;
            if (!parseClassDefinition(&__node_197))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassDefinitionKind, "classDefinition");
                }
                return false;
            }
        }
        else if (yytoken == Token_DEF)
        {
            MethodDefinitionAst *__node_198 = 0;
            if (!parseMethodDefinition(&__node_198))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MethodDefinitionKind, "methodDefinition");
                }
                return false;
            }
        }
        else if (yytoken == Token_RETRY)
        {
            if (yytoken != Token_RETRY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RETRY, "retry");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_YIELD)
        {
            if (yytoken != Token_YIELD)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_YIELD, "yield");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DEFINED)
        {
            KeywordDefinedAst *__node_199 = 0;
            if (!parseKeywordDefined(&__node_199))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordDefinedKind, "keywordDefined");
                }
                return false;
            }
        }
        else if (yytoken == Token_REDO)
        {
            if (yytoken != Token_REDO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REDO, "redo");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_COMMENT)
        {
            if (yytoken != Token_COMMENT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMENT, "comment");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseProgram(ProgramAst **yynode)
{
    *yynode = create<ProgramAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_END_UPCASE
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LINE_BREAK
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SEMI
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD || yytoken == Token_EOF)
    {
        if (yytoken == Token_ALIAS
            || yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_END_UPCASE
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LINE_BREAK
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SEMI
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            CompoundStatementAst *__node_200 = 0;
            if (!parseCompoundStatement(&__node_200))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
            (*yynode)->compoundStatement = __node_200;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (Token_EOF != yytoken)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRangeExpression(RangeExpressionAst **yynode)
{
    *yynode = create<RangeExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        LogicalOrExpressionAst *__node_201 = 0;
        if (!parseLogicalOrExpression(&__node_201))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LogicalOrExpressionKind, "logicalOrExpression");
            }
            return false;
        }
        while (yytoken == Token_EXCLUSIVE_RANGE
               || yytoken == Token_INCLUSIVE_RANGE)
        {
            if (yytoken == Token_INCLUSIVE_RANGE)
            {
                OperatorInclusiveRangeAst *__node_202 = 0;
                if (!parseOperatorInclusiveRange(&__node_202))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorInclusiveRangeKind, "operatorInclusiveRange");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_EXCLUSIVE_RANGE)
            {
                OperatorExclusiveRangeAst *__node_203 = 0;
                if (!parseOperatorExclusiveRange(&__node_203))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorExclusiveRangeKind, "operatorExclusiveRange");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
            LogicalOrExpressionAst *__node_204 = 0;
            if (!parseLogicalOrExpression(&__node_204))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::LogicalOrExpressionKind, "logicalOrExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRegex(RegexAst **yynode)
{
    *yynode = create<RegexAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION)
    {
        if (yytoken == Token_REGEX)
        {
            if (yytoken != Token_REGEX)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REGEX, "regular expression");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION)
        {
            if (yytoken != Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION, "regular expression before expression substitution");
                }
                return false;
            }
            yylex();

            ExpressionSubstitutionAst *__node_205 = 0;
            if (!parseExpressionSubstitution(&__node_205))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionSubstitutionKind, "expressionSubstitution");
                }
                return false;
            }
            while (yytoken == Token_STRING_BETWEEN_EXPRESSION_SUBSTITUTION)
            {
                if (yytoken != Token_STRING_BETWEEN_EXPRESSION_SUBSTITUTION)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STRING_BETWEEN_EXPRESSION_SUBSTITUTION, "string between expression substitution");
                    }
                    return false;
                }
                yylex();

                ExpressionSubstitutionAst *__node_206 = 0;
                if (!parseExpressionSubstitution(&__node_206))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionSubstitutionKind, "expressionSubstitution");
                    }
                    return false;
                }
            }
            if (yytoken != Token_STRING_AFTER_EXPRESSION_SUBSTITUTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING_AFTER_EXPRESSION_SUBSTITUTION, "string after expression substitution");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRelationalExpression(RelationalExpressionAst **yynode)
{
    *yynode = create<RelationalExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        OrExpressionAst *__node_207 = 0;
        if (!parseOrExpression(&__node_207))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OrExpressionKind, "orExpression");
            }
            return false;
        }
        while (yytoken == Token_GREATER_OR_EQUAL
               || yytoken == Token_GREATER_THAN
               || yytoken == Token_LESS_OR_EQUAL
               || yytoken == Token_LESS_THAN)
        {
            if (yytoken == Token_LESS_THAN)
            {
                OperatorLessThanAst *__node_208 = 0;
                if (!parseOperatorLessThan(&__node_208))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorLessThanKind, "operatorLessThan");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_GREATER_THAN)
            {
                OperatorGreaterThanAst *__node_209 = 0;
                if (!parseOperatorGreaterThan(&__node_209))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorGreaterThanKind, "operatorGreaterThan");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_LESS_OR_EQUAL)
            {
                OperatorLessOrEqualAst *__node_210 = 0;
                if (!parseOperatorLessOrEqual(&__node_210))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorLessOrEqualKind, "operatorLessOrEqual");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_GREATER_OR_EQUAL)
            {
                OperatorGreaterOrEqualAst *__node_211 = 0;
                if (!parseOperatorGreaterOrEqual(&__node_211))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorGreaterOrEqualKind, "operatorGreaterOrEqual");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
            OrExpressionAst *__node_212 = 0;
            if (!parseOrExpression(&__node_212))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OrExpressionKind, "orExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRestMethodDefinitionArgument(RestMethodDefinitionArgumentAst **yynode)
{
    *yynode = create<RestMethodDefinitionArgumentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if ((yytoken == Token_STAR) && ( expect_array_or_block_arguments ))
    {
        if (yytoken != Token_STAR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_STAR, "*");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_FUNCTION
            || yytoken == Token_IDENTIFIER)
        {
            if (yytoken == Token_IDENTIFIER)
            {
                if (yytoken != Token_IDENTIFIER)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_FUNCTION)
            {
                if (yytoken != Token_FUNCTION)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FUNCTION, "function");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            if (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                BlockMethodDefinitionArgumentAst *__node_213 = 0;
                if (!parseBlockMethodDefinitionArgument(&__node_213))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::BlockMethodDefinitionArgumentKind, "blockMethodDefinitionArgument");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        expect_array_or_block_arguments = false;
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRestMethodInvocationArgument(RestMethodInvocationArgumentAst **yynode)
{
    *yynode = create<RestMethodInvocationArgumentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_REST_ARG_PREFIX)
    {
        if (yytoken != Token_REST_ARG_PREFIX)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_REST_ARG_PREFIX, "*");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_214 = 0;
        if (!parseExpression(&__node_214))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        if (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            BlockMethodInvocationArgumentAst *__node_215 = 0;
            if (!parseBlockMethodInvocationArgument(&__node_215))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockMethodInvocationArgumentKind, "blockMethodInvocationArgument");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseShiftExpression(ShiftExpressionAst **yynode)
{
    *yynode = create<ShiftExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        AdditiveExpressionAst *__node_216 = 0;
        if (!parseAdditiveExpression(&__node_216))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AdditiveExpressionKind, "additiveExpression");
            }
            return false;
        }
        while (yytoken == Token_LEFT_SHIFT
               || yytoken == Token_RIGHT_SHIFT)
        {
            if (yytoken == Token_LEFT_SHIFT)
            {
                OperatorLeftShiftAst *__node_217 = 0;
                if (!parseOperatorLeftShift(&__node_217))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorLeftShiftKind, "operatorLeftShift");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_RIGHT_SHIFT)
            {
                OperatorRightShiftAst *__node_218 = 0;
                if (!parseOperatorRightShift(&__node_218))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorRightShiftKind, "operatorRightShift");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
            AdditiveExpressionAst *__node_219 = 0;
            if (!parseAdditiveExpression(&__node_219))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AdditiveExpressionKind, "additiveExpression");
                }
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStatement(StatementAst **yynode)
{
    *yynode = create<StatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_END_UPCASE
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        StatementWithoutModifierAst *__node_220 = 0;
        if (!parseStatementWithoutModifier(&__node_220))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::StatementWithoutModifierKind, "statementWithoutModifier");
            }
            return false;
        }
        (*yynode)->statementBody = __node_220;

        std::cout << "stmt" << std::endl;
        while (yytoken == Token_IF
               || yytoken == Token_RESCUE_MODIFIER
               || yytoken == Token_UNLESS
               || yytoken == Token_UNTIL
               || yytoken == Token_WHILE)
        {
            if (yytoken == Token_IF)
            {
                if (yytoken != Token_IF)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_IF, "if");
                    }
                    return false;
                }
                yylex();

                ExpressionAst *__node_221 = 0;
                if (!parseExpression(&__node_221))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_UNLESS)
            {
                if (yytoken != Token_UNLESS)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_UNLESS, "unless");
                    }
                    return false;
                }
                yylex();

                std::cout << "unless here" << std::endl;
                ExpressionAst *__node_222 = 0;
                if (!parseExpression(&__node_222))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_WHILE)
            {
                if (yytoken != Token_WHILE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_WHILE, "while");
                    }
                    return false;
                }
                yylex();

                ExpressionAst *__node_223 = 0;
                if (!parseExpression(&__node_223))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_UNTIL)
            {
                if (yytoken != Token_UNTIL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_UNTIL, "until");
                    }
                    return false;
                }
                yylex();

                ExpressionAst *__node_224 = 0;
                if (!parseExpression(&__node_224))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_RESCUE_MODIFIER)
            {
                if (yytoken != Token_RESCUE_MODIFIER)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RESCUE_MODIFIER, "rescue");
                    }
                    return false;
                }
                yylex();

                ExpressionAst *__node_225 = 0;
                if (!parseExpression(&__node_225))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStatementWithoutModifier(StatementWithoutModifierAst **yynode)
{
    *yynode = create<StatementWithoutModifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_END_UPCASE
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_ALIAS)
        {
            KeywordAliasAst *__node_226 = 0;
            if (!parseKeywordAlias(&__node_226))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordAliasKind, "keywordAlias");
                }
                return false;
            }
            AliasParameterAst *__node_227 = 0;
            if (!parseAliasParameter(&__node_227))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AliasParameterKind, "aliasParameter");
                }
                return false;
            }
            if (yytoken == Token_LINE_BREAK)
            {
                if (yytoken != Token_LINE_BREAK)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LINE_BREAK, "line break");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            AliasParameterAst *__node_228 = 0;
            if (!parseAliasParameter(&__node_228))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AliasParameterKind, "aliasParameter");
                }
                return false;
            }
        }
        else if (yytoken == Token_UNDEF)
        {
            KeywordUndefAst *__node_229 = 0;
            if (!parseKeywordUndef(&__node_229))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordUndefKind, "keywordUndef");
                }
                return false;
            }
            UndefParameterAst *__node_230 = 0;
            if (!parseUndefParameter(&__node_230))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UndefParameterKind, "undefParameter");
                }
                return false;
            }
            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                UndefParameterAst *__node_231 = 0;
                if (!parseUndefParameter(&__node_231))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::UndefParameterKind, "undefParameter");
                    }
                    return false;
                }
            }
        }
        else if (yytoken == Token_BEGIN_UPCASE)
        {
            KeywordBeginUpcaseAst *__node_232 = 0;
            if (!parseKeywordBeginUpcase(&__node_232))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordBeginUpcaseKind, "keywordBeginUpcase");
                }
                return false;
            }
            if (yytoken != Token_LCURLY_BLOCK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LCURLY_BLOCK, "{");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LINE_BREAK
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SEMI
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                CompoundStatementAst *__node_233 = 0;
                if (!parseCompoundStatement(&__node_233))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RCURLY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RCURLY, "}");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_END_UPCASE)
        {
            KeywordEndUpcaseAst *__node_234 = 0;
            if (!parseKeywordEndUpcase(&__node_234))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordEndUpcaseKind, "keywordEndUpcase");
                }
                return false;
            }
            if (yytoken != Token_LCURLY_BLOCK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LCURLY_BLOCK, "{");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LINE_BREAK
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SEMI
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                CompoundStatementAst *__node_235 = 0;
                if (!parseCompoundStatement(&__node_235))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RCURLY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RCURLY, "}");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_ASCII_VALUE
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BINARY
                 || yytoken == Token_BNOT
                 || yytoken == Token_BREAK
                 || yytoken == Token_CASE
                 || yytoken == Token_CLASS
                 || yytoken == Token_CLASS_VARIABLE
                 || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                 || yytoken == Token_COMMAND_OUTPUT
                 || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_COMMENT
                 || yytoken == Token_CONSTANT
                 || yytoken == Token_DEF
                 || yytoken == Token_DEFINED
                 || yytoken == Token_DOUBLE_QUOTED_STRING
                 || yytoken == Token_FALSE
                 || yytoken == Token_FILE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_FOR
                 || yytoken == Token_FUNCTION
                 || yytoken == Token_GLOBAL_VARIABLE
                 || yytoken == Token_HERE_DOC_BEGIN
                 || yytoken == Token_HEX
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_IF
                 || yytoken == Token_INSTANCE_VARIABLE
                 || yytoken == Token_INTEGER
                 || yytoken == Token_KEYWORD_NOT
                 || yytoken == Token_LBRACK
                 || yytoken == Token_LCURLY_HASH
                 || yytoken == Token_LEADING_TWO_COLON
                 || yytoken == Token_LINE
                 || yytoken == Token_LPAREN
                 || yytoken == Token_MODULE
                 || yytoken == Token_NEXT
                 || yytoken == Token_NIL
                 || yytoken == Token_NOT
                 || yytoken == Token_OCTAL
                 || yytoken == Token_REDO
                 || yytoken == Token_REGEX
                 || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_RETRY
                 || yytoken == Token_RETURN
                 || yytoken == Token_SELF
                 || yytoken == Token_SINGLE_QUOTED_STRING
                 || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                 || yytoken == Token_SUPER
                 || yytoken == Token_TRUE
                 || yytoken == Token_UNARY_MINUS
                 || yytoken == Token_UNARY_PLUS
                 || yytoken == Token_UNLESS
                 || yytoken == Token_UNTIL
                 || yytoken == Token_WHILE
                 || yytoken == Token_W_ARRAY
                 || yytoken == Token_YIELD)
        {
            ExpressionAst *__node_236 = 0;
            if (!parseExpression(&__node_236))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->expression = __node_236;

            if (yytoken == Token_COMMA)
            {
                ParallelAssignmentLeftOverAst *__node_237 = 0;
                if (!parseParallelAssignmentLeftOver(&__node_237))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ParallelAssignmentLeftOverKind, "parallelAssignmentLeftOver");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_REST_ARG_PREFIX)
        {
            if (yytoken != Token_REST_ARG_PREFIX)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REST_ARG_PREFIX, "*");
                }
                return false;
            }
            yylex();

            Mlhs_itemAst *__node_238 = 0;
            if (!parseMlhs_item(&__node_238))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Mlhs_itemKind, "mlhs_item");
                }
                return false;
            }
            OperatorAssignAst *__node_239 = 0;
            if (!parseOperatorAssign(&__node_239))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorAssignKind, "operatorAssign");
                }
                return false;
            }
            MrhsAst *__node_240 = 0;
            if (!parseMrhs(&__node_240))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MrhsKind, "mrhs");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStatements(StatementsAst **yynode)
{
    *yynode = create<StatementsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_END_UPCASE
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_KEYWORD_NOT
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_REST_ARG_PREFIX
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        StatementAst *__node_241 = 0;
        if (!parseStatement(&__node_241))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::StatementKind, "statement");
            }
            return false;
        }
        (*yynode)->statementSequence = snoc((*yynode)->statementSequence, __node_241, memoryPool);

        while (yytoken == Token_LINE_BREAK
               || yytoken == Token_SEMI)
        {
            TerminalAst *__node_242 = 0;
            if (!parseTerminal(&__node_242))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TerminalKind, "terminal");
                }
                return false;
            }
            if (yytoken == Token_EOF) break;
            if ((yytoken == Token_LCURLY) || (yytoken == Token_END) //block end
                || (yytoken == Token_RPAREN) || (yytoken == Token_ELSE)
                || (yytoken == Token_ELSIF) || (yytoken == Token_RESCUE)
                || (yytoken == Token_ENSURE) || (yytoken == Token_WHEN) )
                break;
            StatementAst *__node_243 = 0;
            if (!parseStatement(&__node_243))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statementSequence = snoc((*yynode)->statementSequence, __node_243, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseString(StringAst **yynode)
{
    *yynode = create<StringAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION)
    {
        if (yytoken == Token_DOUBLE_QUOTED_STRING)
        {
            if (yytoken != Token_DOUBLE_QUOTED_STRING)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOUBLE_QUOTED_STRING, "double quoted string");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SINGLE_QUOTED_STRING)
        {
            if (yytoken != Token_SINGLE_QUOTED_STRING)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SINGLE_QUOTED_STRING, "single quoted string");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION)
        {
            if (yytoken != Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION, "string before expression substitution");
                }
                return false;
            }
            yylex();

            ExpressionSubstitutionAst *__node_244 = 0;
            if (!parseExpressionSubstitution(&__node_244))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionSubstitutionKind, "expressionSubstitution");
                }
                return false;
            }
            while (yytoken == Token_STRING_BETWEEN_EXPRESSION_SUBSTITUTION)
            {
                if (yytoken != Token_STRING_BETWEEN_EXPRESSION_SUBSTITUTION)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STRING_BETWEEN_EXPRESSION_SUBSTITUTION, "string between expression substitution");
                    }
                    return false;
                }
                yylex();

                ExpressionSubstitutionAst *__node_245 = 0;
                if (!parseExpressionSubstitution(&__node_245))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionSubstitutionKind, "expressionSubstitution");
                    }
                    return false;
                }
            }
            if (yytoken != Token_STRING_AFTER_EXPRESSION_SUBSTITUTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING_AFTER_EXPRESSION_SUBSTITUTION, "string after expression substitution");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSymbol(SymbolAst **yynode)
{
    *yynode = create<SymbolAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE)
    {
        if (yytoken != Token_COLON_WITH_NO_FOLLOWING_SPACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COLON_WITH_NO_FOLLOWING_SPACE, ":");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_FUNCTION)
        {
            if (yytoken != Token_FUNCTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNCTION, "function");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_CONSTANT)
        {
            if (yytoken != Token_CONSTANT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONSTANT, "constant");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_GLOBAL_VARIABLE)
        {
            if (yytoken != Token_GLOBAL_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GLOBAL_VARIABLE, "global variable");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_INSTANCE_VARIABLE)
        {
            if (yytoken != Token_INSTANCE_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INSTANCE_VARIABLE, "instance variable");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CLASS_VARIABLE)
        {
            if (yytoken != Token_CLASS_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CLASS_VARIABLE, "class variable");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_UNARY_PLUS_MINUS_METHOD_NAME)
        {
            if (yytoken != Token_UNARY_PLUS_MINUS_METHOD_NAME)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNARY_PLUS_MINUS_METHOD_NAME, "+/- method");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BAND
                 || yytoken == Token_BNOT
                 || yytoken == Token_BOR
                 || yytoken == Token_BXOR
                 || yytoken == Token_CASE_EQUAL
                 || yytoken == Token_COMPARE
                 || yytoken == Token_DIV
                 || yytoken == Token_EQUAL
                 || yytoken == Token_GREATER_OR_EQUAL
                 || yytoken == Token_GREATER_THAN
                 || yytoken == Token_LBRACK
                 || yytoken == Token_LBRACK_ARRAY_ACCESS
                 || yytoken == Token_LEFT_SHIFT
                 || yytoken == Token_LESS_OR_EQUAL
                 || yytoken == Token_LESS_THAN
                 || yytoken == Token_MATCH
                 || yytoken == Token_MINUS
                 || yytoken == Token_MOD
                 || yytoken == Token_PLUS
                 || yytoken == Token_POWER
                 || yytoken == Token_RIGHT_SHIFT
                 || yytoken == Token_SINGLE_QUOTE
                 || yytoken == Token_STAR)
        {
            OperatorAsMethodnameAst *__node_246 = 0;
            if (!parseOperatorAsMethodname(&__node_246))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorAsMethodnameKind, "operatorAsMethodname");
                }
                return false;
            }
        }
        else if (yytoken == Token_ALIAS
                 || yytoken == Token_AND
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BEGIN_UPCASE
                 || yytoken == Token_BREAK
                 || yytoken == Token_CASE
                 || yytoken == Token_CLASS
                 || yytoken == Token_DEF
                 || yytoken == Token_DEFINED
                 || yytoken == Token_DO
                 || yytoken == Token_ELSE
                 || yytoken == Token_ELSIF
                 || yytoken == Token_END
                 || yytoken == Token_END_UPCASE
                 || yytoken == Token_ENSURE
                 || yytoken == Token_FALSE
                 || yytoken == Token_FILE
                 || yytoken == Token_FOR
                 || yytoken == Token_IF
                 || yytoken == Token_IN
                 || yytoken == Token_LINE
                 || yytoken == Token_MODULE
                 || yytoken == Token_NEXT
                 || yytoken == Token_NIL
                 || yytoken == Token_NOT
                 || yytoken == Token_OR
                 || yytoken == Token_REDO
                 || yytoken == Token_RESCUE
                 || yytoken == Token_RETRY
                 || yytoken == Token_RETURN
                 || yytoken == Token_SELF
                 || yytoken == Token_SUPER
                 || yytoken == Token_THEN
                 || yytoken == Token_TRUE
                 || yytoken == Token_UNDEF
                 || yytoken == Token_UNLESS
                 || yytoken == Token_UNTIL
                 || yytoken == Token_WHEN
                 || yytoken == Token_WHILE
                 || yytoken == Token_YIELD)
        {
            KeywordAst *__node_247 = 0;
            if (!parseKeyword(&__node_247))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordKind, "keyword");
                }
                return false;
            }
        }
        else if (yytoken == Token_DOUBLE_QUOTED_STRING
                 || yytoken == Token_SINGLE_QUOTED_STRING
                 || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION)
        {
            StringAst *__node_248 = 0;
            if (!parseString(&__node_248))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StringKind, "string");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTerminal(TerminalAst **yynode)
{
    *yynode = create<TerminalAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LINE_BREAK
        || yytoken == Token_SEMI)
    {
        if (yytoken == Token_SEMI)
        {
            if (yytoken != Token_SEMI)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMI, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LINE_BREAK)
        {
            if (yytoken != Token_LINE_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LINE_BREAK, "line break");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTernaryIfThenElseExpression(TernaryIfThenElseExpressionAst **yynode)
{
    *yynode = create<TernaryIfThenElseExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        AssignmentExpressionAst *__node_249 = 0;
        if (!parseAssignmentExpression(&__node_249))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AssignmentExpressionKind, "assignmentExpression");
            }
            return false;
        }
        if (yytoken == Token_QUESTION)
        {
            OperatorQuestionAst *__node_250 = 0;
            if (!parseOperatorQuestion(&__node_250))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorQuestionKind, "operatorQuestion");
                }
                return false;
            }
            TernaryIfThenElseExpressionAst *__node_251 = 0;
            if (!parseTernaryIfThenElseExpression(&__node_251))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TernaryIfThenElseExpressionKind, "ternaryIfThenElseExpression");
                }
                return false;
            }
            OperatorColonAst *__node_252 = 0;
            if (!parseOperatorColon(&__node_252))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorColonKind, "operatorColon");
                }
                return false;
            }
            TernaryIfThenElseExpressionAst *__node_253 = 0;
            if (!parseTernaryIfThenElseExpression(&__node_253))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TernaryIfThenElseExpressionKind, "ternaryIfThenElseExpression");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseThenOrTerminalOrColon(ThenOrTerminalOrColonAst **yynode)
{
    *yynode = create<ThenOrTerminalOrColonAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COLON
        || yytoken == Token_LINE_BREAK
        || yytoken == Token_SEMI
        || yytoken == Token_THEN)
    {
        if (yytoken == Token_THEN)
        {
            if (yytoken != Token_THEN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_THEN, "then");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LINE_BREAK
                 || yytoken == Token_SEMI)
        {
            TerminalAst *__node_254 = 0;
            if (!parseTerminal(&__node_254))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TerminalKind, "terminal");
                }
                return false;
            }
            if (yytoken == Token_THEN)
            {
                if (yytoken != Token_THEN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_THEN, "then");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseUnaryExpression(UnaryExpressionAst **yynode)
{
    *yynode = create<UnaryExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASCII_VALUE
        || yytoken == Token_BEGIN
        || yytoken == Token_BINARY
        || yytoken == Token_BNOT
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CLASS
        || yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMMAND_OUTPUT
        || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_COMMENT
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DOUBLE_QUOTED_STRING
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FLOAT
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_HERE_DOC_BEGIN
        || yytoken == Token_HEX
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_INTEGER
        || yytoken == Token_LBRACK
        || yytoken == Token_LCURLY_HASH
        || yytoken == Token_LEADING_TWO_COLON
        || yytoken == Token_LINE
        || yytoken == Token_LPAREN
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NIL
        || yytoken == Token_NOT
        || yytoken == Token_OCTAL
        || yytoken == Token_REDO
        || yytoken == Token_REGEX
        || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_SELF
        || yytoken == Token_SINGLE_QUOTED_STRING
        || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE
        || yytoken == Token_UNARY_MINUS
        || yytoken == Token_UNARY_PLUS
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHILE
        || yytoken == Token_W_ARRAY
        || yytoken == Token_YIELD)
    {
        while (yytoken == Token_BNOT
               || yytoken == Token_NOT
               || yytoken == Token_UNARY_MINUS
               || yytoken == Token_UNARY_PLUS)
        {
            if (yytoken == Token_UNARY_PLUS)
            {
                OperatorUnaryPlusAst *__node_255 = 0;
                if (!parseOperatorUnaryPlus(&__node_255))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorUnaryPlusKind, "operatorUnaryPlus");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_UNARY_MINUS)
            {
                OperatorUnaryMinusAst *__node_256 = 0;
                if (!parseOperatorUnaryMinus(&__node_256))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorUnaryMinusKind, "operatorUnaryMinus");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_BNOT)
            {
                OperatorBNotAst *__node_257 = 0;
                if (!parseOperatorBNot(&__node_257))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorBNotKind, "operatorBNot");
                    }
                    return false;
                }
            }
            else if (yytoken == Token_NOT)
            {
                OperatorNotAst *__node_258 = 0;
                if (!parseOperatorNot(&__node_258))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OperatorNotKind, "operatorNot");
                    }
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        DotAccessAst *__node_259 = 0;
        if (!parseDotAccess(&__node_259))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::DotAccessKind, "dotAccess");
            }
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseUndefParameter(UndefParameterAst **yynode)
{
    *yynode = create<UndefParameterAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ALIAS
        || yytoken == Token_AND
        || yytoken == Token_BAND
        || yytoken == Token_BEGIN
        || yytoken == Token_BEGIN_UPCASE
        || yytoken == Token_BNOT
        || yytoken == Token_BOR
        || yytoken == Token_BREAK
        || yytoken == Token_BXOR
        || yytoken == Token_CASE
        || yytoken == Token_CASE_EQUAL
        || yytoken == Token_CLASS
        || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
        || yytoken == Token_COMPARE
        || yytoken == Token_CONSTANT
        || yytoken == Token_DEF
        || yytoken == Token_DEFINED
        || yytoken == Token_DIV
        || yytoken == Token_DO
        || yytoken == Token_ELSE
        || yytoken == Token_ELSIF
        || yytoken == Token_END
        || yytoken == Token_END_UPCASE
        || yytoken == Token_ENSURE
        || yytoken == Token_EQUAL
        || yytoken == Token_FOR
        || yytoken == Token_FUNCTION
        || yytoken == Token_GREATER_OR_EQUAL
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_IN
        || yytoken == Token_LBRACK
        || yytoken == Token_LBRACK_ARRAY_ACCESS
        || yytoken == Token_LEFT_SHIFT
        || yytoken == Token_LESS_OR_EQUAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_MATCH
        || yytoken == Token_MINUS
        || yytoken == Token_MOD
        || yytoken == Token_MODULE
        || yytoken == Token_NEXT
        || yytoken == Token_NOT
        || yytoken == Token_OR
        || yytoken == Token_PLUS
        || yytoken == Token_POWER
        || yytoken == Token_REDO
        || yytoken == Token_RESCUE
        || yytoken == Token_RETRY
        || yytoken == Token_RETURN
        || yytoken == Token_RIGHT_SHIFT
        || yytoken == Token_SINGLE_QUOTE
        || yytoken == Token_STAR
        || yytoken == Token_SUPER
        || yytoken == Token_THEN
        || yytoken == Token_UNDEF
        || yytoken == Token_UNLESS
        || yytoken == Token_UNTIL
        || yytoken == Token_WHEN
        || yytoken == Token_WHILE
        || yytoken == Token_YIELD)
    {
        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_CONSTANT)
        {
            if (yytoken != Token_CONSTANT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONSTANT, "constant");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_FUNCTION)
        {
            if (yytoken != Token_FUNCTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNCTION, "function");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ASSIGN_WITH_NO_LEADING_SPACE)
            {
                if (yytoken != Token_ASSIGN_WITH_NO_LEADING_SPACE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN_WITH_NO_LEADING_SPACE, "=");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE)
        {
            SymbolAst *__node_260 = 0;
            if (!parseSymbol(&__node_260))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SymbolKind, "symbol");
                }
                return false;
            }
        }
        else if (yytoken == Token_ALIAS
                 || yytoken == Token_AND
                 || yytoken == Token_BEGIN
                 || yytoken == Token_BEGIN_UPCASE
                 || yytoken == Token_BREAK
                 || yytoken == Token_CASE
                 || yytoken == Token_CLASS
                 || yytoken == Token_DEF
                 || yytoken == Token_DEFINED
                 || yytoken == Token_DO
                 || yytoken == Token_ELSE
                 || yytoken == Token_ELSIF
                 || yytoken == Token_END
                 || yytoken == Token_END_UPCASE
                 || yytoken == Token_ENSURE
                 || yytoken == Token_FOR
                 || yytoken == Token_IF
                 || yytoken == Token_IN
                 || yytoken == Token_MODULE
                 || yytoken == Token_NEXT
                 || yytoken == Token_NOT
                 || yytoken == Token_OR
                 || yytoken == Token_REDO
                 || yytoken == Token_RESCUE
                 || yytoken == Token_RETRY
                 || yytoken == Token_RETURN
                 || yytoken == Token_SUPER
                 || yytoken == Token_THEN
                 || yytoken == Token_UNDEF
                 || yytoken == Token_UNLESS
                 || yytoken == Token_UNTIL
                 || yytoken == Token_WHEN
                 || yytoken == Token_WHILE
                 || yytoken == Token_YIELD)
        {
            KeywordAsMethodNameAst *__node_261 = 0;
            if (!parseKeywordAsMethodName(&__node_261))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::KeywordAsMethodNameKind, "keywordAsMethodName");
                }
                return false;
            }
        }
        else if (yytoken == Token_BAND
                 || yytoken == Token_BNOT
                 || yytoken == Token_BOR
                 || yytoken == Token_BXOR
                 || yytoken == Token_CASE_EQUAL
                 || yytoken == Token_COMPARE
                 || yytoken == Token_DIV
                 || yytoken == Token_EQUAL
                 || yytoken == Token_GREATER_OR_EQUAL
                 || yytoken == Token_GREATER_THAN
                 || yytoken == Token_LBRACK
                 || yytoken == Token_LBRACK_ARRAY_ACCESS
                 || yytoken == Token_LEFT_SHIFT
                 || yytoken == Token_LESS_OR_EQUAL
                 || yytoken == Token_LESS_THAN
                 || yytoken == Token_MATCH
                 || yytoken == Token_MINUS
                 || yytoken == Token_MOD
                 || yytoken == Token_PLUS
                 || yytoken == Token_POWER
                 || yytoken == Token_RIGHT_SHIFT
                 || yytoken == Token_SINGLE_QUOTE
                 || yytoken == Token_STAR)
        {
            OperatorAsMethodnameAst *__node_262 = 0;
            if (!parseOperatorAsMethodname(&__node_262))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OperatorAsMethodnameKind, "operatorAsMethodname");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseUnlessExpression(UnlessExpressionAst **yynode)
{
    *yynode = create<UnlessExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNLESS)
    {
        if (yytoken != Token_UNLESS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_UNLESS, "unless");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_263 = 0;
        if (!parseExpression(&__node_263))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        ThenOrTerminalOrColonAst *__node_264 = 0;
        if (!parseThenOrTerminalOrColon(&__node_264))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ThenOrTerminalOrColonKind, "thenOrTerminalOrColon");
            }
            return false;
        }
        if (yytoken == Token_ALIAS
            || yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_END_UPCASE
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LINE_BREAK
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SEMI
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            CompoundStatementAst *__node_265 = 0;
            if (!parseCompoundStatement(&__node_265))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_ELSE)
        {
            if (yytoken != Token_ELSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELSE, "else");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_ALIAS
                || yytoken == Token_ASCII_VALUE
                || yytoken == Token_BEGIN
                || yytoken == Token_BEGIN_UPCASE
                || yytoken == Token_BINARY
                || yytoken == Token_BNOT
                || yytoken == Token_BREAK
                || yytoken == Token_CASE
                || yytoken == Token_CLASS
                || yytoken == Token_CLASS_VARIABLE
                || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
                || yytoken == Token_COMMAND_OUTPUT
                || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_COMMENT
                || yytoken == Token_CONSTANT
                || yytoken == Token_DEF
                || yytoken == Token_DEFINED
                || yytoken == Token_DOUBLE_QUOTED_STRING
                || yytoken == Token_END_UPCASE
                || yytoken == Token_FALSE
                || yytoken == Token_FILE
                || yytoken == Token_FLOAT
                || yytoken == Token_FOR
                || yytoken == Token_FUNCTION
                || yytoken == Token_GLOBAL_VARIABLE
                || yytoken == Token_HERE_DOC_BEGIN
                || yytoken == Token_HEX
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_IF
                || yytoken == Token_INSTANCE_VARIABLE
                || yytoken == Token_INTEGER
                || yytoken == Token_KEYWORD_NOT
                || yytoken == Token_LBRACK
                || yytoken == Token_LCURLY_HASH
                || yytoken == Token_LEADING_TWO_COLON
                || yytoken == Token_LINE
                || yytoken == Token_LINE_BREAK
                || yytoken == Token_LPAREN
                || yytoken == Token_MODULE
                || yytoken == Token_NEXT
                || yytoken == Token_NIL
                || yytoken == Token_NOT
                || yytoken == Token_OCTAL
                || yytoken == Token_REDO
                || yytoken == Token_REGEX
                || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_REST_ARG_PREFIX
                || yytoken == Token_RETRY
                || yytoken == Token_RETURN
                || yytoken == Token_SELF
                || yytoken == Token_SEMI
                || yytoken == Token_SINGLE_QUOTED_STRING
                || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
                || yytoken == Token_SUPER
                || yytoken == Token_TRUE
                || yytoken == Token_UNARY_MINUS
                || yytoken == Token_UNARY_PLUS
                || yytoken == Token_UNDEF
                || yytoken == Token_UNLESS
                || yytoken == Token_UNTIL
                || yytoken == Token_WHILE
                || yytoken == Token_W_ARRAY
                || yytoken == Token_YIELD)
            {
                CompoundStatementAst *__node_266 = 0;
                if (!parseCompoundStatement(&__node_266))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseUntilExpression(UntilExpressionAst **yynode)
{
    *yynode = create<UntilExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_UNTIL)
    {
        KeywordUntilAst *__node_267 = 0;
        if (!parseKeywordUntil(&__node_267))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::KeywordUntilKind, "keywordUntil");
            }
            return false;
        }
        ExpressionAst *__node_268 = 0;
        if (!parseExpression(&__node_268))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        DoOrTerminalOrColonAst *__node_269 = 0;
        if (!parseDoOrTerminalOrColon(&__node_269))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::DoOrTerminalOrColonKind, "doOrTerminalOrColon");
            }
            return false;
        }
        if (yytoken == Token_ALIAS
            || yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_END_UPCASE
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LINE_BREAK
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SEMI
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            CompoundStatementAst *__node_270 = 0;
            if (!parseCompoundStatement(&__node_270))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariable(VariableAst **yynode)
{
    *yynode = create<VariableAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CLASS_VARIABLE
        || yytoken == Token_CONSTANT
        || yytoken == Token_FALSE
        || yytoken == Token_FILE
        || yytoken == Token_FUNCTION
        || yytoken == Token_GLOBAL_VARIABLE
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_INSTANCE_VARIABLE
        || yytoken == Token_LINE
        || yytoken == Token_NIL
        || yytoken == Token_SELF
        || yytoken == Token_SUPER
        || yytoken == Token_TRUE)
    {
        if (yytoken == Token_FUNCTION)
        {
            if (yytoken != Token_FUNCTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FUNCTION, "function");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SELF)
        {
            if (yytoken != Token_SELF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SELF, "self");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SUPER)
        {
            if (yytoken != Token_SUPER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SUPER, "super");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CONSTANT)
        {
            if (yytoken != Token_CONSTANT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONSTANT, "constant");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_INSTANCE_VARIABLE)
        {
            if (yytoken != Token_INSTANCE_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INSTANCE_VARIABLE, "instance variable");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_GLOBAL_VARIABLE)
        {
            if (yytoken != Token_GLOBAL_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GLOBAL_VARIABLE, "global variable");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CLASS_VARIABLE)
        {
            if (yytoken != Token_CLASS_VARIABLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CLASS_VARIABLE, "class variable");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FALSE
                 || yytoken == Token_FILE
                 || yytoken == Token_LINE
                 || yytoken == Token_NIL
                 || yytoken == Token_TRUE)
        {
            PredefinedValueAst *__node_271 = 0;
            if (!parsePredefinedValue(&__node_271))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::PredefinedValueKind, "predefinedValue");
                }
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseWhileExpression(WhileExpressionAst **yynode)
{
    *yynode = create<WhileExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_WHILE)
    {
        KeywordWhileAst *__node_272 = 0;
        if (!parseKeywordWhile(&__node_272))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::KeywordWhileKind, "keywordWhile");
            }
            return false;
        }
        ExpressionAst *__node_273 = 0;
        if (!parseExpression(&__node_273))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        DoOrTerminalOrColonAst *__node_274 = 0;
        if (!parseDoOrTerminalOrColon(&__node_274))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::DoOrTerminalOrColonKind, "doOrTerminalOrColon");
            }
            return false;
        }
        if (yytoken == Token_ALIAS
            || yytoken == Token_ASCII_VALUE
            || yytoken == Token_BEGIN
            || yytoken == Token_BEGIN_UPCASE
            || yytoken == Token_BINARY
            || yytoken == Token_BNOT
            || yytoken == Token_BREAK
            || yytoken == Token_CASE
            || yytoken == Token_CLASS
            || yytoken == Token_CLASS_VARIABLE
            || yytoken == Token_COLON_WITH_NO_FOLLOWING_SPACE
            || yytoken == Token_COMMAND_OUTPUT
            || yytoken == Token_COMMAND_OUTPUT_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_COMMENT
            || yytoken == Token_CONSTANT
            || yytoken == Token_DEF
            || yytoken == Token_DEFINED
            || yytoken == Token_DOUBLE_QUOTED_STRING
            || yytoken == Token_END_UPCASE
            || yytoken == Token_FALSE
            || yytoken == Token_FILE
            || yytoken == Token_FLOAT
            || yytoken == Token_FOR
            || yytoken == Token_FUNCTION
            || yytoken == Token_GLOBAL_VARIABLE
            || yytoken == Token_HERE_DOC_BEGIN
            || yytoken == Token_HEX
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_IF
            || yytoken == Token_INSTANCE_VARIABLE
            || yytoken == Token_INTEGER
            || yytoken == Token_KEYWORD_NOT
            || yytoken == Token_LBRACK
            || yytoken == Token_LCURLY_HASH
            || yytoken == Token_LEADING_TWO_COLON
            || yytoken == Token_LINE
            || yytoken == Token_LINE_BREAK
            || yytoken == Token_LPAREN
            || yytoken == Token_MODULE
            || yytoken == Token_NEXT
            || yytoken == Token_NIL
            || yytoken == Token_NOT
            || yytoken == Token_OCTAL
            || yytoken == Token_REDO
            || yytoken == Token_REGEX
            || yytoken == Token_REGEX_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_REST_ARG_PREFIX
            || yytoken == Token_RETRY
            || yytoken == Token_RETURN
            || yytoken == Token_SELF
            || yytoken == Token_SEMI
            || yytoken == Token_SINGLE_QUOTED_STRING
            || yytoken == Token_STRING_BEFORE_EXPRESSION_SUBSTITUTION
            || yytoken == Token_SUPER
            || yytoken == Token_TRUE
            || yytoken == Token_UNARY_MINUS
            || yytoken == Token_UNARY_PLUS
            || yytoken == Token_UNDEF
            || yytoken == Token_UNLESS
            || yytoken == Token_UNTIL
            || yytoken == Token_WHILE
            || yytoken == Token_W_ARRAY
            || yytoken == Token_YIELD)
        {
            CompoundStatementAst *__node_275 = 0;
            if (!parseCompoundStatement(&__node_275))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::CompoundStatementKind, "compoundStatement");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_END)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_END, "end");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}


} // end of namespace ruby

