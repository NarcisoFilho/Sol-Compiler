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
#ifndef __SYMBOL_TABLE_HPP
#define __SYMBOL_TABLE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h"


enum TokensTypes {
    TK_IDENTIFIER_TOKEN,
    LIT_REAL_TOKEN,
    LIT_INT_TOKEN,
    LIT_CHAR_TOKEN,
    LIT_STRING_TOKEN,
    VARIABLE_ID_TOKEN,
    ARRAY_ID_TOKEN,
    FUNCTION_ID_TOKEN
};

enum DataType {
    REAL_DATA_TYPE,
    INT_DATA_TYPE,
    CHAR_DATA_TYPE
};

typedef struct SymbolTableNode{
    int type;
    char* value;
    int dataType;
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

#endif // __SYMBOL_TABLE_HPP