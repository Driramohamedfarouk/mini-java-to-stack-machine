%{
#include<stdio.h>
#include<stdlib.h>
#include "declarations.h" 
#include "symtab.h"
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

%token <d> NUMBER
%token <s> NAME 
%token EOL

%token IF ELSE WHILE 

%nonassoc <fn> CMP
/* order of precedence from lowest to highest */
%right '='
%left '+' '-'
%left '*' '/'

%type <a> E list stmt
// %type <sl> symlist

%%
calclist : 
  | calclist stmt EOL {printf("= %4.4g\n",eval($2));treefree($2);printf("> ");}
  | calclist EOL {printf("> ");}
;

stmt : IF E '{' list '}'  {$$ = newflow('I',$2,$4,NULL);}
  | IF E '{' list '}' ELSE '{' list '}' {$$ = newflow('I',$2,$4,$8);}
  | WHILE E '{' list '}' {$$ = newflow('W',$2,$4,NULL);}
  | E 
  ;

list : { $$ = NULL; }
  | stmt ';' list { if($3==NULL)
                      $$ = $1;
                    else 
                      $$ = newast('L',$1,$3);  
                  } 
  ;               

E : E CMP E {$$ = newcmp($2,$1,$3);}
  | E '+' E {$$ = newast('+',$1,$3);}
  | E '-' E {$$ = newast('-',$1,$3);}
  | E '*' E {$$ = newast('*',$1,$3);}
  | E '/' E {$$ = newast('/',$1,$3);}
  | '(' E ')' { $$ = $2 ;  }
  | NUMBER { $$ = newnum($1);}
  ;

%%
