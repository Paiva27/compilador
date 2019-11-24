#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "lexico.h"
#include "sintatico.h"
#include "semantico.h"

//Tabela que uso para verificar os tipos de operações resultantes de soma, subtração e multiplicação
void iniciaTbTiposSoma(){
    //Lembrando que 6 = inteiro, 7 = float e 8 = char.
    tbTiposSoma[0][0] = 6;
    tbTiposSoma[0][1] = 7;
    tbTiposSoma[0][2] = 6;
    tbTiposSoma[1][0] = 7;
    tbTiposSoma[1][1] = 7;
    tbTiposSoma[1][2] = 7;
    tbTiposSoma[2][0] = 6;
    tbTiposSoma[2][1] = 7;
    tbTiposSoma[2][2] = 6;
}
//Tabela que uso para verificar os tipos de operaçãoes resultantes de divisão
void iniciaTbTiposDivisao(){
  
    tbTiposDivisao[0][0] = 6;
    tbTiposDivisao[0][1] = 7;
    tbTiposDivisao[0][2] = 6;
    tbTiposDivisao[1][0] = 7;
    tbTiposDivisao[1][1] = 7;
    tbTiposDivisao[1][2] = 7;
    tbTiposDivisao[2][0] = 6;
    tbTiposDivisao[2][1] = 7;
    tbTiposDivisao[2][2] = 6;
}

//Inicia todas minhas tabelas auxiliares, a de .data e do próprio assembly
void iniciaTabelas(){
    for(int i=0; i < 10000;i++){
        tabelaVariaveis[i].variavel = " ";
        tabelaVariaveis[i].tipo = 41;
        tabelaVariaveis[i].valor = " ";
        tabelaVariaveis[i].funcao = " ";
        tabelaVariaveis[i].linha = 0;
        tabelaVariaveis[i].coluna = 0;
    }
    //Declaração de registrador auxiliar

    indexTabela = 0;
    indexLiterais = 0;
    iniciaTbTiposSoma();
    iniciaTbTiposDivisao();

    for(int i=0; i < 10000;i++){
        tabelaAssembly[i].operador = "";
        tabelaAssembly[i].resultado = "";
        tabelaAssembly[i].op1 = "";
        tabelaAssembly[i].op2 = "";
    }
    contEstDeFluxo = 0;
    indexAssembly = 0;
}

//Função que verifica se uma variável já existe na tabela de variáveis, se não, adiciona ela na tabela (Chamada durante atribuições)
void preencheTabela(char *variavel, Categoria tipo,char *funcao,int linha,int coluna,char *valor){
    int flag = 0;
    char *variavelAux = malloc (sizeof (char) * 1000);
    for(int i = 0; i < indexTabela; i++){
        if((strcmp(variavel, tabelaVariaveis[i].variavel) == 0)&&(strcmp(funcao, tabelaVariaveis[i].funcao)==0)){
            printf("\nErro, Variável '%s' já foi declarada nessa função na linha: %d coluna : %d",tabelaVariaveis[i].variavel,
            tabelaVariaveis[i].linha,tabelaVariaveis[i].coluna);
            flag = 1;
        }
    }
    strcpy(variavelAux,variavel);
    if(flag == 0){
        
        tabelaVariaveis[indexTabela].variavel = variavelAux;
        tabelaVariaveis[indexTabela].tipo = tipo;
        tabelaVariaveis[indexTabela].valor = valor;
        tabelaVariaveis[indexTabela].funcao = funcao;
        tabelaVariaveis[indexTabela].linha = linha;
        tabelaVariaveis[indexTabela].coluna = coluna;
        indexTabela++;
    }
}

//Verifica existência de tal variável na tabela, assim durante uma operação aritmética é possível saber se ela existe ou não.
void verificaTabela(char *variavel,Categoria tipo,char *funcao,int linha,int coluna){
    int flag = 0;
    for(int i = 0; i < indexTabela; i++){
        if((strcmp(variavel, tabelaVariaveis[i].variavel) == 0)&&(strcmp(funcao, tabelaVariaveis[i].funcao)== 0)){
                flag=1;
        }
    }
    if((flag != 1)&&(tipo != 2)&&(tipo != 3)&&(tipo != 4))printf("\nVariavel %s, não foi declarada. Erro em linha : %d coluna %d",variavel,linha,coluna);
       
}

//Função auxiliar para printar os tipos de acordo com a categoria do token.
const char *retornaTipo(Categoria tipo){
    if(tipo == 6){
        return "Inteiro";
    }else if(tipo == 7){
        return "Float";
    }else if(tipo == 8){
        return "Char";
    }
}

//Função que verifica e avisa o tipo resultante da operação em relação ao operador que esse valor está sendo atribuido
void mudaVariavelTabela(char *variavel,Categoria tipo,char *funcao,int linha,int coluna){
    for(int i = 0; i < indexTabela; i++){
        if((strcmp(variavel, tabelaVariaveis[i].variavel) == 0)&&(strcmp(funcao, tabelaVariaveis[i].funcao)== 0)){
                if((tabelaVariaveis[i].tipo == 7 )&&(tipo == 6)){
                }else if(tabelaVariaveis[i].tipo != tipo){
                    printf("\nWarning : Esperado tipo: %s e obteve tipo: %s . Na linha : %d coluna %d",
                    retornaTipo(tabelaVariaveis[i].tipo),retornaTipo(tipo),linha,coluna);
                
                }else{

                }
        }
    }  
}

//Função que retorna qual o tipo da variável utilizando a tabela de variáveis.
int verificaOperacao(char *variavel,char *funcao){
    for(int i = 0; i < indexTabela; i++){
        if((strcmp(variavel, tabelaVariaveis[i].variavel) == 0)&&(strcmp(funcao, tabelaVariaveis[i].funcao)== 0)){
        return tabelaVariaveis[i].tipo;            
        }
    }
    return 0;
}


//Função que printa a tabela que representa o .data
void printaTabela(){
    printf("\n    Tabela de .data:\n");
    for(int i = 0; i < indexTabela; i++){
        printf("\n  Variavel %s | Tipo: %d | Valor: %s | Função : %s",tabelaVariaveis[i].variavel,
        tabelaVariaveis[i].tipo,tabelaVariaveis[i].valor,tabelaVariaveis[i].funcao);
    }
}

//Função que retorna qual o index de tal variável dentro da tabela .data para ser usada depois para dar um Load Word
int retornaIndexVariavel(char *variavel,char *funcao,int tipo){
    int aux =0;
    for(int i = 0; i < indexTabela; i++){
    printf("\nERRO na variável. Variavel : %s, tabelaVar: %s Z funcao %s tabelaVar: %s",variavel,tabelaVariaveis[i].variavel,funcao,
    tabelaVariaveis[i].funcao);
        if(((strcmp(variavel, tabelaVariaveis[i].variavel) == 0)&&(strcmp(funcao, tabelaVariaveis[i].funcao)== 0))|| 
        ((strcmp(variavel, tabelaVariaveis[i].valor) == 0)&&(tabelaVariaveis[i].tipo == tipo))){
        return i;
        }
    }
    if((tipo == 3)||(tipo == 4)||(tipo == 5)){
        char *numLiteral = malloc (sizeof (char) * 1000);
        sprintf(numLiteral, "lit%d", indexLiterais);
        preencheTabela(numLiteral, tipo,funcao,0,0,variavel);
        indexLiterais++;
        return retornaIndexVariavel(variavel,funcao,tipo);
    }
    return 0;
}
//Função que é chamada pela preencheTabelaAssembly para sempre que um operador for ser usado, ser carregado da tabela .data
//para ser usada na tabela que representa o código em assembly
char * carregaEmRegistrador(char * op, char * funcao,int tipoOp){
    
    char *numeroRegistradorTemporario = malloc (sizeof (char) * 1000);
    numeroRegistradorTemporario[0] = '\0';
    sprintf(numeroRegistradorTemporario, "t%d", indexAssembly);
    char *operadorAux = "LW";
    char *resultadoAux = numeroRegistradorTemporario;
    char *op1Aux = malloc (sizeof (char) * 100);
    char *op2Aux = " ";
    if(tipoOp != 0){
        strcpy(op1Aux,tabelaVariaveis[retornaIndexVariavel(op,funcao,tipoOp)].variavel);
        tabelaAssembly[indexAssembly].operador = operadorAux;
        tabelaAssembly[indexAssembly].resultado = numeroRegistradorTemporario;
        tabelaAssembly[indexAssembly].op1 = op1Aux;
        tabelaAssembly[indexAssembly].op2 = op2Aux;
        indexAssembly++;
        return numeroRegistradorTemporario;
    }else{
        printf("Não carregou o registrador.");
    }
    return op;
}

void criaLabel(char * label,int cont){
    char *numeroRegistradorTemporario = malloc (sizeof (char) * 1000);
    numeroRegistradorTemporario[0] = '\0';
    sprintf(numeroRegistradorTemporario, "%s%d: ",label, cont);
    char *resultadoAux = "";
    char *op1Aux = "";
    char *op2Aux = " ";
    tabelaAssembly[indexAssembly].operador = numeroRegistradorTemporario;
    tabelaAssembly[indexAssembly].resultado = resultadoAux;
    tabelaAssembly[indexAssembly].op1 = op1Aux;
    tabelaAssembly[indexAssembly].op2 = op2Aux;
    indexAssembly++;
}

void criaComando(char * op,char * result, char *op1, char *op2){
    
    char *operadorAux = malloc (sizeof (char) * 10);
    char *resultadoAux = malloc (sizeof (char) * 1000);
    char *op1Aux = malloc (sizeof (char) * 100);
    char *op2Aux = malloc (sizeof (char) * 100);
    
    strcpy(operadorAux,op);
    strcpy(resultadoAux,result);
    strcpy(op1Aux,op1);
    strcpy(op2Aux,op2);

    tabelaAssembly[indexAssembly].operador = operadorAux;
    tabelaAssembly[indexAssembly].resultado = resultadoAux;
    tabelaAssembly[indexAssembly].op1 = op1Aux;
    tabelaAssembly[indexAssembly].op2 = op2Aux;
    indexAssembly++;

}

//Função responsável por gerar o código em assembly
char * preencheTabelaAssembly(char *operador,char *resultado,char *op1,char *op2, char * funcao,int tipoOp1,int tipoOp2){
        char *numeroRegistradorTemporario = malloc (sizeof (char) * 1000);
        char *resultadoAux = malloc (sizeof (char) * 1000);
        char *operadorAux = malloc (sizeof (char) * 10);
        char *op1Aux = malloc (sizeof (char) * 100);
        char *op2Aux = malloc (sizeof (char) * 100);

        if(strcmp("+", operador)==0|| strcmp("-", operador)==0|| strcmp("*", operador)==0|| strcmp("/", operador)==0){
            if(strcmp("+", operador)==0)strcpy(operadorAux,"ADD");
            else if(strcmp("-", operador)==0)strcpy(operadorAux,"SUB");
            else if(strcmp("*", operador)==0)strcpy(operadorAux,"MUL");
            else if(strcmp("/", operador)==0)strcpy(operadorAux,"DIV");
            strcpy(resultadoAux,resultado);
            if(tipoOp2 == 0){
            //printf("\nOp1 : %s, Op2 %s",op1,op2);
            strcpy(op1Aux,op1);
            strcpy(op2Aux,carregaEmRegistrador(op2,funcao,tipoOp2));
            }else{
            //printf("\nOp1 : %s, Op2 %s",op1,op2);
            strcpy(op1Aux,carregaEmRegistrador(op1,funcao,tipoOp1));
            strcpy(op2Aux,carregaEmRegistrador(op2,funcao,tipoOp2));
            }
            numeroRegistradorTemporario[0] = '\0';
            if((strcmp(resultado,"regTemp") == 0)){ 
                sprintf(numeroRegistradorTemporario, "t%d", indexAssembly);
                tabelaAssembly[indexAssembly].resultado = numeroRegistradorTemporario;
            }else{
                tabelaAssembly[indexAssembly].resultado = resultadoAux;
            }
            tabelaAssembly[indexAssembly].operador = operadorAux;
            tabelaAssembly[indexAssembly].op1 = op1Aux;
            tabelaAssembly[indexAssembly].op2 = op2Aux;
            indexAssembly++;
            return numeroRegistradorTemporario;
        }else if(strcmp("=", operador)==0){
            strcpy(operadorAux,"SW");
            resultadoAux = resultado;
            strcpy(op1Aux,op1);
            strcpy(op2Aux,op2);
            tabelaAssembly[indexAssembly].resultado = resultadoAux;
            tabelaAssembly[indexAssembly].operador = operadorAux;
            tabelaAssembly[indexAssembly].op1 = op1Aux;
            tabelaAssembly[indexAssembly].op2 = op2Aux;
            indexAssembly++;

        }

}

void geraCodigoOpLogica(char * operador,int contador,char * escopoAtual, char * op1,int op1Tipo,char * op2,int op2Tipo){

    char * escopoAux = escopoAtual;
    char * op1Aux = carregaEmRegistrador(op1, escopoAux,op1Tipo);
    char * op2Aux = carregaEmRegistrador(op2, escopoAux,op2Tipo);
    printf("\n\n o1:%s \n\n",op1);
    printf("\n\n o2:%s \n\n",op2);
    char *passTemporario = malloc (sizeof (char) * 1000);
    passTemporario[0] = '\0';
    sprintf(passTemporario, "pass%d", contador);

    if(strcmp("==", operador)==0){
        //branch on equal 
        criaComando("BEQ",op1Aux, op2Aux, passTemporario);

    }else if(strcmp("!=", operador)==0){
        //branch on not equal
        criaComando("BNE",op1Aux, op2Aux, passTemporario);

    }else if(strcmp("<=", operador)==0){
        //branch on less than orequal
        criaComando("BLE",op1Aux, op2Aux, passTemporario);

    }else if(strcmp(">=", operador)==0){
        //branch on greater than or equal
        criaComando("BGE",op1Aux, op2Aux, passTemporario);

    }else if(strcmp(">", operador)==0){
        //branch on greater than
        criaComando("BGT",op1Aux, op2Aux, passTemporario);

    }else if(strcmp("<", operador)==0){
        //branch on less than
        criaComando("BLT",op1Aux, op2Aux, passTemporario);
    }

}

//Função que printa a tabela de códigos na tela
void printaTabelaAssembly(){
    printf("\n   Tabela representativa do código Assembly:\n");
    printf("\n Op | Result | Op1 | Op2");
    for(int i = 0; i < indexAssembly; i++){
        printf("\n  %s  %s  %s %s",tabelaAssembly[i].operador,
        tabelaAssembly[i].resultado,tabelaAssembly[i].op1,tabelaAssembly[i].op2);
    }
}