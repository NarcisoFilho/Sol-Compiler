#ifndef __SEMANTIC_ANALYSER_H_
#define __SEMANTIC_ANALYSER_H_

#include "AST.h"
#include "SymbolTable.h"


// void semanticSetDeclations(AST *node);

// **inferencia de tipo
// em atribuições
// em expressoes
// ** funcao para saber se é booleano

void printSemanticError(char* errorDesc, char* param);
int checkSemantic(AST *node);
void specifyIdentifierType(AST *node, int type);
// int testID(HASH_NODE* id,AST* node);
// void setDataType(AST *node, int type);
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
