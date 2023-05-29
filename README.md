## what this compiler can do
* evaluate arithmetic expressions
* handle only the integer type
* if else statements 
* while loops
* call subroutines
* assigning named variables 
* comparison expressions 

## semantic analysis 
* checking multiply defined variables 
* checking usage of undeclared variables 

## Code Generation 
* Stack Machine
* fixed size of block memory equal to 3*sizeof(int)
* Machine Code is produced in memory 

## Instruction set of our stack machine
| Instruction | Description                                                                                   |
|-------------|-----------------------------------------------------------------------------------------------|
| LDC         | load constant value                                                                           |
| LDV         | load variable by its address                                                                  |
| STORE       | Dépile une valeur et la met dans l'adresse de l'opérande                                      |
| CALL        | Appel de sous-programme                                                                       |
| ENTER       | Entrée dans un sous-programme.                                                                |
| EXIT        | Sortie d’un sous-programme                                                                    |
| RTRN        | Dépile une valeur et continue l’exécution par l’ins-truction dont c’est l’adresse             |
| ADD         | Dépile deux valeurs et empile le résultat de leur addition                                    |
| MUL         | Dépile deux valeurs et empile le résultat de leur multiplication                              |
| DIV         | Dépile deux valeurs et empile le quotient de leur division                                    |
| SUB         | Dépile deux valeurs et empile le résultat de leur soustraction                                |
| INF         | Dépile deux valeurs et empile 1 si la première est inférieure à la seconde, 0 sinon.          |
| INFE        | Dépile deux valeurs et empile 1 si la première est inférieure ou égale à la seconde, 0 sinon. |
| SUP         | Dépile deux valeurs et empile 1 si la première est supérieure à la seconde, 0 sinon.          |
| SUPE        | Dépile deux valeurs et empile 1 si la première est supérieure ou égale à la seconde, 0 sinon. | 
| DIF         | Dépile deux valeurs et empile 1 si la première est différente de la seconde, 0 sinon.         |
| EQ          | Dépile deux valeurs et empile 1 si la première est égale à la seconde, 0 sinon.               |
| IFNOT       | L’exécution continue par l’instruction ayant l’adresse indiqué si le sommet de la pile est 0  |
| JUMP        | L’exécution continue par l’instruction ayant l’adresse indiqué                                |
| ALLOCATE    | allocation d'un nbr de mot au sommet de la pile                                               |