/* This file is part of KDevelop
 *
 * This file is based on the file parse.y from the MRI, version 1.9.2-p136.
 * So, at this point I must recognize the amazing job ruby developers
 * are doing and specially Yukihiro Matsumoto, the Ruby original author
 * and the one who signed parse.y.
 *
 * Copyright (C) 1993-2007 Yukihiro Matsumoto
 * Copyright (C) 2010  Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "node.h"
#include "parser.h"


/* Flags used by the lexer */
struct flags {
  unsigned char eof_reached;
  unsigned char expr_seen;
  unsigned char class_seen;
  unsigned char no_block;
  unsigned char dot_seen;
  unsigned char last_is_paren;
};

#define eof_reached lexer_flags.eof_reached
#define expr_seen lexer_flags.expr_seen
#define class_seen lexer_flags.class_seen
#define no_block lexer_flags.no_block
#define dot_seen lexer_flags.dot_seen
#define last_is_paren lexer_flags.last_is_paren

/*
 * TODO: Document
 */
struct stack_t {
  char * name;
  int start, end; /* TODO: necessary ?¿ */
};


/*
 * This structure defines the parser. It contains the AST, some
 * flags used for internal reasons and some info about the
 * content to parse.
 */
struct parser_t {
  /* Abstract Syntax Tree */
  struct node * ast;

  /* Flags used by the parser */
  struct flags lexer_flags;
  int in_def;

  /* Errors on the file */
  struct error_t errors[2];
  int error_index;

  /* Stack of names */
  struct stack_t * stack[2];
  int sp;

  /* Info about the content to parse */
  unsigned long cursor;
  unsigned long length;
  unsigned int line;
  unsigned int column;
  char * name;
  char * blob;
};

#define yyparse ruby_yyparse
#define YYLEX_PARAM parser


/* yy's functions */
static int yylex(void *, void *);
void yyerror(struct parser_t * p, const char * s, ...);

/* Parser auxiliar functions */
void init_parser(struct parser_t * p);
void free_parser(struct parser_t * p);
int retrieve_source(struct parser_t * p, FILE * fd);
int check_lhs(struct node * n);
void pop_stack(struct parser_t * parser, struct node * n);

%}

%pure_parser
%parse-param {struct parser_t * parser }

%union {  struct node * n;  }

/* Reserved words */
%token CLASS MODULE DEF UNDEF BEGIN RESCUE ENSURE END IF UNLESS THEN ELSIF
%token ELSE CASE WHEN WHILE UNTIL FOR BREAK NEXT REDO RETRY IN DO DO_BLOCK RETURN
%token YIELD KWAND KWOR KWNOT ALIAS DEFINED upBEGIN upEND HEREDOC
%token tTRUE tFALSE NIL ENCODING tFILE LINE SELF SUPER

/* Declare tokens */
%token EOL CVAR NUMBER SYMBOL FNAME BASE STRING COMMENT REGEXP MCALL ARRAY SARY
%token IVAR GLOBAL tLBRACKET tRBRACKET tDOT tTILDE tBACKTICK tCOMMA tCOLON
%token tPOW tUMINUS tUPLUS tLSHIFT tRSHIFT tASSOC tQUESTION tSEMICOLON
%token tOR tAND tAND_BIT tOR_BIT tXOR_BIT tLBRACE tRBRACE tLPAREN tRPAREN
%token tLESSER tGREATER tNOT tPLUS tMINUS tMUL tDIV tMOD KEY CONST
%token tASGN tOP_ASGN tCMP tEQ tEQQ tNEQ tMATCH tNMATCH tGEQ tLEQ tSCOPE


/* Precedence table */
%nonassoc IF UNLESS WHILE UNTIL
%left  KWOR KWAND
%right KWNOT
%nonassoc DEFINED
%right tASGN tOP_ASGN
%right tQUESTION tCOLON
%nonassoc tDOT2 tDOT3
%left tOR
%left tAND
%nonassoc  tCMP tEQ tEQQ tNEQ tMATCH tNMATCH
%left  tGREATER tGEQ tLESSER tLEQ
%left  tOR_BIT tXOR_BIT
%left  tAND_BIT
%left  tLSHIFT tRSHIFT
%left  tPLUS tMINUS
%left  tMUL tDIV tMOD
%nonassoc tUMINUS
%right tPOW
%right tNOT tTILDE tUPLUS


%type <n> exp stmt simple_stmt cmpd_stmt return_stmt yield_stmt const_mcall base
%type <n> if_tail opt_else case_body cases opt_rescue opt_ensure const_scope mcall
%type <n> compstmt stmts lhs assign superclass mlhs mrhs paren_method_call lhs_list
%type <n> item SYMBOL NUMBER REGEXP basic variable not_empty_compstmt module_name
%type <n> exc_var rescue_arg bodystmt f_arglist arg f_blockarg fname single_name
%type <n> f_arguments f_args f_restarg f_optarg primary f_opt primary1 primary2
%type <n> array array_items hash hash_items hash_item method_call call_args
%type <n> opt_lambda_body lambda_body brace_block do_block bv_decls block_list
%type <n> block_args exp_for exc_list rescue_list rescue_item function_args
%type <n> f_bad_arg opt_call_args simple_assign item_list opt_rescue_arg symbol
%type <n> bracket_list bracket_item array_exp m_call_args exp_hash sary const
%type <n> dot_method_call dot_items dot_item array_value opt_bracket_list key

%start parser_start
%%
parser_start: /* nothing */ EOL   { parser->ast = NULL; YYACCEPT; }
  | stmt
  {
    if (parser->errors[0].valid == 1) {
      free_ast(parser->ast);
      parser->ast = NULL;
    } else
      parser->ast = $1;
    YYACCEPT;
  }
;

stmt: simple_stmt
  | cmpd_stmt
  | assign
  | method_call opt_lambda_body { $$ = update_list($1, $2);}
  | hash
  | stmt IF exp           { $$ = alloc_cond(token_if, $3, $1, NULL);      }
  | stmt UNLESS exp       { $$ = alloc_cond(token_unless, $3, $1, NULL);  }
  | stmt WHILE exp        { $$ = alloc_cond(token_while, $3, $1, NULL);   }
  | stmt UNTIL exp        { $$ = alloc_cond(token_until, $3, $1, NULL);   }
  | exp
  | COMMENT               { $$ = 0; }
;

stmts: stmt               { $$ = $1;  }
  | stmts terms stmt      { $$ = update_list($1, $3);  }
;

basic: variable           { $$ = $1;  }
  | NUMBER                { $$ = alloc_node(token_numeric, NULL, NULL);   }
  | symbol                { $$ = $1;  }
  | string                { $$ = alloc_node(token_string, NULL, NULL);    }
  | REGEXP                { $$ = alloc_node(token_regexp, NULL, NULL);    }
  | HEREDOC               { $$ = alloc_node(token_heredoc, NULL, NULL);   }
  | tBACKTICK             { $$ = alloc_node(token_backtick, NULL, NULL);  }
  | other_keywords        { $$ = alloc_node(token_object, NULL, NULL);    }
;

other_keywords: tFALSE
  | tTRUE
  | NIL
  | ENCODING
  | tFILE
  | LINE
  | SELF
  | SUPER
;

string: STRING
  | string STRING
;

primary: basic            { $$ = $1;  }
  | array                 { $$ = $1;  }
  | paren_method_call     { $$ = $1;  }
  | dot_method_call       { $$ = $1;  }
;

primary1: variable        { $$ = $1;  }
  | paren_method_call     { $$ = $1;  }
  | dot_method_call       { $$ = $1;  }
;

primary2: NUMBER          { $$ = alloc_node(token_numeric, NULL, NULL);   }
  | symbol                { $$ = $1;  }
  | string                { $$ = alloc_node(token_string, NULL, NULL);    }
  | REGEXP                { $$ = alloc_node(token_regexp, NULL, NULL);    }
  | HEREDOC               { $$ = alloc_node(token_heredoc, NULL, NULL);   }
  | tBACKTICK             { $$ = alloc_node(token_backtick, NULL, NULL);  }
  | array                 { $$ = $1;  }
  | other_keywords        { $$ = alloc_node(token_object, NULL, NULL);    }
;

simple_stmt: BREAK        { $$ = alloc_node(token_break, NULL, NULL);   }
  | REDO                  { $$ = alloc_node(token_redo, NULL, NULL);    }
  | RETRY                 { $$ = alloc_node(token_retry, NULL, NULL);   }
  | NEXT                  { $$ = alloc_node(token_next, NULL, NULL);    }
  | UNDEF item_list       { $$ = alloc_node(token_undef, $2, NULL);     }
  | ALIAS item item       { $$ = alloc_node(token_alias, $2, $3);       }
  | yield_stmt            { $$ = $1;  }
  | return_stmt           { $$ = $1;  }
;

yield_stmt: YIELD         { $$ = alloc_node(token_yield, NULL, NULL);   }
  | YIELD exp             { $$ = alloc_node(token_yield, $2, NULL);     }
;

return_stmt: RETURN       { $$ = alloc_node(token_return, NULL, NULL);  }
  | RETURN exp            { $$ = alloc_node(token_return, $2, NULL);    }
;

item_list: item           { $$ = $1;  }
  | item comma item_list  { $$ = update_list($1, $3); }
;

item: BASE                { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
  | FNAME                 { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
  | symbol                { $$ = $1; }
;

cmpd_stmt: k_if exp then
  compstmt
  if_tail
  END
  {
    $$ = alloc_cond(token_if, $2, $4, $5);
  }
  | k_unless exp then
    compstmt
    if_tail
    END
    {
      $$ = alloc_cond(token_unless, $2, $4, $5);
    }
  | k_while exp do
    compstmt
    END
    {
      $$ = alloc_cond(token_while, $2, $4, NULL);
    }
  | k_until exp do
    compstmt
    END
    {
      $$ = alloc_cond(token_until, $2, $4, NULL);
    }
  | k_case exp opt_terms
    case_body
    END
    {
      $$ = alloc_cond(token_case, $2, $4, NULL);
    }
  | k_case case_body END
    {
      $$ = alloc_cond(token_case, NULL, $2, NULL);
    }
  | upBEGIN tLBRACE compstmt tRBRACE
    {
      $$ = alloc_node(token_up_begin, $3, NULL);
    }
  | upEND tLBRACE compstmt tRBRACE
    {
      $$ = alloc_node(token_up_end, $3, NULL);
    }
  | k_for mlhs k_in exp_for do compstmt END
    {
      $$ = alloc_cond(token_for, $4, $6, $2);
    }
  | BEGIN bodystmt END
    {
      $$ = $2;
      $$->kind = token_exception;
    }
  | k_def single_name
    {
      parser->in_def++;
    }
    function_args bodystmt END
    {
      parser->in_def--;
      $$ = alloc_cond(token_function, $2, $5, $4);
    }
  | k_module module_name
    {
      if (parser->in_def)
        yyerror(parser, "module definition in method body");
    }
    bodystmt
    END
    {
      $$ = alloc_node(token_module, $4, $2);
    }
  | k_class module_name superclass
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    }
    bodystmt
    END
    {
      $$ = alloc_cond(token_class, $3, $5, $2);
    }
  | k_class tLSHIFT opt_eol_list variable
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    }
    bodystmt
    END
    {
      $$ = alloc_node(token_singleton_class, $6, $4);
    }
;

fname: FNAME  { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
  | base      { $$ = $1; }
;

single_name: base dot_or_scope fname  { $$ = alloc_node(token_object, $1, $3);  }
  | fname                             { $$ = $1;  }
;

function_args: f_arglist eol_or_semicolon  { $$ = $1;  }
  | eol_or_semicolon  { $$ = 0; }
;

module_name: CONST  { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
  | BASE
  {
    yyerror(parser, "class/module name must be CONSTANT");
  }
;

variable: base  { $$ = $1; }
  | CVAR        { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
  | GLOBAL      { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
  | IVAR        { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
  | CONST       { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
;

base: BASE      { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
;

mcall: MCALL    { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
;

const: CONST    { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
;

symbol: SYMBOL  { $$ = alloc_node(token_symbol, NULL, NULL); pop_stack(parser, $$); }
;

key: KEY        { $$ = alloc_node(token_symbol, NULL, NULL); pop_stack(parser, $$); }
;

if_tail: opt_else
  | k_elsif exp then
    compstmt
    if_tail
    {
      $$ = alloc_cond(token_if, $2, $4, $5);
    }
;

opt_else: /* nothing */     { $$ = 0; }
  | ELSE compstmt           { $$ = alloc_cond(token_if, NULL, $2, NULL);  }
;

opt_ensure: /* nothing */   { $$ = 0; }
  | ENSURE compstmt         { $$ = alloc_node(token_ensure, $2, NULL); }
;

opt_rescue: /* nothing */   { $$ = 0;   }
  | rescue_list             { $$ = $1;  }
;

rescue_list: rescue_item    { $$ = $1;  }
  | rescue_list rescue_item { $$ = update_list($1, $2); }
;

rescue_item: RESCUE opt_rescue_arg then compstmt
  {
    $$ = alloc_node(token_rescue, $2, $4);
  }
;

bodystmt: compstmt opt_rescue opt_else opt_ensure
  {
    $$ = alloc_ensure(token_body, $1, $2, $3, $4);
  }
;

superclass: /* nothing */             { $$ = 0;   }
  | tLESSER opt_eol_list module_name  { $$ = $3;  }
;

opt_lambda_body: /* nothing */  { $$ = 0;   }
  | lambda_body                 { $$ = $1;  }
;

lambda_body: brace_block  { $$ = $1;  }
  | do_block              { $$ = $1;  }
;

brace_block: lbrace block_args not_empty_compstmt tRBRACE
  {
    $$ = alloc_node(token_block, $3, $2);
  }
  | lbrace not_empty_compstmt tRBRACE
  {
    $$ = alloc_node(token_block, $2, NULL);
  } 
;

do_block: DO_BLOCK endl block_args compstmt END
  {
    $$ = alloc_node(token_block, $4, $3);
  }
  | DO_BLOCK compstmt END
  {
    $$ = alloc_node(token_block, $2, NULL);
  }
;

block_args: tOR_BIT f_arguments bv_decls tOR_BIT
  {
    $$ = alloc_node(token_object, $2, $3);
  }
  | tOR_BIT bv_decls tOR_BIT
  {
    $$ = alloc_node(token_object, NULL, $2);
  }
  | tOR_BIT f_arguments tOR_BIT
  {
    $$ = alloc_node(token_object, $2, NULL);
  }
;

bv_decls: tSEMICOLON block_list   { $$ = $2;  }
;

block_list: base    { $$ = alloc_node(token_object, NULL, NULL);  }
  | block_list comma base
  {
    $$ = update_list($1, alloc_node(token_object, NULL, NULL));
  }
;

f_arglist: f_arguments            { $$ = $1;  }
  | lparen f_arguments rparen     { $$ = $2;  }
;

f_arguments: tAND_BIT arg         { $$ = $2;  }
  | f_args f_blockarg             { $$ = update_list($1, $2);  }
  | f_restarg comma f_args f_blockarg
    {
      $$ = create_list($1, update_list($3, $4));
    }
  | f_restarg f_blockarg { $$ = update_list($1, $2);  }
  | f_optarg comma f_args f_blockarg
    {
      $$ = concat_list($1, update_list($3, $4));
    }
  | f_optarg f_blockarg  { $$ = update_list($1, $2);  }
  | f_optarg comma f_restarg comma f_args f_blockarg
    {
      $$ = concat_list($1, create_list($3, update_list($5, $6)));
    }
  | f_optarg comma f_restarg f_blockarg
    {
      $$ = concat_list($1, update_list($3, $4));
    }
  | f_args comma f_optarg comma f_args f_blockarg
    {
      $$ = concat_list($1, concat_list($3, update_list($5, $6)));
    }
  | f_args comma f_optarg f_blockarg
    {
      $$ = concat_list($1, update_list($3, $4));
    }
  | f_args comma f_optarg comma f_restarg comma
    f_args f_blockarg
    {
      $$ = concat_list($1, concat_list($3, create_list($5, update_list($7, $8))));
    }
  | f_args comma f_optarg comma f_restarg f_blockarg
    {
      $$ = concat_list($1, concat_list($3, update_list($5, $6)));
    }
;

f_blockarg: /* nothing */ { $$ = 0;   }
  | comma tAND_BIT arg    { $$ = $3;  }
;

f_args: arg               { $$ = $1;  }
  | f_args comma arg      { $$ = update_list($1, $3); }
;

f_restarg: tMUL arg       { $$ = $2;  }
;

f_opt: arg tASGN primary  { $$ = alloc_node(token_object, $1, $3);  }
;

f_optarg: f_opt           { $$ = $1;  }
  | f_optarg comma f_opt  { $$ = update_list($1, $3); }
;

arg: BASE                 { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
  | f_bad_arg             { $$ = 0; }
;

f_bad_arg: CONST
  {
    yyerror(parser, "formal argument cannot be a constant");
    $$ = 0;
  }
  |  IVAR
  {
    yyerror(parser, "formal argument cannot be an instance variable");
    $$ = 0;
  }
  | GLOBAL
  {
    yyerror(parser, "formal argument cannot be a global variable");
    $$ = 0;
  }
  | CVAR
  {
    yyerror(parser, "formal argument cannot be a class variable");
    $$ = 0;
  }
;

opt_rescue_arg: /* nothing */   { $$ = 0;   }
  | rescue_arg                  { $$ = $1;  }
;

rescue_arg: exc_list exc_var
  {
    $$ = alloc_node(token_rescue_arg, $1, $2);
  }
;

exc_list: exp           { $$ = $1;  }
  | exc_list comma exp  { $$ = update_list($1, $3); }
;

exc_var: /* nothing */            { $$ = 0;   }
  | tASSOC opt_eol_list variable  { $$ = $3;  }
;

case_body: k_when exp then compstmt cases
  {
    $$ = alloc_cond(token_when, $2, $4, $5);
  }
;

cases: opt_else
  | case_body
;

then: term
  | THEN
  | term THEN
;

do: term
  | DO
;

k_if: IF opt_eol_list
;

k_elsif: ELSIF opt_eol_list
;

k_unless: UNLESS opt_eol_list
;

k_while: WHILE opt_eol_list
;

k_until: UNTIL opt_eol_list
;

k_case: CASE opt_eol_list
;

k_when: WHEN opt_eol_list
;

k_for: FOR opt_eol_list
;

k_def: DEF opt_eol_list
;

k_module: MODULE opt_eol_list
;

k_class: CLASS opt_eol_list
;

k_in: IN opt_eol_list
;

endl: /* nothing */
  | EOL
;

comma: tCOMMA opt_eol_list
;

lparen: tLPAREN opt_eol_list
;

rparen: opt_eol_list tRPAREN
;

lbracket: tLBRACKET opt_eol_list
;

rbracket: opt_eol_list tRBRACKET
;

lbrace: tLBRACE opt_eol_list
;

rbrace: opt_eol_list tRBRACE
;

asgn: tASGN opt_eol_list
;

op_asgn: tOP_ASGN opt_eol_list
;

compstmt: opt_terms stmts opt_terms   { $$ = $2;  }
  | opt_terms                         { $$ = 0;   }
;

not_empty_compstmt: stmts opt_terms   { $$ = $1;  }
;

opt_eol_list: /* nothing */
  | eol_list
;

eol_list: EOL
  | eol_list EOL
;

term: tSEMICOLON
  | EOL
;

terms: term
  | terms term
;

opt_terms: /* nothing */
  | terms
;

dot_or_scope: tDOT
  | tSCOPE
;

eol_or_semicolon: EOL
  | tSEMICOLON
;

lhs_list: mlhs comma lhs { $$ = update_list($1, $3);  }
  | mlhs comma  { $$ = $1;  }
;

lhs: exp
  {
    /* TODO: Implement a better way to do this, check_lhs can be expensive :( */
    if (check_lhs($1))
      $$ = $1;
    else {
      $$ = 0;
      yyerror(parser, "syntax error, unexpected '=', expecting $end");
    }
  }
  | lparen lhs_list rparen    { $$ = alloc_node(token_object, $2, NULL);  }
  | tMUL variable             { $$ = $2;  }
  | tMUL                      { $$ = alloc_node(token_object, NULL, NULL);  }
;

opt_bracket_list: /* nothing */ { $$ = 0; }
  | bracket_list                { $$ = $1;  }
;

bracket_list: bracket_item      { $$ = $1; }
  | bracket_list bracket_item   { $$ = update_list($1, $2); }
;

bracket_item: lbracket array_exp rbracket { $$ = $2; }
;

mlhs: exp           { $$ = $1;  }
  | mlhs comma      { $$ = $1;  }
  | mlhs comma lhs  { $$ = update_list($1, $3); }
;

mrhs: exp                   { $$ = $1;  }
  | mrhs comma exp          { $$ = update_list($1, $3); }
;

simple_assign: variable asgn primary  { $$ = alloc_node(token_assign, $1, $3);    }
  | variable op_asgn primary          { $$ = alloc_node(token_op_assign, $1, $3); }
  | variable asgn hash                { $$ = alloc_node(token_assign, $1, $3);    }
  | variable op_asgn hash             { $$ = alloc_node(token_op_assign, $1, $3); }
;

assign: mlhs asgn mrhs       { $$ = alloc_node(token_assign, $1, $3);    }
  | mlhs op_asgn mrhs        { $$ = alloc_node(token_op_assign, $1, $3); }
  | mlhs asgn method_call opt_lambda_body
  {
    $$ = alloc_node(token_assign, $1, $3);
    $$ = update_list($$, $4);
  }
  | mlhs op_asgn method_call opt_lambda_body
  {
    $$ = alloc_node(token_op_assign, $1, $3);
    $$ = update_list($$, $4);
  }
  | mlhs asgn hash           { $$ = alloc_node(token_assign, $1, $3);     }
  | mlhs op_asgn hash        { $$ = alloc_node(token_op_assign, $1, $3);  }
  | mlhs asgn cmpd_stmt      { $$ = alloc_node(token_assign, $1, $3);     }
  | mlhs op_asgn cmpd_stmt   { $$ = alloc_node(token_op_assign, $1, $3);  }
;

array: lbracket tRBRACKET               { $$ = alloc_node(token_array, NULL, NULL); }
  | lbracket array_items rbracket       { $$ = alloc_node(token_array, $2, NULL);   }
  | ARRAY                               { $$ = alloc_node(token_array, NULL, NULL); }
;

/* TODO: hash with expr */
array_exp: exp      { $$ = $1;  }
  | simple_assign   { $$ = $1;  }
  | hash            { $$ = $1;  }
;

array_items: array_exp              { $$ = $1;  }
  | array_items comma array_exp     { $$ = update_list($1, $3); }
;

array_value: sary opt_eol_list array_exp rbracket opt_bracket_list
  {
    struct node * n = $3;
    n->next = $5;
    $$ = alloc_node(token_array_value, $1, n);
  }/* TODO */
/*  | variable bracket_item bracket_list
  {
    $$ = alloc_node(token_array_value, $1, create_list($2, $3));
  }*/
;

sary: SARY  { $$ = alloc_node(token_object, NULL, NULL); pop_stack(parser, $$); }
;

hash: lbrace tRBRACE            { $$ = alloc_node(token_hash, NULL, NULL);  }
  | lbrace hash_items rbrace    { $$ = alloc_node(token_hash, $2, NULL);    }
;

hash_items: hash_item           { $$ = $1;  }
  | hash_items comma hash_item  { $$ = update_list($1, $3); }
;

hash_item: exp tASSOC opt_eol_list exp  { $$ = alloc_node(token_object, $1, $4);  }
  | key opt_eol_list exp                { $$ = alloc_node(token_object, $1, $3);  }
;

method_call: fname m_call_args
  {
    $$ = alloc_node(token_method_call, $1, $2);
  }
  | dot_method_call m_call_args
  {
    if (parser->last_is_paren) {
      yyerror(parser, "bad parameter list");
      $$ = 0;
    } else {
      $$ = $1;
      $$->r = $2;
    }
  }
  | const_scope opt_call_args  { $$ = alloc_node(token_method_call, $1, $2); }
;

const_scope: const tSCOPE fname
  {
    $$ = alloc_node(token_object, $1, $3);
  }
;

paren_method_call: mcall opt_call_args rparen
  {
    $$ = alloc_node(token_method_call, $1, $2);
  }
  | const_mcall opt_call_args rparen
  {
    $$ = alloc_node(token_method_call, $1, $2);
  }
;

const_mcall: const tSCOPE mcall { $$ = alloc_node(token_object, $1, $3); }
;

dot_method_call: basic dot_items
  {
    struct node * n = alloc_node(token_method_call, $1, NULL);
    $$ = pop_list(n, $2);
  }
  | lparen exp rparen dot_items
  {
    struct node * n = alloc_node(token_method_call, $2, NULL);
    $$ = pop_list(n, $4);
  }
  | paren_method_call dot_items
  {
    $$ = pop_list($1, $2);
  }
;

dot_items: dot_item     { $$ = $1; }
  | dot_items dot_item  { $$ = update_list($1, $2); }
;

dot_item: tDOT fname
  {
    $$ = $2;
    parser->last_is_paren = 0;
  }
  | tDOT paren_method_call
  {
    $$ = $2;
    parser->last_is_paren = 1;
  }
;

opt_call_args: /* nothing */  { $$ = 0;   }
  | m_call_args               { $$ = $1;  }
;

m_call_args: method_call      { $$ = $1;  }
  | call_args                 { $$ = $1;  }
;

/* TODO: tMUL and tAND_BIT ambiguity :S */
call_args: exp                { $$ = $1;  }
  | call_args comma exp_hash  { $$ = update_list($1, $3); }
;

/* TODO: hash with exp */
exp_hash: exp   { $$ = $1;  }
  | hash        { $$ = $1;  }
  | hash_items  { $$ = alloc_node(token_hash, $1, NULL);  }
;

/* TODO: hash with exp */
exp_for: exp    { $$ = $1;  }
  | hash        { $$ = $1;  }
;

exp: exp tPLUS opt_eol_list exp       { $$ = alloc_node(token_plus, $1, $4);    }
  | exp tMINUS opt_eol_list exp       { $$ = alloc_node(token_minus, $1, $4);   }
  | exp tMUL opt_eol_list exp         { $$ = alloc_node(token_mul, $1, $4);     }
  | exp tDIV opt_eol_list exp         { $$ = alloc_node(token_div, $1, $4);     }
  | exp tMOD opt_eol_list exp         { $$ = alloc_node(token_mod, $1, $4);     }
  | exp tPOW opt_eol_list exp         { $$ = alloc_node(token_exp, $1, $4);     }
  | exp tAND_BIT opt_eol_list exp     { $$ = alloc_node(token_bit_and, $1, $4); }
  | exp tOR_BIT opt_eol_list exp      { $$ = alloc_node(token_bit_or, $1, $4);  }
  | exp tXOR_BIT opt_eol_list exp     { $$ = alloc_node(token_bit_xor, $1, $4); }
  | exp tLSHIFT opt_eol_list exp      { $$ = alloc_node(token_lshift, $1, $4);  }
  | exp tRSHIFT opt_eol_list exp      { $$ = alloc_node(token_rshift, $1, $4);  }
  | lparen exp rparen                 { $$ = $2;  }
  | lparen assign rparen              { $$ = $2;  }
  | lparen method_call rparen         { $$ = $2;  }
  | exp tCMP opt_eol_list exp         { $$ = alloc_node(token_cmp, $1, $4);     }
  | exp tEQ opt_eol_list exp          { $$ = alloc_node(token_eq, $1, $4);      }
  | exp tNEQ opt_eol_list exp         { $$ = alloc_node(token_neq, $1, $4);     }
  | exp tEQQ opt_eol_list exp         { $$ = alloc_node(token_eqq, $1, $4);     }
  | exp tMATCH opt_eol_list exp       { $$ = alloc_node(token_match, $1, $4);   }
  | exp tNMATCH opt_eol_list exp      { $$ = alloc_node(token_nmatch, $1, $4);  }
  | exp tGREATER opt_eol_list exp     { $$ = alloc_node(token_greater, $1, $4); }
  | exp tLESSER opt_eol_list exp      { $$ = alloc_node(token_lesser, $1, $4);  }
  | exp tGEQ opt_eol_list exp         { $$ = alloc_node(token_geq, $1, $4);     }
  | exp tLEQ opt_eol_list exp         { $$ = alloc_node(token_leq, $1, $4);     }
  | exp tOR opt_eol_list exp          { $$ = alloc_node(token_or, $1, $4);      }
  | exp tAND opt_eol_list exp         { $$ = alloc_node(token_and, $1, $4);     }
  | exp KWOR opt_eol_list exp         { $$ = alloc_node(token_kw_or, $1, $4);   }
  | exp KWAND opt_eol_list exp        { $$ = alloc_node(token_kw_and, $1, $4);  }
  | exp tDOT2 opt_eol_list exp        { $$ = alloc_node(token_dot2, $1, $4);    }
  | exp tDOT3 opt_eol_list exp        { $$ = alloc_node(token_dot3, $1, $4);    }
  | exp tQUESTION opt_eol_list exp opt_eol_list tCOLON opt_eol_list exp
  {
    $$ = alloc_cond(token_ternary, $1, $4, $8);
  }
  | KWNOT opt_eol_list exp            { $$ = alloc_node(token_kw_not, $3, NULL);}
  | tTILDE opt_eol_list exp           { $$ = alloc_node(token_neg, $3, NULL);   }
  | tNOT opt_eol_list exp             { $$ = alloc_node(token_not, $3, NULL);   }
  | tUPLUS opt_eol_list exp           { $$ = alloc_node(token_unary_plus, $3, NULL);  }
  | tUMINUS opt_eol_list exp          { $$ = alloc_node(token_unary_minus, $3, NULL); }
  | DEFINED opt_eol_list exp          { $$ = alloc_node(token_defined, $3, NULL);     }
  | primary1 opt_lambda_body          { $$ = update_list($1, $2); }
  | primary2                          { $$ = $1   }
  | array_value                       { $$ = $1;  }
;

%%
#undef parser
#undef yylex

#include <ctype.h>
#include "hash.c"


/* Let's define some useful macros :D */

#define BSIZE 128
#define to_upper(a) (a & ~32)
#define is_upper(c) (c >= 'A' && c <= 'Z')
#define multiline_comment(c) (*(c+1) == 'b' && *(c+2) == 'e' && *(c+3) == 'g' \
                              && *(c+4) == 'i' && *(c+5) == 'n')
#define multiline_end(c) (*c == '=' && *(c+1) == 'e' && *(c+2) == 'n' \
                          && *(c+3) == 'd')
#define isFunction(c) (*c == '!' || *c == '=' || *c == '?')
#define isSimple(c) (c == '(' || c == '{' || c == '[')
#define isShortcut(c) (to_upper(c) == 'W' || c == 'r' || to_upper(c) == 'Q' \
                      || c == 'x' || isSimple(c))
#define isNotSep(c) (isValidVariableIdentifier(c) || isdigit(*c) \
                    || *c == '_' || *c == '$' || *c == '@')
#define isSpecialMethod(buffer) ((strlen(buffer) > 4) && buffer[0] == '_' && \
                                buffer[1] == '_' && buffer[strlen(buffer) - 2] == '_' && \
                                buffer[strlen(buffer) - 1] == '_')
#define parser_dot_seen(t, OP)  if (parser->dot_seen) { \
                                  parser->dot_seen = 0; \
                                  t = FNAME; \
                                } else \
                                  t = OP;
#define cannot_be_heredoc (parser->class_seen || parser->expr_seen || parser->dot_seen)


void init_parser(struct parser_t * p)
{
  p->ast = NULL;
  p->blob = NULL;
  p->cursor = 0;
  p->eof_reached = 0;
  p->expr_seen = 0;
  p->class_seen = 0;
  p->no_block = 0;
  p->dot_seen = 0;
  p->last_is_paren = 0;
  p->in_def = 0;
  p->errors[0].valid = 0;
  p->errors[1].valid = 0;
  p->error_index = 0;
  p->sp = 0;
  p->line = 1;
  p->column = 0;
  p->name = NULL;
}

void free_parser(struct parser_t * p)
{
  int index;

  for (index = 0; index < p->sp; index++) {
    free(p->stack[index]->name);
    free(p->stack[index]);
  }
  free(p->blob);
  free(p->name);
}

/* Read the file's source code and allocate it for further inspection. */
int retrieve_source(struct parser_t * p, FILE * fd)
{
  int length, check;

  fseek(fd, 0, SEEK_END);
  length = ftell(fd);
  fseek(fd, 0, SEEK_SET);

  if (!length)
    return -1;
  p->blob = (char *) malloc (sizeof(char) * length);

  if (!p->blob) {
    fprintf(stderr, "Cannot store contents\n");
    return -1;
  }
  check = fread(p->blob, length, 1, fd);
  if (ferror(fd)) {
    fprintf(stderr, "Reading error\n");
    return -1;
  }
  p->length = length;
  return 0;
}

int check_lhs(struct node * n)
{
  if (n == NULL || n->kind == token_array_value)
    return 1;
  if (n->kind > token_object)
    return 0;
  if (check_lhs(n->l))
    return check_lhs(n->r);
  return 0;
}


/*
 * Some macros to make easier the UTF-8 support
 */
#define is_utf(c) ((c & 0xC0) != 0x80)
#define is_special(c) (utf8_charsize(c) > 1)

/*
 * This function is really simple. It steps over a char of
 * the string s, that is encoded in UTF-8. The result varies on the
 * number of bytes that encodes a single character following the UTF-8
 * rules. Therefore, this function will return 1 if the character
 * is in plain-ASCII, and greater than 1 otherwise.
 */
int utf8_charsize(char * s)
{
  int size = 0;
  int i = 0;

  do {
    i++;
    size++;
  } while (s[i] && !is_utf(s[i]));
  return size;
}

int is_utf8_alpha(char * str)
{
  return is_special(str) ? 1 : isalpha(*str);
}

int is_utf8_graph(char * str)
{
  return is_special(str) ? 1 : isgraph(*str);
}

int is_utf8_digit(char * str)
{
  return is_special(str) ? 0 : isdigit(*str);
}

unsigned char isValidKeyword(char * c)
{
  return ((isalpha(*c) || *c == '_' || *c == '$' || *c == '@')
          && !isdigit(*c) && !is_special(c));
}

int isValidVariableIdentifier(char * c)
{
  if (is_utf8_alpha(c))
    return 1;
  else if (*c == '$' && is_utf8_graph(c + 1) && !is_utf8_digit(c + 1))
    return 1;
  else if ((*c == '_' || *c == '@') && is_utf8_alpha(c + 1))
    return 1;
  else if (*c == '@' && *(c + 1) == '@' && (is_utf8_alpha(c + 2) || *(c + 2) == '_'))
    return 1;
  return 0;
}

int parse_heredoc(struct parser_t * p, char * c, int * curs, int len)
{
  char buffer[BSIZE], aux[BSIZE];
  int i, l = 0;

  /* Check for <<- case */
  if (*(c + 2) == '-') {
    c += 3;
    (*curs)++;
  } else
    c += 2;
  for (i = 0; *c != '\n' && *curs <= len; (*curs)++, ++l)
    buffer[i++] = *c++;
  buffer[i] = '\0';

  for (i = 0; *curs <= len; i++, c++, (*curs)++) {
    aux[i] = *c;
    if (*c == '\n') {
      aux[i + 1] = '\0';
      if (!strncmp(buffer, aux, l) && (l == i))
        return HEREDOC;
      i = -1;
    }
  }
  yyerror(p, "Can't find string \"%s\" anywhere before EOF", buffer);
  return token_invalid;
}

/* Return what's the char that closes c */
char closing_char(char c)
{
  if (c == '(')
    return ')';
  else if (c == '{')
    return '}';
  else
    return ']';
}

/*
 * Let's guess the kind depending on the character after the
 * %-character of expressions like %W
 */
int guess_kind(char c)
{
  if (isSimple(c) || to_upper(c) == 'Q' || c == 'x')
    return STRING;
  else if (to_upper(c) == 'W')
    return ARRAY;
  else
    return REGEXP;
}

/* Push name to the stack */
void push_stack(struct parser_t * parser, char * buf)
{
  parser->stack[parser->sp] = (struct stack_t *) malloc (sizeof(struct stack_t));
  parser->stack[parser->sp]->name = strdup(buf);
  parser->sp++;
}

/* Pop name from the stack. */
void pop_stack(struct parser_t * parser, struct node * n)
{
  n->name = parser->stack[0]->name;
  parser->stack[0] = parser->stack[1];
  parser->sp--;
}

/*
 * This is the lexer. It reads the source code (blob) and provides tokens to
 * the parser. It also updates the necessary flags.
 */
static int parser_yylex(struct parser_t * parser)
{
  int t = YYEOF;
  char buffer[BSIZE];
  char * c;
  int curs, len;

  curs = parser->cursor;
  len = parser->length;
  if (curs >= len) {
    parser->eof_reached = 1;
    return 0;
  }
  c = parser->blob + curs;

  /* Ignore whitespaces */
  for (; isspace(*c) && *c != '\n'; ++c, ++curs);

  if (*c == '#') {
    for (; *c != '\n' && curs < len; ++c, ++curs);
    t = COMMENT;
  } else if (*c == '\n') {
    t = EOL;
    parser->no_block = 0;
    parser->expr_seen = 0;
    parser->dot_seen = 0;
    parser->column = -1; /* So it's correct after curs++ */
    parser->line++;
    curs++;
  } else if (isdigit(*c)) {
    char hex = 0;
    char bin = 0;
    char hasPoint = 0;
    char aux = 0;
    if (*c == '0') {
      if (to_upper(*(c + 1)) == 'X') {
        hex = 1;
        curs++;
        c++;
      }
      else if (to_upper(*(c + 1)) == 'B') {
        bin = 1;
        curs++;
        c++;
      }
      curs++;
      c++;
    }
    while (curs < len && ((isdigit(*c) && !bin) || (!hex && !bin && !hasPoint && *c == '.')
          || (hex && to_upper(*c) >= 'A' && to_upper(*c) < 'G')
          || (bin && (*c == '1' || *c == '0')))) {
      if (*c == '.') {
        if (!isdigit(*(c + 1)))
          break; /* Don't mess with ranges */
        hasPoint = 1;
      }
      aux = 1;
      c++;
      curs++;
    }
    if ((bin || hex) && !aux)
      yyerror(parser, "numeric literal without digits");
    /* is it an exponential number ? */
    if (!bin && !hex && to_upper(*c) == 'E' && (isdigit(*(c + 1)) ||
       ((*(c + 1) == '+' || *(c + 1) == '-') && isdigit(*(c + 2))))) {
      c++;
      curs++;
      if (*c == '+' || *c == '-') {
        c++;
        curs++;
      }
      while ((curs < len) && isdigit(*c)) {
        c++;
        curs++;
      }
    }
    parser->expr_seen =  1;
    parser->dot_seen = 0;
    t = NUMBER;
  } else if (isNotSep(c)) {
    char * ptr = buffer;
    int step = 0;
    unsigned char isConstant = 1;

    do {
      if (is_special(c) || (*c > 'Z' && !isdigit(*c)))
        isConstant = 0;
      step = utf8_charsize(c);
      while (step-- > 0) {
        *ptr++ = *c++;
        curs++;
      }
    } while (curs < len && isNotSep(c));
    *ptr = '\0';

    const struct kwtable *kw = rb_reserved_word(buffer, ptr - buffer);
    if (kw) {
      t = kw->id;
      if (t == WHILE || t == UNTIL || t == FOR)
        parser->no_block = 1;
      else if (t == CLASS) {
        /* check for class() method */
        if (parser->dot_seen) {
          push_stack(parser, buffer);
          t = FNAME;
          parser->dot_seen = 0;
        } else
          parser->class_seen = 1;
      }
    } else if ((!strcmp(buffer, "defined")) && (*c == '?')) {
      ++curs;
      t = DEFINED;
    } else if (isValidVariableIdentifier(buffer)) {
      push_stack(parser, buffer);
      if (isConstant || is_upper(buffer[0]))
        t = CONST;
      else if (*c == ':' && *(c + 1) != ':') {
        t = KEY;
        ++c;
        ++curs;
      } else {
        if (buffer[0] == '@' && strlen(buffer) > 1 && buffer[1] == '@')
          t = CVAR;
        else if (buffer[0] == '@')
          t = IVAR;
        else if (buffer[0] == '$')
          t = GLOBAL;
        else if (isFunction(c)) {
          curs++;
          c++;
          t = FNAME;
        } else
          t = BASE;
        parser->expr_seen = 1;
        if (parser->class_seen)
          parser->class_seen = 0;
        if (t == BASE && *c == '[') {
          ++curs;
          t = SARY;
        }
        if (*c == '(' && (t == BASE || t == FNAME)) {
          ++curs;
          t = MCALL;
        }
      }
    } else if (isSpecialMethod(buffer)) {
      push_stack(parser, buffer);
      t = BASE;
    } else
      t = token_invalid;
    parser->dot_seen = 0;
  } else if (*c == '[') {
    t = tLBRACKET;
    curs++;
  } else if (*c == ']') {
    t = tRBRACKET;
    curs++;
  } else if (*c == '=') {
    curs++;
    if (*(c + 1) == '=') {
      ++curs;
      if (*(c + 2) == '=') {
        parser_dot_seen(t, tEQQ);
        curs++;
      } else
        parser_dot_seen(t, tEQ);
      ++curs;
    } else if (*(c + 1) == '~') {
      ++curs;
      parser_dot_seen(t, tMATCH);
    } else if (*(c + 1) == '>') {
      ++curs;
      t = tASSOC;
    } else if (multiline_comment(c)) {
      curs += 5;
      c += 5;
      for(; !multiline_end(c); ++curs, ++c);
      curs += 3;
      t = COMMENT;
    } else
      t = tASGN;
  } else if (*c == '<') {
    curs++;
    if (*(c + 1) == '<') {
      curs++;
      if (*(c + 2) == '=') {
        curs++;
        t = tOP_ASGN;
      } else {
        if (cannot_be_heredoc) {
          parser_dot_seen(t, tLSHIFT);
        } else
          t = parse_heredoc(parser, c, &curs, len);
      }
    } else if (*(c + 1) == '=') {
      curs++;
      if (*(c + 2) == '>') {
        curs++;
        parser_dot_seen(t, tCMP);
      } else
        parser_dot_seen(t, tLEQ);
    } else
      parser_dot_seen(t, tLESSER);
  } else if (*c == '>') {
    curs++;
    if (*(c + 1) == '>') {
      curs++;
      if (*(c + 2) == '=') {
        curs++;
        t = tOP_ASGN;
      } else
        parser_dot_seen(t, tRSHIFT);
    } else if (*(c + 1) == '=') {
      curs++;
      parser_dot_seen(t, tGEQ);
    } else
      parser_dot_seen(t, tGREATER);
  } else if (*c == '!') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      parser_dot_seen(t, tNEQ);
    } else if (*(c + 1) == '~') {
      curs++;
      parser_dot_seen(t, tNMATCH);
    } else
      parser_dot_seen(t, tNOT);
  } else if (*c == '+') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else {
      parser_dot_seen(t, tPLUS);
      if (!parser->expr_seen && t == tPLUS)
        t = tUPLUS;
    }
  } else if (*c == '-') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else {
      parser_dot_seen(t, tMINUS);
      if (!parser->expr_seen && t == tMINUS)
        t = tUMINUS;
    }
  } else if (*c == '*') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else if (*(c + 1) == '*') {
      ++curs;
      if (*(c + 2) == '=') {
        ++curs;
        t = tOP_ASGN;
      } else
        parser_dot_seen(t, tPOW);
    } else
      parser_dot_seen(t, tMUL);
  } else if (*c == '/') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else {
      if (parser->expr_seen) {
        parser_dot_seen(t, tDIV);
      } else {
        ++c;
        for (; *c != '/'; ++c, ++curs) {
          if (*c == '#' && *(c + 1) == '{') {
            c += 2;
            curs += 2;
            for (; *c != '}'; ++c, ++curs)
              if (curs >= len) {
                yyerror(parser, "expecting '}' token in regular expression");
                curs = len + 1; /* So we can force curs >= len error */
                break;
              }
          }
          if (*c == '\\' && *(c + 1) == '/') {
            curs++;
            c++;
          }
        }
        t = REGEXP;
        curs++;
      }
      parser->expr_seen = 0;
    }
  } else if (*c == '%') {
    ++curs;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else if (isShortcut(*(c + 1))) {
      int catalan = 1;
      int kind = guess_kind(*(c + 1));
      unsigned char is_simple = isSimple(*(c + 1));
      char open, close;

      if (*(c + 2) != '(' && *(c + 2) != '[' && *(c + 2) != '{' && !is_simple) {
        yyerror(parser, "unterminated string meets end of file");
        t = token_invalid;
        catalan = -1;
      }
      curs += (3 - is_simple);
      c += (3 - is_simple);
      open = *(c - 1);
      close = closing_char(*(c - 1));
      while (catalan != -1) {
        if (*c == '#' && *(c + 1) == '{') {
          c += 2;
          curs += 2;
          for (; *c != '}'; ++c, ++curs)
            if (curs >= len) {
              yyerror(parser, "expecting '}' token in string");
              curs = len + 1; /* So we can force curs >= len error */
              break;
            }
          c++;
          curs++;
        }
        if (*c == open)
          ++catalan;
        else if (*c == close) {
          --catalan;
          if (!catalan)
            break;
        }
        if (curs >= len) {
          yyerror(parser, "unterminated string meets end of file");
          t = token_invalid;
          break;
        }
        c++;
        curs++;
      }
      /* Don't overwrite token kind if an error occurred */
      if (!catalan)
        t = kind;
    } else
      parser_dot_seen(t, tMOD);
  } else if (*c == '&') {
    ++curs;
    if (*(c + 1) == '&') {
      ++curs;
      if (*(c + 2) == '=') {
        ++curs;
        t = tOP_ASGN;
      } else
        t = tAND;
    } else if (*(c + 1) == '=') {
      ++curs;
      t = tOP_ASGN;
    } else
      parser_dot_seen(t, tAND_BIT);
  } else if (*c == '|') {
    ++curs;
    if (*(c + 1) == '|') {
      ++curs;
      if (*(c + 2) == '=') {
        ++curs;
        t = tOP_ASGN;
      } else
        t = tOR;
    } else if (*(c + 1) == '=') {
      ++curs;
      t = tOP_ASGN;
    } else
      parser_dot_seen(t, tOR_BIT);
  } else if (*c == '.') {
    curs++;
    if (*(c + 1) == '.') {
      curs++;
      if (*(c + 2) == '.') {
        curs++;
        t = tDOT3;
      } else
        t = tDOT2;
    } else {
      t = tDOT;
      parser->dot_seen = 1;
    }
  } else if (*c == ':') {
    curs++;
    if (*(c + 1) == ':') {
      curs++;
      t = tSCOPE;
    } else if (isNotSep(c + 1)) {
      char * ptr = buffer;
      int step = 0;
      curs--;
      do {
        step = utf8_charsize(c);
        while (step-- > 0) {
          *ptr++ = *c++;
          curs++;
        }
      } while (curs < len && isNotSep(c));
      *ptr = '\0';
      push_stack(parser, buffer);
      t = SYMBOL;
    } else
      t = tCOLON;
  } else if (*c == ';') {
    curs++;
    t = tSEMICOLON;
  } else if (*c == '?') {
    curs++;
    t = tQUESTION;
  } else if (*c == '\'') {
    curs++;
    ++c;
    while (1) {
      if (*c == '\\' && *(c + 1) == '\'') {
        c += 2;
        curs += 2;
      }
      if (*c == '\'')
        break;
      if (curs >= len) {
        yyerror(parser, "unterminated string meets end of file");
        t = token_invalid;
        break;
      }
      c++;
      curs++;
    }
    parser->expr_seen = 1;
    curs++;
    t = STRING;
  } else if (*c == '"') {
    curs++;
    ++c;
    while (1) {
      if (*c == '#' && *(c + 1) == '{') {
        c += 2;
        curs += 2;
        for (; *c != '}'; ++c, ++curs)
          if (curs >= len || *c == '"') {
            yyerror(parser, "expecting '}' token in string");
            curs = len + 1; /* So we can force curs >= len error */
            break;
          }
      }
      if (*c == '\\' && *(c + 1) == '"') {
        c += 2;
        curs += 2;
      }
      if (*c == '"')
        break;
      if (curs >= len) {
        yyerror(parser, "unterminated string meets end of file");
        t = token_invalid;
        break;
      }
      c++;
      curs++;
    }
    parser->expr_seen = 1;
    curs++;
    t = STRING;
  } else if (*c == '(') {
    curs++;
    t = tLPAREN;
  } else if (*c == ')') {
    curs++;
    t = tRPAREN;
  } else if (*c == '{') {
    curs++;
    t = tLBRACE;
  } else if (*c == '}') {
    curs++;
    t = tRBRACE;
  } else if (*c == ',') {
    curs++;
    t = tCOMMA;
  } else if (*c == '`') {
    curs++;
    ++c;
    while (1) {
      if (*c == '#' && *(c + 1) == '{') {
        c += 2;
        curs += 2;
        for (; *c != '}'; ++c, ++curs)
          if (curs >= len || *c == '`') {
            yyerror(parser, "expecting '}' token in backtick command");
            curs = len + 1; /* So we can force curs >= len error */
            break;
          }
      }
      if (*c == '\\' && *(c + 1) == '`') {
        curs += 2;
        c += 2;
      }
      if (*c == '`')
        break;
      if (curs >= len) {
        yyerror(parser, "unterminated backtick command meets end of file");
        t = token_invalid;
        break;
      }
      c++;
      curs++;
    }
    parser->expr_seen = 1;
    curs++;
    t = tBACKTICK;
  } else if (*c == '~') {
    curs++;
    parser_dot_seen(t, tTILDE);
  } else if (*c == '^') {
    curs++;
    parser_dot_seen(t, tXOR_BIT);
  }
 
  /*
   * Once we have the token id, we should update the parser
   * flags to avoid conflicts and weird behavior :P
   */

  if (t == DO && !parser->no_block) {
    t = DO_BLOCK;
    parser->no_block = 0;
    parser->dot_seen = 0;
  }

  parser->column += curs - parser->cursor;
  parser->cursor = curs;
  if (curs >= len)
    parser->eof_reached = 1;
  if (t == tOP_ASGN || t == tASGN)
    parser->expr_seen = 0;
  if (t == token_whitespace)
    t = EOL;
  return t;
}

/*
 * Standard yylex. It's quite simple, just cast
 * the (void *) and call parser_yylex
 */
static int yylex(void * lval, void * p)
{
  struct parser_t * parser = (struct parser_t *) p;

  return parser_yylex(parser);
}

/*
 * Error handling. Take the formmated string s and append the error
 * string to the list of errors p->errors.
 */
void yyerror(struct parser_t * p, const char * s, ...)
{
  char err[256];

  sprintf(err, "%s:%i: ", p->name, p->line);
  strcat(err, s);

  p->errors[p->error_index].msg = strdup(err);
  p->errors[p->error_index].line = p->line;
  p->errors[p->error_index].col = p->column;
  p->errors[p->error_index].valid = 1;
  p->error_index++;

  p->eof_reached = 1;
}

RubyAst * rb_compile_file(const char * path)
{
  struct parser_t p;
  RubyAst * result;

  /* Open specified file */
  FILE * fd = fopen(path, "r");
  if (!fd) {
    fprintf(stderr, "Cannot open file: %s\n", path);
    return 0;
  }

  /* Set up parser */
  init_parser(&p);
  if (retrieve_source(&p, fd) < 0) {
    fclose(fd);
    return 0;
  }

  p.name = strdup(path);
  result = (RubyAst *) malloc (sizeof(RubyAst));
  result->tree = NULL;
  for (;;) {
    yyparse(&p);
    if (p.ast != NULL) {
      if (result->tree == NULL)
        result->tree = p.ast;
      else
        update_list(result->tree, p.ast);
    }
    if (p.eof_reached) {
      result->errors[0] = p.errors[0];
      result->errors[1] = p.errors[1];
      break;
    }
  }
  free_parser(&p);

  return result;
}

/*
 * Compile a file like the rb_compile_file function but printing
 * things directly to the stdout. This function is used for the tests.
 */
int yycompile_file(const char * path)
{
  struct parser_t p;
  int index;

  /* Open specified file */
  FILE * fd = fopen(path, "r");
  if (!fd) {
    fprintf(stderr, "Cannot open file: %s\n", path);
    return 0;
  }

  /* Set up parser */
  init_parser(&p);
  if (retrieve_source(&p, fd) < 0) {
    fclose(fd);
    return 0;
  }

  p.name = strdup(path);
  printf("Resulting AST's:");
  for (;;) {
    printf("\n");
    yyparse(&p);
    print_node(p.ast);
    if (p.ast != NULL) {
      if (p.ast->cond != NULL) {
        printf("\nCondition: ");
        print_node(p.ast->cond);
      }
      if (p.ast->ensure != NULL) {
        printf("\nEnsure: ");
        print_node(p.ast->ensure);
      }
    }
    if (p.eof_reached) {
      print_errors(p.errors);
      break;
    }
  }

  /* Check if the stack is empty or not */
  for (index = 0; index < p.sp; index++)
    printf("\nT: %s", p.stack[index]->name);
  printf("\n");
  free_parser(&p);

  return 1;
}

