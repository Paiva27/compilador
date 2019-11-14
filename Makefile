all: lexico
lexico: main.o lexico.o sintatico.o semantico.o
	gcc -o exec/exec objetos/main.o objetos/lexico.o objetos/sintatico.o objetos/semantico.o
main.o: main.c
	gcc -o objetos/main.o -c main.c
lexico.o: lexico.c lexico.h
	gcc -o objetos/lexico.o -c lexico.c
sintatico.o: sintatico.c sintatico.h
	gcc -o objetos/sintatico.o -c sintatico.c
semantico.o: semantico.c semantico.h
	gcc -o objetos/semantico.o -c semantico.c 