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

Assembly tabelaAssembly[10000];
int indexAssembly;

//Declaração das tabelas de tipos
int tbTiposSoma[6][3];
int tbTiposDivisao[6][3];


void iniciaTabelas();
void preencheTabela(char *variavel, Categoria tipo, char *funcao,int linha,int coluna);
void printaTabela();
void verificaTabela(char *variavel,Categoria tipo,char *funcao,int linha,int coluna);
int verificaOperacao(char *variavel,char *funcao);
void mudaVariavelTabela(char *variavel,Categoria tipo,char *funcao,int linha,int coluna);
char * preencheTabelaAssembly(char *operador,char *resultado,char *op1,char *op2);
void printaTabelaAssembly();

#endif