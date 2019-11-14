#ifndef ANALISADOR_SINTATICO_H
#define ANALISADOR_SINTATICO_H
#include "lexico.h"

Token lista[10000];
typedef char* string;
typedef enum {FALSE, TRUE} bool;

int analisaLista();
int analisaCodigo();

int analisaIf(int i);
void criaListaTokens();

#endif