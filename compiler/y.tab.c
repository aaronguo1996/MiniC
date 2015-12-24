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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "minic.y"

#include <stdio.h>
#include "minic.h"
#include "node.h"
#define YYDEBUG 1

int node_idx = 0;


/* Line 268 of yacc.c  */
#line 81 "y.tab.c"

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

/* Line 293 of yacc.c  */
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
    MVM_BasicType	basic_type_specifier;
    ArrayDimension	*array_dimension;
    MemberDeclaration	*member_declaration;
    ClassDefinition     *class_definition;



/* Line 293 of yacc.c  */
#line 255 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 267 "y.tab.c"

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
#define YYFINAL  84
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   469

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNRULES -- Number of states.  */
#define YYNSTATES  237

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

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
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    32,    36,    40,    42,    44,
      46,    53,    59,    66,    72,    75,    80,    82,    86,    88,
      91,    93,    97,    99,   103,   105,   107,   109,   111,   113,
     115,   117,   121,   123,   127,   129,   133,   137,   139,   143,
     147,   151,   155,   157,   161,   165,   167,   171,   175,   179,
     181,   184,   187,   189,   192,   195,   197,   199,   201,   206,
     211,   215,   220,   224,   228,   230,   232,   234,   236,   238,
     240,   242,   244,   248,   253,   257,   262,   266,   271,   273,
     276,   280,   283,   287,   288,   290,   294,   297,   299,   301,
     303,   305,   307,   309,   311,   313,   315,   321,   329,   336,
     345,   347,   350,   356,   362,   372,   380,   388,   389,   391,
     395,   396,   398,   402,   406,   410,   416,   417,   422,   425,
     431,   433,   436
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    -1,    63,    -1,    62,    63,    -1,
      68,    -1,   107,    -1,    91,    -1,    52,    -1,    55,    -1,
      56,    -1,    57,    -1,    58,    -1,     7,    -1,    64,    24,
      25,    -1,     7,    24,    25,    -1,    66,    24,    25,    -1,
      64,    -1,    66,    -1,    65,    -1,    67,     7,    20,    69,
      21,   105,    -1,    67,     7,    20,    21,   105,    -1,    67,
       7,    20,    69,    21,    26,    -1,    67,     7,    20,    21,
      26,    -1,    67,     7,    -1,    69,    28,    67,     7,    -1,
      73,    -1,    70,    28,    73,    -1,    91,    -1,    71,    91,
      -1,    73,    -1,    72,    28,    73,    -1,    75,    -1,    83,
      74,    73,    -1,    29,    -1,    47,    -1,    48,    -1,    49,
      -1,    50,    -1,    51,    -1,    76,    -1,    75,    31,    76,
      -1,    77,    -1,    76,    30,    77,    -1,    78,    -1,    77,
      32,    78,    -1,    77,    33,    78,    -1,    79,    -1,    78,
      34,    79,    -1,    78,    35,    79,    -1,    78,    36,    79,
      -1,    78,    37,    79,    -1,    80,    -1,    79,    38,    80,
      -1,    79,    39,    80,    -1,    81,    -1,    80,    40,    81,
      -1,    80,    41,    81,    -1,    80,    42,    81,    -1,    82,
      -1,    39,    81,    -1,    45,    81,    -1,    83,    -1,    83,
      53,    -1,    83,    54,    -1,    84,    -1,    86,    -1,     7,
      -1,    84,    24,    72,    25,    -1,     7,    24,    72,    25,
      -1,    83,    46,     7,    -1,    83,    20,    70,    21,    -1,
      83,    20,    21,    -1,    20,    72,    21,    -1,     3,    -1,
       4,    -1,     5,    -1,     6,    -1,    43,    -1,    44,    -1,
      18,    -1,    85,    -1,    22,    90,    23,    -1,    22,    90,
      28,    23,    -1,    19,    64,    87,    -1,    19,    64,    87,
      89,    -1,    19,    65,    87,    -1,    19,    65,    87,    89,
      -1,    88,    -1,    87,    88,    -1,    24,    72,    25,    -1,
      24,    25,    -1,    89,    24,    25,    -1,    -1,    73,    -1,
      90,    28,    73,    -1,    72,    26,    -1,    92,    -1,    95,
      -1,    97,    -1,    96,    -1,    98,    -1,   100,    -1,   102,
      -1,   103,    -1,   104,    -1,     8,    20,    72,    21,   105,
      -1,     8,    20,    72,    21,   105,     9,   105,    -1,     8,
      20,    72,    21,   105,    93,    -1,     8,    20,    72,    21,
     105,    93,     9,   105,    -1,    94,    -1,    93,    94,    -1,
      10,    20,    72,    21,   105,    -1,    11,    20,    72,    21,
     105,    -1,    13,    20,    99,    26,    99,    26,    99,    21,
     105,    -1,    12,   105,    11,    20,    72,    21,    26,    -1,
      14,    20,     7,    27,    72,    21,   105,    -1,    -1,    72,
      -1,    15,    99,    26,    -1,    -1,     7,    -1,    16,   101,
      26,    -1,    17,   101,    26,    -1,    67,     7,    26,    -1,
      67,     7,    29,    72,    26,    -1,    -1,    22,   106,    71,
      23,    -1,    22,    23,    -1,    59,     7,    22,   108,    23,
      -1,   109,    -1,   108,   109,    -1,    67,     7,    26,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    75,    83,    94,   102,   110,   121,   131,
     141,   151,   161,   172,   183,   200,   218,   234,   243,   251,
     260,   283,   303,   326,   348,   360,   378,   387,   402,   411,
     423,   431,   446,   454,   468,   478,   488,   498,   508,   518,
     528,   536,   551,   559,   573,   581,   595,   610,   618,   632,
     646,   660,   675,   683,   697,   713,   721,   735,   749,   764,
     772,   785,   798,   806,   818,   831,   839,   847,   858,   875,
     894,   909,   926,   941,   957,   966,   975,   984,   993,  1003,
    1013,  1023,  1032,  1047,  1066,  1080,  1096,  1110,  1127,  1135,
    1147,  1163,  1176,  1193,  1202,  1211,  1226,  1238,  1246,  1254,
    1262,  1270,  1278,  1286,  1294,  1302,  1311,  1331,  1356,  1378,
    1406,  1414,  1426,  1447,  1468,  1500,  1527,  1555,  1564,  1573,
    1590,  1599,  1609,  1625,  1641,  1656,  1678,  1677,  1696,  1711,
    1803,  1811,  1823
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_LITERAL", "DECIMAL_LITERAL",
  "STRING_LITERAL", "REGEXP_LITERAL", "IDENTIFIER", "IF", "ELSE", "ELSEIF",
  "WHILE", "DO_T", "FOR", "FOREACH", "RETURN_T", "BREAK", "CONTINUE",
  "NULL_T", "NEW", "LP", "RP", "LC", "RC", "LB", "RB", "SEMICOLON",
  "COLON", "COMMA", "ASSIGN_T", "LOGICAL_AND", "LOGICAL_OR", "EQ", "NE",
  "GT", "GE", "LT", "LE", "ADD", "SUB", "MUL", "DIV", "MOD", "TRUE_T",
  "FALSE_T", "EXCLAMATION", "DOT", "ADD_ASSIGN_T", "SUB_ASSIGN_T",
  "MUL_ASSIGN_T", "DIV_ASSIGN_T", "MOD_ASSIGN_T", "VOID_T", "INCREMENT",
  "DECREMENT", "BOOLEAN_T", "INT_T", "DECIMAL_T", "STRING_T", "CLASS_T",
  "$accept", "program", "external_declaration_list",
  "external_declaration", "basic_type_specifier", "class_type_specifier",
  "array_type_specifier", "type_specifier", "function_definition",
  "parameter_list", "argument_list", "statement_list", "expression",
  "assignment_expression", "assignment_operator", "logical_or_expression",
  "logical_and_expression", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "postfix_expression", "primary_expression", "primary_no_new_array",
  "array_literal", "array_creation", "dimension_expression_list",
  "dimension_expression", "dimension_list", "expression_list", "statement",
  "if_statement", "elseif_list", "elseif", "while_statement",
  "for_statement", "do_while_statement", "foreach_statement",
  "expression_opt", "return_statement", "identifier_opt",
  "break_statement", "continue_statement", "declaration_statement",
  "block", "@1", "class_definition", "member_declaration_list",
  "member_declaration", 0
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    63,    63,    64,    64,
      64,    64,    64,    65,    66,    66,    66,    67,    67,    67,
      68,    68,    68,    68,    69,    69,    70,    70,    71,    71,
      72,    72,    73,    73,    74,    74,    74,    74,    74,    74,
      75,    75,    76,    76,    77,    77,    77,    78,    78,    78,
      78,    78,    79,    79,    79,    80,    80,    80,    80,    81,
      81,    81,    82,    82,    82,    83,    83,    83,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    85,    85,    86,    86,    86,    86,    87,    87,
      88,    89,    89,    90,    90,    90,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    92,    92,    92,    92,
      93,    93,    94,    95,    96,    97,    98,    99,    99,   100,
     101,   101,   102,   103,   104,   104,   106,   105,   105,   107,
     108,   108,   109
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     1,     1,     1,
       6,     5,     6,     5,     2,     4,     1,     3,     1,     2,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     1,     2,     2,     1,     1,     1,     4,     4,
       3,     4,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     4,     3,     4,     3,     4,     1,     2,
       3,     2,     3,     0,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     7,     6,     8,
       1,     2,     5,     5,     9,     7,     7,     0,     1,     3,
       0,     1,     3,     3,     3,     5,     0,     4,     2,     5,
       1,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    74,    75,    76,    77,    67,     0,     0,     0,     0,
       0,   117,   120,   120,    80,     0,     0,    93,     0,    78,
      79,     0,     8,     9,    10,    11,    12,     0,     0,     2,
       3,    17,    19,    18,     0,     5,     0,    30,    32,    40,
      42,    44,    47,    52,    55,    59,    62,    65,    81,    66,
       7,    97,    98,   100,    99,   101,   102,   103,   104,   105,
       6,     0,     0,     0,   126,     0,   117,     0,    67,   118,
       0,   121,     0,     0,    13,     0,     0,     0,    94,     0,
      60,    62,    61,     0,     1,     4,     0,     0,     0,    96,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,    35,    36,    37,
      38,    39,    63,    64,     0,     0,    15,     0,     0,     0,
     128,     0,     0,     0,     0,     0,   119,   122,   123,     0,
      84,    88,    86,    73,    82,     0,     0,    14,    16,     0,
     124,     0,    31,    41,    43,    45,    46,    48,    49,    50,
      51,    53,    54,    56,    57,    58,    72,     0,    26,    70,
      33,     0,    69,     0,     0,     0,     0,    28,     0,   117,
       0,     0,     0,    89,    85,    87,    83,    95,    13,     0,
       0,   130,     0,     0,     0,     0,    71,     0,    68,   106,
     113,     0,   127,    29,     0,     0,     0,    90,    91,     0,
       0,     0,   129,   131,    23,    21,    24,     0,     0,   125,
      27,     0,     0,   108,   110,     0,   117,     0,    92,   132,
      22,    20,     0,   107,     0,     0,   111,   115,     0,   116,
      25,     0,   109,     0,     0,   114,   112
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,    29,    30,    31,    32,    33,    34,    35,   184,
     157,   166,    36,    37,   114,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,   130,   131,   174,
      79,    50,    51,   213,   214,    52,    53,    54,    55,    70,
      56,    72,    57,    58,    59,    65,   121,    60,   180,   181
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -155
static const yytype_int16 yypact[] =
{
     171,  -155,  -155,  -155,  -155,     0,    -4,    36,    51,    63,
      96,   424,   148,   148,  -155,    29,   424,   424,   424,  -155,
    -155,   424,  -155,  -155,  -155,  -155,  -155,   158,   170,   171,
    -155,   149,  -155,   156,   165,  -155,    89,  -155,   150,   162,
      -7,    72,    57,     4,  -155,  -155,    74,   172,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,
    -155,   312,   424,   424,   174,   183,   424,   188,   175,   173,
     176,  -155,   177,   178,  -155,   182,   182,     1,  -155,    37,
    -155,   -14,  -155,   185,  -155,  -155,   184,   186,    -6,  -155,
     424,   424,   424,   424,   424,   424,   424,   424,   424,   424,
     424,   424,   424,   424,   340,  -155,   191,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,   424,   424,  -155,   -13,     9,    10,
    -155,   284,   180,   192,   181,   424,  -155,  -155,  -155,   424,
     193,  -155,   193,  -155,  -155,   368,    92,  -155,  -155,    12,
    -155,   424,  -155,   162,    -7,    72,    72,    57,    57,    57,
      57,     4,     4,  -155,  -155,  -155,  -155,    13,  -155,  -155,
    -155,   101,  -155,    51,    51,   205,   228,  -155,   424,   424,
     424,   126,   396,  -155,   195,   195,  -155,  -155,   196,   214,
      20,  -155,    -9,   215,    14,   134,  -155,   424,  -155,   136,
    -155,   127,  -155,  -155,    26,   198,    38,  -155,  -155,   200,
     212,   223,  -155,  -155,  -155,  -155,  -155,    75,    92,  -155,
    -155,    51,   218,   154,  -155,   226,   424,    51,  -155,  -155,
    -155,  -155,   246,  -155,   424,    51,  -155,  -155,   233,  -155,
    -155,    61,  -155,    51,    51,  -155,  -155
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,  -155,   227,   240,   242,  -155,  -118,  -155,  -155,
    -155,  -155,   -11,   -16,  -155,  -155,   167,   168,    73,    15,
      69,   -10,  -155,    40,  -155,  -155,  -155,   187,   -30,   129,
    -155,  -117,  -155,  -155,    46,  -155,  -155,  -155,  -155,   -64,
    -155,   249,  -155,  -155,  -155,  -154,  -155,  -155,  -155,    84
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -14
static const yytype_int16 yytable[] =
{
      69,    78,   123,   165,   167,    77,   104,   -13,    80,   189,
     190,    82,   162,    64,   139,    90,    62,   204,   179,   178,
     140,   183,   133,   141,    61,    93,    94,   178,   205,    90,
     163,   164,   106,   182,   186,   207,    74,    90,    90,   112,
     113,   187,   208,   202,   101,   102,   103,   215,   165,   193,
     117,   118,   119,   221,    90,    69,    63,   223,    81,   217,
     134,    81,   179,   229,    22,   135,    90,    23,    24,    25,
      26,   232,    22,    64,   142,    23,    24,    25,    26,   235,
     236,    22,   234,    66,    23,    24,    25,    26,   158,    90,
     222,   153,   154,   155,   104,    99,   100,    64,   160,   178,
     173,   220,   173,   105,   161,   195,    95,    96,    97,    98,
     147,   148,   149,   150,   117,    89,    67,    90,   171,   177,
     106,   107,   108,   109,   110,   111,   188,   112,   113,    90,
     185,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    22,   211,   212,    23,    24,    25,
      26,   197,   228,   140,    90,    71,   141,   194,    69,   196,
     209,   171,    90,   225,   212,    83,   145,   146,   151,   152,
      84,   210,    88,    86,     1,     2,     3,     4,     5,     6,
      87,    91,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    92,    17,   122,   124,   115,   120,   159,   125,
     168,    90,   126,   127,   128,    69,   129,   136,   170,   137,
      18,   138,   191,   231,    19,    20,    21,   172,   169,   199,
     200,   201,   206,    22,   216,   218,    23,    24,    25,    26,
      27,     1,     2,     3,     4,     5,     6,   116,   224,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,   219,
      17,   192,   227,   230,   233,    75,    85,    76,   143,   226,
     144,   175,    73,   132,   203,     0,     0,    18,     0,     0,
       0,    19,    20,    21,     0,     0,     0,     0,     0,     0,
      22,     0,     0,    23,    24,    25,    26,     1,     2,     3,
       4,     5,     6,     0,     0,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     2,     3,     4,    68,
       0,     0,     0,    18,     0,     0,     0,    19,    20,    21,
      14,    15,    16,     0,    17,     0,    22,   116,     0,    23,
      24,    25,    26,     1,     2,     3,     4,    68,     0,     0,
       0,    18,     0,     0,     0,    19,    20,    21,    14,    15,
      16,   156,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     2,     3,     4,    68,     0,     0,     0,    18,
       0,     0,     0,    19,    20,    21,    14,    15,    16,     0,
      17,   176,     0,     0,     0,     0,     0,     0,     0,     1,
       2,     3,     4,    68,     0,     0,     0,    18,     0,     0,
       0,    19,    20,    21,    14,    15,    16,     0,    17,     0,
       0,   198,     0,     0,     0,     0,     0,     1,     2,     3,
       4,    68,     0,     0,     0,    18,     0,     0,     0,    19,
      20,    21,    14,    15,    16,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,    19,    20,    21
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-155))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      11,    17,    66,   121,   121,    16,    20,     7,    18,   163,
     164,    21,    25,    22,    20,    28,    20,    26,   136,     7,
      26,   139,    21,    29,    24,    32,    33,     7,   182,    28,
      21,    21,    46,    21,    21,    21,     7,    28,    28,    53,
      54,    28,    28,    23,    40,    41,    42,    21,   166,   166,
      61,    62,    63,   207,    28,    66,    20,   211,    18,    21,
      23,    21,   180,   217,    52,    28,    28,    55,    56,    57,
      58,   225,    52,    22,    90,    55,    56,    57,    58,   233,
     234,    52,    21,    20,    55,    56,    57,    58,   104,    28,
     208,   101,   102,   103,    20,    38,    39,    22,   114,     7,
     130,    26,   132,    29,   115,   169,    34,    35,    36,    37,
      95,    96,    97,    98,   125,    26,    20,    28,   129,   135,
      46,    47,    48,    49,    50,    51,    25,    53,    54,    28,
     141,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    52,     9,    10,    55,    56,    57,
      58,    25,   216,    26,    28,     7,    29,   168,   169,   170,
      26,   172,    28,     9,    10,     7,    93,    94,    99,   100,
       0,   187,     7,    24,     3,     4,     5,     6,     7,     8,
      24,    31,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    30,    22,    11,     7,    24,    23,     7,    24,
      20,    28,    26,    26,    26,   216,    24,    22,    27,    25,
      39,    25,     7,   224,    43,    44,    45,    24,    26,    24,
      24,     7,     7,    52,    26,    25,    55,    56,    57,    58,
      59,     3,     4,     5,     6,     7,     8,    25,    20,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    26,
      22,    23,    26,     7,    21,    15,    29,    15,    91,   213,
      92,   132,    13,    76,   180,    -1,    -1,    39,    -1,    -1,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    55,    56,    57,    58,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    44,    45,
      18,    19,    20,    -1,    22,    -1,    52,    25,    -1,    55,
      56,    57,    58,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    44,    45,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    43,    44,    45,    18,    19,    20,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    43,    44,    45,    18,    19,    20,    -1,    22,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    39,    -1,    -1,    -1,    43,
      44,    45,    18,    19,    20,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    44,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    22,    39,    43,
      44,    45,    52,    55,    56,    57,    58,    59,    61,    62,
      63,    64,    65,    66,    67,    68,    72,    73,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      91,    92,    95,    96,    97,    98,   100,   102,   103,   104,
     107,    24,    20,    20,    22,   105,    20,    20,     7,    72,
      99,     7,   101,   101,     7,    64,    65,    72,    73,    90,
      81,    83,    81,     7,     0,    63,    24,    24,     7,    26,
      28,    31,    30,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    20,    29,    46,    47,    48,    49,
      50,    51,    53,    54,    74,    24,    25,    72,    72,    72,
      23,   106,    11,    99,     7,    24,    26,    26,    26,    24,
      87,    88,    87,    21,    23,    28,    22,    25,    25,    20,
      26,    29,    73,    76,    77,    78,    78,    79,    79,    79,
      79,    80,    80,    81,    81,    81,    21,    70,    73,     7,
      73,    72,    25,    21,    21,    67,    71,    91,    20,    26,
      27,    72,    24,    88,    89,    89,    23,    73,     7,    67,
     108,   109,    21,    67,    69,    72,    21,    28,    25,   105,
     105,     7,    23,    91,    72,    99,    72,    25,    25,    24,
      24,     7,    23,   109,    26,   105,     7,    21,    28,    26,
      73,     9,    10,    93,    94,    21,    26,    21,    25,    26,
      26,   105,    67,   105,    20,     9,    94,    26,    99,   105,
       7,    72,   105,    21,    21,   105,   105
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
      yyerror (YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


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
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
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
#line 64 "minic.y"
    { 
			    TreeNode *program = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(program->name,"program");
			    TreeNode *edcl = nodes[--node_idx];
			    edcl->child = NULL;
			    edcl->sibling = NULL;
			    program->child = edcl;
			    nodes[node_idx++] = program;
			    tree = program;
			}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 76 "minic.y"
    {
			    TreeNode *program = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(program->name,"external_declaration_list");
			    TreeNode *edcl = nodes[--node_idx];
			    program->child = edcl;
			    nodes[node_idx++] = program;
			}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 84 "minic.y"
    {
			    TreeNode *program = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(program->name,"external_declaration_list");
			    TreeNode *edcl = nodes[--node_idx];
			    TreeNode *prog = nodes[--node_idx];
			    prog->sibling = edcl;
			    program->child = prog;
			    nodes[node_idx++] = program;
			}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 95 "minic.y"
    {
			    TreeNode *fd = nodes[--node_idx];
			    TreeNode *edcl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(edcl->name,"external_declaration");
			    edcl->child = fd;
			    nodes[node_idx++] = edcl;
			}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 103 "minic.y"
    {
                TreeNode *fd = nodes[--node_idx];
                TreeNode *edcl = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(edcl->name,"external_declaration");
                edcl->child = fd;
                nodes[node_idx++] = edcl;
			}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 111 "minic.y"
    {
			    MINIC_Compiler *compiler = minic_get_current_compiler();
			    compiler->statement_list = minic_chain_statement_list(compiler->statement_list,(yyvsp[(1) - (1)].statement));
			    TreeNode *st = nodes[--node_idx];
			    TreeNode *edcl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(edcl->name,"external_declaration");
			    edcl->child = st;
			    nodes[node_idx++] = edcl;
			}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 122 "minic.y"
    {
                (yyval.basic_type_specifier) = MVM_VOID_TYPE;
                TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ts->name,"basic_type_specifier");
                TreeNode *bn = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(bn->name,"void");
                ts->child = bn;
                nodes[node_idx++] = ts;
			}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 132 "minic.y"
    { 
			    (yyval.basic_type_specifier) = MVM_BOOLEAN_TYPE;
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"basic_type_specifier");
			    TreeNode *bn = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(bn->name,"boolean");
			    ts->child = bn;
			    nodes[node_idx++] = ts;
			}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 142 "minic.y"
    { 
			    (yyval.basic_type_specifier) = MVM_INTEGER_TYPE;
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"basic_type_specifier");
			    TreeNode *in = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(in->name,"integer");
			    ts->child = in;
			    nodes[node_idx++] = ts;
			}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 152 "minic.y"
    { 
			    (yyval.basic_type_specifier) = MVM_DECIMAL_TYPE;
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"basic_type_specifier");
			    TreeNode *dn = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(dn->name,"decimal");
			    ts->child = dn;
			    nodes[node_idx++] = ts;
			}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 162 "minic.y"
    { 
			    (yyval.basic_type_specifier) = MVM_STRING_TYPE;  
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"basic_type_specifier");
			    TreeNode *sn = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(sn->name,"string");
			    ts->child = sn;
			    nodes[node_idx++] = ts;
			}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 173 "minic.y"
    {
			    (yyval.type_specifier) = minic_create_class_type_specifier((yyvsp[(1) - (1)].identifier));
			    TreeNode *id = malloc(sizeof(TreeNode));
			    strcpy(id->name,(yyvsp[(1) - (1)].identifier));
			    TreeNode *cts = malloc(sizeof(TreeNode));
			    strcpy(cts->name,"class_type_specifier");
			    cts->child = id;
			    nodes[node_idx++] = cts;
			}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 184 "minic.y"
    {
			    TypeSpecifier *basic_type
				= minic_create_type_specifier((yyvsp[(1) - (3)].basic_type_specifier));
			    (yyval.type_specifier) = minic_create_array_type_specifier(basic_type);
			    TreeNode *rb = malloc(sizeof(TreeNode));
			    strcpy(rb->name,"]");
			    TreeNode *lb = malloc(sizeof(TreeNode));
			    strcpy(lb->name,"[");
			    TreeNode *bts = nodes[--node_idx];
			    TreeNode *ats = malloc(sizeof(TreeNode));
			    strcpy(ats->name,"array_type_specifier");
			    lb->sibling = rb;
			    bts->sibling = lb;
			    ats->child = bts;
		 	    nodes[node_idx++] = ats;
			}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 201 "minic.y"
    {
			    TypeSpecifier *class_type
				= minic_create_class_type_specifier((yyvsp[(1) - (3)].identifier));
			    (yyval.type_specifier) = minic_create_array_type_specifier(class_type);
			    TreeNode *rb = malloc(sizeof(TreeNode));
			    strcpy(rb->name,"]");
			    TreeNode *lb = malloc(sizeof(TreeNode));
			    strcpy(lb->name,"[");
			    TreeNode *id = malloc(sizeof(TreeNode));
			    strcpy(id->name,"array_type_specifier");
			    lb->sibling = rb;
			    id->sibling = lb;
			    TreeNode *ats = malloc(sizeof(TreeNode));
			    strcpy(ats->name,"array_type_specifier");
			    ats->child = id;
			    nodes[node_idx++] = ats;
			}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 219 "minic.y"
    {
			    (yyval.type_specifier) = minic_create_array_type_specifier((yyvsp[(1) - (3)].type_specifier));
                            TreeNode *rb = malloc(sizeof(TreeNode));
                            strcpy(rb->name,"]");
                            TreeNode *lb = malloc(sizeof(TreeNode));
                            strcpy(lb->name,"[");
			    TreeNode *atspc = nodes[--node_idx];
                            lb->sibling = rb;
                            atspc->sibling = lb;
                            TreeNode *ats = malloc(sizeof(TreeNode));
                            strcpy(ats->name,"array_type_specifier");
                            ats->child = atspc;
                            nodes[node_idx++] = ats;
			}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 235 "minic.y"
    {
			    (yyval.type_specifier) = minic_create_type_specifier((yyvsp[(1) - (1)].basic_type_specifier));
			    TreeNode *bts = nodes[--node_idx];
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"type_specifier");
			    ts->child = bts;
			    nodes[node_idx++] = ts;
			}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 244 "minic.y"
    {
			    TreeNode *tspc = nodes[--node_idx];
			    TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ts->name,"type_specifier");
			    ts->child = tspc;
			    nodes[node_idx++] = ts;
			}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 252 "minic.y"
    {
                TreeNode *tspc = nodes[--node_idx];
                TreeNode *ts = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ts->name,"type_specifier");
                ts->child = tspc;
                nodes[node_idx++] = ts;
			}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 261 "minic.y"
    {
			    minic_function_define((yyvsp[(1) - (6)].type_specifier),(yyvsp[(2) - (6)].identifier),(yyvsp[(4) - (6)].parameter_list),(yyvsp[(6) - (6)].block));
			    TreeNode *bnode = nodes[--node_idx];
			    TreeNode *rpNode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rpNode->name,")");
			    rpNode->sibling = bnode;
			    TreeNode *plnode = nodes[--node_idx];
			    plnode->sibling = rpNode;
			    TreeNode *lpNode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lpNode->name,"(");
			    lpNode->sibling = plnode;
			    TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(idnode->name,(yyvsp[(2) - (6)].identifier));
			    idnode->sibling = lpNode;
			    TreeNode *tsnode = nodes[--node_idx];
			    tsnode->sibling = idnode;
			    TreeNode *fdnode = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(fdnode->name,"function_definition");
			    fdnode->child = tsnode;
			    nodes[node_idx++] = fdnode;
			    
			}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 284 "minic.y"
    {
			    minic_function_define((yyvsp[(1) - (5)].type_specifier),(yyvsp[(2) - (5)].identifier),NULL,(yyvsp[(5) - (5)].block));
			    TreeNode *bnode = nodes[--node_idx];
                TreeNode *rpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rpNode->name,")");
                rpNode->sibling = bnode;
                TreeNode *lpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lpNode->name,"(");
                lpNode->sibling = rpNode;
                TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(idnode->name,(yyvsp[(2) - (5)].identifier));
                idnode->sibling = lpNode;
                TreeNode *tsnode = nodes[--node_idx];
                tsnode->sibling = idnode;
                TreeNode *fdnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(fdnode->name,"function_definition");
                fdnode->child = tsnode;
                nodes[node_idx++] = fdnode;
			}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 304 "minic.y"
    {
			    minic_function_define((yyvsp[(1) - (6)].type_specifier),(yyvsp[(2) - (6)].identifier),(yyvsp[(4) - (6)].parameter_list),NULL);
			    TreeNode *semnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semnode->name,";");
                TreeNode *rpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rpNode->name,")");
                rpNode->sibling = semnode;
                TreeNode *plnode = nodes[--node_idx];
                plnode->sibling = rpNode;
                TreeNode *lpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lpNode->name,"(");
                lpNode->sibling = plnode;
                TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(idnode->name,(yyvsp[(2) - (6)].identifier));
                idnode->sibling = lpNode;
                TreeNode *tsnode = nodes[--node_idx];
                tsnode->sibling = idnode;
                TreeNode *fdnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(fdnode->name,"function_definition");
                fdnode->child = tsnode;
                nodes[node_idx++] = fdnode;
			}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 327 "minic.y"
    {
			    minic_function_define((yyvsp[(1) - (5)].type_specifier),(yyvsp[(2) - (5)].identifier),NULL,NULL);
			    TreeNode *semnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semnode->name,";");
                TreeNode *rpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rpNode->name,")");
                rpNode->sibling = semnode;
                TreeNode *lpNode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lpNode->name,"(");
                lpNode->sibling = rpNode;
                TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(idnode->name,(yyvsp[(2) - (5)].identifier));
                idnode->sibling = lpNode;
                TreeNode *tsnode = nodes[--node_idx];
                tsnode->sibling = idnode;
                TreeNode *fdnode = (TreeNode*)malloc(sizeof(TreeNode));
    			strcpy(fdnode->name,"function_definition");
                fdnode->child = tsnode;
                nodes[node_idx++] = fdnode;
			}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 349 "minic.y"
    {
			    (yyval.parameter_list) = minic_create_parameter((yyvsp[(1) - (2)].type_specifier),(yyvsp[(2) - (2)].identifier));
			    TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(idnode->name,(yyvsp[(2) - (2)].identifier));
			    TreeNode *tsnode = nodes[--node_idx];
			    tsnode->sibling = idnode;
			    TreeNode *plnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(plnode->name,"parameter_list");
			    plnode->child = tsnode;
			    nodes[node_idx++] = plnode;
			}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 361 "minic.y"
    {
			    (yyval.parameter_list) = minic_chain_parameter((yyvsp[(1) - (4)].parameter_list),(yyvsp[(3) - (4)].type_specifier),(yyvsp[(4) - (4)].identifier));
			    TreeNode *idnode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(idnode->name,(yyvsp[(4) - (4)].identifier));
			    TreeNode *tsnode = nodes[--node_idx];
			    tsnode->sibling = idnode;
			    TreeNode *comma = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(comma->name,",");
			    comma->sibling = tsnode;
			    TreeNode *pl = nodes[--node_idx];
			    pl->sibling = comma;
			    TreeNode *pll = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(pll->name,"parameter_list");
			    pll->child = pl;
			    nodes[node_idx++] = pll;
			}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 379 "minic.y"
    {
			    (yyval.argument_list) = minic_create_argument_list((yyvsp[(1) - (1)].expression));
			    TreeNode *ase = nodes[--node_idx];
			    TreeNode *al = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(al->name,"argument_list");
			    al->child = ase;
			    nodes[node_idx++] = al;
			}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 388 "minic.y"
    {
			    (yyval.argument_list) = minic_chain_argument_list((yyvsp[(1) - (3)].argument_list),(yyvsp[(3) - (3)].expression));
			    TreeNode *ase = nodes[--node_idx];
			    TreeNode *comma = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(comma->name,",");
			    comma->sibling = ase;
			    TreeNode *arl = nodes[--node_idx];
			    arl->sibling = comma;
			    TreeNode *al = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(al->name,"argument_list");
			    al->child = arl;
			    nodes[node_idx++] = al;
			}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 403 "minic.y"
    {
			    (yyval.statement_list) = minic_create_statement_list((yyvsp[(1) - (1)].statement));
			    TreeNode *st = nodes[--node_idx];
			    TreeNode *sl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(sl->name,"statement_list");
			    sl->child = st;
			    nodes[node_idx++] = sl;
			}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 412 "minic.y"
    {
			    (yyval.statement_list) = minic_chain_statement_list((yyvsp[(1) - (2)].statement_list),(yyvsp[(2) - (2)].statement));
			    TreeNode *st = nodes[--node_idx];
			    TreeNode *stl = nodes[--node_idx];
			    stl->sibling = st;
			    TreeNode *sl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(sl->name,"statement_list");
			    sl->child = stl;
			    nodes[node_idx++] = sl;
			}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 424 "minic.y"
    {
			    TreeNode *ase = nodes[--node_idx];
			    TreeNode *exp = (TreeNode*)malloc(sizeof(TreeNode));
			    exp->child = ase;
			    strcpy(exp->name,"expression");
			    nodes[node_idx++] = exp;
			}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 432 "minic.y"
    {
			    (yyval.expression) = minic_create_comma_expression((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
			    TreeNode *ase = nodes[--node_idx];
			    TreeNode *comma = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(comma->name,",");
			    comma->sibling = ase;
			    TreeNode *expr = nodes[--node_idx];
			    expr->sibling = comma;
			    TreeNode *exp = (TreeNode*)malloc(sizeof(TreeNode));
                            exp->child = expr;
                            strcpy(exp->name,"expression");
                            nodes[node_idx++] = exp;
			}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 447 "minic.y"
    {
			    TreeNode *loe = nodes[--node_idx];
			    TreeNode *ase = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ase->name,"assignment_expression");
			    ase->child = loe;
			    nodes[node_idx++] = ase;
			}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 455 "minic.y"
    {
			    (yyval.expression) = minic_create_assign_expression((yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].assignment_operator),(yyvsp[(3) - (3)].expression));
			    TreeNode *ase = nodes[--node_idx];
			    TreeNode *aso = nodes[--node_idx];
			    TreeNode *pe = nodes[--node_idx];
			    aso->sibling = ase;
			    pe->sibling = aso;
			    TreeNode *ae = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ae->name,"assignment_expression");
			    ae->child = pe;
			    nodes[node_idx++] = ae;
			}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 469 "minic.y"
    { 
			    (yyval.assignment_operator) = NORMAL_ASSIGN;
			    TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(assign->name,":=");
			    TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ao->name,"assignment_operator");
			    ao->child = assign;
			    nodes[node_idx++] = ao;	
			}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 479 "minic.y"
    {
			    (yyval.assignment_operator) = ADD_ASSIGN;
			    TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(assign->name,"+=");  
                            TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(ao->name,"assignment_operator");     
                            ao->child = assign;
                            nodes[node_idx++] = ao;
			}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 489 "minic.y"
    { 
                            TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(assign->name,"-=");  
                            TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(ao->name,"assignment_operator");     
                            ao->child = assign;
                            nodes[node_idx++] = ao;
 			    (yyval.assignment_operator) = SUB_ASSIGN;	
			}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 499 "minic.y"
    { 
			    (yyval.assignment_operator) = MUL_ASSIGN;	
                            TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(assign->name,"*=");  
                            TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(ao->name,"assignment_operator");     
                            ao->child = assign;
                            nodes[node_idx++] = ao;
 			}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 509 "minic.y"
    { 
			    (yyval.assignment_operator) = DIV_ASSIGN;	
                            TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(assign->name,"/=");  
                            TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(ao->name,"assignment_operator");     
                            ao->child = assign;
                            nodes[node_idx++] = ao;
 			}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 519 "minic.y"
    { 
			    (yyval.assignment_operator) = MOD_ASSIGN;	
                            TreeNode *assign = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(assign->name,"%=");  
                            TreeNode *ao = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(ao->name,"assignment_operator");     
                            ao->child = assign;
                            nodes[node_idx++] = ao;
 			}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 529 "minic.y"
    {
			    TreeNode *lae = nodes[--node_idx];
			    TreeNode *loe = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(loe->name,"logical_or_expression");
			    loe->child = lae;
			    nodes[node_idx++] = loe;
			}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 537 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(LOGICAL_OR_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
			    TreeNode *lae = nodes[--node_idx];
			    TreeNode *logicalor = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(logicalor->name,"||");
			    logicalor->sibling = lae;
			    TreeNode *loexp = nodes[--node_idx];
			    loexp->sibling = logicalor;
			    TreeNode *loe = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(loe->name,"logical_or_expression");
			    loe->child = loexp;
			    nodes[node_idx++] = loe;
			}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 552 "minic.y"
    {
			    TreeNode *eexp = nodes[--node_idx];
			    TreeNode *lae = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lae->name,"logical_and_expression");
			    lae->child = eexp;
			    nodes[node_idx++] = lae;
			}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 560 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(LOGICAL_AND_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
			    TreeNode *eexp = nodes[--node_idx];
			    TreeNode *logicaland = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(logicaland->name,"&&");
			    logicaland->sibling = eexp;
			    TreeNode *laexp = nodes[--node_idx];
			    laexp->sibling = logicaland;
			    TreeNode *lae = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lae->name,"logical_and_expression");
			    nodes[node_idx++] = lae;
			}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 574 "minic.y"
    {
			    TreeNode *rexp = nodes[--node_idx];
			    TreeNode *eexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(eexp->name,"equality_expression");
			    eexp->child = rexp;
			    nodes[node_idx++] = eexp;
			}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 582 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(EQ_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
			    TreeNode *rexp = nodes[--node_idx];
			    TreeNode *eq = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(eq->name,"=");
			    eq->sibling = rexp;
			    TreeNode *ee = nodes[--node_idx];
			    ee->sibling = eq;
			    TreeNode *eexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(eexp->name,"equlity_expression");
			    eexp->child = ee;
			    nodes[node_idx++] = eexp;
			}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 596 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(NE_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
			    TreeNode *rexp = nodes[--node_idx];
                            TreeNode *eq = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(eq->name,"!=");
                            eq->sibling = rexp;
                            TreeNode *ee = nodes[--node_idx];
                            ee->sibling = eq;
                            TreeNode *eexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(eexp->name,"equlity_expression");
                            eexp->child = ee;
                            nodes[node_idx++] = eexp;
			}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 611 "minic.y"
    {
			    TreeNode *aexp = nodes[--node_idx];
                            TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rexp->name,"relation_expression");
                            rexp->child = aexp;
                            nodes[node_idx++] = rexp;
			}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 619 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(GT_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
                            TreeNode *aexp = nodes[--node_idx];
                            TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(gt->name,">");
                            gt->sibling = aexp;
                            TreeNode *re = nodes[--node_idx];
                            re->sibling = gt;
                            TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rexp->name,"relation_expression");
                            rexp->child = re;
                            nodes[node_idx++] = rexp;
 			}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 633 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(GE_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
                            TreeNode *aexp = nodes[--node_idx];
                            TreeNode *ge = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(ge->name,">=");
                            ge->sibling = aexp;
                            TreeNode *re = nodes[--node_idx];
                            re->sibling = ge;
                            TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rexp->name,"relation_expression");
                            rexp->child = re;
                            nodes[node_idx++] = rexp;
  			}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 647 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(LT_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
                            TreeNode *aexp = nodes[--node_idx];
                            TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(gt->name,"<");
                            gt->sibling = aexp;
                            TreeNode *re = nodes[--node_idx];
                            re->sibling = gt;
                            TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rexp->name,"relation_expression");
                            rexp->child = re;
                            nodes[node_idx++] = rexp;
  			}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 661 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(LE_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
                            TreeNode *aexp = nodes[--node_idx];
                            TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(gt->name,"<=");
                            gt->sibling = aexp;
                            TreeNode *re = nodes[--node_idx];
                            re->sibling = gt;
                            TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rexp->name,"relation_expression");
                            rexp->child = re;
                            nodes[node_idx++] = rexp;
  			}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 676 "minic.y"
    {
			    TreeNode *me = nodes[--node_idx];
			    TreeNode *aexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(aexp->name,"additive_expression");
			    aexp->child = me;
			    nodes[node_idx++] = aexp;
			}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 684 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(ADD_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
                            TreeNode *aexp = nodes[--node_idx];
                            TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(gt->name,"+");
                            gt->sibling = aexp;
                            TreeNode *re = nodes[--node_idx];
                            re->sibling = gt;
                            TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rexp->name,"additive_expression");
                            rexp->child = re;
                            nodes[node_idx++] = rexp;
  			}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 698 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(SUB_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
                            TreeNode *aexp = nodes[--node_idx];
                            TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(gt->name,"-");
                            gt->sibling = aexp;
                            TreeNode *re = nodes[--node_idx];
                            re->sibling = gt;
                            TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rexp->name,"additive_expression");
                            rexp->child = re;
                            nodes[node_idx++] = rexp;
  			}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 714 "minic.y"
    {
			    TreeNode *uexp = nodes[--node_idx];
			    TreeNode *me = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(me->name,"multiplicative_expression");
			    me->child = uexp;
			    nodes[node_idx++] = me;
			}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 722 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(MUL_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
                            TreeNode *aexp = nodes[--node_idx];
                            TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(gt->name,"*");
                            gt->sibling = aexp;
                            TreeNode *re = nodes[--node_idx];
                            re->sibling = gt;
                            TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rexp->name,"multiplicative_expression");
                            rexp->child = re;
                            nodes[node_idx++] = rexp;
  			}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 736 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(DIV_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
                            TreeNode *aexp = nodes[--node_idx];
                            TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(gt->name,"/");
                            gt->sibling = aexp;
                            TreeNode *re = nodes[--node_idx];
                            re->sibling = gt;
                            TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rexp->name,"multiplicative_expression");
                            rexp->child = re;
                            nodes[node_idx++] = rexp;
  			}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 750 "minic.y"
    {
			    (yyval.expression) = minic_create_binary_expression(MOD_EXPRESSION,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression));
                            TreeNode *aexp = nodes[--node_idx];
                            TreeNode *gt = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(gt->name,"%");
                            gt->sibling = aexp;
                            TreeNode *re = nodes[--node_idx];
                            re->sibling = gt;
                            TreeNode *rexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rexp->name,"multiplicative_expression");
                            rexp->child = re;
                            nodes[node_idx++] = rexp;
  			}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 765 "minic.y"
    {
			    TreeNode *postexp = nodes[--node_idx];
			    TreeNode *unaryexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(unaryexp->name,"unary_expression");
			    unaryexp->child = postexp;
			    nodes[node_idx++] = unaryexp;
			}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 773 "minic.y"
    { 
			    (yyval.expression) = minic_create_minus_expression((yyvsp[(2) - (2)].expression));
                            TreeNode *exp = nodes[--node_idx];
                            TreeNode *sub = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(sub->name,"-");
                            sub->sibling = exp;
                            TreeNode *uexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(uexp->name,"unary_expression");
                            uexp->child = sub;
                            nodes[node_idx++] = uexp;
  
			}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 786 "minic.y"
    { 
                            TreeNode *exp = nodes[--node_idx];
                            TreeNode *sub = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(sub->name,"!");
                            sub->sibling = exp;
                            TreeNode *uexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(uexp->name,"unary_expression");
                            uexp->child = sub;
                            nodes[node_idx++] = uexp;
			    (yyval.expression) = minic_create_logical_not_expression((yyvsp[(2) - (2)].expression));
			}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 799 "minic.y"
    {
			    TreeNode *pexp = nodes[--node_idx];
			    TreeNode *postexp = malloc(sizeof(TreeNode));
			    strcpy(postexp->name,"postfix_expression");
			    postexp->child = pexp;
			    nodes[node_idx++] = postexp;
			}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 807 "minic.y"
    {
                            (yyval.expression) = minic_create_incdec_expression((yyvsp[(1) - (2)].expression),INCREMENT_EXPRESSION);
                            TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rp->name,"++");
                            TreeNode *posexp = nodes[--node_idx];
                            posexp->sibling = rp;
                            TreeNode *postexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(postexp->name,"postfix_expression");
                            postexp->child = posexp;
                            nodes[node_idx++] = postexp;
                        }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 819 "minic.y"
    {
                            (yyval.expression) = minic_create_incdec_expression((yyvsp[(1) - (2)].expression),DECREMENT_EXPRESSION);
                            TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rp->name,"--");
                            TreeNode *posexp = nodes[--node_idx];
                            posexp->sibling = rp;
                            TreeNode *postexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(postexp->name,"postfix_expression");
                            postexp->child = posexp;
                            nodes[node_idx++] = postexp;
                        }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 832 "minic.y"
    {
			    TreeNode *pexp = nodes[--node_idx];
			    TreeNode *postexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(postexp->name,"primary_expression");
			    postexp->child = pexp;
			    nodes[node_idx++] = postexp;
			}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 840 "minic.y"
    {
			    TreeNode *ac = nodes[--node_idx];
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_expression");
                            pexp->child = ac;
                            nodes[node_idx++] = pexp;
			}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 848 "minic.y"
    { 
                            (yyval.expression) = minic_create_identifier_expression((yyvsp[(1) - (1)].identifier));
                            TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(id->name,(yyvsp[(1) - (1)].identifier));
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_expression");
                            pexp->child = id;
                            nodes[node_idx++] = pexp;
                        }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 859 "minic.y"
    {
			    (yyval.expression) = minic_create_index_expression((yyvsp[(1) - (4)].expression),(yyvsp[(3) - (4)].expression));
			    TreeNode *rb = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rb->name,"]");
			    TreeNode *exp = nodes[--node_idx];
			    TreeNode *lb = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lb->name,"[");
			    TreeNode *pna = nodes[--node_idx];
			    exp->sibling = rb;
			    lb->sibling = exp;
			    pna->sibling = lb;
			    TreeNode *pnna = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(pnna->name,"primary_no_new_array");
			    pnna->child = pna;
			    nodes[node_idx++] = pnna;
			}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 876 "minic.y"
    {
			    Expression *identifier = minic_create_identifier_expression((yyvsp[(1) - (4)].identifier));
			    (yyval.expression) = minic_create_index_expression(identifier,(yyvsp[(3) - (4)].expression));
			    TreeNode *rb = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rb->name,"]");
                            TreeNode *exp = nodes[--node_idx];
                            TreeNode *lb = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(lb->name,"[");
                            TreeNode *id = malloc(sizeof(TreeNode));
			    strcpy(id->name,(yyvsp[(1) - (4)].identifier));
                            exp->sibling = rb;
                            lb->sibling = exp;
                            id->sibling = lb;
                            TreeNode *pnna = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pnna->name,"primary_no_new_array");
                            pnna->child = id;
                            nodes[node_idx++] = pnna;
			}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 895 "minic.y"
    {
			    (yyval.expression) = minic_create_member_expression((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].identifier));
			    TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(id->name,(yyvsp[(3) - (3)].identifier));
			    TreeNode *dot = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(dot->name,".");
			    TreeNode *pe = nodes[--node_idx];
			    dot->sibling = id;
			    pe->sibling = dot;
			    TreeNode *pnna = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(pnna->name,"primary_no_new_array");
			    pnna->child = pe;
			    nodes[node_idx++] = pnna;
			}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 910 "minic.y"
    {
			    (yyval.expression) = minic_create_function_call_expression((yyvsp[(1) - (4)].expression),(yyvsp[(3) - (4)].argument_list));
			    TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rp->name,")");
			    TreeNode *al = nodes[--node_idx];
			    al->sibling = rp;
			    TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lp->name,"(");
			    lp->sibling = al;
			    TreeNode *posexp = nodes[--node_idx];
			    posexp->sibling = lp;
			    TreeNode *postexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(postexp->name,"primary_no_new_expression");
			    postexp->child = posexp;
			    nodes[node_idx++] = postexp;
			}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 927 "minic.y"
    {
			    (yyval.expression) = minic_create_function_call_expression((yyvsp[(1) - (3)].expression),NULL);
                            TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rp->name,")");
                            TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(lp->name,"(");
                            lp->sibling = rp;
                            TreeNode *posexp = nodes[--node_idx];
                            posexp->sibling = lp;
                            TreeNode *postexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(postexp->name,"primary_no_new_expression");
                            postexp->child = posexp;
                            nodes[node_idx++] = postexp;
			}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 942 "minic.y"
    { 
			    (yyval.expression) = (yyvsp[(2) - (3)].expression);
                            TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rp->name,")");
                            TreeNode *exp = nodes[--node_idx];
                            exp->sibling = rp;
                            TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(lp->name,"(");
                            lp->sibling = exp;
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_no_new_expression");
                            pexp->child = lp;
                            nodes[node_idx++] = pexp;
			     	
			}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 958 "minic.y"
    {
                            TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                            sprintf(id->name,"%d",(yyvsp[(1) - (1)].expression)->u.integer_value);
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_no_new_expression");
                            pexp->child = id;
                            nodes[node_idx++] = pexp;
			}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 967 "minic.y"
    {
                            TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                            sprintf(id->name,"%f",(yyvsp[(1) - (1)].expression)->u.decimal_value);
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_no_new_expression");
                            pexp->child = id;
                            nodes[node_idx++] = pexp;
			}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 976 "minic.y"
    {
                            TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                            sprintf(id->name,"%s",(yyvsp[(1) - (1)].expression)->u.string_value);
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_no_new_expression");
                            pexp->child = id;
                            nodes[node_idx++] = pexp;
			}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 985 "minic.y"
    {
                            TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                            sprintf(id->name,"%s",(yyvsp[(1) - (1)].expression)->u.string_value);
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_no_new_expression");
                            pexp->child = id;
                            nodes[node_idx++] = pexp;
			}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 994 "minic.y"
    { 
			    (yyval.expression) = minic_create_boolean_expression(MVM_TRUE);
                            TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(id->name,"true");
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_no_new_expression");
                            pexp->child = id;
                            nodes[node_idx++] = pexp;
			}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1004 "minic.y"
    { 
			    (yyval.expression) = minic_create_boolean_expression(MVM_FALSE);
                            TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(id->name,"false");
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_no_new_expression");
                            pexp->child = id;
                            nodes[node_idx++] = pexp;
			}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1014 "minic.y"
    {
			    (yyval.expression) = minic_create_null_expression();
                            TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(id->name,"null");
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_no_new_expression");
                            pexp->child = id;
                            nodes[node_idx++] = pexp;
			}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1024 "minic.y"
    {
                            TreeNode *id = nodes[--node_idx];
                            TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(pexp->name,"primary_no_new_expression");
                            pexp->child = id;
                            nodes[node_idx++] = pexp;
			}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1033 "minic.y"
    {
			    (yyval.expression) = minic_create_array_literal_expression((yyvsp[(2) - (3)].expression_list));
			    TreeNode *rc = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rc->name,"}");
			    TreeNode *expl = nodes[--node_idx];
			    TreeNode *lc = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lc->name,"{");
			    TreeNode *arrl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(arrl->name,"array_literal");
			    expl->sibling = rc;
			    lc->sibling = expl;
			    arrl->child = lc;
			    nodes[node_idx++] = arrl;
			}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1048 "minic.y"
    {
			    (yyval.expression) = minic_create_array_literal_expression((yyvsp[(2) - (4)].expression_list));
                            TreeNode *rc = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rc->name,"}");
			    TreeNode *comma = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(comma->name,",");
                            TreeNode *expl = nodes[--node_idx];
                            TreeNode *lc = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(lc->name,"{");
                            TreeNode *arrl = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(arrl->name,"array_literal");
                            comma->sibling = rc;
			    expl->sibling = comma;
                            lc->sibling = expl;
                            arrl->child = lc;
                            nodes[node_idx++] = arrl;
			}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1067 "minic.y"
    {
			    (yyval.expression) = minic_create_basic_array_creation((yyvsp[(2) - (3)].basic_type_specifier),(yyvsp[(3) - (3)].array_dimension),NULL);
			    TreeNode *del = nodes[--node_idx];
			    TreeNode *bts = nodes[--node_idx];
			    TreeNode *new = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(new->name,"new");
			    TreeNode *ac = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ac->name,"array_creation");
			    bts->sibling = del;
			    new->sibling = bts;
			    ac->child = new;
			    nodes[node_idx++] = ac;
			}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1081 "minic.y"
    {
			    (yyval.expression) = minic_create_basic_array_creation((yyvsp[(2) - (4)].basic_type_specifier),(yyvsp[(3) - (4)].array_dimension),(yyvsp[(4) - (4)].array_dimension));
			    TreeNode *dl = nodes[--node_idx];
                            TreeNode *del = nodes[--node_idx];
                            TreeNode *bts = nodes[--node_idx];
                            TreeNode *new = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(new->name,"new");
                            TreeNode *ac = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(ac->name,"array_creation");
			    del->sibling = dl;
                            bts->sibling = del;
                            new->sibling = bts;
                            ac->child = new;
                            nodes[node_idx++] = ac;
			}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1097 "minic.y"
    {
                            (yyval.expression) = minic_create_class_array_creation((yyvsp[(2) - (3)].type_specifier),(yyvsp[(3) - (3)].array_dimension),NULL);
                            TreeNode *del = nodes[--node_idx];
                            TreeNode *bts = nodes[--node_idx];
                            TreeNode *new = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(new->name,"new");
                            TreeNode *ac = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(ac->name,"array_creation");
                            bts->sibling = del;
                            new->sibling = bts;
                            ac->child = new;
                            nodes[node_idx++] = ac;
                        }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1111 "minic.y"
    {
                            (yyval.expression) = minic_create_class_array_creation((yyvsp[(2) - (4)].type_specifier),(yyvsp[(3) - (4)].array_dimension),(yyvsp[(4) - (4)].array_dimension));
                            TreeNode *dl = nodes[--node_idx];
                            TreeNode *del = nodes[--node_idx];
                            TreeNode *bts = nodes[--node_idx];
                            TreeNode *new = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(new->name,"new");
			    TreeNode *ac = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(ac->name,"array_creation");
                            del->sibling = dl;
                            bts->sibling = del;
                            new->sibling = bts;
                            ac->child = new;
                            nodes[node_idx++] = ac;
                        }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1128 "minic.y"
    {
			    TreeNode *de = nodes[--node_idx];
			    TreeNode *del = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(del->name,"dimension_expression_list");
			    del->child = de;
			    nodes[node_idx++] = del;
			}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1136 "minic.y"
    {
			    (yyval.array_dimension) = minic_chain_array_dimension((yyvsp[(1) - (2)].array_dimension),(yyvsp[(2) - (2)].array_dimension));
			    TreeNode *de = nodes[--node_idx];
			    TreeNode *delist = nodes[--node_idx];
			    TreeNode *del = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(del->name,"dimension_expression_list");
                            delist->sibling = de;
			    del->child = delist;
                            nodes[node_idx++] = del;
			}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1148 "minic.y"
    {
			    (yyval.array_dimension) = minic_create_array_dimension((yyvsp[(2) - (3)].expression));
			    TreeNode *rb = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rb->name,"]");
			    TreeNode *exp = nodes[--node_idx];
			    TreeNode *lb = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lb->name,"[");
			    TreeNode *dimexp = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(dimexp->name,"dimension_expression");
			    exp->sibling = rb;
			    lb->sibling = exp;
			    dimexp->child = lb;
			    nodes[node_idx++] = dimexp;
			}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1164 "minic.y"
    {
			    (yyval.array_dimension) = minic_create_array_dimension(NULL);
			    TreeNode *rb = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rb->name,"]");
                TreeNode *lb = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lb->name,"[");
                TreeNode *dimexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(dimexp->name,"dimension_list");
                lb->sibling = rb;
                dimexp->child = lb;
                nodes[node_idx++] = dimexp;
			}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1177 "minic.y"
    {
			    (yyval.array_dimension) = minic_chain_array_dimension((yyvsp[(1) - (3)].array_dimension),minic_create_array_dimension(NULL));
			    TreeNode *rb = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rb->name,"]");
                TreeNode *lb = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lb->name,"[");
    			TreeNode *dl = nodes[--node_idx];
                TreeNode *dimexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(dimexp->name,"dimension_list");
                lb->sibling = rb;
                dl->sibling = lb;
                dimexp->child = dl;
                nodes[node_idx++] = dimexp;
			}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1193 "minic.y"
    {
			    (yyval.expression_list) = NULL;
			    TreeNode *empty = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(empty->name,"#");
			    TreeNode *expl = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(expl->name,"expression_list");
			    expl->child = empty;
			    nodes[node_idx++] = expl;
			}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1203 "minic.y"
    {
			    (yyval.expression_list) = minic_create_expression_list((yyvsp[(1) - (1)].expression));
			    TreeNode *ae = nodes[--node_idx];
			    TreeNode *expl = (TreeNode*)malloc(sizeof(TreeNode));	
			    strcpy(expl->name,"expression_list");
			    expl->child = ae;
			    nodes[node_idx++] = expl;
			}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1212 "minic.y"
    {
			    (yyval.expression_list) = minic_chain_expression_list((yyvsp[(1) - (3)].expression_list),(yyvsp[(3) - (3)].expression));
			    TreeNode *ae = nodes[--node_idx];
                TreeNode *comma = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(comma->name,",");
			    TreeNode *explist = nodes[--node_idx];
			    TreeNode *expl = (TreeNode*)malloc(sizeof(TreeNode));                       
                strcpy(expl->name,"expression_list");
			    comma->sibling = ae;
			    explist->sibling = comma;
                expl->child = explist;
                nodes[node_idx++] = expl;
			}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 1227 "minic.y"
    {
			    (yyval.statement) = minic_create_expression_statement((yyvsp[(1) - (2)].expression));
			    TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    TreeNode *exp = nodes[--node_idx];
			    exp->sibling = semi;
			    TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(statement->name,"statement");
			    statement->child = exp;
			    nodes[node_idx++] = statement;
			}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1239 "minic.y"
    {
			    TreeNode *stmt = nodes[--node_idx];
			    TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(statement->name,"statement");
			    statement->child = stmt;
			    nodes[node_idx++] = statement;
			}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1247 "minic.y"
    {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                nodes[node_idx++] = statement;
            }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1255 "minic.y"
    {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                nodes[node_idx++] = statement;
            }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1263 "minic.y"
    {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                nodes[node_idx++] = statement;
            }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1271 "minic.y"
    {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                nodes[node_idx++] = statement;
            }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1279 "minic.y"
    {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                nodes[node_idx++] = statement;
            }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1287 "minic.y"
    {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                nodes[node_idx++] = statement;
            }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1295 "minic.y"
    {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                nodes[node_idx++] = statement;
            }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1303 "minic.y"
    {
                TreeNode *stmt = nodes[--node_idx];
                TreeNode *statement = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(statement->name,"statement");
                statement->child = stmt;
                nodes[node_idx++] = statement;
            }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1312 "minic.y"
    {
			    (yyval.statement) = minic_create_if_statement((yyvsp[(3) - (5)].expression),(yyvsp[(5) - (5)].block),NULL,NULL);
			    TreeNode *bnode = nodes[--node_idx];
				TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
				strcpy(rp->name,")");
				rp->sibling = bnode;
				TreeNode *exp = nodes[--node_idx];
				exp->sibling = rp;
				TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
				strcpy(lp->name,"(");
				lp->sibling = exp;
				TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
				strcpy(ifnode->name,"IF");
				ifnode->sibling = lp;
				TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
				strcpy(pexp->name,"if_statement");
				pexp->child = ifnode;
				nodes[node_idx++] = pexp;
			}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1332 "minic.y"
    {
			    (yyval.statement) = minic_create_if_statement((yyvsp[(3) - (7)].expression),(yyvsp[(5) - (7)].block),NULL,(yyvsp[(7) - (7)].block));
			    TreeNode *block = nodes[--node_idx];
			    TreeNode *elsenode = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(elsenode->name,"ELSE");
			    elsenode->sibling = block;
                TreeNode *bnode = nodes[--node_idx];
    			bnode->sibling = elsenode;
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"IF");
                ifnode->sibling = lp;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"if_statement");
                pexp->child = ifnode;
                nodes[node_idx++] = pexp;
			}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1357 "minic.y"
    {
			    (yyval.statement) = minic_create_if_statement((yyvsp[(3) - (6)].expression),(yyvsp[(5) - (6)].block),(yyvsp[(6) - (6)].elseif),NULL);
                TreeNode *elsenode = nodes[--node_idx];
                TreeNode *bnode = nodes[--node_idx];
                bnode->sibling = elsenode;
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"IF");
                ifnode->sibling = lp;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"if_statement");
                pexp->child = ifnode;
                nodes[node_idx++] = pexp;
			}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1379 "minic.y"
    {
			    (yyval.statement) = minic_create_if_statement((yyvsp[(3) - (8)].expression),(yyvsp[(5) - (8)].block),(yyvsp[(6) - (8)].elseif),(yyvsp[(8) - (8)].block));
                TreeNode *block = nodes[--node_idx];
                TreeNode *elsenode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(elsenode->name,"ELSE");
                elsenode->sibling = block;
			    TreeNode *elselist = nodes[--node_idx];
			    elselist->sibling = elsenode;
                TreeNode *bnode = nodes[--node_idx];
                bnode->sibling = elselist;
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"IF");
                ifnode->sibling = lp;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"if_statement");
                pexp->child = ifnode;
                nodes[node_idx++] = pexp;
			}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1407 "minic.y"
    {
			    TreeNode *elseifnode = nodes[--node_idx];
			    TreeNode *elselist = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(elselist->name,"elseif_list");
			    elselist->child = elseifnode;
			    nodes[node_idx++] = elselist;
			}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1415 "minic.y"
    {
			    (yyval.elseif) = minic_chain_elseif_list((yyvsp[(1) - (2)].elseif),(yyvsp[(2) - (2)].elseif));
			    TreeNode *elseifnode = nodes[--node_idx];
			    TreeNode *elnode = nodes[--node_idx];
			    elnode->sibling = elseifnode;
			    TreeNode *elselist = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(elselist->name,"elseif_list");
			    elselist->child = elnode;
			    nodes[node_idx++] = elselist;
			}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1427 "minic.y"
    {
			    (yyval.elseif) = minic_create_elseif((yyvsp[(3) - (5)].expression),(yyvsp[(5) - (5)].block));
                TreeNode *bnode = nodes[--node_idx];
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"ELSEIF");
                ifnode->sibling = lp;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"elseif");
                pexp->child = ifnode;
                nodes[node_idx++] = pexp;
			}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1448 "minic.y"
    {
			    (yyval.statement) = minic_create_while_statement(NULL,(yyvsp[(3) - (5)].expression),(yyvsp[(5) - (5)].block));
                TreeNode *bnode = nodes[--node_idx];
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = exp;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"while");
                ifnode->sibling = lp;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"while_statement");
                pexp->child = ifnode;
                nodes[node_idx++] = pexp;
			}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1470 "minic.y"
    {
			    (yyval.statement) = minic_create_for_statement(NULL,(yyvsp[(3) - (9)].expression),(yyvsp[(5) - (9)].expression),(yyvsp[(7) - (9)].expression),(yyvsp[(9) - (9)].block));
                TreeNode *bnode = nodes[--node_idx];
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                TreeNode *postexp = nodes[--node_idx];
                postexp->sibling = rp;
			    TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    semi->sibling = postexp;
			    TreeNode *condexp = nodes[--node_idx];
			    condexp->sibling = semi;
			    TreeNode *semic = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semic->name,";");
			    semic->sibling = condexp;
			    TreeNode *initexp = nodes[--node_idx];
			    initexp->sibling = semic;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = initexp;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"for");
                ifnode->sibling = lp;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"for_statement");
                pexp->child = ifnode;
                nodes[node_idx++] = pexp;
			}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1501 "minic.y"
    {
			    (yyval.statement) = minic_create_do_while_statement(NULL,(yyvsp[(2) - (7)].block),(yyvsp[(5) - (7)].expression));
			    TreeNode *semi = malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    TreeNode *rp = malloc(sizeof(TreeNode));
			    strcpy(rp->name,")");
			    TreeNode *exp = nodes[--node_idx];
			    TreeNode *lp = malloc(sizeof(TreeNode));
			    strcpy(lp->name,"(");
			    TreeNode *wnode = malloc(sizeof(TreeNode));
			    strcpy(wnode->name,"while");
			    TreeNode *bnode = nodes[--node_idx];
			    TreeNode *dnode = malloc(sizeof(TreeNode));
			    strcpy(dnode->name,"do");
			    TreeNode *dwstmt = malloc(sizeof(TreeNode));
			    strcpy(dwstmt->name,"do_while_statement");
			    rp->sibling = semi;
			    exp->sibling = rp;
			    lp->sibling = exp;
			    wnode->sibling = lp;
			    bnode->sibling = wnode;
			    dnode->sibling = bnode;
			    dwstmt->child = dnode;
			    nodes[node_idx++] = dwstmt;
			}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1528 "minic.y"
    {
			    (yyval.statement) = minic_create_foreach_statement(NULL,(yyvsp[(3) - (7)].identifier),(yyvsp[(5) - (7)].expression),(yyvsp[(7) - (7)].block));
                TreeNode *bnode = nodes[--node_idx];
                TreeNode *rp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(rp->name,")");
                rp->sibling = bnode;
                TreeNode *exp = nodes[--node_idx];
                exp->sibling = rp;
			    TreeNode *colon = (TreeNode*)malloc(sizeof(TreeNode));
		  	    strcpy(colon->name,":");
			    colon->sibling = exp;
			    TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(id->name,(yyvsp[(3) - (7)].identifier));
			    id->sibling = colon;
                TreeNode *lp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(lp->name,"(");
                lp->sibling = id;
                TreeNode *ifnode = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(ifnode->name,"foreach");
                ifnode->sibling = lp;
                TreeNode *pexp = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(pexp->name,"foreach_statement");
                pexp->child = ifnode;
                nodes[node_idx++] = pexp;
			}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1555 "minic.y"
    { 
			    (yyval.expression) = NULL;
			    TreeNode *empty = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(empty->name,"#");
			    TreeNode *eopt = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(eopt->name,"expression_opt");
			    eopt->child = empty;
			    nodes[node_idx++] = eopt;
			}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1565 "minic.y"
    {
                TreeNode *empty = nodes[--node_idx];
                TreeNode *eopt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(eopt->name,"expression_opt");
                eopt->child = empty;
                nodes[node_idx++] = eopt;
			}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1574 "minic.y"
    {
			    (yyval.statement) = minic_create_return_statement((yyvsp[(2) - (3)].expression));
			    TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    TreeNode *exp = nodes[--node_idx];
			    exp->sibling = semi;
			    TreeNode *ret = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(ret->name,"return");
			    ret->sibling = exp;
			    TreeNode *retstmt = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(retstmt->name,"return_statement");
			    retstmt->child = ret;
			    nodes[node_idx++] = retstmt;
			}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1590 "minic.y"
    { 
			    (yyval.identifier) = NULL;
			    TreeNode *empty = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(empty->name,"#");
                TreeNode *iopt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(iopt->name,"identifier_opt");
                iopt->child = empty;
                nodes[node_idx++] = iopt;
			}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1600 "minic.y"
    {
			    TreeNode *empty = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(empty->name,(yyvsp[(1) - (1)].identifier));
                TreeNode *iopt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(iopt->name,"identifier_opt");
                iopt->child = empty;
                nodes[node_idx++] = iopt;
			}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1610 "minic.y"
    {
			    (yyval.statement) = minic_create_break_statement((yyvsp[(2) - (3)].identifier));
                TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(semi->name,";");
                TreeNode *id = nodes[--node_idx];
                id->sibling = semi;
                TreeNode *brea = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(brea->name,"break");
                brea->sibling = id;
                TreeNode *retstmt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(retstmt->name,"break_statement");
                retstmt->child = brea;
                nodes[node_idx++] = retstmt;
			}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1626 "minic.y"
    {
			    (yyval.statement) = minic_create_continue_statement((yyvsp[(2) - (3)].identifier));
                TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(semi->name,";");
                TreeNode *id = nodes[--node_idx];
                id->sibling = semi;
                TreeNode *cont = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(cont->name,"continue");
                cont->sibling = id;
                TreeNode *retstmt = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(retstmt->name,"continue_statement");
                retstmt->child = cont;
                nodes[node_idx++] = retstmt;
			}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1642 "minic.y"
    {
			    (yyval.statement) = minic_create_declaration_statement((yyvsp[(1) - (3)].type_specifier),(yyvsp[(2) - (3)].identifier),NULL);
                TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
    			strcpy(semi->name,";");
                TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                strcpy(id->name,(yyvsp[(2) - (3)].identifier));
                id->sibling = semi;
			    TreeNode *tsnode = nodes[--node_idx];
		 	    tsnode->sibling = id;
                            TreeNode *decstmt = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(decstmt->name,"declaration_statement");
                            decstmt->child = tsnode;
                            nodes[node_idx++] = decstmt;
			}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1657 "minic.y"
    {
			    (yyval.statement) = minic_create_declaration_statement((yyvsp[(1) - (5)].type_specifier),(yyvsp[(2) - (5)].identifier),(yyvsp[(4) - (5)].expression));
                            TreeNode *semi = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    TreeNode *exp = nodes[--node_idx];
			    exp->sibling = semi;
			    TreeNode *asst = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(asst->name,":=");
			    asst->sibling = exp;
                            TreeNode *id = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(id->name,(yyvsp[(2) - (5)].identifier));
                            id->sibling = asst;
                            TreeNode *tsnode = nodes[--node_idx];
                            tsnode->sibling = id;
                            TreeNode *decstmt = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(decstmt->name,"declaraton_statement");
                            decstmt->child = tsnode;
                            nodes[node_idx++] = decstmt;
			}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1678 "minic.y"
    {
			    (yyval.block) = minic_open_block();
			}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1682 "minic.y"
    {
			    (yyval.block) = minic_close_block((yyvsp[(2) - (4)].block),(yyvsp[(3) - (4)].statement_list));
			    TreeNode *rc = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(rc->name,"}");
			    TreeNode *sl = nodes[--node_idx];
			    sl->sibling = rc;
			    TreeNode *lc = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(lc->name,"{");
			    lc->sibling = sl;
			    TreeNode *block = (TreeNode*)malloc(sizeof(TreeNode));
			    strcpy(block->name,"block");
			    block->child = lc;
			    nodes[node_idx++] = block;
			}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1697 "minic.y"
    {
			    Block *empty_block = minic_open_block();
			    (yyval.block) = minic_close_block(empty_block,NULL);
                            TreeNode *rc = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(rc->name,"}");
                            TreeNode *lc = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(lc->name,"{");
                            lc->sibling = rc;
                            TreeNode *block = (TreeNode*)malloc(sizeof(TreeNode));
                            strcpy(block->name,"block");
                            block->child = lc;
                            nodes[node_idx++] = block;
			}
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1712 "minic.y"
    {
		 	    minic_start_class_definition((yyvsp[(2) - (5)].identifier));
			    minic_class_define((yyvsp[(4) - (5)].member_declaration));
			    TreeNode *rc = malloc(sizeof(TreeNode));
			    strcpy(rc->name,"}");
			    TreeNode *mdl = nodes[--node_idx];
			    TreeNode *lc = malloc(sizeof(TreeNode));
			    strcpy(lc->name,"{");
			    TreeNode *id = malloc(sizeof(TreeNode));
			    strcpy(id->name,(yyvsp[(2) - (5)].identifier));
			    TreeNode *class = malloc(sizeof(TreeNode));
			    strcpy(class->name,"structure");
			    TreeNode *cd = malloc(sizeof(TreeNode));
			    strcpy(cd->name,"class_definition");
			    mdl->sibling = rc;
			    lc->sibling = mdl;
			    id->sibling = lc;
			    class->sibling = id;
			    cd->child = class;
			    nodes[node_idx++] = cd;
			}
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1804 "minic.y"
    {
			    TreeNode *md = nodes[--node_idx];
			    TreeNode *mdl = malloc(sizeof(TreeNode));
			    strcpy(mdl->name,"member_declaration_list");
			    mdl->child = md;
			    nodes[node_idx++] = mdl;
			}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1812 "minic.y"
    {
			    (yyval.member_declaration) = minic_chain_member_declaration((yyvsp[(1) - (2)].member_declaration),(yyvsp[(2) - (2)].member_declaration));
			    TreeNode *md = nodes[--node_idx];
			    TreeNode *mdlist = nodes[--node_idx];
			    TreeNode *mdl = malloc(sizeof(TreeNode));
			    strcpy(mdl->name,"member_declaration_list");
			    mdlist->sibling = md;
			    mdl->child = mdlist;
			    nodes[node_idx++] = mdl;
			}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1824 "minic.y"
    {
			    (yyval.member_declaration) = minic_create_field_member((yyvsp[(1) - (3)].type_specifier),(yyvsp[(2) - (3)].identifier));
			    TreeNode *semi = malloc(sizeof(TreeNode));
			    strcpy(semi->name,";");
			    TreeNode *id = malloc(sizeof(TreeNode));
			    strcpy(id->name,(yyvsp[(2) - (3)].identifier));
			    TreeNode *ts = nodes[--node_idx];
			    id->sibling = semi;	
			    ts->sibling = id;
			    TreeNode *md = malloc(sizeof(TreeNode));
			    strcpy(md->name,"member_declaration");
			    md->child = ts;
			    nodes[node_idx++] = md;
			}
    break;



/* Line 1806 of yacc.c  */
#line 4087 "y.tab.c"
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
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
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
		      yytoken, &yylval);
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
		  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
#line 1857 "minic.y"


