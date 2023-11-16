/** JOKERC: Joker language compiler
 *  MODULE: Symbol Table
 *  @date october 27 2023
 *  @version 1.0
 *  @author Manoel Narciso Reis
 *  @brief A compiler Symbol Table implementation, based on hashtable data structure.
 *      -> Interface functions:
 *          - initSymbolTable
 *          - addSymbol
 *          - findSymbol
 *          - removeSymbol
 *          - printSymbolTable
 *          - getTableSize
 *          - getAddedElementsCountInTable
 *          - setRehashAlertStatus
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h"
#include "tokens.h"

typedef struct SymbolTableNode{
    int type;
    char* value;
    struct SymbolTableNode* nextNode;
}SymbolTableNode;

/// Prototypes
    // Public(Interface functions)
    int initSymbolTable();
    void printSymbolTable();
    SymbolTableNode* addSymbol(char*, int);
    SymbolTableNode* findSymbol(char*);
    int removeSymbol(char*);
    int setRehashAlertStatus(int);

    // Private(Internal functions)
    static bool rehashSymbolTable();
    static int calculateHashAddress(char*);
    static int getGreaterPrimeNumber(int);
    static bool isPrimeNumber(int);
    static float getLoadFactor();
    static void printSymbolType(int);
    static void insertNodeInTable(SymbolTableNode*);