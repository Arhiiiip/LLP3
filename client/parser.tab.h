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
    VERTEX = 258,                  /* VERTEX  */
    HAS = 259,                     /* HAS  */
    OUT = 260,                     /* OUT  */
    OPEN = 261,                    /* OPEN  */
    CREATE = 262,                  /* CREATE  */
    CLOSE = 263,                   /* CLOSE  */
    DELETE = 264,                  /* DELETE  */
    CREATE_SCHEMA = 265,           /* CREATE_SCHEMA  */
    DELETE_SCHEMA = 266,           /* DELETE_SCHEMA  */
    ADD_VERTEX = 267,              /* ADD_VERTEX  */
    TOK_NODES = 268,               /* TOK_NODES  */
    EQUALS = 269,                  /* EQUALS  */
    GREATER = 270,                 /* GREATER  */
    GREATER_EQUALS = 271,          /* GREATER_EQUALS  */
    LESS = 272,                    /* LESS  */
    LESS_EQUALS = 273,             /* LESS_EQUALS  */
    NOT_EQUALS = 274,              /* NOT_EQUALS  */
    CONTAINS = 275,                /* CONTAINS  */
    INTEGER = 276,                 /* INTEGER  */
    DECIMAL = 277,                 /* DECIMAL  */
    BOOLEAN = 278,                 /* BOOLEAN  */
    WORD = 279,                    /* WORD  */
    FILENAME = 280,                /* FILENAME  */
    MY_INTEGER = 281,              /* MY_INTEGER  */
    MY_FLOAT = 282,                /* MY_FLOAT  */
    MY_STRING = 283,               /* MY_STRING  */
    MY_BOOLEAN = 284,              /* MY_BOOLEAN  */
    MY_REF = 285,                  /* MY_REF  */
    VALUES = 286,                  /* VALUES  */
    OTHER = 287,                   /* OTHER  */
    RIGHT_BRACE = 288,             /* RIGHT_BRACE  */
    LEFT_BRACE = 289,              /* LEFT_BRACE  */
    QUOTE = 290,                   /* QUOTE  */
    DOT = 291,                     /* DOT  */
    COMMA = 292,                   /* COMMA  */
    SEMICOLON = 293                /* SEMICOLON  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "parser.y"

    /* types */
    char *string;
	int integer;
	double decimal;
	int boolean;

	char *ref_name;
	int data_type;
	int cmp_type;

#line 114 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
