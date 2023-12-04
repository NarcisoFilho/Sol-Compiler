#include "ASTTree.h"

ASTTree* astTreeCreate(SymbolTableNode *symbol, int type, ASTTree *son0, ASTTree *son1, ASTTree *son2, ASTTree *son3){
	ASTTree* tree = NULL;
	tree = calloc(1, sizeof(ASTTree));
	tree->symbol = symbol;
	tree->type = type;
	
	tree->sons[0] = son0;
	tree->sons[1] = son1;
	tree->sons[2] = son2;
	tree->sons[3] = son3;
	
	return tree;
}

void ASTTreePrint(ASTTree *node, int level){	
	if(node != NULL){
		for(int tabs = 0; tabs < level; tabs++)
			printf ("  ");
		
		switch(node->type){
			// case AST_SYMBOL: printf ("ASTREE_SYMBOL"); break;
			// case AST_ADD: printf ("ASTREE_ADD"); break;
			// case AST_SUB: printf ("ASTREE_SUB"); break;
			// case AST_MUL: printf ("ASTREE_MUL"); break;
			// case AST_DIV: printf ("ASTREE_DIV"); break;
			// case AST_LOGIC_G: printf ("ASTREE_LOGIC_G"); break;
			// case AST_LOGIC_L: printf ("ASTREE_LOGIC_L"); break;
			// case AST_LOGIC_LE: printf ("ASTREE_LOGIC_LE"); break;
			// case AST_LOGIC_GE: printf ("ASTREE_LOGIC_GE"); break;
			// case AST_LOGIC_EQ: printf ("ASTREE_LOGIC_EQ"); break;
			// case AST_LOGIC_NE: printf ("ASTREE_LOGIC_NE"); break;
			// case AST_LOGIC_AND: printf ("ASTREE_LOGIC_AND"); break;
			// case AST_LOGIC_OR: printf ("ASTREE_LOGIC_OR"); break;
			// case AST_LOGIC_NOT: printf ("ASTREE_LOGIC_NOT"); break;
			// case AST_VECTOR_EXPR: printf ("ASTREE_VECTOR_EXPR"); break;
			// case AST_FUNC_CALL: printf ("ASTREE_FUNC_CALL"); break;
			// case AST_LIST_ARG_BEGIN: printf ("ASTREE_LIST_ARG_BEGIN"); break;
			// case AST_ASSIGN: printf ("ASTREE_ASSIGN"); break;
			// case AST_VEC_ASSIGN: printf ("ASTREE_VEC_ASSIGN"); break;
			// case AST_READ: printf ("ASTREE_READ"); break;
			// case AST_PRINT: printf ("ASTREE_PRINT"); break;
			// case AST_PRINT_ELEM: printf ("ASTREE_PRINT_ELEM"); break;
			// case AST_RETURN: printf ("ASTREE_RETURN"); break;
			// case AST_WHEN_THEN: printf ("ASTREE_WHEN_THEN"); break;
			// case AST_WHEN_THEN_ELSE: printf ("ASTREE_WHEN_THEN_ELSE"); break;
			// case AST_WHILE: printf ("ASTREE_WHILE"); break;
			// case AST_FOR: printf ("ASTREE_FOR"); break;
			// case AST_SEQ_CMD: printf ("ASTREE_SEQ_CMD"); break;

			// case AST_CJTODEC_ELEM: printf ("AST_CJTODEC_ELEM"); break;
			// case AST_DEC_VAR_GLOB: printf ("AST_DEC_VAR_GLOB"); break;
			// case AST_DEC_VEC_GLOB: printf ("AST_DEC_VEC_GLOB"); break;
			// case AST_DEC_VEC_SEQ: printf ("AST_DEC_VEC_SEQ"); break;
			// case AST_DEC_VEC: printf ("AST_DEC_VEC"); break;
			// case AST_SEQNUM_ELEM: printf ("AST_SEQNUM_ELEM"); break;
			// case AST_DEC_FUNC: printf ("AST_DEC_FUNC"); break;
			// case AST_CABEC: printf ("AST_CABEC"); break;
			// case AST_PARAM_ELEM: printf ("ASTREE_PARAM_ELEM"); break;
			// case AST_PARAM: printf ("ASTREE_PARAM"); break;
			// case AST_BYTE: printf ("AST_BYTE"); break;
			// case AST_SHORT: printf ("AST_SHORT"); break;
			// case AST_LONG: printf ("AST_LONG"); break;
			// case AST_FLOAT: printf ("AST_FLOAT"); break;
			// case AST_DOUBLE: printf ("AST_DOUBLE"); break;

			// case AST_PARENTESIS_EXPR: printf ("ASTREE_PARENTESIS_EXPR"); break;
			// case AST_COMMAND_BLOCK: printf ("ASTREE_COMMAND_BLOCK"); break;
			// case AST_LIST_ARG_ELEM: printf ("ASTREE_LIST_ARG_ELEM"); break;

			default: printf ("ASTREE_UNDEFINED");
		}
		
		if(node->symbol != NULL){
			printf(": %s", node->symbol->value);
		}

		for(int son = 0; son < MAX_SONS_COUNT; son++)
			ASTTreePrint(node->sons[son], level + 1);
	}
}

void ASTTreeGenerateProgram (ASTTree* node, FILE* outputFileName){

}
