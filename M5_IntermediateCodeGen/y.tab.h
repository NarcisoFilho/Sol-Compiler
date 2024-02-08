#ifndef _yy_defines_h_
#define _yy_defines_h_

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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE {
	struct SymbolTableNode *symbol;
    struct AST *astNod;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
