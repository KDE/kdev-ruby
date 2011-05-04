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
#define YYFINAL  136
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2649

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  129
/* YYNRULES -- Number of rules.  */
#define YYNRULES  337
/* YYNRULES -- Number of states.  */
#define YYNSTATES  608

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
     223,   224,   231,   232,   240,   242,   244,   246,   248,   252,
     254,   257,   259,   261,   263,   265,   267,   269,   271,   273,
     275,   277,   279,   281,   283,   285,   287,   293,   294,   297,
     298,   301,   302,   304,   306,   309,   314,   319,   320,   324,
     325,   327,   329,   331,   336,   340,   346,   350,   355,   359,
     363,   366,   368,   372,   374,   378,   381,   384,   389,   392,
     397,   400,   407,   412,   419,   424,   433,   440,   441,   445,
     447,   451,   454,   458,   460,   464,   466,   468,   470,   472,
     474,   476,   477,   479,   482,   484,   488,   489,   493,   499,
     501,   503,   505,   507,   510,   512,   514,   517,   520,   523,
     526,   529,   532,   535,   538,   541,   544,   547,   550,   551,
     553,   556,   559,   562,   565,   568,   571,   574,   577,   580,
     584,   586,   589,   590,   592,   594,   597,   599,   601,   603,
     606,   607,   609,   611,   613,   615,   617,   621,   624,   626,
     630,   633,   635,   636,   638,   640,   643,   647,   649,   652,
     656,   658,   662,   666,   670,   674,   678,   682,   686,   691,
     696,   700,   704,   708,   712,   715,   719,   721,   723,   725,
     727,   729,   733,   739,   741,   744,   748,   750,   754,   759,
     763,   766,   769,   772,   775,   779,   782,   786,   790,   794,
     798,   801,   806,   809,   811,   814,   817,   820,   821,   823,
     824,   826,   828,   830,   832,   834,   836,   840,   842,   846,
     848,   850,   852,   854,   857,   860,   862,   864,   869,   874,
     879,   884,   889,   894,   899,   904,   909,   914,   919,   923,
     927,   931,   936,   941,   946,   951,   956,   961,   966,   971,
     976,   981,   986,   991,   996,  1001,  1006,  1011,  1020,  1024,
    1028,  1032,  1036,  1040,  1044,  1047,  1049,  1051
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     107,     0,    -1,    46,    -1,   108,    -1,   116,    -1,   121,
      -1,   208,    -1,   217,   145,    -1,   214,    -1,   108,    11,
     234,    -1,   108,    12,   234,    -1,   108,    18,   234,    -1,
     108,    19,   234,    -1,   234,    -1,   108,    -1,   109,   196,
     108,    -1,   131,    -1,    48,    -1,   135,    -1,   112,    -1,
      53,    -1,    37,    -1,    63,    -1,   111,    -1,    39,    -1,
      38,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    52,    -1,   112,    52,    -1,   110,
      -1,   209,    -1,   220,    -1,   222,    -1,   131,    -1,   220,
      -1,   222,    -1,    48,    -1,   135,    -1,   112,    -1,    53,
      -1,    37,    -1,    63,    -1,   209,    -1,   111,    -1,    21,
      -1,    23,    -1,    24,    -1,    22,    -1,     6,   119,    -1,
      33,   120,   120,    -1,   117,    -1,   118,    -1,    29,    -1,
      29,   234,    -1,    28,    -1,    28,   234,    -1,   120,    -1,
     120,   182,   119,    -1,    51,    -1,    50,    -1,   135,    -1,
     169,   234,   167,   191,   137,    10,    -1,   171,   234,   167,
     191,   137,    10,    -1,   172,   234,   168,   191,    10,    -1,
     173,   234,   168,   191,    10,    -1,   174,   234,   197,   165,
      10,    -1,   174,   165,    10,    -1,    35,    79,   191,    80,
      -1,    36,    79,   191,    80,    -1,   176,   205,   180,   233,
     168,   191,    10,    -1,     7,   143,    10,    -1,    -1,   177,
     128,   122,   129,   143,    10,    -1,    -1,   178,   130,   123,
     143,    10,    -1,    -1,   179,   130,   144,   124,   143,    10,
      -1,    -1,   179,    69,   193,   131,   125,   143,    10,    -1,
      50,    -1,   132,    -1,   126,    -1,   134,    -1,   132,   198,
     126,    -1,   126,    -1,   152,   199,    -1,   199,    -1,    92,
      -1,   218,    -1,    51,    -1,   132,    -1,    47,    -1,    58,
      -1,    57,    -1,    92,    -1,    51,    -1,    54,    -1,    92,
      -1,    49,    -1,    91,    -1,   138,    -1,   170,   234,   167,
     191,   137,    -1,    -1,    15,   191,    -1,    -1,     9,   191,
      -1,    -1,   141,    -1,   142,    -1,   141,   142,    -1,     8,
     161,   167,   191,    -1,   191,   140,   138,   139,    -1,    -1,
      83,   193,   130,    -1,    -1,   146,    -1,   147,    -1,   148,
      -1,   187,   149,   192,    80,    -1,   187,   192,    80,    -1,
      27,   181,   149,   191,    10,    -1,    27,   191,    10,    -1,
      77,   153,   150,    77,    -1,    77,   150,    77,    -1,    77,
     153,    77,    -1,    73,   151,    -1,   132,    -1,   151,   182,
     132,    -1,   153,    -1,   183,   153,   184,    -1,    76,   159,
      -1,   155,   154,    -1,   156,   182,   155,   154,    -1,   156,
     154,    -1,   158,   182,   155,   154,    -1,   158,   154,    -1,
     158,   182,   156,   182,   155,   154,    -1,   158,   182,   156,
     154,    -1,   155,   182,   158,   182,   155,   154,    -1,   155,
     182,   158,   154,    -1,   155,   182,   158,   182,   156,   182,
     155,   154,    -1,   155,   182,   158,   182,   156,   154,    -1,
      -1,   182,    76,   159,    -1,   159,    -1,   155,   182,   159,
      -1,    88,   159,    -1,   159,    93,   113,    -1,   157,    -1,
     158,   182,   157,    -1,    51,    -1,   160,    -1,    92,    -1,
      57,    -1,    58,    -1,    47,    -1,    -1,   162,    -1,   163,
     164,    -1,   234,    -1,   163,   182,   234,    -1,    -1,    71,
     193,   131,    -1,   175,   234,   167,   191,   166,    -1,   138,
      -1,   165,    -1,   195,    -1,    13,    -1,   195,    13,    -1,
     195,    -1,    26,    -1,    11,   193,    -1,    14,   193,    -1,
      12,   193,    -1,    18,   193,    -1,    19,   193,    -1,    16,
     193,    -1,    17,   193,    -1,    20,   193,    -1,     5,   193,
      -1,     4,   193,    -1,     3,   193,    -1,    25,   193,    -1,
      -1,    46,    -1,    64,   193,    -1,    81,   193,    -1,   193,
      82,    -1,    59,   193,    -1,   193,    60,    -1,    79,   193,
      -1,   193,    80,    -1,    93,   193,    -1,    94,   193,    -1,
     197,   109,   197,    -1,   197,    -1,   109,   197,    -1,    -1,
     194,    -1,    46,    -1,   194,    46,    -1,    73,    -1,    46,
      -1,   195,    -1,   196,   195,    -1,    -1,   196,    -1,    61,
      -1,   103,    -1,    46,    -1,    73,    -1,   205,   182,   201,
      -1,   205,   182,    -1,   234,    -1,   183,   200,   184,    -1,
      88,   131,    -1,    88,    -1,    -1,   203,    -1,   204,    -1,
     203,   204,    -1,   185,   210,   186,    -1,   234,    -1,   205,
     182,    -1,   205,   182,   201,    -1,   234,    -1,   206,   182,
     234,    -1,   131,   189,   113,    -1,   131,   190,   113,    -1,
     131,   189,   214,    -1,   131,   190,   214,    -1,   205,   189,
     206,    -1,   205,   190,   206,    -1,   205,   189,   217,   145,
      -1,   205,   190,   217,   145,    -1,   205,   189,   214,    -1,
     205,   190,   214,    -1,   205,   189,   121,    -1,   205,   190,
     121,    -1,   185,    60,    -1,   185,   211,   186,    -1,    55,
      -1,   234,    -1,   207,    -1,   214,    -1,   210,    -1,   211,
     182,   210,    -1,   213,   193,   210,   186,   202,    -1,    56,
      -1,   187,    80,    -1,   187,   215,   188,    -1,   216,    -1,
     215,   182,   216,    -1,   234,    71,   193,   234,    -1,   136,
     193,   234,    -1,   126,   227,    -1,   222,   227,    -1,   218,
     225,    -1,   134,   219,    -1,   134,   103,   126,    -1,   103,
     134,    -1,   219,   103,   127,    -1,   133,   226,   184,    -1,
     221,   226,   184,    -1,   134,   103,   133,    -1,   110,   223,
      -1,   183,   234,   184,   223,    -1,   220,   223,    -1,   224,
      -1,   223,   224,    -1,    61,   126,    -1,    61,   220,    -1,
      -1,   227,    -1,    -1,   228,    -1,   217,    -1,   229,    -1,
     217,    -1,   230,    -1,   234,    -1,   229,   182,   231,    -1,
     232,    -1,   230,   182,   232,    -1,   234,    -1,   214,    -1,
     215,    -1,   231,    -1,    76,   234,    -1,    88,   234,    -1,
     234,    -1,   214,    -1,   234,    86,   193,   234,    -1,   234,
      87,   193,   234,    -1,   234,    88,   193,   234,    -1,   234,
      89,   193,   234,    -1,   234,    90,   193,   234,    -1,   234,
      66,   193,   234,    -1,   234,    76,   193,   234,    -1,   234,
      77,   193,   234,    -1,   234,    78,   193,   234,    -1,   234,
      69,   193,   234,    -1,   234,    70,   193,   234,    -1,   183,
     234,   184,    -1,   183,   208,   184,    -1,   183,   217,   184,
      -1,   234,    95,   193,   234,    -1,   234,    96,   193,   234,
      -1,   234,    98,   193,   234,    -1,   234,    97,   193,   234,
      -1,   234,    99,   193,   234,    -1,   234,   100,   193,   234,
      -1,   234,    84,   193,   234,    -1,   234,    83,   193,   234,
      -1,   234,   101,   193,   234,    -1,   234,   102,   193,   234,
      -1,   234,    74,   193,   234,    -1,   234,    75,   193,   234,
      -1,   234,    31,   193,   234,    -1,   234,    30,   193,   234,
      -1,   234,   105,   193,   234,    -1,   234,   104,   193,   234,
      -1,   234,    72,   193,   234,   193,    65,   193,   234,    -1,
      32,   193,   234,    -1,    62,   193,   234,    -1,    85,   193,
     234,    -1,    68,   193,   234,    -1,    67,   193,   234,    -1,
      34,   193,   234,    -1,   114,   145,    -1,   115,    -1,   212,
      -1,    50,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   163,   163,   164,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   187,   188,   191,   192,   193,   194,
     195,   196,   197,   198,   201,   202,   203,   204,   205,   206,
     207,   208,   211,   212,   215,   216,   217,   218,   221,   222,
     223,   226,   227,   228,   229,   230,   231,   232,   233,   236,
     237,   238,   239,   240,   241,   242,   243,   246,   247,   250,
     251,   254,   255,   258,   259,   260,   263,   270,   277,   283,
     289,   295,   299,   303,   307,   311,   317,   316,   326,   325,
     336,   335,   346,   345,   357,   358,   361,   362,   365,   366,
     369,   370,   373,   374,   375,   381,   382,   383,   384,   385,
     388,   391,   394,   397,   400,   403,   404,   412,   413,   416,
     417,   420,   421,   424,   425,   428,   434,   440,   441,   444,
     445,   448,   449,   452,   456,   462,   466,   472,   476,   480,
     486,   489,   490,   496,   497,   500,   501,   502,   506,   507,
     511,   512,   516,   520,   524,   528,   533,   539,   540,   543,
     544,   547,   550,   553,   554,   557,   558,   561,   566,   571,
     576,   583,   584,   587,   593,   594,   597,   598,   601,   607,
     608,   611,   612,   613,   616,   617,   620,   623,   626,   629,
     632,   635,   638,   641,   644,   647,   650,   653,   656,   657,
     660,   663,   666,   669,   672,   675,   678,   681,   684,   687,
     688,   691,   694,   695,   698,   699,   702,   703,   706,   707,
     710,   711,   714,   715,   718,   719,   722,   723,   726,   736,
     737,   738,   741,   742,   745,   746,   749,   752,   753,   754,
     757,   758,   761,   762,   763,   764,   767,   768,   769,   774,
     779,   780,   781,   782,   785,   786,   787,   791,   792,   793,
     796,   797,   800,   812,   815,   816,   819,   820,   823,   824,
     827,   831,   841,   844,   849,   856,   857,   860,   864,   870,
     873,   878,   883,   889,   890,   893,   898,   905,   906,   909,
     910,   913,   914,   917,   918,   922,   923,   926,   927,   931,
     932,   933,   936,   937,   938,   942,   943,   946,   947,   948,
     949,   950,   951,   952,   953,   954,   955,   956,   957,   958,
     959,   960,   961,   962,   963,   964,   965,   966,   967,   968,
     969,   970,   971,   972,   973,   974,   975,   976,   980,   981,
     982,   983,   984,   985,   986,   987,   988,   989
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
  "cmpd_stmt", "$@1", "$@2", "$@3", "$@4", "fname", "fname_or_const",
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
     124,   121,   125,   121,   126,   126,   127,   127,   128,   128,
     129,   129,   130,   130,   130,   131,   131,   131,   131,   131,
     132,   133,   134,   135,   136,   137,   137,   138,   138,   139,
     139,   140,   140,   141,   141,   142,   143,   144,   144,   145,
     145,   146,   146,   147,   147,   148,   148,   149,   149,   149,
     150,   151,   151,   152,   152,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   154,   154,   155,
     155,   156,   157,   158,   158,   159,   159,   160,   160,   160,
     160,   161,   161,   162,   163,   163,   164,   164,   165,   166,
     166,   167,   167,   167,   168,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     191,   192,   193,   193,   194,   194,   195,   195,   196,   196,
     197,   197,   198,   198,   199,   199,   200,   200,   201,   201,
     201,   201,   202,   202,   203,   203,   204,   205,   205,   205,
     206,   206,   207,   207,   207,   207,   208,   208,   208,   208,
     208,   208,   208,   208,   209,   209,   209,   210,   210,   210,
     211,   211,   212,   213,   214,   214,   215,   215,   216,   216,
     217,   217,   217,   218,   218,   219,   219,   220,   220,   221,
     222,   222,   222,   223,   223,   224,   224,   225,   225,   226,
     226,   227,   227,   228,   228,   229,   229,   230,   230,   231,
     231,   231,   232,   232,   232,   233,   233,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234
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
       0,     6,     0,     7,     1,     1,     1,     1,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     0,     2,     0,
       2,     0,     1,     1,     2,     4,     4,     0,     3,     0,
       1,     1,     1,     4,     3,     5,     3,     4,     3,     3,
       2,     1,     3,     1,     3,     2,     2,     4,     2,     4,
       2,     6,     4,     6,     4,     8,     6,     0,     3,     1,
       3,     2,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     0,     1,     2,     1,     3,     0,     3,     5,     1,
       1,     1,     1,     2,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     0,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       1,     2,     0,     1,     1,     2,     1,     1,     1,     2,
       0,     1,     1,     1,     1,     1,     3,     2,     1,     3,
       2,     1,     0,     1,     1,     2,     3,     1,     2,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     4,     4,
       3,     3,     3,     3,     2,     3,     1,     1,     1,     1,
       1,     3,     5,     1,     2,     3,     1,     3,     4,     3,
       2,     2,     2,     2,     3,     2,     3,     3,     3,     3,
       2,     4,     2,     1,     2,     2,     2,     0,     1,     0,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     1,
       1,     1,     1,     2,     2,     1,     1,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     3,
       3,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     8,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   202,   202,   202,     0,   210,   202,   202,   202,   202,
     202,   202,    49,    52,    50,    51,    59,    57,   202,     0,
     202,     0,     0,    45,    25,    24,    26,    27,    28,    29,
      30,    31,     2,    96,    41,   103,   337,   100,    32,    44,
     101,   246,   253,    98,    97,   202,   202,    46,   202,   202,
     202,   202,   202,    99,     0,     3,     0,    48,    43,   119,
     335,     4,    55,    56,     5,     0,    38,    95,   279,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,    47,   336,   202,     8,   119,
     277,    39,   279,    40,    13,   204,   186,   203,   185,   184,
      64,    63,    53,    61,    65,   207,   206,     0,   111,   208,
     211,   200,   176,   178,   181,   179,   180,   183,   337,    95,
       0,    40,    60,    58,     0,     0,     0,   210,   210,   193,
       0,     0,     0,   195,   191,     0,     1,     0,     0,     0,
       0,     0,   270,   273,    33,   210,   334,   120,   121,   122,
       0,   281,   260,   282,   285,     0,     0,   104,   202,   290,
     291,   256,   283,   202,   280,   284,   292,   287,   289,     0,
     263,     0,     0,     0,     0,   202,     0,     0,   210,     0,
     227,    84,    89,    76,    85,    94,    92,    78,     0,    93,
     202,   117,   202,   202,   227,   244,    38,   248,   250,   202,
     249,   247,   254,   202,     0,   202,   202,   202,   228,     0,
       0,     0,     7,   262,   278,   272,   202,   261,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   205,     0,    75,   161,
     107,   112,   113,   209,    14,   210,     0,   328,    54,   333,
       0,     0,   329,   332,   331,   330,     9,    10,    11,    12,
     102,   275,    85,   276,   274,   207,     0,     0,     0,   210,
       0,     0,     0,   293,   294,     0,     0,   267,     0,     0,
     202,   264,   269,   265,     0,   172,   210,   171,   210,   175,
     210,   174,   210,   182,    71,     0,     0,   202,     0,     0,
     212,   213,     0,   210,     0,     0,   202,    80,   309,   310,
     308,     0,     0,     0,   245,     0,   255,     0,   190,   197,
     198,   221,     0,   229,   218,   242,   236,   240,   119,   230,
     243,   237,   241,   119,   202,   268,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,     0,   162,   166,   164,   210,
     109,   114,   211,   199,    72,    73,   210,   126,   160,   155,
     158,   159,     0,     0,     0,   157,     0,     0,   147,   147,
     153,   147,   149,   156,   201,     0,   124,   286,   259,   257,
     192,   288,     0,    86,   266,    87,   107,   173,   107,     0,
       0,   210,     0,   187,   296,     0,   295,   214,   215,   210,
       0,   133,     0,    91,    88,     0,    99,    82,     0,   210,
     271,    21,    17,    20,    22,    34,    23,    19,   232,    16,
      18,     0,    35,   234,    36,    37,   233,   235,   251,   194,
     196,   220,   202,     0,     0,   238,   239,   222,   324,   323,
     302,   306,   307,   202,   321,   322,   303,   304,   305,   318,
     317,   297,   298,   299,   300,   301,   311,   312,   314,   313,
     315,   316,   319,   320,   326,   325,   210,   202,   163,     0,
     108,   210,   116,    15,     0,   131,   130,   135,   151,   128,
     129,     0,   136,     0,   138,     0,   140,     0,     0,   123,
     258,   202,     0,   105,     0,     0,    68,    69,   107,    70,
     210,     0,    90,   202,    79,   210,   118,     0,   202,   219,
     228,   231,     0,   252,   223,   224,     0,   115,     0,   165,
     110,   125,     0,   127,     0,   147,   150,   147,   149,   147,
     147,   154,   152,   177,    66,     0,    67,   169,   170,   168,
       0,    77,   134,     0,    81,     0,   229,   202,   225,   202,
     167,   132,   148,   144,     0,   137,     0,   139,   142,     0,
     210,    74,    83,   226,     0,   147,   147,   150,   147,   107,
     327,   143,   146,     0,   141,   106,   147,   145
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    54,   254,   279,    56,    57,    58,   448,    59,    60,
      61,    62,    63,   102,   103,    64,   309,   313,   439,   535,
      65,   414,   183,   429,   187,    66,   119,    68,   120,    70,
     158,   522,   523,   502,   250,   251,   252,   107,   317,   146,
     147,   148,   149,   280,   396,   506,   430,   397,   512,   398,
     399,   400,   401,   402,   403,   375,   376,   377,   498,   176,
     569,   296,   300,    71,   524,    72,    73,    74,    75,   177,
      76,    77,    78,    79,   308,   276,   586,    80,   287,    81,
     324,    82,   326,   209,   210,   108,   281,   288,    97,   109,
     110,   111,   312,   433,   462,   333,   543,   544,   545,    83,
     336,   197,    84,    85,   198,   199,    86,    87,    88,   160,
     161,    89,    90,   170,    91,    92,   121,   142,   143,   213,
     163,   152,   164,   153,   165,   166,   167,   425,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -481
static const yytype_int16 yypact[] =
{
     935,    22,    22,    22,   264,    32,    22,    22,    22,    22,
      22,    22,  -481,  -481,  -481,  -481,  2105,  2105,    22,   264,
      22,     9,    15,    46,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,    64,  -481,  2161,  -481,  -481,    74,
    -481,  -481,  -481,  -481,  -481,    22,    22,    85,    22,    22,
      22,    22,    22,    48,   158,   290,   124,   128,   117,    21,
    -481,  -481,  -481,  -481,  -481,  2217,   129,  2273,  1589,   101,
     145,  2105,  2105,  2105,  2105,  1228,  2105,   113,    42,    44,
    2217,  1768,  1824,    77,  -481,  -481,  -481,    22,  -481,    21,
    2217,   124,  1589,  2217,  1258,  -481,  -481,   166,  -481,  -481,
    -481,  -481,  -481,   153,  -481,  -481,  -481,   211,   215,  -481,
      32,  1101,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
     116,  -481,  1515,  1515,  2105,   264,  2105,    32,    32,  -481,
    2105,  2105,  2105,  -481,  -481,  2105,  -481,  2105,  2105,  2105,
    2105,   106,   124,  -481,  -481,    24,  -481,  -481,  -481,  -481,
    1018,  -481,  -481,   153,  1515,  2105,  2105,  -481,    22,  -481,
     153,  -481,  -481,    22,  -481,   153,  -481,  -481,  1417,   106,
     135,   582,   582,   689,   689,    22,   214,  2105,  1319,    28,
    1515,  -481,  -481,  -481,   -14,  -481,    48,  -481,   142,  -481,
      22,   171,    22,    22,  1380,  -481,    89,  -481,  -481,    27,
    -481,  1515,  -481,    27,  1417,    22,    22,    22,  1936,  1172,
    1172,  1993,  -481,  -481,  -481,   124,    22,  -481,    22,    22,
      22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,  -481,   264,  -481,  2105,
     237,   215,  -481,  -481,   290,    32,   205,  2374,  -481,  2374,
     180,   188,  -481,   206,  -481,  -481,  1515,  1515,  1515,  1515,
    -481,  -481,  -481,  -481,  -481,   194,   197,   266,   487,    32,
    1101,   200,  1880,  1515,  1515,  2105,  2049,  -481,   195,  1650,
      22,  -481,  -481,  -481,    -6,  -481,    32,   275,    32,  -481,
      32,  -481,    32,  -481,  -481,   582,   273,    22,  1993,   751,
    -481,  -481,   113,    32,    -6,   169,    22,  -481,  -481,  -481,
     124,  2329,  2329,  1993,  -481,   240,  -481,   223,  -481,  -481,
    -481,   169,  2217,  -481,  1515,  -481,   153,  -481,    21,  1515,
    -481,   153,  -481,    21,    22,  -481,  2105,  2105,  2105,  2105,
    2105,  2105,  2105,  2105,  2105,  2105,  2105,  2105,  2105,  2105,
    2105,  2105,  2105,  2105,  2105,  2105,  2105,  2105,  2105,  2105,
    2105,  2105,  2105,  2105,  -481,    29,  -481,    -2,  1515,    32,
     295,  -481,   844,  -481,  -481,  -481,    32,  -481,  -481,  -481,
    -481,  -481,   259,   337,   337,  -481,   234,    70,   153,   153,
    -481,   153,   224,  -481,  -481,   239,  -481,  -481,  1515,  -481,
    -481,  -481,  2105,  -481,  -481,  -481,    68,  -481,    68,   311,
     312,    32,   318,  -481,  -481,    25,  1515,  -481,  -481,    32,
      53,  -481,   646,  -481,  -481,   319,  -481,  -481,    42,    32,
     124,  -481,  -481,  -481,  -481,   124,  -481,   323,  -481,  -481,
    -481,  2105,  -481,  -481,   124,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,    22,    77,  2105,  -481,  -481,   320,  2374,  2374,
     206,   209,   209,  1478,  2448,  2485,   545,   747,   747,  2559,
    2559,   121,   121,   206,   206,   206,  2522,  2522,  2522,  2522,
    2522,  2522,  2559,  2559,  2411,  2411,    32,    22,  -481,  2105,
    -481,    32,  -481,   290,   368,  -481,   153,  -481,  -481,  -481,
    -481,   303,  -481,   108,  -481,   108,  -481,   723,  2375,  -481,
    1515,    22,   371,  -481,  2105,   377,  -481,  -481,   186,  -481,
      32,   379,  -481,    22,  -481,    32,  -481,   380,  1478,  -481,
    1711,  1515,  1993,  -481,   320,  -481,   327,  -481,   169,  1515,
    -481,  -481,   259,  -481,   337,   153,   224,   153,  -481,   153,
     153,  -481,  -481,  -481,  -481,   582,  -481,  -481,  -481,  -481,
     388,  -481,  -481,   390,  -481,   124,     8,    22,  -481,    22,
    -481,  -481,  -481,  -481,   723,  -481,   108,  -481,  -481,   108,
      32,  -481,  -481,  -481,  2105,   153,   153,  -481,   153,    68,
    2374,  -481,  -481,   108,  -481,  -481,   153,  -481
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -481,  -481,     3,   291,  -296,  -290,  -288,  -300,  -481,  -481,
    -481,  -481,  -481,   154,    20,   -33,  -481,  -481,  -481,  -481,
     -57,  -481,  -481,  -481,   -74,    51,   414,  -123,   437,     2,
    -481,  -391,  -237,  -481,  -481,  -481,   156,  -285,  -481,   -80,
    -481,  -481,  -481,   134,     7,  -481,  -481,  -280,    43,  -436,
    -480,  -467,  -108,    18,  -481,  -481,  -481,  -481,  -481,  -282,
    -481,  -168,  -160,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,    26,  -141,  -175,  -424,
    -321,   -49,  -481,   217,   219,   241,   136,   233,  -481,     1,
    -192,  -117,  -481,   -13,  -481,  -122,  -481,  -481,  -116,   -68,
     212,  -481,   -65,  -286,  -181,  -481,  -481,  -481,     4,   348,
     133,   341,   -67,  -481,  -125,  -481,    38,   -89,  -135,  -481,
     349,   109,  -481,  -481,  -481,   161,   157,  -481,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -228
static const yytype_int16 yytable[] =
{
     122,   123,   215,    55,   298,   191,   104,   274,   179,   212,
     150,   189,   189,   380,   302,   192,   273,   318,   319,   320,
     182,   104,   456,   467,   422,   445,   445,   525,   435,   431,
     344,   446,   446,   447,   447,   452,   452,   560,    93,   125,
     150,   345,   295,   542,   181,    37,   292,   310,   145,   154,
     561,   299,   168,   307,  -216,   171,   172,   173,   174,   178,
     180,   306,   205,   382,   194,   201,   204,   332,    95,   497,
     275,   105,   159,    95,   154,   105,   168,   154,   105,   557,
     274,   559,   521,   379,   271,   200,   270,   382,   127,   311,
    -216,   205,   205,   185,   128,   185,   159,   106,   106,   427,
      50,  -188,   106,    93,   596,   106,    93,   -21,   257,   208,
     259,   253,   291,   190,   262,   263,   264,   561,    93,   265,
     542,   266,   267,   268,   269,   -17,   428,   104,    93,   247,
      93,    93,   196,   292,   186,   -20,   186,   421,   383,   283,
     284,   205,   458,   392,   531,   258,   -22,   510,   595,    93,
     -16,  -102,   533,   598,   537,   388,   181,    37,   136,   389,
      40,   305,   404,   181,    37,   390,   391,   606,   432,   144,
     206,   207,   297,   297,   301,   301,   335,   340,   -19,   282,
     451,   451,   206,   207,   554,   141,   286,   220,    93,   -23,
     -16,   289,   334,   339,   339,   201,   454,   454,   270,   214,
     395,   379,   217,   175,   169,   208,   -18,   496,   605,   233,
     234,   235,   246,   337,   342,   200,    33,   205,   562,   256,
      37,   248,   445,   249,   304,   323,    43,    44,   446,   286,
     447,   440,   452,   378,    96,    98,    99,   413,   294,   112,
     113,   114,   115,   116,   117,   314,   568,    93,    93,   104,
     573,   124,   379,   126,   316,   434,   593,   291,   465,    40,
     384,   436,   196,   466,   463,   530,   168,   192,   385,   408,
     204,  -189,   220,   168,   278,   220,   387,   410,   129,   130,
     406,   131,   132,   133,   134,   135,   159,   539,   417,   150,
     175,   567,   426,   159,   150,   231,   232,   233,   234,   235,
     459,   137,   138,   460,   501,   274,   297,   201,   139,   140,
      37,   509,   424,    35,   100,   101,   194,   518,    93,   519,
     211,   526,   527,   450,   450,   453,   457,   200,   529,   534,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   495,   572,   455,
     455,   577,   464,   575,   536,   215,   437,   464,   260,   261,
      93,   189,   449,   449,   196,   144,   297,   451,   551,    45,
     553,   564,   461,   253,   388,   503,   277,   566,   389,   571,
     574,   285,   579,   454,   390,   391,   520,   590,   591,   332,
     592,   374,   255,   499,   511,   555,   151,   381,   303,   162,
     386,   507,   508,   321,    67,   322,   405,   532,   576,   409,
      93,   193,   341,   315,   513,   515,   301,   517,   578,   395,
     203,   151,   325,   162,   151,   538,   327,    69,   328,   329,
     330,   216,   514,   407,   516,     0,   411,     0,   541,     0,
       0,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,    67,
       0,     0,    67,   549,     0,     0,   440,     0,     0,   540,
       0,   184,     0,     0,    67,     0,     0,     0,     0,     0,
       0,     0,    69,     0,    67,    69,    67,    67,   565,     0,
       0,     0,     0,     0,     0,   188,   188,    69,     0,     0,
     450,     0,     0,   412,   334,    67,   201,    69,     0,    69,
      69,   556,   552,   558,   388,     0,     0,   416,   389,   418,
     423,   419,     0,   420,   390,   391,   200,     0,    69,   438,
     338,   343,     0,     0,     0,   272,   455,     0,     0,     0,
     392,     0,     0,   393,    67,     0,   297,     0,     0,   449,
       0,     0,   582,     0,     0,   394,     0,   325,   600,   395,
       0,   584,     0,   272,     0,     0,   589,    69,     0,     0,
       0,     0,     0,   196,     0,   295,     0,     0,   583,   580,
     585,     0,   587,   588,   597,     0,   293,   558,     0,     0,
       0,   220,   218,   219,   221,   222,     0,     0,     0,     0,
     500,   558,   603,    67,    67,     0,     0,   504,   105,     0,
       0,   231,   232,   233,   234,   235,     0,     0,   601,   602,
       0,   604,     0,     0,     0,     0,    69,    69,   220,   607,
       0,   221,   222,     0,   223,   106,   224,   225,   226,   227,
     228,     0,   528,     0,     0,   229,   230,     0,   231,   232,
     233,   234,   235,   193,     0,     0,     0,   236,   237,   238,
     239,   240,   241,   242,   243,     0,   244,   245,     0,     0,
       0,     0,     0,   388,    67,     0,     0,   389,     0,     0,
       0,     0,     0,   390,   391,     0,   546,     0,   272,     0,
       0,     0,     0,     0,     0,   299,     0,    69,     0,   218,
     219,     0,   393,     0,     0,     0,   272,     0,   272,     0,
     548,   415,     0,     0,   394,   105,     0,   547,   395,     0,
       0,     0,   550,     0,     0,     0,    67,     0,     0,     0,
       0,   293,     0,     0,   563,   220,     0,     0,   221,   222,
       0,   223,   106,   224,   225,   226,   227,   228,     0,    69,
     388,   570,   229,   230,   389,   231,   232,   233,   234,   235,
     390,   391,     0,     0,   236,   237,   238,   239,   240,   241,
     242,   243,     0,   244,   245,     0,    67,   427,   388,   554,
       0,     0,   389,     0,     0,     0,   505,     0,   390,   391,
     325,   394,   594,   220,     0,   395,   221,   222,     0,    69,
       0,     0,     0,   226,   428,     0,     0,   393,     0,     0,
       0,   599,    51,   231,   232,   233,   234,   235,     0,   394,
       0,     0,     0,   395,     0,     0,     0,     1,     2,     3,
       4,     5,     0,     0,     0,     6,     7,     0,     0,     0,
       8,     0,     9,    10,    11,    12,    13,    14,    15,     0,
       0,     0,    16,    17,     0,   188,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
     105,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,     0,    46,    47,     0,     0,
       0,    48,    49,     0,     0,     0,     0,   106,     0,     0,
       0,     0,     0,    50,     0,    51,     0,     0,     0,    52,
       0,     0,     0,     0,     0,     0,    53,     0,     1,     2,
       3,     4,     5,     0,     0,     0,     6,     7,     0,     0,
       0,     8,     0,     9,    10,    11,    12,    13,    14,    15,
       0,     0,     0,    16,    17,     0,   581,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,     0,     0,    46,    47,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,    51,     0,     0,     0,
      52,     1,     2,     3,     4,     5,     0,    53,     0,     6,
       7,     0,     0,     0,     8,     0,     9,    10,    11,    12,
      13,    14,    15,     0,     0,     0,    16,    17,     0,     0,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     0,     0,
      46,    47,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,   278,     0,    50,     0,    51,
       0,     0,     0,    52,     1,     2,     3,     4,     5,     0,
      53,     0,     6,     7,     0,     0,     0,     8,     0,     9,
      10,    11,    12,    13,    14,    15,     0,     0,     0,    16,
      17,     0,     0,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,    46,    47,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     1,     2,     3,     0,     5,
      50,     0,    51,     6,     7,     0,    52,     0,     8,     0,
       9,    10,    11,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,     0,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     0,     0,    46,    47,     0,     0,     0,    48,
      49,     0,     0,     0,     0,   175,     0,     0,     0,     0,
       0,    50,     0,    51,     0,     0,     0,    52,     0,     0,
      18,     0,    20,     0,    53,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    33,    34,    35,   118,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   218,   219,
      46,    47,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,     0,    52,     0,     0,     0,     0,     0,     0,
      53,     0,  -227,     0,   220,     0,     0,   221,   222,     0,
     223,     0,   224,   225,   226,   227,   228,     0,     0,     0,
       0,   229,   230,     0,   231,   232,   233,   234,   235,   218,
     219,  -227,  -227,   236,   237,   238,   239,   240,   241,   242,
     243,     0,   244,   245,     0,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   220,     0,     0,   221,   222,
       0,   223,   106,   224,   225,   226,   227,   228,     0,     0,
       0,     0,   229,   230,     0,   231,   232,   233,   234,   235,
     218,   219,     0,     0,   236,   237,   238,   239,   240,   241,
     242,   243,     0,   244,   245,     0,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   220,   218,   219,   221,
     222,     0,   223,     0,   224,   225,   226,   227,   228,     0,
       0,     0,  -202,   229,   230,     0,   231,   232,   233,   234,
     235,     0,     0,     0,     0,   236,   237,   238,   239,   240,
     241,   242,   243,   220,   244,   245,   221,   222,   290,   223,
       0,   224,   225,   226,   227,   228,     0,     0,     0,     0,
     229,   230,     0,   231,   232,   233,   234,   235,   218,   219,
       0,     0,   236,   237,   238,   239,   240,   241,   242,   243,
       0,   244,   245,     0,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   220,   218,   219,   221,   222,     0,
     223,     0,   224,   225,   226,   227,   228,     0,     0,     0,
       0,   229,   230,     0,   231,   232,   233,   234,   235,     0,
       0,     0,     0,   236,   237,   238,   239,   240,   241,   242,
     243,   220,   244,   245,   221,   222,     0,   223,     0,   224,
     225,   226,   227,   228,     0,     0,     0,     0,   229,   230,
       0,   231,   232,   233,   234,   235,     0,     0,     0,     0,
     236,   237,   238,   239,   240,   241,   242,   243,     0,   244,
     245,    18,     0,    20,     0,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,    46,    47,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,   155,     0,     0,    50,     0,
      51,     0,     0,     0,    52,     0,     0,   156,     0,     0,
     157,    53,    18,     0,    20,     0,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    33,    34,    35,
     118,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,    47,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,   155,     0,     0,    50,
       0,    51,     0,     0,     0,    52,     0,     0,   156,     0,
       0,   157,    53,    18,     0,    20,     0,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,  -217,    33,    34,
      35,   118,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,    46,    47,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,  -217,     0,     0,    52,     0,     0,   331,
      18,     0,    20,    53,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    33,    34,    35,   118,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   195,     0,
      46,    47,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,    51,
       0,     0,     0,    52,     0,     0,    18,     0,    20,     0,
      53,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    33,    34,    35,   118,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,     0,    46,    47,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,    51,     0,     0,     0,    52,
       0,     0,    18,     0,    20,   157,    53,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    33,    34,    35,
     118,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,    47,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,    51,     0,     0,     0,    52,     0,     0,    18,     0,
      20,   157,    53,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     0,    33,    34,    35,   118,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     0,     0,    46,    47,
       0,     0,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
       0,    52,     0,     0,   331,    18,     0,    20,    53,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      33,    34,    35,   118,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,    46,    47,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,    51,     0,     0,     0,    52,     0,
       0,    18,     0,    20,     0,    53,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,   118,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,    46,    47,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,    52,     0,     0,    18,     0,    20,
     157,    53,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    33,    34,    35,   118,    37,    38,    39,    40,
      41,    42,    43,    44,    45,     0,     0,    46,    47,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,     0,     0,     0,
      52,     0,     0,   -84,     0,   -84,     0,    53,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,     0,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,     0,     0,   -84,   -84,     0,     0,     0,   -84,   -84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -84,     0,     0,     0,   -84,     0,     0,    18,
       0,    20,     0,   -84,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,    46,
      47,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
       0,     0,    52,     0,     0,   -85,     0,   -85,     0,    53,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,     0,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,     0,     0,   -85,   -85,     0,     0,     0,
     -85,   -85,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -85,     0,     0,     0,   -85,     0,
       0,     0,     0,     0,     0,   -85,   441,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,   442,    35,     0,
      37,    38,   443,    40,    41,     0,    43,    44,    45,     0,
       0,     0,   444,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
      51,     0,   441,    24,    25,    26,    27,    28,    29,    30,
      31,    53,    33,   442,    35,     0,    37,    38,   443,    40,
      41,     0,    43,    44,    45,     0,     0,     0,   444,     0,
     220,     0,     0,   221,   222,     0,   223,     0,   224,   225,
     226,   227,   228,     0,     0,     0,    51,   229,   230,     0,
     231,   232,   233,   234,   235,     0,     0,    53,     0,   236,
     237,   238,   239,   240,   241,   242,   243,   220,   244,   245,
     221,   222,     0,     0,     0,   224,   225,   226,   227,   228,
       0,     0,     0,     0,   229,   230,     0,   231,   232,   233,
     234,   235,     0,     0,     0,     0,   236,   237,   238,   239,
     240,   241,   242,   243,   220,  -228,  -228,   221,   222,     0,
       0,     0,     0,   225,   226,   227,   228,     0,     0,     0,
       0,   229,   230,     0,   231,   232,   233,   234,   235,     0,
       0,     0,     0,   236,   237,   238,   239,   240,   241,   242,
     243,   220,     0,     0,   221,   222,     0,     0,     0,     0,
       0,   226,   227,   228,     0,     0,     0,     0,   229,   230,
       0,   231,   232,   233,   234,   235,     0,     0,     0,     0,
     236,   237,   238,   239,   240,   241,   242,   243,   220,     0,
       0,   221,   222,     0,     0,     0,     0,     0,   226,   227,
     228,     0,     0,     0,     0,   229,   230,     0,   231,   232,
     233,   234,   235,     0,     0,     0,     0,  -228,  -228,  -228,
    -228,  -228,  -228,   242,   243,   220,     0,     0,   221,   222,
       0,     0,     0,     0,     0,   226,   227,   228,     0,     0,
       0,     0,     0,     0,     0,   231,   232,   233,   234,   235
};

static const yytype_int16 yycheck[] =
{
      16,    17,    91,     0,   172,    79,     4,   142,    76,    89,
      59,    78,    79,   250,   174,    80,   141,   192,   193,   194,
      77,    19,   322,   344,   306,   321,   322,   418,   313,   309,
     211,   321,   322,   321,   322,   321,   322,   517,     0,    19,
      89,   216,    13,   467,    50,    51,   169,    61,    27,    65,
     517,    26,    68,    25,    46,    71,    72,    73,    74,    75,
      76,   178,    64,   255,    80,    81,    82,   208,    46,    71,
      46,    46,    68,    46,    90,    46,    92,    93,    46,   515,
     215,   517,    14,    15,   141,    81,    92,   279,    79,   103,
      82,    64,    64,    51,    79,    51,    92,    73,    73,    46,
      79,    77,    73,    65,   584,    73,    68,    61,   124,    83,
     126,   110,   169,    69,   130,   131,   132,   584,    80,   135,
     544,   137,   138,   139,   140,    61,    73,   125,    90,   103,
      92,    93,    81,   256,    92,    61,    92,   305,   255,   155,
     156,    64,   323,    73,   429,   125,    61,    77,   584,   111,
      61,   103,   432,   589,   439,    47,    50,    51,     0,    51,
      54,   177,   279,    50,    51,    57,    58,   603,   309,    52,
      93,    94,   171,   172,   173,   174,   209,   210,    61,   153,
     321,   322,    93,    94,    76,    61,   160,    66,   150,    61,
      61,   165,   208,   209,   210,   211,   321,   322,    92,    90,
      92,    15,    93,    17,   103,   179,    61,   375,   599,    88,
      89,    90,    46,   209,   210,   211,    47,    64,   518,   103,
      51,    10,   518,     8,    10,   199,    57,    58,   518,   203,
     518,   320,   518,   249,     1,     2,     3,   294,   103,     6,
       7,     8,     9,    10,    11,   103,   528,   209,   210,   247,
     535,    18,    15,    20,    83,   312,   577,   314,   338,    54,
      80,    92,   211,   343,   332,   425,   282,   332,    80,   285,
     286,    77,    66,   289,    77,    66,    10,    82,    45,    46,
      80,    48,    49,    50,    51,    52,   282,   462,    13,   338,
      17,   528,   308,   289,   343,    86,    87,    88,    89,    90,
      60,    11,    12,    80,     9,   440,   305,   323,    18,    19,
      51,    77,   308,    49,    50,    51,   332,    93,   280,    80,
      87,    10,    10,   321,   322,   321,   322,   323,    10,    10,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   533,   321,
     322,   542,   336,   538,   438,   454,   315,   341,   127,   128,
     332,   438,   321,   322,   323,    52,   375,   518,    10,    59,
      77,    10,   331,   382,    47,   382,   145,    10,    51,    10,
      10,   158,    65,   518,    57,    58,   412,   565,    10,   540,
      10,   247,   111,   377,   397,   513,    65,   251,   175,    68,
     276,   393,   394,   196,     0,   196,   280,   430,   540,   286,
     382,    80,   210,   190,   398,   399,   425,   401,   544,    92,
      82,    90,   199,    92,    93,   451,   203,     0,   205,   206,
     207,    92,   399,   282,   401,    -1,   289,    -1,   464,    -1,
      -1,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,    65,
      -1,    -1,    68,   499,    -1,    -1,   575,    -1,    -1,   463,
      -1,    77,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    90,    68,    92,    93,   524,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    -1,    -1,
     518,    -1,    -1,   290,   540,   111,   542,    90,    -1,    92,
      93,   513,   506,   515,    47,    -1,    -1,   296,    51,   298,
     307,   300,    -1,   302,    57,    58,   542,    -1,   111,   316,
     209,   210,    -1,    -1,    -1,   141,   518,    -1,    -1,    -1,
      73,    -1,    -1,    76,   150,    -1,   565,    -1,    -1,   518,
      -1,    -1,   554,    -1,    -1,    88,    -1,   344,   594,    92,
      -1,   555,    -1,   169,    -1,    -1,   560,   150,    -1,    -1,
      -1,    -1,    -1,   542,    -1,    13,    -1,    -1,   555,   548,
     557,    -1,   559,   560,   586,    -1,   169,   589,    -1,    -1,
      -1,    66,    30,    31,    69,    70,    -1,    -1,    -1,    -1,
     379,   603,   596,   209,   210,    -1,    -1,   386,    46,    -1,
      -1,    86,    87,    88,    89,    90,    -1,    -1,   595,   596,
      -1,   598,    -1,    -1,    -1,    -1,   209,   210,    66,   606,
      -1,    69,    70,    -1,    72,    73,    74,    75,    76,    77,
      78,    -1,   421,    -1,    -1,    83,    84,    -1,    86,    87,
      88,    89,    90,   332,    -1,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,    -1,   104,   105,    -1,    -1,
      -1,    -1,    -1,    47,   280,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    57,    58,    -1,   473,    -1,   294,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    -1,   280,    -1,    30,
      31,    -1,    76,    -1,    -1,    -1,   312,    -1,   314,    -1,
     497,   294,    -1,    -1,    88,    46,    -1,   496,    92,    -1,
      -1,    -1,   501,    -1,    -1,    -1,   332,    -1,    -1,    -1,
      -1,   314,    -1,    -1,   521,    66,    -1,    -1,    69,    70,
      -1,    72,    73,    74,    75,    76,    77,    78,    -1,   332,
      47,   530,    83,    84,    51,    86,    87,    88,    89,    90,
      57,    58,    -1,    -1,    95,    96,    97,    98,    99,   100,
     101,   102,    -1,   104,   105,    -1,   382,    46,    47,    76,
      -1,    -1,    51,    -1,    -1,    -1,   392,    -1,    57,    58,
     577,    88,   579,    66,    -1,    92,    69,    70,    -1,   382,
      -1,    -1,    -1,    76,    73,    -1,    -1,    76,    -1,    -1,
      -1,   590,    81,    86,    87,    88,    89,    90,    -1,    88,
      -1,    -1,    -1,    92,    -1,    -1,    -1,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    28,    29,    -1,   438,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    73,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    28,    29,    -1,   552,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    -1,
      -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,
      85,     3,     4,     5,     6,     7,    -1,    92,    -1,    11,
      12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    28,    29,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    79,    -1,    81,
      -1,    -1,    -1,    85,     3,     4,     5,     6,     7,    -1,
      92,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    28,
      29,    -1,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      79,    -1,    81,    11,    12,    -1,    85,    -1,    16,    -1,
      18,    19,    20,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,
      68,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,
      32,    -1,    34,    -1,    92,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    30,    31,
      62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    64,    -1,    66,    -1,    -1,    69,    70,    -1,
      72,    -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    83,    84,    -1,    86,    87,    88,    89,    90,    30,
      31,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,    -1,   104,   105,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,
      -1,    72,    73,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    83,    84,    -1,    86,    87,    88,    89,    90,
      30,    31,    -1,    -1,    95,    96,    97,    98,    99,   100,
     101,   102,    -1,   104,   105,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    30,    31,    69,
      70,    -1,    72,    -1,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    82,    83,    84,    -1,    86,    87,    88,    89,
      90,    -1,    -1,    -1,    -1,    95,    96,    97,    98,    99,
     100,   101,   102,    66,   104,   105,    69,    70,    71,    72,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      83,    84,    -1,    86,    87,    88,    89,    90,    30,    31,
      -1,    -1,    95,    96,    97,    98,    99,   100,   101,   102,
      -1,   104,   105,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    30,    31,    69,    70,    -1,
      72,    -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    83,    84,    -1,    86,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,    66,   104,   105,    69,    70,    -1,    72,    -1,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    83,    84,
      -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,    -1,
      95,    96,    97,    98,    99,   100,   101,   102,    -1,   104,
     105,    32,    -1,    34,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,    -1,
      81,    -1,    -1,    -1,    85,    -1,    -1,    88,    -1,    -1,
      91,    92,    32,    -1,    34,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,
      -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    88,    -1,
      -1,    91,    92,    32,    -1,    34,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    85,    -1,    -1,    88,
      32,    -1,    34,    92,    -1,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    85,    -1,    -1,    32,    -1,    34,    -1,
      92,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    85,
      -1,    -1,    32,    -1,    34,    91,    92,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    32,    -1,
      34,    91,    92,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,    -1,    -1,    88,    32,    -1,    34,    92,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    85,    -1,
      -1,    32,    -1,    34,    -1,    92,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    85,    -1,    -1,    32,    -1,    34,
      91,    92,    37,    38,    39,    40,    41,    42,    43,    44,
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
      -1,    -1,    85,    -1,    -1,    32,    -1,    34,    -1,    92,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    -1,
      51,    52,    53,    54,    55,    -1,    57,    58,    59,    -1,
      -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    92,    47,    48,    49,    -1,    51,    52,    53,    54,
      55,    -1,    57,    58,    59,    -1,    -1,    -1,    63,    -1,
      66,    -1,    -1,    69,    70,    -1,    72,    -1,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    81,    83,    84,    -1,
      86,    87,    88,    89,    90,    -1,    -1,    92,    -1,    95,
      96,    97,    98,    99,   100,   101,   102,    66,   104,   105,
      69,    70,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    83,    84,    -1,    86,    87,    88,
      89,    90,    -1,    -1,    -1,    -1,    95,    96,    97,    98,
      99,   100,   101,   102,    66,   104,   105,    69,    70,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    83,    84,    -1,    86,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    76,    77,    78,    -1,    -1,    -1,    -1,    83,    84,
      -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,    -1,
      95,    96,    97,    98,    99,   100,   101,   102,    66,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,    66,    -1,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,    90
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
     115,   116,   117,   118,   121,   126,   131,   132,   133,   134,
     135,   169,   171,   172,   173,   174,   176,   177,   178,   179,
     183,   185,   187,   205,   208,   209,   212,   213,   214,   217,
     218,   220,   221,   222,   234,    46,   193,   194,   193,   193,
      50,    51,   119,   120,   135,    46,    73,   143,   191,   195,
     196,   197,   193,   193,   193,   193,   193,   193,    50,   132,
     134,   222,   234,   234,   193,   120,   193,    79,    79,   193,
     193,   193,   193,   193,   193,   193,     0,    11,    12,    18,
      19,    61,   223,   224,    52,    27,   145,   146,   147,   148,
     187,   217,   227,   229,   234,    76,    88,    91,   136,   214,
     215,   216,   217,   226,   228,   230,   231,   232,   234,   103,
     219,   234,   234,   234,   234,    17,   165,   175,   234,   205,
     234,    50,   126,   128,   132,    51,    92,   130,   134,   218,
      69,   130,   208,   217,   234,    60,   131,   207,   210,   211,
     214,   234,    80,   215,   234,    64,    93,    94,   182,   189,
     190,   193,   145,   225,   227,   223,   226,   227,    30,    31,
      66,    69,    70,    72,    74,    75,    76,    77,    78,    83,
      84,    86,    87,    88,    89,    90,    95,    96,    97,    98,
      99,   100,   101,   102,   104,   105,    46,   182,    10,     8,
     140,   141,   142,   195,   108,   109,   103,   234,   120,   234,
     191,   191,   234,   234,   234,   234,   234,   234,   234,   234,
      92,   126,   132,   220,   224,    46,   181,   191,    77,   109,
     149,   192,   182,   234,   234,   193,   182,   184,   193,   182,
      71,   126,   133,   134,   103,    13,   167,   195,   167,    26,
     168,   195,   168,   193,    10,   234,   197,    25,   180,   122,
      61,   103,   198,   123,   103,   193,    83,   144,   184,   184,
     184,   189,   190,   182,   186,   193,   188,   193,   193,   193,
     193,    88,   183,   201,   234,   121,   206,   214,   217,   234,
     121,   206,   214,   217,   210,   184,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   119,   161,   162,   163,   234,    15,
     138,   142,   196,   197,    80,    80,   149,    10,    47,    51,
      57,    58,    73,    76,    88,    92,   150,   153,   155,   156,
     157,   158,   159,   160,   197,   192,    80,   231,   234,   216,
      82,   232,   193,   126,   127,   134,   191,    13,   191,   191,
     191,   167,   165,   193,   214,   233,   234,    46,    73,   129,
     152,   153,   183,   199,   126,   143,    92,   131,   193,   124,
     223,    37,    48,    53,    63,   110,   111,   112,   113,   131,
     135,   183,   209,   214,   220,   222,   113,   214,   210,    60,
      80,   131,   200,   205,   182,   145,   145,   186,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   167,    71,   164,   182,
     191,     9,   139,   108,   191,   132,   151,   159,   159,    77,
      77,   150,   154,   182,   154,   182,   154,   182,    93,    80,
     234,    14,   137,   138,   170,   137,    10,    10,   191,    10,
     168,   143,   199,   153,    10,   125,   130,   143,   234,   184,
     182,   234,   185,   202,   203,   204,   193,   191,   193,   234,
     191,    10,   182,    77,    76,   158,   159,   155,   159,   155,
     156,   157,   113,   193,    10,   234,    10,   138,   165,   166,
     191,    10,   184,   143,    10,   184,   201,   210,   204,    65,
     131,   132,   159,   154,   182,   154,   182,   154,   154,   182,
     167,    10,    10,   186,   193,   155,   156,   159,   155,   191,
     234,   154,   154,   182,   154,   137,   155,   154
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
#line 163 "../parser.y"
    { parser->ast = NULL; YYACCEPT; ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 165 "../parser.y"
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
#line 178 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 180 "../parser.y"
    { (yyval.n) = alloc_cond(token_if, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);      ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 181 "../parser.y"
    { (yyval.n) = alloc_cond(token_unless, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);  ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 182 "../parser.y"
    { (yyval.n) = alloc_cond(token_while, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);   ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 183 "../parser.y"
    { (yyval.n) = alloc_cond(token_until, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);   ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 187 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 188 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 191 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 192 "../parser.y"
    { (yyval.n) = alloc_node(token_numeric, NULL, NULL);   ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 193 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 194 "../parser.y"
    { (yyval.n) = alloc_node(token_string, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 195 "../parser.y"
    { (yyval.n) = alloc_node(token_regexp, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 196 "../parser.y"
    { (yyval.n) = alloc_node(token_heredoc, NULL, NULL);   ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 197 "../parser.y"
    { (yyval.n) = alloc_node(token_backtick, NULL, NULL); pop_string(parser, (yyval.n)); ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 198 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);    ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 215 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 216 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 217 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 218 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 221 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 222 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 223 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 226 "../parser.y"
    { (yyval.n) = alloc_node(token_numeric, NULL, NULL);   ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 227 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 228 "../parser.y"
    { (yyval.n) = alloc_node(token_string, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 229 "../parser.y"
    { (yyval.n) = alloc_node(token_regexp, NULL, NULL); pop_string(parser, (yyval.n));   ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 230 "../parser.y"
    { (yyval.n) = alloc_node(token_heredoc, NULL, NULL);   ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 231 "../parser.y"
    { (yyval.n) = alloc_node(token_backtick, NULL, NULL); pop_string(parser, (yyval.n)); ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 232 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 233 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);    ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 236 "../parser.y"
    { (yyval.n) = alloc_node(token_break, NULL, NULL);   ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 237 "../parser.y"
    { (yyval.n) = alloc_node(token_redo, NULL, NULL);    ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 238 "../parser.y"
    { (yyval.n) = alloc_node(token_retry, NULL, NULL);   ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 239 "../parser.y"
    { (yyval.n) = alloc_node(token_next, NULL, NULL);    ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 240 "../parser.y"
    { (yyval.n) = alloc_node(token_undef, (yyvsp[(2) - (2)].n), NULL);     ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 241 "../parser.y"
    { (yyval.n) = alloc_node(token_alias, (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));       ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 242 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 243 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 246 "../parser.y"
    { (yyval.n) = alloc_node(token_yield, NULL, NULL);   ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 247 "../parser.y"
    { (yyval.n) = alloc_node(token_yield, (yyvsp[(2) - (2)].n), NULL);     ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 250 "../parser.y"
    { (yyval.n) = alloc_node(token_return, NULL, NULL);  ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 251 "../parser.y"
    { (yyval.n) = alloc_node(token_return, (yyvsp[(2) - (2)].n), NULL);    ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 254 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 255 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 258 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 259 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 260 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 267 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_if, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
  ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 274 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_unless, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
    ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 280 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_while, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 286 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_until, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 292 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_case, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
    ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 296 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_case, NULL, (yyvsp[(2) - (3)].n), NULL);
    ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 300 "../parser.y"
    {
      (yyval.n) = alloc_node(token_up_begin, (yyvsp[(3) - (4)].n), NULL);
    ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 304 "../parser.y"
    {
      (yyval.n) = alloc_node(token_up_end, (yyvsp[(3) - (4)].n), NULL);
    ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 308 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_for, (yyvsp[(4) - (7)].n), (yyvsp[(6) - (7)].n), (yyvsp[(2) - (7)].n));
    ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 312 "../parser.y"
    {
      (yyval.n) = (yyvsp[(2) - (3)].n);
      (yyval.n)->kind = token_exception;
    ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 317 "../parser.y"
    {
      parser->in_def++;
    ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 321 "../parser.y"
    {
      parser->in_def--;
      (yyval.n) = alloc_cond(token_function, (yyvsp[(2) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(4) - (6)].n));
    ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 326 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "module definition in method body");
    ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 332 "../parser.y"
    {
      (yyval.n) = alloc_node(token_module, (yyvsp[(4) - (5)].n), (yyvsp[(2) - (5)].n));
    ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 336 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 342 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_class, (yyvsp[(3) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(2) - (6)].n));
    ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 346 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 352 "../parser.y"
    {
      (yyval.n) = alloc_node(token_singleton_class, (yyvsp[(6) - (7)].n), (yyvsp[(4) - (7)].n));
    ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 357 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 358 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 361 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 362 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 365 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 366 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 369 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 370 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 373 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 374 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 376 "../parser.y"
    {
    yyerror(parser, "class/module name must be CONSTANT");
  ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 381 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 382 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 383 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 384 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 385 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 388 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 391 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 394 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 397 "../parser.y"
    { (yyval.n) = alloc_node(token_symbol, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 400 "../parser.y"
    { (yyval.n) = alloc_node(token_symbol, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 407 "../parser.y"
    {
      (yyval.n) = alloc_cond(token_if, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
    ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 412 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 413 "../parser.y"
    { (yyval.n) = alloc_cond(token_if, NULL, (yyvsp[(2) - (2)].n), NULL);  ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 416 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 417 "../parser.y"
    { (yyval.n) = alloc_node(token_ensure, (yyvsp[(2) - (2)].n), NULL); ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 420 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 421 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 424 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 425 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 429 "../parser.y"
    {
    (yyval.n) = alloc_node(token_rescue, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 435 "../parser.y"
    {
    (yyval.n) = alloc_ensure(token_body, (yyvsp[(1) - (4)].n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 440 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 441 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 444 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 445 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 448 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 449 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 453 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(3) - (4)].n), (yyvsp[(2) - (4)].n));
  ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 457 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 463 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(4) - (5)].n), (yyvsp[(3) - (5)].n));
  ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 467 "../parser.y"
    {
    (yyval.n) = alloc_node(token_block, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 473 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n));
  ;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 477 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, NULL, (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 481 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);
  ;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 486 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 489 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);  ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 491 "../parser.y"
    {
    (yyval.n) = update_list((yyvsp[(1) - (3)].n), alloc_node(token_object, NULL, NULL));
  ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 496 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 497 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 500 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 501 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 503 "../parser.y"
    {
      (yyval.n) = create_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 506 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 508 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 511 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 513 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), create_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 517 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 521 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 525 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 530 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (8)].n), concat_list((yyvsp[(3) - (8)].n), create_list((yyvsp[(5) - (8)].n), update_list((yyvsp[(7) - (8)].n), (yyvsp[(8) - (8)].n)))));
    ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 534 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 539 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 540 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 543 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 544 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 547 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 550 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 553 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 554 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 557 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 558 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 562 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a constant");
    (yyval.n) = 0;
  ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 567 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be an instance variable");
    (yyval.n) = 0;
  ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 572 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a global variable");
    (yyval.n) = 0;
  ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 577 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a class variable");
    (yyval.n) = 0;
  ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 583 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 584 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 588 "../parser.y"
    {
    (yyval.n) = alloc_node(token_rescue_arg, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 593 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 594 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 597 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 598 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  ;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 602 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_when, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
  ;}
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 687 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 688 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 691 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 722 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 723 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 727 "../parser.y"
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

  case 219:

/* Line 1464 of yacc.c  */
#line 736 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);  ;}
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 737 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 738 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL);  ;}
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 741 "../parser.y"
    { (yyval.n) = 0; ;}
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 742 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 745 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 746 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 749 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n); ;}
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 752 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 753 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  ;}
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 754 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 757 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 758 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 761 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 762 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 763 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 764 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 767 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    ;}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 768 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 770 "../parser.y"
    {
    (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 775 "../parser.y"
    {
    (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 779 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     ;}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 780 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 781 "../parser.y"
    { (yyval.n) = alloc_node(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     ;}
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 782 "../parser.y"
    { (yyval.n) = alloc_node(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 785 "../parser.y"
    { (yyval.n) = alloc_node(token_array, NULL, NULL); ;}
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 786 "../parser.y"
    { (yyval.n) = alloc_node(token_array, (yyvsp[(2) - (3)].n), NULL);   ;}
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 787 "../parser.y"
    { (yyval.n) = alloc_node(token_array, NULL, NULL); ;}
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 791 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 792 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 793 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 796 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 797 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 801 "../parser.y"
    {
    struct node * n = (yyvsp[(3) - (5)].n);
    n->next = (yyvsp[(5) - (5)].n);
    (yyval.n) = alloc_node(token_array_value, (yyvsp[(1) - (5)].n), n);
  ;}
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 812 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 815 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, NULL, NULL);  ;}
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 816 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, (yyvsp[(2) - (3)].n), NULL);    ;}
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 819 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 820 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 823 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 824 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  ;}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 828 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 832 "../parser.y"
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

  case 262:

/* Line 1464 of yacc.c  */
#line 841 "../parser.y"
    { (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 845 "../parser.y"
    {
    struct node * n = alloc_node(token_object, (yyvsp[(1) - (2)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 850 "../parser.y"
    {
    struct node * n = alloc_node(token_object, (yyvsp[(1) - (3)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(3) - (3)].n));
  ;}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 856 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 857 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 861 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 865 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (3)].n), (yyvsp[(2) - (3)].n));
  ;}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 870 "../parser.y"
    { (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 874 "../parser.y"
    {
    struct node * n = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 879 "../parser.y"
    {
    struct node * n = alloc_node(token_method_call, (yyvsp[(2) - (4)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(4) - (4)].n));
  ;}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 884 "../parser.y"
    {
    (yyval.n) = pop_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  ;}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 889 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); ;}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 890 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 894 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 0;
  ;}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 899 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 1;
  ;}
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 905 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 906 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 279:

/* Line 1464 of yacc.c  */
#line 909 "../parser.y"
    { (yyval.n) = 0;   ;}
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 910 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 913 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 914 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 917 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 284:

/* Line 1464 of yacc.c  */
#line 918 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 922 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 923 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 287:

/* Line 1464 of yacc.c  */
#line 926 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 927 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); ;}
    break;

  case 289:

/* Line 1464 of yacc.c  */
#line 931 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 932 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 933 "../parser.y"
    { (yyval.n) = alloc_node(token_hash, (yyvsp[(1) - (1)].n), NULL);  ;}
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 936 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 937 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 938 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  ;}
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 942 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 943 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 946 "../parser.y"
    { (yyval.n) = alloc_node(token_plus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 947 "../parser.y"
    { (yyval.n) = alloc_node(token_minus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 948 "../parser.y"
    { (yyval.n) = alloc_node(token_mul, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 949 "../parser.y"
    { (yyval.n) = alloc_node(token_div, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 950 "../parser.y"
    { (yyval.n) = alloc_node(token_mod, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 951 "../parser.y"
    { (yyval.n) = alloc_node(token_exp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 303:

/* Line 1464 of yacc.c  */
#line 952 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 953 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 305:

/* Line 1464 of yacc.c  */
#line 954 "../parser.y"
    { (yyval.n) = alloc_node(token_bit_xor, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 306:

/* Line 1464 of yacc.c  */
#line 955 "../parser.y"
    { (yyval.n) = alloc_node(token_lshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 956 "../parser.y"
    { (yyval.n) = alloc_node(token_rshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 308:

/* Line 1464 of yacc.c  */
#line 957 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 309:

/* Line 1464 of yacc.c  */
#line 958 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 310:

/* Line 1464 of yacc.c  */
#line 959 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  ;}
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 960 "../parser.y"
    { (yyval.n) = alloc_node(token_cmp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 312:

/* Line 1464 of yacc.c  */
#line 961 "../parser.y"
    { (yyval.n) = alloc_node(token_eq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      ;}
    break;

  case 313:

/* Line 1464 of yacc.c  */
#line 962 "../parser.y"
    { (yyval.n) = alloc_node(token_neq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 314:

/* Line 1464 of yacc.c  */
#line 963 "../parser.y"
    { (yyval.n) = alloc_node(token_eqq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 315:

/* Line 1464 of yacc.c  */
#line 964 "../parser.y"
    { (yyval.n) = alloc_node(token_match, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 965 "../parser.y"
    { (yyval.n) = alloc_node(token_nmatch, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 966 "../parser.y"
    { (yyval.n) = alloc_node(token_greater, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); ;}
    break;

  case 318:

/* Line 1464 of yacc.c  */
#line 967 "../parser.y"
    { (yyval.n) = alloc_node(token_lesser, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 319:

/* Line 1464 of yacc.c  */
#line 968 "../parser.y"
    { (yyval.n) = alloc_node(token_geq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 969 "../parser.y"
    { (yyval.n) = alloc_node(token_leq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 321:

/* Line 1464 of yacc.c  */
#line 970 "../parser.y"
    { (yyval.n) = alloc_node(token_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      ;}
    break;

  case 322:

/* Line 1464 of yacc.c  */
#line 971 "../parser.y"
    { (yyval.n) = alloc_node(token_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     ;}
    break;

  case 323:

/* Line 1464 of yacc.c  */
#line 972 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   ;}
    break;

  case 324:

/* Line 1464 of yacc.c  */
#line 973 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  ;}
    break;

  case 325:

/* Line 1464 of yacc.c  */
#line 974 "../parser.y"
    { (yyval.n) = alloc_node(token_dot2, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 326:

/* Line 1464 of yacc.c  */
#line 975 "../parser.y"
    { (yyval.n) = alloc_node(token_dot3, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    ;}
    break;

  case 327:

/* Line 1464 of yacc.c  */
#line 977 "../parser.y"
    {
    (yyval.n) = alloc_cond(token_ternary, (yyvsp[(1) - (8)].n), (yyvsp[(4) - (8)].n), (yyvsp[(8) - (8)].n));
  ;}
    break;

  case 328:

/* Line 1464 of yacc.c  */
#line 980 "../parser.y"
    { (yyval.n) = alloc_node(token_kw_not, (yyvsp[(3) - (3)].n), NULL);;}
    break;

  case 329:

/* Line 1464 of yacc.c  */
#line 981 "../parser.y"
    { (yyval.n) = alloc_node(token_neg, (yyvsp[(3) - (3)].n), NULL);   ;}
    break;

  case 330:

/* Line 1464 of yacc.c  */
#line 982 "../parser.y"
    { (yyval.n) = alloc_node(token_not, (yyvsp[(3) - (3)].n), NULL);   ;}
    break;

  case 331:

/* Line 1464 of yacc.c  */
#line 983 "../parser.y"
    { (yyval.n) = alloc_node(token_unary_plus, (yyvsp[(3) - (3)].n), NULL);  ;}
    break;

  case 332:

/* Line 1464 of yacc.c  */
#line 984 "../parser.y"
    { (yyval.n) = alloc_node(token_unary_minus, (yyvsp[(3) - (3)].n), NULL); ;}
    break;

  case 333:

/* Line 1464 of yacc.c  */
#line 985 "../parser.y"
    { (yyval.n) = alloc_node(token_defined, (yyvsp[(3) - (3)].n), NULL);     ;}
    break;

  case 334:

/* Line 1464 of yacc.c  */
#line 986 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); ;}
    break;

  case 335:

/* Line 1464 of yacc.c  */
#line 987 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n)   ;}
    break;

  case 336:

/* Line 1464 of yacc.c  */
#line 988 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  ;}
    break;

  case 337:

/* Line 1464 of yacc.c  */
#line 989 "../parser.y"
    { (yyval.n) = alloc_node(token_object, NULL, NULL); pop_stack(parser, (yyval.n)); ;}
    break;



/* Line 1464 of yacc.c  */
#line 4615 "../parser.c"
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
#line 992 "../parser.y"

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


