#ifndef __SEMANTIC_ANALYSER_H_
#define __SEMANTIC_ANALYSER_H_

#include "AST.h"
#include "SymbolTable.h"


// void semanticSetDeclations(AST *node);

// **inferencia de tipo
// em atribuições
// em expressoes
// ** funcao para saber se é booleano

void printSemanticError(char*, char*);
int checkSemantic(AST*);
void specifyIdentifierType(AST*, int);
void specifySymbolDataType(AST*, DataType);
void setDataType(AST*, int);
bool checkAssignment(AST*);
// int testID(HASH_NODE* id,AST* node);
// int calculateFunctionParametersNumber(AST *node);
// void setNumParams(AST *node, int npar);
// void checkSymbolsUse(AST *node);
// void verifyParams(AST *node);
// int verifyFuncCallParams(AST *node);
// int countFuncCallParams(AST* node);
// void checkAstNodeDataType(AST *node);
// int aritmeticInference(AST *node);
// int typeInference(int type1, int type2);
// int verifyAssignmentTypes(int type1, int type2);
// void hashCheckUndeclared();

#endif // __SEMANTIC_ANALYSER_H_
