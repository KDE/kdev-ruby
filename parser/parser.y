/* This file is part of KDevelop
 *
 * This file is based on the file parse.y from the MRI, version 1.9.2-p136.
 * So, at this point I must recognize the amazing job ruby developers
 * are doing and specially Yukihiro Matsumoto, the Ruby original author
 * and the one who signed parse.y.
 *
 * Copyright (C) 1993-2007 Yukihiro Matsumoto
 * Copyright (C) 2010 Miquel Sabaté <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


%{
/* make clang happy */
extern char *strdup(const char *s);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"


#define SSIZE 256
#define LSIZE (SSIZE << 2)


/* The state bits, as defined below, have been extracted from the MRI. */
enum lex_state_bits {
    EXPR_BEG_bit,               /* ignore newline, +/- is a sign. */
    EXPR_END_bit,               /* newline significant, +/- is an operator. */
    EXPR_ENDARG_bit,            /* ditto, and unbound braces. */
    EXPR_ENDFN_bit,             /* ditto, and unbound braces. */
    EXPR_ARG_bit,               /* newline significant, +/- is an operator. */
    EXPR_CMDARG_bit,            /* newline significant, +/- is an operator. */
    EXPR_MID_bit,               /* newline significant, +/- is an operator. */
    EXPR_FNAME_bit,             /* ignore newline, no reserved words. */
    EXPR_DOT_bit,               /* right after `.' or `::', no reserved words. */
    EXPR_CLASS_bit,             /* immediate after `class', no here document. */
    EXPR_VALUE_bit,             /* alike EXPR_BEG but label is disallowed. */
};

/* This enum defines the states in which the lexer can be. */
enum lex_state_e {
#define DEF_EXPR(n) EXPR_##n = (1 << EXPR_##n##_bit)
    DEF_EXPR(BEG),
    DEF_EXPR(END),
    DEF_EXPR(ENDARG),
    DEF_EXPR(ENDFN),
    DEF_EXPR(ARG),
    DEF_EXPR(CMDARG),
    DEF_EXPR(MID),
    DEF_EXPR(FNAME),
    DEF_EXPR(DOT),
    DEF_EXPR(CLASS),
    DEF_EXPR(VALUE),
    EXPR_BEG_ANY  =  (EXPR_BEG | EXPR_VALUE | EXPR_MID | EXPR_CLASS),
    EXPR_ARG_ANY  =  (EXPR_ARG | EXPR_CMDARG),
    EXPR_END_ANY  =  (EXPR_END | EXPR_ENDARG | EXPR_ENDFN)
};

/* Helper macros for handling the lexer states. */
#define IS_lex_state_for(x, ls) ((x) & (ls))
#define IS_lex_state(ls)        IS_lex_state_for(lex_state, (ls))

/* And now some macros that will help us on some stacks of the parser. */
#define BITSTACK_PUSH(stack, n) ((stack) = ((stack)<<1)|((n)&1))
#define BITSTACK_POP(stack)     ((stack) = (stack) >> 1)
#define BITSTACK_LEXPOP(stack)  ((stack) = ((stack) >> 1) | ((stack) & 1))
#define BITSTACK_SET_P(stack)   ((stack)&1)

#define COND_PUSH(n)    BITSTACK_PUSH(parser->cond_stack, (n))
#define COND_POP()      BITSTACK_POP(parser->cond_stack)
#define COND_LEXPOP()   BITSTACK_LEXPOP(parser->cond_stack)
#define COND_P()        BITSTACK_SET_P(parser->cond_stack)

#define CMDARG_PUSH(n)  BITSTACK_PUSH(parser->cmdarg_stack, (n))
#define CMDARG_POP()    BITSTACK_POP(parser->cmdarg_stack)
#define CMDARG_LEXPOP() BITSTACK_LEXPOP(parser->cmdarg_stack)
#define CMDARG_P()      BITSTACK_SET_P(parser->cmdarg_stack)


/*
 * This structure represents a string/heredoc/regexp/shortcut term.
 */
struct term_t {
    int token;
    char *word;
    int nest;
    unsigned char term;
    unsigned char paren;
    unsigned char can_embed : 1;
    unsigned char nestable : 1;
};

/*
 * This structure contains a comment on the code. It basically stores
 * the comment itself in a dynamically allocated char pointer, and the
 * line where it was found.
 */
struct comment_t {
    char *comment;
    int line;
};

/*
 * This structure defines all the information that the parser has.
 * It contains the AST, flags, stacks, etc.
 */
struct parser_t {
    /* Abstract Syntax Tree */
    struct node *ast;

    /* Stack of positions */
    struct pos_t *pos_stack;
    int stack_scale;
    int pos_size;

    /* Flags used by the parser */
    unsigned char eof_reached : 1;
    unsigned int cond_stack;
    unsigned int cmdarg_stack;
    int in_def;
    int paren_nest;
    int lpar_beg;
    int parser_command_start;
    enum ruby_version version;

    /* Stuff from the lexer */
    enum lex_state_e lex_state;
    struct term_t *lex_strterm;
    char *lex_p;
    char *lex_prev;
    char *lex_pend;
    unsigned long lex_prevc;

    /* Basically used to handle heredocs properly */
    unsigned long line_pend;
    unsigned long column_pend;
    unsigned char here_found : 1;

    /* Errors on the file */
    struct error_t *errors;
    struct error_t *last_error;
    unsigned char warning : 1;
    unsigned char unrecoverable : 1;

    /* Stack of names */
    char *stack[2];
    char *aux;
    int sp;

    /* The last allocated comment + the comment stack    */
    struct comment_t last_comment;
    char *comment_stack[SSIZE];
    int comment_index;

    /* Info about the content to parse */
    unsigned long length;
    unsigned long line;
    unsigned long column;
    unsigned char content_given : 1;
    char *blob;
};

#include "parser.h"
#define yyparse ruby_yyparse
#define YYERROR_VERBOSE 1

/* Macros to access some attributes in a fancier way. */
#define lex_strterm parser->lex_strterm
#define lex_state parser->lex_state
#define command_start parser->parser_command_start

/* yy's functions */
#if YYPURE
static int yylex(void *, void *);
#else
static int yylex(void *);
#endif
static void yyerror(struct parser_t *, const char *);
#define yywarning(msg) { parser->warning = 1; yyerror(parser, (msg)); parser->warning = 0;}

/* The static functions below deal with stacks. */
static void pop_stack(struct parser_t *parser, struct node *n);
static void push_last_comment(struct parser_t *parser);
static void pop_comment(struct parser_t *parser, struct node *n);
static void pop_pos(struct parser_t *parser, struct node *n);
static void pop_start(struct parser_t *parser, struct node *n);
static void pop_end(struct parser_t *parser, struct node *n);

/* Helper macros for nodes, positions and stacks */
#define ALLOC_N(kind, l, r) alloc_node(kind, l, r); pop_pos(parser, yyval.n);
#define DISPOSE2(node1, node2) { free_ast(node1); free_ast(node2); }
#define DISPOSE3(node1, node2, node3) { DISPOSE2(node1, node2); free_ast(node3); }
#define POP_STACK pop_stack(parser, yyval.n)
#define discard_pos() pop_pos(parser, NULL)
#define copy_op(op) { parser->aux = strdup(op); }
%}

%pure-parser
%lex-param {struct parser_t *parser }
%parse-param { struct parser_t *parser }
%union {
    struct node *n;
    int num;
    struct term_t *term;
}

/* Tokens */
%token tCLASS tMODULE tDEF tUNDEF tBEGIN tRESCUE tENSURE tEND tIF tUNLESS
%token tTHEN tELSIF tELSE tCASE tWHEN tWHILE tUNTIL tFOR tBREAK tNEXT tREDO
%token tRETRY tIN tDO tDO_COND tDO_BLOCK tRETURN tYIELD tKWAND tKWOR tKWNOT
%token tALIAS tDEFINED upBEGIN upEND tTRUE tFALSE tNIL tENCODING tDSTAR
%token tFILE tLINE tSELF tSUPER GLOBAL BASE CONST tDO_LAMBDA tCHAR tIMAGINARY
%token IVAR CVAR tINTEGER tFLOAT tNTH_REF tBACKTICK tpEND tSYMBEG tRATIONAL
%token tAMPER tAREF tASET tASSOC tCOLON2 tCOLON3 tLAMBDA tLAMBEG tLBRACE
%token tLBRACKET tLPAREN tLPAREN_ARG tSTAR tCOMMENT ARRAY tKEY SYMBOL tUMINUS_NUM
%token tSTRING_BEG tSTRING_CONTENT tSTRING_DBEG tSTRING_DEND tSTRING_END tSTRING_DVAR

/* Types */
%type <n> singleton strings string literal numeric cpath rescue_arg
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
%type <n> opt_args_tail args_tail f_kwarg block_args_tail opt_block_args_tail
%type <n> f_kw f_block_kw f_block_kwarg f_kwrest simple_numeric
%type <n> string_contents string_content string_dvar

/* When an error has been found, free all the nodes from bison's stacks */
%destructor { free_ast($$); } <n>

/* precedence table */
%nonassoc tLOWEST
%nonassoc tLBRACE_ARG

%nonassoc modifier_if modifier_unless modifier_while modifier_until
%left tKWOR tKWAND
%right tKWNOT
%nonassoc tDEFINED
%right '=' tOP_ASGN
%left modifier_rescue
%right '?' ':'
%nonassoc tDOT2 tDOT3
%left tOR
%left tAND
%nonassoc tCMP tEQ tEQQ tNEQ tMATCH tNMATCH
%left '>' tGEQ '<' tLEQ
%left '|' '^'
%left '&'
%left tLSHIFT tRSHIFT
%left '+' '-'
%left '*' '/' '%'
%right tUMINUS_NUM tUMINUS
%right tPOW
%right '!' '~' tUPLUS

%%

top_compstmt: top_stmt  { parser->ast = $1; $$ = 0; YYACCEPT; }
    | term              { $$ = 0; YYACCEPT; }
;

top_stmt: none
    | stmt
    | error stmt { $$ = $2; }
;

bodystmt:
    {
        $<num>$ = parser->line;
    }
    {
        $<num>$ = parser->column;
    }
    compstmt opt_rescue opt_else opt_ensure
    {
        $$ = alloc_ensure(token_body, $3, $4, $5, $6);
        pop_end(parser, $$); /* Every bodystmt ends with tEND */
        $$->pos.start_line = $<num>1;
        $$->pos.start_col = $<num>2;
    }
;

compstmt: stmts opt_terms { $$ = $1; }
;

stmts: none
    | stmt
    | stmts terms stmt  { $$ = ($1 == NULL) ? $3 : update_list($1, $3); }
    | error stmt        { $$ = $2; }
;

stmt: tALIAS fsym { lex_state = EXPR_FNAME; } fsym
    {
        $$ = alloc_node(token_alias, $2, $4);
    }
    | tALIAS GLOBAL GLOBAL
    {
        /* Ugly as hell, but it works */
        struct node *l = alloc_node(token_object, NULL, NULL);
        l->flags = 3;
        struct node *r = alloc_node(token_object, NULL, NULL);
        r->flags = 3;
        pop_pos(parser, r);
        pop_pos(parser, l);
        pop_stack(parser, l);
        pop_stack(parser, r);
        $$ = alloc_node(token_alias, l, r);
    }
    | tALIAS GLOBAL tNTH_REF
    {
        yyerror(parser, "can't make alias for the number variables");
        $$ = 0;
    }
    | tUNDEF undef_list
    {
        $$ = alloc_node(token_undef, NULL, $2);;
    }
    | stmt modifier_if expr
    {
        $$ = alloc_cond(token_if, $3, $1, NULL);
    }
    | stmt modifier_unless expr
    {
        $$ = alloc_cond(token_unless, $3, $1, NULL);
    }
    | stmt modifier_while expr
    {
        $$ = alloc_cond(token_while, $3, $1, NULL);
    }
    | stmt modifier_until expr
    {
        $$ = alloc_cond(token_until, $3, $1, NULL);
    }
    | stmt modifier_rescue stmt
    {
        $$ = alloc_cond(token_rescue, $3, $1, NULL);
    }
    | upBEGIN
    {
        if (parser->in_def)
            yyerror(parser, "BEGIN in method");
    }
    '{' compstmt '}'
    {
        $$ = alloc_node(token_up_begin, $4, NULL);
        discard_pos(); /* } */
        discard_pos(); /* { */
    }
    | upEND '{' compstmt '}'
    {
        $$ = alloc_node(token_up_end, $3, NULL);
        discard_pos(); /* } */
        discard_pos(); /* { */
    }
    | lhs '=' command_call  { $$ = alloc_node(token_assign, $1, $3); }
    | mlhs '=' command_call { $$ = alloc_node(token_assign, $1, $3); }
    | variable tOP_ASGN command_call { $$ = alloc_node(token_op_assign, $1, $3); }
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
        $$ = NULL;
        DISPOSE3($1, $3, $5);
    }
    | primary tCOLON2 base tOP_ASGN command_call
    {
        struct node *aux = alloc_node(token_object, $1, $3);
        $$ = alloc_node(token_op_assign, aux, $5);
    }
    | backref tOP_ASGN command_call { $$ = alloc_node(token_op_assign, $1, $3); }
    | lhs '=' mrhs  { $$ = alloc_node(token_assign, $1, $3); }
    | mlhs '=' arg  { $$ = alloc_node(token_assign, $1, $3); }
    | mlhs '=' mrhs { $$ = alloc_node(token_assign, $1, $3); }
    | expr
    | tpEND { $$ = alloc_node(token__end__, NULL, NULL); }
;

expr: command_call
    | expr tKWAND expr      { $$ = alloc_node(token_kw_and, $1, $3);   }
    | expr tKWOR expr       { $$ = alloc_node(token_kw_or, $1, $3);    }
    | tKWNOT opt_eol expr   { $$ = alloc_node(token_kw_not, $3, NULL); }
    | '!' command_call      { $$ = alloc_node(token_not, $2, NULL);    }
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
        $$ = ALLOC_N(token_block, $3, $2);
        pop_start(parser, $$);
    }
;

command: operation command_args             %prec tLOWEST
    {
        $$ = alloc_node(token_method_call, $1, $2);
    }
    | operation command_args cmd_brace_block
    {
        $$ = alloc_cond(token_method_call, $3, $1, $2);
    }
    | primary '.' operation2 command_args         %prec tLOWEST
    {
        struct node *aux = update_list($1, $3);
        $$ = alloc_node(token_method_call, aux, $4);
    }
    | primary '.' operation2 command_args cmd_brace_block
    {
        struct node *aux = update_list($1, $3);
        $$ = alloc_cond(token_method_call, $5, aux, $4);
    }
    | primary tCOLON2 operation2 command_args %prec tLOWEST
    {
        struct node *aux = update_list($1, $3);
        $$ = alloc_node(token_method_call, aux, $4);
    }
    | primary tCOLON2 operation2 command_args cmd_brace_block
    {
        struct node *aux = update_list($1, $3);
        $$ = alloc_cond(token_method_call, $5, aux, $4);
    }
    | tSUPER call_args  { $$ = alloc_node(token_method_call, $2, NULL); }
    | tYIELD call_args  { $$ = alloc_node(token_yield, $2, NULL);       }
    | tRETURN call_args { $$ = alloc_node(token_return, $2, NULL);      }
    | tBREAK call_args  { $$ = alloc_node(token_break, $2, NULL);       }
    | tNEXT call_args   { $$ = alloc_node(token_next, $2, NULL);        }
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
        $$ = alloc_node(token_object, NULL, NULL);
        $$->flags = 2;
        $$ = update_list($1, $$);
    }
    | mlhs_head tSTAR ',' mlhs_post
    {
        $$ = alloc_node(token_object, NULL, NULL);
        $$->flags = 2;
        $$ = update_list($1, $$);
        $$ = concat_list($$, $4);
    }
    | tSTAR mlhs_node               { $$ = $2; $$->flags = 1; }
    | tSTAR mlhs_node ',' mlhs_post { $$ = update_list($2, $4); $2->flags = 1; }
    | tSTAR
    {
        $$ = alloc_node(token_object, NULL, NULL);
        $$->flags = 2;
    }
    | tSTAR ',' mlhs_post
    {
        $$ = alloc_node(token_object, NULL, NULL);
        $$->flags = 2;
        $$ = update_list($$, $3);
    }
;

mlhs_item: mlhs_node
    | tLPAREN mlhs_inner rparen { $$ = alloc_node(token_object, $2, NULL); }
;

mlhs_head: mlhs_item ','        { $$ = $1; }
    | mlhs_head mlhs_item ','   { $$ = update_list($1, $2); }
;

mlhs_post: mlhs_item            { $$ = $1; }
    | mlhs_post ',' mlhs_item   { $$ = update_list($1, $3); }
;

mlhs_node: variable
    | primary '[' opt_call_args rbracket
    {
        $$ = alloc_node(token_array_value, $1, $3);
    }
    | primary '.' base          { $$ = alloc_node(token_method_call, $1, $3); }
    | primary tCOLON2 base      { $$ = alloc_node(token_method_call, $1, $3); }
    | primary '.' const         { $$ = alloc_node(token_method_call, $1, $3); }
    | primary tCOLON2 const
    {
        if (parser->in_def)
            yyerror(parser, "dynamic constant assignment");
        $$ = alloc_node(token_method_call, $1, $3);
    }
    | tCOLON3 const
    {
        if (parser->in_def)
            yyerror(parser, "dynamic constant assignment");
        $$ = $2;
    }
    | backref
;

lhs: variable
    | primary '[' opt_call_args rbracket
    {
        $$ = alloc_node(token_array_value, $1, $3);
    }
    | primary '.' base          { $$ = alloc_node(token_method_call, $1, $3); }
    | primary tCOLON2 base      { $$ = alloc_node(token_method_call, $1, $3); }
    | primary '.' const         { $$ = alloc_node(token_method_call, $1, $3); }
    | primary tCOLON2 const
    {
        if (parser->in_def)
            yyerror(parser, "dynamic constant assignment");
        $$ = alloc_node(token_method_call, $1, $3);
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
      $$ = 0;
    }
    | const
;

cpath: tCOLON3 cname        { $$ = $2; }
    | cname                 { $$ = $1; }
    | primary tCOLON2 cname
    {
        $$ = update_list($1, $3);
        $$->pos.end_line = $3->pos.end_line;
        $$->pos.end_col = $3->pos.end_col;
    }
;

fname: base
    | const
    | op
    {
        lex_state = EXPR_ENDFN;
        $$ = alloc_node(token_object, NULL, NULL);
        $$->name = parser->aux;
        $$->pos.start_line = $$->pos.end_line = parser->line;
        $$->pos.end_col = parser->column;
        $$->pos.start_col = $$->pos.end_col - strlen(parser->aux); 
    }
    | reswords
    {
        lex_state = EXPR_ENDFN;
        $$ = alloc_node(token_object, NULL, NULL);
    }
;

fsym: fname | symbol
;

undef_list: fsym
    | undef_list ',' { lex_state = EXPR_FNAME; } fsym { $$ = update_list($1, $4); }
;

op: '|' { copy_op("|"); } | '^' { copy_op("^"); } | '&' { copy_op("&"); }
    | tCMP { copy_op("<=>"); } | tEQ { copy_op("=="); } | tEQQ { copy_op("===");}
    | tMATCH { copy_op("=~"); } | tNMATCH {copy_op("!~");} | '>' { copy_op(">");}
    | tGEQ { copy_op(">="); } | '<' { copy_op("<"); } | tLEQ { copy_op("<="); }
    | tNEQ {copy_op("!=");} | tLSHIFT {copy_op("<<");} | tRSHIFT {copy_op(">>");}
    | '+' { copy_op("+"); } | '-' { copy_op("-"); } | '*' { copy_op("*"); }
    | tSTAR { copy_op("*"); } | '/' { copy_op("/"); } | '%' { copy_op("%"); }
    | tPOW { copy_op("**"); } | tAREF { copy_op("[]"); } | '`' { copy_op("`");}
    | tUPLUS { copy_op("+"); } | tASET { copy_op("[]="); }
    | tUMINUS { copy_op("-"); } | tDSTAR { copy_op("**"); }
    | '!' { copy_op("!"); } | '~' { copy_op("~"); }
;

reswords: tLINE | tFILE | tENCODING | upBEGIN | upEND | tALIAS | tKWAND
    | tBEGIN | tBREAK | tCASE | tCLASS | tDEF | tDEFINED | tDO | tELSE | tELSIF
    | tEND | tENSURE | tFALSE | tFOR | tIN | tMODULE | tNEXT | tNIL | tKWNOT
    | tKWOR | tREDO | tRESCUE | tRETRY | tRETURN | tSELF | tSUPER | tTHEN | tTRUE
    | tUNDEF | tWHEN | tYIELD | tIF | tUNLESS | tWHILE | tUNTIL
;

arg: lhs '=' arg { $$ = alloc_node(token_assign, $1, $3); }
    | lhs '=' arg modifier_rescue arg
    {
        struct node *aux = alloc_cond(token_rescue, $5, $3, NULL);
        $$ = alloc_node(token_assign, $1, aux);
    }
    | variable tOP_ASGN arg { $$ = alloc_node(token_op_assign, $1, $3); }
    | variable tOP_ASGN arg modifier_rescue arg
    {
        struct node *aux = alloc_cond(token_rescue, $5, $3, NULL);
        $$ = alloc_node(token_op_assign, $1, aux);
    }
    | primary '[' opt_call_args rbracket tOP_ASGN arg
    {
        struct node *aux = alloc_node(token_array_value, $1, $3);
        $$ = alloc_node(token_op_assign, aux, $6);
    }
    | primary '.' base tOP_ASGN arg
    {
        struct node *aux = alloc_node(token_object, $1, $3);
        $$ = alloc_node(token_op_assign, aux, $5);
    }
    | primary '.' const tOP_ASGN arg
    {
        struct node *aux = alloc_node(token_object, $1, $3);
        $$ = alloc_node(token_op_assign, aux, $5);
    }
    | primary tCOLON2 base tOP_ASGN arg
    {
        struct node *aux = alloc_node(token_object, $1, $3);
        $$ = alloc_node(token_op_assign, aux, $5);
    }
    | primary tCOLON2 const tOP_ASGN arg
    {
        yyerror(parser, "constant re-assignment");
        $$ = NULL;
        DISPOSE3($1, $3, $5);
    }
    | tCOLON3 const tOP_ASGN arg
    {
        yyerror(parser, "constant re-assignment");
        $$ = NULL;
        DISPOSE2($2, $4);
    }
    | backref tOP_ASGN arg { $$ = alloc_node(token_assign, $1, $3); }
    | arg tDOT2 arg { $$ = alloc_node(token_dot2, $1, $3); }
    | arg tDOT3 arg { $$ = alloc_node(token_dot3, $1, $3);}
    | arg '+' arg { $$ = alloc_node(token_plus, $1, $3); }
    | arg '-' arg { $$ = alloc_node(token_minus, $1, $3);}
    | arg '*' arg { $$ = alloc_node(token_mul, $1, $3);}
    | arg '/' arg { $$ = alloc_node(token_div, $1, $3);}
    | arg '%' arg { $$ = alloc_node(token_mod, $1, $3);}
    | arg tPOW arg { $$ = alloc_node(token_pow, $1, $3);}
    | tUMINUS_NUM simple_numeric tPOW arg
    {
        struct node *aux = alloc_node(token_pow, $2, $4);
        $$ = alloc_node(token_unary_minus, aux, NULL);
    }
    | tUPLUS arg    { $$ = alloc_node(token_unary_plus, $2, NULL);    }
    | tUMINUS arg { $$ = alloc_node(token_unary_minus, $2, NULL); }
    | arg '|' arg { $$ = alloc_node(token_bit_or, $1, $3);    }
    | arg '^' arg { $$ = alloc_node(token_bit_xor, $1, $3);    }
    | arg '&' arg { $$ = alloc_node(token_bit_and, $1, $3);    }
    | arg tCMP arg    { $$ = alloc_node(token_cmp, $1, $3);    }
    | arg '>' arg    { $$ = alloc_node(token_greater, $1, $3);    }
    | arg tGEQ arg    { $$ = alloc_node(token_geq, $1, $3);    }
    | arg '<' arg    { $$ = alloc_node(token_lesser, $1, $3);    }
    | arg tLEQ arg    { $$ = alloc_node(token_leq, $1, $3);    }
    | arg tEQ arg    { $$ = alloc_node(token_eq, $1, $3);    }
    | arg tEQQ arg    { $$ = alloc_node(token_eqq, $1, $3);    }
    | arg tNEQ arg    { $$ = alloc_node(token_neq, $1, $3);    }
    | arg tMATCH arg    { $$ = alloc_node(token_match, $1, $3); }
    | arg tNMATCH arg    { $$ = alloc_node(token_nmatch, $1, $3);    }
    | '!' arg    { $$ = alloc_node(token_not, $2, NULL);    }
    | '~' arg { $$ = alloc_node(token_neg, $2, NULL);    }
    | arg tLSHIFT arg { $$ = alloc_node(token_lshift, $1, $3); }
    | arg tRSHIFT arg { $$ = alloc_node(token_rshift, $1, $3); }
    | arg tAND arg { $$ = alloc_node(token_and, $1, $3); }
    | arg tOR arg { $$ = alloc_node(token_or, $1, $3); }
    | tDEFINED opt_eol arg { $$ = alloc_node(token_defined, $3, NULL); }
    | arg '?' arg opt_eol ':' arg
    {
        $$ = alloc_cond(token_ternary, $1, $3, $6);
    }
    | primary
;

aref_args: none
    | args trailer              { $$ = $1; }
    | args ',' assocs trailer   { $$ = update_list($1, $3); }
    | assocs trailer            { $$ = $1; }
;

paren_args: '(' opt_call_args rparen { $$ = $2; }
;

opt_paren_args : none | paren_args
;

opt_call_args: none | call_args
;

call_args: command
    | args opt_block_arg { $$ = update_list($1, $2); }
    | assocs opt_block_arg
    {
        struct node *aux = alloc_node(token_hash, $1, NULL);
        $$ = update_list(aux, $2);
    }
    | args ',' assocs opt_block_arg
    {
        struct node *aux = alloc_node(token_hash, $3, NULL);
        struct node *n = update_list(aux, $4);
        $$ = concat_list($1, n);
    }
    | block_arg
;

command_args:
    {
        $<num>$ = parser->cmdarg_stack;
        CMDARG_PUSH(1);
    } call_args
    {
        parser->cmdarg_stack = $<num>$;
        $$ = $2;
    }
;

block_arg: tAMPER arg { $$ = $2; }
;

opt_block_arg: ',' block_arg { $$ = $2; }
    | ',' { $$ = NULL; }
    | none
;

args: arg
    | tSTAR arg             { $$ = $2; }
    | args ',' arg          { $$ = update_list($1, $3); }
    | args ',' tSTAR arg    { $$ = update_list($1, $4); }
;

mrhs: args ',' arg          { $$ = update_list($1, $3); }
    | args ',' tSTAR arg    { $$ = update_list($1, $4); }
    | tSTAR arg             { $$ = $2; }
;

primary: literal
    | strings
    | variable
    | backref
    | tBEGIN bodystmt tEND      { $$ = alloc_node(token_begin, $2, NULL); }
    | tLPAREN_ARG expr { lex_state = EXPR_ENDARG; } rparen   { $$ = $2; }
    | tLPAREN compstmt ')'      { $$ = $2; }
    | primary tCOLON2 const
    {
        struct node *aux = update_list($1, $3);
        $$ = alloc_node(token_method_call, aux, NULL);
    }
    | tCOLON3 const             { $$ = $2; }
    | ARRAY                     { $$ = alloc_node(token_array, NULL, NULL); }
    | tLBRACKET aref_args ']'   { $$ = alloc_node(token_array, $2, NULL); }
    | tLBRACE assoc_list '}'
    {
        $$ = alloc_node(token_hash, $2, NULL);
        discard_pos();
    }
    | tRETURN                   { $$ = alloc_node(token_return, NULL, NULL); }
    | tYIELD '(' call_args rparen { $$ = alloc_node(token_yield, $3, NULL); }
    | tYIELD '(' rparen         { $$ = alloc_node(token_yield, NULL, NULL); }
    | tYIELD                    { $$ = alloc_node(token_yield, NULL, NULL); }
    | tDEFINED opt_eol '(' expr rparen
    {
        $$ = alloc_node(token_defined, $4, NULL);
    }
    | tKWNOT '(' expr rparen    { $$ = alloc_node(token_kw_not, $3, NULL); }
    | tKWNOT '(' rparen         { $$ = alloc_node(token_kw_not, NULL, NULL); }
    | operation brace_block     { $$ = alloc_cond(token_method_call, $2, $1, NULL); }
    | method_call opt_brace_block
    {
        $$ = $1;
        $$->cond = $2;
    }
    | tLAMBDA lambda    { $$ = alloc_cond(token_method_call, $2, NULL, NULL); }
    | tIF expr then compstmt if_tail tEND
    {
        $$ = alloc_cond(token_if, $2, $4, $5);
        discard_pos(); /* tEND */
    }
    | tUNLESS expr then compstmt opt_else tEND
    {
        $$ = alloc_cond(token_unless, $2, $4, $5);
        discard_pos(); /* tEND */
    }
    | tWHILE { COND_PUSH(1); } expr do { COND_POP(); } compstmt tEND
    {
        $$ = alloc_cond(token_while, $3, $6, NULL);
        discard_pos(); /* tEND */
    }
    | tUNTIL { COND_PUSH(1); } expr do { COND_POP(); } compstmt tEND
    {
        $$ = alloc_cond(token_while, $3, $6, NULL);
        discard_pos(); /* tEND */
    }
    | tCASE expr opt_terms case_body tEND
    {
        $$ = alloc_cond(token_case, $2, $4, NULL);
        discard_pos(); /* tEND */
    }
    | tCASE opt_terms case_body tEND
    {
        $$ = alloc_node(token_case, $3, NULL);
        discard_pos(); /* tEND */
    }
    | tFOR for_var tIN { COND_PUSH(1); } expr do { COND_POP(); } compstmt tEND
    {
        $$ = alloc_cond(token_for, $5, $8, $2);
        discard_pos(); /* tEND */
    }
    | tCLASS cpath superclass
    {
        if (parser->in_def)
            yyerror(parser, "class definition in method body");
    }
    bodystmt tEND
    {
        $$ = alloc_cond(token_class, $3, $5, $2);
        pop_comment(parser, $$);
    }
    | tCLASS opt_terms tLSHIFT expr term bodystmt tEND
    {
        $$ = alloc_node(token_singleton_class, $6, $4);
        pop_comment(parser, $$);
    }
    | tMODULE cpath
    {
        if (parser->in_def)
            yyerror(parser, "module definition in method body");
    }
    bodystmt tEND
    {
        $$ = alloc_node(token_module, $4, $2);
        pop_comment(parser, $$);
    }
    | tDEF fname
    {
        parser->in_def++;
    }
    f_arglist bodystmt tEND
    {
        parser->in_def--;
        $$ = alloc_cond(token_function, $2, $5, $4);
        pop_comment(parser, $$);
    }
    | tDEF singleton dot_or_colon { lex_state = EXPR_FNAME; } fname
    {
        lex_state = EXPR_ENDFN;
        parser->in_def++;
    }
    f_arglist bodystmt tEND
    {
        $$ = alloc_node(token_object, $2, $5);
        $$ = alloc_cond(token_function, $$, $8, $7);
        $$->flags = 1; /* Class method */
        pop_comment(parser, $$);
        parser->in_def--;
    }
    | tBREAK    { $$ = alloc_node(token_break, NULL, NULL);    }
    | tNEXT     { $$ = alloc_node(token_next, NULL, NULL);     }
    | tREDO     { $$ = alloc_node(token_redo, NULL, NULL);     }
    | tRETRY    { $$ = alloc_node(token_retry, NULL, NULL);    }
;

then: term
    | tTHEN
    | term tTHEN
;

do: term | tDO_COND
;

if_tail: opt_else
    | tELSIF expr then compstmt if_tail
    {
        $$ = alloc_cond(token_if, $2, $4, $5);
    }
;

opt_else: none
    | tELSE compstmt    { $$ = alloc_node(token_if, $2, NULL);  }
;

for_var: lhs | mlhs
;

f_marg: f_norm_arg              { $$ = $1; }
    | tLPAREN f_margs rparen    { $$ = $2; }
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

block_args_tail: f_block_kwarg ',' f_kwrest opt_f_block_arg
    {
        $$ = concat_list($1, update_list($3, $4));
    }
    | f_block_kwarg opt_f_block_arg
    {
        $$ = update_list($1, $2);
    }
    | f_kwrest opt_f_block_arg
    {
        $$ = update_list($1, $2);
    }
    | f_block_arg { $$ = $1; }
;

opt_block_args_tail: ',' block_args_tail { $$ = $2; }
    | /* none */ { $$ = 0; }
;

block_param: f_arg ',' f_block_optarg ',' f_rest_arg opt_block_args_tail
    {
        $$ = concat_list($1, concat_list($3, update_list($5, $6)));
    }
    | f_arg ',' f_block_optarg ',' f_rest_arg ',' f_arg opt_block_args_tail
    {
        $$ = concat_list($1, concat_list($3, create_list($5, update_list($7, $8))));
    }
    | f_arg ',' f_block_optarg opt_block_args_tail
    {
        $$ = concat_list($1, update_list($3, $4));
    }
    | f_arg ',' f_block_optarg ',' f_arg opt_block_args_tail
    {
        $$ = concat_list($1, concat_list($3, update_list($5, $6)));
    }
    | f_arg ',' f_rest_arg opt_block_args_tail
    {
        $$ = update_list($1, update_list($3, $4));
    }
    | f_arg ',' { $$ = $1; }
    | f_arg ',' f_rest_arg ',' f_arg opt_block_args_tail
    {
        $$ = concat_list($1, concat_list($3, update_list($5, $6)));
    }
    | f_arg opt_block_args_tail { $$ = update_list($1, $2); }
    | f_block_optarg ',' f_rest_arg opt_block_args_tail
    {
        $$ = concat_list($1, update_list($3, $4));
    }
    | f_block_optarg ',' f_rest_arg ',' f_arg opt_block_args_tail
    {
        $$ = concat_list($1, create_list($3, update_list($5, $6)));
    }
    | f_block_optarg opt_block_args_tail { $$ = update_list($1, $2); }
    | f_block_optarg ',' f_arg opt_block_args_tail
    {
        $$ = concat_list($1, update_list($3, $4));
    }
    | f_rest_arg opt_block_args_tail { $$ = update_list($1, $2); }
    | f_rest_arg ',' f_arg opt_block_args_tail
    {
        $$ = create_list($1, update_list($3, $4));
    }
    | block_args_tail
;

opt_block_param: none
    | block_param_def
    {
      command_start = 1;
      $$ = $1;
    }
;

block_param_def : '|' opt_bv_decl '|'   { $$ = $2;      }
    | tOR                               { $$ = NULL;    }
    | '|' block_param opt_bv_decl '|'   { $$ = update_list($2, $3); }
;

opt_bv_decl: none
    | ';' bv_decls
    {
        if (parser->version < ruby19) {
            yywarning("Block local variables are only available in Ruby 1.9.x or higher.");
        }
        $$ = $2;
    }
;

bv_decls: bvar
    | bv_decls ',' bvar { $$ = update_list($1, $3); }
;

bvar: base
    | f_bad_arg
    {
      $$ = NULL;
      free_ast($1);
    }
;

lambda:
    {
        $<num>$ = parser->lpar_beg;
        parser->lpar_beg = ++parser->paren_nest;
    }
    f_larglist lambda_body
    {
        parser->lpar_beg = $<num>1;
        $$ = alloc_node(token_block, $3, $2);
    }
;

f_larglist: '(' f_args opt_bv_decl rparen { $$ = update_list($2, $3); }
    | f_args
;

lambda_body: tLAMBEG compstmt '}'
    {
        $$ = $2;
        discard_pos(); /* } */
        discard_pos(); /* { */
    }
    | tDO_LAMBDA compstmt tEND
    {
        $$ = $2;
        discard_pos(); /* end */
    }
;

do_block: tDO_BLOCK opt_block_param compstmt tEND
    {
        $$ = ALLOC_N(token_block, $3, $2);
        pop_start(parser, $$);
    }
;

block_call: command do_block { $1->cond = $2; $$ = $1; }
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
    }
    | primary '.' operation2 opt_paren_args
    {
        struct node *aux = update_list($1, $3);
        $$ = alloc_node(token_method_call, aux, $4);
    }
    | primary tCOLON2 operation2 paren_args
    {
        struct node *aux = update_list($1, $3);
        $$ = alloc_node(token_method_call, aux, $4);
    }
    | primary tCOLON2 operation3
    {
        struct node *aux = update_list($1, $3);
        $$ = alloc_node(token_method_call, aux, NULL);
    }
    | primary '.' paren_args
    {
        $$ = alloc_node(token_method_call, $1, $3);
    }
    | primary tCOLON2 paren_args
    {
        $$ = alloc_node(token_method_call, $1, $3);
    }
    | super paren_args { $$ = $1; $$->r = $2; }
    | super
    | primary '[' opt_call_args rbracket
    {
        $$ = alloc_node(token_array_value, $1, $3);
    }
;

opt_brace_block: none
    | brace_block
;

brace_block: '{' opt_block_param compstmt '}'
    {
        $$ = ALLOC_N(token_block, $3, $2);
        pop_start(parser, $$);
    }
    | tDO opt_block_param compstmt tEND
    {
        $$ = ALLOC_N(token_block, $3, $2);
        pop_start(parser, $$);
    }
;

case_body: tWHEN args then compstmt cases
    {
        $$ = alloc_cond(token_when, $2, $4, $5);
    }
;

cases: opt_else | case_body
;

opt_rescue: tRESCUE rescue_arg then compstmt opt_rescue
    {
         $$ = alloc_node(token_rescue, $2, $4);
         $$->ensure = $5;
    }
    | none
;

rescue_arg: exc_list exc_var
    {
        $$ = ($1 || $2) ? alloc_node(token_rescue_arg, $1, $2) : NULL;
    }
;

exc_list: arg | mrhs | none
;

exc_var: none | tASSOC lhs { $$ = $2; }
;

opt_ensure: none
    | tENSURE compstmt  { $$ = alloc_node(token_ensure, $2, NULL); }
;

literal: numeric | symbol
;

strings: string         { $$ = $1; }
    | strings string    { $$ = update_list($1, $2); }
;

string: tCHAR
    {
        $$ = alloc_node(token_string, NULL, NULL);
    }
    | tSTRING_BEG string_contents tSTRING_END
    {
        $$ = alloc_node(lex_strterm->token, $2, NULL);
        if (lex_strterm->word) {
            free(lex_strterm->word);
            lex_strterm->word = NULL;
        }
        free(lex_strterm);
        lex_strterm = NULL;
    }
;

string_contents: /* none */ { $$ = 0; }
    | string_contents string_content
    {
        if ($1 != NULL)
            $$ = update_list($1, $2);
        else
            $$ = $2;
    }
;

string_content: tSTRING_CONTENT { $$ = 0; }
    | tSTRING_DBEG
    {
        lex_state = EXPR_BEG;
        $<num>$ = parser->cond_stack;
    }
    {
        $<term>$ = lex_strterm;
        lex_strterm = NULL;
    }
    compstmt '}'
    {
        parser->cond_stack = $<num>2;
        lex_strterm = $<term>3;
        $$ = $4;
        discard_pos(); /* } */
    }
    | tSTRING_DVAR
    {
        $<term>$ = lex_strterm;
        lex_strterm = NULL;
        lex_state = EXPR_BEG;
    }
    string_dvar
    {
        lex_strterm = $<term>2;
        $$ = $3;
    }
;

string_dvar: backref
    | GLOBAL    { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags = 3; POP_STACK; }
    | IVAR      { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags = 4; POP_STACK; }
    | CVAR      { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags = 5; POP_STACK; }
;

symbol: tSYMBEG sym
    {
        $$ = $2;
        $$->kind = token_symbol;
        $$->pos.start_col--;
    }
;

sym: fname
    | strings
    | GLOBAL    { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags = 3; POP_STACK; }
    | IVAR      { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags = 4; POP_STACK; }
    | CVAR      { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags = 5; POP_STACK; }
;

numeric: simple_numeric
    | tUMINUS_NUM simple_numeric   %prec tLOWEST
    {
        $$ = alloc_node(token_unary_minus, $2, NULL);
    }
;

simple_numeric: tINTEGER        { $$ = alloc_node(token_numeric, NULL, NULL); $$->flags = 0; }
    | tFLOAT                    { $$ = alloc_node(token_numeric, NULL, NULL); $$->flags = 1; }
    | tRATIONAL
    {
        if (parser->version < ruby21) {
            yywarning("Rational literals are only available in Ruby 2.1.x or higher.");
        }
        $$ = alloc_node(token_numeric, NULL, NULL); $$->flags = 2;
    }
    | tIMAGINARY
    {
        if (parser->version < ruby21) {
            yywarning("Imaginary literals are only available in Ruby 2.1.x or higher.");
        }
        $$ = alloc_node(token_numeric, NULL, NULL); $$->flags = 3;
    }
;

variable: base
    | GLOBAL    { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags = 3; POP_STACK; }
    | IVAR      { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags = 4; POP_STACK; }
    | CVAR      { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags = 5; POP_STACK; }
    | const
    | other_vars
;

other_vars: tNIL    { $$ = alloc_node(token_nil, NULL, NULL);      }
    | tSELF         { $$ = alloc_node(token_self, NULL, NULL);     }
    | tTRUE         { $$ = alloc_node(token_true, NULL, NULL);     }
    | tFALSE        { $$ = alloc_node(token_false, NULL, NULL);    }
    | tFILE         { $$ = alloc_node(token_file, NULL, NULL);     }
    | tLINE         { $$ = alloc_node(token_line, NULL, NULL);     }
    | tENCODING     { $$ = alloc_node(token_encoding, NULL, NULL); }
;

backref: tNTH_REF   { $$ = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
;

superclass: term { $$ = NULL; }
    | '<'
    {
        lex_state = EXPR_BEG;
        command_start = 1;
    }
    expr term
    {
        $$ = $3;
    }
    | error term { yyerrok; $$ = NULL; }
;

f_arglist: '(' f_args rparen
    {
        $$ = $2;
        lex_state = EXPR_BEG;
        command_start = 1;
    }
    | f_args term
    {
        $$ = $1;
        lex_state = EXPR_BEG;
        command_start = 1;
    }
;

args_tail: f_kwarg ',' f_kwrest opt_f_block_arg
    {
        if (parser->version < ruby20) {
            yywarning("Keyword arguments are only available in Ruby 2.0.x or higher.");
        }
        $$ = concat_list($1, update_list($3, $4));
    }
    | f_kwarg opt_f_block_arg
    {
        if (parser->version < ruby20) {
            yywarning("Keyword arguments are only available in Ruby 2.0.x or higher.");
        }
        $$ = update_list($1, $2);
    }
    | f_kwrest opt_f_block_arg
    {
        if (parser->version < ruby20) {
            yywarning("Keyword arguments are only available in Ruby 2.0.x or higher.");
        }
        $$ = update_list($1, $2);
    }
    | f_block_arg
    {
        $$ = $1;
    }
;

opt_args_tail: ',' args_tail    { $$ = $2; }
    | /* none */                { $$ = 0;  }
;

f_args: f_arg ',' f_optarg ',' f_rest_arg opt_args_tail
    {
        $$ = concat_list($1, concat_list($3, concat_list($5, $6)));
    }
    | f_arg ',' f_optarg ',' f_rest_arg ',' f_arg opt_args_tail
    {
        $$ = concat_list($1, concat_list($3, create_list($5, concat_list($7, $8))));
    }
    | f_arg ',' f_optarg opt_args_tail
    {
        $$ = concat_list($1, concat_list($3, $4));
    }
    | f_arg ',' f_optarg ',' f_arg opt_args_tail
    {
        $$ = concat_list($1, concat_list($3, concat_list($5, $6)));
    }
    | f_arg ',' f_rest_arg opt_args_tail
    {
        $$ = concat_list($1, concat_list($3, $4));
    }
    | f_arg ',' f_rest_arg ',' f_arg opt_args_tail
    {
        $$ = concat_list($1, concat_list($3, concat_list($5, $6)));
    }
    | f_arg opt_args_tail
    {
        $$ = concat_list($1, $2);
    }
    | f_optarg ',' f_rest_arg opt_args_tail
    {
        $$ = concat_list($1, concat_list($3, $4));
    }
    | f_optarg ',' f_rest_arg ',' f_arg opt_args_tail
    {
        $$ = concat_list($1, create_list($3, concat_list($5, $6)));
    }
    | f_optarg opt_args_tail
    {
        $$ = concat_list($1, $2);
    }
    | f_optarg ',' f_arg opt_args_tail
    {
        $$ = concat_list($1, concat_list($3, $4));
    }
    | f_rest_arg opt_args_tail
    {
        $$ = concat_list($1, $2);
    }
    | f_rest_arg ',' f_arg opt_args_tail
    {
        $$ = create_list($1, concat_list($3, $4));
    }
    | args_tail
    | none
;

f_bad_arg: CONST    { yyerror(parser, "formal argument cannot be a constant"); $$ = 0;             }
    | IVAR          { yyerror(parser, "formal argument cannot be an instance variable"); $$ = 0;   }
    | GLOBAL        { yyerror(parser, "formal argument cannot be a global variable"); $$ = 0;      }
    | CVAR          { yyerror(parser, "formal argument cannot be a class variable"); $$ = 0;       }
;

f_norm_arg: f_bad_arg | base
;

f_arg_item: f_norm_arg
    | tLPAREN f_margs rparen { $$ = $2; }
;

f_arg: f_arg_item
    | f_arg ',' f_arg_item { $$ = concat_list($1, $3); }
;

f_kw: label arg
    {
        $$ = alloc_node(token_object, $1, $2);
        $$->flags = 4;
    }
;

f_block_kw: label primary
    {
        $$ = alloc_node(token_object, $1, $2);
        $$->flags = 4;
    }
;

f_block_kwarg: f_block_kw               { $$ = $1; }
    | f_block_kwarg ',' f_block_kw      { $$ = update_list($1, $3); }
;

f_kwarg: f_kw           { $$ = $1; }
    | f_kwarg ',' f_kw  { $$ = update_list($1, $3); }
;

kwrest_mark: tPOW | tDSTAR
;

f_kwrest: kwrest_mark base
    {
        $$ = $2;
        $$->flags = 5;
    }
    | kwrest_mark
    {
        $$ = alloc_node(token_object, NULL, NULL);
        $$->flags = 5;
    }
;

f_opt: base '='
    {
        $<num>$ = parser->column;
    }
    arg
    {
        $$ = alloc_node(token_assign, $1, $4);
        $1->flags = 3;
        $4->pos.start_col = $<num>3;
        $4->pos.end_col = parser->column;
        $4->pos.offset = parser->lex_prev - parser->blob;
    }
;

f_block_opt: base '=' primary { $$ = alloc_node(token_assign, $1, $3); }
;

f_block_optarg: f_block_opt
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
    | '(' { lex_state = EXPR_BEG; } expr rparen
    {
        if ($3 == 0)
            yyerror(parser, "can't define singleton method for ().");
        else {
            switch ($3->kind) {
                case token_string:
                case token_regexp:
                case token_numeric:
                case token_symbol:
                case token_array:
                    yyerror(parser, "can't define singleton method for literals");
            }
        }
        $$ = $3;
    }
;

const: CONST { $$ = ALLOC_N(token_object, NULL, NULL); $$->flags = 6; POP_STACK; }
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
    }
    | label arg
    {
        if (parser->version < ruby19) {
            yywarning("This syntax is only available in Ruby 1.9.x or higher.");
        }
        $$ = alloc_node(token_object, $1, $2);
    }
    | tDSTAR arg
    {
        if (parser->version < ruby20) {
            yywarning("tDSTAR token is only available in Ruby 2.0.x or higher.");
        }
        $$ = $2;
    }
;

operation: base | const
;

operation2: base
    | const
    | op
    {
        $$ = alloc_node(token_object, NULL, NULL);
        $$->name = parser->aux;
    }
;

operation3: base
    | op
    {
        $$ = alloc_node(token_object, NULL, NULL);
        $$->name = parser->aux;
    }
;

label: tKEY     { $$ = ALLOC_N(token_symbol, NULL, NULL); POP_STACK; }
;

super: tSUPER   { $$ = alloc_node(token_super, NULL, NULL); }
;

dot_or_colon: '.' | tCOLON2
;

opt_terms: /* none */ | terms
;

opt_eol: /* none */ | '\n'
;

rparen: opt_eol ')'
;

rbracket: opt_eol ']'
;

trailer: opt_eol | ','
;

term: ';' {yyerrok;} | '\n'
;

terms: term | terms ';' {yyerrok;}
;

none: /* none */ { $$ = NULL; }
;

%%
#undef parser
#undef yylex

#include <ctype.h>
#include "hash.c"


/* Let's define some useful macros :D */

#define _unused_(c) (void) c;
#define multiline_comment(c) (*(c+1) == 'b' && *(c+2) == 'e' && *(c+3) == 'g' && *(c+4) == 'i' && *(c+5) == 'n')
#define multiline_end(c) (*c == '=' && *(c+1) == 'e' && *(c+2) == 'n' && *(c+3) == 'd')
#define not_sep(c) (is_valid_identifier(c) || is_utf8_digit(c) || *c == '_')
#define is_blank(c) (c == ' ' || c == '\t')
#define SWAP(a, b, aux) { aux = a; a = b; b = aux; }
#define is_special_method(buffer) ((strlen(buffer) > 4) && buffer[0] == '_' && \
                                                                buffer[1] == '_' && buffer[strlen(buffer) - 2] == '_' && \
                                                                buffer[strlen(buffer) - 1] == '_')
#define IS_EOF() ((unsigned int) (parser->lex_p - parser->blob) >= parser->length)
#define IS_ARG() IS_lex_state(EXPR_ARG_ANY)
#define IS_END() IS_lex_state(EXPR_END_ANY)
#define IS_BEG() IS_lex_state(EXPR_BEG_ANY)
#define IS_SPCARG(c) (IS_ARG() && space_seen && !isspace(c))
#define IS_LABEL_POSSIBLE() ((IS_lex_state(EXPR_BEG | EXPR_ENDFN) && !cmd_state) || IS_ARG())
#define IS_LABEL_SUFFIX() (*parser->lex_p == ':' && *(parser->lex_p + 1) != ':')
#define IS_AFTER_OPERATOR() IS_lex_state(EXPR_FNAME | EXPR_DOT)


/* Initialize the parser */
static void init_parser(struct parser_t *parser)
{
    parser->content_given = 0;
    parser->ast = NULL;
    parser->blob = NULL;
    parser->lex_p = NULL;
    parser->lex_prev = NULL;
    parser->lex_prevc = 0;
    parser->lex_pend = NULL;
    parser->line_pend = 0;
    parser->column_pend = 0;
    parser->here_found = 0;
    parser->eof_reached = 0;
    parser->cond_stack = 0;
    parser->cmdarg_stack = 0;
    parser->in_def = 0;
    parser->lpar_beg = 0;
    parser->paren_nest = 0;
    parser->sp = 0;
    parser->line = 1;
    parser->column = 0;
    parser->pos_stack = (struct pos_t *) malloc(SSIZE * sizeof(struct pos_t));
    parser->stack_scale = 0;
    parser->pos_size = 0;
    parser->errors = NULL;
    parser->last_error = NULL;
    parser->warning = 0;
    parser->unrecoverable = 0;
    parser->last_comment.comment = NULL;
    parser->last_comment.line = 0;
    parser->comment_index = 0;
    command_start = 1;
    lex_strterm = NULL;
    lex_state = EXPR_BEG;
}

/* Free the parser */
static void free_parser(struct parser_t *parser)
{
    int index;

    for (index = 0; index < parser->sp; index++)
        free(parser->stack[index]);
    if (parser->pos_stack != NULL)
        free(parser->pos_stack);
    if (lex_strterm && lex_strterm->word)
        free(lex_strterm->word);
    if (parser->last_comment.comment)
      free(parser->last_comment.comment);
    if (!parser->content_given)
        free(parser->blob);
}

/* Read the file's source code and allocate it for further inspection. */
static int retrieve_source(struct parser_t *p, const char *path)
{
    int length;

    /* Open specified file */
    FILE *fd = fopen(path, "r");
    if (!fd) {
        fprintf(stderr, "Cannot open file: %s\n", path);
        return 0;
    }

    fseek(fd, 0, SEEK_END);
    length = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    if (!length)
        return 0;
    p->blob = (char *) malloc(sizeof(char) * length);

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
    p->lex_p = p->blob;
    fclose(fd);
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
static int utf8_charsize(const char *s)
{
    int size = 0;
    int i = 0;

    do {
        i++;
        size++;
    } while (s[i] && !is_utf(s[i]));
    return size;
}

static int is_utf8_alpha(const char *str)
{
    return is_special(str) ? 1 : isalpha(*str);
}

static int is_utf8_alnum(const char *str)
{
    return is_special(str) ? 1 : isalnum(*str);
}

static int is_utf8_graph(const char *str)
{
    return is_special(str) ? 1 : isgraph(*str);
}

static int is_utf8_digit(const char *str)
{
    return is_special(str) ? 0 : isdigit(*str);
}

/* Check that the given parameter points to a valid identifier */
static int is_valid_identifier(const char *c)
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

/* Get the next character and move the lexer forward. */
static int parser_nextc(struct parser_t *parser)
{
    int c;

    if (parser->eof_reached || IS_EOF())
        return -1;

    parser->lex_prev = parser->lex_p;
    parser->lex_prevc = parser->column;
    c = (unsigned char) *parser->lex_p++;
    if (c == '\n') {
        if (parser->here_found) {
            parser->line = parser->line_pend;
            parser->column = parser->column_pend;
            parser->lex_p = parser->lex_pend + 1;
            parser->here_found = 0;
        }
        parser->line++;
        parser->column = -1;
    }
    parser->column++;
    return c;
}
#define nextc() parser_nextc(parser)

/* Move the lexer backwards. */
static void parser_pushback(struct parser_t *parser)
{
    parser->column--;
    parser->lex_p--;
    if (*parser->lex_p == '\n') {
        parser->line--;
        parser->column = parser->lex_prevc;
    }
}
#define pushback() parser_pushback(parser)

/* It parses a heredoc identifier and sets a new lex_strterm */
static int parse_heredoc_identifier(struct parser_t *parser)
{
    char *buffer, *ptr;
    int count = SSIZE, scale = 0;
    char c = nextc();
    unsigned char quote_seen = 0, term = ' ';
    unsigned char dash_seen = 0;

    /* Check for <<- case */
    if (c == '-') {
        dash_seen = 1;
        c = nextc();
    }
    /* And now surrounding quotes */
    if (c == '\'' || c == '"' || c == '`') {
        term = c;
        c = nextc();
        quote_seen = 1;
    }
    if (!quote_seen && !is_identchar(parser->lex_prev)) {
        if (dash_seen)
            pushback();
        return 0;
    }

    buffer = (char *) malloc(SSIZE * sizeof(char));
    ptr = buffer;
    for (;;) {
        /* If quote was seen, anything except the term is accepted */
        if (quote_seen) {
            if (c == term || !is_utf8_graph(parser->lex_prev))
                break;
        } else if (!is_identchar(parser->lex_prev))
            break;
        if (!count) {
            scale++;
            buffer = (char *) realloc(buffer, (SSIZE << scale) * sizeof(char));
        }
        *ptr++ = c;
        c = nextc();
        if (c < 0) {
            free(buffer);
            yyerror(parser, "unterminated here document identifier");
            return 0;
        }
    }
    *ptr = '\0';
    pushback();

    lex_strterm = (struct term_t *) malloc(sizeof(struct term_t));
    lex_strterm->term = 1;
    lex_strterm->can_embed = dash_seen;
    lex_strterm->word = buffer;
    lex_strterm->token = token_heredoc;
    lex_strterm->nestable = 0;
    lex_strterm->paren = 0;
    parser->lex_pend = parser->lex_p + quote_seen;
    parser->line_pend = parser->line;
    parser->column_pend = parser->column;
    return 1;
}

/* Let's parse a heredoc */
static int parse_heredoc(struct parser_t *parser)
{
    int length = strlen(lex_strterm->word);
    char aux[length];
    char c = nextc();
    int i = 0;
    int ax = 0;

    /* Skip until next line */
    while (c != -1 && c != '\n')
        c = nextc();

    do {
        c = nextc();

        /* Ignore initial spaces if dash seen */
        if (i == 0 && lex_strterm->can_embed)
            while (isspace(c) || c == '\n')
                c = nextc();
        if (c == '#' && *(parser->lex_prev - 1) != '\\') {
            c = nextc();
            switch (c) {
                case '$': case '@':
                    parser->column -= ax;
                    pushback();
                    return tSTRING_DVAR;
                case '{':
                    parser->column -= ax;
                    command_start = 1;
                    return tSTRING_DBEG;
            }
        }
        aux[i] = c;
        if (c == '\n') {
            if ((length == i) && !strncmp(lex_strterm->word, aux, i)) {
                pushback();
                return tSTRING_END;
            }
            i = -1;
        } else
            ax += utf8_charsize(parser->lex_prev) - 1;
        if (i >= length)
            i = -1;
        i++;
    } while (c != -1);

    parser->eof_reached = 1;
    if (lex_strterm->word) {
        free(lex_strterm->word);
        lex_strterm->word = NULL;
    }
    free(lex_strterm);
    lex_strterm = NULL;
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

/* Guess the token kind of the shortcut based on the given character */
static int guess_kind(struct parser_t *parser, char c)
{
    if (!isalpha(c))
        return token_string;

    switch (c) {
        case 'Q': case 'q': case 'x': return token_string;
        case 'I': case 'i':
            if (parser->version < ruby20) {
                yywarning("This shortcut is only available in Ruby 2.0.x or higher.");
            }
        case 'W': case 'w': return token_array;
        case 's': return token_symbol;
        case 'r': return token_regexp;
        default:
            yyerror(parser, "unknown type of %string");
            return 0;
    }
}

/* Push name to the stack */
static void push_stack(struct parser_t *parser, const char *buf)
{
    parser->stack[parser->sp] = strdup(buf);
    parser->sp++;
}

/* Pop name from the stack. */
static void pop_stack(struct parser_t *parser, struct node *n)
{
    if (n != NULL)
        n->name = parser->stack[0];
    parser->stack[0] = parser->stack[1];
    parser->stack[1] = NULL;
    parser->sp--;
}

/* Push a position into the stack of positions */
static void push_pos(struct parser_t *parser, struct pos_t tokp)
{
    int scale = SSIZE * parser->stack_scale;

    parser->pos_size++;
    if (parser->pos_size > SSIZE) {
        parser->pos_size = 1;
        parser->stack_scale++;
        scale += SSIZE;
        parser->pos_stack = (struct pos_t *) realloc(parser->pos_stack, scale * sizeof(struct pos_t));
    }
    parser->pos_stack[parser->pos_size + scale - 1] = tokp;
}

/* Pop a position from the stack of positions and assign to the given node */
static void pop_pos(struct parser_t *parser, struct node *n)
{
    int scale = SSIZE * parser->stack_scale;
    int pos = parser->pos_size - 1 + scale;
    struct pos_t tokp = parser->pos_stack[pos];

    if (n != NULL) {
        n->pos.start_line = tokp.start_line;
        n->pos.start_col = tokp.start_col;
        n->pos.end_line = tokp.end_line;
        n->pos.end_col = tokp.end_col;
        n->pos.offset = tokp.offset;
    }
    parser->pos_size--;
    if (parser->pos_size == 0 && parser->stack_scale > 0) {
        parser->stack_scale--;
        parser->pos_size = SSIZE;
        scale -= SSIZE;
        parser->pos_stack = (struct pos_t *) realloc(parser->pos_stack, scale * sizeof(struct pos_t));
    }
}

/* Like pop_pos but it just copies the start position to the given node */
static void pop_start(struct parser_t *parser, struct node *n)
{
    n->pos.start_line = parser->pos_stack[parser->pos_size - 1].start_line;
    n->pos.start_col = parser->pos_stack[parser->pos_size - 1].start_col;
    pop_pos(parser, NULL);
}

/* Like pop_pos but it just copies the end position to the given node */
static void pop_end(struct parser_t *parser, struct node *n)
{
    n->pos.end_line = parser->pos_stack[parser->pos_size - 1].start_line;
    n->pos.end_col = parser->pos_stack[parser->pos_size - 1].start_col;
    pop_pos(parser, NULL);
}

/* Push the last comment that we've found to the stack of comments. */
static void push_last_comment(struct parser_t *parser)
{
    if ((parser->line - parser->last_comment.line) < 2)
        parser->comment_stack[parser->comment_index] = parser->last_comment.comment;
    else {
        parser->comment_stack[parser->comment_index] = NULL;
        if (parser->last_comment.comment)
            free(parser->last_comment.comment);
    }
    parser->comment_index++;
    parser->last_comment.comment = NULL;
}

/* Pop a comment from the stack of comments and assign it to the given node */
static void pop_comment(struct parser_t *parser, struct node *n)
{
    if (parser->comment_index > 0) {
        parser->comment_index--;
        n->comment = parser->comment_stack[parser->comment_index];
    }
}

#define __check_buffer_size(N) { \
  if (count > N) { \
    count = 0; \
    scale++; \
    buffer = (char *) realloc(buffer, scale * 1024); \
  } \
}

/* Store the given comment as the last comment seen */
static void store_comment(struct parser_t *parser, char *comment)
{
    if (parser->last_comment.comment != NULL)
        free(parser->last_comment.comment);
    parser->last_comment.comment = comment;
    parser->last_comment.line = parser->line;
}

/* Check if the given parameter points to an indented comment */
static int is_indented_comment(struct parser_t *parser)
{
    char *c = parser->lex_prev;
    char *original = c;

    for (; *c == ' ' || *c == '\t'; ++c);
    parser->lex_p += (c - original);
    parser->column += (c - original);
    return (*c == '#');
}

/* Read a comment and store it if possible */
static void set_comment(struct parser_t *parser)
{
    int c, count = 0, scale = 0;
    char *buffer = (char *) malloc(LSIZE);

    for (;; ++count) {
        if (c != '#' && !is_indented_comment(parser))
            break;
        c = *(parser->lex_p - 1);
        while (c == '#' && c != -1)
            c = nextc();
        if (c != '\n') {
            for (; c != -1; count++) {
                __check_buffer_size(1000);
                buffer[count] = c;
                c = nextc();
                if (c == '\n') {
                    buffer[++count] = c;
                    break;
                }
            }
        } else
            buffer[count] = c;
        c = nextc();
    }

    if (c != -1)
        pushback();
    buffer[count] = '\0';
    store_comment(parser, buffer);
}

/* Parse a string or a regexp */
static int parse_string(struct parser_t *parser)
{
    register int c = *parser->lex_p;
    int next = *(parser->lex_p + 1);

    if (c == '\\' && (next == '\\' || next == lex_strterm->term || next == lex_strterm->paren)) {
        parser->lex_p += 2;
        parser->column += 2;
        return tSTRING_CONTENT;
    }

    if (c == lex_strterm->term) {
        nextc();
        if (lex_strterm->nestable) {
            lex_strterm->nest--;
            if (lex_strterm->nest > 0)
                return tSTRING_CONTENT;
        }
        return tSTRING_END;
    } else if (lex_strterm->nestable && lex_strterm->paren == c) {
        lex_strterm->nest++;
        nextc();
        return tSTRING_CONTENT;
    }

    if (IS_EOF()) {
        parser->eof_reached = 1;
        yyerror(parser, "unterminated string meets end of file");
        free(lex_strterm);
        lex_strterm = NULL;
        return token_invalid;
    }

    if (lex_strterm->can_embed && c == '#' && *(parser->lex_prev) != '\\') {
        nextc();
        switch (*parser->lex_p) {
            case '$': case '@':
                return tSTRING_DVAR;
            case '{':
                c = nextc();
                command_start = 1;
                return tSTRING_DBEG;
        }
        pushback();
    }

    /* Re-using the next and the c variables */
    next = utf8_charsize(parser->lex_p);
    c = next - 1;
    while (next-- > 0) {
        if (nextc() < 0) {
            parser->eof_reached = 1;
            free(lex_strterm);
            lex_strterm = NULL;
            return token_invalid;
        }
    }
    parser->column -= c;
    return tSTRING_CONTENT;
}

/* Regular expressions can end with some options, read them */
static void parse_re_options(struct parser_t *parser)
{
    char aux[64];
    int c = *parser->lex_p;

    while (isalpha(c)) {
        if (c != 'i' && c != 'm' && c != 'x' && c != 'o' &&
            c != 'u' && c != 'e' && c != 's' && c != 'n') {
            sprintf(aux, "unknown regexp option - %c", c);
            yyerror(parser, aux);
            return;
        }
        c = nextc();
    }
    pushback();
}

/* Standard warning for ambiguous arguments */
static void arg_ambiguous_gen(struct parser_t *parser)
{
    yywarning("ambiguous first argument; put parentheses or even spaces");
}
#define arg_ambiguous() (arg_ambiguous_gen(parser), 1)

/*
 * This is the lexer. It reads the source code (blob) and provides tokens to
 * the parser. It also updates the necessary flags.
 */
static int parser_yylex(struct parser_t *parser)
{
    register int c;
    int bc = 0;
    char *cp;
    char lexbuf[SSIZE];
    unsigned char space_seen = 0;
    int cmd_state;
    struct pos_t tokp = {-1, -1, -1, -1, 0};

    /* Check for string terminations: string, regexp, heredoc, shortcut */
    if (lex_strterm) {
        if (lex_strterm->token == token_heredoc) {
            c = parse_heredoc(parser);
            if (c == tSTRING_END) {
                tokp.end_line = parser->line;
                tokp.end_col = parser->column;
                SWAP(parser->line, parser->line_pend, bc);
                SWAP(parser->column, parser->column_pend, bc);
                SWAP(parser->lex_p, parser->lex_pend, cp);
                parser->here_found = 1;
                lex_state = EXPR_END;

            }
        } else {
            c = parse_string(parser);
            if (c == tSTRING_END) {
                if (lex_strterm->token == token_regexp && isalpha(*parser->lex_p))
                    parse_re_options(parser);
                lex_state = EXPR_END;
            }
        }
        return c;
    }

    cmd_state = command_start;
    command_start = 0;
retry:
    c = nextc();

    tokp.start_line = parser->line;
    tokp.start_col = parser->column - 1;

    /* Check numeric values here instead of entering the main switch */
    if (isdigit(c)) {
        cp = lexbuf;
        goto tnum;
    }

    switch (c) {
        case '\0':      /* NULL */
        case EOF:       /* end of script */
            parser->eof_reached = 1;
            return token_invalid;

        /* white spaces */
        case ' ': case '\t': case '\f': case '\r':
        case '\13': /* vertical tab */
            space_seen = 1;
            goto retry;
        case '#':
            set_comment(parser);
        case '\n':
            if (IS_lex_state(EXPR_BEG | EXPR_VALUE | EXPR_CLASS | EXPR_FNAME | EXPR_DOT))
                goto retry;
            CMDARG_PUSH(0);
            lex_state = EXPR_BEG;
            command_start = 1;
            return '\n';
        case '=':
            lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
            bc = nextc();
            if (bc == '=') {
                if (nextc() == '=')
                    return tEQQ;
                pushback();
                return tEQ;
            }
            if (bc == '~')
                return tMATCH;
            if (bc == '>')
                return tASSOC;
            if (multiline_comment(parser->lex_prev - 1)) {
                parser->column += 4;
                parser->lex_p += 4;
                while (!multiline_end(parser->lex_prev))
                    nextc();
                parser->column += 3;
                parser->lex_p += 3;
                bc = 0;
                goto retry;
            }
            break;
        case '[':
            parser->paren_nest++;
            if (IS_AFTER_OPERATOR()) {
                lex_state = EXPR_ARG;
                bc = nextc();
                if (bc == ']') {
                    if (nextc() == '=')
                        return tASET;
                    c = tAREF;
                }
                break;
            } else if (IS_BEG())
                c = tLBRACKET;
            else if (IS_ARG() && space_seen)
                c = tLBRACKET;
            lex_state = EXPR_BEG;
            COND_PUSH(0);
            CMDARG_PUSH(0);
            return c;
        case ']':
            parser->paren_nest--;
            lex_state = EXPR_ENDARG;
            CMDARG_LEXPOP();
            COND_LEXPOP();
            return c;
        case '<':
            bc = nextc();
            if (bc == '<' && !IS_lex_state(EXPR_DOT | EXPR_CLASS) &&
                !IS_END() && (!IS_ARG() || space_seen)) {
                if (parse_heredoc_identifier(parser))
                    return tSTRING_BEG;
                pushback();
            }
            if (IS_AFTER_OPERATOR())
                lex_state = EXPR_ARG;
            else {
                if (IS_lex_state(EXPR_CLASS))
                    command_start = 1;
                lex_state = EXPR_BEG;
            }
            if (bc == '=') {
                if (nextc() == '>')
                    return tCMP;
                pushback();
                return tLEQ;
            }
            if (bc == '<') {
                if (nextc() == '=') {
                    lex_state = EXPR_BEG;
                    return tOP_ASGN;
                }
                c = tLSHIFT;
            }
            break;
        case '>':
            lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
            bc = nextc();
            if (bc == '=')
                return tGEQ;
            if (bc == '>') {
                if (nextc() == '=') {
                    lex_state = EXPR_BEG;
                    return tOP_ASGN;
                }
                c = tRSHIFT;
            }
            break;
        case '!':
            bc = nextc();
            if (IS_AFTER_OPERATOR()) {
                lex_state = EXPR_ARG;
                if (bc == '@')
                    return '!';
            } else
                lex_state = EXPR_BEG;
            if (bc == '=')
                return tNEQ;
            if (bc == '~')
                return tNMATCH;
            break;
        case '+':
            bc = nextc();
            if (IS_AFTER_OPERATOR()) {
                lex_state = EXPR_ARG;
                if (bc == '@')
                    return tUPLUS;
                pushback();
                return '+';
            }
            if (bc == '=') {
                lex_state = EXPR_BEG;
                return tOP_ASGN;
            }
            if (IS_BEG() || (IS_SPCARG(bc) && arg_ambiguous())) {
                lex_state = EXPR_BEG;
                pushback();
                return tUPLUS;
            }
            lex_state = EXPR_BEG;
            break;
        case '-':
            bc = nextc();
            if (IS_AFTER_OPERATOR()) {
                lex_state = EXPR_ARG;
                if (bc == '@')
                    return tUMINUS;
                pushback();
                return '-';
            }
            if (bc == '=') {
                lex_state = EXPR_BEG;
                return tOP_ASGN;
            }
            if (bc == '>') {
                lex_state = EXPR_ENDFN;
                return tLAMBDA;
            }
            if (IS_BEG() || (IS_SPCARG(bc) && arg_ambiguous())) {
                lex_state = EXPR_BEG;
                pushback();
                if (bc != -1 && isdigit(bc))
                    return tUMINUS_NUM;
                return tUMINUS;
            }
            lex_state = EXPR_BEG;
            break;
        case '*':
            bc = nextc();
            if (bc == '=') {
                lex_state = EXPR_BEG;
                return tOP_ASGN;
            }
            if (bc == '*') {
                bc = nextc();
                if (bc == '=') {
                    lex_state = EXPR_BEG;
                    return tOP_ASGN;
                }
                pushback();
                if (IS_SPCARG(bc)) {
                    yywarning("`**' interpreted as argument prefix");
                    c = tDSTAR;
                } else if (IS_BEG())
                    c = tDSTAR;
                else
                    c = tPOW;
                lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
                return c;
            }
            if (IS_SPCARG(bc)) {
                yywarning("`*' interpreted as argument prefix");
                c = tSTAR;
            } else if (IS_BEG())
                c = tSTAR;
            lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
            break;
        case '/':
            if (IS_lex_state(EXPR_BEG_ANY)) {
            regexp:
                lex_strterm = (struct term_t *) malloc(sizeof(struct term_t));
                lex_strterm->term = c;
                lex_strterm->can_embed = 1;
                lex_strterm->token = token_regexp;
                lex_strterm->word = NULL;
                lex_strterm->nestable = 0;
                lex_strterm->paren = 0;
                return tSTRING_BEG;
            }
            bc = nextc();
            if (bc == '=') {
                lex_state = EXPR_BEG;
                return tOP_ASGN;
            }
            pushback();
            if (IS_SPCARG(bc)) {
                arg_ambiguous_gen(parser);
                goto regexp;
            }
            lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
            return c;
        case '%':
            bc = nextc();
            if (IS_lex_state(EXPR_BEG_ANY) || IS_SPCARG(bc)) {
                lex_strterm = (struct term_t *) malloc(sizeof(struct term_t));
                lex_strterm->token = guess_kind(parser, bc);
                if (isalpha(bc))
                    bc = nextc();
                lex_strterm->term = closing_char(bc);
                lex_strterm->can_embed = 1;
                lex_strterm->word = NULL;
                lex_strterm->paren = bc;
                lex_strterm->nestable = (bc != lex_strterm->term);
                lex_strterm->nest = 1;
                return tSTRING_BEG;
            }
            if (bc == '=') {
                lex_state = EXPR_BEG;
                return tOP_ASGN;
            }
            lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
            break;
        case '&':
            bc = nextc();
            if (bc == '&') {
                lex_state = EXPR_BEG;
                if (nextc() == '=')
                    return tOP_ASGN;
                pushback();
                return tAND;
            }
            if (bc == '=') {
                lex_state = EXPR_BEG;
                return tOP_ASGN;
            }
            if (IS_SPCARG(bc)) {
                yywarning("`&' interpreted as argument prefix");
                c = tAMPER;
            } else if (IS_BEG())
                c = tAMPER;
            lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
            break;
        case '|':
            bc = nextc();
            if (bc == '|') {
                lex_state = EXPR_BEG;
                if (nextc() == '=')
                    return tOP_ASGN;
                pushback();
                return tOR;
            }
            if (bc == '=') {
                lex_state = EXPR_BEG;
                return tOP_ASGN;
            }
            lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
            break;
        case '.':
            lex_state = EXPR_BEG;
            bc = nextc();
            if (bc == '.') {
                if (nextc() == '.')
                    return tDOT3;
                pushback();
                return tDOT2;
            }
            lex_state = EXPR_DOT;
            break;
        case ':':
            bc = nextc();
            if (bc == ':') {
                if (IS_BEG() || IS_lex_state(EXPR_CLASS) || IS_SPCARG(-1)) {
                    lex_state = EXPR_BEG;
                    return tCOLON3;
                }
                lex_state = EXPR_DOT;
                return tCOLON2;
            }
            if (IS_END() || isspace(bc)) {
                lex_state = EXPR_BEG;
                break;
            }
            lex_state = EXPR_FNAME;
            pushback();
            return tSYMBEG;
        case '^':
            if (nextc() == '=') {
                lex_state = EXPR_BEG;
                return tOP_ASGN;
            }
            lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
            break;
        case ';':
            command_start = 1;
            /* fallthrough */
        case ',':
            lex_state = EXPR_BEG;
            return c;
        case '?':
            if (IS_END()) {
                lex_state = EXPR_VALUE;
                return c;
            }
            bc = nextc();
            if (isspace(bc)) {
                lex_state = EXPR_VALUE;
                break;
            }
            if (bc == '\\')
                nextc();
            if (IS_BEG()) {
                lex_state = EXPR_END;
                return tCHAR;
            }
            if (is_blank(*parser->lex_p) || *parser->lex_p == ':') {
                lex_state = EXPR_VALUE;
                break;
            }
            lex_state = EXPR_END;
            return tCHAR;
        case '`':
            if (IS_lex_state(EXPR_FNAME)) {
                lex_state = EXPR_ENDFN;
                return c;
            }
            if (IS_lex_state(EXPR_DOT)) {
                lex_state = (cmd_state) ? EXPR_CMDARG : EXPR_ARG;
                return c;
            }
            /* fallthrough */
        case '"':
            space_seen = 1;
            /* fallthrough */
        case '\'':
            lex_strterm = (struct term_t *) malloc(sizeof(struct term_t));
            lex_strterm->term = c;
            lex_strterm->can_embed = space_seen;
            lex_strterm->token = token_string;
            lex_strterm->word = NULL;
            lex_strterm->nestable = 0;
            lex_strterm->paren = 0;
            return tSTRING_BEG;
        case '\\':
            if (nextc() == '\n') {
                space_seen = 1;
                goto retry;
            }
            pushback();
            return c;
        case '(':
            if (IS_BEG())
                c = tLPAREN;
            else if (IS_SPCARG(-1))
                c = tLPAREN_ARG;
            parser->paren_nest++;
            lex_state = EXPR_BEG;
            COND_PUSH(0);
            CMDARG_PUSH(0);
            return c;
        case ')':
            parser->paren_nest--;
            lex_state = EXPR_ENDFN;
            CMDARG_LEXPOP();
            COND_LEXPOP();
            return c;
        case '{':
            if (parser->lpar_beg && parser->lpar_beg == parser->paren_nest) {
                lex_state = EXPR_BEG;
                parser->lpar_beg = 0;
                parser->paren_nest--;
                COND_PUSH(0);
                CMDARG_PUSH(0);
                push_pos(parser, tokp);
                if (parser->version < ruby19) {
                    yywarning("\"->\" syntax is only available in Ruby 1.9.x or higher.");
                }
                return tLAMBEG; /* this is a lambda ->() {} construction */
            }
            if (IS_ARG() || IS_lex_state(EXPR_END | EXPR_ENDFN))
                c = '{';
            else if (IS_lex_state(EXPR_ENDARG))
                c = tLBRACE_ARG; /* block (expr) */
            else
                c = tLBRACE; /* smells like a hash */
            COND_PUSH(0);
            CMDARG_PUSH(0);
            lex_state = EXPR_BEG;
            if (c != tLBRACE) {
                push_pos(parser, tokp);
                command_start = 1;
            }
            return c; /* block (primary) */
        case '}':
            CMDARG_LEXPOP();
            COND_LEXPOP();
            tokp.end_line = parser->line;
            tokp.end_col = parser->column;
            push_pos(parser, tokp);
            lex_state = EXPR_ENDARG;
            return c;
        case '@':
            cp = lexbuf;
            *cp++ = c;
            c = nextc();
            if (c != '@') {
                bc = IVAR;
            } else {
                *cp++ = c;
                c = nextc();
                bc = CVAR;
            }
            goto talpha;
        case '$':
            tokp.end_line = parser->line;
            cp = lexbuf;
            *cp++ = c;
            bc = nextc();
            switch (bc) {
                case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                    c = bc;
                    while (isdigit(c)) {
                        *cp++ = c;
                        c = nextc();
                    }
                    *cp = '\0';
                    pushback();
                    c = tNTH_REF;
                    break;
                case '~': case '*': case '$': case '?': case '!': case '@':
                case '/': case '\\': case ';': case ',': case '.': case '=':
                case ':': case '<': case '>': case '\"':
                case '&': case '`': case '\'': case '+':
                case '0':
                    c = GLOBAL;
                    *cp++ = bc;
                    *cp = '\0';
                    break;
                case '-':
                    c = nextc();
                    *cp++ = bc;
                    bc = GLOBAL;
                    goto talpha;
                default:
                    c = bc;
                    bc = GLOBAL;
                    goto talpha;
            }
            lex_state = EXPR_END;
            tokp.end_col = parser->column;
            push_pos(parser, tokp);
            push_stack(parser, lexbuf);
            return c;
        case '~':
            if (IS_AFTER_OPERATOR()) {
                bc = nextc();
                if (bc != '@')
                    pushback();
                lex_state = EXPR_ARG;
            } else
                lex_state = EXPR_BEG;
            return c;
        default:
            cp = lexbuf;
            goto talpha;
    }
    pushback();
    return c;

talpha:
    {
        int step = 0;
        int ax = 0;

        /* It's time to parse the word */
        while (not_sep(parser->lex_prev)) {
            step = utf8_charsize(parser->lex_prev);
            ax += step - 1;
            while (step-- > 0) {
                *cp++ = c;
                c = nextc();
            }
            if (c < 0) {
                parser->eof_reached = 1;
                break;
            }
        }
        *cp = '\0';
        parser->column -= ax;
        tokp.end_line = tokp.start_line;
        tokp.end_col = parser->lex_prevc - ax;
        pushback();

        /* IVAR, CVAR, GLOBAL */
        if (bc > 0) {
            push_pos(parser, tokp);
            push_stack(parser, lexbuf);
            lex_state = EXPR_END;
            return bc;
        }

        /* Check for '!', '?' and '=' at the end of the word */
        if (c == '!' || c == '?') {
            *cp++ = c;
            *cp = '\0';
            tokp.end_col++;
            nextc();
            c = BASE;
        } else {
            c = 0;
            if (IS_lex_state(EXPR_FNAME)) {
                bc = nextc();
                if (bc == '=') {
                    bc = nextc();
                    if (bc != '>') {
                        *cp++ = '=';
                        *cp = '\0';
                        tokp.end_col++;
                        c = BASE;
                    } else
                        pushback();
                }
                pushback();
            }
            c = (!c && isupper(lexbuf[0])) ? CONST : BASE;
        }

        /* Check if this is just a hash key. */
        if (IS_LABEL_POSSIBLE() && IS_LABEL_SUFFIX()) {
            lex_state = EXPR_BEG;
            nextc();
            push_stack(parser, lexbuf);
            push_pos(parser, tokp);
            return tKEY;
        }

        /* Check if this is a keyword */
        const struct kwtable *kw = NULL;
        if (!IS_lex_state(EXPR_DOT)) {
            kw = rb_reserved_word(lexbuf, cp - lexbuf);
            if (kw) {
                enum lex_state_e state = lex_state;
                lex_state = kw->state;
                if (state == EXPR_FNAME)
                    return kw->id[0];
                if (lex_state == EXPR_BEG)
                    command_start = 1;
                switch (kw->id[0]) {
                    case tCLASS: case tMODULE: case tDEF:
                        push_last_comment(parser);
                        break;
                    case tDO:
                        if (parser->lpar_beg && parser->lpar_beg == parser->paren_nest) {
                            parser->lpar_beg = 0;
                            parser->paren_nest--;
                            return tDO_LAMBDA;
                        }
                        if (COND_P())
                            return tDO_COND;
                        push_pos(parser, tokp);
                        if (CMDARG_P() && state != EXPR_CMDARG)
                            return tDO_BLOCK;
                        return tDO;
                    case tEND:
                        push_pos(parser, tokp);
                        break;
                }
                if (IS_lex_state_for(state, EXPR_BEG | EXPR_VALUE))
                    return kw->id[0];
                else {
                    if (kw->id[0] != kw->id[1])
                        lex_state = EXPR_BEG;
                    return kw->id[1];
                }
            }
        }

        /* Maybe this is just some special method */
        if (is_special_method(lexbuf)) {
            if (!strcmp(lexbuf, "__END__")) {
                parser->eof_reached = 1;
                return tpEND;
            }
        }

        /* If this is not a keyword, push its position and the name */
        if (!kw) {
            push_stack(parser, lexbuf);
            push_pos(parser, tokp);
        }

        /* Update the state of the lexer */
        if (IS_lex_state(EXPR_BEG_ANY | EXPR_ARG_ANY | EXPR_DOT))
            lex_state = (cmd_state) ? EXPR_CMDARG : EXPR_ARG;
        else if (lex_state == EXPR_FNAME)
            lex_state = EXPR_ENDFN;
        else
            lex_state = EXPR_END;
        return c;
    }

tnum:
    {
        char hex, bin, has_point, aux;
        hex = bin = has_point = aux = 0;

        lex_state = EXPR_END;
        if (c == '0') {
            bc = nextc();
            if (toupper(bc) == 'X') {
                hex = 1;
                c = nextc();
            } else if (toupper(bc) == 'B') {
                bin = 1;
                c = nextc();
            }
            pushback();
        }
        while (c > 0 && ((isdigit(c) && !bin) || (!hex && !bin && !has_point && c == '.')
                    || (hex && toupper(c) >= 'A' && toupper(c) < 'G')
                    || (bin && (c == '1' || c == '0')) || c == '_')) {
            if (c == '.') {
                if (!isdigit(*parser->lex_p)) {
                    tokp.end_line = parser->line;
                    tokp.end_col = parser->column - 1;
                    pushback();
                    return tINTEGER;
                }
                has_point = 1;
            }
            aux = 1;
            c = nextc();
        }
        if ((bin || hex) && !aux)
            yyerror(parser, "numeric literal without digits");

        /* is it an exponential number ? */
        if (!bin && !hex && toupper(c) == 'E') {
            c = nextc();
            if (isdigit(c) || ((c == '+' || c == '-') && isdigit(*(parser->lex_p))))
                c = nextc();
            while (c != -1 && isdigit(c))
                c = nextc();
        }

        if (c != -1)
            pushback();
        tokp.end_line = parser->line + 1;
        tokp.end_col = parser->column + 1;
        if (c == 'r') {
            nextc();
            return tRATIONAL;
        } else if (c == 'i') {
            nextc();
            return tIMAGINARY;
        }
        tokp.end_line--;
        tokp.end_col--;
        return (has_point) ? tFLOAT : tINTEGER;
    }
}

/* Standard yylex. */
#if YYPURE
static int yylex(void *lval, void *p)
#else
static int yylex(void *p)
#endif
{
    struct parser_t *parser = (struct parser_t *) p;
    int t = token_invalid;
    _unused_(lval);

    t = parser_yylex(parser);
    return t;
}

/*
 * Error handling. Take the formmated string s and append the error
 * string to the list of errors p->errors.
 */
static void yyerror(struct parser_t *parser, const char *s)
{
    struct error_t *e = (struct error_t *) malloc(sizeof(struct error_t));

    e->msg = strdup(s);
    e->line = parser->line;
    e->column = parser->column;
    e->warning = parser->warning;
    e->next = e;
    if (parser->errors)
        parser->last_error->next = e;
    else
        parser->errors = e;
    parser->last_error = e;
    parser->last_error->next = NULL;

    parser->eof_reached = !e->warning;
    if (!parser->unrecoverable)
      parser->unrecoverable = !e->warning;
}

struct ast_t * rb_compile_file(struct options_t *opts)
{
    struct parser_t p;
    struct ast_t *result;

    /* Initialize parser */
    init_parser(&p);
    p.version = opts->version;
    if (!opts->contents) {
        if (!retrieve_source(&p, opts->path))
            return NULL;
    } else {
        p.content_given = 1;
        p.length = strlen(opts->contents);
        p.blob = opts->contents;
        p.lex_p = opts->contents;
    }

    /* Let's parse */
    result = (struct ast_t *) malloc(sizeof(struct ast_t));
    result->tree = NULL;
    result->unrecoverable = 0;
    for (;;) {
        yyparse(&p);
        if (p.ast != NULL) {
            if (result->tree == NULL)
                result->tree = p.ast;
            else
                update_list(result->tree, p.ast);
        }
        if (p.eof_reached) {
            result->errors = p.errors;
            result->unrecoverable = p.unrecoverable;
            break;
        }
    }
    free_parser(&p);

    return result;
}

#ifdef BUILD_TESTS
/*
 * Compile a file like the rb_compile_file function but printing
 * things directly to the stdout. This function is used for the tests.
 */
int rb_debug_file(struct options_t *opts)
{
    struct parser_t p;
    int index;

    /* Set up parser */
    init_parser(&p);
    p.version = opts->version;
    if (!retrieve_source(&p, opts->path))
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
            if (p.errors)
                print_errors(p.errors);
            break;
        }
    }

    /* Check that all the stacks are empty */
    for (index = 0; index < p.sp; index++)
        printf("\nS: %s", p.stack[index]);
    printf("\n");

    for (index = 0; index < p.pos_size; index++)
        printf("\nP: %i:%i", p.pos_stack[index].start_line, p.pos_stack[index].start_col);
    printf("\n");
    free_parser(&p);
    return 1;
}
#endif
