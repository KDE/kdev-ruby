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
  unsigned char error;
  unsigned char expr_seen;
  unsigned char class_seen;
  unsigned char no_block;
  unsigned char dot_seen;
  unsigned char last_is_paren;
};

#define eof_reached lexer_flags.eof_reached
#define error lexer_flags.error
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
  char ** errors;
  int error_index;

  /* Stack of names */
  struct stack_t * stack[2];
  int sp;

  /* Info about the content to parse */
  unsigned long cursor;
  unsigned long length;
  unsigned int line;
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



/* Line 189 of yacc.c  */
#line 157 "../parser.c"

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
#line 114 "../parser.y"
  struct node * n;  


/* Line 214 of yacc.c  */
#line 303 "../parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 315 "../parser.c"

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
#define YYLAST   2388

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  123
/* YYNRULES -- Number of rules.  */
#define YYNRULES  321
/* YYNRULES -- Number of states.  */
#define YYNSTATES  586

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
     823,   825,   827,   832,   837,   842,   847,   852,   857,   862,
     867,   872,   877,   882,   886,   890,   894,   899,   904,   909,
     914,   919,   924,   929,   934,   939,   944,   949,   954,   959,
     964,   969,   974,   983,   987,   991,   995,   999,  1003,  1007,
    1010,  1012
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
      -1,   214,    -1,   229,    -1,   214,    -1,   229,    87,   193,
     229,    -1,   229,    88,   193,   229,    -1,   229,    89,   193,
     229,    -1,   229,    90,   193,   229,    -1,   229,    91,   193,
     229,    -1,   229,    67,   193,   229,    -1,   229,    77,   193,
     229,    -1,   229,    78,   193,   229,    -1,   229,    79,   193,
     229,    -1,   229,    70,   193,   229,    -1,   229,    71,   193,
     229,    -1,   183,   229,   184,    -1,   183,   208,   184,    -1,
     183,   217,   184,    -1,   229,    96,   193,   229,    -1,   229,
      97,   193,   229,    -1,   229,    99,   193,   229,    -1,   229,
      98,   193,   229,    -1,   229,   100,   193,   229,    -1,   229,
     101,   193,   229,    -1,   229,    85,   193,   229,    -1,   229,
      84,   193,   229,    -1,   229,   102,   193,   229,    -1,   229,
     103,   193,   229,    -1,   229,    75,   193,   229,    -1,   229,
      76,   193,   229,    -1,   229,    31,   193,   229,    -1,   229,
      30,   193,   229,    -1,   229,   106,   193,   229,    -1,   229,
     105,   193,   229,    -1,   229,    73,   193,   229,   193,    66,
     193,   229,    -1,    32,   193,   229,    -1,    63,   193,   229,
      -1,    86,   193,   229,    -1,    69,   193,   229,    -1,    68,
     193,   229,    -1,    34,   193,   229,    -1,   115,   145,    -1,
     116,    -1,   212,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   168,   168,   169,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   193,   194,   197,   198,   199,
     200,   201,   202,   203,   204,   207,   208,   209,   210,   211,
     212,   213,   214,   217,   218,   221,   222,   223,   224,   227,
     228,   229,   232,   233,   234,   235,   236,   237,   238,   239,
     242,   243,   244,   245,   246,   247,   248,   249,   252,   253,
     256,   257,   260,   261,   264,   265,   266,   269,   276,   283,
     289,   295,   301,   305,   309,   313,   317,   323,   322,   332,
     331,   342,   341,   352,   351,   363,   364,   367,   368,   371,
     372,   375,   376,   382,   383,   384,   385,   386,   389,   392,
     395,   398,   401,   404,   405,   413,   414,   417,   418,   421,
     422,   425,   426,   429,   435,   441,   442,   445,   446,   449,
     450,   453,   457,   463,   467,   473,   477,   481,   487,   490,
     491,   497,   498,   501,   502,   503,   507,   508,   512,   513,
     517,   521,   525,   529,   534,   540,   541,   544,   545,   548,
     551,   554,   555,   558,   559,   562,   567,   572,   577,   584,
     585,   588,   594,   595,   598,   599,   602,   608,   609,   612,
     613,   614,   617,   618,   621,   624,   627,   630,   633,   636,
     639,   642,   645,   648,   651,   654,   657,   658,   661,   664,
     667,   670,   673,   676,   679,   682,   685,   688,   689,   692,
     695,   696,   699,   700,   703,   704,   707,   708,   711,   712,
     715,   716,   719,   720,   723,   724,   727,   737,   738,   739,
     742,   743,   746,   747,   750,   753,   754,   755,   758,   759,
     762,   763,   764,   765,   768,   769,   770,   775,   780,   781,
     782,   783,   786,   787,   788,   792,   793,   794,   797,   798,
     801,   813,   816,   817,   820,   821,   824,   825,   828,   832,
     842,   845,   851,   855,   861,   864,   869,   874,   880,   881,
     884,   889,   896,   897,   900,   901,   905,   906,   910,   911,
     915,   916,   919,   920,   921,   922,   923,   924,   925,   926,
     927,   928,   929,   930,   931,   932,   933,   934,   935,   936,
     937,   938,   939,   940,   941,   942,   943,   944,   945,   946,
     947,   948,   949,   953,   954,   955,   956,   957,   958,   959,
     960,   961
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
     228,   228,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229
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
       1,     1,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,     3,     3,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     8,     3,     3,     3,     3,     3,     3,     2,
       1,     1
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
     117,   320,     4,    56,    57,     5,     0,    39,    93,   272,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    48,   321,   200,     8,
     117,   272,    40,   272,    41,    13,   202,   184,   201,   183,
     182,    65,    64,    54,    62,    66,   205,   204,     0,   109,
     206,   209,   198,   174,   176,   179,   177,   178,   181,    93,
       0,    41,    61,    59,     0,     0,     0,   208,   208,   191,
       0,     0,     0,   193,   189,     0,     1,     0,     0,     0,
       0,     0,   265,   268,    34,   208,   319,   118,   119,   120,
       0,   274,   258,   275,   276,   200,   273,     0,     0,     0,
       0,     0,   200,     0,     0,   208,     0,   225,    88,    77,
      86,    92,    91,    79,   200,   115,   200,   200,   225,   242,
      39,   246,   248,   200,   247,   245,   252,   102,   200,   200,
     254,     0,   200,   200,   200,   226,     0,     0,     0,     7,
     260,   267,   200,   259,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   203,     0,    76,   159,   105,   110,   111,   207,
      15,   208,     0,   313,    55,   318,     0,     0,   314,   317,
     316,   315,     9,    10,    11,    12,   100,   270,    86,   271,
     269,   205,     0,     0,     0,   208,     0,     0,     0,   262,
       0,   261,   264,   170,   208,   169,   208,   173,   208,   172,
     208,   180,    72,     0,     0,   200,     0,     0,   210,   211,
       0,   208,     0,   200,    81,   294,   295,   293,     0,     0,
       0,   243,     0,     0,     0,   253,     0,   200,   188,   195,
     196,   219,     0,   227,   216,   240,   234,   238,   117,   228,
     241,   235,   239,   117,   200,   263,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,     0,   160,   164,   162,   208,
     107,   112,   209,   197,    73,    74,   208,   124,   158,   153,
     156,   157,     0,     0,     0,   155,     0,     0,   145,   145,
     151,   145,   147,   154,   199,     0,   122,   279,   277,   278,
     190,   105,   171,   105,     0,     0,   208,     0,   185,   281,
       0,   280,   212,   213,   208,     0,   131,     0,    90,    87,
       0,    97,    83,     0,   208,   266,    22,    18,    21,    23,
      35,    24,    20,   230,    17,    19,     0,    36,   232,    37,
      38,   231,   233,   249,   192,   257,   255,   194,     0,   218,
     200,     0,     0,   236,   237,   220,   309,   308,   287,   291,
     292,   200,   306,   307,   288,   289,   290,   303,   302,   282,
     283,   284,   285,   286,   296,   297,   299,   298,   300,   301,
     304,   305,   311,   310,   208,   200,   161,     0,   106,   208,
     114,    16,     0,   129,   128,   133,   149,   126,   127,     0,
     134,     0,   136,     0,   138,     0,     0,   121,   200,     0,
     103,     0,     0,    69,    70,   105,    71,   208,     0,    89,
     200,    80,   208,   116,     0,   200,   256,   217,   226,   229,
       0,   250,   221,   222,     0,   113,     0,   163,   108,   123,
       0,   125,     0,   145,   148,   145,   147,   145,   145,   152,
     150,   175,    67,     0,    68,   167,   168,   166,     0,    78,
     132,     0,    82,     0,   227,   200,   223,   200,   165,   130,
     146,   142,     0,   135,     0,   137,   140,     0,   208,    75,
      84,   224,     0,   145,   145,   148,   145,   105,   312,   141,
     144,     0,   139,   104,   145,   143
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    55,   240,   265,    57,    58,    59,   423,    60,    61,
      62,    63,    64,   103,   104,    65,   287,   291,   414,   512,
      66,   169,   404,   173,    67,   119,    69,   120,    71,   188,
     499,   500,   480,   236,   237,   238,   108,   294,   146,   147,
     148,   149,   266,   376,   484,   405,   377,   490,   378,   379,
     380,   381,   382,   383,   355,   356,   357,   476,   163,   547,
     274,   278,    72,   501,    73,    74,    75,    76,   164,    77,
      78,    79,    80,   286,   262,   564,    81,   269,    82,   301,
      83,   305,   196,   197,   109,   267,   270,    98,   110,   111,
     112,   290,   408,   440,   313,   521,   522,   523,    84,   316,
     181,    85,    86,   182,   183,    87,    88,    89,   189,   190,
      90,    91,    92,    93,   121,   142,   143,   155,   156,   153,
     388,   400,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -463
static const yytype_int16 yypact[] =
{
     911,    -5,    -5,    -5,   161,    91,    -5,    -5,    -5,    -5,
      -5,    -5,  -463,  -463,  -463,  -463,  2055,  2055,    -5,   161,
      -5,   -33,   -28,     6,  -463,  -463,  -463,  -463,  -463,  -463,
    -463,  -463,  -463,  -463,    19,  -463,  -463,  -463,  -463,  -463,
      37,  -463,  -463,  -463,  -463,  -463,    -5,    -5,    77,    -5,
      -5,    -5,    -5,    -5,    60,   151,   290,   114,   125,     2,
      12,  -463,  -463,  -463,  -463,  -463,  1769,   137,  1826,  1769,
     112,   156,  2055,  2055,  2055,  2055,   716,  2055,    83,     0,
       4,  1769,  1655,  1712,    55,  -463,  -463,  -463,    -5,  -463,
      12,  1769,   114,  1769,  1769,  1236,  -463,  -463,   127,  -463,
    -463,  -463,  -463,  -463,   163,  -463,  -463,  -463,   230,   243,
    -463,    91,  1079,  -463,  -463,  -463,  -463,  -463,  -463,  -463,
     157,  -463,  1522,  1522,  2055,   161,  2055,    91,    91,  -463,
    2055,  2055,  2055,  -463,  -463,  2055,  -463,  2055,  2055,  2055,
    2055,    32,   114,  -463,  -463,    81,  -463,  -463,  -463,  -463,
     995,  -463,  -463,   163,  1522,    -5,  -463,   141,   641,   641,
    1186,  1186,    -5,   256,  2055,  1298,    20,  1522,  -463,  -463,
       9,  -463,  -463,  -463,    -5,   185,    -5,    -5,  1360,  -463,
      41,  -463,  -463,   101,  -463,  1522,  -463,  -463,    -5,   101,
    -463,  1410,    -5,    -5,    -5,  1883,  1151,  1151,  1941,  -463,
    -463,   114,    -5,  -463,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,  -463,   161,  -463,  2055,   263,   243,  -463,  -463,
     290,    91,   224,  2137,  -463,  2137,   199,   201,  -463,   216,
    -463,  -463,  1522,  1522,  1522,  1522,  -463,  -463,  -463,  -463,
    -463,   212,   214,   287,   339,    91,  1079,   217,  1941,  -463,
     221,  -463,  -463,  -463,    91,   294,    91,  -463,    91,  -463,
      91,  -463,  -463,   641,   324,    -5,  1941,   552,  -463,  -463,
      83,    91,    47,    -5,  -463,  -463,  -463,   114,  2091,  2091,
    1941,  -463,   284,  2055,  1998,  -463,   265,    -5,  -463,  -463,
    -463,    47,  1769,  -463,  1522,  -463,   163,  -463,    12,  1522,
    -463,   163,  -463,    12,    -5,  -463,  2055,  2055,  2055,  2055,
    2055,  2055,  2055,  2055,  2055,  2055,  2055,  2055,  2055,  2055,
    2055,  2055,  2055,  2055,  2055,  2055,  2055,  2055,  2055,  2055,
    2055,  2055,  2055,  2055,  -463,    27,  -463,     7,  1522,    91,
     338,  -463,   820,  -463,  -463,  -463,    91,  -463,  -463,  -463,
    -463,  -463,   297,   150,   150,  -463,   273,   115,   163,   163,
    -463,   163,   258,  -463,  -463,   272,  -463,  -463,  -463,  1522,
    -463,   180,  -463,   180,   347,   348,    91,   357,  -463,  -463,
      16,  1522,  -463,  -463,    91,   100,  -463,   461,  -463,  -463,
     358,  -463,  -463,     0,    91,   114,  -463,  -463,  -463,  -463,
     114,  -463,   325,  -463,  -463,  -463,  2055,  -463,  -463,   114,
    -463,  -463,  -463,  -463,  -463,  1522,  -463,  -463,  2055,  -463,
      -5,    55,  2055,  -463,  -463,   320,  2137,  2137,   216,   385,
     385,  1472,  2211,  2248,   443,   723,   723,   603,   603,   204,
     204,   216,   216,   216,  2285,  2285,  2285,  2285,  2285,  2285,
     603,   603,  2174,  2174,    91,    -5,  -463,  2055,  -463,    91,
    -463,   290,   371,  -463,   163,  -463,  -463,  -463,  -463,   304,
    -463,   458,  -463,   458,  -463,   573,  2138,  -463,    -5,   373,
    -463,  2055,   374,  -463,  -463,    69,  -463,    91,   383,  -463,
      -5,  -463,    91,  -463,   384,  1472,  1522,  -463,  1597,  1522,
    1941,  -463,   320,  -463,   329,  -463,    47,  1522,  -463,  -463,
     297,  -463,   150,   163,   258,   163,  -463,   163,   163,  -463,
    -463,  -463,  -463,   641,  -463,  -463,  -463,  -463,   386,  -463,
    -463,   391,  -463,   114,    34,    -5,  -463,    -5,  -463,  -463,
    -463,  -463,   573,  -463,   458,  -463,  -463,   458,    91,  -463,
    -463,  -463,  2055,   163,   163,  -463,   163,   180,  2137,  -463,
    -463,   458,  -463,  -463,   163,  -463
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -463,  -463,     3,   299,  -269,  -261,  -255,  -282,  -463,  -463,
    -463,  -463,  -463,   186,     5,    28,  -463,  -463,  -463,  -463,
     -53,  -463,  -463,   -73,   -69,    76,  -130,   343,     1,  -463,
    -372,  -230,  -463,  -463,  -463,   183,  -276,  -463,   -58,  -463,
    -463,  -463,   167,    53,  -463,  -463,  -264,  -159,  -404,  -462,
    -460,   -60,  -278,  -463,  -463,  -463,  -463,  -463,  -256,  -463,
    -151,  -142,  -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,
    -463,  -463,  -463,  -463,  -463,   102,  -146,  -166,  -411,  -302,
     -42,  -463,   253,   255,   111,   173,   353,  -463,    87,   -97,
    -134,  -463,    35,  -463,   -75,  -463,  -463,   -78,   -68,   248,
    -463,   -55,  -229,  -182,  -463,  -463,  -463,   -36,  -463,   142,
     398,  -463,  -127,  -463,   109,   -90,  -138,    92,    90,  -463,
    -463,  -463,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -226
static const yytype_int16 yytable[] =
{
     122,   123,   201,    56,   260,   105,   360,   175,   276,   166,
     295,   296,   297,   180,   259,   410,   324,   431,   150,   280,
     105,   502,   445,   406,   125,   168,   176,   272,   397,   420,
     420,   284,   199,   538,   520,   539,   325,   421,   421,   145,
     273,    96,   277,   422,   422,   285,   184,   127,   150,   312,
     154,   171,   128,   154,   144,   171,   158,   159,   160,   161,
     165,   167,   106,   260,   -20,   178,   185,   191,   -22,   427,
     427,   288,   192,   106,   174,   154,    68,   154,   154,   475,
    -214,   -18,    36,    37,   359,   192,   162,    41,   257,   535,
     107,   537,    51,   172,    33,   485,   486,   172,    37,   -21,
     574,   107,   539,   -17,   271,    44,    45,   363,   243,    94,
     245,   520,   272,   289,   248,   249,   250,  -214,   433,   251,
     192,   252,   253,   254,   255,   256,   105,   261,   508,   180,
     244,   384,   396,    36,    37,   193,   194,   106,   514,   -23,
     411,   407,    68,   510,   362,    68,   402,    96,   283,   193,
     194,   136,   426,   426,   170,   107,   152,    68,   573,  -186,
     317,   322,   184,   576,  -100,   107,   192,    68,   362,    68,
      68,   429,   429,   232,   403,    94,   141,   584,    94,   314,
     319,   319,   185,   200,   203,   202,   195,   -24,    68,   372,
      94,    36,    37,   488,   498,   359,    41,   368,   239,   -17,
      94,   369,    94,    94,   474,   583,   233,   415,   370,   371,
      35,   101,   102,   534,   540,   536,   157,   258,   -19,   358,
     492,    94,   494,   412,   315,   320,    68,   420,   192,   424,
     424,   180,   387,   258,   105,   421,   551,   409,   246,   247,
     234,   422,   439,   375,   441,   275,   275,   279,   279,   546,
     399,   235,   389,   571,   560,   268,   263,   176,   507,    94,
     443,   242,   428,   432,   184,   444,   282,   427,   195,   293,
     401,   206,    68,    68,   517,   545,   150,   260,   359,    41,
     364,   150,   365,   206,   185,   300,   575,   435,   191,   536,
    -187,   304,   264,   219,   220,   221,   178,   367,   386,   425,
     425,   137,   138,   536,   390,    94,    94,   392,   139,   140,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   555,   201,
     513,   162,    68,    70,   550,   434,   437,   479,    37,   553,
     426,   487,   496,   497,    97,    99,   100,   503,   504,   113,
     114,   115,   116,   117,   118,   481,   258,   506,   511,   429,
     275,   124,   312,   126,   561,    94,   563,   144,   565,   566,
      46,   529,   531,   542,   544,   391,   368,   393,    68,   394,
     369,   395,   568,   549,   552,   557,   569,   370,   371,   129,
     130,   570,   131,   132,   133,   134,   135,   430,   430,    70,
     515,   241,    70,   372,   579,   580,   373,   582,   442,   354,
     361,    94,   516,   442,    70,   585,   519,   424,   374,   366,
     489,   533,   375,   298,    70,   299,    70,    70,    68,   385,
     509,   198,   275,   554,   556,   321,   436,     0,   483,   239,
       0,   180,   206,     0,     0,    70,     0,   558,     0,   477,
       0,   527,     0,   415,   151,     0,     0,   151,     0,     0,
     478,    94,   217,   218,   219,   220,   221,   482,     0,   177,
     491,   493,     0,   495,   184,   543,     0,   279,     0,   151,
       0,   151,   151,    70,     0,     0,     0,   425,     0,     0,
       0,     0,   314,     0,   185,   368,     0,   505,   368,   369,
     206,     0,   369,   207,   208,   281,   370,   371,     0,   370,
     371,     0,     0,     0,     0,     0,     0,   292,     0,     0,
     217,   218,   219,   220,   221,   532,   302,     0,   373,    70,
      70,   303,   306,   518,     0,   308,   309,   310,     0,     0,
     374,   375,     0,     0,   375,     0,   578,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   525,   530,     0,     0,     0,
     528,     0,     0,     0,   318,   323,     0,     0,   402,   368,
       0,     0,     0,   369,     0,   430,   559,     0,     0,    70,
     370,   371,     0,     0,     0,     0,     0,     0,   548,     0,
     368,     0,     0,     0,   369,     0,   403,     0,     0,   373,
     275,   370,   371,     0,    52,   562,     0,     0,   398,     0,
     567,   374,     0,     0,     0,   375,   413,     0,     0,     0,
     532,     0,     0,     0,   273,    70,     0,     0,     0,     0,
     438,     0,   374,     0,     0,     0,   375,     0,     0,     0,
     206,   204,   205,   207,   208,     0,   581,   302,     0,   577,
     212,   213,   214,     0,     0,     0,     0,   106,     0,     0,
     217,   218,   219,   220,   221,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,     0,     0,   206,     0,
     177,   207,   208,     0,   209,   107,   210,   211,   212,   213,
     214,     0,     0,     0,     0,   215,   216,     0,   217,   218,
     219,   220,   221,   162,     0,     0,     0,   222,   223,   224,
     225,   226,   227,   228,   229,     0,   230,   231,    18,     0,
      20,     0,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     0,    33,    34,    35,     0,    37,    38,     0,
      40,    41,    42,    43,    44,    45,    46,     0,     0,    47,
      48,     0,     0,     0,    49,    50,     0,     0,     0,     0,
     206,     0,     0,   207,   208,     0,     0,     0,    52,     0,
     212,     0,    53,     0,   524,     0,     0,     0,     0,    54,
     217,   218,   219,   220,   221,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     5,   526,     0,
       0,     6,     7,     0,     0,     0,     8,     0,     9,    10,
      11,    12,    13,    14,    15,     0,     0,     0,    16,    17,
       0,   541,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   106,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,     0,     0,    47,    48,     0,     0,     0,    49,    50,
       0,     0,     0,     0,   107,     0,     0,     0,     0,     0,
      51,     0,    52,     0,     0,     0,    53,     0,   302,     0,
     572,     0,     0,    54,     1,     2,     3,     4,     5,     0,
       0,     0,     6,     7,     0,     0,     0,     8,     0,     9,
      10,    11,    12,    13,    14,    15,     0,     0,     0,    16,
      17,     0,     0,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,     0,     0,    47,    48,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,    52,     0,     0,     0,    53,     1,     2,
       3,     4,     5,     0,    54,     0,     6,     7,     0,     0,
       0,     8,     0,     9,    10,    11,    12,    13,    14,    15,
       0,     0,     0,    16,    17,     0,     0,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,     0,     0,    47,    48,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,     0,   264,     0,    51,     0,    52,     0,     0,
       0,    53,     1,     2,     3,     4,     5,     0,    54,     0,
       6,     7,     0,     0,     0,     8,     0,     9,    10,    11,
      12,    13,    14,    15,     0,     0,     0,    16,    17,     0,
       0,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
       0,     0,    47,    48,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,     1,     2,     3,     0,     5,    51,
       0,    52,     6,     7,     0,    53,     0,     8,     0,     9,
      10,    11,    54,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,    33,    34,
      35,    36,    37,    38,     0,    40,    41,    42,    43,    44,
      45,    46,   277,     0,    47,    48,   204,   205,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,   106,    52,     0,     0,     0,    53,     0,     0,
       0,     0,     0,     0,    54,     0,     0,     0,     0,     0,
       0,     0,     0,   206,     0,     0,   207,   208,     0,   209,
     107,   210,   211,   212,   213,   214,   204,   205,     0,     0,
     215,   216,     0,   217,   218,   219,   220,   221,     0,     0,
       0,     0,   222,   223,   224,   225,   226,   227,   228,   229,
       0,   230,   231,     0,     0,     0,     0,     0,     0,     0,
       0,  -225,     0,   206,     0,     0,   207,   208,     0,   209,
       0,   210,   211,   212,   213,   214,     0,     0,     0,     0,
     215,   216,     0,   217,   218,   219,   220,   221,   204,   205,
    -225,  -225,   222,   223,   224,   225,   226,   227,   228,   229,
       0,   230,   231,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   206,     0,     0,   207,   208,
       0,   209,   107,   210,   211,   212,   213,   214,     0,     0,
       0,     0,   215,   216,     0,   217,   218,   219,   220,   221,
     204,   205,     0,     0,   222,   223,   224,   225,   226,   227,
     228,   229,     0,   230,   231,     0,    96,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   206,     0,     0,
     207,   208,     0,   209,     0,   210,   211,   212,   213,   214,
     204,   205,     0,  -200,   215,   216,     0,   217,   218,   219,
     220,   221,     0,     0,     0,     0,   222,   223,   224,   225,
     226,   227,   228,   229,     0,   230,   231,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   206,     0,     0,
     207,   208,   307,   209,     0,   210,   211,   212,   213,   214,
       0,     0,     0,     0,   215,   216,     0,   217,   218,   219,
     220,   221,   204,   205,     0,     0,   222,   223,   224,   225,
     226,   227,   228,   229,     0,   230,   231,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   206,
       0,     0,   207,   208,     0,   209,     0,   210,   211,   212,
     213,   214,   204,   205,     0,     0,   215,   216,     0,   217,
     218,   219,   220,   221,     0,     0,     0,     0,   222,   223,
     224,   225,   226,   227,   228,   229,     0,   230,   231,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   206,
       0,     0,   207,   208,     0,   209,     0,   210,   211,   212,
     213,   214,     0,     0,     0,     0,   215,   216,     0,   217,
     218,   219,   220,   221,     0,     0,     0,     0,   222,   223,
     224,   225,   226,   227,   228,   229,     0,   230,   231,    18,
       0,    20,     0,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,  -215,    33,    34,    35,     0,    37,    38,
       0,    40,    41,    42,    43,    44,    45,    46,     0,     0,
      47,    48,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
    -215,     0,     0,    53,     0,     0,   311,    18,     0,    20,
      54,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    33,    34,    35,     0,    37,    38,     0,    40,
      41,    42,    43,    44,    45,    46,   179,     0,    47,    48,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,    52,     0,     0,
       0,    53,     0,     0,    18,     0,    20,     0,    54,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    33,
      34,    35,     0,    37,    38,     0,    40,    41,    42,    43,
      44,    45,    46,     0,     0,    47,    48,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   186,    52,     0,     0,     0,    53,     0,
       0,    18,     0,    20,   187,    54,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,    36,
      37,    38,     0,    40,    41,    42,    43,    44,    45,    46,
       0,     0,    47,    48,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    52,     0,     0,     0,    53,     0,     0,   -86,     0,
     -86,     0,    54,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,     0,   -86,   -86,   -86,   -86,   -86,   -86,     0,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,     0,     0,   -86,
     -86,     0,     0,     0,   -86,   -86,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -86,     0,
       0,     0,   -86,     0,     0,    18,     0,    20,     0,   -86,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      33,    34,    35,     0,    37,    38,     0,    40,    41,    42,
      43,    44,    45,    46,     0,     0,    47,    48,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    52,     0,     0,     0,    53,
       0,     0,   311,    18,     0,    20,    54,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,    33,    34,
      35,     0,    37,    38,     0,    40,    41,    42,    43,    44,
      45,    46,     0,     0,    47,    48,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,    52,     0,     0,     0,    53,     0,     0,
      18,     0,    20,     0,    54,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    33,    34,    35,     0,    37,
      38,     0,    40,    41,    42,    43,    44,    45,    46,     0,
       0,    47,    48,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,     0,     0,     0,    53,     0,     0,    18,     0,    20,
     187,    54,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    33,    34,    35,     0,    37,    38,     0,    40,
      41,    42,    43,    44,    45,    46,     0,     0,    47,    48,
       0,     0,     0,    49,    50,     0,     0,     0,   416,    24,
      25,    26,    27,    28,    29,    30,    31,    52,    33,   417,
      35,    53,    37,    38,     0,   418,    41,    42,    54,    44,
      45,    46,     0,     0,     0,   419,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,    52,     0,   416,    24,    25,    26,    27,
      28,    29,    30,    31,    54,    33,   417,    35,     0,    37,
      38,     0,   418,    41,    42,     0,    44,    45,    46,     0,
       0,     0,   419,     0,   206,     0,     0,   207,   208,     0,
     209,     0,   210,   211,   212,   213,   214,     0,     0,     0,
      52,   215,   216,     0,   217,   218,   219,   220,   221,     0,
       0,    54,     0,   222,   223,   224,   225,   226,   227,   228,
     229,   206,   230,   231,   207,   208,     0,     0,     0,   210,
     211,   212,   213,   214,     0,     0,     0,     0,   215,   216,
       0,   217,   218,   219,   220,   221,     0,     0,     0,     0,
     222,   223,   224,   225,   226,   227,   228,   229,   206,  -226,
    -226,   207,   208,     0,     0,     0,     0,   211,   212,   213,
     214,     0,     0,     0,     0,   215,   216,     0,   217,   218,
     219,   220,   221,     0,     0,     0,     0,   222,   223,   224,
     225,   226,   227,   228,   229,   206,     0,     0,   207,   208,
       0,     0,     0,     0,     0,   212,   213,   214,     0,     0,
       0,     0,   215,   216,     0,   217,   218,   219,   220,   221,
       0,     0,     0,     0,   222,   223,   224,   225,   226,   227,
     228,   229,   206,     0,     0,   207,   208,     0,     0,     0,
       0,     0,   212,   213,   214,     0,     0,     0,     0,   215,
     216,     0,   217,   218,   219,   220,   221,     0,     0,     0,
       0,  -226,  -226,  -226,  -226,  -226,  -226,   228,   229
};

static const yytype_int16 yycheck[] =
{
      16,    17,    92,     0,   142,     4,   236,    80,   159,    77,
     176,   177,   178,    82,   141,   291,   198,   299,    60,   161,
      19,   393,   324,   287,    19,    78,    81,   157,   284,   298,
     299,   165,    90,   495,   445,   495,   202,   298,   299,    27,
      13,    46,    26,   298,   299,    25,    82,    80,    90,   195,
      66,    51,    80,    69,    52,    51,    72,    73,    74,    75,
      76,    77,    46,   201,    62,    81,    82,    83,    62,   298,
     299,    62,    65,    46,    70,    91,     0,    93,    94,    72,
      46,    62,    50,    51,    15,    65,    17,    55,   141,   493,
      74,   495,    80,    93,    47,   373,   374,    93,    51,    62,
     562,    74,   562,    62,   157,    58,    59,   241,   124,     0,
     126,   522,   242,   104,   130,   131,   132,    83,   300,   135,
      65,   137,   138,   139,   140,    93,   125,    46,   404,   198,
     125,   265,   283,    50,    51,    94,    95,    46,   414,    62,
      93,   287,    66,   407,   241,    69,    46,    46,   164,    94,
      95,     0,   298,   299,    78,    74,    66,    81,   562,    78,
     196,   197,   198,   567,   104,    74,    65,    91,   265,    93,
      94,   298,   299,    46,    74,    66,    62,   581,    69,   195,
     196,   197,   198,    91,    94,    93,    84,    62,   112,    74,
      81,    50,    51,    78,    14,    15,    55,    47,   111,    62,
      91,    51,    93,    94,   355,   577,   104,   297,    58,    59,
      49,    50,    51,   491,   496,   493,   104,   141,    62,   235,
     379,   112,   381,   292,   196,   197,   150,   496,    65,   298,
     299,   300,   268,   157,   233,   496,   512,   290,   127,   128,
      10,   496,   311,    93,   312,   158,   159,   160,   161,   505,
     286,     8,   268,   555,   532,   153,   145,   312,   400,   150,
     318,   104,   298,   299,   300,   323,    10,   496,   166,    84,
     286,    67,   196,   197,   440,   505,   318,   415,    15,    55,
      81,   323,    81,    67,   300,   183,   564,   303,   304,   567,
      78,   189,    78,    89,    90,    91,   312,    10,    81,   298,
     299,    11,    12,   581,    83,   196,   197,    13,    18,    19,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   520,   429,
     413,    17,   266,     0,   510,    61,    81,     9,    51,   515,
     496,    78,    94,    81,     1,     2,     3,    10,    10,     6,
       7,     8,     9,    10,    11,   362,   290,    10,    10,   496,
     283,    18,   518,    20,   533,   266,   535,    52,   537,   538,
      60,    10,    78,    10,    10,   274,    47,   276,   312,   278,
      51,   280,   543,    10,    10,    66,    10,    58,    59,    46,
      47,    10,    49,    50,    51,    52,    53,   298,   299,    66,
     426,   112,    69,    74,   573,   574,    77,   576,   316,   233,
     237,   312,   438,   321,    81,   584,   442,   496,    89,   262,
     377,   491,    93,   180,    91,   180,    93,    94,   362,   266,
     405,    88,   355,   518,   522,   197,   304,    -1,   372,   362,
      -1,   520,    67,    -1,    -1,   112,    -1,   526,    -1,   357,
      -1,   477,    -1,   553,    66,    -1,    -1,    69,    -1,    -1,
     359,   362,    87,    88,    89,    90,    91,   366,    -1,    81,
     378,   379,    -1,   381,   520,   501,    -1,   400,    -1,    91,
      -1,    93,    94,   150,    -1,    -1,    -1,   496,    -1,    -1,
      -1,    -1,   518,    -1,   520,    47,    -1,   396,    47,    51,
      67,    -1,    51,    70,    71,   162,    58,    59,    -1,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,   174,    -1,    -1,
      87,    88,    89,    90,    91,    77,   183,    -1,    77,   196,
     197,   188,   189,   441,    -1,   192,   193,   194,    -1,    -1,
      89,    93,    -1,    -1,    93,    -1,   572,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   474,   484,    -1,    -1,    -1,
     479,    -1,    -1,    -1,   196,   197,    -1,    -1,    46,    47,
      -1,    -1,    -1,    51,    -1,   496,   530,    -1,    -1,   266,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,   507,    -1,
      47,    -1,    -1,    -1,    51,    -1,    74,    -1,    -1,    77,
     543,    58,    59,    -1,    82,   533,    -1,    -1,   285,    -1,
     538,    89,    -1,    -1,    -1,    93,   293,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    13,   312,    -1,    -1,    -1,    -1,
     307,    -1,    89,    -1,    -1,    -1,    93,    -1,    -1,    -1,
      67,    30,    31,    70,    71,    -1,   574,   324,    -1,   568,
      77,    78,    79,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      87,    88,    89,    90,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   362,    -1,    -1,    67,    -1,
     312,    70,    71,    -1,    73,    74,    75,    76,    77,    78,
      79,    -1,    -1,    -1,    -1,    84,    85,    -1,    87,    88,
      89,    90,    91,    17,    -1,    -1,    -1,    96,    97,    98,
      99,   100,   101,   102,   103,    -1,   105,   106,    32,    -1,
      34,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    48,    49,    -1,    51,    52,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    63,
      64,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    70,    71,    -1,    -1,    -1,    82,    -1,
      77,    -1,    86,    -1,   451,    -1,    -1,    -1,    -1,    93,
      87,    88,    89,    90,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,   475,    -1,
      -1,    11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    28,    29,
      -1,   498,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    63,    64,    -1,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    82,    -1,    -1,    -1,    86,    -1,   555,    -1,
     557,    -1,    -1,    93,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    28,
      29,    -1,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    64,    -1,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    82,    -1,    -1,    -1,    86,     3,     4,
       5,     6,     7,    -1,    93,    -1,    11,    12,    -1,    -1,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    28,    29,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    64,
      -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    -1,    80,    -1,    82,    -1,    -1,
      -1,    86,     3,     4,     5,     6,     7,    -1,    93,    -1,
      11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    28,    29,    -1,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    64,    -1,    -1,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    80,
      -1,    82,    11,    12,    -1,    86,    -1,    16,    -1,    18,
      19,    20,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    58,
      59,    60,    26,    -1,    63,    64,    30,    31,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    46,    82,    -1,    -1,    -1,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    70,    71,    -1,    73,
      74,    75,    76,    77,    78,    79,    30,    31,    -1,    -1,
      84,    85,    -1,    87,    88,    89,    90,    91,    -1,    -1,
      -1,    -1,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    67,    -1,    -1,    70,    71,    -1,    73,
      -1,    75,    76,    77,    78,    79,    -1,    -1,    -1,    -1,
      84,    85,    -1,    87,    88,    89,    90,    91,    30,    31,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,   105,   106,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    70,    71,
      -1,    73,    74,    75,    76,    77,    78,    79,    -1,    -1,
      -1,    -1,    84,    85,    -1,    87,    88,    89,    90,    91,
      30,    31,    -1,    -1,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,   105,   106,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      70,    71,    -1,    73,    -1,    75,    76,    77,    78,    79,
      30,    31,    -1,    83,    84,    85,    -1,    87,    88,    89,
      90,    91,    -1,    -1,    -1,    -1,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      70,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      -1,    -1,    -1,    -1,    84,    85,    -1,    87,    88,    89,
      90,    91,    30,    31,    -1,    -1,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,   105,   106,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    70,    71,    -1,    73,    -1,    75,    76,    77,
      78,    79,    30,    31,    -1,    -1,    84,    85,    -1,    87,
      88,    89,    90,    91,    -1,    -1,    -1,    -1,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,   105,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    70,    71,    -1,    73,    -1,    75,    76,    77,
      78,    79,    -1,    -1,    -1,    -1,    84,    85,    -1,    87,
      88,    89,    90,    91,    -1,    -1,    -1,    -1,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,   105,   106,    32,
      -1,    34,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    51,    52,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      63,    64,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      83,    -1,    -1,    86,    -1,    -1,    89,    32,    -1,    34,
      93,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    48,    49,    -1,    51,    52,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    63,    64,
      -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    82,    -1,    -1,
      -1,    86,    -1,    -1,    32,    -1,    34,    -1,    93,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    -1,    51,    52,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    64,    -1,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    86,    -1,
      -1,    32,    -1,    34,    92,    93,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    64,    -1,    -1,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    -1,    86,    -1,    -1,    32,    -1,
      34,    -1,    93,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    48,    49,    50,    51,    52,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    63,
      64,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    86,    -1,    -1,    32,    -1,    34,    -1,    93,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    -1,    51,    52,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    64,    -1,    -1,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,
      -1,    -1,    89,    32,    -1,    34,    93,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    -1,    51,    52,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    64,    -1,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    82,    -1,    -1,    -1,    86,    -1,    -1,
      32,    -1,    34,    -1,    93,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    -1,    51,
      52,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    63,    64,    -1,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    -1,    86,    -1,    -1,    32,    -1,    34,
      92,    93,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    48,    49,    -1,    51,    52,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    64,
      -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    82,    47,    48,
      49,    86,    51,    52,    -1,    54,    55,    56,    93,    58,
      59,    60,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    82,    -1,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    93,    47,    48,    49,    -1,    51,
      52,    -1,    54,    55,    56,    -1,    58,    59,    60,    -1,
      -1,    -1,    64,    -1,    67,    -1,    -1,    70,    71,    -1,
      73,    -1,    75,    76,    77,    78,    79,    -1,    -1,    -1,
      82,    84,    85,    -1,    87,    88,    89,    90,    91,    -1,
      -1,    93,    -1,    96,    97,    98,    99,   100,   101,   102,
     103,    67,   105,   106,    70,    71,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    -1,    -1,    -1,    -1,    84,    85,
      -1,    87,    88,    89,    90,    91,    -1,    -1,    -1,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,    67,   105,
     106,    70,    71,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    -1,    -1,    -1,    -1,    84,    85,    -1,    87,    88,
      89,    90,    91,    -1,    -1,    -1,    -1,    96,    97,    98,
      99,   100,   101,   102,   103,    67,    -1,    -1,    70,    71,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    -1,    -1,
      -1,    -1,    84,    85,    -1,    87,    88,    89,    90,    91,
      -1,    -1,    -1,    -1,    96,    97,    98,    99,   100,   101,
     102,   103,    67,    -1,    -1,    70,    71,    -1,    -1,    -1,
      -1,    -1,    77,    78,    79,    -1,    -1,    -1,    -1,    84,
      85,    -1,    87,    88,    89,    90,    91,    -1,    -1,    -1,
      -1,    96,    97,    98,    99,   100,   101,   102,   103
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
     157,   158,   159,   160,   197,   192,    81,   214,   227,   229,
      83,   191,    13,   191,   191,   191,   167,   165,   193,   214,
     228,   229,    46,    74,   129,   152,   153,   183,   199,   127,
     143,    93,   131,   193,   125,   222,    37,    48,    54,    64,
     111,   112,   113,   114,   131,   135,   183,   209,   214,   219,
     221,   114,   214,   210,    61,   229,   216,    81,   193,   131,
     200,   205,   182,   145,   145,   186,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   229,   167,    72,   164,   182,   191,     9,
     139,   109,   191,   132,   151,   159,   159,    78,    78,   150,
     154,   182,   154,   182,   154,   182,    94,    81,    14,   137,
     138,   170,   137,    10,    10,   191,    10,   168,   143,   199,
     153,    10,   126,   130,   143,   229,   229,   184,   182,   229,
     185,   202,   203,   204,   193,   191,   193,   229,   191,    10,
     182,    78,    77,   158,   159,   155,   159,   155,   156,   157,
     114,   193,    10,   229,    10,   138,   165,   166,   191,    10,
     184,   143,    10,   184,   201,   210,   204,    66,   131,   132,
     159,   154,   182,   154,   182,   154,   154,   182,   167,    10,
      10,   186,   193,   155,   156,   159,   155,   191,   229,   154,
     154,   182,   154,   137,   155,   154
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
#line 168 "../parser.y"
    { parser->ast = NULL; YYACCEPT; ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 170 "../parser.y"
    {
    if (parser->error) {
      free_ast(parser->ast);
      parser->ast = NULL;
    } else
      parser->ast = (yyvsp[(1) - (1)].n);
    YYACCEPT;
  ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 183 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 185 "../parser.y"
    { (yyval.n) = alloc_cond(token_if, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);      ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 186 "../parser.y"
    { (yyval.n) = alloc_cond(token_unless, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);  ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 187 "../parser.y"
    { (yyval.n) = alloc_cond(token_while, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);   ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 188 "../parser.y"
    { (yyval.n) = alloc_cond(token_until, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);   ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 190 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 193 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 194 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 197 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 198 "../parser.y"
    { (yyval.n) = alloc_node(token_numeric, NULL, NULL);   ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 199 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 200 "../parser.y"
    { (yyval.n) = alloc_node(token_string, NULL, NULL);    ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 201 "../parser.y"
    { (yyval.n) = alloc_node(token_regexp, NULL, NULL);    ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 202 "../parser.y"
    { (yyval.n) = alloc_node(token_heredoc, NULL, NULL);   ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 203 "../parser.y"
    { (yyval.n) = alloc_node(token_backtick, NULL, NULL);  ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 204 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);    ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 221 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 222 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 223 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 224 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 227 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 228 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 229 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 232 "../parser.y"
    { (yyval.n) = alloc_node(token_numeric, NULL, NULL);   ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 233 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 234 "../parser.y"
    { (yyval.n) = alloc_node(token_string, NULL, NULL);    ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 235 "../parser.y"
    { (yyval.n) = alloc_node(token_regexp, NULL, NULL);    ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 236 "../parser.y"
    { (yyval.n) = alloc_node(token_heredoc, NULL, NULL);   ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 237 "../parser.y"
    { (yyval.n) = alloc_node(token_backtick, NULL, NULL);  ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 238 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 239 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);    ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 242 "../parser.y"
    { (yyval.n) = alloc_node(token_break, NULL, NULL);   ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 243 "../parser.y"
    { (yyval.n) = alloc_node(token_redo, NULL, NULL);    ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 244 "../parser.y"
    { (yyval.n) = alloc_node(token_retry, NULL, NULL);   ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 245 "../parser.y"
    { (yyval.n) = alloc_node(token_next, NULL, NULL);    ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 246 "../parser.y"
    { (yyval.n) = alloc_node(token_undef, (yyvsp[(2) - (2)].n), NULL);     ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 247 "../parser.y"
    { (yyval.n) = alloc_node(token_alias, (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));       ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 248 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 249 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 252 "../parser.y"
    { (yyval.n) = alloc_node(token_yield, NULL, NULL);   ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 253 "../parser.y"
    { (yyval.n) = alloc_node(token_yield, (yyvsp[(2) - (2)].n), NULL);     ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 256 "../parser.y"
    { (yyval.n) = alloc_node(token_return, NULL, NULL);  ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 257 "../parser.y"
    { (yyval.n) = alloc_node(token_return, (yyvsp[(2) - (2)].n), NULL);    ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 260 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 261 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 264 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 265 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 266 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 273 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_if, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
  ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 280 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_unless, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
    ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 286 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_while, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 292 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_until, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 298 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_case, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 302 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_case, NULL, (yyvsp[(2) - (3)].n), NULL);
    ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 306 "../parser.y"
    {
      (yyval.n) = alloc_node(token_up_begin, (yyvsp[(3) - (4)].n), NULL);
    ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 310 "../parser.y"
    {
      (yyval.n) = alloc_node(token_up_end, (yyvsp[(3) - (4)].n), NULL);
    ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 314 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_for, (yyvsp[(4) - (7)].n), (yyvsp[(6) - (7)].n), (yyvsp[(2) - (7)].n));
    ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 318 "../parser.y"
    {
      (yyval.n) = (yyvsp[(2) - (3)].n);
      (yyval.n)->kind = token_exception;
    ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 323 "../parser.y"
    {
      parser->in_def++;
    ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 327 "../parser.y"
    {
      parser->in_def--;
      (yyval.n) = alloc_cond(token_function, (yyvsp[(2) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(4) - (6)].n));
    ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 332 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "module definition in method body");
    ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 338 "../parser.y"
    {
      (yyval.n) = alloc_node(token_module, (yyvsp[(4) - (5)].n), (yyvsp[(2) - (5)].n));
    ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 342 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 348 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_class, (yyvsp[(3) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(2) - (6)].n));
    ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 352 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 358 "../parser.y"
    {
      (yyval.n) = alloc_node(token_singleton_class, (yyvsp[(6) - (7)].n), (yyvsp[(4) - (7)].n));
    ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 363 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 364 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 367 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 368 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 371 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 372 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 375 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 377 "../parser.y"
    {
    yyerror(parser, "class/module name must be CONSTANT");
  ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 382 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 383 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 384 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 385 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 386 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 389 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 392 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 395 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 398 "../parser.y"
    { (yyval.n) = alloc_node(token_symbol, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 401 "../parser.y"
    { (yyval.n) = alloc_node(token_symbol, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 408 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_if, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
    ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 413 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 414 "../parser.y"
    { (yyval.n) = alloc_cond(token_if, NULL, (yyvsp[(2) - (2)].n), NULL);  ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 417 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 418 "../parser.y"
    { (yyval.n) = alloc_node(token_ensure, (yyvsp[(2) - (2)].n), NULL); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 421 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 422 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 425 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 426 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 430 "../parser.y"
    {
    (yyval.n) = alloc_node(token_rescue, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 436 "../parser.y"
    {
    (yyval.n) = alloc_ensure(token_body, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 441 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 442 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 445 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 446 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 449 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 450 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 454 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(3) - (4)].n), (yyvsp[(2) - (4)].n));
  ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 458 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 464 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(4) - (5)].n), (yyvsp[(3) - (5)].n));
  ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 468 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 474 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n));
  ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 478 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, NULL, (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 482 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 487 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 490 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);  ;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 492 "../parser.y"
    {
    (yyval.n) = update_list((yyvsp[(1) - (3)].n), alloc_node(token_object, NULL, NULL));
  ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 497 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 498 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 501 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 502 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 504 "../parser.y"
    {
      (yyval.n) = create_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 507 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 509 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 512 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 514 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), create_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 518 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 522 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 526 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 531 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (8)].n), concat_list((yyvsp[(3) - (8)].n), create_list((yyvsp[(5) - (8)].n), update_list((yyvsp[(7) - (8)].n), (yyvsp[(8) - (8)].n)))));
    ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 535 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 540 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 541 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 544 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 545 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 548 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 551 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 554 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 555 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 558 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 559 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 563 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a constant");
    (yyval.n) = 0;
  ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 568 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be an instance variable");
    (yyval.n) = 0;
  ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 573 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a global variable");
    (yyval.n) = 0;
  ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 578 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a class variable");
    (yyval.n) = 0;
  ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 584 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 585 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 589 "../parser.y"
    {
    (yyval.n) = alloc_node(token_rescue_arg, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 594 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 595 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 598 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 599 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 603 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_when, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
  ;}
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 688 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 689 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 692 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 723 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 724 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 728 "../parser.y"
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
#line 737 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);  ;}
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 738 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 739 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);  ;}
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 742 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 743 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 746 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 747 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 750 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n); ;}
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 753 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 754 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 755 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 758 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 759 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 762 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 763 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 764 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 765 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 768 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 769 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 771 "../parser.y"
    {
    (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 776 "../parser.y"
    {
    (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 780 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     ;}
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 781 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 782 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     ;}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 783 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 786 "../parser.y"
    { (yyval.n) = alloc_node(token_array, NULL, NULL); ;}
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 787 "../parser.y"
    { (yyval.n) = alloc_node(token_array, (yyvsp[(2) - (3)].n), NULL);   ;}
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 788 "../parser.y"
    { (yyval.n) = alloc_node(token_array, NULL, NULL); ;}
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 792 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 793 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 794 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 797 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 798 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 802 "../parser.y"
    {
    struct node * n = (yyvsp[(3) - (5)].n);
    n->next = (yyvsp[(5) - (5)].n);
    (yyval.n) = alloc_node(token_array_value, (yyvsp[(1) - (5)].n), n);
  ;}
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 813 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 816 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, NULL, NULL);  ;}
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 817 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, (yyvsp[(2) - (3)].n), NULL);    ;}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 820 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 821 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 824 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 825 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 829 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 833 "../parser.y"
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
#line 842 "../parser.y"
    { (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 846 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  ;}
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 852 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 856 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 861 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 865 "../parser.y"
    {
    struct node * n = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 870 "../parser.y"
    {
    struct node * n = alloc_node(token_method_call, (yyvsp[(2) - (4)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 875 "../parser.y"
    {
    (yyval.n) = pop_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 880 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 881 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 885 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 0;
  ;}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 890 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 1;
  ;}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 896 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 897 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 900 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 901 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 905 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 906 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 910 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 279:

/* Line 1464 of yacc.c  */
#line 911 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 915 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 916 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 919 "../parser.y"
    { (yyval.n) = alloc_node(token_plus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 920 "../parser.y"
    { (yyval.n) = alloc_node(token_minus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 284:

/* Line 1464 of yacc.c  */
#line 921 "../parser.y"
    { (yyval.n) = alloc_node(token_mul, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 922 "../parser.y"
    { (yyval.n) = alloc_node(token_div, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 923 "../parser.y"
    { (yyval.n) = alloc_node(token_mod, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 287:

/* Line 1464 of yacc.c  */
#line 924 "../parser.y"
    { (yyval.n) = alloc_node(token_exp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 925 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 289:

/* Line 1464 of yacc.c  */
#line 926 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 927 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_xor, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 928 "../parser.y"
    { (yyval.n) = alloc_node(token_lshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 929 "../parser.y"
    { (yyval.n) = alloc_node(token_rshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 930 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 931 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 932 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 933 "../parser.y"
    { (yyval.n) = alloc_node(token_cmp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 934 "../parser.y"
    { (yyval.n) = alloc_node(token_eq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      ;}
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 935 "../parser.y"
    { (yyval.n) = alloc_node(token_neq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 936 "../parser.y"
    { (yyval.n) = alloc_node(token_eqq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 937 "../parser.y"
    { (yyval.n) = alloc_node(token_match, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 938 "../parser.y"
    { (yyval.n) = alloc_node(token_nmatch, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 939 "../parser.y"
    { (yyval.n) = alloc_node(token_greater, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 303:

/* Line 1464 of yacc.c  */
#line 940 "../parser.y"
    { (yyval.n) = alloc_node(token_lesser, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 941 "../parser.y"
    { (yyval.n) = alloc_node(token_geq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 305:

/* Line 1464 of yacc.c  */
#line 942 "../parser.y"
    { (yyval.n) = alloc_node(token_leq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 306:

/* Line 1464 of yacc.c  */
#line 943 "../parser.y"
    { (yyval.n) = alloc_node(token_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      ;}
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 944 "../parser.y"
    { (yyval.n) = alloc_node(token_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 308:

/* Line 1464 of yacc.c  */
#line 945 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 309:

/* Line 1464 of yacc.c  */
#line 946 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 310:

/* Line 1464 of yacc.c  */
#line 947 "../parser.y"
    { (yyval.n) = alloc_node(token_dot2, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 948 "../parser.y"
    { (yyval.n) = alloc_node(token_dot3, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 312:

/* Line 1464 of yacc.c  */
#line 950 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_ternary, (yyvsp[(1) - (8)].n), (yyvsp[(4) - (8)].n), (yyvsp[(8) - (8)].n));
  ;}
    break;

  case 313:

/* Line 1464 of yacc.c  */
#line 953 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_not, (yyvsp[(3) - (3)].n), NULL);;}
    break;

  case 314:

/* Line 1464 of yacc.c  */
#line 954 "../parser.y"
    { (yyval.n) = alloc_node(token_neg, (yyvsp[(3) - (3)].n), NULL);   ;}
    break;

  case 315:

/* Line 1464 of yacc.c  */
#line 955 "../parser.y"
    { (yyval.n) = alloc_node(token_not, (yyvsp[(3) - (3)].n), NULL);   ;}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 956 "../parser.y"
    { (yyval.n) = alloc_node(token_unary_plus, (yyvsp[(3) - (3)].n), NULL);  ;}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 957 "../parser.y"
    { (yyval.n) = alloc_node(token_unary_minus, (yyvsp[(3) - (3)].n), NULL); ;}
    break;

  case 318:

/* Line 1464 of yacc.c  */
#line 958 "../parser.y"
    { (yyval.n) = alloc_node(token_defined, (yyvsp[(3) - (3)].n), NULL);     ;}
    break;

  case 319:

/* Line 1464 of yacc.c  */
#line 959 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 960 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n)   ;}
    break;

  case 321:

/* Line 1464 of yacc.c  */
#line 961 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;



/* Line 1464 of yacc.c  */
#line 4439 "../parser.c"
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
#line 964 "../parser.y"

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
  p->error = 0;
  p->expr_seen = 0;
  p->class_seen = 0;
  p->no_block = 0;
  p->dot_seen = 0;
  p->last_is_paren = 0;
  p->in_def = 0;
  p->errors = (char **) malloc (sizeof(char));
  p->error_index = 0;
  p->sp = 0;
  p->line = 1;
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
  char err[64];
  char buffer[64];
  va_list ap;

  va_start(ap, s);
  sprintf(err, "%s:%i: ", p->name, p->line);
  vsprintf(buffer, s, ap);
  strcat(err, buffer);
  *(p->errors + p->error_index) = strdup(err);
  p->error_index++;

  p->eof_reached = 1;
  p->error = 1;
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
    free(p.errors);
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
      result->errors = p.errors;
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
    free(p.errors);
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


