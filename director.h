#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _BEST_MOVIE_
#define _BEST_MOVIE_

struct best_movie{
  char *title;
  struct movie *movie_link;
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

DIRECTOR public_director;

void init_director();
void add_list_director(FILE *list, char* origin);
struct movie* search_director_to_movie_title(char* title);
int search_director_to_movie(DIRECTOR tmp);
void link_director_to_movie();

MOVIE list_movie_director(char* title);
MOVIE put_list_movie_director(MOVIE origin, MOVIE tmp);
void print_director(DIRECTOR director);

DIRECTOR list_director(char* serial_number, char* name, char* sex, char* birth, MOVIE movie);
DIRECTOR put_list_director(DIRECTOR origin, DIRECTOR tmp);
void print_movie_director(MOVIE movie);

#endif
