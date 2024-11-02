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
#line 1 "syntax.y"

    #include <string>
    #include <unordered_map>
    #include "type.hpp"
    #include "visitSyntaxTree.hpp"
    using std::string;
    using std::unordered_map;
    #define YY_NO_UNPUT
    #include "lex.yy.c"
    void yyerror(const char *s);
    void lineinfor(void);
    Node* root_node;
    unordered_map<string,Type*> symbolTable;
    extern int isError;
    #define PARSER_error_OUTPUT stdout
    #include "yyerror_myself.hpp"

#line 89 "syntax.tab.c"

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

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LOWER_ERROR = 3,                /* LOWER_ERROR  */
  YYSYMBOL_ILLEGAL_TOKEN = 4,              /* ILLEGAL_TOKEN  */
  YYSYMBOL_LOWER_THAN_ELSE = 5,            /* LOWER_THAN_ELSE  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_TYPE = 7,                       /* TYPE  */
  YYSYMBOL_STRUCT = 8,                     /* STRUCT  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_FLOAT = 13,                     /* FLOAT  */
  YYSYMBOL_CHAR = 14,                      /* CHAR  */
  YYSYMBOL_ID = 15,                        /* ID  */
  YYSYMBOL_ASSIGN = 16,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 17,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 18,              /* MINUS_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 19,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 20,                /* DIV_ASSIGN  */
  YYSYMBOL_XOR = 21,                       /* XOR  */
  YYSYMBOL_BOR = 22,                       /* BOR  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_AND = 24,                       /* AND  */
  YYSYMBOL_BAND = 25,                      /* BAND  */
  YYSYMBOL_LT = 26,                        /* LT  */
  YYSYMBOL_LE = 27,                        /* LE  */
  YYSYMBOL_GT = 28,                        /* GT  */
  YYSYMBOL_GE = 29,                        /* GE  */
  YYSYMBOL_NE = 30,                        /* NE  */
  YYSYMBOL_EQ = 31,                        /* EQ  */
  YYSYMBOL_LOWER_MINUS = 32,               /* LOWER_MINUS  */
  YYSYMBOL_PLUS = 33,                      /* PLUS  */
  YYSYMBOL_MINUS = 34,                     /* MINUS  */
  YYSYMBOL_MUL = 35,                       /* MUL  */
  YYSYMBOL_DIV = 36,                       /* DIV  */
  YYSYMBOL_NOT = 37,                       /* NOT  */
  YYSYMBOL_LP = 38,                        /* LP  */
  YYSYMBOL_RP = 39,                        /* RP  */
  YYSYMBOL_LB = 40,                        /* LB  */
  YYSYMBOL_RB = 41,                        /* RB  */
  YYSYMBOL_DOT = 42,                       /* DOT  */
  YYSYMBOL_SEMI = 43,                      /* SEMI  */
  YYSYMBOL_COMMA = 44,                     /* COMMA  */
  YYSYMBOL_LC = 45,                        /* LC  */
  YYSYMBOL_RC = 46,                        /* RC  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_Program = 48,                   /* Program  */
  YYSYMBOL_ExtDefList = 49,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 50,                    /* ExtDef  */
  YYSYMBOL_Specifier_FunDec_Recv = 51,     /* Specifier_FunDec_Recv  */
  YYSYMBOL_ExtDecList = 52,                /* ExtDecList  */
  YYSYMBOL_Specifier = 53,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 54,           /* StructSpecifier  */
  YYSYMBOL_VarDec = 55,                    /* VarDec  */
  YYSYMBOL_FunDec = 56,                    /* FunDec  */
  YYSYMBOL_VarList = 57,                   /* VarList  */
  YYSYMBOL_ParamDec = 58,                  /* ParamDec  */
  YYSYMBOL_CompSt = 59,                    /* CompSt  */
  YYSYMBOL_StmtList = 60,                  /* StmtList  */
  YYSYMBOL_Stmt = 61,                      /* Stmt  */
  YYSYMBOL_DefList = 62,                   /* DefList  */
  YYSYMBOL_Def = 63,                       /* Def  */
  YYSYMBOL_DecList = 64,                   /* DecList  */
  YYSYMBOL_Dec = 65,                       /* Dec  */
  YYSYMBOL_Args = 66,                      /* Args  */
  YYSYMBOL_Exp = 67                        /* Exp  */
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
typedef yytype_uint8 yy_state_t;

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   731

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  168

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   301


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    57,    57,    63,    64,    66,    71,    76,    81,    82,
      84,    89,    90,    91,    94,    95,    97,    99,   100,   103,
     104,   106,   107,   109,   110,   111,   113,   114,   115,   117,
     120,   123,   124,   126,   127,   128,   129,   131,   133,   135,
     136,   137,   138,   139,   142,   143,   149,   154,   155,   162,
     163,   164,   166,   167,   173,   174,   177,   183,   189,   195,
     201,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   233,   234,   241,   242,   249,   250,   256,   261,   265,
     268,   270,   271
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
  "\"end of file\"", "error", "\"invalid token\"", "LOWER_ERROR",
  "ILLEGAL_TOKEN", "LOWER_THAN_ELSE", "ELSE", "TYPE", "STRUCT", "IF",
  "WHILE", "RETURN", "INT", "FLOAT", "CHAR", "ID", "ASSIGN", "PLUS_ASSIGN",
  "MINUS_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "XOR", "BOR", "OR", "AND",
  "BAND", "LT", "LE", "GT", "GE", "NE", "EQ", "LOWER_MINUS", "PLUS",
  "MINUS", "MUL", "DIV", "NOT", "LP", "RP", "LB", "RB", "DOT", "SEMI",
  "COMMA", "LC", "RC", "$accept", "Program", "ExtDefList", "ExtDef",
  "Specifier_FunDec_Recv", "ExtDecList", "Specifier", "StructSpecifier",
  "VarDec", "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt",
  "DefList", "Def", "DecList", "Dec", "Args", "Exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-46)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-45)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      88,   -46,   -13,    10,   -46,    88,   -32,    79,   -46,   -26,
     -46,   -46,    63,   -46,   -46,    -2,   -46,    26,   -12,   -46,
      78,    72,    72,   328,    63,    81,   -46,   -46,   -46,    86,
      72,    90,    19,    -5,    59,    -7,    98,   -46,    83,    55,
     491,   -46,   -46,   -46,    65,   491,   491,   491,   -46,    58,
     328,   109,   -46,   -46,   -46,    72,     0,   111,    82,   -46,
     -46,   -46,   -46,   491,   -46,    72,   104,   -46,   -46,   491,
     491,   491,   146,   485,   193,    50,   183,   -46,   -46,   -46,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,    91,   -46,    67,   -46,   -46,    88,   113,   -46,
     -46,   420,   -46,   -46,   392,   220,   257,   -46,   -46,   -46,
     -46,   114,   359,   -46,   -46,   448,   514,   540,   565,   589,
     612,   633,   653,   672,   319,   689,   193,   193,   193,   193,
     193,   193,   -18,   -18,    50,    50,   294,   -46,   -46,   -46,
     328,   328,   328,   328,   328,   -46,   -46,   491,   -46,   -46,
     -46,   -46,   106,   -46,   -46,   -46,   328,   -46
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    14,     0,     0,     2,     3,     0,     0,    15,    17,
       1,     4,     0,     7,     9,    19,     6,     0,    11,    10,
       0,     0,     0,    31,     0,     0,     8,     5,    19,     0,
       0,     0,     0,    52,     0,    49,     0,    92,     0,     0,
       0,    88,    89,    90,    87,     0,     0,     0,    34,     0,
      31,     0,    45,    25,    23,     0,     0,    28,     0,    12,
      13,    18,    16,     0,    48,     0,     0,    47,    46,     0,
       0,     0,     0,     0,    78,    79,     0,    30,    32,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,    29,    24,    22,     0,     0,    21,
      20,    53,    50,    51,     0,     0,     0,    41,    35,    83,
      82,     0,    55,    77,    76,    91,    56,    57,    58,    59,
      60,    75,    73,    62,    61,    74,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,     0,    86,    26,    27,
       0,     0,     0,     0,     0,    81,    80,     0,    85,    84,
      43,    42,    36,    39,    38,    54,     0,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -46,   -46,   141,   -46,   -46,   -14,     9,   -46,     8,   -46,
     -45,   -46,   142,   107,   360,     1,   -46,    46,   -46,    -3,
     -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,    17,    22,     8,    33,    19,
      56,    57,    48,    49,    50,    23,    24,    34,    35,   121,
      51
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,   105,     9,    28,    31,    74,    75,    76,    28,     7,
      10,    63,   108,    12,     7,    18,    59,    99,   100,    20,
      61,    32,   101,   111,   102,    52,    18,    26,    29,   114,
     115,   116,    30,   122,    55,    29,    25,    65,    18,   106,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   148,   104,    21,    62,    55,   -44,    36,    27,
       1,     2,   -44,   -44,   -44,   -44,   -44,   -44,   -44,    21,
      14,    66,    53,   109,    69,     1,     2,    28,     1,     2,
     101,    60,   102,    71,    15,     1,     2,   -44,    58,    67,
     -44,   -44,    64,    73,    77,   113,   147,    29,   -44,   -44,
      79,   112,   166,    80,   149,   155,    55,   122,     1,     2,
      54,    70,    16,   110,   -44,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    68,    97,    98,    99,   100,    11,   117,    13,   101,
      80,   102,   103,   156,   165,   107,     0,    78,     0,     0,
       0,     0,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,     0,    97,
      98,    99,   100,     0,   123,     0,   101,    80,   102,   118,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,     0,    97,    98,    99,   100,
       0,   151,   124,   101,    80,   102,    97,    98,    99,   100,
       0,     0,     0,   101,     0,   102,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,     0,    97,    98,    99,   100,     0,   153,   152,
     101,    80,   102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
      97,    98,    99,   100,     0,   158,   154,   101,    80,   102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,     0,    97,    98,    99,
     100,     0,    37,     0,   101,   159,   102,    38,    39,    40,
      41,    42,    43,    44,    90,    91,    92,    93,    94,    95,
      96,     0,    97,    98,    99,   100,     0,     0,     0,   101,
       0,   102,    45,    80,     0,    46,    47,     0,     0,     0,
       0,     0,     0,    12,     0,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,     0,    97,    98,    99,   100,    80,     0,     0,   101,
       0,   102,     0,   157,     0,     0,     0,     0,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    80,    97,    98,    99,   100,     0,
       0,   150,   101,     0,   102,     0,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,   -45,    97,    98,    99,   100,     0,     0,     0,
     101,     0,   102,     0,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
       0,    97,    98,    99,   100,     0,   119,     0,   101,    37,
     102,     0,     0,     0,     0,    37,     0,    41,    42,    43,
      44,     0,     0,    41,    42,    43,    44,     0,     0,     0,
     160,   161,   162,   163,   164,     0,     0,     0,     0,    45,
       0,     0,    46,    47,   120,    45,   167,     0,    46,    47,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,     0,    97,    98,    99,
     100,     0,     0,     0,   101,     0,   102,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,     0,    97,    98,    99,   100,     0,     0,     0,
     101,     0,   102,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,     0,    97,    98,
      99,   100,     0,     0,     0,   101,     0,   102,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,     0,    97,    98,    99,   100,     0,     0,     0,   101,
       0,   102,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,     0,    97,    98,    99,   100,     0,
       0,     0,   101,     0,   102,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,     0,    97,    98,    99,   100,
       0,     0,     0,   101,     0,   102,    88,    89,    90,    91,
      92,    93,    94,    95,    96,     0,    97,    98,    99,   100,
       0,     0,     0,   101,     0,   102,    89,    90,    91,    92,
      93,    94,    95,    96,     0,    97,    98,    99,   100,     0,
       0,     0,   101,     0,   102,    91,    92,    93,    94,    95,
      96,     0,    97,    98,    99,   100,     0,     0,     0,   101,
       0,   102
};

static const yytype_int16 yycheck[] =
{
      40,     1,    15,    15,    18,    45,    46,    47,    15,     0,
       0,    16,    57,    45,     5,     7,    30,    35,    36,    45,
       1,    20,    40,    63,    42,    24,    18,     1,    40,    69,
      70,    71,    44,    73,    25,    40,    38,    44,    30,    39,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   107,    55,     1,    46,    57,     4,    22,    43,
       7,     8,     9,    10,    11,    12,    13,    14,    15,     1,
       1,    35,     1,     1,     1,     7,     8,    15,     7,     8,
      40,     1,    42,    38,    15,     7,     8,    34,    12,     1,
      37,    38,    43,    38,    46,     1,    15,    40,    45,    46,
       1,    65,     6,     4,     1,     1,   107,   157,     7,     8,
      39,    38,    43,    41,    46,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    43,    33,    34,    35,    36,     5,     1,     6,    40,
       4,    42,    43,    39,   157,    44,    -1,    50,    -1,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    -1,     1,    -1,    40,     4,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,    34,    35,    36,
      -1,     1,    39,    40,     4,    42,    33,    34,    35,    36,
      -1,    -1,    -1,    40,    -1,    42,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    -1,     1,    39,
      40,     4,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    -1,     1,    39,    40,     4,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    34,    35,
      36,    -1,     4,    -1,    40,    41,    42,     9,    10,    11,
      12,    13,    14,    15,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      -1,    42,    34,     4,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,     4,    -1,    -1,    40,
      -1,    42,    -1,    44,    -1,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     4,    33,    34,    35,    36,    -1,
      -1,    39,    40,    -1,    42,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     4,    33,    34,    35,    36,    -1,    -1,    -1,
      40,    -1,    42,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    34,    35,    36,    -1,     1,    -1,    40,     4,
      42,    -1,    -1,    -1,    -1,     4,    -1,    12,    13,    14,
      15,    -1,    -1,    12,    13,    14,    15,    -1,    -1,    -1,
     150,   151,   152,   153,   154,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    38,    39,    34,   166,    -1,    37,    38,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    34,    35,
      36,    -1,    -1,    -1,    40,    -1,    42,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      40,    -1,    42,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    40,    -1,    42,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      -1,    42,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    40,    -1,    42,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    40,    -1,    42,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    40,    -1,    42,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    -1,
      -1,    -1,    40,    -1,    42,    26,    27,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      -1,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,    48,    49,    50,    51,    53,    54,    15,
       0,    49,    45,    59,     1,    15,    43,    52,    55,    56,
      45,     1,    53,    62,    63,    38,     1,    43,    15,    40,
      44,    52,    62,    55,    64,    65,    64,     4,     9,    10,
      11,    12,    13,    14,    15,    34,    37,    38,    59,    60,
      61,    67,    62,     1,    39,    53,    57,    58,    12,    52,
       1,     1,    46,    16,    43,    44,    64,     1,    43,     1,
      38,    38,    67,    38,    67,    67,    67,    46,    60,     1,
       4,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    33,    34,    35,
      36,    40,    42,    43,    55,     1,    39,    44,    57,     1,
      41,    67,    64,     1,    67,    67,    67,     1,    43,     1,
      39,    66,    67,     1,    39,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    15,    57,     1,
      39,     1,    39,     1,    39,     1,    39,    44,     1,    41,
      61,    61,    61,    61,    61,    66,     6,    61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    50,    50,    50,
      51,    52,    52,    52,    53,    53,    54,    54,    54,    55,
      55,    55,    56,    56,    56,    56,    57,    57,    57,    58,
      59,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    62,    62,    63,    63,    63,    64,
      64,    64,    65,    65,    66,    66,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     2,     3,     2,
       2,     1,     3,     3,     1,     1,     5,     2,     5,     1,
       4,     4,     4,     3,     4,     3,     3,     3,     1,     2,
       4,     0,     2,     2,     1,     3,     5,     7,     5,     5,
       2,     3,     5,     5,     0,     2,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       4,     4,     3,     3,     4,     4,     3,     1,     1,     1,
       1,     3,     1
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 57 "syntax.y"
                    {
    (yyval.Node_value)= new Node("Program",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[0].Node_value));
    root_node=(yyval.Node_value);
    root_node->print(0);
}
#line 1488 "syntax.tab.c"
    break;

  case 3: /* ExtDefList: %empty  */
#line 63 "syntax.y"
           {(yyval.Node_value)=new Node("ExtDefList",(yyloc).first_line,Node_TYPE::NOTHING);}
#line 1494 "syntax.tab.c"
    break;

  case 4: /* ExtDefList: ExtDef ExtDefList  */
#line 64 "syntax.y"
                        {(yyval.Node_value)=new Node("ExtDefList",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1500 "syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 66 "syntax.y"
                                   {
    (yyval.Node_value)=new Node("ExtDef",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
    extDefVisit_SES((yyval.Node_value));
    }
#line 1510 "syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 71 "syntax.y"
                     {
    (yyval.Node_value)=new Node("ExtDef",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[-1].Node_value),(yyvsp[0].Node_value));
    extDefVisit_SS((yyval.Node_value));
    }
#line 1520 "syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier_FunDec_Recv CompSt  */
#line 76 "syntax.y"
                                   {
    (yyval.Node_value)=new Node("ExtDef",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[-1].Node_value)->nodes[0],(yyvsp[-1].Node_value)->nodes[1],(yyvsp[0].Node_value));
    extDefVisit_SFC((yyval.Node_value));
    }
#line 1530 "syntax.tab.c"
    break;

  case 8: /* ExtDef: Specifier ExtDecList error  */
#line 81 "syntax.y"
                                  {yyerror_myself(YYERROR_TYPE::MISS_SEMI);}
#line 1536 "syntax.tab.c"
    break;

  case 9: /* ExtDef: Specifier error  */
#line 82 "syntax.y"
                      {yyerror_myself(YYERROR_TYPE::MISS_SEMI);}
#line 1542 "syntax.tab.c"
    break;

  case 10: /* Specifier_FunDec_Recv: Specifier FunDec  */
#line 84 "syntax.y"
                                      {
    (yyval.Node_value)=new Node("Specifier_FunDec_Recv",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[-1].Node_value),(yyvsp[0].Node_value));
    Specifier_FunDec_Recv_SF((yyval.Node_value));
}
#line 1552 "syntax.tab.c"
    break;

  case 11: /* ExtDecList: VarDec  */
#line 89 "syntax.y"
                   {(yyval.Node_value)=new Node("ExtDecList",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));}
#line 1558 "syntax.tab.c"
    break;

  case 12: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 90 "syntax.y"
                              {(yyval.Node_value)=new Node("ExtDecList",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1564 "syntax.tab.c"
    break;

  case 13: /* ExtDecList: VarDec ExtDecList error  */
#line 91 "syntax.y"
                              {yyerror_myself(YYERROR_TYPE::MISS_COMMA);}
#line 1570 "syntax.tab.c"
    break;

  case 14: /* Specifier: TYPE  */
#line 94 "syntax.y"
                {(yyval.Node_value)=new Node("Specifier",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));}
#line 1576 "syntax.tab.c"
    break;

  case 15: /* Specifier: StructSpecifier  */
#line 95 "syntax.y"
                      {(yyval.Node_value)=new Node("Specifier",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));}
#line 1582 "syntax.tab.c"
    break;

  case 16: /* StructSpecifier: STRUCT ID LC DefList RC  */
#line 97 "syntax.y"
                                         {
    (yyval.Node_value)=new Node("StructSpecifier",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-4].Node_value),(yyvsp[-3].Node_value),(yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1589 "syntax.tab.c"
    break;

  case 17: /* StructSpecifier: STRUCT ID  */
#line 99 "syntax.y"
                 {(yyval.Node_value)=new Node("StructSpecifier",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1595 "syntax.tab.c"
    break;

  case 18: /* StructSpecifier: STRUCT ID LC DefList error  */
#line 100 "syntax.y"
                                 { isError = 1;yyerror_myself(YYERROR_TYPE::LACK_OF_RC); }
#line 1601 "syntax.tab.c"
    break;

  case 19: /* VarDec: ID  */
#line 103 "syntax.y"
           {(yyval.Node_value)=new Node("VarDec",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));}
#line 1607 "syntax.tab.c"
    break;

  case 20: /* VarDec: VarDec LB INT RB  */
#line 104 "syntax.y"
                       {
    (yyval.Node_value)=new Node("VarDec",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-3].Node_value),(yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1614 "syntax.tab.c"
    break;

  case 21: /* VarDec: VarDec LB INT error  */
#line 106 "syntax.y"
                                            {yyerror_myself(YYERROR_TYPE::LACK_OF_RB);}
#line 1620 "syntax.tab.c"
    break;

  case 22: /* FunDec: ID LP VarList RP  */
#line 107 "syntax.y"
                         {
    (yyval.Node_value)=new Node("FunDec",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-3].Node_value),(yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));funDecVisit((yyval.Node_value));}
#line 1627 "syntax.tab.c"
    break;

  case 23: /* FunDec: ID LP RP  */
#line 109 "syntax.y"
                {(yyval.Node_value)=new Node("FunDec",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));funDecVisit((yyval.Node_value));}
#line 1633 "syntax.tab.c"
    break;

  case 24: /* FunDec: ID LP VarList error  */
#line 110 "syntax.y"
                          {yyerror_myself(YYERROR_TYPE::LACK_OF_RP);}
#line 1639 "syntax.tab.c"
    break;

  case 25: /* FunDec: ID LP error  */
#line 111 "syntax.y"
                  {yyerror_myself(YYERROR_TYPE::LACK_OF_RP);}
#line 1645 "syntax.tab.c"
    break;

  case 26: /* VarList: ParamDec COMMA VarList  */
#line 113 "syntax.y"
                                {(yyval.Node_value)=new Node("VarList",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1651 "syntax.tab.c"
    break;

  case 27: /* VarList: ParamDec VarList error  */
#line 114 "syntax.y"
                             {yyerror_myself(YYERROR_TYPE::MISS_COMMA);}
#line 1657 "syntax.tab.c"
    break;

  case 28: /* VarList: ParamDec  */
#line 115 "syntax.y"
               {(yyval.Node_value)=new Node("VarList",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[0].Node_value));}
#line 1663 "syntax.tab.c"
    break;

  case 29: /* ParamDec: Specifier VarDec  */
#line 117 "syntax.y"
                           {(yyval.Node_value)=new Node("ParamDec",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1669 "syntax.tab.c"
    break;

  case 30: /* CompSt: LC DefList StmtList RC  */
#line 120 "syntax.y"
                               {
    (yyval.Node_value)=new Node("CompSt",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-3].Node_value),(yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1676 "syntax.tab.c"
    break;

  case 31: /* StmtList: %empty  */
#line 123 "syntax.y"
           {(yyval.Node_value)=new Node("StmtList",(yyloc).first_line,Node_TYPE::NOTHING);}
#line 1682 "syntax.tab.c"
    break;

  case 32: /* StmtList: Stmt StmtList  */
#line 124 "syntax.y"
                     {(yyval.Node_value)=new Node("StmtList",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1688 "syntax.tab.c"
    break;

  case 33: /* Stmt: Exp SEMI  */
#line 126 "syntax.y"
               {(yyval.Node_value)=new Node("Stmt",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1694 "syntax.tab.c"
    break;

  case 34: /* Stmt: CompSt  */
#line 127 "syntax.y"
             {(yyval.Node_value)=new Node("Stmt",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));}
#line 1700 "syntax.tab.c"
    break;

  case 35: /* Stmt: RETURN Exp SEMI  */
#line 128 "syntax.y"
                      {(yyval.Node_value)=new Node("Stmt",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1706 "syntax.tab.c"
    break;

  case 36: /* Stmt: IF LP Exp RP Stmt  */
#line 129 "syntax.y"
                                              {
    (yyval.Node_value)=new Node("Stmt",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-4].Node_value),(yyvsp[-3].Node_value),(yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1713 "syntax.tab.c"
    break;

  case 37: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 131 "syntax.y"
                                  {
    (yyval.Node_value)=new Node("Stmt",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-6].Node_value),(yyvsp[-5].Node_value),(yyvsp[-4].Node_value),(yyvsp[-3].Node_value),(yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1720 "syntax.tab.c"
    break;

  case 38: /* Stmt: WHILE LP Exp RP Stmt  */
#line 133 "syntax.y"
                           {
    (yyval.Node_value)=new Node("Stmt",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-4].Node_value),(yyvsp[-3].Node_value),(yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1727 "syntax.tab.c"
    break;

  case 39: /* Stmt: WHILE LP Exp error Stmt  */
#line 135 "syntax.y"
                              {yyerror_myself(YYERROR_TYPE::LACK_OF_RP); }
#line 1733 "syntax.tab.c"
    break;

  case 40: /* Stmt: Exp error  */
#line 136 "syntax.y"
                {yyerror_myself(YYERROR_TYPE::MISS_SEMI);}
#line 1739 "syntax.tab.c"
    break;

  case 41: /* Stmt: RETURN Exp error  */
#line 137 "syntax.y"
                       {yyerror_myself(YYERROR_TYPE::MISS_SEMI);}
#line 1745 "syntax.tab.c"
    break;

  case 42: /* Stmt: IF LP Exp error Stmt  */
#line 138 "syntax.y"
                            {YYERROR;yyerror_myself(YYERROR_TYPE::LACK_OF_RP); }
#line 1751 "syntax.tab.c"
    break;

  case 43: /* Stmt: IF error Exp RP Stmt  */
#line 139 "syntax.y"
                           {yyerror_myself(YYERROR_TYPE::LACK_OF_LP); }
#line 1757 "syntax.tab.c"
    break;

  case 44: /* DefList: %empty  */
#line 142 "syntax.y"
         {(yyval.Node_value)=new Node("DefList",(yyloc).first_line,Node_TYPE::NOTHING);}
#line 1763 "syntax.tab.c"
    break;

  case 45: /* DefList: Def DefList  */
#line 143 "syntax.y"
                  {(yyval.Node_value)=new Node("DefList",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1769 "syntax.tab.c"
    break;

  case 46: /* Def: Specifier DecList SEMI  */
#line 149 "syntax.y"
                            {
    (yyval.Node_value)=new Node("Def",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
    defVisit((yyval.Node_value));
    }
#line 1779 "syntax.tab.c"
    break;

  case 47: /* Def: Specifier DecList error  */
#line 154 "syntax.y"
                              {yyerror_myself(YYERROR_TYPE::MISS_SEMI);}
#line 1785 "syntax.tab.c"
    break;

  case 48: /* Def: error DecList SEMI  */
#line 155 "syntax.y"
                         {
    yyerror_myself(YYERROR_TYPE::MISS_SPEC);
    printf("error\n");
    (yyval.Node_value)->print();
    (yyvsp[-1].Node_value)->print();
    }
#line 1796 "syntax.tab.c"
    break;

  case 49: /* DecList: Dec  */
#line 162 "syntax.y"
             {(yyval.Node_value)=new Node("DecList",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));}
#line 1802 "syntax.tab.c"
    break;

  case 50: /* DecList: Dec COMMA DecList  */
#line 163 "syntax.y"
                        {(yyval.Node_value)=new Node("DecList",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1808 "syntax.tab.c"
    break;

  case 51: /* DecList: Dec DecList error  */
#line 164 "syntax.y"
                         {yyerror_myself(YYERROR_TYPE::MISS_COMMA);}
#line 1814 "syntax.tab.c"
    break;

  case 52: /* Dec: VarDec  */
#line 166 "syntax.y"
            {(yyval.Node_value)=new Node("Dec",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[0].Node_value));}
#line 1820 "syntax.tab.c"
    break;

  case 53: /* Dec: VarDec ASSIGN Exp  */
#line 167 "syntax.y"
                        {
    (yyval.Node_value)=new Node("Dec",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
    // 声明时初始化
    }
#line 1829 "syntax.tab.c"
    break;

  case 54: /* Args: Exp COMMA Args  */
#line 173 "syntax.y"
                      {(yyval.Node_value)=new Node("Args",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));}
#line 1835 "syntax.tab.c"
    break;

  case 55: /* Args: Exp  */
#line 174 "syntax.y"
          {(yyval.Node_value)=new Node("Args",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));}
#line 1841 "syntax.tab.c"
    break;

  case 56: /* Exp: Exp ASSIGN Exp  */
#line 177 "syntax.y"
                    {
    (yyval.Node_value)=new Node("Exp",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
    checkRvalueInLeftSide((yyval.Node_value));
    checkTypeMatch((yyvsp[-2].Node_value),(yyvsp[0].Node_value),(yylsp[-1]).first_line);
    }
#line 1852 "syntax.tab.c"
    break;

  case 57: /* Exp: Exp PLUS_ASSIGN Exp  */
#line 183 "syntax.y"
                          {
    (yyval.Node_value)=new Node("Exp",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
    checkRvalueInLeftSide((yyval.Node_value));
    checkTypeMatch((yyvsp[-2].Node_value),(yyvsp[0].Node_value),(yylsp[-1]).first_line);
    }
#line 1863 "syntax.tab.c"
    break;

  case 58: /* Exp: Exp MINUS_ASSIGN Exp  */
#line 189 "syntax.y"
                           {
    (yyval.Node_value)=new Node("Exp",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
    checkRvalueInLeftSide((yyval.Node_value));
    checkTypeMatch((yyvsp[-2].Node_value),(yyvsp[0].Node_value),(yylsp[-1]).first_line);
    }
#line 1874 "syntax.tab.c"
    break;

  case 59: /* Exp: Exp MUL_ASSIGN Exp  */
#line 195 "syntax.y"
                         {
    (yyval.Node_value)=new Node("Exp",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
    checkRvalueInLeftSide((yyval.Node_value));
    checkTypeMatch((yyvsp[-2].Node_value),(yyvsp[0].Node_value),(yylsp[-1]).first_line);
    }
#line 1885 "syntax.tab.c"
    break;

  case 60: /* Exp: Exp DIV_ASSIGN Exp  */
#line 201 "syntax.y"
                         {
    (yyval.Node_value)=new Node("Exp",(yyloc).first_line);
    (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
    checkRvalueInLeftSide((yyval.Node_value));
    checkTypeMatch((yyvsp[-2].Node_value),(yyvsp[0].Node_value),(yylsp[-1]).first_line);
    }
#line 1896 "syntax.tab.c"
    break;

  case 61: /* Exp: Exp AND Exp  */
#line 207 "syntax.y"
                  {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getBoolOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1902 "syntax.tab.c"
    break;

  case 62: /* Exp: Exp OR Exp  */
#line 208 "syntax.y"
                 {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getBoolOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1908 "syntax.tab.c"
    break;

  case 63: /* Exp: Exp LT Exp  */
#line 209 "syntax.y"
                 {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1914 "syntax.tab.c"
    break;

  case 64: /* Exp: Exp LE Exp  */
#line 210 "syntax.y"
                 {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1920 "syntax.tab.c"
    break;

  case 65: /* Exp: Exp GT Exp  */
#line 211 "syntax.y"
                 {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1926 "syntax.tab.c"
    break;

  case 66: /* Exp: Exp GE Exp  */
#line 212 "syntax.y"
                 {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1932 "syntax.tab.c"
    break;

  case 67: /* Exp: Exp NE Exp  */
#line 213 "syntax.y"
                 {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1938 "syntax.tab.c"
    break;

  case 68: /* Exp: Exp EQ Exp  */
#line 214 "syntax.y"
                 {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1944 "syntax.tab.c"
    break;

  case 69: /* Exp: Exp PLUS Exp  */
#line 215 "syntax.y"
                   {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1950 "syntax.tab.c"
    break;

  case 70: /* Exp: Exp MINUS Exp  */
#line 216 "syntax.y"
                    {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1956 "syntax.tab.c"
    break;

  case 71: /* Exp: Exp MUL Exp  */
#line 217 "syntax.y"
                  {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1962 "syntax.tab.c"
    break;

  case 72: /* Exp: Exp DIV Exp  */
#line 218 "syntax.y"
                  {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1968 "syntax.tab.c"
    break;

  case 73: /* Exp: Exp BOR Exp  */
#line 219 "syntax.y"
                  {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1974 "syntax.tab.c"
    break;

  case 74: /* Exp: Exp BAND Exp  */
#line 220 "syntax.y"
                   {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1980 "syntax.tab.c"
    break;

  case 75: /* Exp: Exp XOR Exp  */
#line 221 "syntax.y"
                  {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));getAlrthOperatorType((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));}
#line 1986 "syntax.tab.c"
    break;

  case 76: /* Exp: LP Exp RP  */
#line 222 "syntax.y"
                {(yyval.Node_value)=new Node("Exp",(yyloc).first_line); (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));(yyval.Node_value)->type=(yyvsp[-1].Node_value)->type;}
#line 1992 "syntax.tab.c"
    break;

  case 77: /* Exp: LP Exp error  */
#line 223 "syntax.y"
                   {yyerror_myself(YYERROR_TYPE::LACK_OF_RP);}
#line 1998 "syntax.tab.c"
    break;

  case 78: /* Exp: MINUS Exp  */
#line 224 "syntax.y"
                                  {(yyval.Node_value)=new Node("Exp",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[-1].Node_value),(yyvsp[0].Node_value));(yyval.Node_value)->type=(yyvsp[0].Node_value)->type;checkAlrthOperatorType((yyvsp[0].Node_value));}
#line 2004 "syntax.tab.c"
    break;

  case 79: /* Exp: NOT Exp  */
#line 225 "syntax.y"
              {(yyval.Node_value)=new Node("Exp",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[-1].Node_value),(yyvsp[0].Node_value));(yyval.Node_value)->type=(yyvsp[0].Node_value)->type;}
#line 2010 "syntax.tab.c"
    break;

  case 80: /* Exp: ID LP Args RP  */
#line 226 "syntax.y"
                    {
      checkInvokeExist((yyvsp[-3].Node_value),(yylsp[-3]).first_line);
      checkFunctionParams((yyvsp[-3].Node_value),(yyvsp[-1].Node_value),(yylsp[-1]).first_line);
      (yyval.Node_value)=new Node("Exp",(yyloc).first_line);
      (yyval.Node_value)->push_back((yyvsp[-3].Node_value),(yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
      getReturnTypeOfFunction((yyval.Node_value),(yyvsp[-3].Node_value));
      }
#line 2022 "syntax.tab.c"
    break;

  case 81: /* Exp: ID LP Args error  */
#line 233 "syntax.y"
                       {yyerror_myself(YYERROR_TYPE::LACK_OF_RP);}
#line 2028 "syntax.tab.c"
    break;

  case 82: /* Exp: ID LP RP  */
#line 234 "syntax.y"
               {
      checkInvokeExist((yyvsp[-2].Node_value),(yylsp[-2]).first_line);
      checkFunctionParams((yyvsp[-2].Node_value),nullptr,(yylsp[0]).first_line);
      (yyval.Node_value)=new Node("Exp",(yyloc).first_line);
      (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
      getReturnTypeOfFunction((yyval.Node_value),(yyvsp[-2].Node_value));
    }
#line 2040 "syntax.tab.c"
    break;

  case 83: /* Exp: ID LP error  */
#line 241 "syntax.y"
                  {yyerror_myself(YYERROR_TYPE::LACK_OF_RP);}
#line 2046 "syntax.tab.c"
    break;

  case 84: /* Exp: Exp LB Exp RB  */
#line 242 "syntax.y"
                   {
        (yyval.Node_value)=new Node("Exp",(yyloc).first_line);
        (yyval.Node_value)->push_back((yyvsp[-3].Node_value),(yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
        // LB is [
        checkArrayExists((yyvsp[-3].Node_value));
        getArrayType((yyval.Node_value),(yyvsp[-3].Node_value),(yyvsp[-1].Node_value));
    }
#line 2058 "syntax.tab.c"
    break;

  case 85: /* Exp: Exp LB Exp error  */
#line 249 "syntax.y"
                       {yyerror_myself(YYERROR_TYPE::LACK_OF_RB);}
#line 2064 "syntax.tab.c"
    break;

  case 86: /* Exp: Exp DOT ID  */
#line 250 "syntax.y"
                 {
        (yyval.Node_value)=new Node("Exp",(yyloc).first_line);
        (yyval.Node_value)->push_back((yyvsp[-2].Node_value),(yyvsp[-1].Node_value),(yyvsp[0].Node_value));
        checkNoSuchMember((yyval.Node_value));
        searchAndPutTypeOfDot((yyval.Node_value),(yyvsp[-2].Node_value),(yyvsp[0].Node_value));
    }
#line 2075 "syntax.tab.c"
    break;

  case 87: /* Exp: ID  */
#line 256 "syntax.y"
         {
    (yyval.Node_value)=new Node("Exp",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));
    checkIdExists((yyvsp[0].Node_value),(yylsp[0]).first_line);
    idToExp((yyval.Node_value),(yyvsp[0].Node_value));
    }
#line 2085 "syntax.tab.c"
    break;

  case 88: /* Exp: INT  */
#line 261 "syntax.y"
          {
    (yyval.Node_value)=new Node("Exp",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));
    (yyval.Node_value)->type = Type::getPrimitiveINT();
    }
#line 2094 "syntax.tab.c"
    break;

  case 89: /* Exp: FLOAT  */
#line 265 "syntax.y"
            {(yyval.Node_value)=new Node("Exp",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));
        (yyval.Node_value)->type = Type::getPrimitiveFLOAT();
        }
#line 2102 "syntax.tab.c"
    break;

  case 90: /* Exp: CHAR  */
#line 268 "syntax.y"
           {(yyval.Node_value)=new Node("Exp",(yyloc).first_line);(yyval.Node_value)->push_back((yyvsp[0].Node_value));
            (yyval.Node_value)->type = Type::getPrimitiveCHAR();}
#line 2109 "syntax.tab.c"
    break;

  case 91: /* Exp: Exp ILLEGAL_TOKEN Exp  */
#line 270 "syntax.y"
                            {}
#line 2115 "syntax.tab.c"
    break;

  case 92: /* Exp: ILLEGAL_TOKEN  */
#line 271 "syntax.y"
                    {}
#line 2121 "syntax.tab.c"
    break;


#line 2125 "syntax.tab.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 273 "syntax.y"

void yyerror(const char *s){
    isError=1;
    if(s[0]  == '0'){}
    fprintf(PARSER_error_OUTPUT,"Error type B at Line %d: ",yylloc.first_line-1);
    //fprintf(PARSER_error_OUTPUT, "syntax Error: %s\n", s);
    //lineinfor();
}

void lineinfor(void){
    fprintf(PARSER_error_OUTPUT, "begin at:(%d,%d)\n",yylloc.first_line,yylloc.first_column);
    fprintf(PARSER_error_OUTPUT, "end at:(%d,%d)\n",yylloc.last_line,yylloc.last_column);
}
