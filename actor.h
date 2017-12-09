#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifndef _BEST_MOVIE_
#define _BEST_MOVIE_

struct best_movie
{
   char* title;
   struct movie* movie_link;
   struct best_movie *movie_next;
};

typedef struct best_movie* MOVIE;

#endif

FILE *actor_log_read, *actor_log_add,*actor_list;

struct actor
{
   int serial_number;
   char *name;
   bool sex;
   char* birth;
   struct best_movie *movie;
   struct actor *actor_next;
};

typedef struct actor* ACTOR;

#include "option.h"
ACTOR public_actor;

MOVIE list_movie_actor(char* title);
MOVIE put_list_movie_actor(MOVIE origin, MOVIE tmp);
ACTOR list_actor(int serial_number, char* name, bool sex, char* birth, MOVIE movie);
ACTOR put_list_actor(ACTOR origin, ACTOR tmp);

struct movie* search_actor_to_movie_title(char* title);
int search_actor_to_movie(ACTOR public_actor_tmp);
void link_actor_to_movie();

void print_movie_actor(MOVIE movie);
void print_actor(ACTOR actor);
void actor_rtol(char* actor_str);
void init_actor();

#endif
