#include <stdio.h> 
#include <stdlib.h> 
#include <stdarg.h> 
#include "declarations.h"
#include "symtab.h"

struct ast* newast(int nodetype, struct ast *l, struct ast *r){
	struct ast *a = malloc(sizeof(struct ast));
	if(!a) {
	yyerror("out of space");
	exit(0);
	}
	a->nodetype = nodetype;
	a->l = l;
	a->r = r;
	return a;
}

struct ast *newnum(double d){
	struct numval *a = malloc(sizeof(struct numval));
	if(!a) {
	yyerror("out of space");
	exit(0);
	}
	a->nodetype = 'K';
	a->value = d;
	return (struct ast *)a;
}

struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el){
	struct flow *a = malloc(sizeof(struct flow));
	if(!a) {
		yyerror("out of space");
		exit(0);
	}
	a->nodetype = nodetype ; 
	a->cond = cond ;
	a->thenb = tl ;  
	a->elseb = el ;  
	return (struct ast*) a ; 
}


struct ast *newcmp(int cmptype, struct ast *l, struct ast *r){
	return newast('0'+cmptype,l,r) ; 
}


struct ast *newref(struct symbol *s){
	struct symref *a = malloc(sizeof(struct symref)) ;
	if(!a) {
		yyerror("out of space");
		exit(0);
	}
	a->nodetype='N';
	a->s = s ; 
	return (struct ast*) a ;
}

struct ast *newasgn(struct symbol *s, struct ast *a){
	struct symasgn *b = malloc(sizeof(struct symasgn));
	if(!b) {
		yyerror("out of space");
		exit(0);
	}
	b->nodetype = '=' ;
	b->s = s ; 
	b->a = a ; 
	return (struct ast*) b ; 
}

double eval(struct ast *a) {
	double v; // calculated value of this subtree
	switch(a->nodetype) {
	case 'K': v = ((struct numval *)a)->value; break;

	/* return the value in the symbol table */
	case 'N': v = (((struct symref *)a)->s)->value ;
	/* evaluate the AST and put the value to the symbol table */
	case '=': v = ((struct symasgn *)a)->s->value = eval(((struct symasgn *)a)->a) ; break ;  

	case '+': v = eval(a->l) + eval(a->r); break;
	case '-': v = eval(a->l) - eval(a->r); break;
	case '*': v = eval(a->l) * eval(a->r); break;
	case '/': v = eval(a->l) / eval(a->r); break;
	case 'M': v = -eval(a->l); break;

	/* comparaison  */
	/*>*/
	case '1': v = (eval(a->l)>eval(a->r))? 1 : 0 ; break ;
	/*<*/
	case '2': v = (eval(a->l)<eval(a->r))? 1 : 0 ; break ;
	/*!=*/
	case '3': v = (eval(a->l)!=eval(a->r))? 1 : 0 ; break ;
	/*==*/
	case '4': v = (eval(a->l)==eval(a->r))? 1 : 0 ; break ;
	/*>=*/
	case '5': v = (eval(a->l)>=eval(a->r))? 1 : 0 ; break ;
	/*<=*/
	case '6': v = (eval(a->l)<=eval(a->r))? 1 : 0 ; break ;

	case 'I': 
	if(eval(((struct flow*)a)->cond)){
		if(((struct flow*)a)->thenb){
			printf("inside then \n") ;
			printf("%c\n",((struct flow*)a)->thenb->nodetype) ;
			printf("%c\n",((struct flow*)a)->thenb->l->nodetype) ;
			printf("%c\n",((struct flow*)a)->thenb->r->nodetype) ;
			v = eval(((struct flow*)a)->thenb) ;
		}else{
			v=0.0;
		}
	}else{
		if(((struct flow*)a)->elseb){
			v = eval(((struct flow*)a)->elseb) ;
		}else{
			v=0.0;
		}
	}
	case 'L': eval(a->l); v = eval(a->r); break;
	default: printf("internal error: bad node %c\n", a->nodetype);
	}
	return v;
}

void treefree(struct ast *a) {
	switch(a->nodetype) {
	/* two subtrees */
	case '+':
	case '-':
	case '*':
	case '/':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
		treefree(a->r);
	/* one subtree */
	case 'M':
		treefree(a->l);
	/* no subtree */
	case 'K': case 'N':
		free(a);
		break;
	case '=':
		free(((struct symasgn*)a)->a);
		break;	
	case 'I': 
		free(((struct flow*)a)->cond);
		if (((struct flow*)a)->thenb) free(((struct flow*)a)->thenb);
		if (((struct flow*)a)->elseb) free(((struct flow*)a)->elseb);	
		break;
	default: printf("internal error: free bad node %c\n", a->nodetype);
	}
	free(a);
}

int main() {
	printf("> ");
	return yyparse();
}

void yyerror(char *s, ...) {
	printf("error %s at line %d\n",s,yylineno);
}