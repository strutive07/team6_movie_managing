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

void you_wanna_end();
void whats_up_commander();

void update_list_director(char *option, char *serial, DIRECTOR director);
DIRECTOR move_serial_director(int serial, DIRECTOR origin);

void update_list_actor(char *option, char *serial, ACTOR actor);
ACTOR move_serial_actor(int serial, ACTOR origin);

void update_list_movie(char *option, char *serial, struct movie *movie);
struct movie* move_serial_movie(int serial, struct movie *origin);

int director_overlap(DIRECTOR director);
int actor_overlap(ACTOR actor);

void colon_rchange(char *tmp_char);

void print_list_director(DIRECTOR director, char *serial);
void print_list_actor(ACTOR actor, char *serial);
void print_list_movie(struct movie *movie, char *serial);

DIRECTOR serach_last_director(DIRECTOR public_first_director);
void option_add_movie(struct movie *movie);
void option_add_director(DIRECTOR public_first_director);
void option_add_actor(ACTOR public_actor);
ACTOR serach_last_actor(ACTOR public_actor);
void fprint_list_movie_director_actor(struct movie *movie, DIRECTOR director, ACTOR actor);
int option_search_meta_search(char* string_orign, char* string_search);
int option_search_movie(struct movie* movie, char* search_string);
int option_search_director(DIRECTOR director, char* search_string);
int option_search_actor(ACTOR actor, char* search_string);

void save_list_movie(char* option, struct movie *movie);
void save_list_director(char* option, struct director *director);
void save_list_actor(char* option, struct actor *actor);
char* insert_string(char *origin, char *insert, int pos);

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

void sort_actor(char option, ACTOR actor);
void sort_director(char option, DIRECTOR director);
void sort_movie(char option, struct movie* movie);

int count_actor_list(ACTOR actor);
int count_director_list(DIRECTOR director);
int count_movie_list(struct movie* movie);

void option_delete_actor(int num,ACTOR actor);

#endif
