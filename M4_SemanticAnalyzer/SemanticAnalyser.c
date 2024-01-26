#include "SemanticAnalyser.h"

int semanticErrorsCount = 0;

void printSemanticErrorMessage(char* errorDescription, char* identifier){
	if(identifier == NULL){
		fprintf(stderr,"Semantic error: %s\n", errorDescription);	
	}else{
		fprintf(stderr,"Semantic error: %s (%s)\n", errorDescription, identifier);	
	}

	semanticErrorsCount++;	
}

int checkSemantic(AST *node){
	// hashCheckUndeclared();	
	// checkAstNodeDataType(node);
	// checkSymbolsUse(node);

	return semanticErrorsCount;
}

void specifyIdentifierType(AST* node, int type){
	if(node != NULL){
		if(node->symbol != NULL){
			switch(type){
				case AST_PARAM:	
					if(node->symbol->type != TK_IDENTIFIER_TOKEN){
						printSemanticErrorMessage("Redeclaration of parameter", node->symbol->value);
						return;
					}
					
					node->symbol->type = PARAM_ID_TOKEN;
					setDataType(node, node->sons[0]->type);
					break;
				case AST_VAR_DECLARATION: 				
					if(node->symbol->type != TK_IDENTIFIER_TOKEN){
						printSemanticErrorMessage("Redeclaration of variable", node->symbol->value);
						return;
					}

					node->symbol->type = VARIABLE_ID_TOKEN;
					setDataType(node, node->sons[0]->type);
					break;
				case AST_ARRAY_DECLARATION: 
					if(node->symbol->type != TK_IDENTIFIER_TOKEN){
						printSemanticErrorMessage("Redeclaration of array", node->symbol->value);
						return;
					}

					node->symbol->type = ARRAY_ID_TOKEN;
					setDataType(node, node->sons[0]->type);
					break;
				case AST_ARRAY_DEC_AND_INIT: 
					if(node->symbol->type != TK_IDENTIFIER_TOKEN){
						printSemanticErrorMessage("Redeclaration of array", node->symbol->value);
						return;
					}

					node->symbol->type = ARRAY_ID_TOKEN;
					setDataType(node, node->sons[0]->type);
					break;
				case AST_FUNCTION_DECLARATION:
					if(node->symbol->type != TK_IDENTIFIER_TOKEN){
						printSemanticErrorMessage("Function redeclaration", node->symbol->value);
						return;
					}
					node->symbol->type = FUNCTION_ID_TOKEN;
					setDataType(node, node->sons[0]->type);
					// int parametersNumber = calculateFunctionParametersNumber(node->son[0]->son[1]);
					// setNumParams(node,parametersNumber);
					break;
				case LIT_CHAR_TOKEN:
					if(node->symbol->type != TK_IDENTIFIER_TOKEN){
						printSemanticErrorMessage("Function redeclaration", node->symbol->value);
						return;
					}
					node->symbol->type = FUNCTION_ID_TOKEN;
					setDataType(node, node->sons[0]->type);
					// int parametersNumber = calculateFunctionParametersNumber(node->son[0]->son[1]);
					// setNumParams(node,parametersNumber);
					break;
			}
		}
	}
}

void specifySymbolDataType(AST* node, DataType dataType){
	if(node != NULL){
		if(node->symbol != NULL){
			if(node->type == AST_SYMBOL){
				node->symbol->dataType = dataType;
			}
		}
	}
}

int calculateFunctionParametersNumber(AST* node){
	if(!node)
		return 0;
	else
		return 1 + calculateFunctionParametersNumber(node->sons[1]);
}

void setDataType(AST *node, int type){
	switch(type){
		case AST_CHAR: node->symbol->dataType = CHAR_DATA_TYPE; break;
		case AST_INT: node->symbol->dataType = INT_DATA_TYPE; break;
		case AST_FLOAT: node->symbol->dataType = REAL_DATA_TYPE; break;
		default: node->symbol->dataType = UNDEF_DATA_TYPE; break;
	}
	// node->dataType = node->symbol->dataType;
}

bool checkAssignment(AST* astNode){
	// switch(astNode->type){
	// 	case AST_VAR_DECLARATION:
	// 		if(astNode->symbol->dataType != astNode->sons[0])
	// 		break;
	// }
	return true;
}
// void setNumParams(AST *node, int npar){
// 	int address = hash_address(node->son[0]->symbol->value);
// 	SymbolTableNode* hash = hash_find(node->son[0]->symbol->value, address);
// 	hash->params_count = npar;

// 	//for(int i = 0; i < npar; i++) {
// 	switch (npar) {
// 		case 1:
// 			hash->params_type[0] = node->son[0]->son[1]->son[0]->dataType;
// 			break;
// 		case 2:
// 			hash->params_type[0] = node->son[0]->son[1]->son[0]->dataType;
// 			hash->params_type[1] = node->son[0]->son[1]->son[1]->son[0]->dataType;
// 			break;
// 		case 3:
// 			hash->params_type[0] = node->son[0]->son[1]->son[0]->dataType;
// 			hash->params_type[1] = node->son[0]->son[1]->son[1]->son[0]->dataType;
// 			hash->params_type[2] = node->son[0]->son[1]->son[1]->son[1]->son[0]->dataType;
// 			break;
// 		case 4:
// 			hash->params_type[0] = node->son[0]->son[1]->son[0]->dataType;
// 			hash->params_type[1] = node->son[0]->son[1]->son[1]->son[0]->dataType;
// 			hash->params_type[2] = node->son[0]->son[1]->son[1]->son[1]->son[0]->dataType;
// 			hash->params_type[3] = node->son[0]->son[1]->son[1]->son[1]->son[1]->son[0]->dataType;
// 			break;
// 		default:
// 			break;
// 	}
// 	//}


// }


// void checkSymbolsUse(AST *node){
// 	if(node == NULL){
// 		return;
// 	}
	
// 	switch(node->type){
// 		case AST_ASSIGN:
// 			if(node->symbol->type != SYMBOL_VAR){
// 				printSemanticError("expressao de atribuicao invalida",NULL);
// 			}
// 			break;
// 		case AST_VEC_ASSIGN:
// 			if(node->son[0]->type == AST_DIV) {
// 				printSemanticError("indice do vetor deve ser do tipo inteiro", node->symbol->value); 
// 			} else if(node->symbol->type != SYMBOL_VEC){
// 				printSemanticError("expressao de atribuicao de vetor invalida",NULL);
// 			}
// 			break;
// 		case AST_VECTOR_EXPR:
// 			if(node->son[0]->type == AST_DIV) {
// 				printSemanticError("indice do vetor deve ser do tipo inteiro", node->symbol->value); 
// 			}else if(node->symbol->type != SYMBOL_VEC){
// 				printSemanticError("expressao de acesso ao vetor invalida",NULL);
// 			}
// 			break;
// 		case AST_FUNC_CALL:
// 			if(node->symbol->type != SYMBOL_FUNC){
// 				printSemanticError("expressao de chamada de funcao invalida",NULL);		
// 			}			
// 			break;
// 		//Somente variaveis escalares sao aceitas no comando read e nao vetores ou pos. de vetores
// 		case AST_READ:
// 			if(node->symbol->type != SYMBOL_VAR){
// 				printSemanticError("comando 'read' invalido, apenas valores escalares sao aceitos",NULL);		
// 			}			
// 			break;		
// 	}

// 	int i;
// 	for(i=0; i<MAX_SONS; i++){
// 		checkSymbolsUse(node->son[i]);
// 	}
// }

// void verifyParams(AST* node){
// 	int n_par = 0;
// 	if(node->son[0]){
// 		int val = verifyFuncCallParams(node->son[0]);
// 		if(!val) 
// 			printSemanticError("ha parametros invalidos na chamada da funcao",node->symbol->value);
// 		n_par = countFuncCallParams(node->son[0]);
// 	}		
// 	int address = hash_address(node->symbol->value);
// 	SymbolTableNode* hash = hash_find(node->symbol->value, address);
// 	int correct_n_par = hash->params_count;
// 	if(n_par != correct_n_par)
// 		printSemanticError("numero invalido de parametros na chamada da funcao",node->symbol->value);
// }

// int isType(int num) {

// 	switch (num) {

// 		case DATATYPE_BYTE:
// 		case DATATYPE_SHORT:
// 		case DATATYPE_LONG:
// 		case DATATYPE_CHAR:
// 			return 1;
// 			break;

// 		case DATATYPE_FLOAT:
// 		case DATATYPE_DOUBLE:
// 			return 2;
// 			break;

// 		case DATATYPE_STRING:
// 			return 3;
// 			break;

// 		default:
// 			return 4;
// 			break;	

// 	}

// 	return -1;

// }


// void verifyParamsType(AST* node) {

// 	// node AST_FUNC_CALL
// 	int address = hash_address(node->symbol->value);
// 	SymbolTableNode* hash = hash_find(node->symbol->value, address);
// 	int n_par = hash->params_count;

// 	//printf("HAUUAHUHAUHAUHAUHA = %d", node->son[0]->son[0]->dataType);

// 	switch(n_par) {

// 		case 1:
// 			if((isType(hash->params_type[0])) == (isType(node->son[0]->son[0]->dataType))) {
// 					//printf("TIPOS IGUAIS\n");
// 		 	} else {
// 				printSemanticError("tipos dos parametros incompativeis com a declaracao",node->symbol->value);
// 			}
// 			break;
// 		case 2:
// 			if(((isType(hash->params_type[0])) == (isType(node->son[0]->son[0]->dataType))) &&
// 			   ((isType(hash->params_type[1])) == (isType(node->son[0]->son[1]->son[0]->dataType))))  {
// 				//printf("TIPOS IGUAIS\n");
// 		 	} else {
// 				printSemanticError("tipos dos parametros incompativeis com a declaracao",node->symbol->value);
// 			}
// 			break;
// 		case 3:
// 			if(((isType(hash->params_type[0])) == (isType(node->son[0]->son[0]->dataType))) &&
// 			   ((isType(hash->params_type[1])) == (isType(node->son[0]->son[1]->son[0]->dataType))) &&   
// 			   ((isType(hash->params_type[2])) == (isType(node->son[0]->son[1]->son[1]->son[0]->dataType)))) {
// 				//printf("TIPOS IGUAIS\n");
// 		 	} else {
// 				printSemanticError("tipos dos parametros incompativeis com a declaracao",node->symbol->value);
// 			}
// 			break;
// 		case 4:
// 			if(((isType(hash->params_type[0])) == (isType(node->son[0]->son[0]->dataType))) &&
// 			   ((isType(hash->params_type[1])) == (isType(node->son[0]->son[1]->son[0]->dataType))) &&   
// 			   ((isType(hash->params_type[2])) == (isType(node->son[0]->son[1]->son[1]->son[0]->dataType))) && 
// 			   ((isType(hash->params_type[3])) == (isType(node->son[0]->son[1]->son[1]->son[1]->son[0]->dataType)))) {
// 				//printf("TIPOS IGUAIS\n");
// 		 	} else {
// 				printSemanticError("tipos dos parametros incompativeis com a declaracao",node->symbol->value);
// 			}
// 			break;
// 		default:
// 			break;
// 	}

// }



// int verifyFuncCallParams(AST* node){
// 	if(!node){
// 		return 1;
// 	}
	
// 	int acc_val = verifyFuncCallParams(node->son[1]);
// 	if(acc_val == 0){
// 		return 0;
// 	} 
	
// 	return 1; 
// }

// int countFuncCallParams(AST* node){
// 	if(!node)
// 		return 0;
// 	else
// 		return 1 + countFuncCallParams(node->son[1]);
// }

// int testID(SymbolTableNode* id,AST* node){
// 	if(id->type == SYMBOL_VEC || id->type == SYMBOL_FUNC){
// 		printSemanticError("uso invalido de vetor/funcao", id->value);
// 		node->dataType = DATATYPE_UNDEFINED;
// 		return 0;
// 	}
// 	return 1;
// }


// //TODO : verificar print
// void checkAstNodeDataType(AST *node){
// 	if(node == NULL){
// 		return;
// 	}

// 	int i;
// 	for(i=0; i<MAX_SONS; i++){
// 		checkAstNodeDataType(node->son[i]);
// 	}

// 	switch(node->type){
// 		case AST_SYMBOL:
// 			if(testID(node->symbol,node))
// 				node->dataType = node->symbol->dataType;
// 			break;		
// 		case AST_VECTOR_EXPR:
// 			if(node->son[0]->dataType != DATATYPE_LONG && 
// 				node->son[0]->dataType != DATATYPE_SHORT && 
// 				node->son[0]->dataType != DATATYPE_BYTE &&
// 				node->son[0]->dataType != DATATYPE_CHAR) {
// 				printSemanticError("indice do vetor deve ser do tipo inteiro", node->symbol->value); 
// 			}
// 			node->dataType = node->symbol->dataType;
// 			break;
// 		case AST_FUNC_CALL:  // not sure if node->symbol->dataType ou node->symbol->type
// 			// talvez uma condicao a mais se for literal
// 			verifyParams(node);
// 			verifyParamsType(node);
// 			node->dataType = node->symbol->dataType;
// 			break;
// 		case AST_LOGIC_L:
// 		case AST_LOGIC_G:
// 		case AST_LOGIC_LE:
// 		case AST_LOGIC_GE:
// 			if(node->son[0]->dataType == DATATYPE_BOOL || node->son[1]->dataType == DATATYPE_BOOL){
// 				printSemanticError("expressao booleana em operacao relacional", NULL);
// 			}
// 			if(node->son[0]->dataType == DATATYPE_UNDEFINED || node->son[1]->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("expressao UNDEFINED em operacao relacional", NULL);
// 				node->dataType = DATATYPE_UNDEFINED;
// 			}
// 			else
// 				node->dataType = DATATYPE_BOOL;
// 			break;
// 		case AST_LOGIC_EQ:
// 		case AST_LOGIC_NE:
// 			if((node->son[0]->dataType == DATATYPE_BOOL && node->son[1]->dataType != DATATYPE_BOOL) || 
// 			(node->son[1]->dataType == DATATYPE_BOOL && node->son[0]->dataType != DATATYPE_BOOL)){
// 				printSemanticError("conflito de tipos em operação de eq/ne", NULL);
// 			}
// 			if(node->son[0]->dataType == DATATYPE_UNDEFINED || node->son[1]->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("expressao UNDEFINED em operacao relacional", NULL);
// 				node->dataType = DATATYPE_UNDEFINED;
// 			}
// 			else
// 				node->dataType = DATATYPE_BOOL;
// 			break;
// 		case AST_LOGIC_AND:	
// 		case AST_LOGIC_OR:
// 			if(node->son[0]->dataType != DATATYPE_BOOL || node->son[1]->dataType != DATATYPE_BOOL){
// 				printSemanticError("expressao booleana esperada em operacao and/or", NULL); 
// 			}
// 			if(node->son[0]->dataType == DATATYPE_UNDEFINED || node->son[1]->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("expressao UNDEFINED em operacao relacional", NULL);
// 				node->dataType = DATATYPE_UNDEFINED;
// 			}
// 			else
// 				node->dataType = DATATYPE_BOOL;	
// 			break;
// 		case AST_ADD:    
// 		case AST_SUB: 
// 		case AST_MUL: 
// 		case AST_DIV: 
// 			if(node->son[0]->dataType == DATATYPE_BOOL || node->son[1]->dataType == DATATYPE_BOOL){
// 				printSemanticError("expressao booleana nao esperada em expressao aritmetica", NULL);
// 			}
// 			if(node->son[0]->dataType == DATATYPE_UNDEFINED || node->son[1]->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("expressao UNDEFINED em operacao aritmetica", NULL);
// 				node->dataType = DATATYPE_UNDEFINED;
// 			}
// 			else
// 				node->dataType = aritmeticInference(node);
// 			break;
// 		case AST_ASSIGN: 
// 			if(!verifyAssignmentTypes(node->symbol->dataType, node->son[0]->dataType)){
// 				printSemanticError("conflito de tipos na atribuicao", NULL);
// 			}
// 			if(node->son[0]->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("expressao UNDEFINED em comando ASSIGN", NULL);
// 				node->dataType = DATATYPE_UNDEFINED;
// 			}
// 			else
// 				node->dataType = node->symbol->dataType;
// 			break;
// 		case AST_VEC_ASSIGN: 
// 			if(node->son[0]->dataType != DATATYPE_LONG && node->son[0]->dataType != DATATYPE_SHORT
// 				 && node->son[0]->dataType != DATATYPE_CHAR && node->son[0]->dataType != DATATYPE_BYTE) {
// 				printSemanticError("indice do vetor em atribuicao v[indice] deve ser do tipo inteiro", node->symbol->value); 
// 			}
// 			if(!verifyAssignmentTypes(node->symbol->dataType, node->son[1]->dataType)){
// 				printSemanticError("conflito de tipos na atribuicao", NULL);
// 			}
// 			if(node->son[1]->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("expressao UNDEFINED em comando ASSIGN", NULL);
// 				node->dataType = DATATYPE_UNDEFINED;
// 			}
// 			else
// 				node->dataType = node->symbol->dataType;
// 			break;
// 		case AST_PARENTESIS_EXPR:
// 			node->dataType = node->son[0]->dataType;
// 			break;
// 		case AST_FOR:
// 			if(node->son[0]->dataType == DATATYPE_UNDEFINED || node->son[1]->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("expressao UNDEFINED em comando FOR", NULL);
// 			}	
// 			break;
// 		case AST_WHILE:
// 			if(node->son[0]->dataType != DATATYPE_BOOL){
// 				printSemanticError("expresao booleana esperada em comando WHILE", NULL);	
// 			}
// 			if(node->son[0]->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("expressao UNDEFINED em comando WHILE", NULL);
// 			}
// 			break;
// 		case AST_IF_THEN:
// 		case AST_IF_THEN_ELSE:
// 			if(node->son[0]->dataType != DATATYPE_BOOL){
// 				printSemanticError("expresao booleana esperada em comando WHEN", NULL);
// 			}
// 			if(node->son[0]->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("expressao UNDEFINED em comando WHEN", NULL);
// 			}
// 			break;		
// 		case AST_RETURN:	
// 			if(node->son[0]->dataType == DATATYPE_BOOL){
// 				printSemanticError("comando RETURN do tipo booleano nao esperado", NULL);
// 			}
// 			if(node->son[0]->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("expressao UNDEFINED em comando RETURN", NULL);
// 			}
// 			break;
// 		case AST_READ:
// 			if(node->symbol->dataType == DATATYPE_BOOL || node->symbol->dataType == DATATYPE_UNDEFINED){
// 				printSemanticError("comando READ com tipo nao esperado", NULL);
// 			}
// 			break;
// 		// print é uma lista de elementos onde cada elemento pode ser um string ou expressao aritmetica
// 		case AST_PRINT_ELEM:
// 			if(node->symbol){
// 				if(node->symbol->dataType != DATATYPE_STRING){
// 					printSemanticError("comando PRINT com simbolo nao esperado, deve ser string", NULL);
// 				}
// 			}else if(node->son[0]){
// 				if(node->son[0]->dataType == DATATYPE_BOOL || node->son[0]->dataType == DATATYPE_UNDEFINED){
// 					printSemanticError("comando PRINT com expressao nao esperada, deve ser aritmetica", NULL);
// 				}
// 			}
// 	}

// 	//printf("type: %d datatype: %d \n", node->type, node->dataType);
// }
// int aritmeticInference(AST *node){
// 	// eh soh isso ?? 
// 	return typeInference(node->son[0]->dataType, node->son[1]->dataType);

// }

// int typeInference(int type1, int type2){

// 	if(type1 == DATATYPE_DOUBLE || type2 == DATATYPE_DOUBLE){
// 		return DATATYPE_DOUBLE;
// 	}
// 	else if(type1 == DATATYPE_FLOAT || type2 == DATATYPE_FLOAT){
// 		return DATATYPE_FLOAT;
// 	}
// 	else if(type1 == DATATYPE_LONG || type2 == DATATYPE_LONG){
// 		return DATATYPE_LONG;
// 	}
// 	else if(type1 == DATATYPE_SHORT || type2 == DATATYPE_SHORT){
// 		return DATATYPE_SHORT;
// 	}
// 	else if(type1 == DATATYPE_BYTE || type2 == DATATYPE_BYTE){
// 		return DATATYPE_BYTE;
// 	}else{ 
// 		return DATATYPE_UNDEFINED;
// 	}	
// }

// int verifyAssignmentTypes(int type1, int type2){


// 	if(type1 == DATATYPE_BOOL || type2 == DATATYPE_BOOL){
// 		return 0;
// 	}
// 	if(type1 == DATATYPE_UNDEFINED || type2 == DATATYPE_UNDEFINED){
// 		return 0;
// 	}
// 	if(isType(type1) == isType(type2)){
// 		return 1;
// 	}else{
// 		return 0;
// 	}
// }

// void hashCheckUndeclared(){
// 	SymbolTableNode *node;
// 	int i;	 
// 	for(i=0; i<HASH_SIZE; i++){
// 		for(node=hash_table[i]; node; node=node->next){ 
// 			if(node->type == AST_SYMBOL){
// 				//erro variavel nao declarada
// 				printSemanticError("variavel nao declarada", node->value); 
// 			}
// 		}
// 	} 
// }
