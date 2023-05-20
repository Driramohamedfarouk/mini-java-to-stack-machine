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

/* is a reference to the variable in the symbol table */
struct symref {
	int nodetype ; /* type N */
	struct symbol *s; 
};

/* the node representing a variable assignment  */
struct symasgn{
	int nodetype ; /* type = */
	struct symbol *s;
	struct ast *a ; 
};

struct func {
	int nodetype ; /* type C */
	struct ast *l ; /* statements  */
	struct symbol *s  ; /* list of arguments */
};


struct ast* newast(int nodetype, struct ast *l, struct ast *r);
struct ast* newnum(double d);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);

struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s,struct ast *a);


struct ast *newfunc(struct symbol *s,struct ast *l);


double eval(struct ast *a);

void treefree(struct ast *a) ;

void print_ast(struct ast* node, int level);


