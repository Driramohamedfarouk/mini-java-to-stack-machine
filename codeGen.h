#define PROGRAM_LENGTH 9777
#define LDC "LDC"
#define LDV "LDV"
#define STORE "STORE"
#define APPEL "APPEL"
#define ENTREE "ENTREE"
#define SORTIE "SORTIE"
#define RETOUR "RETOUR"
#define ADD "ADD"
#define MUL "MUL"
#define DIV "DIV"
#define SUB "SUB"
#define INF "INF"
#define INFE "INFE"
#define SUP  "SUP"
#define SUPE "SUPE"
#define DIF "DIF"
#define EGAL "EGAL"

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



void codeGen(struct ast* );
void print_machine_code();
