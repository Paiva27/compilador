#include "lexico.h"
#include "sintatico.h"
#include<stdlib.h>
#include<stdio.h>


int main(int argc, char *argv[]){
    iniciar(argc, argv);
    criaListaTokens();
    analisaLista();
    encerrar();
    return 0;
}