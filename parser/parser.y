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

#include <node.h>
#include "parser.h"


#define STACK_SIZE 128


/* Flags used by the lexer */
struct flags_t {
  unsigned char eof_reached : 1;
  unsigned char expr_seen : 1;
  unsigned char class_seen : 1;
  unsigned char no_block : 1;
  unsigned char dot_seen : 1;
  unsigned char last_is_paren : 1;
};

#define eof_reached lexer_flags.eof_reached
#define expr_seen lexer_flags.expr_seen
#define class_seen lexer_flags.class_seen
#define no_block lexer_flags.no_block
#define dot_seen lexer_flags.dot_seen
#define last_is_paren lexer_flags.last_is_paren


/* Structure representing a position */
struct pos_t {
  int startLine, endLine;
  int startCol, endCol;
};

/* A comment has a text and a line */
struct comment_t {
  char *comment;
  int line;
};


/*
 * This structure defines the parser. It contains the AST, some
 * flags used for internal reasons and some info about the
 * content to parse.
 */
struct parser_t {
  /* Abstract Syntax Tree */
  struct node * ast;

  /* Stack of positions */
  struct pos_t * pos_stack;
  struct pos_t auxiliar;
  struct node * last_pos;
  unsigned char call_args : 1;
  int stack_scale;
  int pos_size;

  /* Flags used by the parser */
  struct flags_t lexer_flags;
  int in_def;

  /* Errors on the file */
  struct error_t errors[2];
  int error_index;

  /* Stack of names */
  char * stack[2];
  struct node * string_names;
  int sp;

  /* The last allocated comment + the comment stack  */
  struct comment_t last_comment;
  char *comment_stack[STACK_SIZE];
  int comment_index;

  /* Info about the content to parse */
  unsigned long cursor;
  unsigned long length;
  unsigned long line;
  unsigned long column;
  char * name;
  char * blob;
};

#define yyparse ruby_yyparse
#define YYLEX_PARAM parser


/* yy's functions */
int yylex(void *, void *);
void yyerror(struct parser_t * p, const char * s, ...);

/* Parser auxiliar functions */
void init_parser(struct parser_t * p);
void free_parser(struct parser_t * p);
int check_lhs(struct node * n);
int retrieve_source(struct parser_t * p, const char * path);

#define ALLOC_N(kind, l, r) alloc_node(kind, l, r); fix_pos(parser, yyval.n);
#define ALLOC_C(kind, cond, l, r) alloc_cond(kind, cond, l, r); fix_pos(parser, yyval.n);
#define ALLOC_MOD(kind, cond, l, r) ALLOC_C(kind, cond, l, r); copy_range(yyval.n, l, cond);

void pop_stack(struct parser_t * parser, struct node * n);
#define POP_STACK pop_stack(parser, yyval.n)
void pop_string(struct parser_t * parser, struct node * n);
#define POP_STR pop_string(parser, yyval.n)
void push_string(struct parser_t * parser, char * buffer);
void multiple_string(struct parser_t * parser, struct node * n);
void push_last_comment(struct parser_t * parser);
void pop_comment(struct parser_t * parser, struct node *n);


void fix_pos(struct parser_t * parser, struct node * n);
void push_pos(struct parser_t * parser, struct pos_t tokp);
void pop_pos(struct parser_t * parser, struct node * n);
void pop_start(struct parser_t * parser, struct node * n);
void pop_end(struct parser_t * parser, struct node * n);
#define copy_start(dest, src) dest->startLine = src->startLine; dest->startCol = src->startCol
#define copy_end(dest, src) dest->endLine = src->endLine; dest->endCol = src->endCol
#define copy_range(dest, src1, src2) copy_start(dest, src1); copy_end(dest, src2)
#define copy_pos(dest, src) copy_range(dest, src, src);
#define manual_fix() {\
    struct node * n = parser->last_pos; \
    struct pos_t tp = { n->startLine, n->startCol, n->endLine, n->endCol }; \
    pop_pos(parser, parser->last_pos); \
    push_pos(parser, tp);\
  }
#define fix_mrhs(n) { if (n->r->last != NULL) { copy_end(n, n->r->last); } }
#define fix_mrhs_left(n) { if (n->l->last != NULL) { copy_end(n, n->l->last); } }
#define CONCAT_STRING     parser->auxiliar.endLine = parser->pos_stack[parser->pos_size - 1].endLine; \
                          parser->auxiliar.endCol = parser->pos_stack[parser->pos_size - 1].endCol;
%}

%pure_parser
%parse-param {struct parser_t * parser }

%union {  struct node * n;  }

/* Reserved words */
%token CLASS MODULE DEF UNDEF BEGIN RESCUE ENSURE END IF UNLESS THEN ELSIF
%token ELSE CASE WHEN WHILE UNTIL FOR BREAK NEXT REDO RETRY IN DO DO_BLOCK
%token RETURN YIELD KWAND KWOR KWNOT ALIAS DEFINED upBEGIN upEND
%token HEREDOC tTRUE tFALSE NIL ENCODING tFILE LINE SELF SUPER

/* Declare tokens */
%token EOL CVAR NUMBER SYMBOL FNAME BASE STRING REGEXP MCALL ARRAY SARY
%token IVAR GLOBAL tLBRACKET tRBRACKET tDOT tTILDE tBACKTICK tCOMMA tCOLON
%token tPOW tUMINUS tUPLUS tLSHIFT tRSHIFT tASSOC tQUESTION tSEMICOLON COMMENT
%token tOR tAND tAND_BIT tOR_BIT tXOR_BIT tLBRACE tRBRACE tLPAREN tRPAREN
%token tLESSER tGREATER tNOT tPLUS tMINUS tMUL tDIV tMOD KEY CONST tCOLON3
%token tASGN tOP_ASGN tCMP tEQ tEQQ tNEQ tMATCH tNMATCH tGEQ tLEQ tCOLON2


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
%type <n> block_args exp_for exc_list rescue_list rescue_item function_args block_params
%type <n> f_bad_arg simple_assign item_list opt_rescue_arg symbol exp_or_hash
%type <n> bracket_list bracket_item array_exp m_call_args exp_hash sary const single_name_mcall
%type <n> dot_method_call dot_items dot_item scope_items array_value opt_bracket_list key
%type <n> m_call_args_paren opt_call_args_paren call_args_paren exp_paren fname_or_const

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
  | assign                { fix_mrhs($$); }
  | method_call opt_lambda_body
  {
    $$ = update_list($1, $2);
    parser->call_args = 0;
  }
  | hash
  | stmt m_if exp         { $$ = ALLOC_MOD(token_if, $3, $1, NULL);     }
  | stmt m_unless exp     { $$ = ALLOC_MOD(token_unless, $3, $1, NULL); }
  | stmt m_while exp      { $$ = ALLOC_MOD(token_while, $3, $1, NULL);  }
  | stmt m_until exp      { $$ = ALLOC_MOD(token_until, $3, $1, NULL);  }
  | exp
;

stmts: stmt               { $$ = $1;  }
  | stmts terms stmt      { $$ = update_list($1, $3);  }
;

basic: variable           { $$ = $1;  }
  | NUMBER                { $$ = ALLOC_N(token_numeric, NULL, NULL);   }
  | symbol                { $$ = $1;  }
  | string
  {
    $$ = ALLOC_N(token_string, NULL, NULL); POP_STR;
    multiple_string(parser, $$);
  }
  | REGEXP                { $$ = ALLOC_N(token_regexp, NULL, NULL); POP_STR;    }
  | HEREDOC               { $$ = ALLOC_N(token_heredoc, NULL, NULL);   }
  | tBACKTICK             { $$ = ALLOC_N(token_backtick, NULL, NULL); POP_STR;  }
  | other_keywords        { $$ = ALLOC_N(token_object, NULL, NULL);    }
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
  {
    CONCAT_STRING;
    pop_pos(parser, NULL);
  }
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

primary2: NUMBER          { $$ = ALLOC_N(token_numeric, NULL, NULL);   }
  | symbol                { $$ = $1;  }
  | string
  {
    $$ = ALLOC_N(token_string, NULL, NULL); POP_STR;
    multiple_string(parser, $$);
  }
  | REGEXP                { $$ = ALLOC_N(token_regexp, NULL, NULL); POP_STR;   }
  | HEREDOC               { $$ = ALLOC_N(token_heredoc, NULL, NULL);   }
  | tBACKTICK             { $$ = ALLOC_N(token_backtick, NULL, NULL); POP_STR; }
  | array                 { $$ = $1;  }
  | other_keywords        { $$ = ALLOC_N(token_object, NULL, NULL);    }
;

simple_stmt: BREAK        { $$ = ALLOC_N(token_break, NULL, NULL);   }
  | REDO                  { $$ = ALLOC_N(token_redo, NULL, NULL);    }
  | RETRY                 { $$ = ALLOC_N(token_retry, NULL, NULL);   }
  | NEXT                  { $$ = ALLOC_N(token_next, NULL, NULL);    }
  | UNDEF item_list       { $$ = ALLOC_N(token_undef, NULL, $2); fix_mrhs($$);      }
  | ALIAS item item       { $$ = ALLOC_N(token_alias, $2, $3); copy_end($$,$3);     }
  | yield_stmt            { $$ = $1;  }
  | return_stmt           { $$ = $1;  }
;

yield_stmt: YIELD         { $$ = ALLOC_N(token_yield, NULL, NULL);   }
  | YIELD exp             { $$ = ALLOC_N(token_yield, $2, NULL);     }
;

return_stmt: RETURN       { $$ = ALLOC_N(token_return, NULL, NULL);  }
  | RETURN exp            { $$ = ALLOC_N(token_return, $2, NULL); copy_end($$, $2);   }
;

item_list: item           { $$ = $1;  }
  | item comma item_list  { $$ = update_list($1, $3); }
;

item: BASE                { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
  | FNAME                 { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
  | symbol                { $$ = $1; }
;

cmpd_stmt: k_if exp then
  compstmt
  if_tail
  END
  {
    $$ = ALLOC_C(token_if, $2, $4, $5);
    pop_start(parser, $$);
  }
  | k_unless exp then
    compstmt
    if_tail
    END
    {
      $$ = ALLOC_C(token_unless, $2, $4, $5);
      pop_start(parser, $$);
    }
  | k_while exp do
    compstmt
    END
    {
      $$ = ALLOC_C(token_while, $2, $4, NULL);
      pop_start(parser, $$);
    }
  | k_until exp do
    compstmt
    END
    {
      $$ = ALLOC_C(token_until, $2, $4, NULL);
      pop_start(parser, $$);
    }
  | k_case exp opt_terms
    case_body
    END
    {
      $$ = ALLOC_C(token_case, $2, $4, NULL);
      pop_start(parser, $$);
    }
  | k_case case_body END
    {
      $$ = ALLOC_C(token_case, NULL, $2, NULL);
      pop_start(parser, $$);
    }
  | upBEGIN tLBRACE compstmt tRBRACE
    {
      $$ = ALLOC_N(token_up_begin, $3, NULL);
      pop_pos(parser, NULL);
      pop_start(parser, $$);
    }
  | upEND tLBRACE compstmt tRBRACE
    {
      $$ = ALLOC_N(token_up_end, $3, NULL);
      pop_pos(parser, NULL);
      pop_start(parser, $$);
    }
  | k_for mlhs k_in exp_for do compstmt END
    {
      $$ = ALLOC_C(token_for, $4, $6, $2);
      pop_pos(parser, NULL);
      pop_start(parser, $$);
    }
  | BEGIN bodystmt END
    {
      $$ = ALLOC_N(token_exception, $2, NULL);
      pop_start(parser, $$);
    }
  | k_def single_name
    {
      parser->in_def++;
    }
    function_args bodystmt END
    {
      parser->in_def--;
      $$ = ALLOC_C(token_function, $2, $5, $4);
      pop_comment(parser, $$);
      pop_start(parser, $$);
    }
  | k_def single_name_mcall
    {
      parser->in_def++;
    }
    f_arglist tRPAREN bodystmt END
    {
      parser->in_def--;
      $$ = ALLOC_C(token_function, $2, $6, $4);
      pop_comment(parser, $$);
      pop_start(parser, $$);
    }
  | k_module module_name
    {
      if (parser->in_def)
        yyerror(parser, "module definition in method body");
    }
    bodystmt
    END
    {
      $$ = ALLOC_N(token_module, $4, $2);
      pop_comment(parser, $$);
      pop_start(parser, $$);
    }
  | k_class module_name
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    }
    bodystmt
    END
    {
      $$ = ALLOC_C(token_class, NULL, $4, $2);
      pop_comment(parser, $$);
      pop_start(parser, $$);
    }  
  | k_class module_name superclass
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    }
    bodystmt
    END
    {
      $$ = ALLOC_C(token_class, $3, $5, $2);
      pop_comment(parser, $$);
      pop_start(parser, $$);
    }
  | k_class tLSHIFT exp_or_hash
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    }
    term
    bodystmt
    END
    {
      $$ = ALLOC_N(token_singleton_class, $6, $3);
      pop_comment(parser, $$);
      pop_start(parser, $$);
    }
;

fname: FNAME    { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
  | base        { $$ = $1;  }
;

fname_or_const: fname { $$ = $1;  }
  | const             { $$ = $1;  }
;

single_name: base dot_or_scope fname
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_range($$, $1, $3);
  }
  | fname   { $$ = $1;  }
;

single_name_mcall: base dot_or_scope mcall
	{
    $$ = alloc_node(token_object, $1, $3);
    copy_range($$, $1, $3);		
	}
	| mcall		{ $$ = $1;	}
;

function_args: f_arglist eol_or_semicolon  { $$ = $1;  }
  | eol_or_semicolon  { $$ = 0; }
;

module_name: CONST  { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
  | const_scope     { $$ = $1;  }
  | BASE
  {
    yyerror(parser, "class/module name must be CONSTANT");
  }
;

variable: base  { $$ = $1; }
  | CVAR        { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
  | GLOBAL      { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
  | IVAR        { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
  | CONST       { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
;

base: BASE      { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
;

mcall: MCALL    { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; $$->endCol--; }
;

const: CONST    { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
;

symbol: SYMBOL  { $$ = ALLOC_N(token_symbol, NULL, NULL); POP_STACK; }
;

key: KEY        { $$ = ALLOC_N(token_symbol, NULL, NULL); POP_STACK; }
;

if_tail: opt_else
  | k_elsif exp then
    compstmt
    if_tail
    {
      $$ = ALLOC_C(token_if, $2, $4, $5);
      struct pos_t tp = { $$->startLine, $$->endLine, $$->startCol, $$->endCol };

      pop_pos(parser, $$);
      push_pos(parser, tp);
    }
;

opt_else: /* nothing */     { $$ = 0; }
  | ELSE compstmt
  {
    $$ = ALLOC_C(token_if, NULL, $2, NULL);
    struct pos_t tp = { $$->startLine, $$->endLine, $$->startCol, $$->endCol };

    pop_pos(parser, $$);
    push_pos(parser, tp);
  }
;

opt_ensure: /* nothing */   { $$ = 0; }
  | ENSURE compstmt
  {
    $$ = ALLOC_N(token_ensure, $2, NULL);
    struct pos_t tp = { $$->startLine, $$->endLine, $$->startCol, $$->endCol };

    pop_pos(parser, $$);
    push_pos(parser, tp);    
  }
;

opt_rescue: /* nothing */   { $$ = 0;   }
  | rescue_list             { $$ = $1;  }
;

rescue_list: rescue_item    { $$ = $1;  }
  | rescue_list rescue_item { $$ = update_list($1, $2); }
;

rescue_item: RESCUE opt_rescue_arg then compstmt
  {
    $$ = ALLOC_N(token_rescue, $2, $4);
    struct pos_t tp = { $$->startLine, $$->endLine, $$->startCol, $$->endCol };

    pop_pos(parser, $$);
    push_pos(parser, tp);
  }
;

bodystmt: compstmt opt_rescue opt_else opt_ensure
  {
    $$ = alloc_ensure(token_body, $1, $2, $3, $4);
    if ($1 != NULL) {
      if ($1->last != NULL) {
        copy_range($$, $1, $1->last);
      } else {
        copy_range($$, $1, $1);
      }
    }
  }
;

superclass: tLESSER opt_eol_list module_name  { $$ = $3;  }
;

opt_lambda_body: /* nothing */  { $$ = 0;   }
  | lambda_body                 { $$ = $1;  }
;

lambda_body: brace_block  { $$ = $1;  }
  | do_block              { $$ = $1;  }
;

brace_block: lbrace block_args not_empty_compstmt tRBRACE
  {
    pop_pos(parser, NULL);
    $$ = ALLOC_N(token_block, $3, $2);
    if ($3->last != NULL) {
      copy_end($$, $3->last);
    } else {
      copy_end($$, $3);
    }
  }
  | lbrace not_empty_compstmt tRBRACE
  {
    pop_pos(parser, NULL);
    $$ = ALLOC_N(token_block, $2, NULL);
    if ($2->last != NULL) {
      copy_end($$, $2->last);
    } else {
      copy_end($$, $2);
    }
  }
;

do_block: k_do_block endl block_args compstmt END
  {
    pop_pos(parser, parser->last_pos);
    $$ = ALLOC_N(token_block, $4, $3);
    if ($4 != NULL) {
      if ($4->last != NULL) {
        copy_end($$, $4->last);
      } else {
        copy_end($$, $4);
      }
    } else { 
      copy_pos($$, parser->last_pos);
    }
  }
  | k_do_block compstmt END
  {
    pop_pos(parser, parser->last_pos);
    $$ = ALLOC_N(token_block, $2, NULL);
    if ($2 != NULL) {
      if ($2->last != NULL) {
        copy_end($$, $2->last);
      } else {
        copy_end($$, $2);
      }
    } else {
      copy_pos($$, parser->last_pos);
    }
  }
;

block_params: f_arguments { $$ = $1;  }
  | comma tAND_BIT arg    { $$ = $3;  }
  | f_args comma          { $$ = $1;  }
  | f_args comma f_restarg f_blockarg
  {
    $$ = concat_list($1, update_list($3, $4));
  }
  | f_args comma f_restarg comma f_args f_blockarg
  {
    $$ = concat_list($1, create_list($3, update_list($5, $6)));
  }
;

block_args: tOR_BIT block_params bv_decls tOR_BIT
  {
    $$ = alloc_node(token_object, $2, $3);
    copy_range($$, $2, $3); 
  }
  | tOR_BIT bv_decls tOR_BIT
  {
    $$ = alloc_node(token_object, NULL, $2);
    copy_range($$, $2, $2); 
  }
  | tOR_BIT block_params tOR_BIT
  {
    $$ = alloc_node(token_object, $2, NULL);
    copy_range($$, $2, $2); 
  }
;

bv_decls: tSEMICOLON block_list   { $$ = $2;  }
;

block_list: base          { $$ = $1;  }
  | block_list comma base { $$ = update_list($1, $3); }
;

f_arglist: f_arguments            { $$ = $1;  }
  | tAND_BIT arg                  { $$ = $2;  }
  | lparen f_arguments rparen     { $$ = $2;  }
  | lparen tAND_BIT arg rparen    { $$ = $3;  }
;

f_arguments: f_args f_blockarg    { $$ = update_list($1, $2);  }
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

f_opt: arg tASGN primary
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_range($$, $1, $3);
  }
;

f_optarg: f_opt           { $$ = $1;  }
  | f_optarg comma f_opt  { $$ = update_list($1, $3); }
;

arg: BASE                 { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
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
    if ($2 != NULL) {
      copy_range($$, $1, $2);
    } else {
      copy_range($$, $1, $1);
    }
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
    /* The following statements fixes some issues around positions. */
    $$ = ALLOC_N(token_object, NULL, NULL);
    struct pos_t t = {$$->startLine, $$->endLine, $$->startCol, $$->endCol};
    $$ = ALLOC_C(token_when, $2, $4, $5);
    push_pos(parser, t);
  }
;

cases: opt_else
  | case_body
;

then: term
  | THEN      { pop_pos(parser, NULL);  }
  | term THEN { pop_pos(parser, NULL);  }
;

do: term
  | DO
  {
    if (!parser->call_args) {
      pop_pos(parser, parser->last_pos);
      parser->call_args = 1;
    } else
      pop_pos(parser, NULL);
  }
;

k_do_block: DO_BLOCK
  {
    struct node * n = parser->last_pos;
    struct pos_t tp = { n->startLine, n->endLine, n->startCol, n->endCol };

    if (parser->call_args) {
      pop_pos(parser, parser->last_pos);
      push_pos(parser, tp);
      parser->call_args = 0;
    }
  }
;

k_if: IF opt_eol_list
;

m_if: IF  { manual_fix(); }
;

m_unless: UNLESS    { manual_fix(); }
;

m_while: WHILE      { manual_fix(); }
;

m_until: UNTIL      { manual_fix(); }
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

k_for: FOR opt_eol_list   { parser->call_args = 1;  }
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
  | tCOLON2
;

eol_or_semicolon: EOL
  | tSEMICOLON
;

lhs_list: mlhs comma lhs    { $$ = update_list($1, $3);  }
  | mlhs comma              { $$ = $1;  }
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
  | lparen lhs_list rparen
  {
    $$ = alloc_node(token_object, $2, NULL);
    if ($2->last != NULL) {
      copy_range($$, $2, $2->last);
    } else {
      copy_range($$, $2, $2);
    }
  }
  | tMUL variable             { $$ = $2;  }
  | tMUL
  {
    $$ = alloc_node(token_object, NULL, NULL);
    $$->startLine = $$->endLine = parser->auxiliar.startLine;
    $$->startCol = parser->auxiliar.startCol;
    $$->endCol = $$->startCol + 1;
    parser->auxiliar.endLine = -1;
  }
;

opt_bracket_list: /* nothing */ { $$ = 0; }
  | bracket_list                { $$ = $1;  }
;

bracket_list: bracket_item      { $$ = $1;  }
  | bracket_list bracket_item   { $$ = update_list($1, $2); }
;

bracket_item: lbracket array_exp rbracket { $$ = $2; pop_pos(parser, NULL); }
;

mlhs: exp           { $$ = $1;  }
  | mlhs comma      { $$ = $1;  }
  | mlhs comma lhs  { $$ = update_list($1, $3); }
;

mrhs: exp                   { $$ = $1;  }
  | mrhs comma exp          { $$ = update_list($1, $3); }
;

simple_assign: variable asgn primary  { $$ = ALLOC_N(token_assign, $1, $3);    }
  | variable op_asgn primary          { $$ = ALLOC_N(token_op_assign, $1, $3); }
  | variable asgn hash                { $$ = ALLOC_N(token_assign, $1, $3);    }
  | variable op_asgn hash             { $$ = ALLOC_N(token_op_assign, $1, $3); }
;

assign: mlhs asgn mrhs       { $$ = ALLOC_N(token_assign, $1, $3);   }
  | mlhs op_asgn mrhs        { $$ = ALLOC_N(token_op_assign, $1, $3); }
  | mlhs asgn method_call opt_lambda_body
  {
    $$ = ALLOC_N(token_assign, $1, $3);
    $$ = update_list($$, $4);
    parser->call_args = 0;
  }
  | mlhs op_asgn method_call opt_lambda_body
  {
    $$ = ALLOC_N(token_op_assign, $1, $3);
    $$ = update_list($$, $4);
    parser->call_args = 0;
  }
  | mlhs asgn hash           { $$ = ALLOC_N(token_assign, $1, $3);     }
  | mlhs op_asgn hash        { $$ = ALLOC_N(token_op_assign, $1, $3);  }
  | mlhs asgn cmpd_stmt      { $$ = ALLOC_N(token_assign, $1, $3);     }
  | mlhs op_asgn cmpd_stmt   { $$ = ALLOC_N(token_op_assign, $1, $3);  }
;

array: lbracket tRBRACKET               { $$ = ALLOC_N(token_array, NULL, NULL); }
  | lbracket array_items rbracket       { $$ = ALLOC_N(token_array, $2, NULL); fix_mrhs_left($$);  }
  | ARRAY                               { $$ = ALLOC_N(token_array, NULL, NULL); POP_STR; }
;

array_exp: exp      { $$ = $1;  }
  | simple_assign   { $$ = $1;  }
  | hash            { $$ = $1;  }
;

array_items: array_exp              { $$ = $1;  }
  | array_items comma               { $$ = $1;  }
  | array_items comma array_exp     { $$ = update_list($1, $3); }
;

array_value: sary opt_eol_list array_exp rbracket opt_bracket_list
  {
    struct node * n = $3;
    n->next = $5;
    $$ = alloc_node(token_array_value, $1, n);
    if ($5 != NULL) {
      if ($5->last != NULL) {
        copy_range($$, $1, $5->last);
      } else {
        copy_range($$, $1, $5);
      }
    } else {
      copy_range($$, $1, $3);
    }
  }/* TODO */
/*  | variable bracket_item bracket_list
  {
    $$ = alloc_node(token_array_value, $1, create_list($2, $3));
  }*/
;

sary: SARY
  {
    $$ = ALLOC_N(token_object, NULL, NULL);
    $$->endCol--;
    POP_STACK;
  }
;

hash: lbrace tRBRACE
  { 
    $$ = alloc_node(token_hash, NULL, NULL);
    pop_pos(parser, $$);
    pop_start(parser, $$);
  }
  | lbrace hash_items rbrace
  {
    pop_pos(parser, parser->last_pos);
    $$ = ALLOC_N(token_hash, $2, NULL);
    fix_mrhs_left($$);
  }
;

hash_items: hash_item           { $$ = $1;  }
  | hash_items comma            { $$ = $1;  }
  | hash_items comma hash_item  { $$ = update_list($1, $3); }
;

hash_item: exp tASSOC opt_eol_list exp
  {
    $$ = alloc_node(token_object, $1, $4);
    copy_range($$, $1, $4);
  }
  | key opt_eol_list exp
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_range($$, $1, $3);
  }
;

method_call: fname m_call_args
  {
    $$ = alloc_node(token_method_call, $1, $2);
    if ($2 == NULL) {
      copy_pos($$, $1);
    } else if ($2->last != NULL) {
      copy_range($$, $1, $2->last);
    } else {
      copy_range($$, $1, $2);
    }
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
  | const_scope m_call_args
  {
    $$ = alloc_node(token_method_call, $1, $2);
    if ($2 == NULL) {
      copy_range($$, $1, $1);
    } else {
      if ($2->last != NULL) {
        copy_range($$, $1, $2->last);
      } else {
        copy_range($$, $1, $2);
      }
    }
  }
;

const_scope: const scope_items
  {
    struct node * n = alloc_node(token_object, $1, NULL);
    $$ = pop_list(n, $2);
    if ($2->last != NULL) {
      copy_range($$, $1, $2->last);
    } else {
      copy_range($$, $1, $2);
    }
  }
  | const tCOLON2 fname
  {
    struct node * n = alloc_node(token_object, $1, NULL);
    $$ = pop_list(n, $3);
    copy_range($$, $1, $3);
  }
  | tCOLON3 const scope_items
  {
    struct node * n = alloc_node(token_object, $2, NULL);
    $$ = pop_list(n, $3);
    if ($3->last != NULL) {
      copy_range($$, $2, $3->last);
    } else {
      copy_range($$, $2, $3);
    }
  }
;

scope_items: tCOLON2 const               { $$ = $2;  }
  | scope_items tCOLON2 fname_or_const   { $$ = update_list($1, $3); }
;

paren_method_call: mcall opt_call_args_paren rparen
  {
    $$ = alloc_node(token_method_call, $1, $2);
    if ($2 == NULL) {
      copy_range($$, $1, $1);
    } else {
      if ($2->last != NULL) {
        copy_range($$, $1, $2->last);
      } else {
        copy_range($$, $1, $2);
      }
    }
  }
  | const_mcall opt_call_args_paren rparen
  {
    $$ = alloc_node(token_method_call, $1, $2);
    if ($2 == NULL) {
      copy_range($$, $1, $1);
    } else {
      if ($2->last != NULL) {
        copy_range($$, $1, $2->last);
      } else {
        copy_range($$, $1, $2);
      }
    }
  }
;

const_mcall: const tCOLON2 mcall { $$ = ALLOC_N(token_object, $1, $3); }
;

dot_method_call: basic dot_items
  {
    struct node * n = alloc_node(token_method_call, $1, NULL);
    $$ = pop_list(n, $2);
    if ($2->last != NULL) {
      copy_range($$, $1, $2->last);
    } else {
      copy_range($$, $1, $2);
    }
  }
  | lparen exp rparen dot_items
  {
    struct node * n = alloc_node(token_method_call, $2, NULL);
    $$ = pop_list(n, $4);
    if ($4->last != NULL) {
      copy_range($$, $2, $4->last);
    } else {
      copy_range($$, $2, $4);
    }
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

opt_call_args_paren: /* nothing */  { $$ = 0;   }
  | m_call_args_paren               { $$ = $1;  }
;

m_call_args: method_call      { $$ = $1;  }
  | call_args
  {
    $$ = $1;
    parser->call_args = 1;
  }
;

m_call_args_paren: method_call  { $$ = $1;  }
  | call_args_paren             { $$ = $1;  }
;

/* TODO: tMUL and tAND_BIT ambiguity :S */
call_args: exp                { $$ = $1;  }
  | call_args comma exp_hash  { $$ = update_list($1, $3); }
;

call_args_paren: exp_paren          { $$ = $1;  }
  | call_args_paren comma exp_paren { $$ = update_list($1, $3); }
;

exp_or_hash: exp { $$ = $1; }
  | hash         { $$ = $1; }
;

/* TODO: hash with exp */
exp_hash: exp   { $$ = $1;  }
  | const_scope { $$ = $1;  }
  | hash        { $$ = $1;  }
  | hash_items
  {
    $$ = alloc_node(token_hash, $1, NULL);
    if ($1->last != NULL) {
      copy_range($$, $1, $1->last);
    } else {
      copy_range($$, $1, $1);
    }
  }
;

exp_paren: exp_hash   { $$ = $1;  }
  | tAND_BIT exp      { $$ = $2;  }
  | tMUL exp          { $$ = $2;  }
;

/* TODO: hash with exp */
exp_for: exp    { $$ = $1;  }
  | hash        { $$ = $1;  }
;

exp: exp tPLUS opt_eol_list exp       { $$ = ALLOC_N(token_plus, $1, $4);    }
  | exp tMINUS opt_eol_list exp       { $$ = ALLOC_N(token_minus, $1, $4);   }
  | exp tMUL opt_eol_list exp         { $$ = ALLOC_N(token_mul, $1, $4);     }
  | exp tDIV opt_eol_list exp         { $$ = ALLOC_N(token_div, $1, $4);     }
  | exp tMOD opt_eol_list exp         { $$ = ALLOC_N(token_mod, $1, $4);     }
  | exp tPOW opt_eol_list exp         { $$ = ALLOC_N(token_exp, $1, $4);     }
  | exp tAND_BIT opt_eol_list exp     { $$ = ALLOC_N(token_bit_and, $1, $4); }
  | exp tOR_BIT opt_eol_list exp      { $$ = ALLOC_N(token_bit_or, $1, $4);  }
  | exp tXOR_BIT opt_eol_list exp     { $$ = ALLOC_N(token_bit_xor, $1, $4); }
  | exp tLSHIFT opt_eol_list exp      { $$ = ALLOC_N(token_lshift, $1, $4);  }
  | exp tRSHIFT opt_eol_list exp      { $$ = ALLOC_N(token_rshift, $1, $4);  }
  | lparen exp rparen                 { $$ = $2;  }
  | lparen assign rparen              { $$ = $2; fix_mrhs($$);  }
  | lparen method_call rparen         { $$ = $2;  }
  | exp tCMP opt_eol_list exp         { $$ = ALLOC_N(token_cmp, $1, $4);     }
  | exp tEQ opt_eol_list exp          { $$ = ALLOC_N(token_eq, $1, $4);      }
  | exp tNEQ opt_eol_list exp         { $$ = ALLOC_N(token_neq, $1, $4);     }
  | exp tEQQ opt_eol_list exp         { $$ = ALLOC_N(token_eqq, $1, $4);     }
  | exp tMATCH opt_eol_list exp       { $$ = ALLOC_N(token_match, $1, $4);   }
  | exp tNMATCH opt_eol_list exp      { $$ = ALLOC_N(token_nmatch, $1, $4);  }
  | exp tGREATER opt_eol_list exp     { $$ = ALLOC_N(token_greater, $1, $4); }
  | exp tLESSER opt_eol_list exp      { $$ = ALLOC_N(token_lesser, $1, $4);  }
  | exp tGEQ opt_eol_list exp         { $$ = ALLOC_N(token_geq, $1, $4);     }
  | exp tLEQ opt_eol_list exp         { $$ = ALLOC_N(token_leq, $1, $4);     }
  | exp tOR opt_eol_list exp          { $$ = ALLOC_N(token_or, $1, $4);      }
  | exp tAND opt_eol_list exp         { $$ = ALLOC_N(token_and, $1, $4);     }
  | exp KWOR opt_eol_list exp         { $$ = ALLOC_N(token_kw_or, $1, $4);   }
  | exp KWAND opt_eol_list exp        { $$ = ALLOC_N(token_kw_and, $1, $4);  }
  | exp tDOT2 opt_eol_list exp        { $$ = ALLOC_N(token_dot2, $1, $4);    }
  | exp tDOT3 opt_eol_list exp        { $$ = ALLOC_N(token_dot3, $1, $4);    }
  | exp tQUESTION opt_eol_list exp opt_eol_list tCOLON opt_eol_list exp
  {
    $$ = ALLOC_C(token_ternary, $1, $4, $8);
  }
  | KWNOT opt_eol_list exp            { $$ = ALLOC_N(token_kw_not, $3, NULL);}
  | tTILDE opt_eol_list exp           { $$ = ALLOC_N(token_neg, $3, NULL);   }
  | tNOT opt_eol_list exp             { $$ = ALLOC_N(token_not, $3, NULL);   }
  | tUPLUS opt_eol_list exp           { $$ = ALLOC_N(token_unary_plus, $3, NULL);  }
  | tUMINUS opt_eol_list exp          { $$ = ALLOC_N(token_unary_minus, $3, NULL); }
  | DEFINED opt_eol_list exp          { $$ = ALLOC_N(token_defined, $3, NULL); copy_end($$, $3);  }
  | primary1 opt_lambda_body          { $$ = update_list($1, $2); }
  | primary2                          { $$ = $1;  }
  | array_value                       { $$ = $1;  }
  | FNAME                             { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
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
#define isNotSep(c) (isValidVariableIdentifier(c) || is_utf8_digit(c) \
                    || *c == '_' || *c == '$' || *c == '@')
#define isSpecialMethod(buffer) ((strlen(buffer) > 4) && buffer[0] == '_' && \
                                buffer[1] == '_' && buffer[strlen(buffer) - 2] == '_' && \
                                buffer[strlen(buffer) - 1] == '_')
#define parser_dot_seen(t, OP) { if (parser->dot_seen) { \
                                  parser->dot_seen = 0; \
                                  t = FNAME; \
                                } else \
                                  t = OP; \
                                }
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
  p->error_index = 0;
  p->sp = 0;
  p->line = 1;
  p->column = 0;
  p->name = NULL;
  p->string_names = NULL;
  p->pos_stack = (struct pos_t *) malloc (STACK_SIZE * sizeof(struct pos_t));
  p->stack_scale = 0;
  p->pos_size = 0;
  p->last_pos = NULL;
  p->call_args = 0;
  p->auxiliar.endLine = -1;
  p->errors[0].valid = 0;
  p->errors[1].valid = 0;
  p->last_comment.comment = NULL;
  p->comment_index = 0;
}

void free_parser(struct parser_t * p)
{
  int index;

  for (index = 0; index < p->sp; index++)
    free(p->stack[index]);
  free(p->pos_stack);
  free(p->blob);
  free(p->name);
  if (p->last_comment.comment != NULL)
    free(p->last_comment.comment);
}

/* Read the file's source code and allocate it for further inspection. */
int retrieve_source(struct parser_t * p, const char * path)
{
  int length;

  /* Open specified file */
  FILE * fd = fopen(path, "r");
  if (!fd) {
    fprintf(stderr, "Cannot open file: %s\n", path);
    return 0;
  }

  fseek(fd, 0, SEEK_END);
  length = ftell(fd);
  fseek(fd, 0, SEEK_SET);

  if (!length)
    return 0;
  p->blob = (char *) malloc (sizeof(char) * length);

  if (!p->blob) {
    fprintf(stderr, "Cannot store contents\n");
    return 0;
  }
  fread(p->blob, length, 1, fd);
  if (ferror(fd)) {
    fprintf(stderr, "Reading error\n");
    return 0;
  }
  p->length = length;
  return 1;
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
int utf8_charsize(const char * s)
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

void push_string_var(struct parser_t * p, int * curs, char ** ch)
{
  char *c = *ch;
  struct pos_t tp = { p->line, p->line, p->column + (*curs - p->cursor + 2), -1 };
  int possible_error = *curs + 1;
  char buffer[BSIZE];
  char * ptr = buffer;
  int step = 0; /* How many bytes the actual utf8 char has */
  int ax = 0; /* Used to properly update the column when the utf8 chars appear */

  c += 2;
  *curs += 2;
  while (*c != '}') {
    step = utf8_charsize(c);
    ax += step - 1;
    while (step-- > 0) {
      *ptr++ = *c++;
      (*curs)++;
    }
    if ((unsigned int) *curs >= p->length || *c == '"') {
      p->column = possible_error;
      yyerror(p, "expecting '}' token in string");
      *curs = p->length + 1; /* So we can force curs >= len error */
      break;
    }
  }
  *ch = c;
  *ptr = '\0';
  p->column -= ax;
  tp.endCol = p->column + *curs - p->cursor;
  push_pos(p, tp);
  push_string(p, buffer);
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
      p->line++;
      aux[i + 1] = '\0';
      if (!strncmp(buffer, aux, l) && (l == i)) {
        p->line--;
        p->column = i;
        return HEREDOC;
      }
      i = -1;
    }
  }
  strcpy(aux, "Can't find string \"");
  strcat(aux, buffer);
  yyerror(p, strcat(aux, "\" anywhere before EOF"));
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
void push_stack(struct parser_t * parser, const char * buf)
{
  parser->stack[parser->sp] = strdup(buf);
  parser->sp++;
}

/* Pop name from the stack. */
void pop_stack(struct parser_t * parser, struct node * n)
{
  n->name = parser->stack[0];
  parser->stack[0] = parser->stack[1];
  parser->stack[1] = NULL;
  parser->sp--;
}

/* Push a string variable */
void push_string(struct parser_t * parser, char * buffer)
{
  struct node * new_node = alloc_node(token_object, NULL, NULL);

  new_node->name = strdup(buffer);
  pop_pos(parser, new_node);
  if (!parser->string_names)
    parser->string_names = new_node;
  else
    parser->string_names = update_list(parser->string_names, new_node);
}

/* Pop a list of string variables */
void pop_string(struct parser_t * parser, struct node * n)
{
  n->l = parser->string_names;
  parser->string_names = NULL;
}

void multiple_string(struct parser_t * parser, struct node * n)
{
  if (parser->auxiliar.endLine > 0) {
    n->endLine = parser->auxiliar.endLine;
    n->endCol = parser->auxiliar.endCol;
    parser->auxiliar.endLine = -1;
  }
}

void push_pos(struct parser_t * parser, struct pos_t tokp)
{
  int scale = STACK_SIZE * parser->stack_scale;

  parser->pos_size++;
  if (parser->pos_size > STACK_SIZE) {
    parser->pos_size = 1;
    parser->stack_scale++;
    scale += STACK_SIZE;
    parser->pos_stack = (struct pos_t *) realloc (parser->pos_stack, scale * sizeof(struct pos_t));
  }
  parser->pos_stack[parser->pos_size + scale - 1] = tokp;
}

void pop_pos(struct parser_t * parser, struct node * n)
{
  int scale = STACK_SIZE * parser->stack_scale;
  int pos = parser->pos_size - 1 + scale;
  struct pos_t tokp = parser->pos_stack[pos];

  if (n != NULL) {
    n->startLine = tokp.startLine;
    n->startCol = tokp.startCol;
    n->endLine = tokp.endLine;
    n->endCol = tokp.endCol;
  }
  parser->pos_size--;
  if (parser->pos_size == 0 && parser->stack_scale > 0) {
    parser->stack_scale--;
    parser->pos_size = STACK_SIZE;
    scale -= STACK_SIZE;
    parser->pos_stack = (struct pos_t *) realloc (parser->pos_stack, scale * sizeof(struct pos_t));
  }
}

void pop_start(struct parser_t * parser, struct node * n)
{
  n->startLine = parser->pos_stack[parser->pos_size - 1].startLine;
  n->startCol = parser->pos_stack[parser->pos_size - 1].startCol;
  pop_pos(parser, NULL);
}

void pop_end(struct parser_t * parser, struct node * n)
{
  n->endLine = parser->pos_stack[parser->pos_size - 1].endLine;
  n->endCol = parser->pos_stack[parser->pos_size - 1].endCol;
  pop_pos(parser, NULL);
}

void push_last_comment(struct parser_t * parser)
{
  if ((parser->line - parser->last_comment.line) < 2)
    parser->comment_stack[parser->comment_index] = parser->last_comment.comment;
  else
    parser->comment_stack[parser->comment_index] = NULL;
  parser->comment_index++;
  parser->last_comment.comment = NULL;
}

void pop_comment(struct parser_t * parser, struct node *n)
{
  parser->comment_index--;
  n->comment = parser->comment_stack[parser->comment_index];
}

/*
 * The following macros are helpers to the fix_pos function.
 */

#define has_operators(kind) ((kind > 1 && kind < token_neg && kind != token_kw_not) || \
                            (kind > token_unary_minus && kind < token_ternary))
#define is_unary(kind) (kind >= token_neg && kind <= token_unary_minus)
#define kw_not_or_hash(kind) (kind == token_hash || kind == token_kw_not)


void fix_pos(struct parser_t * parser, struct node * n)
{
  int kind;

  if (n == NULL)
    return;

  kind = n->kind;
  if (has_operators(kind) && kind != token_hash) {
    n->startLine = n->l->startLine;
    n->startCol = n->l->startCol;
    n->endLine = n->r->endLine;
    n->endCol = n->r->endCol;
  } else if (is_unary(kind) || kw_not_or_hash(kind)) {
    pop_pos(parser, n);
    n->endLine = n->l->endLine;
    n->endCol = n->l->endCol;    
  } else if (kind == token_ternary) {
    n->startLine = n->cond->startLine;
    n->startCol = n->cond->startCol;
    n->endLine = n->r->endLine;
    n->endCol = n->r->endCol;
  } else {
    pop_pos(parser, n);
    parser->last_pos = n;
  }
}

#define __check_should_break { \
  if (*c != '#') { \
    int aux = is_indented_comment(c); \
    if (!aux) \
      break; \
    else { \
      c += aux; \
      curs += aux; \
      i += aux; \
    } \
  } \
}

#define __check_buffer_size(N) { \
  if (count > N) { \
    count = 0; \
    scale++; \
    buffer = (char *) realloc(buffer, scale * 1024); \
  } \
}

#define __handle_comment_eol { \
  c++; curs++; \
  i = 0; \
  parser->line++; \
}

void store_comment(struct parser_t *parser, char *comment)
{
  if (parser->last_comment.comment != NULL)
    free(parser->last_comment.comment);
  parser->last_comment.comment = strdup(comment);
  parser->last_comment.line = parser->line;
  free(comment);
}

int is_indented_comment(char *c)
{
  char *original = c;

  for (; *c == ' ' || *c == '\t'; ++c);
  return (*c == '#') ? (c - original) : 0;
}

int get_comment(struct parser_t *parser, char *c, int curs)
{
  int len = parser->length;
  int initial = curs;
  int i = parser->column;
  int count = 0, scale = 1;
  char *buffer = (char *) malloc(1024);

  for (;; ++count) {
    __check_should_break;

    /* We don't want to store initial #'s */
    for (; *c == '#' && curs < len; ++c, ++curs, ++i);

    if (*c == '\n') {
      buffer[count] = *c;
      __handle_comment_eol;
    } else {
      for (; curs < len; ++c, ++curs, ++i, ++count) {
        __check_buffer_size(1000);
        buffer[count] = *c;
        if (*c == '\n') {
          __handle_comment_eol;
          break;
        }
      }
    }
  }

  buffer[count] = '\0';
  store_comment(parser, buffer);

  /* Magic to preserve the integrity of the column/cursor counting */
  parser->column = i;
  return curs - initial;
}

/*
 * This is the lexer. It reads the source code (blob) and provides tokens to
 * the parser. It also updates the necessary flags.
 */
int parser_yylex(struct parser_t * parser)
{
  int t = YYEOF;
  char buffer[BSIZE];
  char * c;
  int curs, len;
  unsigned char space_seen = 0;
  struct pos_t tokp = {-1, -1, -1, -1};

  curs = parser->cursor;
  len = parser->length;
  if (curs >= len) {
    parser->eof_reached = 1;
    return 0;
  }
  c = parser->blob + curs;

  /* Ignore whitespaces and backslashes */
  space_seen = *c;
  for (; (isspace(*c) || *c == '\\') && *c != '\n';
      ++c, ++curs, parser->column++, parser->cursor++);
  (space_seen != *c) ? (space_seen = 1) : (space_seen = 0);

  if (*c == '#') {
    int inc = get_comment(parser, c, curs);
    curs += inc;
    c += inc;
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

    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
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
    int step = 0; /* How many bytes the actual utf8 char has */
    int ax = 0; /* Used to properly update the column when the utf8 chars appear */
    unsigned char isConstant = 1;
    unsigned char isGlobal = (*c == '$');

    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    do {
      if (is_special(c) || (*c > 'Z' && !isdigit(*c)))
        isConstant = 0;
      step = utf8_charsize(c);
      ax += step - 1;
      while (step-- > 0) {
        *ptr++ = *c++;
        curs++;
      }
    } while (curs < len && ((isGlobal && !isspace(*c)) || isNotSep(c)));
    *ptr = '\0';
    parser->column -= ax;
    const struct kwtable *kw = rb_reserved_word(buffer, ptr - buffer);
    if (kw) {
      t = kw->id;
      if (t == WHILE || t == UNTIL || t == FOR)
        parser->no_block = 1;
      else if (t == DEF) {
        push_last_comment(parser);
      } else if (t == MODULE) {
        push_last_comment(parser);
      } else if (t == CLASS) {
        /* check for class() method */
        if (parser->dot_seen) {
          push_stack(parser, buffer);
          t = FNAME;
          parser->dot_seen = 0;
        } else {
          push_last_comment(parser);
          parser->class_seen = 1;
        }
      } else if (t == tFILE || t == ENCODING || t == LINE)
        parser->expr_seen = 1;
    } else if ((!strcmp(buffer, "defined")) && (*c == '?')) {
      ++curs;
      t = DEFINED;
    } else if (isGlobal) {
      push_stack(parser, buffer);
      parser->expr_seen = 1;
      t = GLOBAL;
    } else if (isValidVariableIdentifier(buffer)) {
      push_stack(parser, buffer);
      parser->expr_seen = 1;
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
        else if (isFunction(c)) {
          curs++;
          c++;
          t = FNAME;
        } else
          t = BASE;
        if (parser->class_seen)
          parser->class_seen = 0;
        if (t == BASE && *c == '[') {
          ++curs;
          t = SARY;
        }
        if (*c == '(' && (t == BASE || t == FNAME)) {
          ++curs;
          parser->expr_seen = 0;
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
    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
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
      parser->expr_seen = 0;
    } else if (*(c + 1) == '>') {
      ++curs;
      t = tASSOC;
    } else if (multiline_comment(c)) {
      curs += 5;
      c += 5;
      for(; !multiline_end(c); ++curs, ++c)
        if (*c == '\n')
          parser->line++;
      curs += 3;
      t = EOL;
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
        } else {
          tokp.startLine = parser->line;
          tokp.startCol = parser->column;
          t = parse_heredoc(parser, c, &curs, len);
          tokp.endLine = parser->line;
          tokp.endCol = parser->column;
        }
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
    } else {
      tokp.startLine = tokp.endLine = parser->line;
      tokp.startCol = parser->column;
      parser_dot_seen(t, tNOT);
    }
  } else if (*c == '+') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else {
      parser_dot_seen(t, tPLUS);
      if (!parser->expr_seen && t == tPLUS) {
        tokp.startLine = tokp.endLine = parser->line;
        tokp.startCol = parser->column;
        t = tUPLUS;
      }
    }
  } else if (*c == '-') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else if (*(c + 1) == '>') {
      curs++;
      if (*(c + 2) == '(') {
        curs++;
        t = MCALL;
      } else
        t = BASE;
      push_stack(parser, "->");
      tokp.startLine = tokp.endLine = parser->line;
      tokp.startCol = parser->column;
      tokp.endLine = tokp.startCol + 2;
    } else {
      parser_dot_seen(t, tMINUS);
      if (!parser->expr_seen && t == tMINUS) {
        tokp.startLine = tokp.endLine = parser->line;
        tokp.startCol = parser->column;
        t = tUMINUS;
      }
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
    } else {
      parser_dot_seen(t, tMUL);
      parser->auxiliar.startLine = parser->line;
      parser->auxiliar.startCol = parser->column;
    }
  } else if (*c == '/') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else {
      if (parser->expr_seen) {
        parser_dot_seen(t, tDIV);
      } else {
        tokp.startLine = tokp.endLine = parser->line;
        tokp.startCol = parser->column;
        ++c;
        for (; *c != '/'; ++c, ++curs) {
          if (*c == '#' && *(c + 1) == '{')
            push_string_var(parser, &curs, &c);
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
      int inc = curs + 2 - is_simple;
      int ax = 0;
      int step = 0;

      tokp.startLine = tokp.endLine = parser->line;
      tokp.startCol = parser->column;
      if (*(c + 2) != '(' && *(c + 2) != '[' && *(c + 2) != '{' && !is_simple) {
        yyerror(parser, "unterminated string meets end of file");
        t = token_invalid;
        catalan = -1;
      }
      curs = inc;
      c += 3 - is_simple;
      open = *(c - 1);
      close = closing_char(*(c - 1));
      while (catalan != -1) {
        if (*c == '#' && *(c + 1) == '{') {
          push_string_var(parser, &curs, &c);
          ++curs;
          ++c;
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

        /* We read the next char here, at the end of the loop */
        step = utf8_charsize(c);
        ax += step - 1;
        parser->column -= step - 1;
        for (; step-- > 0; c++, curs++);
      }
      /* Don't overwrite token kind if an error occurred */
      if (!catalan) {
        t = kind;
        if (kind == STRING)
          ++curs;
      }
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
      if (!parser->expr_seen || (parser->expr_seen && space_seen))
        t = tCOLON3;
      else
        t = tCOLON2;
    } else if (isNotSep(c + 1)) {
      char * ptr = buffer;
      int step = 0;
      int ax = 0;
      curs--;
      do {
        step = utf8_charsize(c);
        ax += step - 1;
        while (step-- > 0) {
          *ptr++ = *c++;
          curs++;
        }
      } while (curs < len && isNotSep(c));
      *ptr = '\0';
      push_stack(parser, buffer);
      tokp.startLine = tokp.endLine = parser->line;
      parser->column -= ax;
      tokp.startCol = parser->column;
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
    int step = 0;
    int ax = 0;

    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    curs++;
    ++c;
    while (1) {
      step = utf8_charsize(c);
      ax += step - 1;
      if (*c == '\'')
        break;
      for (; step-- > 0; c++, curs++);
      if (*c == '\\' && *(c + 1) == '\'') {
        c += 2;
        curs += 2;
      }
      if (curs >= len) {
        yyerror(parser, "unterminated string meets end of file");
        t = token_invalid;
        break;
      }
    }
    parser->column -= ax;
    parser->expr_seen = 1;
    curs++;
    t = STRING;
  } else if (*c == '"') {
    int step = 0;
    int ax = 0;

    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    curs++;
    ++c;
    while (*c != '"') {
      step = utf8_charsize(c);
      ax += step - 1;
      parser->column -= step - 1;
      for (; step-- > 0; c++, curs++);
      if (*c == '#' && *(c + 1) == '{')
        push_string_var(parser, &curs, &c);
      if (*c == '\\' && *(c + 1) == '"') {
        c += 2;
        curs += 2;
      }
      if (curs >= len) {
        yyerror(parser, "unterminated string meets end of file");
        t = token_invalid;
        break;
      }
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
    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    curs++;
    t = tLBRACE;
  } else if (*c == '}') {
    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    curs++;
    t = tRBRACE;
  } else if (*c == ',') {
    curs++;
    parser->expr_seen = 0;
    t = tCOMMA;
  } else if (*c == '`') {
    int ax = 0;
    int step = 0;

    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    curs++;
    ++c;
    while (1) {
      step = utf8_charsize(c);
      ax += step - 1;
      parser->column -= step - 1;
      for (; step-- > 0; c++, curs++);
      if (*c == '#' && *(c + 1) == '{')
        push_string_var(parser, &curs, &c);
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
    }
    parser->expr_seen = 1;
    curs++;
    t = tBACKTICK;
  } else if (*c == '~') {
    curs++;
    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = tokp.endCol = parser->column;
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

  /* TODO: clean this */
  if (t == COMMENT) {
    t = EOL;
  } else
    parser->column += curs - parser->cursor;

  parser->cursor = curs;
  if (tokp.startLine > 0) {
    if (t != HEREDOC)
      tokp.endCol = parser->column;
    push_pos(parser, tokp);
  }

  if (curs >= len)
    parser->eof_reached = 1;
  if (t == tOP_ASGN || t == tASGN)
    parser->expr_seen = 0;
  if (t == token_whitespace)
    t = EOL;
  return t;
}

/*
 * Standard yylex.
 */
int yylex(void * lval, void * p)
{
  struct parser_t * parser = (struct parser_t *) p;
  (void) lval;

  return parser_yylex(parser);
}

/*
 * Error handling. Take the formmated string s and append the error
 * string to the list of errors p->errors.
 */
void yyerror(struct parser_t * p, const char * s, ...)
{
  if (p->error_index < 1) {
    p->errors[p->error_index].msg = strdup(s);
    p->errors[p->error_index].line = p->line;
    p->errors[p->error_index].col = p->column;
    p->errors[p->error_index].valid = 1;
    p->error_index++;
  }
  p->eof_reached = 1;
}

/*
 * Copy errors to the RubyAst structure.
 */
void copy_error(Ast * ast, int index, struct error_t p)
{
  ast->errors[index].valid = p.valid;
  ast->errors[index].line = p.line;
  ast->errors[index].col = p.col;
  ast->errors[index].msg = p.msg;
}

Ast * rb_compile_file(const char * path, const char * contents)
{
  struct parser_t p;
  Ast * result;

  /* Initialize parser */
  init_parser(&p);
  p.name = strdup(path);
  if (!contents) {
    if (!retrieve_source(&p, path))
      return NULL;
  } else {
    p.blob = strdup(contents);
    p.length = strlen(contents);
  }

  /* Let's parse */
  result = (Ast *) malloc (sizeof(Ast));
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
      copy_error(result, 0, p.errors[0]);
      copy_error(result, 1, p.errors[1]);
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
int rb_debug_file(const char * path)
{
  struct parser_t p;
  int index;

  /* Set up parser */
  init_parser(&p);
  p.name = strdup(path);
  if (!retrieve_source(&p, path))
    return 0;

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
      if (p.ast->l != NULL && p.ast->l->ensure != NULL) {
        if (p.ast->l->cond != NULL) {
          printf("\nCondition: ");
          print_node(p.ast->l->cond);
        }
        printf("\nEnsure: ");
        print_node(p.ast->l->ensure);
      }
      free_ast(p.ast);
      p.ast = NULL;
    }
    if (p.eof_reached) {
      if (p.errors[0].valid)
        print_errors(p.errors);
      break;
    }
  }

  /* Check that all the stacks are empty */
  for (index = 0; index < p.sp; index++)
    printf("\nS: %s", p.stack[index]);
  printf("\n");

  for (index = 0; index < p.pos_size; index++)
    printf("\nP: %i:%i", p.pos_stack[index].startLine, p.pos_stack[index].startCol);
  printf("\n");
  return 1;
}
