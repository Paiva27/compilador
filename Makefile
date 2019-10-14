all: lexico
lexico: main.o lexico.o 
	gcc -o exec/lexico objetos/main.o objetos/lexico.o 
main.o: main.c
	gcc -o objetos/main.o -c main.c
lexico.o: lexico.c lexico.h
	gcc -o objetos/lexico.o -c lexico.c