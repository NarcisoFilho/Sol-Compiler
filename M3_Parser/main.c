#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.yy.h"
#include "y.tab.h"
#include "SymbolTable.h"
#include "AST.h"

void initMe();
int isRunning();
int yyparse();

int main(int argc, char** argv){
    if(argc < 3){
        printf("Error: Expected 2 argument but receives %d\n", argc - 1);
        printf("Usage: %s 'inputFile' 'outputFile'\n", argv[0]);
        exit(1);
    }
    
    initMe();

	FILE* inputFile = fopen(argv[1], "r");
    if(inputFile == NULL){
        printf("\aError: Unable to open input file '%s'\n", argv[1]);
        exit(1);
    }

    yyin = inputFile;

    printf("\n# Parsing \n");

    if(yyparse() != 3){
        printf("\nSuccessfully parsed!\n");   
        FILE* outputFile = fopen(argv[2], "w");
        if(outputFile == NULL){
            printf("\aError: Unable to create output file '%s'\n", argv[2]);
            exit(1);
        }else{
            astExportProgram(outputFile);
        }

        return 0;
    }else{
        printf("\a\n");
        return 3;
    }
}

