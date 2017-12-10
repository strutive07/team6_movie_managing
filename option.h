#ifndef _OPTION_H_
#define _OPTION_H_

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movie.h"
#include "director.h"
#include "actor.h"

void you_wanna_end(int sig); // 시그널 종료 여부를 묻는 함수
void whats_up_commander(); // 명령 입력을 받는 함수

void update_list_director(char *option, char *serial, DIRECTOR director); // director update 함수
DIRECTOR move_serial_director(int serial, DIRECTOR origin); // 특정 시리얼넘버 이동 함수

void update_list_actor(char *option, char *serial, ACTOR actor); // actor update 함수
ACTOR move_serial_actor(int serial, ACTOR origin); // 특정 시리얼 넘버 이동 함수

void update_list_movie(char *option, char *serial, struct movie *movie); //movie update 함수
struct movie* move_serial_movie(int serial, struct movie *origin); // 특정 시리얼 넘버 이동 함수

int director_overlap(char *tmp); // Same record 체크함수
int actor_overlap(char *tmp); // Same record 체크함수
int movie_overlap(char *tmp); // Same record 체크함수

void colon_rchange(char *tmp_char); // ??; -> : 변경함수(출력용)
void colon_frchange(FILE* fm,char *tmp_char);

void print_list_director(DIRECTOR director, char *serial); // director print 함수
void print_list_actor(ACTOR actor, char *serial); // actor print 함수
void print_list_movie(struct movie *movie, char *serial); // movie print 함수

DIRECTOR serach_last_director(DIRECTOR public_first_director); //마지막 director 찾는 함수
void option_add_movie(struct movie *movie);//옵션 - add 명령어 - movie 추가
void option_add_director(DIRECTOR public_first_director);//옵션 - add 명령어 - director 추가
void option_add_actor(ACTOR public_actor);//옵션 - add 명령어 - actor 추가
ACTOR serach_last_actor(ACTOR public_actor);//마지막 actor 찾는 함수
void fprint_list_movie_director_actor(char isMovie_DIrector_Actor,struct movie *movie, DIRECTOR director, ACTOR actor);//movie, director, actor list 에 업데이트 해주는 함수. 이미 list 파일이 있으면 현재 시간 받아서 백업본 만듬.
int option_search_meta_search(char* string_orign, char* string_search);//search 함수. string_search 인자로 메타문자가 포함될수 있는 문자열을 받아서 메타문자 문자열 검색 을 해주는 함수.
int option_search_movie(struct movie* movie, char* search_string);//movie 의 멤버들에서 search 하는 함수
int option_search_director(DIRECTOR director, char* search_string);//director 의 멤버들에서 search 하는 함수
int option_search_actor(ACTOR actor, char* search_string);//actor 의 멤버들에서 search 하는 함수

char* now_time_string();//현재 시간 문자열로 만들어서 리턴해주는 함수

void save_list_movie(char* option, struct movie *movie, char* option2); // movie 구조체 save 함수
void save_list_director(char* option, struct director *director, char* option2); // director 구조체 save 함수
void save_list_actor(char* option, struct actor *actor, char* option2); // actor 구조체 save 함수
char* insert_string(char *origin, char *insert, int pos); // string 2개 연결 함수

int cmp_actor_n(const void* a,const void* b);
int cmp_actor_s(const void* a,const void* b);
int cmp_actor_b(const void* a,const void* b);
int cmp_actor_m(const void* a,const void* b);
int cmp_director_n(const void* a,const void* b);
int cmp_director_s(const void* a,const void* b);
int cmp_director_b(const void* a,const void* b);
int cmp_director_m(const void* a,const void* b);
int cmp_movie_tt(const void* a,const void* b);
int cmp_movie_g(const void* a,const void* b);
int cmp_movie_d(const void* a,const void* b);
int cmp_movie_y(const void* a,const void* b);
int cmp_movie_r(const void* a,const void* b);
int cmp_movie_a(const void* a,const void* b);

void sort_actor(char option, ACTOR actor,char* option2);
void sort_director(char option, DIRECTOR director,char* option2);
void sort_movie(char option, struct movie* movie,char* option2);

int count_actor_list(ACTOR actor);
int count_director_list(DIRECTOR director);
int count_movie_list(struct movie* movie);

void option_delete_actor(int num,ACTOR actor,bool from_where);
void option_delete_director(int num,DIRECTOR director,bool from_where);
void option_delete_movie(int num,struct movie* movie,bool from_where);

#endif
