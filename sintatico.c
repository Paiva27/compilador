#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "lexico.h"
#include "sintatico.h"

int quantidadeErros = 0;

void criaListaTokens(){
    Token *token = proximo_token();
   /* //Cria a cabeça da lista
    lista[0].categoria = 0;
    lista[0].valor = "inicio";
    lista[0].linha = 0;
    lista[0].coluna = 0;*/

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
int analisaParametros(int i){
    int flag = 0;    
    //Enquanto tiver dentro do parenteses procura declaraçoes de paramentros
    while(flag == 0){
        //Analisa caso o token seja int,float,char ou void
        if((lista[i+1].categoria==6)||(lista[i+1].categoria==7)||(lista[i+1].categoria==8)||(lista[i+1].categoria==25)){
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
                    i += 3;
                }else if(lista[i+3].categoria == 32){
                    //Acabou a declaração
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


int analisaDeclaracaoVariaveis (int i){
    int flag = 0;
       while(flag == 0){
            //Verifica se tem tipo ID após o tipo
            if(lista[i+1].categoria== 1){
                //Caso tenha mais um parametro verifica se tem virgula
                if(lista[i+2].categoria == 38){
                    //Pula a ultima decalaração e vai para a proxima
                    i += 2;
                }else if(lista[i+2].categoria == 37){
                    //Acabou a declaração
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

int operacaoAritmetica(int i){
    //Verificando se tem um operador de atribuição "="
    if(lista[i+1].categoria == 30){
        //Verifica se após o operador de atribuição existe um id
        if(lista[i+2].categoria == 1){
            //Verificando se tem um operador de soma,subtração,multiplicação,divisão
            if((lista[i+3].categoria == 26) || (lista[i+3].categoria == 27) || (lista[i+3].categoria == 28) || (lista[i+3].categoria == 29)){
                //Verificando se após os operadores aritméticos existe um outro id
                if((lista[i+4].categoria == 1)||(lista[i+4].categoria == 3)||(lista[i+4].categoria == 4)||(lista[i+4].categoria == 5)){
                    if(lista[i+5].categoria == 37){
                        return i += 5;
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

int analisaFor(int i){
    //Verifica o parenteses aberto
    if(lista[i+1].categoria==31){
        //Verifica se a declaração esta sendo feita por um tipo aceito 
        if((lista[i+2].categoria == 6) || (lista[i+2].categoria == 7) || (lista[i+2].categoria == 8)){
            i = analisaDeclaracaoVariaveis(i+2);
            i = operacaoLogica(i);
            if(lista[i+2].categoria==1){
                i = operacaoAritmetica(i+2);
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

int analisaEscopo(int i){
    //Enquanto não chegar no final da função (indicado por } ) ele continua a andar nos tokens
    while (lista[i+1].categoria != 35){
        //If para a declaração de variáveis tipos : int, float, char e void.
        if((lista[i+1].categoria==6)||(lista[i+1].categoria==7)||(lista[i+1].categoria==8)||(lista[i+1].categoria==25)){
            i = analisaDeclaracaoVariaveis(i+1);
        }
        //If que indica que estão sendo feitas operações aritméticas dentro do escopo.
        else if(lista[i+1].categoria==1){
            i = operacaoAritmetica(i+1);
        }
        //If que chama uma função para analisar se tudo esta certo com o if do codigo
        else if(lista[i+1].categoria==9){
            i = analisaIf(i+1);
            i = analisaElse(i);
        } 
        //If que chama uma função para analisar se tudo esta certo com o for do codigo
        else if(lista[i+1].categoria==11){
            i = analisaFor(i+1);
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
        if(lista[i+2].categoria == 31){
            //Verifica a declaração dos parametros 
            i = analisaParametros(i+2);
                //Analisa o escopo da função 
                if(lista[i+1].categoria == 36){
                    return analisaEscopo(i+1);
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