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

MOVIE list_movie_actor(char* title);//대표영화 삽입 함수
MOVIE put_list_movie_actor(MOVIE origin, MOVIE tmp);//대표영화 연결 함수
ACTOR list_actor(int serial_number, char* name, bool sex, char* birth, MOVIE movie);//구조체 삽입 함수
ACTOR put_list_actor(ACTOR origin, ACTOR tmp);//구조체 연결 함수

struct movie* search_actor_to_movie_title(char* title);//대표영화가 movie 구조체에 있는지 이름으로 확인하는 함수
int search_actor_to_movie(ACTOR public_actor_tmp);//대표영화가 movie 구조체에 있는지 확인하는 함수
void link_actor_to_movie();//대표영화와 movie구조체를 연결하는 함수

void print_movie_actor(MOVIE movie);//대표영화를 list파일에 출력하는 함수
void print_actor(ACTOR actor);//actor구조체를 list파일에 출력하는 함수
void actor_rtol(char* actor_str);//log파일 내용을 구조체로 넣는 함수
void init_actor();//log파일 내용을 구조체로 넣는 작업을 시작하는 함수

#endif
