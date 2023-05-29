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
| Instruction | Description                  |
|-------------|------------------------------|
| LDC         | load constant value          |
| LDV         | load variable by its address |
