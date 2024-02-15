%{
    /** JOKERC: Joker language compiler
    *  Module: Lexical Analyzer(Scanner)
    *  @date october 27 2023
    *  @version 1.0
    *  @author Manoel Narciso Reis
    *  @brief Scanner module of JOKERC
    * 
    */
    #include "Boolean.h"
    #include "SymbolTable.h" 
    #include "CompilerErrorType.h" 
    #include "y.tab.h"

    bool running = true;
    int lineNumber = 1;
    int col = 0;
    int prvTokSz = 0;
    extern YYSTYPE yylval;
    
    void resetCol();
    void setCol();

    typedef struct{
        int row;
        int col;
    } RC;
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
    \n              {++lineNumber;resetCol();}
    [\t ]+          {setCol();}

    char            {setCol(); return KW_CHAR; }
    int             {setCol(); return KW_INT; }
    float           {setCol(); return KW_FLOAT; }
    code            {setCol(); return KW_CODE;}
    if              {setCol(); return KW_IF;}
    else            {setCol(); return KW_ELSE;}
    while           {setCol(); return KW_WHILE;}
    input           {setCol(); return KW_INPUT;}
    print           {setCol(); return KW_PRINT;}
    return          {setCol(); return KW_RETURN;}

    "<="            {setCol(); return OPERATOR_LE;}
    ">="            {setCol(); return OPERATOR_GE;}
    "=="            {setCol(); return OPERATOR_EQ;}
    "!="            {setCol(); return OPERATOR_DIF;}
   
    [0-9]*[.][0-9]+ {yylval.symbol = addSymbol(yytext, LIT_REAL_TOKEN); setCol(); return LIT_REAL;}
    [0-9]+          {yylval.symbol = addSymbol(yytext, LIT_INT_TOKEN); setCol(); return LIT_INT;}
    {literalStr}    {yylval.symbol = addSymbol(yytext, LIT_STRING_TOKEN); setCol(); return LIT_STRING;}
    {literalChar}   {yylval.symbol = addSymbol(yytext, LIT_CHAR_TOKEN); setCol(); return LIT_CHAR;}

    [a-zA-Z_0-9]+   {yylval.symbol = addSymbol(yytext, TK_IDENTIFIER_TOKEN); setCol(); return TK_IDENTIFIER;}
    {specialChar}   {setCol(); return (int)(yytext[0]);}
    .               {compilerErrorAlert(lineNumber, yytext, INVALID_CHARACTER); setCol(); return TOKEN_ERROR;}
}

<BLOCK_COMMENT>{
    {blkCmmtEnd}    {yy_pop_state();}
    \n              {++lineNumber; resetCol();}
    .+              {setCol();}
}

<LINE_COMMENT>{
    \n              {yy_pop_state();++lineNumber;resetCol();}
    .+              {setCol();}
}

%%
int yywrap(){
    running = false;
    return 1;
}

int isRunning(){
    return (int)running;
}

int getRow(){
    return lineNumber;
}

int getCol(){
    return col;
}

RC getRC(){
    RC rc;
    rc.row = getRow();
    rc.col = getCol();

    return rc;
}

void initMe(){
    initSymbolTable();
    //setRehashAlertStatus((int)true);
    setRehashAlertStatus((int)false);  // Uncomment if don't want rehashing notification
}

void setCol(){
    col+=prvTokSz;
    prvTokSz=yyleng;
}

void resetCol(){
    col = prvTokSz = 0;
}