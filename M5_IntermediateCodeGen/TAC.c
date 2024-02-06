#include "TAC.h"


TAC* tacCreate(TACtype type, SymbolTableNode* dst, SymbolTableNode* src1, SymbolTableNode* src2){
    TAC* tac = (TAC*)calloc(1, sizeof(TAC));

    if(tac != NULL){
        tac->type = type;
        tac->dst = dst;
        tac->src1 = src1;
        tac->src2 = src2;
        tac->prev = NULL;
        tac->next = NULL;
        return NULL;
    }else{
        perror("\aCan't allocate memory to create TAC!\n");
        exit(1);
    }
}   

TAC* tacsLink(TAC* tac1, TAC* tac2){
    TAC* resultingTAC;
    if(tac1 != NULL  &&  tac2 != NULL){
        resultingTAC = tac1;
        while(resultingTAC->next != NULL){
            resultingTAC = resultingTAC->next;
        }
        resultingTAC->next = tac2;
        tac2->prev = resultingTAC;
        resultingTAC = tac1;
        return resultingTAC;
    }else{
        if(tac1 != NULL){
            return tac1;
        }else if(tac2 != NULL){
            return tac2;
        }else{
            return NULL;
        }
    }
}

TAC* tacGenerateFromAST(AST* ast){
    if(ast != NULL){
        // for(int s = 0 ; s < getSonsCountFromType(ast->type); s++){
        //     tacGenerateFromAST(ast->sons[s]);
        // }
        
        switch(ast->type){
            case AST_FULL_PROG:
                return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_HEADER:
                return tacGenerateFromAST(ast->sons[0]);
            case AST_DECLARATION_LIST:
                return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_FUNCTION_DECLARATION:
                break;
            case AST_FUNCTION_IMPLEMENTATION_LIST:
                return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_FUNCTION_IMPLEMENTATION:
                return generateProcedureImplementation(ast);
            case AST_CMD_BLOCK:
                return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_CMD_LIST:
                return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
           
            case AST_ADD:
            case AST_SUB:
            case AST_MUL:
            case AST_OPERATOR_LE:
            case AST_OPERATOR_GE:
            case AST_OPERATOR_EQ:
            case AST_OPERATOR_DIF:
            case AST_GREATER_THAN:
            case AST_LESS_THAN:
            case AST_AND:
            case AST_OR:
                return generateBinaryOpTAC(ast);
            case AST_NOT:
                return tacCreate(TAC_NOT, createTempSymbol(), ast->sons[0], NULL);
           
            case AST_RETURN:
                return tacCreate(TAC_RETURN, createTempSymbol(), ast->sons[0], NULL);
            case AST_PRINT:
                return tacCreate(TAC_PRINT, ast->sons[0], NULL, NULL);
            case AST_INPUT:
                return tacCreate(TAC_INPUT, createTempSymbol(), ast->sons[0], NULL);
            
            case AST_ASSIGNMENT:
                break;
            case AST_ARRAY_ASSIGN:
                break;

            case AST_WHILE:
                break;
            case AST_IF_THEN:
                break;
            case AST_IF_THEN_ELSE:
                break;
            case AST_FUNCTION_CALLING:
                break;
            case AST_SYMBOL:
                break;
            case AST_ARRAY_EXPR:
                break;
            case AST_ARG_LIST:
                break;
            case AST_LITERAL_LIST:
                break;
            case AST_PARAM_LIST:
                break;
            case AST_PARAM:
                break;
            case AST_VAR_DECLARATION:
                break;
            case AST_ARRAY_DECLARATION:
                break;
            case AST_ARRAY_DEC_AND_INIT:
                break;

            // case AST_CHAR:
            // case AST_INT:
            // case AST_FLOAT:

        }
    }else{
        return NULL;
    }
    return NULL;    //exclude later
}

TAC* generateBinaryOpTAC(AST* ast){
    TAC* tac = NULL;
    if(ast != NULL){
        TACtype tacType = decodeTACtypeFromASTtype(decodeTACtypeFromASTtype);
        if(tacType != TAC_UNDEF){
            if(ast->sons[0] != NULL){
                if(ast->sons[1] != NULL){
                    tac = tacCreate(tacType, createTempSymbol(), ast->sons[0], ast->sons[1]);
                }
            }
        }
    }

    return tac;
}

TAC* generateProcedureImplementation(AST* ast){
    if(ast != NULL){
        if(ast->type == AST_FUNCTION_IMPLEMENTATION){
            TAC* initTac = tacCreate(TAC_BEGIN_PROCEDURE, createLabelSymbol(), ast->sons[0], NULL);
            TAC* commandsTac = tacGenerateFromAST(ast->sons[0]);
            TAC* endTac = tacCreate(TAC_END_PROCEDURE, createLabelSymbol(), ast->sons[0], NULL);
            return tacsLink(tacsLink(initTac, commandsTac), endTac);
        }
    }
    return NULL;
}

TACtype decodeTACtypeFromASTtype(ASTtype astType){
    switch(astType){
        // case AST_FULL_PROG:
        //     return TAC_;
        // case AST_HEADER:
        //     return TAC_;
        // case AST_FUNCTION_IMPLEMENTATION_LIST:
        //     return TAC_;
        // case AST_CHAR:
        //     return TAC_;
        // case AST_INT:
        //     return TAC_;
        // case AST_FLOAT:
        //     return TAC_;
        case AST_ADD:
            return TAC_ADD;
        case AST_SUB:
            return TAC_SUB;
        case AST_MUL:
            return TAC_MUL;
        case AST_DIV:
            return TAC_DIV;
        case AST_OPERATOR_LE:
            return TAC_OPERATOR_LE;
        case AST_OPERATOR_GE:
            return TAC_OPERATOR_GE;
        case AST_OPERATOR_EQ:
            return TAC_OPERATOR_EQ;
        case AST_OPERATOR_DIF:
            return TAC_OPERATOR_DIF;
        case AST_GREATER_THAN:
            return TAC_GREATER_THAN;
        case AST_LESS_THAN:
            return TAC_LESS_THAN;
        case AST_AND:
            return TAC_AND;
        case AST_OR:
            return TAC_OR;
        case AST_NOT:
            return TAC_NOT;
        // case AST_FUNCTION_DECLARATION:
        //     return TAC_;
        // case AST_FUNCTION_IMPLEMENTATION:
        //     return TAC_;
        // case AST_PRINT:
        //     return TAC_;
        // case AST_INPUT:
        //     return TAC_;
        // case AST_RETURN:
        //     return TAC_;
        // case AST_ASSIGNMENT:
        //     return TAC_;
        // case AST_ARRAY_ASSIGN:
        //     return TAC_;
        // case AST_WHILE:
        //     return TAC_;
        // case AST_IF_THEN:
        //     return TAC_;
        // case AST_IF_THEN_ELSE:
        //     return TAC_;
        // case AST_FUNCTION_CALLING:
        //     return TAC_;
        // case AST_SYMBOL:
        //     return TAC_;
        //     break;
        // case AST_ARRAY_EXPR:
        //     return TAC_;
        // case AST_CMD_BLOCK:
        //     return TAC_;
        // case AST_CMD_LIST:
        //     return TAC_;
        // case AST_ARG_LIST:
        //     return TAC_;
        // case AST_LITERAL_LIST:
        //     return TAC_;
        // case AST_PARAM_LIST:
        //     return TAC_;
        // case AST_PARAM:
        //     return TAC_;
        // case AST_VAR_DECLARATION:
        //     return TAC_;
        // case AST_ARRAY_DECLARATION:
        //     return TAC_;
        // case AST_ARRAY_DEC_AND_INIT:
        //     return TAC_;
        // case AST_DECLARATION_LIST:
        //     return TAC_;
    }
    return TAC_UNDEF;
}

int digitsCount(int number){
    int digitsCount = 0;
    while(number != 0){
        digitsCount++;
        number = number / 10;
    }
    return digitsCount;
}

SymbolTableNode* createTempSymbol(){
    static int tempSerialNumber = 0;
    int tempNameSize = strlen(TEMP_SYMBOL_STAMP) + digitsCount(tempSerialNumber) + 1;
    char tempName[tempNameSize];
    sprintf(tempName, "%s%d", TEMP_SYMBOL_STAMP, tempSerialNumber++);

    return addSymbol(tempName, VARIABLE_ID_TOKEN);
}

SymbolTableNode* createLabelSymbol(){
    static int labelSerialNumber = 0;
    int labelNameSize = strlen(LABEL_STAMP) + digitsCount(labelSerialNumber) + 1;
    char labelName[labelNameSize];
    sprintf(labelName, "%s%d", LABEL_STAMP, labelSerialNumber++);

    return addSymbol(labelName, VARIABLE_ID_TOKEN);
}
