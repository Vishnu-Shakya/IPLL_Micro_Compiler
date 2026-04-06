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
#line 1 "a7_220101113.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbol table structure
typedef struct symbol {
    char *name;
    char *type;
    int scope;
    struct symbol *next;
} Symbol;

Symbol *symbolTable = NULL;

// Function prototypes
void addSymbol(char *name, char *type, int scope);
Symbol *findSymbol(char *name, int scope);
void printSymbolTable();
void yyerror(char *s);
int yylex();

// Global variables
int current_scope = 0;

#line 97 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 257 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_INTEGER_CONSTANT = 4,           /* INTEGER_CONSTANT  */
  YYSYMBOL_FLOATING_CONSTANT = 5,          /* FLOATING_CONSTANT  */
  YYSYMBOL_CHARACTER_CONSTANT = 6,         /* CHARACTER_CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 7,             /* STRING_LITERAL  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_INTEGER = 11,                   /* INTEGER  */
  YYSYMBOL_CHAR = 12,                      /* CHAR  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_CONST = 14,                     /* CONST  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_BOOL = 16,                      /* BOOL  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_DO = 18,                        /* DO  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_MC_BEGIN = 20,                  /* MC_BEGIN  */
  YYSYMBOL_END = 21,                       /* END  */
  YYSYMBOL_ARROW = 22,                     /* ARROW  */
  YYSYMBOL_INCREMENT = 23,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 24,                 /* DECREMENT  */
  YYSYMBOL_AMPERSAND = 25,                 /* AMPERSAND  */
  YYSYMBOL_ASTERISK = 26,                  /* ASTERISK  */
  YYSYMBOL_PLUS = 27,                      /* PLUS  */
  YYSYMBOL_MINUS = 28,                     /* MINUS  */
  YYSYMBOL_EXCLAMATION = 29,               /* EXCLAMATION  */
  YYSYMBOL_FORWARD_SLASH = 30,             /* FORWARD_SLASH  */
  YYSYMBOL_PERCENT = 31,                   /* PERCENT  */
  YYSYMBOL_LEFT_SHIFT = 32,                /* LEFT_SHIFT  */
  YYSYMBOL_RIGHT_SHIFT = 33,               /* RIGHT_SHIFT  */
  YYSYMBOL_LESS_THAN = 34,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_THAN = 35,              /* GREATER_THAN  */
  YYSYMBOL_LP = 36,                        /* LP  */
  YYSYMBOL_RP = 37,                        /* RP  */
  YYSYMBOL_LESS_THAN_EQUAL = 38,           /* LESS_THAN_EQUAL  */
  YYSYMBOL_GREATER_THAN_EQUAL = 39,        /* GREATER_THAN_EQUAL  */
  YYSYMBOL_EQUAL_EQUAL = 40,               /* EQUAL_EQUAL  */
  YYSYMBOL_NOT_EQUAL = 41,                 /* NOT_EQUAL  */
  YYSYMBOL_CARET = 42,                     /* CARET  */
  YYSYMBOL_PIPE = 43,                      /* PIPE  */
  YYSYMBOL_LOGICAL_AND = 44,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 45,                /* LOGICAL_OR  */
  YYSYMBOL_QUESTION_MARK = 46,             /* QUESTION_MARK  */
  YYSYMBOL_COLON = 47,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 48,                 /* SEMICOLON  */
  YYSYMBOL_ASSIGN = 49,                    /* ASSIGN  */
  YYSYMBOL_COMMA = 50,                     /* COMMA  */
  YYSYMBOL_51_ = 51,                       /* '['  */
  YYSYMBOL_52_ = 52,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_expression = 54,                /* expression  */
  YYSYMBOL_assignment_expression = 55,     /* assignment_expression  */
  YYSYMBOL_conditional_expression = 56,    /* conditional_expression  */
  YYSYMBOL_logical_OR_expression = 57,     /* logical_OR_expression  */
  YYSYMBOL_logical_AND_expression = 58,    /* logical_AND_expression  */
  YYSYMBOL_equality_expression = 59,       /* equality_expression  */
  YYSYMBOL_relational_expression = 60,     /* relational_expression  */
  YYSYMBOL_additive_expression = 61,       /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 62, /* multiplicative_expression  */
  YYSYMBOL_unary_operator = 63,            /* unary_operator  */
  YYSYMBOL_unary_expression = 64,          /* unary_expression  */
  YYSYMBOL_argument_expression_list_opt = 65, /* argument_expression_list_opt  */
  YYSYMBOL_argument_expression_list = 66,  /* argument_expression_list  */
  YYSYMBOL_postfix_expression = 67,        /* postfix_expression  */
  YYSYMBOL_primary_expression = 68,        /* primary_expression  */
  YYSYMBOL_declaration = 69,               /* declaration  */
  YYSYMBOL_init_declarator = 70,           /* init_declarator  */
  YYSYMBOL_type_specifier = 71,            /* type_specifier  */
  YYSYMBOL_declarator = 72,                /* declarator  */
  YYSYMBOL_pointer_opt = 73,               /* pointer_opt  */
  YYSYMBOL_direct_declarator = 74,         /* direct_declarator  */
  YYSYMBOL_pointer = 75,                   /* pointer  */
  YYSYMBOL_parameter_list_opt = 76,        /* parameter_list_opt  */
  YYSYMBOL_parameter_list = 77,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 78,     /* parameter_declaration  */
  YYSYMBOL_initializer = 79,               /* initializer  */
  YYSYMBOL_statement = 80,                 /* statement  */
  YYSYMBOL_compound_statement = 81,        /* compound_statement  */
  YYSYMBOL_82_1 = 82,                      /* $@1  */
  YYSYMBOL_block_item_list_opt = 83,       /* block_item_list_opt  */
  YYSYMBOL_block_item_list = 84,           /* block_item_list  */
  YYSYMBOL_block_item = 85,                /* block_item  */
  YYSYMBOL_expression_statement = 86,      /* expression_statement  */
  YYSYMBOL_expression_opt = 87,            /* expression_opt  */
  YYSYMBOL_selection_statement = 88,       /* selection_statement  */
  YYSYMBOL_iteration_statement = 89,       /* iteration_statement  */
  YYSYMBOL_jump_statement = 90,            /* jump_statement  */
  YYSYMBOL_translation_unit = 91,          /* translation_unit  */
  YYSYMBOL_function_definition = 92,       /* function_definition  */
  YYSYMBOL_function_declarator = 93        /* function_declarator  */
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
#define YYFINAL  81
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   274

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  166

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


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
       2,    51,     2,    52,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    75,    75,    79,    80,    84,    85,    89,    90,    94,
      95,    99,   100,   101,   105,   106,   107,   108,   109,   113,
     114,   115,   119,   120,   121,   122,   126,   127,   128,   129,
     130,   131,   132,   136,   137,   138,   139,   143,   144,   148,
     149,   153,   154,   155,   156,   160,   177,   178,   179,   180,
     181,   186,   192,   193,   197,   198,   199,   200,   201,   205,
     209,   210,   214,   218,   222,   229,   233,   234,   238,   239,
     243,   247,   253,   258,   259,   260,   261,   262,   267,   267,
     274,   275,   279,   280,   284,   285,   289,   293,   294,   298,
     301,   307,   310,   316,   321,   322,   323,   324,   325,   326,
     327,   328,   332,   341
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "INTEGER_CONSTANT", "FLOATING_CONSTANT", "CHARACTER_CONSTANT",
  "STRING_LITERAL", "RETURN", "VOID", "FLOAT", "INTEGER", "CHAR", "FOR",
  "CONST", "WHILE", "BOOL", "IF", "DO", "ELSE", "MC_BEGIN", "END", "ARROW",
  "INCREMENT", "DECREMENT", "AMPERSAND", "ASTERISK", "PLUS", "MINUS",
  "EXCLAMATION", "FORWARD_SLASH", "PERCENT", "LEFT_SHIFT", "RIGHT_SHIFT",
  "LESS_THAN", "GREATER_THAN", "LP", "RP", "LESS_THAN_EQUAL",
  "GREATER_THAN_EQUAL", "EQUAL_EQUAL", "NOT_EQUAL", "CARET", "PIPE",
  "LOGICAL_AND", "LOGICAL_OR", "QUESTION_MARK", "COLON", "SEMICOLON",
  "ASSIGN", "COMMA", "'['", "']'", "$accept", "expression",
  "assignment_expression", "conditional_expression",
  "logical_OR_expression", "logical_AND_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_operator", "unary_expression",
  "argument_expression_list_opt", "argument_expression_list",
  "postfix_expression", "primary_expression", "declaration",
  "init_declarator", "type_specifier", "declarator", "pointer_opt",
  "direct_declarator", "pointer", "parameter_list_opt", "parameter_list",
  "parameter_declaration", "initializer", "statement",
  "compound_statement", "$@1", "block_item_list_opt", "block_item_list",
  "block_item", "expression_statement", "expression_opt",
  "selection_statement", "iteration_statement", "jump_statement",
  "translation_unit", "function_definition", "function_declarator", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-83)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-104)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     196,   -83,   -83,   -83,   -83,   -83,   238,   -83,   -83,   -83,
     -83,   -25,   -83,   -22,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   238,   -39,   -83,   -83,   -27,     7,     9,   -18,
      35,    28,   238,   -11,   -12,   -83,   -83,    30,   -83,   -83,
     -83,    20,   -83,   -83,   -83,   162,   -83,   -83,    41,   224,
     238,    67,    49,   238,   238,   238,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,    43,   -83,   -83,
     238,    94,   238,   238,   -83,    50,    53,   101,   -83,    85,
     -83,   -83,   -39,   -83,   -83,   -83,   -83,   238,    30,    58,
      76,   -83,   -83,    93,    67,   -83,   -83,     7,    43,    69,
       9,   -18,   -18,    35,    35,    35,    35,    28,    28,    43,
      43,    43,   -83,   -83,   -83,    81,    70,    73,   -83,   238,
     -29,   -83,   -83,    71,   119,   238,   104,   -83,   -83,   238,
     -83,   238,   -83,   -83,   -83,    32,   130,   238,     4,    89,
     120,   -83,   -83,    30,   108,    88,   -83,    95,   109,    32,
     238,   104,   146,   132,    32,   -83,   104,   116,   117,   -83,
     -83,   -83,   -83,   -83,   104,   -83
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      88,    45,    46,    47,    48,    49,    88,    54,    57,    56,
      55,     0,    58,     0,    78,    31,    32,    26,    27,    28,
      29,    30,     0,    96,     2,     3,     5,     7,     9,    11,
      14,    19,     0,    22,    33,    41,    95,    61,    99,    73,
      74,     0,    75,    76,    77,    88,    94,    87,     0,    88,
       0,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
       0,     0,    38,     0,    65,     0,    52,     0,    60,     0,
      86,     1,   101,    98,   100,    97,    93,    88,    61,     0,
       0,    84,    85,     0,    80,    82,    50,     8,    22,     0,
      10,    12,    13,    15,    16,    17,    18,    20,    21,    23,
      24,    25,     4,    44,    39,     0,    37,     0,    51,     0,
      62,    59,   102,     0,     0,    88,    88,    79,    83,     0,
      43,     0,    42,    72,    53,    67,     0,    88,    62,     0,
      89,     6,    40,    61,     0,    66,    68,     0,     0,    67,
      88,    88,    71,    64,     0,    63,    88,     0,     0,    90,
      70,    69,    92,    64,    88,    91
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -83,    15,   -67,    29,   -83,   106,   102,    25,    83,    38,
     -83,   -30,   -83,   -83,   -83,   -83,     8,   -83,     1,   -83,
     -82,   -83,   -83,    11,   -83,    22,   -83,     0,    82,   -83,
     -83,   -83,    86,   -83,    -2,   -83,   -83,   -83,   -83,   118,
     -83
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    47,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,   115,   116,    34,    35,    91,    75,    88,    76,
      77,   121,    78,   144,   145,   146,   134,    92,    39,    51,
      93,    94,    95,    40,    41,    42,    43,    44,    45,    46,
      79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      38,    37,    67,   112,    48,   114,   124,   135,    36,   -87,
      71,    49,    68,    69,    50,    23,    58,    59,    53,    54,
      60,    61,   136,    98,    72,    98,    98,    98,    98,    98,
      98,    98,    98,    98,   109,   110,   111,    52,    70,    73,
     149,     7,     8,     9,    10,    84,    37,    89,    12,    56,
      57,    55,   133,    83,    64,   136,    74,    87,    65,    66,
      82,   152,    62,    63,   142,    90,    68,    69,    80,    99,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,   101,   102,    12,    13,   123,    96,    14,   117,    86,
      15,    16,    17,    18,    19,    20,    21,   113,   118,    98,
     107,   108,   119,    22,   120,    14,   125,     1,     2,     3,
       4,     5,     6,   126,   127,   -88,   129,    11,   130,   137,
     131,    13,   138,   139,    14,   132,   140,    15,    16,    17,
      18,    19,    20,    21,   147,   148,   143,   150,   154,   151,
      22,   103,   104,   105,   106,   153,   156,   155,   158,   160,
     143,   159,  -103,   163,   164,   143,   162,   100,   141,    97,
     157,   122,    81,    85,   165,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,   161,     0,    12,    13,
     128,     0,    14,     0,     0,    15,    16,    17,    18,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    22,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,    12,    13,     0,     0,    14,     0,     0,    15,
      16,    17,    18,    19,    20,    21,     0,     1,     2,     3,
       4,     5,    22,     7,     8,     9,    10,     0,     0,     0,
      12,     1,     2,     3,     4,     5,     0,    15,    16,    17,
      18,    19,    20,    21,     0,     0,     0,     0,     0,     0,
      22,    15,    16,    17,    18,    19,    20,    21,     0,     0,
       0,     0,     0,     0,    22
};

static const yytype_int16 yycheck[] =
{
       0,     0,    32,    70,     6,    72,    88,    36,     0,    48,
      22,    36,    23,    24,    36,     0,    34,    35,    45,    46,
      38,    39,    51,    53,    36,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    22,    49,    51,
      36,     9,    10,    11,    12,    45,    45,    49,    16,    40,
      41,    44,   119,    45,    26,    51,    26,    49,    30,    31,
      45,   143,    27,    28,   131,    50,    23,    24,    48,    54,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    56,    57,    16,    17,    87,    37,    20,    73,    48,
      23,    24,    25,    26,    27,    28,    29,     3,    48,   129,
      62,    63,    49,    36,     3,    20,    48,     3,     4,     5,
       6,     7,     8,    37,    21,    48,    47,    13,    37,    48,
      50,    17,     3,   125,    20,    52,   126,    23,    24,    25,
      26,    27,    28,    29,     4,   137,   135,    48,    50,    19,
      36,    58,    59,    60,    61,    37,    37,    52,   150,     3,
     149,   151,    20,    37,    37,   154,   156,    55,   129,    53,
     149,    79,     0,    45,   164,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   154,    -1,    16,    17,
      94,    -1,    20,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    36,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    16,    17,    -1,    -1,    20,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    -1,     3,     4,     5,
       6,     7,    36,     9,    10,    11,    12,    -1,    -1,    -1,
      16,     3,     4,     5,     6,     7,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    16,    17,    20,    23,    24,    25,    26,    27,
      28,    29,    36,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    67,    68,    69,    71,    80,    81,
      86,    87,    88,    89,    90,    91,    92,    54,    87,    36,
      36,    82,    54,    45,    46,    44,    40,    41,    34,    35,
      38,    39,    27,    28,    26,    30,    31,    64,    23,    24,
      49,    22,    36,    51,    26,    70,    72,    73,    75,    93,
      48,     0,    54,    69,    80,    92,    48,    69,    71,    87,
      54,    69,    80,    83,    84,    85,    37,    58,    64,    54,
      59,    60,    60,    61,    61,    61,    61,    62,    62,    64,
      64,    64,    55,     3,    55,    65,    66,    54,    48,    49,
       3,    74,    81,    87,    73,    48,    37,    21,    85,    47,
      37,    50,    52,    55,    79,    36,    51,    48,     3,    87,
      80,    56,    55,    71,    76,    77,    78,     4,    87,    36,
      48,    19,    73,    37,    50,    52,    37,    76,    87,    80,
       3,    78,    80,    37,    37,    80
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    59,    60,    60,    60,    60,    60,    61,
      61,    61,    62,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    64,    64,    64,    64,    65,    65,    66,
      66,    67,    67,    67,    67,    68,    68,    68,    68,    68,
      68,    69,    70,    70,    71,    71,    71,    71,    71,    72,
      73,    73,    74,    74,    74,    75,    76,    76,    77,    77,
      78,    78,    79,    80,    80,    80,    80,    80,    82,    81,
      83,    83,    84,    84,    85,    85,    86,    87,    87,    88,
      88,    89,    89,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    92,    93
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     5,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     1,     0,     1,
       3,     1,     4,     4,     3,     1,     1,     1,     1,     1,
       3,     3,     1,     3,     1,     1,     1,     1,     1,     2,
       1,     0,     1,     4,     4,     1,     1,     0,     1,     3,
       3,     2,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     2,     1,     1,     2,     1,     0,     5,
       7,     9,     8,     3,     1,     1,     1,     2,     2,     1,
       2,     2,     3,     5
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
  case 2: /* expression: assignment_expression  */
#line 75 "a7_220101113.y"
                            { printf("Reduction: expression -> assignment_expression\n"); }
#line 1481 "y.tab.c"
    break;

  case 3: /* assignment_expression: conditional_expression  */
#line 79 "a7_220101113.y"
                             { printf("Reduction: assignment_expression -> conditional_expression\n"); }
#line 1487 "y.tab.c"
    break;

  case 4: /* assignment_expression: unary_expression ASSIGN assignment_expression  */
#line 80 "a7_220101113.y"
                                                    { printf("Reduction: assignment_expression -> unary_expression ASSIGN assignment_expression\n"); }
#line 1493 "y.tab.c"
    break;

  case 5: /* conditional_expression: logical_OR_expression  */
#line 84 "a7_220101113.y"
                            { printf("Reduction: conditional_expression -> logical_OR_expression\n"); }
#line 1499 "y.tab.c"
    break;

  case 6: /* conditional_expression: logical_OR_expression QUESTION_MARK expression COLON conditional_expression  */
#line 85 "a7_220101113.y"
                                                                                  { printf("Reduction: conditional_expression -> logical_OR_expression QUESTION_MARK expression COLON conditional_expression\n"); }
#line 1505 "y.tab.c"
    break;

  case 7: /* logical_OR_expression: logical_AND_expression  */
#line 89 "a7_220101113.y"
                             { printf("Reduction: logical_OR_expression -> logical_AND_expression\n"); }
#line 1511 "y.tab.c"
    break;

  case 8: /* logical_OR_expression: logical_OR_expression LOGICAL_OR logical_AND_expression  */
#line 90 "a7_220101113.y"
                                                              { printf("Reduction: logical_OR_expression -> logical_OR_expression LOGICAL_OR logical_AND_expression\n"); }
#line 1517 "y.tab.c"
    break;

  case 9: /* logical_AND_expression: equality_expression  */
#line 94 "a7_220101113.y"
                          { printf("Reduction: logical_AND_expression -> equality_expression\n"); }
#line 1523 "y.tab.c"
    break;

  case 10: /* logical_AND_expression: logical_AND_expression LOGICAL_AND equality_expression  */
#line 95 "a7_220101113.y"
                                                             { printf("Reduction: logical_AND_expression -> logical_AND_expression LOGICAL_AND equality_expression\n"); }
#line 1529 "y.tab.c"
    break;

  case 11: /* equality_expression: relational_expression  */
#line 99 "a7_220101113.y"
                            { printf("Reduction: equality_expression -> relational_expression\n"); }
#line 1535 "y.tab.c"
    break;

  case 12: /* equality_expression: equality_expression EQUAL_EQUAL relational_expression  */
#line 100 "a7_220101113.y"
                                                            { printf("Reduction: equality_expression -> equality_expression EQUAL_EQUAL relational_expression\n"); }
#line 1541 "y.tab.c"
    break;

  case 13: /* equality_expression: equality_expression NOT_EQUAL relational_expression  */
#line 101 "a7_220101113.y"
                                                          { printf("Reduction: equality_expression -> equality_expression NOT_EQUAL relational_expression\n"); }
#line 1547 "y.tab.c"
    break;

  case 14: /* relational_expression: additive_expression  */
#line 105 "a7_220101113.y"
                          { printf("Reduction: relational_expression -> additive_expression\n"); }
#line 1553 "y.tab.c"
    break;

  case 15: /* relational_expression: relational_expression LESS_THAN additive_expression  */
#line 106 "a7_220101113.y"
                                                          { printf("Reduction: relational_expression -> relational_expression LESS_THAN additive_expression\n"); }
#line 1559 "y.tab.c"
    break;

  case 16: /* relational_expression: relational_expression GREATER_THAN additive_expression  */
#line 107 "a7_220101113.y"
                                                             { printf("Reduction: relational_expression -> relational_expression GREATER_THAN additive_expression\n"); }
#line 1565 "y.tab.c"
    break;

  case 17: /* relational_expression: relational_expression LESS_THAN_EQUAL additive_expression  */
#line 108 "a7_220101113.y"
                                                                { printf("Reduction: relational_expression -> relational_expression LESS_THAN_EQUAL additive_expression\n"); }
#line 1571 "y.tab.c"
    break;

  case 18: /* relational_expression: relational_expression GREATER_THAN_EQUAL additive_expression  */
#line 109 "a7_220101113.y"
                                                                   { printf("Reduction: relational_expression -> relational_expression GREATER_THAN_EQUAL additive_expression\n"); }
#line 1577 "y.tab.c"
    break;

  case 19: /* additive_expression: multiplicative_expression  */
#line 113 "a7_220101113.y"
                                { printf("Reduction: additive_expression -> multiplicative_expression\n"); }
#line 1583 "y.tab.c"
    break;

  case 20: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 114 "a7_220101113.y"
                                                         { printf("Reduction: additive_expression -> additive_expression PLUS multiplicative_expression\n"); }
#line 1589 "y.tab.c"
    break;

  case 21: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 115 "a7_220101113.y"
                                                          { printf("Reduction: additive_expression -> additive_expression MINUS multiplicative_expression\n"); }
#line 1595 "y.tab.c"
    break;

  case 22: /* multiplicative_expression: unary_expression  */
#line 119 "a7_220101113.y"
                       { printf("Reduction: multiplicative_expression -> unary_expression\n"); }
#line 1601 "y.tab.c"
    break;

  case 23: /* multiplicative_expression: multiplicative_expression ASTERISK unary_expression  */
#line 120 "a7_220101113.y"
                                                          { printf("Reduction: multiplicative_expression -> multiplicative_expression ASTERISK unary_expression\n"); }
#line 1607 "y.tab.c"
    break;

  case 24: /* multiplicative_expression: multiplicative_expression FORWARD_SLASH unary_expression  */
#line 121 "a7_220101113.y"
                                                               { printf("Reduction: multiplicative_expression -> multiplicative_expression FORWARD_SLASH unary_expression\n"); }
#line 1613 "y.tab.c"
    break;

  case 25: /* multiplicative_expression: multiplicative_expression PERCENT unary_expression  */
#line 122 "a7_220101113.y"
                                                         { printf("Reduction: multiplicative_expression -> multiplicative_expression PERCENT unary_expression\n"); }
#line 1619 "y.tab.c"
    break;

  case 26: /* unary_operator: AMPERSAND  */
#line 126 "a7_220101113.y"
                { printf("Reduction: unary_operator -> AMPERSAND\n"); }
#line 1625 "y.tab.c"
    break;

  case 27: /* unary_operator: ASTERISK  */
#line 127 "a7_220101113.y"
               { printf("Reduction: unary_operator -> ASTERISK\n"); }
#line 1631 "y.tab.c"
    break;

  case 28: /* unary_operator: PLUS  */
#line 128 "a7_220101113.y"
           { printf("Reduction: unary_operator -> PLUS\n"); }
#line 1637 "y.tab.c"
    break;

  case 29: /* unary_operator: MINUS  */
#line 129 "a7_220101113.y"
            { printf("Reduction: unary_operator -> MINUS\n"); }
#line 1643 "y.tab.c"
    break;

  case 30: /* unary_operator: EXCLAMATION  */
#line 130 "a7_220101113.y"
                  { printf("Reduction: unary_operator -> EXCLAMATION\n"); }
#line 1649 "y.tab.c"
    break;

  case 31: /* unary_operator: INCREMENT  */
#line 131 "a7_220101113.y"
                { printf("Reduction: unary_operator -> INCREMENT\n"); }
#line 1655 "y.tab.c"
    break;

  case 32: /* unary_operator: DECREMENT  */
#line 132 "a7_220101113.y"
                { printf("Reduction: unary_operator -> DECREMENT\n"); }
#line 1661 "y.tab.c"
    break;

  case 33: /* unary_expression: postfix_expression  */
#line 136 "a7_220101113.y"
                         { printf("Reduction: unary_expression -> postfix_expression\n"); }
#line 1667 "y.tab.c"
    break;

  case 34: /* unary_expression: unary_operator unary_expression  */
#line 137 "a7_220101113.y"
                                      { printf("Reduction: unary_expression -> unary_operator unary_expression\n"); }
#line 1673 "y.tab.c"
    break;

  case 35: /* unary_expression: unary_expression INCREMENT  */
#line 138 "a7_220101113.y"
                                { printf("Reduction: unary_expression -> unary_expression INCREMENT\n"); }
#line 1679 "y.tab.c"
    break;

  case 36: /* unary_expression: unary_expression DECREMENT  */
#line 139 "a7_220101113.y"
                                { printf("Reduction: unary_expression -> unary_expression DECREMENT\n"); }
#line 1685 "y.tab.c"
    break;

  case 37: /* argument_expression_list_opt: argument_expression_list  */
#line 143 "a7_220101113.y"
                               { printf("Reduction: argument_expression_list_opt -> argument_expression_list\n"); }
#line 1691 "y.tab.c"
    break;

  case 38: /* argument_expression_list_opt: %empty  */
#line 144 "a7_220101113.y"
                  { printf("Reduction: argument_expression_list_opt -> empty\n"); }
#line 1697 "y.tab.c"
    break;

  case 39: /* argument_expression_list: assignment_expression  */
#line 148 "a7_220101113.y"
                            { printf("Reduction: argument_expression_list -> assignment_expression\n"); }
#line 1703 "y.tab.c"
    break;

  case 40: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 149 "a7_220101113.y"
                                                           { printf("Reduction: argument_expression_list -> argument_expression_list COMMA assignment_expression\n"); }
#line 1709 "y.tab.c"
    break;

  case 41: /* postfix_expression: primary_expression  */
#line 153 "a7_220101113.y"
                         { printf("Reduction: postfix_expression -> primary_expression\n"); }
#line 1715 "y.tab.c"
    break;

  case 42: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 154 "a7_220101113.y"
                                            { printf("Reduction: postfix_expression -> postfix_expression '[' expression ']'\n"); }
#line 1721 "y.tab.c"
    break;

  case 43: /* postfix_expression: postfix_expression LP argument_expression_list_opt RP  */
#line 155 "a7_220101113.y"
                                                            { printf("Reduction: postfix_expression -> postfix_expression LP argument_expression_list_opt RP\n"); }
#line 1727 "y.tab.c"
    break;

  case 44: /* postfix_expression: postfix_expression ARROW IDENTIFIER  */
#line 156 "a7_220101113.y"
                                          { printf("Reduction: postfix_expression -> postfix_expression ARROW IDENTIFIER\n"); }
#line 1733 "y.tab.c"
    break;

  case 45: /* primary_expression: IDENTIFIER  */
#line 160 "a7_220101113.y"
                 {
        printf("Reduction: primary_expression -> IDENTIFIER\n");
        Symbol *s = findSymbol((yyvsp[0].sval), current_scope);

        if (s == NULL) {
            // Check in global scope
            for(int i=current_scope-1;i>=0;i=i-1){
            s = findSymbol((yyvsp[0].sval), i);
            if (s != NULL) {
                break;
            }
            }
          if (s == NULL) {
            printf("Warning: Undeclared identifier %s\n", (yyvsp[0].sval));
        }
        }
    }
#line 1755 "y.tab.c"
    break;

  case 46: /* primary_expression: INTEGER_CONSTANT  */
#line 177 "a7_220101113.y"
                       { printf("Reduction: primary_expression -> INTEGER_CONSTANT\n"); }
#line 1761 "y.tab.c"
    break;

  case 47: /* primary_expression: FLOATING_CONSTANT  */
#line 178 "a7_220101113.y"
                        { printf("Reduction: primary_expression -> FLOATING_CONSTANT\n"); }
#line 1767 "y.tab.c"
    break;

  case 48: /* primary_expression: CHARACTER_CONSTANT  */
#line 179 "a7_220101113.y"
                         { printf("Reduction: primary_expression -> CHARACTER_CONSTANT\n"); }
#line 1773 "y.tab.c"
    break;

  case 49: /* primary_expression: STRING_LITERAL  */
#line 180 "a7_220101113.y"
                     { printf("Reduction: primary_expression -> STRING_LITERAL\n"); }
#line 1779 "y.tab.c"
    break;

  case 50: /* primary_expression: LP expression RP  */
#line 181 "a7_220101113.y"
                       { printf("Reduction: primary_expression -> LP expression RP\n"); }
#line 1785 "y.tab.c"
    break;

  case 51: /* declaration: type_specifier init_declarator SEMICOLON  */
#line 186 "a7_220101113.y"
                                               {
        printf("Reduction: declaration -> type_specifier init_declarator ';'\n");
    }
#line 1793 "y.tab.c"
    break;

  case 52: /* init_declarator: declarator  */
#line 192 "a7_220101113.y"
                 { printf("Reduction: init_declarator -> declarator\n"); }
#line 1799 "y.tab.c"
    break;

  case 53: /* init_declarator: declarator ASSIGN initializer  */
#line 193 "a7_220101113.y"
                                    { printf("Reduction: init_declarator -> declarator ASSIGN initializer\n"); }
#line 1805 "y.tab.c"
    break;

  case 54: /* type_specifier: VOID  */
#line 197 "a7_220101113.y"
           { printf("Reduction: type_specifier -> VOID\n"); }
#line 1811 "y.tab.c"
    break;

  case 55: /* type_specifier: CHAR  */
#line 198 "a7_220101113.y"
           { printf("Reduction: type_specifier -> CHAR\n"); }
#line 1817 "y.tab.c"
    break;

  case 56: /* type_specifier: INTEGER  */
#line 199 "a7_220101113.y"
              { printf("Reduction: type_specifier -> INTEGER\n"); }
#line 1823 "y.tab.c"
    break;

  case 57: /* type_specifier: FLOAT  */
#line 200 "a7_220101113.y"
            { printf("Reduction: type_specifier -> FLOAT\n"); }
#line 1829 "y.tab.c"
    break;

  case 58: /* type_specifier: BOOL  */
#line 201 "a7_220101113.y"
           { printf("Reduction: type_specifier -> BOOL\n"); }
#line 1835 "y.tab.c"
    break;

  case 59: /* declarator: pointer_opt direct_declarator  */
#line 205 "a7_220101113.y"
                                    { printf("Reduction: declarator -> pointer_opt direct_declarator\n"); }
#line 1841 "y.tab.c"
    break;

  case 60: /* pointer_opt: pointer  */
#line 209 "a7_220101113.y"
              { printf("Reduction: pointer_opt -> pointer\n"); }
#line 1847 "y.tab.c"
    break;

  case 61: /* pointer_opt: %empty  */
#line 210 "a7_220101113.y"
                  { printf("Reduction: pointer_opt -> empty\n"); }
#line 1853 "y.tab.c"
    break;

  case 62: /* direct_declarator: IDENTIFIER  */
#line 214 "a7_220101113.y"
                 {
        printf("Reduction: direct_declarator -> IDENTIFIER\n");
        addSymbol((yyvsp[0].sval), "identifier", current_scope);
    }
#line 1862 "y.tab.c"
    break;

  case 63: /* direct_declarator: IDENTIFIER '[' INTEGER_CONSTANT ']'  */
#line 218 "a7_220101113.y"
                                          {
        printf("Reduction: direct_declarator -> IDENTIFIER '[' INTEGER_CONSTANT ']'\n");
        addSymbol((yyvsp[-3].sval), "array", current_scope);
    }
#line 1871 "y.tab.c"
    break;

  case 64: /* direct_declarator: IDENTIFIER LP parameter_list_opt RP  */
#line 222 "a7_220101113.y"
                                          {
        printf("Reduction: direct_declarator -> IDENTIFIER LP parameter_list_opt RP\n");
        addSymbol((yyvsp[-3].sval), "function", current_scope);
    }
#line 1880 "y.tab.c"
    break;

  case 65: /* pointer: ASTERISK  */
#line 229 "a7_220101113.y"
               { printf("Reduction: pointer -> ASTERISK\n"); }
#line 1886 "y.tab.c"
    break;

  case 66: /* parameter_list_opt: parameter_list  */
#line 233 "a7_220101113.y"
                     { printf("Reduction: parameter_list_opt -> parameter_list\n"); }
#line 1892 "y.tab.c"
    break;

  case 67: /* parameter_list_opt: %empty  */
#line 234 "a7_220101113.y"
                  { printf("Reduction: parameter_list_opt -> empty\n"); }
#line 1898 "y.tab.c"
    break;

  case 68: /* parameter_list: parameter_declaration  */
#line 238 "a7_220101113.y"
                            { printf("Reduction: parameter_list -> parameter_declaration\n"); }
#line 1904 "y.tab.c"
    break;

  case 69: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 239 "a7_220101113.y"
                                                 { printf("Reduction: parameter_list -> parameter_list COMMA parameter_declaration\n"); }
#line 1910 "y.tab.c"
    break;

  case 70: /* parameter_declaration: type_specifier pointer_opt IDENTIFIER  */
#line 243 "a7_220101113.y"
                                            {
        printf("Reduction: parameter_declaration -> type_specifier pointer_opt IDENTIFIER\n");
        addSymbol((yyvsp[0].sval), "parameter", current_scope);
    }
#line 1919 "y.tab.c"
    break;

  case 71: /* parameter_declaration: type_specifier pointer_opt  */
#line 247 "a7_220101113.y"
                                 {
        printf("Reduction: parameter_declaration -> type_specifier pointer_opt\n");
    }
#line 1927 "y.tab.c"
    break;

  case 72: /* initializer: assignment_expression  */
#line 253 "a7_220101113.y"
                            { printf("Reduction: initializer -> assignment_expression\n"); }
#line 1933 "y.tab.c"
    break;

  case 73: /* statement: compound_statement  */
#line 258 "a7_220101113.y"
                         { printf("Reduction: statement -> compound_statement\n"); }
#line 1939 "y.tab.c"
    break;

  case 74: /* statement: expression_statement  */
#line 259 "a7_220101113.y"
                           { printf("Reduction: statement -> expression_statement\n"); }
#line 1945 "y.tab.c"
    break;

  case 75: /* statement: selection_statement  */
#line 260 "a7_220101113.y"
                          { printf("Reduction: statement -> selection_statement\n"); }
#line 1951 "y.tab.c"
    break;

  case 76: /* statement: iteration_statement  */
#line 261 "a7_220101113.y"
                          { printf("Reduction: statement -> iteration_statement\n"); }
#line 1957 "y.tab.c"
    break;

  case 77: /* statement: jump_statement  */
#line 262 "a7_220101113.y"
                     { printf("Reduction: statement -> jump_statement\n"); }
#line 1963 "y.tab.c"
    break;

  case 78: /* $@1: %empty  */
#line 267 "a7_220101113.y"
               { current_scope++; }
#line 1969 "y.tab.c"
    break;

  case 79: /* compound_statement: MC_BEGIN $@1 block_item_list_opt END  */
#line 267 "a7_220101113.y"
                                                            {
        printf("Reduction: compound_statement -> MC_BEGIN block_item_list_opt END\n");
        current_scope--;
    }
#line 1978 "y.tab.c"
    break;

  case 80: /* block_item_list_opt: block_item_list  */
#line 274 "a7_220101113.y"
                      { printf("Reduction: block_item_list_opt -> block_item_list\n"); }
#line 1984 "y.tab.c"
    break;

  case 81: /* block_item_list_opt: %empty  */
#line 275 "a7_220101113.y"
                  { printf("Reduction: block_item_list_opt -> empty\n"); }
#line 1990 "y.tab.c"
    break;

  case 82: /* block_item_list: block_item  */
#line 279 "a7_220101113.y"
                 { printf("Reduction: block_item_list -> block_item\n"); }
#line 1996 "y.tab.c"
    break;

  case 83: /* block_item_list: block_item_list block_item  */
#line 280 "a7_220101113.y"
                                 { printf("Reduction: block_item_list -> block_item_list block_item\n"); }
#line 2002 "y.tab.c"
    break;

  case 84: /* block_item: declaration  */
#line 284 "a7_220101113.y"
                  { printf("Reduction: block_item -> declaration\n"); }
#line 2008 "y.tab.c"
    break;

  case 85: /* block_item: statement  */
#line 285 "a7_220101113.y"
                { printf("Reduction: block_item -> statement\n"); }
#line 2014 "y.tab.c"
    break;

  case 86: /* expression_statement: expression_opt SEMICOLON  */
#line 289 "a7_220101113.y"
                               { printf("Reduction: expression_statement -> expression_opt ';'\n"); }
#line 2020 "y.tab.c"
    break;

  case 87: /* expression_opt: expression  */
#line 293 "a7_220101113.y"
                 { printf("Reduction: expression_opt -> expression\n"); }
#line 2026 "y.tab.c"
    break;

  case 88: /* expression_opt: %empty  */
#line 294 "a7_220101113.y"
                  { printf("Reduction: expression_opt -> empty\n"); }
#line 2032 "y.tab.c"
    break;

  case 89: /* selection_statement: IF LP expression RP statement  */
#line 298 "a7_220101113.y"
                                    {
        printf("Reduction: selection_statement -> IF LP expression RP statement\n");
    }
#line 2040 "y.tab.c"
    break;

  case 90: /* selection_statement: IF LP expression RP statement ELSE statement  */
#line 301 "a7_220101113.y"
                                                   {
        printf("Reduction: selection_statement -> IF LP expression RP statement ELSE statement\n");
    }
#line 2048 "y.tab.c"
    break;

  case 91: /* iteration_statement: FOR LP expression_opt SEMICOLON expression_opt SEMICOLON expression_opt RP statement  */
#line 307 "a7_220101113.y"
                                                                                           {
        printf("Reduction: iteration_statement -> FOR LP expression_opt ';' expression_opt ';' expression_opt RP statement\n");
    }
#line 2056 "y.tab.c"
    break;

  case 92: /* iteration_statement: FOR LP declaration expression_opt SEMICOLON expression_opt RP statement  */
#line 310 "a7_220101113.y"
                                                                              {
        printf("Reduction: iteration_statement -> FOR LP expression_opt ';' expression_opt ';' expression_opt RP statement\n");
    }
#line 2064 "y.tab.c"
    break;

  case 93: /* jump_statement: RETURN expression_opt SEMICOLON  */
#line 316 "a7_220101113.y"
                                      { printf("Reduction: jump_statement -> RETURN expression_opt ';'\n"); }
#line 2070 "y.tab.c"
    break;

  case 94: /* translation_unit: function_definition  */
#line 321 "a7_220101113.y"
                          { printf("Reduction: translation_unit -> function_definition\n"); }
#line 2076 "y.tab.c"
    break;

  case 95: /* translation_unit: declaration  */
#line 322 "a7_220101113.y"
                  { printf("Reduction: translation_unit -> declaration\n"); }
#line 2082 "y.tab.c"
    break;

  case 96: /* translation_unit: expression  */
#line 323 "a7_220101113.y"
                 { printf("Reduction: translation_unit -> expression\n"); }
#line 2088 "y.tab.c"
    break;

  case 97: /* translation_unit: translation_unit function_definition  */
#line 324 "a7_220101113.y"
                                           { printf("Reduction: translation_unit -> translation_unit function_definition\n"); }
#line 2094 "y.tab.c"
    break;

  case 98: /* translation_unit: translation_unit declaration  */
#line 325 "a7_220101113.y"
                                   { printf("Reduction: translation_unit -> translation_unit declaration\n"); }
#line 2100 "y.tab.c"
    break;

  case 102: /* function_definition: type_specifier function_declarator compound_statement  */
#line 332 "a7_220101113.y"
                                                            {
        printf("Reduction: function_definition -> type_specifier function_declarator compound_statement\n");
    }
#line 2108 "y.tab.c"
    break;

  case 103: /* function_declarator: pointer_opt IDENTIFIER LP parameter_list_opt RP  */
#line 341 "a7_220101113.y"
                                                      {
        printf("Reduction: function_declarator -> pointer_opt IDENTIFIER LP parameter_list_opt RP\n");
        addSymbol((yyvsp[-3].sval), "function", current_scope);
    }
#line 2117 "y.tab.c"
    break;


#line 2121 "y.tab.c"

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

#line 347 "a7_220101113.y"


/* Function to add symbol */
void addSymbol(char *name, char *type, int scope) {
    Symbol *s = (Symbol *)malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->type = strdup(type);
    s->scope = scope;
    s->next = symbolTable;
    symbolTable = s;
}

/* Function to find symbol */
Symbol *findSymbol(char *name, int scope) {
    Symbol *s = symbolTable;
    while (s) {
        if (strcmp(s->name, name) == 0 && s->scope == scope) {
            return s;
        }
        s = s->next;
    }
    return NULL;
}

/* Function to print symbol table */
void printSymbolTable() {
    Symbol *s = symbolTable;
    printf("Symbol Table:\n");
    while (s) {
        printf("Name: %s, Type: %s, Scope: %d\n", s->name, s->type, s->scope);
        s = s->next;
    }
}

/* Error handling function */
void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

/* Main function */
int main() {
    printf("Parsing micro C code...\n");
    yyparse();
    printSymbolTable();
    return 0;
}
