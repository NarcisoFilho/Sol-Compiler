#include <stdlib.h>
#include <string.h>
#include "Boolean.h"

typedef struct{
    int type;
    char* value;
    SymbolTableNode* nextNode;
}SymbolTableNode;

#define SYMBOL_TABLE_SIZE 1001

SymbolTableNode symbolTable[SYMBOL_TABLE_SIZE];

/// Prototypes
int initSymbolTable();
SymbolTableNode addSymbol(char*);
SymbolTableNode findSymbol(char*);
int insertSymbolTableNode(SymbolTableNode);
SymbolTableNode removeSymbolTableNode(SymbolTableNode);
int getHashAddress(char*);

int initSymbolTable(){
    for(int i = 0 ; i < SYMBOL_TABLE_SIZE ; i++){
        symbolTable[i].nextNode = 0;
        symbolTable[i].type = -1;
        symbolTable[i].name = callo;      
    }
}

SymbolTableNode addSymbol(char symbolName[]){
    SymbolTableNode node;


    return node;
}

SymbolTableNode findSymbol(char symbolName[]){
    int address = getHashAddress(symbolName);
    SymbolTableNode *node = &(symbolTable[address]);

    do{
        if(strcmp(symbolName, node->name) == 0){
            return *node
        }
        node = node->nextNode;
    }while(node != 0);

    return *node;
}

int getHashAddress(char symbolName[]){
    int address = 1;
    int letter;
    
    int i = 0;
    while((letter =(int)symbolName[i]) != '\0'){
        address *= letter;
        address %= SYMBOL_TABLE_SIZE;
        i++;
    }

    return address;
}

int insertSymbolTableNode(SymbolTableNode* node){
    int address = getHashAddress(node->value);

    node->nextNode = &(symbolTable[address]);
    symbolTable[address] = *(node);

    return true;
}