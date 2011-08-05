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
#line 152 "../parser.y"
  struct node * n;  


/* Line 293 of yacc.c  */
#line 339 "../parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 351 "../parser.c"

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
#define YYLAST   2677

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  139
/* YYNRULES -- Number of rules.  */
#define YYNRULES  357
/* YYNRULES -- Number of states.  */
#define YYNSTATES  640

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
     832,   835,   838,   842,   845,   849,   853,   857,   861,   864,
     869,   872,   874,   877,   880,   883,   884,   886,   887,   889,
     891,   893,   895,   897,   899,   903,   905,   909,   911,   913,
     915,   917,   919,   921,   924,   927,   929,   931,   936,   941,
     946,   951,   956,   961,   966,   971,   976,   981,   986,   990,
     994,   998,  1003,  1008,  1013,  1018,  1023,  1028,  1033,  1038,
    1043,  1048,  1053,  1058,  1063,  1068,  1073,  1078,  1087,  1091,
    1095,  1099,  1103,  1107,  1111,  1114,  1116,  1118
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     107,     0,    -1,    46,    -1,   108,    -1,   116,    -1,   121,
      -1,   217,    -1,   226,   148,    -1,   223,    -1,   108,   175,
     244,    -1,   108,   176,   244,    -1,   108,   177,   244,    -1,
     108,   178,   244,    -1,   244,    -1,   108,    -1,   109,   205,
     108,    -1,   134,    -1,    48,    -1,   138,    -1,   112,    -1,
      53,    -1,    37,    -1,    63,    -1,   111,    -1,    39,    -1,
      38,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    52,    -1,   112,    52,    -1,   110,
      -1,   218,    -1,   229,    -1,   231,    -1,   134,    -1,   229,
      -1,   231,    -1,    48,    -1,   138,    -1,   112,    -1,    53,
      -1,    37,    -1,    63,    -1,   218,    -1,   111,    -1,    21,
      -1,    23,    -1,    24,    -1,    22,    -1,     6,   119,    -1,
      33,   120,   120,    -1,   117,    -1,   118,    -1,    29,    -1,
      29,   244,    -1,    28,    -1,    28,   244,    -1,   120,    -1,
     120,   191,   119,    -1,    51,    -1,    50,    -1,   138,    -1,
     174,   244,   171,   200,   140,    10,    -1,   180,   244,   171,
     200,   140,    10,    -1,   181,   244,   172,   200,    10,    -1,
     182,   244,   172,   200,    10,    -1,   183,   244,   206,   169,
      10,    -1,   183,   169,    10,    -1,    35,    79,   200,    80,
      -1,    36,    79,   200,    80,    -1,   185,   214,   189,   243,
     172,   200,    10,    -1,     7,   146,    10,    -1,    -1,   186,
     130,   122,   132,   146,    10,    -1,    -1,   186,   131,   123,
     156,    82,   146,    10,    -1,    -1,   187,   133,   124,   146,
      10,    -1,    -1,   188,   133,   125,   146,    10,    -1,    -1,
     188,   133,   147,   126,   146,    10,    -1,    -1,   188,    69,
     240,   127,   204,   146,    10,    -1,    50,    -1,   135,    -1,
     128,    -1,   137,    -1,   135,   207,   128,    -1,   128,    -1,
     135,   207,   136,    -1,   136,    -1,   156,   208,    -1,   208,
      -1,    92,    -1,   227,    -1,    51,    -1,   135,    -1,    47,
      -1,    58,    -1,    57,    -1,    92,    -1,    51,    -1,    54,
      -1,    92,    -1,    49,    -1,    91,    -1,   141,    -1,   179,
     244,   171,   200,   140,    -1,    -1,    15,   200,    -1,    -1,
       9,   200,    -1,    -1,   144,    -1,   145,    -1,   144,   145,
      -1,     8,   165,   171,   200,    -1,   200,   143,   141,   142,
      -1,    83,   202,   133,    -1,    -1,   149,    -1,   150,    -1,
     151,    -1,   196,   153,   201,    80,    -1,   196,   201,    80,
      -1,   173,   190,   153,   200,    10,    -1,   173,   200,    10,
      -1,   157,    -1,   191,    76,   163,    -1,   159,   191,    -1,
     159,   191,   160,   158,    -1,   159,   191,   160,   191,   159,
     158,    -1,    77,   152,   154,    77,    -1,    77,   154,    77,
      -1,    77,   152,    77,    -1,    73,   155,    -1,   135,    -1,
     155,   191,   135,    -1,   157,    -1,    76,   163,    -1,   192,
     157,   193,    -1,   192,    76,   163,   193,    -1,   159,   158,
      -1,   160,   191,   159,   158,    -1,   160,   158,    -1,   162,
     191,   159,   158,    -1,   162,   158,    -1,   162,   191,   160,
     191,   159,   158,    -1,   162,   191,   160,   158,    -1,   159,
     191,   162,   191,   159,   158,    -1,   159,   191,   162,   158,
      -1,   159,   191,   162,   191,   160,   191,   159,   158,    -1,
     159,   191,   162,   191,   160,   158,    -1,    -1,   191,    76,
     163,    -1,   163,    -1,   159,   191,   163,    -1,    88,   163,
      -1,   163,    93,   113,    -1,   161,    -1,   162,   191,   161,
      -1,    51,    -1,   164,    -1,    92,    -1,    57,    -1,    58,
      -1,    47,    -1,    -1,   166,    -1,   167,   168,    -1,   244,
      -1,   167,   191,   244,    -1,    -1,    71,   202,   134,    -1,
     184,   244,   171,   200,   170,    -1,   141,    -1,   169,    -1,
     204,    -1,    13,    -1,   204,    13,    -1,   204,    -1,    26,
      -1,    27,    -1,    11,   202,    -1,    11,    -1,    12,    -1,
      18,    -1,    19,    -1,    14,   202,    -1,    12,   202,    -1,
      18,   202,    -1,    19,   202,    -1,    16,   202,    -1,    17,
     202,    -1,    20,   202,    -1,     5,   202,    -1,     4,   202,
      -1,     3,   202,    -1,    25,   202,    -1,    -1,    46,    -1,
      64,   202,    -1,    81,   202,    -1,   202,    82,    -1,    59,
     202,    -1,   202,    60,    -1,    79,   202,    -1,   202,    80,
      -1,    93,   202,    -1,    94,   202,    -1,   206,   109,   206,
      -1,   206,    -1,   109,   206,    -1,    -1,   203,    -1,    46,
      -1,   203,    46,    -1,    73,    -1,    46,    -1,   204,    -1,
     205,   204,    -1,    -1,   205,    -1,    61,    -1,   103,    -1,
      46,    -1,    73,    -1,   214,   191,   210,    -1,   214,   191,
      -1,   244,    -1,   192,   209,   193,    -1,    88,   134,    -1,
      88,    -1,    -1,   212,    -1,   213,    -1,   212,   213,    -1,
     194,   219,   195,    -1,   244,    -1,   214,   191,    -1,   214,
     191,   210,    -1,   244,    -1,   215,   191,   244,    -1,   134,
     198,   113,    -1,   134,   199,   113,    -1,   134,   198,   223,
      -1,   134,   199,   223,    -1,   214,   198,   215,    -1,   214,
     199,   215,    -1,   214,   198,   226,   148,    -1,   214,   199,
     226,   148,    -1,   214,   198,   223,    -1,   214,   199,   223,
      -1,   214,   198,   121,    -1,   214,   199,   121,    -1,   194,
      60,    -1,   194,   220,   195,    -1,    55,    -1,   244,    -1,
     216,    -1,   223,    -1,   219,    -1,   220,   191,    -1,   220,
     191,   219,    -1,   222,   202,   219,   195,   211,    -1,    56,
      -1,   196,    80,    -1,   196,   224,   197,    -1,   225,    -1,
     224,   191,    -1,   224,   191,   225,    -1,   244,    71,   202,
     244,    -1,   139,   202,   244,    -1,   128,   236,    -1,   231,
     236,    -1,   227,   234,    -1,   137,   228,    -1,   137,   103,
     128,    -1,   103,   137,    -1,   228,   103,   129,    -1,   136,
     235,   193,    -1,   230,   235,   193,    -1,   137,   103,   136,
      -1,   110,   232,    -1,   192,   244,   193,   232,    -1,   229,
     232,    -1,   233,    -1,   232,   233,    -1,    61,   128,    -1,
      61,   229,    -1,    -1,   236,    -1,    -1,   237,    -1,   226,
      -1,   238,    -1,   226,    -1,   239,    -1,   244,    -1,   238,
     191,   241,    -1,   242,    -1,   239,   191,   242,    -1,   244,
      -1,   223,    -1,   244,    -1,   223,    -1,   224,    -1,   241,
      -1,    76,   244,    -1,    88,   244,    -1,   244,    -1,   223,
      -1,   244,    86,   202,   244,    -1,   244,    87,   202,   244,
      -1,   244,    88,   202,   244,    -1,   244,    89,   202,   244,
      -1,   244,    90,   202,   244,    -1,   244,    66,   202,   244,
      -1,   244,    76,   202,   244,    -1,   244,    77,   202,   244,
      -1,   244,    78,   202,   244,    -1,   244,    69,   202,   244,
      -1,   244,    70,   202,   244,    -1,   192,   244,   193,    -1,
     192,   217,   193,    -1,   192,   226,   193,    -1,   244,    95,
     202,   244,    -1,   244,    96,   202,   244,    -1,   244,    98,
     202,   244,    -1,   244,    97,   202,   244,    -1,   244,    99,
     202,   244,    -1,   244,   100,   202,   244,    -1,   244,    84,
     202,   244,    -1,   244,    83,   202,   244,    -1,   244,   101,
     202,   244,    -1,   244,   102,   202,   244,    -1,   244,    74,
     202,   244,    -1,   244,    75,   202,   244,    -1,   244,    31,
     202,   244,    -1,   244,    30,   202,   244,    -1,   244,   105,
     202,   244,    -1,   244,   104,   202,   244,    -1,   244,    72,
     202,   244,   202,    65,   202,   244,    -1,    32,   202,   244,
      -1,    62,   202,   244,    -1,    85,   202,   244,    -1,    68,
     202,   244,    -1,    67,   202,   244,    -1,    34,   202,   244,
      -1,   114,   148,    -1,   115,    -1,   221,    -1,    50,    -1
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
    1069,  1077,  1083,  1091,  1092,  1093,  1096,  1101,  1108,  1117,
    1127,  1142,  1152,  1160,  1161,  1164,  1177,  1192,  1195,  1205,
    1215,  1221,  1222,  1225,  1230,  1237,  1238,  1241,  1242,  1245,
    1246,  1253,  1254,  1258,  1259,  1262,  1263,  1266,  1267,  1271,
    1272,  1273,  1284,  1285,  1286,  1290,  1291,  1294,  1295,  1296,
    1297,  1298,  1299,  1300,  1301,  1302,  1303,  1304,  1305,  1306,
    1307,  1308,  1309,  1310,  1311,  1312,  1313,  1314,  1315,  1316,
    1317,  1318,  1319,  1320,  1321,  1322,  1323,  1324,  1328,  1329,
    1330,  1331,  1332,  1333,  1334,  1335,  1336,  1337
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
  "dot_items", "dot_item", "opt_call_args", "opt_call_args_paren",
  "m_call_args", "m_call_args_paren", "call_args", "call_args_paren",
  "exp_or_hash", "exp_hash", "exp_paren", "exp_for", "exp", 0
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
     124,   121,   125,   121,   126,   121,   127,   121,   128,   128,
     129,   129,   130,   130,   131,   131,   132,   132,   133,   133,
     133,   134,   134,   134,   134,   134,   135,   136,   137,   138,
     139,   140,   140,   141,   141,   142,   142,   143,   143,   144,
     144,   145,   146,   147,   148,   148,   149,   149,   150,   150,
     151,   151,   152,   152,   152,   152,   152,   153,   153,   153,
     154,   155,   155,   156,   156,   156,   156,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   158,   158,
     159,   159,   160,   161,   162,   162,   163,   163,   164,   164,
     164,   164,   165,   165,   166,   167,   167,   168,   168,   169,
     170,   170,   171,   171,   171,   172,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   200,   201,   202,   202,
     203,   203,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   208,   209,   209,   210,   210,   210,   210,   211,   211,
     212,   212,   213,   214,   214,   214,   215,   215,   216,   216,
     216,   216,   217,   217,   217,   217,   217,   217,   217,   217,
     218,   218,   218,   219,   219,   219,   220,   220,   220,   221,
     222,   223,   223,   224,   224,   224,   225,   225,   226,   226,
     226,   227,   227,   228,   228,   229,   229,   230,   231,   231,
     231,   232,   232,   233,   233,   234,   234,   235,   235,   236,
     236,   237,   237,   238,   238,   239,   239,   240,   240,   241,
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
       2,     2,     3,     2,     3,     3,     3,     3,     2,     4,
       2,     1,     2,     2,     2,     0,     1,     0,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     1,     1,     1,
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
     218,   218,   218,   105,     0,     3,     0,    48,    43,   124,
     355,     4,    55,    56,     5,     0,    38,   101,   297,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,    47,   356,   218,     8,   124,
     295,    39,   297,    40,    13,   220,   202,   219,   201,   200,
      64,    63,    53,    61,    65,   223,   222,     0,   117,   224,
     227,   216,   188,   194,   197,   195,   196,   199,   357,   101,
       0,    40,    60,    58,     0,     0,     0,   226,   226,   209,
       0,     0,     0,   211,   207,     0,     1,   189,   190,   191,
     192,     0,     0,     0,     0,     0,   288,   291,    33,   187,
     354,   125,   126,   127,   226,     0,   299,   278,   300,   303,
       0,     0,   110,   218,   310,   311,   273,   301,   218,   298,
     302,   312,   305,   309,     0,   281,     0,     0,     0,     0,
     218,     0,     0,   226,     0,   243,    88,    93,    76,    78,
      89,    95,   100,    98,    80,     0,    99,     0,    82,   218,
     218,   243,   260,    38,   264,   266,   218,   265,   263,   271,
     218,     0,   218,   218,   218,   244,     0,     0,     0,     7,
     280,   296,   290,   218,   279,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   221,     0,    75,   172,   113,   118,   119,
     225,    14,   226,     0,   348,    54,   353,     0,     0,   349,
     352,   351,   350,     9,    10,    11,    12,   108,   293,    89,
     294,   292,   223,     0,     0,     0,   226,     0,     0,     0,
     313,   314,     0,   274,   285,     0,     0,   218,   282,   287,
     283,     0,   183,   226,   182,   226,   186,   226,   185,   226,
     198,    71,     0,     0,   218,     0,     0,     0,   228,   229,
       0,   226,     0,   308,    86,   307,   218,   226,    84,   329,
     330,   328,     0,     0,   267,   261,     0,   272,     0,   206,
     213,   214,   237,     0,   245,   234,   258,   252,   256,   124,
     246,   259,   253,   257,   124,   218,   286,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,     0,   173,   177,   175,
     226,   115,   120,   227,   215,    72,    73,   226,   131,   171,
     166,   169,   170,     0,     0,   168,     0,     0,   132,   158,
     158,   164,   158,   160,   167,     0,   217,     0,   129,   304,
     277,   275,   208,   306,     0,    90,   284,    91,   113,   184,
     113,     0,     0,   226,     0,   203,   316,     0,   315,   230,
     231,     0,   226,     0,   143,   158,     0,    97,     0,    92,
      94,     0,     0,     0,     0,   226,   289,    21,    17,    20,
      22,    34,    23,    19,   248,    16,    18,     0,    35,   250,
      36,    37,   249,   251,   268,   210,   212,   105,   236,   218,
       0,     0,   254,   255,   238,   344,   343,   322,   326,   327,
     218,   341,   342,   323,   324,   325,   338,   337,   317,   318,
     319,   320,   321,   331,   332,   334,   333,   335,   336,   339,
     340,   346,   345,   226,   218,   174,     0,   114,   226,   122,
      15,     0,   141,   140,   162,   139,     0,   138,   147,   134,
     149,     0,   151,     0,     0,     0,   128,   276,   218,     0,
     111,     0,     0,    68,    69,   113,    70,   226,   144,     0,
      96,     0,     0,   218,   226,    81,   226,   123,    83,     0,
     218,   235,   244,   247,     0,   269,   239,   240,     0,   121,
       0,   176,   116,   130,     0,   137,     0,   158,   158,   161,
     158,   160,   158,   158,   165,   163,   133,   193,    66,     0,
      67,   180,   181,   179,     0,    77,   218,   145,     0,     0,
      85,     0,   245,   218,   241,   218,   178,   142,   159,   135,
       0,   155,     0,   148,     0,   150,   153,     0,   226,    74,
     146,    79,    87,   242,     0,   158,   158,   158,   161,   158,
     113,   347,   136,   154,   157,     0,   152,   112,   158,   156
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    54,   261,   286,    56,    57,    58,   464,    59,    60,
      61,    62,    63,   102,   103,    64,   316,   317,   321,   327,
     455,   452,    65,   426,   188,   189,   442,   194,    66,   119,
      68,   120,    70,   163,   539,   540,   519,   257,   258,   259,
     107,   328,   150,   151,   152,   153,   406,   287,   407,   523,
     443,   444,   528,   445,   410,   411,   412,   413,   414,   386,
     387,   388,   515,   181,   593,   303,   307,   154,    71,   141,
     142,   143,   144,   541,    72,    73,    74,    75,   182,    76,
      77,    78,    79,   315,   283,   614,    80,   294,    81,   335,
      82,   337,   216,   217,   108,   288,   295,    97,   109,   110,
     111,   320,   447,   479,   344,   565,   566,   567,    83,   347,
     204,    84,    85,   205,   206,    86,    87,    88,   165,   166,
      89,    90,   175,    91,    92,   121,   146,   147,   220,   168,
     157,   169,   158,   170,   324,   171,   172,   437,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -490
static const yytype_int16 yypact[] =
{
     973,    65,    65,    65,   233,    -1,    65,    65,    65,    65,
      65,    65,  -490,  -490,  -490,  -490,  2195,  2195,    65,   233,
      65,   -12,    45,    74,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,    76,  -490,  2251,  -490,  -490,   102,
    -490,  -490,  -490,  -490,  -490,    65,    65,   113,    65,    65,
      65,    65,    65,    83,   179,   305,   145,   147,    21,    15,
    -490,  -490,  -490,  -490,  -490,  2307,   152,  2363,  1679,   120,
     167,  2195,  2195,  2195,  2195,  1318,  2195,   187,    -3,   134,
    2307,  1858,  1914,    89,  -490,  -490,  -490,    65,  -490,    15,
    2307,   145,  1679,  2307,  1348,  -490,  -490,   184,  -490,  -490,
    -490,  -490,  -490,   170,  -490,  -490,  -490,   226,   231,  -490,
      -1,  1139,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
     155,  -490,  1605,  1605,  2195,   233,  2195,    -1,    -1,  -490,
    2195,  2195,  2195,  -490,  -490,  2195,  -490,  -490,  -490,  -490,
    -490,  2195,  2195,  2195,  2195,    30,   145,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,    23,  1056,  -490,  -490,   170,  1605,
    2195,  2195,  -490,    65,  -490,   170,  -490,  -490,    65,  -490,
     170,  -490,  -490,  1507,    30,   162,   614,   614,  1244,  1244,
      65,   258,  2195,  1409,    37,  1605,  -490,  -490,  -490,  -490,
     -25,  -490,  -490,    83,  -490,   171,  -490,  2026,   192,    65,
      65,  1470,  -490,   117,  -490,  -490,   168,  -490,  1605,  -490,
     168,  1507,    65,    65,    65,  2082,  1210,  1210,  2026,  -490,
    -490,  -490,   145,    65,  -490,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,  -490,   233,  -490,  2195,   255,   231,  -490,
    -490,   305,    -1,   235,  2464,  -490,  2464,   205,   206,  -490,
     246,  -490,  -490,  1605,  1605,  1605,  1605,  -490,  -490,  -490,
    -490,  -490,   236,   238,   309,    85,    -1,  1139,   245,  1970,
    1605,  1605,  2195,  2139,  -490,   253,  1740,    65,  -490,  -490,
    -490,    41,  -490,    -1,   324,    -1,  -490,    -1,  -490,    -1,
    -490,  -490,   614,   321,    65,  2026,   678,   710,  -490,  -490,
     187,    -1,    41,  -490,  -490,  1605,    65,    -1,  -490,  -490,
    -490,   145,  2419,  2419,  2026,  -490,   279,  -490,   260,  -490,
    -490,  -490,    28,  2307,  -490,  1605,  -490,   170,  -490,    15,
    1605,  -490,   170,  -490,    15,    65,  -490,  2195,  2195,  2195,
    2195,  2195,  2195,  2195,  2195,  2195,  2195,  2195,  2195,  2195,
    2195,  2195,  2195,  2195,  2195,  2195,  2195,  2195,  2195,  2195,
    2195,  2195,  2195,  2195,  2195,  -490,    22,  -490,   100,  1605,
      -1,   363,  -490,   883,  -490,  -490,  -490,    -1,  -490,  -490,
    -490,  -490,  -490,   333,   374,  -490,    26,   308,  -490,   170,
     170,  -490,   170,   293,  -490,   311,  -490,   312,  -490,  -490,
    1605,  -490,  -490,  -490,  2195,  -490,  -490,  -490,   232,  -490,
     232,   379,   383,    -1,   386,  -490,  -490,    24,  1605,  -490,
    -490,   374,    -1,    25,  -490,   170,    99,  -490,   325,  -490,
    -490,   399,    -1,    -3,   402,    -1,   145,  -490,  -490,  -490,
    -490,   145,  -490,   367,  -490,  -490,  -490,  2195,  -490,  -490,
     145,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,    65,
      89,  2195,  -490,  -490,   364,  2464,  2464,   246,   244,   244,
    1568,   782,  2538,   740,   567,   567,   727,   727,   129,   129,
     246,   246,   246,  2575,  2575,  2575,  2575,  2575,  2575,   727,
     727,  2501,  2501,    -1,    65,  -490,  2195,  -490,    -1,  -490,
     305,   414,  -490,   170,  -490,  -490,   349,  -490,  -490,   353,
    -490,    55,  -490,   353,  2465,   374,  -490,  1605,    65,   417,
    -490,  2195,   423,  -490,  -490,    92,  -490,    -1,  -490,   428,
    -490,    55,   374,    65,    -1,  -490,    -1,  -490,  -490,   432,
    1568,  -490,  1801,  1605,  2026,  -490,   364,  -490,   375,  -490,
      28,  1605,  -490,  -490,   333,  -490,   374,   170,   170,   293,
     170,  -490,   170,   170,  -490,  -490,  -490,  -490,  -490,   614,
    -490,  -490,  -490,  -490,   433,  -490,    65,  -490,   436,   439,
    -490,   145,     8,    65,  -490,    65,  -490,  -490,  -490,  -490,
      55,  -490,   353,  -490,    55,  -490,  -490,    55,    -1,  -490,
    -490,  -490,  -490,  -490,  2195,   170,   170,   170,  -490,   170,
     232,  2464,  -490,  -490,  -490,    55,  -490,  -490,   170,  -490
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -490,  -490,     4,   339,  -307,  -305,  -303,  -310,  -490,  -490,
    -490,  -490,  -490,   190,    14,    39,  -490,  -490,  -490,  -490,
    -490,  -490,     6,  -490,  -490,  -490,  -490,   -70,   -28,   430,
     -56,   521,    42,  -490,  -410,  -247,  -490,  -490,  -490,   195,
    -287,  -490,   -83,  -490,  -490,  -490,  -490,   174,    52,  -490,
     142,  -248,   -33,  -222,  -482,  -489,  -381,   130,  -490,  -490,
    -490,  -490,  -490,  -291,  -490,  -174,  -165,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,    51,  -128,  -182,  -445,  -340,
     -46,  -490,   259,   261,   274,   214,   242,  -490,   -17,  -157,
    -145,  -490,    60,  -490,   -58,  -490,  -490,   -61,   -65,   291,
    -490,   -64,  -301,  -194,  -490,  -490,  -490,    84,   427,   218,
     434,   -71,  -490,  -140,  -490,   104,   -89,  -134,  -490,   421,
     132,  -490,  -490,  -490,  -490,   227,   219,  -490,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -244
static const yytype_int16 yytable[] =
{
     122,   123,   222,   305,    55,   280,   219,   196,   196,   198,
     391,   184,   281,   155,   309,   484,   199,   329,   330,   331,
     542,   191,   434,   472,   355,   461,   461,   462,   462,   463,
     463,   468,   468,   125,   451,   302,   318,   408,   313,   564,
     454,   356,   149,   155,   584,   105,   104,   577,   192,   159,
     306,   583,   173,   203,  -232,   176,   177,   178,   179,   183,
     185,   104,   314,   409,   201,   208,   211,   127,   105,   282,
     105,   439,   106,   148,   159,    33,   173,   159,   319,    37,
     186,    37,   -19,   187,    40,    43,    44,   343,   281,   193,
    -232,   186,    37,   260,    50,   106,   106,   106,   440,   403,
    -204,   212,   399,   525,    93,   393,   400,   390,   264,   180,
     266,    95,   401,   402,   269,   270,   271,   394,   299,   272,
     477,   564,   277,   584,   128,   273,   274,   275,   276,   393,
     627,   576,   399,   277,   215,   -21,   400,   -17,   433,   265,
     474,   416,   401,   402,   290,   291,   399,   405,   578,   212,
     400,   278,   164,   212,   254,   549,   401,   402,   403,   304,
     304,   308,   308,   -20,   212,   207,   312,   104,   559,    93,
     578,   514,    93,   404,   -22,   552,   164,   405,   -16,   136,
     298,   325,   213,   214,    93,   192,  -108,   404,   446,   446,
     203,   405,   470,   470,    93,   227,    93,    93,   553,   345,
     350,   350,   208,   197,   467,   467,   145,   299,   -23,   289,
     213,   214,   513,   -16,    95,    93,   293,   240,   241,   242,
     637,   296,   221,   174,   585,   224,   193,   461,   -18,   462,
     253,   463,   212,   468,   212,   215,   255,   186,    37,   256,
     389,    40,   456,    96,    98,    99,   538,   390,   112,   113,
     114,   115,   116,   117,   592,   346,   351,   334,   263,    93,
     124,   293,   126,   623,   450,   301,   482,   598,   311,   599,
     390,   483,   547,   173,   322,   326,   420,   211,   480,   199,
     173,   323,    35,   100,   101,   395,   396,   129,   130,    40,
     131,   132,   133,   134,   135,   304,   104,   561,   591,   438,
     348,   353,   207,   155,   465,   465,   203,   425,   155,   580,
     227,   582,   227,  -205,   478,   285,   137,   138,   208,   398,
      93,    93,   281,   139,   140,   418,   449,   201,   298,   218,
     238,   239,   240,   241,   242,   422,   415,   429,   180,   475,
     476,   485,   486,   487,   488,   489,   490,   491,   492,   493,
     494,   495,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   512,   304,
     603,   597,   518,   164,   466,   466,   260,   530,   601,   532,
     164,   222,   196,   557,    37,   527,   534,   535,   625,   543,
     626,    93,   536,   544,   470,   629,   546,   520,   481,   436,
     399,   267,   268,   481,   400,   292,   467,   554,   537,   555,
     401,   402,   558,   638,   620,   618,   469,   473,   207,   148,
     308,   399,   310,    45,   573,   400,   575,   588,   284,   576,
      67,   401,   402,   590,   343,   556,   471,   471,   595,   516,
     605,   404,   600,   619,   385,   405,   621,    93,   336,   622,
     262,   560,   338,   392,   339,   340,   341,   397,   526,   448,
     529,   531,   332,   533,   333,   563,   405,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,    67,   551,    93,    67,   156,
     571,   417,   167,   550,   602,   604,   465,   190,   352,   210,
      67,   421,   456,   223,   200,   423,   419,     0,     0,     0,
      67,    69,    67,    67,   156,   589,   167,   156,     0,     0,
       0,   562,     0,     0,   524,     0,   203,     0,     0,   424,
       0,    67,   606,     0,   609,   611,   345,   613,   208,   615,
     616,     0,     0,     0,     0,     0,   435,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   453,     0,
       0,   548,   304,     0,   574,   279,   466,   428,     0,   430,
       0,   431,     0,   432,     0,    67,    69,     0,     0,    69,
       0,     0,   632,   633,   634,     0,   636,   336,     0,   195,
     195,    69,     0,     0,   279,   639,     0,     0,   631,     0,
       0,    69,     0,    69,    69,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   302,   610,   612,
       0,     0,    69,   227,   617,     0,   228,   229,   471,     0,
       0,     0,     0,   233,   225,   226,    67,    67,   207,     0,
     349,   354,     0,   238,   239,   240,   241,   242,     0,   579,
     105,   581,     0,     0,   517,   586,     0,     0,     0,     0,
       0,   521,     0,     0,     0,     0,    69,     0,   635,     0,
     227,   579,   596,   228,   229,     0,   230,   106,   231,   232,
     233,   234,   235,     0,     0,   300,     0,   236,   237,     0,
     238,   239,   240,   241,   242,     0,   608,   545,     0,   243,
     244,   245,   246,   247,   248,   249,   250,    67,   251,   252,
       0,     0,     0,     0,   439,   399,     0,     0,     0,   400,
       0,   279,   568,     0,     0,   401,   402,    69,    69,     0,
     581,     0,     0,     0,   628,     0,     0,   581,     0,     0,
     279,   440,   279,     0,   441,     0,   570,   399,     0,    51,
       0,   400,     0,     0,     0,   581,   404,   401,   402,     0,
     405,     0,     0,    67,     0,     0,     0,   200,     0,     0,
     587,     0,     0,     0,     0,     0,   441,   569,     0,     0,
       0,    51,   572,   227,     0,     0,   228,   229,   404,     0,
       0,     0,   405,   233,   234,   235,   227,     0,    69,   228,
     229,     0,     0,   238,   239,   240,   241,   242,     0,     0,
       0,   594,   427,    67,     0,     0,   238,   239,   240,   241,
     242,     0,     0,   522,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   300,     0,   336,     0,   624,   227,     0,
       0,   228,   229,     0,     0,     0,     0,   232,   233,   234,
     235,     0,     0,     0,    69,   236,   237,     0,   238,   239,
     240,   241,   242,     0,     0,     0,     0,   243,   244,   245,
     246,   247,   248,   249,   250,     0,     1,     2,     3,     4,
       5,     0,   630,     0,     6,     7,     0,     0,     0,     8,
       0,     9,    10,    11,    12,    13,    14,    15,     0,     0,
       0,    16,    17,     0,    69,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,   105,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,    46,    47,     0,     0,     0,
      48,    49,     0,     0,     0,     0,   106,     0,     0,     0,
       0,     0,    50,     0,    51,     0,     0,     0,    52,     0,
       0,     0,     0,     0,   195,    53,     1,     2,     3,     4,
       5,     0,     0,     0,     6,     7,     0,     0,     0,     8,
       0,     9,    10,    11,    12,    13,    14,    15,     0,     0,
       0,    16,    17,     0,   607,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,    46,    47,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,    51,     0,     0,     0,    52,     1,
       2,     3,     4,     5,     0,    53,     0,     6,     7,     0,
       0,     0,     8,     0,     9,    10,    11,    12,    13,    14,
      15,     0,     0,     0,    16,    17,     0,     0,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     0,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     0,     0,    46,    47,
       0,     0,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,   285,     0,    50,     0,    51,     0,     0,
       0,    52,     1,     2,     3,     4,     5,     0,    53,     0,
       6,     7,     0,     0,     0,     8,     0,     9,    10,    11,
      12,    13,    14,    15,     0,     0,     0,    16,    17,     0,
       0,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,    46,    47,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     1,     2,     3,     0,     5,    50,     0,
      51,     6,     7,     0,    52,     0,     8,     0,     9,    10,
      11,    53,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,     0,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
     306,     0,    46,    47,   225,   226,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
     105,    51,     0,     0,     0,    52,     0,     0,     0,     0,
       0,     0,    53,     0,     0,     0,     0,     0,     0,     0,
     227,     0,     0,   228,   229,     0,   230,   106,   231,   232,
     233,   234,   235,     0,     0,     0,     0,   236,   237,     0,
     238,   239,   240,   241,   242,   180,     0,     0,     0,   243,
     244,   245,   246,   247,   248,   249,   250,     0,   251,   252,
      18,     0,    20,     0,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    33,    34,    35,   118,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   225,   226,
      46,    47,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,     0,    52,     0,     0,     0,     0,     0,     0,
      53,     0,  -243,     0,   227,     0,     0,   228,   229,     0,
     230,     0,   231,   232,   233,   234,   235,     0,     0,     0,
       0,   236,   237,     0,   238,   239,   240,   241,   242,   225,
     226,  -243,  -243,   243,   244,   245,   246,   247,   248,   249,
     250,     0,   251,   252,     0,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   227,     0,     0,   228,   229,
       0,   230,   106,   231,   232,   233,   234,   235,     0,     0,
       0,     0,   236,   237,     0,   238,   239,   240,   241,   242,
     225,   226,     0,     0,   243,   244,   245,   246,   247,   248,
     249,   250,     0,   251,   252,     0,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   227,   225,   226,   228,
     229,     0,   230,     0,   231,   232,   233,   234,   235,     0,
       0,     0,  -218,   236,   237,     0,   238,   239,   240,   241,
     242,     0,     0,     0,     0,   243,   244,   245,   246,   247,
     248,   249,   250,   227,   251,   252,   228,   229,   297,   230,
       0,   231,   232,   233,   234,   235,     0,     0,     0,     0,
     236,   237,     0,   238,   239,   240,   241,   242,   225,   226,
       0,     0,   243,   244,   245,   246,   247,   248,   249,   250,
       0,   251,   252,     0,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   227,   225,   226,   228,   229,     0,
     230,     0,   231,   232,   233,   234,   235,     0,     0,     0,
       0,   236,   237,     0,   238,   239,   240,   241,   242,     0,
       0,     0,     0,   243,   244,   245,   246,   247,   248,   249,
     250,   227,   251,   252,   228,   229,     0,   230,     0,   231,
     232,   233,   234,   235,     0,     0,     0,     0,   236,   237,
       0,   238,   239,   240,   241,   242,     0,     0,     0,     0,
     243,   244,   245,   246,   247,   248,   249,   250,     0,   251,
     252,    18,     0,    20,     0,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,    46,    47,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,   160,     0,     0,    50,     0,
      51,     0,     0,     0,    52,     0,     0,   161,     0,     0,
     162,    53,    18,     0,    20,     0,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    33,    34,    35,
     118,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,    47,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,   160,     0,     0,    50,
       0,    51,     0,     0,     0,    52,     0,     0,   161,     0,
       0,   162,    53,    18,     0,    20,     0,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,  -233,    33,    34,
      35,   118,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,    46,    47,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,  -233,     0,     0,    52,     0,     0,   342,
      18,     0,    20,    53,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    33,    34,    35,   118,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   202,     0,
      46,    47,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,    51,
       0,     0,     0,    52,     0,     0,    18,     0,    20,     0,
      53,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    33,    34,    35,   118,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,     0,    46,    47,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   209,    51,     0,     0,     0,    52,
       0,     0,    18,     0,    20,   162,    53,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    33,    34,    35,
     118,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,    47,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,    51,     0,     0,     0,    52,     0,     0,    18,     0,
      20,   162,    53,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     0,    33,    34,    35,   118,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     0,     0,    46,    47,
       0,     0,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,    51,     0,     0,
       0,    52,     0,     0,    18,     0,    20,     0,    53,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    33,
      34,    35,   118,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     0,     0,    46,    47,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,     0,     0,    52,     0,     0,
     342,    18,     0,    20,    53,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,    34,    35,   118,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,    46,    47,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,    52,     0,     0,    18,     0,    20,
     162,    53,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    33,    34,    35,   118,    37,    38,    39,    40,
      41,    42,    43,    44,    45,     0,     0,    46,    47,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,     0,     0,     0,
      52,     0,     0,   -88,     0,   -88,     0,    53,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,     0,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,     0,     0,   -88,   -88,     0,     0,     0,   -88,   -88,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -88,     0,     0,     0,   -88,     0,     0,    18,
       0,    20,     0,   -88,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,    46,
      47,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
       0,     0,    52,     0,     0,   -89,     0,   -89,     0,    53,
     -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,     0,
     -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,   -89,   -89,     0,     0,   -89,   -89,     0,     0,     0,
     -89,   -89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -89,     0,     0,     0,   -89,     0,
       0,     0,     0,     0,     0,   -89,   457,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    33,   458,    35,     0,
      37,    38,   459,    40,    41,     0,    43,    44,    45,     0,
       0,     0,   460,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
      51,     0,   457,    24,    25,    26,    27,    28,    29,    30,
      31,    53,    33,   458,    35,     0,    37,    38,   459,    40,
      41,     0,    43,    44,    45,     0,     0,     0,   460,     0,
     227,     0,     0,   228,   229,     0,   230,     0,   231,   232,
     233,   234,   235,     0,     0,     0,    51,   236,   237,     0,
     238,   239,   240,   241,   242,     0,     0,    53,     0,   243,
     244,   245,   246,   247,   248,   249,   250,   227,   251,   252,
     228,   229,     0,     0,     0,   231,   232,   233,   234,   235,
       0,     0,     0,     0,   236,   237,     0,   238,   239,   240,
     241,   242,     0,     0,     0,     0,   243,   244,   245,   246,
     247,   248,   249,   250,   227,  -244,  -244,   228,   229,     0,
       0,     0,     0,     0,   233,   234,   235,     0,     0,     0,
       0,   236,   237,     0,   238,   239,   240,   241,   242,     0,
       0,     0,     0,   243,   244,   245,   246,   247,   248,   249,
     250,   227,     0,     0,   228,   229,     0,     0,     0,     0,
       0,   233,   234,   235,     0,     0,     0,     0,   236,   237,
       0,   238,   239,   240,   241,   242,     0,     0,     0,     0,
    -244,  -244,  -244,  -244,  -244,  -244,   249,   250
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-490))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-244))

static const yytype_int16 yycheck[] =
{
      16,    17,    91,   177,     0,   145,    89,    78,    79,    79,
     257,    76,   146,    59,   179,   355,    80,   199,   200,   201,
     430,    77,   313,   333,   218,   332,   333,   332,   333,   332,
     333,   332,   333,    19,   321,    13,    61,   285,   183,   484,
     327,   223,    27,    89,   533,    46,     4,   529,    51,    65,
      26,   533,    68,    81,    46,    71,    72,    73,    74,    75,
      76,    19,    25,   285,    80,    81,    82,    79,    46,    46,
      46,    46,    73,    52,    90,    47,    92,    93,   103,    51,
      50,    51,    61,    77,    54,    57,    58,   215,   222,    92,
      82,    50,    51,   110,    79,    73,    73,    73,    73,    73,
      77,    64,    47,    77,     0,   262,    51,    15,   124,    17,
     126,    46,    57,    58,   130,   131,   132,   262,   174,   135,
      92,   566,    92,   612,    79,   141,   142,   143,   144,   286,
     612,    76,    47,    92,    83,    61,    51,    61,   312,   125,
     334,   286,    57,    58,   160,   161,    47,    92,   529,    64,
      51,   145,    68,    64,   103,   442,    57,    58,    73,   176,
     177,   178,   179,    61,    64,    81,   182,   125,   455,    65,
     551,    71,    68,    88,    61,    76,    92,    92,    61,     0,
     174,   197,    93,    94,    80,    51,   103,    88,   316,   317,
     218,    92,   332,   333,    90,    66,    92,    93,   446,   215,
     216,   217,   218,    69,   332,   333,    61,   263,    61,   158,
      93,    94,   386,    61,    46,   111,   165,    88,    89,    90,
     630,   170,    90,   103,   534,    93,    92,   534,    61,   534,
      46,   534,    64,   534,    64,   184,    10,    50,    51,     8,
     256,    54,   331,     1,     2,     3,    14,    15,     6,     7,
       8,     9,    10,    11,   545,   216,   217,   206,   103,   155,
      18,   210,    20,   603,   320,   103,   349,   554,    10,   556,
      15,   354,   437,   289,   103,    83,   292,   293,   343,   343,
     296,   197,    49,    50,    51,    80,    80,    45,    46,    54,
      48,    49,    50,    51,    52,   312,   254,   479,   545,   315,
     216,   217,   218,   349,   332,   333,   334,   301,   354,   531,
      66,   533,    66,    77,   342,    77,    11,    12,   334,    10,
     216,   217,   456,    18,    19,    80,   320,   343,   322,    87,
      86,    87,    88,    89,    90,    82,   285,    13,    17,    60,
      80,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   386,
     564,   553,     9,   289,   332,   333,   393,   410,   560,   412,
     296,   470,   453,   453,    51,    77,    93,    76,   610,    10,
     612,   287,    80,    10,   534,   617,    10,   393,   347,   315,
      47,   127,   128,   352,    51,   163,   534,    82,   424,    10,
      57,    58,    10,   635,   596,   589,   332,   333,   334,    52,
     437,    47,   180,    59,    10,    51,    77,    10,   154,    76,
       0,    57,    58,    10,   562,   452,   332,   333,    10,   388,
      65,    88,    10,    10,   254,    92,    10,   343,   206,    10,
     111,   467,   210,   258,   212,   213,   214,   283,   406,   317,
     409,   410,   203,   412,   203,   481,    92,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,    65,   445,   393,    68,    65,
     516,   287,    68,   443,   562,   566,   534,    77,   217,    82,
      80,   293,   601,    92,    80,   296,   289,    -1,    -1,    -1,
      90,     0,    92,    93,    90,   541,    92,    93,    -1,    -1,
      -1,   480,    -1,    -1,   404,    -1,   564,    -1,    -1,   297,
      -1,   111,   570,    -1,   577,   578,   562,   580,   564,   582,
     583,    -1,    -1,    -1,    -1,    -1,   314,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   326,    -1,
      -1,   441,   589,    -1,   523,   145,   534,   303,    -1,   305,
      -1,   307,    -1,   309,    -1,   155,    65,    -1,    -1,    68,
      -1,    -1,   625,   626,   627,    -1,   629,   355,    -1,    78,
      79,    80,    -1,    -1,   174,   638,    -1,    -1,   624,    -1,
      -1,    90,    -1,    92,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,   577,   578,
      -1,    -1,   111,    66,   583,    -1,    69,    70,   534,    -1,
      -1,    -1,    -1,    76,    30,    31,   216,   217,   564,    -1,
     216,   217,    -1,    86,    87,    88,    89,    90,    -1,   529,
      46,   531,    -1,    -1,   390,   535,    -1,    -1,    -1,    -1,
      -1,   397,    -1,    -1,    -1,    -1,   155,    -1,   627,    -1,
      66,   551,   552,    69,    70,    -1,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,   174,    -1,    83,    84,    -1,
      86,    87,    88,    89,    90,    -1,   576,   433,    -1,    95,
      96,    97,    98,    99,   100,   101,   102,   287,   104,   105,
      -1,    -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    51,
      -1,   301,   490,    -1,    -1,    57,    58,   216,   217,    -1,
     610,    -1,    -1,    -1,   614,    -1,    -1,   617,    -1,    -1,
     320,    73,   322,    -1,    76,    -1,   514,    47,    -1,    81,
      -1,    51,    -1,    -1,    -1,   635,    88,    57,    58,    -1,
      92,    -1,    -1,   343,    -1,    -1,    -1,   343,    -1,    -1,
     538,    -1,    -1,    -1,    -1,    -1,    76,   513,    -1,    -1,
      -1,    81,   518,    66,    -1,    -1,    69,    70,    88,    -1,
      -1,    -1,    92,    76,    77,    78,    66,    -1,   287,    69,
      70,    -1,    -1,    86,    87,    88,    89,    90,    -1,    -1,
      -1,   547,   301,   393,    -1,    -1,    86,    87,    88,    89,
      90,    -1,    -1,   403,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   322,    -1,   603,    -1,   605,    66,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    -1,    -1,    -1,   343,    83,    84,    -1,    86,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,    -1,     3,     4,     5,     6,
       7,    -1,   618,    -1,    11,    12,    -1,    -1,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    29,    -1,   393,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    68,    -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    -1,    -1,   453,    92,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    29,    -1,   574,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    85,     3,
       4,     5,     6,     7,    -1,    92,    -1,    11,    12,    -1,
      -1,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    28,    29,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    79,    -1,    81,    -1,    -1,
      -1,    85,     3,     4,     5,     6,     7,    -1,    92,    -1,
      11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    28,    29,    -1,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    62,    63,    -1,    -1,    -1,    67,    68,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    79,    -1,
      81,    11,    12,    -1,    85,    -1,    16,    -1,    18,    19,
      20,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      26,    -1,    62,    63,    30,    31,    -1,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      46,    81,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    69,    70,    -1,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    -1,    83,    84,    -1,
      86,    87,    88,    89,    90,    17,    -1,    -1,    -1,    95,
      96,    97,    98,    99,   100,   101,   102,    -1,   104,   105,
      32,    -1,    34,    -1,    -1,    37,    38,    39,    40,    41,
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
      -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,
      -1,    85,    -1,    -1,    32,    -1,    34,    -1,    92,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,
      88,    32,    -1,    34,    92,    -1,    37,    38,    39,    40,
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
      -1,    -1,    -1,    -1,    76,    77,    78,    -1,    -1,    -1,
      -1,    83,    84,    -1,    86,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    76,    77,    78,    -1,    -1,    -1,    -1,    83,    84,
      -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,    -1,
      95,    96,    97,    98,    99,   100,   101,   102
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
     115,   116,   117,   118,   121,   128,   134,   135,   136,   137,
     138,   174,   180,   181,   182,   183,   185,   186,   187,   188,
     192,   194,   196,   214,   217,   218,   221,   222,   223,   226,
     227,   229,   230,   231,   244,    46,   202,   203,   202,   202,
      50,    51,   119,   120,   138,    46,    73,   146,   200,   204,
     205,   206,   202,   202,   202,   202,   202,   202,    50,   135,
     137,   231,   244,   244,   202,   120,   202,    79,    79,   202,
     202,   202,   202,   202,   202,   202,     0,    11,    12,    18,
      19,   175,   176,   177,   178,    61,   232,   233,    52,    27,
     148,   149,   150,   151,   173,   196,   226,   236,   238,   244,
      76,    88,    91,   139,   223,   224,   225,   226,   235,   237,
     239,   241,   242,   244,   103,   228,   244,   244,   244,   244,
      17,   169,   184,   244,   214,   244,    50,   128,   130,   131,
     135,   136,    51,    92,   133,   137,   227,    69,   133,   217,
     226,   244,    60,   134,   216,   219,   220,   223,   244,    80,
     224,   244,    64,    93,    94,   191,   198,   199,   202,   148,
     234,   236,   232,   235,   236,    30,    31,    66,    69,    70,
      72,    74,    75,    76,    77,    78,    83,    84,    86,    87,
      88,    89,    90,    95,    96,    97,    98,    99,   100,   101,
     102,   104,   105,    46,   191,    10,     8,   143,   144,   145,
     204,   108,   109,   103,   244,   120,   244,   200,   200,   244,
     244,   244,   244,   244,   244,   244,   244,    92,   128,   135,
     229,   233,    46,   190,   200,    77,   109,   153,   201,   191,
     244,   244,   202,   191,   193,   202,   191,    71,   128,   136,
     137,   103,    13,   171,   204,   171,    26,   172,   204,   172,
     202,    10,   244,   206,    25,   189,   122,   123,    61,   103,
     207,   124,   103,   223,   240,   244,    83,   125,   147,   193,
     193,   193,   198,   199,   191,   195,   202,   197,   202,   202,
     202,   202,    88,   192,   210,   244,   121,   215,   223,   226,
     244,   121,   215,   223,   226,   219,   193,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   119,   165,   166,   167,   244,
      15,   141,   145,   205,   206,    80,    80,   153,    10,    47,
      51,    57,    58,    73,    88,    92,   152,   154,   157,   159,
     160,   161,   162,   163,   164,   191,   206,   201,    80,   241,
     244,   225,    82,   242,   202,   128,   129,   137,   200,    13,
     200,   200,   200,   171,   169,   202,   223,   243,   244,    46,
      73,    76,   132,   156,   157,   159,   192,   208,   156,   128,
     136,   146,   127,   202,   146,   126,   232,    37,    48,    53,
      63,   110,   111,   112,   113,   134,   138,   192,   218,   223,
     229,   231,   113,   223,   219,    60,    80,    92,   134,   209,
     214,   191,   148,   148,   195,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   171,    71,   168,   191,   200,     9,   142,
     108,   200,   135,   155,   163,    77,   154,    77,   158,   191,
     158,   191,   158,   191,    93,    76,    80,   244,    14,   140,
     141,   179,   140,    10,    10,   200,    10,   172,   163,   146,
     208,   191,    76,   157,    82,    10,   204,   133,    10,   146,
     244,   193,   191,   244,   194,   211,   212,   213,   202,   200,
     202,   244,   200,    10,   191,    77,    76,   160,   162,   163,
     159,   163,   159,   160,   161,   113,   163,   202,    10,   244,
      10,   141,   169,   170,   200,    10,   163,   193,   146,   146,
      10,   193,   210,   219,   213,    65,   134,   135,   163,   158,
     191,   158,   191,   158,   191,   158,   158,   191,   171,    10,
     193,    10,    10,   195,   202,   159,   159,   160,   163,   159,
     200,   244,   158,   158,   158,   191,   158,   140,   159,   158
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
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
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
    if ((yyvsp[(2) - (2)].n)->last != NULL) {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)->last);
    } else {
      copy_range((yyval.n), (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
    }
  }
    break;

  case 279:

/* Line 1806 of yacc.c  */
#line 1118 "../parser.y"
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
#line 1128 "../parser.y"
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
#line 1143 "../parser.y"
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
#line 1153 "../parser.y"
    {
    struct node * n = alloc_node(token_object, (yyvsp[(1) - (3)].n), NULL);
    (yyval.n) = pop_list(n, (yyvsp[(3) - (3)].n));
    copy_range((yyval.n), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
  }
    break;

  case 283:

/* Line 1806 of yacc.c  */
#line 1160 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 284:

/* Line 1806 of yacc.c  */
#line 1161 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 285:

/* Line 1806 of yacc.c  */
#line 1165 "../parser.y"
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

  case 286:

/* Line 1806 of yacc.c  */
#line 1178 "../parser.y"
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
#line 1192 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 288:

/* Line 1806 of yacc.c  */
#line 1196 "../parser.y"
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

  case 289:

/* Line 1806 of yacc.c  */
#line 1206 "../parser.y"
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

  case 290:

/* Line 1806 of yacc.c  */
#line 1216 "../parser.y"
    {
    (yyval.n) = pop_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n));
  }
    break;

  case 291:

/* Line 1806 of yacc.c  */
#line 1221 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 292:

/* Line 1806 of yacc.c  */
#line 1222 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 293:

/* Line 1806 of yacc.c  */
#line 1226 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 0;
  }
    break;

  case 294:

/* Line 1806 of yacc.c  */
#line 1231 "../parser.y"
    {
    (yyval.n) = (yyvsp[(2) - (2)].n);
    parser->last_is_paren = 1;
  }
    break;

  case 295:

/* Line 1806 of yacc.c  */
#line 1237 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 296:

/* Line 1806 of yacc.c  */
#line 1238 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 297:

/* Line 1806 of yacc.c  */
#line 1241 "../parser.y"
    { (yyval.n) = 0;   }
    break;

  case 298:

/* Line 1806 of yacc.c  */
#line 1242 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 299:

/* Line 1806 of yacc.c  */
#line 1245 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 300:

/* Line 1806 of yacc.c  */
#line 1247 "../parser.y"
    {
    (yyval.n) = (yyvsp[(1) - (1)].n);
    parser->call_args = 1;
  }
    break;

  case 301:

/* Line 1806 of yacc.c  */
#line 1253 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 302:

/* Line 1806 of yacc.c  */
#line 1254 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 303:

/* Line 1806 of yacc.c  */
#line 1258 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 304:

/* Line 1806 of yacc.c  */
#line 1259 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 305:

/* Line 1806 of yacc.c  */
#line 1262 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 306:

/* Line 1806 of yacc.c  */
#line 1263 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 307:

/* Line 1806 of yacc.c  */
#line 1266 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 308:

/* Line 1806 of yacc.c  */
#line 1267 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n); }
    break;

  case 309:

/* Line 1806 of yacc.c  */
#line 1271 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 310:

/* Line 1806 of yacc.c  */
#line 1272 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 311:

/* Line 1806 of yacc.c  */
#line 1274 "../parser.y"
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
#line 1284 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 313:

/* Line 1806 of yacc.c  */
#line 1285 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 314:

/* Line 1806 of yacc.c  */
#line 1286 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (2)].n);  }
    break;

  case 315:

/* Line 1806 of yacc.c  */
#line 1290 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 316:

/* Line 1806 of yacc.c  */
#line 1291 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 317:

/* Line 1806 of yacc.c  */
#line 1294 "../parser.y"
    { (yyval.n) = ALLOC_N(token_plus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    }
    break;

  case 318:

/* Line 1806 of yacc.c  */
#line 1295 "../parser.y"
    { (yyval.n) = ALLOC_N(token_minus, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   }
    break;

  case 319:

/* Line 1806 of yacc.c  */
#line 1296 "../parser.y"
    { (yyval.n) = ALLOC_N(token_mul, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 320:

/* Line 1806 of yacc.c  */
#line 1297 "../parser.y"
    { (yyval.n) = ALLOC_N(token_div, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 321:

/* Line 1806 of yacc.c  */
#line 1298 "../parser.y"
    { (yyval.n) = ALLOC_N(token_mod, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 322:

/* Line 1806 of yacc.c  */
#line 1299 "../parser.y"
    { (yyval.n) = ALLOC_N(token_exp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 323:

/* Line 1806 of yacc.c  */
#line 1300 "../parser.y"
    { (yyval.n) = ALLOC_N(token_bit_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); }
    break;

  case 324:

/* Line 1806 of yacc.c  */
#line 1301 "../parser.y"
    { (yyval.n) = ALLOC_N(token_bit_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 325:

/* Line 1806 of yacc.c  */
#line 1302 "../parser.y"
    { (yyval.n) = ALLOC_N(token_bit_xor, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); }
    break;

  case 326:

/* Line 1806 of yacc.c  */
#line 1303 "../parser.y"
    { (yyval.n) = ALLOC_N(token_lshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 327:

/* Line 1806 of yacc.c  */
#line 1304 "../parser.y"
    { (yyval.n) = ALLOC_N(token_rshift, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 328:

/* Line 1806 of yacc.c  */
#line 1305 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  }
    break;

  case 329:

/* Line 1806 of yacc.c  */
#line 1306 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n); fix_mrhs((yyval.n));  }
    break;

  case 330:

/* Line 1806 of yacc.c  */
#line 1307 "../parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);  }
    break;

  case 331:

/* Line 1806 of yacc.c  */
#line 1308 "../parser.y"
    { (yyval.n) = ALLOC_N(token_cmp, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 332:

/* Line 1806 of yacc.c  */
#line 1309 "../parser.y"
    { (yyval.n) = ALLOC_N(token_eq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      }
    break;

  case 333:

/* Line 1806 of yacc.c  */
#line 1310 "../parser.y"
    { (yyval.n) = ALLOC_N(token_neq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 334:

/* Line 1806 of yacc.c  */
#line 1311 "../parser.y"
    { (yyval.n) = ALLOC_N(token_eqq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 335:

/* Line 1806 of yacc.c  */
#line 1312 "../parser.y"
    { (yyval.n) = ALLOC_N(token_match, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   }
    break;

  case 336:

/* Line 1806 of yacc.c  */
#line 1313 "../parser.y"
    { (yyval.n) = ALLOC_N(token_nmatch, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 337:

/* Line 1806 of yacc.c  */
#line 1314 "../parser.y"
    { (yyval.n) = ALLOC_N(token_greater, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n)); }
    break;

  case 338:

/* Line 1806 of yacc.c  */
#line 1315 "../parser.y"
    { (yyval.n) = ALLOC_N(token_lesser, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 339:

/* Line 1806 of yacc.c  */
#line 1316 "../parser.y"
    { (yyval.n) = ALLOC_N(token_geq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 340:

/* Line 1806 of yacc.c  */
#line 1317 "../parser.y"
    { (yyval.n) = ALLOC_N(token_leq, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 341:

/* Line 1806 of yacc.c  */
#line 1318 "../parser.y"
    { (yyval.n) = ALLOC_N(token_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));      }
    break;

  case 342:

/* Line 1806 of yacc.c  */
#line 1319 "../parser.y"
    { (yyval.n) = ALLOC_N(token_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));     }
    break;

  case 343:

/* Line 1806 of yacc.c  */
#line 1320 "../parser.y"
    { (yyval.n) = ALLOC_N(token_kw_or, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));   }
    break;

  case 344:

/* Line 1806 of yacc.c  */
#line 1321 "../parser.y"
    { (yyval.n) = ALLOC_N(token_kw_and, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));  }
    break;

  case 345:

/* Line 1806 of yacc.c  */
#line 1322 "../parser.y"
    { (yyval.n) = ALLOC_N(token_dot2, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    }
    break;

  case 346:

/* Line 1806 of yacc.c  */
#line 1323 "../parser.y"
    { (yyval.n) = ALLOC_N(token_dot3, (yyvsp[(1) - (4)].n), (yyvsp[(4) - (4)].n));    }
    break;

  case 347:

/* Line 1806 of yacc.c  */
#line 1325 "../parser.y"
    {
    (yyval.n) = ALLOC_C(token_ternary, (yyvsp[(1) - (8)].n), (yyvsp[(4) - (8)].n), (yyvsp[(8) - (8)].n));
  }
    break;

  case 348:

/* Line 1806 of yacc.c  */
#line 1328 "../parser.y"
    { (yyval.n) = ALLOC_N(token_kw_not, (yyvsp[(3) - (3)].n), NULL);}
    break;

  case 349:

/* Line 1806 of yacc.c  */
#line 1329 "../parser.y"
    { (yyval.n) = ALLOC_N(token_neg, (yyvsp[(3) - (3)].n), NULL);   }
    break;

  case 350:

/* Line 1806 of yacc.c  */
#line 1330 "../parser.y"
    { (yyval.n) = ALLOC_N(token_not, (yyvsp[(3) - (3)].n), NULL);   }
    break;

  case 351:

/* Line 1806 of yacc.c  */
#line 1331 "../parser.y"
    { (yyval.n) = ALLOC_N(token_unary_plus, (yyvsp[(3) - (3)].n), NULL);  }
    break;

  case 352:

/* Line 1806 of yacc.c  */
#line 1332 "../parser.y"
    { (yyval.n) = ALLOC_N(token_unary_minus, (yyvsp[(3) - (3)].n), NULL); }
    break;

  case 353:

/* Line 1806 of yacc.c  */
#line 1333 "../parser.y"
    { (yyval.n) = ALLOC_N(token_defined, (yyvsp[(3) - (3)].n), NULL); copy_end((yyval.n), (yyvsp[(3) - (3)].n));  }
    break;

  case 354:

/* Line 1806 of yacc.c  */
#line 1334 "../parser.y"
    { (yyval.n) = update_list((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n)); }
    break;

  case 355:

/* Line 1806 of yacc.c  */
#line 1335 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 356:

/* Line 1806 of yacc.c  */
#line 1336 "../parser.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);  }
    break;

  case 357:

/* Line 1806 of yacc.c  */
#line 1337 "../parser.y"
    { (yyval.n) = ALLOC_N(token_object, NULL, NULL); POP_STACK; }
    break;



/* Line 1806 of yacc.c  */
#line 5135 "../parser.c"
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
#line 1340 "../parser.y"

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
  struct pos_t tokp = {-1, -1, -1, -1};

  curs = parser->cursor;
  len = parser->length;
  if (curs >= len) {
    parser->eof_reached = 1;
    return 0;
  }
  c = parser->blob + curs;

  /* Ignore whitespaces and backslashes */
  for (; (isspace(*c) || *c == '\\') && *c != '\n';
      ++c, ++curs, parser->column++, parser->cursor++);

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

