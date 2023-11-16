%{
    #include <stdio.h>
    #include <stdlib.h>		

    // Prototypes
	int yylex();
	void yyerror(const char*);
	int getLineNumber(void);
%}

%token KW_CHAR KW_INT KW_FLOAT
%token KW_CODE 
%token KW_IF KW_ELSE KW_WHILE
%token KW_INPUT KW_PRINT
%token KW_RETURN
%token OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%token TK_IDENTIFIER
%token LIT_INT LIT_REAL LIT_CHAR LIT_STRING
%token TOKEN_ERROR

%left '|'
%left '&'
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF '<' '>'
%left '+' '-'
%left '*' '/'
%right '~'

%union {
	struct SymbolTableNode *symbol;
}

%%
program: declarationsList codeImplementationList
    ;

// Declaration Section
declarationsList: declaration 
    | declaration declarationsList
    ;

declaration: dataType TK_IDENTIFIER '=' expression ';' 
    | dataType TK_IDENTIFIER '[' LIT_INT ']' ';'
    | dataType TK_IDENTIFIER '[' LIT_INT ']' literalsList ';'
    | dataType TK_IDENTIFIER '(' formalParameterList ')' ';'
    ;
formalParameterList: dataType TK_IDENTIFIER
    | dataType TK_IDENTIFIER ',' formalParameterList
    |
    ;

expression: literal 
    | TK_IDENTIFIER
    | literal operator expression
    | TK_IDENTIFIER operator expression
    | '(' expression ')'
    ;

literalsList: literal
    | literal literalsList
    ;

literal: LIT_INT 
    | LIT_CHAR
    | LIT_REAL
    | LIT_STRING
    ;

dataType: KW_INT 
    | KW_CHAR
    | KW_FLOAT
    ;

operator: OPERATOR_LE
    | OPERATOR_GE
    | OPERATOR_EQ
    | OPERATOR_DIF
    | '+'
    | '-'
    | '*'
    | '/'
    | '&'
    | '<'
    | '>'
    | '|'
    | '~'
    ;

// Implementation Section
codeImplementationList: codeImplementation
    | codeImplementation codeImplementationList
    ;

codeImplementation: KW_CODE TK_IDENTIFIER cmd
    ;

cmd: TK_IDENTIFIER '=' expression ';'
    | TK_IDENTIFIER '=' cmd
    | TK_IDENTIFIER '(' argumentsList ')' ';'
    | TK_IDENTIFIER '[' expression ']' '=' expression ';'
    | KW_RETURN expression ';'
    | KW_INPUT '(' dataType ')' ';'    
    | KW_PRINT expression ';'
    | KW_PRINT TK_IDENTIFIER '[' expression ']' ';'
    | KW_WHILE '(' expression ')' cmd
    | KW_IF '(' expression ')' cmd
    | KW_IF '(' expression ')' cmd KW_ELSE cmd
    | '{' cmdList '}'
    | '{' '}'
    | ';'
    ;

cmdList: cmd
    | cmd cmdList
    ;

argumentsList: argument
    | argument ',' argumentsList
    ;

argument: TK_IDENTIFIER
    | literal
    ;

%%

void yyerror(const char *wrongSentence){
	printf("Error (l.%d): %s\n", getLineNumber(), wrongSentence);
	
    exit(3);
}