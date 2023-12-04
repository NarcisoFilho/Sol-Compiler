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
    #include "SymbolTable.h" 
    #include "main.c" 

    bool running = true;
    int lineNumber = 1;
%}

%option stack
%x LINE_COMMENT
%x BLOCK_COMMENT

specialChar [-,;(){}=+*/%<>&|~]|"["|"]" 
lineCmmt    "//"
blkCmmt	    "///"
blkCmmtEnd  "\\\\\\"
literalStr  \"[^"]*\"
literalChar \'[^']*\'

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

    "<="            {addSymbol(yytext, OPERATOR_LE); return OPERATOR_LE;}
    ">="            {addSymbol(yytext, OPERATOR_GE); return OPERATOR_GE;}
    "=="            {addSymbol(yytext, OPERATOR_EQ); return OPERATOR_EQ;}
    "!="            {addSymbol(yytext, OPERATOR_DIF); return OPERATOR_DIF;}
   
    [0-9]*[.][0-9]+ {addSymbol(yytext, LIT_REAL); return LIT_REAL;}
    [0-9]+          {addSymbol(yytext, LIT_INT); return LIT_INT;}
    {literalStr}    {addSymbol(yytext, LIT_STRING); return LIT_STRING;}
    {literalChar}   {addSymbol(yytext, LIT_CHAR); return LIT_CHAR;}

    [a-zA-Z_0-9]+   {addSymbol(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}
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

void initMe(){
    initSymbolTable();
    setRehashAlertStatus((int)true);
    // setHehashAlert((int)false);  // Uncomment if don't want rehashing notification
}

