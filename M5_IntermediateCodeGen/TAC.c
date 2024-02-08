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
        switch(ast->type){
            case AST_FULL_PROG: return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_FUNCTION_IMPLEMENTATION_LIST: return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_FUNCTION_IMPLEMENTATION: return generateProcedureImplementation(ast);
            case AST_CMD_BLOCK: return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_CMD_LIST: return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_NOT: return generateNotOpTAC(ast);
            case AST_ADD:          return generateBinaryOpTAC(ast);
            case AST_SUB:          return generateBinaryOpTAC(ast);
            case AST_MUL:          return generateBinaryOpTAC(ast);
            case AST_OPERATOR_LE:  return generateBinaryOpTAC(ast);
            case AST_OPERATOR_GE:  return generateBinaryOpTAC(ast);
            case AST_OPERATOR_EQ:  return generateBinaryOpTAC(ast);
            case AST_OPERATOR_DIF: return generateBinaryOpTAC(ast);
            case AST_GREATER_THAN: return generateBinaryOpTAC(ast);
            case AST_LESS_THAN:    return generateBinaryOpTAC(ast);
            case AST_AND:          return generateBinaryOpTAC(ast);
            case AST_OR:           return generateBinaryOpTAC(ast);
            case AST_RETURN: return generateReturnTAC(ast);
            case AST_PRINT: return generatePrintTAC(ast);
            case AST_INPUT: return generateInputTAC(ast);            
            case AST_ASSIGNMENT: return generateAssignmentTAC(ast);
            case AST_ARRAY_ASSIGN:return generateArrayAssignmentTAC(ast);
            case AST_WHILE: break;
            case AST_IF_THEN: break;
            case AST_IF_THEN_ELSE: break;
            case AST_FUNCTION_CALLING: break;
            case AST_SYMBOL: break;
            case AST_ARRAY_EXPR: break;
            case AST_ARG_LIST: return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_LITERAL_LIST: return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_PARAM_LIST: return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_PARAM: break;
            default: break;
            // case AST_VAR_DECLARATION:
            //     break;
            // case AST_ARRAY_DECLARATION:
            //     break;
            // case AST_ARRAY_DEC_AND_INIT:
            //     break;

            // case AST_CHAR:
            // case AST_INT:
            // case AST_FLOAT:
            // case AST_HEADER:
            //     return tacGenerateFromAST(ast->sons[0]);
            // case AST_DECLARATION_LIST:
            //     return tacsLink(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            // case AST_FUNCTION_DECLARATION:
            //     break;
        }
    }
    return NULL;
}

TAC* generateArrayAssignmentTAC(AST* ast){
    SymbolTableNode *dst = ast->symbol;
    SymbolTableNode *src1 = (ast->sons[0] != NULL) ? ast->sons[0]->symbol : NULL;
    SymbolTableNode *src2 = (ast->sons[1] != NULL) ? ast->sons[1]->symbol : NULL;
    return tacCreate(TAC_ARRAY_ASSIGNMENT, dst, src1, src2);
}

TAC* generateAssignmentTAC(AST* ast){
    SymbolTableNode *dst = ast->symbol;
    SymbolTableNode *src1 = (ast->sons[0] != NULL) ? ast->sons[0]->symbol : NULL;
    return tacCreate(TAC_ASSINGNMENT, dst, src1, NULL);
}

TAC* generateNotOpTAC(AST* ast){
    SymbolTableNode *src1 = (ast->sons[0] != NULL) ? ast->sons[0]->symbol : NULL;
    return tacCreate(TAC_NOT, createTempSymbol(), src1, NULL);
}

TAC* generateReturnTAC(AST* ast){
    SymbolTableNode *src1 = (ast->sons[0] != NULL) ? ast->sons[0]->symbol : NULL;
    return tacCreate(TAC_RETURN, createTempSymbol(), src1, NULL);
}

TAC* generatePrintTAC(AST* ast){
    SymbolTableNode *dst = (ast->sons[0] != NULL) ? ast->sons[0]->symbol : NULL;
    return tacCreate(TAC_PRINT, dst, NULL, NULL);
}

TAC* generateInputTAC(AST* ast){
    SymbolTableNode *src1 = (ast->sons[0] != NULL) ? ast->sons[0]->symbol : NULL;
    return tacCreate(TAC_INPUT, createTempSymbol(), src1, NULL);
}

TAC* generateBinaryOpTAC(AST* ast){
    TAC* tac = NULL;
    if(ast != NULL){
        TACtype tacType = decodeBinaryOperationTACtypeFromASTtype(ast->type);
        if(tacType != TAC_UNDEF){
            if(ast->sons[0] != NULL){
                if(ast->sons[1] != NULL){
                    tac = tacCreate(tacType, createTempSymbol(), ast->sons[0]->symbol, ast->sons[1]->symbol);
                }
            }
        }
    }

    return tac;
}

TAC* generateProcedureImplementation(AST* ast){
    if(ast != NULL){
        if(ast->type == AST_FUNCTION_IMPLEMENTATION){
            if(ast->sons[0] != NULL){
                TAC* initTac = tacCreate(TAC_BEGIN_PROCEDURE, createLabelSymbol(), ast->sons[0]->symbol, NULL);
                TAC* commandsTac = tacGenerateFromAST(ast->sons[0]);
                TAC* endTac = tacCreate(TAC_END_PROCEDURE, createLabelSymbol(), ast->sons[0]->symbol, NULL);
                return tacsLink(tacsLink(initTac, commandsTac), endTac);
            }
        }
    }
    return NULL;
}

TACtype decodeBinaryOperationTACtypeFromASTtype(ASTtype astType){
    switch(astType){
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
        default:
            break;
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
