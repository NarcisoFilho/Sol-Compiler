#include "AST.h"

AST* globalAST;

void setGlobalAST(AST* ast){
	globalAST = ast;
}

AST* astCreate(SymbolTableNode *symbol, enum AST_TYPE type, ...){
	AST* tree = NULL;
	tree = calloc(1, sizeof(AST));
	tree->symbol = symbol;
	tree->type = type;
	tree->father = NULL;

	int sonsCount = getSonsCountFromType(type);

	if(sonsCount > 0 ){
		tree->sons = calloc(sonsCount, sizeof(AST*));

		va_list args;
		va_start(args, type);
		
		for(int i = 0 ; i < sonsCount ; i++){		
			tree->sons[i] = va_arg(args, struct AST *);
			if(tree->sons[i] != NULL)
				tree->sons[i]->father = tree;
		}

		va_end(args);
	}
		
	return tree;
}

void setRC(AST* ast, RC rc){
	ast->row = rc.row;
	ast->col = rc.col;
}

void astPrint(AST *node, int level){	
	if(node != NULL){
		for(int tabs = 0; tabs < level; tabs++)
			printf ("  ");
				
		printf ("%s", getTypeName(node->type));

		if(node->symbol != NULL){
			if(node->symbol->value != NULL){
				printf(": %s", node->symbol->value);
			}
		}
		
		printf(" \n");

		int sonsCount = getSonsCountFromType(node->type);
		
		for(int sonIndex = 0; sonIndex < sonsCount; sonIndex++)
			astPrint(node->sons[sonIndex], level + 1);
	}
}

void astExportProgram(FILE* outputFile){
	astGenerateCode(globalAST, outputFile, 0, 1);
}

void applyIdentation(FILE* outputFile, int level, int newLine){
	if(newLine != 0){
		for(;level; level--){
			fprintf(outputFile, "\t");
		}
	}
}

void astGenerateCode(AST* node, FILE* outputFile, int indentationLevel, int newLine){
	if(node != NULL){
		switch(node->type){
			case AST_FULL_PROG:
				astGenerateCode(node->sons[0], outputFile, indentationLevel, 1);
				fprintf(outputFile, "\n");
				astGenerateCode(node->sons[1], outputFile, indentationLevel, 1);
				break;
			case AST_HEADER:
				astGenerateCode(node->sons[0], outputFile, indentationLevel, 1);
				break;
			case AST_DECLARATION_LIST:
				astGenerateCode(node->sons[0], outputFile, indentationLevel, 1);
				astGenerateCode(node->sons[1], outputFile, indentationLevel, 1);
				break;
			case AST_VAR_DECLARATION:
				astGenerateCode(node->sons[0], outputFile, indentationLevel, 1);
				fprintf(outputFile, " %s = ", node->symbol->value);
				astGenerateCode(node->sons[1], outputFile, indentationLevel, 1);
				fprintf(outputFile, ";\n");
				break;
			case AST_ARRAY_DECLARATION:
				astGenerateCode(node->sons[0], outputFile, indentationLevel, 1);
				fprintf(outputFile, " %s[", node->symbol->value);
				astGenerateCode(node->sons[1], outputFile, indentationLevel, 1);
				fprintf(outputFile, "];\n");
				break;
			case AST_ARRAY_DEC_AND_INIT:
				astGenerateCode(node->sons[0], outputFile, indentationLevel, 1);
				fprintf(outputFile, " %s[", node->symbol->value);
				astGenerateCode(node->sons[1], outputFile, indentationLevel, 1);
				fprintf(outputFile, "] ");
				astGenerateCode(node->sons[2], outputFile, indentationLevel, 1);
				fprintf(outputFile, ";\n");
				break;
			case AST_FUNCTION_DECLARATION:
				astGenerateCode(node->sons[0], outputFile, indentationLevel, 1);
				fprintf(outputFile, " %s(", node->symbol->value);
				astGenerateCode(node->sons[1], outputFile, indentationLevel, 1);
				fprintf(outputFile, ");\n");
				break;

			case AST_FUNCTION_IMPLEMENTATION_LIST:
				astGenerateCode(node->sons[0], outputFile, indentationLevel, 1);
				fprintf(outputFile, "\n");
				astGenerateCode(node->sons[1], outputFile, indentationLevel, 1);
				break;

			case AST_CHAR:
				fprintf(outputFile, "char");
				break;
			case AST_INT:
				fprintf(outputFile, "int");
				break;
			case AST_FLOAT:
				fprintf(outputFile, "float");
				break;
			case AST_ADD:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " + ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_SUB:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " - ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_MUL:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " * ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_DIV:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " / ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_OPERATOR_LE:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " <= ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_OPERATOR_GE:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " >= ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_OPERATOR_EQ:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " == ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_OPERATOR_DIF:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " != ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_GREATER_THAN:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " > ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_LESS_THAN:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " < ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_AND:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " & ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_OR:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " | ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_NOT:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, " ~ ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			
			case AST_FUNCTION_IMPLEMENTATION:
				fprintf(outputFile, "code %s ", node->symbol->value);
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);

				break;
			case AST_PRINT:
				applyIdentation(outputFile, indentationLevel, newLine);
			
				fprintf(outputFile, "print ");
				astGenerateCode(node->sons[0],outputFile, indentationLevel, newLine);
				fprintf(outputFile, ";\n");
				break;
			case AST_INPUT:
				applyIdentation(outputFile, indentationLevel, newLine);
				
				fprintf(outputFile, "input(");
				astGenerateCode(node->sons[0],outputFile, indentationLevel, newLine);
				fprintf(outputFile, ")");
				break;
			case AST_RETURN:
				applyIdentation(outputFile, indentationLevel, newLine);

				fprintf(outputFile, "return ");
				astGenerateCode(node->sons[0],outputFile, indentationLevel, newLine);
				fprintf(outputFile, ";\n");
				break;
			case AST_ASSIGNMENT:
				applyIdentation(outputFile, indentationLevel, newLine);

				fprintf(outputFile, "%s = ", node->symbol->value);
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, ";\n");
				break;
			case AST_ARRAY_ASSIGN:
				applyIdentation(outputFile, indentationLevel, newLine);

				fprintf(outputFile, "%s[", node->symbol->value);
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, "] = ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				fprintf(outputFile, ";\n");
				break;
			case AST_WHILE:
				applyIdentation(outputFile, indentationLevel, 1);

				fprintf(outputFile, "while(");
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, ") ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_IF_THEN:
				applyIdentation(outputFile, indentationLevel, 1);

				fprintf(outputFile, "if(");
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, ") ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				break;
			case AST_IF_THEN_ELSE:
				applyIdentation(outputFile, indentationLevel, 1);

				fprintf(outputFile, "if(");
				astGenerateCode(node->sons[0],outputFile, indentationLevel, 0);
				fprintf(outputFile, ") ");
				astGenerateCode(node->sons[1],outputFile, indentationLevel, 0);
				
				applyIdentation(outputFile, indentationLevel, 1);
				fprintf(outputFile, "else ");
				astGenerateCode(node->sons[2],outputFile, indentationLevel, 0);
				break;
			case AST_FUNCTION_CALLING:
				// applyIdentation(outputFile, indentationLevel, newLine);

				fprintf(outputFile, "%s(", node->symbol->value);
				astGenerateCode(node->sons[0],outputFile, indentationLevel, newLine);
				fprintf(outputFile, ")");
				break;
			case AST_SYMBOL:
				fprintf(outputFile, "%s",node->symbol->value);
				break;
			case AST_ARRAY_EXPR:    
				fprintf(outputFile, "%s[", node->symbol->value);
				astGenerateCode(node->sons[0],outputFile, indentationLevel, newLine);
				fprintf(outputFile, "]");
				break;
			case AST_CMD_BLOCK:
				applyIdentation(outputFile, indentationLevel, newLine);
				fprintf(outputFile, "{\n");
				
				astGenerateCode(node->sons[0],outputFile, indentationLevel+1, 1);
				
				applyIdentation(outputFile, indentationLevel, 1);
				fprintf(outputFile, "}\n");
				break;
			case AST_ARG_LIST:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, newLine);				
				astGenerateCode(node->sons[1],outputFile, indentationLevel, newLine);							
				break;
			case AST_LITERAL_LIST:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, newLine);
				fprintf(outputFile, " ");				
				astGenerateCode(node->sons[1],outputFile, indentationLevel, newLine);
				break;
			case AST_PARAM:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, newLine);
				fprintf(outputFile, " %s", node->symbol->value);				
				break;
			case AST_PARAM_LIST:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, newLine);
				fprintf(outputFile, ", ");				
				astGenerateCode(node->sons[1],outputFile, indentationLevel, newLine);
				break;
			case AST_CMD_LIST:
				astGenerateCode(node->sons[0],outputFile, indentationLevel, newLine);				
				astGenerateCode(node->sons[1],outputFile, indentationLevel, newLine);
				break;		
			default:
				break;
		}
	}

}

int getSonsCountFromType(enum AST_TYPE nodeType){
	switch(nodeType){
		case AST_FULL_PROG:
			return 2;
		case AST_HEADER:
			return 1;

    	case AST_DECLARATION_LIST:
			return 2;
    	case AST_VAR_DECLARATION:
			return 2;
    	case AST_ARRAY_DECLARATION:
			return 2;
    	case AST_ARRAY_DEC_AND_INIT:
			return 3;
    	case AST_FUNCTION_DECLARATION:
			return 2;

    	case AST_FUNCTION_IMPLEMENTATION_LIST:
			return 2;


		case AST_CHAR:
			return 0;
    	case AST_INT:
			return 0;
    	case AST_FLOAT:
			return 0;
    	case AST_ADD:
			return 2;
    	case AST_SUB:
			return 2;
    	case AST_MUL:
			return 2;
    	case AST_DIV:
			return 2;
    	case AST_OPERATOR_LE:
			return 2;
    	case AST_OPERATOR_GE:
			return 2;
    	case AST_OPERATOR_EQ:
			return 2;
    	case AST_OPERATOR_DIF:
			return 2;
    	case AST_GREATER_THAN:
			return 2;
    	case AST_LESS_THAN:
			return 2;
    	case AST_AND:
			return 2;
    	case AST_OR:
			return 2;
    	case AST_NOT:
			return 1;
    	case AST_FUNCTION_IMPLEMENTATION:
			return 1;
    	case AST_PRINT:
			return 1;
    	case AST_INPUT:
			return 1;
    	case AST_RETURN:
			return 1;
    	case AST_ASSIGNMENT:
			return 1;
    	case AST_ARRAY_ASSIGN:
			return 2;
    	case AST_WHILE:
			return 2;
    	case AST_IF_THEN:
			return 2;
    	case AST_IF_THEN_ELSE:
			return 3;
    	case AST_FUNCTION_CALLING:
			return 1;
    	case AST_SYMBOL:
			return 0;
		case AST_ARRAY_EXPR:    
			return 1;
    	case AST_CMD_BLOCK:
			return 1;
    	case AST_ARG_LIST:
			return 2;
    	case AST_LITERAL_LIST:
			return 2;
		case AST_PARAM:
			return 1;
    	case AST_PARAM_LIST:
			return 2;
		
		
    	case AST_CMD_LIST:
			return 2;
		default:
			return 1;
		}
}

char* getTypeName(enum AST_TYPE nodeType){
	switch(nodeType){
		case AST_FULL_PROG:
			return strgfy(AST_FULL_PROG);
		case AST_HEADER:
			return strgfy(AST_HEADER);
		case AST_CHAR:
			return strgfy(AST_CHAR);
    	case AST_INT:
			return strgfy(AST_INT);
    	case AST_FLOAT:
			return strgfy(AST_FLOAT);
    	case AST_ADD:
			return  strgfy(AST_ADD);
    	case AST_SUB:
			return  strgfy(AST_SUB);
    	case AST_MUL:
			return  strgfy(AST_MUL);
    	case AST_DIV:
			return  strgfy(AST_DIV);
    	case AST_OPERATOR_LE:
			return  strgfy(AST_OPERATOR_LE);
    	case AST_OPERATOR_GE:
			return  strgfy(AST_OPERATOR_GE);
    	case AST_OPERATOR_EQ:
			return  strgfy(AST_OPERATOR_EQ);
    	case AST_OPERATOR_DIF:
			return  strgfy(AST_OPERATOR_DIF);
    	case AST_GREATER_THAN:
			return  strgfy(AST_GREATER_THAN);
    	case AST_LESS_THAN:
			return  strgfy(AST_LESS_THAN);
    	case AST_AND:
			return  strgfy(AST_AND);
    	case AST_OR:
			return  strgfy(AST_OR);
    	case AST_NOT:
			return  strgfy(AST_NOT);
    	case AST_FUNCTION_DECLARATION:
			return  strgfy(AST_FUNCTION_DECLARATION);
    	case AST_FUNCTION_IMPLEMENTATION:
			return  strgfy(AST_FUNCTION_IMPLEMENTATION);
    	case AST_PRINT:
			return  strgfy(AST_PRINT);
    	case AST_INPUT:
			return  strgfy(AST_INPUT);
    	case AST_RETURN:
			return  strgfy(AST_RETURN);
    	case AST_ASSIGNMENT:
			return  strgfy(AST_ASSIGNMENT);
    	case AST_ARRAY_ASSIGN:
			return  strgfy(AST_ARRAY_ASSIGN);
    	case AST_WHILE:
			return  strgfy(AST_WHILE);
    	case AST_IF_THEN:
			return  strgfy(AST_IF_THEN);
    	case AST_IF_THEN_ELSE:
			return  strgfy(AST_IF_THEN_ELSE);
    	case AST_FUNCTION_CALLING:
			return  strgfy(AST_FUNCTION_CALLING);
    	case AST_SYMBOL:
			return  strgfy(AST_SYMBOL);
    	case AST_ARRAY_EXPR:    
			return  strgfy(AST_ARRAY_EXPR);
    	case AST_FUNCTION_IMPLEMENTATION_LIST:
			return  strgfy(AST_FUNCTION_IMPLEMENTATION_LIST);
    	case AST_CMD_LIST:
			return  strgfy(AST_CMD_LIST);
    	case AST_LITERAL_LIST:
			return  strgfy(AST_LITERAL_LIST);
    	case AST_VAR_DECLARATION:
			return  strgfy(AST_VAR_DECLARATION);
    	case AST_ARRAY_DECLARATION:
			return  strgfy(AST_ARRAY_DECLARATION);
    	case AST_ARRAY_DEC_AND_INIT:
			return  strgfy(AST_ARRAY_DEC_AND_INIT);
    	case AST_DECLARATION_LIST:
			return  strgfy(AST_DECLARATION_LIST);
    	case AST_PARAM_LIST:
			return  strgfy(AST_PARAM_LIST);
    	case AST_PARAM:
			return  strgfy(AST_PARAM);
    	case AST_CMD_BLOCK:
			return strgfy(AST_CMD_BLOCK);
    	case AST_ARG_LIST:
			return strgfy(AST_ARG_LIST);
		default:
			return "AST_UNDEFINED";
		}
}

int calculateSonsCount(AST ast){
	return sizeof(ast) / sizeof(AST);
}
