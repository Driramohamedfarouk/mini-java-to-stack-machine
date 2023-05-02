#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include "symtab.h"
#include "declarations.h"

void yyerror(char*s, ...);


/* hash function */
static unsigned symhash(char *sym){
    unsigned int hash = 0 ; 
    unsigned c ; 
    while ( c = *sym++) hash = hash*9 ^ c ; 
    return hash ;
}

/* hashing with linear probing */
struct symbol *lookup(char* sym) {
    struct symbol *sp = &symbol_table[symhash(sym)%SYM_TAB_SIZE];
    int scount = SYM_TAB_SIZE ;
    while (--scount>=0){
        /* if the symbol already exists */
        if(sp->name&& !strcmp(sp->name,sym)) return sp ;
        /* if there is an empty slot */
        if(!sp->name){
            sp->name = strdup(sym);
            sp->value = 0 ; 
            sp->func = NULL ; 
            sp->syms = NULL ; 
            return sp ; 
        }
        /* otherwise increment pointer while checking that we did not arrive at the end */
        if(++sp >= symbol_table+SYM_TAB_SIZE) sp = symbol_table ;  
    }
    yyerror("symbol table is full \n");
    abort();
};


struct symlist *newsymlist(struct symbol *sym, struct symlist *next){
    struct symlist *sl = malloc(sizeof(struct symlist));
    if(!sl) {
        yyerror("out of space");
        exit(0);
    }
    sl->sym = sym;
    sl->next = next;
    return sl;
}

/* free a list of symbols */
void symlistfree(struct symlist *sl) {
	struct symlist *nsl;
	while(sl) {
		nsl = sl->next;
		free(sl);
		sl = nsl;
	}
}


void def_func(struct symbol *name,struct symlist *syms,struct ast *stmts){
	if(name->func) symlistfree(name->syms);
	if (name->syms) treefree(name->func);
	name->func = stmts ; 
	name->syms	= syms ; 
}



