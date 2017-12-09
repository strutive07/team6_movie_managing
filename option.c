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

        command_what = strtok(NULL, " ");
        split = strtok(NULL, " ");

        if (!strcmp(command_what, "d")){
          print_list_director(director, split);
        }else if(!strcmp(command_what, "a")){
          print_list_actor(actor, split);
        }else if(!strcmp(command_what,"m")){
          print_list_movie(movies, split);
        }else{
            continue;
        }
      }

      if(!strcmp(split, "delete")){

        command_what = strtok(NULL, " ");
        split = strtok(NULL, " ");
        int a = atoi(split);
    /*    if (!strcmp(command_what, "d")){
          option_delete_director(a, director);
        }else*/ if(!strcmp(command_what, "a")){
          option_delete_actor(a, actor);
        }else{
            continue;
        }/*else if(!strcmp(command_what,"m")){
          option_delete_movie(a, movies);
        }*/
      }

      if(!strcmp(split, "end")){
        printf("Do you want Save?\n");
        printf("[ Y : save data, N : don't Save ] : ");
        gets(split);
        if(!strcmp(split, "y") || !strcmp(split, "Y")){
          strcpy(option, "ALL COMMANDS");
          save_list_movie(option, movies, NULL);
          strcpy(option, "ALL COMMANDS");
          save_list_director(option, director, NULL);
          strcpy(option, "ALL COMMANDS");
          save_list_actor(option, actor, NULL);
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
          if(!strcmp(option, "-f")){ // tgdyra, nsbm이 아니고 -f면 옵션이 없다는 뜻
          strcpy(option, "ALL COMMANDS");
        }else if((split = strtok(NULL, " ")) != NULL){ // split이 잘랐을때 NULL이 아니면 -f를 저장
          if(strcmp(split, "-f")){ // -f가 아닐 경우 == filename를 바로 입력했을때
            continue;
          }else{
          option2 = (char *)malloc(sizeof(char)*100);
          option2 = strtok(NULL, " "); // -f filename
          printf("\n\nfilename is %s\n\n",option2);
        }
          }
        }else{ // save m 처럼 전부 디폴트일 때
        option = (char *)malloc(sizeof(char)*13); // token 과정에서 NULL처리가 되서 할당안하면 안되네
        strcpy(option, "ALL COMMANDS");
      }

        if(!strcmp(command_what, "m"))
        {
          save_list_movie(option, movies, option2);
        }
        else if(!strcmp(command_what, "d"))
        {
          save_list_director(option, director, option2);
        }
        else if(!strcmp(command_what, "a"))
        {
          save_list_actor(option, actor, option2);
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
        option = strtok(NULL, " ");
        option2 = strtok(NULL, " ");

          if(*option == '-')
          strcpy(option, option+1);
          int search_flag = 1;
        while(*option != '\0'){
          if(*option == 'm'){
            int tmp_flag = 1;
            tmp_flag = option_search_movie(public_first_movie, option2);
            if(search_flag == 1){
              search_flag = tmp_flag;
            }
          }else if(*option == 'd'){
            int tmp_flag = 1;
            tmp_flag = option_search_director(public_director, option2);
            if(search_flag == 1){
              search_flag = tmp_flag;
            }
          }else if(*option == 'a'){
            int tmp_flag = 1;
            tmp_flag = option_search_actor(public_actor, option2);
            if(search_flag == 1){
              search_flag = tmp_flag;
            }
          }
          strcpy(option, option+1);
        }
        if(search_flag == 0){
          printf("@@ No such record.\n");
        }
      }

      if(!strcmp(split, "sort")){
        // 옵션이 없는 경우 에러

        // save m option -f filename
        command_what = strtok(NULL, " "); // mda
        printf("command\n");
        if((option = strtok(NULL, " ")) != NULL){ // option이든 filename이든 있을 때
          if(!strcmp(option, "-f")){ // tgdyra, nsbm이 아니고 -f면 옵션이 없다는 뜻
          strcpy(option, "ALL COMMANDS");
        }else if((split = strtok(NULL, " ")) != NULL){ // split이 잘랐을때 NULL이 아니면 -f를 저장
          if(strcmp(split, "-f")){ // -f가 아닐 경우 == filename를 바로 입력했을때
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
        char option_letter;
        if(!strcmp(option,"ALL COMMANDS")){
          option_letter = 0;
      }else{
          option_letter = *option;
      }

        if(!strcmp(command_what, "m"))
        {
          sort_movie(option_letter, movies);
        }
        else if(!strcmp(command_what, "d"))
        {
          sort_director(option_letter, director);
        }
        else if(!strcmp(command_what, "a"))
        {
          sort_actor(option_letter, actor);
        }else
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

  MOVIE movie_copy_tmp = director -> movie;
  MOVIE movie_write_tmp = director -> movie;
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
  if(director_overlap(colon_change(tmp))){
    return;
  }
  director->name = (char*)malloc(strlen(tmp)+1);
  strcpy(director->name, tmp);
  free(tmp);
  update_check *= 2;
  break;

  case 's':
  printf("Director sex > ");
  gets(tmp);
  char letter = *tmp;
  if(letter != 'M' && letter != 'W'){
    printf("Wrong(Only M or W)\n");
    i--;
    break;
  }
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
  gets(tmp); // 문장 받고

  if((tmp2 = strtok(tmp, ",")) != NULL){ // 자르고
  movie_copy_tmp->title = (char*)malloc(strlen(tmp2)+5); // 공간 만든다음
  strcpy(movie_copy_tmp -> title, colon_change(tmp2)); // 문장 넣어주고
  while((tmp2 = strtok(NULL,",")) != NULL){ // 잘라서 더 있으면
    if(movie_copy_tmp -> movie_next == NULL){
      MOVIE next_movie = (MOVIE)malloc(sizeof(struct best_movie));
      movie_copy_tmp -> movie_next = next_movie;
      next_movie -> title = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후 <- 에러
      strcpy(next_movie -> title, colon_change(tmp2)); // 내용을 복사해서 넣고
    }else{
    movie_copy_tmp = movie_copy_tmp -> movie_next; // next로 넘겨서
    movie_copy_tmp -> title = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후
    strcpy(movie_copy_tmp -> title, colon_change(tmp2)); // 내용을 복사해서 넣고
      }
    }
    lint_movie_to_director(public_director, public_first_movie); // 링크로 연결할게 있는지 체크
    link_director_to_movie();
  }
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
       while(movie_write_tmp != NULL){
       fprintf(write_in_log,"%s", movie_write_tmp->title);
       movie_write_tmp = movie_write_tmp -> movie_next;
       if(movie_write_tmp != NULL)
       fprintf(write_in_log,",");
     }
   }
     fprintf(write_in_log, "\n");

     fclose(write_in_log);
     fprint_list_movie_director_actor('D', public_first_movie, public_director, public_actor);
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
  char *tmp2 = (char*)malloc(sizeof(char)*100);
  int update_check = 1;

  MOVIE movie_copy_tmp = actor -> movie;
  MOVIE movie_write_tmp = actor -> movie;

  FILE *write_in_log;

  if(!strcmp(option, "ALL COMMANDS")){
    strcpy(option, "nsbm");
  }

  write_in_log = fopen("actor_log.txt","a");

  while(i < strlen(option)){

  option_letter = *(option+i);

  tmp = (char *)calloc(1,sizeof(char)*100);

  switch(option_letter){

  case 'n':
  printf("Actor name > ");
  gets(tmp);
  if(director_overlap(colon_change(tmp))){
      return;
  }
  actor->name = (char*)malloc(strlen(tmp)+1);
  strcpy(actor->name, tmp);
  free(tmp);
  update_check *= 2;
  break;

  case 's':
  printf("Actor sex > ");
  gets(tmp);
  if(!strcmp(tmp, "M")){
    actor -> sex = 1;
  }else if(!strcmp(tmp, "W")){
    actor -> sex = 0;
  }else{
    printf("ONLY W or M can run in data\n");
  }
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
  if((tmp2 = strtok(tmp, ",")) != NULL){ // 자르고
  movie_copy_tmp->title = (char*)malloc(strlen(tmp2)+5); // 공간 만든다음
  strcpy(movie_copy_tmp -> title, colon_change(tmp2)); // 문장 넣어주고
  while((tmp2 = strtok(NULL,",")) != NULL){ // 잘라서 더 있으면
    if(movie_copy_tmp -> movie_next == NULL){
      MOVIE next_movie = (MOVIE)malloc(sizeof(struct best_movie));
      movie_copy_tmp -> movie_next = next_movie;
      next_movie -> title = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후 <- 에러
      strcpy(next_movie -> title, colon_change(tmp2)); // 내용을 복사해서 넣고
    }else{
    movie_copy_tmp = movie_copy_tmp -> movie_next; // next로 넘겨서
    movie_copy_tmp -> title = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후
    strcpy(movie_copy_tmp -> title, colon_change(tmp2)); // 내용을 복사해서 넣고
      }
    }
  }
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
  while(movie_write_tmp != NULL){
  fprintf(write_in_log,"%s", movie_write_tmp->title);
  movie_write_tmp = movie_write_tmp -> movie_next;
  if(movie_write_tmp != NULL)
  fprintf(write_in_log,",");
  }
}
     fprintf(write_in_log, "\n");

     fclose(write_in_log);
  fprint_list_movie_director_actor('A', public_first_movie, public_director, public_actor);
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
  char *tmp2 = (char*)malloc(sizeof(char)*100);
  int update_check = 1;

  struct linked_list_actor *actor_copy_tmp = movies -> actor;
  struct linked_list_actor *actor_write_tmp = movies -> actor;

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
  if(movie_overlap(colon_change(tmp))){
      return;
  }
  movies -> title = (char*)malloc(strlen(tmp)+1);
  strcpy(movies -> title, colon_change(tmp));
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
  link_director_to_movie();
  lint_movie_to_director(public_director, public_first_movie);
  update_check *= 5;
  break;

  case 'y':
  printf("Movie year > ");
  gets(tmp);
  movies->year = atoi(tmp);
  free(tmp);
  update_check *= 7;
  break;

  case 'r':
  printf("Movie time > ");
  gets(tmp);
  movies->time = atoi(tmp);
  free(tmp);
  update_check *= 11;
  break;

  case 'a':
  printf("Movie actor > ");
  gets(tmp);
  if((tmp2 = strtok(tmp, ",")) != NULL){ // 자르고
  actor_copy_tmp->actor_name = (char*)malloc(strlen(tmp2)+5); // 공간 만든다음
  strcpy(actor_copy_tmp -> actor_name, colon_change(tmp2)); // 문장 넣어주고
  while((tmp2 = strtok(NULL,",")) != NULL){ // 잘라서 더 있으면
    if(actor_copy_tmp -> actor_next == NULL){
      struct linked_list_actor *next_actor = (struct linked_list_actor*)malloc(sizeof(struct linked_list_actor));
      actor_copy_tmp -> actor_next = next_actor;
      next_actor -> actor_name = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후 <- 에러
      strcpy(next_actor -> actor_name, colon_change(tmp2)); // 내용을 복사해서 넣고
    }else{
    actor_copy_tmp = actor_copy_tmp -> actor_next; // next로 넘겨서
    actor_copy_tmp -> actor_name = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후
    strcpy(actor_copy_tmp -> actor_name, colon_change(tmp2)); // 내용을 복사해서 넣고
      }
    }
  }
  lint_movie_to_actor(public_actor, public_first_movie);
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
   }else{
    fprintf(write_in_log,":%s", movies->genre);
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
    fprintf(write_in_log,":");
    while(actor_write_tmp != NULL){
    fprintf(write_in_log,"%s", actor_write_tmp->actor_name);
    actor_write_tmp = actor_write_tmp -> actor_next;
    if(actor_write_tmp   != NULL)
    fprintf(write_in_log,",");
    }
  }
     fprintf(write_in_log, "\n");
     fclose(write_in_log);
       fprint_list_movie_director_actor('M', public_first_movie, public_director, public_actor);
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

  }
  return new;
}


int director_overlap(char *tmp){ // 다른 번호일때 찾는거 해야됨

  char* Y_N = (char *)malloc(sizeof(char));
  DIRECTOR check_overlap = public_director;
  while(check_overlap -> name != NULL){
  if(!strcmp(tmp ,check_overlap -> name)){
    break;
  }else{
    check_overlap = check_overlap -> director_next;
  }
  if(check_overlap == NULL){
    return 0;
  }
} //처음부터 이름을 전부 비교하고, 같다 -> break, 아니면 넘기고, if로 마지막이면 return 0
  printf("You have the same record\n");
  MOVIE movie_printonly = check_overlap->movie;
    printf("%d : ", check_overlap-> serial_number);
    colon_rchange(check_overlap -> name);
    printf("%c ", check_overlap -> sex);
    printf("%s \n", check_overlap -> birth);
    while(movie_printonly != NULL){
      printf("Best movie : ");
      colon_rchange(movie_printonly -> title);
      putchar('\n');
      movie_printonly = movie_printonly ->  movie_next;
    }
  printf("Do you want to change the record? (Y/N) : ");
  gets(Y_N);
  while(1){
  if(!strcmp(Y_N, "Y") || !strcmp(Y_N, "y")){
    return 0;
  }else if(!strcmp(Y_N, "N") || !strcmp(Y_N, "n")){
    return 1;
  }else{
    printf("y or n please\n");
    continue;
    }
  }
}

int actor_overlap(char *tmp){
  char* Y_N = (char *)malloc(sizeof(char));
  ACTOR check_overlap = public_actor;
  while(check_overlap -> name != NULL){
  if(!strcmp(tmp ,check_overlap -> name)){
    break;
  }else{
    check_overlap = check_overlap -> actor_next;
  }
  if(check_overlap == NULL){
    return 0;
  }
}
  printf("You have the same record\n");
  MOVIE movie_printonly = check_overlap->movie;
    printf("%d : ", check_overlap-> serial_number);
    colon_rchange(check_overlap -> name);
    printf("%c ", check_overlap -> sex);
    printf("%s \n", check_overlap -> birth);
    while(movie_printonly != NULL){
      printf("Best movie : ");
      colon_rchange(movie_printonly -> title);
      putchar('\n');
      movie_printonly = movie_printonly ->  movie_next;
    }
  printf("Do you want to change the record? (Y/N) : ");
  gets(Y_N);
  while(1){
  if(!strcmp(Y_N, "Y") || !strcmp(Y_N, "y")){
    return 0;
  }else if(!strcmp(Y_N, "N") || !strcmp(Y_N, "n")){
    return 1;
  }else{
    printf("y or n please\n");
    continue;
    }
  }
}

int movie_overlap(char *tmp){
  char* Y_N = (char *)malloc(sizeof(char));
  int i = 1;
  struct movie *check_overlap = public_first_movie;
  while(check_overlap -> title != NULL){
  if(!strcmp(tmp ,check_overlap -> title)){
    break;
  }else{
    check_overlap = check_overlap -> movie_next;
  }
  if(check_overlap == NULL){
    return 0;
  }
}
  printf("You have the same record\n");
  struct linked_list_actor *actor_printonly = check_overlap->actor;
    printf("%d : ", check_overlap-> Serial_number);
    colon_rchange(check_overlap -> title);
    printf("%s ", check_overlap -> genre);
    printf("%s \n", check_overlap->director.name);
    while(actor_printonly != NULL){
      printf("Actor %d : ",i++);
      colon_rchange(actor_printonly -> actor_name);
      putchar('\n');
      actor_printonly = actor_printonly ->  actor_next;
    }
  printf("Do you want to change the record? (Y/N) : ");
  gets(Y_N);
  while(1){
  if(!strcmp(Y_N, "Y") || !strcmp(Y_N, "y")){
    return 0;
  }else if(!strcmp(Y_N, "N") || !strcmp(Y_N, "n")){
    return 1;
  }else{
    printf("y or n please\n");
    continue;
    }
  }
}
void print_list_director(DIRECTOR director, char *serial){

  int serial_num = atoi(serial);

  if(serial_num != 1)
  director = move_serial_director(serial_num, director);
  if(director == NULL){
    printf("No Such Record\n");
    return;
  }
  MOVIE movie_printonly = director->movie;
    printf("%d : ", director-> serial_number);
    colon_rchange(director -> name);
    printf(" %c ", director -> sex);
    printf("%s \n", director -> birth);
    while(movie_printonly != NULL){
      printf("Best movie : ");
      colon_rchange(movie_printonly -> title);
      if(movie_printonly -> movie_link == NULL){
      putchar('\n');
      }else{
      printf(" : %d : %d\n", movie_printonly -> movie_link -> year, movie_printonly -> movie_link -> time);
      }
      movie_printonly = movie_printonly ->  movie_next;
    }
}
void print_list_actor(ACTOR actor, char *serial){

  int serial_num = atoi(serial);

  if(serial_num != 1)
  actor = move_serial_actor(serial_num, actor);
  if(actor == NULL){
    printf("No Such Record\n");
    return;
  }
  MOVIE actor_printonly = actor -> movie;
    printf("%d : ", actor -> serial_number);
    colon_rchange(actor -> name);
    printf(" %c ", actor -> sex);
    printf("%s \n", actor -> birth);

    while(actor_printonly != NULL){
      printf("Best movie : ");
      colon_rchange(actor_printonly -> title);
      if(actor_printonly -> movie_link == NULL){
      putchar('\n');
      }else{
      printf(" : %d : %d\n", actor_printonly -> movie_link -> year, actor_printonly -> movie_link -> time);
      }
      actor_printonly = actor_printonly -> movie_next;
    }
}
void print_list_movie(struct movie *movie, char *serial){

  int serial_num = atoi(serial);

  if(serial_num != 1)
  movie = move_serial_movie(serial_num, movie);
  if(movie == NULL){
    printf("No Such Record\n");
    return;
  }
  struct linked_list_actor *movie_printonly = movie -> actor;
    printf("%d : ", movie -> Serial_number);
    colon_rchange(movie -> title);
    colon_rchange(movie -> genre);
    putchar('\n');
    printf("D : ");
    colon_rchange(movie -> director.name);
    putchar('\n');
     if((movie -> director.director_pointer) != NULL){
       printf("(%s)\n",movie -> director.director_pointer -> birth);
    }else{
      putchar('\n');
    }
    int b = 0;
    while(movie_printonly != NULL){
      b++;
      printf("A%d : ", b);
      colon_rchange(movie_printonly -> actor_name);
      if(movie_printonly -> actor_pointer == NULL){
      putchar('\n');
      }else{
      printf("(%s)\n", movie_printonly -> actor_pointer -> birth);
      }
      movie_printonly = movie_printonly -> actor_next;
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
  struct movie *tmp_head_movie = movie;
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
  // fseek(mv_log_read,0,SEEK_END);
  // int file_size = ftell(mv_log_read);
  // printf("\n==\n%d\n=\n", file_size);

  inMovie -> movie_next = NULL;
  lastMovie = search_last_movie(movie);
  if(lastMovie == NULL){
        inMovie -> Serial_number = 1 ;
  }else{
    lastMovie -> movie_next = inMovie;
    inMovie -> Serial_number = (lastMovie -> Serial_number) +1 ;
  }

  inMovie -> actor = create_actor_struct(tmp_char);
  int tmp_flag_for_overlap_check = 0;
  while(tmp_head_movie != NULL){
    if(!strcmp(tmp_head_movie -> title, inMovie -> title)){
      printf("%s", tmp_head_movie -> title);
      printf("You have the same record in movie list. \n%d:%s:%s:%s:%d:%d:", tmp_head_movie->Serial_number, tmp_head_movie-> title, tmp_head_movie->genre, tmp_head_movie->director.name,tmp_head_movie-> year, tmp_head_movie->time);
      struct linked_list_actor* tmp_head_overlap_actor = tmp_head_movie -> actor;
      while(tmp_head_overlap_actor != NULL){
        if(tmp_head_overlap_actor -> actor_next == NULL){
          printf("%s", tmp_head_overlap_actor->actor_name );
          break;
        }else{
          printf("%s, ", tmp_head_overlap_actor-> actor_name);
          tmp_head_overlap_actor = tmp_head_overlap_actor -> actor_next;
        }
      }
      printf("\nDo you want to add any way? ");
      gets(tmp_char);
      if(*(tmp_char+0) == 'y' || *(tmp_char+0) == 'Y'){
        if(*(tmp_char+1) == 'e' || *(tmp_char+1) == 'E'){
          if(*(tmp_char+2) == 's' || *(tmp_char+2) == 's'){
            tmp_flag_for_overlap_check = 1;
          }
        }
      }
      if(tmp_flag_for_overlap_check == 1){
        break;
      }else{
        return;
      }
    }else{
      tmp_head_movie = tmp_head_movie -> movie_next;
    }
  }
  if(1){
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
    fprintf(mv_log_write, "\n");
  }
  // else{
  //   fprintf(mv_log_write, "add:%d:%s:%s:%s:%d:%d:", inMovie -> Serial_number, inMovie -> title, inMovie -> genre, inMovie -> director.name, inMovie -> year, inMovie -> time);
  //   struct linked_list_actor *tmp_print_actor = inMovie -> actor;
  //   while(tmp_print_actor != NULL){
  //     if(tmp_print_actor -> actor_next == NULL){
  //       fprintf(mv_log_write, "%s", tmp_print_actor -> actor_name);
  //     }else{
  //       fprintf(mv_log_write, "%s, ", tmp_print_actor -> actor_name);
  //     }
  //     tmp_print_actor = tmp_print_actor -> actor_next;
  //   }
  //   fprintf(mv_log_write, "\n");
  // }
  free(tmp_char);
  fclose(mv_log_read);
  fclose(mv_log_write);
  fprint_list_movie_director_actor('M', public_first_movie, public_director, public_actor);
  lint_movie_to_actor(public_actor, public_first_movie);
  lint_movie_to_director(public_director, public_first_movie);
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
  int tmp_flag_for_overlap_check = 0;
  while(tmp_head_director != NULL){
    if(!strcmp(tmp_head_director -> name, tmp_char)){
      printf("You have the same record in actor list. \n%d:%s:%c:%s:", tmp_head_director->serial_number, tmp_head_director-> name, tmp_head_director->sex, tmp_head_director-> birth);
      MOVIE tmp_head_overlap_actor = tmp_head_director -> movie;
      while(tmp_head_overlap_actor != NULL){
        if(tmp_head_overlap_actor -> movie_next == NULL){
          printf("%s", tmp_head_overlap_actor->title );
          break;
        }else{
          printf("%s, ", tmp_head_overlap_actor-> title);
          tmp_head_overlap_actor = tmp_head_overlap_actor -> movie_next;
        }
      }
      printf("\nDo you want to add any way? ");
      gets(tmp_char);
      if(*(tmp_char+0) == 'y' || *(tmp_char+0) == 'Y'){
        if(*(tmp_char+1) == 'e' || *(tmp_char+1) == 'E'){
          if(*(tmp_char+2) == 's' || *(tmp_char+2) == 's'){
            tmp_flag_for_overlap_check = 1;
          }
        }
      }
      if(tmp_flag_for_overlap_check == 1){
        break;
      }else{
        return;
      }
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
  // fseek(director_log_read,0,SEEK_END);
  // int file_size = ftell(director_log_read);


  director -> director_next = NULL;
  LastDirector = serach_last_director(public_first_director);
  if(LastDirector == NULL){
        director -> serial_number = 1 ;
  }else{
    LastDirector -> director_next = director;
    director -> serial_number = (LastDirector -> serial_number) +1 ;
  }


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
  if(1){
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
    fprintf(director_log_write, "\n");
  }
  // else{
  //   fprintf(director_log_write, "add:%d:%s:%c:%s:", director -> serial_number, director -> name, director -> sex, director -> birth);
  //   MOVIE tmp_print_movie = director -> movie;
  //   while(tmp_print_movie != NULL){
  //     if(tmp_print_movie -> movie_next == NULL){
  //       fprintf(director_log_write, "%s", tmp_print_movie -> title);
  //     }else{
  //       fprintf(director_log_write, "%s, ", tmp_print_movie -> title);
  //     }
  //     tmp_print_movie = tmp_print_movie -> movie_next;
  //   }
  //   fprintf(director_log_write, "\n");
  // }
  free(tmp_char);
  fclose(director_log_read);
  fclose(director_log_write);
  fprint_list_movie_director_actor('D', public_first_movie, public_director, public_actor);
  link_director_to_movie();
}
DIRECTOR serach_last_director(DIRECTOR public_first_director){
  DIRECTOR director = public_first_director;
  if(public_first_director == NULL){
    return NULL;
  }
  while((director -> director_next) != NULL){
    director = director -> director_next;
  }
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
      *(file_name + 0) = 'm';
      *(file_name + 1) = 'o';
      *(file_name + 2) = 'v';
      *(file_name + 3) = 'i';
      *(file_name + 4) = 'e';
      *(file_name + 5) = '_';
      *(file_name + 6) = 'l';
      *(file_name + 7) = 'i';
      *(file_name + 8) = 's';
      *(file_name + 9) = 't';
      *(file_name + 10) = '.';
      *(file_name + 11) = '\0';

      // strcat(file_name, "movie_list.");
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
      *(file_name + 0) = 'd';
      *(file_name + 1) = 'i';
      *(file_name + 2) = 'r';
      *(file_name + 3) = 'e';
      *(file_name + 4) = 'c';
      *(file_name + 5) = 't';
      *(file_name + 6) = 'o';
      *(file_name + 7) = 'r';
      *(file_name + 8) = '_';
      *(file_name + 9) = 'l';
      *(file_name + 10) = 'i';
      *(file_name + 11) = 's';
      *(file_name + 12) = 't';
      *(file_name + 13) = '.';
      *(file_name + 14) = '\0';
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
        printf(" actor_list File Open Error");
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
      char* ffile_nname = (char*)malloc(sizeof(char)*50);
      *(ffile_nname + 0) = 'a';
      *(ffile_nname + 1) = 'c';
      *(ffile_nname + 2) = 't';
      *(ffile_nname + 3) = 'o';
      *(ffile_nname + 4) = 'r';
      *(ffile_nname + 5) = '_';
      *(ffile_nname + 6) = 'l';
      *(ffile_nname + 7) = 'i';
      *(ffile_nname + 8) = 's';
      *(ffile_nname + 9) = 't';
      *(ffile_nname + 10) = '.';
      *(ffile_nname + 11) = '\0';
      strcat(ffile_nname, time_string);
      if((create_tmp_actor_list = fopen(ffile_nname, "w")) == NULL){
        printf("create_tmp_actor_list File Open Error");
        exit(1);
      }
      char chch;
      while((chch=fgetc(tmp_actor_list)) != EOF){
        printf("%c", chch);
        fputc(chch, create_tmp_actor_list);
      }
      fclose(create_tmp_actor_list);
      if((actor_list = fopen("actor_list.txt", "w")) == NULL){
        printf("actor_list in two File Open Error");
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
  int tmp_flag_for_overlap_check = 0;
  while(tmp_head_actor != NULL){
    if(!strcmp(tmp_head_actor -> name, tmp_char)){
      if(tmp_head_actor -> sex){
        printf("You have the same record in actor list. \n%d:%s:M:%s:", tmp_head_actor->serial_number, tmp_head_actor-> name, tmp_head_actor-> birth);
      }else{
        printf("You have the same record in actor list. \n%d:%s:F:%s:", tmp_head_actor->serial_number, tmp_head_actor-> name, tmp_head_actor-> birth);
      }
      MOVIE tmp_head_overlap_actor = tmp_head_actor -> movie;
      while(tmp_head_overlap_actor != NULL){
        if(tmp_head_overlap_actor -> movie_next == NULL){
          printf("%s", tmp_head_overlap_actor->title );
          break;
        }else{
          printf("%s, ", tmp_head_overlap_actor-> title);
          tmp_head_overlap_actor = tmp_head_overlap_actor -> movie_next;
        }
      }
      printf("\nDo you want to add any way? ");
      gets(tmp_char);
      if(*(tmp_char+0) == 'y' || *(tmp_char+0) == 'Y'){
        if(*(tmp_char+1) == 'e' || *(tmp_char+1) == 'E'){
          if(*(tmp_char+2) == 's' || *(tmp_char+2) == 's'){
            tmp_flag_for_overlap_check = 1;
          }
        }
      }
      if(tmp_flag_for_overlap_check == 1){
        break;
      }else{
        return;
      }
    }else{
      tmp_head_actor = tmp_head_actor -> actor_next;
    }
  }
  printf("ho?");
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
  printf("%s", tmp_char);
  // fseek(actor_log_read,0,SEEK_END);
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
  int file_size = ftell(actor_log_read);
  actor -> actor_next = NULL;

  LastActor = serach_last_actor(public_actor);
  if(LastActor == NULL){
    actor -> serial_number = 1 ;
  }else{
    LastActor -> actor_next = actor;
    actor -> serial_number = (LastActor -> serial_number) +1 ;
  }

  if(1){
    if(actor -> sex){
      fprintf(actor_log_write, "add:%d:%s:M:%s:", actor -> serial_number, actor -> name, actor -> birth);
    }else{
      fprintf(actor_log_write, "add:%d:%s:F:%s:", actor -> serial_number, actor -> name, actor -> birth);
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
    fprintf(actor_log_write, "\n");
  }
  free(tmp_char);
  fclose(actor_log_read);
  fclose(actor_log_write);
  fprint_list_movie_director_actor('A', public_first_movie, public_director, public_actor);
  link_actor_to_movie();
}
ACTOR serach_last_actor(ACTOR public_actor){
  ACTOR actor = public_actor;
  if(public_actor == NULL){
    return NULL;
  }
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
                // printf("right !\norigin : %s, search_data : %s\n", string_orign, string_search);
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
                  // printf("right !\norigin : %s, search_data : %s\n", string_orign, string_search);
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
                // printf("right !\norigin : %s, search_data : %s\n", string_orign, string_search);
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
      // printf("right !\norigin : %s, search_data : %s\n", string_orign, string_search);
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
      printf("\n");
    }
    movie = movie -> movie_next;
  }
  if(flag == 0){
    // printf("no %s in movie", search_string);
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
      printf("\n");
    }

    director = director -> director_next;
  }
  if(flag == 0){
    // printf("no %s in director", search_string);
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
      printf("\n");
    }
    actor = actor -> actor_next;
  }
  if(flag == 0){
    // printf("no %s in actor", search_string);
    return 0;
  }else{
    return 1;
  }
}
void save_list_movie(char* option, struct movie *movie, char* option2)
{
  FILE *fp, *tmp, *tmp_print;
  struct movie* save_movie = public_first_movie;
  char *movie_list_str;
  char* filename = (char*)malloc(sizeof(char)*100);
  int size = 0;

  if(*option == '-')
  {
    strcpy(option, option+1);
  }

  if(option2 == NULL)
  {
    strcpy(filename, "movie_list.txt");
  }
  else
  {
    strcpy(filename, option2);
  }
  fp = fopen(filename, "w");

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          movie_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          movie_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          movie_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          movie_list_str = (char*)malloc(size + 100);

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

                year = (char*)malloc(sizeof(char) * 100);
                sprintf(year, "%d", save_movie->year);

                movie_list_str = insert_string(movie_list_str, year, i+1);
                fprintf(tmp_print, "%s\n", movie_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("filename_list_tmp.txt", filename);

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          movie_list_str = (char*)malloc(size + 100);

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

                time = (char*)malloc(sizeof(char) * 100);
                sprintf(time, "%d", save_movie->time);

                movie_list_str = insert_string(movie_list_str, time, i+1);
                fprintf(tmp_print, "%s\n", movie_list_str);
                fflush(tmp_print);

                break;
              }
            }
            rename("filename_list_tmp.txt", filename);

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          movie_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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

void save_list_director(char* option, struct director *director, char* option2)
{
  FILE *fp, *tmp, *tmp_print;
  DIRECTOR save_director = public_director;
  char *director_list_str;
  char *filename = (char*)malloc(sizeof(char)*100);
  int size = 0;

  if(*option == '-')
  {
    strcpy(option, option+1);
  }

  if(option2 == NULL)
  {
    strcpy(filename, "director_list.txt");
  }
  else
  {
    strcpy(filename, option2);
  }
  fp = fopen(filename, "w");

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          director_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          director_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          director_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          director_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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

void save_list_actor(char* option, struct actor *actor, char* option2)
{
  FILE *fp, *tmp, *tmp_print;
  ACTOR save_actor = public_actor;
  char *actor_list_str;
  char *filename = (char*)malloc(sizeof(char)*100);
  int size = 0;

  if(*option == '-')
  {
    strcpy(option, option+1);
  }

  if(option2 == NULL)
  {
    strcpy(filename, "actor_list.txt");
  }
  else
  {
    strcpy(filename, option2);
  }
  fp = fopen(filename, "w");

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          actor_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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

          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          actor_list_str = (char*)malloc(size + 100);
          sex = (char*)malloc(sizeof(char) + 10);

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
            rename("filename_list_tmp.txt", filename);

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          actor_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          actor_list_str = (char*)malloc(size + 100);

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
            rename("filename_list_tmp.txt", filename);

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
  str = (char*)malloc(size + 100);
  strncpy(str, origin, pos);
  strcpy(origin, origin+pos+1);

  strcat(str, insert);
  strcat(str, origin);

  return str;
}

void colon_rchange(char *tmp_char){ // ??; => :
  int tmp_char_length = strlen(tmp_char)+1;
  for(int i=0; i<tmp_char_length; i++){
    if(*(tmp_char+i) == '?'){
      if(*(tmp_char+i+1) == '?'){
        if(*(tmp_char+i+2) == ';'){
          printf(":");
          i += 3;
        }
      }
    }
    printf("%c",*(tmp_char+i));
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
  		printf("%s:",(sort_list+i)->director.name);
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

void option_delete_actor(int num,ACTOR actor,bool from_where)
{
  ACTOR actor_tmp=actor;
  ACTOR actor_tmp2=actor;
  bool break_flag=false;
  ACTOR actor_next_tmp;
  ACTOR public_actor_next_tmp;
  int n=count_actor_list(actor);
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
    actor_tmp=actor_tmp->actor_next;
  }
  if (actor_tmp->serial_number==num)
  {
    actor_next_tmp=actor_tmp->actor_next;
    break_flag=true;
  }

  if (break_flag)
  {
    if (cnt==0 && n!=1)
    {
      public_actor_next_tmp=public_actor->actor_next;
      public_actor->serial_number=public_actor_next_tmp->serial_number;
      strcpy(public_actor->name,public_actor_next_tmp->name);
      public_actor->sex=public_actor_next_tmp->sex;
      strcpy(public_actor->birth,public_actor_next_tmp->birth);
      while(public_actor->movie->movie_next!=NULL)
      {
        movie_next_tmp=public_actor->movie->movie_next;
        free(actor_tmp->movie->title);
        public_actor->movie=movie_next_tmp;
      }
      public_actor->movie=public_actor_next_tmp->movie;

      public_actor->actor_next=public_actor_next_tmp->actor_next;

      free(public_actor_next_tmp->name);
      free(public_actor_next_tmp->birth);
    }
    else if (cnt==0 && n==1)
    {
      free(public_actor->name);
      free(public_actor->birth);
      while(public_actor->movie->movie_next!=NULL)
      {
        movie_next_tmp=public_actor->movie->movie_next;
        free(actor_tmp->movie->title);
        public_actor->movie=movie_next_tmp;
      }
      free(public_actor->actor_next);
      public_actor=NULL;
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
        actor_tmp->movie=movie_next_tmp;
      }
      free(actor_tmp->movie->title);
    }

    link_actor_to_movie();

    printf("Delete Complete!\n");

    if (!from_where)
    {
      FILE *actor_log_write;
      actor_log_write=fopen("actor_log.txt","a");
      fprintf(actor_log_write,"delete:%d::::\n",num);
      fclose(actor_log_write);
      fprint_list_movie_director_actor('A',public_first_movie,public_director,public_actor);
    }
  }
  else
  {
    printf("No such record\n");
  }
}

void option_delete_director(int num,DIRECTOR director,bool from_where)
{
  DIRECTOR director_tmp=director;
  DIRECTOR director_tmp2=director;
  bool break_flag=false;
  DIRECTOR director_next_tmp;
  DIRECTOR public_director_next_tmp;
  int n=count_director_list(director);
  int cnt=0;
  struct best_movie* movie_next_tmp;

  while (director_tmp->director_next!=NULL)
  {
    if (director_tmp->serial_number==num)
    {
      break_flag=true;
      director_next_tmp=director_tmp->director_next;
      break;
    }
    cnt++;
    director_tmp=director_tmp->director_next;
  }
  if (director_tmp->serial_number==num)
  {
    director_next_tmp=director_tmp->director_next;
    break_flag=true;
  }

  if (break_flag)
  {
    if (cnt==0 && n!=1)
    {
      public_director_next_tmp=public_director->director_next;
      public_director->serial_number=public_director_next_tmp->serial_number;
      strcpy(public_director->name,public_director_next_tmp->name);
      public_director->sex=public_director_next_tmp->sex;
      strcpy(public_director->birth,public_director_next_tmp->birth);
      while(public_director->movie->movie_next!=NULL)
      {
        movie_next_tmp=public_director->movie->movie_next;
        free(public_director->movie->title);
        public_director->movie=movie_next_tmp;
      }
      public_director->movie=public_director_next_tmp->movie;
      public_director->director_next=public_director_next_tmp->director_next;
    }
    else if (cnt==0 && n==1)
    {
      free(public_director->name);
      free(public_director->birth);
      while(director_tmp->movie->movie_next!=NULL)
      {
        movie_next_tmp=public_director->movie->movie_next;
        free(public_director->movie->title);
        public_director->movie=movie_next_tmp;
      }
      free(public_director->movie->title);
      public_director=NULL;
    }
    else
    {
      for (int i=0;i<cnt-1;i++)
      {
        director_tmp2=director_tmp2->director_next;
      }
      director_tmp2->director_next=director_next_tmp;

      free(director_tmp->name);

      while(director_tmp->movie->movie_next!=NULL)
      {
        movie_next_tmp=director_tmp->movie->movie_next;
        free(director_tmp->movie->title);
        director_tmp->movie=movie_next_tmp;
      }
      free(director_tmp->movie->title);
    }

    link_director_to_movie();

    printf("Delete Complete!\n");

    if (!from_where)
    {
      FILE *director_log_write;
      director_log_write=fopen("director_log.txt","a");
      fprintf(director_log_write,"delete:%d::::\n",num);
      fclose(director_log_write);
      fprint_list_movie_director_actor('D',public_first_movie,public_director,public_actor);
    }
  }
  else
  {
    printf("No such record\n");
  }

}

void option_delete_movie(int num,struct movie* movie,bool from_where)
{
  struct movie* movie_tmp=movie;
  struct movie* movie_tmp2=movie;
  bool break_flag=false;
  struct movie* movie_next_tmp;
  struct movie* public_first_movie_next_tmp;
  int n=count_movie_list(movie);
  int cnt=0;
  struct linked_list_actor* actor_next_tmp;

  while (movie_tmp->movie_next!=NULL)
  {
    if (movie_tmp->Serial_number==num)
    {
      break_flag=true;
      movie_next_tmp=movie_tmp->movie_next;
      break;
    }
    cnt++;
    movie_tmp=movie_tmp->movie_next;
  }
  if (movie_tmp->Serial_number==num)
  {
    movie_next_tmp=movie_tmp->movie_next;
    break_flag=true;
  }

  if (break_flag)
  {
    if (cnt==0 && n!=1)
    {
      public_first_movie_next_tmp=public_first_movie->movie_next;
      public_first_movie->Serial_number=public_first_movie_next_tmp->Serial_number;
      strcpy(public_first_movie->title,public_first_movie_next_tmp->title);
      strcpy(public_first_movie->genre,public_first_movie_next_tmp->genre);
      public_first_movie->director=public_first_movie_next_tmp->director;
      public_first_movie->year=public_first_movie_next_tmp->year;
      public_first_movie->time=public_first_movie_next_tmp->time;
      while(public_first_movie->actor->actor_next!=NULL)
      {
        actor_next_tmp=public_first_movie->actor->actor_next;
        free(public_first_movie->actor->actor_name);
        public_first_movie->actor=actor_next_tmp;
      }
      free(movie_tmp->actor->actor_name);
      public_first_movie->actor=public_first_movie_next_tmp->actor;

      public_first_movie->movie_next=public_first_movie_next_tmp->movie_next;
    }
    else if (cnt==0 && n==1)
    {
      free(public_first_movie->title);
      free(public_first_movie->genre);
      while(public_first_movie->actor->actor_next!=NULL)
      {
        actor_next_tmp=public_first_movie->actor->actor_next;
        free(public_first_movie->actor->actor_name);
        public_first_movie->actor=actor_next_tmp;
      }
      free(movie_tmp->actor->actor_name);
      public_first_movie=NULL;
    }
    else
    {
      for (int i=0;i<cnt-1;i++)
      {
        movie_tmp2=movie_tmp2->movie_next;
      }
      movie_tmp2->movie_next=movie_next_tmp;

      free(movie_tmp->title);
      free(movie_tmp->genre);

      while(movie_tmp->actor->actor_next!=NULL)
      {
        actor_next_tmp=movie_tmp->actor->actor_next;
        free(movie_tmp->actor->actor_name);
        movie_tmp->actor=actor_next_tmp;
      }
      free(movie_tmp->actor->actor_name);
    }

    lint_movie_to_actor(public_actor,public_first_movie);
    lint_movie_to_director(public_director,public_first_movie);

    printf("Delete Complete!\n");

    if (!from_where)
    {
      FILE *movie_log_write;
      movie_log_write=fopen("movie_log.txt","a");
      fprintf(movie_log_write,"delete:%d::::\n",num);
      fclose(movie_log_write);
      fprint_list_movie_director_actor('M',public_first_movie,public_director,public_actor);
    }
  }
  else
  {
    printf("No such record\n");
  }

}
