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


/* Line 268 of yacc.c  */
#line 194 "../parser.c"

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
     tCOLON3 = 348,
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
     tCOLON2 = 359,
     tDOT3 = 360,
     tDOT2 = 361
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 152 "../parser.y"
  struct node * n;  


/* Line 293 of yacc.c  */
#line 340 "../parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 352 "../parser.c"

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
#define YYFINAL  139
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2746

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  138
/* YYNRULES -- Number of rules.  */
#define YYNRULES  357
/* YYNRULES -- Number of states.  */
#define YYNSTATES  645

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
      22,    26,    30,    34,    36,    38,    42,    44,    46,    48,
      50,    52,    54,    56,    58,    60,    62,    64,    66,    68,
      70,    72,    74,    76,    79,    81,    83,    85,    87,    89,
      91,    93,    95,    97,    99,   101,   103,   105,   107,   109,
     111,   113,   115,   117,   120,   124,   126,   128,   130,   133,
     135,   138,   140,   144,   146,   148,   150,   157,   164,   170,
     176,   182,   186,   191,   196,   204,   208,   209,   216,   217,
     225,   226,   232,   233,   239,   240,   247,   248,   256,   258,
     260,   262,   264,   268,   270,   274,   276,   279,   281,   283,
     285,   287,   289,   291,   293,   295,   297,   299,   301,   303,
     305,   307,   309,   315,   316,   319,   320,   323,   324,   326,
     328,   331,   336,   341,   345,   346,   348,   350,   352,   357,
     361,   367,   371,   373,   377,   380,   385,   392,   397,   401,
     405,   408,   410,   414,   416,   419,   423,   428,   431,   436,
     439,   444,   447,   454,   459,   466,   471,   480,   487,   488,
     492,   494,   498,   501,   505,   507,   511,   513,   515,   517,
     519,   521,   523,   524,   526,   529,   531,   535,   536,   540,
     546,   548,   550,   552,   554,   557,   559,   561,   563,   566,
     568,   570,   572,   574,   577,   580,   583,   586,   589,   592,
     595,   598,   601,   604,   607,   608,   610,   613,   616,   619,
     622,   625,   628,   631,   634,   637,   641,   643,   646,   647,
     649,   651,   654,   656,   658,   660,   663,   664,   666,   668,
     670,   672,   674,   678,   681,   683,   687,   690,   692,   693,
     695,   697,   700,   704,   706,   709,   713,   715,   719,   723,
     727,   731,   735,   739,   743,   748,   753,   757,   761,   765,
     769,   772,   776,   778,   780,   782,   784,   786,   789,   793,
     799,   801,   804,   808,   810,   813,   817,   822,   826,   829,
     832,   835,   838,   842,   846,   849,   853,   857,   861,   865,
     868,   873,   876,   878,   881,   884,   887,   888,   890,   892,
     894,   896,   898,   900,   904,   906,   910,   912,   914,   916,
     918,   920,   922,   924,   927,   930,   932,   934,   939,   944,
     949,   954,   959,   964,   969,   974,   979,   984,   989,   993,
     997,  1001,  1006,  1011,  1016,  1021,  1026,  1031,  1036,  1041,
    1046,  1051,  1056,  1061,  1066,  1071,  1076,  1081,  1090,  1094,
    1098,  1102,  1106,  1110,  1114,  1117,  1119,  1121
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     108,     0,    -1,    46,    -1,   109,    -1,   117,    -1,   122,
      -1,   218,    -1,   227,   149,    -1,   224,    -1,   109,   176,
     244,    -1,   109,   177,   244,    -1,   109,   178,   244,    -1,
     109,   179,   244,    -1,   244,    -1,   109,    -1,   110,   206,
     109,    -1,   135,    -1,    48,    -1,   139,    -1,   113,    -1,
      53,    -1,    37,    -1,    63,    -1,   112,    -1,    39,    -1,
      38,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    52,    -1,   113,    52,    -1,   111,
      -1,   219,    -1,   230,    -1,   232,    -1,   135,    -1,   230,
      -1,   232,    -1,    48,    -1,   139,    -1,   113,    -1,    53,
      -1,    37,    -1,    63,    -1,   219,    -1,   112,    -1,    21,
      -1,    23,    -1,    24,    -1,    22,    -1,     6,   120,    -1,
      33,   121,   121,    -1,   118,    -1,   119,    -1,    29,    -1,
      29,   244,    -1,    28,    -1,    28,   244,    -1,   121,    -1,
     121,   192,   120,    -1,    51,    -1,    50,    -1,   139,    -1,
     175,   244,   172,   201,   141,    10,    -1,   181,   244,   172,
     201,   141,    10,    -1,   182,   244,   173,   201,    10,    -1,
     183,   244,   173,   201,    10,    -1,   184,   244,   207,   170,
      10,    -1,   184,   170,    10,    -1,    35,    79,   201,    80,
      -1,    36,    79,   201,    80,    -1,   186,   215,   190,   243,
     173,   201,    10,    -1,     7,   147,    10,    -1,    -1,   187,
     131,   123,   133,   147,    10,    -1,    -1,   187,   132,   124,
     157,    82,   147,    10,    -1,    -1,   188,   134,   125,   147,
      10,    -1,    -1,   189,   134,   126,   147,    10,    -1,    -1,
     189,   134,   148,   127,   147,    10,    -1,    -1,   189,    69,
     240,   128,   205,   147,    10,    -1,    50,    -1,   136,    -1,
     129,    -1,   138,    -1,   136,   208,   129,    -1,   129,    -1,
     136,   208,   137,    -1,   137,    -1,   157,   209,    -1,   209,
      -1,    92,    -1,   228,    -1,    51,    -1,   136,    -1,    47,
      -1,    58,    -1,    57,    -1,    92,    -1,    51,    -1,    54,
      -1,    92,    -1,    49,    -1,    91,    -1,   142,    -1,   180,
     244,   172,   201,   141,    -1,    -1,    15,   201,    -1,    -1,
       9,   201,    -1,    -1,   145,    -1,   146,    -1,   145,   146,
      -1,     8,   166,   172,   201,    -1,   201,   144,   142,   143,
      -1,    83,   203,   134,    -1,    -1,   150,    -1,   151,    -1,
     152,    -1,   197,   154,   202,    80,    -1,   197,   202,    80,
      -1,   174,   191,   154,   201,    10,    -1,   174,   201,    10,
      -1,   158,    -1,   192,    76,   164,    -1,   160,   192,    -1,
     160,   192,   161,   159,    -1,   160,   192,   161,   192,   160,
     159,    -1,    77,   153,   155,    77,    -1,    77,   155,    77,
      -1,    77,   153,    77,    -1,    73,   156,    -1,   136,    -1,
     156,   192,   136,    -1,   158,    -1,    76,   164,    -1,   193,
     158,   194,    -1,   193,    76,   164,   194,    -1,   160,   159,
      -1,   161,   192,   160,   159,    -1,   161,   159,    -1,   163,
     192,   160,   159,    -1,   163,   159,    -1,   163,   192,   161,
     192,   160,   159,    -1,   163,   192,   161,   159,    -1,   160,
     192,   163,   192,   160,   159,    -1,   160,   192,   163,   159,
      -1,   160,   192,   163,   192,   161,   192,   160,   159,    -1,
     160,   192,   163,   192,   161,   159,    -1,    -1,   192,    76,
     164,    -1,   164,    -1,   160,   192,   164,    -1,    88,   164,
      -1,   164,    94,   114,    -1,   162,    -1,   163,   192,   162,
      -1,    51,    -1,   165,    -1,    92,    -1,    57,    -1,    58,
      -1,    47,    -1,    -1,   167,    -1,   168,   169,    -1,   244,
      -1,   168,   192,   244,    -1,    -1,    71,   203,   135,    -1,
     185,   244,   172,   201,   171,    -1,   142,    -1,   170,    -1,
     205,    -1,    13,    -1,   205,    13,    -1,   205,    -1,    26,
      -1,    27,    -1,    11,   203,    -1,    11,    -1,    12,    -1,
      18,    -1,    19,    -1,    14,   203,    -1,    12,   203,    -1,
      18,   203,    -1,    19,   203,    -1,    16,   203,    -1,    17,
     203,    -1,    20,   203,    -1,     5,   203,    -1,     4,   203,
      -1,     3,   203,    -1,    25,   203,    -1,    -1,    46,    -1,
      64,   203,    -1,    81,   203,    -1,   203,    82,    -1,    59,
     203,    -1,   203,    60,    -1,    79,   203,    -1,   203,    80,
      -1,    94,   203,    -1,    95,   203,    -1,   207,   110,   207,
      -1,   207,    -1,   110,   207,    -1,    -1,   204,    -1,    46,
      -1,   204,    46,    -1,    73,    -1,    46,    -1,   205,    -1,
     206,   205,    -1,    -1,   206,    -1,    61,    -1,   104,    -1,
      46,    -1,    73,    -1,   215,   192,   211,    -1,   215,   192,
      -1,   244,    -1,   193,   210,   194,    -1,    88,   135,    -1,
      88,    -1,    -1,   213,    -1,   214,    -1,   213,   214,    -1,
     195,   220,   196,    -1,   244,    -1,   215,   192,    -1,   215,
     192,   211,    -1,   244,    -1,   216,   192,   244,    -1,   135,
     199,   114,    -1,   135,   200,   114,    -1,   135,   199,   224,
      -1,   135,   200,   224,    -1,   215,   199,   216,    -1,   215,
     200,   216,    -1,   215,   199,   227,   149,    -1,   215,   200,
     227,   149,    -1,   215,   199,   224,    -1,   215,   200,   224,
      -1,   215,   199,   122,    -1,   215,   200,   122,    -1,   195,
      60,    -1,   195,   221,   196,    -1,    55,    -1,   244,    -1,
     217,    -1,   224,    -1,   220,    -1,   221,   192,    -1,   221,
     192,   220,    -1,   223,   203,   220,   196,   212,    -1,    56,
      -1,   197,    80,    -1,   197,   225,   198,    -1,   226,    -1,
     225,   192,    -1,   225,   192,   226,    -1,   244,    71,   203,
     244,    -1,   140,   203,   244,    -1,   129,   236,    -1,   232,
     236,    -1,   228,   236,    -1,   138,   229,    -1,   138,   104,
     129,    -1,    93,   138,   229,    -1,   104,   138,    -1,   229,
     104,   130,    -1,   137,   235,   194,    -1,   231,   235,   194,
      -1,   138,   104,   137,    -1,   111,   233,    -1,   193,   244,
     194,   233,    -1,   230,   233,    -1,   234,    -1,   233,   234,
      -1,    61,   129,    -1,    61,   230,    -1,    -1,   237,    -1,
     227,    -1,   238,    -1,   227,    -1,   239,    -1,   244,    -1,
     238,   192,   241,    -1,   242,    -1,   239,   192,   242,    -1,
     244,    -1,   224,    -1,   244,    -1,   228,    -1,   224,    -1,
     225,    -1,   241,    -1,    76,   244,    -1,    88,   244,    -1,
     244,    -1,   224,    -1,   244,    86,   203,   244,    -1,   244,
      87,   203,   244,    -1,   244,    88,   203,   244,    -1,   244,
      89,   203,   244,    -1,   244,    90,   203,   244,    -1,   244,
      66,   203,   244,    -1,   244,    76,   203,   244,    -1,   244,
      77,   203,   244,    -1,   244,    78,   203,   244,    -1,   244,
      69,   203,   244,    -1,   244,    70,   203,   244,    -1,   193,
     244,   194,    -1,   193,   218,   194,    -1,   193,   227,   194,
      -1,   244,    96,   203,   244,    -1,   244,    97,   203,   244,
      -1,   244,    99,   203,   244,    -1,   244,    98,   203,   244,
      -1,   244,   100,   203,   244,    -1,   244,   101,   203,   244,
      -1,   244,    84,   203,   244,    -1,   244,    83,   203,   244,
      -1,   244,   102,   203,   244,    -1,   244,   103,   203,   244,
      -1,   244,    74,   203,   244,    -1,   244,    75,   203,   244,
      -1,   244,    31,   203,   244,    -1,   244,    30,   203,   244,
      -1,   244,   106,   203,   244,    -1,   244,   105,   203,   244,
      -1,   244,    72,   203,   244,   203,    65,   203,   244,    -1,
      32,   203,   244,    -1,    62,   203,   244,    -1,    85,   203,
     244,    -1,    68,   203,   244,    -1,    67,   203,   244,    -1,
      34,   203,   244,    -1,   115,   149,    -1,   116,    -1,   222,
      -1,    50,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   208,   208,   209,   220,   221,   222,   223,   228,   229,
     230,   231,   232,   233,   236,   237,   240,   241,   242,   243,
     248,   249,   250,   251,   254,   255,   256,   257,   258,   259,
     260,   261,   264,   265,   272,   273,   274,   275,   278,   279,
     280,   283,   284,   285,   290,   291,   292,   293,   294,   297,
     298,   299,   300,   301,   302,   303,   304,   307,   308,   311,
     312,   315,   316,   319,   320,   321,   324,   332,   340,   347,
     354,   361,   366,   372,   378,   384,   390,   389,   400,   399,
     410,   409,   421,   420,   432,   431,   443,   442,   456,   457,
     460,   461,   464,   469,   472,   477,   480,   481,   484,   485,
     486,   492,   493,   494,   495,   496,   499,   502,   505,   508,
     511,   514,   515,   527,   528,   538,   539,   549,   550,   553,
     554,   557,   567,   580,   583,   584,   587,   588,   591,   601,
     613,   627,   643,   644,   645,   646,   650,   656,   661,   666,
     673,   676,   677,   680,   681,   682,   683,   686,   687,   691,
     692,   696,   697,   701,   705,   709,   713,   718,   724,   725,
     728,   729,   732,   735,   742,   743,   746,   747,   750,   755,
     760,   765,   772,   773,   776,   787,   788,   791,   792,   795,
     805,   806,   809,   810,   811,   814,   815,   825,   838,   841,
     844,   847,   850,   853,   856,   859,   862,   865,   868,   871,
     874,   877,   880,   883,   886,   887,   890,   893,   896,   899,
     902,   905,   908,   911,   914,   917,   918,   921,   924,   925,
     928,   929,   932,   933,   936,   937,   940,   941,   944,   945,
     948,   949,   952,   953,   956,   966,   975,   976,   986,   987,
     990,   991,   994,   997,   998,   999,  1002,  1003,  1006,  1007,
    1008,  1009,  1012,  1013,  1014,  1020,  1026,  1027,  1028,  1029,
    1032,  1033,  1034,  1038,  1039,  1040,  1043,  1044,  1045,  1048,
    1069,  1077,  1083,  1091,  1092,  1093,  1096,  1101,  1108,  1119,
    1129,  1144,  1154,  1160,  1172,  1173,  1176,  1189,  1204,  1207,
    1217,  1227,  1233,  1234,  1237,  1242,  1249,  1250,  1253,  1254,
    1261,  1262,  1266,  1267,  1270,  1271,  1274,  1275,  1279,  1280,
    1281,  1282,  1293,  1294,  1295,  1299,  1300,  1303,  1304,  1305,
    1306,  1307,  1308,  1309,  1310,  1311,  1312,  1313,  1314,  1315,
    1316,  1317,  1318,  1319,  1320,  1321,  1322,  1323,  1324,  1325,
    1326,  1327,  1328,  1329,  1330,  1331,  1332,  1333,  1337,  1338,
    1339,  1340,  1341,  1342,  1343,  1344,  1345,  1346
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
  "tDIV", "tMOD", "KEY", "CONST", "tCOLON3", "tASGN", "tOP_ASGN", "tCMP",
  "tEQ", "tEQQ", "tNEQ", "tMATCH", "tNMATCH", "tGEQ", "tLEQ", "tCOLON2",
  "tDOT3", "tDOT2", "$accept", "parser_start", "stmt", "stmts", "basic",
  "other_keywords", "string", "primary", "primary1", "primary2",
  "simple_stmt", "yield_stmt", "return_stmt", "item_list", "item",
  "cmpd_stmt", "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "fname",
  "fname_or_const", "single_name", "single_name_mcall", "function_args",
  "module_name", "variable", "base", "mcall", "const", "symbol", "key",
  "if_tail", "opt_else", "opt_ensure", "opt_rescue", "rescue_list",
  "rescue_item", "bodystmt", "superclass", "opt_lambda_body",
  "lambda_body", "brace_block", "do_block", "block_params", "block_args",
  "bv_decls", "block_list", "f_arglist", "f_arguments", "f_blockarg",
  "f_args", "f_restarg", "f_opt", "f_optarg", "arg", "f_bad_arg",
  "opt_rescue_arg", "rescue_arg", "exc_list", "exc_var", "case_body",
  "cases", "then", "do", "k_do_block", "k_if", "m_if", "m_unless",
  "m_while", "m_until", "k_elsif", "k_unless", "k_while", "k_until",
  "k_case", "k_when", "k_for", "k_def", "k_module", "k_class", "k_in",
  "endl", "comma", "lparen", "rparen", "lbracket", "rbracket", "lbrace",
  "rbrace", "asgn", "op_asgn", "compstmt", "not_empty_compstmt",
  "opt_eol_list", "eol_list", "term", "terms", "opt_terms", "dot_or_scope",
  "eol_or_semicolon", "lhs_list", "lhs", "opt_bracket_list",
  "bracket_list", "bracket_item", "mlhs", "mrhs", "simple_assign",
  "assign", "array", "array_exp", "array_items", "array_value", "sary",
  "hash", "hash_items", "hash_item", "method_call", "const_scope",
  "scope_items", "paren_method_call", "const_mcall", "dot_method_call",
  "dot_items", "dot_item", "opt_call_args_paren", "m_call_args",
  "m_call_args_paren", "call_args", "call_args_paren", "exp_or_hash",
  "exp_hash", "exp_paren", "exp_for", "exp", 0
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
     109,   109,   109,   109,   110,   110,   111,   111,   111,   111,
     111,   111,   111,   111,   112,   112,   112,   112,   112,   112,
     112,   112,   113,   113,   114,   114,   114,   114,   115,   115,
     115,   116,   116,   116,   116,   116,   116,   116,   116,   117,
     117,   117,   117,   117,   117,   117,   117,   118,   118,   119,
     119,   120,   120,   121,   121,   121,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   123,   122,   124,   122,
     125,   122,   126,   122,   127,   122,   128,   122,   129,   129,
     130,   130,   131,   131,   132,   132,   133,   133,   134,   134,
     134,   135,   135,   135,   135,   135,   136,   137,   138,   139,
     140,   141,   141,   142,   142,   143,   143,   144,   144,   145,
     145,   146,   147,   148,   149,   149,   150,   150,   151,   151,
     152,   152,   153,   153,   153,   153,   153,   154,   154,   154,
     155,   156,   156,   157,   157,   157,   157,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   159,   159,
     160,   160,   161,   162,   163,   163,   164,   164,   165,   165,
     165,   165,   166,   166,   167,   168,   168,   169,   169,   170,
     171,   171,   172,   172,   172,   173,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   201,   202,   203,   203,
     204,   204,   205,   205,   206,   206,   207,   207,   208,   208,
     209,   209,   210,   210,   211,   211,   211,   211,   212,   212,
     213,   213,   214,   215,   215,   215,   216,   216,   217,   217,
     217,   217,   218,   218,   218,   218,   218,   218,   218,   218,
     219,   219,   219,   220,   220,   220,   221,   221,   221,   222,
     223,   224,   224,   225,   225,   225,   226,   226,   227,   227,
     227,   228,   228,   228,   229,   229,   230,   230,   231,   232,
     232,   232,   233,   233,   234,   234,   235,   235,   236,   236,
     237,   237,   238,   238,   239,   239,   240,   240,   241,   241,
     241,   241,   242,   242,   242,   243,   243,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244
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
       5,     3,     4,     4,     7,     3,     0,     6,     0,     7,
       0,     5,     0,     5,     0,     6,     0,     7,     1,     1,
       1,     1,     3,     1,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     0,     2,     0,     2,     0,     1,     1,
       2,     4,     4,     3,     0,     1,     1,     1,     4,     3,
       5,     3,     1,     3,     2,     4,     6,     4,     3,     3,
       2,     1,     3,     1,     2,     3,     4,     2,     4,     2,
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
       2,     3,     1,     1,     1,     1,     1,     2,     3,     5,
       1,     2,     3,     1,     2,     3,     4,     3,     2,     2,
       2,     2,     3,     3,     2,     3,     3,     3,     3,     2,
       4,     2,     1,     2,     2,     2,     0,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     3,
       3,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     8,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   218,   218,   218,     0,   226,   218,   218,   218,   218,
     218,   218,    49,    52,    50,    51,    59,    57,   218,     0,
     218,     0,     0,    45,    25,    24,    26,    27,    28,    29,
      30,    31,     2,   102,    41,   109,   357,   106,    32,    44,
     107,   262,   270,   104,   103,   218,   218,    46,   218,   218,
     218,   218,   218,   105,     0,     0,     3,     0,    48,    43,
     124,   355,     4,    55,    56,     5,     0,    38,   101,   296,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    47,   356,   218,     8,
     124,     0,    39,   296,    40,    13,   220,   202,   219,   201,
     200,    64,    63,    53,    61,    65,   223,   222,     0,   117,
     224,   227,   216,   188,   194,   197,   195,   196,   199,   357,
     101,     0,    40,    60,    58,     0,     0,     0,   226,   226,
     209,     0,     0,     0,   211,   207,     0,   108,     0,     1,
     189,   190,   191,   192,     0,     0,     0,     0,     0,   289,
     292,    33,   187,   354,   125,   126,   127,   226,     0,   298,
     278,   299,   302,     0,     0,   110,   218,   310,   311,   273,
     300,   309,   218,   297,   301,   312,   304,   308,     0,   281,
       0,     0,     0,     0,   218,     0,     0,   226,     0,   243,
      88,    93,    76,    78,    89,    95,   100,    98,    80,     0,
      99,     0,    82,   218,   218,   243,   260,    38,   264,   266,
     218,   265,   263,   271,   218,     0,   218,   218,   218,   244,
       0,     0,     0,     7,   280,   291,   218,   279,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   221,     0,    75,   172,
     113,   118,   119,   225,    14,   226,     0,   348,    54,   353,
       0,     0,   349,   352,   351,   350,     0,   283,     9,    10,
      11,    12,   294,    89,   295,   293,   223,     0,     0,     0,
     226,     0,     0,     0,   313,   314,     0,   274,   286,     0,
       0,   218,   282,   288,   284,     0,   183,   226,   182,   226,
     186,   226,   185,   226,   198,    71,     0,     0,   218,     0,
       0,     0,   228,   229,     0,   226,     0,   307,    86,   306,
     218,   226,    84,   329,   330,   328,     0,     0,   267,   261,
       0,   272,     0,   206,   213,   214,   237,     0,   245,   234,
     258,   252,   256,   124,   246,   259,   253,   257,   124,   218,
     287,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    62,
       0,   173,   177,   175,   226,   115,   120,   227,   215,    72,
      73,   226,   131,   171,   166,   169,   170,     0,     0,   168,
       0,     0,   132,   158,   158,   164,   158,   160,   167,     0,
     217,     0,   129,   309,   303,   277,   275,   208,   305,     0,
      90,   285,    91,   113,   184,   113,     0,     0,   226,     0,
     203,   316,     0,   315,   230,   231,     0,   226,     0,   143,
     158,     0,    97,     0,    92,    94,     0,     0,     0,     0,
     226,   290,    21,    17,    20,    22,    34,    23,    19,   248,
      16,    18,     0,    35,   250,    36,    37,   249,   251,   268,
     210,   212,   105,   236,   218,     0,     0,   254,   255,   238,
     344,   343,   322,   326,   327,   218,   341,   342,   323,   324,
     325,   338,   337,   317,   318,   319,   320,   321,   331,   332,
     334,   333,   335,   336,   339,   340,   346,   345,   226,   218,
     174,     0,   114,   226,   122,    15,     0,   141,   140,   162,
     139,     0,   138,   147,   134,   149,     0,   151,     0,     0,
       0,   128,   276,   218,     0,   111,     0,     0,    68,    69,
     113,    70,   226,   144,     0,    96,     0,     0,   218,   226,
      81,   226,   123,    83,     0,   218,   235,   244,   247,     0,
     269,   239,   240,     0,   121,     0,   176,   116,   130,     0,
     137,     0,   158,   158,   161,   158,   160,   158,   158,   165,
     163,   133,   193,    66,     0,    67,   180,   181,   179,     0,
      77,   218,   145,     0,     0,    85,     0,   245,   218,   241,
     218,   178,   142,   159,   135,     0,   155,     0,   148,     0,
     150,   153,     0,   226,    74,   146,    79,    87,   242,     0,
     158,   158,   158,   161,   158,   113,   347,   136,   154,   157,
       0,   152,   112,   158,   156
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    55,   264,   290,    57,    58,    59,   469,    60,    61,
      62,    63,    64,   103,   104,    65,   320,   321,   325,   331,
     460,   457,    66,   431,   192,   193,   447,   198,    67,   120,
      69,   121,    71,   166,   544,   545,   524,   260,   261,   262,
     108,   332,   153,   154,   155,   156,   410,   291,   411,   528,
     448,   449,   533,   450,   414,   415,   416,   417,   418,   390,
     391,   392,   520,   185,   598,   307,   311,   157,    72,   144,
     145,   146,   147,   546,    73,    74,    75,    76,   186,    77,
      78,    79,    80,   319,   287,   619,    81,   298,    82,   339,
      83,   341,   220,   221,   109,   292,   299,    98,   110,   111,
     112,   324,   452,   484,   348,   570,   571,   572,    84,   351,
     208,    85,    86,   209,   210,    87,    88,    89,   168,   169,
      90,    91,   179,    92,    93,   122,   149,   150,   172,   224,
     173,   161,   174,   328,   175,   176,   442,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -512
static const yytype_int16 yypact[] =
{
     987,    36,    36,    36,   276,    17,    36,    36,    36,    36,
      36,    36,  -512,  -512,  -512,  -512,  2390,  2390,    36,   276,
      36,    46,    89,    32,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,   146,  -512,  1881,  -512,  -512,   150,
    -512,  -512,  -512,  -512,  -512,    36,    36,   159,    36,    36,
      36,    36,    36,   111,   127,   222,   305,   164,   165,   117,
      10,  -512,  -512,  -512,  -512,  -512,  1938,   167,  1995,  1695,
     130,   175,  2390,  2390,  2390,  2390,  1639,  2390,   181,    -5,
       4,  1938,  2109,  2165,   107,  -512,  -512,  -512,    36,  -512,
      10,  1938,   164,  1695,  1938,  1307,  -512,  -512,   191,  -512,
    -512,  -512,  -512,  -512,   176,  -512,  -512,  -512,   234,   250,
    -512,    17,  1153,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,   155,  -512,  1564,  1564,  2390,   276,  2390,    17,    17,
    -512,  2390,  2390,  2390,  -512,  -512,  2390,  -512,   157,  -512,
    -512,  -512,  -512,  -512,  2390,  2390,  2390,  2390,    49,   164,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,    88,  1070,  -512,
    -512,   176,  1564,  2390,  2390,  -512,    36,  -512,   176,  -512,
    -512,  1938,    36,  -512,   176,  -512,  -512,  1466,    49,   171,
     792,   792,  1258,  1258,    36,   259,  2390,  1368,    37,  1564,
    -512,  -512,  -512,  -512,   -12,  -512,  -512,   111,  -512,   183,
    -512,  2221,   196,    36,    36,  1417,  -512,    18,  -512,  -512,
     154,  -512,  1564,  -512,   154,  1466,    36,    36,    36,  2277,
    1224,  1224,  2221,  -512,  -512,   164,    36,  -512,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,  -512,   276,  -512,  2390,
     297,   250,  -512,  -512,   305,    17,   237,  2491,  -512,  2491,
     239,   240,  -512,   248,  -512,  -512,   127,   171,  1564,  1564,
    1564,  1564,  -512,  -512,  -512,  -512,   251,   252,   325,   125,
      17,  1153,   264,  1819,  1564,  1564,  2390,  2334,  -512,   257,
    1757,    36,  -512,  -512,  -512,    99,  -512,    17,   361,    17,
    -512,    17,  -512,    17,  -512,  -512,   792,   362,    36,  2221,
     564,   367,  -512,  -512,   181,    17,    99,  -512,  -512,  1564,
      36,    17,  -512,  -512,  -512,   164,  2446,  2446,  2221,  -512,
     318,  -512,   301,  -512,  -512,  -512,   283,  1938,  -512,  1564,
    -512,   176,  -512,    10,  1564,  -512,   176,  -512,    10,    36,
    -512,  2390,  2390,  2390,  2390,  2390,  2390,  2390,  2390,  2390,
    2390,  2390,  2390,  2390,  2390,  2390,  2390,  2390,  2390,  2390,
    2390,  2390,  2390,  2390,  2390,  2390,  2390,  2390,  2390,  -512,
      34,  -512,     5,  1564,    17,   373,  -512,   896,  -512,  -512,
    -512,    17,  -512,  -512,  -512,  -512,  -512,   334,   379,  -512,
      59,   309,  -512,   176,   176,  -512,   176,   299,  -512,   315,
    -512,   314,  -512,  -512,  -512,  1564,  -512,  -512,  -512,  2390,
    -512,  -512,  -512,   144,  -512,   144,   391,   392,    17,   402,
    -512,  -512,    22,  1564,  -512,  -512,   379,    17,    35,  -512,
     176,    47,  -512,   335,  -512,  -512,   413,    17,    -5,   417,
      17,   164,  -512,  -512,  -512,  -512,   164,  -512,   380,  -512,
    -512,  -512,  2390,  -512,  -512,   164,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,    36,   107,  2390,  -512,  -512,   372,
    2491,  2491,   248,   482,   482,  1515,  2567,  2605,   671,   666,
     666,   600,   600,   375,   375,   248,   248,   248,  2643,  2643,
    2643,  2643,  2643,  2643,   600,   600,  2529,  2529,    17,    36,
    -512,  2390,  -512,    17,  -512,   305,   423,  -512,   176,  -512,
    -512,   358,  -512,  -512,   573,  -512,   105,  -512,   573,  2492,
     379,  -512,  1564,    36,   430,  -512,  2390,   432,  -512,  -512,
     158,  -512,    17,  -512,   434,  -512,   105,   379,    36,    17,
    -512,    17,  -512,  -512,   436,  1515,  -512,  2052,  1564,  2221,
    -512,   372,  -512,   382,  -512,   283,  1564,  -512,  -512,   334,
    -512,   379,   176,   176,   299,   176,  -512,   176,   176,  -512,
    -512,  -512,  -512,  -512,   792,  -512,  -512,  -512,  -512,   440,
    -512,    36,  -512,   441,   442,  -512,   164,    28,    36,  -512,
      36,  -512,  -512,  -512,  -512,   105,  -512,   573,  -512,   105,
    -512,  -512,   105,    17,  -512,  -512,  -512,  -512,  -512,  2390,
     176,   176,   176,  -512,   176,   144,  2491,  -512,  -512,  -512,
     105,  -512,  -512,   176,  -512
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -512,  -512,     8,   341,  -306,  -301,  -265,  -323,  -512,  -512,
    -512,  -512,  -512,   200,    14,   -41,  -512,  -512,  -512,  -512,
    -512,  -512,    82,  -512,  -512,  -512,  -512,   -78,   -28,   438,
     -27,   513,     0,  -512,  -411,  -243,  -512,  -512,  -512,   207,
    -293,  -512,   -70,  -512,  -512,  -512,  -512,   214,    92,  -512,
     189,  -264,   140,  -225,  -495,  -511,  -432,    98,  -512,  -512,
    -512,  -512,  -512,  -302,  -512,  -178,  -172,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,  -512,
    -512,  -512,  -512,  -512,  -512,    53,  -128,  -182,  -444,  -343,
     -20,  -512,   307,   310,  -123,   227,   244,  -512,   118,   -91,
    -146,  -512,    72,  -512,   -46,  -512,  -512,   -49,   -65,   302,
    -512,   -71,  -253,  -196,  -512,  -512,  -512,    84,   445,   228,
     443,   -51,   388,  -141,  -512,    52,   -79,  -140,   447,    20,
    -512,  -512,  -512,  -512,   242,   233,  -512,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -244
static const yytype_int16 yytable[] =
{
     123,   124,   202,   309,   105,   270,   271,   284,    56,   285,
     203,   313,   188,   225,   477,   439,   489,   395,   171,   105,
     223,   333,   334,   335,   547,   412,   359,   589,   200,   200,
     466,   466,   456,   126,   288,   467,   467,   152,   459,   582,
     158,   317,   171,   588,   360,   569,   196,   306,   310,   322,
     162,   195,    94,   177,   207,   196,   180,   181,   182,   183,
     187,   189,   318,   106,   413,   205,   212,   215,   106,   216,
     158,   468,   468,   201,  -232,   162,   519,   177,   162,   -16,
     106,   444,    96,   473,   473,   285,   160,   197,    54,    50,
     107,   347,   323,   -21,   403,   107,   197,    54,   404,   190,
      37,   216,   583,    40,   405,   406,   589,   107,   445,   267,
    -232,   269,   217,   218,   227,   272,   273,   274,    94,   398,
     275,    94,   632,   557,   583,   128,   105,   569,   278,   279,
     280,   281,   407,    94,   286,   408,   530,   219,   438,   409,
     268,   137,   479,    94,   420,    94,    94,   294,   295,   190,
      37,   303,   403,   167,   554,   162,   404,   257,   543,   394,
     191,   107,   405,   406,    94,  -204,   211,   564,   129,   151,
     316,   216,   403,   394,   397,   184,   404,   167,   -19,   350,
     355,   581,   405,   406,   433,   329,   435,   558,   436,   216,
     437,   137,   451,   451,   207,   475,   475,   409,   407,   397,
      96,   217,   218,   349,   354,   354,   212,   -17,   472,   472,
      94,   -20,   518,   408,   293,  -108,   590,   409,   216,   137,
     -22,   297,   139,    94,   642,   148,   -23,   300,   -16,   263,
     282,   190,    37,   466,   178,    40,   -18,   256,   467,   303,
     216,   219,   423,   393,   258,    97,    99,   100,   597,   423,
     113,   114,   115,   116,   117,   118,   461,   105,   259,   266,
     302,   276,   125,   338,   127,   628,   603,   297,   604,   315,
     552,   522,    94,    94,   468,   305,   203,   177,   526,   330,
     425,   215,   485,   487,   177,   327,   473,   326,   488,   130,
     131,    40,   132,   133,   134,   135,   136,   455,   308,   308,
     312,   312,   566,   443,   352,   357,   211,   596,   470,   470,
     207,   585,   394,   587,   230,   550,   140,   141,   483,   399,
     400,   285,   212,   142,   143,    35,   101,   102,  -205,   289,
      33,   205,   222,   158,    37,   402,   471,   471,   158,   427,
      43,    44,   419,    94,   422,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   608,   434,   482,   602,   167,   480,   184,
     562,   481,   523,   606,   167,    37,   532,   430,   476,   476,
     630,   540,   631,   539,   541,   574,   225,   634,   475,    94,
     577,   548,   549,   441,   486,   525,   454,   200,   302,   486,
     296,   472,   551,   542,   403,   643,   623,   559,   404,   625,
     474,   478,   211,   560,   405,   406,   403,   563,   314,   599,
     404,    45,   151,   578,   308,   580,   405,   406,    68,   347,
     593,   230,   595,   446,   600,   521,   605,   610,    51,    94,
     624,   626,   627,   265,   340,   408,   565,   389,   342,   409,
     343,   344,   345,   243,   244,   245,   534,   536,   396,   538,
     568,   409,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     635,   401,   531,   556,    68,   576,   529,    68,   308,   159,
     453,   470,   170,    70,   336,   263,   194,   337,   421,    68,
     555,   607,   609,   356,   204,   426,   277,   461,   214,    68,
     594,    68,    68,   428,   159,   424,   170,   159,   567,   471,
     226,   207,     0,     0,   553,   429,     0,   611,   230,     0,
      68,   349,     0,   212,   535,     0,   537,     0,     0,     0,
     312,     0,   440,     0,     0,     0,     0,   138,   241,   242,
     243,   244,   245,     0,   458,   561,     0,     0,     0,    70,
       0,   579,    70,     0,     0,     0,   283,     0,     0,     0,
       0,   476,   199,   199,    70,     0,    68,     0,     0,     0,
       0,     0,     0,   340,    70,     0,    70,    70,     0,    68,
     444,   403,     0,   636,   159,   404,   283,     0,     0,     0,
     403,   405,   406,     0,   404,    70,     0,     0,     0,     0,
     405,   406,   584,     0,   586,   615,   617,   445,   591,     0,
     446,   622,     0,     0,     0,    51,     0,     0,     0,   581,
       0,     0,   408,   211,   584,   601,   409,     0,    68,    68,
       0,   408,     0,   353,   358,   409,   230,     0,     0,   231,
     232,    70,     0,     0,     0,     0,   236,   237,   238,   613,
       0,     0,     0,     0,    70,   640,   241,   242,   243,   244,
     245,   304,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   308,   586,     0,     0,     0,   633,     0,     0,
     586,     0,   614,   616,     0,   618,     0,   620,   621,    68,
       0,     0,   230,    70,    70,   231,   232,   230,   586,   573,
     231,   232,   236,   283,     0,     0,     0,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   241,   242,   243,
     244,   245,   283,   575,   283,     0,     0,     0,     0,     0,
     637,   638,   639,     0,   641,     0,     0,     0,     0,     0,
       0,     0,     0,   644,     0,    68,     0,   592,     0,   304,
     204,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    70,   306,    70,     0,     0,     0,
       0,     0,     0,    70,     0,     0,     0,     0,   432,     0,
       0,     0,   228,   229,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    68,     0,     0,   106,   304,
       0,     0,     0,     0,     0,   527,     0,     0,     0,     0,
       0,     0,   340,     0,   629,     0,     0,     0,   230,     0,
      70,   231,   232,     0,   233,   107,   234,   235,   236,   237,
     238,     0,     0,     0,     0,   239,   240,     0,   241,   242,
     243,   244,   245,     0,     0,     0,     0,     0,   246,   247,
     248,   249,   250,   251,   252,   253,     0,   254,   255,     1,
       2,     3,     4,     5,     0,     0,     0,     6,     7,     0,
      70,     0,     8,     0,     9,    10,    11,    12,    13,    14,
      15,     0,     0,     0,    16,    17,     0,     0,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,   106,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     0,     0,    46,    47,
       0,     0,     0,    48,    49,     0,     0,     0,     0,   107,
       0,   199,     0,     0,     0,    50,     0,    51,     0,     0,
       0,    52,     0,     0,     0,     0,     0,     0,    53,    54,
       1,     2,     3,     4,     5,     0,     0,     0,     6,     7,
       0,     0,     0,     8,     0,     9,    10,    11,    12,    13,
      14,    15,     0,     0,     0,    16,    17,   612,     0,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,    46,
      47,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,    51,     0,
       0,     0,    52,     1,     2,     3,     4,     5,     0,    53,
      54,     6,     7,     0,     0,     0,     8,     0,     9,    10,
      11,    12,    13,    14,    15,     0,     0,     0,    16,    17,
       0,     0,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,    47,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,   289,     0,    50,
       0,    51,     0,     0,     0,    52,     1,     2,     3,     4,
       5,     0,    53,    54,     6,     7,     0,     0,     0,     8,
       0,     9,    10,    11,    12,    13,    14,    15,     0,     0,
       0,    16,    17,     0,     0,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,    46,    47,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     1,     2,     3,
       0,     5,    50,     0,    51,     6,     7,     0,    52,     0,
       8,     0,     9,    10,    11,    53,    54,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,   310,     0,    46,    47,   228,   229,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,   106,    51,     0,     0,     0,    52,
       0,     0,     0,     0,     0,     0,    53,    54,     0,     0,
       0,     0,     0,     0,   230,     0,     0,   231,   232,     0,
     233,   107,   234,   235,   236,   237,   238,   228,   229,     0,
       0,   239,   240,     0,   241,   242,   243,   244,   245,     0,
       0,     0,     0,     0,   246,   247,   248,   249,   250,   251,
     252,   253,     0,   254,   255,     0,     0,     0,     0,     0,
       0,  -243,     0,   230,     0,     0,   231,   232,     0,   233,
       0,   234,   235,   236,   237,   238,     0,     0,     0,     0,
     239,   240,     0,   241,   242,   243,   244,   245,   228,   229,
       0,  -243,  -243,   246,   247,   248,   249,   250,   251,   252,
     253,     0,   254,   255,   106,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   230,     0,     0,   231,   232,     0,
     233,   107,   234,   235,   236,   237,   238,   228,   229,     0,
       0,   239,   240,     0,   241,   242,   243,   244,   245,     0,
       0,     0,     0,    96,   246,   247,   248,   249,   250,   251,
     252,   253,     0,   254,   255,     0,     0,     0,     0,     0,
       0,     0,     0,   230,     0,     0,   231,   232,     0,   233,
       0,   234,   235,   236,   237,   238,   228,   229,     0,  -218,
     239,   240,     0,   241,   242,   243,   244,   245,     0,     0,
       0,     0,     0,   246,   247,   248,   249,   250,   251,   252,
     253,     0,   254,   255,     0,     0,     0,     0,     0,     0,
       0,     0,   230,     0,     0,   231,   232,   301,   233,     0,
     234,   235,   236,   237,   238,   228,   229,     0,     0,   239,
     240,     0,   241,   242,   243,   244,   245,     0,     0,     0,
       0,    96,   246,   247,   248,   249,   250,   251,   252,   253,
       0,   254,   255,     0,     0,     0,     0,     0,     0,     0,
       0,   230,     0,     0,   231,   232,     0,   233,     0,   234,
     235,   236,   237,   238,   228,   229,     0,     0,   239,   240,
       0,   241,   242,   243,   244,   245,     0,     0,     0,     0,
       0,   246,   247,   248,   249,   250,   251,   252,   253,     0,
     254,   255,     0,     0,     0,     0,     0,     0,     0,     0,
     230,     0,     0,   231,   232,     0,   233,     0,   234,   235,
     236,   237,   238,     0,     0,     0,     0,   239,   240,     0,
     241,   242,   243,   244,   245,     0,   184,     0,     0,     0,
     246,   247,   248,   249,   250,   251,   252,   253,     0,   254,
     255,    18,     0,    20,     0,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,   119,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,    46,    47,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,    52,     0,     0,    18,     0,    20,
       0,    53,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,     0,     0,    46,    47,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,   163,     0,     0,    50,     0,    51,     0,     0,     0,
      52,     0,     0,   164,     0,     0,   165,    53,    54,    18,
       0,    20,     0,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,    33,    34,    35,   119,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,    46,
      47,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,   163,     0,     0,    50,     0,    51,     0,
       0,     0,    52,     0,     0,   164,     0,     0,   165,    53,
      54,    18,     0,    20,     0,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,   119,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,    46,    47,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
      51,     0,     0,     0,    52,     0,     0,     0,     0,     0,
     165,    53,    54,   -88,     0,   -88,     0,     0,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,     0,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,     0,     0,   -88,   -88,     0,     0,     0,   -88,   -88,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -88,     0,     0,     0,   -88,     0,     0,     0,
      18,     0,    20,   -88,   -88,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     0,     0,
      46,    47,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,     0,    52,     0,     0,     0,   -89,     0,   -89,
      53,    54,   -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,     0,   -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,     0,     0,   -89,   -89,     0,
       0,     0,   -89,   -89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -89,     0,     0,     0,
     -89,     0,     0,     0,    18,     0,    20,   -89,   -89,    23,
      24,    25,    26,    27,    28,    29,    30,    31,  -233,    33,
      34,    35,   119,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     0,     0,    46,    47,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,  -233,     0,     0,    52,     0,     0,
     346,    18,     0,    20,    53,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,   119,
      37,    38,    39,    40,    41,    42,    43,    44,    45,   206,
       0,    46,    47,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
      51,     0,     0,     0,    52,     0,     0,    18,     0,    20,
       0,    53,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    33,    34,    35,   119,    37,    38,    39,    40,
      41,    42,    43,    44,    45,     0,     0,    46,    47,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   213,    51,     0,     0,     0,
      52,     0,     0,    18,     0,    20,   165,    53,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,    33,    34,
      35,   119,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,    46,    47,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,    51,     0,     0,     0,    52,     0,     0,    18,
       0,    20,     0,    53,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,    33,    34,    35,   119,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,    46,
      47,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
       0,     0,    52,     0,     0,   346,    18,     0,    20,    53,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    33,    34,    35,   119,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,     0,    46,    47,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,    52,
       0,     0,    18,     0,    20,   165,    53,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    33,    34,    35,
     119,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,    47,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     0,     0,    52,     0,     0,     0,     0,
       0,     0,    53,   462,    24,    25,    26,    27,    28,    29,
      30,    31,     0,    33,   463,    35,     0,    37,    38,   464,
      40,    41,     0,    43,    44,    45,     0,     0,     0,   465,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,    51,     0,   462,
      24,    25,    26,    27,    28,    29,    30,    31,    53,    33,
     463,    35,     0,    37,    38,   464,    40,    41,     0,    43,
      44,    45,     0,     0,     0,   465,     0,   230,     0,     0,
     231,   232,     0,   233,     0,   234,   235,   236,   237,   238,
       0,     0,     0,    51,   239,   240,     0,   241,   242,   243,
     244,   245,     0,     0,    53,     0,     0,   246,   247,   248,
     249,   250,   251,   252,   253,   230,   254,   255,   231,   232,
       0,     0,     0,   234,   235,   236,   237,   238,     0,     0,
       0,     0,   239,   240,     0,   241,   242,   243,   244,   245,
       0,     0,     0,     0,     0,   246,   247,   248,   249,   250,
     251,   252,   253,   230,  -244,  -244,   231,   232,     0,     0,
       0,     0,   235,   236,   237,   238,     0,     0,     0,     0,
     239,   240,     0,   241,   242,   243,   244,   245,     0,     0,
       0,     0,     0,   246,   247,   248,   249,   250,   251,   252,
     253,   230,     0,     0,   231,   232,     0,     0,     0,     0,
       0,   236,   237,   238,     0,     0,     0,     0,   239,   240,
       0,   241,   242,   243,   244,   245,     0,     0,     0,     0,
       0,   246,   247,   248,   249,   250,   251,   252,   253,   230,
       0,     0,   231,   232,     0,     0,     0,     0,     0,   236,
     237,   238,     0,     0,     0,     0,   239,   240,     0,   241,
     242,   243,   244,   245,     0,     0,     0,     0,     0,  -244,
    -244,  -244,  -244,  -244,  -244,   252,   253
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-512))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-244))

static const yytype_int16 yycheck[] =
{
      16,    17,    80,   181,     4,   128,   129,   148,     0,   149,
      81,   183,    77,    92,   337,   317,   359,   260,    69,    19,
      90,   203,   204,   205,   435,   289,   222,   538,    79,    80,
     336,   337,   325,    19,   157,   336,   337,    27,   331,   534,
      60,   187,    93,   538,   226,   489,    51,    13,    26,    61,
      66,    78,     0,    69,    82,    51,    72,    73,    74,    75,
      76,    77,    25,    46,   289,    81,    82,    83,    46,    64,
      90,   336,   337,    69,    46,    91,    71,    93,    94,    61,
      46,    46,    46,   336,   337,   225,    66,    92,    93,    79,
      73,   219,   104,    61,    47,    73,    92,    93,    51,    50,
      51,    64,   534,    54,    57,    58,   617,    73,    73,   125,
      82,   127,    94,    95,    94,   131,   132,   133,    66,   265,
     136,    69,   617,    76,   556,    79,   126,   571,   144,   145,
     146,   147,    73,    81,    46,    88,    77,    84,   316,    92,
     126,    92,   338,    91,   290,    93,    94,   163,   164,    50,
      51,   178,    47,    69,   447,   171,    51,   104,    14,    15,
      78,    73,    57,    58,   112,    77,    82,   460,    79,    52,
     186,    64,    47,    15,   265,    17,    51,    93,    61,   220,
     221,    76,    57,    58,   307,   201,   309,   451,   311,    64,
     313,    92,   320,   321,   222,   336,   337,    92,    73,   290,
      46,    94,    95,   219,   220,   221,   222,    61,   336,   337,
     158,    61,   390,    88,   161,   104,   539,    92,    64,    92,
      61,   168,     0,   171,   635,    61,    61,   174,    61,   111,
     148,    50,    51,   539,   104,    54,    61,    46,   539,   266,
      64,   188,   293,   259,    10,     1,     2,     3,   550,   300,
       6,     7,     8,     9,    10,    11,   335,   257,     8,   104,
     178,   104,    18,   210,    20,   608,   559,   214,   561,    10,
     442,   394,   220,   221,   539,   104,   347,   293,   401,    83,
     296,   297,   347,   353,   300,   201,   539,   104,   358,    45,
      46,    54,    48,    49,    50,    51,    52,   324,   180,   181,
     182,   183,   484,   319,   220,   221,   222,   550,   336,   337,
     338,   536,    15,   538,    66,   438,    11,    12,   346,    80,
      80,   461,   338,    18,    19,    49,    50,    51,    77,    77,
      47,   347,    88,   353,    51,    10,   336,   337,   358,    82,
      57,    58,   289,   291,    80,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   569,    13,    92,   558,   293,    60,    17,
     458,    80,     9,   565,   300,    51,    77,   305,   336,   337,
     615,    76,   617,    94,    80,   518,   475,   622,   539,   347,
     523,    10,    10,   319,   351,   397,   324,   458,   326,   356,
     166,   539,    10,   429,    47,   640,   594,    82,    51,   601,
     336,   337,   338,    10,    57,    58,    47,    10,   184,   552,
      51,    59,    52,    10,   316,    77,    57,    58,     0,   567,
      10,    66,    10,    76,    10,   392,    10,    65,    81,   397,
      10,    10,    10,   112,   210,    88,   472,   257,   214,    92,
     216,   217,   218,    88,    89,    90,   413,   414,   261,   416,
     486,    92,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     623,   287,   410,   450,    66,   521,   408,    69,   390,    66,
     321,   539,    69,     0,   207,   397,    78,   207,   291,    81,
     448,   567,   571,   221,    81,   297,   138,   606,    83,    91,
     546,    93,    94,   300,    91,   293,    93,    94,   485,   539,
      93,   569,    -1,    -1,   446,   301,    -1,   575,    66,    -1,
     112,   567,    -1,   569,   414,    -1,   416,    -1,    -1,    -1,
     442,    -1,   318,    -1,    -1,    -1,    -1,    54,    86,    87,
      88,    89,    90,    -1,   330,   457,    -1,    -1,    -1,    66,
      -1,   528,    69,    -1,    -1,    -1,   148,    -1,    -1,    -1,
      -1,   539,    79,    80,    81,    -1,   158,    -1,    -1,    -1,
      -1,    -1,    -1,   359,    91,    -1,    93,    94,    -1,   171,
      46,    47,    -1,   629,   171,    51,   178,    -1,    -1,    -1,
      47,    57,    58,    -1,    51,   112,    -1,    -1,    -1,    -1,
      57,    58,   534,    -1,   536,   582,   583,    73,   540,    -1,
      76,   588,    -1,    -1,    -1,    81,    -1,    -1,    -1,    76,
      -1,    -1,    88,   569,   556,   557,    92,    -1,   220,   221,
      -1,    88,    -1,   220,   221,    92,    66,    -1,    -1,    69,
      70,   158,    -1,    -1,    -1,    -1,    76,    77,    78,   581,
      -1,    -1,    -1,    -1,   171,   632,    86,    87,    88,    89,
      90,   178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   594,   615,    -1,    -1,    -1,   619,    -1,    -1,
     622,    -1,   582,   583,    -1,   585,    -1,   587,   588,   291,
      -1,    -1,    66,   220,   221,    69,    70,    66,   640,   495,
      69,    70,    76,   305,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    86,    87,    88,
      89,    90,   324,   519,   326,    -1,    -1,    -1,    -1,    -1,
     630,   631,   632,    -1,   634,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   643,    -1,   347,    -1,   543,    -1,   276,
     347,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   291,    13,   293,    -1,    -1,    -1,
      -1,    -1,    -1,   300,    -1,    -1,    -1,    -1,   305,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   397,    -1,    -1,    46,   326,
      -1,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,
      -1,    -1,   608,    -1,   610,    -1,    -1,    -1,    66,    -1,
     347,    69,    70,    -1,    72,    73,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    -1,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,   105,   106,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,
     397,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    28,    29,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    73,
      -1,   458,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    92,    93,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    28,    29,   579,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,
      -1,    -1,    85,     3,     4,     5,     6,     7,    -1,    92,
      93,    11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    28,    29,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    79,
      -1,    81,    -1,    -1,    -1,    85,     3,     4,     5,     6,
       7,    -1,    92,    93,    11,    12,    -1,    -1,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    29,    -1,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    68,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    79,    -1,    81,    11,    12,    -1,    85,    -1,
      16,    -1,    18,    19,    20,    92,    93,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    26,    -1,    62,    63,    30,    31,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    46,    81,    -1,    -1,    -1,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    92,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,
      72,    73,    74,    75,    76,    77,    78,    30,    31,    -1,
      -1,    83,    84,    -1,    86,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    -1,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,   105,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    66,    -1,    -1,    69,    70,    -1,    72,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      83,    84,    -1,    86,    87,    88,    89,    90,    30,    31,
      -1,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,   105,   106,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,
      72,    73,    74,    75,    76,    77,    78,    30,    31,    -1,
      -1,    83,    84,    -1,    86,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    46,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,   105,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,    72,
      -1,    74,    75,    76,    77,    78,    30,    31,    -1,    82,
      83,    84,    -1,    86,    87,    88,    89,    90,    -1,    -1,
      -1,    -1,    -1,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    69,    70,    71,    72,    -1,
      74,    75,    76,    77,    78,    30,    31,    -1,    -1,    83,
      84,    -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,
      -1,    46,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    69,    70,    -1,    72,    -1,    74,
      75,    76,    77,    78,    30,    31,    -1,    -1,    83,    84,
      -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,    -1,
      -1,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
     105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    69,    70,    -1,    72,    -1,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    -1,    83,    84,    -1,
      86,    87,    88,    89,    90,    -1,    17,    -1,    -1,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,   105,
     106,    32,    -1,    34,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    85,    -1,    -1,    32,    -1,    34,
      -1,    92,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    -1,
      -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,
      85,    -1,    -1,    88,    -1,    -1,    91,    92,    93,    32,
      -1,    34,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    -1,    81,    -1,
      -1,    -1,    85,    -1,    -1,    88,    -1,    -1,    91,    92,
      93,    32,    -1,    34,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,
      91,    92,    93,    32,    -1,    34,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    -1,
      32,    -1,    34,    92,    93,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    32,    -1,    34,
      92,    93,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    -1,
      -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      85,    -1,    -1,    -1,    32,    -1,    34,    92,    93,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    85,    -1,    -1,
      88,    32,    -1,    34,    92,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    -1,    85,    -1,    -1,    32,    -1,    34,
      -1,    92,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    -1,
      -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,
      85,    -1,    -1,    32,    -1,    34,    91,    92,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    32,
      -1,    34,    -1,    92,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      63,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    85,    -1,    -1,    88,    32,    -1,    34,    92,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    85,
      -1,    -1,    32,    -1,    34,    91,    92,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
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
      89,    90,    -1,    -1,    92,    -1,    -1,    96,    97,    98,
      99,   100,   101,   102,   103,    66,   105,   106,    69,    70,
      -1,    -1,    -1,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    83,    84,    -1,    86,    87,    88,    89,    90,
      -1,    -1,    -1,    -1,    -1,    96,    97,    98,    99,   100,
     101,   102,   103,    66,   105,   106,    69,    70,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      83,    84,    -1,    86,    87,    88,    89,    90,    -1,    -1,
      -1,    -1,    -1,    96,    97,    98,    99,   100,   101,   102,
     103,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    76,    77,    78,    -1,    -1,    -1,    -1,    83,    84,
      -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,    -1,
      -1,    96,    97,    98,    99,   100,   101,   102,   103,    66,
      -1,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    -1,    -1,    -1,    -1,    83,    84,    -1,    86,
      87,    88,    89,    90,    -1,    -1,    -1,    -1,    -1,    96,
      97,    98,    99,   100,   101,   102,   103
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
      79,    81,    85,    92,    93,   108,   109,   111,   112,   113,
     115,   116,   117,   118,   119,   122,   129,   135,   136,   137,
     138,   139,   175,   181,   182,   183,   184,   186,   187,   188,
     189,   193,   195,   197,   215,   218,   219,   222,   223,   224,
     227,   228,   230,   231,   232,   244,    46,   203,   204,   203,
     203,    50,    51,   120,   121,   139,    46,    73,   147,   201,
     205,   206,   207,   203,   203,   203,   203,   203,   203,    50,
     136,   138,   232,   244,   244,   203,   121,   203,    79,    79,
     203,   203,   203,   203,   203,   203,   203,    92,   138,     0,
      11,    12,    18,    19,   176,   177,   178,   179,    61,   233,
     234,    52,    27,   149,   150,   151,   152,   174,   197,   227,
     236,   238,   244,    76,    88,    91,   140,   224,   225,   226,
     227,   228,   235,   237,   239,   241,   242,   244,   104,   229,
     244,   244,   244,   244,    17,   170,   185,   244,   215,   244,
      50,   129,   131,   132,   136,   137,    51,    92,   134,   138,
     228,    69,   134,   218,   227,   244,    60,   135,   217,   220,
     221,   224,   244,    80,   225,   244,    64,    94,    95,   192,
     199,   200,   203,   149,   236,   233,   235,   236,    30,    31,
      66,    69,    70,    72,    74,    75,    76,    77,    78,    83,
      84,    86,    87,    88,    89,    90,    96,    97,    98,    99,
     100,   101,   102,   103,   105,   106,    46,   192,    10,     8,
     144,   145,   146,   205,   109,   110,   104,   244,   121,   244,
     201,   201,   244,   244,   244,   244,   104,   229,   244,   244,
     244,   244,   129,   136,   230,   234,    46,   191,   201,    77,
     110,   154,   202,   192,   244,   244,   203,   192,   194,   203,
     192,    71,   129,   137,   138,   104,    13,   172,   205,   172,
      26,   173,   205,   173,   203,    10,   244,   207,    25,   190,
     123,   124,    61,   104,   208,   125,   104,   224,   240,   244,
      83,   126,   148,   194,   194,   194,   199,   200,   192,   196,
     203,   198,   203,   203,   203,   203,    88,   193,   211,   244,
     122,   216,   224,   227,   244,   122,   216,   224,   227,   220,
     194,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   120,
     166,   167,   168,   244,    15,   142,   146,   206,   207,    80,
      80,   154,    10,    47,    51,    57,    58,    73,    88,    92,
     153,   155,   158,   160,   161,   162,   163,   164,   165,   192,
     207,   202,    80,   228,   241,   244,   226,    82,   242,   203,
     129,   130,   138,   201,    13,   201,   201,   201,   172,   170,
     203,   224,   243,   244,    46,    73,    76,   133,   157,   158,
     160,   193,   209,   157,   129,   137,   147,   128,   203,   147,
     127,   233,    37,    48,    53,    63,   111,   112,   113,   114,
     135,   139,   193,   219,   224,   230,   232,   114,   224,   220,
      60,    80,    92,   135,   210,   215,   192,   149,   149,   196,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   172,    71,
     169,   192,   201,     9,   143,   109,   201,   136,   156,   164,
      77,   155,    77,   159,   192,   159,   192,   159,   192,    94,
      76,    80,   244,    14,   141,   142,   180,   141,    10,    10,
     201,    10,   173,   164,   147,   209,   192,    76,   158,    82,
      10,   205,   134,    10,   147,   244,   194,   192,   244,   195,
     212,   213,   214,   203,   201,   203,   244,   201,    10,   192,
      77,    76,   161,   163,   164,   160,   164,   160,   161,   162,
     114,   164,   203,    10,   244,    10,   142,   170,   171,   201,
      10,   164,   194,   147,   147,    10,   194,   211,   220,   214,
      65,   135,   136,   164,   159,   192,   159,   192,   159,   192,
     159,   159,   192,   172,    10,   194,    10,    10,   196,   203,
     160,   160,   161,   164,   160,   201,   244,   159,   159,   159,
     192,   159,   141,   160,   159
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
#line 208 "../parser.y"
    { parser->ast = NULL; YYACCEPT; }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 210 "../parser.y"
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
#line 222 "../parser.y"
    { fix_mrhs((yyval.n)); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 224 "../parser.y"
    {
    (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    parser->call_args = 0;
  }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 229 "../parser.y"
    { (yyval.n) = ALLOC_MOD(token_if, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);     }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 230 "../parser.y"
    { (yyval.n) = ALLOC_MOD(token_unless, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 231 "../parser.y"
    { (yyval.n) = ALLOC_MOD(token_while, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);  }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 232 "../parser.y"
    { (yyval.n) = ALLOC_MOD(token_until, (yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n), NULL);  }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 236 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 237 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 240 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 241 "../parser.y"
    { (yyval.n) = ALLOC_N(token_numeric, NULL, NULL);   }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 242 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 244 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_string, NULL, NULL); POP_STR;
    multiple_string(parser, (yyval.n));
  }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 248 "../parser.y"
    { (yyval.n) = ALLOC_N(token_regexp, NULL, NULL); POP_STR;    }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 249 "../parser.y"
    { (yyval.n) = ALLOC_N(token_heredoc, NULL, NULL);   }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 250 "../parser.y"
    { (yyval.n) = ALLOC_N(token_backtick, NULL, NULL); POP_STR;  }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 251 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL);    }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 266 "../parser.y"
    {
    CONCAT_STRING;
    pop_pos(parser, NULL);
  }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 272 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 273 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 274 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 275 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 278 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 279 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 280 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 283 "../parser.y"
    { (yyval.n) = ALLOC_N(token_numeric, NULL, NULL);   }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 284 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 286 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_string, NULL, NULL); POP_STR;
    multiple_string(parser, (yyval.n));
  }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 290 "../parser.y"
    { (yyval.n) = ALLOC_N(token_regexp, NULL, NULL); POP_STR;   }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 291 "../parser.y"
    { (yyval.n) = ALLOC_N(token_heredoc, NULL, NULL);   }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 292 "../parser.y"
    { (yyval.n) = ALLOC_N(token_backtick, NULL, NULL); POP_STR; }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 293 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 294 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL);    }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 297 "../parser.y"
    { (yyval.n) = ALLOC_N(token_break, NULL, NULL);   }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 298 "../parser.y"
    { (yyval.n) = ALLOC_N(token_redo, NULL, NULL);    }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 299 "../parser.y"
    { (yyval.n) = ALLOC_N(token_retry, NULL, NULL);   }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 300 "../parser.y"
    { (yyval.n) = ALLOC_N(token_next, NULL, NULL);    }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 301 "../parser.y"
    { (yyval.n) = ALLOC_N(token_undef, NULL, (yyvsp[(2) - (2)].n)); fix_mrhs((yyval.n));      }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 302 "../parser.y"
    { (yyval.n) = ALLOC_N(token_alias, (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)); copy_end((yyval.n),(yyvsp[(3) - (3)].n));     }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 303 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 304 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 307 "../parser.y"
    { (yyval.n) = ALLOC_N(token_yield, NULL, NULL);   }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 308 "../parser.y"
    { (yyval.n) = ALLOC_N(token_yield, (yyvsp[(2) - (2)].n), NULL);     }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 311 "../parser.y"
    { (yyval.n) = ALLOC_N(token_return, NULL, NULL);  }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 312 "../parser.y"
    { (yyval.n) = ALLOC_N(token_return, (yyvsp[(2) - (2)].n), NULL); copy_end((yyval.n), (yyvsp[(2) - (2)].n));   }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 315 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 316 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 319 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 320 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 321 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 328 "../parser.y"
    {
    (yyval.n) = ALLOC_C(token_if, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
    pop_start(parser, (yyval.n));
  }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 336 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_unless, (yyvsp[(2) - (6)].n), (yyvsp[(4) - (6)].n), (yyvsp[(5) - (6)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 343 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_while, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 350 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_until, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 357 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_case, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 362 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_case, NULL, (yyvsp[(2) - (3)].n), NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 367 "../parser.y"
    {
      (yyval.n) = ALLOC_N(token_up_begin, (yyvsp[(3) - (4)].n), NULL);
      pop_pos(parser, NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 373 "../parser.y"
    {
      (yyval.n) = ALLOC_N(token_up_end, (yyvsp[(3) - (4)].n), NULL);
      pop_pos(parser, NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 379 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_for, (yyvsp[(4) - (7)].n), (yyvsp[(6) - (7)].n), (yyvsp[(2) - (7)].n));
      pop_pos(parser, NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 385 "../parser.y"
    {
      (yyval.n) = ALLOC_N(token_exception, (yyvsp[(2) - (3)].n), NULL);
      pop_start(parser, (yyval.n));
    }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 390 "../parser.y"
    {
      parser->in_def++;
    }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 394 "../parser.y"
    {
      parser->in_def--;
      (yyval.n) = ALLOC_C(token_function, (yyvsp[(2) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(4) - (6)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 400 "../parser.y"
    {
      parser->in_def++;
    }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 404 "../parser.y"
    {
      parser->in_def--;
      (yyval.n) = ALLOC_C(token_function, (yyvsp[(2) - (7)].n), (yyvsp[(6) - (7)].n), (yyvsp[(4) - (7)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 410 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "module definition in method body");
    }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 416 "../parser.y"
    {
      (yyval.n) = ALLOC_N(token_module, (yyvsp[(4) - (5)].n), (yyvsp[(2) - (5)].n));
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
      (yyval.n) = ALLOC_C(token_class, NULL, (yyvsp[(4) - (5)].n), (yyvsp[(2) - (5)].n));
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
      (yyval.n) = ALLOC_C(token_class, (yyvsp[(3) - (6)].n), (yyvsp[(5) - (6)].n), (yyvsp[(2) - (6)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 443 "../parser.y"
    {
      if (parser->in_def)
        yyerror(parser, "class definition in method body");
    }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 450 "../parser.y"
    {
      (yyval.n) = ALLOC_N(token_singleton_class, (yyvsp[(6) - (7)].n), (yyvsp[(3) - (7)].n));
      pop_start(parser, (yyval.n));
    }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 456 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 457 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 460 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 461 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 465 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 469 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 473 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));		
	}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 477 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);	}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 480 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 481 "../parser.y"
    { (yyval.n) = 0; }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 484 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 485 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 487 "../parser.y"
    {
    yyerror(parser, "class/module name must be CONSTANT");
  }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 492 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 493 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 494 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 495 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 496 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 499 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 502 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; (yyval.n)->endCol--; }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 505 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 508 "../parser.y"
    { (yyval.n) = ALLOC_N(token_symbol, NULL, NULL); POP_STACK; }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 511 "../parser.y"
    { (yyval.n) = ALLOC_N(token_symbol, NULL, NULL); POP_STACK; }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 518 "../parser.y"
    {
      (yyval.n) = ALLOC_C(token_if, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
      struct pos_t tp = { (yyval.n)->startLine, (yyval.n)->endLine, (yyval.n)->startCol, (yyval.n)->endCol };

      pop_pos(parser, (yyval.n));
      push_pos(parser, tp);
    }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 527 "../parser.y"
    { (yyval.n) = 0; }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 529 "../parser.y"
    {
    (yyval.n) = ALLOC_C(token_if, NULL, (yyvsp[(2) - (2)].n), NULL);
    struct pos_t tp = { (yyval.n)->startLine, (yyval.n)->endLine, (yyval.n)->startCol, (yyval.n)->endCol };

    pop_pos(parser, (yyval.n));
    push_pos(parser, tp);
  }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 538 "../parser.y"
    { (yyval.n) = 0; }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 540 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_ensure, (yyvsp[(2) - (2)].n), NULL);
    struct pos_t tp = { (yyval.n)->startLine, (yyval.n)->endLine, (yyval.n)->startCol, (yyval.n)->endCol };

    pop_pos(parser, (yyval.n));
    push_pos(parser, tp);    
  }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 549 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 550 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 553 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 554 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 558 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_rescue, (yyvsp[(2) - (4)].n), (yyvsp[(4) - (4)].n));
    struct pos_t tp = { (yyval.n)->startLine, (yyval.n)->endLine, (yyval.n)->startCol, (yyval.n)->endCol };

    pop_pos(parser, (yyval.n));
    push_pos(parser, tp);
  }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 568 "../parser.y"
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

  case 123:

/* Line 1806 of yacc.c  */
#line 580 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 583 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 584 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 587 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 588 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 592 "../parser.y"
    {
    pop_pos(parser, NULL);
    (yyval.n) = ALLOC_N(token_block, (yyvsp[(3) - (4)].n), (yyvsp[(2) - (4)].n));
    if ((yyvsp[(3) - (4)].n)->last != NULL) {
      copy_end((yyval.n), (yyvsp[(3) - (4)].n)->last);
    } else {
      copy_end((yyval.n), (yyvsp[(3) - (4)].n));
    }
  }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 602 "../parser.y"
    {
    pop_pos(parser, NULL);
    (yyval.n) = ALLOC_N(token_block, (yyvsp[(2) - (3)].n), NULL);
    if ((yyvsp[(2) - (3)].n)->last != NULL) {
      copy_end((yyval.n), (yyvsp[(2) - (3)].n)->last);
    } else {
      copy_end((yyval.n), (yyvsp[(2) - (3)].n));
    }
  }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 614 "../parser.y"
    {
    pop_pos(parser, parser->last_pos);
    (yyval.n) = ALLOC_N(token_block, (yyvsp[(4) - (5)].n), (yyvsp[(3) - (5)].n));
    if ((yyvsp[(4) - (5)].n) != NULL) {
      if ((yyvsp[(4) - (5)].n)->last != NULL) {
        copy_end((yyval.n), (yyvsp[(4) - (5)].n)->last);
      } else {
        copy_end((yyval.n), (yyvsp[(4) - (5)].n));
      }
    } else { 
      copy_pos((yyval.n), parser->last_pos);
    }
  }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 628 "../parser.y"
    {
    pop_pos(parser, parser->last_pos);
    (yyval.n) = ALLOC_N(token_block, (yyvsp[(2) - (3)].n), NULL);
    if ((yyvsp[(2) - (3)].n) != NULL) {
      if ((yyvsp[(2) - (3)].n)->last != NULL) {
        copy_end((yyval.n), (yyvsp[(2) - (3)].n)->last);
      } else {
        copy_end((yyval.n), (yyvsp[(2) - (3)].n));
      }
    } else {
      copy_pos((yyval.n), parser->last_pos);
    }
  }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 643 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 644 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 645 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 647 "../parser.y"
    {
    (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
  }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 651 "../parser.y"
    {
    (yyval.n) = concat_list((yyvsp[(1) - (6)].n), create_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
  }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 657 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n));
    copy_range((yyval.n), (yyvsp[(2) - (4)].n), (yyvsp[(3) - (4)].n)); 
  }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 662 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, NULL, (yyvsp[(2) - (3)].n));
    copy_range((yyval.n), (yyvsp[(2) - (3)].n), (yyvsp[(2) - (3)].n)); 
  }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 667 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);
    copy_range((yyval.n), (yyvsp[(2) - (3)].n), (yyvsp[(2) - (3)].n)); 
  }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 673 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 676 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 677 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 680 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 681 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 682 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 683 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (4)].n);  }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 686 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 688 "../parser.y"
    {
      (yyval.n) = create_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 691 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 693 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 696 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));  }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 698 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), create_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 702 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 706 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 710 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (4)].n), update_list((yyvsp[(3) - (4)].n), (yyvsp[(4) - (4)].n)));
    }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 715 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (8)].n), concat_list((yyvsp[(3) - (8)].n), create_list((yyvsp[(5) - (8)].n), update_list((yyvsp[(7) - (8)].n), (yyvsp[(8) - (8)].n)))));
    }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 719 "../parser.y"
    {
      (yyval.n) = concat_list((yyvsp[(1) - (6)].n), concat_list((yyvsp[(3) - (6)].n), update_list((yyvsp[(5) - (6)].n), (yyvsp[(6) - (6)].n))));
    }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 724 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 725 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 728 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 729 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 732 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 736 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 742 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 743 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 746 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 747 "../parser.y"
    { (yyval.n) = 0; }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 751 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a constant");
    (yyval.n) = 0;
  }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 756 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be an instance variable");
    (yyval.n) = 0;
  }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 761 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a global variable");
    (yyval.n) = 0;
  }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 766 "../parser.y"
    {
    yyerror(parser, "formal argument cannot be a class variable");
    (yyval.n) = 0;
  }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 772 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 773 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 777 "../parser.y"
    {
    (yyval.n) = alloc_node(token_rescue_arg, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    if ((yyvsp[(2) - (2)].n) != NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    } else {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(1) - (2)].n));
    }
  }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 787 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 788 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 791 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 792 "../parser.y"
    { (yyval.n) = (yyvsp[(3) - (3)].n);  }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 796 "../parser.y"
    {
    /* The following statements fixes some issues around positions. */
    (yyval.n) = ALLOC_N(token_object, NULL, NULL);
    struct pos_t t = {(yyval.n)->startLine, (yyval.n)->endLine, (yyval.n)->startCol, (yyval.n)->endCol};
    (yyval.n) = ALLOC_C(token_when, (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
    push_pos(parser, t);
  }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 810 "../parser.y"
    { pop_pos(parser, NULL);  }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 811 "../parser.y"
    { pop_pos(parser, NULL);  }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 816 "../parser.y"
    {
    if (!parser->call_args) {
      pop_pos(parser, parser->last_pos);
      parser->call_args = 1;
    } else
      pop_pos(parser, NULL);
  }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 826 "../parser.y"
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

  case 189:

/* Line 1806 of yacc.c  */
#line 841 "../parser.y"
    { manual_fix(); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 844 "../parser.y"
    { manual_fix(); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 847 "../parser.y"
    { manual_fix(); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 850 "../parser.y"
    { manual_fix(); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 871 "../parser.y"
    { parser->call_args = 1;  }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 917 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 918 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 921 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 952 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 953 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 957 "../parser.y"
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

  case 235:

/* Line 1806 of yacc.c  */
#line 967 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);
    if ((yyvsp[(2) - (3)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(2) - (3)].n), (yyvsp[(2) - (3)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(2) - (3)].n), (yyvsp[(2) - (3)].n));
    }
  }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 975 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 977 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, NULL, NULL);
    (yyval.n)->startLine = (yyval.n)->endLine = parser->auxiliar.startLine;
    (yyval.n)->startCol = parser->auxiliar.startCol;
    (yyval.n)->endCol = (yyval.n)->startCol + 1;
    parser->auxiliar.endLine = -1;
  }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 986 "../parser.y"
    { (yyval.n) = 0; }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 987 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 990 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 991 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 994 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n); pop_pos(parser, NULL); }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 997 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 998 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 999 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1002 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 1003 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 1006 "../parser.y"
    { (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 1007 "../parser.y"
    { (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 1008 "../parser.y"
    { (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));    }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 1009 "../parser.y"
    { (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 1012 "../parser.y"
    { (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));   }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 1013 "../parser.y"
    { (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 1015 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
    parser->call_args = 0;
  }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 1021 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (4)].n), (yyvsp[(3) - (4)].n));
    (yyval.n) = update_list((yyval.n), (yyvsp[(4) - (4)].n));
    parser->call_args = 0;
  }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1026 "../parser.y"
    { (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1027 "../parser.y"
    { (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 1028 "../parser.y"
    { (yyval.n) = ALLOC_N(token_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));     }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 1029 "../parser.y"
    { (yyval.n) = ALLOC_N(token_op_assign, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));  }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 1032 "../parser.y"
    { (yyval.n) = ALLOC_N(token_array, NULL, NULL); }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 1033 "../parser.y"
    { (yyval.n) = ALLOC_N(token_array, (yyvsp[(2) - (3)].n), NULL); fix_mrhs_left((yyval.n));  }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 1034 "../parser.y"
    { (yyval.n) = ALLOC_N(token_array, NULL, NULL); POP_STR; }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 1038 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 1039 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 1040 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 1043 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 267:

/* Line 1806 of yacc.c  */
#line 1044 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 1045 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 269:

/* Line 1806 of yacc.c  */
#line 1049 "../parser.y"
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

  case 270:

/* Line 1806 of yacc.c  */
#line 1070 "../parser.y"
    {
    (yyval.n) = ALLOC_N(token_object, NULL, NULL);
    (yyval.n)->endCol--;
    POP_STACK;
  }
    break;

  case 271:

/* Line 1806 of yacc.c  */
#line 1078 "../parser.y"
    { 
    (yyval.n) = alloc_node(token_hash, NULL, NULL);
    pop_pos(parser, (yyval.n));
    pop_start(parser, (yyval.n));
  }
    break;

  case 272:

/* Line 1806 of yacc.c  */
#line 1084 "../parser.y"
    {
    pop_pos(parser, parser->last_pos);
    (yyval.n) = ALLOC_N(token_hash, (yyvsp[(2) - (3)].n), NULL);
    fix_mrhs_left((yyval.n));
  }
    break;

  case 273:

/* Line 1806 of yacc.c  */
#line 1091 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 274:

/* Line 1806 of yacc.c  */
#line 1092 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);  }
    break;

  case 275:

/* Line 1806 of yacc.c  */
#line 1093 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 276:

/* Line 1806 of yacc.c  */
#line 1097 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));
    copy_range((yyval.n), (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));
  }
    break;

  case 277:

/* Line 1806 of yacc.c  */
#line 1102 "../parser.y"
    {
    (yyval.n) = alloc_node(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
    copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  }
    break;

  case 278:

/* Line 1806 of yacc.c  */
#line 1109 "../parser.y"
    {
    (yyval.n) = alloc_node(token_method_call, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    if ((yyvsp[(2) - (2)].n) == NULL) {
      copy_pos((yyval.n), (yyvsp[(1) - (2)].n));
    } else if ((yyvsp[(2) - (2)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    }
  }
    break;

  case 279:

/* Line 1806 of yacc.c  */
#line 1120 "../parser.y"
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

  case 280:

/* Line 1806 of yacc.c  */
#line 1130 "../parser.y"
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

  case 281:

/* Line 1806 of yacc.c  */
#line 1145 "../parser.y"
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

  case 282:

/* Line 1806 of yacc.c  */
#line 1155 "../parser.y"
    {
    struct node * n = alloc_node(token_object, (yyvsp[(1) - (3)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(3) - (3)].n));
    copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  }
    break;

  case 283:

/* Line 1806 of yacc.c  */
#line 1161 "../parser.y"
    {
    struct node * n = alloc_node(token_object, (yyvsp[(2) - (3)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(3) - (3)].n));
    if ((yyvsp[(3) - (3)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n));
    }
  }
    break;

  case 284:

/* Line 1806 of yacc.c  */
#line 1172 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 285:

/* Line 1806 of yacc.c  */
#line 1173 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 286:

/* Line 1806 of yacc.c  */
#line 1177 "../parser.y"
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

  case 287:

/* Line 1806 of yacc.c  */
#line 1190 "../parser.y"
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

  case 288:

/* Line 1806 of yacc.c  */
#line 1204 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 289:

/* Line 1806 of yacc.c  */
#line 1208 "../parser.y"
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

  case 290:

/* Line 1806 of yacc.c  */
#line 1218 "../parser.y"
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

  case 291:

/* Line 1806 of yacc.c  */
#line 1228 "../parser.y"
    {
    (yyval.n) = pop_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  }
    break;

  case 292:

/* Line 1806 of yacc.c  */
#line 1233 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 293:

/* Line 1806 of yacc.c  */
#line 1234 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 294:

/* Line 1806 of yacc.c  */
#line 1238 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 0;
  }
    break;

  case 295:

/* Line 1806 of yacc.c  */
#line 1243 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 1;
  }
    break;

  case 296:

/* Line 1806 of yacc.c  */
#line 1249 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 297:

/* Line 1806 of yacc.c  */
#line 1250 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 298:

/* Line 1806 of yacc.c  */
#line 1253 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 299:

/* Line 1806 of yacc.c  */
#line 1255 "../parser.y"
    {
    (yyval.n) = (yyvsp[(1) - (1)].n);
    parser->call_args = 1;
  }
    break;

  case 300:

/* Line 1806 of yacc.c  */
#line 1261 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 301:

/* Line 1806 of yacc.c  */
#line 1262 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 302:

/* Line 1806 of yacc.c  */
#line 1266 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 303:

/* Line 1806 of yacc.c  */
#line 1267 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 304:

/* Line 1806 of yacc.c  */
#line 1270 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 305:

/* Line 1806 of yacc.c  */
#line 1271 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 306:

/* Line 1806 of yacc.c  */
#line 1274 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 307:

/* Line 1806 of yacc.c  */
#line 1275 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 308:

/* Line 1806 of yacc.c  */
#line 1279 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 309:

/* Line 1806 of yacc.c  */
#line 1280 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 310:

/* Line 1806 of yacc.c  */
#line 1281 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 311:

/* Line 1806 of yacc.c  */
#line 1283 "../parser.y"
    {
    (yyval.n) = alloc_node(token_hash, (yyvsp[(1) - (1)].n), NULL);
    if ((yyvsp[(1) - (1)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (1)].n), (yyvsp[(1) - (1)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(1) - (1)].n), (yyvsp[(1) - (1)].n));
    }
  }
    break;

  case 312:

/* Line 1806 of yacc.c  */
#line 1293 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 313:

/* Line 1806 of yacc.c  */
#line 1294 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 314:

/* Line 1806 of yacc.c  */
#line 1295 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 315:

/* Line 1806 of yacc.c  */
#line 1299 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 316:

/* Line 1806 of yacc.c  */
#line 1300 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 317:

/* Line 1806 of yacc.c  */
#line 1303 "../parser.y"
    { (yyval.n) = ALLOC_N(token_plus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    }
    break;

  case 318:

/* Line 1806 of yacc.c  */
#line 1304 "../parser.y"
    { (yyval.n) = ALLOC_N(token_minus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   }
    break;

  case 319:

/* Line 1806 of yacc.c  */
#line 1305 "../parser.y"
    { (yyval.n) = ALLOC_N(token_mul, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 320:

/* Line 1806 of yacc.c  */
#line 1306 "../parser.y"
    { (yyval.n) = ALLOC_N(token_div, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 321:

/* Line 1806 of yacc.c  */
#line 1307 "../parser.y"
    { (yyval.n) = ALLOC_N(token_mod, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 322:

/* Line 1806 of yacc.c  */
#line 1308 "../parser.y"
    { (yyval.n) = ALLOC_N(token_exp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 323:

/* Line 1806 of yacc.c  */
#line 1309 "../parser.y"
    { (yyval.n) = ALLOC_N(token_bit_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); }
    break;

  case 324:

/* Line 1806 of yacc.c  */
#line 1310 "../parser.y"
    { (yyval.n) = ALLOC_N(token_bit_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 325:

/* Line 1806 of yacc.c  */
#line 1311 "../parser.y"
    { (yyval.n) = ALLOC_N(token_bit_xor, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); }
    break;

  case 326:

/* Line 1806 of yacc.c  */
#line 1312 "../parser.y"
    { (yyval.n) = ALLOC_N(token_lshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 327:

/* Line 1806 of yacc.c  */
#line 1313 "../parser.y"
    { (yyval.n) = ALLOC_N(token_rshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 328:

/* Line 1806 of yacc.c  */
#line 1314 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  }
    break;

  case 329:

/* Line 1806 of yacc.c  */
#line 1315 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n); fix_mrhs((yyval.n));  }
    break;

  case 330:

/* Line 1806 of yacc.c  */
#line 1316 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  }
    break;

  case 331:

/* Line 1806 of yacc.c  */
#line 1317 "../parser.y"
    { (yyval.n) = ALLOC_N(token_cmp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 332:

/* Line 1806 of yacc.c  */
#line 1318 "../parser.y"
    { (yyval.n) = ALLOC_N(token_eq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      }
    break;

  case 333:

/* Line 1806 of yacc.c  */
#line 1319 "../parser.y"
    { (yyval.n) = ALLOC_N(token_neq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 334:

/* Line 1806 of yacc.c  */
#line 1320 "../parser.y"
    { (yyval.n) = ALLOC_N(token_eqq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 335:

/* Line 1806 of yacc.c  */
#line 1321 "../parser.y"
    { (yyval.n) = ALLOC_N(token_match, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   }
    break;

  case 336:

/* Line 1806 of yacc.c  */
#line 1322 "../parser.y"
    { (yyval.n) = ALLOC_N(token_nmatch, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 337:

/* Line 1806 of yacc.c  */
#line 1323 "../parser.y"
    { (yyval.n) = ALLOC_N(token_greater, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); }
    break;

  case 338:

/* Line 1806 of yacc.c  */
#line 1324 "../parser.y"
    { (yyval.n) = ALLOC_N(token_lesser, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 339:

/* Line 1806 of yacc.c  */
#line 1325 "../parser.y"
    { (yyval.n) = ALLOC_N(token_geq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 340:

/* Line 1806 of yacc.c  */
#line 1326 "../parser.y"
    { (yyval.n) = ALLOC_N(token_leq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 341:

/* Line 1806 of yacc.c  */
#line 1327 "../parser.y"
    { (yyval.n) = ALLOC_N(token_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      }
    break;

  case 342:

/* Line 1806 of yacc.c  */
#line 1328 "../parser.y"
    { (yyval.n) = ALLOC_N(token_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 343:

/* Line 1806 of yacc.c  */
#line 1329 "../parser.y"
    { (yyval.n) = ALLOC_N(token_kw_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   }
    break;

  case 344:

/* Line 1806 of yacc.c  */
#line 1330 "../parser.y"
    { (yyval.n) = ALLOC_N(token_kw_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 345:

/* Line 1806 of yacc.c  */
#line 1331 "../parser.y"
    { (yyval.n) = ALLOC_N(token_dot2, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    }
    break;

  case 346:

/* Line 1806 of yacc.c  */
#line 1332 "../parser.y"
    { (yyval.n) = ALLOC_N(token_dot3, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    }
    break;

  case 347:

/* Line 1806 of yacc.c  */
#line 1334 "../parser.y"
    {
    (yyval.n) = ALLOC_C(token_ternary, (yyvsp[(1) - (8)].n), (yyvsp[(4) - (8)].n), (yyvsp[(8) - (8)].n));
  }
    break;

  case 348:

/* Line 1806 of yacc.c  */
#line 1337 "../parser.y"
    { (yyval.n) = ALLOC_N(token_kw_not, (yyvsp[(3) - (3)].n), NULL);}
    break;

  case 349:

/* Line 1806 of yacc.c  */
#line 1338 "../parser.y"
    { (yyval.n) = ALLOC_N(token_neg, (yyvsp[(3) - (3)].n), NULL);   }
    break;

  case 350:

/* Line 1806 of yacc.c  */
#line 1339 "../parser.y"
    { (yyval.n) = ALLOC_N(token_not, (yyvsp[(3) - (3)].n), NULL);   }
    break;

  case 351:

/* Line 1806 of yacc.c  */
#line 1340 "../parser.y"
    { (yyval.n) = ALLOC_N(token_unary_plus, (yyvsp[(3) - (3)].n), NULL);  }
    break;

  case 352:

/* Line 1806 of yacc.c  */
#line 1341 "../parser.y"
    { (yyval.n) = ALLOC_N(token_unary_minus, (yyvsp[(3) - (3)].n), NULL); }
    break;

  case 353:

/* Line 1806 of yacc.c  */
#line 1342 "../parser.y"
    { (yyval.n) = ALLOC_N(token_defined, (yyvsp[(3) - (3)].n), NULL); copy_end((yyval.n), (yyvsp[(3) - (3)].n));  }
    break;

  case 354:

/* Line 1806 of yacc.c  */
#line 1343 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 355:

/* Line 1806 of yacc.c  */
#line 1344 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 356:

/* Line 1806 of yacc.c  */
#line 1345 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 357:

/* Line 1806 of yacc.c  */
#line 1346 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;



/* Line 1806 of yacc.c  */
#line 5164 "../parser.c"
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
#line 1349 "../parser.y"

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
      else if (t == CLASS) {
        /* check for class() method */
        if (parser->dot_seen) {
          push_stack(parser, buffer);
          t = FNAME;
          parser->dot_seen = 0;
        } else
          parser->class_seen = 1;
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
/* TODO printf("Kind: %i, Buffer: %s Expr_seen: %i\n", t, buffer, parser->expr_seen); */
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

