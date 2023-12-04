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
#include "SymbolTable.h"

// Private Data (Internal atributes)
static SymbolTableNode** symbolTable;          // Symbol Table pointer
static int currentTableSize = 7;            // Table entries count(atomatically increased)
static int addedSymbolsCount = 0;              // Added symbols number
static const float maximusLoadFactor = 0.7;    
static bool rehashAlertActive = false;         // When active, notification is printed in table rehashing event

/** @brief Initializes 'symbolTable', setting all pointers in list to zero
 */
int initSymbolTable(){    
    // Check if it is set a reasonable currentTableSize value
    if(currentTableSize <= 0)   
        return (int)false;

    // Allocate memory and check
    symbolTable = (SymbolTableNode**)malloc(currentTableSize * sizeof(SymbolTableNode*));
    if(symbolTable == 0 )
        return (int)false;
    
    // Table's pointers initialization
    for(int i = 0 ; i < currentTableSize ; i++)
        symbolTable[i] = 0;
        
    return (int)true;
}

/** @brief Add 'symbol', of type 'symbolType', in 'symbolTable'
 *  @param symbol The symbol to be inserted
 *  @param symbolType The type of 'symbol'
 *  @return A pointer to the inserted symbol, or 0 if some error ocurred
 */
SymbolTableNode* addSymbol(char symbol[], int symbolType){
    SymbolTableNode *node = findSymbol(symbol);
   
    if(node == 0){
        // Rehashe Symbol Table if necessary
        if(getLoadFactor() >= maximusLoadFactor){
            if(rehashAlertActive){
                if(rehashSymbolTable())
                    printf("-> Symbol Table Rehashed (%d entries)\n", currentTableSize);
                else
                    printf("->\a Can not rehash Symbol Table!\n");
            }
        }

        // Insert new node
        int address = calculateHashAddress(symbol);
        node = (SymbolTableNode*)calloc(1, sizeof(SymbolTableNode));

        char* value = (char*)calloc(strlen(symbol) + 1, sizeof(char));
        strcpy(value, symbol);
        node->value = value;
        node->type = symbolType;
        insertNodeInTable(node);
        addedSymbolsCount++;
    }

    return node;
}

/** @brief Remove 'symbol' from 'symbolType'
 *  @param symbol The symbol to be removed
 *  @return 1 if the element was removed and 0 if it did not
 */
int removeSymbol(char symbol[]){
    SymbolTableNode *node = findSymbol(symbol);

    if(node == 0){
        return (int)false;
    }else{
        int address = calculateHashAddress(symbol);
        if(symbolTable[address] != 0){
            if(symbolTable[address] == node){
                symbolTable[address] = node->nextNode;
                free(node->value);                
                free(node);
                addedSymbolsCount--;
                return (int)true;
            }else{
                SymbolTableNode *previousNode = symbolTable[address];
                while(previousNode != 0){
                    if(previousNode->nextNode == node){
                        previousNode->nextNode = node->nextNode;
                        free(node);
                        addedSymbolsCount--;
                        return (int)true;
                    }
                }
            }
        }
        return (int)false;
    }
}

/** @brief Search 'symbolTable' for 'symbol'
 *  @param symbol The symbol to be searched
 *  @return A pointer to the target symbol, or 0 
 * if it is not finded
 */
SymbolTableNode* findSymbol(char symbol[]){
    int address = calculateHashAddress(symbol);
    SymbolTableNode *node = symbolTable[address];
    
    while(node != 0){
        if(strcmp(symbol, node->value) == 0){
            return node;
        }
        node = node->nextNode;
    }

    return 0;
}

/** @brief Present Symbol Table contents in stdout
 */
void printSymbolTable(){
    printf("-------- SYMBOL TABLE --------\n");
    printf(" line |      <type>symbol     \n");
    printf("------+-----------------------\n");
    for(int i = 0 ; i < currentTableSize ; i++){
        SymbolTableNode *node = symbolTable[i];
        bool rowWasAlreadyIndicated = false;
        while(node != 0){
            if(!rowWasAlreadyIndicated){
                if(i != currentTableSize - 1)
                    printf(" %4d +--- ", i);
                else{
                    printf(" %4d L--- ", i);
                }
                rowWasAlreadyIndicated = true;
            }else{
                printf("  ---  ");
            }
            printSymbolType(node->type);              
            printf("%s", node->value);
            node = node->nextNode;
        }
        if(rowWasAlreadyIndicated){
            if(i != currentTableSize - 1)
                printf("\n      |\n");
            else
                printf("\n");                
        }else{
            if(i == currentTableSize - 1)
                printf(" %4d L---\n", i);
        }
    }
}

void printSymbolType(int type){
    switch(type){
        case TK_IDENTIFIER:
            printf("<ID>");
            break;
        case LIT_REAL:
            printf("<LFLOAT>");
            break;
        case LIT_INT:
            printf("<LINT>");
            break;
        case LIT_STRING:
            printf("<LSTR>");
            break;
        case LIT_CHAR:
            printf("<LCHAR>");
            break;
        default:
            printf("<OP>");
            break;
    }
}

/** @brief Return the number of added elements in Symbol Table
 *  @return Symbol Table's added elements count
 */
int getAddedElementsCountInTable(){
    return addedSymbolsCount;
}

/** @brief Return the number of list slots in Symbol Table
 *  @return Symbol Table's list slots count
 */
int getTableSize(){
    return currentTableSize;
}

/** @brief Turn ON/OFF rehashing notification
 *  @param newStatus New rehashing notification mode
 *  @return 1 if operaration was successfully and 0 other case
 */
int setRehashAlertStatus(int newStatus){
    rehashAlertActive = (bool)newStatus;
    return (int)((int)rehashAlertActive == newStatus);
}

/// ================== AUXILIARY FUNCTIONS =======================================

/** Calculate the address of specified symbol in 'symbolTable'
 *  @param  symbol The symbol for calculate adrress
 *  @return The address(index) of 'symbol' in 'symbolTable'
 */
int calculateHashAddress(char symbol[]){
    int address = 1;
    int letter;
    
    int i = 0;
    while((letter =(int)symbol[i]) != '\0'){
        address++;
        address *= letter;
        address %= currentTableSize;
        i++;
    }

    return address;
}

/** @brief Return the greater prime number until 'upperLimit'
 *  @param upperLimit Greater number checked for primality property
 *  @return The greater prime number until 'upperLimit'. If 'upperLimit' smaller than the smallest 
 *  prime number(2), number 2 is returned
 */
int getGreaterPrimeNumber(int upperLimit){    
    for(int greater = upperLimit ; greater >= 2 ; greater--){
        if(isPrimeNumber(greater))
            return greater;
    }

    return 2;   // The smallest prime number
}

/** @brief Check if a number is prime
 *  @param number The number to be checked about primality
 *  @return true if 'number' is prime and false if it is not
 */
bool isPrimeNumber(int number){
    for(int divisor = 2 ; divisor < number ; divisor++){
        if(number % divisor == 0)
            return false;
    }

    return true;
}

/** @brief Calculates to Load Factor of the Hashtable. The Load Factor
 * is the relationship between the number of elements added and
 * the table slots
 *  @param number The number to be checked about primality
 *  @return true if 'number' is prime and false if it is not
 */
float getLoadFactor(){    
    return addedSymbolsCount / (float)currentTableSize;
}

/** @brief Resize the Symbol Table for about twice the current size. 
 * The new size will be exactly the greater prime number until twice
 * the current size.
 *  @return true if rehash happend successfully and false if did not
 */
bool rehashSymbolTable(){
    // New Symbol Table size
    int oldSize = currentTableSize;
    currentTableSize = getGreaterPrimeNumber(2*currentTableSize);

    // Allocate new bigger table
    SymbolTableNode **oldTable = symbolTable;
    symbolTable = (SymbolTableNode**)malloc(currentTableSize * sizeof(SymbolTableNode*));
    if(symbolTable == 0 ){
        symbolTable = oldTable;
        currentTableSize = oldSize;
        return false;
    }
    
    // Table's pointers initialization
    for(int i = 0 ; i < currentTableSize ; i++)
        symbolTable[i] = 0;    
    
    for(int i = 0 ; i < oldSize ; i++){
        SymbolTableNode *node = oldTable[i];
        SymbolTableNode *nextNode;
        while(node != 0){
            nextNode = node->nextNode;
            insertNodeInTable(node);
            node = nextNode;
        }
    }

    return true;
}


/** @brief Insert a Table node in Symbol Table
 *  @param node Pointer to the node to be inserted
 */
void insertNodeInTable(SymbolTableNode* node){
    int address = calculateHashAddress(node->value);
    node->nextNode = symbolTable[address];
    symbolTable[address] = node;
}
