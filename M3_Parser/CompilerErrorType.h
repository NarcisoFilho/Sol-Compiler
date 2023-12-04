#include <stdio.h>

typedef enum{
    INVALID_CHARACTER,
    MULTI_CHARACTER_CONSTANTE
}CompilerErrorType;

void compilerErrorAlert(int lineNumber, char* wrongToken, CompilerErrorType errorType){
    switch (errorType){
    case INVALID_CHARACTER:
        printf("Error <l%d>: Invalid character(%c)\n", lineNumber, wrongToken[0]);        
        break;
    case MULTI_CHARACTER_CONSTANTE:
        printf("Error <l%d>: Multi-character literal of type char (%s)\n", lineNumber, wrongToken);        
        break;
    default:
        printf("Error <l%d>\n", lineNumber);        
        break;
    }
}