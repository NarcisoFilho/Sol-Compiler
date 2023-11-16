/** JockerC: Test file 
  * 
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
    if(argc < 2){
        printf("Error: Expected 1 argument but receives 0\n");
        printf("Usage: %s 'fileName'\n", argv[0]);
        exit(1);
    }
    initMe();

    FILE* inputFile = freopen(argv[1], "r", stdin);
    int type;
    int lastLine = -1;
    int currentLine;
    while(isRunning()){
        type = yylex(); 
    }

    printSymbolTable();

    return 0;
}
