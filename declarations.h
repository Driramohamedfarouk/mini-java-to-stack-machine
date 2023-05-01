extern int yylineno ; 
void yyerror(char*s, ...);
int yylex(void);
int yyparse(void);


struct ast {
	int nodetype ;
	struct ast *l;
	struct ast *r; 
};

struct numval {
	int nodetype ; 
	double value ;
};

struct flow {
	int nodetype ; 
	struct ast* cond ;
	struct ast* thenb ; /* then branch */
	struct ast* elseb ; /* else branch */
};


struct ast* newast(int nodetype, struct ast *l, struct ast *r);
struct ast* newnum(double d);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);

double eval(struct ast *a);

void treefree(struct ast *a) ;


