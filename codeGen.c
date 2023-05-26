#include "codeGen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"
#include "symtab.h"


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
        case 'W' :
            /*
            int alpha = instructionNb , beta = 0 ;
            codeGen(((struct flow*)a)->cond);
            beta = instructionNb ;
            // possible temporary instruction malloc + free
            // add IFNOT beta to machine code
            codeGen(((struct flow*)a)->thenb);
            // add JUMP to alpha
            // update beta value ( keep a pointer on beta for example )
            machine_code[beta].operand = instructionNb ; /* or ++ */
            break;

        /* comparaison  */
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
        case 'I' :
            // separate cases when there is a then branch and where there is not
            printf(">>>> %d", instructionNb);
            codeGen(((struct flow*)a)->cond);
            int alpha = instructionNb;
            printf(">>>> alpha %d", alpha);
            struct instruct *j = malloc(sizeof(struct instruct));
            if(!j){
                yyerror("out of space") ;
            }
            j->code_op=IFNOT;
            j->operand = 7 ;
            machine_code[alpha] = *j ;
            instructionNb++;
            codeGen(((struct flow*)a)->thenb);
            printf(">>>> before else %d", instructionNb);
            j->operand = instructionNb ;
            machine_code[alpha]=*j ;
            if(((struct flow*)a)->elseb){
                codeGen(((struct flow*)a)->elseb);
            }
            printf(">>>> %d", instructionNb);
            return ;
            break ;
        case 'C' :
            // allocate one memory word for function result
            printf(">>>> %d", instructionNb);
            struct instruct *k = malloc(sizeof(struct instruct));
            if(!k){
                yyerror("out of space") ;
            }
            k->code_op = ALLOCATE ;
            k->operand = 1 ;
            machine_code[instructionNb++] = *k ;
            // add function params
            codeGen(((struct func *)a)->l);
            // store the value of the instruction number in an array

            // CALL alpha
            // alpha calculated after
            i->code_op = CALL ;
            i->operand = 0 ;
            //i->fct_name  = ((struct func*)a)->s->name ;
            machine_code[instructionNb++] = *i ;
            //printf("%s\n",(((struct func *)a)->s)->name);
            codeGen((((struct func *)a)->s)->func);
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
        if( strcmp(code,ADD)==0 || strcmp(code,SUB)==0 || strcmp(code,INF)==0 || strcmp(code,SUP)==0 ){
            printf("%d : %s\n",j,machine_code[j].code_op);
        }else if (strcmp(code,IFNOT)==0) {
            printf("%d : %s %d\n",j,machine_code[j].code_op,machine_code[j].operand);
        }else{
            printf("%d : %s %x\n",j,machine_code[j].code_op,machine_code[j].operand);
        }
    }
}