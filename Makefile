CC=gcc 
 

cal : cal.l cal.y declarations.c declarations.h symtab.c symtab.h
	bison -d cal.y
	flex cal.l
	$(CC) -o $@ cal.tab.c lex.yy.c declarations.c symtab.c


clean : 
	rm -f cal 
