#include "asm.h"

void generateAsm(TAC* tacList, const char* fileName){
    FILE *file = fopen(fileName, "w");

    while(tacList != NULL){
        fprintf(file, "%s", generateAsmFromTac(tacList));
        tacList = tacList->next;
    }



    fclose(file);
}

const char* generateAsmFromTac(TAC* tac){
    static char code[200];
    char aux[50] = {0};

    strcpy(code, "");

    if(tac != NULL){
        switch(tac->type){
            case TAC_SYMBOL:
                break;
            case TAC_LABEL:
                break;
            case TAC_BEGIN_PROCEDURE:
                break;
            case TAC_END_PROCEDURE:
                break;
            case TAC_CALL_PROCEDURE:
                break;
            case TAC_PUSH_ARG:
                break;
            case TAC_POP_ARG:
                break;
            case TAC_COPY:
                sprintf(code, "mov   eax, %s\n", tac->src1->value);
                sprintf(aux, "mov   %s, eax\n", tac->dst->value);
                strcat(code, aux);
                break;
            case TAC_MOV_LAST_RETURN:
                break;
            case TAC_ADD:
                sprintf(code, "mov   eax, %s\n", tac->src1->value);
                sprintf(aux, "add   eax, %s\n", tac->src2->value);
                strcat(code, aux);
                sprintf(aux, "mov   %s, eax\n", tac->dst->value);
                strcat(code, aux);
                break;
            case TAC_SUB:
                sprintf(code, "mov   eax, %s\n", tac->src1->value);
                sprintf(aux, "sub   eax, %s\n", tac->src2->value);
                strcat(code, aux);
                sprintf(aux, "mov   %s, eax\n", tac->dst->value);
                strcat(code, aux);
                break;
            case TAC_MUL:
                break;
            case TAC_DIV:
                break;
            case TAC_OPERATOR_LE:
                break;
            case TAC_OPERATOR_GE:
                break;
            case TAC_OPERATOR_EQ:
                break;
            case TAC_OPERATOR_DIF:
                break;
            case TAC_GREATER_THAN:
                break;
            case TAC_LESS_THAN:
                break;
            case TAC_AND:
                break;
            case TAC_OR:
                break;
            case TAC_NOT:
                break;
            case TAC_RETURN:
                break;
            case TAC_PRINT:
                break;
            case TAC_INPUT:
                break;
            case TAC_ARRAY_ASSIGNMENT:
                break;
            case TAC_COPY_ARRAY_ELEMENT:
                break;
            case TAC_JMP:
                break;
            case TAC_JMP_IFZ:
                break;
            case TAC_CLAUSE_SYMBOL:
                break;
            case TAC_UNDEF:
                break;
            case TAC_VAR_INT_DECLARATION:
                break;
            case TAC_VAR_CHAR_DECLARATION:
                break;
            case TAC_VAR_FLOAT_DECLARATION:
                break;
            case TAC_PAR_INT_DECLARATION:
                break;
            case TAC_PAR_CHAR_DECLARATION:
                break;
            case TAC_PAR_FLOAT_DECLARATION:
                break;
            case TAC_ARRAY_INT_DECLARATION:
                break;
            case TAC_ARRAY_CHAR_DECLARATION:
                break;
            case TAC_ARRAY_FLOAT_DECLARATION:
                break;
            case TAC_PROCEDURE_INT_DEC:
                break;
            case TAC_PROCEDURE_CHAR_DEC:
                break;
            case TAC_PROCEDURE_FLOAT_DEC:
                break;
            default:
                break;
        }
    }

    return (const char*)code;
}