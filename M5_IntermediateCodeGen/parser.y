%{
    #include <stdio.h>
    #include <stdlib.h>		
	#include "AST.h"
	#include "y.tab.h"
    #include "SemanticAnalyser.h"	
    
    // Prototypes
	int yylex();
	void yyerror(const char*);
	int getRow(void);
	int getCol(void);
    RC getRC(void);
%}

%token KW_CHAR KW_INT KW_FLOAT
%token KW_CODE 
%token KW_IF KW_ELSE KW_WHILE
%token KW_INPUT KW_PRINT
%token KW_RETURN
%token OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%token TOKEN_ERROR
%token<symbol> TK_IDENTIFIER
%token<symbol> LIT_INT LIT_REAL LIT_CHAR LIT_STRING

%type<astNod> program
%type<astNod> declarationsList
%type<astNod> declaration
%type<astNod> formalParameter
%type<astNod> formalParameterList
%type<astNod> expression
%type<astNod> literalsList
%type<astNod> literal
%type<astNod> dataType
%type<astNod> codeImplementationList
%type<astNod> codeImplementation
%type<astNod> cmd
%type<astNod> cmdList
%type<astNod> argumentsList

%left '='
%left '|'
%left '&'
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF '<' '>'
%left '+' '-'
%left '*' '/'
%right '~'

%union {
	struct SymbolTableNode *symbol;
    struct AST *astNod;
}

%%
program: declarationsList codeImplementationList        {   $$ = astCreate(NULL, AST_FULL_PROG, $1, $2); 
                                                            setRC($$, getRC());     
                                                            setGlobalAST($$); 
                                                            /**astPrint($$,0)*/; 
                                                            if(!checkSemantic($$)) return 4; 
                                                        }
    | declarationsList                                  {$$ = astCreate(NULL, AST_HEADER, $1); setRC($$, getRC()); setGlobalAST($$);}
    ;

// Declaration Section      
declarationsList: declaration                           {$$ = $1;}          
    | declaration declarationsList                      {$$ = astCreate(NULL, AST_DECLARATION_LIST, $1, $2);}
    ;

declaration: dataType TK_IDENTIFIER '=' expression ';'              {$$ = astCreate($2, AST_VAR_DECLARATION, $1, $4); setRC($$, getRC());}
    | dataType TK_IDENTIFIER '[' literal ']' ';'                    {$$ = astCreate($2, AST_ARRAY_DECLARATION, $1, $4); setRC($$, getRC());}
    | dataType TK_IDENTIFIER '[' literal ']' literalsList ';'       {$$ = astCreate($2, AST_ARRAY_DEC_AND_INIT, $1, $4, $6); setRC($$, getRC());}        
    | dataType TK_IDENTIFIER '(' formalParameterList ')' ';'        {$$ = astCreate($2, AST_FUNCTION_DECLARATION, $1, $4); setRC($$, getRC());}
    ;

formalParameter: dataType TK_IDENTIFIER                 {$$ = astCreate($2, AST_PARAM, $1); setRC($$, getRC());}
    ;

formalParameterList: formalParameter                    {$$ = $1;}
    | formalParameter ',' formalParameterList           {$$ = astCreate(NULL, AST_PARAM_LIST, $1, $3);  setRC($$, getRC());}
    |                                                   {$$ = NULL;}
    ;

expression: literal                                     {$$=$1;}
    | TK_IDENTIFIER                                     {$$ = astCreate($1, AST_SYMBOL); setRC($$, getRC());}
    | TK_IDENTIFIER '[' expression ']'                  {$$ = astCreate($1, AST_ARRAY_EXPR, $3); setRC($$, getRC());}
    | TK_IDENTIFIER '(' argumentsList ')'               {$$ = astCreate($1, AST_FUNCTION_CALLING, $3); setRC($$, getRC());}    
    | KW_INPUT '(' dataType ')'                         {$$ = astCreate(NULL, AST_INPUT, $3); setRC($$, getRC());}
    | '(' expression ')'                                {$$=$2;}
    | expression OPERATOR_LE expression                 {$$ = astCreate(NULL, AST_OPERATOR_LE,$1,$3); setRC($$, getRC());}
    | expression OPERATOR_GE expression                 {$$ = astCreate(NULL, AST_OPERATOR_GE,$1,$3); setRC($$, getRC());}
    | expression OPERATOR_EQ expression                 {$$ = astCreate(NULL, AST_OPERATOR_EQ,$1,$3); setRC($$, getRC());}
    | expression OPERATOR_DIF expression                {$$ = astCreate(NULL, AST_OPERATOR_DIF,$1,$3); setRC($$, getRC());}
    | expression '+' expression                         {$$ = astCreate(NULL, AST_ADD,$1,$3); setRC($$, getRC());}
    | expression '-' expression                         {$$ = astCreate(NULL, AST_SUB,$1,$3); setRC($$, getRC());}
    | expression '*' expression                         {$$ = astCreate(NULL, AST_MUL,$1,$3); setRC($$, getRC());}
    | expression '/' expression                         {$$ = astCreate(NULL, AST_DIV,$1,$3); setRC($$, getRC());}
    | expression '&' expression                         {$$ = astCreate(NULL, AST_AND,$1,$3); setRC($$, getRC());}
    | expression '<' expression                         {$$ = astCreate(NULL, AST_LESS_THAN,$1,$3); setRC($$, getRC());}                    
    | expression '>' expression                         {$$ = astCreate(NULL, AST_GREATER_THAN,$1,$3); setRC($$, getRC());}
    | expression '|' expression                         {$$ = astCreate(NULL, AST_OR,$1,$3); setRC($$, getRC());}
    | '~' expression                                    {$$ = astCreate(NULL, AST_NOT,$2); setRC($$, getRC());}
    ;

literalsList: literal       {$$ = $1;}       
    | literal literalsList  {$$ = astCreate(NULL, AST_LITERAL_LIST, $1, $2); setRC($$, getRC());}
    ;

literal: LIT_INT            {$$ = astCreate($1, AST_SYMBOL); setRC($$, getRC());}
    | LIT_CHAR              {$$ = astCreate($1, AST_SYMBOL); setRC($$, getRC());}
    | LIT_REAL              {$$ = astCreate($1, AST_SYMBOL); setRC($$, getRC());}
    | LIT_STRING            {$$ = astCreate($1, AST_SYMBOL); setRC($$, getRC());}
    ;

dataType: KW_INT            {$$ = astCreate(NULL, AST_INT); setRC($$, getRC());}
    | KW_CHAR               {$$ = astCreate(NULL, AST_CHAR); setRC($$, getRC());}
    | KW_FLOAT              {$$ = astCreate(NULL, AST_FLOAT); setRC($$, getRC());}
    ;

// Implementation Section
codeImplementationList: codeImplementation                      {$$ = $1;}
    | codeImplementation codeImplementationList                 {$$ = astCreate(NULL, AST_FUNCTION_IMPLEMENTATION_LIST, $1, $2); setRC($$, getRC());}
    ;

codeImplementation: KW_CODE TK_IDENTIFIER cmd                   {$$ = astCreate($2, AST_FUNCTION_IMPLEMENTATION, $3); setRC($$, getRC());}
    ;

cmd: '{' '}'                                                    {$$ = astCreate(NULL, AST_CMD_BLOCK, NULL); setRC($$, getRC());}
    | ';'                                                       {$$ = NULL;}
    | '{' cmdList '}'                                           {$$ = astCreate(NULL, AST_CMD_BLOCK, $2); setRC($$, getRC());}          
    | TK_IDENTIFIER '=' expression ';'                          {$$ = astCreate($1, AST_ASSIGNMENT, $3); setRC($$, getRC());}
    | TK_IDENTIFIER '[' expression ']' '=' expression ';'       {$$ = astCreate($1, AST_ARRAY_ASSIGN, $3, $6); setRC($$, getRC());}
    | KW_IF '(' expression ')' cmd                              {$$ = astCreate(NULL, AST_IF_THEN, $3, $5); setRC($$, getRC());}
    | KW_IF '(' expression ')' cmd KW_ELSE cmd                  {$$ = astCreate(NULL, AST_IF_THEN_ELSE, $3, $5, $7); setRC($$, getRC());}
    | KW_WHILE '(' expression ')' cmd                           {$$ = astCreate(NULL, AST_WHILE, $3, $5); setRC($$, getRC());}
    | KW_PRINT expression ';'                                   {$$ = astCreate(NULL, AST_PRINT, $2); setRC($$, getRC());}
    | KW_RETURN expression ';'                                  {$$ = astCreate(NULL, AST_RETURN, $2); setRC($$, getRC());}
    | expression ';'                                            {$$ = $1;}
    ;

cmdList: cmd                                                    {$$ = $1;}
    | cmd cmdList                                               {$$ = astCreate(NULL, AST_CMD_LIST, $1, $2); setRC($$, getRC());}
    ;
        
argumentsList: expression                                       {$$ = astCreate(NULL, AST_ARG_LIST, $1, NULL); setRC($$, getRC());}
    | expression ',' argumentsList                              {$$ = astCreate(NULL, AST_ARG_LIST, $1, $3); setRC($$, getRC());}
    ;

%%

void yyerror(const char *wrongSentence){
	printf("Error (l.%d): %s\n", getRow(), wrongSentence);
	
    exit(3);
}
