#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void you_wanna_end();
void update_list_director(int serial, DIRECTOR director, char *option);
void move_serial(int serial, DIRECTOR origin);

void update_list_director(int serial, DIRECTOR director, char *option){

  // director = move_serial(serial, director);

  int i = 0;
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

void move_serial(int serial, DIRECTOR origin){
  DIRECTOR new;
  new = origin;
  int i = 0;
  while(serial != new -> serial_number)
  {
    new = new->director_next;
  }
  // origin = new;
  printf("%d\n", new->serial_number);

}

void you_wanna_end()
{
  char a;
  printf("\nGet Interrupt Signal. \n");
  printf("Do you want to exit myMOVIE program? (Y/N) \n");
  a = getchar();
  if(a == 'y' || a == 'Y'){
    printf("bye\n");
    exit(0);
  }else if(a == 'n' || a == 'N'){
    getchar();
  }


}
