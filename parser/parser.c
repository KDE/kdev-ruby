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
  char * stack[2];
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
#line 151 "../parser.c"

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

/* Line 214 of yacc.c  */
#line 108 "../parser.y"
  struct node * n;  


/* Line 214 of yacc.c  */
#line 296 "../parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 308 "../parser.c"

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
#define YYFINAL  135
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2416

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  123
/* YYNRULES -- Number of rules.  */
#define YYNRULES  321
/* YYNRULES -- Number of states.  */
#define YYNSTATES  586

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
     223,   224,   231,   232,   240,   242,   244,   248,   250,   253,
     255,   257,   259,   261,   263,   265,   267,   269,   271,   273,
     275,   277,   279,   281,   287,   288,   291,   292,   295,   296,
     298,   300,   303,   308,   313,   314,   318,   319,   321,   323,
     325,   330,   334,   340,   344,   349,   353,   357,   360,   362,
     366,   368,   372,   375,   378,   383,   386,   391,   394,   401,
     406,   413,   418,   427,   434,   435,   439,   441,   445,   448,
     452,   454,   458,   460,   462,   464,   466,   468,   470,   471,
     473,   476,   478,   482,   483,   487,   493,   495,   497,   499,
     501,   504,   506,   508,   511,   514,   517,   520,   523,   526,
     529,   532,   535,   538,   541,   544,   545,   547,   550,   553,
     556,   559,   562,   565,   568,   571,   574,   578,   580,   583,
     584,   586,   588,   591,   593,   595,   597,   600,   601,   603,
     605,   607,   609,   611,   615,   618,   620,   624,   627,   629,
     630,   632,   634,   637,   641,   643,   646,   650,   652,   656,
     660,   664,   668,   672,   676,   680,   685,   690,   694,   698,
     702,   706,   709,   713,   715,   717,   719,   721,   723,   727,
     733,   735,   738,   742,   744,   748,   753,   757,   760,   763,
     766,   770,   774,   778,   782,   785,   790,   793,   795,   798,
     801,   804,   805,   807,   809,   811,   813,   817,   819,   821,
     823,   825,   827,   832,   837,   842,   847,   852,   857,   862,
     867,   872,   877,   882,   886,   890,   894,   899,   904,   909,
     914,   919,   924,   929,   934,   939,   944,   949,   954,   959,
     964,   969,   974,   983,   987,   991,   995,   999,  1003,  1007,
    1010,  1012
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     107,     0,    -1,    46,    -1,   108,    -1,   116,    -1,   121,
      -1,   207,    -1,   216,   144,    -1,   213,    -1,   108,    11,
     228,    -1,   108,    12,   228,    -1,   108,    18,   228,    -1,
     108,    19,   228,    -1,   228,    -1,   108,    -1,   109,   195,
     108,    -1,   130,    -1,    48,    -1,   134,    -1,   112,    -1,
      53,    -1,    37,    -1,    63,    -1,   111,    -1,    39,    -1,
      38,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    52,    -1,   112,    52,    -1,   110,
      -1,   208,    -1,   218,    -1,   220,    -1,   130,    -1,   218,
      -1,   220,    -1,    48,    -1,   134,    -1,   112,    -1,    53,
      -1,    37,    -1,    63,    -1,   208,    -1,   111,    -1,    21,
      -1,    23,    -1,    24,    -1,    22,    -1,     6,   119,    -1,
      33,   120,   120,    -1,   117,    -1,   118,    -1,    29,    -1,
      29,   228,    -1,    28,    -1,    28,   228,    -1,   120,    -1,
     120,   181,   119,    -1,    51,    -1,    50,    -1,   134,    -1,
     168,   228,   166,   190,   136,    10,    -1,   170,   228,   166,
     190,   136,    10,    -1,   171,   228,   167,   190,    10,    -1,
     172,   228,   167,   190,    10,    -1,   173,   228,   196,   164,
      10,    -1,   173,   164,    10,    -1,    35,    79,   190,    80,
      -1,    36,    79,   190,    80,    -1,   175,   204,   179,   227,
     167,   190,    10,    -1,     7,   142,    10,    -1,    -1,   176,
     127,   122,   128,   142,    10,    -1,    -1,   177,   129,   123,
     142,    10,    -1,    -1,   178,   129,   143,   124,   142,    10,
      -1,    -1,   178,    69,   192,   130,   125,   142,    10,    -1,
      50,    -1,   131,    -1,   131,   197,   126,    -1,   126,    -1,
     151,   198,    -1,   198,    -1,    92,    -1,    51,    -1,   131,
      -1,    47,    -1,    58,    -1,    57,    -1,    92,    -1,    51,
      -1,    54,    -1,    92,    -1,    49,    -1,    91,    -1,   137,
      -1,   169,   228,   166,   190,   136,    -1,    -1,    15,   190,
      -1,    -1,     9,   190,    -1,    -1,   140,    -1,   141,    -1,
     140,   141,    -1,     8,   160,   166,   190,    -1,   190,   139,
     137,   138,    -1,    -1,    83,   192,   129,    -1,    -1,   145,
      -1,   146,    -1,   147,    -1,   186,   148,   191,    80,    -1,
     186,   191,    80,    -1,    27,   180,   148,   190,    10,    -1,
      27,   190,    10,    -1,    77,   152,   149,    77,    -1,    77,
     149,    77,    -1,    77,   152,    77,    -1,    73,   150,    -1,
     131,    -1,   150,   181,   131,    -1,   152,    -1,   182,   152,
     183,    -1,    76,   158,    -1,   154,   153,    -1,   155,   181,
     154,   153,    -1,   155,   153,    -1,   157,   181,   154,   153,
      -1,   157,   153,    -1,   157,   181,   155,   181,   154,   153,
      -1,   157,   181,   155,   153,    -1,   154,   181,   157,   181,
     154,   153,    -1,   154,   181,   157,   153,    -1,   154,   181,
     157,   181,   155,   181,   154,   153,    -1,   154,   181,   157,
     181,   155,   153,    -1,    -1,   181,    76,   158,    -1,   158,
      -1,   154,   181,   158,    -1,    88,   158,    -1,   158,    93,
     113,    -1,   156,    -1,   157,   181,   156,    -1,    51,    -1,
     159,    -1,    92,    -1,    57,    -1,    58,    -1,    47,    -1,
      -1,   161,    -1,   162,   163,    -1,   228,    -1,   162,   181,
     228,    -1,    -1,    71,   192,   130,    -1,   174,   228,   166,
     190,   165,    -1,   137,    -1,   164,    -1,   194,    -1,    13,
      -1,   194,    13,    -1,   194,    -1,    26,    -1,    11,   192,
      -1,    14,   192,    -1,    12,   192,    -1,    18,   192,    -1,
      19,   192,    -1,    16,   192,    -1,    17,   192,    -1,    20,
     192,    -1,     5,   192,    -1,     4,   192,    -1,     3,   192,
      -1,    25,   192,    -1,    -1,    46,    -1,    64,   192,    -1,
      81,   192,    -1,   192,    82,    -1,    59,   192,    -1,   192,
      60,    -1,    79,   192,    -1,   192,    80,    -1,    93,   192,
      -1,    94,   192,    -1,   196,   109,   196,    -1,   196,    -1,
     109,   196,    -1,    -1,   193,    -1,    46,    -1,   193,    46,
      -1,    73,    -1,    46,    -1,   194,    -1,   195,   194,    -1,
      -1,   195,    -1,    61,    -1,   103,    -1,    46,    -1,    73,
      -1,   204,   181,   200,    -1,   204,   181,    -1,   228,    -1,
     182,   199,   183,    -1,    88,   130,    -1,    88,    -1,    -1,
     202,    -1,   203,    -1,   202,   203,    -1,   184,   209,   185,
      -1,   228,    -1,   204,   181,    -1,   204,   181,   200,    -1,
     228,    -1,   205,   181,   228,    -1,   130,   188,   113,    -1,
     130,   189,   113,    -1,   130,   188,   213,    -1,   130,   189,
     213,    -1,   204,   188,   205,    -1,   204,   189,   205,    -1,
     204,   188,   216,   144,    -1,   204,   189,   216,   144,    -1,
     204,   188,   213,    -1,   204,   189,   213,    -1,   204,   188,
     121,    -1,   204,   189,   121,    -1,   184,    60,    -1,   184,
     210,   185,    -1,    55,    -1,   228,    -1,   206,    -1,   213,
      -1,   209,    -1,   210,   181,   209,    -1,   212,   192,   209,
     185,   201,    -1,    56,    -1,   186,    80,    -1,   186,   214,
     187,    -1,   215,    -1,   214,   181,   215,    -1,   228,    71,
     192,   228,    -1,   135,   192,   228,    -1,   126,   224,    -1,
     220,   224,    -1,   217,   223,    -1,   133,   103,   126,    -1,
     132,   223,   183,    -1,   219,   223,   183,    -1,   133,   103,
     132,    -1,   110,   221,    -1,   182,   228,   183,   221,    -1,
     218,   221,    -1,   222,    -1,   221,   222,    -1,    61,   126,
      -1,    61,   218,    -1,    -1,   224,    -1,   216,    -1,   225,
      -1,   228,    -1,   225,   181,   226,    -1,   228,    -1,   213,
      -1,   214,    -1,   228,    -1,   213,    -1,   228,    86,   192,
     228,    -1,   228,    87,   192,   228,    -1,   228,    88,   192,
     228,    -1,   228,    89,   192,   228,    -1,   228,    90,   192,
     228,    -1,   228,    66,   192,   228,    -1,   228,    76,   192,
     228,    -1,   228,    77,   192,   228,    -1,   228,    78,   192,
     228,    -1,   228,    69,   192,   228,    -1,   228,    70,   192,
     228,    -1,   182,   228,   183,    -1,   182,   207,   183,    -1,
     182,   216,   183,    -1,   228,    95,   192,   228,    -1,   228,
      96,   192,   228,    -1,   228,    98,   192,   228,    -1,   228,
      97,   192,   228,    -1,   228,    99,   192,   228,    -1,   228,
     100,   192,   228,    -1,   228,    84,   192,   228,    -1,   228,
      83,   192,   228,    -1,   228,   101,   192,   228,    -1,   228,
     102,   192,   228,    -1,   228,    74,   192,   228,    -1,   228,
      75,   192,   228,    -1,   228,    31,   192,   228,    -1,   228,
      30,   192,   228,    -1,   228,   105,   192,   228,    -1,   228,
     104,   192,   228,    -1,   228,    72,   192,   228,   192,    65,
     192,   228,    -1,    32,   192,   228,    -1,    62,   192,   228,
      -1,    85,   192,   228,    -1,    68,   192,   228,    -1,    67,
     192,   228,    -1,    34,   192,   228,    -1,   114,   144,    -1,
     115,    -1,   211,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   162,   162,   163,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   186,   187,   190,   191,   192,   193,
     194,   195,   196,   197,   200,   201,   202,   203,   204,   205,
     206,   207,   210,   211,   214,   215,   216,   217,   220,   221,
     222,   225,   226,   227,   228,   229,   230,   231,   232,   235,
     236,   237,   238,   239,   240,   241,   242,   245,   246,   249,
     250,   253,   254,   257,   258,   259,   262,   269,   276,   282,
     288,   294,   298,   302,   306,   310,   316,   315,   325,   324,
     335,   334,   345,   344,   356,   357,   360,   361,   364,   365,
     368,   369,   375,   376,   377,   378,   379,   382,   385,   388,
     391,   394,   397,   398,   406,   407,   410,   411,   414,   415,
     418,   419,   422,   428,   434,   435,   438,   439,   442,   443,
     446,   450,   456,   460,   466,   470,   474,   480,   483,   484,
     490,   491,   494,   495,   496,   500,   501,   505,   506,   510,
     514,   518,   522,   527,   533,   534,   537,   538,   541,   544,
     547,   548,   551,   552,   555,   560,   565,   570,   577,   578,
     581,   587,   588,   591,   592,   595,   601,   602,   605,   606,
     607,   610,   611,   614,   617,   620,   623,   626,   629,   632,
     635,   638,   641,   644,   647,   650,   651,   654,   657,   660,
     663,   666,   669,   672,   675,   678,   681,   682,   685,   688,
     689,   692,   693,   696,   697,   700,   701,   704,   705,   708,
     709,   712,   713,   716,   717,   720,   730,   731,   732,   735,
     736,   739,   740,   743,   746,   747,   748,   751,   752,   755,
     756,   757,   758,   761,   762,   763,   768,   773,   774,   775,
     776,   779,   780,   781,   785,   786,   787,   790,   791,   794,
     806,   809,   810,   813,   814,   817,   818,   821,   825,   835,
     838,   844,   848,   854,   857,   862,   867,   873,   874,   877,
     882,   889,   890,   893,   894,   898,   899,   903,   904,   905,
     909,   910,   913,   914,   915,   916,   917,   918,   919,   920,
     921,   922,   923,   924,   925,   926,   927,   928,   929,   930,
     931,   932,   933,   934,   935,   936,   937,   938,   939,   940,
     941,   942,   943,   947,   948,   949,   950,   951,   952,   953,
     954,   955
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
  "cmpd_stmt", "$@1", "$@2", "$@3", "$@4", "fname", "single_name",
  "function_args", "module_name", "variable", "base", "mcall", "const",
  "symbol", "key", "if_tail", "opt_else", "opt_ensure", "opt_rescue",
  "rescue_list", "rescue_item", "bodystmt", "superclass",
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
     124,   121,   125,   121,   126,   126,   127,   127,   128,   128,
     129,   129,   130,   130,   130,   130,   130,   131,   132,   133,
     134,   135,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   141,   142,   143,   143,   144,   144,   145,   145,
     146,   146,   147,   147,   148,   148,   148,   149,   150,   150,
     151,   151,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   153,   153,   154,   154,   155,   156,
     157,   157,   158,   158,   159,   159,   159,   159,   160,   160,
     161,   162,   162,   163,   163,   164,   165,   165,   166,   166,
     166,   167,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   190,   191,   192,
     192,   193,   193,   194,   194,   195,   195,   196,   196,   197,
     197,   198,   198,   199,   199,   200,   200,   200,   200,   201,
     201,   202,   202,   203,   204,   204,   204,   205,   205,   206,
     206,   206,   206,   207,   207,   207,   207,   207,   207,   207,
     207,   208,   208,   208,   209,   209,   209,   210,   210,   211,
     212,   213,   213,   214,   214,   215,   215,   216,   216,   216,
     217,   218,   218,   219,   220,   220,   220,   221,   221,   222,
     222,   223,   223,   224,   224,   225,   225,   226,   226,   226,
     227,   227,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228
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
       0,     6,     0,     7,     1,     1,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     0,     2,     0,     2,     0,     1,
       1,     2,     4,     4,     0,     3,     0,     1,     1,     1,
       4,     3,     5,     3,     4,     3,     3,     2,     1,     3,
       1,     3,     2,     2,     4,     2,     4,     2,     6,     4,
       6,     4,     8,     6,     0,     3,     1,     3,     2,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     0,     1,
       2,     1,     3,     0,     3,     5,     1,     1,     1,     1,
       2,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     0,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     1,     2,     0,
       1,     1,     2,     1,     1,     1,     2,     0,     1,     1,
       1,     1,     1,     3,     2,     1,     3,     2,     1,     0,
       1,     1,     2,     3,     1,     2,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     4,     4,     3,     3,     3,
       3,     2,     3,     1,     1,     1,     1,     1,     3,     5,
       1,     2,     3,     1,     3,     4,     3,     2,     2,     2,
       3,     3,     3,     3,     2,     4,     2,     1,     2,     2,
       2,     0,     1,     1,     1,     1,     3,     1,     1,     1,
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
       0,   199,   199,   199,     0,   207,   199,   199,   199,   199,
     199,   199,    49,    52,    50,    51,    59,    57,   199,     0,
     199,     0,     0,    45,    25,    24,    26,    27,    28,    29,
      30,    31,     2,    93,    41,   100,    84,    97,    32,    44,
      98,   243,   250,    95,    94,   199,   199,    46,   199,   199,
     199,   199,   199,    96,     0,     3,     0,    48,    43,   116,
     320,     4,    55,    56,     5,     0,    38,    92,   271,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,    47,   321,   199,     8,   116,
     271,    39,   271,    40,    13,   201,   183,   200,   182,   181,
      64,    63,    53,    61,    65,   204,   203,     0,   108,   205,
     208,   197,   173,   175,   178,   176,   177,   180,    92,     0,
      40,    60,    58,     0,     0,     0,   207,   207,   190,     0,
       0,     0,   192,   188,     0,     1,     0,     0,     0,     0,
       0,   264,   267,    33,   207,   319,   117,   118,   119,     0,
     273,   257,   274,   275,   199,   272,     0,     0,     0,     0,
       0,   199,     0,     0,   207,     0,   224,    87,    76,    85,
      91,    90,    78,   199,   114,   199,   199,   224,   241,    38,
     245,   247,   199,   246,   244,   251,   101,   199,   199,   253,
       0,   199,   199,   199,   225,     0,     0,     0,     7,   259,
     266,   199,   258,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   202,     0,    75,   158,   104,   109,   110,   206,    14,
     207,     0,   313,    54,   318,     0,     0,   314,   317,   316,
     315,     9,    10,    11,    12,    99,   269,    85,   270,   268,
     204,     0,     0,     0,   207,     0,     0,     0,   261,     0,
     260,   263,   169,   207,   168,   207,   172,   207,   171,   207,
     179,    71,     0,     0,   199,     0,     0,   209,   210,     0,
     207,     0,   199,    80,   294,   295,   293,     0,     0,     0,
     242,     0,     0,     0,   252,     0,   199,   187,   194,   195,
     218,     0,   226,   215,   239,   233,   237,   116,   227,   240,
     234,   238,   116,   199,   262,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    62,     0,   159,   163,   161,   207,   106,
     111,   208,   196,    72,    73,   207,   123,   157,   152,   155,
     156,     0,     0,     0,   154,     0,     0,   144,   144,   150,
     144,   146,   153,   198,     0,   121,   278,   279,   276,   277,
     189,   104,   170,   104,     0,     0,   207,     0,   184,   281,
       0,   280,   211,   212,   207,     0,   130,     0,    89,    86,
       0,    96,    82,     0,   207,   265,    21,    17,    20,    22,
      34,    23,    19,   229,    16,    18,     0,    35,   231,    36,
      37,   230,   232,   248,   191,   256,   254,   193,     0,   217,
     199,     0,     0,   235,   236,   219,   309,   308,   287,   291,
     292,   199,   306,   307,   288,   289,   290,   303,   302,   282,
     283,   284,   285,   286,   296,   297,   299,   298,   300,   301,
     304,   305,   311,   310,   207,   199,   160,     0,   105,   207,
     113,    15,     0,   128,   127,   132,   148,   125,   126,     0,
     133,     0,   135,     0,   137,     0,     0,   120,   199,     0,
     102,     0,     0,    68,    69,   104,    70,   207,     0,    88,
     199,    79,   207,   115,     0,   199,   255,   216,   225,   228,
       0,   249,   220,   221,     0,   112,     0,   162,   107,   122,
       0,   124,     0,   144,   147,   144,   146,   144,   144,   151,
     149,   174,    66,     0,    67,   166,   167,   165,     0,    77,
     131,     0,    81,     0,   226,   199,   222,   199,   164,   129,
     145,   141,     0,   134,     0,   136,   139,     0,   207,    74,
      83,   223,     0,   144,   144,   147,   144,   104,   312,   140,
     143,     0,   138,   103,   144,   142
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    54,   239,   264,    56,    57,    58,   423,    59,    60,
      61,    62,    63,   102,   103,    64,   286,   290,   414,   512,
      65,   168,   404,   172,    66,   118,    68,   119,    70,   187,
     499,   500,   480,   235,   236,   237,   107,   293,   145,   146,
     147,   148,   265,   375,   484,   405,   376,   490,   377,   378,
     379,   380,   381,   382,   354,   355,   356,   476,   162,   547,
     273,   277,    71,   501,    72,    73,    74,    75,   163,    76,
      77,    78,    79,   285,   261,   564,    80,   268,    81,   300,
      82,   304,   195,   196,   108,   266,   269,    97,   109,   110,
     111,   289,   408,   440,   312,   521,   522,   523,    83,   315,
     180,    84,    85,   181,   182,    86,    87,    88,   188,   189,
      89,    90,    91,    92,   120,   141,   142,   154,   155,   152,
     388,   400,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -465
static const yytype_int16 yypact[] =
{
     821,     2,     2,     2,   212,    80,     2,     2,     2,     2,
       2,     2,  -465,  -465,  -465,  -465,  2040,  2040,     2,   212,
       2,    26,    29,    63,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,    70,  -465,  -465,  -465,  -465,    93,
    -465,  -465,  -465,  -465,  -465,     2,     2,   111,     2,     2,
       2,     2,     2,   -40,   177,   208,   132,   142,    67,     8,
    -465,  -465,  -465,  -465,  -465,  1759,   153,  1815,  1759,   154,
     170,  2040,  2040,  2040,  2040,  1173,  2040,    43,   -13,     0,
    1759,  1591,  1647,    18,  -465,  -465,  -465,     2,  -465,     8,
    1759,   132,  1759,  1759,  1203,  -465,  -465,   218,  -465,  -465,
    -465,  -465,  -465,   201,  -465,  -465,  -465,   257,   263,  -465,
      80,   994,  -465,  -465,  -465,  -465,  -465,  -465,  -465,   171,
    -465,  1460,  1460,  2040,   212,  2040,    80,    80,  -465,  2040,
    2040,  2040,  -465,  -465,  2040,  -465,  2040,  2040,  2040,  2040,
     140,   132,  -465,  -465,    83,  -465,  -465,  -465,  -465,   911,
    -465,  -465,   201,  1460,     2,  -465,    -8,   622,   622,  1099,
    1099,     2,   269,  2040,  1264,    14,  1460,  -465,  -465,   -17,
    -465,  -465,  -465,     2,   197,     2,     2,  1325,  -465,    76,
    -465,  -465,   118,  -465,  1460,  -465,  -465,     2,   118,  -465,
    1362,     2,     2,     2,  1871,  1065,  1065,  1928,  -465,  -465,
     132,     2,  -465,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,  -465,   212,  -465,  2040,   270,   263,  -465,  -465,   208,
      80,   230,  2141,  -465,  2141,   209,   221,  -465,   222,  -465,
    -465,  1460,  1460,  1460,  1460,  -465,  -465,  -465,  -465,  -465,
     225,   226,   295,   415,    80,   994,   224,  1703,  -465,   266,
    -465,  -465,  -465,    80,   326,    80,  -465,    80,  -465,    80,
    -465,  -465,   622,   290,     2,  1928,   590,  -465,  -465,    43,
      80,    44,     2,  -465,  -465,  -465,   132,  2096,  2096,  1928,
    -465,   248,  2040,  1984,  -465,   273,     2,  -465,  -465,  -465,
      44,  1759,  -465,  1460,  -465,   201,  -465,     8,  1460,  -465,
     201,  -465,     8,     2,  -465,  2040,  2040,  2040,  2040,  2040,
    2040,  2040,  2040,  2040,  2040,  2040,  2040,  2040,  2040,  2040,
    2040,  2040,  2040,  2040,  2040,  2040,  2040,  2040,  2040,  2040,
    2040,  2040,  2040,  -465,    27,  -465,   124,  1460,    80,   341,
    -465,   725,  -465,  -465,  -465,    80,  -465,  -465,  -465,  -465,
    -465,   303,   294,   294,  -465,   281,   128,   201,   201,  -465,
     201,   275,  -465,  -465,   279,  -465,  -465,   201,  -465,  1362,
    -465,   183,  -465,   183,   359,   363,    80,   366,  -465,  -465,
      24,  1460,  -465,  -465,    80,   129,  -465,   108,  -465,  -465,
     367,  -465,  -465,   -13,    80,   132,  -465,  -465,  -465,  -465,
     132,  -465,   327,  -465,  -465,  -465,  2040,  -465,  -465,   132,
    -465,  -465,  -465,  -465,  -465,  1460,  -465,  -465,  2040,  -465,
       2,    18,  2040,  -465,  -465,   319,  2141,  2141,   222,   394,
     394,  1423,  2215,  2252,  1072,   733,   733,  2326,  2326,   120,
     120,   222,   222,   222,  2289,  2289,  2289,  2289,  2289,  2289,
    2326,  2326,  2178,  2178,    80,     2,  -465,  2040,  -465,    80,
    -465,   208,   371,  -465,   201,  -465,  -465,  -465,  -465,   305,
    -465,   459,  -465,   459,  -465,   461,  2142,  -465,     2,   373,
    -465,  2040,   375,  -465,  -465,   123,  -465,    80,   377,  -465,
       2,  -465,    80,  -465,   380,  1423,  1460,  -465,  1534,  1460,
    1928,  -465,   319,  -465,   329,  -465,    44,  1460,  -465,  -465,
     303,  -465,   294,   201,   275,   201,  -465,   201,   201,  -465,
    -465,  -465,  -465,   622,  -465,  -465,  -465,  -465,   381,  -465,
    -465,   385,  -465,   132,     7,     2,  -465,     2,  -465,  -465,
    -465,  -465,   461,  -465,   459,  -465,  -465,   459,    80,  -465,
    -465,  -465,  2040,   201,   201,  -465,   201,   183,  2141,  -465,
    -465,   459,  -465,  -465,   201,  -465
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -465,  -465,     6,   286,  -236,  -230,  -226,  -285,  -465,  -465,
    -465,  -465,  -465,   166,    11,    28,  -465,  -465,  -465,  -465,
     -60,  -465,  -465,   -75,   -52,    81,  -131,   520,     1,  -465,
    -371,  -224,  -465,  -465,  -465,   165,  -262,  -465,   -73,  -465,
    -465,  -465,   146,    33,  -465,  -465,  -263,   -84,  -405,  -464,
    -463,   -80,    59,  -465,  -465,  -465,  -465,  -465,  -249,  -465,
    -155,  -148,  -465,  -465,  -465,  -465,  -465,  -465,  -465,  -465,
    -465,  -465,  -465,  -465,  -465,    60,  -147,  -168,  -418,  -302,
     -44,  -465,   233,   235,   -90,   158,   354,  -465,   133,  -134,
    -123,  -465,    19,  -465,   -99,  -465,  -465,   -97,   -57,   231,
    -465,   -56,  -214,  -183,  -465,  -465,  -465,   -63,   161,   126,
     328,  -465,  -130,  -465,   148,   -89,  -115,   125,    10,  -465,
    -465,  -465,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -225
static const yytype_int16 yytable[] =
{
     121,   122,   200,   275,   174,   104,    55,   294,   295,   296,
     258,   359,   279,   431,   323,   149,   198,   167,   183,   165,
     104,   445,   502,   406,   175,   271,   259,   520,   410,   179,
     124,   538,   539,   324,   397,   144,   245,   246,   170,   284,
     272,   283,    36,    37,   287,   149,    40,   311,    95,   153,
     276,   170,   153,  -213,   262,   157,   158,   159,   160,   164,
     166,   420,   420,   -99,   177,   184,   190,   421,   421,   173,
     105,   422,   422,   105,   153,   151,   153,   153,   191,   171,
     256,    67,   191,   427,   427,   259,   288,    50,   535,  -213,
     537,    33,   171,    36,    37,    37,   270,   106,   574,   539,
     106,    43,    44,   202,   520,   126,   361,   242,   127,   244,
     271,   192,   193,   247,   248,   249,   433,   362,   250,   143,
     251,   252,   253,   254,   -21,   104,   105,   396,   -19,   260,
     361,   -17,   316,   321,   183,   243,   411,   -16,   358,   407,
     161,   383,   508,   194,   510,   179,    67,   282,    93,    67,
     426,   426,   514,   106,   -20,   367,   106,   573,   169,   368,
    -185,    67,   576,   232,    95,   369,   370,   429,   429,   192,
     193,    67,   -22,    67,    67,   402,   584,   135,   313,   318,
     318,   184,   191,   391,   372,   393,   205,   394,   191,   395,
      36,    37,    67,   140,    40,   475,   373,   498,   358,   474,
     374,   371,   403,   -23,   386,   488,   583,   415,   218,   219,
     220,   540,   267,    93,   -16,   199,    93,   201,   357,   136,
     137,   257,   399,   314,   319,   194,   138,   139,    93,   409,
      67,   -18,   255,   104,   428,   432,   183,   257,    93,   412,
      93,    93,   299,   238,   443,   424,   424,   179,   303,   444,
     551,   389,   507,   571,   441,   175,   546,   156,   439,    93,
     420,    35,   100,   101,   231,   191,   421,   233,   478,   401,
     422,   234,   517,   149,   241,   482,    67,    67,   149,   281,
     292,   545,   427,   184,    40,   358,   435,   190,   205,   363,
     274,   274,   278,   278,   492,   177,   494,    93,   425,   425,
     259,   364,  -186,   263,   385,   366,   505,   161,   434,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   555,   513,   392,
     200,   367,   550,    93,    93,   368,    67,   553,   390,   426,
     479,   369,   370,   437,    37,    96,    98,    99,   487,   497,
     112,   113,   114,   115,   116,   117,   429,   481,   496,   503,
     257,   311,   123,   504,   125,   442,   506,   511,    45,   143,
     442,   529,   531,   542,   525,   544,   374,   549,   568,   528,
     552,   569,    67,   150,   557,   570,   150,   240,   353,   128,
     129,   360,   130,   131,   132,   133,   134,   365,   176,   489,
     515,   533,   297,    93,   298,   274,   477,   548,   150,   554,
     150,   150,   516,   384,   509,   556,   519,   320,   387,   436,
       0,   485,   486,     0,     0,     0,     0,   491,   493,     0,
     495,   197,    67,     0,   424,   430,   430,   303,     0,   561,
       0,   563,   483,   565,   566,     0,     0,   183,     0,    93,
     205,   527,   367,     0,   415,     0,   368,     0,   179,     0,
       0,     0,   369,   370,   558,     0,     0,     0,   577,     0,
     216,   217,   218,   219,   220,   543,     0,   274,   371,   579,
     580,   372,   582,     0,   238,     0,     0,   425,     0,     0,
     585,   518,   313,   373,   184,     0,   367,   374,   367,    93,
     368,     0,   368,     0,     0,   280,   369,   370,   369,   370,
      69,     0,     0,   317,   322,     0,     0,   291,     0,     0,
       0,     0,     0,   278,     0,   532,   301,   532,     0,     0,
       0,   302,   305,     0,   530,   307,   308,   309,     0,   373,
     534,   374,   536,   374,     0,     0,   578,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,    69,     0,     0,    69,     0,
       0,   560,     0,   562,     0,     0,     0,     0,   567,     0,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      69,   559,    69,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   575,     0,     0,   536,     0,     0,     0,
       0,    69,     0,     0,   581,   272,   402,   367,   398,   176,
     536,   368,     0,     0,   430,     0,   413,   369,   370,     0,
       0,     0,   203,   204,     0,     0,     0,     0,     0,     0,
     438,     0,     0,   403,     0,     0,   372,     0,   105,    69,
       0,    51,     0,     0,     0,     0,   274,   301,   373,     0,
       0,     0,   374,     0,     0,     0,     0,     0,   205,     0,
       0,   206,   207,     0,   208,   106,   209,   210,   211,   212,
     213,     0,     0,     0,     0,   214,   215,     0,   216,   217,
     218,   219,   220,     0,     0,    69,    69,   221,   222,   223,
     224,   225,   226,   227,   228,     0,   229,   230,     1,     2,
       3,     4,     5,     0,     0,     0,     6,     7,     0,     0,
       0,     8,     0,     9,    10,    11,    12,    13,    14,    15,
       0,     0,     0,    16,    17,     0,     0,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,   105,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    69,     0,    46,    47,     0,
       0,     0,    48,    49,     0,     0,     0,     0,   106,   205,
       0,     0,   206,   207,    50,   524,    51,     0,     0,   211,
      52,     0,     0,     0,     0,     0,     0,    53,     0,   216,
     217,   218,   219,   220,     1,     2,     3,     4,     5,   526,
       0,    69,     6,     7,     0,     0,     0,     8,     0,     9,
      10,    11,    12,    13,    14,    15,     0,     0,     0,    16,
      17,     0,   541,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    69,     0,    46,    47,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,    51,     0,     0,     0,    52,     0,     0,   301,
       0,   572,     0,    53,     1,     2,     3,     4,     5,     0,
       0,     0,     6,     7,     0,     0,     0,     8,     0,     9,
      10,    11,    12,    13,    14,    15,     0,     0,     0,    16,
      17,     0,     0,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,    46,    47,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,   263,     0,
      50,     0,    51,     0,     0,     0,    52,     1,     2,     3,
       4,     5,     0,    53,     0,     6,     7,     0,     0,     0,
       8,     0,     9,    10,    11,    12,    13,    14,    15,     0,
       0,     0,    16,    17,     0,     0,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,     0,    46,    47,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     1,     2,
       3,     0,     5,    50,     0,    51,     6,     7,     0,    52,
       0,     8,     0,     9,    10,    11,    53,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,     0,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,   276,     0,    46,    47,   203,
     204,     0,    48,    49,     0,     0,     0,     0,   205,     0,
       0,   206,   207,     0,    50,   105,    51,     0,     0,     0,
      52,     0,     0,     0,     0,     0,     0,    53,   216,   217,
     218,   219,   220,     0,     0,   205,     0,     0,   206,   207,
       0,   208,   106,   209,   210,   211,   212,   213,     0,     0,
       0,     0,   214,   215,     0,   216,   217,   218,   219,   220,
     161,     0,     0,     0,   221,   222,   223,   224,   225,   226,
     227,   228,     0,   229,   230,    18,     0,    20,     0,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      33,    34,    35,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,   203,   204,    46,    47,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,     0,     0,     0,    52,     0,
       0,     0,     0,     0,     0,    53,     0,  -224,     0,   205,
       0,     0,   206,   207,     0,   208,     0,   209,   210,   211,
     212,   213,     0,     0,     0,     0,   214,   215,     0,   216,
     217,   218,   219,   220,   203,   204,  -224,  -224,   221,   222,
     223,   224,   225,   226,   227,   228,     0,   229,   230,     0,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     205,     0,     0,   206,   207,     0,   208,   106,   209,   210,
     211,   212,   213,     0,     0,     0,     0,   214,   215,     0,
     216,   217,   218,   219,   220,   203,   204,     0,     0,   221,
     222,   223,   224,   225,   226,   227,   228,     0,   229,   230,
       0,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   205,   203,   204,   206,   207,     0,   208,     0,   209,
     210,   211,   212,   213,     0,     0,     0,  -199,   214,   215,
       0,   216,   217,   218,   219,   220,     0,     0,     0,     0,
     221,   222,   223,   224,   225,   226,   227,   228,   205,   229,
     230,   206,   207,   306,   208,     0,   209,   210,   211,   212,
     213,     0,     0,     0,     0,   214,   215,     0,   216,   217,
     218,   219,   220,   203,   204,     0,     0,   221,   222,   223,
     224,   225,   226,   227,   228,     0,   229,   230,     0,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
     203,   204,   206,   207,     0,   208,     0,   209,   210,   211,
     212,   213,     0,     0,     0,     0,   214,   215,     0,   216,
     217,   218,   219,   220,     0,     0,     0,     0,   221,   222,
     223,   224,   225,   226,   227,   228,   205,   229,   230,   206,
     207,     0,   208,     0,   209,   210,   211,   212,   213,     0,
       0,     0,     0,   214,   215,     0,   216,   217,   218,   219,
     220,     0,     0,     0,     0,   221,   222,   223,   224,   225,
     226,   227,   228,     0,   229,   230,    18,     0,    20,     0,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
    -214,    33,    34,    35,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,     0,    46,    47,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,  -214,     0,     0,    52,
       0,     0,   310,    18,     0,    20,    53,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,    33,    34,
      35,     0,    37,    38,    39,    40,    41,    42,    43,    44,
      45,   178,     0,    46,    47,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,    51,     0,     0,     0,    52,     0,     0,    18,
       0,    20,     0,    53,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,    33,    34,    35,     0,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,    46,
      47,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   185,    51,     0,
       0,     0,    52,     0,     0,    18,     0,    20,   186,    53,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      33,    34,    35,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,    46,    47,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,    51,     0,     0,     0,    52,     0,
       0,    18,     0,    20,   186,    53,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,    46,    47,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,    52,     0,     0,   -85,     0,   -85,
       0,    53,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,     0,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,     0,     0,   -85,   -85,     0,
       0,     0,   -85,   -85,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -85,     0,     0,     0,
     -85,     0,     0,    18,     0,    20,     0,   -85,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,    33,    34,
      35,     0,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,    46,    47,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,     0,     0,     0,    52,     0,     0,   310,
      18,     0,    20,    53,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    33,    34,    35,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     0,     0,
      46,    47,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,    51,
       0,     0,     0,    52,     0,     0,    18,     0,    20,     0,
      53,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    33,    34,    35,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,     0,    46,    47,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,    52,
       0,     0,    18,     0,    20,   186,    53,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    33,    34,    35,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,    47,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     0,     0,    52,     0,     0,     0,     0,
       0,     0,    53,   416,    24,    25,    26,    27,    28,    29,
      30,    31,     0,    33,   417,    35,     0,    37,    38,   418,
      40,    41,     0,    43,    44,    45,     0,     0,     0,   419,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,    51,     0,   416,
      24,    25,    26,    27,    28,    29,    30,    31,    53,    33,
     417,    35,     0,    37,    38,   418,    40,    41,     0,    43,
      44,    45,     0,     0,     0,   419,     0,   205,     0,     0,
     206,   207,     0,   208,     0,   209,   210,   211,   212,   213,
       0,     0,     0,    51,   214,   215,     0,   216,   217,   218,
     219,   220,     0,     0,    53,     0,   221,   222,   223,   224,
     225,   226,   227,   228,   205,   229,   230,   206,   207,     0,
       0,     0,   209,   210,   211,   212,   213,     0,     0,     0,
       0,   214,   215,     0,   216,   217,   218,   219,   220,     0,
       0,     0,     0,   221,   222,   223,   224,   225,   226,   227,
     228,   205,  -225,  -225,   206,   207,     0,     0,     0,     0,
     210,   211,   212,   213,     0,     0,     0,     0,   214,   215,
       0,   216,   217,   218,   219,   220,     0,     0,     0,     0,
     221,   222,   223,   224,   225,   226,   227,   228,   205,     0,
       0,   206,   207,     0,     0,     0,     0,     0,   211,   212,
     213,     0,     0,     0,     0,   214,   215,     0,   216,   217,
     218,   219,   220,     0,     0,     0,     0,   221,   222,   223,
     224,   225,   226,   227,   228,   205,     0,     0,   206,   207,
       0,     0,     0,     0,     0,   211,   212,   213,     0,     0,
       0,     0,   214,   215,     0,   216,   217,   218,   219,   220,
       0,     0,     0,     0,  -225,  -225,  -225,  -225,  -225,  -225,
     227,   228,   205,     0,     0,   206,   207,     0,     0,     0,
       0,     0,   211,   212,   213,     0,     0,     0,     0,     0,
       0,     0,   216,   217,   218,   219,   220
};

static const yytype_int16 yycheck[] =
{
      16,    17,    91,   158,    79,     4,     0,   175,   176,   177,
     140,   235,   160,   298,   197,    59,    89,    77,    81,    76,
      19,   323,   393,   286,    80,   156,   141,   445,   290,    81,
      19,   495,   495,   201,   283,    27,   126,   127,    51,    25,
      13,   164,    50,    51,    61,    89,    54,   194,    46,    65,
      26,    51,    68,    46,   144,    71,    72,    73,    74,    75,
      76,   297,   298,   103,    80,    81,    82,   297,   298,    69,
      46,   297,   298,    46,    90,    65,    92,    93,    64,    92,
     140,     0,    64,   297,   298,   200,   103,    79,   493,    82,
     495,    47,    92,    50,    51,    51,   156,    73,   562,   562,
      73,    57,    58,    93,   522,    79,   240,   123,    79,   125,
     241,    93,    94,   129,   130,   131,   299,   240,   134,    52,
     136,   137,   138,   139,    61,   124,    46,   282,    61,    46,
     264,    61,   195,   196,   197,   124,    92,    61,    15,   286,
      17,   264,   404,    83,   407,   197,    65,   163,     0,    68,
     297,   298,   414,    73,    61,    47,    73,   562,    77,    51,
      77,    80,   567,   103,    46,    57,    58,   297,   298,    93,
      94,    90,    61,    92,    93,    46,   581,     0,   194,   195,
     196,   197,    64,   273,    76,   275,    66,   277,    64,   279,
      50,    51,   111,    61,    54,    71,    88,    14,    15,   354,
      92,    73,    73,    61,   267,    77,   577,   296,    88,    89,
      90,   496,   152,    65,    61,    90,    68,    92,   234,    11,
      12,   140,   285,   195,   196,   165,    18,    19,    80,   289,
     149,    61,    92,   232,   297,   298,   299,   156,    90,   291,
      92,    93,   182,   110,   317,   297,   298,   299,   188,   322,
     512,   267,   400,   555,   311,   311,   505,   103,   310,   111,
     496,    49,    50,    51,    46,    64,   496,    10,   358,   285,
     496,     8,   440,   317,   103,   365,   195,   196,   322,    10,
      83,   505,   496,   299,    54,    15,   302,   303,    66,    80,
     157,   158,   159,   160,   378,   311,   380,   149,   297,   298,
     415,    80,    77,    77,    80,    10,   396,    17,    60,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   520,   413,    13,
     429,    47,   510,   195,   196,    51,   265,   515,    82,   496,
       9,    57,    58,    80,    51,     1,     2,     3,    77,    80,
       6,     7,     8,     9,    10,    11,   496,   361,    93,    10,
     289,   518,    18,    10,    20,   315,    10,    10,    59,    52,
     320,    10,    77,    10,   474,    10,    92,    10,   543,   479,
      10,    10,   311,    65,    65,    10,    68,   111,   232,    45,
      46,   236,    48,    49,    50,    51,    52,   261,    80,   376,
     426,   491,   179,   265,   179,   282,   356,   507,    90,   518,
      92,    93,   438,   265,   405,   522,   442,   196,   267,   303,
      -1,   372,   373,    -1,    -1,    -1,    -1,   377,   378,    -1,
     380,    87,   361,    -1,   496,   297,   298,   387,    -1,   533,
      -1,   535,   371,   537,   538,    -1,    -1,   520,    -1,   311,
      66,   477,    47,    -1,   553,    -1,    51,    -1,   520,    -1,
      -1,    -1,    57,    58,   526,    -1,    -1,    -1,   568,    -1,
      86,    87,    88,    89,    90,   501,    -1,   354,    73,   573,
     574,    76,   576,    -1,   361,    -1,    -1,   496,    -1,    -1,
     584,   441,   518,    88,   520,    -1,    47,    92,    47,   361,
      51,    -1,    51,    -1,    -1,   161,    57,    58,    57,    58,
       0,    -1,    -1,   195,   196,    -1,    -1,   173,    -1,    -1,
      -1,    -1,    -1,   400,    -1,    76,   182,    76,    -1,    -1,
      -1,   187,   188,    -1,   484,   191,   192,   193,    -1,    88,
     491,    92,   493,    92,    -1,    -1,   572,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,    65,    -1,    -1,    68,    -1,
      -1,   532,    -1,   533,    -1,    -1,    -1,    -1,   538,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,   530,    92,    93,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   564,    -1,    -1,   567,    -1,    -1,    -1,
      -1,   111,    -1,    -1,   574,    13,    46,    47,   284,   311,
     581,    51,    -1,    -1,   496,    -1,   292,    57,    58,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
     306,    -1,    -1,    73,    -1,    -1,    76,    -1,    46,   149,
      -1,    81,    -1,    -1,    -1,    -1,   543,   323,    88,    -1,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    69,    70,    -1,    72,    73,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,    87,
      88,    89,    90,    -1,    -1,   195,   196,    95,    96,    97,
      98,    99,   100,   101,   102,    -1,   104,   105,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    28,    29,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,   265,    -1,    62,    63,    -1,
      -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    73,    66,
      -1,    -1,    69,    70,    79,   451,    81,    -1,    -1,    76,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,    86,
      87,    88,    89,    90,     3,     4,     5,     6,     7,   475,
      -1,   311,    11,    12,    -1,    -1,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    28,
      29,    -1,   498,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,   361,    -1,    62,    63,    -1,    -1,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,   555,
      -1,   557,    -1,    92,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    28,
      29,    -1,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      79,    -1,    81,    -1,    -1,    -1,    85,     3,     4,     5,
       6,     7,    -1,    92,    -1,    11,    12,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    28,    29,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    79,    -1,    81,    11,    12,    -1,    85,
      -1,    16,    -1,    18,    19,    20,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    26,    -1,    62,    63,    30,
      31,    -1,    67,    68,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    69,    70,    -1,    79,    46,    81,    -1,    -1,    -1,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    92,    86,    87,
      88,    89,    90,    -1,    -1,    66,    -1,    -1,    69,    70,
      -1,    72,    73,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    83,    84,    -1,    86,    87,    88,    89,    90,
      17,    -1,    -1,    -1,    95,    96,    97,    98,    99,   100,
     101,   102,    -1,   104,   105,    32,    -1,    34,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    30,    31,    62,    63,    -1,    -1,    -1,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    -1,    64,    -1,    66,
      -1,    -1,    69,    70,    -1,    72,    -1,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,
      87,    88,    89,    90,    30,    31,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,    -1,   104,   105,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    69,    70,    -1,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    -1,    83,    84,    -1,
      86,    87,    88,    89,    90,    30,    31,    -1,    -1,    95,
      96,    97,    98,    99,   100,   101,   102,    -1,   104,   105,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    30,    31,    69,    70,    -1,    72,    -1,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    82,    83,    84,
      -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,    -1,
      95,    96,    97,    98,    99,   100,   101,   102,    66,   104,
     105,    69,    70,    71,    72,    -1,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,    87,
      88,    89,    90,    30,    31,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,    -1,   104,   105,    -1,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      30,    31,    69,    70,    -1,    72,    -1,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,
      87,    88,    89,    90,    -1,    -1,    -1,    -1,    95,    96,
      97,    98,    99,   100,   101,   102,    66,   104,   105,    69,
      70,    -1,    72,    -1,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    -1,    83,    84,    -1,    86,    87,    88,    89,
      90,    -1,    -1,    -1,    -1,    95,    96,    97,    98,    99,
     100,   101,   102,    -1,   104,   105,    32,    -1,    34,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    85,
      -1,    -1,    88,    32,    -1,    34,    92,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    -1,    -1,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    32,
      -1,    34,    -1,    92,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    -1,
      -1,    -1,    85,    -1,    -1,    32,    -1,    34,    91,    92,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    85,    -1,
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
      49,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    88,
      32,    -1,    34,    92,    -1,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    85,    -1,    -1,    32,    -1,    34,    -1,
      92,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    85,
      -1,    -1,    32,    -1,    34,    91,    92,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    92,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    48,    49,    -1,    51,    52,    53,
      54,    55,    -1,    57,    58,    59,    -1,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    92,    47,
      48,    49,    -1,    51,    52,    53,    54,    55,    -1,    57,
      58,    59,    -1,    -1,    -1,    63,    -1,    66,    -1,    -1,
      69,    70,    -1,    72,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    81,    83,    84,    -1,    86,    87,    88,
      89,    90,    -1,    -1,    92,    -1,    95,    96,    97,    98,
      99,   100,   101,   102,    66,   104,   105,    69,    70,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    83,    84,    -1,    86,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,    66,   104,   105,    69,    70,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    83,    84,
      -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,    -1,
      95,    96,    97,    98,    99,   100,   101,   102,    66,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,    66,    -1,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    -1,    -1,
      -1,    -1,    83,    84,    -1,    86,    87,    88,    89,    90,
      -1,    -1,    -1,    -1,    95,    96,    97,    98,    99,   100,
     101,   102,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    90
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
     115,   116,   117,   118,   121,   126,   130,   131,   132,   133,
     134,   168,   170,   171,   172,   173,   175,   176,   177,   178,
     182,   184,   186,   204,   207,   208,   211,   212,   213,   216,
     217,   218,   219,   220,   228,    46,   192,   193,   192,   192,
      50,    51,   119,   120,   134,    46,    73,   142,   190,   194,
     195,   196,   192,   192,   192,   192,   192,   192,   131,   133,
     220,   228,   228,   192,   120,   192,    79,    79,   192,   192,
     192,   192,   192,   192,   192,     0,    11,    12,    18,    19,
      61,   221,   222,    52,    27,   144,   145,   146,   147,   186,
     216,   224,   225,   228,   223,   224,   103,   228,   228,   228,
     228,    17,   164,   174,   228,   204,   228,   126,   127,   131,
      51,    92,   129,    69,   129,   207,   216,   228,    60,   130,
     206,   209,   210,   213,   228,    80,    91,   135,   214,   215,
     228,    64,    93,    94,   181,   188,   189,   192,   144,   223,
     221,   223,   224,    30,    31,    66,    69,    70,    72,    74,
      75,    76,    77,    78,    83,    84,    86,    87,    88,    89,
      90,    95,    96,    97,    98,    99,   100,   101,   102,   104,
     105,    46,   181,    10,     8,   139,   140,   141,   194,   108,
     109,   103,   228,   120,   228,   190,   190,   228,   228,   228,
     228,   228,   228,   228,   228,    92,   126,   131,   218,   222,
      46,   180,   190,    77,   109,   148,   191,   181,   183,   192,
     126,   132,    13,   166,   194,   166,    26,   167,   194,   167,
     192,    10,   228,   196,    25,   179,   122,    61,   103,   197,
     123,   192,    83,   143,   183,   183,   183,   188,   189,   181,
     185,   192,   192,   181,   187,   192,    71,   192,   192,   192,
      88,   182,   200,   228,   121,   205,   213,   216,   228,   121,
     205,   213,   216,   209,   183,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   119,   160,   161,   162,   228,    15,   137,
     141,   195,   196,    80,    80,   148,    10,    47,    51,    57,
      58,    73,    76,    88,    92,   149,   152,   154,   155,   156,
     157,   158,   159,   196,   191,    80,   213,   214,   226,   228,
      82,   190,    13,   190,   190,   190,   166,   164,   192,   213,
     227,   228,    46,    73,   128,   151,   152,   182,   198,   126,
     142,    92,   130,   192,   124,   221,    37,    48,    53,    63,
     110,   111,   112,   113,   130,   134,   182,   208,   213,   218,
     220,   113,   213,   209,    60,   228,   215,    80,   192,   130,
     199,   204,   181,   144,   144,   185,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   166,    71,   163,   181,   190,     9,
     138,   108,   190,   131,   150,   158,   158,    77,    77,   149,
     153,   181,   153,   181,   153,   181,    93,    80,    14,   136,
     137,   169,   136,    10,    10,   190,    10,   167,   142,   198,
     152,    10,   125,   129,   142,   228,   228,   183,   181,   228,
     184,   201,   202,   203,   192,   190,   192,   228,   190,    10,
     181,    77,    76,   157,   158,   154,   158,   154,   155,   156,
     113,   192,    10,   228,    10,   137,   164,   165,   190,    10,
     183,   142,    10,   183,   200,   209,   203,    65,   130,   131,
     158,   153,   181,   153,   181,   153,   153,   181,   166,    10,
      10,   185,   192,   154,   155,   158,   154,   190,   228,   153,
     153,   181,   153,   136,   154,   153
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
#line 162 "../parser.y"
    { parser->ast = NULL; YYACCEPT; ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 164 "../parser.y"
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
#line 177 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 179 "../parser.y"
    { (yyval.n) = alloc_cond(token_if, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);      ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 180 "../parser.y"
    { (yyval.n) = alloc_cond(token_unless, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);  ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 181 "../parser.y"
    { (yyval.n) = alloc_cond(token_while, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);   ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 182 "../parser.y"
    { (yyval.n) = alloc_cond(token_until, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);   ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 186 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 187 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 190 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 191 "../parser.y"
    { (yyval.n) = alloc_node(token_numeric, NULL, NULL);   ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 192 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 193 "../parser.y"
    { (yyval.n) = alloc_node(token_string, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 194 "../parser.y"
    { (yyval.n) = alloc_node(token_regexp, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 195 "../parser.y"
    { (yyval.n) = alloc_node(token_heredoc, NULL, NULL);   ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 196 "../parser.y"
    { (yyval.n) = alloc_node(token_backtick, NULL, NULL); pop_string(parser, (yyval.n)); ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 197 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);    ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 214 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 215 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 216 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 217 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 220 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 221 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 222 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 225 "../parser.y"
    { (yyval.n) = alloc_node(token_numeric, NULL, NULL);   ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 226 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 227 "../parser.y"
    { (yyval.n) = alloc_node(token_string, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 228 "../parser.y"
    { (yyval.n) = alloc_node(token_regexp, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 229 "../parser.y"
    { (yyval.n) = alloc_node(token_heredoc, NULL, NULL);   ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 230 "../parser.y"
    { (yyval.n) = alloc_node(token_backtick, NULL, NULL); pop_string(parser, (yyval.n)); ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 231 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 232 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);    ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 235 "../parser.y"
    { (yyval.n) = alloc_node(token_break, NULL, NULL);   ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 236 "../parser.y"
    { (yyval.n) = alloc_node(token_redo, NULL, NULL);    ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 237 "../parser.y"
    { (yyval.n) = alloc_node(token_retry, NULL, NULL);   ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 238 "../parser.y"
    { (yyval.n) = alloc_node(token_next, NULL, NULL);    ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 239 "../parser.y"
    { (yyval.n) = alloc_node(token_undef, (yyvsp[(2) - (2)].n), NULL);     ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 240 "../parser.y"
    { (yyval.n) = alloc_node(token_alias, (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));       ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 241 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 242 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 245 "../parser.y"
    { (yyval.n) = alloc_node(token_yield, NULL, NULL);   ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 246 "../parser.y"
    { (yyval.n) = alloc_node(token_yield, (yyvsp[(2) - (2)].n), NULL);     ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 249 "../parser.y"
    { (yyval.n) = alloc_node(token_return, NULL, NULL);  ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 250 "../parser.y"
    { (yyval.n) = alloc_node(token_return, (yyvsp[(2) - (2)].n), NULL);    ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 253 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 254 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 257 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 258 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 259 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 266 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_if, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
  ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 273 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_unless, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
    ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 279 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_while, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 285 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_until, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 291 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_case, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 295 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_case, NULL, (yyvsp[(2) - (3)].n), NULL);
    ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 299 "../parser.y"
    {
      (yyval.n) = alloc_node(token_up_begin, (yyvsp[(3) - (4)].n), NULL);
    ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 303 "../parser.y"
    {
      (yyval.n) = alloc_node(token_up_end, (yyvsp[(3) - (4)].n), NULL);
    ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 307 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_for, (yyvsp[(4) - (7)].n), (yyvsp[(6) - (7)].n), (yyvsp[(2) - (7)].n));
    ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 311 "../parser.y"
    {
      (yyval.n) = (yyvsp[(2) - (3)].n);
      (yyval.n)->kind = token_exception;
    ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 316 "../parser.y"
    {
      parser->in_def++;
    ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 320 "../parser.y"
    {
      parser->in_def--;
      (yyval.n) = alloc_cond(token_function, (yyvsp[(2) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(4) - (6)].n));
    ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 325 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "module definition in method body");
    ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 331 "../parser.y"
    {
      (yyval.n) = alloc_node(token_module, (yyvsp[(4) - (5)].n), (yyvsp[(2) - (5)].n));
    ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 335 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 341 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_class, (yyvsp[(3) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(2) - (6)].n));
    ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 345 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 351 "../parser.y"
    {
      (yyval.n) = alloc_node(token_singleton_class, (yyvsp[(6) - (7)].n), (yyvsp[(4) - (7)].n));
    ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 356 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 357 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 360 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 361 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 364 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 365 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 368 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 370 "../parser.y"
    {
    yyerror(parser, "class/module name must be CONSTANT");
  ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 375 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 376 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 377 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 378 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 379 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 382 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 385 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 388 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 391 "../parser.y"
    { (yyval.n) = alloc_node(token_symbol, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 394 "../parser.y"
    { (yyval.n) = alloc_node(token_symbol, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 401 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_if, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
    ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 406 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 407 "../parser.y"
    { (yyval.n) = alloc_cond(token_if, NULL, (yyvsp[(2) - (2)].n), NULL);  ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 410 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 411 "../parser.y"
    { (yyval.n) = alloc_node(token_ensure, (yyvsp[(2) - (2)].n), NULL); ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 414 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 415 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 418 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 419 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 423 "../parser.y"
    {
    (yyval.n) = alloc_node(token_rescue, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 429 "../parser.y"
    {
    (yyval.n) = alloc_ensure(token_body, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 434 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 435 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 438 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 439 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 442 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 443 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 447 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(3) - (4)].n), (yyvsp[(2) - (4)].n));
  ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 451 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 457 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(4) - (5)].n), (yyvsp[(3) - (5)].n));
  ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 461 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 467 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n));
  ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 471 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, NULL, (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 475 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 480 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 483 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);  ;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 485 "../parser.y"
    {
    (yyval.n) = update_list((yyvsp[(1) - (3)].n), alloc_node(token_object, NULL, NULL));
  ;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 490 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 491 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 494 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 495 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 497 "../parser.y"
    {
      (yyval.n) = create_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 500 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 502 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 505 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 507 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), create_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 511 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 515 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 519 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 524 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (8)].n), concat_list((yyvsp[(3) - (8)].n), create_list((yyvsp[(5) - (8)].n), update_list((yyvsp[(7) - (8)].n), (yyvsp[(8) - (8)].n)))));
    ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 528 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 533 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 534 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 537 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 538 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 541 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 544 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 547 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 548 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 551 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 552 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 556 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a constant");
    (yyval.n) = 0;
  ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 561 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be an instance variable");
    (yyval.n) = 0;
  ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 566 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a global variable");
    (yyval.n) = 0;
  ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 571 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a class variable");
    (yyval.n) = 0;
  ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 577 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 578 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 582 "../parser.y"
    {
    (yyval.n) = alloc_node(token_rescue_arg, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 587 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 588 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 591 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 592 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 596 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_when, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
  ;}
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 681 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 682 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 685 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 716 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 717 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 721 "../parser.y"
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

  case 216:

/* Line 1464 of yacc.c  */
#line 730 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);  ;}
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 731 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 732 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);  ;}
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 735 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 736 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 739 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 740 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 743 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n); ;}
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 746 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 747 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 748 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 751 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 752 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 755 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 756 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 757 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 758 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 761 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 762 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 764 "../parser.y"
    {
    (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 769 "../parser.y"
    {
    (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 773 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     ;}
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 774 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 775 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     ;}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 776 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 779 "../parser.y"
    { (yyval.n) = alloc_node(token_array, NULL, NULL); ;}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 780 "../parser.y"
    { (yyval.n) = alloc_node(token_array, (yyvsp[(2) - (3)].n), NULL);   ;}
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 781 "../parser.y"
    { (yyval.n) = alloc_node(token_array, NULL, NULL); ;}
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 785 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 786 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 787 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 790 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 791 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 795 "../parser.y"
    {
    struct node * n = (yyvsp[(3) - (5)].n);
    n->next = (yyvsp[(5) - (5)].n);
    (yyval.n) = alloc_node(token_array_value, (yyvsp[(1) - (5)].n), n);
  ;}
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 806 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 809 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, NULL, NULL);  ;}
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 810 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, (yyvsp[(2) - (3)].n), NULL);    ;}
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 813 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 814 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 817 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 818 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 822 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 826 "../parser.y"
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

  case 259:

/* Line 1464 of yacc.c  */
#line 835 "../parser.y"
    { (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 839 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  ;}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 845 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 849 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 854 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 858 "../parser.y"
    {
    struct node * n = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 863 "../parser.y"
    {
    struct node * n = alloc_node(token_method_call, (yyvsp[(2) - (4)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 868 "../parser.y"
    {
    (yyval.n) = pop_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 873 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 874 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 878 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 0;
  ;}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 883 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 1;
  ;}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 889 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 890 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 893 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 894 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 898 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 899 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 903 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 904 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 279:

/* Line 1464 of yacc.c  */
#line 905 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, (yyvsp[(1) - (1)].n), NULL);  ;}
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 909 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 910 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 913 "../parser.y"
    { (yyval.n) = alloc_node(token_plus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 914 "../parser.y"
    { (yyval.n) = alloc_node(token_minus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 284:

/* Line 1464 of yacc.c  */
#line 915 "../parser.y"
    { (yyval.n) = alloc_node(token_mul, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 916 "../parser.y"
    { (yyval.n) = alloc_node(token_div, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 917 "../parser.y"
    { (yyval.n) = alloc_node(token_mod, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 287:

/* Line 1464 of yacc.c  */
#line 918 "../parser.y"
    { (yyval.n) = alloc_node(token_exp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 919 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 289:

/* Line 1464 of yacc.c  */
#line 920 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 921 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_xor, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 922 "../parser.y"
    { (yyval.n) = alloc_node(token_lshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 923 "../parser.y"
    { (yyval.n) = alloc_node(token_rshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 924 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 925 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 926 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 927 "../parser.y"
    { (yyval.n) = alloc_node(token_cmp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 928 "../parser.y"
    { (yyval.n) = alloc_node(token_eq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      ;}
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 929 "../parser.y"
    { (yyval.n) = alloc_node(token_neq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 930 "../parser.y"
    { (yyval.n) = alloc_node(token_eqq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 931 "../parser.y"
    { (yyval.n) = alloc_node(token_match, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 932 "../parser.y"
    { (yyval.n) = alloc_node(token_nmatch, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 933 "../parser.y"
    { (yyval.n) = alloc_node(token_greater, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 303:

/* Line 1464 of yacc.c  */
#line 934 "../parser.y"
    { (yyval.n) = alloc_node(token_lesser, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 935 "../parser.y"
    { (yyval.n) = alloc_node(token_geq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 305:

/* Line 1464 of yacc.c  */
#line 936 "../parser.y"
    { (yyval.n) = alloc_node(token_leq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 306:

/* Line 1464 of yacc.c  */
#line 937 "../parser.y"
    { (yyval.n) = alloc_node(token_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      ;}
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 938 "../parser.y"
    { (yyval.n) = alloc_node(token_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 308:

/* Line 1464 of yacc.c  */
#line 939 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 309:

/* Line 1464 of yacc.c  */
#line 940 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 310:

/* Line 1464 of yacc.c  */
#line 941 "../parser.y"
    { (yyval.n) = alloc_node(token_dot2, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 942 "../parser.y"
    { (yyval.n) = alloc_node(token_dot3, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 312:

/* Line 1464 of yacc.c  */
#line 944 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_ternary, (yyvsp[(1) - (8)].n), (yyvsp[(4) - (8)].n), (yyvsp[(8) - (8)].n));
  ;}
    break;

  case 313:

/* Line 1464 of yacc.c  */
#line 947 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_not, (yyvsp[(3) - (3)].n), NULL);;}
    break;

  case 314:

/* Line 1464 of yacc.c  */
#line 948 "../parser.y"
    { (yyval.n) = alloc_node(token_neg, (yyvsp[(3) - (3)].n), NULL);   ;}
    break;

  case 315:

/* Line 1464 of yacc.c  */
#line 949 "../parser.y"
    { (yyval.n) = alloc_node(token_not, (yyvsp[(3) - (3)].n), NULL);   ;}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 950 "../parser.y"
    { (yyval.n) = alloc_node(token_unary_plus, (yyvsp[(3) - (3)].n), NULL);  ;}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 951 "../parser.y"
    { (yyval.n) = alloc_node(token_unary_minus, (yyvsp[(3) - (3)].n), NULL); ;}
    break;

  case 318:

/* Line 1464 of yacc.c  */
#line 952 "../parser.y"
    { (yyval.n) = alloc_node(token_defined, (yyvsp[(3) - (3)].n), NULL);     ;}
    break;

  case 319:

/* Line 1464 of yacc.c  */
#line 953 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 954 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n)   ;}
    break;

  case 321:

/* Line 1464 of yacc.c  */
#line 955 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;



/* Line 1464 of yacc.c  */
#line 4438 "../parser.c"
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
#line 958 "../parser.y"

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
void push_stack(struct parser_t * parser, char * buf)
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
    t = EOL;
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
      int possible_error, start;

      start = curs;
      if (*(c + 2) != '(' && *(c + 2) != '[' && *(c + 2) != '{' && !is_simple) {
        parser->column = curs - parser->line + 4;
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
          possible_error = curs - parser->line + 1;
          c += 2;
          curs += 2;
          for (ptr = buffer; *c != '}'; ++c, ++curs) {
            *ptr++ = *c;
            if (curs >= len) {
              parser->column = possible_error;
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
          parser->column = start;
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
    int possible_error = curs;
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
        parser->column = possible_error - parser->line + 2;
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
    int possible_error = 0;

    curs++;
    ++c;
    while (1) {
      if (*c == '#' && *(c + 1) == '{') {
        possible_error = curs - parser->line + 2;
        c += 2;
        curs += 2;
        for (ptr = buffer; *c != '}'; ++c, ++curs) {
          *ptr++ = *c;
          if (curs >= len || *c == '"') {
            parser->column = possible_error;
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
        parser->column = possible_error;
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
    int possible_error = 0;

    curs++;
    ++c;
    while (1) {
      if (*c == '#' && *(c + 1) == '{') {
        possible_error = curs - parser->line + 2;
        c += 2;
        curs += 2;
        for (ptr = buffer; *c != '}'; ++c, ++curs) {
          *ptr++ = *c;
          if (curs >= len || *c == '`') {
            parser->column = possible_error;
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
        parser->column = possible_error;
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
    printf("\nT: %s", p.stack[index]);
  printf("\n");
  free_parser(&p);

  return 1;
}


