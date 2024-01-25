/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20220114

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
    #include <stdio.h>
    #include <stdlib.h>		
	#include "AST.h"
    #include "SemanticAnalyser.h"	
	#include "y.tab.h"
    
    /* Prototypes*/
	int yylex();
	void yyerror(const char*);
	int getLineNumber(void);
    int checkSemantic(AST *);
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 48 "parser.y"
typedef union YYSTYPE {
	struct SymbolTableNode *symbol;
    struct AST *astNod;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 48 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_CHAR 257
#define KW_INT 258
#define KW_FLOAT 259
#define KW_CODE 260
#define KW_IF 261
#define KW_ELSE 262
#define KW_WHILE 263
#define KW_INPUT 264
#define KW_PRINT 265
#define KW_RETURN 266
#define OPERATOR_LE 267
#define OPERATOR_GE 268
#define OPERATOR_EQ 269
#define OPERATOR_DIF 270
#define TOKEN_ERROR 271
#define TK_IDENTIFIER 272
#define LIT_INT 273
#define LIT_REAL 274
#define LIT_CHAR 275
#define LIT_STRING 276
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    1,    1,    2,    2,    2,    2,    3,    4,
    4,    4,    5,    5,    5,    5,    5,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    6,    6,    7,    7,    7,    7,    8,    8,    8,    9,
    9,   10,   11,   11,   11,   11,   11,   11,   11,   11,
   11,   11,   12,   12,   13,   13,
};
static const YYINT yylen[] = {                            2,
    2,    1,    1,    2,    5,    6,    7,    6,    2,    1,
    3,    0,    1,    1,    4,    4,    4,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    1,    2,    1,    1,    1,    1,    1,    1,    1,    1,
    2,    3,    2,    1,    3,    4,    7,    5,    7,    5,
    3,    3,    1,    2,    1,    3,
};
static const YYINT yydefred[] = {                         0,
   38,   37,   39,    0,    0,    0,    0,    0,    1,    0,
    4,    0,    0,   41,    0,    0,    0,    0,    0,    0,
    0,    0,   44,    0,   42,    0,    0,   33,   35,   34,
   36,    0,    0,   13,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   43,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    5,    0,    0,    0,    9,    0,    0,
   51,   52,    0,    0,   54,   45,    0,    0,    0,    0,
   18,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   25,   26,    6,    0,    0,   11,    8,    0,    0,
   46,    0,   17,   15,    0,   16,    7,   32,    0,   50,
    0,   56,    0,    0,   49,   47,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  257,  258,  259,  278,  279,  280,  286,  260,  287,  288,
  279,  272,  272,  287,   61,   91,   40,  261,  263,  265,
  266,  272,   59,  123,  289,  264,  272,  273,  274,  275,
  276,   40,  283,  285,  285,  281,  282,  286,   40,   40,
  283,  283,   61,   91,  125,  289,  290,   40,   91,   40,
  283,  267,  268,  269,  270,  124,   38,   60,   62,   43,
   45,   42,   47,   59,   93,   44,   41,  272,  283,  283,
   59,   59,  283,  283,  290,  125,  286,  283,  283,  291,
   41,  283,  283,  283,  283,  283,  283,  283,  283,  283,
  283,  283,  283,   59,  284,  285,  282,   59,   41,   41,
   59,   93,   41,   93,   44,   41,   59,  284,  289,  289,
   61,  291,  262,  283,  289,   59,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          4,
    5,    6,   36,   37,   79,   95,   34,    7,    9,   10,
   46,   47,   80,
};
static const YYINT yysindex[] = {                      -211,
    0,    0,    0,    0, -251, -211, -247, -246,    0, -251,
    0,  -16,  243,    0,  -40, -115, -211,   11,   13,  -40,
  -40,  -55,    0,  222,    0,   15,  -33,    0,    0,    0,
    0,  -40,   19,    0,  -51,   -1,   32, -216,  -40,  -40,
   27,   50,  -40,  -40,    0,  243,  -57, -211,  -40,  -40,
   58,  -40,  -40,  -40,  -40,  -40,  -40,  -40,  -40,  -40,
  -40,  -40,  -40,    0,  -32, -211,   17,    0,   87,   95,
    0,    0,  103,  128,    0,    0,   36,  156,  261,   39,
    0,   74,   74,   74,   74,  299,  150,   74,   74,   -3,
   -3,    0,    0,    0,   23, -115,    0,    0,  243,  243,
    0,   45,    0,    0,  -40,    0,    0,    0, -178,    0,
  -40,    0,  243,  291,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,  107,    3,    0,    0,    0,  108,
    0,    0,    0,    0,    0,    0,   70,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -30,    0,    0,    0,
    0,    0,    0,    0,    0,   72,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   -2,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   70,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   81,    0,
    0,  340,  345,  349,  372,  -39,  412,  399,  408,  -22,
  -10,    0,    0,    0,    0,   56,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    1,    0,
    0,    0,    0,    0,    0,    0,
};
#if YYBTYACC
static const YYINT yycindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
  121,    0,    0,   65,  532,   43,    2,   -7,  125,    0,
   -9,   98,   47,
};
#define YYTABLESIZE 678
static const YYINT yytable[] = {                         32,
   48,   30,    3,   25,   30,   43,   50,   14,    8,   38,
   14,   14,   14,   14,   14,   23,   14,   35,   23,   30,
   23,   23,   23,   17,   12,   13,   94,   24,   14,   14,
   24,   14,   24,   24,   24,   44,   23,   23,   62,   23,
   77,   65,   66,   63,   15,    1,    2,    3,   24,   24,
   39,   24,   40,   30,   48,   68,   57,   49,   38,   48,
   62,   60,   14,   61,   57,   63,   96,   76,   62,   60,
   23,   61,   67,   63,   16,   98,  103,   64,   58,  106,
   59,  107,   24,  113,   30,   71,   58,   57,   59,  109,
  110,   62,   60,   14,   61,   57,   63,   96,   81,   62,
   60,   23,   61,  115,   63,  111,    2,   40,   72,   58,
   12,   59,   10,   24,   31,   62,   60,   58,   61,   59,
   63,   55,   53,   48,   57,   48,   11,   99,   62,   60,
   97,   61,   57,   63,   14,  100,   62,   60,  108,   61,
   57,   63,   56,   75,   62,   60,   58,   61,   59,   63,
   56,  112,    0,    0,   58,    0,   59,   28,   29,   30,
   31,  101,   58,    0,   59,   57,    0,    0,    0,   62,
   60,    0,   61,   56,   63,    0,    0,    0,    0,    0,
    0,   56,    0,    0,    0,    0,    0,   58,    0,   59,
    0,   62,   60,   57,   61,    0,   63,   62,   60,    0,
   61,    0,   63,    0,    0,    0,    0,    0,    0,   58,
   56,   59,    0,    0,    0,   58,    0,   59,   56,    0,
  102,    0,    0,   26,    0,    0,   56,    0,    0,    0,
    0,   27,   28,   29,   30,   31,   14,   14,   14,   14,
   28,   29,   30,   31,   23,   23,   23,   23,  104,    0,
    0,   56,    0,    0,    0,    0,   24,   24,   24,   24,
   48,   48,    3,   48,    0,   48,   48,    0,    0,    0,
    0,    0,   48,    0,    0,    0,    0,    0,    0,   56,
   23,    0,    0,    0,    0,   52,   53,   54,   55,    0,
    0,    0,    0,   52,   53,   54,   55,    0,   57,    0,
    0,   23,   62,   60,  105,   61,    0,   63,    0,    0,
    0,    0,    0,    0,    0,    0,   52,   53,   54,   55,
   58,    0,   59,    0,   52,   53,   54,   55,   57,    0,
    0,    0,   62,   60,    0,   61,   57,   63,    0,    0,
   62,   60,    0,   61,   24,   63,   45,    0,    0,  116,
   58,    0,   59,   52,   53,   54,   55,    0,   58,    0,
   59,   52,   53,   54,   55,   24,    0,    0,    0,   52,
   53,   54,   55,    0,    0,    0,    0,   19,    0,    0,
   19,    0,   20,   19,   56,   20,   21,    0,   20,   21,
    0,    0,   21,    0,   52,   53,   54,   55,   19,   19,
    0,   19,    0,   20,   20,    0,   20,   21,   21,   22,
   21,    0,   22,    0,   56,   22,   52,   53,   54,   55,
    0,    0,   52,   53,   54,   55,    0,    0,    0,    0,
   22,   22,   19,   22,    0,    0,   28,   20,    0,   28,
    0,   21,   28,    0,    0,   29,    0,    0,   29,   27,
    0,   29,   27,    0,    0,   27,    0,   28,   28,    0,
   28,    0,    0,   19,   22,    0,   29,   29,   20,   29,
   27,    0,   21,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   18,    0,   19,    0,   20,   21,    0,    0,
    0,   28,    0,   22,    0,   22,    0,    0,    0,    0,
   29,    0,    0,   18,   27,   19,    0,   20,   21,    0,
    0,    0,    0,    0,   22,    0,    0,    0,    0,    0,
    0,    0,   28,    0,    0,    0,    0,   52,   53,   54,
   55,   29,    0,    0,    0,   27,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   33,    0,    0,    0,
    0,   41,   42,    0,    0,    0,    0,   52,   53,   54,
   55,    0,    0,   51,    0,   52,   53,   54,   55,    0,
   69,   70,    0,    0,   73,   74,    0,    0,    0,    0,
   78,    0,    0,   82,   83,   84,   85,   86,   87,   88,
   89,   90,   91,   92,   93,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   19,   19,   19,   19,
    0,   20,   20,   20,   20,   21,   21,   21,   21,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   22,   22,
   22,   22,  114,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   28,   28,   28,   28,    0,
    0,    0,    0,    0,   29,   29,   29,   29,
};
static const YYINT yycheck[] = {                         40,
    0,   41,    0,   13,   44,   61,   40,   38,  260,   17,
   41,   42,   43,   44,   45,   38,   47,   16,   41,   59,
   43,   44,   45,   40,  272,  272,   59,   38,   59,   60,
   41,   62,   43,   44,   45,   91,   59,   60,   42,   62,
   48,   93,   44,   47,   61,  257,  258,  259,   59,   60,
   40,   62,   40,   93,   40,  272,   38,   91,   66,   59,
   42,   43,   93,   45,   38,   47,   65,  125,   42,   43,
   93,   45,   41,   47,   91,   59,   41,   59,   60,   41,
   62,   59,   93,  262,  124,   59,   60,   38,   62,   99,
  100,   42,   43,  124,   45,   38,   47,   96,   41,   42,
   43,  124,   45,  113,   47,   61,    0,    0,   59,   60,
   41,   62,   41,  124,   59,   42,   43,   60,   45,   62,
   47,   41,  125,  123,   38,  125,    6,   41,   42,   43,
   66,   45,   38,   47,   10,   41,   42,   43,   96,   45,
   38,   47,  124,   46,   42,   43,   60,   45,   62,   47,
  124,  105,   -1,   -1,   60,   -1,   62,  273,  274,  275,
  276,   59,   60,   -1,   62,   38,   -1,   -1,   -1,   42,
   43,   -1,   45,  124,   47,   -1,   -1,   -1,   -1,   -1,
   -1,  124,   -1,   -1,   -1,   -1,   -1,   60,   -1,   62,
   -1,   42,   43,   38,   45,   -1,   47,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,   60,
  124,   62,   -1,   -1,   -1,   60,   -1,   62,  124,   -1,
   93,   -1,   -1,  264,   -1,   -1,  124,   -1,   -1,   -1,
   -1,  272,  273,  274,  275,  276,  267,  268,  269,  270,
  273,  274,  275,  276,  267,  268,  269,  270,   93,   -1,
   -1,  124,   -1,   -1,   -1,   -1,  267,  268,  269,  270,
  260,  261,  260,  263,   -1,  265,  266,   -1,   -1,   -1,
   -1,   -1,  272,   -1,   -1,   -1,   -1,   -1,   -1,  124,
   59,   -1,   -1,   -1,   -1,  267,  268,  269,  270,   -1,
   -1,   -1,   -1,  267,  268,  269,  270,   -1,   38,   -1,
   -1,   59,   42,   43,   44,   45,   -1,   47,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  267,  268,  269,  270,
   60,   -1,   62,   -1,  267,  268,  269,  270,   38,   -1,
   -1,   -1,   42,   43,   -1,   45,   38,   47,   -1,   -1,
   42,   43,   -1,   45,  123,   47,  125,   -1,   -1,   59,
   60,   -1,   62,  267,  268,  269,  270,   -1,   60,   -1,
   62,  267,  268,  269,  270,  123,   -1,   -1,   -1,  267,
  268,  269,  270,   -1,   -1,   -1,   -1,   38,   -1,   -1,
   41,   -1,   38,   44,  124,   41,   38,   -1,   44,   41,
   -1,   -1,   44,   -1,  267,  268,  269,  270,   59,   60,
   -1,   62,   -1,   59,   60,   -1,   62,   59,   60,   38,
   62,   -1,   41,   -1,  124,   44,  267,  268,  269,  270,
   -1,   -1,  267,  268,  269,  270,   -1,   -1,   -1,   -1,
   59,   60,   93,   62,   -1,   -1,   38,   93,   -1,   41,
   -1,   93,   44,   -1,   -1,   38,   -1,   -1,   41,   38,
   -1,   44,   41,   -1,   -1,   44,   -1,   59,   60,   -1,
   62,   -1,   -1,  124,   93,   -1,   59,   60,  124,   62,
   59,   -1,  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  261,   -1,  263,   -1,  265,  266,   -1,   -1,
   -1,   93,   -1,  272,   -1,  124,   -1,   -1,   -1,   -1,
   93,   -1,   -1,  261,   93,  263,   -1,  265,  266,   -1,
   -1,   -1,   -1,   -1,  272,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  124,   -1,   -1,   -1,   -1,  267,  268,  269,
  270,  124,   -1,   -1,   -1,  124,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   15,   -1,   -1,   -1,
   -1,   20,   21,   -1,   -1,   -1,   -1,  267,  268,  269,
  270,   -1,   -1,   32,   -1,  267,  268,  269,  270,   -1,
   39,   40,   -1,   -1,   43,   44,   -1,   -1,   -1,   -1,
   49,   -1,   -1,   52,   53,   54,   55,   56,   57,   58,
   59,   60,   61,   62,   63,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  267,  268,  269,  270,
   -1,  267,  268,  269,  270,  267,  268,  269,  270,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  267,  268,
  269,  270,  111,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  267,  268,  269,  270,   -1,
   -1,   -1,   -1,   -1,  267,  268,  269,  270,
};
#if YYBTYACC
static const YYINT yyctable[] = {                        -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 276
#define YYUNDFTOKEN 292
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"$end",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",
"'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"error","KW_CHAR","KW_INT","KW_FLOAT",
"KW_CODE","KW_IF","KW_ELSE","KW_WHILE","KW_INPUT","KW_PRINT","KW_RETURN",
"OPERATOR_LE","OPERATOR_GE","OPERATOR_EQ","OPERATOR_DIF","TOKEN_ERROR",
"TK_IDENTIFIER","LIT_INT","LIT_REAL","LIT_CHAR","LIT_STRING","$accept",
"program","declarationsList","declaration","formalParameter",
"formalParameterList","expression","literalsList","literal","dataType",
"codeImplementationList","codeImplementation","cmd","cmdList","argumentsList",
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : declarationsList codeImplementationList",
"program : declarationsList",
"declarationsList : declaration",
"declarationsList : declaration declarationsList",
"declaration : dataType TK_IDENTIFIER '=' expression ';'",
"declaration : dataType TK_IDENTIFIER '[' literal ']' ';'",
"declaration : dataType TK_IDENTIFIER '[' literal ']' literalsList ';'",
"declaration : dataType TK_IDENTIFIER '(' formalParameterList ')' ';'",
"formalParameter : dataType TK_IDENTIFIER",
"formalParameterList : formalParameter",
"formalParameterList : formalParameter ',' formalParameterList",
"formalParameterList :",
"expression : literal",
"expression : TK_IDENTIFIER",
"expression : TK_IDENTIFIER '[' expression ']'",
"expression : TK_IDENTIFIER '(' argumentsList ')'",
"expression : KW_INPUT '(' dataType ')'",
"expression : '(' expression ')'",
"expression : expression OPERATOR_LE expression",
"expression : expression OPERATOR_GE expression",
"expression : expression OPERATOR_EQ expression",
"expression : expression OPERATOR_DIF expression",
"expression : expression '+' expression",
"expression : expression '-' expression",
"expression : expression '*' expression",
"expression : expression '/' expression",
"expression : expression '&' expression",
"expression : expression '<' expression",
"expression : expression '>' expression",
"expression : expression '|' expression",
"literalsList : literal",
"literalsList : literal literalsList",
"literal : LIT_INT",
"literal : LIT_CHAR",
"literal : LIT_REAL",
"literal : LIT_STRING",
"dataType : KW_INT",
"dataType : KW_CHAR",
"dataType : KW_FLOAT",
"codeImplementationList : codeImplementation",
"codeImplementationList : codeImplementation codeImplementationList",
"codeImplementation : KW_CODE TK_IDENTIFIER cmd",
"cmd : '{' '}'",
"cmd : ';'",
"cmd : '{' cmdList '}'",
"cmd : TK_IDENTIFIER '=' expression ';'",
"cmd : TK_IDENTIFIER '[' expression ']' '=' expression ';'",
"cmd : KW_IF '(' expression ')' cmd",
"cmd : KW_IF '(' expression ')' cmd KW_ELSE cmd",
"cmd : KW_WHILE '(' expression ')' cmd",
"cmd : KW_PRINT expression ';'",
"cmd : KW_RETURN expression ';'",
"cmdList : cmd",
"cmdList : cmd cmdList",
"argumentsList : expression",
"argumentsList : expression ',' argumentsList",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
YYLTYPE  yyloc; /* position returned by actions */
YYLTYPE  yylloc; /* position from the lexer */
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
/* variables for the parser stack */
static YYSTACKDATA yystack;
#if YYBTYACC

/* Current parser state */
static YYParseState *yyps = 0;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = 0;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = 0;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = 0;

/* End position of lexical value queue */
static YYSTYPE *yylve = 0;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = 0;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = 0;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = 0;

/* End position of lexical position queue */
static YYLTYPE *yylpe = 0;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = 0;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = 0;

static YYINT  *yylexemes = 0;
#endif /* YYBTYACC */
#line 141 "parser.y"

void yyerror(const char *wrongSentence){
	printf("Error (l.%d): %s\n", getLineNumber(), wrongSentence);
	
    exit(3);
}
#line 640 "y.tab.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

#if YYBTYACC
    yyps = yyNewState(0); if (yyps == 0) goto yyenomem;
    yyps->save = 0;
#endif /* YYBTYACC */
    yym = 0;
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 1:
#line 54 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_FULL_PROG, yystack.l_mark[-1].astNod, yystack.l_mark[0].astNod); astPrint(yyval.astNod, 0); setGlobalAST(yyval.astNod); checkSemantic(yyval.astNod);}
#line 1313 "y.tab.c"
break;
case 2:
#line 55 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_HEADER, yystack.l_mark[0].astNod); astPrint(yyval.astNod, 0); setGlobalAST(yyval.astNod);}
#line 1318 "y.tab.c"
break;
case 3:
#line 59 "parser.y"
	{yyval.astNod = yystack.l_mark[0].astNod;}
#line 1323 "y.tab.c"
break;
case 4:
#line 60 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_DECLARATION_LIST, yystack.l_mark[-1].astNod, yystack.l_mark[0].astNod);}
#line 1328 "y.tab.c"
break;
case 5:
#line 63 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[-3].symbol, AST_VAR_DECLARATION, yystack.l_mark[-4].astNod, yystack.l_mark[-1].astNod); specifyIdentifierType(yyval.astNod, AST_VAR_DECLARATION);}
#line 1333 "y.tab.c"
break;
case 6:
#line 64 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[-4].symbol, AST_ARRAY_DECLARATION, yystack.l_mark[-5].astNod, yystack.l_mark[-2].astNod); specifyIdentifierType(yyval.astNod, AST_ARRAY_DECLARATION);}
#line 1338 "y.tab.c"
break;
case 7:
#line 65 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[-5].symbol, AST_ARRAY_DEC_AND_INIT, yystack.l_mark[-6].astNod, yystack.l_mark[-3].astNod, yystack.l_mark[-1].astNod);}
#line 1343 "y.tab.c"
break;
case 8:
#line 66 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[-4].symbol, AST_FUNCTION_DECLARATION, yystack.l_mark[-5].astNod, yystack.l_mark[-2].astNod); specifyIdentifierType(yyval.astNod, AST_FUNCTION_DECLARATION);}
#line 1348 "y.tab.c"
break;
case 9:
#line 69 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[0].symbol, AST_PARAM, yystack.l_mark[-1].astNod);}
#line 1353 "y.tab.c"
break;
case 10:
#line 72 "parser.y"
	{yyval.astNod = yystack.l_mark[0].astNod;}
#line 1358 "y.tab.c"
break;
case 11:
#line 73 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_PARAM_LIST, yystack.l_mark[-2].astNod, yystack.l_mark[0].astNod);}
#line 1363 "y.tab.c"
break;
case 12:
#line 74 "parser.y"
	{yyval.astNod = NULL;}
#line 1368 "y.tab.c"
break;
case 13:
#line 77 "parser.y"
	{yyval.astNod=yystack.l_mark[0].astNod;}
#line 1373 "y.tab.c"
break;
case 14:
#line 78 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[0].symbol, AST_SYMBOL);}
#line 1378 "y.tab.c"
break;
case 15:
#line 79 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[-3].symbol, AST_ARRAY_EXPR, yystack.l_mark[-1].astNod);}
#line 1383 "y.tab.c"
break;
case 16:
#line 80 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[-3].symbol, AST_FUNCTION_CALLING, yystack.l_mark[-1].astNod);}
#line 1388 "y.tab.c"
break;
case 17:
#line 81 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_INPUT, yystack.l_mark[-1].astNod);}
#line 1393 "y.tab.c"
break;
case 18:
#line 82 "parser.y"
	{yyval.astNod=yystack.l_mark[-1].astNod;}
#line 1398 "y.tab.c"
break;
case 19:
#line 83 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_OPERATOR_LE,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1403 "y.tab.c"
break;
case 20:
#line 84 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_OPERATOR_GE,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1408 "y.tab.c"
break;
case 21:
#line 85 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_OPERATOR_EQ,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1413 "y.tab.c"
break;
case 22:
#line 86 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_OPERATOR_DIF,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1418 "y.tab.c"
break;
case 23:
#line 87 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_ADD,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1423 "y.tab.c"
break;
case 24:
#line 88 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_SUB,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1428 "y.tab.c"
break;
case 25:
#line 89 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_MUL,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1433 "y.tab.c"
break;
case 26:
#line 90 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_DIV,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1438 "y.tab.c"
break;
case 27:
#line 91 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_AND,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1443 "y.tab.c"
break;
case 28:
#line 92 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_LESS_THAN,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1448 "y.tab.c"
break;
case 29:
#line 93 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_GREATER_THAN,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1453 "y.tab.c"
break;
case 30:
#line 94 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_OR,yystack.l_mark[-2].astNod,yystack.l_mark[0].astNod);}
#line 1458 "y.tab.c"
break;
case 31:
#line 97 "parser.y"
	{yyval.astNod = yystack.l_mark[0].astNod;}
#line 1463 "y.tab.c"
break;
case 32:
#line 98 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_LITERAL_LIST, yystack.l_mark[-1].astNod, yystack.l_mark[0].astNod);}
#line 1468 "y.tab.c"
break;
case 33:
#line 101 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[0].symbol, AST_SYMBOL);}
#line 1473 "y.tab.c"
break;
case 34:
#line 102 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[0].symbol, AST_SYMBOL);}
#line 1478 "y.tab.c"
break;
case 35:
#line 103 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[0].symbol, AST_SYMBOL);}
#line 1483 "y.tab.c"
break;
case 36:
#line 104 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[0].symbol, AST_SYMBOL);}
#line 1488 "y.tab.c"
break;
case 37:
#line 107 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_INT);}
#line 1493 "y.tab.c"
break;
case 38:
#line 108 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_CHAR);}
#line 1498 "y.tab.c"
break;
case 39:
#line 109 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_FLOAT);}
#line 1503 "y.tab.c"
break;
case 40:
#line 113 "parser.y"
	{yyval.astNod = yystack.l_mark[0].astNod;}
#line 1508 "y.tab.c"
break;
case 41:
#line 114 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_FUNCTION_IMPLEMENTATION_LIST, yystack.l_mark[-1].astNod, yystack.l_mark[0].astNod);}
#line 1513 "y.tab.c"
break;
case 42:
#line 117 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[-1].symbol, AST_FUNCTION_IMPLEMENTATION, yystack.l_mark[0].astNod);}
#line 1518 "y.tab.c"
break;
case 43:
#line 120 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_CMD_BLOCK, NULL);}
#line 1523 "y.tab.c"
break;
case 44:
#line 121 "parser.y"
	{yyval.astNod = NULL;}
#line 1528 "y.tab.c"
break;
case 45:
#line 122 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_CMD_BLOCK, yystack.l_mark[-1].astNod);}
#line 1533 "y.tab.c"
break;
case 46:
#line 123 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[-3].symbol, AST_ASSIGNMENT, yystack.l_mark[-1].astNod);}
#line 1538 "y.tab.c"
break;
case 47:
#line 124 "parser.y"
	{yyval.astNod = astCreate(yystack.l_mark[-6].symbol, AST_ARRAY_ASSIGN, yystack.l_mark[-4].astNod, yystack.l_mark[-1].astNod);}
#line 1543 "y.tab.c"
break;
case 48:
#line 125 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_IF_THEN, yystack.l_mark[-2].astNod, yystack.l_mark[0].astNod);}
#line 1548 "y.tab.c"
break;
case 49:
#line 126 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_IF_THEN_ELSE, yystack.l_mark[-4].astNod, yystack.l_mark[-2].astNod, yystack.l_mark[0].astNod);}
#line 1553 "y.tab.c"
break;
case 50:
#line 127 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_WHILE, yystack.l_mark[-2].astNod, yystack.l_mark[0].astNod);}
#line 1558 "y.tab.c"
break;
case 51:
#line 128 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_PRINT, yystack.l_mark[-1].astNod);}
#line 1563 "y.tab.c"
break;
case 52:
#line 129 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_RETURN, yystack.l_mark[-1].astNod);}
#line 1568 "y.tab.c"
break;
case 53:
#line 132 "parser.y"
	{yyval.astNod = yystack.l_mark[0].astNod;}
#line 1573 "y.tab.c"
break;
case 54:
#line 133 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_CMD_LIST, yystack.l_mark[-1].astNod, yystack.l_mark[0].astNod);}
#line 1578 "y.tab.c"
break;
case 55:
#line 136 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_ARG_LIST, yystack.l_mark[0].astNod, NULL);}
#line 1583 "y.tab.c"
break;
case 56:
#line 137 "parser.y"
	{yyval.astNod = astCreate(NULL, AST_ARG_LIST, yystack.l_mark[-2].astNod, yystack.l_mark[0].astNod);}
#line 1588 "y.tab.c"
break;
#line 1590 "y.tab.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}
