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

#endif
