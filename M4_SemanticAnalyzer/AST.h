#ifndef __AST_TREE_H_
#define __AST_TREE_H_

#include "SymbolTable.h"
#include <stdarg.h>

#define strgfy(label) #label

enum AST_TYPE;
typedef struct AST{
	int type;
    int dataType;
	SymbolTableNode *symbol;
	struct AST **sons;
	struct AST *father;
    int row;
    int col;
} AST;

typedef struct{
    int row;
    int col;
} RC;

void setGlobalAST(AST*);
void applyIdentation(FILE*, int, int);
AST* astCreate(SymbolTableNode*, enum AST_TYPE, ...);
void setRC(AST*, RC);
void astPrint(AST*, int);
void setGlobalAST(AST *);
void astExportProgram(FILE*);
void astGenerateCode(AST*, FILE*, int, int);
int calculateSonsCount(AST);
int getSonsCountFromType(enum AST_TYPE);
char* getTypeName(enum AST_TYPE);

enum AST_TYPE{
    AST_FULL_PROG,
    AST_HEADER,
    AST_FUNCTION_IMPLEMENTATION_LIST,

    AST_CHAR,
    AST_INT,
    AST_FLOAT,
    
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV,
    AST_OPERATOR_LE,
    AST_OPERATOR_GE,
    AST_OPERATOR_EQ,
    AST_OPERATOR_DIF,
    AST_GREATER_THAN,
    AST_LESS_THAN,
    AST_AND,
    AST_OR,
    AST_NOT,

    AST_FUNCTION_DECLARATION,
    AST_FUNCTION_IMPLEMENTATION,

    AST_PRINT,
    AST_INPUT,
    AST_RETURN,
    AST_ASSIGNMENT,
    AST_ARRAY_ASSIGN,
    
    AST_WHILE,
    AST_IF_THEN,
    AST_IF_THEN_ELSE,
    AST_FUNCTION_CALLING,

    AST_SYMBOL,
    AST_ARRAY_EXPR,    
    AST_CMD_BLOCK,
    AST_CMD_LIST,
    AST_ARG_LIST,
    AST_LITERAL_LIST,
    AST_PARAM_LIST,
    AST_PARAM,
    AST_VAR_DECLARATION,
    AST_ARRAY_DECLARATION,
    AST_ARRAY_DEC_AND_INIT,

    AST_DECLARATION_LIST,
};

#endif // __AST_TREE_H_
