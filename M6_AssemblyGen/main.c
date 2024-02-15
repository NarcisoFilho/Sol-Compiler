/** JockerC: Test file 
  * 
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.yy.h"
#include "y.tab.h"
#include "SymbolTable.h"
#include <unistd.h>

void initMe();
int isRunning();
int yyparse();
void setFileName();

const char* convertFileNameToAsm(const char*);

int main(int argc, char** argv){
    if(argc < 2){
        printf("Error: Expected 1 argument but receives 0\n");
        printf("Usage: %s 'fileName'\n", argv[0]);
        exit(1);
    }
    
    initMe();

	FILE* inputFile = fopen(argv[1], "r");
	
    yyin = inputFile;

    setFileName(convertFileNameToAsm(argv[1]));
    int parserReturn = yyparse();

    if(parserReturn == 3){
        printf("Syntax errors found!\a\n");
        exit(3);
    }else{
        if(parserReturn == 4){
            printf("Semantic errors found!\a\n");
            exit(4);
        }else{
            return 0;
        }
    }
}

const char* convertFileNameToAsm(const char* fileName){
    static char asmFileName[100] = "";
    strcpy(asmFileName, fileName);

    int l = 0;
    while(l < strlen(asmFileName)){
        if(asmFileName[l] == '.'){
            asmFileName[l+1] = '\0';
            break;
        }
        l++;
    }

    strcat(asmFileName, "asm");
    return asmFileName;
}