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
struct movie move_serial_movie(int serial, struct movie *origin);

void save_list_movie(char* option, struct movie *movie);
void save_list_director(char* option, struct director *director);
void save_list_actor(char* option, struct actor *actor);
char* insert_string(char *origin, char *insert, int pos);

#endif
