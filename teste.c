#include <stdio.h>
#include "SymbolTable.h"


int main(){
    initSymbolTable();

    addSymbol("var1", 1);
    addSymbol("var2", 1);
    addSymbol("var3", 1);
    addSymbol("oceano", 2);
    addSymbol("77", 3);
    for(int i = 1 ; i <= 20 ; i++){
        char constName[10] = {0};
        sprintf(constName, "const%d", i);
        addSymbol(constName, 4);
    }

    printSymbolTable();
    return 0;
}
