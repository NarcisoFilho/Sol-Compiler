#ifndef __SEMANTIC_ANALYSER_H_
#define __SEMANTIC_ANALYSER_H_

#include "AST.h"
#include "SymbolTable.h"

typedef enum{
    SE_REDECLARATION,
    SE_DATA_TYPE_INCOMPATIBILITY,
    SE_INVALID_INDEX_TYPE,
    SE_INVALID_ARRAY_SIZE_TYPE,
    SE_INVALID_INIT_LIST_SIZE,
    SE_INCOMPATIBLE_OPERAND_TYPES,
    SE_NOT_BOOLEAN_OPERANDS,
    SE_UNDECLARED_FUNCTION,
    SE_UNIMPLEMENTED_FUNCTION,
    SE_FUNCTION_IMPLEMENTED_TWICE,
    SE_NOT_VAR_ID,
    SE_NOT_ARRAY_ID,
    SE_NOT_FUNC_ID,
    SE_UNEXPECTED_ARGUMENTS_COUNT,
    SE_UNEXPECTED_ARGUMENTS_TYPE,
    SE_INVALID_RETURN_DATA_TYPE,
    SE_UNDECLARED_IDENTIFIER,
} SemanticErrorType;

typedef struct{
    SemanticErrorType errorType;
    AST* ast;
}SemanticError;


bool checkSemantic(AST*);
void checkDeclarationStatement(AST*);
bool verifyIDUnicity(AST*);
void redefineIDSymbolType(AST*);
void defineIDSymbolDataType(AST*);
void verifyInitCompatibility(AST*);
bool verifyDataTypesCompatibility(DataType, DataType);
bool verifyIndexType(AST*);
bool verifyArrayIndexType(AST*);
bool isIntegerValue(DataType);
void checkIdentifierDeclaration(AST*);
void setASTDataType(AST*, DataType);
DataType determineListType(AST*);
DataType calculateOutcomeDatatype(DataType, DataType);
const char* getDataTypeByCode(DataType);
void determineLiteralDataType(AST*);
void checkAssignmentDataTypeCompatibility(AST*);
void checkArraySizeRestrictions(AST*);
bool checkFunctionDeclaration(AST*);
bool checkFunctionReimplementation(AST*);
bool checkFunctionImplementation(AST*);
bool verifyIfIsIDType(AST*, TokensTypes);
bool checkIfIsArrayID(AST*);
bool checkIfIsVarID(AST*);
bool checkIfIsFunctionID(AST*);
int calculateParametersCount(AST*);
int calculateArgumentsListSize(AST*);
void checkFunctionCalling(AST*);
void checkArgumentsProvided(AST*);
void defineFormalParameters(AST*);
void specifyParametersInSymbol(SymbolTableNode*, AST*);
AST* findFunctionScope(AST*);

void pushSError(SemanticError);
void alertAllErrors();
void alertError(SemanticError);



#endif // __SEMANTIC_ANALYSER_H_
