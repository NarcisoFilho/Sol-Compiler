#ifndef __TAC_H_
#define __TAC_H_

#include "SymbolTable.h"
#include "AST.h"

#define TEMP_SYMBOL_STAMP "_J0CK35_TEMP_"
#define LABEL_STAMP "_J0CK35_LABEL_"

typedef enum TACtype{
    TAC_SYMBOL,
    TAC_LABEL,
    TAC_BEGIN_PROCEDURE,
    TAC_END_PROCEDURE,
    TAC_ADD,
    TAC_SUB,
    TAC_MUL,
    TAC_DIV,
    TAC_OPERATOR_LE,
    TAC_OPERATOR_GE,
    TAC_OPERATOR_EQ,
    TAC_OPERATOR_DIF,
    TAC_GREATER_THAN,
    TAC_LESS_THAN,
    TAC_AND,
    TAC_OR,
    TAC_NOT,
    TAC_RETURN,
    TAC_PRINT,
    TAC_INPUT,
    TAC_UNDEF,
}TACtype;

typedef struct TAC{
    SymbolTableNode* dst;
    SymbolTableNode* src1;
    SymbolTableNode* src2;
    TACtype type;
    struct TAC* prev;
    struct TAC* next;
}TAC;

TAC* tacCreate(TACtype, SymbolTableNode*, SymbolTableNode*, SymbolTableNode*);
TAC* tacsLink(TAC*, TAC*);
TAC* tacGenerateFromAST(AST*);
TAC* generateBinaryOpTAC(AST*);
TAC* generateProcedureImplementation(AST*);
SymbolTableNode* createTempSymbol();
int digitsCount(int);
TACtype decodeTACtypeFromASTtype(ASTtype);


#endif //__TAC_H_
