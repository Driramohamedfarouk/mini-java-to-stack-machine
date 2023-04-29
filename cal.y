%{
#include<stdio.h>
#include<stdlib.h>
#include "declarations.h" 
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
}

%token <d> NUMBER
%token EOL

%type <a> E F T


%%
calclist : 
  | calclist E EOL {printf("= %4.4g\n",eval($2));treefree($2);printf("> ");}
  | calclist EOL {printf("> ");}
;
E : F 
  | E '+' F {$$ = newast('+',$1,$3);}
  | E '-' F {$$ = newast('-',$1,$3);}
  ;


F : T 
  | F '*' T {$$ = newast('*',$1,$3);}
  | F '/' T {$$ = newast('/',$1,$3);}
  ;

T : NUMBER { $$ = newnum($1);  }
  | '(' E ')' { $$ = $2 ;  }
  | '-' T { $$ = newast('M',$2,NULL);  }			
%%
