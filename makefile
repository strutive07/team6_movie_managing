project: actor.o director.o movie.o main.o
	gcc -o project main.o movie.o director.o actor.o
main.o: main.c
	gcc -c main.c
movie.o: movie.c movie.h
	gcc -c movie.c
director.o: director.c director.h
	gcc -c director.c
actor.o: actor.c actor.h
	gcc -c actor.c
