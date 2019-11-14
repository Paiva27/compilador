#include "lexico.h"
#include "sintatico.h"
#include "semantico.h"
#include<stdlib.h>
#include<stdio.h>


int main(int argc, char *argv[]){
    iniciar(argc, argv);
    criaListaTokens();
    iniciaTabelas();
    analisaLista();
    encerrar();
    printaTabela();
    printf("\n-----------\n");
    printaTabelaAssembly();
    return 0;
}