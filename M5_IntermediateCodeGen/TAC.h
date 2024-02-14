#ifndef __TAC_H_
#define __TAC_H_

#include <stdarg.h>
#include "SymbolTable.h"
#include "AST.h"

#define TEMP_SYMBOL_STAMP "_temp_"
#define LABEL_STAMP "_label_"

typedef enum TACtype{
    TAC_SYMBOL,
    TAC_LABEL,
    TAC_BEGIN_PROCEDURE,
    TAC_END_PROCEDURE,
    TAC_CALL_PROCEDURE,
    TAC_PUSH_ARG,
    TAC_POP_ARG,
    TAC_COPY,
    TAC_MOV_LAST_RETURN,
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
    TAC_ARRAY_ASSIGNMENT,
    TAC_JMP,
    TAC_JMP_IFZ,
    TAC_CLAUSE_SYMBOL,
    TAC_UNDEF,
    TAC_VAR_INT_DECLARATION,
    TAC_VAR_CHAR_DECLARATION,
    TAC_VAR_FLOAT_DECLARATION,
    TAC_PAR_INT_DECLARATION,
    TAC_PAR_CHAR_DECLARATION,
    TAC_PAR_FLOAT_DECLARATION,
    TAC_ARRAY_INT_DECLARATION,
    TAC_ARRAY_CHAR_DECLARATION,
    TAC_ARRAY_FLOAT_DECLARATION,
    TAC_PROCEDURE_INT_DEC,
    TAC_PROCEDURE_CHAR_DEC,
    TAC_PROCEDURE_FLOAT_DEC,
}TACtype;

typedef struct TAC{
    SymbolTableNode* dst;
    SymbolTableNode* src1;
    SymbolTableNode* src2;
    TACtype type;
    struct TAC* prev;
    struct TAC* next;
    int brLineBefore;
    int brLineAfter;
}TAC;

TAC* tacCreate(TACtype, SymbolTableNode*, SymbolTableNode*, SymbolTableNode*);
TAC* joinTacs(TAC*, TAC*);
TAC* tacGenerateFromAST(AST*);
TAC* generateBinaryOpTAC(AST*);
TAC* generateProcedureImplementation(AST*);
SymbolTableNode* createTempSymbol();
SymbolTableNode* createLabelSymbol();
int digitsCount(int);
TACtype decodeBinaryOperationTACtypeFromASTtype(ASTtype);
TAC* generateNotOpTAC(AST*);
TAC* generateReturnTAC(AST*);
TAC* generatePrintTAC(AST*);
TAC* generateInputTAC(AST*);
TAC* generateAssignmentTAC(AST*);
TAC* generateArrayAssignmentTAC(AST*);
void printTAC(TAC*);
const char* getNameFromTACtype(TACtype);
TAC* generateIfElseTAC(AST*);
TAC* generateIfTAC(AST*);
TAC* generateWhileTAC(AST*);
// TAC* generateArgListTAC(AST*);
TAC* generateProcedureCallTAC(AST*);
TAC* generateLabelTAC(SymbolTableNode*);
void breakLineBefore(TAC*);
void breakLineAfter(TAC*);
TAC* generateStackArgumentsListTAC(AST*);
TAC* generateUnstackArgumentsListTAC(AST*);
TAC* generateParamAssignWithArgListTAC(AST*, SymbolTableNode*, int);
TAC* generateParamAssignTACfromParamAST(AST*, SymbolTableNode*, int);
TAC* generateParamAssignWithArgTAC(TAC*, SymbolTableNode*, int);
TAC* generateVarDeclarationTAC(AST*);
TAC* generateArrayDeclarationTAC(AST*);
TAC* generateArrayDeclarationAndInitTAC(AST*);
TAC* generateParamDecTac(AST*);
TAC* generateProcedureDeclarationTAC(AST*);


#endif //__TAC_H_
