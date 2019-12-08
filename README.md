# Compilador - Analisador Léxico, Sintático, Semântico e Geração de Código

###### Aluno: Rafael Paiva de Moraes
###### Matricula: 172050018
----
## Analisador Sintático : 
Entrega e apresentação do trabalho dia: 29/ Outubro/ 2019

## Funcionalidades:
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

## Analisador Semântico e Geração de código: 
Entrega e apresentação do trabalho dia: 10/12/2019

## Funcionalidades Semânticas e geração de código:
Ao declarar uma variável ela é mandada para uma tabela representada pela struct ***tabelaVariaveis***.
Esta tabela também representa o ***.data*** da parte de geração de código.
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
            a = a + b * 5 - a ;
        }
Criando se uma pilha de operações seguindo a ordem de multiplicação e divisão e depois soma e subtração,
como essa : ***bx5 ->  +a  -> -a***

----
## Gerando código:
O código gerado é colocado dentro de uma tabela que representa o código em assembly.
Está funcionando para operações de ***atribuição*** e ***aritméticas*** e nas estruturas de controle de fluxo: ***if,else,for,while***.
Abaixo possui um exemplo da aplicação executando o arquivo ***"teste.c"***



        int sePa(int b){
            char c,a;
            int d;
        }
        int main(){
            float a;
            int b;
            char c;
            int i;
            for(i = 0; i <= 10; i = i + 1){
                if(b ==){
                    a = 5;
                    while(b < 15){
                        b = b + 11;
                        }
                 }else{
                     a =10;
                 }
             }
            a = a + b * 5;
        }
        
        

### Geraria uma tabela .data como a seguinte:

![tabeladata](https://user-images.githubusercontent.com/50743654/69489391-5092dd80-0e56-11ea-9cf2-f42b43dc4808.png)

### E geraria um código assembly como esse:

![assembly](https://user-images.githubusercontent.com/50743654/69489525-132f4f80-0e58-11ea-88c2-9514a4aaaa14.png)


----
## Sobre o Assembly MIPS:

As instruções utilizadas para desenvolver esse código foram tiradas desse link: 
https://www.dsi.unive.it/~gasparetto/materials/MIPS_Instruction_Set.pdf.

É importante ressaltar que dessas instruções utilizadas, também foram usadas ***pseudo-instruções***.
Além disso, também é de suma importância relatar que foram utilizados ***registradores temporários "infinitos"***,
ou seja, diferentemente de um código em MIPS que vai até o **$t9** porém para esse programa seria possível até o **$t999**.
E que para o **IF** gere código corretamente, é necessário utilizar do ***}else{}*** mesmo que desnecessário.



## Melhorias e implementações futuras:
 Melhorias futuras possíves seriam a adição do comando break dentro das estruturas de controle de fluxo, além de uma implementação de alguma melhoria para a redução de variáveis temporárias, além de uma forma do if funcionar corretamente sem o else junto.
