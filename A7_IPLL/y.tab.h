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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    IDENTIFIER = 258,              /* IDENTIFIER  */
    INTEGER_CONSTANT = 259,        /* INTEGER_CONSTANT  */
    FLOATING_CONSTANT = 260,       /* FLOATING_CONSTANT  */
    CHARACTER_CONSTANT = 261,      /* CHARACTER_CONSTANT  */
    STRING_LITERAL = 262,          /* STRING_LITERAL  */
    RETURN = 263,                  /* RETURN  */
    VOID = 264,                    /* VOID  */
    FLOAT = 265,                   /* FLOAT  */
    INTEGER = 266,                 /* INTEGER  */
    CHAR = 267,                    /* CHAR  */
    FOR = 268,                     /* FOR  */
    CONST = 269,                   /* CONST  */
    WHILE = 270,                   /* WHILE  */
    BOOL = 271,                    /* BOOL  */
    IF = 272,                      /* IF  */
    DO = 273,                      /* DO  */
    ELSE = 274,                    /* ELSE  */
    MC_BEGIN = 275,                /* MC_BEGIN  */
    END = 276,                     /* END  */
    ARROW = 277,                   /* ARROW  */
    INCREMENT = 278,               /* INCREMENT  */
    DECREMENT = 279,               /* DECREMENT  */
    AMPERSAND = 280,               /* AMPERSAND  */
    ASTERISK = 281,                /* ASTERISK  */
    PLUS = 282,                    /* PLUS  */
    MINUS = 283,                   /* MINUS  */
    EXCLAMATION = 284,             /* EXCLAMATION  */
    FORWARD_SLASH = 285,           /* FORWARD_SLASH  */
    PERCENT = 286,                 /* PERCENT  */
    LEFT_SHIFT = 287,              /* LEFT_SHIFT  */
    RIGHT_SHIFT = 288,             /* RIGHT_SHIFT  */
    LESS_THAN = 289,               /* LESS_THAN  */
    GREATER_THAN = 290,            /* GREATER_THAN  */
    LP = 291,                      /* LP  */
    RP = 292,                      /* RP  */
    LESS_THAN_EQUAL = 293,         /* LESS_THAN_EQUAL  */
    GREATER_THAN_EQUAL = 294,      /* GREATER_THAN_EQUAL  */
    EQUAL_EQUAL = 295,             /* EQUAL_EQUAL  */
    NOT_EQUAL = 296,               /* NOT_EQUAL  */
    CARET = 297,                   /* CARET  */
    PIPE = 298,                    /* PIPE  */
    LOGICAL_AND = 299,             /* LOGICAL_AND  */
    LOGICAL_OR = 300,              /* LOGICAL_OR  */
    QUESTION_MARK = 301,           /* QUESTION_MARK  */
    COLON = 302,                   /* COLON  */
    SEMICOLON = 303,               /* SEMICOLON  */
    ASSIGN = 304,                  /* ASSIGN  */
    COMMA = 305                    /* COMMA  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define INTEGER_CONSTANT 259
#define FLOATING_CONSTANT 260
#define CHARACTER_CONSTANT 261
#define STRING_LITERAL 262
#define RETURN 263
#define VOID 264
#define FLOAT 265
#define INTEGER 266
#define CHAR 267
#define FOR 268
#define CONST 269
#define WHILE 270
#define BOOL 271
#define IF 272
#define DO 273
#define ELSE 274
#define MC_BEGIN 275
#define END 276
#define ARROW 277
#define INCREMENT 278
#define DECREMENT 279
#define AMPERSAND 280
#define ASTERISK 281
#define PLUS 282
#define MINUS 283
#define EXCLAMATION 284
#define FORWARD_SLASH 285
#define PERCENT 286
#define LEFT_SHIFT 287
#define RIGHT_SHIFT 288
#define LESS_THAN 289
#define GREATER_THAN 290
#define LP 291
#define RP 292
#define LESS_THAN_EQUAL 293
#define GREATER_THAN_EQUAL 294
#define EQUAL_EQUAL 295
#define NOT_EQUAL 296
#define CARET 297
#define PIPE 298
#define LOGICAL_AND 299
#define LOGICAL_OR 300
#define QUESTION_MARK 301
#define COLON 302
#define SEMICOLON 303
#define ASSIGN 304
#define COMMA 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "a7_220101113.y"

    int ival;
    float fval;
    char *sval;
    char *type;

#line 174 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
