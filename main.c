#include "lexico.h"
#include<stdlib.h>


int main(int argc, char *argv[]){

    iniciar(argc, argv);
    Token *token = proximo_token();
    while(token != NULL){
        imprimeToken(token);
        token = proximo_token();
    }
    encerrar();
    return 0;
}