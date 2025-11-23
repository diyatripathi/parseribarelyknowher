/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAM = 258,                 /* PROGRAM  */
    FUNCTION = 259,                /* FUNCTION  */
    VAR = 260,                     /* VAR  */
    INTEGER = 261,                 /* INTEGER  */
    STRING = 262,                  /* STRING  */
    WHILE = 263,                   /* WHILE  */
    DO = 264,                      /* DO  */
    IF = 265,                      /* IF  */
    THEN = 266,                    /* THEN  */
    ELSE = 267,                    /* ELSE  */
    KW_BEGIN = 268,                /* KW_BEGIN  */
    KW_END = 269,                  /* KW_END  */
    ID = 270,                      /* ID  */
    STR = 271,                     /* STR  */
    NUM = 272,                     /* NUM  */
    PLUS = 273,                    /* PLUS  */
    MINUS = 274,                   /* MINUS  */
    STAR = 275,                    /* STAR  */
    SLASH = 276,                   /* SLASH  */
    LT = 277,                      /* LT  */
    GT = 278,                      /* GT  */
    LE = 279,                      /* LE  */
    GE = 280,                      /* GE  */
    EQ = 281,                      /* EQ  */
    NEQ = 282,                     /* NEQ  */
    ASSIGN = 283,                  /* ASSIGN  */
    LPAREN = 284,                  /* LPAREN  */
    RPAREN = 285,                  /* RPAREN  */
    COMMA = 286,                   /* COMMA  */
    SEMI = 287,                    /* SEMI  */
    DOT = 288,                     /* DOT  */
    COLON = 289,                   /* COLON  */
    LOWER_THAN_ELSE = 290          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define PROGRAM 258
#define FUNCTION 259
#define VAR 260
#define INTEGER 261
#define STRING 262
#define WHILE 263
#define DO 264
#define IF 265
#define THEN 266
#define ELSE 267
#define KW_BEGIN 268
#define KW_END 269
#define ID 270
#define STR 271
#define NUM 272
#define PLUS 273
#define MINUS 274
#define STAR 275
#define SLASH 276
#define LT 277
#define GT 278
#define LE 279
#define GE 280
#define EQ 281
#define NEQ 282
#define ASSIGN 283
#define LPAREN 284
#define RPAREN 285
#define COMMA 286
#define SEMI 287
#define DOT 288
#define COLON 289
#define LOWER_THAN_ELSE 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 9 "PIBKH_PA3.y"

    int       ival;      /* for NUM */
    char     *sval;      /* for ID, STR */
    Symbol   *sym;       /* for expression, term, factor */
    NameList *namelist;  /* for variable_list */
    TypeKind  type;      /* for type nonterminal */

#line 145 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
