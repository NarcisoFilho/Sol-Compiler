#ifndef __AST_TREE_H_
#define __AST_TREE_H_

#include "SymbolTable.h"

#define MAX_SONS_COUNT 4

enum AST_CODES {
    AST_CODE_CHAR,
    AST_CODE_INT,
    AST_CODE_FLOAT,
    
    AST_CODE_ADD,
    AST_CODE_SUB,
    AST_CODE_MUL,
    AST_CODE_DIV,
    AST_CODE_OPERATOR_LE,
    AST_CODE_OPERATOR_GE,
    AST_CODE_OPERATOR_EQ,
    AST_CODE_OPERATOR_DIF,
    AST_CODE_OPERATOR_G,
    AST_CODE_OPERATOR_L,
    AST_CODE_AND,
    AST_CODE_OR,
    AST_CODE_NOT,



    AST_CODE_FUNCTION_DECLARATION,

    AST_CODE_PRINT,
    AST_CODE_READ,
    AST_CODE_RETURN,
    AST_CODE_ASSIGNMENT,
    AST_CODE_ARRAY_ASSIGNMENT,
    
    AST_CODE_WHILE,
    AST_CODE_IF_THEN,
    AST_CODE_IF_THEN_ELSE,
    AST_CODE_FUNCTION_CALLING,


    AST_CODE_SYMBOL,

    AST_CODE_VECTOR_EXPR,    
    AST_CODE_LIST_ARG_BEGIN,
    AST_CODE_SEQ_CMD,
    AST_CODE_CJTODEC_ELEM,
    AST_CODE_DEC_VAR_GLOB,
    AST_CODE_DEC_VEC_GLOB,
    AST_CODE_DEC_VEC_SEQ,
    AST_CODE_DEC_VEC,
    AST_CODE_SEQNUM_ELEM,
    AST_CODE_DEC_FUNC,
    AST_CODE_CABEC,
    AST_CODE_PARAM_ELEM,
    AST_CODE_PARAM,
    AST_CODE_PARENTESIS_EXPR,
    AST_CODE_COMMAND_BLOCK,
    AST_CODE_LIST_ARG_ELEM,
};

typedef struct ASTTree{
	int type;
	SymbolTableNode *symbol;
	struct ASTTree *sons[MAX_SONS_COUNT];
} ASTTree;

ASTTree* astTree;

ASTTree* astTreeCreate(SymbolTableNode *symbol, int type, ASTTree *son0, ASTTree *son1, ASTTree *son2, ASTTree *son3);
void astTreePrint(ASTTree *node, int level);
void astTreeGenerateProgram (ASTTree* node, FILE* outputFileName);

#endif // __AST_TREE_H_
