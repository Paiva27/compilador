# Compilador - Analisador Léxico e Sintático

Aluno: Rafael Paiva de Moraes
Matricula: 172050018
-------------
# Analisador Sintático : 
Entrega e apresentação do trabalho dia: 29/ Outubro/ 2019
-------------
# Funcionalidades:
Compilador básico que contém :
- Os tipos : ***int,float e char***
- As Estruturas de controle de fluxo  : ***if, else,for e while***
- Lida com erros básicos de sintaxe como:

`void sabre(int a){ 
        if (a  b ){  //Erro de sintaxe 1
            a = a + 5;
        }else{
            a =  & ;   //Erro de sintaxe 2
        }
        for(int a b ; a  b; i ){ //Erro de sintaxe 3,4,5
             a = a b; //Erro de sintaxe 6
        }
    }
    
    float b(int c){
        a = c;
        while(a -){ //Erro de sintaxe 7
            int a b; //Erro de sintaxe 8
        }
    }
    
    int main(){
        int b a; //Erro de sintaxe 9
    }`
