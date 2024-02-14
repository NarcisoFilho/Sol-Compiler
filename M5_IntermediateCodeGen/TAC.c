#include "TAC.h"

SymbolTableNode *listOfTempSymbolsAdded[400];
SymbolTableNode *listOfLabelsAdded[400];
int countOfTempSymbolsAdded = 0;
int countOfLabelsAdded = 0;

TAC* tacCreate(TACtype type, SymbolTableNode* dst, SymbolTableNode* src1, SymbolTableNode* src2){
    TAC* tac = (TAC*)calloc(1, sizeof(TAC));

    if(tac != NULL){
        tac->type = type;
        tac->dst = dst;
        tac->src1 = src1;
        tac->src2 = src2;
        tac->prev = NULL;
        tac->next = NULL;
        tac->brLineBefore = 0;
        tac->brLineAfter = 0;
        return tac;
    }else{
        perror("\aCan't allocate memory to create TAC!\n");
        exit(1);
    }
}   

TAC* joinTacs(TAC* tac1, TAC* tac2){
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

TAC* joinMutipleTacs(int count, ...){
    if(count > 0){
        va_list args;
        va_start(args, count);

        TAC *joinedTAC = NULL;

        for(int i = 0; i < count; i++){
            TAC *nextTac = va_arg(args, TAC*);
            joinedTAC = joinTacs(joinedTAC, nextTac);
        }
        va_end(args);

        return joinedTAC;
    }
    return NULL;
}

TAC* tacGenerateFromAST(AST* ast){
    if(ast != NULL){
        switch(ast->type){
            case AST_FULL_PROG: return joinTacs(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_FUNCTION_IMPLEMENTATION_LIST: return joinTacs(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_FUNCTION_IMPLEMENTATION: return generateProcedureImplementation(ast);
            case AST_CMD_BLOCK: return tacGenerateFromAST(ast->sons[0]);
            case AST_CMD_LIST: return joinTacs(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
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
            case AST_ARRAY_ASSIGN: return generateArrayAssignmentTAC(ast);
            case AST_WHILE: return generateWhileTAC(ast);
            case AST_IF_THEN_ELSE: return generateIfElseTAC(ast);
            case AST_IF_THEN: return generateIfTAC(ast);
            case AST_FUNCTION_CALLING: return generateProcedureCallTAC(ast);
            case AST_SYMBOL: return tacCreate(TAC_SYMBOL, ast->symbol, NULL, NULL);
            case AST_ARRAY_EXPR: break;
            // case AST_ARG_LIST: return generateArgListTAC(ast);
            case AST_LITERAL_LIST: return joinTacs(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_PARAM_LIST: return joinTacs(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_PARAM: return generateParamDecTac(ast);
        
            case AST_HEADER: return tacGenerateFromAST(ast->sons[0]);
            case AST_DECLARATION_LIST: return joinTacs(tacGenerateFromAST(ast->sons[0]), tacGenerateFromAST(ast->sons[1]));
            case AST_VAR_DECLARATION: return generateVarDeclarationTAC(ast);
            case AST_ARRAY_DECLARATION: return generateArrayDeclarationTAC(ast);
            case AST_ARRAY_DEC_AND_INIT: return generateArrayDeclarationAndInitTAC(ast);
            case AST_FUNCTION_DECLARATION: return generateProcedureDeclarationTAC(ast);
            default: break;
        }
    }
    return NULL;
}

TAC* generateVarDeclarationTAC(AST* ast){
    switch(ast->sons[0]->type){
        case AST_INT: return tacCreate(TAC_VAR_INT_DECLARATION, ast->symbol, ast->sons[1]->symbol, NULL);
        case AST_CHAR: return tacCreate(TAC_VAR_CHAR_DECLARATION, ast->symbol, ast->sons[1]->symbol, NULL);
        case AST_FLOAT: return tacCreate(TAC_VAR_FLOAT_DECLARATION, ast->symbol, ast->sons[1]->symbol, NULL);
    }
    return NULL;
}

TAC* generateParamDecTac(AST* ast){
    if(ast != NULL){
        if(ast->sons[0] != NULL){
            switch(ast->sons[0]->type){
                case AST_INT: return tacCreate(TAC_PAR_INT_DECLARATION, ast->symbol, NULL, NULL);
                case AST_CHAR: return tacCreate(TAC_PAR_CHAR_DECLARATION, ast->symbol, NULL, NULL);
                case AST_FLOAT: return tacCreate(TAC_PAR_FLOAT_DECLARATION, ast->symbol, NULL, NULL);
            }
        }
    }
    return NULL;
}

TAC* generateProcedureDeclarationTAC(AST* ast){
    if(ast != NULL){
        TAC *procedureDecTac = NULL;
        switch(ast->sons[0]->type){
            case AST_INT: procedureDecTac = tacCreate(TAC_PROCEDURE_INT_DEC, ast->symbol, NULL, NULL); break;
            case AST_CHAR: procedureDecTac = tacCreate(TAC_PROCEDURE_CHAR_DEC, ast->symbol, NULL, NULL); break;
            case AST_FLOAT: procedureDecTac = tacCreate(TAC_PROCEDURE_FLOAT_DEC, ast->symbol, NULL, NULL); break;
        }
        if(procedureDecTac != NULL){
            TAC *paramsListTac = tacGenerateFromAST(ast->sons[1]);
            return joinTacs(procedureDecTac, paramsListTac);
        }
    }
    return NULL;
}

TAC* generateArrayDeclarationTAC(AST* ast){
    switch(ast->sons[0]->type){
        case AST_INT: return tacCreate(TAC_ARRAY_INT_DECLARATION, ast->symbol, ast->sons[1]->symbol, NULL);
        case AST_CHAR: return tacCreate(TAC_ARRAY_CHAR_DECLARATION, ast->symbol, ast->sons[1]->symbol, NULL);
        case AST_FLOAT: return tacCreate(TAC_ARRAY_FLOAT_DECLARATION, ast->symbol, ast->sons[1]->symbol, NULL);
    }
    return NULL;
}

TAC* generateArrayDeclarationAndInitTAC(AST* ast){
    SymbolTableNode *literalListLabel = createLabelSymbol();
    TAC *literailsListLabelTac = generateLabelTAC(literalListLabel);
    TAC *literailsListTac = tacGenerateFromAST(ast->sons[2]);
    TAC *declarationTac;

    switch(ast->sons[0]->type){
        case AST_INT: declarationTac = tacCreate(TAC_ARRAY_INT_DECLARATION, ast->symbol, ast->sons[1]->symbol, literalListLabel); break;
        case AST_CHAR: declarationTac = tacCreate(TAC_ARRAY_CHAR_DECLARATION, ast->symbol, ast->sons[1]->symbol, literalListLabel); break;
        case AST_FLOAT: declarationTac = tacCreate(TAC_ARRAY_FLOAT_DECLARATION, ast->symbol, ast->sons[1]->symbol, literalListLabel); break;
    }

    literailsListLabelTac->brLineBefore = 1;
    declarationTac->brLineAfter = 1;

    return joinMutipleTacs(3, literailsListLabelTac, literailsListTac, declarationTac);
}

TAC* generateParamAssignWithArgListTAC(AST* ast, SymbolTableNode* function, int paramNumber){
    if(ast != NULL){
        if(ast->sons[1] != NULL){

            TAC *son0Tac = tacGenerateFromAST(ast->sons[0]);
            TAC *son1Tac;
            TAC *son0AssignmentTac;
            TAC *son1AssignmentTac;
            
            son0AssignmentTac = generateParamAssignWithArgTAC(son0Tac, function, paramNumber);
            
            if(ast->sons[1]->type == AST_ARG_LIST){
                son1Tac = generateParamAssignWithArgListTAC(ast->sons[1], function, paramNumber+1);
                son1AssignmentTac = son1Tac;
            }else{
                son1Tac = tacGenerateFromAST(ast->sons[1]);
                son1AssignmentTac = generateParamAssignWithArgTAC(son1Tac, function, paramNumber);
            }

            return joinTacs(son0AssignmentTac, son1AssignmentTac);
        }else{
            if(ast->sons[0] != NULL){
                return generateParamAssignTACfromParamAST(ast->sons[0], function, paramNumber);
            }
        }
    }
    return NULL;
}
TAC* generateStackArgumentsListTAC(AST* ast){
    if(ast != NULL){
        if(ast->sons[1] != NULL){
            TAC *son0Tac;
            TAC *son1Tac;
            if(ast->sons[0]->type == AST_ARG_LIST){
                son0Tac = generateStackArgumentsListTAC(ast->sons[0]);
            }else{
                son0Tac = tacGenerateFromAST(ast->sons[0]);
            }

            if(ast->sons[1]->type == AST_ARG_LIST){
                son1Tac = generateStackArgumentsListTAC(ast->sons[1]);
            }else{
                son1Tac = tacGenerateFromAST(ast->sons[1]);
            }

            return joinTacs(son0Tac, son1Tac);
        }else{
            if(ast->sons[0] != NULL){
                TAC *argumentTac = tacGenerateFromAST(ast->sons[0]);

                if(argumentTac != NULL){   
                    TAC *pushTac = tacCreate(TAC_PUSH_ARG, argumentTac->dst, NULL, NULL);

                    if(argumentTac->type != TAC_SYMBOL){
                        pushTac = joinTacs(argumentTac, pushTac);
                    }

                    return pushTac;
                }
            }
        }
    }
    return NULL;
}

TAC* generateUnstackArgumentsListTAC(AST* ast){
    if(ast != NULL){
        if(ast->sons[1] != NULL){
            TAC *son0Tac;
            TAC *son1Tac;
            if(ast->sons[0]->type == AST_ARG_LIST){
                son0Tac = generateUnstackArgumentsListTAC(ast->sons[0]);
            }else{
                son0Tac = tacGenerateFromAST(ast->sons[0]);
            }

            if(ast->sons[1]->type == AST_ARG_LIST){
                son1Tac = generateUnstackArgumentsListTAC(ast->sons[1]);
            }else{
                son1Tac = tacGenerateFromAST(ast->sons[1]);
            }

            return joinTacs(son0Tac, son1Tac);
        }else{
            if(ast->sons[0] != NULL){
                return tacCreate(TAC_POP_ARG, NULL, NULL, NULL);
            }
        }
    }
    return NULL;
}

TAC* generateProcedureCallTAC(AST* ast){
    SymbolTableNode *returnValue = createTempSymbol();
    TAC* parametersAssigmentTac = generateParamAssignWithArgListTAC(ast->sons[0], ast->symbol, 0);
    TAC* procedureCallTac = tacCreate(TAC_CALL_PROCEDURE, ast->symbol, NULL, NULL);
    TAC* returnValueTac = tacCreate(TAC_MOV_LAST_RETURN, returnValue, NULL, NULL);
    TAC* symbolClauseTac = tacCreate(TAC_CLAUSE_SYMBOL, returnValue, NULL, NULL);
    
    return joinMutipleTacs(4, symbolClauseTac, parametersAssigmentTac, procedureCallTac, returnValueTac);
}

TAC* generateWhileTAC(AST* ast){
    SymbolTableNode *labelToWhileBegin = createLabelSymbol();
    SymbolTableNode *labelToWhileEnd = createLabelSymbol();

    TAC* booleanExpressionTac = tacGenerateFromAST(ast->sons[0]);
    TAC *jmpToWhileEndTac = tacCreate(TAC_JMP_IFZ, labelToWhileEnd, booleanExpressionTac->dst, NULL);
    TAC *jmpToWhileBeginTac = tacCreate(TAC_JMP, labelToWhileBegin, NULL, NULL);
    TAC *cmdList = tacGenerateFromAST(ast->sons[1]);
    TAC *beginLabelTac = generateLabelTAC(labelToWhileBegin);
    TAC *endLabelTac = generateLabelTAC(labelToWhileEnd);

    endLabelTac->brLineAfter = 1;
    beginLabelTac->brLineBefore = 1;

    return joinMutipleTacs(6, beginLabelTac, booleanExpressionTac, jmpToWhileEndTac, cmdList, jmpToWhileBeginTac, endLabelTac);
}

TAC* generateIfElseTAC(AST* ast){
    SymbolTableNode *labelToElseCmd = createLabelSymbol();
    SymbolTableNode *labelToEndIf = createLabelSymbol();
    
    TAC *expressionTestTac = tacGenerateFromAST(ast->sons[0]);
    TAC *jmpElseTac = tacCreate(TAC_JMP_IFZ, labelToElseCmd, expressionTestTac->dst, NULL);
    TAC *jmpEndIfTac = tacCreate(TAC_JMP, labelToEndIf, NULL, NULL);
    TAC *elseLabelTac = generateLabelTAC(labelToElseCmd);
    TAC *endLabelTac = generateLabelTAC(labelToEndIf);

    expressionTestTac->brLineBefore = 1;
    endLabelTac->brLineAfter = 1;

    return joinMutipleTacs(7, expressionTestTac, jmpElseTac, tacGenerateFromAST(ast->sons[1]), jmpEndIfTac, elseLabelTac, tacGenerateFromAST(ast->sons[2]), endLabelTac);
}

TAC* generateIfTAC(AST* ast){
    SymbolTableNode *labelToEndIf = createLabelSymbol();
    TAC *expressionTestTac = tacGenerateFromAST(ast->sons[0]);
    TAC *jmpEndIfTac = tacCreate(TAC_JMP_IFZ, labelToEndIf, expressionTestTac->dst, NULL);
    TAC *cmdList = tacGenerateFromAST(ast->sons[1]);
    TAC *endLabelTac = generateLabelTAC(labelToEndIf);

    expressionTestTac->brLineBefore = 1;
    endLabelTac->brLineAfter = 1;
    
    return joinMutipleTacs(4, expressionTestTac, jmpEndIfTac, cmdList, endLabelTac);
}

TAC* generateLabelTAC(SymbolTableNode* symbol){
    return tacCreate(TAC_LABEL, symbol, NULL, NULL);
}

TAC* generateArrayAssignmentTAC(AST* ast){
    SymbolTableNode *dst = ast->symbol;
    SymbolTableNode *src1 = (ast->sons[0] != NULL) ? ast->sons[0]->symbol : NULL;
    SymbolTableNode *src2 = (ast->sons[1] != NULL) ? ast->sons[1]->symbol : NULL;
    return tacCreate(TAC_ARRAY_ASSIGNMENT, dst, src1, src2);
}

TAC* generateAssignmentTAC(AST* ast){
    if(ast != NULL){
        TAC* valueTac = tacGenerateFromAST(ast->sons[0]);
        if(valueTac != NULL){
            SymbolTableNode *dst = ast->symbol;
            TAC *assigmentTac = tacCreate(TAC_COPY, dst, valueTac->dst, NULL);
            
            if(valueTac->type != TAC_SYMBOL){
                assigmentTac = joinTacs(valueTac, assigmentTac);
            }

            return assigmentTac;
        }
    }

    return NULL;
}

TAC* generateNotOpTAC(AST* ast){
    SymbolTableNode *src1 = (ast->sons[0] != NULL) ? ast->sons[0]->symbol : NULL;
    return tacCreate(TAC_NOT, createTempSymbol(), src1, NULL);
}

TAC* generateReturnTAC(AST* ast){
    TAC *valueTac = tacGenerateFromAST(ast->sons[0]);
    if(valueTac != NULL){
        TAC *returnTac = tacCreate(TAC_RETURN, valueTac->dst, NULL, NULL);

        if(valueTac->type != TAC_SYMBOL){
            returnTac = joinTacs(valueTac, returnTac);
        }
        return returnTac;
    }
    return NULL;
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
                    TAC* operand0 = tacGenerateFromAST(ast->sons[0]);
                    TAC* operand1 = tacGenerateFromAST(ast->sons[1]);
                    SymbolTableNode* resultSymbol = createTempSymbol();

                    tac = tacCreate(tacType, resultSymbol, operand0->dst, operand1->dst);
                    
                    if(operand1->type != TAC_SYMBOL){
                        tac = joinTacs(operand1, tac);
                    }

                    if(operand0->type != TAC_SYMBOL){
                        tac = joinTacs(operand0, tac);
                    }
                    
                    TAC *clauseSymbolTac = tacCreate(TAC_CLAUSE_SYMBOL, resultSymbol, NULL, NULL);
                    tac = joinTacs(clauseSymbolTac, tac);
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
                TAC* initTac = tacCreate(TAC_BEGIN_PROCEDURE, ast->symbol, ast->sons[0]->symbol, NULL);
                TAC* commandsTac = tacGenerateFromAST(ast->sons[0]);
                TAC* endTac = tacCreate(TAC_END_PROCEDURE, ast->symbol, NULL, NULL);

                initTac->brLineBefore = 2;
                endTac->brLineAfter = 2;

                return joinTacs(joinTacs(initTac, commandsTac), endTac);
            }
        }
    }
    return NULL;
}

TAC* generateParamAssignTACfromParamAST(AST* ast, SymbolTableNode* function, int paramNumber){
    if(ast != NULL){
        TAC *argumentTac = tacGenerateFromAST(ast);
        return generateParamAssignWithArgTAC(argumentTac, function, paramNumber);
    }
    return NULL;
}

TAC* generateParamAssignWithArgTAC(TAC* argumentTac, SymbolTableNode* function, int paramNumber){
    if(argumentTac != NULL){
        if(argumentTac != NULL){   
            if(function->parameters[paramNumber] != NULL){
                SymbolTableNode *dueParameter = function->parameters[paramNumber];
                TAC *pushTac = tacCreate(TAC_COPY, dueParameter, argumentTac->dst, NULL);

                if(argumentTac->type != TAC_SYMBOL){
                    pushTac = joinTacs(argumentTac, pushTac);
                }

                return pushTac;
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

void printTAC(TAC* tac){
    if(tac != NULL){
        breakLineBefore(tac);
        if(tac->type != TAC_CLAUSE_SYMBOL){
            const char* tacTypeName = getNameFromTACtype(tac->type);
            const char* dst = (tac->dst != NULL) ? tac->dst->value : "0";
            const char* src1 = (tac->src1 != NULL) ? tac->src1->value : "0";
            const char* src2 = (tac->src2 != NULL) ? tac->src2->value : "0";
            
            printf("%s %s, %s, %s\n", tacTypeName, dst, src1, src2);
        }
        breakLineAfter(tac);
        
        printTAC(tac->next);
    }
}

void breakLineBefore(TAC* tac){
    for(int i = tac->brLineBefore; i; i--){
        printf("\n");
    }
}

void breakLineAfter(TAC* tac){
    for(int i = tac->brLineAfter; i; i--){
        printf("\n");
    }
}

const char* getNameFromTACtype(TACtype type){
    switch(type){
        case TAC_SYMBOL:
            return "TAC_SYMBOL";
        case TAC_LABEL:
            return "TAC_LABEL";
        case TAC_BEGIN_PROCEDURE:
            return "TAC_BEGIN_PROCEDURE";
        case TAC_END_PROCEDURE:
            return "TAC_END_PROCEDURE";
        case TAC_ADD:
            return "TAC_ADD";
        case TAC_SUB:
            return "TAC_SUB";
        case TAC_MUL:
            return "TAC_MUL";
        case TAC_DIV:
            return "TAC_DIV";
        case TAC_OPERATOR_LE:
            return "TAC_OPERATOR_LE";
        case TAC_OPERATOR_GE:
            return "TAC_OPERATOR_GE";
        case TAC_OPERATOR_EQ:
            return "TAC_OPERATOR_EQ";
        case TAC_OPERATOR_DIF:
            return "TAC_OPERATOR_DIF";
        case TAC_GREATER_THAN:
            return "TAC_GREATER_THAN";
        case TAC_LESS_THAN:
            return "TAC_LESS_THAN";
        case TAC_AND:
            return "TAC_AND";
        case TAC_OR:
            return "TAC_OR";
        case TAC_NOT:
            return "TAC_NOT";
        case TAC_RETURN:
            return "TAC_RETURN";
        case TAC_PRINT:
            return "TAC_PRINT";
        case TAC_INPUT:
            return "TAC_INPUT";
        case TAC_ARRAY_ASSIGNMENT:
            return "TAC_ARRAY_ASSIGNMENT";
        case TAC_JMP_IFZ:
            return "TAC_JMP_IFZ";
        case TAC_JMP:
            return "TAC_JMP";
        case TAC_PUSH_ARG:
            return "TAC_PUSH_ARG";
        case TAC_POP_ARG:
            return "TAC_POP_ARG";
        case TAC_CALL_PROCEDURE:
            return "TAC_CALL_PROCEDURE";
        case TAC_COPY:
            return "TAC_COPY";
        case TAC_MOV_LAST_RETURN:
            return "TAC_MOV_LAST_RETURN";
        case TAC_CLAUSE_SYMBOL:
            return "TAC_CLAUSE_SYMBOL";
        case TAC_UNDEF:
            return "TAC_UNDEF";
        case TAC_VAR_INT_DECLARATION:
            return "TAC_VAR_INT_DECLARATION";
        case TAC_VAR_CHAR_DECLARATION:
            return "TAC_VAR_CHAR_DECLARATION";
        case TAC_VAR_FLOAT_DECLARATION:
            return "TAC_VAR_FLOAT_DECLARATION";
        case TAC_ARRAY_INT_DECLARATION:
            return "TAC_ARRAY_INT_DECLARATION";
        case TAC_ARRAY_CHAR_DECLARATION:
            return "TAC_ARRAY_CHAR_DECLARATION";
        case TAC_ARRAY_FLOAT_DECLARATION:
            return "TAC_ARRAY_FLOAT_DECLARATION";
        case TAC_PAR_INT_DECLARATION:
            return "TAC_PAR_INT_DECLARATION";
        case TAC_PAR_CHAR_DECLARATION:
            return "TAC_PAR_CHAR_DECLARATION";
        case TAC_PAR_FLOAT_DECLARATION:
            return "TAC_PAR_FLOAT_DECLARATION";
        case TAC_PROCEDURE_INT_DEC:
            return "TAC_PROCEDURE_INT_DEC";
        case TAC_PROCEDURE_CHAR_DEC:
            return "TAC_PROCEDURE_CHAR_DEC";
        case TAC_PROCEDURE_FLOAT_DEC:
            return "TAC_PROCEDURE_FLOAT_DEC";
        default:
            return "?";
    }
}   

void registerAddedTempSymbol(SymbolTableNode* tempSymbolAdded){
    listOfTempSymbolsAdded[countOfTempSymbolsAdded++] = tempSymbolAdded;
}

void registerAddedLabel(SymbolTableNode* tempSymbolAdded){
    listOfTempSymbolsAdded[countOfTempSymbolsAdded++] = tempSymbolAdded;
}
