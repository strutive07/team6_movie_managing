#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _BEST_MOVIE_
#define _BEST_MOVIE_

struct best_movie{
  char *title;
  struct best_movie *movie_next;
};

#endif

struct director{
  int serial_number;
  char *name;
  char sex;
  char *birth;
  struct best_movie *movie;
  struct director *director_next;
};

typedef struct best_movie* MOVIE;
typedef struct director* DIRECTOR;

void init_director();
void add_list_director(FILE *list, char* origin);

MOVIE list_movie_director(char* title);
MOVIE put_list_movie_director(MOVIE origin, MOVIE tmp);
void print_director(DIRECTOR director);

DIRECTOR list_director(char* serial_number, char* name, char* sex, char* birth, MOVIE movie);
DIRECTOR put_list_director(DIRECTOR origin, DIRECTOR tmp);
void print_movie_director(MOVIE movie);

#endif
