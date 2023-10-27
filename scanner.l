%{
/** JOKERC: Joker language compiler
 *  Module: Lexical Analyzer(Scanner)
 *  @date october 27 2023
 *  @version 1.0
 *  @author Manoel Narciso Reis
 *  @brief Scanner module of JOKERC
 * 
 */
    #include "tokens.h"
    #include "Boolean.h"
    #include "CompilerErrorType.h" 

    Boolean running = true;
    int lineNumber = 1;
%}

%option stack
%x LINE_COMMENT
%x BLOCK_COMMENT

specialChar [-,;(){}=+*/%<>&|~]|"["|"]" 
lineCmmt    "//"
blkCmmt	    "///"
blkCmmtEnd  "\\\\\\"
literalStr  \".*\"
literalChar \'.\'|\'\\.\'
multiChar   \'..+\'   

%%
<INITIAL>{
    {blkCmmt}       {yy_push_state(BLOCK_COMMENT);}
    {lineCmmt}      {yy_push_state(LINE_COMMENT);}
    \n              {++lineNumber;}
    [\t ]+          {}

    char            {return KW_CHAR;}
    int             {return KW_INT;}
    float           {return KW_FLOAT;}
    code            {return KW_CODE;}
    if              {return KW_IF;}
    else            {return KW_ELSE;}
    while           {return KW_WHILE;}
    input           {return KW_INPUT;}
    print           {return KW_PRINT;}
    return          {return KW_RETURN;}

    "<="            {return OPERATOR_LE;}
    ">="            {return OPERATOR_GE;}
    "=="            {return OPERATOR_EQ;}
    "!="            {return OPERATOR_DIF;}
   
    [0-9]*.[0-9]+   {return LIT_REAL;}
    [0-9]+          {return LIT_INT;}
    {literalStr}    {return LIT_STRING;}
    {literalChar}   {return LIT_CHAR;}
    {multiChar}     {compilerErrorAlert(lineNumber, yytext, MULTI_CHARACTER_CONSTANTE); return TOKEN_ERROR;}

    [a-zA-Z_0-9]+   {return TK_IDENTIFIER;}
    {specialChar}   {return (int)(yytext[0]);}
    .               {compilerErrorAlert(lineNumber, yytext, INVALID_CHARACTER); return TOKEN_ERROR;}
}

<BLOCK_COMMENT>{
    {blkCmmtEnd}    {yy_pop_state();}
    \n              {++lineNumber;}
    .+              {}
}

<LINE_COMMENT>{
    \n              {yy_pop_state();++lineNumber;}
    .+              {}
}

%%
int yywrap(){
    running = false;
    return 1;
}

int isRunning(){
    return (int)running;
}

int getLineNumber(){
    return lineNumber;
}

#include <stdlib.h>
int main(int argc, char** argv){
    if(argc < 2){
        printf("Error: Expected 1 argument but receives 0\n");
        printf("Usage: %s 'fileName'\n", argv[0]);
        exit(1);
    }

    FILE* inputFile = freopen(argv[1], "r", stdin);
    int type;
    int lastLine = -1;
    int currentLine;
    while(isRunning()){
        type = yylex();
        if((currentLine = getLineNumber()) != lastLine){
            printf("<l%d> %s: \n", currentLine, yytext );
            lastLine = currentLine;
        }
        switch(type){
            case KW_CHAR:
                printf("\tKW_CHAR(%s)\n", yytext);
                break;
            case KW_INT:
                printf("\tKW_INT(%s)\n", yytext);
                break;
            case KW_FLOAT:
                printf("\tKW_FLOAT(%s)\n", yytext);
                break;
            case KW_CODE:
                printf("\tKW_CODE(%s)\n", yytext);
                break;
            case KW_IF:
                printf("\tKW_IF(%s)\n", yytext);
                break;
            case KW_ELSE:
                printf("\tKW_ELSE(%s)\n", yytext);
                break;
            case KW_WHILE:
                printf("\tKW_WHILE(%s)\n", yytext);
                break;
            case KW_INPUT:
                printf("\tKW_INPUT(%s)\n", yytext);
                break;
            case KW_PRINT:
                printf("\tKW_PRINT(%s)\n", yytext);
                break;
            case KW_RETURN:
                printf("\tKW_RETURN(%s)\n", yytext);
                break;
            case LIT_CHAR:
                printf("\tLIT_CHAR(%s)\n", yytext);
                break;
            case LIT_STRING:
                printf("\tLIT_STRING(%s)\n", yytext);
                break;
            case LIT_INT:
                printf("\tLIT_INT(%s)\n", yytext);
                break;
            case LIT_REAL:
                printf("\tLIT_REAL(%s)\n", yytext);
                break;
            case TK_IDENTIFIER:
                printf("\tTK_IDENTIFIER(%s)\n", yytext);
                break;
            case OPERATOR_LE:
                printf("\tOPERATOR_LE(%s)\n", yytext);
                break;
            case OPERATOR_GE:
                printf("\tOPERATOR_GE(%s)\n", yytext);
                break;
            case OPERATOR_EQ:
                printf("\tOPERATOR_EQ(%s)\n", yytext);
                break;
            case OPERATOR_DIF:
                printf("\tOPERATOR_DIF(%s)\n", yytext);
                break;
            case TOKEN_ERROR:
                printf("\tTOKEN_ERROR(%s)\n", yytext);
                break;
            default:
                printf("\tOther(%s)\n", yytext);
                break;
        }   
    }

    return 0;
}
