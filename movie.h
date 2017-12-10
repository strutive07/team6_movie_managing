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
//actor  구조체(in movie)
struct linked_list_actor{
  char* actor_name;
  struct linked_list_actor *actor_next;
  struct actor *actor_pointer;
};
//director struct (in movie)
struct director_in_movie{
  char* name;
  struct director *director_pointer;
};
//movie struct
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

//함수 원형
// void print_actor(struct linked_list_actor *actor);
struct linked_list_actor *create_actor_struct(char * actor_parse);//movie 에 있는 actor 를 만들어주는 함수. strtok 으로 , 기준으로 문자열을 잘라 저장함
struct movie *parse_movie(char* buffer, int isFirst);//1줄씩 받은것을 add, update, delete 를 처리해주는 함수
struct movie *search_last_movie(struct movie *movie);//마지막 movie 구조체를 찾는 함수. 없으면 NULL 마지막 구조체가 찾아지면 그 구조체 주소 반환
void init_movie();//main 에서 쓸 movie 초기화 함수
struct director* search_director_in_movie(DIRECTOR argument_director, char* argument_name);//argument_name 로 받은 문자열을 director 에 있는 name 멤버에서 찾는 함수
void lint_movie_to_director(DIRECTOR argument_director, struct movie* argument_movie);// movie 와 director 를 link 해주는 함수
struct actor* search_actor_in_movie(ACTOR argument_actor, char* argument_actor_name);//argument_name 로 받은 문자열을 actor 에 있는 name 멤버에서 찾는 함수
void lint_movie_to_actor(ACTOR argument_actor, struct movie* argument_movie);// movie 와 actor 를 link 해주는 함수
char* colon_change(char* tmp_char);// :   ->    ??;   로 변환해주는 함수
#endif
