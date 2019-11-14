# Compilador - Analisador Léxico e Sintático

###### Aluno: Rafael Paiva de Moraes
###### Matricula: 172050018
----
## Analisador Sintático : 
Entrega e apresentação do trabalho dia: 29/ Outubro/ 2019

## Compilar e Executar : 
Para compilar o código na pasta principal digite o comando ***"make"***
Para executar o código na pasta /exec digite o comando ***"./exec ../teste.c"***

## Funcionalidades Sintáticas:
Compilador básico que contém :
- Os tipos : ***int, float e char***
- As Estruturas de controle de fluxo  : ***if, else, for e while***
- Lida com erros básicos de sintaxe como:



        
        float b(int c){
            a = c;
            while(a -){ //Erro de sintaxe 1
                int a b; //Erro de sintaxe 2
            }
        }
        
        int main(){
            int b == a; //Erro de sintaxe 3
        }


## Lidando com erros:
Ao lidar com erros, procurou-se sempre ir para a próxima posição "segura" disponível, como por exemplo no ***Erro de sintaxe 1***  o próximo token válido seria ***")"*** que fecha a interação com o if. Ou então no ***Erro de sintaxe 2***  que o próximo token "seguro" seria o ponto e vírgula, assim podendo continuar o código sem mais problemas.

## Analisador Semântico e geração de código: 
Entrega e apresentação do trabalho dia: dd/mm/yyyy

## Funcionalidades Semânticas e geração de código:
Ao declarar uma variável ela é mandada para uma tabela representada pela struct ***tabelaVariaveis***.
Quando uma variável é utilizada é checado antes se ela esta contida na lista, caso não, reporta-se o erro.

-----

Quando existe uma operação aritmética, os tipos da operação são checados.
Por exemplo:
       
        
        int main(){
            int b;
            float a;
            b = a + 5;
        }

Retorna-se assim um ***Warning*** pois, a operação retorna um tipo float enquanto a variável de atribuição é tipo int.
A decisão do tipo resultante da operação aritmética é feita através de uma tabela que para o caso do operador soma é:

Tipos | int | float | char
:-------: | :------: | :------: | :------:
int     | int | float | int
float    | float | float | float
char    | int | float | int


----

Em casos de mais de uma operação na mesma atribuição ele cria uma pilha de operações.
Por exemplo:
        
        
        int main(){
            int b;
            float a;
            a = a + b * 5 + a ;
        }
Criando se uma pilha de operações seguindo a ordem de multiplicação e divisão e depois soma e subtração,
como essa : ***b*5 -> +a  -> +a***

----

Por enquanto o código gerado é uma tabela que simula um assembly e só funciona para operações aritméticas.
Por exemplo:

        
        
        int main(){
            int b;
            float a;
            a = a + b * 5;
        }

Geraria uma tabela como a seguinte:

Operador | Resultado | Op1 | Op2
:-------: | :------: | :------: | :------:
MUL     | t0 | b | 5
ADD    | t1 | t0 | a
ATR    | a | t1 | -


## Melhorias e implementações futuras:
 O foco principal é dar possibilidades maiores para operadores lógicos e aritméticos com mais recursos como os operadores ou, and e not. Ou mesmo com a utilização de parênteses para definir uma ordem para a operação.
