#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void you_wanna_end();
void whats_up_commander();
void update_list(char *command_what, char *option, char *split, DIRECTOR director);
void update_list_director(char *option, char *serial, DIRECTOR director);
DIRECTOR move_serial(int serial, DIRECTOR origin);

void whats_up_commander(){

  printf(">> Welcome to My Movie <<\n");
  printf("File Loading......\n");
  printf("You can use add, update, delete, search, sort, save, end commands.\n");

  char *whats_up_commander = (char*)malloc(sizeof(char)*100);
  char *split = (char*)malloc(sizeof(char)*100);
  char *command_what = (char*)malloc(sizeof(char));
  char *option = (char*)malloc(sizeof(char)*100);
  signal(SIGINT, you_wanna_end);
  while(1){
    printf("(movie) ");
    gets(whats_up_commander);
    split = strtok(whats_up_commander, " ");

    if(!strcmp(split,"update")){
      command_what = strtok(NULL, " ");
      option = strtok(NULL, " ");
      split = strtok(NULL, " ");
      update_list(command_what, option, split, director);
    }
  }

}

void update_list(char *command_what, char *option, char *split,DIRECTOR director){
  if (!strcmp(command_what, "d")){
    update_list_director(option, split, director);
  }
}


void you_wanna_end(int sig)
{
  char a;
  printf("\nGet Interrupt Signal.\n");
  printf("Do you want to exit myMOVIE program? (Y/N) ");
  scanf("%c", &a);
  if((a == 'y') || (a == 'Y')){
    printf("bye");
    exit(1);
  }
}

void update_list_director(char *option, char *serial, DIRECTOR director){

  int i = 0;
  int serial_num = atoi(serial);
  director = move_serial(serial_num, director);
  char option_letter = *option;
  char *tmp;

  while(i < strlen(option)){

  option_letter = *(option+i);

  tmp = (char *)calloc(1,sizeof(char)*100);

  switch(option_letter){

  case 'n':
  printf("Director name > ");
  gets(tmp);
  director->name = (char*)malloc(strlen(tmp)+1);
  strcpy(director->name, tmp);
  free(tmp);
  break;

  case 's':
  printf("Director sex > ");
  scanf("%c", &director -> sex);
  break;

  case 'b':
  printf("Director birth > ");
  scanf("%s", tmp);
  director->birth = (char*)malloc(strlen(tmp)+1);
  strcpy(director->birth, tmp);
  free(tmp);
  break;

  case 'm':
  printf("Director movie > ");
  gets(tmp);
  director->movie->title = (char*)malloc(strlen(tmp)+1);
  strcpy(director->movie->title, tmp);
  free(tmp);
  break;

  default:
  break;
  }

  i++;
  }

  //log 에 update 기록, 중복일 경우. 처음에 입력 어떻게 받는지.

}

DIRECTOR move_serial(int serial, DIRECTOR origin){
  DIRECTOR new;
  new = origin;
  int i = 0;
  while(serial != new -> serial_number)
  {
    new = new->director_next;
  }
  printf("%d\n", new->serial_number);
  return new;
}
