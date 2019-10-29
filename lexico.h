#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H


enum categoria{
    tk_inicio = 0,
    tk_id = 1,
    tk_rel_op = 2,
    tk_const_int = 3,
    tk_const_float =4,
    tk_const_lit = 5,
    tk_kw_int = 6,
    tk_kw_float = 7,
    tk_kw_char = 8,
    tk_kw_if = 9,
    tk_kw_else = 10,
    tk_kw_for = 11,
    tk_kw_while = 12,
    tk_kw_break = 13,
    tk_kw_not = 14,
    tk_kw_and = 15,
    tk_kw_or = 16,
    tk_kw_main = 17,
    tk_kw_func = 18,
    tk_kw_return = 19,
    tk_kw_strcmp = 20,
    tk_kw_strcop = 21,
    tk_kw_input = 22,
    tk_kw_output = 23,
    tk_kw_include = 24,
    tk_kw_void = 25,
    tk_op_add = 26,
    tk_op_sub = 27,
    tk_op_mul = 28,
    tk_op_div = 29,
    tk_op_atrib = 30,
    tk_open_par = 31,
    tk_close_par = 32,
    tk_open_bra = 33,
    tk_close_bra = 34,
    tk_close_key = 35,
    tk_open_key = 36,
    tk_semicolon = 37,
    tk_comma = 38,
    erro  = 39,
    fim = 40
};
typedef enum categoria Categoria;

typedef struct token Token;

struct token{
    char *valor;
    Categoria categoria;
    int linha;
    int coluna;
};


Categoria achar_categoria(char *buffer);

void imprimeToken(Token *token);

char* pegar_valor_token(Token *token);

Token* delimitador();

Token* operador_aritmetico();

Token* operador_relacional();

Token* palavra();

Token* constante_literal();

Token* constante_numerica();

Token* incorretos();

void iniciar(int argc, char *argv[]);

void encerrar();

Token* proximo_token();

void eliminar_comentario();


#endif