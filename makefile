main.o: main.c table.h saisie.h utils.h
	gcc -c main.c -lncurses

table.o: table.c table.h
	gcc -c table.c

sasie.o: saisie.c saisie.h table.h
	gcc -c saisie.c

utils.o: utils.c utils.h table.h
	gcc -c utils.c

main: main.o table.o saisie.o utils.o
	gcc main.o table.o saisie.o utils.o -o main -lncurses
