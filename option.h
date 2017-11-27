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
DIRECTOR move_serial(int serial, DIRECTOR origin);
DIRECTOR serach_last_director(DIRECTOR public_first_director);
void option_add_movie(struct movie *movie);
void option_add_director(DIRECTOR public_first_director);
void fprint_list_movie_director_actor(struct movie *movie, DIRECTOR director, ACTOR actor);
void option_add_actor(ACTOR public_actor);
ACTOR serach_last_actor(ACTOR public_actor);
#endif
