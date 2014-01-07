/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 4 "parser.ypp"

	#include "file/lexerDefs.h"
	#include "file/parserDefs.h"
	#include "file/parser.h"
	#include "file/write.h" // to_string(Type);

	#include "File.h"
	#include "DistributedType.h"
	#include "NumericRange.h"
	#include "NumericType.h"
	#include "ArrayType.h"
	#include "Struct.h"
	#include "Class.h"
	#include "Field.h"
	#include "Method.h"
	#include "Parameter.h"
	#include "MolecularField.h"

	#include <unistd.h>
	#include <stdint.h> // Fixed width integer limits
	#include <math.h>   // Float INFINITY
	#include <stack>    // std::stack

	#define yyparse run_parser
	#define yylex run_lexer
	#define yyerror parser_error
	#define yywarning parser_warning
	#define yylval dcyylval
	#define yychar dcyychar
	#define yydebug dcyydebug
	#define yynerrs dcyynerrs

	// Because our token type contains objects of type string, which
	// require correct copy construction (and not simply memcpying), we
	// cannot use bison's built-in auto-stack-grow feature.  As an easy
	// solution, we ensure here that we have enough yacc stack to start
	// with, and that it doesn't ever try to grow.
	#define YYINITDEPTH 1000
	#define YYMAXDEPTH 1000

	using namespace std;
	namespace dclass   // open namespace dclass
	{
	

	// Parser output
	static File* parsed_file = (File*)NULL;
	static string* parsed_value = (string*)NULL;

	// Parser state
	static Class* current_class = (Class*)NULL;
	static Struct* current_struct = (Struct*)NULL;

	// Stack of distributed types for parsing values
	struct TypeAndDepth
	{
		int depth;
		const DistributedType* type;
		TypeAndDepth(const DistributedType* t, int d) : depth(d), type(t) {}
	};
	static stack<TypeAndDepth> type_stack;
	static int current_depth;

	/* Helper functions */
	static bool check_depth();
	static bool check_depth(int depth);
	static void depth_error(string what);
	static void depth_error(int depth, string what);
	static string number_value(Type type, double &number);
	static string number_value(Type type, int64_t &number);
	static string number_value(Type type, uint64_t &number);

////////////////////////////////////////////////////////////////////
// Defining the interface to the parser.
////////////////////////////////////////////////////////////////////

	void init_file_parser(istream& in, const string& filename, File& file)
	{
		parsed_file = &file;
		init_file_lexer(in, filename);
	}

	void init_value_parser(istream& in, const string& source,
	                       const DistributedType* type, string& output)
	{
		parsed_value = &output;
		current_depth = 0;
		type_stack.push(TypeAndDepth(type, 0));
		init_value_lexer(in, source);
	}

	void cleanup_parser()
	{
		current_depth = 0;
		type_stack = stack<TypeAndDepth>();
		parsed_file = (File*)NULL;
		parsed_value = (string*)NULL;
	}

	int parser_error_count()
	{
		return lexer_error_count();
	}
	int parser_warning_count()
	{
		return lexer_warning_count();
	}

	void parser_error(const string &msg)
	{
		lexer_error(msg);
	}
	void parser_warning(const string &msg)
	{
		parser_error(msg);
	}

/* Line 371 of yacc.c  */
#line 186 "parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     UNSIGNED_INTEGER = 258,
     SIGNED_INTEGER = 259,
     REAL = 260,
     STRING = 261,
     HEX_STRING = 262,
     IDENTIFIER = 263,
     CHAR = 264,
     START_DC_FILE = 265,
     START_DC_VALUE = 266,
     KW_DCLASS = 267,
     KW_STRUCT = 268,
     KW_FROM = 269,
     KW_IMPORT = 270,
     KW_TYPEDEF = 271,
     KW_KEYWORD = 272,
     KW_INT8 = 273,
     KW_INT16 = 274,
     KW_INT32 = 275,
     KW_INT64 = 276,
     KW_UINT8 = 277,
     KW_UINT16 = 278,
     KW_UINT32 = 279,
     KW_UINT64 = 280,
     KW_FLOAT32 = 281,
     KW_FLOAT64 = 282,
     KW_STRING = 283,
     KW_BLOB = 284,
     KW_CHAR = 285
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 281 "parser.cpp"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
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
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   235

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  165
/* YYNRULES -- Number of states.  */
#define YYNSTATES  246

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    44,     2,     2,
      42,    43,    33,     2,    34,    45,    32,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,    31,
       2,    39,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    11,    14,    17,    20,    23,
      26,    29,    31,    33,    35,    38,    43,    45,    49,    51,
      53,    55,    59,    61,    65,    68,    71,    73,    76,    78,
      81,    82,    90,    92,    95,    97,   101,   103,   105,   108,
     112,   115,   117,   118,   125,   127,   130,   134,   136,   138,
     140,   142,   144,   146,   148,   149,   154,   156,   161,   162,
     167,   168,   173,   174,   180,   183,   185,   187,   189,   191,
     193,   198,   203,   208,   212,   216,   218,   220,   225,   227,
     229,   231,   233,   235,   240,   244,   248,   252,   256,   260,
     263,   266,   269,   273,   275,   277,   279,   281,   282,   287,
     290,   295,   296,   301,   302,   307,   309,   311,   315,   318,
     320,   322,   326,   329,   331,   333,   335,   337,   339,   341,
     343,   345,   347,   349,   351,   353,   355,   357,   359,   361,
     362,   367,   369,   373,   374,   379,   381,   383,   387,   391,
     394,   395,   400,   402,   404,   408,   412,   416,   420,   424,
     428,   430,   432,   434,   436,   438,   440,   442,   444,   446,
     448,   450,   452,   454,   456,   459
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    10,    48,    -1,    11,    49,    -1,   122,
      -1,    48,    31,    -1,    48,    60,    -1,    48,    67,    -1,
      48,    50,    -1,    48,    55,    -1,    48,    58,    -1,   122,
      -1,   108,    -1,   109,    -1,    15,    51,    -1,    14,    51,
      15,    52,    -1,    54,    -1,    51,    32,    54,    -1,    53,
      -1,    33,    -1,    54,    -1,    53,    34,    54,    -1,     8,
      -1,    54,    35,     8,    -1,    16,    56,    -1,    81,     8,
      -1,     8,    -1,    17,    59,    -1,   122,    -1,    59,     8,
      -1,    -1,    12,     8,    61,    62,    36,    65,    37,    -1,
     122,    -1,    38,    63,    -1,    64,    -1,    63,    34,    64,
      -1,     8,    -1,   122,    -1,    65,    31,    -1,    65,    66,
      31,    -1,    71,   121,    -1,    84,    -1,    -1,    13,     8,
      68,    36,    69,    37,    -1,   122,    -1,    69,    31,    -1,
      69,    70,    31,    -1,    71,    -1,    72,    -1,    74,    -1,
      75,    -1,    76,    -1,    80,    -1,    81,    -1,    -1,    81,
      39,    73,   108,    -1,    56,    -1,    74,    40,   102,    41,
      -1,    -1,    74,    39,    77,   108,    -1,    -1,    75,    39,
      78,   108,    -1,    -1,    80,    39,   109,    79,   108,    -1,
       8,    92,    -1,    82,    -1,    83,    -1,    57,    -1,    87,
      -1,    86,    -1,    87,    40,   102,    41,    -1,    57,    40,
     102,    41,    -1,    86,    40,   102,    41,    -1,     8,    38,
      85,    -1,    84,    34,    85,    -1,     8,    -1,   119,    -1,
     119,    42,   102,    43,    -1,    88,    -1,    89,    -1,    90,
      -1,    91,    -1,   120,    -1,    88,    42,   101,    43,    -1,
      88,    44,   106,    -1,    89,    44,   106,    -1,    88,    35,
     104,    -1,    89,    35,   104,    -1,    90,    35,   104,    -1,
      42,    43,    -1,    93,    43,    -1,    42,    94,    -1,    93,
      34,    94,    -1,    96,    -1,    97,    -1,    98,    -1,    81,
      -1,    -1,    81,    39,    95,   108,    -1,    82,     8,    -1,
      96,    40,   102,    41,    -1,    -1,    96,    39,    99,   108,
      -1,    -1,    97,    39,   100,   108,    -1,   122,    -1,   107,
      -1,   107,    45,   107,    -1,   107,   106,    -1,   122,    -1,
     103,    -1,   103,    45,   103,    -1,   103,   105,    -1,     9,
      -1,   104,    -1,     3,    -1,     4,    -1,     3,    -1,     4,
      -1,     5,    -1,     9,    -1,   106,    -1,     4,    -1,     3,
      -1,     5,    -1,     6,    -1,     7,    -1,   115,    -1,   112,
      -1,    -1,    42,   110,   111,    43,    -1,   108,    -1,   111,
      34,   108,    -1,    -1,    36,   113,   114,    37,    -1,   108,
      -1,   109,    -1,   114,    34,   108,    -1,   114,    34,   109,
      -1,    40,    41,    -1,    -1,    40,   116,   117,    41,    -1,
     108,    -1,   118,    -1,   117,    34,   108,    -1,   117,    34,
     118,    -1,     4,    33,   104,    -1,     3,    33,   104,    -1,
       5,    33,   104,    -1,     7,    33,   104,    -1,    28,    -1,
      29,    -1,    30,    -1,    18,    -1,    19,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      26,    -1,    27,    -1,   122,    -1,   121,     8,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   224,   224,   225,   230,   231,   232,   233,   234,   235,
     236,   240,   246,   252,   261,   266,   275,   276,   283,   284,
     291,   295,   303,   304,   311,   353,   363,   378,   382,   383,
     391,   390,   430,   431,   435,   442,   452,   483,   484,   485,
     523,   546,   554,   553,   593,   594,   595,   629,   630,   634,
     635,   636,   637,   641,   646,   645,   663,   670,   679,   678,
     691,   690,   703,   702,   717,   724,   725,   729,   747,   751,
     755,   759,   763,   770,   774,   799,   821,   832,   846,   847,
     848,   849,   853,   857,   869,   878,   890,   897,   904,   914,
     918,   925,   935,   948,   949,   950,   951,   956,   955,   971,
     978,   987,   986,   999,   998,  1013,  1014,  1015,  1016,  1020,
    1021,  1022,  1023,  1027,  1039,  1043,  1055,  1071,  1072,  1073,
    1077,  1089,  1093,  1102,  1111,  1120,  1150,  1180,  1181,  1201,
    1200,  1237,  1238,  1246,  1245,  1282,  1283,  1284,  1288,  1295,
    1301,  1300,  1330,  1331,  1332,  1333,  1337,  1358,  1379,  1400,
    1425,  1426,  1430,  1431,  1432,  1433,  1434,  1435,  1436,  1437,
    1438,  1439,  1440,  1444,  1448,  1461
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "UNSIGNED_INTEGER", "SIGNED_INTEGER",
  "REAL", "STRING", "HEX_STRING", "IDENTIFIER", "CHAR", "START_DC_FILE",
  "START_DC_VALUE", "KW_DCLASS", "KW_STRUCT", "KW_FROM", "KW_IMPORT",
  "KW_TYPEDEF", "KW_KEYWORD", "KW_INT8", "KW_INT16", "KW_INT32",
  "KW_INT64", "KW_UINT8", "KW_UINT16", "KW_UINT32", "KW_UINT64",
  "KW_FLOAT32", "KW_FLOAT64", "KW_STRING", "KW_BLOB", "KW_CHAR", "';'",
  "'.'", "'*'", "','", "'/'", "'{'", "'}'", "':'", "'='", "'['", "']'",
  "'('", "')'", "'%'", "'-'", "$accept", "grammar", "file", "value",
  "import", "import_module", "import_symbols", "import_symbol_list",
  "import_alternatives", "typedef", "nonmethod_type_with_name",
  "defined_type", "keyword_decl", "keyword_decl_list", "dclass", "$@1",
  "class_inheritance", "class_parents", "defined_class", "class_fields",
  "class_field", "dstruct", "$@2", "struct_fields", "struct_field",
  "named_field", "unnamed_field", "$@3", "field_with_name",
  "field_with_name_as_array", "field_with_name_and_default", "$@4", "$@5",
  "$@6", "method_as_field", "nonmethod_type", "nonmethod_type_no_array",
  "type_with_array", "molecular", "defined_field", "builtin_array_type",
  "numeric_type", "numeric_token_only", "numeric_with_range",
  "numeric_with_modulus", "numeric_with_divisor", "method", "method_body",
  "parameter", "$@7", "param_with_name", "param_with_name_as_array",
  "param_with_name_and_default", "$@8", "$@9", "numeric_range",
  "array_range", "char_or_uint", "small_unsigned_integer",
  "small_negative_integer", "number", "char_or_number", "type_value",
  "method_value", "$@10", "parameter_values", "struct_value", "$@11",
  "field_values", "array_value", "$@12", "element_values",
  "array_expansion", "array_type_token", "numeric_type_token",
  "keyword_list", "empty", YY_NULL
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
     285,    59,    46,    42,    44,    47,   123,   125,    58,    61,
      91,    93,    40,    41,    37,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    48,    48,    48,    48,
      48,    49,    49,    49,    50,    50,    51,    51,    52,    52,
      53,    53,    54,    54,    55,    56,    57,    58,    59,    59,
      61,    60,    62,    62,    63,    63,    64,    65,    65,    65,
      66,    66,    68,    67,    69,    69,    69,    70,    70,    71,
      71,    71,    71,    72,    73,    72,    74,    75,    77,    76,
      78,    76,    79,    76,    80,    81,    81,    82,    82,    82,
      83,    83,    83,    84,    84,    85,    86,    86,    87,    87,
      87,    87,    88,    89,    90,    90,    91,    91,    91,    92,
      92,    93,    93,    94,    94,    94,    94,    95,    94,    96,
      97,    99,    98,   100,    98,   101,   101,   101,   101,   102,
     102,   102,   102,   103,   103,   104,   105,   106,   106,   106,
     107,   107,   108,   108,   108,   108,   108,   108,   108,   110,
     109,   111,   111,   113,   112,   114,   114,   114,   114,   115,
     116,   115,   117,   117,   117,   117,   118,   118,   118,   118,
     119,   119,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   121,   121,   122
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     2,     2,     2,     2,     2,
       2,     1,     1,     1,     2,     4,     1,     3,     1,     1,
       1,     3,     1,     3,     2,     2,     1,     2,     1,     2,
       0,     7,     1,     2,     1,     3,     1,     1,     2,     3,
       2,     1,     0,     6,     1,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     4,     0,     4,
       0,     4,     0,     5,     2,     1,     1,     1,     1,     1,
       4,     4,     4,     3,     3,     1,     1,     4,     1,     1,
       1,     1,     1,     4,     3,     3,     3,     3,     3,     2,
       2,     2,     3,     1,     1,     1,     1,     0,     4,     2,
       4,     0,     4,     0,     4,     1,     1,     3,     2,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     3,     0,     4,     1,     1,     3,     3,     2,
       0,     4,     1,     1,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   165,   165,     0,     2,     4,   123,   122,   124,   125,
     126,   133,   140,   129,     3,    12,    13,   128,   127,    11,
       1,     0,     0,     0,     0,     0,   165,     5,     8,     9,
      10,     6,     7,     0,   139,     0,     0,    30,    42,    22,
       0,    16,    14,    26,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   150,   151,   152,    24,    67,     0,
      65,    66,    69,    68,    78,    79,    80,    81,    76,    82,
      27,    28,   135,   136,     0,   123,   122,   124,   126,   142,
       0,   143,   131,     0,   165,     0,     0,     0,     0,   165,
      25,   165,   165,     0,   165,     0,     0,     0,     0,   165,
      29,     0,   134,     0,     0,     0,     0,     0,   141,     0,
     130,     0,     0,    32,   165,    19,    15,    18,    20,    17,
      23,   115,   113,     0,   110,   114,   109,     0,     0,    86,
     117,   118,   119,   120,     0,   121,   106,   105,    84,    87,
      85,    88,     0,   137,   138,   147,   146,   148,   149,   144,
     145,   132,    36,    33,    34,   165,     0,    44,     0,    71,
     116,     0,   112,    72,    70,    83,     0,   108,    77,     0,
       0,    37,    26,    45,    43,    56,     0,    47,    48,    49,
      50,    51,    52,    53,    21,   111,   107,    35,    26,    38,
      31,     0,   165,    41,     0,    64,     0,    46,    58,   165,
      60,     0,    54,     0,    39,    40,   163,     0,    89,    96,
      65,    91,    93,    94,    95,     0,    90,     0,     0,     0,
      62,     0,    75,    73,   164,    74,    97,    99,   101,   165,
     103,    92,    59,    57,    61,     0,    55,     0,     0,     0,
       0,    63,    98,   102,   100,   104
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    14,    28,    40,   116,   117,    41,    29,
     175,    58,    30,    70,    31,    84,   112,   153,   154,   170,
     191,    32,    85,   156,   176,   177,   178,   221,   179,   180,
     181,   217,   219,   235,   182,    59,    60,    61,   193,   223,
      62,    63,    64,    65,    66,    67,   195,   196,   211,   237,
     212,   213,   214,   238,   240,   134,   123,   124,   125,   162,
     135,   136,    15,    16,    36,    83,    17,    33,    74,    18,
      35,    80,    81,    68,    69,   205,   126
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -169
static const yytype_int16 yypact[] =
{
      67,  -169,    18,    37,   134,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,   -28,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,    40,    53,    75,    75,   190,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,    18,  -169,    27,    35,  -169,  -169,  -169,
      13,     0,    64,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,    72,   105,
    -169,  -169,    85,   100,    20,    -8,   106,  -169,   101,  -169,
     144,  -169,  -169,  -169,    16,   109,   120,   121,   122,  -169,
      32,  -169,  -169,    22,   118,   123,    11,    75,   149,    43,
    -169,    43,    43,   158,   115,    90,   158,    90,   158,    43,
    -169,    18,  -169,   158,   158,   158,   158,    27,  -169,    35,
    -169,   154,   127,  -169,  -169,  -169,  -169,   130,     0,     0,
    -169,  -169,  -169,   125,     6,  -169,  -169,   126,   146,  -169,
    -169,  -169,  -169,  -169,   142,  -169,    12,  -169,  -169,  -169,
    -169,  -169,   147,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,   157,  -169,  -169,   108,  -169,    75,  -169,
    -169,    43,  -169,  -169,  -169,  -169,   115,  -169,  -169,   154,
     152,  -169,   150,  -169,  -169,  -169,   137,  -169,  -169,    46,
     155,  -169,   160,     4,     0,  -169,  -169,  -169,    73,  -169,
    -169,   162,  -169,   163,    80,  -169,    38,  -169,  -169,    43,
    -169,   159,  -169,   188,  -169,   192,  -169,   188,  -169,   164,
     198,  -169,    82,   182,  -169,   190,  -169,    35,   181,    35,
    -169,    35,  -169,  -169,  -169,  -169,  -169,  -169,  -169,    43,
    -169,  -169,  -169,  -169,  -169,    35,  -169,    35,    35,   183,
      35,  -169,  -169,  -169,  -169,  -169
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -169,  -169,  -169,  -169,  -169,   199,  -169,  -169,   -78,  -169,
     200,  -169,  -169,  -169,  -169,  -169,  -169,  -169,    57,  -169,
    -169,  -169,  -169,  -169,  -169,    58,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -145,  -168,  -169,  -169,    23,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,    14,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,   -85,    66,   -14,  -169,
     -77,    65,   -33,   -32,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,   128,  -169,  -169,  -169,     3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      72,    73,    79,    82,     5,    19,   127,   128,   118,   119,
     160,   183,    90,    34,   142,   130,   131,   132,   138,    39,
     140,     6,     7,     8,     9,    10,   210,    96,    86,    71,
      75,    76,    77,     9,    78,    88,    97,    20,     6,     7,
       8,     9,    10,   202,   115,    87,   121,   210,    37,   209,
     101,   161,   122,   102,    11,    93,   109,   166,    12,   167,
      13,    38,    94,    11,    95,   110,   107,    12,   143,   144,
     209,    11,   215,   108,   149,    12,   151,     1,     2,   129,
     184,   216,   139,    39,   141,   198,   199,   113,    43,   145,
     146,   147,   148,   130,   131,   132,    87,   137,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   203,    89,    90,   218,   194,   172,   157,   130,   131,
     132,   228,   229,   208,   133,    91,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,   173,
      92,    98,   103,    99,   239,   174,    21,    22,    23,    24,
      25,    26,   100,   104,   105,   106,   111,   120,   171,   114,
     188,   121,   152,   155,   158,    27,   159,   163,   197,   220,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,   189,   232,   165,   234,   164,   236,   190,
     168,   169,   194,   204,   200,   206,   222,   207,    43,   201,
     224,    13,   241,   226,   242,   243,   227,   245,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   230,   233,    42,   244,    57,   187,   185,   192,   231,
     225,   186,     0,     0,     0,   150
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-169)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      33,    33,    35,    36,     1,     2,    91,    92,    86,    87,
       4,   156,     8,    41,    99,     3,     4,     5,    95,     8,
      97,     3,     4,     5,     6,     7,   194,    35,    15,    26,
       3,     4,     5,     6,     7,    35,    44,     0,     3,     4,
       5,     6,     7,    39,    33,    32,     3,   215,     8,   194,
      34,    45,     9,    37,    36,    35,    34,    45,    40,   136,
      42,     8,    42,    36,    44,    43,    34,    40,   101,   101,
     215,    36,    34,    41,   107,    40,   109,    10,    11,    93,
     158,    43,    96,     8,    98,    39,    40,    84,     8,   103,
     104,   105,   106,     3,     4,     5,    32,    94,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    38,    40,     8,   199,    42,     8,   114,     3,     4,
       5,    39,    40,    43,     9,    40,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      40,    35,    33,    42,   229,    37,    12,    13,    14,    15,
      16,    17,     8,    33,    33,    33,    38,     8,   155,    36,
       8,     3,     8,    36,    34,    31,    41,    41,    31,   201,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   217,    43,   219,    41,   221,    37,
      43,    34,    42,    31,    39,   192,     8,    34,     8,    39,
       8,    42,   235,    39,   237,   238,     8,   240,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    39,    41,    24,    41,    25,   169,   161,   170,   215,
     207,   166,    -1,    -1,    -1,   107
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    11,    47,    48,   122,     3,     4,     5,     6,
       7,    36,    40,    42,    49,   108,   109,   112,   115,   122,
       0,    12,    13,    14,    15,    16,    17,    31,    50,    55,
      58,    60,    67,   113,    41,   116,   110,     8,     8,     8,
      51,    54,    51,     8,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    56,    57,    81,
      82,    83,    86,    87,    88,    89,    90,    91,   119,   120,
      59,   122,   108,   109,   114,     3,     4,     5,     7,   108,
     117,   118,   108,   111,    61,    68,    15,    32,    35,    40,
       8,    40,    40,    35,    42,    44,    35,    44,    35,    42,
       8,    34,    37,    33,    33,    33,    33,    34,    41,    34,
      43,    38,    62,   122,    36,    33,    52,    53,    54,    54,
       8,     3,     9,   102,   103,   104,   122,   102,   102,   104,
       3,     4,     5,     9,   101,   106,   107,   122,   106,   104,
     106,   104,   102,   108,   109,   104,   104,   104,   104,   108,
     118,   108,     8,    63,    64,    36,    69,   122,    34,    41,
       4,    45,   105,    41,    41,    43,    45,   106,    43,    34,
      65,   122,     8,    31,    37,    56,    70,    71,    72,    74,
      75,    76,    80,    81,    54,   103,   107,    64,     8,    31,
      37,    66,    71,    84,    42,    92,    93,    31,    39,    40,
      39,    39,    39,    38,    31,   121,   122,    34,    43,    81,
      82,    94,    96,    97,    98,    34,    43,    77,   102,    78,
     109,    73,     8,    85,     8,    85,    39,     8,    39,    40,
      39,    94,   108,    41,   108,    79,   108,    95,    99,   102,
     100,   108,   108,   108,    41,   108
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

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 11:
/* Line 1787 of yacc.c  */
#line 241 "parser.ypp"
    {
		parsed_value->clear();
		if(!check_depth(0)) depth_error(0);
		type_stack.pop();
	}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 247 "parser.ypp"
    {
		parsed_value->assign((yyvsp[(1) - (1)].str));
		if(!check_depth(0)) depth_error(0, "type");
		type_stack.pop();
	}
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 253 "parser.ypp"
    {
		parsed_value->assign((yyvsp[(1) - (1)].str));
		if(!check_depth(0)) depth_error(0, "method");
		type_stack.pop();
	}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 262 "parser.ypp"
    {
		Import* import = new Import((yyvsp[(2) - (2)].str));
		parsed_file->add_import(import);
	}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 267 "parser.ypp"
    {
		Import* import = new Import((yyvsp[(2) - (4)].str));
		import->symbols.assign((yyvsp[(4) - (4)].strings).begin(), (yyvsp[(4) - (4)].strings).end());
		parsed_file->add_import(import);
	}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 275 "parser.ypp"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 277 "parser.ypp"
    {
		(yyval.str) = (yyvsp[(1) - (3)].str) + string(".") + (yyvsp[(3) - (3)].str);
	}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 283 "parser.ypp"
    { (yyval.strings) = (yyvsp[(1) - (1)].strings); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 285 "parser.ypp"
    {
		(yyval.strings) = vector<string>();
	}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 292 "parser.ypp"
    {
		(yyval.strings) = vector<string>(1, (yyvsp[(1) - (1)].str));
	}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 296 "parser.ypp"
    {
		(yyvsp[(1) - (3)].strings).push_back((yyvsp[(3) - (3)].str));
		(yyval.strings) = (yyvsp[(1) - (3)].strings);
	}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 303 "parser.ypp"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 305 "parser.ypp"
    {
		(yyval.str) = (yyvsp[(1) - (3)].str) + string("/") + (yyvsp[(3) - (3)].str);
	}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 312 "parser.ypp"
    {
		if((yyvsp[(2) - (2)].nametype).type == (DistributedType*)NULL)
		{
			// TODO: Figure out if we need to do anything here
			break;
		}

		bool type_added	= parsed_file->add_typedef((yyvsp[(2) - (2)].nametype).name, (yyvsp[(2) - (2)].nametype).type);
		if(!type_added)
		{
			// Lets be really descriptive about why this failed
			DistributedType* dtype = parsed_file->get_type_by_name((yyvsp[(2) - (2)].nametype).name);
			if(dtype == (DistributedType*)NULL)
			{
				parser_error("Unknown error adding typedef to file.");
				break;
			}

			Struct* dstruct = dtype->as_struct();
			if(dstruct == (Struct*)NULL)
			{
				parser_error("Cannot add 'typedef " + (yyvsp[(2) - (2)].nametype).name
				             + "' to file because a typedef was already declared with that name.");
				break;
			}

			if(dstruct->as_class())
			{
				parser_error("Cannot add 'typedef " + (yyvsp[(2) - (2)].nametype).name
				             + "' to file because a class was already declared with that name.");
			}
			else
			{
				parser_error("Cannot add 'typedef " + (yyvsp[(2) - (2)].nametype).name
				             + "' to file because a struct was already declared with that name.");
			}
		}
	}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 354 "parser.ypp"
    {
		TokenType::NameType nt;
		nt.type = (yyvsp[(1) - (2)].u.dtype);
		nt.name = (yyvsp[(2) - (2)].str);
		(yyval.nametype) = nt;
	}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 364 "parser.ypp"
    {
		DistributedType* dtype = parsed_file->get_type_by_name((yyvsp[(1) - (1)].str));
		if(dtype == (DistributedType*)NULL)
		{
			parser_error("Type '" + string((yyvsp[(1) - (1)].str)) + "' has not been declared.");
			(yyval.u.dtype) = NULL;
			break;
		}

		(yyval.u.dtype) = dtype;
	}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 384 "parser.ypp"
    {
		parsed_file->add_keyword((yyvsp[(2) - (2)].str));
	}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 391 "parser.ypp"
    {
		current_class = new Class(parsed_file, (yyvsp[(2) - (2)].str));
	}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 395 "parser.ypp"
    {
		bool class_added = parsed_file->add_class(current_class);
		if(!class_added)
		{
			// Lets be really descriptive about why this failed
			DistributedType* dtype = parsed_file->get_type_by_name(current_class->get_name());
			if(dtype == (DistributedType*)NULL)
			{
				parser_error("Unknown error adding class to file.");
				break;
			}

			Struct* dstruct = dtype->as_struct();
			if(dstruct == (Struct*)NULL)
			{
				parser_error("Cannot add 'dclass " + current_class->get_name()
				             + "' to file because a typedef was already declared with that name.");
				break;
			}

			if(dstruct->as_class())
			{
				parser_error("Cannot add 'dclass " + current_class->get_name()
				             + "' to file because a class was already declared with that name.");
			}
			else
			{
				parser_error("Cannot add 'dclass " + current_class->get_name()
				             + "' to file because a struct was already declared with that name.");
			}
		}
	}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 436 "parser.ypp"
    {
		if((yyvsp[(1) - (1)].u.dclass) != (Class*)NULL)
		{
			current_class->add_parent((yyvsp[(1) - (1)].u.dclass));
		}
	}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 443 "parser.ypp"
    {
		if((yyvsp[(3) - (3)].u.dclass) != (Class*)NULL)
		{
			current_class->add_parent((yyvsp[(3) - (3)].u.dclass));
		}
	}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 453 "parser.ypp"
    {
		DistributedType* dtype = parsed_file->get_type_by_name((yyvsp[(1) - (1)].str));
		if(dtype == (DistributedType*)NULL)
		{
			parser_error("'dclass " + string((yyvsp[(1) - (1)].str)) + "' has not been declared.");
			(yyval.u.dclass) = NULL;
			break;
		}

		Struct* dstruct = dtype->as_struct();
		if(dstruct == (Struct*)NULL)
		{
			parser_error("class cannot inherit from non-class type '" + string((yyvsp[(1) - (1)].str)) + "'.");
			(yyval.u.dclass) = NULL;
			break;
		}

		Class* dclass = dstruct->as_class();
		if(dclass == (Class*)NULL)
		{
			parser_error("class cannot inherit from struct type '" + string((yyvsp[(1) - (1)].str)) + "'.");
			(yyval.u.dclass) = NULL;
			break;
		}

		(yyval.u.dclass) = dclass;
	}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 486 "parser.ypp"
    {
		if((yyvsp[(2) - (3)].u.dfield) == (Field*)NULL)
		{
			// Ignore this field, it should have already generated a parser error
			break;
		}

		bool field_added = current_class->add_field((yyvsp[(2) - (3)].u.dfield));
		if(!field_added)
		{
			// Lets be really descriptive about why this failed
			if(current_class->get_field_by_name((yyvsp[(2) - (3)].u.dfield)->get_name()))
			{
				parser_error("Cannot add field '" + (yyvsp[(2) - (3)].u.dfield)->get_name()
				             + "', a field with that name already exists in 'dclass "
				             + current_class->get_name() + "'.");
			}
			else if(current_class->get_name() == (yyvsp[(2) - (3)].u.dfield)->get_name())
			{
				if((yyvsp[(2) - (3)].u.dfield)->as_molecular())
				{
					parser_error("Cannot use a molecular field as a constructor.");
				}
				else
				{
					parser_error("The constructor must be the first field in the class.");
				}
			}
			else
			{
				parser_error("Unknown error adding field to class.");
			}
		}
	}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 524 "parser.ypp"
    {
		if((yyvsp[(1) - (2)].u.dfield) == (Field*)NULL)
		{
			// Ignore this field, it should have already generated a parser error
			break;
		}

		if((yyvsp[(1) - (2)].u.dfield)->get_name().empty())
		{
			parser_error("An unnamed field can't be defined in a class.");
			(yyval.u.dfield) = NULL;
			break;
		}

		// Add the keywords to the class
		for(auto it = (yyvsp[(2) - (2)].strings).begin(); it != (yyvsp[(2) - (2)].strings).end(); ++it)
		{
			(yyvsp[(1) - (2)].u.dfield)->add_keyword(*it);
		}

		(yyval.u.dfield) = (yyvsp[(1) - (2)].u.dfield);
	}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 547 "parser.ypp"
    {
		(yyval.u.dfield) = (Field*)(yyvsp[(1) - (1)].u.dmolecule);
	}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 554 "parser.ypp"
    {
		current_struct = new Struct(parsed_file, (yyvsp[(2) - (2)].str));
	}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 558 "parser.ypp"
    {
		bool struct_added = parsed_file->add_struct(current_struct);
		if(!struct_added)
		{
			// Lets be really descriptive about why this failed
			DistributedType* dtype = parsed_file->get_type_by_name(current_struct->get_name());
			if(dtype == (DistributedType*)NULL)
			{
				parser_error("Unknown error adding struct to file.");
				break;
			}

			Struct* dstruct = dtype->as_struct();
			if(dstruct == (Struct*)NULL)
			{
				parser_error("Cannot add 'struct " + current_struct->get_name()
				             + "' to file because a typedef was already declared with that name.");
				break;
			}

			if(dstruct->as_class())
			{
				parser_error("Cannot add 'struct " + current_struct->get_name()
				             + "' to file because a class was already declared with that name.");
			}
			else
			{
				parser_error("Cannot add 'struct " + current_struct->get_name()
				             + "' to file because a struct was already declared with that name.");
			}
		}
	}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 596 "parser.ypp"
    {
		if((yyvsp[(2) - (3)].u.dfield) == (Field*)NULL)
		{
			// Ignore this field, it should have already generated a parser error
			break;
		}

		if(!current_struct->add_field((yyvsp[(2) - (3)].u.dfield)))
		{
			// Lets be really descriptive about why this failed
			if(current_struct->get_field_by_name((yyvsp[(2) - (3)].u.dfield)->get_name()))
			{
				parser_error("Cannot add field '" + (yyvsp[(2) - (3)].u.dfield)->get_name()
				             + "', a field with that name already exists in 'struct "
				             + current_struct->get_name() + "'.");
			}
			else if(current_struct->get_name() == (yyvsp[(2) - (3)].u.dfield)->get_name())
			{
				parser_error("A constructor can't be defined in a struct.");
			}
			else if((yyvsp[(2) - (3)].u.dfield)->get_type()->as_method())
			{
				parser_error("A method can't be defined in a struct.");
			}
			else
			{
				parser_error("Unknown error adding field to struct.");
			}
		}
	}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 642 "parser.ypp"
    {
		(yyval.u.dfield) = new Field((yyvsp[(1) - (1)].u.dtype));
	}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 646 "parser.ypp"
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[(1) - (2)].u.dtype), 0));
	}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 651 "parser.ypp"
    {
		Field* field = new Field((yyvsp[(1) - (4)].u.dtype));
		(yyval.u.dfield) = new Field((yyvsp[(1) - (4)].u.dtype));


		if(!check_depth(0)) depth_error(0, "unnamed field");
		type_stack.pop();
		field->set_default_value((yyvsp[(4) - (4)].str));
	}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 664 "parser.ypp"
    {
		(yyval.u.dfield) = new Field((yyvsp[(1) - (1)].nametype).type, (yyvsp[(1) - (1)].nametype).name);
	}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 671 "parser.ypp"
    {
		(yyvsp[(1) - (4)].u.dfield)->set_type(new ArrayType((yyvsp[(1) - (4)].u.dfield)->get_type(), (yyvsp[(3) - (4)].range)));
		(yyval.u.dfield) = (yyvsp[(1) - (4)].u.dfield);
	}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 679 "parser.ypp"
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[(1) - (2)].u.dfield)->get_type(), 0));
	}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 684 "parser.ypp"
    {
		(yyval.u.dfield) = (yyvsp[(1) - (4)].u.dfield);
		if(!check_depth(0)) depth_error(0, "field '" + (yyvsp[(1) - (4)].u.dfield)->get_name() + "'");
		type_stack.pop();
		(yyvsp[(1) - (4)].u.dfield)->set_default_value((yyvsp[(4) - (4)].str));
	}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 691 "parser.ypp"
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[(1) - (2)].u.dfield)->get_type(), 0));
	}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 696 "parser.ypp"
    {
		(yyval.u.dfield) = (yyvsp[(1) - (4)].u.dfield);
		if(!check_depth(0)) depth_error(0, "field '" + (yyvsp[(1) - (4)].u.dfield)->get_name() + "'");
		type_stack.pop();
		(yyvsp[(1) - (4)].u.dfield)->set_default_value((yyvsp[(4) - (4)].str));
	}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 703 "parser.ypp"
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[(1) - (3)].u.dfield)->get_type(), 0));
	}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 708 "parser.ypp"
    {
		(yyval.u.dfield) = (yyvsp[(1) - (5)].u.dfield);
		if(!check_depth(0)) depth_error(0, "method");
		type_stack.pop();
		(yyvsp[(1) - (5)].u.dfield)->set_default_value((yyvsp[(3) - (5)].str));
	}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 718 "parser.ypp"
    {
		(yyval.u.dfield) = new Field((yyvsp[(2) - (2)].u.dmethod), (yyvsp[(1) - (2)].str));
	}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 730 "parser.ypp"
    {
		if((yyvsp[(1) - (1)].u.dtype) == (DistributedType*)NULL)
		{
			// defined_type should have output an error, pass NULL upstream
			(yyval.u.dtype) = NULL;
			break;
		}

		if((yyvsp[(1) - (1)].u.dtype)->get_type() == METHOD)
		{
			parser_error("Cannot use a method type here.");
			(yyval.u.dtype) = NULL;
			break;
		}

		(yyval.u.dtype) = (yyvsp[(1) - (1)].u.dtype);
	}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 748 "parser.ypp"
    {
		(yyval.u.dtype) = (DistributedType*)(yyvsp[(1) - (1)].u.dnumeric);
	}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 756 "parser.ypp"
    {
		(yyval.u.dtype) = new ArrayType((yyvsp[(1) - (4)].u.dnumeric), (yyvsp[(3) - (4)].range));
	}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 760 "parser.ypp"
    {
		(yyval.u.dtype) = new ArrayType((yyvsp[(1) - (4)].u.dtype), (yyvsp[(3) - (4)].range));
	}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 764 "parser.ypp"
    {
		(yyval.u.dtype) = new ArrayType((yyvsp[(1) - (4)].u.dtype), (yyvsp[(3) - (4)].range));
	}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 771 "parser.ypp"
    {
		(yyval.u.dmolecule) = new MolecularField(current_class, (yyvsp[(1) - (3)].str));
	}
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 775 "parser.ypp"
    {
		(yyval.u.dmolecule) = (yyvsp[(1) - (3)].u.dmolecule);

		if((yyvsp[(3) - (3)].u.dfield) == (Field*)NULL)
		{
			// Ignore this field, it should have already generated an error
		}

		bool field_added = (yyvsp[(1) - (3)].u.dmolecule)->add_field((yyvsp[(3) - (3)].u.dfield));
		if(!field_added)
		{
			if((yyvsp[(3) - (3)].u.dfield)->as_molecular())
			{
				parser_error("Cannot add molecular '" + (yyvsp[(3) - (3)].u.dfield)->get_name() + "' to a molecular field.");
			}
			else if(!(yyvsp[(1) - (3)].u.dmolecule)->has_matching_keywords(*(yyvsp[(3) - (3)].u.dfield)))
			{
				parser_error("Mismatched keywords in molecular between " +
					(yyvsp[(1) - (3)].u.dmolecule)->get_field(0)->get_name() + " and " + (yyvsp[(3) - (3)].u.dfield)->get_name() + ".");
			}
		}
	}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 800 "parser.ypp"
    {
		if(!current_class)
		{
			parser_error("Field '" + (yyvsp[(1) - (1)].str) + "' not defined in current class.");
			(yyval.u.dfield) = NULL;
			break;
		}

		Field *field = current_class->get_field_by_name((yyvsp[(1) - (1)].str));
		if(field == (Field*)NULL)
		{
			parser_error("Field '" + (yyvsp[(1) - (1)].str) + "' not defined in current class.");
			(yyval.u.dfield) = NULL;
			break;
		}

		(yyval.u.dfield) = field;
	}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 822 "parser.ypp"
    {
		if((yyvsp[(1) - (1)].u.type) == STRING)
		{
			(yyval.u.dtype) = new ArrayType(new NumericType(CHAR));
		}
		else
		{
			(yyval.u.dtype) = new ArrayType(new NumericType(UINT8));
		}
	}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 833 "parser.ypp"
    {
		if((yyvsp[(1) - (4)].u.type) == STRING)
		{
			(yyval.u.dtype) = new ArrayType(new NumericType(CHAR), (yyvsp[(3) - (4)].range));
		}
		else
		{
			(yyval.u.dtype) = new ArrayType(new NumericType(UINT8), (yyvsp[(3) - (4)].range));
		}
	}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 853 "parser.ypp"
    { (yyval.u.dnumeric) = new NumericType((yyvsp[(1) - (1)].u.type)); }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 858 "parser.ypp"
    {
		if(!(yyvsp[(1) - (4)].u.dnumeric)->set_range((yyvsp[(3) - (4)].range)))
		{
			parser_error("Invalid range for type.");
		}

		(yyval.u.dnumeric) = (yyvsp[(1) - (4)].u.dnumeric);
	}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 870 "parser.ypp"
    {
		if(!(yyvsp[(1) - (3)].u.dnumeric)->set_modulus((yyvsp[(3) - (3)].u.real)))
		{
			parser_error("Invalid modulus for type.");
		}

		(yyval.u.dnumeric) = (yyvsp[(1) - (3)].u.dnumeric);
	}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 879 "parser.ypp"
    {
		if(!(yyvsp[(1) - (3)].u.dnumeric)->set_modulus((yyvsp[(3) - (3)].u.real)))
		{
			parser_error("Invalid modulus for type.");
		}

		(yyval.u.dnumeric) = (yyvsp[(1) - (3)].u.dnumeric);
	}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 891 "parser.ypp"
    {
		if(!(yyvsp[(1) - (3)].u.dnumeric)->set_divisor((yyvsp[(3) - (3)].u.uint32)))
		{
			parser_error("Invalid divisor for type.");
		}
	}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 898 "parser.ypp"
    {
		if(!(yyvsp[(1) - (3)].u.dnumeric)->set_divisor((yyvsp[(3) - (3)].u.uint32)))
		{
			parser_error("Invalid divisor for type.");
		}
	}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 905 "parser.ypp"
    {
		if(!(yyvsp[(1) - (3)].u.dnumeric)->set_divisor((yyvsp[(3) - (3)].u.uint32)))
		{
			parser_error("Invalid divisor for type.");
		}
	}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 915 "parser.ypp"
    {
		(yyval.u.dmethod) = new Method();
	}
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 919 "parser.ypp"
    {
		(yyval.u.dmethod) = (yyvsp[(1) - (2)].u.dmethod);
	}
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 926 "parser.ypp"
    {
		Method* fn = new Method();
		bool param_added = fn->add_parameter((yyvsp[(2) - (2)].u.dparam));
		if(!param_added)
		{
			parser_error("Unknown error adding parameter to method.");
		}
		(yyval.u.dmethod) = fn;
	}
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 936 "parser.ypp"
    {
		bool param_added = (yyvsp[(1) - (3)].u.dmethod)->add_parameter((yyvsp[(3) - (3)].u.dparam));
		if(!param_added)
		{
			parser_error("Cannot add parameter '" + (yyvsp[(3) - (3)].u.dparam)->get_name()
			             + "', a parameter with that name is already used in this method.");
		}
		(yyval.u.dmethod) = (yyvsp[(1) - (3)].u.dmethod);
	}
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 952 "parser.ypp"
    {
		(yyval.u.dparam) = new Parameter((yyvsp[(1) - (1)].u.dtype));
	}
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 956 "parser.ypp"
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[(1) - (2)].u.dtype),0));
	}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 961 "parser.ypp"
    {
		Parameter* param = new Parameter((yyvsp[(1) - (4)].u.dtype));
		(yyval.u.dparam) = param;

		if(!check_depth(0)) depth_error(0, "type");
		type_stack.pop();
		param->set_default_value((yyvsp[(4) - (4)].str));
	}
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 972 "parser.ypp"
    {
		(yyval.u.dparam) = new Parameter((yyvsp[(1) - (2)].u.dtype), (yyvsp[(2) - (2)].str));
	}
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 979 "parser.ypp"
    {
		(yyvsp[(1) - (4)].u.dparam)->set_type(new ArrayType((yyvsp[(1) - (4)].u.dparam)->get_type(), (yyvsp[(3) - (4)].range)));
		(yyval.u.dparam) = (yyvsp[(1) - (4)].u.dparam);
	}
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 987 "parser.ypp"
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[(1) - (2)].u.dparam)->get_type(), 0));
	}
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 992 "parser.ypp"
    {
		(yyval.u.dparam) = (yyvsp[(1) - (4)].u.dparam);
		if(!check_depth(0)) depth_error(0, "parameter '" + (yyvsp[(1) - (4)].u.dparam)->get_name() + "'");
		type_stack.pop();
		(yyvsp[(1) - (4)].u.dparam)->set_default_value((yyvsp[(4) - (4)].str));
	}
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 999 "parser.ypp"
    {
		current_depth = 0;
		type_stack.push(TypeAndDepth((yyvsp[(1) - (2)].u.dparam)->get_type(), 0));
	}
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 1004 "parser.ypp"
    {
		(yyval.u.dparam) = (yyvsp[(1) - (4)].u.dparam);
		if(!check_depth(0)) depth_error(0, "parameter '" + (yyvsp[(1) - (4)].u.dparam)->get_name() + "'");
		type_stack.pop();
		(yyvsp[(1) - (4)].u.dparam)->set_default_value((yyvsp[(4) - (4)].str));
	}
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 1013 "parser.ypp"
    { (yyval.range) = NumericRange(); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 1014 "parser.ypp"
    { (yyval.range) = NumericRange((yyvsp[(1) - (1)].u.real), (yyvsp[(1) - (1)].u.real)); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 1015 "parser.ypp"
    { (yyval.range) = NumericRange((yyvsp[(1) - (3)].u.real), (yyvsp[(3) - (3)].u.real)); }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 1016 "parser.ypp"
    { (yyval.range) = NumericRange((yyvsp[(1) - (2)].u.real), (yyvsp[(2) - (2)].u.real)); }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 1020 "parser.ypp"
    { (yyval.range) = NumericRange(); }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 1021 "parser.ypp"
    { (yyval.range) = NumericRange((yyvsp[(1) - (1)].u.uint32), (yyvsp[(1) - (1)].u.uint32)); }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 1022 "parser.ypp"
    { (yyval.range) = NumericRange((yyvsp[(1) - (3)].u.uint32), (yyvsp[(3) - (3)].u.uint32)); }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 1023 "parser.ypp"
    { (yyval.range) = NumericRange((yyvsp[(1) - (2)].u.uint32), (yyvsp[(2) - (2)].u.uint32)); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 1028 "parser.ypp"
    {
		if((yyvsp[(1) - (1)].str).length() != 1)
		{
			parser_error("Single character required.");
			(yyval.u.uint32) = 0;
		}
		else
		{
			(yyval.u.uint32) = (unsigned char)(yyvsp[(1) - (1)].str)[0];
		}
	}
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 1044 "parser.ypp"
    {
		(yyval.u.uint32) = (unsigned int)(yyvsp[(1) - (1)].u.uint64);
		if((yyval.u.uint32) != (yyvsp[(1) - (1)].u.uint64))
		{
			parser_error("Number out of range.");
			(yyval.u.uint32) = 1;
		}
	}
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 1056 "parser.ypp"
    {
		(yyval.u.uint32) = (unsigned int) - (yyvsp[(1) - (1)].u.int64);
		if((yyvsp[(1) - (1)].u.int64) >= 0)
		{
			parser_error("Syntax error while parsing small_negative_integer.");
		}
		else if((yyval.u.uint32) != -(yyvsp[(1) - (1)].u.int64))
		{
			parser_error("Number out of range.");
			(yyval.u.uint32) = 1;
		}
	}
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 1071 "parser.ypp"
    { (yyval.u.real) = (double)(yyvsp[(1) - (1)].u.uint64); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 1072 "parser.ypp"
    { (yyval.u.real) = (double)(yyvsp[(1) - (1)].u.int64); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 1078 "parser.ypp"
    {
		if((yyvsp[(1) - (1)].str).length() != 1)
		{
			parser_error("Single character required.");
			(yyval.u.real) = 0;
		}
		else
		{
			(yyval.u.real) = (double)(unsigned char)(yyvsp[(1) - (1)].str)[0];
		}
	}
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 1094 "parser.ypp"
    {
		if(!check_depth()) depth_error("signed integer");

		const DistributedType* dtype = type_stack.top().type;;
		type_stack.pop(); // Remove numeric type from stack

		(yyval.str) = number_value(dtype->get_type(), (yyvsp[(1) - (1)].u.int64));
	}
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 1103 "parser.ypp"
    {
		if(!check_depth()) depth_error("unsigned integer");

		const DistributedType* dtype = type_stack.top().type;;
		type_stack.pop(); // Remove numeric type from stack

		(yyval.str) = number_value(dtype->get_type(), (yyvsp[(1) - (1)].u.uint64));
	}
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 1112 "parser.ypp"
    {
		if(!check_depth()) depth_error("floating point");

		const DistributedType* dtype = type_stack.top().type;;
		type_stack.pop(); // Remove numeric type from stack

		(yyval.str) = number_value(dtype->get_type(), (yyvsp[(1) - (1)].u.real));
	}
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 1121 "parser.ypp"
    {
		if(!check_depth()) depth_error("string");

		const DistributedType* dtype = type_stack.top().type;;
		type_stack.pop(); // Remove string type from stack

		if(dtype->get_type() == STRING)
		{
			if((yyvsp[(1) - (1)].str).length() != dtype->get_size())
			{
				parser_error("Value for fixed-length string has incorrect length.");
			}

			(yyval.str) = (yyvsp[(1) - (1)].str);
		}
		else if(dtype->get_type() == VARSTRING)
		{
			// TODO: Check for range limits
			// Prepend length tag
			sizetag_t length = (yyvsp[(1) - (1)].str).length();
			(yyval.str) = string((char*)&length, sizeof(sizetag_t)) + (yyvsp[(1) - (1)].str);
		}
		else
		{
			parser_error("Cannot use string value for non-string type '"
			             + to_string(dtype->get_type()) + "'.");
			(yyval.str) = (yyvsp[(1) - (1)].str);
		}
	}
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 1151 "parser.ypp"
    {
		if(!check_depth()) depth_error("hex-string");

		const DistributedType* dtype = type_stack.top().type;;
		type_stack.pop(); // Remove type from stack

		if(dtype->get_type() == BLOB)
		{
			if((yyvsp[(1) - (1)].str).length() != dtype->get_size())
			{
				parser_error("Value for fixed-length blob has incorrect length.");
			}

			(yyval.str) = (yyvsp[(1) - (1)].str);
		}
		else if(dtype->get_type() == VARBLOB)
		{
			// TODO: Check for range limits
			// Prepend length tag
			sizetag_t length = (yyvsp[(1) - (1)].str).length();
			(yyval.str) = string((char*)&length, sizeof(sizetag_t)) + (yyvsp[(1) - (1)].str);
		}
		else
		{
			parser_error("Cannot use hex value for non-blob type '"
			             + to_string(dtype->get_type()) + "'.");
			(yyval.str) = (yyvsp[(1) - (1)].str);
		}
	}
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 1182 "parser.ypp"
    {
		// TODO
		/*
		else if(type == DT_struct)
		{
			parser_warning("The {val} format is still parsed as an array value, values may not be properly validated or packed for a struct.");
			$$ = $1;
		}
		else
		{
			parser_error("Cannot use array composition as value for non-array type.");
			$$ = $1;
		}
		*/
	}
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 1201 "parser.ypp"
    {
		if(!check_depth()) depth_error("method");

		const DistributedType* dtype = type_stack.top().type;;
		if(dtype->as_method())
		{
			current_depth++;
			const Method* method = dtype->as_method();

			size_t num_params = method->get_num_parameters();
			for(unsigned int i = 1; i <= num_params; ++i)
			{
				// Reverse iteration
				const Parameter* param = method->get_parameter(num_params-i);
				// Add parameter types to stack such that the first is on top
				type_stack.push(TypeAndDepth(param->get_type(), current_depth));
			}
		}
		else
		{
			parser_error("Cannot use method-value for non-method type '"
			             + to_string(dtype->get_type()) + "'.");
		}
	}
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 1226 "parser.ypp"
    {
		if(type_stack.top().type->as_method())
		{
			current_depth--;
		}
		type_stack.pop(); // Remove method type from the stack
		(yyval.str) = (yyvsp[(3) - (4)].str);
	}
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 1239 "parser.ypp"
    {
		(yyval.str) = (yyvsp[(1) - (3)].str) + (yyvsp[(3) - (3)].str);
	}
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 1246 "parser.ypp"
    {
		if(!check_depth()) depth_error("struct");

		const DistributedType* dtype = type_stack.top().type;;
		if(dtype->as_struct())
		{
			current_depth++;
			const Struct* dstruct = dtype->as_struct();

			size_t num_fields = dstruct->get_num_fields();
			for(unsigned int i = 1; i <= num_fields; ++i)
			{
				// Reverse iteration
				const Field* field = dstruct->get_field(num_fields-i);
				// Add field types to stack such that the first is on top
				type_stack.push(TypeAndDepth(field->get_type(), current_depth));
			}
		}
		else
		{
			parser_error("Cannot use struct-composition for non-struct type '"
			             + to_string(dtype->get_type()) + "'.");
		}
	}
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 1271 "parser.ypp"
    {
		if(type_stack.top().type->as_struct())
		{
			current_depth--;
		}
		type_stack.pop(); // Remove method type from the stack
		(yyval.str) = (yyvsp[(3) - (4)].str);
	}
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 1285 "parser.ypp"
    {
		(yyval.str) = (yyvsp[(1) - (3)].str) + (yyvsp[(3) - (3)].str);
	}
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 1289 "parser.ypp"
    {
		(yyval.str) = (yyvsp[(1) - (3)].str) + (yyvsp[(3) - (3)].str);
	}
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 1296 "parser.ypp"
    {
		// TODO: deal with fixed sized and varsized array
		(yyval.str) = "";
	}
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 1301 "parser.ypp"
    {
		if(!check_depth()) depth_error("array");

		const DistributedType* dtype = type_stack.top().type;;
		if(dtype->as_array())
		{
			current_depth++;
			const ArrayType* array = dtype->as_array();

			// TODO: Cry in pain...
		}
		else
		{
			parser_error("Cannot use array-composition for non-array type '"
			             + to_string(dtype->get_type()) + "'.");
		}
	}
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 1319 "parser.ypp"
    {
		if(type_stack.top().type->as_array())
		{
			current_depth--;
		}
		type_stack.pop(); // Remove method type from the stack
		(yyval.str) = (yyvsp[(3) - (4)].str);
	}
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 1338 "parser.ypp"
    {
		/*
		string val;

		ArrayParameter* arr = current_parameter->as_field()->as_parameter()->as_array_parameter();
		if(arr == (ArrayParameter*)NULL)
		{
			parser_error("Cannot use array expansion as value for non-array parameter.");
		}
		else
		{
			for(unsigned int i = 0; i < $3; i++)
			{
				val += number_value(arr->get_element_type()->get_datatype(), $1);
			}
		}

		$$ = val;
		*/
	}
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 1359 "parser.ypp"
    {
		/*
		string val;

		ArrayParameter* arr = current_parameter->as_field()->as_parameter()->as_array_parameter();
		if(arr == (ArrayParameter*)NULL)
		{
			parser_error("Cannot use array expansion as value for non-array parameter.");
		}
		else
		{
			for(unsigned int i = 0; i < $3; i++)
			{
				val += number_value(arr->get_element_type()->get_datatype(), $1);
			}
		}

		$$ = val;
		*/
	}
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 1380 "parser.ypp"
    {
		/*
		string val;

		ArrayParameter* arr = current_parameter->as_field()->as_parameter()->as_array_parameter();
		if(arr == (ArrayParameter*)NULL)
		{
			parser_error("Cannot use array expansion as value for non-array parameter.");
		}
		else
		{
			for(unsigned int i = 0; i < $3; i++)
			{
				val += number_value(arr->get_element_type()->get_datatype(), $1);
			}
		}

		$$ = val;
		*/
	}
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 1401 "parser.ypp"
    {
		/*
		string val;

		// TODO: Check array type compatible with HEX_STRING,
		//       and check integer bounds if current parameter has integer type.
		ArrayParameter* arr = current_parameter->as_field()->as_parameter()->as_array_parameter();
		if(arr == (ArrayParameter*)NULL)
		{
			parser_error("Cannot use array expansion as value for non-array parameter.");
		}
		else
		{
			for(unsigned int i = 0; i < $3; i++)
			{
				val += $1;
			}
		}
		$$ = val;
		*/
	}
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 1425 "parser.ypp"
    { (yyval.u.type) = STRING; }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 1426 "parser.ypp"
    { (yyval.u.type) = BLOB; }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 1430 "parser.ypp"
    { (yyval.u.type) = CHAR; }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 1431 "parser.ypp"
    { (yyval.u.type) = INT8; }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 1432 "parser.ypp"
    { (yyval.u.type) = INT16; }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 1433 "parser.ypp"
    { (yyval.u.type) = INT32; }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 1434 "parser.ypp"
    { (yyval.u.type) = INT64; }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 1435 "parser.ypp"
    { (yyval.u.type) = UINT8; }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 1436 "parser.ypp"
    { (yyval.u.type) = UINT16; }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 1437 "parser.ypp"
    { (yyval.u.type) = UINT32; }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 1438 "parser.ypp"
    { (yyval.u.type) = UINT64; }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 1439 "parser.ypp"
    { (yyval.u.type) = FLOAT32; }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 1440 "parser.ypp"
    { (yyval.u.type) = FLOAT64; }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 1445 "parser.ypp"
    {
		(yyval.strings) = vector<string>();
	}
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 1449 "parser.ypp"
    {
		(yyval.strings) = (yyvsp[(1) - (2)].strings);
		if(!parsed_file->has_keyword((yyvsp[(2) - (2)].str)))
		{
			parser_error("Keyword '" + (yyvsp[(2) - (2)].str) + "' has not been declared.");
			break;
		}

		(yyvsp[(1) - (2)].strings).push_back((yyvsp[(2) - (2)].str));
	}
    break;


/* Line 1787 of yacc.c  */
#line 3238 "parser.cpp"
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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


/* Line 2050 of yacc.c  */
#line 1465 "parser.ypp"
 /* Start helper function section */


bool check_depth()
{
	return (!type_stack.empty() && current_depth == type_stack.top().depth);
}

bool check_depth(int depth)
{
	return (current_depth == depth && check_depth());
}

void depth_error(string what)
{
	if(type_stack.empty() || current_depth < type_stack.top().depth)
	{
		parser_error("Too many nested values while parsing value for " + what + ".");
	}
	else
	{
		parser_error("Too few nested values while parsing value for " + what + ".");	
	}
}

void depth_error(int depth, string what)
{
	if(current_depth > depth)
	{
		parser_error("Too few nested values before this " + what + " value.");
	}
	else
	{
		parser_error("Too many nested values before this " + what + " value.");
	}
}

string number_value(Type type, double &number)
{
	switch(type)
	{
		case FLOAT32:
		{
			float v = number;
			if(v == INFINITY || v == -INFINITY)
			{
				parser_error("Value is out of range for type 'float32'.");
			}

			return string((char*)&v, sizeof(float));
		}
		case FLOAT64:
		{
			return string((char*)&number, sizeof(double));
		}
		case INT8:
		case INT16:
		case INT32:
		case INT64:
		case UINT8:
		case UINT16:
		case UINT32:
		case UINT64:
		{
			parser_error("Cannot use floating-point value for integer datatype.");
			return string();
		}
		default:
		{
			parser_error("Cannot use floating-point value for non-numeric datatype.");
			return string();
		}
	}
}

string number_value(Type type, int64_t &number)
{
	switch(type)
	{
		case INT8:
		{
			if(INT8_MIN > number || number > INT8_MAX)
			{
				parser_error("Signed integer out of range for type 'int8'.");
			}

			int8_t v = number;
			return string((char*)&v, sizeof(int8_t));
		}
		case INT16:
		{
			if(INT16_MIN > number || number > INT16_MAX)
			{
				parser_error("Signed integer out of range for type 'int16'.");
			}

			uint16_t v = number;
			return string((char*)&v, sizeof(int16_t));
		}
		case INT32:
		{
			if(INT32_MIN > number || number > INT32_MAX)
			{
				parser_error("Signed integer out of range for type 'int32'.");
			}

			int32_t v = number;
			return string((char*)&v, sizeof(int32_t));
		}
		case INT64:
		{
			return string((char*)&number, sizeof(int64_t));
		}
		case UINT8:
		case UINT16:
		case UINT32:
		case UINT64:
		{
			if(number < 0)
			{
				parser_error("Can't use negative value for unsigned integer datatype.");
			}
			uint64_t v = number;
			return number_value(type, v);
		}
		case FLOAT32:
		case FLOAT64:
		{
			// Note: Expecting number to be converted to a double by value (ie. -1 becomes -1.0)
			double v = number;
			return number_value(type, v);
		}
		default:
		{
			parser_error("Cannot use signed integer value for non-numeric datatype.");
			return string();
		}
	}
}

string number_value(Type type, uint64_t &number)
{
	switch(type)
	{
		case UINT8:
		{
			if(number > UINT8_MAX)
			{
				parser_error("Unsigned integer out of range for type 'uint8'.");
			}

			uint8_t v = number;
			return string((char*)&v, sizeof(uint8_t));
		}
		case UINT16:
		{
			if(number > UINT16_MAX)
			{
				parser_error("Unsigned integer out of range for type 'uint16'.");
			}

			uint16_t v = number;
			return string((char*)&v, sizeof(uint16_t));
		}
		case UINT32:
		{
			if(number > UINT32_MAX)
			{
				parser_error("Unsigned integer out of range for type 'uint32'.");
			}

			uint32_t v = number;
			return string((char*)&v, sizeof(uint32_t));
		}
		case UINT64:
		{
			return string((char*)&number, sizeof(uint64_t));
		}
		case INT8:
		case INT16:
		case INT32:
		case INT64:
		{
			if(number > INT64_MAX)
			{
				parser_error("Unsigned integer out of range for signed integer datatype.");
			}
			int64_t v = number;
			return number_value(type, v);
		}
		case FLOAT32:
		case FLOAT64:
		{
			// Note: Expecting number to be converted to a double by value (ie. 3 becomes 3.0)
			double v = number;
			return number_value(type, v);
		}
		default:
		{
			parser_error("Cannot use unsigned integer value for non-numeric datatype.");
			return string();
		}
	}
}


} // close namespace dclass
