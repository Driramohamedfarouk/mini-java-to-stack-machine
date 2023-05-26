#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeGen.h"
#include "declarations.h"
#include "symtab.h"


int instructionNb = 0 ;

int nb_of_called_func = 0 ;

int alpha = 0 , beta = 0  ;

// TODO : refactor allocation of struct instruction to a function

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
            codeGen(newref(((struct symasgn*)a)->s)); // TODO : check possible error
            codeGen(((struct symasgn*)a)->a);
            i->code_op = STORE ;
            // lookup not new ref
            i->operand = ((struct symasgn*)a)->s ;
            machine_code[instructionNb++] = *i ;
            break ;
        case '+' :
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = ADD;
            machine_code[instructionNb++] = *i ;
            break ;
        case '-' :
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = SUB;
            machine_code[instructionNb++] = *i ;
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

        /* comparison  */
            /*>*/
        case '1':
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = SUP;
            machine_code[instructionNb++] = *i ;
            break ;
            /*<*/
        case '2':
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = INF;
            machine_code[instructionNb++] = *i ;
            break ;
            /*!=*/
        case '3':
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = DIF;
            machine_code[instructionNb++] = *i ;
            break ;
            /*==*/
        case '4':
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = EQ;
            machine_code[instructionNb++] = *i ;
            break ;
            /*>=*/
        case '5':
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = SUPE;
            machine_code[instructionNb++] = *i ;
            break ;
            /*<=*/
        case '6':
            codeGen(a->l) ;
            codeGen(a->r) ;
            i->code_op = INFE;
            machine_code[instructionNb++] = *i ;
            break ;
        case 'W' :
            alpha = instructionNb ;
            codeGen(((struct flow*)a)->cond);
            beta = instructionNb ;
            struct instruct *m = malloc(sizeof(struct instruct));
            if(!m){
                yyerror("out of space") ;
            }
            m->code_op=IFNOT;
            m->operand = 0 ;
            machine_code[beta] = *m ;
            instructionNb++;
            codeGen(((struct flow*)a)->thenb);
            struct instruct *n = malloc(sizeof(struct instruct));
            if(!n){
                yyerror("out of space") ;
            }
            n->code_op = JUMP ;
            n->operand = alpha ;
            machine_code[instructionNb++] = *n ;
            machine_code[beta].operand = instructionNb ;
            break ;
        case 'I' :
            // separate cases when there is a then branch and where there is not
            codeGen(((struct flow*)a)->cond);
            alpha = instructionNb;
            printf(">>>> alpha %d", alpha);
            struct instruct *j = malloc(sizeof(struct instruct));
            if(!j){
                yyerror("out of space") ;
            }
            j->code_op=IFNOT;
            j->operand = 0 ;
            machine_code[alpha] = *j ;
            instructionNb++;
            codeGen(((struct flow*)a)->thenb);
            printf(">>>> before else %d", instructionNb);
            j->operand = instructionNb ;
            machine_code[alpha]=*j ;
            if(((struct flow*)a)->elseb){
                codeGen(((struct flow*)a)->elseb);
            }
            return ;
            break ;
        case 'C' :
            printf("");
            // allocate one memory word for function result
            struct instruct *k = malloc(sizeof(struct instruct));
            if(!k){
                yyerror("out of space") ;
            }
            k->code_op = ALLOC ;
            k->operand = 1 ;
            machine_code[instructionNb++] = *k ;
            // add function params
            codeGen(((struct func *)a)->l);
            i->code_op = CALL ;
            i->operand = 0 ;
            addresses[nb_of_called_func] = instructionNb ;
            func_bodies[nb_of_called_func] = (((struct func *)a)->s)->func ;
            machine_code[instructionNb++] = *i ;
            nb_of_called_func++ ;
            break ;
        default:
            printf("\n");
            break ;
    }
    return ;
}


void print_machine_code(){
    for (int j = 0; j < instructionNb; ++j) {
        // TODO : format output with switch
        char *code =  machine_code[j].code_op ;
        if( strcmp(code,ADD)==0 || strcmp(code,SUB)==0 || strcmp(code,MUL)==0 || strcmp(code,DIV)==0 ||
            strcmp(code,INFE)==0 || strcmp(code,SUPE)==0 || strcmp(code,INF)==0 || strcmp(code,SUP)==0 ||
            strcmp(code,ENTER)==0 || strcmp(code,EXIT)==0 || strcmp(code,RTRN)==0
        ){
            printf("%d : %s\n",j,machine_code[j].code_op);
        }else if (strcmp(code,IFNOT)==0 || strcmp(code,CALL)==0) {
            printf("%d : %s %d\n",j,machine_code[j].code_op,machine_code[j].operand);
        }else{
            printf("%d : %s %x\n",j,machine_code[j].code_op,machine_code[j].operand);
        }
    }
}


/*
 * this method generates machine code for functions
 * and update the instruction nb from witch they are called
 * */
void add_function_bodies(){
    struct instruct *l = malloc(sizeof(struct instruct));
    if(!l){
        yyerror("out of space") ;
    }
    l->code_op = ENTER ;
    struct instruct *j = malloc(sizeof(struct instruct));
    if(!j){
        yyerror("out of space") ;
    }
    j->code_op=EXIT ;
    struct instruct *r = malloc(sizeof(struct instruct));
    if(!r){
        yyerror("out of space") ;
    }
    r->code_op=RTRN ;
    for (int i = 0; i < MAX_FUNCTION_CALLS; ++i) {
        if(addresses[i]){
            machine_code[addresses[i]].operand = instructionNb ;
            machine_code[instructionNb++] = *l ;
            codeGen(func_bodies[i]);
            machine_code[instructionNb++] = *j ;
            machine_code[instructionNb++] = *r ;
        }
    }
}
