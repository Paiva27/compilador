#ifndef ANALISADOR_SEMANTICO_H
#define ANALISADOR_SEMANTICO_H
#include "lexico.h"
#include "sintatico.h"

typedef struct variavel Variavel;
typedef struct assembly Assembly;

struct variavel{
    char *variavel;
    Categoria tipo;
    char *valor;
    char *funcao;
    int linha;
    int coluna;
};

struct assembly{
    char *operador;
    char *resultado;
    char *op1;
    char *op2;
};


Variavel tabelaVariaveis[10000];
int indexTabela;
int indexLiterais;

Assembly tabelaAssembly[10000];
int indexAssembly;


//Declaração das tabelas de tipos
int tbTiposSoma[6][3];
int tbTiposDivisao[6][3];

int contEstDeFluxo;
void geraCodigoOpLogica(char * operador,int contador,char * escopoAtual, char * op1,int op1Tipo,char * op2,int op2Tipo);
char * carregaEmRegistrador(char * op, char * funcao,int tipoOp);
void criaComando(char * op,char * result, char *op1, char *op2);
void criaLabel(char * label,int cont);
void iniciaTabelas();
void preencheTabela(char *variavel, Categoria tipo, char *funcao,int linha,int coluna,char * valor);
void printaTabela();
void verificaTabela(char *variavel,Categoria tipo,char *funcao,int linha,int coluna);
int verificaOperacao(char *variavel,char *funcao);
void mudaVariavelTabela(char *variavel,Categoria tipo,char *funcao,int linha,int coluna);
char * preencheTabelaAssembly(char *operador,char *resultado,char *op1,char *op2,char * funcao,int tipoOp1,int tipoOp2);
void printaTabelaAssembly();

#endif