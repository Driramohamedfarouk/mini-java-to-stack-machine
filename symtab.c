#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "declarations.h"
#include "semantic.h"

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


int exists(char* sym) {
    struct symbol *sp = &symbol_table[symhash(sym)%SYM_TAB_SIZE];
    /* if the symbol already exists */
    if(sp->name&& !strcmp(sp->name,sym)) return 1 ;
    return 0 ; 
};

/* should only be called after checking that the symbol does not exist already */
struct symbol *insert(char *sym ) {
    /* assume there will be no collision  */
    struct symbol *sp = &symbol_table[symhash(sym)%SYM_TAB_SIZE];
    int scount = SYM_TAB_SIZE ;
    while (--scount>=0){
        /* if the symbol already exists */
        if(sp->name&& !strcmp(sp->name,sym)) exit(1) ;
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
}


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
    check_multiply_declared_id(name->name);
	if(name->func) treefree(name->func);
	if (name->syms) symlistfree(name->syms);
	name->func = stmts ; 
	name->syms	= syms ; 
}

struct symbol *new_symbol(char *name){
    struct symbol *s = malloc(sizeof(struct symbol));
    if(!s){
        printf("out of space");
        exit(1);
    }
    s->name = strdup(name) ;
    s->func = NULL ;
    s->syms = NULL ;
    s->value = 0.0f ;
    return s ;
}


void print_symtab(){
  printf("\n");	
  for (int i = 0; i < SYM_TAB_SIZE; i++) {
	if (symbol_table[i].name)
	{
		printf("%s  ",symbol_table[i].name) ;	
	}	
  }
  printf("\n");
}