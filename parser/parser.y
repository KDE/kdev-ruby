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

#define STACK_SIZE 128
#define BSIZE STACK_SIZE


/* Flags used by the lexer */
struct flags_t {
  unsigned char eof_reached : 1;
  unsigned char expr_seen : 1;
  unsigned char class_seen : 1;
  unsigned char dot_seen : 1;
  unsigned char last_is_paren : 1;
  unsigned char special_arg : 1;
  unsigned char cond_seen : 1;
  unsigned char cmd_arg : 1;
  unsigned char brace_arg : 1;
  unsigned char def_seen : 1;
  unsigned char in_alias : 1;
  unsigned char symbeg : 1;
  unsigned char mcall : 1;
};

#define eof_reached lexer_flags.eof_reached
#define expr_seen lexer_flags.expr_seen
#define class_seen lexer_flags.class_seen
#define dot_seen lexer_flags.dot_seen
#define last_is_paren lexer_flags.last_is_paren
#define special_arg lexer_flags.special_arg
#define cmd_arg lexer_flags.cmd_arg
#define brace_arg lexer_flags.brace_arg
#define def_seen lexer_flags.def_seen
#define cond_seen lexer_flags.cond_seen
#define in_alias lexer_flags.in_alias
#define symbeg lexer_flags.symbeg
#define mcall lexer_flags.mcall

#define PUSH_CLASS() parser->class_seen = 1;
#define POP_CLASS() parser->class_seen = 0;
#define PUSH_COND() parser->cond_seen = 1;
#define POP_COND() parser->cond_seen = 0;


/* Structure representing a position */
struct pos_t {
  int startLine, endLine;
  int startCol, endCol;
  unsigned long long offset;
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
  int name_length;

  /* Flags used by the parser */
  struct flags_t lexer_flags;
  int in_def;
  int paren_nest;
  int lpar_beg;
  int expr_mid;

  /* Errors on the file */
  struct error_t errors[2];
  int error_index;

  /* Stack of names */
  char * stack[2];
  char * aux;
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
static int yylex(void *, void *);
static void yyerror(struct parser_t * p, const char * s, ...);

/* The static functions below deal with stacks. */

#define ALLOC_N(kind, l, r) alloc_node(kind, l, r); fix_pos(parser, yyval.n);
#define ALLOC_C(kind, cond, l, r) alloc_cond(kind, cond, l, r); fix_pos(parser, yyval.n);
#define ALLOC_TERN(kind, cond, l, r) alloc_cond(kind, cond, l, r); fix_ternary(yyval.n);
#define ALLOC_MOD(kind, cond, l, r) ALLOC_C(kind, cond, l, r); copy_range(yyval.n, l, cond);

static void pop_stack(struct parser_t * parser, struct node * n);
#define POP_STACK pop_stack(parser, yyval.n)
static void pop_string(struct parser_t * parser, struct node * n);
#define POP_STR pop_string(parser, yyval.n)
static void push_string(struct parser_t * parser, char * buffer);
static void multiple_string(struct parser_t * parser, struct node * n);
static void push_last_comment(struct parser_t * parser);
static void pop_comment(struct parser_t * parser, struct node *n);

static void fix_pos(struct parser_t * parser, struct node * n);
static void fix_ternary(struct node * n);
struct node * fix_star(struct parser_t * parser);
static void push_pos(struct parser_t * parser, struct pos_t tokp);
static void pop_pos(struct parser_t * parser, struct node * n);
static void pop_start(struct parser_t * parser, struct node * n);
static void copy_last(struct node * head, struct node * tail);
static void copy_wc_range(struct node * res, struct node * h, struct node * t);
static void copy_wc_range_ext(struct node * res, struct node * h, struct node * t);
#define discard_pos() pop_pos(parser, NULL)
#define copy_start(dest, src) ({ dest->startLine = src->startLine; dest->startCol = src->startCol; })
#define copy_end(dest, src) ({ dest->endLine = src->endLine; dest->endCol = src->endCol; })
#define copy_range(dest, src1, src2) ({ copy_start(dest, src1); copy_end(dest, src2); })
#define copy_pos(dest, src) copy_range(dest, src, src);
#define copy_op(op) { parser->aux = strdup(op); parser->name_length = strlen(op);}
#define CONCAT_STRING     parser->auxiliar.endLine = parser->pos_stack[parser->pos_size - 1].endLine; \
                          parser->auxiliar.endCol = parser->pos_stack[parser->pos_size - 1].endCol;
%}

%pure_parser
%parse-param {struct parser_t * parser }
%union { struct node * n; int num; }

/* Tokens */
%token <n> tCLASS tMODULE tDEF tUNDEF tBEGIN tRESCUE tENSURE tEND tIF tUNLESS
%token <n> tTHEN tELSIF tELSE tCASE tWHEN tWHILE tUNTIL tFOR tBREAK tNEXT tREDO
%token <n> tRETRY tIN tDO tDO_COND tDO_BLOCK tRETURN tYIELD tKWAND tKWOR tKWNOT
%token <n> tALIAS tDEFINED upBEGIN upEND tHEREDOC tTRUE tFALSE tNIL tENCODING
%token <n> tFILE tLINE tSELF tSUPER GLOBAL BASE CONST tDO_LAMBDA STRING
%token <n> REGEXP IVAR CVAR NUMERIC FLOAT tNTH_REF tBACKTICK tpEND tSYMBEG tHERE_PAR
%token <n> tAMPER tAREF tASET tASSOC tCOLON2 tCOLON3 tLAMBDA tLAMBEG tLBRACE
%token <n> tLBRACKET tLPAREN tLPAREN_ARG tSTAR EOL tCOMMENT ARRAY tKEY SYMBOL

/* Types */
%type <n> singleton strings string regexp literal numeric cpath rescue_arg
%type <n> top_compstmt top_stmt bodystmt compstmt stmts stmt expr arg primary
%type <n> command command_call method_call if_tail opt_else case_body cases
%type <n> opt_rescue exc_list exc_var opt_ensure args call_args opt_call_args
%type <n> paren_args opt_paren_args super aref_args opt_block_arg block_arg
%type <n> mrhs superclass block_call block_command f_block_optarg f_block_opt
%type <n> const f_arglist f_args f_arg f_arg_item f_optarg f_marg f_marg_list
%type <n> f_margs assoc_list assocs assoc undef_list backref for_var bvar base
%type <n> block_param opt_block_param block_param_def f_opt bv_decls label none
%type <n> lambda f_larglist lambda_body command_args opt_bv_decl lhs do_block
%type <n> mlhs mlhs_head mlhs_basic mlhs_item mlhs_node mlhs_post mlhs_inner
%type <n> fsym variable symbol operation operation2 operation3 other_vars
%type <n> cname fname f_rest_arg f_block_arg opt_f_block_arg f_norm_arg
%type <n> brace_block cmd_brace_block f_bad_arg sym opt_brace_block

/* precedence table */
%nonassoc tLOWEST
%nonassoc tLBRACE_ARG

%nonassoc  modifier_if modifier_unless modifier_while modifier_until
%left  tKWOR tKWAND
%right tKWNOT
%nonassoc tDEFINED
%right '=' tOP_ASGN
%left modifier_rescue
%right '?' ':'
%nonassoc tDOT2 tDOT3
%left  tOR
%left  tAND
%nonassoc  tCMP tEQ tEQQ tNEQ tMATCH tNMATCH
%left  '>' tGEQ '<' tLEQ
%left  '|' '^'
%left  '&'
%left  tLSHIFT tRSHIFT
%left  '+' '-'
%left  '*' '/' '%'
%right tUMINUS_NUM tUMINUS
%right tPOW
%right '!' '~' tUPLUS

%%

top_compstmt: top_stmt
  {
    if (parser->errors[0].valid == 1) {
      free_ast(parser->ast);
      parser->ast = NULL;
    } else
      parser->ast = $1;
    YYACCEPT;
  }
  | term { $$ = 0; YYACCEPT; }
;

top_stmt: none
  | stmt
  | error stmt { $$ = $2; }
;

bodystmt: compstmt opt_rescue opt_else opt_ensure
  {
    $$ = alloc_ensure(token_body, $1, $2, $3, $4);
    copy_wc_range($$, $1, $1);
  }
;

compstmt: stmts opt_terms { $$ = $1; }
;

stmts: none
  | stmt
  | stmts terms stmt { $$ = ($1 == NULL) ? $3 : update_list($1, $3); }
  | error stmt { $$ = $2; }
;

stmt: tALIAS fsym fsym
  {
    $$ = ALLOC_N(token_alias, $2, $3); copy_end($$, $3);
  }
  | tALIAS GLOBAL GLOBAL
  {
    /* Ugly as hell, but it works */
    struct node * l = alloc_node(token_object, NULL, NULL);
    l->flags = 1;
    struct node * r = alloc_node(token_object, NULL, NULL);
    r->flags = 1;
    fix_pos(parser, r);
    fix_pos(parser, l);
    pop_stack(parser, l);
    pop_stack(parser, r);
    $$ = ALLOC_N(token_alias, l, r); copy_end($$, r);
  }
  | tALIAS GLOBAL tNTH_REF
  {
    yyerror(parser, "can't make alias for the number variables");
  }
  | tUNDEF undef_list
  {
    $$ = ALLOC_N(token_undef, NULL, $2); copy_last($$, $2);
  }
  | stmt modifier_if expr
  {
    $$ = ALLOC_MOD(token_if, $3, $1, NULL);
  }
  | stmt modifier_unless expr
  {
    $$ = ALLOC_MOD(token_unless, $3, $1, NULL);
  }
  | stmt modifier_while expr
  {
    $$ = ALLOC_MOD(token_while, $3, $1, NULL);
  }
  | stmt modifier_until expr
  {
    $$ = ALLOC_MOD(token_until, $3, $1, NULL);
  }
  | stmt modifier_rescue stmt
  {
    $$ = ALLOC_MOD(token_rescue, $3, $1, NULL);
  }
  | upBEGIN
  {
    if (parser->in_def)
      yyerror(parser, "BEGIN in method");
  }
  '{' compstmt '}'
  {
    $$ = ALLOC_N(token_up_begin, $4, NULL);
    pop_pos(parser, NULL);
    pop_start(parser, $$);
  }
  | upEND '{' compstmt '}'
  {
    $$ = ALLOC_N(token_up_end, $3, NULL);
    pop_pos(parser, NULL);
    pop_start(parser, $$);
  }
  | lhs '=' command_call { $$ = ALLOC_N(token_assign, $1, $3); }
  | mlhs '=' command_call { $$ = ALLOC_N(token_assign, $1, $3); }
  | variable tOP_ASGN command_call { $$ = ALLOC_N(token_op_assign, $1, $3); }
  | primary '[' opt_call_args rbracket tOP_ASGN command_call
  {
    struct node *aux = alloc_node(token_array_value, $1, $3);
    $$ = alloc_node(token_op_assign, aux, $6);
  }
  | primary '.' base tOP_ASGN command_call
  {
    struct node *aux = alloc_node(token_object, $1, $3);
    $$ = alloc_node(token_op_assign, aux, $5);
  }
  | primary '.' const tOP_ASGN command_call
  {
    struct node *aux = alloc_node(token_object, $1, $3);
    $$ = alloc_node(token_op_assign, aux, $5);
  }
  | primary tCOLON2 const tOP_ASGN command_call
  {
    yyerror(parser, "constant re-assignment");
  }
  | primary tCOLON2 base tOP_ASGN command_call
  {
    struct node *aux = alloc_node(token_object, $1, $3);
    $$ = alloc_node(token_op_assign, aux, $5);
  }
  | backref tOP_ASGN command_call { $$ = ALLOC_N(token_op_assign, $1, $3); }
  | lhs '=' mrhs { $$ = ALLOC_N(token_assign, $1, $3); }
  | mlhs '=' arg { $$ = ALLOC_N(token_assign, $1, $3); }
  | mlhs '=' mrhs { $$ = ALLOC_N(token_assign, $1, $3); }
  | expr
  | tpEND { $$ = ALLOC_N(token__end__, NULL, NULL); }
;

expr: command_call
  | expr tKWAND expr { $$ = ALLOC_N(token_kw_and, $1, $3); discard_pos(); }
  | expr tKWOR expr { $$ = ALLOC_N(token_kw_or, $1, $3);  discard_pos(); }
  | tKWNOT opt_eol expr { $$ = ALLOC_N(token_kw_not, $3, NULL);}
  | '!' command_call { $$ = ALLOC_N(token_not, $2, NULL); }
  | arg
;

command_call: command | block_command
;

block_command: block_call
  | block_call '.' operation2 command_args
  {
    struct node *aux = update_list($1, $3);
    $$ = alloc_node(token_method_call, aux, $4);
  }
  | block_call tCOLON2 operation2 command_args
  {
    struct node *aux = update_list($1, $3);
    $$ = alloc_node(token_method_call, aux, $4);
  }
;

cmd_brace_block: tLBRACE_ARG opt_block_param compstmt '}'
  {
    discard_pos();
    $$ = ALLOC_N(token_block, $3, $2);
    copy_last($$, $3);
  }
;

command: operation command_args       %prec tLOWEST
  {
    $$ = alloc_node(token_method_call, $1, $2);
    copy_wc_range($$, $1, $2);
  }
  | operation command_args cmd_brace_block
  {
    $$ = alloc_cond(token_method_call, $3, $1, $2);
    copy_wc_range($$, $1, $2);
  }
  | primary '.' operation2 command_args     %prec tLOWEST
  {
    struct node *aux = update_list($1, $3);
    $$ = alloc_node(token_method_call, aux, $4);
    ($4 == NULL) ? copy_wc_range($$, $1, $3) : copy_wc_range($$, $1, $4);
  }
  | primary '.' operation2 command_args cmd_brace_block
  {
    struct node *aux = update_list($1, $3);
    $$ = alloc_cond(token_method_call, $5, aux, $4);
    ($4 == NULL) ? copy_wc_range($$, $1, $3) : copy_wc_range($$, $1, $4);
  }
  | primary tCOLON2 operation2 command_args %prec tLOWEST
  {
    struct node *aux = update_list($1, $3);
    $$ = alloc_node(token_method_call, aux, $4);
    ($4 == NULL) ? copy_wc_range($$, $1, $3) : copy_wc_range($$, $1, $4);
  }
  | primary tCOLON2 operation2 command_args cmd_brace_block
  {
    struct node *aux = update_list($1, $3);
    $$ = alloc_cond(token_method_call, $5, aux, $4);
    ($4 == NULL) ? copy_wc_range($$, $1, $3) : copy_wc_range($$, $1, $4);
  }
  | tSUPER call_args
  {
    $$ = ALLOC_N(token_method_call, $2, NULL);
    copy_last($$, $2);
  }
  | tYIELD call_args
  {
    $$ = ALLOC_N(token_yield, $2, NULL);
    copy_last($$, $2);
  }
  | tRETURN call_args
  {
    $$ = ALLOC_N(token_return, $2, NULL);
    copy_last($$, $2);
  }
  | tBREAK call_args
  {
    $$ = ALLOC_N(token_break, $2, NULL);
    copy_last($$, $2);
  }
  | tNEXT call_args
  {
    $$ = ALLOC_N(token_next, $2, NULL);
    copy_last($$, $2);
  }
;

mlhs: mlhs_basic
  | tLPAREN mlhs_inner rparen { $$ = $2; }
;

mlhs_inner: mlhs_basic
  | tLPAREN mlhs_inner rparen { $$ = $2; }
;

mlhs_basic: mlhs_head
  | mlhs_head mlhs_item { $$ = update_list($1, $2); }
  | mlhs_head tSTAR mlhs_node
  {
    $3->flags = 1;
    $$ = update_list($1, $3);
  }
  | mlhs_head tSTAR mlhs_node ',' mlhs_post
  {
    $3->flags = 1;
    $$ = concat_list($1, update_list($3, $5));
  }
  | mlhs_head tSTAR
  {
    $$ = fix_star(parser);
    $$->flags = 2;
    $$ = update_list($1, $$);
  }
  | mlhs_head tSTAR ',' mlhs_post
  {
    $$ = fix_star(parser);
    $$->flags = 2;
    $$ = update_list($1, $$);
    $$ = concat_list($$, $4);
  }
  | tSTAR mlhs_node { $$ = $2; $$->flags = 1; }
  | tSTAR mlhs_node ',' mlhs_post { $$ = update_list($2, $4); $2->flags = 1; }
  | tSTAR { $$ = fix_star(parser); $$->flags = 2; }
  | tSTAR ',' mlhs_post { $$ = fix_star(parser); $$->flags = 2; $$ = update_list($$, $3); }
;

mlhs_item: mlhs_node
  | tLPAREN mlhs_inner rparen
  {
    $$ = alloc_node(token_object, $2, NULL);
    copy_wc_range($$, $2, $2);
  }
;

mlhs_head: mlhs_item ',' { $$ = $1; }
  | mlhs_head mlhs_item ',' { $$ = update_list($1, $2); }
;

mlhs_post: mlhs_item { $$ = $1; }
  | mlhs_post ',' mlhs_item { $$ = update_list($1, $3); }
;

mlhs_node: variable { $$ = $1; }
  | primary '[' opt_call_args rbracket
  {
    $$ = ALLOC_N(token_array_value, $1, $3);
    copy_wc_range_ext($$, $1, $3);
  }
  | primary '.' base
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_wc_range_ext($$, $1, $3);
  }
  | primary tCOLON2 base
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_wc_range_ext($$, $1, $3);
  }
  | primary '.' const
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_wc_range_ext($$, $1, $3);
  }
  | primary tCOLON2 const
  {
    if (parser->in_def)
      yyerror(parser, "dynamic constant assignment");
    $$ = alloc_node(token_object, $1, $3);
    copy_wc_range_ext($$, $1, $3);
  }
  | tCOLON3 const
  {
    if (parser->in_def)
      yyerror(parser, "dynamic constant assignment");
    $$ = $2;
  }
  | backref
;

lhs: variable { $$ = $1; }
  | primary '[' opt_call_args rbracket
  {
    $$ = ALLOC_N(token_array_value, $1, $3);
    copy_wc_range_ext($$, $1, $3);
  }
  | primary '.' base
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_range($$, $1, $3);
  }
  | primary tCOLON2 base
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_range($$, $1, $3);
  }
  | primary '.' const
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_range($$, $1, $3);
  }
  | primary tCOLON2 const
  {
    if (parser->in_def)
      yyerror(parser, "dynamic constant assignment");
    $$ = alloc_node(token_object, $1, $3);
    copy_range($$, $1, $3);
  }
  | tCOLON3 const
  {
    if (parser->in_def)
      yyerror(parser, "dynamic constant assignment");
    $$ = $2;
  }
;

cname: BASE
  {
    yyerror(parser, "class/module name must be CONSTANT");
  }
  | const
;

cpath: tCOLON3 cname { $$ = $2; }
  | cname { $$ = $1; }
  | primary tCOLON2 cname
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_range($$, $1, $3);
  }
;

/* TODO: reswords, push to the stack ?¿ */
fname: base
  | const
  | op
  {
    $$ = alloc_node(token_object, NULL, NULL);
    $$->name = parser->aux;
    $$->startLine = $$->endLine = parser->line;
    $$->endCol = parser->column - 1;
    $$->startCol = $$->endCol - parser->name_length;
    parser->expr_seen = 1;
    parser->dot_seen = 0;
  }
  | reswords { $$ = ALLOC_N(token_object, NULL, NULL); }
;

fsym: fname | symbol
;

undef_list: fsym
  | undef_list ',' fsym { $$ = update_list($1, $3); }
;

op: '|' { copy_op("|"); } | '^' { copy_op("^"); } | '&' { copy_op("&"); }
  | tCMP { copy_op("<=>"); } | tEQ { copy_op("=="); } | tEQQ { copy_op("===");}
  | tMATCH { copy_op("=~"); } | tNMATCH {copy_op("!~");} | '>' { copy_op(">");}
  | tGEQ { copy_op(">="); } | '<' { copy_op("<"); } | tLEQ { copy_op("<="); }
  | tNEQ {copy_op("!=");} | tLSHIFT {copy_op("<<");} | tRSHIFT {copy_op(">>");}
  | '+' { copy_op("+"); } | '-' { copy_op("-"); } | '*' { copy_op("*"); }
  | tSTAR { copy_op("*"); } | '/' { copy_op("/"); } | '%' { copy_op("%"); }
  | tPOW { copy_op("**"); } | tAREF { copy_op("[]"); } | '`' { copy_op("`");}
  | tUPLUS { copy_op("+"); discard_pos(); } | tASET { copy_op("[]="); }
  | tUMINUS { copy_op("-");discard_pos(); }
  | '!' { copy_op("!"); discard_pos(); } | '~' { copy_op("~"); discard_pos(); }
;

reswords: tLINE | tFILE | tENCODING | upBEGIN | upEND | tALIAS | tKWAND
  | tBEGIN | tBREAK | tCASE | tCLASS | tDEF | tDEFINED | tDO | tELSE | tELSIF
  | tEND | tENSURE | tFALSE | tFOR | tIN | tMODULE | tNEXT | tNIL | tKWNOT
  | tKWOR | tREDO | tRESCUE | tRETRY | tRETURN | tSELF | tSUPER | tTHEN | tTRUE
  | tUNDEF | tWHEN | tYIELD | tIF | tUNLESS | tWHILE | tUNTIL
;

arg: lhs '=' arg { $$ = ALLOC_N(token_assign, $1, $3); }
  | lhs '=' arg modifier_rescue arg
  {
    struct node *aux = ALLOC_MOD(token_rescue, $5, $3, NULL);
    $$ = ALLOC_N(token_assign, $1, aux);
  }
  | variable tOP_ASGN arg { $$ = ALLOC_N(token_op_assign, $1, $3); }
  | variable tOP_ASGN arg modifier_rescue arg
  {
    struct node *aux = ALLOC_MOD(token_rescue, $5, $3, NULL);
    $$ = ALLOC_N(token_op_assign, $1, aux);
  }
  | primary '[' opt_call_args rbracket tOP_ASGN arg
  {
    discard_pos();
    struct node *aux = alloc_node(token_array_value, $1, $3);
    copy_wc_range_ext(aux, $1, $3);
    $$ = ALLOC_N(token_op_assign, aux, $6);
  }
  | primary '.' base tOP_ASGN arg
  {
    struct node *aux  = alloc_node(token_object, $1, $3);
    copy_wc_range_ext(aux, $1, $3);
    $$ = ALLOC_N(token_op_assign, aux, $5);
  }
  | primary '.' const tOP_ASGN arg
  {
    struct node *aux  = alloc_node(token_object, $1, $3);
    copy_wc_range_ext(aux, $1, $3);
    $$ = ALLOC_N(token_op_assign, aux, $5);
  }
  | primary tCOLON2 base tOP_ASGN arg
  {
    struct node *aux  = alloc_node(token_object, $1, $3);
    copy_wc_range_ext(aux, $1, $3);
    $$ = ALLOC_N(token_op_assign, aux, $5);
  }
  | primary tCOLON2 const tOP_ASGN arg
  {
    yyerror(parser, "constant re-assignment");
  }
  | tCOLON3 const tOP_ASGN arg
  {
    yyerror(parser, "constant re-assignment");
  }
  | backref tOP_ASGN arg { $$ = ALLOC_N(token_assign, $1, $3); }
  | arg tDOT2 arg { $$ = ALLOC_N(token_dot2, $1, $3); }
  | arg tDOT3 arg { $$ = ALLOC_N(token_dot3, $1, $3);}
  | arg '+' arg { $$ = ALLOC_N(token_plus, $1, $3); }
  | arg '-' arg { $$ = ALLOC_N(token_minus, $1, $3);}
  | arg '*' arg { $$ = ALLOC_N(token_mul, $1, $3);}
  | arg '/' arg { $$ = ALLOC_N(token_div, $1, $3);}
  | arg '%' arg { $$ = ALLOC_N(token_mod, $1, $3);}
  | arg tPOW arg { $$ = ALLOC_N(token_pow, $1, $3);}
  | tUPLUS arg  { $$ = ALLOC_N(token_unary_plus, $2, NULL);  }
  | tUMINUS arg { $$ = ALLOC_N(token_unary_minus, $2, NULL); }
  | arg '|' arg { $$ = ALLOC_N(token_bit_or, $1, $3);  }
  | arg '^' arg { $$ = ALLOC_N(token_bit_xor, $1, $3);  }
  | arg '&' arg { $$ = ALLOC_N(token_bit_and, $1, $3);  }
  | arg tCMP arg  { $$ = ALLOC_N(token_cmp, $1, $3);  }
  | arg '>' arg  { $$ = ALLOC_N(token_greater, $1, $3);  }
  | arg tGEQ arg  { $$ = ALLOC_N(token_geq, $1, $3);  }
  | arg '<' arg  { $$ = ALLOC_N(token_lesser, $1, $3);  }
  | arg tLEQ arg  { $$ = ALLOC_N(token_leq, $1, $3);  }
  | arg tEQ arg  { $$ = ALLOC_N(token_eq, $1, $3);  }
  | arg tEQQ arg  { $$ = ALLOC_N(token_eqq, $1, $3);  }
  | arg tNEQ arg  { $$ = ALLOC_N(token_neq, $1, $3);  }
  | arg tMATCH arg  { $$ = ALLOC_N(token_match, $1, $3); }
  | arg tNMATCH arg  { $$ = ALLOC_N(token_nmatch, $1, $3);  }
  | '!' arg  { $$ = ALLOC_N(token_not, $2, NULL);  }
  | '~' arg { $$ = ALLOC_N(token_neg, $2, NULL);  }
  | arg tLSHIFT arg { $$ = ALLOC_N(token_lshift, $1, $3); }
  | arg tRSHIFT arg { $$ = ALLOC_N(token_rshift, $1, $3); }
  | arg tAND arg { $$ = ALLOC_N(token_and, $1, $3); }
  | arg tOR arg { $$ = ALLOC_N(token_or, $1, $3); }
  | tDEFINED opt_eol arg
  {
    $$ = ALLOC_N(token_defined, $3, NULL);
    copy_end($$, $3);
  }
  | arg '?' arg opt_eol ':' arg { $$ = ALLOC_TERN(token_ternary, $1, $3, $6); }
  | primary
;

aref_args: none
  | args trailer { $$ = $1; }
  | args ',' assocs trailer { $$ = update_list($1, $3); }
  | assocs trailer { $$ = $1; }
;

paren_args: '(' opt_call_args rparen { $$ = $2; }
  | '(' tHERE_PAR { $$ = ALLOC_N(token_heredoc, NULL, NULL);   }
;

opt_paren_args : none | paren_args
;

opt_call_args: none | call_args
;

call_args: command
  | args opt_block_arg { $$ = update_list($1, $2); }
  | assocs opt_block_arg { $$ = update_list($1, $2); }
  | args ',' assocs opt_block_arg
  {
    struct node *n = update_list($3, $4);
    $$ = concat_list($1, n);
  }
  | block_arg
;

command_args: { parser->cmd_arg = 1; } call_args { $$ = $2; }
;

block_arg: tAMPER arg { $$ = $2; }
;

opt_block_arg: ',' block_arg { $$ = $2; }
  | ',' { $$ = 0; }
  | none
;

args: arg
  | tSTAR arg { $$ = $2; }
  | args ',' arg { $$ = update_list($1, $3); }
  | args ',' tSTAR arg { $$ = update_list($1, $4); }
;

mrhs: args ',' arg { $$ = update_list($1, $3); }
  | args ',' tSTAR arg { $$ = update_list($1, $4); }
  | tSTAR arg { $$ = $2; }
;

primary: literal
  | strings
  | regexp
  | variable
  | backref
  | tBEGIN bodystmt tEND
  {
    $$ = ALLOC_N(token_begin, $2, NULL);
    pop_start(parser, $$);
  }
  | tLPAREN_ARG expr rparen { $$ = $2; }
  | tLPAREN compstmt ')' { $$ = $2; }
  | primary tCOLON2 const
  {
    struct node *aux = update_list($1, $3);
    $$ = alloc_node(token_method_call, aux, NULL);
    copy_range($$, $1, $3);
  }
  | tCOLON3 const { $$ = $2; }
  | ARRAY { $$ = ALLOC_N(token_array, NULL, NULL); }
  | tLBRACKET aref_args ']'
  {
    $$ = ALLOC_N(token_array, $2, NULL);
    if ($2 != NULL && $2->last != NULL) {
      if ($2->last->endLine >= parser->last_pos->endLine)
        copy_end($$, $2->last);
      else
        copy_end($$, parser->last_pos);
    }
  }
  | tLBRACE assoc_list '}'
  {
    pop_pos(parser, parser->last_pos);
    $$ = ALLOC_N(token_hash, $2, NULL);
    if ($2 != NULL && $2->last != NULL) {
      if ($2->last->endLine >= parser->last_pos->endLine) {
        copy_end($$, $2->last);
      } else {
        copy_end($$, parser->last_pos);
      }
    }
  }
  | tRETURN { $$ = ALLOC_N(token_return, NULL, NULL); }
  | tYIELD '(' call_args rparen
  {
    $$ = ALLOC_N(token_yield, $3, NULL);
    copy_last($$, $3);
  }
  | tYIELD '(' rparen { $$ = ALLOC_N(token_yield, NULL, NULL); }
  | tYIELD { $$ = ALLOC_N(token_yield, NULL, NULL); }
  | tDEFINED opt_eol '(' expr rparen
  {
    $$ = ALLOC_N(token_defined, $4, NULL);
    copy_end($$, $4);
  }
  | tKWNOT '(' expr rparen { $$ = ALLOC_N(token_kw_not, $3, NULL);}
  | tKWNOT '(' rparen { $$ = ALLOC_N(token_kw_not, NULL, NULL);}
  | operation brace_block
  {
    $$ = alloc_cond(token_method_call, $2, $1, NULL);
    copy_range($$, $1, $2);
  }
  | method_call opt_brace_block { $$ = $1; $$->cond = $2; }
  | tLAMBDA lambda
  {
    $$ = alloc_cond(token_method_call, $2, NULL, NULL);
    pop_start(parser, $$);
    copy_end($$, $2);
  }
  | tIF expr then compstmt if_tail tEND
  {
    $$ = ALLOC_C(token_if, $2, $4, $5);
    pop_start(parser, $$);
  }
  | tUNLESS expr then compstmt opt_else tEND
  {
    $$ = ALLOC_C(token_unless, $2, $4, $5);
    pop_start(parser, $$);
  }
  | tWHILE { PUSH_COND(); } expr do { POP_COND(); } compstmt tEND
  {
    $$ = ALLOC_C(token_while, $3, $6, NULL);
    pop_start(parser, $$);
  }
  | tUNTIL { PUSH_COND(); } expr do { POP_COND(); } compstmt tEND
  {
    $$ = ALLOC_C(token_while, $3, $6, NULL);
    pop_start(parser, $$);
  }
  | tCASE expr opt_terms case_body tEND
  {
    $$ = ALLOC_C(token_case, $2, $4, NULL);
    pop_start(parser, $$);
  }
  | tCASE opt_terms case_body tEND
  {
    $$ = ALLOC_N(token_case, $3, NULL);
    pop_start(parser, $$);
  }
  | tFOR for_var tIN { PUSH_COND(); } expr do { POP_COND(); } compstmt tEND
  {
    $$ = ALLOC_C(token_for, $5, $8, $2);
    pop_pos(parser, NULL);
    pop_start(parser, $$);
  }
  | tCLASS cpath superclass
  {
    if (parser->in_def)
      yyerror(parser, "class definition in method body");
  }
  bodystmt tEND
  {
    $$ = ALLOC_C(token_class, $3, $5, $2);
    pop_comment(parser, $$);
    pop_start(parser, $$);
  }
  | tCLASS { PUSH_CLASS(); } opt_terms tLSHIFT { POP_CLASS(); } expr
    term bodystmt tEND
  {
    $$ = ALLOC_N(token_singleton_class, $8, $6);
    pop_comment(parser, $$);
    pop_start(parser, $$);
  }
  | tMODULE cpath
  {
    if (parser->in_def)
      yyerror(parser, "module definition in method body");
  }
  bodystmt tEND
  {
    $$ = ALLOC_N(token_module, $4, $2);
    pop_comment(parser, $$);
    pop_start(parser, $$);
  }
  | tDEF fname
  {
    parser->def_seen = 0;
    parser->in_def++;
  }
  f_arglist bodystmt tEND
  {
    parser->in_def--;
    $$ = ALLOC_C(token_function, $2, $5, $4);
    pop_comment(parser, $$);
    if (parser->pos_size > 0)
      pop_start(parser, $$);
  }
  | tDEF singleton dot_or_colon fname
  {
    parser->def_seen = 0;
    parser->in_def++;
  }
  f_arglist bodystmt tEND
  {
    $$ = alloc_node(token_object, $2, $4);
    copy_range($$, $2, $4);
    $$ = ALLOC_C(token_function, $$, $7, $6);
    $$->flags = 1; /* Class method */
    pop_comment(parser, $$);
    pop_start(parser, $$);
    parser->in_def--;
  }
  | tBREAK { $$ = ALLOC_N(token_break, NULL, NULL);   }
  | tNEXT { $$ = ALLOC_N(token_next, NULL, NULL);    }
  | tREDO { $$ = ALLOC_N(token_redo, NULL, NULL);    }
  | tRETRY { $$ = ALLOC_N(token_retry, NULL, NULL);   }
;

then: term
  | tTHEN { discard_pos(); }
  | term tTHEN { discard_pos(); }
;

do: term
  | tDO_COND { discard_pos(); }
;

if_tail: opt_else
  | tELSIF expr then compstmt if_tail
  {
    $$ = ALLOC_C(token_if, $2, $4, $5);
    struct pos_t tp = { $$->startLine, $$->endLine, $$->startCol, $$->endCol, 0 };

    pop_pos(parser, $$);
    push_pos(parser, tp);
    if ($4 != NULL)
      copy_end($$, $4);
  }
;

opt_else: none
  | tELSE compstmt
  {
    $$ = ALLOC_N(token_if, $2, NULL);
    struct pos_t tp = { $$->startLine, $$->endLine, $$->startCol, $$->endCol, 0 };

    pop_pos(parser, $$);
    push_pos(parser, tp);
    if ($2 != NULL)
      copy_end($$, $2);
  }
;

for_var: lhs | mlhs
;

f_marg: f_norm_arg { $$ = $1; }
  | tLPAREN f_margs rparen { $$ = $2; }
;

f_marg_list: f_marg
  | f_marg_list ',' f_marg { $$ = update_list($1, $3); }
;

f_margs: f_marg_list { $$ = $1; }
  | f_marg_list ',' tSTAR f_norm_arg { $$ = update_list($1, $4); }
  | f_marg_list ',' tSTAR f_norm_arg ',' f_marg_list
  {
    $$ = concat_list($1, update_list($4, $6));
  }
  | f_marg_list ',' tSTAR
  {
    struct node *n = alloc_node(token_object, NULL, NULL);
    $$ = update_list($1, n);
  }
  | f_marg_list ',' tSTAR ',' f_marg_list
  {
    struct node *n = alloc_node(token_object, NULL, NULL);
    $$ = concat_list($1, update_list(n, $5));
  }
  | tSTAR f_norm_arg { $$ = $2; }
  | tSTAR f_norm_arg ',' f_marg_list { $$ = update_list($2, $4); }
  | tSTAR { $$ = alloc_node(token_object, NULL, NULL); }
  | tSTAR ',' f_marg_list
  {
    struct node *n = alloc_node(token_object, NULL, NULL);
    $$ = update_list(n, $3);
  }
;

block_param: f_arg ',' f_block_optarg ',' f_rest_arg opt_f_block_arg
  {
    $$ = concat_list($1, concat_list($3, update_list($5, $6)));
  }
  | f_arg ',' f_block_optarg ',' f_rest_arg ',' f_arg opt_f_block_arg
  {
    $$ = concat_list($1, concat_list($3, create_list($5, update_list($7, $8))));
  }
  | f_arg ',' f_block_optarg opt_f_block_arg
  {
    $$ = concat_list($1, update_list($3, $4));
  }
  | f_arg ',' f_block_optarg ',' f_arg opt_f_block_arg
  {
    $$ = concat_list($1, concat_list($3, update_list($5, $6)));
  }
  | f_arg ',' f_rest_arg opt_f_block_arg
  {
    $$ = update_list($1, update_list($3, $4));
  }
  | f_arg ',' { $$ = $1; }
  | f_arg ',' f_rest_arg ',' f_arg opt_f_block_arg
  {
    $$ = concat_list($1, concat_list($3, update_list($5, $6)));
  }
  | f_arg opt_f_block_arg { $$ = update_list($1, $2); }
  | f_block_optarg ',' f_rest_arg opt_f_block_arg
  {
    $$ = concat_list($1, update_list($3, $4));
  }
  | f_block_optarg ',' f_rest_arg ',' f_arg opt_f_block_arg
  {
    $$ = concat_list($1, create_list($3, update_list($5, $6)));
  }
  | f_block_optarg opt_f_block_arg { $$ = update_list($1, $2); }
  | f_block_optarg ',' f_arg opt_f_block_arg
  {
    $$ = concat_list($1, update_list($3, $4));
  }
  | f_rest_arg opt_f_block_arg { $$ = update_list($1, $2); }
  | f_rest_arg ',' f_arg opt_f_block_arg
  {
    $$ = create_list($1, update_list($3, $4));
  }
  | f_block_arg
;

opt_block_param : none
  | block_param_def
;

block_param_def : '|' opt_bv_decl '|' { $$ = $2; }
  | tOR { $$ = 0; }
  | '|' block_param opt_bv_decl '|' { $$ = update_list($2, $3); }
;

opt_bv_decl: none
  | ';' bv_decls { $$ = $2; }
;

bv_decls: bvar
  | bv_decls ',' bvar { $$ = update_list($1, $3); }
;

bvar: base
  | f_bad_arg { $$ = 0; }
;

lambda:
  {
    $<num>$ = parser->lpar_beg;
    parser->lpar_beg = ++parser->paren_nest;
  }
  f_larglist lambda_body
  {
    parser->lpar_beg = $<num>1;
    discard_pos();
    $$ = ALLOC_N(token_block, $3, $2);
    if ($3 != NULL)
      copy_last($$, $3);
    parser->last_pos = NULL;
  }
;

f_larglist: '(' f_args opt_bv_decl rparen { $$ = update_list($2, $3); }
  | f_args
;

lambda_body: tLAMBEG compstmt '}' { $$ = $2; }
  | tDO_LAMBDA compstmt tEND { $$ = $2; }
;

do_block: tDO_BLOCK opt_block_param compstmt tEND
  {
    discard_pos();
    $$ = ALLOC_N(token_block, $3, $2);
    if ($3 != NULL)
      copy_last($$, $3);
    else if ($2 != NULL)
      copy_last($$, $2);
  }
;

block_call: command do_block    { $1->cond = $2; $$ = $1; }
  | block_call '.' operation2 opt_paren_args
  {
    struct node *aux = update_list($1, $3);
    $$ = update_list(aux, $4);
  }
  | block_call tCOLON2 operation2 opt_paren_args
  {
    struct node *aux = update_list($1, $3);
    $$ = update_list(aux, $4);
  }
;

method_call: operation paren_args
  {
    $$ = alloc_node(token_method_call, $1, $2);
    copy_wc_range($$, $1, $2);
  }
  | primary '.' operation2 opt_paren_args
  {
    struct node *aux = update_list($1, $3);
    $$ = alloc_node(token_method_call, aux, $4);
    ($4 == NULL) ? copy_wc_range($$, $1, $3) : copy_wc_range($$, $1, $4);
  }
  | primary tCOLON2 operation2 paren_args
  {
    struct node *aux = update_list($1, $3);
    $$ = alloc_node(token_method_call, aux, $4);
    ($4 == NULL) ? copy_range($$, $1, $3) : copy_range($$, $1, $4);
  }
  | primary tCOLON2 operation3
  {
    struct node *aux = update_list($1, $3);
    $$ = alloc_node(token_method_call, aux, NULL);
    copy_range($$, $1, $3);
  }
  | primary '.' paren_args
  {
    $$ = alloc_node(token_method_call, $1, $3);
  }
  | primary tCOLON2 paren_args
  {
    $$ = alloc_node(token_method_call, $1, $3);
  }
  | super paren_args { $$ = update_list($1, $2); }
  | super
  | primary '[' opt_call_args rbracket
  {
    $$ = ALLOC_N(token_array_value, $1, $3);
    copy_wc_range_ext($$, $1, $3);
  }
;

opt_brace_block: none
  | brace_block
;

brace_block: '{' opt_block_param compstmt '}'
  {
    discard_pos();
    $$ = ALLOC_N(token_block, $3, $2);
    if ($3 != NULL)
      copy_last($$, $3);
    else if ($2 != NULL)
      copy_last($$, $2);
  }
  | tDO opt_block_param compstmt tEND
  {
    discard_pos();
    $$ = ALLOC_N(token_block, $3, $2);
    if ($3 != NULL)
      copy_last($$, $3);
    else if ($2 != NULL)
      copy_last($$, $2);
  }
;

case_body: tWHEN { parser->expr_seen = 0; } args then compstmt cases
  {
    /* The following statements fixes some issues around positions. */
    $$ = ALLOC_N(token_object, NULL, NULL);
    struct pos_t t = {$$->startLine, $$->endLine, $$->startCol, $$->endCol, 0};
    $$ = ALLOC_C(token_when, $3, $5, $6);
    push_pos(parser, t);
    if ($5 != NULL)
      copy_last($$, $5);
  }
;

cases: opt_else | case_body
;

opt_rescue: tRESCUE rescue_arg then compstmt opt_rescue
  {
     $$ = ALLOC_N(token_rescue, $2, $4);
    struct pos_t tp = { $$->startLine, $$->endLine, $$->startCol, $$->endCol, 0 };

    pop_pos(parser, $$);
    push_pos(parser, tp);
    if ($4 != NULL)
      copy_last($$, $4);
    else if ($2 != NULL)
      copy_end($$, $2);
  }
  | none
;

rescue_arg: exc_list exc_var
  {
    if ($2 != NULL) {
      $$ = alloc_node(token_rescue_arg, $1, $2);
      ($1 != NULL) ? copy_range($$, $1, $2) : copy_range($$, $2, $2);
    } else if ($1 != NULL) {
      $$ = alloc_node(token_rescue_arg, $1, $2);
      copy_range($$, $1, $1);
    } else
      $$ = 0;
  }
;

exc_list: arg | mrhs | none
;

exc_var: none | tASSOC lhs { $$ = $2; }
;

opt_ensure: none
  | tENSURE compstmt
  {
    $$ = ALLOC_N(token_ensure, $2, NULL);
    struct pos_t tp = { $$->startLine, $$->endLine, $$->startCol, $$->endCol, 0 };

    pop_pos(parser, $$);
    push_pos(parser, tp);
    if ($2 != NULL)
      copy_end($$, $2);
  }
;

literal: numeric | symbol
;

strings: string
  {
    $$ = ALLOC_N(token_string, NULL, NULL); POP_STR;
    multiple_string(parser, $$);
  }
  | tHEREDOC { $$ = ALLOC_N(token_heredoc, NULL, NULL);   }
;

string: STRING
  | tBACKTICK
  | string STRING { CONCAT_STRING; pop_pos(parser, NULL); }
;

regexp: REGEXP { $$ = ALLOC_N(token_regexp, NULL, NULL); POP_STR; }
;

symbol: tSYMBEG sym
  {
    $$ = ALLOC_N(token_symbol, NULL, NULL);
    copy_end($$, $2);
    if ($2->name != NULL)
      $$->name = strdup($2->name);
    free_ast($2);
  }
;

sym: fname
  | strings
  | IVAR { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
  | GLOBAL { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags=1; POP_STACK; }
  | CVAR { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
;

numeric: NUMERIC { $$ = ALLOC_N(token_numeric, NULL, NULL); }
  | FLOAT { $$ = ALLOC_N(token_numeric, NULL, NULL); $$->flags = 1; }
;

variable: base
  | IVAR   { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
  | GLOBAL { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags=1; POP_STACK; }
  | const
  | CVAR   { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
  | other_vars
;

other_vars: tNIL { $$ = ALLOC_N(token_nil, NULL, NULL); }
  | tSELF  { $$ = ALLOC_N(token_self, NULL, NULL); }
  | tTRUE  { $$ = ALLOC_N(token_true, NULL, NULL); }
  | tFALSE { $$ = ALLOC_N(token_false, NULL, NULL); }
  | tFILE  { $$ = ALLOC_N(token_file, NULL, NULL); }
  | tLINE  { $$ = ALLOC_N(token_line, NULL, NULL); }
  | tENCODING { $$ = ALLOC_N(token_encoding, NULL, NULL); }
;

backref: tNTH_REF { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
;

superclass: term { $$ = 0; }
  | '<' { parser->expr_seen = 0; } expr term { $$ = $3; }
  | error term { yyerrok; $$ = 0; }
;

f_arglist: '(' f_args rparen { $$ = $2; }
  | f_args term { $$ = $1; }
;

f_args: f_arg ',' f_optarg ',' f_rest_arg opt_f_block_arg
  {
    $$ = concat_list($1, concat_list($3, update_list($5, $6)));
  }
  | f_arg ',' f_optarg ',' f_rest_arg ',' f_arg opt_f_block_arg
  {
    $$ = concat_list($1, concat_list($3, create_list($5, update_list($7, $8))));
  }
  | f_arg ',' f_optarg opt_f_block_arg
  {
    $$ = concat_list($1, update_list($3, $4));
  }
  | f_arg ',' f_optarg ',' f_arg opt_f_block_arg
  {
    $$ = concat_list($1, concat_list($3, update_list($5, $6)));
  }
  | f_arg ',' f_rest_arg opt_f_block_arg
  {
    $$ = concat_list($1, update_list($3, $4));
  }
  | f_arg ',' f_rest_arg ',' f_arg opt_f_block_arg
  {
    $$ = concat_list($1, concat_list($3, update_list($5, $6)));
  }
  | f_arg opt_f_block_arg { $$ = update_list($1, $2); }
  | f_optarg ',' f_rest_arg opt_f_block_arg
  {
    $$ = concat_list($1, update_list($3, $4));
  }
  | f_optarg ',' f_rest_arg ',' f_arg opt_f_block_arg
  {
    $$ = concat_list($1, create_list($3, update_list($5, $6)));
  }
  | f_optarg opt_f_block_arg { $$ = update_list($1, $2); }
  | f_optarg ',' f_arg opt_f_block_arg
  {
    $$ = concat_list($1, update_list($3, $4));
  }
  | f_rest_arg opt_f_block_arg { $$ = update_list($1, $2); }
  | f_rest_arg ',' f_arg opt_f_block_arg
  {
    $$ = create_list($1, update_list($3, $4));
  }
  | f_block_arg
  | none
;

f_bad_arg: CONST { yyerror(parser, "formal argument cannot be a constant"); }
  | IVAR { yyerror(parser, "formal argument cannot be an instance variable"); }
  | GLOBAL { yyerror(parser, "formal argument cannot be a global variable"); }
  | CVAR { yyerror(parser, "formal argument cannot be a class variable"); }
;

f_norm_arg: f_bad_arg | base
;

f_arg_item: f_norm_arg { $$ = $1; }
  | tLPAREN f_margs rparen { $$ = $2; }
;

f_arg: f_arg_item
  | f_arg ',' f_arg_item { $$ = update_list($1, $3); }
;

f_opt: base '=' arg { $$ = ALLOC_N(token_assign, $1, $3); }
;

f_block_opt: base '=' primary { $$ = ALLOC_N(token_assign, $1, $3); }
;

f_block_optarg  : f_block_opt { $$ = $1; }
  | f_block_optarg ',' f_block_opt { $$ = update_list($1, $3); }
;

f_optarg: f_opt
  | f_optarg ',' f_opt { $$ = update_list($1, $3); }
;

restarg_mark: '*' | tSTAR
;

f_rest_arg: restarg_mark base { $$ = $2; $$->flags = 1; }
  | restarg_mark { $$ = alloc_node(token_object, NULL, NULL); $$->flags = 1; }
;

blkarg_mark: '&' | tAMPER
;

f_block_arg: blkarg_mark base { $$ = $2; $$->flags = 2; }
;

opt_f_block_arg : ',' f_block_arg { $$ = $2; }
  | none
;

singleton: variable { $$ = $1; }
  | '(' expr rparen
  {
    if ($2 == 0)
      yyerror(parser, "can't define singleton method for ().");
    else {
      switch ($2->kind) {
        case token_string:
        case token_regexp:
        case token_numeric:
        case token_symbol:
        case token_array:
          yyerror(parser, "can't define singleton method for literals");
      }
    }
    $$ = $2;
  }
;

const: CONST { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
;

base: BASE { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
;

assoc_list: none
  | assocs trailer { $$ = $1; }
;

assocs: assoc
  | assocs ',' assoc { $$ = update_list($1, $3); }
;

assoc: arg tASSOC arg
  {
    $$ = alloc_node(token_object, $1, $3);
    copy_range($$, $1, $3);
  }
  | label arg
  {
    $$ = alloc_node(token_object, $1, $2);
    copy_range($$, $1, $2);
  }
;

operation: base
  | const
;

operation2: base
  | const
  | op { $$ = alloc_node(token_object, NULL, NULL); $$->name = parser->aux; }
;

operation3: base
  | op { $$ = alloc_node(token_object, NULL, NULL); $$->name = parser->aux; }
;

label: tKEY { $$ = ALLOC_N(token_symbol, NULL, NULL); POP_STACK; }
;

super: tSUPER { $$ = ALLOC_N(token_method_call, NULL, NULL); }
;

dot_or_colon: '.' | tCOLON2
;

opt_terms: /* none */ | terms
;

opt_eol: /* none */ | EOL
;

rparen: opt_eol ')'
;

rbracket: opt_eol ']'
;

trailer: opt_eol | ','
;

term: ';' {yyerrok;} | EOL
;

terms: term | terms ';' {yyerrok;}
;

none : /* none */ { $$ = 0; }
;

%%
#undef parser
#undef yylex

#include <ctype.h>
#include "hash.c"


/* Let's define some useful macros :D */

#define to_upper(a) (a & ~32)
#define is_upper(c) (c >= 'A' && c <= 'Z')
#define multiline_comment(c) (*(c+1) == 'b' && *(c+2) == 'e' && *(c+3) == 'g' \
                              && *(c+4) == 'i' && *(c+5) == 'n')
#define multiline_end(c) (*c == '=' && *(c+1) == 'e' && *(c+2) == 'n' \
                          && *(c+3) == 'd')
#define is_simple(c) (c == '(' || c == '{' || c == '[' || c == '|' || c == '<' || c == '/' || c == '$')
#define is_shortcut(c) (to_upper(c) == 'W' || c == 'r' || to_upper(c) == 'Q' \
                      || c == 'x' || is_simple(c))
#define not_sep(c) (is_valid_identifier(c) || is_utf8_digit(c) \
                    || *c == '_' || *c == '$' || *c == '@')
#define is_special_method(buffer) ((strlen(buffer) > 4) && buffer[0] == '_' && \
                                buffer[1] == '_' && buffer[strlen(buffer) - 2] == '_' && \
                                buffer[strlen(buffer) - 1] == '_')
#define cannot_be_heredoc (parser->class_seen || parser->expr_seen || parser->dot_seen)


static void init_parser(struct parser_t * p)
{
  p->ast = NULL;
  p->blob = NULL;
  p->cursor = 0;
  p->eof_reached = 0;
  p->expr_seen = 0;
  p->class_seen = 0;
  p->dot_seen = 0;
  p->last_is_paren = 0;
  p->cond_seen = 0;
  p->special_arg = 0;
  p->cmd_arg = 0;
  p->brace_arg = 0;
  p->in_def = 0;
  p->in_alias = 0;
  p->symbeg = 0;
  p->mcall = 0;
  p->expr_mid = 0;
  p->lpar_beg = 0;
  p->paren_nest = 0;
  p->error_index = 0;
  p->def_seen = 0;
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
  p->last_comment.line = -1;
  p->comment_index = 0;
}

static void free_parser(struct parser_t * p)
{
  int index;

  for (index = 0; index < p->sp; index++)
    free(p->stack[index]);
  if (p->pos_stack != NULL)
    free(p->pos_stack);
  free(p->blob);
  free(p->name);
  if (p->last_comment.comment != NULL)
    free(p->last_comment.comment);
}

/* Read the file's source code and allocate it for further inspection. */
static int retrieve_source(struct parser_t * p, const char * path)
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

/*
 * Some macros to make easier the UTF-8 support
 */
#define is_utf(c) ((c & 0xC0) != 0x80)
#define is_special(c) (utf8_charsize(c) > 1)
#define is_identchar(c) (is_utf8_alnum(c) || *c == '_')

/*
 * This function is really simple. It steps over a char of
 * the string s, that is encoded in UTF-8. The result varies on the
 * number of bytes that encodes a single character following the UTF-8
 * rules. Therefore, this function will return 1 if the character
 * is in plain-ASCII, and greater than 1 otherwise.
 */
static int utf8_charsize(const char * s)
{
  int size = 0;
  int i = 0;

  do {
    i++;
    size++;
  } while (s[i] && !is_utf(s[i]));
  return size;
}

static int is_utf8_alpha(const char * str)
{
  return is_special(str) ? 1 : isalpha(*str);
}

static int is_utf8_alnum(const char * str)
{
  return is_special(str) ? 1 : isalnum(*str);
}

static int is_utf8_graph(const char * str)
{
  return is_special(str) ? 1 : isgraph(*str);
}

static int is_utf8_digit(const char * str)
{
  return is_special(str) ? 0 : isdigit(*str);
}

static int is_valid_identifier(const char * c)
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

static int push_string_var(struct parser_t * p, int * curs, char ** ch, int oax)
{
  char *c = *ch;
  int diff = *curs - p->cursor - oax + 2;
  struct pos_t tp = { p->line, p->line, p->column + diff, -1, 0 };
  int possible_error = *curs + 1;
  char buffer[BSIZE];
  char * ptr = buffer;
  int step = 0; /* How many bytes the actual utf8 character has */
  int ax = 0; /* Used to properly update the column when utf8 chars appear */
  int i = 0;

  c += 2;
  *curs += 2;
  while (*c != '}') {
    step = utf8_charsize(c);
    ax += step - 1;
    i++;
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
  tp.endCol = tp.startCol + i;
  push_pos(p, tp);
  push_string(p, buffer);
  return i;
}

static int parse_heredoc(struct parser_t * p, char * c, int * curs)
{
  char buffer[BSIZE], aux[BSIZE];
  unsigned char quote_seen = 0, term = ' ';
  unsigned char dash_seen = 0;
  int i, l = 0, spaces = 0;
  int len = p->length;

  /* Check for <<- case */
  if (*(c + 2) == '-') {
    dash_seen = 1;
    c += 3;
    (*curs)++;
  } else
    c += 2;
  if (*c == '\'' || *c == '"') {
    term = *c;
    c++; (*curs)++;
    quote_seen = 1;
  }
  for (i = 0; (is_identchar(c) || *c == term) && *curs <= len; (*curs)++, ++l)
    buffer[i++] = *c++;
  buffer[i - quote_seen] = '\0';
  if (quote_seen && *(c - 1) != term)
    yyerror(p, "unterminated here document identifier");
  l -= quote_seen;

  for (i = 0; *curs <= len; i++, c++, (*curs)++) {
    /* Ignore initial spaces if dash seen */
    if (i == 0 && dash_seen)
      for (; isspace(*c) && *c != '\n' && *curs <= len; c++, (*curs)++, spaces++);
    aux[i] = *c;
    if (*c == '\n') {
      p->line++;
      aux[i + 1] = '\0';
      if (!strncmp(buffer, aux, l) && (l == i)) {
        p->line--;
        p->column = i + spaces;
        return tHEREDOC;
      }
      spaces = 0;
      i = -1;
    }
    if (i > l)
      i = -1;
  }
  sprintf(aux, "Can't find string \"%s\" anywhere before EOF", buffer);
  yyerror(p, aux);
  return token_invalid;
}

/* Return what's the char that closes c */
static char closing_char(char c)
{
  switch (c) {
    case '[': return ']';
    case '(': return ')';
    case '<': return '>';
    case '{': return '}';
    default: return c;
  }
}

/*
 * Let's guess the kind depending on the character after the
 * %-character of expressions like %W
 */
static int guess_kind(char c)
{
  if (!isalpha(c) || to_upper(c) == 'Q' || c == 'x')
    return STRING;
  else if (to_upper(c) == 'W')
    return ARRAY;
  return REGEXP;
}

/* Push name to the stack */
static void push_stack(struct parser_t * parser, const char * buf)
{
  parser->stack[parser->sp] = strdup(buf);
  parser->sp++;
}

/* Pop name from the stack. */
static void pop_stack(struct parser_t * parser, struct node * n)
{
  if (n != NULL)
    n->name = parser->stack[0];
  parser->stack[0] = parser->stack[1];
  parser->stack[1] = NULL;
  parser->sp--;
}

/* Push a string variable */
static void push_string(struct parser_t * parser, char * buffer)
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
static void pop_string(struct parser_t * parser, struct node * n)
{
  n->l = parser->string_names;
  parser->string_names = NULL;
}

static void multiple_string(struct parser_t * parser, struct node * n)
{
  if (parser->auxiliar.endLine > 0) {
    n->endLine = parser->auxiliar.endLine;
    n->endCol = parser->auxiliar.endCol;
    parser->auxiliar.endLine = -1;
  }
}

static void push_pos(struct parser_t * parser, struct pos_t tokp)
{
  int scale = STACK_SIZE * parser->stack_scale;

  parser->pos_size++;
  if (parser->pos_size > STACK_SIZE) {
    parser->pos_size = 1;
    parser->stack_scale++;
    scale += STACK_SIZE;
    parser->pos_stack = (struct pos_t *) realloc (parser->pos_stack, scale * sizeof(struct pos_t));
  }
  tokp.offset = parser->cursor;
  parser->pos_stack[parser->pos_size + scale - 1] = tokp;
}

static void pop_pos(struct parser_t * parser, struct node * n)
{
  int scale = STACK_SIZE * parser->stack_scale;
  int pos = parser->pos_size - 1 + scale;
  struct pos_t tokp = parser->pos_stack[pos];

  if (n != NULL) {
    n->startLine = tokp.startLine;
    n->startCol = tokp.startCol;
    n->endLine = tokp.endLine;
    n->endCol = tokp.endCol;
    n->offset = tokp.offset;
  }
  parser->pos_size--;
  if (parser->pos_size == 0 && parser->stack_scale > 0) {
    parser->stack_scale--;
    parser->pos_size = STACK_SIZE;
    scale -= STACK_SIZE;
    parser->pos_stack = (struct pos_t *) realloc (parser->pos_stack, scale * sizeof(struct pos_t));
  }
}

static void pop_start(struct parser_t * parser, struct node * n)
{
  n->startLine = parser->pos_stack[parser->pos_size - 1].startLine;
  n->startCol = parser->pos_stack[parser->pos_size - 1].startCol;
  pop_pos(parser, NULL);
}

static void copy_wc_range(struct node * res, struct node * h, struct node * t)
{
  if (t != NULL)
    (t->last != NULL) ? copy_range(res, h, t->last) : copy_range(res, h, t);
}

static void copy_wc_range_ext(struct node * res, struct node * h, struct node * t)
{
  if (t != NULL)
    (t->last != NULL) ? copy_range(res, h, t->last) : copy_range(res, h, t);
  else
    copy_range(res, h, h);
}

static void copy_last(struct node * h, struct node * t)
{
  (t->last != NULL) ? copy_end(h, t->last) : copy_end(h, t);
}

static void push_last_comment(struct parser_t * parser)
{
  if ((parser->line - parser->last_comment.line) < 2)
    parser->comment_stack[parser->comment_index] = parser->last_comment.comment;
  else
    parser->comment_stack[parser->comment_index] = NULL;
  parser->comment_index++;
  parser->last_comment.comment = NULL;
}

static void pop_comment(struct parser_t * parser, struct node *n)
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


static void fix_pos(struct parser_t * parser, struct node * n)
{
  int kind;
  struct node * aux;

  if (n == NULL)
    return;

  kind = n->kind;
  if (has_operators(kind) && kind != token_hash) {
    copy_start(n, n->l);
    aux = (n->r->last != NULL) ? n->r->last : n->r;
    copy_end(n, aux);
  } else if (is_unary(kind) || kind == token_kw_not) {
    pop_pos(parser, n);
    n->endLine = n->l->endLine;
    n->endCol = n->l->endCol;
  } else if (kind == token_hash) {
    pop_pos(parser, n);
    if (n->l != NULL) {
      n->endLine = n->l->endLine;
      n->endCol = n->l->endCol;
    }
  } else {
    pop_pos(parser, n);
    parser->last_pos = n;
  }
}

/* Specialized version of the fix_pos function for ternary operators */
static void fix_ternary(struct node * n)
{
  if (n == NULL)
    return;

  n->startLine = n->cond->startLine;
  n->startCol = n->cond->startCol;
  n->endLine = n->r->endLine;
  n->endCol = n->r->endCol;
}

struct node * fix_star(struct parser_t * parser)
{
  struct node *res = alloc_node(token_object, NULL, NULL);
  res->startLine = res->endLine = parser->auxiliar.startLine;
  res->startCol = parser->auxiliar.startCol;
  res->endCol = res->startCol + 1;
  parser->auxiliar.endLine = -1;
  return res;
}

/*
 * The following macros and functions make all the magic of fetching comments.
 */

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

static void store_comment(struct parser_t *parser, char *comment)
{
  if (parser->last_comment.comment != NULL)
    free(parser->last_comment.comment);
  parser->last_comment.comment = comment;
  parser->last_comment.line = parser->line;
}

static int is_indented_comment(char *c)
{
  char *original = c;

  for (; *c == ' ' || *c == '\t'; ++c);
  return (*c == '#') ? (c - original) : 0;
}

static int get_comment(struct parser_t *parser, char *c, int curs)
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

static int parse_string(struct parser_t *p, char *c, int curs)
{
  int step = 0; /* How many bytes the actual utf8 character has */
  int ax = 0; /* Used to properly update the column when utf8 chars appear */
  int extra, i;
  int len = p->length;
  int init = curs;
  char term = *c;
  unsigned char vars = (term == '"' || term == '`' || term == '/');

  curs++; c++;
  for (extra = 0, i = p->column + 2; *c != term; i++) {
    for (; *c == '\\' && (*(c + 1) == term || *(c + 1) == '\\'); c += 2, curs += 2, i += 2);
    if (*c == term)
      break;
    if (*c == '\n') {
      p->line++;
      extra += i;
      i = 0;
    }
    if (vars && *c == '#' && *(c + 1) == '{')
      i += push_string_var(p, &curs, &c, ax) + 2;
    step = utf8_charsize(c);
    ax += step - 1;
    for (; step-- > 0; c++, curs++);
    if (curs >= len) {
      yyerror(p, "unterminated string meets end of file");
      break;
    }
  }
  curs++;
  p->column -= ax + extra;
  p->expr_seen = 1;
  return curs - init;
}

static int parse_word(struct parser_t *p, char *c, int curs, char *buffer)
{
  int step = 0; /* How many bytes the actual utf8 character has */
  int ax = 0; /* Used to properly update the column when utf8 chars appear */
  int len = p->length;
  char *ptr = buffer;

  do {
    step = utf8_charsize(c);
    ax += step - 1;
    while (step-- > 0) {
      *ptr++ = *c++;
      curs++;
    }
  } while (curs < len && not_sep(c));
  switch (*c) {
    case '=':
      if (!p->def_seen && !p->symbeg && !p->in_alias)
        break;
      if (*(c + 1) == '>')
        break;
    case '!': case '?':
      *ptr++ = *c++;
  }
  *ptr = '\0';
  if (p->def_seen && (isspace(*c) || *c == '('))
    p->def_seen = 0;
  p->column -= ax;
  return ptr - buffer;
}

static int parse_re_options(struct parser_t *p, char *c, int curs)
{
  int init = curs++;
  char aux[64];
  for (c++; isalpha(*c); c++, curs++) {
    if (*c != 'i' && *c != 'm' && *c != 'x' && *c != 'o' &&
        *c != 'u' && *c != 'e' && *c != 's' && *c != 'n') {
      sprintf(aux, "unknown regexp option - %c", *c);
      yyerror(p, aux);
    }
  }
  return curs - init;
}

/*
 * This is the lexer. It reads the source code (blob) and provides tokens to
 * the parser. It also updates the necessary flags.
 */
static int parser_yylex(struct parser_t * parser)
{
  int t = token_invalid;
  char buffer[BSIZE];
  char * c;
  int curs, len;
  unsigned char space_seen = 0;
  struct pos_t tokp = {-1, -1, -1, -1, 0};

  curs = parser->cursor;
  len = parser->length;
  if (curs >= len || parser->eof_reached) {
    parser->eof_reached = 1;
    return 0;
  }
  c = parser->blob + curs;

  /* Ignore whitespaces and backslashes */
  space_seen = *c;
  for (; isspace(*c) || *c == '\\'; ++c, ++curs, parser->column++, parser->cursor++) {
    if (*c == '\n') {
      if (!parser->expr_seen) {
        parser->column = -1;
        parser->line++;
      } else
        break;
    }
  }
  (space_seen != *c) ? (space_seen = 1) : (space_seen = 0);

  if (*c == '#') {
    int inc = get_comment(parser, c, curs) - 1;
    curs += inc;
    c += inc;
    parser->line--;
    if (curs + 1 >= len) {
      parser->eof_reached = 1;
      return 0;
    }
    t = tCOMMENT;
  } else if (*c == '\n') {
    t = EOL;
    parser->dot_seen = 0;
    parser->cmd_arg = 0;
    parser->column = -1; /* So it's correct after curs++ */
    parser->in_alias = 0;
    parser->line++;
    curs++;
    parser->expr_seen = 0;
  } else if (isdigit(*c)) {
    char hex, bin, has_point, aux;
    hex = bin = has_point = aux = 0;

    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    if (*c == '0') {
      if (to_upper(*(c + 1)) == 'X') {
        hex = 1;
        curs++;
        c++;
      } else if (to_upper(*(c + 1)) == 'B') {
        bin = 1;
        curs++;
        c++;
      }
      curs++;
      c++;
    }
    while (curs < len && ((isdigit(*c) && !bin) || (!hex && !bin && !has_point && *c == '.')
          || (hex && to_upper(*c) >= 'A' && to_upper(*c) < 'G')
          || (bin && (*c == '1' || *c == '0')) || *c == '_')) {
      if (*c == '.') {
        if (!isdigit(*(c + 1)))
          break; /* Don't mess with ranges */
        has_point = 1;
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
      for (; (curs < len) && isdigit(*c); c++, curs++);
    }
    parser->expr_seen =  1;
    parser->dot_seen = 0;
    t = (has_point) ? FLOAT : NUMERIC;
  } else if (*c == '$') {
    int inc = 1;
    curs++;
    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    buffer[0] = '$';
    switch (*(c + 1)) {
      case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        for (c += 1; isdigit(*c); c++, curs++)
          buffer[inc++] = *c;
        buffer[inc] = '\0';
        t = tNTH_REF;
        break;
      case '~': case '*': case '$': case '?': case '!': case '@':
      case '/': case '\\': case ';': case ',': case '.': case '=':
      case ':': case '<': case '>': case '\"':
      case '&': case '`': case '\'': case '+':
      case '0':
        t = GLOBAL;
        curs++;
        buffer[inc++] = *(c + 1);
        buffer[inc] = '\0';
        break;
      case '-':
        buffer[inc++] = *(c + 1);
        curs++;
      default:
        t = GLOBAL;
        inc = parse_word(parser, c + inc, curs + inc, buffer + inc);
        curs += inc;
        break;
    }
    parser->expr_seen = 1;
    parser->dot_seen = 0;
    push_stack(parser, buffer);
  } else if (*c == '@') {
    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    int inc = parse_word(parser, c, curs, buffer);
    t = (inc > 1 && buffer[1] == '@') ? CVAR : IVAR;
    curs += inc;
    push_stack(parser, buffer);
    parser->expr_seen = 1;
    parser->dot_seen = 0;
  } else if (not_sep(c)) {
    int diff;

    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    diff = parse_word(parser, c, curs, buffer);
    c += diff; curs += diff;

    if (*c == '(') {
      t = BASE;
      push_stack(parser, buffer);
      parser->expr_seen = 0;
      parser->special_arg = 1;
      parser->mcall = 1;
    } else if (parser->dot_seen) {
      push_stack(parser, buffer);
      t = BASE;
      parser->dot_seen = 0;
      parser->expr_seen = 1;
    } else {
      const struct kwtable *kw = rb_reserved_word(buffer, diff);
      if (kw) {
        t = kw->id[0];
        switch (t) {
          case tDEF:
            parser->def_seen = 1;
          case tMODULE: case tCLASS:
            push_last_comment(parser);
            break;
          case tALIAS:
            parser->in_alias = 1;
            break;
          case tEND:
            parser->cmd_arg = 0;
            break;
          case tRETURN:
            parser->expr_mid = 2;
        }
        if (t != kw->id[1] && (parser->expr_seen || parser->expr_mid > 0)) {
          t = kw->id[1];
          parser->expr_seen = 0;
        } else
          parser->expr_seen = kw->expr;
      } else if (is_special_method(buffer)) {
        if (!strcmp(buffer, "__END__")) {
          parser->eof_reached = 1;
          t = tpEND;
        } else {
          push_stack(parser, buffer);
          t = BASE;
        }
      } else if (not_sep(buffer)) {
        parser->expr_seen = 1;
        if (is_upper(buffer[0]))
          t = CONST;
        else if (*c == ':' && *(c + 1) != ':') {
          t = tKEY;
          parser->expr_seen = 0;
          ++curs;
        } else
          t = BASE;
        push_stack(parser, buffer);
      }
    }
    parser->dot_seen = 0;
  } else if (*c == '[') {
    unsigned char should_store = 1;
    curs++;
    parser->paren_nest++;
    parser->cmd_arg = 0;
    if (parser->dot_seen || parser->def_seen) {
      if (*(c + 1) == ']') {
        ++curs;
        should_store = 0;
        if (*(c + 2) == '=') {
          ++curs;
          t = tASET;
        } else
          t = tAREF;
      } else if (!parser->def_seen)
        t = '[';
    } else if (!parser->expr_seen || space_seen) {
      t = tLBRACKET;
    } else {
      t = '[';
    }
    if (should_store) {
      tokp.startLine = tokp.endLine = parser->line;
      tokp.startCol = parser->column;
    }
    parser->expr_seen = 0;
  } else if (*c == ']') {
    parser->paren_nest--;
    parser->expr_seen = 1;
    parser->brace_arg = 1;
    t = ']';
    curs++;
  } else if (*c == '=') {
    curs++;
    if (*(c + 1) == '=') {
      ++curs;
      parser->expr_seen = 0;
      if (*(c + 2) == '=') {
        t = tEQQ;
        curs++;
      } else
        t = tEQ;
    } else if (*(c + 1) == '~') {
      ++curs;
      parser->expr_seen = 0;
      t = tMATCH;
      parser->expr_seen = 0;
    } else if (*(c + 1) == '>') {
      ++curs;
      parser->expr_seen = 0;
      t = tASSOC;
    } else if (multiline_comment(c)) {
      curs += 5;
      c += 5;
      for(; !multiline_end(c); ++curs, ++c)
        if (*c == '\n')
          parser->line++;
      curs += 3;
      t = tCOMMENT;
    } else
      t = '=';
  } else if (*c == '<') {
    curs++;
    if (*(c + 1) == '<') {
      curs++;
      if (*(c + 2) == '=') {
        curs++;
        t = tOP_ASGN;
      } else {
        if (cannot_be_heredoc) {
          parser->expr_seen = 0;
          t = tLSHIFT;
        } else {
          tokp.startLine = parser->line;
          tokp.startCol = parser->column;
          t = parse_heredoc(parser, c, &curs);
          tokp.endLine = parser->line;
          tokp.endCol = parser->column;
          parser->expr_seen = 1;
          if (parser->mcall) {
            t = tHERE_PAR;
            parser->mcall = 0;
          }
        }
      }
    } else if (*(c + 1) == '=') {
      curs++;
      parser->expr_seen = 0;
      if (*(c + 2) == '>') {
        curs++;
        t = tCMP;
      } else
        t = tLEQ;
    } else {
      parser->expr_seen = 0;
      t = '<';
    }
  } else if (*c == '>') {
    curs++;
    parser->expr_seen = 0;
    if (*(c + 1) == '>') {
      curs++;
      if (*(c + 2) == '=') {
        curs++;
        t = tOP_ASGN;
      } else
        t = tRSHIFT;
    } else if (*(c + 1) == '=') {
      curs++;
      t = tGEQ;
    } else
      t = '>';
  } else if (*c == '!') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      parser->expr_seen = 0;
      t = tNEQ;
    } else if (*(c + 1) == '~') {
      curs++;
      parser->expr_seen = 0;
      t = tNMATCH;
    } else {
      tokp.startLine = tokp.endLine = parser->line;
      tokp.startCol = parser->column;
      if (parser->def_seen && *(c + 1) == '@')
        curs++;
      t = '!';
    }
  } else if (*c == '+') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else {
      t = '+';
      if (!parser->expr_seen) {
        tokp.startLine = tokp.endLine = parser->line;
        tokp.startCol = parser->column;
        t = tUPLUS;
      } else if (parser->def_seen && *(c + 1) == '@') {
        curs++;
        tokp.startLine = tokp.endLine = parser->line;
        tokp.startCol = parser->column;
        t = tUPLUS;
      } else if (parser->expr_seen && space_seen && !isspace(*(c + 1))) {
        tokp.startLine = tokp.endLine = parser->line;
        tokp.startCol = parser->column;
        t = tUPLUS;
      } else
        parser->expr_seen = 0;
    }
  } else if (*c == '-') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else if (*(c + 1) == '>') {
      curs++;
      tokp.startLine = tokp.endLine = parser->line;
      tokp.startCol = parser->column;
      t = tLAMBDA;
    } else {
      t = '-';
      if (!parser->expr_seen) {
        tokp.startLine = tokp.endLine = parser->line;
        tokp.startCol = parser->column;
        t = tUMINUS;
      } else if (parser->def_seen && *(c + 1) == '@') {
        curs++;
        tokp.startLine = tokp.endLine = parser->line;
        tokp.startCol = parser->column;
        t = tUMINUS;
      }  else if (parser->expr_seen && space_seen && !isspace(*(c + 1))) {
        parser->expr_seen = 0;
        tokp.startLine = tokp.endLine = parser->line;
        tokp.startCol = parser->column;
        t = tUMINUS;
      } else
        parser->expr_seen = 0;
    }
  } else if (*c == '*') {
    curs++;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else if (*(c + 1) == '*') {
      ++curs;
      parser->expr_seen = 0;
      if (*(c + 2) == '=') {
        ++curs;
        t = tOP_ASGN;
      } else
        t = tPOW;
    } else {
      if (!parser->expr_seen || parser->dot_seen)
        t = tSTAR;
      else
        t = '*';
      parser->expr_seen = 0;
      parser->auxiliar.startLine = parser->line;
      parser->auxiliar.startCol = parser->column;
    }
  } else if (*c == '/') {
    curs++;
    if (!parser->expr_seen) {
      int diff;
      tokp.startLine = parser->line;
      tokp.startCol = parser->column;
      diff = parse_string(parser, c, curs) - 1;
      tokp.endLine = parser->line;
      curs += diff;
      c += diff;
      if (isalpha(*(c + 1)))
        curs += parse_re_options(parser, c, curs) - 1;
      t = REGEXP;
    } else if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else {
      t = '/';
      parser->expr_seen = 0;
    }
  } else if (*c == '%') {
    ++curs;
    if (*(c + 1) == '=') {
      curs++;
      t = tOP_ASGN;
    } else if (is_shortcut(*(c + 1))) {
      int catalan = 1;
      int kind = guess_kind(*(c + 1));
      unsigned char is_simple = !isalpha(*(c + 1));
      char open, close;
      int ax = 0;
      int step = 0;

      tokp.startLine = tokp.endLine = parser->line;
      tokp.startCol = parser->column;
      curs += 2 - is_simple;
      c += 3 - is_simple;
      open = *(c - 1);
      close = closing_char(*(c - 1));
      while (catalan != -1) {
        if (*c == '#' && *(c + 1) == '{') {
          push_string_var(parser, &curs, &c, 0);
          ++curs;
          ++c;
        }
        if (*c == close) {
          --catalan;
          if (!catalan)
            break;
        } else if (*c == open)
          ++catalan;
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
        if (*c == '\n') {
          tokp.endLine++;
          parser->line++;
          parser->cursor = curs + 1;
        }
      }
      /* Don't overwrite token kind if an error occurred */
      if (!catalan) {
        t = kind;
        ++curs;
      }
      parser->expr_seen = 1;
    } else {
      t = '%';
      parser->expr_seen = 0;
    }
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
    } else if (!parser->expr_seen || parser->dot_seen)
      t = tAMPER;
    else
      t = '&';
    parser->expr_seen = 0;
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
      t = '|';
    parser->expr_seen = 0;
  } else if (*c == '.') {
    curs++;
    if (*(c + 1) == '.') {
      curs++;
      parser->expr_seen = 0;
      if (*(c + 2) == '.') {
        curs++;
        t = tDOT3;
      } else
        t = tDOT2;
    } else {
      t = '.';
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
    } else if (!isspace(*(c + 1))) {
      tokp.startLine = tokp.endLine = parser->line;
      tokp.startCol = parser->column;
      t = tSYMBEG;
      parser->symbeg = 1;
      parser->expr_seen = 1;
    } else {
      parser->expr_seen = 0;
      t = ':';
    }
  } else if (*c == ';') {
    curs++;
    parser->expr_seen = 0;
    t = ';';
  } else if (*c == '?') {
    curs++;
    if (!isspace(*(c + 1))) {
      if (!parser->expr_seen) {
        curs++;
        tokp.startLine = tokp.endLine = parser->line;
        tokp.startCol = parser->column;
        tokp.endCol = tokp.startCol + 2;
        t = STRING;
        parser->expr_seen = 1;
      } else
        t = '?';
    } else
      t = '?';
  } else if (*c == '\'') {
    tokp.startLine = parser->line;
    tokp.startCol = parser->column;
    curs += parse_string(parser, c, curs);
    tokp.endLine = parser->line;
    t = STRING;
  } else if (*c == '"') {
    tokp.startLine = parser->line;
    tokp.startCol = parser->column;
    curs += parse_string(parser, c, curs);
    tokp.endLine = parser->line;
    t = STRING;
  } else if (*c == '(') {
    parser->paren_nest++;
    parser->cmd_arg = 0;
    if (parser->special_arg) {
      parser->special_arg = 0;
      t = '(';
    } else if (!parser->expr_seen || parser->cond_seen)
      t = tLPAREN;
    else
      t = '(';
    curs++;
  } else if (*c == ')') {
    parser->paren_nest--;
    curs++;
    parser->expr_seen = 1;
    if (!parser->paren_nest)
      parser->mcall = 0;
    t = ')';
  } else if (*c == '{') {
    if (parser->lpar_beg && parser->lpar_beg == parser->paren_nest) {
      parser->lpar_beg = 0;
      parser->paren_nest--;
      t = tLAMBEG; /* this is a lambda ->() {} construction */
    } else if (!parser->expr_seen || parser->cond_seen)
      t = tLBRACE; /* smells like hash */
    else if (parser->brace_arg)
      t = tLBRACE_ARG; /* block (expr) */
    else
      t = '{'; /* block (primary) */
    parser->cmd_arg = 0;
    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    curs++;
  } else if (*c == '}') {
    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = parser->column;
    parser->expr_seen = 1;
    parser->brace_arg = 1;
    parser->cmd_arg = 0;
    curs++;
    t = '}';
  } else if (*c == ',') {
    curs++;
    parser->expr_seen = 0;
    t = ',';
  } else if (*c == '`') {
    if (parser->def_seen) {
      curs++;
      t = '`';
    } else {
      tokp.startLine = parser->line;
      tokp.startCol = parser->column;
      curs += parse_string(parser, c, curs);
      tokp.endLine = parser->line;
      t = tBACKTICK;
    }
  } else if (*c == '~') {
    curs++;
    tokp.startLine = tokp.endLine = parser->line;
    tokp.startCol = tokp.endCol = parser->column;
    if (parser->def_seen && *(c + 1) == '@')
      curs++;
    t = '~';
  } else if (*c == '^') {
    curs++;
    t = '^';
    parser->expr_seen = 0;
  }

  /* Let's fix the tDO token */
  if (t == tDO) {
    if (parser->lpar_beg && parser->lpar_beg == parser->paren_nest) {
      parser->lpar_beg = 0;
      parser->paren_nest--;
      t = tDO_LAMBDA;
    } else if (parser->cond_seen) {
      t = tDO_COND;
    } else if (parser->cmd_arg || !parser->expr_seen || parser->brace_arg) {
      parser->cmd_arg = 0;
      t = tDO_BLOCK;
    } else
      t = tDO;
    parser->dot_seen = 0;
    parser->expr_seen = 0;
  }

  /* Unset some flags if necessary */
  if (parser->brace_arg && *c != '}' && *c != ']')
    parser->brace_arg = 0;
  if (t == tOP_ASGN || t == '=')
    parser->expr_seen = 0;

  parser->expr_mid--;
  if (parser->symbeg && t != tSYMBEG) {
    parser->symbeg = 0;
    parser->expr_seen = 1;
  }

  if (t != tCOMMENT)
    parser->column += curs - parser->cursor;

  parser->cursor = curs;
  if (tokp.startLine > 0) {
    if (tokp.endCol < 0)
      tokp.endCol = parser->column;
    push_pos(parser, tokp);
  }

  /* it's the end... */
  if (curs >= len)
    parser->eof_reached = 1;
  return t;
}

/*
 * Standard yylex.
 */
static int yylex(void * lval, void * p)
{
  struct parser_t * parser = (struct parser_t *) p;
  int ret;
  (void) lval; /* like Q_UNUSED */

  /* This parser does not like comments inside the grammar */
  while ((ret = parser_yylex(parser)) == tCOMMENT);
  return ret;
}

/*
 * Error handling. Take the formmated string s and append the error
 * string to the list of errors p->errors.
 */
static void yyerror(struct parser_t * p, const char * s, ...)
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
static void copy_error(RAst * ast, int index, struct error_t p)
{
  ast->errors[index].valid = p.valid;
  ast->errors[index].line = p.line;
  ast->errors[index].col = p.col;
  ast->errors[index].msg = p.msg;
}

RAst * rb_compile_file(const char * path, const char * contents)
{
  struct parser_t p;
  RAst * result;

  /* Initialize parser */
  init_parser(&p);
  p.name = strdup(path);
  if (!contents) {
    if (!retrieve_source(&p, path))
      return NULL;
  } else {
    p.length = strlen(contents);
    p.blob = strdup(contents);
  }

  /* Let's parse */
  result = (RAst *) malloc (sizeof(RAst));
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
