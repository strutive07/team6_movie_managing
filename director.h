// 헤더파일 중복 체크
#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _BEST_MOVIE_
#define _BEST_MOVIE_

// director 내부에 들어가는 best movie 구조체
struct best_movie{
  char *title;
  struct movie *movie_link;
  struct best_movie *movie_next;
};

#endif

// director 구조체
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

void init_director(); // log 파일에서 읽어서 director 구조체 생성
void add_list_director(FILE *list, char* origin); // list 파일 생성
struct movie* search_director_to_movie_title(char* title);  // movie 구조체의 제목 확인
int search_director_to_movie(DIRECTOR tmp); // director 구조체에서 best movie 구조체 체크
void link_director_to_movie(); // movie 구조체와 연결하는 함수

MOVIE list_movie_director(char* title); // best movie 구조체 생성
MOVIE put_list_movie_director(MOVIE origin, MOVIE tmp); // best movie 구조체에 추가 연결
void print_movie_director(MOVIE movie); // best movie 구조체 출력

DIRECTOR list_director(char* serial_number, char* name, char* sex, char* birth, MOVIE movie); // director 구조체 생성
DIRECTOR put_list_director(DIRECTOR origin, DIRECTOR tmp); // director 구조체 추가 연결
void print_director(DIRECTOR director); // director 구조체 출력

#endif
