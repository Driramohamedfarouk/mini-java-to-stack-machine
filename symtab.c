#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include "symtab.h"
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
