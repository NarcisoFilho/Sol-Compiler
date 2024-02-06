/** JockerC: Test file 
  * 
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.yy.h"
#include "y.tab.h"
#include "SymbolTable.h"
// #include <time.h>
#include <unistd.h>

void initMe();
int isRunning();
int yyparse();

int main(int argc, char** argv){
    if(argc < 2){
        printf("Error: Expected 1 argument but receives 0\n");
        printf("Usage: %s 'fileName'\n", argv[0]);
        exit(1);
    }
    
    initMe();

	FILE* inputFile = fopen(argv[1], "r");
	
    yyin = inputFile;

    int parserReturn = yyparse();

    if(parserReturn == 3){
        printf("Syntax errors found!\a\n");
        exit(3);
    }else{
        // printSymbolTable();
        if(parserReturn == 4){
            printf("Semantic errors found!\a\n");
            exit(4);
        }else{
            // printf("Successfully parsed!\n");
            return 0;
        }
    }
}
