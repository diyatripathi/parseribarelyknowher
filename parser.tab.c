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
#line 1 "PIBKH_PA2.y"

#include <stdio.h>
#include "PIBKH_PA3.h"

int yylex(void);
void yyerror(const char *s);

#line 79 "parser.tab.c"

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
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_FUNCTION = 4,                   /* FUNCTION  */
  YYSYMBOL_VAR = 5,                        /* VAR  */
  YYSYMBOL_INTEGER = 6,                    /* INTEGER  */
  YYSYMBOL_STRING = 7,                     /* STRING  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_DO = 9,                         /* DO  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_THEN = 11,                      /* THEN  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_KW_BEGIN = 13,                  /* KW_BEGIN  */
  YYSYMBOL_KW_END = 14,                    /* KW_END  */
  YYSYMBOL_ID = 15,                        /* ID  */
  YYSYMBOL_STR = 16,                       /* STR  */
  YYSYMBOL_NUM = 17,                       /* NUM  */
  YYSYMBOL_PLUS = 18,                      /* PLUS  */
  YYSYMBOL_MINUS = 19,                     /* MINUS  */
  YYSYMBOL_STAR = 20,                      /* STAR  */
  YYSYMBOL_SLASH = 21,                     /* SLASH  */
  YYSYMBOL_LT = 22,                        /* LT  */
  YYSYMBOL_GT = 23,                        /* GT  */
  YYSYMBOL_LE = 24,                        /* LE  */
  YYSYMBOL_GE = 25,                        /* GE  */
  YYSYMBOL_EQ = 26,                        /* EQ  */
  YYSYMBOL_NEQ = 27,                       /* NEQ  */
  YYSYMBOL_ASSIGN = 28,                    /* ASSIGN  */
  YYSYMBOL_LPAREN = 29,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 30,                    /* RPAREN  */
  YYSYMBOL_COMMA = 31,                     /* COMMA  */
  YYSYMBOL_SEMI = 32,                      /* SEMI  */
  YYSYMBOL_DOT = 33,                       /* DOT  */
  YYSYMBOL_COLON = 34,                     /* COLON  */
  YYSYMBOL_LOWER_THAN_ELSE = 35,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_program = 37,                   /* program  */
  YYSYMBOL_declaration_list_opt = 38,      /* declaration_list_opt  */
  YYSYMBOL_declaration_list = 39,          /* declaration_list  */
  YYSYMBOL_variable_list = 40,             /* variable_list  */
  YYSYMBOL_type = 41,                      /* type  */
  YYSYMBOL_function_declaration_list_opt = 42, /* function_declaration_list_opt  */
  YYSYMBOL_function_declaration_list = 43, /* function_declaration_list  */
  YYSYMBOL_function_declaration = 44,      /* function_declaration  */
  YYSYMBOL_function_header = 45,           /* function_header  */
  YYSYMBOL_46_1 = 46,                      /* $@1  */
  YYSYMBOL_parameter_list = 47,            /* parameter_list  */
  YYSYMBOL_compound_statement = 48,        /* compound_statement  */
  YYSYMBOL_opt_semi = 49,                  /* opt_semi  */
  YYSYMBOL_statement_list = 50,            /* statement_list  */
  YYSYMBOL_statement = 51,                 /* statement  */
  YYSYMBOL_selection_statement = 52,       /* selection_statement  */
  YYSYMBOL_iteration_statement = 53,       /* iteration_statement  */
  YYSYMBOL_expression_list = 54,           /* expression_list  */
  YYSYMBOL_expression = 55,                /* expression  */
  YYSYMBOL_simple_expression = 56,         /* simple_expression  */
  YYSYMBOL_term = 57,                      /* term  */
  YYSYMBOL_factor = 58                     /* factor  */
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   105

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  116

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


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
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    44,    44,    48,    49,    53,    62,    74,    78,    85,
      87,    92,    93,    97,    98,   102,   110,   109,   135,   143,
     154,   158,   159,   163,   164,   168,   175,   179,   185,   186,
     187,   191,   192,   196,   200,   205,   213,   215,   221,   227,
     233,   239,   245,   254,   256,   262,   271,   273,   279,   288,
     292,   300,   306,   310,   318,   322
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
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "FUNCTION",
  "VAR", "INTEGER", "STRING", "WHILE", "DO", "IF", "THEN", "ELSE",
  "KW_BEGIN", "KW_END", "ID", "STR", "NUM", "PLUS", "MINUS", "STAR",
  "SLASH", "LT", "GT", "LE", "GE", "EQ", "NEQ", "ASSIGN", "LPAREN",
  "RPAREN", "COMMA", "SEMI", "DOT", "COLON", "LOWER_THAN_ELSE", "$accept",
  "program", "declaration_list_opt", "declaration_list", "variable_list",
  "type", "function_declaration_list_opt", "function_declaration_list",
  "function_declaration", "function_header", "$@1", "parameter_list",
  "compound_statement", "opt_semi", "statement_list", "statement",
  "selection_statement", "iteration_statement", "expression_list",
  "expression", "simple_expression", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-56)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,    -5,    22,    50,   -56,    48,    57,    79,    80,   -56,
     -13,    69,    73,    79,    55,    48,    57,    74,    26,   -56,
      16,    58,    56,   -56,    73,    30,   -56,   -56,   -56,    61,
      63,    21,    21,    19,   -56,    62,   -56,   -56,   -56,   -56,
     -56,   -56,    26,   -56,    57,    66,   -56,   -56,    21,    21,
      21,    81,    33,    47,   -56,    85,    21,    -2,    16,    83,
      67,    31,   -21,    21,   -56,   -56,    68,    16,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    16,   -56,
     -56,    40,   -56,   -56,   -56,   -56,    26,    70,    57,    46,
     -56,   -56,    47,    47,    60,    60,    60,    60,    60,    60,
     -56,   -56,    88,   -56,    21,   -56,    26,    32,   -56,    16,
     -56,    71,    26,   -56,   -56,   -56
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,    11,     4,     7,
       0,     0,     0,    12,     0,     3,     0,     0,     0,    16,
       0,     0,     0,    14,     0,     0,     8,     9,    10,     0,
       0,     0,     0,     0,    28,    21,    23,    29,    30,     2,
      13,    15,     0,     6,     0,    49,    51,    50,     0,     0,
       0,     0,    36,    43,    46,     0,     0,     0,    22,     0,
       0,     0,     0,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    25,
      26,     0,    34,    24,    20,     5,     0,     0,     0,     0,
      52,    33,    44,    45,    37,    38,    39,    40,    41,    42,
      47,    48,    31,    27,     0,    18,     0,     0,    53,     0,
      35,     0,     0,    32,    17,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,    86,   -56,   -14,   -37,   -56,   -56,    89,   -56,
     -56,   -56,    -4,   -56,   -56,   -55,   -56,   -56,    42,   -31,
     -29,    12,   -42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     7,     8,    10,    29,    12,    13,    14,    15,
      30,    62,    34,    59,    35,    36,    37,    38,    81,    82,
      52,    53,    54
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      51,    55,    25,    83,     1,    60,    64,    65,    21,    87,
       3,    88,    91,    45,    46,    47,    48,    49,    17,    66,
      41,    18,     4,   102,    31,    79,    32,    50,    80,    20,
      61,    33,    27,    28,   100,   101,    45,    46,    47,    48,
      49,    94,    95,    96,    97,    98,    99,    56,    57,   105,
      50,    68,    69,     6,   113,    70,    71,    72,    73,    74,
      75,    17,    17,    17,    42,    86,   112,    76,    77,   111,
     103,   104,     9,   110,   107,   115,   108,   104,    68,    69,
      92,    93,     5,    11,    19,    16,    20,    23,    40,    26,
      67,    39,    44,    43,    58,    63,    78,    84,    90,    85,
     109,    24,    22,   114,   106,    89
};

static const yytype_int8 yycheck[] =
{
      31,    32,    16,    58,     3,    42,    48,    49,    12,    30,
      15,    32,    67,    15,    16,    17,    18,    19,    31,    50,
      24,    34,     0,    78,     8,    56,    10,    29,    30,    13,
      44,    15,     6,     7,    76,    77,    15,    16,    17,    18,
      19,    70,    71,    72,    73,    74,    75,    28,    29,    86,
      29,    18,    19,     5,   109,    22,    23,    24,    25,    26,
      27,    31,    31,    31,    34,    34,    34,    20,    21,   106,
      30,    31,    15,   104,    88,   112,    30,    31,    18,    19,
      68,    69,    32,     4,    15,     5,    13,    32,    32,    15,
       9,    33,    29,    32,    32,    29,    11,    14,    30,    32,
      12,    15,    13,    32,    34,    63
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    37,    15,     0,    32,     5,    38,    39,    15,
      40,     4,    42,    43,    44,    45,     5,    31,    34,    15,
      13,    48,    44,    32,    38,    40,    15,     6,     7,    41,
      46,     8,    10,    15,    48,    50,    51,    52,    53,    33,
      32,    48,    34,    32,    29,    15,    16,    17,    18,    19,
      29,    55,    56,    57,    58,    55,    28,    29,    32,    49,
      41,    40,    47,    29,    58,    58,    55,     9,    18,    19,
      22,    23,    24,    25,    26,    27,    20,    21,    11,    55,
      30,    54,    55,    51,    14,    32,    34,    30,    32,    54,
      30,    51,    57,    57,    56,    56,    56,    56,    56,    56,
      58,    58,    51,    30,    31,    41,    34,    40,    30,    12,
      55,    41,    34,    51,    32,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    40,    40,    41,
      41,    42,    42,    43,    43,    44,    46,    45,    47,    47,
      48,    49,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    52,    52,    53,    54,    54,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    56,    57,    57,    57,    58,
      58,    58,    58,    58,    58,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     0,     1,     6,     5,     1,     3,     1,
       1,     0,     1,     3,     2,     3,     0,     9,     3,     5,
       4,     0,     1,     1,     3,     3,     3,     4,     1,     1,
       1,     4,     6,     4,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       1,     1,     3,     4,     2,     2
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
  case 5: /* declaration_list: declaration_list VAR variable_list COLON type SEMI  */
#line 54 "PIBKH_PA2.y"
    {
        NameList *nl = (yyvsp[-3].namelist);
        while (nl) {
            SymbolKind kind = SYM_VAR;
            symtab_insert(currentST, nl->name, (yyvsp[-1].type), kind, 4);
            nl = nl->next;
        }
    }
#line 1202 "parser.tab.c"
    break;

  case 6: /* declaration_list: VAR variable_list COLON type SEMI  */
#line 63 "PIBKH_PA2.y"
    {
        NameList *nl = (yyvsp[-3].namelist);
        while (nl) {
            SymbolKind kind = SYM_VAR;
            symtab_insert(currentST, nl->name, (yyvsp[-1].type), kind, 4);
            nl = nl->next;
        }
    }
#line 1215 "parser.tab.c"
    break;

  case 7: /* variable_list: ID  */
#line 75 "PIBKH_PA2.y"
      {
          (yyval.namelist) = make_namelist((yyvsp[0].sval));
      }
#line 1223 "parser.tab.c"
    break;

  case 8: /* variable_list: variable_list COMMA ID  */
#line 79 "PIBKH_PA2.y"
      {
          (yyval.namelist) = append_namelist((yyvsp[-2].namelist), (yyvsp[0].sval));
      }
#line 1231 "parser.tab.c"
    break;

  case 9: /* type: INTEGER  */
#line 86 "PIBKH_PA2.y"
      { (yyval.type) = TYPE_INT; }
#line 1237 "parser.tab.c"
    break;

  case 10: /* type: STRING  */
#line 88 "PIBKH_PA2.y"
      { (yyval.type) = TYPE_STRING; }
#line 1243 "parser.tab.c"
    break;

  case 15: /* function_declaration: function_header declaration_list_opt compound_statement  */
#line 103 "PIBKH_PA2.y"
    {
        if (currentST->parent) currentST = currentST->parent;
    }
#line 1251 "parser.tab.c"
    break;

  case 16: /* $@1: %empty  */
#line 110 "PIBKH_PA2.y"
      {
          /* Create the function's symbol table *before* parsing parameters */
          SymbolTable *fnST = symtab_create((yyvsp[0].sval), currentST);
          currentST = fnST;   /* parameter_list now inserts into fnST */
      }
#line 1261 "parser.tab.c"
    break;

  case 17: /* function_header: FUNCTION ID $@1 LPAREN parameter_list RPAREN COLON type SEMI  */
#line 116 "PIBKH_PA2.y"
      {
          /* currentST is the function's ST, whose parent is the global ST */
          SymbolTable *fnST   = currentST;
          SymbolTable *parent = fnST->parent;

          /* Insert function symbol in parent (global) table */
          Symbol *f = symtab_insert(parent,
                                    (yyvsp[-7].sval),   /* function name */
                                    (yyvsp[-1].type),   /* return type (type nonterminal) */
                                    SYM_FUNC,
                                    0);
          f->nested = fnST;   /* link function to its symbol table */

          /* Stay in fnST; function_declaration will pop back to parent */
      }
#line 1281 "parser.tab.c"
    break;

  case 18: /* parameter_list: variable_list COLON type  */
#line 136 "PIBKH_PA2.y"
    {
        NameList *nl = (yyvsp[-2].namelist);
        while (nl) {
            symtab_insert(currentST, nl->name, (yyvsp[0].type), SYM_PARAM, 4);
            nl = nl->next;
        }
    }
#line 1293 "parser.tab.c"
    break;

  case 19: /* parameter_list: parameter_list SEMI variable_list COLON type  */
#line 144 "PIBKH_PA2.y"
    {
        NameList *nl = (yyvsp[-2].namelist);
        while (nl) {
            symtab_insert(currentST, nl->name, (yyvsp[0].type), SYM_PARAM, 4);
            nl = nl->next;
        }
    }
#line 1305 "parser.tab.c"
    break;

  case 25: /* statement: ID ASSIGN expression  */
#line 169 "PIBKH_PA2.y"
      {
          Symbol *lhs = st_lookup(currentST, (yyvsp[-2].sval));
          if (lhs && (yyvsp[0].sym)) {
              emit("=", (yyvsp[0].sym)->name, "", lhs->name);
          }
      }
#line 1316 "parser.tab.c"
    break;

  case 26: /* statement: ID LPAREN RPAREN  */
#line 176 "PIBKH_PA2.y"
      {
          emit("call", (yyvsp[-2].sval), "0", "");
      }
#line 1324 "parser.tab.c"
    break;

  case 27: /* statement: ID LPAREN expression_list RPAREN  */
#line 180 "PIBKH_PA2.y"
      {
          char buf[32];
          sprintf(buf, "%d", (yyvsp[-1].ival));
          emit("call", (yyvsp[-3].sval), buf, "");
      }
#line 1334 "parser.tab.c"
    break;

  case 34: /* expression_list: expression  */
#line 201 "PIBKH_PA2.y"
      {
          if ((yyvsp[0].sym)) emit("param", (yyvsp[0].sym)->name, "", "");
          (yyval.ival) = 1;
      }
#line 1343 "parser.tab.c"
    break;

  case 35: /* expression_list: expression_list COMMA expression  */
#line 206 "PIBKH_PA2.y"
      {
          if ((yyvsp[0].sym)) emit("param", (yyvsp[0].sym)->name, "", "");
          (yyval.ival) = (yyvsp[-2].ival) + 1;
      }
#line 1352 "parser.tab.c"
    break;

  case 36: /* expression: simple_expression  */
#line 214 "PIBKH_PA2.y"
      { (yyval.sym) = (yyvsp[0].sym); }
#line 1358 "parser.tab.c"
    break;

  case 37: /* expression: simple_expression LT simple_expression  */
#line 216 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("<", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, t->name);
          (yyval.sym) = t;
      }
#line 1368 "parser.tab.c"
    break;

  case 38: /* expression: simple_expression GT simple_expression  */
#line 222 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit(">", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, t->name);
          (yyval.sym) = t;
      }
#line 1378 "parser.tab.c"
    break;

  case 39: /* expression: simple_expression LE simple_expression  */
#line 228 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("<=", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, t->name);
          (yyval.sym) = t;
      }
#line 1388 "parser.tab.c"
    break;

  case 40: /* expression: simple_expression GE simple_expression  */
#line 234 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit(">=", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, t->name);
          (yyval.sym) = t;
      }
#line 1398 "parser.tab.c"
    break;

  case 41: /* expression: simple_expression EQ simple_expression  */
#line 240 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("==", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, t->name);
          (yyval.sym) = t;
      }
#line 1408 "parser.tab.c"
    break;

  case 42: /* expression: simple_expression NEQ simple_expression  */
#line 246 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("<>", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, t->name);
          (yyval.sym) = t;
      }
#line 1418 "parser.tab.c"
    break;

  case 43: /* simple_expression: term  */
#line 255 "PIBKH_PA2.y"
      { (yyval.sym) = (yyvsp[0].sym); }
#line 1424 "parser.tab.c"
    break;

  case 44: /* simple_expression: simple_expression PLUS term  */
#line 257 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("+", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, t->name);
          (yyval.sym) = t;
      }
#line 1434 "parser.tab.c"
    break;

  case 45: /* simple_expression: simple_expression MINUS term  */
#line 263 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("-", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, t->name);
          (yyval.sym) = t;
      }
#line 1444 "parser.tab.c"
    break;

  case 46: /* term: factor  */
#line 272 "PIBKH_PA2.y"
      { (yyval.sym) = (yyvsp[0].sym); }
#line 1450 "parser.tab.c"
    break;

  case 47: /* term: term STAR factor  */
#line 274 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("*", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, t->name);
          (yyval.sym) = t;
      }
#line 1460 "parser.tab.c"
    break;

  case 48: /* term: term SLASH factor  */
#line 280 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("/", (yyvsp[-2].sym)->name, (yyvsp[0].sym)->name, t->name);
          (yyval.sym) = t;
      }
#line 1470 "parser.tab.c"
    break;

  case 49: /* factor: ID  */
#line 289 "PIBKH_PA2.y"
      {
          (yyval.sym) = st_lookup(currentST, (yyvsp[0].sval));
      }
#line 1478 "parser.tab.c"
    break;

  case 50: /* factor: NUM  */
#line 293 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          char buf[32];
          sprintf(buf, "%d", (yyvsp[0].ival));
          emit("=", buf, "", t->name);
          (yyval.sym) = t;
      }
#line 1490 "parser.tab.c"
    break;

  case 51: /* factor: STR  */
#line 301 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_STRING);
          emit("=", (yyvsp[0].sval), "", t->name);
          (yyval.sym) = t;
      }
#line 1500 "parser.tab.c"
    break;

  case 52: /* factor: LPAREN expression RPAREN  */
#line 307 "PIBKH_PA2.y"
      {
          (yyval.sym) = (yyvsp[-1].sym);
      }
#line 1508 "parser.tab.c"
    break;

  case 53: /* factor: ID LPAREN expression_list RPAREN  */
#line 311 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          char buf[32];
          sprintf(buf, "%d", (yyvsp[-1].ival));
          emit("call", (yyvsp[-3].sval), buf, t->name);
          (yyval.sym) = t;
      }
#line 1520 "parser.tab.c"
    break;

  case 54: /* factor: PLUS factor  */
#line 319 "PIBKH_PA2.y"
      {
          (yyval.sym) = (yyvsp[0].sym);
      }
#line 1528 "parser.tab.c"
    break;

  case 55: /* factor: MINUS factor  */
#line 323 "PIBKH_PA2.y"
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("uminus", (yyvsp[0].sym)->name, "", t->name);
          (yyval.sym) = t;
      }
#line 1538 "parser.tab.c"
    break;


#line 1542 "parser.tab.c"

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

#line 330 "PIBKH_PA2.y"


void yyerror(const char *s) { printf("%s\n", s); }
