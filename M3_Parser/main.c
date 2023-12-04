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
void loadingEffect(int);

int main(int argc, char** argv){
    if(argc < 2){
        printf("Error: Expected 1 argument but receives 0\n");
        printf("Usage: %s 'fileName'\n", argv[0]);
        exit(1);
    }
    
    initMe();

	FILE* inputFile = fopen(argv[1], "r");
	
    yyin = inputFile;

    printf("\n# Scanning ");
    loadingEffect(500);

    int parserReturn = yyparse();
    printSymbolTable();

    printf("\n# Parsing ");
    loadingEffect(500);

    if(parserReturn != 3){
        printSymbolTable();
        printf("Successfully parsed!\n");
        return 0;
    }else{
        printf("\a\n");
        return 3;
    }
}

void loadingEffect(int msTime){
    for (int i = 0; i < 4; ++i) {
        printf(">");
        // fflush(stdout); 
        // usleep(msTime * 1000);
    }
}
