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

      else if(!strcmp(split, "save"))
      {
        // 옵션이 없는 경우 에러
        command_what = strtok(NULL, " "); // mda
        option = strtok(NULL, " "); // option
        if(*option == '-')
        {
          strcpy(option, option + 1);
        }
        // split = strtok(NULL, " "); // -f filename

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
        }
        else
        {
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

  if(director == NULL){
    printf("No Such Record\n");
    return;
  }
  char option_letter = *option;
  char *tmp;
  int update_check = 1;
  int overlap = 0;
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
  director->movie->title = (char*)malloc(strlen(director->movie->title)+strlen(tmp)+3);
  // strcat(director->movie->title, ", ")
  // strcat(director->movie->title, tmp);
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
     update_check -= 100;
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
     update_check -= 1000;
   }else{
     fprintf(write_in_log,":%s", actor->name);
   }

   if((update_check % 3 != 0)){
     fprintf(write_in_log, ":=");
     update_check -= 100;
   }else{
    fprintf(write_in_log,":%c", actor->sex);
  }

   if((update_check % 5 != 0)){
     fprintf(write_in_log, ":=");
   }else{
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
    if(new == NULL){
      return NULL;
    }
  }

  return new;
}

void update_list_movie(char *option, char *serial, struct movie *movies){

  int i = 0;
  int serial_num = atoi(serial);
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
int director_overlap(DIRECTOR director){
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


void print_list_director(DIRECTOR director, char *serial){

  int serial_num = atoi(serial);
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

void save_list_movie(char* option, struct movie *movie)
{
  FILE *fp, *tmp, *tmp_print;
  struct movie* save_movie = public_first_movie;
  char *movie_list_str;
  int size = 0;

  fp = fopen("movie_list.txt", "w");

  // if(option == NULL)
  // {
  //   // strcpy(option, "tgdyra");
  // }

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

  // if(option == NULL)
  // {
  //   // strcpy(option, "nsbm");
  // }

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

  // if(option == NULL)
  // {
  //   // strcpy(option, "nsbm");
  // }

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
