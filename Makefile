CC=gcc 
 

javac : java.l java.y declarations.c declarations.h symtab.c symtab.h semantic.h semantic.c
	bison -d java.y
	flex java.l
	$(CC) -o $@ semantic.c symtab.c declarations.c java.tab.c lex.yy.c


clean : 
	rm -f javac 
