/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.3"

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

/* Line 189 of yacc.c  */
#line 27 "../parser.y"

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
  struct node * string_names;
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
void update_contents(struct parser_t * p, const char * contents);
int check_lhs(struct node * n);
void pop_stack(struct parser_t * parser, struct node * n);
void pop_string(struct parser_t * parser, struct node * n);



/* Line 189 of yacc.c  */
#line 159 "../parser.c"

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
     COMMENT = 308,
     REGEXP = 309,
     MCALL = 310,
     ARRAY = 311,
     SARY = 312,
     IVAR = 313,
     GLOBAL = 314,
     tLBRACKET = 315,
     tRBRACKET = 316,
     tDOT = 317,
     tTILDE = 318,
     tBACKTICK = 319,
     tCOMMA = 320,
     tCOLON = 321,
     tPOW = 322,
     tUMINUS = 323,
     tUPLUS = 324,
     tLSHIFT = 325,
     tRSHIFT = 326,
     tASSOC = 327,
     tQUESTION = 328,
     tSEMICOLON = 329,
     tOR = 330,
     tAND = 331,
     tAND_BIT = 332,
     tOR_BIT = 333,
     tXOR_BIT = 334,
     tLBRACE = 335,
     tRBRACE = 336,
     tLPAREN = 337,
     tRPAREN = 338,
     tLESSER = 339,
     tGREATER = 340,
     tNOT = 341,
     tPLUS = 342,
     tMINUS = 343,
     tMUL = 344,
     tDIV = 345,
     tMOD = 346,
     KEY = 347,
     CONST = 348,
     tASGN = 349,
     tOP_ASGN = 350,
     tCMP = 351,
     tEQ = 352,
     tEQQ = 353,
     tNEQ = 354,
     tMATCH = 355,
     tNMATCH = 356,
     tGEQ = 357,
     tLEQ = 358,
     tSCOPE = 359,
     tDOT3 = 360,
     tDOT2 = 361
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 116 "../parser.y"
  struct node * n;  


/* Line 214 of yacc.c  */
#line 305 "../parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 317 "../parser.c"

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  136
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2442

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  123
/* YYNRULES -- Number of rules.  */
#define YYNRULES  322
/* YYNRULES -- Number of states.  */
#define YYNSTATES  587

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   361

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
     105,   106
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    16,    18,
      22,    26,    30,    34,    36,    38,    40,    44,    46,    48,
      50,    52,    54,    56,    58,    60,    62,    64,    66,    68,
      70,    72,    74,    76,    78,    81,    83,    85,    87,    89,
      91,    93,    95,    97,    99,   101,   103,   105,   107,   109,
     111,   113,   115,   117,   119,   122,   126,   128,   130,   132,
     135,   137,   140,   142,   146,   148,   150,   152,   159,   166,
     172,   178,   184,   188,   193,   198,   206,   210,   211,   218,
     219,   225,   226,   233,   234,   242,   244,   246,   250,   252,
     255,   257,   259,   261,   263,   265,   267,   269,   271,   273,
     275,   277,   279,   281,   283,   289,   290,   293,   294,   297,
     298,   300,   302,   305,   310,   315,   316,   320,   321,   323,
     325,   327,   332,   336,   342,   346,   351,   355,   359,   362,
     364,   368,   370,   374,   377,   380,   385,   388,   393,   396,
     403,   408,   415,   420,   429,   436,   437,   441,   443,   447,
     450,   454,   456,   460,   462,   464,   466,   468,   470,   472,
     473,   475,   478,   480,   484,   485,   489,   495,   497,   499,
     501,   503,   506,   508,   510,   513,   516,   519,   522,   525,
     528,   531,   534,   537,   540,   543,   546,   547,   549,   552,
     555,   558,   561,   564,   567,   570,   573,   576,   580,   582,
     585,   586,   588,   590,   593,   595,   597,   599,   602,   603,
     605,   607,   609,   611,   613,   617,   620,   622,   626,   629,
     631,   632,   634,   636,   639,   643,   645,   648,   652,   654,
     658,   662,   666,   670,   674,   678,   682,   687,   692,   696,
     700,   704,   708,   711,   715,   717,   719,   721,   723,   725,
     729,   735,   737,   740,   744,   746,   750,   755,   759,   762,
     765,   768,   772,   776,   780,   784,   787,   792,   795,   797,
     800,   803,   806,   807,   809,   811,   813,   815,   819,   821,
     823,   825,   827,   829,   834,   839,   844,   849,   854,   859,
     864,   869,   874,   879,   884,   888,   892,   896,   901,   906,
     911,   916,   921,   926,   931,   936,   941,   946,   951,   956,
     961,   966,   971,   976,   985,   989,   993,   997,  1001,  1005,
    1009,  1012,  1014
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     108,     0,    -1,    46,    -1,   109,    -1,   117,    -1,   122,
      -1,   208,    -1,   217,   145,    -1,   214,    -1,   109,    11,
     229,    -1,   109,    12,   229,    -1,   109,    18,   229,    -1,
     109,    19,   229,    -1,   229,    -1,    53,    -1,   109,    -1,
     110,   196,   109,    -1,   131,    -1,    48,    -1,   135,    -1,
     113,    -1,    54,    -1,    37,    -1,    64,    -1,   112,    -1,
      39,    -1,    38,    -1,    40,    -1,    41,    -1,    42,    -1,
      43,    -1,    44,    -1,    45,    -1,    52,    -1,   113,    52,
      -1,   111,    -1,   209,    -1,   219,    -1,   221,    -1,   131,
      -1,   219,    -1,   221,    -1,    48,    -1,   135,    -1,   113,
      -1,    54,    -1,    37,    -1,    64,    -1,   209,    -1,   112,
      -1,    21,    -1,    23,    -1,    24,    -1,    22,    -1,     6,
     120,    -1,    33,   121,   121,    -1,   118,    -1,   119,    -1,
      29,    -1,    29,   229,    -1,    28,    -1,    28,   229,    -1,
     121,    -1,   121,   182,   120,    -1,    51,    -1,    50,    -1,
     135,    -1,   169,   229,   167,   191,   137,    10,    -1,   171,
     229,   167,   191,   137,    10,    -1,   172,   229,   168,   191,
      10,    -1,   173,   229,   168,   191,    10,    -1,   174,   229,
     197,   165,    10,    -1,   174,   165,    10,    -1,    35,    80,
     191,    81,    -1,    36,    80,   191,    81,    -1,   176,   205,
     180,   228,   168,   191,    10,    -1,     7,   143,    10,    -1,
      -1,   177,   128,   123,   129,   143,    10,    -1,    -1,   178,
     130,   124,   143,    10,    -1,    -1,   179,   130,   144,   125,
     143,    10,    -1,    -1,   179,    70,   193,   131,   126,   143,
      10,    -1,    50,    -1,   132,    -1,   132,   198,   127,    -1,
     127,    -1,   152,   199,    -1,   199,    -1,    93,    -1,    51,
      -1,   132,    -1,    47,    -1,    59,    -1,    58,    -1,    93,
      -1,    51,    -1,    55,    -1,    93,    -1,    49,    -1,    92,
      -1,   138,    -1,   170,   229,   167,   191,   137,    -1,    -1,
      15,   191,    -1,    -1,     9,   191,    -1,    -1,   141,    -1,
     142,    -1,   141,   142,    -1,     8,   161,   167,   191,    -1,
     191,   140,   138,   139,    -1,    -1,    84,   193,   130,    -1,
      -1,   146,    -1,   147,    -1,   148,    -1,   187,   149,   192,
      81,    -1,   187,   192,    81,    -1,    27,   181,   149,   191,
      10,    -1,    27,   191,    10,    -1,    78,   153,   150,    78,
      -1,    78,   150,    78,    -1,    78,   153,    78,    -1,    74,
     151,    -1,   132,    -1,   151,   182,   132,    -1,   153,    -1,
     183,   153,   184,    -1,    77,   159,    -1,   155,   154,    -1,
     156,   182,   155,   154,    -1,   156,   154,    -1,   158,   182,
     155,   154,    -1,   158,   154,    -1,   158,   182,   156,   182,
     155,   154,    -1,   158,   182,   156,   154,    -1,   155,   182,
     158,   182,   155,   154,    -1,   155,   182,   158,   154,    -1,
     155,   182,   158,   182,   156,   182,   155,   154,    -1,   155,
     182,   158,   182,   156,   154,    -1,    -1,   182,    77,   159,
      -1,   159,    -1,   155,   182,   159,    -1,    89,   159,    -1,
     159,    94,   114,    -1,   157,    -1,   158,   182,   157,    -1,
      51,    -1,   160,    -1,    93,    -1,    58,    -1,    59,    -1,
      47,    -1,    -1,   162,    -1,   163,   164,    -1,   229,    -1,
     163,   182,   229,    -1,    -1,    72,   193,   131,    -1,   175,
     229,   167,   191,   166,    -1,   138,    -1,   165,    -1,   195,
      -1,    13,    -1,   195,    13,    -1,   195,    -1,    26,    -1,
      11,   193,    -1,    14,   193,    -1,    12,   193,    -1,    18,
     193,    -1,    19,   193,    -1,    16,   193,    -1,    17,   193,
      -1,    20,   193,    -1,     5,   193,    -1,     4,   193,    -1,
       3,   193,    -1,    25,   193,    -1,    -1,    46,    -1,    65,
     193,    -1,    82,   193,    -1,   193,    83,    -1,    60,   193,
      -1,   193,    61,    -1,    80,   193,    -1,   193,    81,    -1,
      94,   193,    -1,    95,   193,    -1,   197,   110,   197,    -1,
     197,    -1,   110,   197,    -1,    -1,   194,    -1,    46,    -1,
     194,    46,    -1,    74,    -1,    46,    -1,   195,    -1,   196,
     195,    -1,    -1,   196,    -1,    62,    -1,   104,    -1,    46,
      -1,    74,    -1,   205,   182,   201,    -1,   205,   182,    -1,
     229,    -1,   183,   200,   184,    -1,    89,   131,    -1,    89,
      -1,    -1,   203,    -1,   204,    -1,   203,   204,    -1,   185,
     210,   186,    -1,   229,    -1,   205,   182,    -1,   205,   182,
     201,    -1,   229,    -1,   206,   182,   229,    -1,   131,   189,
     114,    -1,   131,   190,   114,    -1,   131,   189,   214,    -1,
     131,   190,   214,    -1,   205,   189,   206,    -1,   205,   190,
     206,    -1,   205,   189,   217,   145,    -1,   205,   190,   217,
     145,    -1,   205,   189,   214,    -1,   205,   190,   214,    -1,
     205,   189,   122,    -1,   205,   190,   122,    -1,   185,    61,
      -1,   185,   211,   186,    -1,    56,    -1,   229,    -1,   207,
      -1,   214,    -1,   210,    -1,   211,   182,   210,    -1,   213,
     193,   210,   186,   202,    -1,    57,    -1,   187,    81,    -1,
     187,   215,   188,    -1,   216,    -1,   215,   182,   216,    -1,
     229,    72,   193,   229,    -1,   136,   193,   229,    -1,   127,
     225,    -1,   221,   225,    -1,   218,   224,    -1,   134,   104,
     127,    -1,   133,   224,   184,    -1,   220,   224,   184,    -1,
     134,   104,   133,    -1,   111,   222,    -1,   183,   229,   184,
     222,    -1,   219,   222,    -1,   223,    -1,   222,   223,    -1,
      62,   127,    -1,    62,   219,    -1,    -1,   225,    -1,   217,
      -1,   226,    -1,   229,    -1,   226,   182,   227,    -1,   229,
      -1,   214,    -1,   215,    -1,   229,    -1,   214,    -1,   229,
      87,   193,   229,    -1,   229,    88,   193,   229,    -1,   229,
      89,   193,   229,    -1,   229,    90,   193,   229,    -1,   229,
      91,   193,   229,    -1,   229,    67,   193,   229,    -1,   229,
      77,   193,   229,    -1,   229,    78,   193,   229,    -1,   229,
      79,   193,   229,    -1,   229,    70,   193,   229,    -1,   229,
      71,   193,   229,    -1,   183,   229,   184,    -1,   183,   208,
     184,    -1,   183,   217,   184,    -1,   229,    96,   193,   229,
      -1,   229,    97,   193,   229,    -1,   229,    99,   193,   229,
      -1,   229,    98,   193,   229,    -1,   229,   100,   193,   229,
      -1,   229,   101,   193,   229,    -1,   229,    85,   193,   229,
      -1,   229,    84,   193,   229,    -1,   229,   102,   193,   229,
      -1,   229,   103,   193,   229,    -1,   229,    75,   193,   229,
      -1,   229,    76,   193,   229,    -1,   229,    31,   193,   229,
      -1,   229,    30,   193,   229,    -1,   229,   106,   193,   229,
      -1,   229,   105,   193,   229,    -1,   229,    73,   193,   229,
     193,    66,   193,   229,    -1,    32,   193,   229,    -1,    63,
     193,   229,    -1,    86,   193,   229,    -1,    69,   193,   229,
      -1,    68,   193,   229,    -1,    34,   193,   229,    -1,   115,
     145,    -1,   116,    -1,   212,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   170,   170,   171,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   195,   196,   199,   200,   201,
     202,   203,   204,   205,   206,   209,   210,   211,   212,   213,
     214,   215,   216,   219,   220,   223,   224,   225,   226,   229,
     230,   231,   234,   235,   236,   237,   238,   239,   240,   241,
     244,   245,   246,   247,   248,   249,   250,   251,   254,   255,
     258,   259,   262,   263,   266,   267,   268,   271,   278,   285,
     291,   297,   303,   307,   311,   315,   319,   325,   324,   334,
     333,   344,   343,   354,   353,   365,   366,   369,   370,   373,
     374,   377,   378,   384,   385,   386,   387,   388,   391,   394,
     397,   400,   403,   406,   407,   415,   416,   419,   420,   423,
     424,   427,   428,   431,   437,   443,   444,   447,   448,   451,
     452,   455,   459,   465,   469,   475,   479,   483,   489,   492,
     493,   499,   500,   503,   504,   505,   509,   510,   514,   515,
     519,   523,   527,   531,   536,   542,   543,   546,   547,   550,
     553,   556,   557,   560,   561,   564,   569,   574,   579,   586,
     587,   590,   596,   597,   600,   601,   604,   610,   611,   614,
     615,   616,   619,   620,   623,   626,   629,   632,   635,   638,
     641,   644,   647,   650,   653,   656,   659,   660,   663,   666,
     669,   672,   675,   678,   681,   684,   687,   690,   691,   694,
     697,   698,   701,   702,   705,   706,   709,   710,   713,   714,
     717,   718,   721,   722,   725,   726,   729,   739,   740,   741,
     744,   745,   748,   749,   752,   755,   756,   757,   760,   761,
     764,   765,   766,   767,   770,   771,   772,   777,   782,   783,
     784,   785,   788,   789,   790,   794,   795,   796,   799,   800,
     803,   815,   818,   819,   822,   823,   826,   827,   830,   834,
     844,   847,   853,   857,   863,   866,   871,   876,   882,   883,
     886,   891,   898,   899,   902,   903,   907,   908,   912,   913,
     914,   918,   919,   922,   923,   924,   925,   926,   927,   928,
     929,   930,   931,   932,   933,   934,   935,   936,   937,   938,
     939,   940,   941,   942,   943,   944,   945,   946,   947,   948,
     949,   950,   951,   952,   956,   957,   958,   959,   960,   961,
     962,   963,   964
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
  "CVAR", "NUMBER", "SYMBOL", "FNAME", "BASE", "STRING", "COMMENT",
  "REGEXP", "MCALL", "ARRAY", "SARY", "IVAR", "GLOBAL", "tLBRACKET",
  "tRBRACKET", "tDOT", "tTILDE", "tBACKTICK", "tCOMMA", "tCOLON", "tPOW",
  "tUMINUS", "tUPLUS", "tLSHIFT", "tRSHIFT", "tASSOC", "tQUESTION",
  "tSEMICOLON", "tOR", "tAND", "tAND_BIT", "tOR_BIT", "tXOR_BIT",
  "tLBRACE", "tRBRACE", "tLPAREN", "tRPAREN", "tLESSER", "tGREATER",
  "tNOT", "tPLUS", "tMINUS", "tMUL", "tDIV", "tMOD", "KEY", "CONST",
  "tASGN", "tOP_ASGN", "tCMP", "tEQ", "tEQQ", "tNEQ", "tMATCH", "tNMATCH",
  "tGEQ", "tLEQ", "tSCOPE", "tDOT3", "tDOT2", "$accept", "parser_start",
  "stmt", "stmts", "basic", "other_keywords", "string", "primary",
  "primary1", "primary2", "simple_stmt", "yield_stmt", "return_stmt",
  "item_list", "item", "cmpd_stmt", "$@1", "$@2", "$@3", "$@4", "fname",
  "single_name", "function_args", "module_name", "variable", "base",
  "mcall", "const", "symbol", "key", "if_tail", "opt_else", "opt_ensure",
  "opt_rescue", "rescue_list", "rescue_item", "bodystmt", "superclass",
  "opt_lambda_body", "lambda_body", "brace_block", "do_block",
  "block_args", "bv_decls", "block_list", "f_arglist", "f_arguments",
  "f_blockarg", "f_args", "f_restarg", "f_opt", "f_optarg", "arg",
  "f_bad_arg", "opt_rescue_arg", "rescue_arg", "exc_list", "exc_var",
  "case_body", "cases", "then", "do", "k_if", "k_elsif", "k_unless",
  "k_while", "k_until", "k_case", "k_when", "k_for", "k_def", "k_module",
  "k_class", "k_in", "endl", "comma", "lparen", "rparen", "lbracket",
  "rbracket", "lbrace", "rbrace", "asgn", "op_asgn", "compstmt",
  "not_empty_compstmt", "opt_eol_list", "eol_list", "term", "terms",
  "opt_terms", "dot_or_scope", "eol_or_semicolon", "lhs_list", "lhs",
  "opt_bracket_list", "bracket_list", "bracket_item", "mlhs", "mrhs",
  "simple_assign", "assign", "array", "array_exp", "array_items",
  "array_value", "sary", "hash", "hash_items", "hash_item", "method_call",
  "const_scope", "paren_method_call", "const_mcall", "dot_method_call",
  "dot_items", "dot_item", "opt_call_args", "m_call_args", "call_args",
  "exp_hash", "exp_for", "exp", 0
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
     355,   356,   357,   358,   359,   360,   361
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   107,   108,   108,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   110,   110,   111,   111,   111,
     111,   111,   111,   111,   111,   112,   112,   112,   112,   112,
     112,   112,   112,   113,   113,   114,   114,   114,   114,   115,
     115,   115,   116,   116,   116,   116,   116,   116,   116,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   118,   118,
     119,   119,   120,   120,   121,   121,   121,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   123,   122,   124,
     122,   125,   122,   126,   122,   127,   127,   128,   128,   129,
     129,   130,   130,   131,   131,   131,   131,   131,   132,   133,
     134,   135,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   141,   141,   142,   143,   144,   144,   145,   145,   146,
     146,   147,   147,   148,   148,   149,   149,   149,   150,   151,
     151,   152,   152,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   154,   154,   155,   155,   156,
     157,   158,   158,   159,   159,   160,   160,   160,   160,   161,
     161,   162,   163,   163,   164,   164,   165,   166,   166,   167,
     167,   167,   168,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   191,   192,
     193,   193,   194,   194,   195,   195,   196,   196,   197,   197,
     198,   198,   199,   199,   200,   200,   201,   201,   201,   201,
     202,   202,   203,   203,   204,   205,   205,   205,   206,   206,
     207,   207,   207,   207,   208,   208,   208,   208,   208,   208,
     208,   208,   209,   209,   209,   210,   210,   210,   211,   211,
     212,   213,   214,   214,   215,   215,   216,   216,   217,   217,
     217,   218,   219,   219,   220,   221,   221,   221,   222,   222,
     223,   223,   224,   224,   225,   225,   226,   226,   227,   227,
     227,   228,   228,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     2,     1,     3,
       3,     3,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     1,     1,     1,     2,
       1,     2,     1,     3,     1,     1,     1,     6,     6,     5,
       5,     5,     3,     4,     4,     7,     3,     0,     6,     0,
       5,     0,     6,     0,     7,     1,     1,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     0,     2,     0,     2,     0,
       1,     1,     2,     4,     4,     0,     3,     0,     1,     1,
       1,     4,     3,     5,     3,     4,     3,     3,     2,     1,
       3,     1,     3,     2,     2,     4,     2,     4,     2,     6,
       4,     6,     4,     8,     6,     0,     3,     1,     3,     2,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     0,
       1,     2,     1,     3,     0,     3,     5,     1,     1,     1,
       1,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     0,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     1,     2,
       0,     1,     1,     2,     1,     1,     1,     2,     0,     1,
       1,     1,     1,     1,     3,     2,     1,     3,     2,     1,
       0,     1,     1,     2,     3,     1,     2,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     4,     4,     3,     3,
       3,     3,     2,     3,     1,     1,     1,     1,     1,     3,
       5,     1,     2,     3,     1,     3,     4,     3,     2,     2,
       2,     3,     3,     3,     3,     2,     4,     2,     1,     2,
       2,     2,     0,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,     3,     3,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     8,     3,     3,     3,     3,     3,     3,
       2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   200,   200,   200,     0,   208,   200,   200,   200,   200,
     200,   200,    50,    53,    51,    52,    60,    58,   200,     0,
     200,     0,     0,    46,    26,    25,    27,    28,    29,    30,
      31,    32,     2,    94,    42,   101,    85,    98,    33,    14,
      45,    99,   244,   251,    96,    95,   200,   200,    47,   200,
     200,   200,   200,   200,    97,     0,     3,     0,    49,    44,
     117,   321,     4,    56,    57,     5,     0,    39,    93,   272,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    48,   322,   200,     8,
     117,   272,    40,   272,    41,    13,   202,   184,   201,   183,
     182,    65,    64,    54,    62,    66,   205,   204,     0,   109,
     206,   209,   198,   174,   176,   179,   177,   178,   181,    93,
       0,    41,    61,    59,     0,     0,     0,   208,   208,   191,
       0,     0,     0,   193,   189,     0,     1,     0,     0,     0,
       0,     0,   265,   268,    34,   208,   320,   118,   119,   120,
       0,   274,   258,   275,   276,   200,   273,     0,     0,     0,
       0,     0,   200,     0,     0,   208,     0,   225,    88,    77,
      86,    92,    91,    79,   200,   115,   200,   200,   225,   242,
      39,   246,   248,   200,   247,   245,   252,   102,   200,   200,
     254,     0,   200,   200,   200,   226,     0,     0,     0,     7,
     260,   267,   200,   259,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   203,     0,    76,   159,   105,   110,   111,   207,
      15,   208,     0,   314,    55,   319,     0,     0,   315,   318,
     317,   316,     9,    10,    11,    12,   100,   270,    86,   271,
     269,   205,     0,     0,     0,   208,     0,     0,     0,   262,
       0,   261,   264,   170,   208,   169,   208,   173,   208,   172,
     208,   180,    72,     0,     0,   200,     0,     0,   210,   211,
       0,   208,     0,   200,    81,   295,   296,   294,     0,     0,
       0,   243,     0,     0,     0,   253,     0,   200,   188,   195,
     196,   219,     0,   227,   216,   240,   234,   238,   117,   228,
     241,   235,   239,   117,   200,   263,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,     0,   160,   164,   162,   208,
     107,   112,   209,   197,    73,    74,   208,   124,   158,   153,
     156,   157,     0,     0,     0,   155,     0,     0,   145,   145,
     151,   145,   147,   154,   199,     0,   122,   279,   280,   277,
     278,   190,   105,   171,   105,     0,     0,   208,     0,   185,
     282,     0,   281,   212,   213,   208,     0,   131,     0,    90,
      87,     0,    97,    83,     0,   208,   266,    22,    18,    21,
      23,    35,    24,    20,   230,    17,    19,     0,    36,   232,
      37,    38,   231,   233,   249,   192,   257,   255,   194,     0,
     218,   200,     0,     0,   236,   237,   220,   310,   309,   288,
     292,   293,   200,   307,   308,   289,   290,   291,   304,   303,
     283,   284,   285,   286,   287,   297,   298,   300,   299,   301,
     302,   305,   306,   312,   311,   208,   200,   161,     0,   106,
     208,   114,    16,     0,   129,   128,   133,   149,   126,   127,
       0,   134,     0,   136,     0,   138,     0,     0,   121,   200,
       0,   103,     0,     0,    69,    70,   105,    71,   208,     0,
      89,   200,    80,   208,   116,     0,   200,   256,   217,   226,
     229,     0,   250,   221,   222,     0,   113,     0,   163,   108,
     123,     0,   125,     0,   145,   148,   145,   147,   145,   145,
     152,   150,   175,    67,     0,    68,   167,   168,   166,     0,
      78,   132,     0,    82,     0,   227,   200,   223,   200,   165,
     130,   146,   142,     0,   135,     0,   137,   140,     0,   208,
      75,    84,   224,     0,   145,   145,   148,   145,   105,   313,
     141,   144,     0,   139,   104,   145,   143
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    55,   240,   265,    57,    58,    59,   424,    60,    61,
      62,    63,    64,   103,   104,    65,   287,   291,   415,   513,
      66,   169,   405,   173,    67,   119,    69,   120,    71,   188,
     500,   501,   481,   236,   237,   238,   108,   294,   146,   147,
     148,   149,   266,   376,   485,   406,   377,   491,   378,   379,
     380,   381,   382,   383,   355,   356,   357,   477,   163,   548,
     274,   278,    72,   502,    73,    74,    75,    76,   164,    77,
      78,    79,    80,   286,   262,   565,    81,   269,    82,   301,
      83,   305,   196,   197,   109,   267,   270,    98,   110,   111,
     112,   290,   409,   441,   313,   522,   523,   524,    84,   316,
     181,    85,    86,   182,   183,    87,    88,    89,   189,   190,
      90,    91,    92,    93,   121,   142,   143,   155,   156,   153,
     389,   401,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -464
static const yytype_int16 yypact[] =
{
     924,    36,    36,    36,   160,     9,    36,    36,    36,    36,
      36,    36,  -464,  -464,  -464,  -464,  2109,  2109,    36,   160,
      36,    19,    84,    51,  -464,  -464,  -464,  -464,  -464,  -464,
    -464,  -464,  -464,  -464,   110,  -464,  -464,  -464,  -464,  -464,
     122,  -464,  -464,  -464,  -464,  -464,    36,    36,   127,    36,
      36,    36,    36,    36,   100,   212,   267,   152,   153,   106,
      15,  -464,  -464,  -464,  -464,  -464,  1823,   158,  1880,  1823,
     119,   173,  2109,  2109,  2109,  2109,  1202,  2109,   151,   -12,
      -2,  1823,  1652,  1709,    96,  -464,  -464,  -464,    36,  -464,
      15,  1823,   152,  1823,  1823,  1233,  -464,  -464,   205,  -464,
    -464,  -464,  -464,  -464,   197,  -464,  -464,  -464,   254,   257,
    -464,     9,  1092,  -464,  -464,  -464,  -464,  -464,  -464,  -464,
     176,  -464,  1519,  1519,  2109,   160,  2109,     9,     9,  -464,
    2109,  2109,  2109,  -464,  -464,  2109,  -464,  2109,  2109,  2109,
    2109,    34,   152,  -464,  -464,    88,  -464,  -464,  -464,  -464,
    1008,  -464,  -464,   197,  1519,    36,  -464,   142,   635,   635,
    1127,  1127,    36,   271,  2109,  1295,    44,  1519,  -464,  -464,
     -17,  -464,  -464,  -464,    36,   198,    36,    36,  1357,  -464,
      49,  -464,  -464,    47,  -464,  1519,  -464,  -464,    36,    47,
    -464,  1407,    36,    36,    36,  1937,   739,   739,  1995,  -464,
    -464,   152,    36,  -464,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,  -464,   160,  -464,  2109,   268,   257,  -464,  -464,
     267,     9,   238,  2191,  -464,  2191,   213,   214,  -464,   231,
    -464,  -464,  1519,  1519,  1519,  1519,  -464,  -464,  -464,  -464,
    -464,   225,   226,   296,   542,     9,  1092,   227,  1766,  -464,
     224,  -464,  -464,  -464,     9,   327,     9,  -464,     9,  -464,
       9,  -464,  -464,   635,   292,    36,  1995,   433,  -464,  -464,
     151,     9,    39,    36,  -464,  -464,  -464,   152,  2145,  2145,
    1995,  -464,   286,  2109,  2052,  -464,   273,    36,  -464,  -464,
    -464,    39,  1823,  -464,  1519,  -464,   197,  -464,    15,  1519,
    -464,   197,  -464,    15,    36,  -464,  2109,  2109,  2109,  2109,
    2109,  2109,  2109,  2109,  2109,  2109,  2109,  2109,  2109,  2109,
    2109,  2109,  2109,  2109,  2109,  2109,  2109,  2109,  2109,  2109,
    2109,  2109,  2109,  2109,  -464,    33,  -464,   113,  1519,     9,
     339,  -464,   840,  -464,  -464,  -464,     9,  -464,  -464,  -464,
    -464,  -464,   298,   136,   136,  -464,   289,   -27,   197,   197,
    -464,   197,   276,  -464,  -464,   290,  -464,  -464,   197,  -464,
    1407,  -464,   124,  -464,   124,   366,   367,     9,   368,  -464,
    -464,    18,  1519,  -464,  -464,     9,    89,  -464,   436,  -464,
    -464,   372,  -464,  -464,   -12,     9,   152,  -464,  -464,  -464,
    -464,   152,  -464,   331,  -464,  -464,  -464,  2109,  -464,  -464,
     152,  -464,  -464,  -464,  -464,  -464,  1519,  -464,  -464,  2109,
    -464,    36,    96,  2109,  -464,  -464,   324,  2191,  2191,   231,
     382,   382,  1469,  2265,  2302,   602,   746,   746,   609,   609,
     201,   201,   231,   231,   231,  2339,  2339,  2339,  2339,  2339,
    2339,   609,   609,  2228,  2228,     9,    36,  -464,  2109,  -464,
       9,  -464,   267,   375,  -464,   197,  -464,  -464,  -464,  -464,
     308,  -464,   322,  -464,   322,  -464,   578,  2192,  -464,    36,
     377,  -464,  2109,   380,  -464,  -464,    79,  -464,     9,   386,
    -464,    36,  -464,     9,  -464,   388,  1469,  1519,  -464,  1594,
    1519,  1995,  -464,   324,  -464,   336,  -464,    39,  1519,  -464,
    -464,   298,  -464,   136,   197,   276,   197,  -464,   197,   197,
    -464,  -464,  -464,  -464,   635,  -464,  -464,  -464,  -464,   398,
    -464,  -464,   399,  -464,   152,    57,    36,  -464,    36,  -464,
    -464,  -464,  -464,   578,  -464,   322,  -464,  -464,   322,     9,
    -464,  -464,  -464,  2109,   197,   197,  -464,   197,   124,  2191,
    -464,  -464,   322,  -464,  -464,   197,  -464
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -464,  -464,     6,   300,  -272,  -270,  -236,  -275,  -464,  -464,
    -464,  -464,  -464,   177,    12,    10,  -464,  -464,  -464,  -464,
     -53,  -464,  -464,   -76,   -45,    76,  -117,   155,     1,  -464,
    -375,  -229,  -464,  -464,  -464,   179,  -269,  -464,   -60,  -464,
    -464,  -464,   156,    37,  -464,  -464,  -252,    75,  -462,  -463,
    -458,   -72,    59,  -464,  -464,  -464,  -464,  -464,  -261,  -464,
    -150,  -144,  -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,
    -464,  -464,  -464,  -464,  -464,   275,  -122,  -166,  -392,  -306,
     -47,  -464,   239,   242,   115,   159,   354,  -464,    -9,  -193,
    -124,  -464,    20,  -464,   -95,  -464,  -464,   -94,   -56,   233,
    -464,   -73,  -228,  -182,  -464,  -464,  -464,   -68,   163,   130,
     105,  -464,  -139,  -464,   147,   -89,  -127,    82,   -14,  -464,
    -464,  -464,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -226
static const yytype_int16 yytable[] =
{
     122,   123,   259,   201,   175,   105,    56,   360,   176,   276,
     295,   296,   297,   150,   184,   260,   324,   280,   446,   503,
     105,   166,   411,   398,   432,   168,   421,   421,   422,   422,
     199,   125,   536,   539,   538,   407,   325,   180,   540,   171,
     272,   284,   145,   150,   277,   288,   273,   372,   362,   171,
     154,   489,   152,   154,   521,   106,   158,   159,   160,   161,
     165,   167,   423,   423,   106,   178,   185,   191,   174,   285,
     428,   428,   362,   312,   260,   154,    68,   154,   154,   106,
     203,   172,    96,   107,    36,    37,    33,   289,   257,    41,
      37,   172,   107,    96,   359,    51,   162,    44,    45,   127,
     575,   574,   239,  -214,   271,   540,   577,   107,   243,   192,
     245,   -17,   192,   -22,   248,   249,   250,   363,   434,   251,
     585,   252,   253,   254,   255,   272,   105,   256,   317,   322,
     184,   521,   412,   397,   261,   403,   509,   244,   499,   359,
    -214,   384,    68,   193,   194,    68,   515,    94,   283,   275,
     275,   279,   279,   180,   170,    70,   511,    68,   144,   430,
     430,   192,   107,   404,   128,   408,  -186,    68,   -20,    68,
      68,   151,   -18,   200,   151,   202,   427,   427,   192,   314,
     319,   319,   185,   368,   -21,   476,   177,   369,    68,   -23,
     193,   194,    36,    37,   370,   371,   151,    41,   151,   151,
     387,    36,    37,   584,  -100,   475,   315,   320,   416,    35,
     101,   102,   136,    94,   141,   -24,    94,   258,   400,   358,
     -17,    70,   541,   157,    70,   421,    68,   422,    94,   375,
     429,   433,   184,   258,   105,   -19,    70,   410,    94,   176,
      94,    94,   246,   247,   552,   547,    70,   413,    70,    70,
     572,   232,   390,   425,   425,   180,   442,   508,   444,    94,
     263,   423,   192,   445,   234,   235,   440,    70,   206,   428,
     402,   150,    68,    68,   275,   518,   150,   546,   137,   138,
     242,   282,   293,   359,   185,   139,   140,   436,   191,   260,
     219,   220,   221,    41,   364,   365,   178,    94,   206,   426,
     426,   318,   323,  -187,   264,    70,   367,   391,   386,   162,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   514,   556,
     393,   201,    68,    94,    94,   551,   275,   435,   480,    37,
     554,    70,    70,   239,   438,    97,    99,   100,   430,   195,
     113,   114,   115,   116,   117,   118,   258,   488,   482,   368,
     497,   498,   124,   369,   126,   427,   504,   505,   507,   233,
     370,   371,   512,   144,    46,   530,   532,   543,    68,   392,
     545,   394,   279,   395,   569,   396,   550,   312,   553,   533,
     129,   130,   558,   131,   132,   133,   134,   135,   570,   571,
     354,   516,   241,    94,   490,   375,   361,   177,   366,   298,
     534,    70,   299,   517,   555,   385,   510,   520,   268,   557,
     321,   388,   486,   487,   437,     0,     0,     0,    68,     0,
       0,   195,   198,     0,     0,   431,   431,     0,   484,   206,
       0,     0,   425,   184,   493,     0,   495,     0,   300,    94,
       0,     0,   528,     0,   304,   416,     0,    70,     0,   217,
     218,   219,   220,   221,   479,     0,   180,     0,     0,   403,
     368,   483,   559,   368,   369,     0,   544,   369,     0,     0,
       0,   370,   371,     0,   370,   371,     0,     0,   426,     0,
       0,     0,     0,   314,     0,   185,     0,   404,     0,    94,
     373,     0,   506,   373,     0,    52,   281,    70,     0,     0,
       0,     0,   374,     0,     0,   374,   375,     0,   292,   375,
       0,     0,     0,     0,     0,   275,     0,   302,     0,     0,
       0,     0,   303,   306,     0,     0,   308,   309,   310,     0,
       0,   535,     0,   537,     0,     0,     0,   579,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,     0,     0,     0,   368,
     526,   443,   561,   369,     0,   529,   443,     0,     0,     0,
     370,   371,     0,     0,     0,     0,     0,   560,     0,   562,
       0,   564,     0,   566,   567,     0,   372,     0,     0,   373,
       0,     0,     0,   549,   576,   368,     0,   537,     0,   369,
       0,   374,   478,     0,     0,   375,   370,   371,     0,   399,
       0,   537,     0,     0,   431,     0,     0,   414,   273,   580,
     581,     0,   583,   492,   494,   533,   496,     0,     0,     0,
     586,   439,     0,   304,     0,   204,   205,   374,     0,   206,
       0,   375,   207,   208,     0,     0,   206,     0,   302,   207,
     208,   106,     0,     0,   578,     0,   212,   213,   214,   217,
     218,   219,   220,   221,     0,     0,   217,   218,   219,   220,
     221,     0,   206,     0,     0,   207,   208,     0,   209,   107,
     210,   211,   212,   213,   214,     0,     0,   519,     0,   215,
     216,     0,   217,   218,   219,   220,   221,     0,     0,     0,
       0,   222,   223,   224,   225,   226,   227,   228,   229,     0,
     230,   231,     1,     2,     3,     0,     5,     0,     0,     0,
       6,     7,     0,     0,     0,     8,     0,     9,    10,    11,
     531,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,    36,
      37,    38,     0,    40,    41,    42,    43,    44,    45,    46,
       0,     0,    47,    48,     0,     0,   525,    49,    50,   563,
       0,     0,     0,   206,   568,     0,   207,   208,     0,    51,
       0,    52,     0,   212,     0,    53,     0,     0,     0,     0,
     527,     0,    54,   217,   218,   219,   220,   221,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     5,     0,     0,
     582,     6,     7,   542,     0,     0,     8,     0,     9,    10,
      11,    12,    13,    14,    15,     0,     0,     0,    16,    17,
       0,     0,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   106,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,     0,     0,    47,    48,     0,     0,     0,    49,    50,
     302,     0,   573,     0,   107,     0,     0,     0,     0,     0,
      51,     0,    52,     0,     0,     0,    53,     1,     2,     3,
       4,     5,     0,    54,     0,     6,     7,     0,     0,     0,
       8,     0,     9,    10,    11,    12,    13,    14,    15,     0,
       0,     0,    16,    17,     0,     0,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,     0,     0,    47,    48,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,     0,    52,     0,     0,     0,
      53,     1,     2,     3,     4,     5,     0,    54,     0,     6,
       7,     0,     0,     0,     8,     0,     9,    10,    11,    12,
      13,    14,    15,     0,     0,     0,    16,    17,     0,     0,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,     0,
       0,    47,    48,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,     0,   264,     0,    51,     0,
      52,     0,     0,     0,    53,     1,     2,     3,     4,     5,
       0,    54,     0,     6,     7,     0,     0,     0,     8,     0,
       9,    10,    11,    12,    13,    14,    15,     0,     0,     0,
      16,    17,     0,     0,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,   277,     0,    47,    48,   204,   205,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,   106,    52,     0,     0,     0,    53,     0,
       0,     0,     0,     0,     0,    54,     0,     0,     0,     0,
       0,     0,     0,     0,   206,     0,     0,   207,   208,     0,
     209,   107,   210,   211,   212,   213,   214,     0,     0,     0,
       0,   215,   216,     0,   217,   218,   219,   220,   221,   162,
       0,     0,     0,   222,   223,   224,   225,   226,   227,   228,
     229,     0,   230,   231,    18,     0,    20,     0,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    33,
      34,    35,     0,    37,    38,     0,    40,    41,    42,    43,
      44,    45,    46,   204,   205,    47,    48,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    52,     0,     0,     0,    53,     0,
       0,     0,     0,     0,     0,    54,     0,     0,  -225,     0,
     206,     0,     0,   207,   208,     0,   209,     0,   210,   211,
     212,   213,   214,     0,     0,     0,     0,   215,   216,     0,
     217,   218,   219,   220,   221,   204,   205,  -225,  -225,   222,
     223,   224,   225,   226,   227,   228,   229,     0,   230,   231,
       0,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   206,     0,     0,   207,   208,     0,   209,   107,
     210,   211,   212,   213,   214,     0,     0,     0,     0,   215,
     216,     0,   217,   218,   219,   220,   221,   204,   205,     0,
       0,   222,   223,   224,   225,   226,   227,   228,   229,     0,
     230,   231,     0,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   206,     0,     0,   207,   208,     0,
     209,     0,   210,   211,   212,   213,   214,   204,   205,     0,
    -200,   215,   216,     0,   217,   218,   219,   220,   221,     0,
       0,     0,     0,   222,   223,   224,   225,   226,   227,   228,
     229,     0,   230,   231,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   206,     0,     0,   207,   208,   307,
     209,     0,   210,   211,   212,   213,   214,     0,     0,     0,
       0,   215,   216,     0,   217,   218,   219,   220,   221,   204,
     205,     0,     0,   222,   223,   224,   225,   226,   227,   228,
     229,     0,   230,   231,     0,    96,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   206,     0,     0,   207,
     208,     0,   209,     0,   210,   211,   212,   213,   214,   204,
     205,     0,     0,   215,   216,     0,   217,   218,   219,   220,
     221,     0,     0,     0,     0,   222,   223,   224,   225,   226,
     227,   228,   229,     0,   230,   231,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   206,     0,     0,   207,
     208,     0,   209,     0,   210,   211,   212,   213,   214,     0,
       0,     0,     0,   215,   216,     0,   217,   218,   219,   220,
     221,     0,     0,     0,     0,   222,   223,   224,   225,   226,
     227,   228,   229,     0,   230,   231,    18,     0,    20,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
    -215,    33,    34,    35,     0,    37,    38,     0,    40,    41,
      42,    43,    44,    45,    46,     0,     0,    47,    48,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,  -215,     0,     0,
      53,     0,     0,   311,    18,     0,    20,    54,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    33,
      34,    35,     0,    37,    38,     0,    40,    41,    42,    43,
      44,    45,    46,   179,     0,    47,    48,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,     0,    52,     0,     0,     0,    53,     0,
       0,    18,     0,    20,     0,    54,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,     0,
      37,    38,     0,    40,    41,    42,    43,    44,    45,    46,
       0,     0,    47,    48,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     186,    52,     0,     0,     0,    53,     0,     0,    18,     0,
      20,   187,    54,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     0,    33,    34,    35,     0,    37,    38,     0,
      40,    41,    42,    43,    44,    45,    46,     0,     0,    47,
      48,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,     0,    52,     0,
       0,     0,    53,     0,     0,    18,     0,    20,   187,    54,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      33,    34,    35,    36,    37,    38,     0,    40,    41,    42,
      43,    44,    45,    46,     0,     0,    47,    48,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    52,     0,     0,     0,    53,
       0,     0,   -86,     0,   -86,     0,    54,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,     0,   -86,   -86,   -86,
     -86,   -86,   -86,     0,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,     0,     0,   -86,   -86,     0,     0,     0,   -86,   -86,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -86,     0,     0,     0,   -86,     0,     0,    18,
       0,    20,     0,   -86,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,    33,    34,    35,     0,    37,    38,
       0,    40,    41,    42,    43,    44,    45,    46,     0,     0,
      47,    48,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
       0,     0,     0,    53,     0,     0,   311,    18,     0,    20,
      54,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    33,    34,    35,     0,    37,    38,     0,    40,
      41,    42,    43,    44,    45,    46,     0,     0,    47,    48,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,    52,     0,     0,
       0,    53,     0,     0,    18,     0,    20,     0,    54,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    33,
      34,    35,     0,    37,    38,     0,    40,    41,    42,    43,
      44,    45,    46,     0,     0,    47,    48,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    52,     0,     0,     0,    53,     0,
       0,    18,     0,    20,   187,    54,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,     0,
      37,    38,     0,    40,    41,    42,    43,    44,    45,    46,
       0,     0,    47,    48,     0,     0,     0,    49,    50,     0,
       0,     0,   417,    24,    25,    26,    27,    28,    29,    30,
      31,    52,    33,   418,    35,    53,    37,    38,     0,   419,
      41,    42,    54,    44,    45,    46,     0,     0,     0,   420,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,    52,     0,   417,
      24,    25,    26,    27,    28,    29,    30,    31,    54,    33,
     418,    35,     0,    37,    38,     0,   419,    41,    42,     0,
      44,    45,    46,     0,     0,     0,   420,     0,   206,     0,
       0,   207,   208,     0,   209,     0,   210,   211,   212,   213,
     214,     0,     0,     0,    52,   215,   216,     0,   217,   218,
     219,   220,   221,     0,     0,    54,     0,   222,   223,   224,
     225,   226,   227,   228,   229,   206,   230,   231,   207,   208,
       0,     0,     0,   210,   211,   212,   213,   214,     0,     0,
       0,     0,   215,   216,     0,   217,   218,   219,   220,   221,
       0,     0,     0,     0,   222,   223,   224,   225,   226,   227,
     228,   229,   206,  -226,  -226,   207,   208,     0,     0,     0,
       0,   211,   212,   213,   214,     0,     0,     0,     0,   215,
     216,     0,   217,   218,   219,   220,   221,     0,     0,     0,
       0,   222,   223,   224,   225,   226,   227,   228,   229,   206,
       0,     0,   207,   208,     0,     0,     0,     0,     0,   212,
     213,   214,     0,     0,     0,     0,   215,   216,     0,   217,
     218,   219,   220,   221,     0,     0,     0,     0,   222,   223,
     224,   225,   226,   227,   228,   229,   206,     0,     0,   207,
     208,     0,     0,     0,     0,     0,   212,   213,   214,     0,
       0,     0,     0,   215,   216,     0,   217,   218,   219,   220,
     221,     0,     0,     0,     0,  -226,  -226,  -226,  -226,  -226,
    -226,   228,   229
};

static const yytype_int16 yycheck[] =
{
      16,    17,   141,    92,    80,     4,     0,   236,    81,   159,
     176,   177,   178,    60,    82,   142,   198,   161,   324,   394,
      19,    77,   291,   284,   299,    78,   298,   299,   298,   299,
      90,    19,   494,   496,   496,   287,   202,    82,   496,    51,
     157,   165,    27,    90,    26,    62,    13,    74,   241,    51,
      66,    78,    66,    69,   446,    46,    72,    73,    74,    75,
      76,    77,   298,   299,    46,    81,    82,    83,    70,    25,
     298,   299,   265,   195,   201,    91,     0,    93,    94,    46,
      94,    93,    46,    74,    50,    51,    47,   104,   141,    55,
      51,    93,    74,    46,    15,    80,    17,    58,    59,    80,
     563,   563,   111,    46,   157,   563,   568,    74,   124,    65,
     126,    62,    65,    62,   130,   131,   132,   241,   300,   135,
     582,   137,   138,   139,   140,   242,   125,    93,   196,   197,
     198,   523,    93,   283,    46,    46,   405,   125,    14,    15,
      83,   265,    66,    94,    95,    69,   415,     0,   164,   158,
     159,   160,   161,   198,    78,     0,   408,    81,    52,   298,
     299,    65,    74,    74,    80,   287,    78,    91,    62,    93,
      94,    66,    62,    91,    69,    93,   298,   299,    65,   195,
     196,   197,   198,    47,    62,    72,    81,    51,   112,    62,
      94,    95,    50,    51,    58,    59,    91,    55,    93,    94,
     268,    50,    51,   578,   104,   355,   196,   197,   297,    49,
      50,    51,     0,    66,    62,    62,    69,   141,   286,   235,
      62,    66,   497,   104,    69,   497,   150,   497,    81,    93,
     298,   299,   300,   157,   233,    62,    81,   290,    91,   312,
      93,    94,   127,   128,   513,   506,    91,   292,    93,    94,
     556,    46,   268,   298,   299,   300,   312,   401,   318,   112,
     145,   497,    65,   323,    10,     8,   311,   112,    67,   497,
     286,   318,   196,   197,   283,   441,   323,   506,    11,    12,
     104,    10,    84,    15,   300,    18,    19,   303,   304,   416,
      89,    90,    91,    55,    81,    81,   312,   150,    67,   298,
     299,   196,   197,    78,    78,   150,    10,    83,    81,    17,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   414,   521,
      13,   430,   266,   196,   197,   511,   355,    61,     9,    51,
     516,   196,   197,   362,    81,     1,     2,     3,   497,    84,
       6,     7,     8,     9,    10,    11,   290,    78,   362,    47,
      94,    81,    18,    51,    20,   497,    10,    10,    10,   104,
      58,    59,    10,    52,    60,    10,    78,    10,   312,   274,
      10,   276,   401,   278,   544,   280,    10,   519,    10,    77,
      46,    47,    66,    49,    50,    51,    52,    53,    10,    10,
     233,   427,   112,   266,   377,    93,   237,   312,   262,   180,
     492,   266,   180,   439,   519,   266,   406,   443,   153,   523,
     197,   268,   373,   374,   304,    -1,    -1,    -1,   362,    -1,
      -1,   166,    88,    -1,    -1,   298,   299,    -1,   372,    67,
      -1,    -1,   497,   521,   379,    -1,   381,    -1,   183,   312,
      -1,    -1,   478,    -1,   189,   554,    -1,   312,    -1,    87,
      88,    89,    90,    91,   359,    -1,   521,    -1,    -1,    46,
      47,   366,   527,    47,    51,    -1,   502,    51,    -1,    -1,
      -1,    58,    59,    -1,    58,    59,    -1,    -1,   497,    -1,
      -1,    -1,    -1,   519,    -1,   521,    -1,    74,    -1,   362,
      77,    -1,   397,    77,    -1,    82,   162,   362,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    89,    93,    -1,   174,    93,
      -1,    -1,    -1,    -1,    -1,   544,    -1,   183,    -1,    -1,
      -1,    -1,   188,   189,    -1,    -1,   192,   193,   194,    -1,
      -1,   492,    -1,   494,    -1,    -1,    -1,   573,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,    -1,    -1,    -1,    47,
     475,   316,   533,    51,    -1,   480,   321,    -1,    -1,    -1,
      58,    59,    -1,    -1,    -1,    -1,    -1,   531,    -1,   534,
      -1,   536,    -1,   538,   539,    -1,    74,    -1,    -1,    77,
      -1,    -1,    -1,   508,   565,    47,    -1,   568,    -1,    51,
      -1,    89,   357,    -1,    -1,    93,    58,    59,    -1,   285,
      -1,   582,    -1,    -1,   497,    -1,    -1,   293,    13,   574,
     575,    -1,   577,   378,   379,    77,   381,    -1,    -1,    -1,
     585,   307,    -1,   388,    -1,    30,    31,    89,    -1,    67,
      -1,    93,    70,    71,    -1,    -1,    67,    -1,   324,    70,
      71,    46,    -1,    -1,   569,    -1,    77,    78,    79,    87,
      88,    89,    90,    91,    -1,    -1,    87,    88,    89,    90,
      91,    -1,    67,    -1,    -1,    70,    71,    -1,    73,    74,
      75,    76,    77,    78,    79,    -1,    -1,   442,    -1,    84,
      85,    -1,    87,    88,    89,    90,    91,    -1,    -1,    -1,
      -1,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
     105,   106,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,
     485,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    64,    -1,    -1,   452,    68,    69,   534,
      -1,    -1,    -1,    67,   539,    -1,    70,    71,    -1,    80,
      -1,    82,    -1,    77,    -1,    86,    -1,    -1,    -1,    -1,
     476,    -1,    93,    87,    88,    89,    90,    91,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
     575,    11,    12,   499,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    28,    29,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    63,    64,    -1,    -1,    -1,    68,    69,
     556,    -1,   558,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    82,    -1,    -1,    -1,    86,     3,     4,     5,
       6,     7,    -1,    93,    -1,    11,    12,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    28,    29,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    63,    64,    -1,
      -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    82,    -1,    -1,    -1,
      86,     3,     4,     5,     6,     7,    -1,    93,    -1,    11,
      12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    28,    29,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    63,    64,    -1,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    80,    -1,
      82,    -1,    -1,    -1,    86,     3,     4,     5,     6,     7,
      -1,    93,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      28,    29,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    26,    -1,    63,    64,    30,    31,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    46,    82,    -1,    -1,    -1,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    70,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    -1,    -1,    -1,
      -1,    84,    85,    -1,    87,    88,    89,    90,    91,    17,
      -1,    -1,    -1,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,   105,   106,    32,    -1,    34,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    -1,    51,    52,    -1,    54,    55,    56,    57,
      58,    59,    60,    30,    31,    63,    64,    -1,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    65,    -1,
      67,    -1,    -1,    70,    71,    -1,    73,    -1,    75,    76,
      77,    78,    79,    -1,    -1,    -1,    -1,    84,    85,    -1,
      87,    88,    89,    90,    91,    30,    31,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    -1,   105,   106,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    70,    71,    -1,    73,    74,
      75,    76,    77,    78,    79,    -1,    -1,    -1,    -1,    84,
      85,    -1,    87,    88,    89,    90,    91,    30,    31,    -1,
      -1,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
     105,   106,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    70,    71,    -1,
      73,    -1,    75,    76,    77,    78,    79,    30,    31,    -1,
      83,    84,    85,    -1,    87,    88,    89,    90,    91,    -1,
      -1,    -1,    -1,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    70,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    -1,    -1,    -1,
      -1,    84,    85,    -1,    87,    88,    89,    90,    91,    30,
      31,    -1,    -1,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,   105,   106,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      71,    -1,    73,    -1,    75,    76,    77,    78,    79,    30,
      31,    -1,    -1,    84,    85,    -1,    87,    88,    89,    90,
      91,    -1,    -1,    -1,    -1,    96,    97,    98,    99,   100,
     101,   102,   103,    -1,   105,   106,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,
      71,    -1,    73,    -1,    75,    76,    77,    78,    79,    -1,
      -1,    -1,    -1,    84,    85,    -1,    87,    88,    89,    90,
      91,    -1,    -1,    -1,    -1,    96,    97,    98,    99,   100,
     101,   102,   103,    -1,   105,   106,    32,    -1,    34,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    63,    64,    -1,
      -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    83,    -1,    -1,
      86,    -1,    -1,    89,    32,    -1,    34,    93,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    -1,    51,    52,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,    64,    -1,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    82,    -1,    -1,    -1,    86,    -1,
      -1,    32,    -1,    34,    -1,    93,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    -1,
      51,    52,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    64,    -1,    -1,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    86,    -1,    -1,    32,    -1,
      34,    92,    93,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    48,    49,    -1,    51,    52,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    63,
      64,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    82,    -1,
      -1,    -1,    86,    -1,    -1,    32,    -1,    34,    92,    93,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    64,    -1,    -1,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,
      -1,    -1,    32,    -1,    34,    -1,    93,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    52,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    63,    64,    -1,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    86,    -1,    -1,    32,
      -1,    34,    -1,    93,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    49,    -1,    51,    52,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      63,    64,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    86,    -1,    -1,    89,    32,    -1,    34,
      93,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    48,    49,    -1,    51,    52,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    64,
      -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    82,    -1,    -1,
      -1,    86,    -1,    -1,    32,    -1,    34,    -1,    93,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    -1,    51,    52,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    64,    -1,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,    -1,
      -1,    32,    -1,    34,    92,    93,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    -1,
      51,    52,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    64,    -1,    -1,    -1,    68,    69,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    82,    47,    48,    49,    86,    51,    52,    -1,    54,
      55,    56,    93,    58,    59,    60,    -1,    -1,    -1,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    82,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    93,    47,
      48,    49,    -1,    51,    52,    -1,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    -1,    64,    -1,    67,    -1,
      -1,    70,    71,    -1,    73,    -1,    75,    76,    77,    78,
      79,    -1,    -1,    -1,    82,    84,    85,    -1,    87,    88,
      89,    90,    91,    -1,    -1,    93,    -1,    96,    97,    98,
      99,   100,   101,   102,   103,    67,   105,   106,    70,    71,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    -1,    -1,
      -1,    -1,    84,    85,    -1,    87,    88,    89,    90,    91,
      -1,    -1,    -1,    -1,    96,    97,    98,    99,   100,   101,
     102,   103,    67,   105,   106,    70,    71,    -1,    -1,    -1,
      -1,    76,    77,    78,    79,    -1,    -1,    -1,    -1,    84,
      85,    -1,    87,    88,    89,    90,    91,    -1,    -1,    -1,
      -1,    96,    97,    98,    99,   100,   101,   102,   103,    67,
      -1,    -1,    70,    71,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    -1,    -1,    -1,    -1,    84,    85,    -1,    87,
      88,    89,    90,    91,    -1,    -1,    -1,    -1,    96,    97,
      98,    99,   100,   101,   102,   103,    67,    -1,    -1,    70,
      71,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    -1,
      -1,    -1,    -1,    84,    85,    -1,    87,    88,    89,    90,
      91,    -1,    -1,    -1,    -1,    96,    97,    98,    99,   100,
     101,   102,   103
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    11,    12,    16,    18,
      19,    20,    21,    22,    23,    24,    28,    29,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    63,    64,    68,
      69,    80,    82,    86,    93,   108,   109,   111,   112,   113,
     115,   116,   117,   118,   119,   122,   127,   131,   132,   133,
     134,   135,   169,   171,   172,   173,   174,   176,   177,   178,
     179,   183,   185,   187,   205,   208,   209,   212,   213,   214,
     217,   218,   219,   220,   221,   229,    46,   193,   194,   193,
     193,    50,    51,   120,   121,   135,    46,    74,   143,   191,
     195,   196,   197,   193,   193,   193,   193,   193,   193,   132,
     134,   221,   229,   229,   193,   121,   193,    80,    80,   193,
     193,   193,   193,   193,   193,   193,     0,    11,    12,    18,
      19,    62,   222,   223,    52,    27,   145,   146,   147,   148,
     187,   217,   225,   226,   229,   224,   225,   104,   229,   229,
     229,   229,    17,   165,   175,   229,   205,   229,   127,   128,
     132,    51,    93,   130,    70,   130,   208,   217,   229,    61,
     131,   207,   210,   211,   214,   229,    81,    92,   136,   215,
     216,   229,    65,    94,    95,   182,   189,   190,   193,   145,
     224,   222,   224,   225,    30,    31,    67,    70,    71,    73,
      75,    76,    77,    78,    79,    84,    85,    87,    88,    89,
      90,    91,    96,    97,    98,    99,   100,   101,   102,   103,
     105,   106,    46,   182,    10,     8,   140,   141,   142,   195,
     109,   110,   104,   229,   121,   229,   191,   191,   229,   229,
     229,   229,   229,   229,   229,   229,    93,   127,   132,   219,
     223,    46,   181,   191,    78,   110,   149,   192,   182,   184,
     193,   127,   133,    13,   167,   195,   167,    26,   168,   195,
     168,   193,    10,   229,   197,    25,   180,   123,    62,   104,
     198,   124,   193,    84,   144,   184,   184,   184,   189,   190,
     182,   186,   193,   193,   182,   188,   193,    72,   193,   193,
     193,    89,   183,   201,   229,   122,   206,   214,   217,   229,
     122,   206,   214,   217,   210,   184,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   120,   161,   162,   163,   229,    15,
     138,   142,   196,   197,    81,    81,   149,    10,    47,    51,
      58,    59,    74,    77,    89,    93,   150,   153,   155,   156,
     157,   158,   159,   160,   197,   192,    81,   214,   215,   227,
     229,    83,   191,    13,   191,   191,   191,   167,   165,   193,
     214,   228,   229,    46,    74,   129,   152,   153,   183,   199,
     127,   143,    93,   131,   193,   125,   222,    37,    48,    54,
      64,   111,   112,   113,   114,   131,   135,   183,   209,   214,
     219,   221,   114,   214,   210,    61,   229,   216,    81,   193,
     131,   200,   205,   182,   145,   145,   186,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   167,    72,   164,   182,   191,
       9,   139,   109,   191,   132,   151,   159,   159,    78,    78,
     150,   154,   182,   154,   182,   154,   182,    94,    81,    14,
     137,   138,   170,   137,    10,    10,   191,    10,   168,   143,
     199,   153,    10,   126,   130,   143,   229,   229,   184,   182,
     229,   185,   202,   203,   204,   193,   191,   193,   229,   191,
      10,   182,    78,    77,   158,   159,   155,   159,   155,   156,
     157,   114,   193,    10,   229,    10,   138,   165,   166,   191,
      10,   184,   143,    10,   184,   201,   210,   204,    66,   131,
     132,   159,   154,   182,   154,   182,   154,   154,   182,   167,
      10,    10,   186,   193,   155,   156,   159,   155,   191,   229,
     154,   154,   182,   154,   137,   155,   154
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
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

/* Line 1464 of yacc.c  */
#line 170 "../parser.y"
    { parser->ast = NULL; YYACCEPT; ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 172 "../parser.y"
    {
    if (parser->errors[0].valid == 1) {
      free_ast(parser->ast);
      parser->ast = NULL;
    } else
      parser->ast = (yyvsp[(1) - (1)].n);
    YYACCEPT;
  ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 185 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 187 "../parser.y"
    { (yyval.n) = alloc_cond(token_if, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);      ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 188 "../parser.y"
    { (yyval.n) = alloc_cond(token_unless, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);  ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 189 "../parser.y"
    { (yyval.n) = alloc_cond(token_while, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);   ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 190 "../parser.y"
    { (yyval.n) = alloc_cond(token_until, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);   ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 192 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 195 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 196 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 199 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 200 "../parser.y"
    { (yyval.n) = alloc_node(token_numeric, NULL, NULL);   ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 201 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 202 "../parser.y"
    { (yyval.n) = alloc_node(token_string, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 203 "../parser.y"
    { (yyval.n) = alloc_node(token_regexp, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 204 "../parser.y"
    { (yyval.n) = alloc_node(token_heredoc, NULL, NULL);   ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 205 "../parser.y"
    { (yyval.n) = alloc_node(token_backtick, NULL, NULL); pop_string(parser, (yyval.n)); ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 206 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);    ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 223 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 224 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 225 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 226 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 229 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 230 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 231 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 234 "../parser.y"
    { (yyval.n) = alloc_node(token_numeric, NULL, NULL);   ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 235 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 236 "../parser.y"
    { (yyval.n) = alloc_node(token_string, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 237 "../parser.y"
    { (yyval.n) = alloc_node(token_regexp, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 238 "../parser.y"
    { (yyval.n) = alloc_node(token_heredoc, NULL, NULL);   ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 239 "../parser.y"
    { (yyval.n) = alloc_node(token_backtick, NULL, NULL); pop_string(parser, (yyval.n)); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 240 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 241 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);    ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 244 "../parser.y"
    { (yyval.n) = alloc_node(token_break, NULL, NULL);   ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 245 "../parser.y"
    { (yyval.n) = alloc_node(token_redo, NULL, NULL);    ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 246 "../parser.y"
    { (yyval.n) = alloc_node(token_retry, NULL, NULL);   ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 247 "../parser.y"
    { (yyval.n) = alloc_node(token_next, NULL, NULL);    ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 248 "../parser.y"
    { (yyval.n) = alloc_node(token_undef, (yyvsp[(2) - (2)].n), NULL);     ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 249 "../parser.y"
    { (yyval.n) = alloc_node(token_alias, (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));       ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 250 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 251 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 254 "../parser.y"
    { (yyval.n) = alloc_node(token_yield, NULL, NULL);   ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 255 "../parser.y"
    { (yyval.n) = alloc_node(token_yield, (yyvsp[(2) - (2)].n), NULL);     ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 258 "../parser.y"
    { (yyval.n) = alloc_node(token_return, NULL, NULL);  ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 259 "../parser.y"
    { (yyval.n) = alloc_node(token_return, (yyvsp[(2) - (2)].n), NULL);    ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 262 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 263 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 266 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 267 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 268 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 275 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_if, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
  ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 282 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_unless, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
    ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 288 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_while, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 294 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_until, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 300 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_case, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 304 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_case, NULL, (yyvsp[(2) - (3)].n), NULL);
    ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 308 "../parser.y"
    {
      (yyval.n) = alloc_node(token_up_begin, (yyvsp[(3) - (4)].n), NULL);
    ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 312 "../parser.y"
    {
      (yyval.n) = alloc_node(token_up_end, (yyvsp[(3) - (4)].n), NULL);
    ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 316 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_for, (yyvsp[(4) - (7)].n), (yyvsp[(6) - (7)].n), (yyvsp[(2) - (7)].n));
    ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 320 "../parser.y"
    {
      (yyval.n) = (yyvsp[(2) - (3)].n);
      (yyval.n)->kind = token_exception;
    ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 325 "../parser.y"
    {
      parser->in_def++;
    ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 329 "../parser.y"
    {
      parser->in_def--;
      (yyval.n) = alloc_cond(token_function, (yyvsp[(2) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(4) - (6)].n));
    ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 334 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "module definition in method body");
    ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 340 "../parser.y"
    {
      (yyval.n) = alloc_node(token_module, (yyvsp[(4) - (5)].n), (yyvsp[(2) - (5)].n));
    ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 344 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 350 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_class, (yyvsp[(3) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(2) - (6)].n));
    ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 354 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 360 "../parser.y"
    {
      (yyval.n) = alloc_node(token_singleton_class, (yyvsp[(6) - (7)].n), (yyvsp[(4) - (7)].n));
    ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 365 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 366 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 369 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 370 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 373 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 374 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 377 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 379 "../parser.y"
    {
    yyerror(parser, "class/module name must be CONSTANT");
  ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 384 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 385 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 386 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 387 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 388 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 391 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 394 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 397 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 400 "../parser.y"
    { (yyval.n) = alloc_node(token_symbol, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 403 "../parser.y"
    { (yyval.n) = alloc_node(token_symbol, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 410 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_if, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
    ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 415 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 416 "../parser.y"
    { (yyval.n) = alloc_cond(token_if, NULL, (yyvsp[(2) - (2)].n), NULL);  ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 419 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 420 "../parser.y"
    { (yyval.n) = alloc_node(token_ensure, (yyvsp[(2) - (2)].n), NULL); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 423 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 424 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 427 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 428 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 432 "../parser.y"
    {
    (yyval.n) = alloc_node(token_rescue, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 438 "../parser.y"
    {
    (yyval.n) = alloc_ensure(token_body, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 443 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 444 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 447 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 448 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 451 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 452 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 456 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(3) - (4)].n), (yyvsp[(2) - (4)].n));
  ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 460 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 466 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(4) - (5)].n), (yyvsp[(3) - (5)].n));
  ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 470 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 476 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n));
  ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 480 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, NULL, (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 484 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 489 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 492 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);  ;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 494 "../parser.y"
    {
    (yyval.n) = update_list((yyvsp[(1) - (3)].n), alloc_node(token_object, NULL, NULL));
  ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 499 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 500 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 503 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 504 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 506 "../parser.y"
    {
      (yyval.n) = create_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 509 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 511 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 514 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 516 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), create_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 520 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 524 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 528 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 533 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (8)].n), concat_list((yyvsp[(3) - (8)].n), create_list((yyvsp[(5) - (8)].n), update_list((yyvsp[(7) - (8)].n), (yyvsp[(8) - (8)].n)))));
    ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 537 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 542 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 543 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 546 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 547 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 550 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 553 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 556 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 557 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 560 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 561 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 565 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a constant");
    (yyval.n) = 0;
  ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 570 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be an instance variable");
    (yyval.n) = 0;
  ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 575 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a global variable");
    (yyval.n) = 0;
  ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 580 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a class variable");
    (yyval.n) = 0;
  ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 586 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 587 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 591 "../parser.y"
    {
    (yyval.n) = alloc_node(token_rescue_arg, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 596 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 597 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 600 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 601 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 605 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_when, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
  ;}
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 690 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 691 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 694 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 725 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 726 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 730 "../parser.y"
    {
    /* TODO: Implement a better way to do this, check_lhs can be expensive :( */
    if (check_lhs((yyvsp[(1) - (1)].n)))
      (yyval.n) = (yyvsp[(1) - (1)].n);
    else {
      (yyval.n) = 0;
      yyerror(parser, "syntax error, unexpected '=', expecting $end");
    }
  ;}
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 739 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);  ;}
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 740 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 741 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);  ;}
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 744 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 745 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 748 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 749 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 752 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n); ;}
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 755 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 756 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 757 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 760 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 761 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 764 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 765 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 766 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 767 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 770 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 771 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 773 "../parser.y"
    {
    (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 778 "../parser.y"
    {
    (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 782 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     ;}
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 783 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 784 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     ;}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 785 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 788 "../parser.y"
    { (yyval.n) = alloc_node(token_array, NULL, NULL); ;}
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 789 "../parser.y"
    { (yyval.n) = alloc_node(token_array, (yyvsp[(2) - (3)].n), NULL);   ;}
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 790 "../parser.y"
    { (yyval.n) = alloc_node(token_array, NULL, NULL); ;}
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 794 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 795 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 796 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 799 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 800 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 804 "../parser.y"
    {
    struct node * n = (yyvsp[(3) - (5)].n);
    n->next = (yyvsp[(5) - (5)].n);
    (yyval.n) = alloc_node(token_array_value, (yyvsp[(1) - (5)].n), n);
  ;}
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 815 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 818 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, NULL, NULL);  ;}
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 819 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, (yyvsp[(2) - (3)].n), NULL);    ;}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 822 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 823 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 826 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 827 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 831 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 835 "../parser.y"
    {
    if (parser->last_is_paren) {
      yyerror(parser, "bad parameter list");
      (yyval.n) = 0;
    } else {
      (yyval.n) = (yyvsp[(1) - (2)].n);
      (yyval.n)->r = (yyvsp[(2) - (2)].n);
    }
  ;}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 844 "../parser.y"
    { (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 848 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  ;}
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 854 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 858 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 863 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 867 "../parser.y"
    {
    struct node * n = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 872 "../parser.y"
    {
    struct node * n = alloc_node(token_method_call, (yyvsp[(2) - (4)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 877 "../parser.y"
    {
    (yyval.n) = pop_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 882 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 883 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 887 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 0;
  ;}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 892 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 1;
  ;}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 898 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 899 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 902 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 903 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 907 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 908 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 912 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 279:

/* Line 1464 of yacc.c  */
#line 913 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 914 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, (yyvsp[(1) - (1)].n), NULL);  ;}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 918 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 919 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 922 "../parser.y"
    { (yyval.n) = alloc_node(token_plus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 284:

/* Line 1464 of yacc.c  */
#line 923 "../parser.y"
    { (yyval.n) = alloc_node(token_minus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 924 "../parser.y"
    { (yyval.n) = alloc_node(token_mul, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 925 "../parser.y"
    { (yyval.n) = alloc_node(token_div, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 287:

/* Line 1464 of yacc.c  */
#line 926 "../parser.y"
    { (yyval.n) = alloc_node(token_mod, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 927 "../parser.y"
    { (yyval.n) = alloc_node(token_exp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 289:

/* Line 1464 of yacc.c  */
#line 928 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 929 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 930 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_xor, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 931 "../parser.y"
    { (yyval.n) = alloc_node(token_lshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 932 "../parser.y"
    { (yyval.n) = alloc_node(token_rshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 933 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 934 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 935 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 936 "../parser.y"
    { (yyval.n) = alloc_node(token_cmp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 937 "../parser.y"
    { (yyval.n) = alloc_node(token_eq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      ;}
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 938 "../parser.y"
    { (yyval.n) = alloc_node(token_neq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 939 "../parser.y"
    { (yyval.n) = alloc_node(token_eqq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 940 "../parser.y"
    { (yyval.n) = alloc_node(token_match, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 941 "../parser.y"
    { (yyval.n) = alloc_node(token_nmatch, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 303:

/* Line 1464 of yacc.c  */
#line 942 "../parser.y"
    { (yyval.n) = alloc_node(token_greater, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 943 "../parser.y"
    { (yyval.n) = alloc_node(token_lesser, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 305:

/* Line 1464 of yacc.c  */
#line 944 "../parser.y"
    { (yyval.n) = alloc_node(token_geq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 306:

/* Line 1464 of yacc.c  */
#line 945 "../parser.y"
    { (yyval.n) = alloc_node(token_leq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 946 "../parser.y"
    { (yyval.n) = alloc_node(token_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      ;}
    break;

  case 308:

/* Line 1464 of yacc.c  */
#line 947 "../parser.y"
    { (yyval.n) = alloc_node(token_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 309:

/* Line 1464 of yacc.c  */
#line 948 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 310:

/* Line 1464 of yacc.c  */
#line 949 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 950 "../parser.y"
    { (yyval.n) = alloc_node(token_dot2, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 312:

/* Line 1464 of yacc.c  */
#line 951 "../parser.y"
    { (yyval.n) = alloc_node(token_dot3, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 313:

/* Line 1464 of yacc.c  */
#line 953 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_ternary, (yyvsp[(1) - (8)].n), (yyvsp[(4) - (8)].n), (yyvsp[(8) - (8)].n));
  ;}
    break;

  case 314:

/* Line 1464 of yacc.c  */
#line 956 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_not, (yyvsp[(3) - (3)].n), NULL);;}
    break;

  case 315:

/* Line 1464 of yacc.c  */
#line 957 "../parser.y"
    { (yyval.n) = alloc_node(token_neg, (yyvsp[(3) - (3)].n), NULL);   ;}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 958 "../parser.y"
    { (yyval.n) = alloc_node(token_not, (yyvsp[(3) - (3)].n), NULL);   ;}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 959 "../parser.y"
    { (yyval.n) = alloc_node(token_unary_plus, (yyvsp[(3) - (3)].n), NULL);  ;}
    break;

  case 318:

/* Line 1464 of yacc.c  */
#line 960 "../parser.y"
    { (yyval.n) = alloc_node(token_unary_minus, (yyvsp[(3) - (3)].n), NULL); ;}
    break;

  case 319:

/* Line 1464 of yacc.c  */
#line 961 "../parser.y"
    { (yyval.n) = alloc_node(token_defined, (yyvsp[(3) - (3)].n), NULL);     ;}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 962 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 321:

/* Line 1464 of yacc.c  */
#line 963 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n)   ;}
    break;

  case 322:

/* Line 1464 of yacc.c  */
#line 964 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;



/* Line 1464 of yacc.c  */
#line 4460 "../parser.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (parser, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (parser, yymsg);
	  }
	else
	  {
	    yyerror (parser, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, parser);
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



/* Line 1684 of yacc.c  */
#line 967 "../parser.y"

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
  p->string_names = NULL;
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
  int length;

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
  fread(p->blob, length, 1, fd);
  if (ferror(fd)) {
    fprintf(stderr, "Reading error\n");
    return -1;
  }
  p->length = length;
  return 0;
}

/* We only have to update some attributes about the contents */
void update_contents(struct parser_t * p, const char * contents)
{
  p->blob = strdup(contents);
  p->length = strlen(contents);
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

/* Push a string variable */
void push_string(struct parser_t * parser, char * buffer)
{
  struct node * new_node = alloc_node(token_object, NULL, NULL);

  new_node->name = strdup(buffer);
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
      char * ptr;

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
          for (ptr = buffer; *c != '}'; ++c, ++curs) {
            *ptr++ = *c;
            if (curs >= len) {
              yyerror(parser, "expecting '}' token in string");
              curs = len + 1; /* So we can force curs >= len error */
              break;
            }
          }
          *ptr = '\0';
          push_string(parser, buffer);
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
    char * ptr;

    curs++;
    ++c;
    while (1) {
      if (*c == '#' && *(c + 1) == '{') {
        c += 2;
        curs += 2;
        for (ptr = buffer; *c != '}'; ++c, ++curs) {
          *ptr++ = *c;
          if (curs >= len || *c == '"') {
            yyerror(parser, "expecting '}' token in string");
            curs = len + 1; /* So we can force curs >= len error */
            break;
          }
        }
        *ptr = '\0';
        push_string(parser, buffer);
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
    char * ptr;

    curs++;
    ++c;
    while (1) {
      if (*c == '#' && *(c + 1) == '{') {
        c += 2;
        curs += 2;
        for (ptr = buffer; *c != '}'; ++c, ++curs) {
          *ptr++ = *c;
          if (curs >= len || *c == '`') {
            yyerror(parser, "expecting '}' token in backtick command");
            curs = len + 1; /* So we can force curs >= len error */
            break;
          }
        }
        *ptr = '\0';
        push_string(parser, buffer);
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

RubyAst * rb_compile_file(const char * path, const char * contents)
{
  struct parser_t p;
  RubyAst * result;

  /* Set up parser */
  init_parser(&p);
  update_contents(&p, contents);
  p.name = strdup(path);

  /* Initialize the RubyAst & enter the "parsing" loop */
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


