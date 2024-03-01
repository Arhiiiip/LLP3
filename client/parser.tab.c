/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser.y"

    #include "ast_tree.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>

    int yylex();
    int yyparse();
    void yyerror(const char *s);
    extern char *yytext;

    struct ast_tree tree = {.type = UNDEFINED};
    bool array_list_created = false;
    struct statement *cur_statement = NULL;

    char *file_name;
    int opened = 0;

#line 91 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VERTEX = 3,                     /* VERTEX  */
  YYSYMBOL_HAS = 4,                        /* HAS  */
  YYSYMBOL_OUT = 5,                        /* OUT  */
  YYSYMBOL_OPEN = 6,                       /* OPEN  */
  YYSYMBOL_CREATE = 7,                     /* CREATE  */
  YYSYMBOL_CLOSE = 8,                      /* CLOSE  */
  YYSYMBOL_DELETE = 9,                     /* DELETE  */
  YYSYMBOL_CREATE_SCHEMA = 10,             /* CREATE_SCHEMA  */
  YYSYMBOL_DELETE_SCHEMA = 11,             /* DELETE_SCHEMA  */
  YYSYMBOL_ADD_VERTEX = 12,                /* ADD_VERTEX  */
  YYSYMBOL_TOK_NODES = 13,                 /* TOK_NODES  */
  YYSYMBOL_EQUALS = 14,                    /* EQUALS  */
  YYSYMBOL_GREATER = 15,                   /* GREATER  */
  YYSYMBOL_GREATER_EQUALS = 16,            /* GREATER_EQUALS  */
  YYSYMBOL_LESS = 17,                      /* LESS  */
  YYSYMBOL_LESS_EQUALS = 18,               /* LESS_EQUALS  */
  YYSYMBOL_NOT_EQUALS = 19,                /* NOT_EQUALS  */
  YYSYMBOL_CONTAINS = 20,                  /* CONTAINS  */
  YYSYMBOL_INTEGER = 21,                   /* INTEGER  */
  YYSYMBOL_DECIMAL = 22,                   /* DECIMAL  */
  YYSYMBOL_BOOLEAN = 23,                   /* BOOLEAN  */
  YYSYMBOL_WORD = 24,                      /* WORD  */
  YYSYMBOL_FILENAME = 25,                  /* FILENAME  */
  YYSYMBOL_MY_INTEGER = 26,                /* MY_INTEGER  */
  YYSYMBOL_MY_FLOAT = 27,                  /* MY_FLOAT  */
  YYSYMBOL_MY_STRING = 28,                 /* MY_STRING  */
  YYSYMBOL_MY_BOOLEAN = 29,                /* MY_BOOLEAN  */
  YYSYMBOL_MY_REF = 30,                    /* MY_REF  */
  YYSYMBOL_VALUES = 31,                    /* VALUES  */
  YYSYMBOL_OTHER = 32,                     /* OTHER  */
  YYSYMBOL_RIGHT_BRACE = 33,               /* RIGHT_BRACE  */
  YYSYMBOL_LEFT_BRACE = 34,                /* LEFT_BRACE  */
  YYSYMBOL_QUOTE = 35,                     /* QUOTE  */
  YYSYMBOL_DOT = 36,                       /* DOT  */
  YYSYMBOL_COMMA = 37,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 38,                 /* SEMICOLON  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_commands = 40,                  /* commands  */
  YYSYMBOL_command = 41,                   /* command  */
  YYSYMBOL_select = 42,                    /* select  */
  YYSYMBOL_open_file = 43,                 /* open_file  */
  YYSYMBOL_create_file = 44,               /* create_file  */
  YYSYMBOL_close_file = 45,                /* close_file  */
  YYSYMBOL_create_schema = 46,             /* create_schema  */
  YYSYMBOL_delete_schema = 47,             /* delete_schema  */
  YYSYMBOL_add_vertex = 48,                /* add_vertex  */
  YYSYMBOL_select_nodes = 49,              /* select_nodes  */
  YYSYMBOL_select_condition = 50,          /* select_condition  */
  YYSYMBOL_join = 51,                      /* join  */
  YYSYMBOL_delete_command = 52,            /* delete_command  */
  YYSYMBOL_select_statements = 53,         /* select_statements  */
  YYSYMBOL_select_statement = 54,          /* select_statement  */
  YYSYMBOL_attribute_value_pairs = 55,     /* attribute_value_pairs  */
  YYSYMBOL_attribute_value_pair = 56,      /* attribute_value_pair  */
  YYSYMBOL_attribute_pairs = 57,           /* attribute_pairs  */
  YYSYMBOL_data_type = 58,                 /* data_type  */
  YYSYMBOL_attribute_pair = 59,            /* attribute_pair  */
  YYSYMBOL_cmp_type = 60,                  /* cmp_type  */
  YYSYMBOL_argument = 61                   /* argument  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   90

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  107

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    71,    75,    76,    77,    78,    79,    80,
      81,    85,    86,    87,    88,    92,   100,   108,   116,   124,
     132,   140,   146,   147,   157,   158,   172,   173,   185,   186,
     187,   191,   205,   219,   233,   249,   250,   254,   264,   274,
     284,   297,   298,   302,   303,   304,   305,   306,   310,   320,
     335,   336,   337,   338,   339,   340,   341,   345
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VERTEX", "HAS", "OUT",
  "OPEN", "CREATE", "CLOSE", "DELETE", "CREATE_SCHEMA", "DELETE_SCHEMA",
  "ADD_VERTEX", "TOK_NODES", "EQUALS", "GREATER", "GREATER_EQUALS", "LESS",
  "LESS_EQUALS", "NOT_EQUALS", "CONTAINS", "INTEGER", "DECIMAL", "BOOLEAN",
  "WORD", "FILENAME", "MY_INTEGER", "MY_FLOAT", "MY_STRING", "MY_BOOLEAN",
  "MY_REF", "VALUES", "OTHER", "RIGHT_BRACE", "LEFT_BRACE", "QUOTE", "DOT",
  "COMMA", "SEMICOLON", "$accept", "commands", "command", "select",
  "open_file", "create_file", "close_file", "create_schema",
  "delete_schema", "add_vertex", "select_nodes", "select_condition",
  "join", "delete_command", "select_statements", "select_statement",
  "attribute_value_pairs", "attribute_value_pair", "attribute_pairs",
  "data_type", "attribute_pair", "cmp_type", "argument", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-24)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -24,    15,   -24,   -10,     1,    13,    14,    16,    18,    19,
     -19,    10,   -24,   -24,   -24,   -24,   -24,   -24,   -24,    20,
      21,    22,    23,    20,    20,    20,   -24,     5,   -24,   -24,
     -24,    30,    26,    35,    36,    37,   -24,    31,   -24,    29,
      32,   -24,    33,   -24,    34,    39,    40,   -21,   -24,    12,
     -24,    20,   -24,    38,    43,    44,   -24,    20,   -24,    20,
     -22,    45,   -24,   -24,   -24,   -24,    28,   -24,    42,   -24,
      46,    47,   -24,     3,   -18,   -24,    24,   -24,   -24,   -24,
     -24,    48,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,    51,    20,   -15,    53,    54,    55,
      56,    57,   -24,   -24,   -24,   -24,   -24
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     4,     5,     6,     7,     8,     9,    11,     0,
       0,     0,     0,     0,     0,     0,     3,     0,    12,    13,
      14,     0,     0,     0,     0,     0,    41,     0,    35,     0,
       0,    27,     0,    21,     0,     0,     0,     0,    19,     0,
      28,     0,    57,     0,     0,     0,    18,     0,    20,     0,
       0,     0,    15,    16,    17,    42,     0,    36,     0,    23,
      30,     0,    25,     0,     0,    29,     0,    43,    45,    44,
      46,    47,    48,    37,    38,    39,    40,    50,    51,    52,
      53,    54,    55,    56,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    31,    32,    33,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    28,    29,    30,    60,    70,    49,    67,    47,    82,
      65,    94,    32
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      36,    37,    38,    83,    84,    85,    98,    99,   100,    39,
      40,    69,    56,    31,    41,     2,    57,    31,     3,    26,
      31,     4,     5,     6,    19,     7,     8,     9,    61,    77,
      78,    79,    80,    81,    66,    20,    68,    71,    87,    88,
      89,    90,    91,    92,    93,    58,    27,    21,    22,    59,
      23,    86,    24,    25,    42,    31,    33,    34,    35,    43,
      44,    45,    46,    50,    48,    73,    51,     0,    52,    53,
       0,    62,    97,   101,    54,    55,    63,    64,    72,    74,
       0,     0,    95,    75,    76,    96,   102,   103,   104,   105,
     106
};

static const yytype_int8 yycheck[] =
{
      23,    24,    25,    21,    22,    23,    21,    22,    23,     4,
       5,    33,    33,    35,     9,     0,    37,    35,     3,    38,
      35,     6,     7,     8,    34,    10,    11,    12,    51,    26,
      27,    28,    29,    30,    57,    34,    59,    60,    14,    15,
      16,    17,    18,    19,    20,    33,    36,    34,    34,    37,
      34,    74,    34,    34,    24,    35,    35,    35,    35,    33,
      25,    25,    25,    34,    33,    37,    34,    -1,    35,    35,
      -1,    33,    95,    96,    35,    35,    33,    33,    33,    37,
      -1,    -1,    34,    37,    37,    34,    33,    33,    33,    33,
      33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    40,     0,     3,     6,     7,     8,    10,    11,    12,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    34,
      34,    34,    34,    34,    34,    34,    38,    36,    50,    51,
      52,    35,    61,    35,    35,    35,    61,    61,    61,     4,
       5,     9,    24,    33,    25,    25,    25,    57,    33,    55,
      34,    34,    35,    35,    35,    35,    33,    37,    33,    37,
      53,    61,    33,    33,    33,    59,    61,    56,    61,    33,
      54,    61,    33,    37,    37,    37,    37,    26,    27,    28,
      29,    30,    58,    21,    22,    23,    61,    14,    15,    16,
      17,    18,    19,    20,    60,    34,    34,    61,    21,    22,
      23,    61,    33,    33,    33,    33,    33
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    41,    41,    41,    41,    41,    41,
      41,    42,    42,    42,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    50,    51,    51,    52,    52,    53,    53,
      53,    54,    54,    54,    54,    55,    55,    56,    56,    56,
      56,    57,    57,    58,    58,    58,    58,    58,    59,    59,
      60,    60,    60,    60,    60,    60,    60,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     6,     6,     6,     5,     4,
       5,     4,     0,     5,     0,     5,     0,     2,     0,     3,
       2,     6,     6,     6,     6,     0,     3,     3,     3,     3,
       3,     0,     3,     1,     1,     1,     1,     1,     3,     6,
       1,     1,     1,     1,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* commands: commands command SEMICOLON  */
#line 71 "parser.y"
                               { YYACCEPT; }
#line 1206 "parser.tab.c"
    break;

  case 11: /* select: select_nodes  */
#line 85 "parser.y"
                     { tree.type = SELECT_REQ; }
#line 1212 "parser.tab.c"
    break;

  case 15: /* open_file: OPEN LEFT_BRACE QUOTE FILENAME QUOTE RIGHT_BRACE  */
#line 92 "parser.y"
                                                         {
		tree.type = OPEN_FILE_REQ;
		tree.file.filename = malloc(sizeof(char) * strlen((yyvsp[-2].string)));
		strcpy(tree.file.filename, (yyvsp[-2].string));
	}
#line 1222 "parser.tab.c"
    break;

  case 16: /* create_file: CREATE LEFT_BRACE QUOTE FILENAME QUOTE RIGHT_BRACE  */
#line 100 "parser.y"
                                                           {
		tree.type = CREATE_FILE_REQ;
		tree.file.filename = malloc(sizeof(char) * strlen((yyvsp[-2].string)));
		strcpy(tree.file.filename, (yyvsp[-2].string));
	}
#line 1232 "parser.tab.c"
    break;

  case 17: /* close_file: CLOSE LEFT_BRACE QUOTE FILENAME QUOTE RIGHT_BRACE  */
#line 108 "parser.y"
                                                          {
		tree.type = CLOSE_FILE_REQ;
		tree.file.filename = malloc(sizeof(char) * strlen((yyvsp[-2].string)));
        strcpy(tree.file.filename, (yyvsp[-2].string));
	}
#line 1242 "parser.tab.c"
    break;

  case 18: /* create_schema: CREATE_SCHEMA LEFT_BRACE argument attribute_pairs RIGHT_BRACE  */
#line 116 "parser.y"
                                                                      {
		tree.type = CREATE_SCHEMA_REQ;
		tree.create_schema.name = malloc(sizeof(char) * strlen((yyvsp[-2].string)));
		strcpy(tree.create_schema.name, (yyvsp[-2].string));
}
#line 1252 "parser.tab.c"
    break;

  case 19: /* delete_schema: DELETE_SCHEMA LEFT_BRACE argument RIGHT_BRACE  */
#line 124 "parser.y"
                                                      {
		tree.type = DELETE_SCHEMA_REQ;
		tree.create_schema.name = malloc(sizeof(char) * strlen((yyvsp[-1].string)));
		strcpy(tree.create_schema.name, (yyvsp[-1].string));
}
#line 1262 "parser.tab.c"
    break;

  case 20: /* add_vertex: ADD_VERTEX LEFT_BRACE argument attribute_value_pairs RIGHT_BRACE  */
#line 132 "parser.y"
                                                                         {
		tree.type = ADD_VERTEX_REQ;
		tree.add_vertex.name = malloc(sizeof(char) * strlen((yyvsp[-2].string)));
		strcpy(tree.add_vertex.name, (yyvsp[-2].string));
	}
#line 1272 "parser.tab.c"
    break;

  case 21: /* select_nodes: VERTEX LEFT_BRACE argument RIGHT_BRACE  */
#line 140 "parser.y"
                                               {
		tree.schema_name = malloc(sizeof(char) * strlen((yyvsp[-1].string)));
		strcpy(tree.schema_name, (yyvsp[-1].string));
	}
#line 1281 "parser.tab.c"
    break;

  case 23: /* select_condition: DOT HAS LEFT_BRACE select_statements RIGHT_BRACE  */
#line 147 "parser.y"
                                                     {
		if(!array_list_created) {
			tree.statements = create_array();
			array_list_created = true;
		}
		add_to_array(tree.statements, cur_statement);
		cur_statement = NULL;
	}
#line 1294 "parser.tab.c"
    break;

  case 25: /* join: DOT OUT LEFT_BRACE argument RIGHT_BRACE  */
#line 158 "parser.y"
                                            {
		if(!array_list_created) {
			tree.statements = create_array();
			array_list_created = true;
		}
		cur_statement = malloc(sizeof(struct statement));
		cur_statement->type = OUT_TYPE;
		cur_statement->attr_name = malloc(sizeof(char) * strlen((yyvsp[-1].string)));
		strcpy(cur_statement->attr_name, (yyvsp[-1].string));
		add_to_array(tree.statements, cur_statement);
		cur_statement = NULL;
	}
#line 1311 "parser.tab.c"
    break;

  case 27: /* delete_command: DOT DELETE  */
#line 173 "parser.y"
               {
		if(!array_list_created) {
			tree.statements = create_array();
			array_list_created = true;
		}
		cur_statement = malloc(sizeof(struct statement));
		cur_statement->type = DELETE_TYPE;
		add_to_array(tree.statements, cur_statement);
		cur_statement = NULL;
	}
#line 1326 "parser.tab.c"
    break;

  case 29: /* select_statements: select_statements select_statement COMMA  */
#line 186 "parser.y"
                                             { }
#line 1332 "parser.tab.c"
    break;

  case 30: /* select_statements: select_statements select_statement  */
#line 187 "parser.y"
                                       { }
#line 1338 "parser.tab.c"
    break;

  case 31: /* select_statement: argument COMMA cmp_type LEFT_BRACE INTEGER RIGHT_BRACE  */
#line 191 "parser.y"
                                                               {
		if(cur_statement == NULL) {
			cur_statement = malloc(sizeof(struct statement));
			cur_statement->type = SELECT_CONDITION_TYPE;
			cur_statement->conditions = create_array();
		}
		struct select_condition *cond = malloc(sizeof(struct select_condition));
		cond->attr_name = malloc(sizeof(char) * strlen((yyvsp[-5].string)));
		strcpy(cond->attr_name, (yyvsp[-5].string));
		cond->option = (yyvsp[-3].cmp_type);
		cond->attr_type = INTEGER_AT;
		cond->value.integer_value = (yyvsp[-1].integer);
		add_to_array(cur_statement->conditions, cond);
	}
#line 1357 "parser.tab.c"
    break;

  case 32: /* select_statement: argument COMMA cmp_type LEFT_BRACE DECIMAL RIGHT_BRACE  */
#line 205 "parser.y"
                                                           {
		if(cur_statement == NULL) {
			cur_statement = malloc(sizeof(struct statement));
			cur_statement->type = SELECT_CONDITION_TYPE;
			cur_statement->conditions = create_array();
		}
		struct select_condition *cond = malloc(sizeof(struct select_condition));
		cond->attr_name = malloc(sizeof(char) * strlen((yyvsp[-5].string)));
		strcpy(cond->attr_name, (yyvsp[-5].string));
		cond->option = (yyvsp[-3].cmp_type);
		cond->attr_type = FLOAT_AT;
		cond->value.float_value = (yyvsp[-1].decimal);
		add_to_array(cur_statement->conditions, cond);
	}
#line 1376 "parser.tab.c"
    break;

  case 33: /* select_statement: argument COMMA cmp_type LEFT_BRACE BOOLEAN RIGHT_BRACE  */
#line 219 "parser.y"
                                                           {
		if(cur_statement == NULL) {
			cur_statement = malloc(sizeof(struct statement));
			cur_statement->type = SELECT_CONDITION_TYPE;
			cur_statement->conditions = create_array();
		}
		struct select_condition *cond = malloc(sizeof(struct select_condition));
		cond->attr_name = malloc(sizeof(char) * strlen((yyvsp[-5].string)));
		strcpy(cond->attr_name, (yyvsp[-5].string));
		cond->option = (yyvsp[-3].cmp_type);
		cond->attr_type = BOOL_AT;
		cond->value.bool_value = (yyvsp[-1].boolean);
		add_to_array(cur_statement->conditions, cond);
}
#line 1395 "parser.tab.c"
    break;

  case 34: /* select_statement: argument COMMA cmp_type LEFT_BRACE argument RIGHT_BRACE  */
#line 233 "parser.y"
                                                             {
		if(cur_statement == NULL) {
			cur_statement = malloc(sizeof(struct statement));
			cur_statement->type = SELECT_CONDITION_TYPE;
			cur_statement->conditions = create_array();
		}
		struct select_condition *cond = malloc(sizeof(struct select_condition));
		cond->attr_name = malloc(sizeof(char) * strlen((yyvsp[-5].string)));
		strcpy(cond->attr_name, (yyvsp[-5].string));
		cond->option = (yyvsp[-3].cmp_type);
		cond->attr_type = STRING_AT;
		cond->value.string_value = (yyvsp[-1].string);
		add_to_array(cur_statement->conditions, cond);
	}
#line 1414 "parser.tab.c"
    break;

  case 36: /* attribute_value_pairs: attribute_value_pairs COMMA attribute_value_pair  */
#line 250 "parser.y"
                                                     { }
#line 1420 "parser.tab.c"
    break;

  case 37: /* attribute_value_pair: argument COMMA INTEGER  */
#line 254 "parser.y"
                               {
		if(!array_list_created) {
			tree.add_vertex.attribute_values = create_array();
			array_list_created = true;
		}
		struct attribute_value *attr_val = malloc(sizeof(struct attribute_value));
		*attr_val = (struct attribute_value) {.attr_name = malloc(sizeof(char) * strlen((yyvsp[-2].string))), .attr_type = INTEGER_AT, .value = (union value) {.integer_value = (yyvsp[0].integer)}};
		strcpy(attr_val->attr_name, (yyvsp[-2].string));
		add_to_array(tree.add_vertex.attribute_values, attr_val);
	}
#line 1435 "parser.tab.c"
    break;

  case 38: /* attribute_value_pair: argument COMMA DECIMAL  */
#line 264 "parser.y"
                          {
		if(!array_list_created) {
			tree.add_vertex.attribute_values = create_array();
			array_list_created = true;
		}
		struct attribute_value *attr_val = malloc(sizeof(struct attribute_value));
		*attr_val = (struct attribute_value) {.attr_name = malloc(sizeof(char) * strlen((yyvsp[-2].string))), .attr_type = FLOAT_AT, .value = (union value) {.float_value = (yyvsp[0].decimal)}}; 
		strcpy(attr_val->attr_name, (yyvsp[-2].string));
		add_to_array(tree.add_vertex.attribute_values, attr_val);
	}
#line 1450 "parser.tab.c"
    break;

  case 39: /* attribute_value_pair: argument COMMA BOOLEAN  */
#line 274 "parser.y"
                          {
		if(!array_list_created) {
			tree.add_vertex.attribute_values = create_array();
			array_list_created = true;
		}
		struct attribute_value *attr_val = malloc(sizeof(struct attribute_value));
		*attr_val = (struct attribute_value) {.attr_name = malloc(sizeof(char) * strlen((yyvsp[-2].string))), .attr_type = BOOL_AT, .value = (union value) {.bool_value = (yyvsp[0].boolean)}};
		strcpy(attr_val->attr_name, (yyvsp[-2].string));
		add_to_array(tree.add_vertex.attribute_values, attr_val);
	}
#line 1465 "parser.tab.c"
    break;

  case 40: /* attribute_value_pair: argument COMMA argument  */
#line 284 "parser.y"
                           {
		if(!array_list_created) {
			tree.add_vertex.attribute_values = create_array();
			array_list_created = true;
		}
		struct attribute_value *attr_val = malloc(sizeof(struct attribute_value));
		*attr_val = (struct attribute_value) {.attr_name = malloc(sizeof(char) * strlen((yyvsp[-2].string))), .attr_type = STRING_AT, .value = (union value) {.string_value = malloc(sizeof(char) * strlen((yyvsp[0].string)))}};
		strcpy(attr_val->value.string_value, (yyvsp[0].string));
		strcpy(attr_val->attr_name, (yyvsp[-2].string));
		add_to_array(tree.add_vertex.attribute_values, attr_val);
}
#line 1481 "parser.tab.c"
    break;

  case 42: /* attribute_pairs: attribute_pairs COMMA attribute_pair  */
#line 298 "parser.y"
                                         { }
#line 1487 "parser.tab.c"
    break;

  case 43: /* data_type: MY_INTEGER  */
#line 302 "parser.y"
                   { (yyval.data_type) = INTEGER_AT; }
#line 1493 "parser.tab.c"
    break;

  case 44: /* data_type: MY_STRING  */
#line 303 "parser.y"
            { (yyval.data_type) = STRING_AT; }
#line 1499 "parser.tab.c"
    break;

  case 45: /* data_type: MY_FLOAT  */
#line 304 "parser.y"
           { (yyval.data_type) = FLOAT_AT; }
#line 1505 "parser.tab.c"
    break;

  case 46: /* data_type: MY_BOOLEAN  */
#line 305 "parser.y"
             { (yyval.data_type) = BOOL_AT; }
#line 1511 "parser.tab.c"
    break;

  case 47: /* data_type: MY_REF  */
#line 306 "parser.y"
         { (yyval.data_type) = REF_AT; }
#line 1517 "parser.tab.c"
    break;

  case 48: /* attribute_pair: argument COMMA data_type  */
#line 310 "parser.y"
                                 {
		if (!array_list_created) {
		tree.create_schema.attributes = create_array();
		array_list_created = true;
		}
		struct attribute* attr_decl = malloc(sizeof(struct attribute));
		*attr_decl = (struct attribute) {.attr_name = malloc(sizeof(char) * strlen((yyvsp[-2].string))), .attr_type = (yyvsp[0].data_type),};
		strcpy(attr_decl->attr_name, (yyvsp[-2].string));
		add_to_array(tree.create_schema.attributes, attr_decl);
	}
#line 1532 "parser.tab.c"
    break;

  case 49: /* attribute_pair: argument COMMA MY_REF LEFT_BRACE argument RIGHT_BRACE  */
#line 320 "parser.y"
                                                          {
		if (!array_list_created) {
		tree.create_schema.attributes = create_array();
		printf("array created\n");
		array_list_created = true;
		}
		struct attribute* attr_decl = malloc(sizeof(struct attribute));
		*attr_decl = (struct attribute) {.attr_name = malloc(sizeof(char) * strlen((yyvsp[-5].string))), .attr_type = REF_AT, .schema_ref_name = malloc(sizeof(char) * strlen((yyvsp[-1].string)))};
		strcpy(attr_decl->attr_name, (yyvsp[-5].string));
		strcpy(attr_decl->schema_ref_name, (yyvsp[-1].string));
		add_to_array(tree.create_schema.attributes, attr_decl);
	}
#line 1549 "parser.tab.c"
    break;

  case 50: /* cmp_type: EQUALS  */
#line 335 "parser.y"
               { (yyval.cmp_type) = EQUALS_CMP; }
#line 1555 "parser.tab.c"
    break;

  case 51: /* cmp_type: GREATER  */
#line 336 "parser.y"
            { (yyval.cmp_type) = GREATER_CMP; }
#line 1561 "parser.tab.c"
    break;

  case 52: /* cmp_type: GREATER_EQUALS  */
#line 337 "parser.y"
                   { (yyval.cmp_type) = GREATER_EQUALS_CMP; }
#line 1567 "parser.tab.c"
    break;

  case 53: /* cmp_type: LESS  */
#line 338 "parser.y"
         { (yyval.cmp_type) = LESS_CMP; }
#line 1573 "parser.tab.c"
    break;

  case 54: /* cmp_type: LESS_EQUALS  */
#line 339 "parser.y"
                { (yyval.cmp_type) = LESS_EQUALS_CMP; }
#line 1579 "parser.tab.c"
    break;

  case 55: /* cmp_type: NOT_EQUALS  */
#line 340 "parser.y"
               { (yyval.cmp_type) = NOT_EQUALS_CMP; }
#line 1585 "parser.tab.c"
    break;

  case 56: /* cmp_type: CONTAINS  */
#line 341 "parser.y"
             { (yyval.cmp_type) = CONTAINS_CMP; }
#line 1591 "parser.tab.c"
    break;

  case 57: /* argument: QUOTE WORD QUOTE  */
#line 345 "parser.y"
                         { (yyval.string) = (yyvsp[-1].string); }
#line 1597 "parser.tab.c"
    break;


#line 1601 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 348 "parser.y"


void yyerror (char const *s) {
   fprintf (stderr, "%s undeclared", s);
}

int yywrap() {
	return 1;
}

struct ast_tree get_request_tree(){
	array_list_created = 0;
	struct ast_tree rtree;
	rtree = tree;

	//free_tree(&tree);
	tree.type = UNDEFINED;
	tree.statements = 0;

	return rtree;
}
