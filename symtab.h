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