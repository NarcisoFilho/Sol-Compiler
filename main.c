// #include <stdlib.h>
// #include "tokens.h"

// int main(int argc, char** argv){
//     if(argc < 2){
//         printf("Error: Expected 1 argument but receives 0\n");
//         printf("Usage: %s 'fileName'\n", argv[0]);
//         exit(1);
//     }

//     FILE* inputFile = freopen(argv[1], "r", stdin);
//     int type;
//     int lastLine = -1;
//     int currentLine;
//     while(isRunning()){
//         type = yylex();
//         if((currentLine = getLineNumber()) != lastLine){
//             printf("<l%d> %s: \n", currentLine, yytext );
//             lastLine = currentLine;
//         }
//         switch(type){
//             case KW_CHAR:
//                 printf("\tKW_CHAR(%s)\n", yytext);
//                 break;
//             case KW_INT:
//                 printf("\tKW_INT(%s)\n", yytext);
//                 break;
//             case KW_FLOAT:
//                 printf("\tKW_FLOAT(%s)\n", yytext);
//                 break;
//             case KW_CODE:
//                 printf("\tKW_CODE(%s)\n", yytext);
//                 break;
//             case KW_IF:
//                 printf("\tKW_IF(%s)\n", yytext);
//                 break;
//             case KW_ELSE:
//                 printf("\tKW_ELSE(%s)\n", yytext);
//                 break;
//             case KW_WHILE:
//                 printf("\tKW_WHILE(%s)\n", yytext);
//                 break;
//             case KW_INPUT:
//                 printf("\tKW_INPUT(%s)\n", yytext);
//                 break;
//             case KW_PRINT:
//                 printf("\tKW_PRINT(%s)\n", yytext);
//                 break;
//             case KW_RETURN:
//                 printf("\tKW_RETURN(%s)\n", yytext);
//                 break;
//             case LIT_CHAR:
//                 printf("\tLIT_CHAR(%s)\n", yytext);
//                 break;
//             case LIT_STRING:
//                 printf("\tLIT_STRING(%s)\n", yytext);
//                 break;
//             case LIT_INT:
//                 printf("\tLIT_INT(%s)\n", yytext);
//                 break;
//             case LIT_REAL:
//                 printf("\tLIT_REAL(%s)\n", yytext);
//                 break;
//             case TK_IDENTIFIER:
//                 printf("\tTK_IDENTIFIER(%s)\n", yytext);
//                 break;
//             case OPERATOR_LE:
//                 printf("\tOPERATOR_LE(%s)\n", yytext);
//                 break;
//             case OPERATOR_GE:
//                 printf("\tOPERATOR_GE(%s)\n", yytext);
//                 break;
//             case OPERATOR_EQ:
//                 printf("\tOPERATOR_EQ(%s)\n", yytext);
//                 break;
//             case OPERATOR_DIF:
//                 printf("\tOPERATOR_DIF(%s)\n", yytext);
//                 break;
//             case TOKEN_ERROR:
//                 printf("\tTOKEN_ERROR(%s)\n", yytext);
//                 break;
//             default:
//                 printf("\tOther(%s)\n", yytext);
//                 break;
//         }   
//     }

//     return 0;
// }