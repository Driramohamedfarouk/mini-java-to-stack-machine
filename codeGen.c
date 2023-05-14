#include "codeGen.h"
#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

// stack pointer
int instructionNb = 0  ;

void codeGen(struct ast* a){
    if(!a){
        return ;
    }
    struct instruct *i = malloc(sizeof(struct instruct));
    if(!i){
        yyerror("out of space") ;
    }
    switch (a->nodetype) {
        case 'L':
            codeGen(a->l);
            codeGen(a->r);
            break ;
        case 'K' :
            i->code_op = LDC ;
            i->operand = ((struct numval *)a)->value  ;
            machine_code[instructionNb++] = *i ;
            return;
            break ;
        case 'N' :
            i->code_op = LDV ;
            i->operand = ((struct symref *)a)->s ; /* possible type problem */
            machine_code[instructionNb++] = *i ;
            return ;
            break ;
        case '=' :
            codeGen(newref(((struct symasgn*)a)->s));
            codeGen(((struct symasgn*)a)->a);
            i->code_op = STORE ;
            i->operand = newref(((struct symasgn*)a)->s) ;
            machine_code[instructionNb++] = *i ;
            return ;
            break ;
        case '+' :
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = ADD;
            machine_code[instructionNb++] = *i ;
            return;
            break ;
        case '*' :
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = MUL;
            machine_code[instructionNb++] = *i ;
            break ;
        case '/' :
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = DIV;
            machine_code[instructionNb++] = *i ;
            break ;
        case 'C' :
            i->code_op = APPEL ;
            //i->fct_name  = ((struct func*)a)->s->name ;
            machine_code[instructionNb++] = *i ;
            break ;
        case 'I' :
            codeGen(((struct flow*)a)->cond);
            machine_code[instructionNb++] = *i ;
            return ;
            break ;
        default:
            printf("\n");
            break ;
    }
    return ;
}


void print_machine_code(){
    for (int j = 0; j < instructionNb; ++j) {
        printf("%d : %s %x\n",j,machine_code[j].code_op,machine_code[j].operand);
    }
}