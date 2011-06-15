/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 27 "../parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "node.h"
#include "parser.h"


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
#define STACK_SIZE 128


/* yy's functions */
static int yylex(void *, void *);
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


void fix_pos(struct parser_t * parser, struct node * n);
void push_pos(struct parser_t * parser, struct pos_t tokp);
void pop_pos(struct parser_t * parser, struct node * n);
void pop_start(struct parser_t * parser, struct node * n);
void pop_end(struct parser_t * parser, struct node * n);
#define copy_start(dest, src) dest->startLine = src->startLine; dest->startCol = src->startCol
#define copy_end(dest, src) dest->endLine = src->endLine; dest->endCol = src->endCol
#define copy_range(dest, src1, src2) copy_start(dest, src1); copy_end(dest, src2)
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


/* Line 268 of yacc.c  */
#line 193 "../parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CLASS = 258,
     MODULE = 259,
     DEF = 260,
     UNDEF = 261,
     BEGIN = 262,
     RESCUE = 263,
     ENSURE = 264,
     END = 265,
     IF = 266,
     UNLESS = 267,
     THEN = 268,
     ELSIF = 269,
     ELSE = 270,
     CASE = 271,
     WHEN = 272,
     WHILE = 273,
     UNTIL = 274,
     FOR = 275,
     BREAK = 276,
     NEXT = 277,
     REDO = 278,
     RETRY = 279,
     IN = 280,
     DO = 281,
     DO_BLOCK = 282,
     RETURN = 283,
     YIELD = 284,
     KWAND = 285,
     KWOR = 286,
     KWNOT = 287,
     ALIAS = 288,
     DEFINED = 289,
     upBEGIN = 290,
     upEND = 291,
     HEREDOC = 292,
     tTRUE = 293,
     tFALSE = 294,
     NIL = 295,
     ENCODING = 296,
     tFILE = 297,
     LINE = 298,
     SELF = 299,
     SUPER = 300,
     EOL = 301,
     CVAR = 302,
     NUMBER = 303,
     SYMBOL = 304,
     FNAME = 305,
     BASE = 306,
     STRING = 307,
     REGEXP = 308,
     MCALL = 309,
     ARRAY = 310,
     SARY = 311,
     IVAR = 312,
     GLOBAL = 313,
     tLBRACKET = 314,
     tRBRACKET = 315,
     tDOT = 316,
     tTILDE = 317,
     tBACKTICK = 318,
     tCOMMA = 319,
     tCOLON = 320,
     tPOW = 321,
     tUMINUS = 322,
     tUPLUS = 323,
     tLSHIFT = 324,
     tRSHIFT = 325,
     tASSOC = 326,
     tQUESTION = 327,
     tSEMICOLON = 328,
     tOR = 329,
     tAND = 330,
     tAND_BIT = 331,
     tOR_BIT = 332,
     tXOR_BIT = 333,
     tLBRACE = 334,
     tRBRACE = 335,
     tLPAREN = 336,
     tRPAREN = 337,
     tLESSER = 338,
     tGREATER = 339,
     tNOT = 340,
     tPLUS = 341,
     tMINUS = 342,
     tMUL = 343,
     tDIV = 344,
     tMOD = 345,
     KEY = 346,
     CONST = 347,
     tASGN = 348,
     tOP_ASGN = 349,
     tCMP = 350,
     tEQ = 351,
     tEQQ = 352,
     tNEQ = 353,
     tMATCH = 354,
     tNMATCH = 355,
     tGEQ = 356,
     tLEQ = 357,
     tSCOPE = 358,
     tDOT3 = 359,
     tDOT2 = 360
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 151 "../parser.y"
  struct node * n;  


/* Line 293 of yacc.c  */
#line 338 "../parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 350 "../parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  136
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2608

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  135
/* YYNRULES -- Number of rules.  */
#define YYNRULES  343
/* YYNRULES -- Number of states.  */
#define YYNSTATES  616

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   360

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    16,    18,
      22,    26,    30,    34,    36,    38,    42,    44,    46,    48,
      50,    52,    54,    56,    58,    60,    62,    64,    66,    68,
      70,    72,    74,    76,    79,    81,    83,    85,    87,    89,
      91,    93,    95,    97,    99,   101,   103,   105,   107,   109,
     111,   113,   115,   117,   120,   124,   126,   128,   130,   133,
     135,   138,   140,   144,   146,   148,   150,   157,   164,   170,
     176,   182,   186,   191,   196,   204,   208,   209,   216,   217,
     223,   224,   230,   231,   238,   239,   247,   249,   251,   253,
     255,   259,   261,   264,   266,   268,   270,   272,   274,   276,
     278,   280,   282,   284,   286,   288,   290,   292,   294,   300,
     301,   304,   305,   308,   309,   311,   313,   316,   321,   326,
     330,   331,   333,   335,   337,   342,   346,   352,   356,   361,
     365,   369,   372,   374,   378,   380,   384,   387,   390,   395,
     398,   403,   406,   413,   418,   425,   430,   439,   446,   447,
     451,   453,   457,   460,   464,   466,   470,   472,   474,   476,
     478,   480,   482,   483,   485,   488,   490,   494,   495,   499,
     505,   507,   509,   511,   513,   516,   518,   520,   522,   525,
     527,   529,   531,   533,   536,   539,   542,   545,   548,   551,
     554,   557,   560,   563,   566,   567,   569,   572,   575,   578,
     581,   584,   587,   590,   593,   596,   600,   602,   605,   606,
     608,   610,   613,   615,   617,   619,   622,   623,   625,   627,
     629,   631,   633,   637,   640,   642,   646,   649,   651,   652,
     654,   656,   659,   663,   665,   668,   672,   674,   678,   682,
     686,   690,   694,   698,   702,   707,   712,   716,   720,   724,
     728,   731,   735,   737,   739,   741,   743,   745,   749,   755,
     757,   760,   764,   766,   770,   775,   779,   782,   785,   788,
     791,   795,   798,   802,   806,   810,   814,   817,   822,   825,
     827,   830,   833,   836,   837,   839,   840,   842,   844,   846,
     848,   850,   852,   856,   858,   862,   864,   866,   868,   870,
     873,   876,   878,   880,   885,   890,   895,   900,   905,   910,
     915,   920,   925,   930,   935,   939,   943,   947,   952,   957,
     962,   967,   972,   977,   982,   987,   992,   997,  1002,  1007,
    1012,  1017,  1022,  1027,  1036,  1040,  1044,  1048,  1052,  1056,
    1060,  1063,  1065,  1067
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     107,     0,    -1,    46,    -1,   108,    -1,   116,    -1,   121,
      -1,   214,    -1,   223,   146,    -1,   220,    -1,   108,   172,
     240,    -1,   108,   173,   240,    -1,   108,   174,   240,    -1,
     108,   175,   240,    -1,   240,    -1,   108,    -1,   109,   202,
     108,    -1,   132,    -1,    48,    -1,   136,    -1,   112,    -1,
      53,    -1,    37,    -1,    63,    -1,   111,    -1,    39,    -1,
      38,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    52,    -1,   112,    52,    -1,   110,
      -1,   215,    -1,   226,    -1,   228,    -1,   132,    -1,   226,
      -1,   228,    -1,    48,    -1,   136,    -1,   112,    -1,    53,
      -1,    37,    -1,    63,    -1,   215,    -1,   111,    -1,    21,
      -1,    23,    -1,    24,    -1,    22,    -1,     6,   119,    -1,
      33,   120,   120,    -1,   117,    -1,   118,    -1,    29,    -1,
      29,   240,    -1,    28,    -1,    28,   240,    -1,   120,    -1,
     120,   188,   119,    -1,    51,    -1,    50,    -1,   136,    -1,
     171,   240,   168,   197,   138,    10,    -1,   177,   240,   168,
     197,   138,    10,    -1,   178,   240,   169,   197,    10,    -1,
     179,   240,   169,   197,    10,    -1,   180,   240,   203,   166,
      10,    -1,   180,   166,    10,    -1,    35,    79,   197,    80,
      -1,    36,    79,   197,    80,    -1,   182,   211,   186,   239,
     169,   197,    10,    -1,     7,   144,    10,    -1,    -1,   183,
     129,   122,   130,   144,    10,    -1,    -1,   184,   131,   123,
     144,    10,    -1,    -1,   185,   131,   124,   144,    10,    -1,
      -1,   185,   131,   145,   125,   144,    10,    -1,    -1,   185,
      69,   199,   132,   126,   144,    10,    -1,    50,    -1,   133,
      -1,   127,    -1,   135,    -1,   133,   204,   127,    -1,   127,
      -1,   153,   205,    -1,   205,    -1,    92,    -1,   224,    -1,
      51,    -1,   133,    -1,    47,    -1,    58,    -1,    57,    -1,
      92,    -1,    51,    -1,    54,    -1,    92,    -1,    49,    -1,
      91,    -1,   139,    -1,   176,   240,   168,   197,   138,    -1,
      -1,    15,   197,    -1,    -1,     9,   197,    -1,    -1,   142,
      -1,   143,    -1,   142,   143,    -1,     8,   162,   168,   197,
      -1,   197,   141,   139,   140,    -1,    83,   199,   131,    -1,
      -1,   147,    -1,   148,    -1,   149,    -1,   193,   150,   198,
      80,    -1,   193,   198,    80,    -1,   170,   187,   150,   197,
      10,    -1,   170,   197,    10,    -1,    77,   154,   151,    77,
      -1,    77,   151,    77,    -1,    77,   154,    77,    -1,    73,
     152,    -1,   133,    -1,   152,   188,   133,    -1,   154,    -1,
     189,   154,   190,    -1,    76,   160,    -1,   156,   155,    -1,
     157,   188,   156,   155,    -1,   157,   155,    -1,   159,   188,
     156,   155,    -1,   159,   155,    -1,   159,   188,   157,   188,
     156,   155,    -1,   159,   188,   157,   155,    -1,   156,   188,
     159,   188,   156,   155,    -1,   156,   188,   159,   155,    -1,
     156,   188,   159,   188,   157,   188,   156,   155,    -1,   156,
     188,   159,   188,   157,   155,    -1,    -1,   188,    76,   160,
      -1,   160,    -1,   156,   188,   160,    -1,    88,   160,    -1,
     160,    93,   113,    -1,   158,    -1,   159,   188,   158,    -1,
      51,    -1,   161,    -1,    92,    -1,    57,    -1,    58,    -1,
      47,    -1,    -1,   163,    -1,   164,   165,    -1,   240,    -1,
     164,   188,   240,    -1,    -1,    71,   199,   132,    -1,   181,
     240,   168,   197,   167,    -1,   139,    -1,   166,    -1,   201,
      -1,    13,    -1,   201,    13,    -1,   201,    -1,    26,    -1,
      27,    -1,    11,   199,    -1,    11,    -1,    12,    -1,    18,
      -1,    19,    -1,    14,   199,    -1,    12,   199,    -1,    18,
     199,    -1,    19,   199,    -1,    16,   199,    -1,    17,   199,
      -1,    20,   199,    -1,     5,   199,    -1,     4,   199,    -1,
       3,   199,    -1,    25,   199,    -1,    -1,    46,    -1,    64,
     199,    -1,    81,   199,    -1,   199,    82,    -1,    59,   199,
      -1,   199,    60,    -1,    79,   199,    -1,   199,    80,    -1,
      93,   199,    -1,    94,   199,    -1,   203,   109,   203,    -1,
     203,    -1,   109,   203,    -1,    -1,   200,    -1,    46,    -1,
     200,    46,    -1,    73,    -1,    46,    -1,   201,    -1,   202,
     201,    -1,    -1,   202,    -1,    61,    -1,   103,    -1,    46,
      -1,    73,    -1,   211,   188,   207,    -1,   211,   188,    -1,
     240,    -1,   189,   206,   190,    -1,    88,   132,    -1,    88,
      -1,    -1,   209,    -1,   210,    -1,   209,   210,    -1,   191,
     216,   192,    -1,   240,    -1,   211,   188,    -1,   211,   188,
     207,    -1,   240,    -1,   212,   188,   240,    -1,   132,   195,
     113,    -1,   132,   196,   113,    -1,   132,   195,   220,    -1,
     132,   196,   220,    -1,   211,   195,   212,    -1,   211,   196,
     212,    -1,   211,   195,   223,   146,    -1,   211,   196,   223,
     146,    -1,   211,   195,   220,    -1,   211,   196,   220,    -1,
     211,   195,   121,    -1,   211,   196,   121,    -1,   191,    60,
      -1,   191,   217,   192,    -1,    55,    -1,   240,    -1,   213,
      -1,   220,    -1,   216,    -1,   217,   188,   216,    -1,   219,
     199,   216,   192,   208,    -1,    56,    -1,   193,    80,    -1,
     193,   221,   194,    -1,   222,    -1,   221,   188,   222,    -1,
     240,    71,   199,   240,    -1,   137,   199,   240,    -1,   127,
     233,    -1,   228,   233,    -1,   224,   231,    -1,   135,   225,
      -1,   135,   103,   127,    -1,   103,   135,    -1,   225,   103,
     128,    -1,   134,   232,   190,    -1,   227,   232,   190,    -1,
     135,   103,   134,    -1,   110,   229,    -1,   189,   240,   190,
     229,    -1,   226,   229,    -1,   230,    -1,   229,   230,    -1,
      61,   127,    -1,    61,   226,    -1,    -1,   233,    -1,    -1,
     234,    -1,   223,    -1,   235,    -1,   223,    -1,   236,    -1,
     240,    -1,   235,   188,   237,    -1,   238,    -1,   236,   188,
     238,    -1,   240,    -1,   220,    -1,   221,    -1,   237,    -1,
      76,   240,    -1,    88,   240,    -1,   240,    -1,   220,    -1,
     240,    86,   199,   240,    -1,   240,    87,   199,   240,    -1,
     240,    88,   199,   240,    -1,   240,    89,   199,   240,    -1,
     240,    90,   199,   240,    -1,   240,    66,   199,   240,    -1,
     240,    76,   199,   240,    -1,   240,    77,   199,   240,    -1,
     240,    78,   199,   240,    -1,   240,    69,   199,   240,    -1,
     240,    70,   199,   240,    -1,   189,   240,   190,    -1,   189,
     214,   190,    -1,   189,   223,   190,    -1,   240,    95,   199,
     240,    -1,   240,    96,   199,   240,    -1,   240,    98,   199,
     240,    -1,   240,    97,   199,   240,    -1,   240,    99,   199,
     240,    -1,   240,   100,   199,   240,    -1,   240,    84,   199,
     240,    -1,   240,    83,   199,   240,    -1,   240,   101,   199,
     240,    -1,   240,   102,   199,   240,    -1,   240,    74,   199,
     240,    -1,   240,    75,   199,   240,    -1,   240,    31,   199,
     240,    -1,   240,    30,   199,   240,    -1,   240,   105,   199,
     240,    -1,   240,   104,   199,   240,    -1,   240,    72,   199,
     240,   199,    65,   199,   240,    -1,    32,   199,   240,    -1,
      62,   199,   240,    -1,    85,   199,   240,    -1,    68,   199,
     240,    -1,    67,   199,   240,    -1,    34,   199,   240,    -1,
     114,   146,    -1,   115,    -1,   218,    -1,    50,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   207,   207,   208,   219,   220,   221,   222,   227,   228,
     229,   230,   231,   232,   235,   236,   239,   240,   241,   242,
     247,   248,   249,   250,   253,   254,   255,   256,   257,   258,
     259,   260,   263,   264,   271,   272,   273,   274,   277,   278,
     279,   282,   283,   284,   289,   290,   291,   292,   293,   296,
     297,   298,   299,   300,   301,   302,   303,   306,   307,   310,
     311,   314,   315,   318,   319,   320,   323,   331,   339,   346,
     353,   360,   365,   371,   377,   383,   389,   388,   399,   398,
     410,   409,   421,   420,   432,   431,   444,   445,   448,   449,
     452,   457,   460,   461,   464,   465,   466,   472,   473,   474,
     475,   476,   479,   482,   485,   488,   491,   494,   495,   507,
     508,   518,   519,   529,   530,   533,   534,   537,   547,   560,
     563,   564,   567,   568,   571,   581,   593,   603,   615,   620,
     625,   632,   635,   636,   639,   640,   643,   644,   645,   649,
     650,   654,   655,   659,   663,   667,   671,   676,   682,   683,
     686,   687,   690,   693,   700,   701,   704,   705,   708,   713,
     718,   723,   730,   731,   734,   745,   746,   749,   750,   753,
     764,   765,   768,   769,   770,   773,   774,   784,   797,   800,
     803,   806,   809,   812,   815,   818,   821,   824,   827,   830,
     833,   836,   839,   842,   845,   846,   849,   852,   855,   858,
     861,   864,   867,   870,   873,   876,   877,   880,   883,   884,
     887,   888,   891,   892,   895,   896,   899,   900,   903,   904,
     907,   908,   911,   912,   915,   925,   934,   935,   945,   946,
     949,   950,   953,   956,   957,   958,   961,   962,   965,   966,
     967,   968,   971,   972,   973,   979,   985,   986,   987,   988,
     991,   992,   993,   997,   998,   999,  1002,  1003,  1006,  1027,
    1035,  1036,  1044,  1045,  1048,  1053,  1060,  1069,  1079,  1094,
    1104,  1112,  1113,  1116,  1129,  1144,  1147,  1157,  1167,  1173,
    1174,  1177,  1182,  1189,  1190,  1193,  1194,  1197,  1198,  1205,
    1206,  1210,  1211,  1214,  1215,  1219,  1220,  1221,  1232,  1233,
    1234,  1238,  1239,  1242,  1243,  1244,  1245,  1246,  1247,  1248,
    1249,  1250,  1251,  1252,  1253,  1254,  1255,  1256,  1257,  1258,
    1259,  1260,  1261,  1262,  1263,  1264,  1265,  1266,  1267,  1268,
    1269,  1270,  1271,  1272,  1276,  1277,  1278,  1279,  1280,  1281,
    1282,  1283,  1284,  1285
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "MODULE", "DEF", "UNDEF",
  "BEGIN", "RESCUE", "ENSURE", "END", "IF", "UNLESS", "THEN", "ELSIF",
  "ELSE", "CASE", "WHEN", "WHILE", "UNTIL", "FOR", "BREAK", "NEXT", "REDO",
  "RETRY", "IN", "DO", "DO_BLOCK", "RETURN", "YIELD", "KWAND", "KWOR",
  "KWNOT", "ALIAS", "DEFINED", "upBEGIN", "upEND", "HEREDOC", "tTRUE",
  "tFALSE", "NIL", "ENCODING", "tFILE", "LINE", "SELF", "SUPER", "EOL",
  "CVAR", "NUMBER", "SYMBOL", "FNAME", "BASE", "STRING", "REGEXP", "MCALL",
  "ARRAY", "SARY", "IVAR", "GLOBAL", "tLBRACKET", "tRBRACKET", "tDOT",
  "tTILDE", "tBACKTICK", "tCOMMA", "tCOLON", "tPOW", "tUMINUS", "tUPLUS",
  "tLSHIFT", "tRSHIFT", "tASSOC", "tQUESTION", "tSEMICOLON", "tOR", "tAND",
  "tAND_BIT", "tOR_BIT", "tXOR_BIT", "tLBRACE", "tRBRACE", "tLPAREN",
  "tRPAREN", "tLESSER", "tGREATER", "tNOT", "tPLUS", "tMINUS", "tMUL",
  "tDIV", "tMOD", "KEY", "CONST", "tASGN", "tOP_ASGN", "tCMP", "tEQ",
  "tEQQ", "tNEQ", "tMATCH", "tNMATCH", "tGEQ", "tLEQ", "tSCOPE", "tDOT3",
  "tDOT2", "$accept", "parser_start", "stmt", "stmts", "basic",
  "other_keywords", "string", "primary", "primary1", "primary2",
  "simple_stmt", "yield_stmt", "return_stmt", "item_list", "item",
  "cmpd_stmt", "$@1", "$@2", "$@3", "$@4", "$@5", "fname",
  "fname_or_const", "single_name", "function_args", "module_name",
  "variable", "base", "mcall", "const", "symbol", "key", "if_tail",
  "opt_else", "opt_ensure", "opt_rescue", "rescue_list", "rescue_item",
  "bodystmt", "superclass", "opt_lambda_body", "lambda_body",
  "brace_block", "do_block", "block_args", "bv_decls", "block_list",
  "f_arglist", "f_arguments", "f_blockarg", "f_args", "f_restarg", "f_opt",
  "f_optarg", "arg", "f_bad_arg", "opt_rescue_arg", "rescue_arg",
  "exc_list", "exc_var", "case_body", "cases", "then", "do", "k_do_block",
  "k_if", "m_if", "m_unless", "m_while", "m_until", "k_elsif", "k_unless",
  "k_while", "k_until", "k_case", "k_when", "k_for", "k_def", "k_module",
  "k_class", "k_in", "endl", "comma", "lparen", "rparen", "lbracket",
  "rbracket", "lbrace", "rbrace", "asgn", "op_asgn", "compstmt",
  "not_empty_compstmt", "opt_eol_list", "eol_list", "term", "terms",
  "opt_terms", "dot_or_scope", "eol_or_semicolon", "lhs_list", "lhs",
  "opt_bracket_list", "bracket_list", "bracket_item", "mlhs", "mrhs",
  "simple_assign", "assign", "array", "array_exp", "array_items",
  "array_value", "sary", "hash", "hash_items", "hash_item", "method_call",
  "const_scope", "scope_items", "paren_method_call", "const_mcall",
  "dot_method_call", "dot_items", "dot_item", "opt_call_args",
  "opt_call_args_paren", "m_call_args", "m_call_args_paren", "call_args",
  "call_args_paren", "exp_hash", "exp_paren", "exp_for", "exp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   106,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   109,   109,   110,   110,   110,   110,
     110,   110,   110,   110,   111,   111,   111,   111,   111,   111,
     111,   111,   112,   112,   113,   113,   113,   113,   114,   114,
     114,   115,   115,   115,   115,   115,   115,   115,   115,   116,
     116,   116,   116,   116,   116,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   120,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   122,   121,   123,   121,
     124,   121,   125,   121,   126,   121,   127,   127,   128,   128,
     129,   129,   130,   130,   131,   131,   131,   132,   132,   132,
     132,   132,   133,   134,   135,   136,   137,   138,   138,   139,
     139,   140,   140,   141,   141,   142,   142,   143,   144,   145,
     146,   146,   147,   147,   148,   148,   149,   149,   150,   150,
     150,   151,   152,   152,   153,   153,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   155,   155,
     156,   156,   157,   158,   159,   159,   160,   160,   161,   161,
     161,   161,   162,   162,   163,   164,   164,   165,   165,   166,
     167,   167,   168,   168,   168,   169,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   197,   198,   199,   199,
     200,   200,   201,   201,   202,   202,   203,   203,   204,   204,
     205,   205,   206,   206,   207,   207,   207,   207,   208,   208,
     209,   209,   210,   211,   211,   211,   212,   212,   213,   213,
     213,   213,   214,   214,   214,   214,   214,   214,   214,   214,
     215,   215,   215,   216,   216,   216,   217,   217,   218,   219,
     220,   220,   221,   221,   222,   222,   223,   223,   223,   224,
     224,   225,   225,   226,   226,   227,   228,   228,   228,   229,
     229,   230,   230,   231,   231,   232,   232,   233,   233,   234,
     234,   235,   235,   236,   236,   237,   237,   237,   238,   238,
     238,   239,   239,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     2,     1,     3,
       3,     3,     3,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     1,     1,     1,     2,     1,
       2,     1,     3,     1,     1,     1,     6,     6,     5,     5,
       5,     3,     4,     4,     7,     3,     0,     6,     0,     5,
       0,     5,     0,     6,     0,     7,     1,     1,     1,     1,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     0,
       2,     0,     2,     0,     1,     1,     2,     4,     4,     3,
       0,     1,     1,     1,     4,     3,     5,     3,     4,     3,
       3,     2,     1,     3,     1,     3,     2,     2,     4,     2,
       4,     2,     6,     4,     6,     4,     8,     6,     0,     3,
       1,     3,     2,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     0,     1,     2,     1,     3,     0,     3,     5,
       1,     1,     1,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     0,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     1,     2,     0,     1,
       1,     2,     1,     1,     1,     2,     0,     1,     1,     1,
       1,     1,     3,     2,     1,     3,     2,     1,     0,     1,
       1,     2,     3,     1,     2,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     4,     4,     3,     3,     3,     3,
       2,     3,     1,     1,     1,     1,     1,     3,     5,     1,
       2,     3,     1,     3,     4,     3,     2,     2,     2,     2,
       3,     2,     3,     3,     3,     3,     2,     4,     2,     1,
       2,     2,     2,     0,     1,     0,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     1,     1,     1,     2,
       2,     1,     1,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,     3,     3,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     8,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   208,   208,   208,     0,   216,   208,   208,   208,   208,
     208,   208,    49,    52,    50,    51,    59,    57,   208,     0,
     208,     0,     0,    45,    25,    24,    26,    27,    28,    29,
      30,    31,     2,    98,    41,   105,   343,   102,    32,    44,
     103,   252,   259,   100,    99,   208,   208,    46,   208,   208,
     208,   208,   208,   101,     0,     3,     0,    48,    43,   120,
     341,     4,    55,    56,     5,     0,    38,    97,   285,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,    47,   342,   208,     8,   120,
     283,    39,   285,    40,    13,   210,   192,   209,   191,   190,
      64,    63,    53,    61,    65,   213,   212,     0,   113,   214,
     217,   206,   178,   184,   187,   185,   186,   189,   343,    97,
       0,    40,    60,    58,     0,     0,     0,   216,   216,   199,
       0,     0,     0,   201,   197,     0,     1,   179,   180,   181,
     182,     0,     0,     0,     0,     0,   276,   279,    33,   177,
     340,   121,   122,   123,   216,     0,   287,   266,   288,   291,
       0,     0,   106,   208,   296,   297,   262,   289,   208,   286,
     290,   298,   293,   295,     0,   269,     0,     0,     0,     0,
     208,     0,     0,   216,     0,   233,    86,    91,    76,    87,
      96,    94,    78,     0,    95,   208,    80,   208,   208,   233,
     250,    38,   254,   256,   208,   255,   253,   260,   208,     0,
     208,   208,   208,   234,     0,     0,     0,     7,   268,   284,
     278,   208,   267,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   211,     0,    75,   162,   109,   114,   115,   215,    14,
     216,     0,   334,    54,   339,     0,     0,   335,   338,   337,
     336,     9,    10,    11,    12,   104,   281,    87,   282,   280,
     213,     0,     0,     0,   216,     0,     0,     0,   299,   300,
       0,     0,   273,     0,     0,   208,   270,   275,   271,     0,
     173,   216,   172,   216,   176,   216,   175,   216,   188,    71,
       0,     0,   208,     0,     0,   218,   219,     0,   216,     0,
       0,   208,   216,    82,   315,   316,   314,     0,     0,     0,
     251,     0,   261,     0,   196,   203,   204,   227,     0,   235,
     224,   248,   242,   246,   120,   236,   249,   243,   247,   120,
     208,   274,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      62,     0,   163,   167,   165,   216,   111,   116,   217,   205,
      72,    73,   216,   127,   161,   156,   159,   160,     0,     0,
       0,   158,     0,     0,   148,   148,   154,   148,   150,   157,
     207,     0,   125,   292,   265,   263,   198,   294,     0,    88,
     272,    89,   109,   174,   109,     0,     0,   216,     0,   193,
     302,     0,   301,   220,   221,   216,     0,   134,     0,    93,
      90,     0,   101,    84,     0,     0,   216,   277,    21,    17,
      20,    22,    34,    23,    19,   238,    16,    18,     0,    35,
     240,    36,    37,   239,   241,   257,   200,   202,   226,   208,
       0,     0,   244,   245,   228,   330,   329,   308,   312,   313,
     208,   327,   328,   309,   310,   311,   324,   323,   303,   304,
     305,   306,   307,   317,   318,   320,   319,   321,   322,   325,
     326,   332,   331,   216,   208,   164,     0,   110,   216,   118,
      15,     0,   132,   131,   136,   152,   129,   130,     0,   137,
       0,   139,     0,   141,     0,     0,   124,   264,   208,     0,
     107,     0,     0,    68,    69,   109,    70,   216,     0,    92,
     208,    79,   216,   119,    81,     0,   208,   225,   234,   237,
       0,   258,   229,   230,     0,   117,     0,   166,   112,   126,
       0,   128,     0,   148,   151,   148,   150,   148,   148,   155,
     153,   183,    66,     0,    67,   170,   171,   169,     0,    77,
     135,     0,    83,     0,   235,   208,   231,   208,   168,   133,
     149,   145,     0,   138,     0,   140,   143,     0,   216,    74,
      85,   232,     0,   148,   148,   151,   148,   109,   333,   144,
     147,     0,   142,   108,   148,   146
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    54,   259,   284,    56,    57,    58,   455,    59,    60,
      61,    62,    63,   102,   103,    64,   314,   318,   322,   446,
     542,    65,   420,   188,   435,   192,    66,   119,    68,   120,
      70,   163,   529,   530,   509,   255,   256,   257,   107,   323,
     150,   151,   152,   153,   285,   402,   513,   436,   403,   519,
     404,   405,   406,   407,   408,   409,   381,   382,   383,   505,
     181,   577,   301,   305,   154,    71,   141,   142,   143,   144,
     531,    72,    73,    74,    75,   182,    76,    77,    78,    79,
     313,   281,   594,    80,   292,    81,   330,    82,   332,   214,
     215,   108,   286,   293,    97,   109,   110,   111,   317,   439,
     469,   339,   551,   552,   553,    83,   342,   202,    84,    85,
     203,   204,    86,    87,    88,   165,   166,    89,    90,   175,
      91,    92,   121,   146,   147,   218,   168,   157,   169,   158,
     170,   171,   172,   431,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -492
static const yytype_int16 yypact[] =
{
     867,    75,    75,    75,   143,    92,    75,    75,    75,    75,
      75,    75,  -492,  -492,  -492,  -492,  2089,  2089,    75,   143,
      75,    25,    68,    71,  -492,  -492,  -492,  -492,  -492,  -492,
    -492,  -492,  -492,  -492,    89,  -492,  2145,  -492,  -492,   109,
    -492,  -492,  -492,  -492,  -492,    75,    75,   140,    75,    75,
      75,    75,    75,   111,   221,   193,   162,   169,   130,    27,
    -492,  -492,  -492,  -492,  -492,  2201,   171,  2257,  1573,   133,
     176,  2089,  2089,  2089,  2089,  1212,  2089,   159,     2,   139,
    2201,  1752,  1808,    93,  -492,  -492,  -492,    75,  -492,    27,
    2201,   162,  1573,  2201,  1242,  -492,  -492,   197,  -492,  -492,
    -492,  -492,  -492,   181,  -492,  -492,  -492,   238,   241,  -492,
      92,  1033,  -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,
     157,  -492,  1499,  1499,  2089,   143,  2089,    92,    92,  -492,
    2089,  2089,  2089,  -492,  -492,  2089,  -492,  -492,  -492,  -492,
    -492,  2089,  2089,  2089,  2089,   104,   162,  -492,  -492,  -492,
    -492,  -492,  -492,  -492,   102,   950,  -492,  -492,   181,  1499,
    2089,  2089,  -492,    75,  -492,   181,  -492,  -492,    75,  -492,
     181,  -492,  -492,  1401,   104,   160,   662,   662,  1138,  1138,
      75,   252,  2089,  1303,    53,  1499,  -492,  -492,  -492,     8,
    -492,   111,  -492,   161,  -492,    75,   185,    75,    75,  1364,
    -492,    69,  -492,  -492,    67,  -492,  1499,  -492,    67,  1401,
      75,    75,    75,  1920,  1104,  1104,  1977,  -492,  -492,  -492,
     162,    75,  -492,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,  -492,   143,  -492,  2089,   258,   241,  -492,  -492,   193,
      92,   222,  2358,  -492,  2358,   205,   208,  -492,   227,  -492,
    -492,  1499,  1499,  1499,  1499,  -492,  -492,  -492,  -492,  -492,
     217,   230,   294,   473,    92,  1033,   229,  1864,  1499,  1499,
    2089,  2033,  -492,   228,  1634,    75,  -492,  -492,  -492,    -4,
    -492,    92,   298,    92,  -492,    92,  -492,    92,  -492,  -492,
     662,   299,    75,  1977,   460,  -492,  -492,   159,    92,    -4,
     177,    75,    92,  -492,  -492,  -492,   162,  2313,  2313,  1977,
    -492,   257,  -492,   240,  -492,  -492,  -492,   177,  2201,  -492,
    1499,  -492,   181,  -492,    27,  1499,  -492,   181,  -492,    27,
      75,  -492,  2089,  2089,  2089,  2089,  2089,  2089,  2089,  2089,
    2089,  2089,  2089,  2089,  2089,  2089,  2089,  2089,  2089,  2089,
    2089,  2089,  2089,  2089,  2089,  2089,  2089,  2089,  2089,  2089,
    -492,    29,  -492,   114,  1499,    92,   309,  -492,   766,  -492,
    -492,  -492,    92,  -492,  -492,  -492,  -492,  -492,   270,   526,
     526,  -492,   247,    16,   181,   181,  -492,   181,   234,  -492,
    -492,   248,  -492,  -492,  1499,  -492,  -492,  -492,  2089,  -492,
    -492,  -492,   203,  -492,   203,   321,   323,    92,   325,  -492,
    -492,    66,  1499,  -492,  -492,    92,   107,  -492,   399,  -492,
    -492,   368,  -492,  -492,     2,   369,    92,   162,  -492,  -492,
    -492,  -492,   162,  -492,   333,  -492,  -492,  -492,  2089,  -492,
    -492,   162,  -492,  -492,  -492,  -492,  -492,  -492,  -492,    75,
      93,  2089,  -492,  -492,   328,  2358,  2358,   227,   629,   629,
    1462,  2432,  2469,   561,  1111,  1111,   611,   611,   213,   213,
     227,   227,   227,  2506,  2506,  2506,  2506,  2506,  2506,   611,
     611,  2395,  2395,    92,    75,  -492,  2089,  -492,    92,  -492,
     193,   378,  -492,   181,  -492,  -492,  -492,  -492,   312,  -492,
     349,  -492,   349,  -492,   577,  2359,  -492,  1499,    75,   380,
    -492,  2089,   381,  -492,  -492,    55,  -492,    92,   383,  -492,
      75,  -492,    92,  -492,  -492,   384,  1462,  -492,  1695,  1499,
    1977,  -492,   328,  -492,   332,  -492,   177,  1499,  -492,  -492,
     270,  -492,   526,   181,   234,   181,  -492,   181,   181,  -492,
    -492,  -492,  -492,   662,  -492,  -492,  -492,  -492,   388,  -492,
    -492,   394,  -492,   162,    40,    75,  -492,    75,  -492,  -492,
    -492,  -492,   577,  -492,   349,  -492,  -492,   349,    92,  -492,
    -492,  -492,  2089,   181,   181,  -492,   181,   203,  2358,  -492,
    -492,   349,  -492,  -492,   181,  -492
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -492,  -492,     4,   297,  -292,  -284,  -266,  -310,  -492,  -492,
    -492,  -492,  -492,   168,    10,    11,  -492,  -492,  -492,  -492,
    -492,   145,  -492,  -492,  -492,   -63,   -76,    84,  -137,   405,
      -2,  -492,  -404,  -246,  -492,  -492,  -492,   155,  -219,  -492,
     -57,  -492,  -492,  -492,   142,    18,  -492,  -492,  -287,    58,
    -451,  -491,  -485,   -96,   -85,  -492,  -492,  -492,  -492,  -492,
    -280,  -492,  -174,  -154,  -492,  -492,  -492,  -492,  -492,  -492,
    -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,  -492,
    -492,  -492,   -75,  -108,  -101,  -452,  -331,   -49,  -492,   225,
     226,   129,   146,   364,  -492,   -97,  -197,  -142,  -492,    -8,
    -492,  -115,  -492,  -492,  -109,   -52,   232,  -492,   -68,  -260,
    -186,  -492,  -492,  -492,   -47,   366,   163,   -42,   -64,  -492,
    -139,  -492,    91,   -84,  -135,  -492,   360,    44,  -492,  -492,
    -492,   166,   164,  -492,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -234
static const yytype_int16 yytable[] =
{
     122,   123,   104,   303,    55,   201,   278,   220,   213,   386,
     155,   279,   197,   258,   194,   194,   196,   104,   463,   474,
     532,   164,   550,   156,   184,   307,   167,   437,   252,   125,
     350,   428,   217,   568,   205,   452,   452,   297,   198,   569,
     155,   311,   300,   453,   453,   164,   186,    37,   156,   159,
     167,   156,   173,   190,   149,   176,   177,   178,   179,   183,
     185,   454,   454,   388,   199,   206,   209,   459,   459,   315,
     385,   565,   180,   567,   159,   105,   173,   159,   312,   302,
     302,   306,   306,   287,    67,   279,  -222,   388,   275,   398,
     291,    93,   304,   517,   191,   294,   324,   325,   326,   441,
     550,   604,   106,   445,   127,   338,    50,   569,   262,   213,
     264,   316,   105,    95,   267,   268,   269,   210,   389,   270,
     351,    95,  -222,   104,   297,   271,   272,   273,   274,   329,
     -16,   210,   -21,   291,   219,   263,   427,   222,   105,   106,
     201,   603,   410,   465,   288,   289,   606,   128,   280,    67,
     -17,   540,    67,   433,   186,    37,    93,   210,    40,    93,
     614,   189,   211,   212,    67,   106,   310,   343,   348,   205,
     -20,    93,   344,   349,    67,   106,    67,    67,   210,  -194,
     434,    93,   148,    93,    93,   504,   211,   212,   461,   461,
     190,   -19,    35,   100,   101,    67,   275,   340,   345,   345,
     206,   -22,    93,   613,   137,   138,   438,   503,   195,   186,
      37,   139,   140,   302,  -104,   570,   538,   528,   385,   458,
     458,   136,   187,   145,    33,   341,   346,   545,    37,   277,
     -23,   191,   -16,   452,    43,    44,   174,   -18,   384,    67,
     164,   453,   447,   251,   443,   210,    93,   164,   253,   254,
     104,   456,   456,   201,   601,   576,   265,   266,   277,   454,
     261,   468,   309,   299,   319,   459,   430,   471,   321,   442,
     197,   173,   471,   385,   414,   209,    40,   537,   173,   225,
     460,   464,   205,   282,   302,   390,   470,   472,   391,   575,
     276,   258,   473,   225,  -195,   155,   198,   432,    67,    67,
     155,   238,   239,   240,   393,    93,    93,   283,   506,   412,
     416,   423,   279,   206,   514,   515,   180,   466,   508,   296,
     467,    37,   199,   581,   516,   457,   457,   525,   526,   520,
     522,   533,   524,   534,   306,   536,   475,   476,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   585,    96,    98,    99,   547,    67,
     112,   113,   114,   115,   116,   117,    93,   220,   541,   544,
     194,   543,   124,   277,   126,   148,   461,    45,   559,   561,
     572,   574,   510,   579,   582,   548,   394,   587,   599,   598,
     395,   277,   527,   277,   600,    69,   396,   397,   260,   129,
     130,   387,   131,   132,   133,   134,   135,   458,   462,   462,
     380,   518,    67,   392,   563,   562,   327,   328,   539,    93,
     422,   411,   424,   584,   425,   564,   426,   566,   560,   580,
     338,   401,   546,   586,   419,   583,   394,   347,   208,   456,
     395,   216,   221,   413,   415,   549,   396,   397,   417,     0,
       0,     0,   440,   521,   296,   523,     0,     0,     0,     0,
      69,     0,    67,    69,   201,   399,   302,   590,     0,    93,
     588,     0,   512,   193,   193,    69,     0,   400,   592,     0,
     557,   401,     0,   597,     0,    69,     0,    69,    69,   447,
       0,     0,     0,   205,     0,     0,   433,   394,     0,   605,
       0,   395,   566,     0,   507,   573,    69,   396,   397,     0,
     394,   511,     0,   457,   395,     0,   566,   290,     0,   611,
     396,   397,   340,   434,   206,     0,   399,     0,     0,     0,
       0,    51,     0,     0,   308,     0,   398,     0,   400,   399,
       0,     0,   401,     0,     0,     0,   535,     0,     0,   320,
      69,   400,     0,     0,     0,   401,     0,     0,   331,     0,
       0,     0,   333,   394,   334,   335,   336,   395,     0,   298,
       0,     0,     0,   396,   397,     0,   608,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,     0,   462,     0,   401,    69,
      69,   591,     0,   593,   394,   595,   596,   225,   395,     0,
     226,   227,   555,     0,   396,   397,     0,   558,     0,     0,
       0,     0,     0,     0,   589,     0,     0,   236,   237,   238,
     239,   240,     0,   562,     0,     0,     0,     0,     0,   418,
       0,   609,   610,     0,   612,   400,   578,     0,     0,   401,
       0,     0,   615,     0,     0,   300,   429,   225,     0,     0,
     226,   227,     0,     0,     0,   444,     0,   231,   232,   233,
      69,     0,   223,   224,     0,   225,     0,   236,   237,   238,
     239,   240,     0,     0,   421,     0,     0,     0,   105,     0,
       0,     0,     0,     0,   331,   236,   237,   238,   239,   240,
       0,     0,     0,     0,   298,     0,     0,   607,   225,     0,
       0,   226,   227,     0,   228,   106,   229,   230,   231,   232,
     233,     0,     0,    69,     0,   234,   235,     0,   236,   237,
     238,   239,   240,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   248,     0,   249,   250,     0,     1,
       2,     3,     4,     5,     0,     0,     0,     6,     7,     0,
       0,     0,     8,     0,     9,    10,    11,    12,    13,    14,
      15,     0,     0,    69,    16,    17,     0,     0,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,   105,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     0,     0,    46,    47,
       0,     0,     0,    48,    49,     0,     0,     0,     0,   106,
       0,     0,     0,     0,   554,    50,     0,    51,     0,   193,
       0,    52,     0,     0,     0,     0,     0,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   556,     0,
       1,     2,     3,     4,     5,     0,     0,     0,     6,     7,
       0,     0,     0,     8,     0,     9,    10,    11,    12,    13,
      14,    15,   571,     0,     0,    16,    17,     0,     0,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,    46,
      47,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,    51,   331,
       0,   602,    52,     1,     2,     3,     4,     5,     0,    53,
       0,     6,     7,     0,     0,     0,     8,     0,     9,    10,
      11,    12,    13,    14,    15,     0,     0,     0,    16,    17,
       0,     0,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,    47,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,   283,     0,    50,
       0,    51,     0,     0,     0,    52,     1,     2,     3,     4,
       5,     0,    53,     0,     6,     7,     0,     0,     0,     8,
       0,     9,    10,    11,    12,    13,    14,    15,     0,     0,
       0,    16,    17,     0,     0,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,    46,    47,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     1,     2,     3,
       0,     5,    50,     0,    51,     6,     7,     0,    52,     0,
       8,     0,     9,    10,    11,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,   304,     0,    46,    47,   223,   224,
       0,    48,    49,     0,     0,     0,     0,   225,     0,     0,
     226,   227,     0,    50,   105,    51,     0,   231,     0,    52,
       0,     0,     0,     0,     0,     0,    53,   236,   237,   238,
     239,   240,     0,     0,   225,     0,     0,   226,   227,     0,
     228,   106,   229,   230,   231,   232,   233,     0,     0,     0,
       0,   234,   235,     0,   236,   237,   238,   239,   240,   180,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
     248,     0,   249,   250,    18,     0,    20,     0,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    33,
      34,    35,   118,    37,    38,    39,    40,    41,    42,    43,
      44,    45,   223,   224,    46,    47,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,     0,     0,    52,     0,     0,
       0,     0,     0,     0,    53,     0,  -233,     0,   225,     0,
       0,   226,   227,     0,   228,     0,   229,   230,   231,   232,
     233,     0,     0,     0,     0,   234,   235,     0,   236,   237,
     238,   239,   240,   223,   224,  -233,  -233,   241,   242,   243,
     244,   245,   246,   247,   248,     0,   249,   250,     0,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   225,
       0,     0,   226,   227,     0,   228,   106,   229,   230,   231,
     232,   233,     0,     0,     0,     0,   234,   235,     0,   236,
     237,   238,   239,   240,   223,   224,     0,     0,   241,   242,
     243,   244,   245,   246,   247,   248,     0,   249,   250,     0,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     225,   223,   224,   226,   227,     0,   228,     0,   229,   230,
     231,   232,   233,     0,     0,     0,  -208,   234,   235,     0,
     236,   237,   238,   239,   240,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,   248,   225,   249,   250,
     226,   227,   295,   228,     0,   229,   230,   231,   232,   233,
       0,     0,     0,     0,   234,   235,     0,   236,   237,   238,
     239,   240,   223,   224,     0,     0,   241,   242,   243,   244,
     245,   246,   247,   248,     0,   249,   250,     0,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   225,   223,
     224,   226,   227,     0,   228,     0,   229,   230,   231,   232,
     233,     0,     0,     0,     0,   234,   235,     0,   236,   237,
     238,   239,   240,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   248,   225,   249,   250,   226,   227,
       0,   228,     0,   229,   230,   231,   232,   233,     0,     0,
       0,     0,   234,   235,     0,   236,   237,   238,   239,   240,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,   248,     0,   249,   250,    18,     0,    20,     0,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,    46,    47,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,   160,
       0,     0,    50,     0,    51,     0,     0,     0,    52,     0,
       0,   161,     0,     0,   162,    53,    18,     0,    20,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    33,    34,    35,   118,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,     0,    46,    47,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
     160,     0,     0,    50,     0,    51,     0,     0,     0,    52,
       0,     0,   161,     0,     0,   162,    53,    18,     0,    20,
       0,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,  -223,    33,    34,    35,   118,    37,    38,    39,    40,
      41,    42,    43,    44,    45,     0,     0,    46,    47,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,  -223,     0,     0,
      52,     0,     0,   337,    18,     0,    20,    53,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    33,
      34,    35,   118,    37,    38,    39,    40,    41,    42,    43,
      44,    45,   200,     0,    46,    47,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     0,    51,     0,     0,     0,    52,     0,     0,
      18,     0,    20,     0,    53,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    33,    34,    35,   118,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     0,     0,
      46,    47,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   207,    51,
       0,     0,     0,    52,     0,     0,    18,     0,    20,   162,
      53,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    33,    34,    35,   118,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,     0,    46,    47,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,    51,     0,     0,     0,    52,
       0,     0,    18,     0,    20,   162,    53,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    33,    34,    35,
     118,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,    47,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     0,     0,    52,     0,     0,   337,    18,
       0,    20,    53,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,    33,    34,    35,   118,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,    46,
      47,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,    51,     0,
       0,     0,    52,     0,     0,    18,     0,    20,     0,    53,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      33,    34,    35,   118,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,    46,    47,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,     0,     0,     0,    52,     0,
       0,    18,     0,    20,   162,    53,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,   118,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,    46,    47,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,    52,     0,     0,   -86,     0,   -86,
       0,    53,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,     0,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,     0,     0,   -86,   -86,     0,
       0,     0,   -86,   -86,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -86,     0,     0,     0,
     -86,     0,     0,    18,     0,    20,     0,   -86,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,    46,    47,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,     0,     0,     0,    52,     0,     0,   -87,
       0,   -87,     0,    53,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,     0,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,     0,     0,   -87,
     -87,     0,     0,     0,   -87,   -87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -87,     0,
       0,     0,   -87,     0,     0,     0,     0,     0,     0,   -87,
     448,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      33,   449,    35,     0,    37,    38,   450,    40,    41,     0,
      43,    44,    45,     0,     0,     0,   451,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,    51,     0,   448,    24,    25,    26,
      27,    28,    29,    30,    31,    53,    33,   449,    35,     0,
      37,    38,   450,    40,    41,     0,    43,    44,    45,     0,
       0,     0,   451,     0,   225,     0,     0,   226,   227,     0,
     228,     0,   229,   230,   231,   232,   233,     0,     0,     0,
      51,   234,   235,     0,   236,   237,   238,   239,   240,     0,
       0,    53,     0,   241,   242,   243,   244,   245,   246,   247,
     248,   225,   249,   250,   226,   227,     0,     0,     0,   229,
     230,   231,   232,   233,     0,     0,     0,     0,   234,   235,
       0,   236,   237,   238,   239,   240,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,   248,   225,  -234,
    -234,   226,   227,     0,     0,     0,     0,   230,   231,   232,
     233,     0,     0,     0,     0,   234,   235,     0,   236,   237,
     238,   239,   240,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   248,   225,     0,     0,   226,   227,
       0,     0,     0,     0,     0,   231,   232,   233,     0,     0,
       0,     0,   234,   235,     0,   236,   237,   238,   239,   240,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,   248,   225,     0,     0,   226,   227,     0,     0,     0,
       0,     0,   231,   232,   233,     0,     0,     0,     0,   234,
     235,     0,   236,   237,   238,   239,   240,     0,     0,     0,
       0,  -234,  -234,  -234,  -234,  -234,  -234,   247,   248
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-492))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-234))

static const yytype_int16 yycheck[] =
{
      16,    17,     4,   177,     0,    81,   145,    91,    83,   255,
      59,   146,    80,   110,    78,    79,    79,    19,   328,   350,
     424,    68,   474,    65,    76,   179,    68,   314,   103,    19,
     216,   311,    89,   524,    81,   327,   328,   174,    80,   524,
      89,   183,    13,   327,   328,    92,    50,    51,    90,    65,
      92,    93,    68,    51,    27,    71,    72,    73,    74,    75,
      76,   327,   328,   260,    80,    81,    82,   327,   328,    61,
      15,   522,    17,   524,    90,    46,    92,    93,    25,   176,
     177,   178,   179,   158,     0,   220,    46,   284,    92,    73,
     165,     0,    26,    77,    92,   170,   197,   198,   199,   318,
     552,   592,    73,   322,    79,   213,    79,   592,   124,   184,
     126,   103,    46,    46,   130,   131,   132,    64,   260,   135,
     221,    46,    82,   125,   261,   141,   142,   143,   144,   204,
      61,    64,    61,   208,    90,   125,   310,    93,    46,    73,
     216,   592,   284,   329,   160,   161,   597,    79,    46,    65,
      61,   438,    68,    46,    50,    51,    65,    64,    54,    68,
     611,    77,    93,    94,    80,    73,   182,   214,   215,   216,
      61,    80,   214,   215,    90,    73,    92,    93,    64,    77,
      73,    90,    52,    92,    93,    71,    93,    94,   327,   328,
      51,    61,    49,    50,    51,   111,    92,   213,   214,   215,
     216,    61,   111,   607,    11,    12,   314,   381,    69,    50,
      51,    18,    19,   310,   103,   525,   435,    14,    15,   327,
     328,     0,    77,    61,    47,   214,   215,   446,    51,   145,
      61,    92,    61,   525,    57,    58,   103,    61,   254,   155,
     287,   525,   326,    46,   320,    64,   155,   294,    10,     8,
     252,   327,   328,   329,   585,   535,   127,   128,   174,   525,
     103,   337,    10,   103,   103,   525,   313,   342,    83,    92,
     338,   287,   347,    15,   290,   291,    54,   431,   294,    66,
     327,   328,   329,   154,   381,    80,   338,   344,    80,   535,
     145,   388,   349,    66,    77,   344,   338,   313,   214,   215,
     349,    88,    89,    90,    10,   214,   215,    77,   383,    80,
      82,    13,   447,   329,   399,   400,    17,    60,     9,   174,
      80,    51,   338,   542,    77,   327,   328,    93,    80,   404,
     405,    10,   407,    10,   431,    10,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   550,     1,     2,     3,   469,   285,
       6,     7,     8,     9,    10,    11,   285,   461,    10,    10,
     444,   444,    18,   299,    20,    52,   525,    59,    10,    77,
      10,    10,   388,    10,    10,   470,    47,    65,    10,   573,
      51,   317,   418,   319,    10,     0,    57,    58,   111,    45,
      46,   256,    48,    49,    50,    51,    52,   525,   327,   328,
     252,   403,   338,   281,   520,    76,   201,   201,   436,   338,
     301,   285,   303,   548,   305,   520,   307,   522,   513,   540,
     548,    92,   458,   552,   299,   546,    47,   215,    82,   525,
      51,    87,    92,   287,   291,   471,    57,    58,   294,    -1,
      -1,    -1,   317,   405,   319,   407,    -1,    -1,    -1,    -1,
      65,    -1,   388,    68,   550,    76,   573,   562,    -1,   388,
     556,    -1,   398,    78,    79,    80,    -1,    88,   563,    -1,
     506,    92,    -1,   568,    -1,    90,    -1,    92,    93,   583,
      -1,    -1,    -1,   550,    -1,    -1,    46,    47,    -1,   594,
      -1,    51,   597,    -1,   385,   531,   111,    57,    58,    -1,
      47,   392,    -1,   525,    51,    -1,   611,   163,    -1,   604,
      57,    58,   548,    73,   550,    -1,    76,    -1,    -1,    -1,
      -1,    81,    -1,    -1,   180,    -1,    73,    -1,    88,    76,
      -1,    -1,    92,    -1,    -1,    -1,   427,    -1,    -1,   195,
     155,    88,    -1,    -1,    -1,    92,    -1,    -1,   204,    -1,
      -1,    -1,   208,    47,   210,   211,   212,    51,    -1,   174,
      -1,    -1,    -1,    57,    58,    -1,   602,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,    -1,   525,    -1,    92,   214,
     215,   563,    -1,   565,    47,   567,   568,    66,    51,    -1,
      69,    70,   503,    -1,    57,    58,    -1,   508,    -1,    -1,
      -1,    -1,    -1,    -1,   560,    -1,    -1,    86,    87,    88,
      89,    90,    -1,    76,    -1,    -1,    -1,    -1,    -1,   295,
      -1,   603,   604,    -1,   606,    88,   537,    -1,    -1,    92,
      -1,    -1,   614,    -1,    -1,    13,   312,    66,    -1,    -1,
      69,    70,    -1,    -1,    -1,   321,    -1,    76,    77,    78,
     285,    -1,    30,    31,    -1,    66,    -1,    86,    87,    88,
      89,    90,    -1,    -1,   299,    -1,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    -1,   350,    86,    87,    88,    89,    90,
      -1,    -1,    -1,    -1,   319,    -1,    -1,   598,    66,    -1,
      -1,    69,    70,    -1,    72,    73,    74,    75,    76,    77,
      78,    -1,    -1,   338,    -1,    83,    84,    -1,    86,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,    -1,   104,   105,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,   388,    28,    29,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    73,
      -1,    -1,    -1,    -1,   480,    79,    -1,    81,    -1,   444,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   504,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,   528,    -1,    -1,    28,    29,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,   585,
      -1,   587,    85,     3,     4,     5,     6,     7,    -1,    92,
      -1,    11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    28,    29,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    79,
      -1,    81,    -1,    -1,    -1,    85,     3,     4,     5,     6,
       7,    -1,    92,    -1,    11,    12,    -1,    -1,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    29,    -1,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    68,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    79,    -1,    81,    11,    12,    -1,    85,    -1,
      16,    -1,    18,    19,    20,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    26,    -1,    62,    63,    30,    31,
      -1,    67,    68,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      69,    70,    -1,    79,    46,    81,    -1,    76,    -1,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    92,    86,    87,    88,
      89,    90,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,
      72,    73,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    83,    84,    -1,    86,    87,    88,    89,    90,    17,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,    -1,   104,   105,    32,    -1,    34,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    30,    31,    62,    63,    -1,    -1,    -1,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    92,    -1,    64,    -1,    66,    -1,
      -1,    69,    70,    -1,    72,    -1,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,    87,
      88,    89,    90,    30,    31,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,    -1,   104,   105,    -1,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    69,    70,    -1,    72,    73,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,
      87,    88,    89,    90,    30,    31,    -1,    -1,    95,    96,
      97,    98,    99,   100,   101,   102,    -1,   104,   105,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    30,    31,    69,    70,    -1,    72,    -1,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    82,    83,    84,    -1,
      86,    87,    88,    89,    90,    -1,    -1,    -1,    -1,    95,
      96,    97,    98,    99,   100,   101,   102,    66,   104,   105,
      69,    70,    71,    72,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    83,    84,    -1,    86,    87,    88,
      89,    90,    30,    31,    -1,    -1,    95,    96,    97,    98,
      99,   100,   101,   102,    -1,   104,   105,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    30,
      31,    69,    70,    -1,    72,    -1,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,    66,   104,   105,    69,    70,
      -1,    72,    -1,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    83,    84,    -1,    86,    87,    88,    89,    90,
      -1,    -1,    -1,    -1,    95,    96,    97,    98,    99,   100,
     101,   102,    -1,   104,   105,    32,    -1,    34,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    85,    -1,
      -1,    88,    -1,    -1,    91,    92,    32,    -1,    34,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    85,
      -1,    -1,    88,    -1,    -1,    91,    92,    32,    -1,    34,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    -1,
      -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      85,    -1,    -1,    88,    32,    -1,    34,    92,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    63,    -1,    -1,    -1,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,
      32,    -1,    34,    -1,    92,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,
      -1,    -1,    -1,    85,    -1,    -1,    32,    -1,    34,    91,
      92,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    85,
      -1,    -1,    32,    -1,    34,    91,    92,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    88,    32,
      -1,    34,    92,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,
      -1,    -1,    85,    -1,    -1,    32,    -1,    34,    -1,    92,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    -1,
      -1,    32,    -1,    34,    91,    92,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    85,    -1,    -1,    32,    -1,    34,
      -1,    92,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    -1,
      -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      85,    -1,    -1,    32,    -1,    34,    -1,    92,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    32,
      -1,    34,    -1,    92,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    92,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    -1,    51,    52,    53,    54,    55,    -1,
      57,    58,    59,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    92,    47,    48,    49,    -1,
      51,    52,    53,    54,    55,    -1,    57,    58,    59,    -1,
      -1,    -1,    63,    -1,    66,    -1,    -1,    69,    70,    -1,
      72,    -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      81,    83,    84,    -1,    86,    87,    88,    89,    90,    -1,
      -1,    92,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,    66,   104,   105,    69,    70,    -1,    -1,    -1,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    83,    84,
      -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,    -1,
      95,    96,    97,    98,    99,   100,   101,   102,    66,   104,
     105,    69,    70,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,    66,    -1,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    -1,    -1,
      -1,    -1,    83,    84,    -1,    86,    87,    88,    89,    90,
      -1,    -1,    -1,    -1,    95,    96,    97,    98,    99,   100,
     101,   102,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,    83,
      84,    -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,
      -1,    95,    96,    97,    98,    99,   100,   101,   102
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    11,    12,    16,    18,
      19,    20,    21,    22,    23,    24,    28,    29,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    62,    63,    67,    68,
      79,    81,    85,    92,   107,   108,   110,   111,   112,   114,
     115,   116,   117,   118,   121,   127,   132,   133,   134,   135,
     136,   171,   177,   178,   179,   180,   182,   183,   184,   185,
     189,   191,   193,   211,   214,   215,   218,   219,   220,   223,
     224,   226,   227,   228,   240,    46,   199,   200,   199,   199,
      50,    51,   119,   120,   136,    46,    73,   144,   197,   201,
     202,   203,   199,   199,   199,   199,   199,   199,    50,   133,
     135,   228,   240,   240,   199,   120,   199,    79,    79,   199,
     199,   199,   199,   199,   199,   199,     0,    11,    12,    18,
      19,   172,   173,   174,   175,    61,   229,   230,    52,    27,
     146,   147,   148,   149,   170,   193,   223,   233,   235,   240,
      76,    88,    91,   137,   220,   221,   222,   223,   232,   234,
     236,   237,   238,   240,   103,   225,   240,   240,   240,   240,
      17,   166,   181,   240,   211,   240,    50,   127,   129,   133,
      51,    92,   131,   135,   224,    69,   131,   214,   223,   240,
      60,   132,   213,   216,   217,   220,   240,    80,   221,   240,
      64,    93,    94,   188,   195,   196,   199,   146,   231,   233,
     229,   232,   233,    30,    31,    66,    69,    70,    72,    74,
      75,    76,    77,    78,    83,    84,    86,    87,    88,    89,
      90,    95,    96,    97,    98,    99,   100,   101,   102,   104,
     105,    46,   188,    10,     8,   141,   142,   143,   201,   108,
     109,   103,   240,   120,   240,   197,   197,   240,   240,   240,
     240,   240,   240,   240,   240,    92,   127,   133,   226,   230,
      46,   187,   197,    77,   109,   150,   198,   188,   240,   240,
     199,   188,   190,   199,   188,    71,   127,   134,   135,   103,
      13,   168,   201,   168,    26,   169,   201,   169,   199,    10,
     240,   203,    25,   186,   122,    61,   103,   204,   123,   103,
     199,    83,   124,   145,   190,   190,   190,   195,   196,   188,
     192,   199,   194,   199,   199,   199,   199,    88,   189,   207,
     240,   121,   212,   220,   223,   240,   121,   212,   220,   223,
     216,   190,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     119,   162,   163,   164,   240,    15,   139,   143,   202,   203,
      80,    80,   150,    10,    47,    51,    57,    58,    73,    76,
      88,    92,   151,   154,   156,   157,   158,   159,   160,   161,
     203,   198,    80,   237,   240,   222,    82,   238,   199,   127,
     128,   135,   197,    13,   197,   197,   197,   168,   166,   199,
     220,   239,   240,    46,    73,   130,   153,   154,   189,   205,
     127,   144,    92,   132,   199,   144,   125,   229,    37,    48,
      53,    63,   110,   111,   112,   113,   132,   136,   189,   215,
     220,   226,   228,   113,   220,   216,    60,    80,   132,   206,
     211,   188,   146,   146,   192,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   168,    71,   165,   188,   197,     9,   140,
     108,   197,   133,   152,   160,   160,    77,    77,   151,   155,
     188,   155,   188,   155,   188,    93,    80,   240,    14,   138,
     139,   176,   138,    10,    10,   197,    10,   169,   144,   205,
     154,    10,   126,   131,    10,   144,   240,   190,   188,   240,
     191,   208,   209,   210,   199,   197,   199,   240,   197,    10,
     188,    77,    76,   159,   160,   156,   160,   156,   157,   158,
     113,   199,    10,   240,    10,   139,   166,   167,   197,    10,
     190,   144,    10,   190,   207,   216,   210,    65,   132,   133,
     160,   155,   188,   155,   188,   155,   155,   188,   168,    10,
      10,   192,   199,   156,   157,   160,   156,   197,   240,   155,
     155,   188,   155,   138,   156,   155
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, parser); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct parser_t * parser)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct parser_t * parser;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (parser);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct parser_t * parser)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct parser_t * parser;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, struct parser_t * parser)
#else
static void
yy_reduce_print (yyvsp, yyrule, parser)
    YYSTYPE *yyvsp;
    int yyrule;
    struct parser_t * parser;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parser); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, struct parser_t * parser)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parser)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    struct parser_t * parser;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parser);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (struct parser_t * parser);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (struct parser_t * parser)
#else
int
yyparse (parser)
    struct parser_t * parser;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 207 "../parser.y"
    { parser->ast = NULL; YYACCEPT; }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 209 "../parser.y"
    {
    if (parser->errors[0].valid == 1) {
      free_ast(parser->ast);
      parser->ast = NULL;
    } else
      parser->ast = (yyvsp[(1) - (1)].n);
    YYACCEPT;
  }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 221 "../parser.y"
    { fix_mrhs((yyval.n)); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 223 "../parser.y"
    {
    (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    parser->call_args = 0;
  }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 228 "../parser.y"
    { (yyval.n) = ALLOC_MOD(token_if, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);     }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 229 "../parser.y"
    { (yyval.n) = ALLOC_MOD(token_unless, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 230 "../parser.y"
    { (yyval.n) = ALLOC_MOD(token_while, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);  }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 231 "../parser.y"
    { (yyval.n) = ALLOC_MOD(token_until, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);  }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 235 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 236 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 239 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 240 "../parser.y"
    { (yyval.n) = ALLOC_N(token_numeric, NULL, NULL);   }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 241 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 243 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_string, NULL, NULL); POP_STR;
    multiple_string(parser, (yyval.n));
  }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 247 "../parser.y"
    { (yyval.n) = ALLOC_N(token_regexp, NULL, NULL); POP_STR;    }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 248 "../parser.y"
    { (yyval.n) = ALLOC_N(token_heredoc, NULL, NULL);   }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 249 "../parser.y"
    { (yyval.n) = ALLOC_N(token_backtick, NULL, NULL); POP_STR;  }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 250 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL);    }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 265 "../parser.y"
    {
    CONCAT_STRING;
    pop_pos(parser, NULL);
  }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 271 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 272 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 273 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 274 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 277 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 278 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 279 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 282 "../parser.y"
    { (yyval.n) = ALLOC_N(token_numeric, NULL, NULL);   }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 283 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 285 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_string, NULL, NULL); POP_STR;
    multiple_string(parser, (yyval.n));
  }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 289 "../parser.y"
    { (yyval.n) = ALLOC_N(token_regexp, NULL, NULL); POP_STR;   }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 290 "../parser.y"
    { (yyval.n) = ALLOC_N(token_heredoc, NULL, NULL);   }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 291 "../parser.y"
    { (yyval.n) = ALLOC_N(token_backtick, NULL, NULL); POP_STR; }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 292 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 293 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL);    }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 296 "../parser.y"
    { (yyval.n) = ALLOC_N(token_break, NULL, NULL);   }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 297 "../parser.y"
    { (yyval.n) = ALLOC_N(token_redo, NULL, NULL);    }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 298 "../parser.y"
    { (yyval.n) = ALLOC_N(token_retry, NULL, NULL);   }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 299 "../parser.y"
    { (yyval.n) = ALLOC_N(token_next, NULL, NULL);    }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 300 "../parser.y"
    { (yyval.n) = ALLOC_N(token_undef, NULL, (yyvsp[(2) - (2)].n)); fix_mrhs((yyval.n));      }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 301 "../parser.y"
    { (yyval.n) = ALLOC_N(token_alias, (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)); copy_end((yyval.n),(yyvsp[(3) - (3)].n));     }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 302 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 303 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 306 "../parser.y"
    { (yyval.n) = ALLOC_N(token_yield, NULL, NULL);   }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 307 "../parser.y"
    { (yyval.n) = ALLOC_N(token_yield, (yyvsp[(2) - (2)].n), NULL);     }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 310 "../parser.y"
    { (yyval.n) = ALLOC_N(token_return, NULL, NULL);  }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 311 "../parser.y"
    { (yyval.n) = ALLOC_N(token_return, (yyvsp[(2) - (2)].n), NULL); copy_end((yyval.n), (yyvsp[(2) - (2)].n));   }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 314 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 315 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 318 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 319 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 320 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 327 "../parser.y"
    {
    (yyval.n) = ALLOC_C(token_if, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
    pop_start(parser, (yyval.n));
  }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 335 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_unless, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 342 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_while, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 349 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_until, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 356 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_case, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 361 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_case, NULL, (yyvsp[(2) - (3)].n), NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 366 "../parser.y"
    {
      (yyval.n) = ALLOC_N(token_up_begin, (yyvsp[(3) - (4)].n), NULL);
      pop_pos(parser, NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 372 "../parser.y"
    {
      (yyval.n) = ALLOC_N(token_up_end, (yyvsp[(3) - (4)].n), NULL);
      pop_pos(parser, NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 378 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_for, (yyvsp[(4) - (7)].n), (yyvsp[(6) - (7)].n), (yyvsp[(2) - (7)].n));
      pop_pos(parser, NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 384 "../parser.y"
    {
      (yyval.n) = ALLOC_N(token_exception, (yyvsp[(2) - (3)].n), NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 389 "../parser.y"
    {
      parser->in_def++;
    }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 393 "../parser.y"
    {
      parser->in_def--;
      (yyval.n) = ALLOC_C(token_function, (yyvsp[(2) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(4) - (6)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 399 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "module definition in method body");
    }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 405 "../parser.y"
    {
      (yyval.n) = ALLOC_N(token_module, (yyvsp[(4) - (5)].n), (yyvsp[(2) - (5)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 410 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 416 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_class, NULL, (yyvsp[(4) - (5)].n), (yyvsp[(2) - (5)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 421 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 427 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_class, (yyvsp[(3) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(2) - (6)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 432 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 438 "../parser.y"
    {
      (yyval.n) = ALLOC_N(token_singleton_class, (yyvsp[(6) - (7)].n), (yyvsp[(4) - (7)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 444 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 445 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 448 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 449 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 453 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 457 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 460 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 461 "../parser.y"
    { (yyval.n) = 0; }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 464 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 465 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 467 "../parser.y"
    {
    yyerror(parser, "class/module name must be CONSTANT");
  }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 472 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 473 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 474 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 475 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 476 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 479 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 482 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; (yyval.n)->endCol--; }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 485 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 488 "../parser.y"
    { (yyval.n) = ALLOC_N(token_symbol, NULL, NULL); POP_STACK; }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 491 "../parser.y"
    { (yyval.n) = ALLOC_N(token_symbol, NULL, NULL); POP_STACK; }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 498 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_if, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
      struct pos_t tp = { (yyval.n)->startLine, (yyval.n)->endLine, (yyval.n)->startCol, (yyval.n)->endCol };

      pop_pos(parser, (yyval.n));
      push_pos(parser, tp);
    }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 507 "../parser.y"
    { (yyval.n) = 0; }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 509 "../parser.y"
    {
    (yyval.n) = ALLOC_C(token_if, NULL, (yyvsp[(2) - (2)].n), NULL);
    struct pos_t tp = { (yyval.n)->startLine, (yyval.n)->endLine, (yyval.n)->startCol, (yyval.n)->endCol };

    pop_pos(parser, (yyval.n));
    push_pos(parser, tp);
  }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 518 "../parser.y"
    { (yyval.n) = 0; }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 520 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_ensure, (yyvsp[(2) - (2)].n), NULL);
    struct pos_t tp = { (yyval.n)->startLine, (yyval.n)->endLine, (yyval.n)->startCol, (yyval.n)->endCol };

    pop_pos(parser, (yyval.n));
    push_pos(parser, tp);    
  }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 529 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 530 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 533 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 534 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 538 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_rescue, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
    struct pos_t tp = { (yyval.n)->startLine, (yyval.n)->endLine, (yyval.n)->startCol, (yyval.n)->endCol };

    pop_pos(parser, (yyval.n));
    push_pos(parser, tp);
  }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 548 "../parser.y"
    {
    (yyval.n) = alloc_ensure(token_body, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
    if ((yyvsp[(1) - (4)].n) != NULL) {
      if ((yyvsp[(1) - (4)].n)->last != NULL) {
        copy_range((yyval.n), (yyvsp[(1) - (4)].n), (yyvsp[(1) - (4)].n)->last);
      } else {
        copy_range((yyval.n), (yyvsp[(1) - (4)].n), (yyvsp[(1) - (4)].n));
      }
    }
  }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 560 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 563 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 564 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 567 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 568 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 572 "../parser.y"
    {
    pop_start(parser, parser->last_pos);
    (yyval.n) = ALLOC_N(token_block, (yyvsp[(3) - (4)].n), (yyvsp[(2) - (4)].n));
    if ((yyvsp[(3) - (4)].n)->last != NULL) {
      copy_end((yyval.n), (yyvsp[(3) - (4)].n)->last);
    } else {
      copy_end((yyval.n), (yyvsp[(3) - (4)].n));
    }
  }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 582 "../parser.y"
    {
    pop_pos(parser, parser->last_pos);
    (yyval.n) = ALLOC_N(token_block, (yyvsp[(2) - (3)].n), NULL);
    if ((yyvsp[(2) - (3)].n)->last != NULL) {
      copy_end((yyval.n), (yyvsp[(2) - (3)].n)->last);
    } else {
      copy_end((yyval.n), (yyvsp[(2) - (3)].n));
    }
  }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 594 "../parser.y"
    {
    pop_pos(parser, parser->last_pos);
    (yyval.n) = ALLOC_N(token_block, (yyvsp[(4) - (5)].n), (yyvsp[(3) - (5)].n));
    if ((yyvsp[(4) - (5)].n)->last != NULL) {
      copy_end((yyval.n), (yyvsp[(4) - (5)].n)->last);
    } else {
      copy_end((yyval.n), (yyvsp[(4) - (5)].n));
    }
  }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 604 "../parser.y"
    {
    pop_pos(parser, parser->last_pos);
    (yyval.n) = ALLOC_N(token_block, (yyvsp[(2) - (3)].n), NULL);
    if ((yyvsp[(2) - (3)].n)->last != NULL) {
      copy_end((yyval.n), (yyvsp[(2) - (3)].n)->last);
    } else {
      copy_end((yyval.n), (yyvsp[(2) - (3)].n));
    }
  }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 616 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n));
    copy_range((yyval.n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n));
  }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 621 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, NULL, (yyvsp[(2) - (3)].n));
    copy_range((yyval.n), (yyvsp[(2) - (3)].n), (yyvsp[(2) - (3)].n));
  }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 626 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);
    copy_range((yyval.n), (yyvsp[(2) - (3)].n), (yyvsp[(2) - (3)].n));
  }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 632 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 635 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 636 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 639 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 640 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 643 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 644 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 646 "../parser.y"
    {
      (yyval.n) = create_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 649 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 651 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 654 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 656 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), create_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 660 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 664 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 668 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 673 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (8)].n), concat_list((yyvsp[(3) - (8)].n), create_list((yyvsp[(5) - (8)].n), update_list((yyvsp[(7) - (8)].n), (yyvsp[(8) - (8)].n)))));
    }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 677 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 682 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 683 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 686 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 687 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 690 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 694 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 700 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 701 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 704 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 705 "../parser.y"
    { (yyval.n) = 0; }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 709 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a constant");
    (yyval.n) = 0;
  }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 714 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be an instance variable");
    (yyval.n) = 0;
  }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 719 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a global variable");
    (yyval.n) = 0;
  }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 724 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a class variable");
    (yyval.n) = 0;
  }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 730 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 731 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 735 "../parser.y"
    {
    (yyval.n) = alloc_node(token_rescue_arg, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    if ((yyvsp[(2) - (2)].n) != NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    } else {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(1) - (2)].n));
    }
  }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 745 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 746 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 749 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 750 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 754 "../parser.y"
    {
    /* The following statements fixes some issues around positions. */
    struct node * n = ALLOC_N(token_object, NULL, NULL);
    pop_pos(parser, n);
    struct pos_t t = {n->startLine, n->endLine, n->startCol, n->endCol};
    (yyval.n) = ALLOC_C(token_when, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
    push_pos(parser, t);
  }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 769 "../parser.y"
    { pop_pos(parser, NULL);  }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 770 "../parser.y"
    { pop_pos(parser, NULL);  }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 775 "../parser.y"
    {
    if (!parser->call_args) {
      pop_pos(parser, parser->last_pos);
      parser->call_args = 1;
    } else
      pop_pos(parser, NULL);
  }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 785 "../parser.y"
    {
    struct node * n = parser->last_pos;
    struct pos_t tp = { n->startLine, n->endLine, n->startCol, n->endCol };

    if (parser->call_args) {
      pop_pos(parser, parser->last_pos);
      push_pos(parser, tp);
      parser->call_args = 0;
    }
  }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 800 "../parser.y"
    { manual_fix(); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 803 "../parser.y"
    { manual_fix(); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 806 "../parser.y"
    { manual_fix(); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 809 "../parser.y"
    { manual_fix(); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 830 "../parser.y"
    { parser->call_args = 1;  }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 876 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 877 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 880 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 911 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 912 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 916 "../parser.y"
    {
    /* TODO: Implement a better way to do this, check_lhs can be expensive :( */
    if (check_lhs((yyvsp[(1) - (1)].n)))
      (yyval.n) = (yyvsp[(1) - (1)].n);
    else {
      (yyval.n) = 0;
      yyerror(parser, "syntax error, unexpected '=', expecting $end");
    }
  }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 926 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);
    if ((yyvsp[(2) - (3)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(2) - (3)].n), (yyvsp[(2) - (3)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(2) - (3)].n), (yyvsp[(2) - (3)].n));
    }
  }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 934 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 936 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, NULL, NULL);
    (yyval.n)->startLine = (yyval.n)->endLine = parser->auxiliar.startLine;
    (yyval.n)->startCol = parser->auxiliar.startCol;
    (yyval.n)->endCol = (yyval.n)->startCol + 1;
    parser->auxiliar.endLine = -1;
  }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 945 "../parser.y"
    { (yyval.n) = 0; }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 946 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 949 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 950 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 953 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n); pop_pos(parser, NULL); }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 956 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 957 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 958 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 961 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 962 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 965 "../parser.y"
    { (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 966 "../parser.y"
    { (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 967 "../parser.y"
    { (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 968 "../parser.y"
    { (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 971 "../parser.y"
    { (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));   }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 972 "../parser.y"
    { (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 974 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
    parser->call_args = 0;
  }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 980 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
    parser->call_args = 0;
  }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 985 "../parser.y"
    { (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 986 "../parser.y"
    { (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 987 "../parser.y"
    { (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 988 "../parser.y"
    { (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  }
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 991 "../parser.y"
    { (yyval.n) = ALLOC_N(token_array, NULL, NULL); }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 992 "../parser.y"
    { (yyval.n) = ALLOC_N(token_array, (yyvsp[(2) - (3)].n), NULL); fix_mrhs_left((yyval.n));  }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 993 "../parser.y"
    { (yyval.n) = ALLOC_N(token_array, NULL, NULL); POP_STR; }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 997 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 998 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 999 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1002 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1003 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 1007 "../parser.y"
    {
    struct node * n = (yyvsp[(3) - (5)].n);
    n->next = (yyvsp[(5) - (5)].n);
    (yyval.n) = alloc_node(token_array_value, (yyvsp[(1) - (5)].n), n);
    if ((yyvsp[(5) - (5)].n) != NULL) {
      if ((yyvsp[(5) - (5)].n)->last != NULL) {
        copy_range((yyval.n), (yyvsp[(1) - (5)].n), (yyvsp[(5) - (5)].n)->last);
      } else {
        copy_range((yyval.n), (yyvsp[(1) - (5)].n), (yyvsp[(5) - (5)].n));
      }
    } else {
      copy_range((yyval.n), (yyvsp[(1) - (5)].n), (yyvsp[(3) - (5)].n));
    }
  }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 1028 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_object, NULL, NULL);
    (yyval.n)->endCol--;
    POP_STACK;
  }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 1035 "../parser.y"
    { (yyval.n) = ALLOC_N(token_hash, NULL, NULL); pop_pos(parser, NULL); }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 1037 "../parser.y"
    {
    pop_pos(parser, parser->last_pos);
    (yyval.n) = ALLOC_N(token_hash, (yyvsp[(2) - (3)].n), NULL);
    fix_mrhs_left((yyval.n));
  }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 1044 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 1045 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 1049 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));
    copy_range((yyval.n), (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));
  }
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 1054 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  }
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 1061 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    if ((yyvsp[(2) - (2)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    }
  }
    break;

  case 267:

/* Line 1806 of yacc.c  */
#line 1070 "../parser.y"
    {
    if (parser->last_is_paren) {
      yyerror(parser, "bad parameter list");
      (yyval.n) = 0;
    } else {
      (yyval.n) = (yyvsp[(1) - (2)].n);
      (yyval.n)->r = (yyvsp[(2) - (2)].n);
    }
  }
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 1080 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    if ((yyvsp[(2) - (2)].n) == NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(1) - (2)].n));
    } else {
      if ((yyvsp[(2) - (2)].n)->last != NULL) {
        copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)->last);
      } else {
        copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
      }
    }
  }
    break;

  case 269:

/* Line 1806 of yacc.c  */
#line 1095 "../parser.y"
    {
    struct node * n = alloc_node(token_object, (yyvsp[(1) - (2)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(2) - (2)].n));
    if ((yyvsp[(2) - (2)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    }
  }
    break;

  case 270:

/* Line 1806 of yacc.c  */
#line 1105 "../parser.y"
    {
    struct node * n = alloc_node(token_object, (yyvsp[(1) - (3)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(3) - (3)].n));
    copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  }
    break;

  case 271:

/* Line 1806 of yacc.c  */
#line 1112 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 272:

/* Line 1806 of yacc.c  */
#line 1113 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 273:

/* Line 1806 of yacc.c  */
#line 1117 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
    if ((yyvsp[(2) - (3)].n) == NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(1) - (3)].n));
    } else {
      if ((yyvsp[(2) - (3)].n)->last != NULL) {
        copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n)->last);
      } else {
        copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
      }
    }
  }
    break;

  case 274:

/* Line 1806 of yacc.c  */
#line 1130 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
    if ((yyvsp[(2) - (3)].n) == NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(1) - (3)].n));
    } else {
      if ((yyvsp[(2) - (3)].n)->last != NULL) {
        copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n)->last);
      } else {
        copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
      }
    }
  }
    break;

  case 275:

/* Line 1806 of yacc.c  */
#line 1144 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 276:

/* Line 1806 of yacc.c  */
#line 1148 "../parser.y"
    {
    struct node * n = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(2) - (2)].n));
    if ((yyvsp[(2) - (2)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    }
  }
    break;

  case 277:

/* Line 1806 of yacc.c  */
#line 1158 "../parser.y"
    {
    struct node * n = alloc_node(token_method_call, (yyvsp[(2) - (4)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(4) - (4)].n));
    if ((yyvsp[(4) - (4)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
    }
  }
    break;

  case 278:

/* Line 1806 of yacc.c  */
#line 1168 "../parser.y"
    {
    (yyval.n) = pop_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  }
    break;

  case 279:

/* Line 1806 of yacc.c  */
#line 1173 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 280:

/* Line 1806 of yacc.c  */
#line 1174 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 281:

/* Line 1806 of yacc.c  */
#line 1178 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 0;
  }
    break;

  case 282:

/* Line 1806 of yacc.c  */
#line 1183 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 1;
  }
    break;

  case 283:

/* Line 1806 of yacc.c  */
#line 1189 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 284:

/* Line 1806 of yacc.c  */
#line 1190 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 285:

/* Line 1806 of yacc.c  */
#line 1193 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 286:

/* Line 1806 of yacc.c  */
#line 1194 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 287:

/* Line 1806 of yacc.c  */
#line 1197 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 288:

/* Line 1806 of yacc.c  */
#line 1199 "../parser.y"
    {
    (yyval.n) = (yyvsp[(1) - (1)].n);
    parser->call_args = 1;
  }
    break;

  case 289:

/* Line 1806 of yacc.c  */
#line 1205 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 290:

/* Line 1806 of yacc.c  */
#line 1206 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 291:

/* Line 1806 of yacc.c  */
#line 1210 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 292:

/* Line 1806 of yacc.c  */
#line 1211 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 293:

/* Line 1806 of yacc.c  */
#line 1214 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 294:

/* Line 1806 of yacc.c  */
#line 1215 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 295:

/* Line 1806 of yacc.c  */
#line 1219 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 296:

/* Line 1806 of yacc.c  */
#line 1220 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 297:

/* Line 1806 of yacc.c  */
#line 1222 "../parser.y"
    {
    (yyval.n) = alloc_node(token_hash, (yyvsp[(1) - (1)].n), NULL);
    if ((yyvsp[(1) - (1)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (1)].n), (yyvsp[(1) - (1)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(1) - (1)].n), (yyvsp[(1) - (1)].n));
    }
  }
    break;

  case 298:

/* Line 1806 of yacc.c  */
#line 1232 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 299:

/* Line 1806 of yacc.c  */
#line 1233 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 300:

/* Line 1806 of yacc.c  */
#line 1234 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 301:

/* Line 1806 of yacc.c  */
#line 1238 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 302:

/* Line 1806 of yacc.c  */
#line 1239 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 303:

/* Line 1806 of yacc.c  */
#line 1242 "../parser.y"
    { (yyval.n) = ALLOC_N(token_plus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    }
    break;

  case 304:

/* Line 1806 of yacc.c  */
#line 1243 "../parser.y"
    { (yyval.n) = ALLOC_N(token_minus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   }
    break;

  case 305:

/* Line 1806 of yacc.c  */
#line 1244 "../parser.y"
    { (yyval.n) = ALLOC_N(token_mul, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 306:

/* Line 1806 of yacc.c  */
#line 1245 "../parser.y"
    { (yyval.n) = ALLOC_N(token_div, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 307:

/* Line 1806 of yacc.c  */
#line 1246 "../parser.y"
    { (yyval.n) = ALLOC_N(token_mod, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 308:

/* Line 1806 of yacc.c  */
#line 1247 "../parser.y"
    { (yyval.n) = ALLOC_N(token_exp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 309:

/* Line 1806 of yacc.c  */
#line 1248 "../parser.y"
    { (yyval.n) = ALLOC_N(token_bit_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); }
    break;

  case 310:

/* Line 1806 of yacc.c  */
#line 1249 "../parser.y"
    { (yyval.n) = ALLOC_N(token_bit_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 311:

/* Line 1806 of yacc.c  */
#line 1250 "../parser.y"
    { (yyval.n) = ALLOC_N(token_bit_xor, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); }
    break;

  case 312:

/* Line 1806 of yacc.c  */
#line 1251 "../parser.y"
    { (yyval.n) = ALLOC_N(token_lshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 313:

/* Line 1806 of yacc.c  */
#line 1252 "../parser.y"
    { (yyval.n) = ALLOC_N(token_rshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 314:

/* Line 1806 of yacc.c  */
#line 1253 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  }
    break;

  case 315:

/* Line 1806 of yacc.c  */
#line 1254 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n); fix_mrhs((yyval.n));  }
    break;

  case 316:

/* Line 1806 of yacc.c  */
#line 1255 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  }
    break;

  case 317:

/* Line 1806 of yacc.c  */
#line 1256 "../parser.y"
    { (yyval.n) = ALLOC_N(token_cmp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 318:

/* Line 1806 of yacc.c  */
#line 1257 "../parser.y"
    { (yyval.n) = ALLOC_N(token_eq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      }
    break;

  case 319:

/* Line 1806 of yacc.c  */
#line 1258 "../parser.y"
    { (yyval.n) = ALLOC_N(token_neq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 320:

/* Line 1806 of yacc.c  */
#line 1259 "../parser.y"
    { (yyval.n) = ALLOC_N(token_eqq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 321:

/* Line 1806 of yacc.c  */
#line 1260 "../parser.y"
    { (yyval.n) = ALLOC_N(token_match, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   }
    break;

  case 322:

/* Line 1806 of yacc.c  */
#line 1261 "../parser.y"
    { (yyval.n) = ALLOC_N(token_nmatch, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 323:

/* Line 1806 of yacc.c  */
#line 1262 "../parser.y"
    { (yyval.n) = ALLOC_N(token_greater, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); }
    break;

  case 324:

/* Line 1806 of yacc.c  */
#line 1263 "../parser.y"
    { (yyval.n) = ALLOC_N(token_lesser, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 325:

/* Line 1806 of yacc.c  */
#line 1264 "../parser.y"
    { (yyval.n) = ALLOC_N(token_geq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 326:

/* Line 1806 of yacc.c  */
#line 1265 "../parser.y"
    { (yyval.n) = ALLOC_N(token_leq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 327:

/* Line 1806 of yacc.c  */
#line 1266 "../parser.y"
    { (yyval.n) = ALLOC_N(token_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      }
    break;

  case 328:

/* Line 1806 of yacc.c  */
#line 1267 "../parser.y"
    { (yyval.n) = ALLOC_N(token_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 329:

/* Line 1806 of yacc.c  */
#line 1268 "../parser.y"
    { (yyval.n) = ALLOC_N(token_kw_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   }
    break;

  case 330:

/* Line 1806 of yacc.c  */
#line 1269 "../parser.y"
    { (yyval.n) = ALLOC_N(token_kw_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 331:

/* Line 1806 of yacc.c  */
#line 1270 "../parser.y"
    { (yyval.n) = ALLOC_N(token_dot2, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    }
    break;

  case 332:

/* Line 1806 of yacc.c  */
#line 1271 "../parser.y"
    { (yyval.n) = ALLOC_N(token_dot3, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    }
    break;

  case 333:

/* Line 1806 of yacc.c  */
#line 1273 "../parser.y"
    {
    (yyval.n) = ALLOC_C(token_ternary, (yyvsp[(1) - (8)].n), (yyvsp[(4) - (8)].n), (yyvsp[(8) - (8)].n));
  }
    break;

  case 334:

/* Line 1806 of yacc.c  */
#line 1276 "../parser.y"
    { (yyval.n) = ALLOC_N(token_kw_not, (yyvsp[(3) - (3)].n), NULL);}
    break;

  case 335:

/* Line 1806 of yacc.c  */
#line 1277 "../parser.y"
    { (yyval.n) = ALLOC_N(token_neg, (yyvsp[(3) - (3)].n), NULL);   }
    break;

  case 336:

/* Line 1806 of yacc.c  */
#line 1278 "../parser.y"
    { (yyval.n) = ALLOC_N(token_not, (yyvsp[(3) - (3)].n), NULL);   }
    break;

  case 337:

/* Line 1806 of yacc.c  */
#line 1279 "../parser.y"
    { (yyval.n) = ALLOC_N(token_unary_plus, (yyvsp[(3) - (3)].n), NULL);  }
    break;

  case 338:

/* Line 1806 of yacc.c  */
#line 1280 "../parser.y"
    { (yyval.n) = ALLOC_N(token_unary_minus, (yyvsp[(3) - (3)].n), NULL); }
    break;

  case 339:

/* Line 1806 of yacc.c  */
#line 1281 "../parser.y"
    { (yyval.n) = ALLOC_N(token_defined, (yyvsp[(3) - (3)].n), NULL); copy_end((yyval.n), (yyvsp[(3) - (3)].n));  }
    break;

  case 340:

/* Line 1806 of yacc.c  */
#line 1282 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 341:

/* Line 1806 of yacc.c  */
#line 1283 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 342:

/* Line 1806 of yacc.c  */
#line 1284 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 343:

/* Line 1806 of yacc.c  */
#line 1285 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;



/* Line 1806 of yacc.c  */
#line 4982 "../parser.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (parser, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (parser, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, parser);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (parser, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, parser);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parser);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 1288 "../parser.y"

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
}

void free_parser(struct parser_t * p)
{
  int index;

  for (index = 0; index < p->sp; index++)
    free(p->stack[index]);
  free(p->pos_stack);
  free(p->blob);
  free(p->name);
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
  int step = 0;
  int ax = 0;

  c += 2;
  *curs += 2;
  while (*c != '}') {
    step = utf8_charsize(c);
    ax += step - 1;
    while (step-- > 0) {
      *ptr++ = *c++;
      *curs = *curs + 1;
    }
    if (*curs >= p->length || *c == '"') {
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
  struct pos_t tokp = {-1, -1, -1, -1};

  curs = parser->cursor;
  len = parser->length;
  if (curs >= len) {
    parser->eof_reached = 1;
    return 0;
  }
  c = parser->blob + curs;

  /* Ignore whitespaces */
  for (; isspace(*c) && *c != '\n'; ++c, ++curs, parser->column++, parser->cursor++);

  if (*c == '#') {
    for (; *c != '\n' && curs < len; ++c, ++curs);
    t = EOL;
  } else if (*c == '\n') {
    t = EOL;
    parser->no_block = 0;
    parser->expr_seen = 0;
    parser->dot_seen = 0;
    parser->column = -1;
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
    int step = 0;
    int ax = 0;
    unsigned char isConstant = 1;

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
    } while (curs < len && isNotSep(c));
    *ptr = '\0';
    parser->column -= ax;

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
      t = tSCOPE;
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
  p->errors[p->error_index].msg = strdup(s);
  p->errors[p->error_index].line = p->line;
  p->errors[p->error_index].col = p->column;
  p->errors[p->error_index].valid = 1;
  p->error_index++;
  p->eof_reached = 1;
}

RubyAst * rb_compile_file(const char * path, const char * contents)
{
  struct parser_t p;
  RubyAst * result;

  /* Initialize parser */
  init_parser(&p);
  p.name = strdup(path);
  if (!contents && !retrieve_source(&p, path))
    return NULL;

  /* Let's parse */
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
      #ifdef cplusplus
        result->errors[0] = p.errors[0];
        result->errors[1] = p.errors[1];
      #else
        result->errors = p.errors;
      #endif
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

