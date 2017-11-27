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

  while(1){
    printf("(movie) ");
    gets(whats_up_commander);
    split = strtok(whats_up_commander, " ");

    if(!strcmp(split,"update")){
      command_what = strtok(NULL, " ");
      option = strtok(NULL, " ");
      split = strtok(NULL, " ");

      if (!strcmp(command_what, "d")){
        update_list_director(option, split, public_director);
      }else if(!strcmp(command_what, "a")){
        printf("update_list_actor will be starts\n");
      }else if(!strcmp(command_what,"m")){
        printf("update_list_movie will be starts\n");
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
  }
}

void update_list_director(char *option, char *serial, DIRECTOR director){

  int i = 0;
  int serial_num = atoi(serial);
  director = move_serial(serial_num, director);
  char option_letter = *option;
  char *tmp;
  DIRECTOR before_update = director;
  FILE *write_in_log;

  write_in_log = fopen("director_log.txt","a");

  fprintf(write_in_log,"update:%d",serial_num);

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

  // write_in_log code, before_update랑 같으면 =, 아니면 %s 출력
  if(strcmp(director->name, before_update->name)){
    fprintf(write_in_log, ":=");
  }else
    fprintf(write_in_log,":%s", director->name);

  if((director->sex) == (before_update->sex)){
      fprintf(write_in_log, ":=");
  }else
      fprintf(write_in_log,":%s", director->sex);

  if(strcmp(director->birth, before_update->birth)){
          fprintf(write_in_log, ":=");
  }else
          fprintf(write_in_log,":%s", director->birth);

// 수정 필요
  if(strcmp(director->movie->title, before_update->movie->title)){
          fprintf(write_in_log, ":=");
  }else
          fprintf(write_in_log,":%s", director->movie->title);

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

//option - add
void option_add_movie(struct movie *movie){
  struct movie *inMovie;
  struct movie *lastMovie;
   FILE *mv_log_write, FILE, *mv_log_read;
   if((mv_log_read = fopen("movie_log.txt", "r")) == NULL){
     printf("File Open Error");
     exit(1);
   }
   if((mv_log_write = fopen("movie_log.txt", "a")) == NULL){
     printf("File Open Error");
     exit(1);
   }
  int text_size = 0;
  inMovie = malloc(sizeof(struct movie));
  char* tmp_char = (char*)malloc(sizeof(char)*200);

  printf("title > ");
  gets(tmp_char);
  inMovie -> title = (char*)malloc(sizeof(char)*strlen(tmp_char+5));
  strcpy(inMovie -> title , colon_change(tmp_char));

  printf("genre > ");
  gets(tmp_char);
  inMovie -> genre = (char*)malloc(sizeof(char)*strlen(tmp_char+5));
  // inMovie -> genre = colon_change(tmp_char);
  strcpy(inMovie -> genre , colon_change(tmp_char));

  printf("director > ");
  gets(tmp_char);
  inMovie -> director.name = (char*)malloc(sizeof(char)*strlen(tmp_char)+5);
  // inMovie -> director.name = colon_change(tmp_char);
  strcpy(inMovie -> director.name , colon_change(tmp_char));

  printf("year > ");
  gets(tmp_char);
  inMovie -> year = atoi(tmp_char);

  printf("time > ");
  gets(tmp_char);
  inMovie -> time = atoi(tmp_char);

  printf("actor > ");
  gets(tmp_char);
  fseek(mv_log_read,0,SEEK_END);
  int file_size = ftell(mv_log_read);
  printf("\n==\n%d\n=\n", file_size);

  inMovie -> movie_next = NULL;
  lastMovie = search_last_movie(movie);
  lastMovie -> movie_next = inMovie;
  inMovie -> Serial_number = (lastMovie -> Serial_number) +1 ;
  inMovie -> actor = create_actor_struct(tmp_char);
  if(file_size){
    fprintf(mv_log_write, "\nadd:%d:%s:%s:%s:%d:%d:", inMovie -> Serial_number, inMovie -> title, inMovie -> genre, inMovie -> director.name, inMovie -> year, inMovie -> time);
    struct linked_list_actor *tmp_print_actor = inMovie -> actor;
    while(tmp_print_actor != NULL){
      if(tmp_print_actor -> actor_next == NULL){
        fprintf(mv_log_write, "%s", tmp_print_actor -> actor_name);
      }else{
        fprintf(mv_log_write, "%s, ", tmp_print_actor -> actor_name);
      }
      tmp_print_actor = tmp_print_actor -> actor_next;
    }
  }else{
    fprintf(mv_log_write, "add:%d:%s:%s:%s:%d:%d:", inMovie -> Serial_number, inMovie -> title, inMovie -> genre, inMovie -> director.name, inMovie -> year, inMovie -> time);
    struct linked_list_actor *tmp_print_actor = inMovie -> actor;
    while(tmp_print_actor != NULL){
      if(tmp_print_actor -> actor_next == NULL){
        fprintf(mv_log_write, "%s", tmp_print_actor -> actor_name);
      }else{
        fprintf(mv_log_write, "%s, ", tmp_print_actor -> actor_name);
      }
      tmp_print_actor = tmp_print_actor -> actor_next;
    }
  }
  free(tmp_char);
  fclose(mv_log_read);
  fclose(mv_log_write);
}

void option_add_director(DIRECTOR public_first_director){
  DIRECTOR director;
  DIRECTOR LastDirector;
   FILE *director_log_write, FILE, *director_log_read;
   if((director_log_read = fopen("director_log.txt", "r")) == NULL){
     printf("File Open Error");
     exit(1);
   }
   if((director_log_write = fopen("director_log.txt", "a")) == NULL){
     printf("File Open Error");
     exit(1);
   }
  int text_size = 0;
  director = malloc(sizeof(struct director));
  char* tmp_char = (char*)malloc(sizeof(char)*200);
  printf("\n==\n%d\n=\n", public_first_director -> serial_number);
  printf("name > ");
  gets(tmp_char);
  director -> name = (char*)malloc(sizeof(char)*strlen(tmp_char+5));
  strcpy(director -> name , colon_change(tmp_char));

  printf("sex > ");
  gets(tmp_char);
  // director -> sex = (char*)malloc(sizeof(char)*strlen(tmp_char+5));
  // inMovie -> genre = colon_change(tmp_char);
  // strcpy(inMovie -> genre , colon_change(tmp_char));
  director -> sex = tmp_char[0];

  printf("birth > ");
  gets(tmp_char);
  director -> birth = (char*)malloc(sizeof(char)*strlen(tmp_char)+5);
  // inMovie -> director.name = colon_change(tmp_char);
  strcpy(director -> birth , colon_change(tmp_char));

  printf("best movie > ");
  gets(tmp_char);
  fseek(director_log_read,0,SEEK_END);
  int file_size = ftell(director_log_read);
  printf("\n==\n%d\n=\n", file_size);

  director -> director_next = NULL;
  LastDirector = serach_last_director(public_first_director);
  printf("\n==\n%d\n=\n", LastDirector -> serial_number);
  LastDirector -> director_next = director;
  director -> serial_number = (LastDirector -> serial_number) +1 ;
printf("\n==\n%s\n=\n", tmp_char);
  char* split = strtok(tmp_char, ",");
printf("\n==\n%s\n=\n", split);
  MOVIE movie;
  movie = list_movie_director(split);
  director -> movie = movie;
  printf("\n==\n%s\n=\n", movie -> title);
  while((split = strtok(NULL, ",")) != NULL){
    if(*split+0 == ' '){
      strcpy(split, split+1);
    }
    MOVIE movie_tmp = list_movie_director(split);
    movie = put_list_movie_director(movie, movie_tmp);
  }
  if(file_size){
    fprintf(director_log_write, "\nadd:%d:%s:%c:%s:", director -> serial_number, director -> name, director -> sex, director -> birth);
    MOVIE tmp_print_movie = director -> movie;
    while(tmp_print_movie != NULL){
      if(tmp_print_movie -> movie_next == NULL){
        fprintf(director_log_write, "%s", tmp_print_movie -> title);
      }else{
        fprintf(director_log_write, "%s, ", tmp_print_movie -> title);
      }
      tmp_print_movie = tmp_print_movie -> movie_next;
    }
  }else{
    fprintf(director_log_write, "add:%d:%s:%c:%s:", director -> serial_number, director -> name, director -> sex, director -> birth);
    MOVIE tmp_print_movie = director -> movie;
    while(tmp_print_movie != NULL){
      if(tmp_print_movie -> movie_next == NULL){
        fprintf(director_log_write, "%s", tmp_print_movie -> title);
      }else{
        fprintf(director_log_write, "%s, ", tmp_print_movie -> title);
      }
      tmp_print_movie = tmp_print_movie -> movie_next;
    }
  }
  free(tmp_char);
  fclose(director_log_read);
  fclose(director_log_write);
}

DIRECTOR serach_last_director(DIRECTOR public_first_director){
  DIRECTOR director = public_first_director;
  printf("\n==\n%d\n=\n", director -> serial_number);
  while((director -> director_next) != NULL){
    director = director -> director_next;
  }
  printf("\n==\n%d\n=\n", director -> serial_number);
  return director;
}
void fprint_list_movie_director_actor(struct movie *movie, DIRECTOR director){
  FILE* mv_list, *director_list;
  if((mv_list = fopen("movie_list.txt", "w")) == NULL){
    printf("File Open Error");
    exit(1);
  }
  if((director_list = fopen("director_list.txt", "w")) == NULL){
    printf("File Open Error");
    exit(1);
  }
  //movie_ file print to movie_list.txt
  while(movie != NULL){
    fprintf(mv_list, "%d:%s:%s:%s:%d:%d:", movie -> Serial_number, movie -> title, movie -> genre, movie -> director.name, movie -> year, movie -> time);
    struct linked_list_actor *actor = movie -> actor;
    while(actor != NULL){
      if(actor -> actor_next == NULL){
        fprintf(mv_list,"%s", actor -> actor_name);
        break;
      }else{
        fprintf(mv_list,"%s, ", actor -> actor_name);
      }
      actor = actor -> actor_next;
    }
    if(movie -> movie_next == NULL){
      break;
    }else{
      fprintf(mv_list,"\n");
    }
    movie = movie -> movie_next;
  }

  //director file print to director_list.txt
  while(director != NULL){
    fprintf(director_list, "%d:%s:%c:%s:", director -> serial_number, director -> name, director -> sex, director -> birth);
    MOVIE movie_in_director = director -> movie;
    while(movie_in_director != NULL){
      if(movie_in_director -> movie_next == NULL){
        fprintf(director_list,"%s", movie_in_director -> title);
        break;
      }else{
        fprintf(director_list,"%s, ", movie_in_director -> title);
      }
      movie_in_director = movie_in_director -> movie_next;
    }
    if(director -> director_next == NULL){
      break;
    }else{
      fprintf(director_list,"\n");
    }
    director = director -> director_next;
  }


  fclose(mv_list);
}
