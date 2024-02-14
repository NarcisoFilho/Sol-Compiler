#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa4: SymbolTable.o y.tab.o lex.yy.o main.o AST.o SemanticAnalyser.o  TAC.o
	gcc -o etapa5 main.o lex.yy.o y.tab.o SymbolTable.o AST.o SemanticAnalyser.o TAC.o -Wall 
main.o: main.c
	gcc -c main.c -Wall 
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: parser.y
	yacc -d parser.y
SymbolTable.o: SymbolTable.c
	gcc -c SymbolTable.c -Wall 
AST.o: AST.c
	gcc -c -Wall AST.c
SemanticAnalyser.o: 
	gcc -c SemanticAnalyser.c -Wall 
TAC.o:
	gcc -c TAC.c -Wall 

clean:
	rm etapa5 y.tab.c y.tab.h lex.yy.c lex.yy.h *.o
