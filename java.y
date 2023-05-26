%{
#include <stdio.h>
#include <stdlib.h>
#include "declarations.h" 
#include "symtab.h"
#include "semantic.h"
#include "codeGen.h"
%}

/*
You dont have to declare a type for a token or declare a nonterminal at all if you dont 
use the symbols value. 
If there is a %union in the declarations, bison will give you an 
error if you attempt to use the value of a symbol that doesnt have an assigned type. 
*/

// value of symbol used by bison "yyval"
%union {
struct ast* a ; 
double d ; 
struct symbol *s ; /* pointer to the symbol in the symbol table */
struct symlist *sl ; 
int fn ; /* which comparaison operator */
}

%token CLASS 

%token <d> NUMBER
%token <s> NAME 

%token IF ELSE WHILE MODIFIER TYPE RETURN 

%nonassoc <fn> CMP
/* order of precedence from lowest to highest */
%right '='
%left '+' '-'
%left '*' '/'

%type <a> E list stmt assignment func_call args list_arg cond declaration
%type <sl> var_list vars

%%

// TODO : add print all functions after code Gen
program : 
  | CLASS NAME '{' list '}' { struct ast * res = $4 ; codeGen(res);  }
  ;


/* type ast */
stmt : IF '(' cond ')' '{' list '}'  {$$ = newflow('I',$3,$6,NULL); }
  | IF '(' cond ')' '{' list '}' ELSE '{' list '}' {$$ = newflow('I',$3,$6,$10);}
  | WHILE '(' cond ')' '{' list '}' {$$ = newflow('W',$3,$6,NULL);}
  | assignment ';'
  | func_call ';'
  | declaration ';'
  ;

list : { $$ = NULL; }
  | stmt list     { if($2==NULL)
                      $$ = $1;
                    else 
                      $$ = newast('L',$1,$2);  
                   }
  | func_def list { $$ = $2 ; }
  ;

assignment : NAME '=' E { $$ = newasgn(undeclared_id($1->name),$3);}
           ;

declaration : TYPE  NAME { $$ = newasgn(check_multiply_declared_id($2->name),NULL);}
            | TYPE  NAME '=' E { $$ = newasgn(check_multiply_declared_id($2->name),$4);}
            ;

E : E '+' E {$$ = newast('+',$1,$3);}
  | E '-' E {$$ = newast('-',$1,$3);}
  | E '*' E {$$ = newast('*',$1,$3);}
  | E '/' E {$$ = newast('/',$1,$3);}
  | '(' E ')' { $$ = $2 ;  }
  | NUMBER { $$ = newnum($1);}
  | NAME    { $$ = newref(undeclared_id($1->name));}
  ;

/* add not and AND oR */
cond : E CMP E {$$ = newcmp($2,$1,$3);}
    ;

func_def : MODIFIER TYPE NAME '(' vars ')' '{' list '}' {
  def_func(check_multiply_declared_id($3->name),$5,$8);
}
  ;

// TODO : make vars return a linked list of symbol tables
vars : { $$ = NULL ; }
  | var_list 
  ;

var_list : TYPE NAME { $$ = newsymlist($2,NULL);}
  | TYPE NAME ',' var_list { $$ = newsymlist($2,$4); }
  ; 

func_call : NAME '(' args ')' { $$ = newfunc(undeclared_id($1->name),$3); } /* function call*/
  ;

args : { $$ = NULL; }
  | list_arg { $$ = $1 ;} /*default */
  ;

list_arg : E  {$$ = newast('L',$1,NULL);} 
  | E ',' list_arg {$$ = newast('L',$1,$3);}
  ;


%%
