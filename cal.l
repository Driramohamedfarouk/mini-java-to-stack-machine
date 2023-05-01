%option noyywrap nodefault yylineno
%{
#include "declarations.h"
#include "cal.tab.h"
#include "symtab.h"
%}


/* float exponent */
EXP ([Ee][-+]?[0-9]+)
%%
"+" |
"-" |
"*" |
"/" |
"=" |
";" |
"(" |
")" | 
"{" |
"}" { return yytext[0]; }

">"  {yylval.fn = 1 ; return CMP ;}
"<"  {yylval.fn = 2 ; return CMP ;}
"!=" {yylval.fn = 3 ; return CMP ;}
"==" {yylval.fn = 4 ; return CMP ;}
">=" {yylval.fn = 5 ; return CMP ;}
"<=" {yylval.fn = 6 ; return CMP ;}


"if"     { return IF ; }
"else"   { return ELSE ; }
"while"  { return WHILE ; }


[a-zA-Z][a-zA-Z0-9]* { yylval.s = lookup(yytext) ; return NAME; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }
\n { return EOL; }
"//".*
[ \t]
. { yyerror("Mystery character %c\n", *yytext); }

%%


