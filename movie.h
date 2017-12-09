#ifndef _MOVIE_H_
#define _MOVIE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "director.h"
#include "actor.h"
#include "option.h"
//전역 변수
struct movie *public_next_movie;
struct movie *public_first_movie;
//전역 변수 _ 파일 구조체
  FILE *mv_log_read,*mv_log_add, *mv_list;
//구조체
struct linked_list_actor{
  char* actor_name;
  struct linked_list_actor *actor_next;
  struct actor *actor_pointer;
};

struct director_in_movie{
  char* name;
  struct director *director_pointer;
};

struct movie{
  int Serial_number;
  char* title;
  char* genre;
  struct director_in_movie director;
  int year;
  int time;
  struct linked_list_actor *actor;
  struct movie *movie_next;
};

// struct director{
//   int Serial_number;
// };
// struct actor{
//   int Serial_number;
// };

//함수 원형
// void print_actor(struct linked_list_actor *actor);
struct linked_list_actor *create_actor_struct(char * actor_parse);
struct movie *parse_movie(char* buffer, int isFirst);
struct movie *search_last_movie(struct movie *movie);
void update_movie(struct movie* movie, FILE *mv_log);
void init_movie();
struct director* search_director_in_movie(DIRECTOR argument_director, char* argument_name);
void lint_movie_to_director(DIRECTOR argument_director, struct movie* argument_movie);
struct actor* search_actor_in_movie(ACTOR argument_actor, char* argument_actor_name);
void lint_movie_to_actor(ACTOR argument_actor, struct movie* argument_movie);
char* colon_change(char* tmp_char);
#endif
