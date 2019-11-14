#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "lexico.h"
#include "sintatico.h"
#include "semantico.h"

int quantidadeErros = 0;

void criaListaTokens(){
    Token *token = proximo_token();
    int i = 1;
    while(token != NULL){
        if(token != NULL){
        lista[i].categoria = token->categoria;
        lista[i].valor = token->valor;
        lista[i].linha = token->linha;
        lista[i].coluna = token->coluna;
        i++;
        }
        token = proximo_token();
    }
    lista[i+1].categoria = 40;
    
    i=1;
    while(lista[i].categoria != 40){
        printf("[categoria: %d Valor: %s Linha: %d Coluna: %d]\n", lista[i].categoria, lista[i].valor, lista[i].linha, lista[i].coluna);
        i++;
    }

}

int  analisaLista(){
    int i=1;
    i = analisaCodigo(i);
    printf("\n\nQuantidade de erros no programa : %d",quantidadeErros);
    return 0;
}



int consertaBostaDeclaracaoParametros(int i){ 
    int aux = 0;
    int flag = 0;
        while (flag == 0){
            //Ignora erros até um parentesis
            if(lista[i+aux].categoria == 32){
            return i + aux;
            //Ignora erros até uma chave aberta
            }else if(lista[i+aux].categoria == 36){
            return i;
            }
        aux++;
        }
return i;
}

//Analisa a declaração de parametros em uma função
int analisaParametros(int i,char *funcao){
    int flag = 0;    
    //Enquanto tiver dentro do parenteses procura declaraçoes de paramentros
    while(flag == 0){
        //Analisa caso o token seja int,float,char ou void
        if((lista[i+1].categoria==6)||(lista[i+1].categoria==7)||(lista[i+1].categoria==8)||(lista[i+1].categoria==25)){
            int tipo =  lista[i+1].categoria;
            //Verifica caso tenha um id
            if(lista[i+2].categoria== 1){
                //Caso tenha mais um parametro verifica se tem virgula
                if(lista[i+3].categoria == 38){
                        //Erro caso tenha o parenteses fechado dps da virgula
                        if(lista[i+4].categoria == 32){
                            printf("\nErro - Parametro esperado antes da virgula em : linha: %d , coluna %d ", 
                            lista[i+3].linha ,lista[i+3].coluna);
                            quantidadeErros++;
                        }
                    //Pula a ultima decalaração e vai para a proxima
                    preencheTabela(lista[i+2].valor,tipo,funcao,lista[i+2].linha,lista[i+2].coluna);
                    i += 3;
                }else if(lista[i+3].categoria == 32){
                    //Acabou a declaração
                    preencheTabela(lista[i+2].valor,tipo,funcao,lista[i+2].linha,lista[i+2].coluna);
                    flag = 1;
                }else{
                    //Erro - Caractere não esperado
                    printf("\nErro - Caractere não esperado em : linha: %d , coluna %d ", lista[i+3].linha ,lista[i+3].coluna);
                    quantidadeErros++;
                    return consertaBostaDeclaracaoParametros(i+3);
                }
            //Erro - esperado um id mas tem um parenteses fechado  
            }else if (lista[i+2].categoria == 32) {   
                printf("\nErro - ID esperado em : linha: %d , coluna %d ", lista[i+2].linha ,lista[i+2].coluna);
            return i+2;
            }else{
            // Erro geral na declaração
            printf("\nErro - Caractere não esperado : linha: %d , coluna %d ", lista[i+2].linha ,lista[i+2].coluna);
            return consertaBostaDeclaracaoParametros(i+2);
            }
        }else if(lista[i+1].categoria == 38){
            //Ignorar erro
            printf("\nErro - Caractere não esperado em : linha: %d , coluna %d ", lista[i+1].linha ,lista[i+1].coluna);
            quantidadeErros++;
            i++;
        //Caso não tenha parâmetro na função    
        }else if (lista[i+1].categoria == 32) {   
            return i + 1;
        }else{
            //Erro - (Ou struct) Declaração de tipo não válido   
            printf("\nErro - Declaração de tipo não válido em : linha: %d , coluna %d ", lista[i+1].linha ,lista[i+1].coluna);
            quantidadeErros++;
            return consertaBostaDeclaracaoParametros(i+1);
        }
    }
    //Se flag for 0 ou 1 indicam final da declaração então retorna o fim da declaração no parenteses fechado
    if(flag == 1){
        return i += 3;
    }
return i; 
}

//Função q corrige erros antes de ponto e vírgula e seta os tokens até o próximo ponto e vírgula
int consertaBostaGeral(int i){ 
    int aux = 0;
    int flag = 0;
        while (flag == 0){
            //Ignora erros até um ponto e virgula
            if(lista[i+aux].categoria == 37){
            return i+aux;
            }else if(lista[i+aux].categoria == 32){
            return i+aux;
            }
            aux++;
        }
return i;
}


int analisaDeclaracaoVariaveis (int i,char *funcao){
    int flag = 0;
    int categoria = lista[i].categoria;
       while(flag == 0){
            //Verifica se tem tipo ID após o tipo
            if(lista[i+1].categoria== 1){
                //Caso tenha mais um parametro verifica se tem virgula
                if(lista[i+2].categoria == 38){
                    //Pula a ultima decalaração e vai para a proxima
                    preencheTabela(lista[i+1].valor,categoria,funcao,lista[i+1].linha,lista[i+1].coluna);
                    i += 2;

                }else if(lista[i+2].categoria == 37){
                    //Acabou a declaração
                    preencheTabela(lista[i+1].valor,categoria,funcao,lista[i+1].linha,lista[i+1].coluna);
                    return i+2;
                }else{
                    //Erro - Caractere não esperado
                    printf("\nErro - Caractere não esperado em : linha: %d , coluna %d ", lista[i+2].linha ,lista[i+2].coluna);
                    quantidadeErros++;
                    return consertaBostaGeral(i+2);
                }
            //Erro - esperado um id mas tem um parenteses fechado  
            }else if (lista[i+1].categoria == 32) {   
                printf("\nErro - ID esperado em : linha: %d , coluna %d ", lista[i+1].linha ,lista[i+1].coluna);
                quantidadeErros++;
                return i;
            }else{
            // Erro geral na declaração
            quantidadeErros++;
            return consertaBostaGeral(i+1);
            }
        }
}

int notacaoPilha(Token operadores[100], char *escopoAtual,int iterOperacao){
    printf("\nOperações: ");
    for(int i =0; i < iterOperacao ; i++){
        printf("%s",operadores[i].valor);
    }
    int i = 0, indexPrincipal = 0, aux =0, tipo = 0, op1 = 0 ,op2 = 0;
    char resultTemp[1000] = "";
    while((operadores[i].categoria != 40 )&& aux == 0){
        if((operadores[i].categoria == 28)||(operadores[i].categoria == 29)){
            printf("\n%s%s%s",operadores[i-1].valor,operadores[i].valor,
            operadores[i+1].valor);
            if(operadores[i-1].categoria == 1)
            op1 = verificaOperacao(operadores[i-1].valor,escopoAtual);
            if(operadores[i+1].categoria == 1)
            op2 = verificaOperacao(operadores[i+1].valor,escopoAtual);
            if(op1 == 0)op1 = operadores[i-1].categoria;
            if(op2 == 0)op2 = operadores[i+1].categoria; 
            if(operadores[i].categoria == 29){
                tipo = 7;
            }else{
                tipo = tbTiposSoma[((op1)-3)%3][((op2)-3)%3];
            }
            strcpy(resultTemp,preencheTabelaAssembly(operadores[i].valor,"regTemp",operadores[i-1].valor,operadores[i+1].valor));
            indexPrincipal = i;
            aux = 1;
        }
        i++;
    }
    while((operadores[i].categoria != 40 )){
        if((operadores[i].categoria == 28)||(operadores[i].categoria == 29)){
            printf("\n%s%s",operadores[i].valor,operadores[i+1].valor);
            if(op1 == 0)op1 = operadores[i+1].categoria; 
            if(operadores[i].categoria == 29){
                tipo = 7;
            
            }else{
                tipo = tbTiposSoma[tipo][((op2)-3)%3];
         
            }
        strcpy(resultTemp,preencheTabelaAssembly(operadores[i].valor,"regTemp",resultTemp,operadores[i+1].valor));
        }
        i++;
    }
    if(aux == 0){
        op1 = 0,op2 = 0;
        i = 0;
        while((operadores[i].categoria != 40)&& aux == 0){
        if((operadores[i].categoria == 26)||(operadores[i].categoria == 27)){
            printf("\n%s%s%s",operadores[i-1].valor,operadores[i].valor,
            operadores[i+1].valor);  
            if(operadores[i-1].categoria == 1)
            op1 = verificaOperacao(operadores[i-1].valor,escopoAtual);
            if(operadores[i+1].categoria == 1)
            op2 = verificaOperacao(operadores[i+1].valor,escopoAtual);
            if(op1 == 0)op1 = operadores[i-1].categoria;
            if(op2 == 0)op2 = operadores[i+1].categoria;
            printf("\n%d%s%d",((op1)-3)%3,operadores[i].valor,((op2)-3)%3);
            tipo = tbTiposSoma[((op1)-3)%3][((op2)-3)%3];
            strcpy(resultTemp,preencheTabelaAssembly(operadores[i].valor,"regTemp",operadores[i-1].valor,operadores[i+1].valor));
            indexPrincipal = i;
            aux = 1;
        }
        i++;
        }
        while((operadores[i].categoria != 40)){
            if((operadores[i].categoria == 26)||(operadores[i].categoria == 27)){
                printf("\n%s%s",operadores[i].valor,operadores[i+1].valor);
                op1 = verificaOperacao(operadores[i+1].valor,escopoAtual);
                if(op1 == 0)op1 = operadores[i-1].categoria;
                tipo = tbTiposSoma[((tipo)-3)%3][((op1)-3)%3];
            strcpy(resultTemp,preencheTabelaAssembly(operadores[i].valor,"regTemp",resultTemp,operadores[i+1].valor));
            }

            i++;
        }
    }else{
        i=0;
        while((operadores[i].categoria != 40)){
            if((operadores[i].categoria == 26)||(operadores[i].categoria == 27)){
                printf("\n%s%s",operadores[i].valor,operadores[i+1].valor);
                op1 = verificaOperacao(operadores[i+1].valor,escopoAtual);
                if(op1 == 0)op1 = operadores[i-1].categoria;
                tipo = tbTiposSoma[((tipo)-3)%3][((op1)-3)%3];
                strcpy(resultTemp,preencheTabelaAssembly(operadores[i].valor,"regTemp",resultTemp,operadores[i+1].valor));
            }

            i++;
        }
    }
return tipo;
}

int operacaoAritmetica(int i,char *escopoAtual){
    //Verificando se tem um operador de atribuição "="
    Token operacao[100];
    int iMudou =0;
    int iteraOperacao = 0;
    if(lista[i+1].categoria == 30){
        while(1){
            //Verifica se após o operador de atribuição existe um id
            if((lista[i+2].categoria == 1)||(lista[i+2].categoria == 3)||(lista[i+2].categoria == 4)||(lista[i+2].categoria == 5)){
                verificaTabela(lista[i+2].valor,lista[i+2].categoria,escopoAtual,lista[i+2].linha,lista[i+2].coluna);
                operacao[iteraOperacao].categoria = lista[i+2].categoria;
                operacao[iteraOperacao].valor = lista[i+2].valor;
                operacao[iteraOperacao].linha = lista[i+2].linha;
                operacao[iteraOperacao].coluna = lista[i+2].coluna;
                iteraOperacao++;
                //Verificando se tem um operador de soma,subtração,multiplicação,divisão
                if((lista[i+3].categoria == 26) || (lista[i+3].categoria == 27) || (lista[i+3].categoria == 28) || (lista[i+3].categoria == 29)){
                    operacao[iteraOperacao].categoria = lista[i+3].categoria;
                    operacao[iteraOperacao].valor = lista[i+3].valor;
                    operacao[iteraOperacao].linha = lista[i+3].linha;
                    operacao[iteraOperacao].coluna = lista[i+3].coluna;
                    iteraOperacao++;
                    //Verificando se após os operadores aritméticos existe um outro id
                    if((lista[i+4].categoria == 1)||(lista[i+4].categoria == 3)||(lista[i+4].categoria == 4)||(lista[i+4].categoria == 5)){
                        if(lista[i+4].categoria == 1)
                        verificaTabela(lista[i+4].valor,lista[i+4].categoria,escopoAtual,lista[i+4].linha,lista[i+4].coluna);
                        operacao[iteraOperacao].categoria = lista[i+4].categoria;
                        operacao[iteraOperacao].valor = lista[i+4].valor;
                        operacao[iteraOperacao].linha = lista[i+4].linha;
                        operacao[iteraOperacao].coluna = lista[i+4].coluna;
                        iteraOperacao++;
        
                        if(lista[i+5].categoria == 37){
                            operacao[iteraOperacao].valor = "";
                            operacao[iteraOperacao].linha = 0;
                            operacao[iteraOperacao].coluna = 0;
                            operacao[iteraOperacao].categoria = 40;
                            int novoTipo = notacaoPilha(operacao,escopoAtual,iteraOperacao);
                            mudaVariavelTabela(lista[i-iMudou].valor,novoTipo,escopoAtual,lista[i+4].linha ,lista[i+4].coluna);
                            //printf("Atualmente o temporario é : %s",tabelaAssembly[indexAssembly-1].resultado);
                            preencheTabelaAssembly("=",lista[i-iMudou].valor,tabelaAssembly[indexAssembly-1].resultado,"");
                            return i += 5;
                        }else if((lista[i+5].categoria == 26) || (lista[i+5].categoria == 27) || 
                        (lista[i+5].categoria == 28) || (lista[i+5].categoria == 29)){
                            operacao[iteraOperacao].categoria = lista[i+5].categoria;
                            operacao[iteraOperacao].valor = lista[i+5].valor;
                            operacao[iteraOperacao].linha = lista[i+5].linha;
                            operacao[iteraOperacao].coluna = lista[i+5].coluna;
                            iteraOperacao++;
                            i += 4;
                            iMudou +=4;
                        
                        }else{
                            printf("\nErro - Ponto e vírgula não encontrado esperado em : linha: %d , coluna %d ", 
                            lista[i+4].linha ,lista[i+4].coluna);
                            quantidadeErros++;
                            return consertaBostaGeral(i+4);
                        }
                    //Erro - Faltou um ID para completar a operação
                    }else{ 
                        printf("\nErro - ID não encontrado esperado em : linha: %d , coluna %d ", lista[i+4].linha ,lista[i+4].coluna);
                        quantidadeErros++;
                        return consertaBostaGeral(i+4);
                    }
                //Operação de atribuição de valores entre 2 ids 
                }else if(lista[i+3].categoria == 37){
                    operacao[iteraOperacao].valor = "";
                    operacao[iteraOperacao].linha = 0;
                    operacao[iteraOperacao].coluna = 0;
                    operacao[iteraOperacao].categoria = 40;
                    int novoTipo = notacaoPilha(operacao,escopoAtual,iteraOperacao);
                    mudaVariavelTabela(lista[i].valor,novoTipo,escopoAtual,lista[i+4].linha ,lista[i+4].coluna);
                    preencheTabelaAssembly("=",lista[i].valor,tabelaAssembly[indexAssembly-1].resultado,"");
                    //printf("Atualmente o temporario é : %s",tabelaAssembly[indexAssembly].resultado);
                    return i+=3;
                //Erro - Caracter não esperado depois do operador
                }else{
                    printf("\nErro - Caracter não esperado em : linha: %d , coluna %d ", lista[i+3].linha ,lista[i+3].coluna);  
                    quantidadeErros++;  
                    return consertaBostaGeral(i+3);
                }
            //Operação de atribuição de um valor constante para um id     
            }else if((lista[i+2].categoria == 3)||(lista[i+2].categoria == 4)||(lista[i+2].categoria == 5)){
                return i+3;     
            //Caso não exista id dps da atribuição
            }else{
                printf("\nErro - ID não encontrado esperado em : linha: %d , coluna %d ", lista[i+2].linha ,lista[i+2].coluna);   
                quantidadeErros++; 
                return consertaBostaGeral(i+2);
            }
        }
    
    }else if((lista[i+1].categoria == 26)&&(lista[i+2].categoria == 26)){
        return i + 3;
    }else{
        printf("\nErro - Operador de atribuição esperado em : linha: %d , coluna %d ", lista[i+1].linha ,lista[i+1].coluna);  
        quantidadeErros++;  
        return consertaBostaGeral(i+1);    
    }
return i;
}

//Operação lógica simplificada para ter somente ID Operador_Logico ID ou constante
int operacaoLogica (int i){
    //Verifica caso tenha id
    if(lista[i+1].categoria==1){
        //Verificar se tem um operador lógico no meio
        if(lista[i+2].categoria==2){
            //Verifica se terá um ID ou constante para comparação
            if((lista[i+3].categoria == 1)||(lista[i+3].categoria == 3)||(lista[i+3].categoria == 4)||(lista[i+3].categoria == 5)){
                    return i += 3;    
                }else{
                    printf("\nErro - Erro lógico em linha: %d , coluna %d ", lista[i+3].linha ,lista[i+3].coluna);
                    quantidadeErros++;
                    return consertaBostaGeral(i+3)-1;
                }
            }else{
                 printf("\nErro - Erro lógico em linha: %d , coluna %d ", lista[i+2].linha ,lista[i+2].coluna);
                 quantidadeErros++;
                return consertaBostaGeral(i+2)-1;
            }
        }else{
            printf("\nErro - Erro lógico em linha: %d , coluna %d ", lista[i+1].linha ,lista[i+1].coluna);
            quantidadeErros++;
            return consertaBostaGeral(i+1)-1;
        }
}


int analisaIf(int i){
    //Analisa Parenteses aberto
    if(lista[i+1].categoria==31){
        i = operacaoLogica(i+1);
        //Analisa dps da operação logica se o parenteses foi fechado
        if(lista[i+1].categoria==32){
            //Verifica se uma chave foi aberta
            if(lista[i+2].categoria==36){
                //Chama a função escopo que acaba assim que recebe um }
                i =  analisaEscopo(i+2);    
            }
        }
    }
    return i;  
}

int analisaElse(int i){
    if(lista[i].categoria==35){
        if(lista[i+1].categoria==10){
            if(lista[i+2].categoria==36){
                i = analisaEscopo(i+2);
            }
        }
    }
}

int analisaFor(int i,char *escopoAtual){
    //Verifica o parenteses aberto
    if(lista[i+1].categoria==31){
        //Verifica se a declaração esta sendo feita por um tipo aceito 
        if((lista[i+2].categoria == 6) || (lista[i+2].categoria == 7) || (lista[i+2].categoria == 8)){
            i = analisaDeclaracaoVariaveis(i+2,"2");
            i = operacaoLogica(i);
            if(lista[i+2].categoria==1){
                i = operacaoAritmetica(i+2,escopoAtual);
                if(lista[i+1].categoria==36){
                    i = analisaEscopo(i+1);
                }
            }
        }
    }
}

int analisaWhile(int i){
    //Analisa Parenteses aberto
        if(lista[i+1].categoria==31){
            i = operacaoLogica(i+1);
            //Analisa dps da operação logica se o parenteses foi fechado
            if(lista[i+1].categoria==32){
                //Verifica se uma chave foi aberta
                if(lista[i+2].categoria==36){
                    //Chama a função escopo que acaba assim que recebe um }
                    i =  analisaEscopo(i+2);    
                }
            }
        }
    return i;  
}

int analisaEscopo(int i,char *escopoAtual){
    //Enquanto não chegar no final da função (indicado por } ) ele continua a andar nos tokens
    
    while (lista[i+1].categoria != 35){
        //If para a declaração de variáveis tipos : int, float, char e void.
        if((lista[i+1].categoria==6)||(lista[i+1].categoria==7)||(lista[i+1].categoria==8)||(lista[i+1].categoria==25)){
            i = analisaDeclaracaoVariaveis(i+1,escopoAtual);
        }
        //If que indica que estão sendo feitas operações aritméticas dentro do escopo.
        else if(lista[i+1].categoria==1){
            i = operacaoAritmetica(i+1,escopoAtual);
        }
        //If que chama uma função para analisar se tudo esta certo com o if do codigo
        else if(lista[i+1].categoria==9){
            i = analisaIf(i+1);
            i = analisaElse(i);
        } 
        //If que chama uma função para analisar se tudo esta certo com o for do codigo
        else if(lista[i+1].categoria==11){
            i = analisaFor(i+1,escopoAtual);
        }
        else if(lista[i+1].categoria==12){
            i = analisaWhile(i+1);
        
        }else{ 
            printf("\nErro - O código tem erro de chaves, olhar em linha: %d , coluna %d ", lista[i].linha ,lista[i].coluna);
            quantidadeErros++;
            break;
        }
    }
    return i+1;
}

int analisaFuncao(int i ){
    //Caso seja uma declaração entra aqui categoria ==1 é o nome da função
    if((lista[i+1].categoria == 1)||(lista[i+1].categoria==17)){
        //Verifica se tem um parenteses para declaração dos parametros
        char * escopoAtual = lista[i+1].valor;
        if(lista[i+2].categoria == 31){
            //Verifica a declaração dos parametros 
            i = analisaParametros(i+2,escopoAtual);
                //Analisa o escopo da função 
                if(lista[i+1].categoria == 36){
                    return analisaEscopo(i+1,escopoAtual);
                //Indica uma função vazia, só declaração formal    
                }else if(lista[i+1].categoria == 37){
                    return i+1;
                }else{ 
                //Caso Não seja nem { ou ; dps da função
                printf("\nErro - Caractere não esperado em : linha: %d , coluna %d ", lista[i+1].linha ,lista[i+1].coluna);
                quantidadeErros++;
                }
        }
    }
return 1;
}


int analisaCodigo(int i){
    //Declaração de função 
    if(lista[i].categoria != 0){
        if ((lista[i].categoria==6)||(lista[i].categoria==7)||(lista[i].categoria==8)||(lista[i].categoria==17)||(lista[i].categoria==25)){
            i = analisaFuncao(i);
            i = analisaCodigo(i+1);
        }
    }
return i;
}