#include <stdio.h>
#include "symtab.h"

void yyerror(char*s, ...);


int check_multiply_declared_id(char *name){
    if(exists(name)){
        yyerror("variable %s already declared \n",name);
    }else{
        insert(name);
    }
    return  0 ;
}

int undeclared_id(char *name){
    if(!exists(name)){
        yyerror("use of undeclared variable\n",name);
    }
    return 0 ;
}