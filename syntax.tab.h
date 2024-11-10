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

#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    LOWER_ERROR = 258,             /* LOWER_ERROR  */
    ILLEGAL_TOKEN = 259,           /* ILLEGAL_TOKEN  */
    LOWER_THAN_ELSE = 260,         /* LOWER_THAN_ELSE  */
    ELSE = 261,                    /* ELSE  */
    TYPE = 262,                    /* TYPE  */
    STRUCT = 263,                  /* STRUCT  */
    IF = 264,                      /* IF  */
    WHILE = 265,                   /* WHILE  */
    RETURN = 266,                  /* RETURN  */
    INT = 267,                     /* INT  */
    FLOAT = 268,                   /* FLOAT  */
    CHAR = 269,                    /* CHAR  */
    BOOLEAN = 270,                 /* BOOLEAN  */
    ID = 271,                      /* ID  */
    ASSIGN = 272,                  /* ASSIGN  */
    PLUS_ASSIGN = 273,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 274,            /* MINUS_ASSIGN  */
    MUL_ASSIGN = 275,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 276,              /* DIV_ASSIGN  */
    OR = 277,                      /* OR  */
    AND = 278,                     /* AND  */
    BOR = 279,                     /* BOR  */
    XOR = 280,                     /* XOR  */
    BAND = 281,                    /* BAND  */
    LT = 282,                      /* LT  */
    LE = 283,                      /* LE  */
    GT = 284,                      /* GT  */
    GE = 285,                      /* GE  */
    NE = 286,                      /* NE  */
    EQ = 287,                      /* EQ  */
    LOWER_MINUS = 288,             /* LOWER_MINUS  */
    PLUS = 289,                    /* PLUS  */
    MINUS = 290,                   /* MINUS  */
    MUL = 291,                     /* MUL  */
    DIV = 292,                     /* DIV  */
    NOT = 293,                     /* NOT  */
    LP = 294,                      /* LP  */
    RP = 295,                      /* RP  */
    LB = 296,                      /* LB  */
    RB = 297,                      /* RB  */
    DOT = 298,                     /* DOT  */
    SEMI = 299,                    /* SEMI  */
    COMMA = 300,                   /* COMMA  */
    LC = 301,                      /* LC  */
    RC = 302,                      /* RC  */
    STRING = 303,                  /* STRING  */
    FOR = 304                      /* FOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "syntax.y"

    Node* Node_value;

#line 117 "syntax.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */
