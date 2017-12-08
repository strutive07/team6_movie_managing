#include "option.h"
#include <time.h>
void whats_up_commander(){

  printf(">> Welcome to My Movie <<\n");
  printf("File Loading......\n");
  printf("You can use add, update, delete, search, sort, save, end commands.\n");

  char *whats_up_commander = (char*)malloc(sizeof(char)*100);
  char *split = (char*)malloc(sizeof(char)*100);
  char *command_what = (char*)malloc(sizeof(char));
  char *option = (char*)malloc(sizeof(char)*100);
  char *option2 = (char*)malloc(sizeof(char)*100);
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
      if(atoi(option) == 0){ // 옵션 없이 option값이 시리얼 넘버를 받으면 atoi값은 0이 아닐테니까.
      split = strtok(NULL, " ");
      }else{
      strcpy(split, option);
      strcpy(option, "ALL COMMANDS");
    }

      if (!strcmp(command_what, "d")){
        update_list_director(option, split, director);
      }else if(!strcmp(command_what, "a")){
        update_list_actor(option, split, actor);
      }else if(!strcmp(command_what,"m")){
        update_list_movie(option, split, movies);
      }else{
        continue;
      }


    } // update
      if(!strcmp(split, "print")){
        printf("Print_movie will be run\n");

        command_what = strtok(NULL, " ");
        split = strtok(NULL, " ");

        if (!strcmp(command_what, "d")){
          print_list_director(director, split);
        }else{
            continue;
        // }else if(!strcmp(command_what, "a")){
        //   print_list_actor(actor);
        // }else if(!strcmp(command_what,"m")){
        //   print_list_movie(movies);
        }
      }
      if(!strcmp(split, "end")){
        printf("Do you want Save?\n");
        printf("[ Y : save data, N : don't Save ] : ");
        gets(split);
        if(!strcmp(split, "y") || !strcmp(split, "Y")){
          strcpy(option, "ALL COMMANDS");
          save_list_movie(option, movies);
          strcpy(option, "ALL COMMANDS");
          save_list_director(option, director);
          strcpy(option, "ALL COMMANDS");
          save_list_actor(option, actor);
          exit(1);
        }else if(!strcmp(split, "n") || !strcmp(split, "N")){
          exit(1);
        }else{
          printf("@@ Wrong Command\n");
        }
      }
      if(!strcmp(split, "save")){
        // 옵션이 없는 경우 에러

         // save m option -f filename
        command_what = strtok(NULL, " "); // mda
        printf("command\n");
        if((option = strtok(NULL, " ")) != NULL){ // option이든 filename이든 있을 때
          printf("\n\noption is %s \n\n", option);
          if(!strcmp(option, "-f")){ // tgdyra, nsbm이 아니고 -f면 옵션이 없다는 뜻
          strcpy(option, "ALL COMMANDS");
        }else if((split = strtok(NULL, " ")) != NULL){ // split이 잘랐을때 NULL이 아니면 -f를 저장
          if(strcmp(split, "-f")){ // -f가 아닐 경우 == filename를 바로 입력했을때
            printf("Where is Filename? \n"); // -f 없이 filename을 입력하면 실행을 안하도록 하고
            continue;
          }
          option2 = strtok(NULL, " "); // -f filename
          printf("\n\nfilename is %s\n\n",option2);
          }
        }else{ // save m 처럼 전부 디폴트일 때
        option = (char *)malloc(sizeof(char)*13); // token 과정에서 NULL처리가 되서 할당안하면 안되네
        strcpy(option, "ALL COMMANDS");
        option2 = NULL; //filename default
      }

        if(!strcmp(command_what, "m"))
        {
          save_list_movie(option, movies);
        }
        else if(!strcmp(command_what, "d"))
        {
          save_list_director(option, director);
        }
        else if(!strcmp(command_what, "a"))
        {
          save_list_actor(option, actor);
        }else
        {
          continue;
        }

      }
      if(!strcmp(split,"add")){
        command_what = strtok(NULL, " ");

        if(!strcmp(command_what, "m"))
        {
          option_add_movie(movies);
        }
        else if(!strcmp(command_what, "d"))
        {
          option_add_director(director);
        }
        else if(!strcmp(command_what, "a"))
        {
           option_add_actor(actor);
        }else
        {
          printf("only add m/d/a can run\n");
          continue;
        }
      }
      if(!strcmp(split,"search")){

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
  }else if((a == 'n') || (a == 'N')){
    return;
  }else{
    printf("\n\n@@ Wrong Command\n\n");
    you_wanna_end(2);
  }
}

void update_list_director(char *option, char *serial, DIRECTOR director){

  int i = 0;
  int serial_num = atoi(serial);

  if(serial_num != 1)
  director = move_serial_director(serial_num, director);

  if(director == NULL){
    printf("No Such Record\n");
    return;
  }

  char option_letter = *option;
  char *tmp;
  char *tmp2 = (char*)malloc(sizeof(char)*100);

  int update_check = 1;
  int overlap = 0;

  DIRECTOR movie_copy_tmp = director;
  FILE *write_in_log;


  if(!strcmp(option, "ALL COMMANDS")){
    strcpy(option, "nsbm");
  }

  write_in_log = fopen("director_log.txt","a");

  while(i < strlen(option)){

  option_letter = *(option+i);

  tmp = (char *)calloc(1,sizeof(char)*100);

  switch(option_letter){

  case 'n':
  printf("Director name > ");
  gets(tmp);
  if (!strcmp(tmp, director -> name)){
    if(director_overlap(director)){
      return;
    }
  }
  director->name = (char*)malloc(strlen(tmp)+1);
  strcpy(director->name, tmp);
  free(tmp);
  update_check *= 2;
  break;

  case 's':
  printf("Director sex > ");
  scanf("%c", &(director -> sex));
  update_check *= 3;
  break;

  case 'b':
  printf("Director birth > ");
  gets(tmp);
  director->birth = (char*)malloc(strlen(tmp)+1);
  strcpy(director->birth, tmp);
  free(tmp);
  update_check *= 5;
  break;

  case 'm':
  printf("Director movie > ");
  gets(tmp);
  if(tmp2 = strtok(tmp, ",")){
  movie_copy_tmp->movie->title = (char*)malloc(strlen(tmp2)+1);
  strcpy(movie_copy_tmp -> movie -> title, tmp2);
  printf("aaaaaaaaa\n");

  while((tmp2 = strtok(NULL,",")) != NULL){
    printf("ddddddddddddd\n");
    movie_copy_tmp -> movie = movie_copy_tmp -> movie -> movie_next;
    printf("eeeeeeeeeeee\n");
    movie_copy_tmp -> movie -> title = (char*)malloc(strlen(tmp2)+1); // next 이후 title 접근 자체가 문제?
    printf("fffffffffffff\n");
    strcpy(movie_copy_tmp -> movie -> title, tmp2);
    printf("gggggggggggg\n");
    }
  }
  link_director_to_movie();
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
   }else{
     fprintf(write_in_log,":%s", director->name);
   }

   if((update_check % 3 != 0)){
     fprintf(write_in_log, ":=");
   }else{
    fprintf(write_in_log,":%c", director->sex);
  }

   if((update_check % 5 != 0)){
     fprintf(write_in_log, ":=");
   }else{
     fprintf(write_in_log,":%s", director->birth);
   }
 // 수정 필요
      if((update_check % 7 != 0)){
        fprintf(write_in_log, ":=");
     }else{
       fprintf(write_in_log,":");
       while(director -> movie != NULL){
       fprintf(write_in_log,"%s", director->movie->title);
       director -> movie = director -> movie -> movie_next;
       if(director -> movie != NULL)
       fprintf(write_in_log,",");
     }
   }
     fprintf(write_in_log, "\n");

     fclose(write_in_log);

}


DIRECTOR move_serial_director(int serial, DIRECTOR origin){
  DIRECTOR new;
  new = origin;

  while((serial != new -> serial_number) && (new != NULL))
  {
    new = new->director_next;
    if(new == NULL){
      return NULL;
    }
  }

  return new;
}

void update_list_actor(char *option, char *serial, ACTOR actor){

  int i = 0;
  int serial_num = atoi(serial);

  if(serial_num != 1)
  actor = move_serial_actor(serial_num, actor);

  if(actor == NULL){
    printf("No Such Record\n");
    return;
  }

  char option_letter = *option;
  char *tmp;
  int update_check = 1;
  FILE *write_in_log;

  if(!strcmp(option, "ALL COMMANDS")){
    strcpy(option, "nsb");
  }

  write_in_log = fopen("actor_log.txt","a");

  while(i < strlen(option)){

  option_letter = *(option+i);

  tmp = (char *)calloc(1,sizeof(char)*100);

  switch(option_letter){

  case 'n':
  printf("Actor name > ");
  gets(tmp);
  if (!strcmp(tmp, actor -> name)){
    if(actor_overlap(actor)){
      return;
    }
  }
  actor->name = (char*)malloc(strlen(tmp)+1);
  strcpy(actor->name, tmp);
  free(tmp);
  update_check *= 2;
  break;

  case 's':
  printf("Actor sex > ");
  scanf("%d", &(actor -> sex));
  update_check *= 3;
  break;

  case 'b':
  printf("Actor birth > ");
  gets(tmp);
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
   }else{
     fprintf(write_in_log,":%s", actor->name);
   }

   if((update_check % 3 != 0)){
     fprintf(write_in_log, ":=");
   }else{
     if(actor->sex)
    fprintf(write_in_log,":M", actor->sex);
     else
    fprintf(write_in_log,":W", actor->sex);

  }

   if((update_check % 5 != 0)){
     fprintf(write_in_log, ":=");
   }else{
     fprintf(write_in_log,":%s", actor->birth);
   }
 // 수정 필요
   if((update_check % 7 != 0)){
     fprintf(write_in_log, ":=");
  }else{
    fprintf(write_in_log,":");
    while(actor -> movie != NULL){
    fprintf(write_in_log,"%s", actor->movie->title);
    actor -> movie = actor -> movie -> movie_next;
    if(actor->movie != NULL)
    fprintf(write_in_log,",");
    }
  }
     fprintf(write_in_log, "\n");

     fclose(write_in_log);

}


ACTOR move_serial_actor(int serial, ACTOR origin){
  ACTOR new;
  new = origin;

  while((serial != new -> serial_number) && (new != NULL))
  {
    new = new->actor_next;
    if(new == NULL){
      return NULL;
    }
  }

  return new;
}

void update_list_movie(char *option, char *serial, struct movie *movies){

  int i = 0;
  int serial_num = atoi(serial);

  if(serial_num != 1)
  movies = move_serial_movie(serial_num, movies);

  if(movies == NULL){
    printf("No Such Record\n");
    return;
  }

  char option_letter = *option;
  char *tmp;
  int update_check = 1;
  FILE *write_in_log;

  if(!strcmp(option, "ALL COMMANDS")){
    strcpy(option, "tgdyra");
  }

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
  gets(tmp);
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
   }else{
     fprintf(write_in_log,":%s", movies->title);
   }

   if((update_check % 3 != 0)){
     fprintf(write_in_log, ":=");
     update_check -= 100;
   }else{
    fprintf(write_in_log,":%d", movies->genre);
  }

   if((update_check % 5 != 0)){
     fprintf(write_in_log, ":=");
   }else{
     fprintf(write_in_log,":%s", movies-> director.name);
   }

   if((update_check % 7 != 0)){
     fprintf(write_in_log, ":=");
   }else{
     fprintf(write_in_log,":%d", movies-> year);
   }

   if((update_check % 11 != 0)){
     fprintf(write_in_log, ":=");
   }else{
     fprintf(write_in_log,":%d", movies-> time);
   }

   if((update_check % 13 != 0)){
     fprintf(write_in_log, ":=");
   }else{
     fprintf(write_in_log,":%s", movies-> actor -> actor_name);
   }

     fprintf(write_in_log, "\n");

     fclose(write_in_log);

}


struct movie* move_serial_movie(int serial, struct movie *origin){
  struct movie *new;
  new = origin;

  while((serial != new -> Serial_number) && (new != NULL))
  {
    new = new->movie_next;

    if(new == NULL){
      return NULL;
    }


  return new;
}
}
int director_overlap(DIRECTOR director){ // 다른 번호일때 찾는거 해야됨
  char* Y_N = (char *)malloc(sizeof(char));
  printf("You have the same record\n");
  printf("Director name > %s\n", director -> name);
  printf("Director sex > %c\n", director -> sex);
  printf("Director birth > %s\n", director -> birth);
  while(director -> movie != NULL){
  printf("Director movie > %s\n", director -> movie -> title);
  director -> movie = director -> movie -> movie_next;
  }
  printf("Do you want to change the record? (Y/N) : ");
  gets(Y_N);
  if(!strcmp(Y_N, "Y") || !strcmp(Y_N, "y")){
    return 0;
  }else{
    return 1;
  }
}

int actor_overlap(ACTOR actor){
  char* Y_N = (char *)malloc(sizeof(char));
  printf("You have the same record\n");
  printf("Actor name > %s\n", actor -> name);
  printf("Actor sex > ");
  if(actor -> sex){
    printf("M\n");
  }else{
    printf("W\n");
  }
  printf("Actor birth > %s\n", actor -> birth);
  while(actor -> movie != NULL){
  printf("Actor movie > %s\n", actor -> movie -> title);
  actor -> movie = actor -> movie -> movie_next;
  }
  printf("Do you want to change the record? (Y/N) : ");
  gets(Y_N);
  if(!strcmp(Y_N, "Y") || !strcmp(Y_N, "y")){
    return 0;
  }else{
    return 1;
  }
}

void print_list_director(DIRECTOR director, char *serial){

  int serial_num = atoi(serial);

  if(serial_num != 1)
  director = move_serial_director(serial_num, director);

    printf("%d : ", director -> serial_number);
    printf("%s ", director -> name);
    printf("%c ", director -> sex);
    printf("%s \n", director -> birth);
    while(director -> movie != NULL){
      if (director -> movie -> movie_link == NULL){
        printf("No linked Data\n");
        break;
      }else{
      printf("%s : %d, %d\n", director -> movie -> title, director -> movie -> movie_link -> year, director -> movie -> movie_link -> time); // 제목, 제작년도, 상영시간
      director -> movie = director -> movie -> movie_next;
      }
    }
}
//option - addvoid option_add_movie(struct movie *movie){
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
  struct movie *tmp_head_movie = movie;
  while(tmp_head_movie != NULL){
    if(!strcmp(tmp_head_movie -> title, tmp_char)){
      printf("You have the same record.\n");
      return;
    }else{
      tmp_head_movie = tmp_head_movie -> movie_next;
    }
  }
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
  fprint_list_movie_director_actor('M', public_first_movie, public_director, public_actor);
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

  printf("name > ");
  gets(tmp_char);
  director -> name = (char*)malloc(sizeof(char)*strlen(tmp_char+5));
  strcpy(director -> name , colon_change(tmp_char));
  DIRECTOR tmp_head_director = public_first_director;
  while(tmp_head_director != NULL){
    if(!strcmp(tmp_head_director -> name, tmp_char)){
      printf("You have the same record.\n");
      return;
    }else{
      tmp_head_director = tmp_head_director -> director_next;
    }
  }

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


  director -> director_next = NULL;
  LastDirector = serach_last_director(public_first_director);

  LastDirector -> director_next = director;
  director -> serial_number = (LastDirector -> serial_number) +1 ;

  char* split = strtok(tmp_char, ",");

  MOVIE movie;
  movie = list_movie_director(split);
  director -> movie = movie;

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
  fprint_list_movie_director_actor('D', public_first_movie, public_director, public_actor);
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
void fprint_list_movie_director_actor(char isMovie_DIrector_Actor, struct movie *movie, DIRECTOR director, ACTOR actor){

  FILE* tmp_mv_list, *tmp_director_list, *tmp_actor_list;
  FILE* mv_list, *director_list, *actor_list;

  if(isMovie_DIrector_Actor == 'M'){
    if((tmp_mv_list = fopen("movie_list.txt", "r")) == NULL){
      if((mv_list = fopen("movie_list.txt", "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
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
      fclose(mv_list);
      fclose(tmp_mv_list);
    }else{
      FILE * create_tmp_mv_list;
      char* time_string = now_time_string();
      char* file_name = (char*)malloc(sizeof(char)*100);
      strcat(file_name, "movie_list.");
      strcat(file_name, time_string);
      if((create_tmp_mv_list = fopen(file_name, "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
      char chch;
      while((chch=fgetc(tmp_mv_list)) != EOF){
        // printf("%c", chch);
        fputc(chch, create_tmp_mv_list);
      }
      fclose(create_tmp_mv_list);

      if((mv_list = fopen("movie_list.txt", "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
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
      fclose(mv_list);
      fclose(tmp_mv_list);
    }

  }else if(isMovie_DIrector_Actor == 'D'){
    if((tmp_director_list = fopen("director_list.txt", "r")) == NULL){
      if((director_list = fopen("director_list.txt", "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
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
          fprintf(director_list," \n");
        }
        director = director -> director_next;
      }
      fclose(tmp_director_list);
        fclose(director_list);
    }else{
      FILE * create_tmp_director_list;
      char* time_string = now_time_string();
      char* file_name = (char*)malloc(sizeof(char)*100);
      strcat(file_name, "director_list.");
      strcat(file_name, time_string);
      if((create_tmp_director_list = fopen(file_name, "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
      char chch;
      while((chch=fgetc(tmp_director_list)) != EOF){
        // printf("%c", chch);
        fputc(chch, create_tmp_director_list);
      }
      fclose(create_tmp_director_list);

      if((director_list = fopen("director_list.txt", "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
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
          fprintf(director_list," \n");
        }
        director = director -> director_next;
      }
      fclose(director_list);
      fclose(tmp_director_list);
    }

  }else if(isMovie_DIrector_Actor == 'A'){
    if((tmp_actor_list = fopen("actor_list.txt", "r")) == NULL){
      if((actor_list = fopen("actor_list.txt", "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
      while(actor != NULL){
        if(actor -> sex){
          fprintf(actor_list, "%d:%s:M:%s:", actor -> serial_number, actor -> name, actor -> birth);
        }else{
          fprintf(actor_list, "%d:%s:F:%s:", actor -> serial_number, actor -> name, actor -> birth);
        }

        MOVIE movie_in_actor = actor -> movie;
        while(movie_in_actor != NULL){
          if(movie_in_actor -> movie_next == NULL){
            fprintf(actor_list,"%s", movie_in_actor -> title);
            break;
          }else{
            fprintf(actor_list,"%s, ", movie_in_actor -> title);
          }
          movie_in_actor = movie_in_actor -> movie_next;
        }
        if(actor -> actor_next == NULL){
          break;
        }else{
          fprintf(actor_list,"\n");
        }
        actor = actor -> actor_next;
      }
      fclose(actor_list);
      fclose(tmp_actor_list);
    }else{
      FILE * create_tmp_actor_list;
      char* time_string = now_time_string();
      char* file_name = (char*)malloc(sizeof(char)*100);
      strcat(file_name, "actor_list.");
      strcat(file_name, time_string);
      if((create_tmp_actor_list = fopen(file_name, "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
      char chch;
      while((chch=fgetc(tmp_actor_list)) != EOF){
        printf("%c", chch);
        fputc(chch, create_tmp_actor_list);
      }
      fclose(create_tmp_actor_list);
      if((actor_list = fopen("actor_list.txt", "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
      while(actor != NULL){
        if(actor -> sex){
          fprintf(actor_list, "%d:%s:M:%s:", actor -> serial_number, actor -> name, actor -> birth);
        }else{
          fprintf(actor_list, "%d:%s:F:%s:", actor -> serial_number, actor -> name, actor -> birth);
        }

        MOVIE movie_in_actor = actor -> movie;
        while(movie_in_actor != NULL){
          if(movie_in_actor -> movie_next == NULL){
            fprintf(actor_list,"%s", movie_in_actor -> title);
            break;
          }else{
            fprintf(actor_list,"%s, ", movie_in_actor -> title);
          }
          movie_in_actor = movie_in_actor -> movie_next;
        }
        if(actor -> actor_next == NULL){
          break;
        }else{
          fprintf(actor_list,"\n");
        }
        actor = actor -> actor_next;
      }
      fclose(actor_list);
      fclose(tmp_actor_list);

    }
  }


//actor add
void option_add_actor(ACTOR public_actor){
  ACTOR actor;
  ACTOR LastActor;
   FILE *actor_log_write, FILE, *actor_log_read;
   if((actor_log_read = fopen("actor_log.txt", "r")) == NULL){
     printf("File Open Error");
     exit(1);
   }
   if((actor_log_write = fopen("actor_log.txt", "a")) == NULL){
     printf("File Open Error");
     exit(1);
   }
  int text_size = 0;
  actor = malloc(sizeof(struct actor));
  char* tmp_char = (char*)malloc(sizeof(char)*200);

  printf("name > ");
  gets(tmp_char);
  actor -> name = (char*)malloc(sizeof(char)*strlen(tmp_char+5));
  strcpy(actor -> name , colon_change(tmp_char));

  ACTOR tmp_head_actor = public_actor;
  while(tmp_head_actor != NULL){
    if(!strcmp(tmp_head_actor -> name, tmp_char)){
      printf("You have the same record.\n");
      return;
    }else{
      tmp_head_actor = tmp_head_actor -> actor_next;
    }
  }

  printf("sex > ");
  gets(tmp_char);
  // director -> sex = (char*)malloc(sizeof(char)*strlen(tmp_char+5));
  // inMovie -> genre = colon_change(tmp_char);
  // strcpy(inMovie -> genre , colon_change(tmp_char));

  if(tmp_char[0] =='M'){
    actor -> sex = true;
  }else{
    actor -> sex = false;
  }

  printf("birth > ");
  gets(tmp_char);
  actor -> birth = (char*)malloc(sizeof(char)*strlen(tmp_char)+5);
  // inMovie -> director.name = colon_change(tmp_char);
  strcpy(actor -> birth , colon_change(tmp_char));

  printf("best movie > ");
  gets(tmp_char);
  fseek(actor_log_read,0,SEEK_END);
  int file_size = ftell(actor_log_read);


  actor -> actor_next = NULL;
  LastActor = serach_last_actor(public_actor);

  LastActor -> actor_next = actor;
  actor -> serial_number = (LastActor -> serial_number) +1 ;

  char* split = strtok(tmp_char, ",");

  MOVIE movie;
  movie = list_movie_director(split);
  actor -> movie = movie;

  while((split = strtok(NULL, ",")) != NULL){
    if(*split+0 == ' '){
      strcpy(split, split+1);
    }
    MOVIE movie_tmp = list_movie_director(split);
    movie = put_list_movie_director(movie, movie_tmp);
  }
  if(file_size){
    if(actor -> sex){
      fprintf(actor_log_write, "\nadd:%d:%s:M:%s:", actor -> serial_number, actor -> name, actor -> birth);
    }else{
      fprintf(actor_log_write, "\nadd:%d:%s:F:%s:", actor -> serial_number, actor -> name, actor -> birth);
    }

    MOVIE tmp_print_movie = actor -> movie;
    while(tmp_print_movie != NULL){
      if(tmp_print_movie -> movie_next == NULL){
        fprintf(actor_log_write, "%s", tmp_print_movie -> title);
      }else{
        fprintf(actor_log_write, "%s, ", tmp_print_movie -> title);
      }
      tmp_print_movie = tmp_print_movie -> movie_next;
    }
  }else{
    fprintf(actor_log_write, "add:%d:%s:%c:%s:", actor -> serial_number, actor -> name, actor -> sex, actor -> birth);
    MOVIE tmp_print_movie = actor -> movie;
    while(tmp_print_movie != NULL){
      if(tmp_print_movie -> movie_next == NULL){
        fprintf(actor_log_write, "%s", tmp_print_movie -> title);
      }else{
        fprintf(actor_log_write, "%s, ", tmp_print_movie -> title);
      }
      tmp_print_movie = tmp_print_movie -> movie_next;
    }
  }
  free(tmp_char);
  fclose(actor_log_read);
  fclose(actor_log_write);
  fprint_list_movie_director_actor('A', public_first_movie, public_director, public_actor);
}
ACTOR serach_last_actor(ACTOR public_actor){
  ACTOR actor = public_actor;
  while((actor -> actor_next) != NULL){
    actor = actor -> actor_next;
  }
  printf("%d\n", actor -> serial_number);
  return actor;
}

int option_search_meta_search(char* string_orign, char* string_search){
  int string_search_length = strlen(string_search);
  int string_origin_length = strlen(string_orign);

  if(*(string_search+0) == '*'){
    if(*(string_search+string_search_length-1) == '*'){
      int tmp_string_length = string_search_length - 1;
      int last_flag = 0;
      int flag = 0;
      for(int i=1; i<tmp_string_length; i++){
        for(int j=0; j<string_origin_length; j++){
          if(*(string_orign+j) == *(string_search+i)){
            // printf("\n==\n%s     :      %s\n==\n", (string_orign+j), (string_search+i));
            int search_last_meta_cnt = tmp_string_length - 2;
            int origin_cnt = 0;
            for(int k=i; k<tmp_string_length-1; k++){
              if(*(string_search+k) == '?'){
                search_last_meta_cnt--;
              }else{

                if(*(string_orign+j+origin_cnt) != *(string_search+k)){
                  flag = 1;
                }else{
                  search_last_meta_cnt--;
                }

              }
              origin_cnt++;
            }
            if(flag == 0){
              if(search_last_meta_cnt == 0){
                printf("right !\norigin : %s, search_data : %s\n", string_orign, string_search);
                last_flag = 1;
                return 1;
                break;
              }

            }
          }
          if(last_flag == 1){
            break;
          }
        }
        if(last_flag == 1){
          break;
        }
      }
      return 0;
    }else{
      // printf("ho?");
      int tmp_string_length = string_search_length;
      int last_flag = 0;
      int flag = 0;
      for(int i=1; i<tmp_string_length; i++){
        for(int j=0; j<string_origin_length; j++){
          if(*(string_orign+j) == *(string_search+i)){
            int search_last_meta_cnt = tmp_string_length - 1;
            int origin_cnt = 0;
            for(int k=i; k<tmp_string_length; k++){
              if(*(string_search+k) == '?'){
                search_last_meta_cnt--;
              }else{

                if(*(string_orign+j+origin_cnt) != *(string_search+k)){
                  flag = 1;
                }else{
                  search_last_meta_cnt--;
                }

              }
              origin_cnt++;
            }
            if(flag == 0){
              int z = 0;
              for(z = 0; z< tmp_string_length; z++){
                if(*(string_search + string_search_length - z) != '?'){
                  if(*(string_orign+ string_origin_length  -z) != *(string_search + string_search_length - z)){
                    break;
                  }
                }
              }
              if(z == tmp_string_length){
                if(search_last_meta_cnt == 0){
                  printf("right !\norigin : %s, search_data : %s\n", string_orign, string_search);
                  last_flag = 1;
                  return 1;
                  break;
                }else{
                  flag = 1;
                }
              }else{
                flag = 1;
              }

            }
          }
          if(last_flag == 1){
            break;
          }
        }
        if(last_flag == 1){
          break;
        }
      }
      return 0;
      // printf("\n==\n");
    }
  }else if(*(string_search+string_search_length-1) == '*'){
    int tmp_string_length = string_search_length - 1;
    int last_flag = 0;
    int flag = 0;
    for(int i=0; i<tmp_string_length; i++){
      for(int j=0; j<string_origin_length; j++){
        if(*(string_orign+j) == *(string_search+i)){
          int search_last_meta_cnt = tmp_string_length;
          int origin_cnt = 0;
          for(int k=i; k<tmp_string_length; k++){
            if(*(string_search+k) == '?'){
              search_last_meta_cnt--;
            }else{

              if(*(string_orign+j+origin_cnt) != *(string_search+k)){
                flag = 1;
              }else{
                search_last_meta_cnt--;
              }

            }
            origin_cnt++;
          }
          if(flag == 0){
            int z = 0;
            for(z = 0; z< tmp_string_length; z++){
              if(*(string_search+z) != '?'){
                if(*(string_orign+z) != *(string_search+z)){
                  break;
                }
              }
            }
            if(z == tmp_string_length){
              if(search_last_meta_cnt == 0){
                printf("right !\norigin : %s, search_data : %s\n", string_orign, string_search);
                last_flag = 1;
                return 1;
                break;
              }else{
                flag = 0;
              }
            }else{
              flag = 0;
            }
          }
        }
        if(last_flag == 1){
          break;
        }
      }
      if(last_flag == 1){
        break;
      }
    }
    return 0;
  }else{
    int tmp_string_length = string_search_length;
    int last_flag = 0;
    int flag = 0;
    for(int i=0; i<tmp_string_length; i++){
      if(*(string_search+i) != '?'){
        if(*(string_orign+i) == *(string_search+i)){
        }else{
          flag = 1;
        }
      }
    }
    if(flag == 0){
      printf("right !\norigin : %s, search_data : %s\n", string_orign, string_search);
      return 1;
    }else{
      return 0;
    }
  }
  return 0;
}

int option_search_movie(struct movie* movie, char* search_string){
  int flag = 0;
  int tmp_flag = 0;
  while(movie != NULL){
    int inWhile_tmp_flag = 0;
    tmp_flag = option_search_meta_search(movie -> title, search_string);
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    tmp_flag = option_search_meta_search(movie -> genre, search_string);
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    tmp_flag = option_search_meta_search(movie -> director.name, search_string);
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    struct linked_list_actor* actor = movie -> actor;
    while(actor != NULL){
      tmp_flag = option_search_meta_search(actor -> actor_name, search_string);
      if(inWhile_tmp_flag == 0){
        inWhile_tmp_flag = tmp_flag;
      }
      if(flag == 0){
        flag = tmp_flag;
      }
      actor = actor -> actor_next;
    }
    if(inWhile_tmp_flag == 1){
      printf("%d:%s:%s:%s:%d:%d:", movie -> Serial_number, movie -> title, movie -> genre, movie -> director.name, movie -> year, movie -> time);
      struct linked_list_actor *tmp_print_actor = movie -> actor;
      while(tmp_print_actor != NULL){
        if(tmp_print_actor -> actor_next == NULL){
          printf("%s", tmp_print_actor -> actor_name);
        }else{
          printf("%s, ", tmp_print_actor -> actor_name);
        }
        tmp_print_actor = tmp_print_actor -> actor_next;
      }
    }
    movie = movie -> movie_next;
  }
  if(flag == 0){
    printf("no %s in movie", search_string);
    return 0;
  }else{
    return 1;
  }
}



int option_search_director(DIRECTOR director, char* search_string){
  int flag = 0;
  int tmp_flag = 0;
  while(director != NULL){
    int inWhile_tmp_flag = 0;
    tmp_flag = option_search_meta_search(director -> name, search_string);
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    tmp_flag = option_search_meta_search(director -> birth, search_string);
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    MOVIE movie_in_director = director -> movie;
    while(movie_in_director != NULL){
      tmp_flag = option_search_meta_search(movie_in_director -> title, search_string);
      if(inWhile_tmp_flag == 0){
        inWhile_tmp_flag = tmp_flag;
      }
      if(flag == 0){
        flag = tmp_flag;
      }
      movie_in_director = movie_in_director -> movie_next;
    }
    if(inWhile_tmp_flag == 1){
      printf("%d:%s:%c:%s:", director -> serial_number, director -> name, director -> sex, director -> birth);
      MOVIE tmp_print_movie = director -> movie;
      while(tmp_print_movie != NULL){
        if(tmp_print_movie -> movie_next == NULL){
          printf("%s", tmp_print_movie -> title);
        }else{
          printf("%s, ", tmp_print_movie -> title);
        }
        tmp_print_movie = tmp_print_movie -> movie_next;
      }
    }
    director = director -> director_next;
  }
  if(flag == 0){
    printf("no %s in director", search_string);
    return 0;
  }else{
    return 1;
  }
}

char* now_time_string(){
      time_t timer;
      struct tm *t_time;
      timer = time(NULL);
      t_time = localtime(&timer);
      char* time_string = (char*)malloc(sizeof(char)*100);
      sprintf(time_string, "%d", (t_time->tm_year+1900));
      if((t_time->tm_mon+1) < 10){
        *(time_string+1) = '0';
        time_string++;
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_mon+1));
      }else{
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_mon+1));

      }

      if((t_time->tm_mday) < 10){
        *(time_string+strlen(time_string)) = '0';
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_mday));

      }else{
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_mday));

      }
      if((t_time->tm_hour) < 10){
        *(time_string+strlen(time_string)) = '0';
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_hour));
      }else{
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_hour));
      }

      if((t_time->tm_min) < 10){
        *(time_string+strlen(time_string)) = '0';
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_min));
      }else{
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_min));
      }

      if((t_time->tm_sec) < 10){
        *(time_string+strlen(time_string)) = '0';
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_sec));
      }else{
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_sec));
        *(time_string+strlen(time_string)) = '\0';
      }
      return time_string;
}

int option_search_actor(ACTOR actor, char* search_string){
  int flag = 0;
  int tmp_flag = 0;
  while(actor != NULL){
    int inWhile_tmp_flag = 0;
    tmp_flag = option_search_meta_search(actor -> name, search_string);
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    tmp_flag = option_search_meta_search(actor -> birth, search_string);
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    MOVIE movie_in_actor = actor -> movie;
    while(movie_in_actor != NULL){
      tmp_flag = option_search_meta_search(movie_in_actor -> title, search_string);
      if(inWhile_tmp_flag == 0){
        inWhile_tmp_flag = tmp_flag;
      }
      if(flag == 0){
        flag = tmp_flag;
      }
      movie_in_actor = movie_in_actor -> movie_next;
    }
    if(inWhile_tmp_flag == 1){
      if(actor -> sex){
        printf( "%d:%s:M:%s:", actor -> serial_number, actor -> name, actor -> birth);
      }else{
        printf( "%d:%s:F:%s:", actor -> serial_number, actor -> name, actor -> birth);
      }
      MOVIE tmp_print_movie = actor -> movie;
      while(tmp_print_movie != NULL){
        if(tmp_print_movie -> movie_next == NULL){
          printf("%s", tmp_print_movie -> title);
        }else{
          printf("%s, ", tmp_print_movie -> title);
        }
        tmp_print_movie = tmp_print_movie -> movie_next;
      }
    }
    actor = actor -> actor_next;
  }
  if(flag == 0){
    printf("no %s in actor", search_string);
    return 0;
  }else{
    return 1;
  }
}
void save_list_movie(char* option, struct movie *movie)
{
  FILE *fp, *tmp, *tmp_print;
  struct movie* save_movie = public_first_movie;
  char *movie_list_str;
  int size = 0;

  fp = fopen("movie_list.txt", "w");

  if(!strcmp(option, "ALL COMMANDS"))
   {
      strcpy(option, "tgdyra");
   }

    while(strlen(option))
    {
      switch(*option)
      {
        case 't' :
        if(size == 0)
        {
          while(save_movie)
          {
            fprintf(fp ,"%d:%s:=:=:=:=:=\n", save_movie->Serial_number, save_movie->title);
            save_movie = save_movie->movie_next;
          }
        }
        else
        {
          tmp = fopen("movie_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          movie_list_str = (char*)malloc(size + 1);

          while(fgets(movie_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(movie_list_str+strlen(movie_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(movie_list_str); i++)
            {
              if(*(movie_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 1)
              {
                movie_list_str = insert_string(movie_list_str, save_movie->title, i+1);
                fprintf(tmp_print, "%s\n", movie_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "movie_list.txt");

            save_movie = save_movie->movie_next;
          }

          free(movie_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_movie = public_first_movie;
        printf("Complete option for %c\n", *option);
        break;

        case 'g' :
        if(size == 0)
        {
          while(save_movie)
          {
            fprintf(fp ,"%d:=:%s:=:=:=:=\n", save_movie->Serial_number, save_movie->genre);
            save_movie = save_movie->movie_next;
          }
        }
        else
        {
          tmp = fopen("movie_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          movie_list_str = (char*)malloc(size + 1);

          while(fgets(movie_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(movie_list_str+strlen(movie_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(movie_list_str); i++)
            {
              if(*(movie_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 2)
              {
                movie_list_str = insert_string(movie_list_str, save_movie->genre, i+1);
                fprintf(tmp_print, "%s\n", movie_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "movie_list.txt");

            save_movie = save_movie->movie_next;
          }

          free(movie_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_movie = public_first_movie;
        printf("Complete option for %c\n", *option);
        break;

        case 'd' :
        if(size == 0)
        {
          while(save_movie)
          {
            fprintf(fp ,"%d:=:=:%s:=:=:=\n", save_movie->Serial_number, save_movie->director.name);
            save_movie = save_movie->movie_next;
          }
        }
        else
        {
          tmp = fopen("movie_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          movie_list_str = (char*)malloc(size + 1);

          while(fgets(movie_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(movie_list_str+strlen(movie_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(movie_list_str); i++)
            {
              if(*(movie_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 3)
              {
                movie_list_str = insert_string(movie_list_str, save_movie->director.name, i+1);
                fprintf(tmp_print, "%s\n", movie_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "movie_list.txt");

            save_movie = save_movie->movie_next;
          }

          free(movie_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_movie = public_first_movie;
        printf("Complete option for %c\n", *option);
        break;

        case 'y' :
        if(size == 0)
        {
          while(save_movie)
          {
            fprintf(fp ,"%d:=:=:=:%d:=:=\n", save_movie->Serial_number, save_movie->year);
            save_movie = save_movie->movie_next;
          }
        }
        else
        {
          tmp = fopen("movie_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          movie_list_str = (char*)malloc(size + 1);

          while(fgets(movie_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(movie_list_str+strlen(movie_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(movie_list_str); i++)
            {
              if(*(movie_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 4)
              {
                char *year;

                year = (char*)malloc(sizeof(char) * 5);
                sprintf(year, "%d", save_movie->year);

                movie_list_str = insert_string(movie_list_str, year, i+1);
                fprintf(tmp_print, "%s\n", movie_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "movie_list.txt");

            save_movie = save_movie->movie_next;
          }

          free(movie_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_movie = public_first_movie;
        printf("Complete option for %c\n", *option);
        break;

        case 'r' :
        if(size == 0)
        {
          while(save_movie)
          {
            fprintf(fp ,"%d:=:=:=:=:%d:=\n", save_movie->Serial_number, save_movie->time);
            save_movie = save_movie->movie_next;
          }
        }
        else
        {
          tmp = fopen("movie_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          movie_list_str = (char*)malloc(size + 1);

          while(fgets(movie_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(movie_list_str+strlen(movie_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(movie_list_str); i++)
            {
              if(*(movie_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 5)
              {
                char *time;

                time = (char*)malloc(sizeof(char) * 5);
                sprintf(time, "%d", save_movie->time);

                movie_list_str = insert_string(movie_list_str, time, i+1);
                fprintf(tmp_print, "%s\n", movie_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "movie_list.txt");

            save_movie = save_movie->movie_next;
          }

          free(movie_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_movie = public_first_movie;
        printf("Complete option for %c\n", *option);
        break;

        case 'a' :
        if(size == 0)
        {
          while(save_movie)
          {
            struct linked_list_actor* actor_tmp = save_movie->actor;

            fprintf(fp ,"%d:=:=:=:=:=:%s", save_movie->Serial_number, save_movie->actor->actor_name);

            while(save_movie->actor->actor_next != NULL)
            {
              save_movie->actor = save_movie->actor->actor_next;
              fprintf(fp, ", %s", save_movie->actor->actor_name);
            }
            fprintf(fp, "\n");
            save_movie->actor = actor_tmp;
            save_movie = save_movie->movie_next;
          }
        }
        else
        {
          tmp = fopen("movie_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          movie_list_str = (char*)malloc(size + 1);

          while(fgets(movie_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(movie_list_str+strlen(movie_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(movie_list_str); i++)
            {

              if(*(movie_list_str + i) == ':')
              {
                collon_cnt++;
              }
              if(collon_cnt == 6)
              {
                struct linked_list_actor* actor_tmp = save_movie->actor;

                movie_list_str = insert_string(movie_list_str, save_movie->actor->actor_name, i+1);
                fprintf(tmp_print, "%s", movie_list_str);
                fflush(tmp_print);

                while(save_movie->actor->actor_next != NULL)
                {
                  save_movie->actor = save_movie->actor->actor_next;
                  fprintf(tmp_print, ", %s", save_movie->actor->actor_name);
                  fflush(tmp_print);
                }
                fprintf(tmp_print, "\n");
                save_movie->actor = actor_tmp;

                break;
              }
            }
            rename("test.txt", "movie_list.txt");

            save_movie = save_movie->movie_next;
          }

          free(movie_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_movie = public_first_movie;
        printf("Complete option for %c\n", *option);
        break;

        default :
        printf("There is no option for %c\n", *option);
        break;
      }

      size = ftell(fp);

      strcpy(option, option + 1);
    }

  fclose(fp);
}

void save_list_director(char* option, struct director *director)
{
  FILE *fp, *tmp, *tmp_print;
  DIRECTOR save_director = public_director;
  char *director_list_str;
  int size = 0;

  fp = fopen("director_list.txt", "w");

  if(!strcmp(option, "ALL COMMANDS"))
   {
      strcpy(option, "nsbm");
   }

    while(strlen(option))
    {
      switch(*option)
      {
        case 'n' :
        if(size == 0)
        {
          while(save_director)
          {
            fprintf(fp ,"%d:%s:=:=:=\n", save_director->serial_number, save_director->name);
            save_director = save_director->director_next;
          }
        }
        else
        {
          tmp = fopen("director_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          director_list_str = (char*)malloc(size + 1);

          while(fgets(director_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(director_list_str+strlen(director_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(director_list_str); i++)
            {
              if(*(director_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 1)
              {
                director_list_str = insert_string(director_list_str, save_director->name, i+1);
                fprintf(tmp_print, "%s\n", director_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "director_list.txt");

            save_director = save_director->director_next;
          }

          free(director_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_director = public_director;
        printf("Complete option for %c\n", *option);
        break;

        case 's' :
        if(size == 0)
        {
          while(save_director)
          {
            fprintf(fp ,"%d:=:%c:=:=\n", save_director->serial_number, save_director->sex);
            save_director = save_director->director_next;
          }
        }
        else
        {
          tmp = fopen("director_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          director_list_str = (char*)malloc(size + 1);

          while(fgets(director_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(director_list_str+strlen(director_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(director_list_str); i++)
            {

              if(*(director_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 2)
              {
                director_list_str = insert_string(director_list_str, &(save_director->sex), i+1);
                fprintf(tmp_print, "%s\n", director_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "director_list.txt");

            save_director = save_director->director_next;
          }

          free(director_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_director = public_director;
        printf("Complete option for %c\n", *option);
        break;

        case 'b' :
        if(size == 0)
        {
          while(save_director)
          {
            fprintf(fp ,"%d:=:=:%s:=\n", save_director->serial_number, save_director->birth);
            save_director = save_director->director_next;
          }
        }
        else
        {
          tmp = fopen("director_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          director_list_str = (char*)malloc(size + 1);

          while(fgets(director_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(director_list_str+strlen(director_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(director_list_str); i++)
            {

              if(*(director_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 3)
              {
                director_list_str = insert_string(director_list_str, save_director->birth, i+1);
                fprintf(tmp_print, "%s\n", director_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "director_list.txt");

            save_director = save_director->director_next;
          }

          free(director_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_director = public_director;
        printf("Complete option for %c\n", *option);
        break;

        case 'm' :
        if(size == 0)
        {
          while(save_director)
          {
            struct best_movie* movie_tmp = save_director->movie;

            fprintf(fp, "%d:=:=:=:%s", save_director->serial_number, save_director->movie->title);

            while(save_director->movie->movie_next != NULL)
            {
              save_director->movie = save_director->movie->movie_next;
              fprintf(fp, ", %s", save_director->movie->title);
            }
            fprintf(fp, "\n");
            save_director->movie = movie_tmp;
            save_director = save_director->director_next;
          }
        }
        else
        {
          tmp = fopen("director_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          director_list_str = (char*)malloc(size + 1);

          while(fgets(director_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(director_list_str+strlen(director_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(director_list_str); i++)
            {

              if(*(director_list_str + i) == ':')
              {
                collon_cnt++;
              }
              if(collon_cnt == 4)
              {
                struct best_movie* movie_tmp = save_director->movie;

                director_list_str = insert_string(director_list_str, save_director->movie->title, i+1);
                fprintf(tmp_print, "%s", director_list_str);
                fflush(tmp_print);
                while(save_director->movie->movie_next != NULL)
                {
                  save_director->movie = save_director->movie->movie_next;
                  fprintf(tmp_print, ", %s", save_director->movie->title);
                  fflush(tmp_print);
                }
                fprintf(tmp_print, "\n");
                save_director->movie = movie_tmp;

                break;
              }
            }
            rename("test.txt", "director_list.txt");

            save_director = save_director->director_next;
          }

          free(director_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_director = public_director;
        printf("Complete option for %c\n", *option);
        break;

        default :
        printf("There is no option for %c\n", *option);
        break;
      }

      size = ftell(fp);

      strcpy(option, option + 1);
    }

  fclose(fp);
}

void save_list_actor(char* option, struct actor *actor)
{
  FILE *fp, *tmp, *tmp_print;
  ACTOR save_actor = public_actor;
  char *actor_list_str;
  int size = 0;

  fp = fopen("actor_list.txt", "w");

  if(!strcmp(option, "ALL COMMANDS"))
   {
      strcpy(option, "nsbm");
   }

    while(strlen(option))
    {
      switch(*option)
      {
        case 'n' :
        if(size == 0)
        {
          while(save_actor)
          {
            fprintf(fp ,"%d:%s:=:=:=\n", save_actor->serial_number, save_actor->name);
            save_actor = save_actor->actor_next;
          }
        }
        else
        {
          tmp = fopen("actor_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          actor_list_str = (char*)malloc(size + 1);

          while(fgets(actor_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(actor_list_str+strlen(actor_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(actor_list_str); i++)
            {
              if(*(actor_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 1)
              {
                actor_list_str = insert_string(actor_list_str, save_actor->name, i+1);
                fprintf(tmp_print, "%s\n", actor_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "actor_list.txt");

            save_actor = save_actor->actor_next;
          }

          free(actor_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_actor = public_actor;
        printf("Complete option for %c\n", *option);
        break;

        case 's' :
        if(size == 0)
        {
          while(save_actor)
          {
            char sex;

            if(save_actor->sex)
            {
              sex = 'M';
            }
            else
            {
              sex = 'F';
            }

            fprintf(fp ,"%d:=:%c:=:=\n", save_actor->serial_number, sex);
            save_actor = save_actor->actor_next;
          }
        }
        else
        {
          char* sex;

          tmp = fopen("actor_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          actor_list_str = (char*)malloc(size + 1);
          sex = (char*)malloc(sizeof(char) + 1);

          while(fgets(actor_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(actor_list_str+strlen(actor_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(actor_list_str); i++)
            {

              if(*(actor_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 2)
              {
                if(save_actor->sex)
                {
                  strcpy(sex, "M");
                }
                else
                {
                  strcpy(sex, "F");
                }

                actor_list_str = insert_string(actor_list_str, sex, i+1);
                fprintf(tmp_print, "%s\n", actor_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "actor_list.txt");

            save_actor = save_actor->actor_next;
          }

          free(actor_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_actor = public_actor;
        printf("Complete option for %c\n", *option);
        break;

        case 'b' :
        if(size == 0)
        {
          while(save_actor)
          {
            fprintf(fp ,"%d:=:=:%s:=\n", save_actor->serial_number, save_actor->birth);
            save_actor = save_actor->actor_next;
          }
        }
        else
        {
          tmp = fopen("actor_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          actor_list_str = (char*)malloc(size + 1);

          while(fgets(actor_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(actor_list_str+strlen(actor_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(actor_list_str); i++)
            {

              if(*(actor_list_str + i) == ':')
              {
                collon_cnt++;
              }

              if(collon_cnt == 3)
              {
                actor_list_str = insert_string(actor_list_str, save_actor->birth, i+1);
                fprintf(tmp_print, "%s\n", actor_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("test.txt", "actor_list.txt");

            save_actor = save_actor->actor_next;
          }

          free(actor_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_actor = public_actor;
        printf("Complete option for %c\n", *option);
        break;

        case 'm' :
        if(size == 0)
        {
          while(save_actor)
          {
            struct best_movie* movie_tmp = save_actor->movie;

            fprintf(fp, "%d:=:=:=:%s", save_actor->serial_number, save_actor->movie->title);

            while(save_actor->movie->movie_next != NULL)
            {
              save_actor->movie = save_actor->movie->movie_next;
              fprintf(fp, ", %s", save_actor->movie->title);
            }
            fprintf(fp, "\n");
            save_actor->movie = movie_tmp;
            save_actor = save_actor->actor_next;
          }
        }
        else
        {
          tmp = fopen("actor_list.txt", "r");
          tmp_print = fopen("test.txt", "w");

          actor_list_str = (char*)malloc(size + 1);

          while(fgets(actor_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(actor_list_str+strlen(actor_list_str)-1) = '\0';

            int collon_cnt = 0;
            for(int i = 0; i < strlen(actor_list_str); i++)
            {

              if(*(actor_list_str + i) == ':')
              {
                collon_cnt++;
              }
              if(collon_cnt == 4)
              {
                struct best_movie* movie_tmp = save_actor->movie;

                actor_list_str = insert_string(actor_list_str, save_actor->movie->title, i+1);
                fprintf(tmp_print, "%s", actor_list_str);
                fflush(tmp_print);
                while(save_actor->movie->movie_next != NULL)
                {
                  save_actor->movie = save_actor->movie->movie_next;
                  fprintf(tmp_print, ", %s", save_actor->movie->title);
                  fflush(tmp_print);
                }
                fprintf(tmp_print, "\n");
                save_actor->movie = movie_tmp;

                break;
              }
            }
            rename("test.txt", "actor_list.txt");

            save_actor = save_actor->actor_next;
          }

          free(actor_list_str);

          fclose(tmp_print);
          fclose(tmp);
        }
        save_actor = public_actor;
        printf("Complete option for %c\n", *option);
        break;

        default :
        printf("There is no option for %c\n", *option);
        break;
      }

      size = ftell(fp);

      strcpy(option, option + 1);
    }

  fclose(fp);
}

char* insert_string(char *origin, char *insert, int pos)
{
  char *str;
  int size;
  size = strlen(origin) + strlen(insert) + 1;
  str = (char*)malloc(size + 30);
  strncpy(str, origin, pos);
  strcpy(origin, origin+pos+1);

  strcat(str, insert);
  strcat(str, origin);

  return str;
}

char* colon_rchange(char *tmp_char){ // ??; => :
  char *split1 = (char*)malloc(sizeof(char)*100);
  char *split2 = (char*)malloc(sizeof(char)*100);
  char *split3 = (char*)malloc(sizeof(char)*100);
  split1 = "No Colon";
  while(strchr(tmp_char,';') != NULL){
    split1 = strtok(tmp_char, "?");
    split2 = strtok(NULL, ";");
    split3 = strtok(NULL, "");
    strcat(split1, ":");
    split2 = strcat(split1, split3);
  }
  if(!strcmp(split1, "No Colon")){
    return tmp_char;
  }else{
  return split2;
  }
}

int cmp_actor_n(const void* a,const void* b)
{
	ACTOR a_tmp=(ACTOR)a;
	ACTOR b_tmp=(ACTOR)b;

	return strcmp(a_tmp->name,b_tmp->name);
}


int cmp_actor_s(const void* a,const void* b)
{
	ACTOR a_tmp=(ACTOR)a;
	ACTOR b_tmp=(ACTOR)b;

	if (a_tmp->sex && b_tmp->sex)
		return 0;
	else if (a_tmp->sex)
		return 1;
	else
		return -1;

}

int cmp_actor_b(const void* a,const void* b)
{
	ACTOR a_tmp=(ACTOR)a;
	ACTOR b_tmp=(ACTOR)b;

	return strcmp(a_tmp->birth,b_tmp->birth);
}


int cmp_actor_m(const void* a,const void* b)
{
	ACTOR a_tmp=(ACTOR)a;
	ACTOR b_tmp=(ACTOR)b;

	return strcmp(a_tmp->movie->title,b_tmp->movie->title);
}

int cmp_director_n(const void* a,const void* b)
{
	DIRECTOR a_tmp=(DIRECTOR)a;
	DIRECTOR b_tmp=(DIRECTOR)b;

	return strcmp(a_tmp->name,b_tmp->name);
}


int cmp_director_s(const void* a,const void* b)
{
	DIRECTOR a_tmp=(DIRECTOR)a;
	DIRECTOR b_tmp=(DIRECTOR)b;

	if (a_tmp->sex && b_tmp->sex)
		return 0;
	else if (a_tmp->sex)
		return 1;
	else
		return -1;

}

int cmp_director_b(const void* a,const void* b)
{
	DIRECTOR a_tmp=(DIRECTOR)a;
	DIRECTOR b_tmp=(DIRECTOR)b;

	return strcmp(a_tmp->birth,b_tmp->birth);
}


int cmp_director_m(const void* a,const void* b)
{
	DIRECTOR a_tmp=(DIRECTOR)a;
	DIRECTOR b_tmp=(DIRECTOR)b;

	return strcmp(a_tmp->movie->title,b_tmp->movie->title);
}

int cmp_movie_tt(const void* a,const void* b)
{
	struct movie* a_tmp=(struct movie*)a;
	struct movie* b_tmp=(struct movie*)b;

	return strcmp(a_tmp->title,b_tmp->title);
}

int cmp_movie_g(const void* a,const void* b)
{
  struct movie* a_tmp=(struct movie*)a;
	struct movie* b_tmp=(struct movie*)b;

	return strcmp(a_tmp->genre,b_tmp->genre);
}

int cmp_movie_d(const void* a,const void* b)
{
  struct movie* a_tmp=(struct movie*)a;
	struct movie* b_tmp=(struct movie*)b;

	return strcmp(a_tmp->director.name,b_tmp->director.name);
}

int cmp_movie_y(const void* a,const void* b)
{
  struct movie* a_tmp=(struct movie*)a;
	struct movie* b_tmp=(struct movie*)b;

	if (a_tmp->year<b_tmp->year)
		return 1;
	else if (a_tmp->year==b_tmp->year)
		return 0;
	else
		return -1;
}

int cmp_movie_r(const void* a,const void* b)
{
  struct movie* a_tmp=(struct movie*)a;
	struct movie* b_tmp=(struct movie*)b;

	if (a_tmp->time<b_tmp->time)
		return 1;
	else if (a_tmp->time==b_tmp->time)
		return 0;
	else
		return -1;
}

int cmp_movie_a(const void* a,const void* b)
{
  struct movie* a_tmp=(struct movie*)a;
	struct movie* b_tmp=(struct movie*)b;

	return strcmp(a_tmp->actor->actor_name,b_tmp->actor->actor_name);
}

void sort_actor(char option, ACTOR actor)
{
  if (option==0)
    option='n';
	int n=count_actor_list(actor);
	ACTOR actor_tmp=actor;

	ACTOR sort_list=(ACTOR)malloc(sizeof(struct actor)*n);

	int cnt=0;

	while(actor_tmp->actor_next!=NULL)
	{
		(*(sort_list+cnt))= *actor_tmp;
		cnt++;
		actor_tmp=actor_tmp->actor_next;
	}
	(*(sort_list+cnt))= *actor_tmp;

	if (option=='n')
		qsort(sort_list,n,sizeof(struct actor),cmp_actor_n);
	else if (option=='s')
		qsort(sort_list,n,sizeof(struct actor),cmp_actor_s);
	else if (option=='b')
		qsort(sort_list,n,sizeof(struct actor),cmp_actor_b);
	else if (option=='m')
		qsort(sort_list,n,sizeof(struct actor),cmp_actor_m);

	for (int i=0;i<n;i++)
	{
		printf("%d:%s:",(sort_list+i)->serial_number,(sort_list+i)->name);
		if ((sort_list+i)->sex)
			printf("M:");
		else
			printf("F:");
		printf("%s:",(sort_list+i)->birth);
		while((sort_list+i)->movie->movie_next!=NULL)
		{
			printf("%s,",(sort_list+i)->movie->title);
			(sort_list+i)->movie=(sort_list+i)->movie->movie_next;
		}
		printf("%s\n",(sort_list+i)->movie->title);
	}

	printf("Sort Complete!\n");

	free(sort_list);

}

void sort_director(char option, DIRECTOR director)
{
  if (option==0)
    option='n';
  int cnt=0;
	int n=count_director_list(director);
	DIRECTOR director_tmp=director;

	DIRECTOR sort_list=(DIRECTOR)malloc(sizeof(struct director)*n);

	while(director_tmp->director_next!=NULL)
	{
		(*(sort_list+cnt))=*director_tmp;
		cnt++;
    director_tmp=director_tmp->director_next;
	}
	(*(sort_list+cnt))=*director_tmp;

	if (option=='n')
		qsort(sort_list,n,sizeof(struct director),cmp_director_n);
	else if (option=='s')
		qsort(sort_list,n,sizeof(struct director),cmp_director_s);
	else if (option=='b')
		qsort(sort_list,n,sizeof(struct director),cmp_director_b);
	else if (option=='m')
		qsort(sort_list,n,sizeof(struct director),cmp_director_m);

    for (int i=0;i<n;i++)
  	{
  		printf("%d:%s:",(sort_list+i)->serial_number,(sort_list+i)->name);
      printf("%c:",(sort_list+i)->sex);
  		printf("%s:",(sort_list+i)->birth);
  		while((sort_list+i)->movie->movie_next!=NULL)
  		{
  			printf("%s,",(sort_list+i)->movie->title);
  			(sort_list+i)->movie=(sort_list+i)->movie->movie_next;
  		}
  		printf("%s\n",(sort_list+i)->movie->title);
  	}

  	printf("Sort Complete!\n");

  	free(sort_list);

}

void sort_movie(char option, struct movie* movie)
{
  if (option==0)
    option='t';
  int cnt=0;
	int n=count_movie_list(movie);
	struct movie* movie_tmp=movie;
	struct movie* sort_list=(struct movie*)malloc(sizeof(struct movie)*n);

	while(movie_tmp->movie_next!=NULL)
	{
		(*(sort_list+cnt))=(*movie_tmp);
		cnt++;
    movie_tmp=movie_tmp->movie_next;
	}
	(*(sort_list+cnt))=(*movie_tmp);

	if (option=='t')
		qsort(sort_list,n,sizeof(struct movie),cmp_movie_tt);
	else if (option=='d')
		qsort(sort_list,n,sizeof(struct movie),cmp_movie_d);
	else if (option=='g')
		qsort(sort_list,n,sizeof(struct movie),cmp_movie_g);
	else if (option=='y')
		qsort(sort_list,n,sizeof(struct movie),cmp_movie_y);
	else if (option=='r')
		qsort(sort_list,n,sizeof(struct movie),cmp_movie_r);
	else if (option=='a')
		qsort(sort_list,n,sizeof(struct movie),cmp_movie_a);

    for (int i=0;i<n;i++)
  	{
  		printf("%d:%s:",(sort_list+i)->Serial_number,(sort_list+i)->title);
      printf("%s:",(sort_list+i)->genre);
  		printf("%s:",(sort_list+i)->director);
      printf("%d:%d:",(sort_list+i)->year,(sort_list+i)->time);
  		while((sort_list+i)->actor->actor_next!=NULL)
  		{
  			printf("%s,",(sort_list+i)->actor->actor_name);
  			(sort_list+i)->actor=(sort_list+i)->actor->actor_next;
  		}
  		printf("%s\n",(sort_list+i)->actor->actor_name);
  	}

  	printf("Sort Complete!\n");

  	free(sort_list);

}

int count_actor_list(ACTOR actor)
{
	int cnt=0;
	ACTOR actor_tmp=actor;

	while (actor_tmp->actor_next!=NULL)
	{
		cnt++;
		actor_tmp=actor_tmp->actor_next;
	}
	cnt++;


	return cnt;
}

int count_director_list(DIRECTOR director)
{
	int cnt=0;
	DIRECTOR director_tmp=director;

	while (director_tmp->director_next!=NULL)
	{
		cnt++;
		director_tmp=director_tmp->director_next;
	}
	cnt++;

	return cnt;
}

int count_movie_list(struct movie* movie)
{
	int cnt=0;
	struct movie* movie_tmp=movie;

  while(movie_tmp->movie_next!=NULL)
  {
		cnt++;
		movie_tmp=movie_tmp->movie_next;
  }
	cnt++;

	return cnt;
}

void option_delete_actor(int num,ACTOR actor)
{
  ACTOR actor_tmp=actor;
  ACTOR actor_tmp2=actor;
  bool break_flag=false;
  ACTOR actor_next_tmp;
  ACTOR public_actor_next_tmp;
  int cnt=0;
  struct best_movie* movie_next_tmp;

  while (actor_tmp->actor_next!=NULL)
  {
    if (actor_tmp->serial_number==num)
    {
      break_flag=true;
      actor_next_tmp=actor_tmp->actor_next;
      break;
    }
    cnt++;
  }
  if (actor_tmp->serial_number==num)
  {
    actor_next_tmp=actor_tmp->actor_next;
    break_flag=true;
  }

  if (break_flag)
  {
    if (cnt==0)
    {
      public_actor_next_tmp=public_actor->actor_next;
      public_actor->serial_number=public_actor_next_tmp->serial_number;
      strcpy(public_actor->name,public_actor_next_tmp->name);
      public_actor->sex=public_actor_next_tmp->sex;
      strcpy(public_actor->birth,public_actor_next_tmp->birth);
      public_actor->movie=public_actor_next_tmp->movie;
      public_actor->actor_next=public_actor_next_tmp->actor_next;
    }
    else
    {
      for (int i=0;i<cnt-1;i++)
      {
        actor_tmp2=actor_tmp2->actor_next;
      }
      actor_tmp2->actor_next=actor_next_tmp;

      free(actor_tmp->name);
      while(actor_tmp->movie->movie_next!=NULL)
      {
        movie_next_tmp=actor_tmp->movie->movie_next;
        free(actor_tmp->movie->title);
        free(actor_tmp->movie->movie_link);
        free(actor_tmp->movie->movie_next);
        actor_tmp->movie=movie_next_tmp;
      }
      free(actor_tmp->movie->title);
      free(actor_tmp->movie->movie_link);
      free(actor_tmp->movie->movie_next);

      free(actor_tmp->actor_next);
    }

    link_actor_to_movie();

    printf("Delete Complete!\n");
    fprintf(actor_log_read,"delete:%d::::\n",num);
  }
  else
  {
    printf("No such record\n");
  }

  free(actor_tmp);
  free(actor_tmp2);
  free(actor_next_tmp);
  free(public_actor_next_tmp);
  free(movie_next_tmp);
}
