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

%left '='
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
    | declarationsList
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
    | TK_IDENTIFIER '[' expression ']'
    | TK_IDENTIFIER '(' argumentsList ')'
    | KW_INPUT '(' dataType ')'
    | '(' expression ')'
    | expression OPERATOR_LE expression
    | expression OPERATOR_GE expression
    | expression OPERATOR_EQ expression
    | expression OPERATOR_DIF expression
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '&' expression
    | expression '<' expression
    | expression '>' expression
    | expression '|' expression
    | '~' expression
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

// Implementation Section
codeImplementationList: codeImplementation
    | codeImplementation codeImplementationList
    ;

codeImplementation: KW_CODE TK_IDENTIFIER cmd
    ;

cmd: '{' '}'
    | ';'
    | '{' cmdList '}'
    | TK_IDENTIFIER '=' expression ';'
    | TK_IDENTIFIER '[' expression ']' '=' expression ';'
    | KW_IF '(' expression ')' cmd
    | KW_IF '(' expression ')' cmd KW_ELSE cmd
    | KW_WHILE '(' expression ')' cmd
    | KW_PRINT expression ';'
    | KW_RETURN expression ';'
    ;

cmdList: cmd
    | cmd cmdList
    ;

argumentsList: expression
    | expression ',' argumentsList
    ;

%%

void yyerror(const char *wrongSentence){
	printf("Error (l.%d): %s\n", getLineNumber(), wrongSentence);
	
    exit(3);
}