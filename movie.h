#ifndef _MOVIE_H_
#define _MOVIE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//전역 변수
struct movie *public_next_movie;
struct movie *public_first_movie;
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
void print_movie(struct movie *movie, FILE* mv_log_write);
struct linked_list_actor *create_actor_struct(char * actor_parse);
struct movie *parse_movie(char* buffer, int isFirst);
void add_movie(struct movie *movie, FILE *mv_log_write, FILE *mv_log_read);
struct movie *search_last_movie(struct movie *movie);
void update_movie(struct movie* movie, FILE *mv_log);
void init_movie();

#endif
