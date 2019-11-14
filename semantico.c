#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "lexico.h"
#include "sintatico.h"
#include "semantico.h"

void iniciaTbTiposSoma(){
    
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


void iniciaTabelas(){
    for(int i=0; i < 10000;i++){
        tabelaVariaveis[i].variavel = " ";
        tabelaVariaveis[i].tipo = 41;
        tabelaVariaveis[i].valor = " ";
        tabelaVariaveis[i].funcao = " ";
        tabelaVariaveis[i].linha = 0;
        tabelaVariaveis[i].coluna = 0;
    }
    indexTabela = 0;
    iniciaTbTiposSoma();
    iniciaTbTiposDivisao();

    for(int i=0; i < 10000;i++){
        tabelaAssembly[i].operador = "";
        tabelaAssembly[i].resultado = "";
        tabelaAssembly[i].op1 = "";
        tabelaAssembly[i].op2 = "";
    }
    indexAssembly = 0;
}


void preencheTabela(char *variavel, Categoria tipo,char *funcao,int linha,int coluna){
    int flag = 0;
    for(int i = 0; i < indexTabela; i++){
        if((strcmp(variavel, tabelaVariaveis[i].variavel) == 0)&&(strcmp(funcao, tabelaVariaveis[i].funcao)==0)){
            printf("\nErro, Variável '%s' já foi declarada nessa função na linha: %d coluna : %d",tabelaVariaveis[i].variavel,
            tabelaVariaveis[i].linha,tabelaVariaveis[i].coluna);
            flag = 1;
        }
    }
    if(flag == 0 ){
        tabelaVariaveis[indexTabela].variavel = variavel;
        tabelaVariaveis[indexTabela].tipo = tipo;
        tabelaVariaveis[indexTabela].valor = " ";
        tabelaVariaveis[indexTabela].funcao = funcao;
        tabelaVariaveis[indexTabela].linha = linha;
        tabelaVariaveis[indexTabela].coluna = coluna;
        indexTabela++;
    }
}


void verificaTabela(char *variavel,Categoria tipo,char *funcao,int linha,int coluna){
    int flag = 0;
    for(int i = 0; i < indexTabela; i++){
        if((strcmp(variavel, tabelaVariaveis[i].variavel) == 0)&&(strcmp(funcao, tabelaVariaveis[i].funcao)== 0)){
                flag=1;
        }
    }
    if(flag != 1)printf("\nVariavel %s, não foi declarada. Erro em linha : %d coluna %d",variavel,linha,coluna);
       
}

const char *retornaTipo(Categoria tipo){
    if(tipo == 6){
        return "Inteiro";
    }else if(tipo == 7){
        return "Float";
    }else if(tipo == 8){
        return "Char";
    }
}

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

int verificaOperacao(char *variavel,char *funcao){
    for(int i = 0; i < indexTabela; i++){
        if((strcmp(variavel, tabelaVariaveis[i].variavel) == 0)&&(strcmp(funcao, tabelaVariaveis[i].funcao)== 0)){
        return tabelaVariaveis[i].tipo;            
        }
    }
    return 0;
}


void printaTabela(){
    for(int i = 0; i < indexTabela; i++){
        printf("\n  Variavel %s | Tipo: %d | Valor: %s | Função : %s",tabelaVariaveis[i].variavel,
        tabelaVariaveis[i].tipo,tabelaVariaveis[i].valor,tabelaVariaveis[i].funcao);
    }
}

char * preencheTabelaAssembly(char *operador,char *resultado,char *op1,char *op2){
        char *numeroRegistradorTemporario = malloc (sizeof (char) * 1000);
        char *resultadoAux = malloc (sizeof (char) * 1000);
        char *operadorAux = malloc (sizeof (char) * 10);
        char *op1Aux = malloc (sizeof (char) * 100);
        char *op2Aux = malloc (sizeof (char) * 100);
        strcpy(resultadoAux,resultado);
        strcpy(operadorAux,operador);
        strcpy(op1Aux,op1);
        strcpy(op2Aux,op2);
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

}

void printaTabelaAssembly(){
    for(int i = 0; i < indexAssembly; i++){
        printf("\n  Operador: %s | Resultado: %s | Operador 1: %s | Operador 2 : %s",tabelaAssembly[i].operador,
        tabelaAssembly[i].resultado,tabelaAssembly[i].op1,tabelaAssembly[i].op2);
    }
}