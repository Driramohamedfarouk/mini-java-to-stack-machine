#define PROGRAM_LENGTH 9777
#define LDC "LDC"
#define LDV "LDV"
#define STORE "STORE"
#define CALL "CALL"
#define ENTER "ENTER"
#define EXIT "EXIT"
#define RTRN "RETURN"
#define ADD "ADD"
#define MUL "MUL"
#define DIV "DIV"
#define SUB "SUB"
#define INF "INF"
#define INFE "INFE"
#define SUP  "SUP"
#define SUPE "SUPE"
#define DIF "DIF"
#define EQ "EQ"
#define IFNOT "IFNOT"
#define JUMP "JUMP"
#define ALLOC "ALLOCATE"


#define MAX_FUNCTION_CALLS 300

//TODO : explain what each instruction set do

/********************************************************
 *  INSTRUCTION SET OF THE STACK MACHINE
 ****************************************************** */
/*
 * LDC
 * LDV
 * STORE
 * APPEL
 * ENTREE
 * SORTIE
 * RETOUR
 * ADD
 * MUL
 * DIV
 * SUB
 * INF
 * INFE
 * SUP
 * SUPE
 * DIF
 * EGAL
*/

struct ast;

struct instruct {
    char *code_op;
    int  operand ;
    char *fct_name ;
};


struct instruct machine_code[PROGRAM_LENGTH] ;

// TODO : change this to a linked list

/*struct node {
    int calling_index;
    struct ast * func_body;
};

struct list_node {
    node n ;
    list_node * next ;
};*/

// global variable containing functions to call and from what line did we call it
int addresses[MAX_FUNCTION_CALLS] ;
struct ast* func_bodies[MAX_FUNCTION_CALLS];


void codeGen(struct ast* );
void print_machine_code();
void add_function_bodies();
