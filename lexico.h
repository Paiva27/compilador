#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H


enum categoria{

    tk_rel_op = 256,
    tk_id = 257,
    tk_const_int = 258,
    tk_const_float =259,
    tk_const_lit = 260,
    tk_kw_int = 261,
    tk_kw_float = 262,
    tk_kw_char = 263,
    tk_kw_if = 264,
    tk_kw_else = 265,
    tk_kw_for = 266,
    tk_kw_while = 267,
    tk_kw_break = 268,
    tk_kw_not = 269,
    tk_kw_and = 270,
    tk_kw_or = 271,
    tk_kw_main = 272,
    tk_kw_func = 273,
    tk_kw_return = 274,
    tk_kw_strcmp = 275,
    tk_kw_strcop = 276,
    tk_kw_input = 277,
    tk_kw_output = 278,
    tk_kw_include = 279,
    tk_op_add = 280,
    tk_op_sub = 281,
    tk_op_mul = 282,
    tk_op_div = 283,
    tk_op_atrib = 284,
    tk_open_par = 285,
    tk_close_par = 286,
    tk_open_bra = 287,
    tk_close_bra = 288,
    tk_close_key = 289,
    tk_open_key = 290,
    tk_semicolon = 291,
    tk_comma = 292,
    erro  = 293
};
typedef enum categoria Categoria;

struct token{
    char *valor;
    Categoria categoria;
    int linha;
    int coluna;
};

typedef struct token Token;

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