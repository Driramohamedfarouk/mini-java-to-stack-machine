extern int yylineno ; 
void yyerror(char*s, ...);


struct ast {
	int nodetype ;
	struct ast *l;
	struct ast *r; 
};

struct numval {
	int nodeType ; 
	double value ;
};


struct ast* newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);


double eval(struct ast *a);

void treefree(struct ast *a) ;


