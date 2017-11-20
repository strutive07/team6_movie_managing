project: main.o movie.o director.o actor.o
    gcc -o project main.o movie.o director.o actor.o option.o
main.o: main.c
	  gcc -c main.c
movie.o: movie.c
	  gcc -c movie.c
director.o: director.c
	  gcc -c director.c
actor.o: actor.c
	  gcc -c actor.c
option.o: option.c
	  gcc -c option.c
