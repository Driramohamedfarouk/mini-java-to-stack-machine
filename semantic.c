#include "symtab.h"

void yyerror(char*s, ...);

// create it if it does not exist and return it, otherwise raise error
struct symbol* check_multiply_declared_id(char *name){
    return lookup(name) ;
}
// fail if undeclared otherwise return it
struct symbol* undeclared_id(char *name){
    return exists(name) ;
}