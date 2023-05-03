#include <stdio.h>
#include "symtab.h"

int check_multiply_declared_id(char *name){
    if(exists(name)){
        yyerror("variable %s already declared \n",name);
    }else{
        insert(name);
    }   
}

int undeclared_id(char *name){

}