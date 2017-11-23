#include "option.h"

void whats_up_commander(){

  printf(">> Welcome to My Movie <<\n");
  printf("File Loading......\n");
  printf("You can use add, update, delete, search, sort, save, end commands.\n");

  char *whats_up_commander = (char*)malloc(sizeof(char)*100);
  char *split = (char*)malloc(sizeof(char)*100);
  char *command_what = (char*)malloc(sizeof(char));
  char *option = (char*)malloc(sizeof(char)*100);

  signal(SIGINT, you_wanna_end);

  DIRECTOR director = public_director;
  ACTOR actor = public_actor;
  struct movie *movies = public_first_movie;
  while(1){
    printf("(movie) ");
    gets(whats_up_commander);
    if(strlen(whats_up_commander) == 0){
    continue;
    }else{
    split = strtok(whats_up_commander, " ");
    }
    //strtok 할 게 없으면 fault 나오는걸 하나하나 처리해야할까?
      if(!strcmp(split,"update")){
      command_what = strtok(NULL, " ");
      option = strtok(NULL, " ");
      split = strtok(NULL, " ");

      if (!strcmp(command_what, "d")){
        update_list_director(option, split, director);
      }else if(!strcmp(command_what, "a")){
        update_list_actor(option, split, actor);
      }else if(!strcmp(command_what,"m")){
        update_list_movie(option, split, movies);
      }else{
        continue;
      }


    }
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
  }else{
    return;
  }
}

void update_list_director(char *option, char *serial, DIRECTOR director){

  int i = 0;
  int serial_num = atoi(serial);
  director = move_serial_director(serial_num, director);
  char option_letter = *option;
  char *tmp;
  int update_check = 1;
  FILE *write_in_log;

  write_in_log = fopen("director_log.txt","a");

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
  update_check *= 2;
  printf("%d update check\n", update_check);
  break;

  case 's':
  printf("Director sex > ");
  scanf("%c", &(director -> sex));
  update_check *= 3;
  printf("%d update check\n", update_check);
  break;

  case 'b':
  printf("Director birth > ");
  scanf("%s", tmp);
  director->birth = (char*)malloc(strlen(tmp)+1);
  strcpy(director->birth, tmp);
  free(tmp);
  update_check *= 5;
  printf("%d update check\n", update_check);
  break;

  case 'm':
  printf("Director movie > ");
  gets(tmp);
  director->movie->title = (char*)malloc(strlen(director->movie->title)+strlen(tmp)+3);
  // strcat(director->movie->title, ", ")
  // strcat(director->movie->title, tmp);
  free(tmp);
  update_check *= 7;
  printf("%d update check\n", update_check);
  break;

  default:
  break;
  }

  i++;
  }
  printf("%d update check\n", update_check);

  fprintf(write_in_log,"update:%d",serial_num);

   if((update_check % 2 != 0)){
     fprintf(write_in_log, ":=");
     printf("same name\n");
   }else{
     printf("different name\n");
     fprintf(write_in_log,":%s", director->name);
   }

   if((update_check % 3 != 0)){
     fprintf(write_in_log, ":=");
     printf("same sex\n");
     update_check -= 100;
   }else{
    printf("different sex\n");
    fprintf(write_in_log,":%c", director->sex);
  }

   if((update_check % 5 != 0)){
     fprintf(write_in_log, ":=");
     printf("same birth\n");
   }else{
     printf("different birth\n" );
     fprintf(write_in_log,":%s", director->birth);
   }
 // 수정 필요
   // if((update_check % != 0)){
   //     fprintf(write_in_log, ":=");
   // }else
   //     fprintf(write_in_log,":%s", director->movie->title);
     fprintf(write_in_log, "\n");

     fclose(write_in_log);

}


DIRECTOR move_serial_director(int serial, DIRECTOR origin){
  DIRECTOR new;
  new = origin;

  while((serial != new -> serial_number) && (new != NULL))
  {
    new = new->director_next;
  }

  return new;
}

void update_list_actor(char *option, char *serial, ACTOR actor){

  int i = 0;
  int serial_num = atoi(serial);
  actor = move_serial_actor(serial_num, actor);
  char option_letter = *option;
  char *tmp;
  int update_check = 1;
  FILE *write_in_log;

  write_in_log = fopen("actor_log.txt","a");

  while(i < strlen(option)){

  option_letter = *(option+i);

  tmp = (char *)calloc(1,sizeof(char)*100);

  switch(option_letter){

  case 'n':
  printf("Actor name > ");
  gets(tmp);
  actor->name = (char*)malloc(strlen(tmp)+1);
  strcpy(actor->name, tmp);
  free(tmp);
  update_check *= 2;
  break;

  case 's':
  printf("Actor sex > ");
  scanf("%c", &(actor -> sex));
  update_check *= 3;
  break;

  case 'b':
  printf("Actor birth > ");
  scanf("%s", tmp);
  actor->birth = (char*)malloc(strlen(tmp)+1);
  strcpy(actor->birth, tmp);
  free(tmp);
  update_check *= 5;
  break;

  case 'm':
  printf("Actor movie > ");
  gets(tmp);
  actor->movie->title = (char*)malloc(strlen(actor->movie->title)+strlen(tmp)+3);
  // strcat(actor->movie->title, ", ")
  // strcat(actor->movie->title, tmp);
  free(tmp);
  update_check *= 7;
  break;

  default:
  break;
  }

  i++;
  }

    fprintf(write_in_log,"update:%d",serial_num);

   if((update_check % 2 != 0)){
     fprintf(write_in_log, ":=");
     printf("same name\n");
     update_check -= 1000;
   }else{
     printf("different name\n");
     fprintf(write_in_log,":%s", actor->name);
   }

   if((update_check % 3 != 0)){
     fprintf(write_in_log, ":=");
     printf("same sex\n");
     update_check -= 100;
   }else{
    printf("different sex\n");
    fprintf(write_in_log,":%d", actor->sex);
  }

   if((update_check % 5 != 0)){
     fprintf(write_in_log, ":=");
     printf("same birth\n");
   }else{
     printf("different birth\n" );
     fprintf(write_in_log,":%s", actor->birth);
   }
 // 수정 필요
   // if((update_check % 7 == 0)){
   //     fprintf(write_in_log, ":=");
   // }else
   //     fprintf(write_in_log,":%s", actor->movie->title);
     fprintf(write_in_log, "\n");

     fclose(write_in_log);

}


ACTOR move_serial_actor(int serial, ACTOR origin){
  ACTOR new;
  new = origin;

  while((serial != new -> serial_number) && (new != NULL))
  {
    new = new->actor_next;
  }

  return new;
}

void update_list_movie(char *option, char *serial, struct movie *movies){

  int i = 0;
  int serial_num = atoi(serial);
  *movies = move_serial_movie(serial_num, movies);
  char option_letter = *option;
  char *tmp;
  int update_check = 1;
  FILE *write_in_log;

  write_in_log = fopen("movie_log.txt","a");

  while(i < strlen(option)){

  option_letter = *(option+i);

  tmp = (char *)calloc(1,sizeof(char)*100);

  switch(option_letter){

  case 't':
  printf("Movie title > ");
  gets(tmp);
  movies -> title = (char*)malloc(strlen(tmp)+1);
  strcpy(movies -> title, tmp);
  free(tmp);
  update_check *= 2;
  break;

  case 'g':
  printf("Movie genre > ");
  gets(tmp);
  movies -> genre = (char*)malloc(strlen(tmp)+1);
  strcpy(movies -> genre, tmp);
  free(tmp);
  update_check *= 3;
  break;

  case 'd':
  printf("Movie director > ");
  scanf("%s", tmp);
  movies -> director.name = (char*)malloc(strlen(tmp)+1);
  strcpy(movies -> director.name, tmp);
  free(tmp);
  update_check *= 5;
  break;

  case 'y':
  printf("Movie year > ");
  scanf("%d", &(movies -> year));
  update_check *= 7;
  break;

  case 'r':
  printf("Movie time > ");
  scanf("%d", &(movies -> time));
  update_check *= 11;
  break;

  case 'a':
  printf("Movie actor > ");
  gets(tmp);
  movies -> actor -> actor_name = (char *)malloc(strlen(movies->actor->actor_name) + strlen(tmp)+3);
  strcat(movies -> actor -> actor_name, tmp);
  free(tmp);
  update_check *= 13;
  break;

  default:
  break;
  }

  i++;
  }

    fprintf(write_in_log,"update:%d",serial_num);

   if((update_check % 2 != 0)){
     fprintf(write_in_log, ":=");
     printf("same title\n");
   }else{
     printf("different title\n");
     fprintf(write_in_log,":%s", movies->title);
   }

   if((update_check % 3 != 0)){
     fprintf(write_in_log, ":=");
     printf("same genre\n");
     update_check -= 100;
   }else{
    printf("different genre\n");
    fprintf(write_in_log,":%d", movies->genre);
  }

   if((update_check % 5 != 0)){
     fprintf(write_in_log, ":=");
     printf("same director\n");
   }else{
     printf("different director\n" );
     fprintf(write_in_log,":%s", movies-> director.name);
   }

   if((update_check % 7 != 0)){
     fprintf(write_in_log, ":=");
     printf("same year\n");
   }else{
     printf("different year\n" );
     fprintf(write_in_log,":%d", movies-> year);
   }

   if((update_check % 11 != 0)){
     fprintf(write_in_log, ":=");
     printf("same runtime\n");
   }else{
     printf("different runtime\n" );
     fprintf(write_in_log,":%d", movies-> time);
   }

   if((update_check % 13 != 0)){
     fprintf(write_in_log, ":=");
     printf("same actor\n");
   }else{
     printf("different actor\n" );
     fprintf(write_in_log,":%s", movies-> actor -> actor_name);
   }

     fprintf(write_in_log, "\n");

     fclose(write_in_log);

}


struct movie move_serial_movie(int serial, struct movie *origin){
  struct movie *new;
  new = origin;

  while((serial != new -> Serial_number) && (new != NULL))
  {
    new = new->movie_next;
  }

  return *new;
}
