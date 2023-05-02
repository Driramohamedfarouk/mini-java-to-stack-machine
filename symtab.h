#define SYM_TAB_SIZE 9777

struct symbol
{
    char * name ;
    double value ; 
    struct ast *func ; 
    struct symlist * syms ;  
};



// linked list of symbols used as arguments for functions  
struct symlist
{
    struct symbol *sym ; 
    struct symlist *next ;    
};


struct symbol symbol_table[SYM_TAB_SIZE];

struct symbol *lookup(char*);

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);


/*A function definition consists of the name of the function, a list of dummy arguments,
and an AST that represents the body of the function*/
void def_func(struct symbol* name,struct symlist *syms,struct ast *stmts);