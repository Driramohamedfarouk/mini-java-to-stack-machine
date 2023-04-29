#include <stdio.h> 
#include <stdlib.h> 
#include <stdarg.h> 
#include "declarations.h"

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
	a->nodeType = 'K';
	a->value = d;
	return (struct ast *)a;
}




double eval(struct ast *a) {
	double v; // calculated value of this subtree
	switch(a->nodetype) {
	case 'K': v = ((struct numval *)a)->value; break;
	case '+': v = eval(a->l) + eval(a->r); break;
	case '-': v = eval(a->l) - eval(a->r); break;
	case '*': v = eval(a->l) * eval(a->r); break;
	case '/': v = eval(a->l) / eval(a->r); break;
	case 'M': v = -eval(a->l); break;
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
	treefree(a->r);
	/* one subtree */
	case 'M':
	treefree(a->l);
	/* no subtree */
	case 'K':
	free(a);
	break;
	default: printf("internal error: free bad node %c\n", a->nodetype);
	}
}

int main() {
	printf("> ");
	return yyparse();
}

void yyerror(char *s, ...) {
	printf("error %s at line %d\n",s,yylineno);
}