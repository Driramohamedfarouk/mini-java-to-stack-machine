CC=gcc 
 

cal : cal.l cal.y declarations.c declarations.h
	bison -d cal.y
	flex cal.l
	$(CC) -o $@ cal.tab.c lex.yy.c declarations.c 


clean : 
	rm -f cal 
