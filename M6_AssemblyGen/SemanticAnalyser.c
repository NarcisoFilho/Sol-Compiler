#include "SemanticAnalyser.h"

int semanticErrorsCount = 0;
SemanticError semanticErrors[100];

bool checkSemantic(AST *ast){
	if(ast != NULL){
		for(int i = 0; i < getSonsCountFromType(ast->type); i++){
			checkSemantic(ast->sons[i]);
		}

		switch(ast->type){
			case AST_FULL_PROG:
			case AST_HEADER: 
				if(semanticErrorsCount == 0 ){
					return true;
				}else{
					alertAllErrors();
					return false;
				}
			case AST_VAR_DECLARATION:
				if(verifyIDUnicity(ast)){
					defineIDSymbolDataType(ast);
				}
				setASTDataType(ast, ast->sons[0]->dataType);
				verifyInitCompatibility(ast);
				break;
			case AST_ARRAY_DECLARATION: 
				if(verifyIDUnicity(ast)){
					defineIDSymbolDataType(ast);
				}
				setASTDataType(ast, ast->sons[0]->dataType);
				verifyArrayIndexType(ast);
				break;
			case AST_ARRAY_DEC_AND_INIT: 
				if(verifyIDUnicity(ast)){
					defineIDSymbolDataType(ast);
				}
				setASTDataType(ast, ast->sons[0]->dataType);
				verifyInitCompatibility(ast);
				if(verifyArrayIndexType(ast)){
					checkArraySizeRestrictions(ast);
				}
				break;
			case AST_FUNCTION_DECLARATION: 
				if(verifyIDUnicity(ast)){
					defineIDSymbolDataType(ast);
					defineFormalParameters(ast);
				}
				setASTDataType(ast, ast->sons[0]->dataType);
				break;
			case AST_PARAM:
				if(verifyIDUnicity(ast)){
					defineIDSymbolDataType(ast);
				}
				break;

			case AST_ADD: 
			case AST_SUB: 
			case AST_MUL: 
			case AST_DIV:{ 
				DataType resultDataType = calculateOutcomeDatatype(ast->sons[0]->dataType, ast->sons[1]->dataType);
				setASTDataType(ast, resultDataType);
				if(resultDataType == ERROR_DATA_TYPE){
					SemanticError se;
					se.ast = ast;
					se.row = -1;
					se.col = -1;
					se.errorType = SE_INCOMPATIBLE_OPERAND_TYPES;
					pushSError(se);
				}
			}
				break;
			case AST_OPERATOR_LE: 
			case AST_OPERATOR_GE: 
			case AST_OPERATOR_EQ: 
			case AST_OPERATOR_DIF: 
			case AST_GREATER_THAN: 
			case AST_LESS_THAN: 
				if(verifyDataTypesCompatibility(ast->sons[0]->dataType, ast->sons[1]->dataType)){
					setASTDataType(ast, BOOLEAN_DATA_TYPE);					
				}else{
					setASTDataType(ast, ERROR_DATA_TYPE);
					SemanticError se;
					se.ast = ast;
					se.row = -1;
					se.col = -1;
					se.errorType = SE_INCOMPATIBLE_OPERAND_TYPES;
					pushSError(se);				
				}
				break;
			case AST_AND: 
			case AST_OR: 
				if(ast->sons[0]->dataType == BOOLEAN_DATA_TYPE  &&  ast->sons[1]->dataType == BOOLEAN_DATA_TYPE){
					setASTDataType(ast, BOOLEAN_DATA_TYPE);
				}else if((ast->sons[0]->dataType == ERROR_DATA_TYPE  || ast->sons[0]->dataType == UNDEF_DATA_TYPE)
				&& (ast->sons[1]->dataType == ERROR_DATA_TYPE  || ast->sons[1]->dataType == UNDEF_DATA_TYPE)){
					setASTDataType(ast, UNDEF_DATA_TYPE);
				}else{
					setASTDataType(ast, ERROR_DATA_TYPE);
					SemanticError se;
					se.ast = ast;
					se.row = -1;
					se.col = -1;
					se.errorType = SE_NOT_BOOLEAN_OPERANDS;
					pushSError(se);				
				}
				break;
			case AST_NOT: 
				if(ast->sons[0]->dataType == BOOLEAN_DATA_TYPE){
					setASTDataType(ast, BOOLEAN_DATA_TYPE);
				}else if(ast->sons[0]->dataType != ERROR_DATA_TYPE  && ast->sons[0]->dataType != UNDEF_DATA_TYPE){
					setASTDataType(ast, BOOLEAN_DATA_TYPE);
					SemanticError se;
					se.ast = ast;
					se.row = -1;
					se.col = -1;
					se.errorType = SE_NOT_BOOLEAN_OPERANDS;
					pushSError(se);				
				}
				
				break;

			case AST_FUNCTION_IMPLEMENTATION:
				if(checkFunctionReimplementation(ast)){
					if(checkFunctionDeclaration(ast)){
						setASTDataType(ast, ast->symbol->dataType);
						ast->symbol->type = FUNCTION_IMPLEMENTED_ID_TOKEN;
					}
				}
				break;

			case AST_INPUT: 
				if(ast->sons[0] != NULL){
					setASTDataType(ast, ast->sons[0]->dataType);
				}else{
					setASTDataType(ast, UNDEF_DATA_TYPE);
				}
				break;
			case AST_RETURN: 
				setASTDataType(ast, ast->sons[0]->dataType);
				AST* functionScope = findFunctionScope(ast);
				if(functionScope != NULL){
					if(!verifyDataTypesCompatibility(ast->dataType, functionScope->dataType)){
						SemanticError se;
						se.ast = ast;
						se.row = -1;
						se.col = -1;
						se.errorType = SE_INVALID_RETURN_DATA_TYPE;
						pushSError(se);
					}
				}
				break;
			case AST_ASSIGNMENT: 
				if(checkIfIsVarID(ast)){
					checkAssignmentDataTypeCompatibility(ast);
					setASTDataType(ast, ast->symbol->dataType);
				}else{
					setASTDataType(ast, UNDEF_DATA_TYPE);
				}
				break;
			case AST_ARRAY_ASSIGN: 
				if(checkIfIsArrayID(ast)){
					verifyArrayIndexType(ast);
					setASTDataType(ast, ast->symbol->dataType);
					checkAssignmentDataTypeCompatibility(ast);
				}else{
					setASTDataType(ast, UNDEF_DATA_TYPE);
				}
				break;

			case AST_WHILE:
			case AST_IF_THEN: 
			case AST_IF_THEN_ELSE: 
				if(ast->sons[0] != NULL){
					if(ast->sons[0]->dataType != BOOLEAN_DATA_TYPE){
						if(ast->sons[0]->dataType != UNDEF_DATA_TYPE){
							if(ast->sons[0]->dataType != ERROR_DATA_TYPE){
								SemanticError se;
								se.ast = ast;
								se.row = -1;
								se.col = -1;
								se.errorType = SE_CONDITION_EXPRESSION_NOT_BOOLEAN;
								pushSError(se);
							}
						}
					}
				}
				break;
			case AST_FUNCTION_CALLING: 
				if(checkIfIsFunctionID(ast)){
					checkFunctionCalling(ast);
				}else{
					setASTDataType(ast, UNDEF_DATA_TYPE);
				}
				break;
			case AST_ARRAY_EXPR: 
				if(checkIfIsArrayID(ast)){
					verifyArrayIndexType(ast);
					setASTDataType(ast, ast->symbol->dataType);
				}else{
					setASTDataType(ast, UNDEF_DATA_TYPE);
				}
				break;
			case AST_CMD_BLOCK: 
				break;
			case AST_CMD_LIST: 
				break;
			case AST_ARG_LIST: 
				if(ast->sons[1] == NULL){
					if(ast->sons[0] != NULL){
						ast->dataType = ast->sons[0]->dataType;
					}
				}
				break;
			case AST_LITERAL_LIST: 
				determineListType(ast);
				break;			

			case AST_SYMBOL: 
				checkIdentifierDeclaration(ast);
				determineLiteralDataType(ast);
				setASTDataType(ast, ast->symbol->dataType);
				break;
			case AST_CHAR: 
				setASTDataType(ast, CHAR_DATA_TYPE);
				break;
			case AST_INT: 
				setASTDataType(ast, INT_DATA_TYPE);
				break;
			case AST_FLOAT: 
				setASTDataType(ast, REAL_DATA_TYPE);
				break;
		}
	}

	return true;
}

void checkDeclarationStatement(AST* ast){
	if(ast != NULL){
		switch(ast->type){
			case AST_VAR_DECLARATION:
			case AST_ARRAY_DECLARATION:
			case AST_ARRAY_DEC_AND_INIT:
			case AST_FUNCTION_DECLARATION:
				if(verifyIDUnicity(ast)){
					defineIDSymbolDataType(ast);
				}
				verifyInitCompatibility(ast);
				verifyArrayIndexType(ast);
				break;
		}
	}
}

bool verifyIDUnicity(AST* ast){
	if(ast != NULL){
		if(ast->symbol != NULL){
			if(ast->symbol->type == TK_IDENTIFIER_TOKEN){
				redefineIDSymbolType(ast);
				return true;
			}else{
				SemanticError serror;
				serror.ast = ast;
				serror.row = -1;
				serror.col = -1;
				serror.errorType = SE_REDECLARATION;
				pushSError(serror);
				return false;
			}
		}
	}
	return false;
}

void redefineIDSymbolType(AST* ast){
	if(ast != NULL){
		if(ast->symbol != NULL){
			switch(ast->type){
				case AST_VAR_DECLARATION:
					ast->symbol->type = VARIABLE_ID_TOKEN;
					break;
				case AST_ARRAY_DECLARATION:
				case AST_ARRAY_DEC_AND_INIT:
					ast->symbol->type = ARRAY_ID_TOKEN;
					break;
				case AST_FUNCTION_DECLARATION:
					ast->symbol->type = FUNCTION_ID_TOKEN;
					break;
				case AST_PARAM:
					ast->symbol->type = PARAM_ID_TOKEN;
					break;
			}
		}
	}
}

void defineIDSymbolDataType(AST* ast){
	if(ast != NULL){
		if(ast->symbol != NULL){
			switch(ast->symbol->type){
				case VARIABLE_ID_TOKEN:
				case ARRAY_ID_TOKEN:
				case FUNCTION_ID_TOKEN:
					ast->symbol->dataType = ast->sons[0]->dataType;
					break;
				case PARAM_ID_TOKEN:
					ast->symbol->dataType = ast->sons[0]->dataType;
					break;
			}
		}
	}
}

void verifyInitCompatibility(AST* ast){
	if(ast != NULL){
		SemanticError serror;
		serror.ast = ast;
		serror.row = -1;
		serror.col = -1;
		serror.errorType = SE_DATA_TYPE_INCOMPATIBILITY;

		if(ast->type == AST_VAR_DECLARATION){
			if(!verifyDataTypesCompatibility(ast->sons[0]->dataType, ast->sons[1]->dataType)){
				pushSError(serror);
			}			
		}else if(ast->type == AST_ARRAY_DEC_AND_INIT){
			if(!verifyDataTypesCompatibility(ast->sons[0]->dataType, ast->sons[2]->dataType)){
				pushSError(serror);
			}			
		}
	}
}

void checkAssignmentDataTypeCompatibility(AST* ast){
	if(ast != NULL){
		SemanticError serror;
		serror.ast = ast;
		serror.row = -1;
		serror.col = -1;
		serror.errorType = SE_DATA_TYPE_INCOMPATIBILITY;

		if(ast->type == AST_ASSIGNMENT){
			if(!verifyDataTypesCompatibility(ast->symbol->dataType, ast->sons[0]->dataType)){
				pushSError(serror);
			}			
		}else if(ast->type == AST_ARRAY_ASSIGN){
			if(!verifyDataTypesCompatibility(ast->symbol->dataType, ast->sons[1]->dataType)){
				pushSError(serror);
			}			
		}
	}
}

bool verifyIndexType(AST* ast){
	if(ast != NULL){
		SemanticError serror;
		serror.ast = ast;
		serror.row = -1;
		serror.col = -1;
		serror.errorType = SE_INVALID_INDEX_TYPE;

		int indexSonReference = -1;
		switch(ast->type){
			case AST_ARRAY_EXPR:
				indexSonReference = 0;
				break;
			case AST_ARRAY_DECLARATION:
			case AST_ARRAY_DEC_AND_INIT:
			case AST_ARRAY_ASSIGN:
				indexSonReference = 1;
				break;
		}
		
		if(indexSonReference != -1){
			if(!isIntegerValue(ast->sons[indexSonReference]->dataType)){
				pushSError(serror);
				return false;
			}			
		}

		return true;
	}
	return false;
}

bool verifyArrayIndexType(AST* ast){
	if(ast != NULL){
		SemanticError serror;
		serror.ast = ast;
		serror.row = -1;
		serror.col = -1;

		if(ast->type == AST_ARRAY_DECLARATION || ast->type == AST_ARRAY_DEC_AND_INIT){
			if(!isIntegerValue(ast->sons[1]->dataType)){
				serror.errorType = SE_INVALID_ARRAY_SIZE_TYPE;
				pushSError(serror);
				return false;
			}			
		}else if(ast->type == AST_ARRAY_EXPR || ast->type == AST_ARRAY_ASSIGN){
			if(!isIntegerValue(ast->sons[0]->dataType)){
				serror.errorType = SE_INVALID_INDEX_TYPE;
				pushSError(serror);
				return false;
			}			
		}
	
		return true;
	}
	return false;	
}

bool verifyDataTypesCompatibility(DataType typeA, DataType typeB){
	if(typeA == typeB){
		return true;
	}else{
		if((typeA == INT_DATA_TYPE && typeB == CHAR_DATA_TYPE)
		|| (typeA == CHAR_DATA_TYPE && typeB == INT_DATA_TYPE)){
			return true;
		}else{
			return false;
		}
	}
}

bool isIntegerValue(DataType dataType){
	if(dataType == INT_DATA_TYPE || dataType == CHAR_DATA_TYPE)
		return true;
	else 
		return false;
}


void checkIdentifierDeclaration(AST* ast){
	if(ast != NULL){
		if(ast->type == AST_SYMBOL){
			if(ast->symbol != NULL){
				if(ast->symbol->type == TK_IDENTIFIER_TOKEN){
					SemanticError se;
					se.errorType = SE_UNDECLARED_IDENTIFIER;
					se.ast = ast;
					se.row = -1;
					se.col = -1;
					pushSError(se);
				}
			}
		}
	}
}

void setASTDataType(AST* ast, DataType dataType){
	if(ast != NULL){
		ast->dataType = dataType;
	}
}

DataType determineListType(AST* ast){
	if(ast != NULL){
		if(ast->type == AST_LITERAL_LIST){
			DataType type1 = ast->sons[0]->dataType;
			DataType type2 = determineListType(ast->sons[1]);

			return ast->dataType = calculateOutcomeDatatype(type1, type2);
		}else{
			return ast->dataType = ast->dataType;
		}
	}
	return false;
}

DataType calculateOutcomeDatatype(DataType type1, DataType type2){
	if(type1 == ERROR_DATA_TYPE || type2 == ERROR_DATA_TYPE
	|| type1 == UNDEF_DATA_TYPE || type2 == UNDEF_DATA_TYPE){
		return UNDEF_DATA_TYPE;
	}else if(type1 == type2){
		return type1;
	}else if((type1 == INT_DATA_TYPE && type2 == CHAR_DATA_TYPE)
	||(type1 == CHAR_DATA_TYPE && type2 == INT_DATA_TYPE)){
		return INT_DATA_TYPE;
	}else{
		return ERROR_DATA_TYPE;
	}
}

void determineLiteralDataType(AST* ast){
	if(ast != NULL){
		if(ast->type == AST_SYMBOL && ast->symbol != NULL){
			switch(ast->symbol->type){
				case LIT_INT_TOKEN:
					ast->dataType = ast->symbol->dataType = INT_DATA_TYPE;
					break;
				case LIT_CHAR_TOKEN:
					ast->dataType = ast->symbol->dataType = CHAR_DATA_TYPE;
					break;
				case LIT_REAL_TOKEN:
					ast->dataType = ast->symbol->dataType = REAL_DATA_TYPE;
					break;
				case LIT_STRING_TOKEN:
					ast->dataType = ast->symbol->dataType = STRING_DATA_TYPE;
					break;
			}
		}
	}
}

int calculateLiteralListSize(AST* ast){
	if(ast->type == AST_LITERAL_LIST){
		return 1 + calculateLiteralListSize(ast->sons[1]);
	}else if(ast->type == AST_SYMBOL){ 
		return 1;
	}
	return 0;
}

void checkArraySizeRestrictions(AST* ast){
	if(ast != NULL){
		int arraySize = atoi(ast->sons[1]->symbol->value);
		int arrayElementsNumber = calculateLiteralListSize(ast->sons[2]);

		if(arrayElementsNumber > arraySize){
			SemanticError se;
			se.ast = ast;
			se.row = -1;
			se.col = -1;
			se.errorType = SE_INVALID_INIT_LIST_SIZE;
			pushSError(se);
		}
	}
}

bool checkFunctionDeclaration(AST* ast){
	if(ast != NULL){
		if(ast->symbol != NULL){
			if(ast->symbol->type != FUNCTION_ID_TOKEN){
				SemanticError se;
				se.ast = ast;
				se.row = -1;
				se.col = -1;
				se.errorType = SE_UNDECLARED_FUNCTION;
				pushSError(se);
				return true;
			}
		}
	}
	return false;
}

bool checkFunctionReimplementation(AST* ast){
	if(ast != NULL){
		if(ast->symbol != NULL){
			if(ast->symbol->type == FUNCTION_IMPLEMENTED_ID_TOKEN){
				SemanticError se;
				se.ast = ast;
				se.row = -1;
				se.col = -1;
				se.errorType = SE_FUNCTION_IMPLEMENTED_TWICE;
				pushSError(se);
				return false;	
			}
			return true;
		}
	}
	return false;
}

bool checkFunctionImplementation(AST* ast){
	if(ast != NULL){
		if(ast->symbol != NULL){
			SemanticError se;
			se.ast = ast;
			se.row = -1;
			se.col = -1;
			if(ast->symbol->type == FUNCTION_ID_TOKEN){
				se.errorType = SE_UNIMPLEMENTED_FUNCTION;
				pushSError(se);
				return false;
			}
		}
		return true;
	}
	return false;
}

bool verifyIfIsIDType(AST* ast, TokensTypes type){
	if(ast != NULL){
		if(ast->symbol != NULL){
			if(ast->symbol->type == type){
				return true;
			}
		}
	}
	return false;
}

bool checkIfIsArrayID(AST* ast){
	if(!verifyIfIsIDType(ast, ARRAY_ID_TOKEN)){
		SemanticError se;
		se.ast = ast;
		se.row = -1;
		se.col = -1;
		se.errorType = SE_NOT_ARRAY_ID;
		pushSError(se);
		return false;
	}
	return true;
}

bool checkIfIsVarID(AST* ast){
	if(!verifyIfIsIDType(ast, VARIABLE_ID_TOKEN)){
		SemanticError se;
		se.ast = ast;
		se.row = -1;
		se.col = -1;
		se.errorType = SE_NOT_VAR_ID;
		pushSError(se);
		return false;
	}
	return true;
}

bool checkIfIsFunctionID(AST* ast){
	if(!verifyIfIsIDType(ast, FUNCTION_ID_TOKEN) && !verifyIfIsIDType(ast, FUNCTION_IMPLEMENTED_ID_TOKEN)){
		SemanticError se;
		se.ast = ast;
		se.row = -1;
		se.col = -1;
		se.errorType = SE_NOT_FUNC_ID;
		pushSError(se);
		return false;
	}
	return true;
}

void checkFunctionCalling(AST* ast){
	if(ast != NULL){
		if(ast->type == AST_FUNCTION_CALLING){
			// SemanticError se;
			// se.ast = ast;
			// se.row = -1;
			// se.col = -1;
			if(checkFunctionDeclaration(ast)){
				setASTDataType(ast, ast->symbol->dataType);
				// if(!checkFunctionImplementation(ast)){					
					// se.errorType = SE_UNIMPLEMENTED_FUNCTION;
					// pushSError(se);
				// }
				checkArgumentsProvided(ast);
			}
			// else{
			// 	setASTDataType(ast, UNDEF_DATA_TYPE);
			// 	se.errorType = SE_UNDECLARED_FUNCTION;
			// 	pushSError(se);
			// }
		}
	}

}

void checkArgumentsProvided(AST* ast){
	if(ast != NULL){
		if(ast->type == AST_FUNCTION_CALLING){
			if(ast->symbol != NULL){
				SemanticError se;
				se.ast = ast;
				se.row = -1;
				se.col = -1;

				int parametersCount = ast->symbol->parametersCount;

				if(parametersCount > 0){
					int providedArgumentsCount = calculateArgumentsListSize(ast->sons[0]);
					if(providedArgumentsCount != parametersCount){
						se.errorType = SE_UNEXPECTED_ARGUMENTS_COUNT;
						if(ast->sons[0] != NULL){
							se.row = ast->sons[0]->row;
							se.col = ast->sons[0]->col;
						}
						pushSError(se);
					}
					
					int maxIndex = (providedArgumentsCount < parametersCount) ? providedArgumentsCount : parametersCount;
					AST* argumentsList = ast->sons[0];
					int a = 0;
					while(a < maxIndex  &&  argumentsList != NULL){
						if(argumentsList->sons[0] != NULL){
							if(ast->symbol->parameters[a] != NULL){
								if(!verifyDataTypesCompatibility(argumentsList->sons[0]->dataType, ast->symbol->parameters[a]->dataType)){
									se.errorType = SE_UNEXPECTED_ARGUMENTS_TYPE;
									se.row = ast->sons[0]->row;
									se.col = ast->sons[0]->col;
									pushSError(se);
								}		
							}
						}
						argumentsList = argumentsList->sons[1];
						a++;
					}

				}
			}
		}
	}
}

int calculateParametersCount(AST* ast){
	if(ast != NULL){
		if(ast->type == AST_PARAM_LIST){
			return 1 + calculateParametersCount(ast->sons[1]);
		}else if(ast->type == AST_PARAM){
			return 1;
		}
	}
	return 0;
}

int calculateArgumentsListSize(AST* ast){
	if(ast != NULL){
		if(ast->type == AST_ARG_LIST){
			if(ast->sons[1] != NULL){
				return 1 + calculateArgumentsListSize(ast->sons[1]);
			}else if(ast->sons[0] != NULL){
				return 1;
			}
		}
	}
	return 0;
}

void specifyParametersInSymbol(SymbolTableNode* symbol, AST* parameterList){
	if(parameterList != NULL && symbol != NULL){
		if(parameterList->type == AST_PARAM_LIST){
			specifyParametersInSymbol(symbol, parameterList->sons[0]);
			specifyParametersInSymbol(symbol, parameterList->sons[1]);
		}else if(parameterList->type == AST_PARAM){
			symbol->parameters[symbol->parametersCount++] = parameterList->symbol;
		}
	}
}

void defineFormalParameters(AST* ast){
	if(ast != NULL){
		if(ast->type == AST_FUNCTION_DECLARATION && ast->symbol != NULL){
			ast->symbol->parametersCount = 0;
			int estimatedCount = calculateParametersCount(ast->sons[1]);
			if( estimatedCount > 0){
				AST* paramList = ast->sons[1];
				ast->symbol->parameters = (SymbolTableNode**)calloc(estimatedCount, sizeof(SymbolTableNode*));
				specifyParametersInSymbol(ast->symbol, paramList);
			}else{
				ast->symbol->parameters = NULL;
			}
		}
	}
}

AST* findFunctionScope(AST* ast){
	AST* tree = ast;

	while(tree != NULL  &&  tree->type != AST_FUNCTION_IMPLEMENTATION){
		tree = tree->father;
	}
	if(tree != NULL){
		return tree;
	}else{
		return NULL;
	}
}

void pushSError(SemanticError se){
	semanticErrors[semanticErrorsCount++] = se;
}

void alertAllErrors(){
	for(int e = 0 ; e < semanticErrorsCount ; e++ ){
		alertError(semanticErrors[e]);
	}
}

void alertError(SemanticError se){
	if(se.ast != NULL){
		AST *functionScope;
		const int row = (se.row >= 0) ? se.row : se.ast->row;
		const int col = (se.col >= 0) ? se.col : se.ast->col;

		const char *symbolName = "";
		if(se.ast->symbol != NULL){
			symbolName = se.ast->symbol->value;
		}
		functionScope = findFunctionScope(se.ast);
		
		switch(se.errorType){
			case SE_REDECLARATION:
				fprintf(stderr,"Error (%d,%d): Redeclaration of identifier %s\n", row, col, symbolName);	
				break;
			case SE_UNDECLARED_IDENTIFIER:
				fprintf(stderr,"Error (%d,%d): Undeclared identifier %s\n", row, col, symbolName);	
				break;
			case SE_INVALID_ARRAY_SIZE_TYPE:
				fprintf(stderr,"Error (%d,%d): Using non-integer to specify the size of the array %s\n", row, col, symbolName);	
				break;
			case SE_INVALID_INDEX_TYPE:
				fprintf(stderr,"Error (%d,%d): Using non-integer index to access array %s\n", row, col, symbolName);	
				break;
			case SE_DATA_TYPE_INCOMPATIBILITY:
				{
					const char *dataTypeName = getDataTypeByCode(se.ast->dataType);
					fprintf(stderr,"Error (%d,%d): '%s' should be assigned with %s values\n", row, col, symbolName, dataTypeName);	
				}
				break;
			case SE_INVALID_INIT_LIST_SIZE:
				{
					int maxExpected = atoi(se.ast->sons[1]->symbol->value);
					int receivedCount = calculateLiteralListSize(se.ast->sons[2]);
					fprintf(stderr,"Error (%d,%d): Too many elements for initialization of '%s'. It was expected at most %d elements but received %d.\n", row, col, symbolName, maxExpected, receivedCount);	
				}
				break;
			case SE_INCOMPATIBLE_OPERAND_TYPES:
				fprintf(stderr,"Error (%d,%d): Incompatible operands types.\n", row, col);	
				break;
			case SE_NOT_BOOLEAN_OPERANDS:
				fprintf(stderr,"Error (%d,%d): It was expected boolean operands\n", row, col);	
				break;
			case SE_UNEXPECTED_ARGUMENTS_COUNT:
				fprintf(stderr,"Error (%d,%d): Unexpected arguments count\n", row, col);	
				break;
			case SE_UNEXPECTED_ARGUMENTS_TYPE:
				fprintf(stderr,"Error (%d,%d): Unexpected argument type\n", row, col);	
				break;
			case SE_UNDECLARED_FUNCTION:
				fprintf(stderr,"Error (%d,%d): Unknown function '%s'\n", row, col, symbolName);	
				break;
			case SE_UNIMPLEMENTED_FUNCTION:
				fprintf(stderr,"Error (%d,%d): Function '%s' implementation not found\n", row, col, symbolName);	
				break;
			case SE_NOT_VAR_ID:
				fprintf(stderr,"Error (%d,%d): '%s' is not a scalar variable\n", row, col, symbolName);	
				break;
			case SE_NOT_ARRAY_ID:
				fprintf(stderr,"Error (%d,%d): '%s' is not an array\n", row, col, symbolName);	
				break;
			case SE_NOT_FUNC_ID:
				fprintf(stderr,"Error (%d,%d): '%s' is not a function\n", row, col, symbolName);	
				break;
			case SE_CONDITION_EXPRESSION_NOT_BOOLEAN:
				fprintf(stderr,"Error (%d,%d): The condition expression of a condition statemente should be a boolean value\n", row, col);	
				break;
			case SE_INVALID_RETURN_DATA_TYPE:
				if(functionScope != NULL){
					const char *dataTypeReturnExpected = getDataTypeByCode(functionScope->dataType); 
					const char *functionName = functionScope->symbol->value; 
					fprintf(stderr,"Error (%d,%d): Invalid return data type. Function '%s' should return a value of type %s\n", row, col, functionName, dataTypeReturnExpected);	
				}else{
					fprintf(stderr,"Error (%d,%d): Invalid return data type\n", row, col);	
				}
				break;
			case SE_FUNCTION_IMPLEMENTED_TWICE:
				// fprintf(stderr,"Error (%d,%d): The condition expression of a condition statemente should be a boolean value\n", row, col);	
				break;
			default:
				break;
		}
	}
}

const char* getDataTypeByCode(DataType dataType){
	switch(dataType){
		case INT_DATA_TYPE:
			return "int";	
		case CHAR_DATA_TYPE:
			return "char";	
		case REAL_DATA_TYPE:
			return "float";	
		case BOOLEAN_DATA_TYPE:
			return "boolean";	
		case STRING_DATA_TYPE:
			return "string";	
		case UNDEF_DATA_TYPE:
			return "undef";	
		case ERROR_DATA_TYPE:
			return "error_data_type";	
		default:
			return "!?";
	}
}
