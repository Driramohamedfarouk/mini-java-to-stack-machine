CC=gcc 
 

javac : java.l java.y declarations.c declarations.h symtab.c symtab.h
	bison -d java.y
	flex java.l
	$(CC) -o $@ symtab.c declarations.c java.tab.c lex.yy.c  


clean : 
	rm -f javac 
