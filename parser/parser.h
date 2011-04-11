/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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
     TRUE = 293,
     FALSE = 294,
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

/* Line 1685 of yacc.c  */
#line 114 "../parser.y"
  struct node * n;  


/* Line 1685 of yacc.c  */
#line 161 "../parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif




