
struct symbol
{
    char * name ;
    double value ; 
    struct ast *func ; 
    struct symlist * syms ;  
};



// linked list of symbols 
struct symlist
{
    struct symbol *sym ; 
    struct symlist *next ;    
};

#define SYM_TAB_SIZE 9777
struct symbol symbol_table[SYM_TAB_SIZE];

struct symbol *lookup(char*);

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);