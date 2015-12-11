/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_LITERAL = 258,
     DECIMAL_LITERAL = 259,
     STRING_LITERAL = 260,
     REGEXP_LITERAL = 261,
     IDENTIFIER = 262,
     IF = 263,
     ELSE = 264,
     ELSEIF = 265,
     WHILE = 266,
     DO_T = 267,
     FOR = 268,
     FOREACH = 269,
     RETURN_T = 270,
     BREAK = 271,
     CONTINUE = 272,
     NULL_T = 273,
     NEW = 274,
     LP = 275,
     RP = 276,
     LC = 277,
     RC = 278,
     LB = 279,
     RB = 280,
     SEMICOLON = 281,
     COLON = 282,
     COMMA = 283,
     ASSIGN_T = 284,
     LOGICAL_AND = 285,
     LOGICAL_OR = 286,
     EQ = 287,
     NE = 288,
     GT = 289,
     GE = 290,
     LT = 291,
     LE = 292,
     ADD = 293,
     SUB = 294,
     MUL = 295,
     DIV = 296,
     MOD = 297,
     TRUE_T = 298,
     FALSE_T = 299,
     EXCLAMATION = 300,
     DOT = 301,
     ADD_ASSIGN_T = 302,
     SUB_ASSIGN_T = 303,
     MUL_ASSIGN_T = 304,
     DIV_ASSIGN_T = 305,
     MOD_ASSIGN_T = 306,
     VOID_T = 307,
     INCREMENT = 308,
     DECREMENT = 309,
     BOOLEAN_T = 310,
     INT_T = 311,
     DECIMAL_T = 312,
     STRING_T = 313,
     CLASS_T = 314
   };
#endif
/* Tokens.  */
#define INT_LITERAL 258
#define DECIMAL_LITERAL 259
#define STRING_LITERAL 260
#define REGEXP_LITERAL 261
#define IDENTIFIER 262
#define IF 263
#define ELSE 264
#define ELSEIF 265
#define WHILE 266
#define DO_T 267
#define FOR 268
#define FOREACH 269
#define RETURN_T 270
#define BREAK 271
#define CONTINUE 272
#define NULL_T 273
#define NEW 274
#define LP 275
#define RP 276
#define LC 277
#define RC 278
#define LB 279
#define RB 280
#define SEMICOLON 281
#define COLON 282
#define COMMA 283
#define ASSIGN_T 284
#define LOGICAL_AND 285
#define LOGICAL_OR 286
#define EQ 287
#define NE 288
#define GT 289
#define GE 290
#define LT 291
#define LE 292
#define ADD 293
#define SUB 294
#define MUL 295
#define DIV 296
#define MOD 297
#define TRUE_T 298
#define FALSE_T 299
#define EXCLAMATION 300
#define DOT 301
#define ADD_ASSIGN_T 302
#define SUB_ASSIGN_T 303
#define MUL_ASSIGN_T 304
#define DIV_ASSIGN_T 305
#define MOD_ASSIGN_T 306
#define VOID_T 307
#define INCREMENT 308
#define DECREMENT 309
#define BOOLEAN_T 310
#define INT_T 311
#define DECIMAL_T 312
#define STRING_T 313
#define CLASS_T 314




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 9 "minic.y"

    char 		*identifier;
    ParameterList	*parameter_list;
    ArgumentList	*argument_list;
    Expression		*expression;
    ExpressionList	*expression_list;
    Statement		*statement;
    StatementList	*statement_list;
    Block		*block;
    Elseif		*elseif;
    TypeSpecifier	*type_specifier;
    AssignmentOperator	assignment_operator;
    MINIC_BasicType	basic_type_specifier;
    ArrayDimension	*array_dimension;
    MemberDeclaration	*member_declaration;
    //ClassDefinition     *class_definition;



/* Line 2068 of yacc.c  */
#line 188 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


