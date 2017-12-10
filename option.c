#include "option.h"
#include <time.h>
void whats_up_commander(){ // 입력받는 함수

  printf(">> Welcome to My Movie <<\n");
  printf("File Loading......\n");
  printf("You can use add, update, delete, search, sort, save, end commands.\n");
  // 다음 5개의 포인터는 입력을 받기위한 char형 포인터이다.
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
    gets(whats_up_commander); // gets로 명령어를 받음
    if(strlen(whats_up_commander) == 0){ // 받은게 아무거도 없으면
    continue; //넘어감
    }else{
    split = strtok(whats_up_commander, " "); // 아니면 첫 단어를 잘라 명령어인지 확인
    }

      if(!strcmp(split,"update")){ // update면
      command_what = strtok(NULL, " "); // mda를 자르고
      option = strtok(NULL, " "); // option을 자름
      if(atoi(option) == 0){ // option이 0이면 숫자가 아닌 문자를 받았다고 생각하고
      split = strtok(NULL, " "); // 시리얼 넘버를 받음
      }else{
      strcpy(split, option); // 아닐 경우는 split가 시리얼 넘버라는 뜻
      strcpy(option, "ALL COMMANDS"); //option은 이때 모든 옵션을 사용
    }

      if (!strcmp(command_what, "d")){ // director일 경우
        update_list_director(option, split, director);
      }else if(!strcmp(command_what, "a")){ // actor
        update_list_actor(option, split, actor);
      }else if(!strcmp(command_what,"m")){ // movie
        update_list_movie(option, split, movies);
      }else{
        continue;
      }


    }else if(!strcmp(split, "print")){ //print의 경우

        command_what = strtok(NULL, " "); // mda를 자르고
        split = strtok(NULL, " "); // 시리얼넘버를 자름

        if (!strcmp(command_what, "d")){ // director
          print_list_director(director, split);
        }else if(!strcmp(command_what, "a")){ // actor
          print_list_actor(actor, split);
        }else if(!strcmp(command_what,"m")){ // movie
          print_list_movie(movies, split);
        }else{
            continue;
        }
      }else if(!strcmp(split, "delete")){ // delete의 경우

        command_what = strtok(NULL, " "); // mda를 받고
        split = strtok(NULL, " "); // 시리얼넘버를 자름
        int a = atoi(split); // 이 함수는 인자를 int형으로 받으므로 미리 변환
        if (!strcmp(command_what, "d")){
          option_delete_director(a, director, false); // director
        }else if(!strcmp(command_what, "a")){
          option_delete_actor(a, actor, false); // actor
        }else if(!strcmp(command_what,"m")){
          option_delete_movie(a, movies, false); // movie
        }else{
            continue;
        }
      }else if(!strcmp(split, "end")){ // end의 경우
        printf("Do you want Save?\n");
        printf("[ Y : save data, N : don't Save ] : ");
        gets(split);
        if(!strcmp(split, "y") || !strcmp(split, "Y")){ // 저장 여부를 묻고
          strcpy(option, "ALL COMMANDS");
          save_list_movie(option, movies, NULL); // 디폴트 기준으로 모든 데이터를 save함
          strcpy(option, "ALL COMMANDS");
          save_list_director(option, director, NULL);
          strcpy(option, "ALL COMMANDS");
          save_list_actor(option, actor, NULL);
          exit(1);
        }else if(!strcmp(split, "n") || !strcmp(split, "N")){ // 아니면 그냥 종료
          exit(1);
        }else{
          printf("@@ Wrong Command\n");
        }
      }else if(!strcmp(split, "save")){
      	// save m option -f filename
      	command_what = strtok(NULL, " "); // mda

      	if((option = strtok(NULL, " ")) != NULL){ // option이든 filename이든 있을 때 (-f 혹은 option을 잘랐다.)

      	if((split = strtok(NULL, " ")) == NULL && strcmp(option, "-f")){//option이 있고 split로 자른게 없다 = file이 디폴트
      	 option2 = NULL;
       }else if(split != NULL && !strcmp(split, "-f")){ // split로 자른게 있다 + split이 -f다 = 뒤에 filename이 있다
      	 option2 = (char *)malloc(sizeof(char)*100);
      	 option2 = strtok(NULL, " "); // 다음으로 자른 것이 option2이다.
       }
       if(!strcmp(option, "-f")){ // -f였으면 option은 없었다. split에 filename가 저장되어있다.
	 option2 = (char *)malloc(strlen(split)+1); // option2는 NULL로 초기화될 경우 새로 메모리할당을 하지 않으면 strcpy를 할 공간이 없어 오류가 발생한다.
         strcpy(option2,split);
      	 strcpy(option, "ALL COMMANDS");
       }

      }else{ // option이 없었다면 전부 디폴트였다. save m
      option = (char *)malloc(sizeof(char)*13); // token 과정에서 NULL처리가 되서 할당안하면 안되네
      strcpy(option, "ALL COMMANDS");
      option2 = NULL;
      }
      	if(!strcmp(command_what, "m"))
      	{
      		save_list_movie(option, movies, option2);
          if(split == NULL) // split가 NULL일 경우 이후 strcmp에서 에러가 발생
          split = (char *)malloc(sizeof(char)*100);

          if (option2 == NULL) // option2도
          option2 = (char *)malloc(sizeof(char)*100);
      	}
      	else if(!strcmp(command_what, "d"))
      	{
      		save_list_director(option, director, option2);
          if(split == NULL) // split가 NULL일 경우 이후 strcmp에서 에러가 발생
          split = (char *)malloc(sizeof(char)*100);

          if (option2 == NULL) // option2도
          option2 = (char *)malloc(sizeof(char)*100);
      	}
      	else if(!strcmp(command_what, "a"))
      	{
      		save_list_actor(option, actor, option2);
          if(split == NULL) // split가 NULL일 경우 이후 strcmp에서 에러가 발생
          split = (char *)malloc(sizeof(char)*100);

          if (option2 == NULL) // option2도
          option2 = (char *)malloc(sizeof(char)*100);
      	}else
      	{
      		continue;
      	}

      }else if(!strcmp(split,"add")){ // add의 경우
        command_what = strtok(NULL, " "); //mda를 자름

        if(!strcmp(command_what, "m"))
        {
          option_add_movie(public_first_movie); // movie
        }
        else if(!strcmp(command_what, "d"))
        {
          option_add_director(public_director); // director
        }
        else if(!strcmp(command_what, "a"))
        {
           option_add_actor(public_actor); // actor
        }else
        {
          printf("only add m/d/a can run\n");
          continue;
        }
      }else if(!strcmp(split,"search")){ //search의 경우
        option = strtok(NULL, " "); // -mda
        option2 = strtok(NULL, " "); // 키워드

          if(*option == '-') // -는 자르고
          strcpy(option, option+1);
          int search_flag = 1;
        while(*option != '\0'){
          if(*option == 'm'){
            int tmp_flag = 1;
            tmp_flag = option_search_movie(public_first_movie, option2); // search값(결과가 없으면 0)을 저장
            if(search_flag == 1){
              search_flag = tmp_flag;
            }
          }else if(*option == 'd'){
            int tmp_flag = 1;
            tmp_flag = option_search_director(public_director, option2);// search값(결과가 없으면 0)을 저장
            if(search_flag == 1){
              search_flag = tmp_flag;
            }
          }else if(*option == 'a'){
            int tmp_flag = 1;
            tmp_flag = option_search_actor(public_actor, option2);// search값(결과가 없으면 0)을 저장
            if(search_flag == 1){
              search_flag = tmp_flag;
            }
          }
          strcpy(option, option+1); // 한글자씩 넘김(-md면 m, d 순으로)
        }
        if(search_flag == 0){ // 결과가 없으면 다음 문자 출력
          printf("@@ No such record.\n");
        }
      }else if(!strcmp(split, "sort")){
         // sort m option -f filename
         command_what = strtok(NULL, " "); // mda

         if((option = strtok(NULL, " ")) != NULL){ // option이든 filename이든 있을 때 (-f 혹은 option을 잘랐다.)

         if((split = strtok(NULL, " ")) == NULL && strcmp(option, "-f")){//option이 있고 split로 자른게 없다 = file이 디폴트
          option2 = NULL;
         }else if(split != NULL && !strcmp(split, "-f")){ // split로 자른게 있다 + split이 -f다 = 뒤에 filename이 있다
            option2 = (char *)malloc(sizeof(char)*100);
            option2 = strtok(NULL, " "); // 다음으로 자른 것이 option2이다.
         }
         if(!strcmp(option, "-f")){ // -f였으면 option은 없었다. split에 filename가 저장되어있다.
            option2 = (char *)malloc(strlen(split)+1); // option2는 NULL로 초기화될 경우 새로 메모리할당을 하지 않으면 strcpy를 할 공간이 없어 오류가 발생한다.
	    strcpy(option2,split);
            strcpy(option, "ALL COMMANDS");
         }

       }else{ // option이 없었다면 전부 디폴트였다. sort m
        option = (char *)malloc(sizeof(char)*13); // token 과정에서 NULL처리가 되서 할당안하면 안되네
        strcpy(option, "ALL COMMANDS");
        option2 = NULL; // filename는 default인 NULL로 넘겨받음
        }

        char option_letter_tmp  = *option; // option 전달용

         if(!strcmp(command_what, "m"))
         {
           if (!strcmp(option,"ALL COMMANDS"))
             option_letter_tmp='t'; // option을 안줘 ALL COMMANDS상태면 default인 t로 넘김
            sort_movie(option_letter_tmp, movies, option2);
            if(split == NULL) // split가 NULL일 경우 이후 strcmp에서 에러가 발생
            split = (char *)malloc(sizeof(char)*100);

            if (option2 == NULL) // option2도
            option2 = (char *)malloc(sizeof(char)*100);
         }
         else if(!strcmp(command_what, "d"))
         {
           if (!strcmp(option,"ALL COMMANDS"))
             option_letter_tmp='n'; // option을 안줘 ALL COMMANDS상태면 default인 n으로 넘김
            sort_director(option_letter_tmp, director, option2);
            if(split == NULL) // split가 NULL일 경우 이후 strcmp에서 에러가 발생
            split = (char *)malloc(sizeof(char)*100);

            if (option2 == NULL) // option2도
            option2 = (char *)malloc(sizeof(char)*100);
         }
         else if(!strcmp(command_what, "a"))
         {
           if (!strcmp(option,"ALL COMMANDS"))
             option_letter_tmp='n'; // option을 안줘 ALL COMMANDS상태면 default인 n으로 넘김
            sort_actor(option_letter_tmp, actor, option2);
            if(split == NULL) // split가 NULL일 경우 이후 strcmp에서 에러가 발생
            split = (char *)malloc(sizeof(char)*100);

            if (option2 == NULL) // option2도
            option2 = (char *)malloc(sizeof(char)*100);
         }else
         {
            continue;
         }

       }else{
         printf("@@ Wrong Command\n"); // 해당 명령어가 없을 경우 wrong command를 출력
       }

  }

}


void you_wanna_end(int sig)
{
  char a;
  printf("\nGet Interrupt Signal.\n");
  printf("Do you want to exit myMOVIE program? (Y/N) ");
  scanf("%c", &a); // 종료 여부를 묻는 문자를 받음
  if((a == 'y') || (a == 'Y')){ // 종료
    printf("bye");
    exit(1);
  }else if((a == 'n') || (a == 'N')){ // 원래 함수, whats_up_commander로 돌아감
    return;
  }else{
    printf("\n\n@@ Wrong Command\n\n");
    you_wanna_end(2);
  }
}

void update_list_director(char *option, char *serial, DIRECTOR director){

  int i = 0;
  int serial_num = atoi(serial); // 시리얼번호를 정수로 변환

  if(serial_num != 1)
  director = move_serial_director(serial_num, director); // 시리얼 번호의 디렉터로 이동

  if(director == NULL){ // 없을 경우 종료
    printf("No Such Record\n");
    return;
  }

  char option_letter = *option; // option의 첫글자
  char *tmp;
  char *tmp2 = (char*)malloc(sizeof(char)*100);
  int update_check = 1; // 이후 log에 변경사항 기록 확인용
  int overlap = 0;

  MOVIE movie_copy_tmp = director -> movie; // 구조체 데이터에 영화 입력을 위한 movie구조체
  MOVIE movie_write_tmp = director -> movie; // 파일에 영화 입력을 위한 movie 구조체
  FILE *write_in_log;


  if(!strcmp(option, "ALL COMMANDS")){
    strcpy(option, "nsbm"); // 옵션이 없어 ALL COMMANDS로 치환된걸 다시 변환
  }

  write_in_log = fopen("director_log.txt","a");

  while(i < strlen(option)){

  option_letter = *(option+i); // option 문자를 변경

  tmp = (char *)calloc(1,sizeof(char)*100); // 입력용

  switch(option_letter){

  case 'n':
  printf("Director name > ");
  gets(tmp); //이름을 입력 받음
  if(director_overlap(colon_change(tmp))){ // same record 체크 후 수정여부를 묻는 함수
    return; // no의 경우
  }
  director->name = (char*)malloc(strlen(tmp)+1);//공간 할당 후
  strcpy(director->name, tmp);
  free(tmp); // 복사
  update_check *= 2; // name는 변경이 진행됨을 말함
  break;

  case 's':
  printf("Director sex > ");
  gets(tmp);
  char letter = *tmp;
  if(letter != 'M' && letter != 'F'){ // M이나 F가 아니면 거절 후 i--(밑에서 i++를 하므로 값은 그대로)
    printf("Wrong(Only M or F)\n");
    i--;
    break;
  }
  update_check *= 3; // sex는 변경이 진행됨을 의미
  break;

  case 'b':
  printf("Director birth > ");
  gets(tmp); // 생일을 받고
  director->birth = (char*)malloc(strlen(tmp)+1);//공간을 할당 후
  strcpy(director->birth, tmp); //저장
  free(tmp);
  update_check *= 5; // 변경 진행됨
  break;

  case 'm':
  printf("Director movie > ");
  gets(tmp); // 문장 받고

  if((tmp2 = strtok(tmp, ",")) != NULL){ // 자르고
  movie_copy_tmp->title = (char*)malloc(strlen(tmp2)+5); // 공간 만든다음
  strcpy(movie_copy_tmp -> title, colon_change(tmp2)); // 문장 넣어주고
  while((tmp2 = strtok(NULL,",")) != NULL){ // 잘라서 더 있으면
    if(movie_copy_tmp -> movie_next == NULL){ //else 이후 진행되는 문장, 만약 movie 공간이 부족하면
      MOVIE next_movie = (MOVIE)malloc(sizeof(struct best_movie)); // 새로 MOVIE형 선언 후
      movie_copy_tmp -> movie_next = next_movie; // 공간을 연결해줌
      next_movie -> title = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후
      strcpy(next_movie -> title, colon_change(tmp2)); // 내용을 복사해서 넣음
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
  update_check *= 7;//변경 진행
  break;

  default:
  break;
  }

  i++;
  }

  fprintf(write_in_log,"update:%d",serial_num); //이제 파일에 기록

   if((update_check % 2 != 0)){ // update_check가 2,3,5,7 등의 소수의 곱으로 구성되어 nsbm간 요소가 겹치지 않고 업데이트 여부를 확인할 수 있음
     fprintf(write_in_log, ":=");
   }else{ //0이면 나누어 떨어졌다는 뜻이므로 업데이트가 진행됨을 의미
     fprintf(write_in_log,":%s", director->name);
   }
//이하 다른 3가지 또한 동일
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
       fprintf(write_in_log,"%s", movie_write_tmp->title); // movie의 모든 데이터를 입력
       movie_write_tmp = movie_write_tmp -> movie_next;
       if(movie_write_tmp != NULL)
       fprintf(write_in_log,",");
     }
   }
     fprintf(write_in_log, "\n");

     fclose(write_in_log);
     fprint_list_movie_director_actor('D', public_first_movie, public_director, public_actor); // director_list.현재시간 에 파일저장
}


DIRECTOR move_serial_director(int serial, DIRECTOR origin){ // director 함수를 n번 시리얼로 이동시킴
  DIRECTOR new;
  new = origin;

  while((serial != new -> serial_number) && (new != NULL)) // 시리얼이 같을때까지 혹은 NULL 전까지
  {
    new = new->director_next; // next로 넘긴 후
    if(new == NULL){// 없으면 NULL 리턴
      return NULL;
    }
  }

  return new; // 있으면 그 시리얼 구조체를 리턴
}

void update_list_actor(char *option, char *serial, ACTOR actor){

  int i = 0;
  int serial_num = atoi(serial); // 시리얼번호를 정수로 변환

  if(serial_num != 1)
  actor = move_serial_actor(serial_num, actor); // 시리얼 번호의 디렉터로 이동

  if(actor == NULL){ // 없을 경우 종료
    printf("No Such Record\n");
    return;
  }

  char option_letter = *option; // option의 첫글자
  char *tmp;
  char *tmp2 = (char*)malloc(sizeof(char)*100);
  int update_check = 1; // 이후 log에 변경사항 기록 확인용

  MOVIE movie_copy_tmp = actor -> movie; // 구조체 데이터에 영화 입력을 위한 movie구조체
  MOVIE movie_write_tmp = actor -> movie; // 파일에 영화 입력을 위한 movie 구조체

  FILE *write_in_log;

  if(!strcmp(option, "ALL COMMANDS")){
    strcpy(option, "nsbm"); // 옵션이 없어 ALL COMMANDS로 치환된걸 다시 변환
  }

  write_in_log = fopen("actor_log.txt","a");

  while(i < strlen(option)){

  option_letter = *(option+i); // option 문자를 변경

  tmp = (char *)calloc(1,sizeof(char)*100);  // 입력용

  switch(option_letter){

  case 'n':
  printf("Actor name > ");
  gets(tmp); //이름을 입력 받음
  if(director_overlap(colon_change(tmp))){ // same record 체크 후 수정여부를 묻는 함수
      return;// no의 경우
  }
  actor->name = (char*)malloc(strlen(tmp)+1); //공간 할당 후
  strcpy(actor->name, tmp);
  free(tmp);
  update_check *= 2; // name는 변경이 진행됨을 말함
  break;

  case 's':
  printf("Actor sex > ");
  gets(tmp);
  if(!strcmp(tmp, "M")){
    actor -> sex = 1;
  }else if(!strcmp(tmp, "F")){
    actor -> sex = 0;
  }else{
    printf("ONLY F or M can run in data\n");  // M이나 F가 아니면 거절 후 i--(밑에서 i++를 하므로 값은 그대로)
  }
  update_check *= 3; // 변경 진행됨
  break;

  case 'b':
  printf("Actor birth > ");
  gets(tmp); // 생일을 받고
  actor->birth = (char*)malloc(strlen(tmp)+1); //공간을 할당 후
  strcpy(actor->birth, tmp);  //저장
  free(tmp);
  update_check *= 5; // 변경 진행됨
  break;

  case 'm':
  printf("Actor movie > ");
  gets(tmp);
  if((tmp2 = strtok(tmp, ",")) != NULL){ // 자르고
  movie_copy_tmp->title = (char*)malloc(strlen(tmp2)+5); // 공간 만든다음
  strcpy(movie_copy_tmp -> title, colon_change(tmp2)); // 문장 넣어주고
  while((tmp2 = strtok(NULL,",")) != NULL){ // 잘라서 더 있으면
    if(movie_copy_tmp -> movie_next == NULL){ //else 이후 진행되는 문장, 만약 movie 공간이 부족하면
      MOVIE next_movie = (MOVIE)malloc(sizeof(struct best_movie)); // 새로 MOVIE형 선언 후
      movie_copy_tmp -> movie_next = next_movie; // 공간을 연결해줌
      next_movie -> title = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후
      strcpy(next_movie -> title, colon_change(tmp2)); // 내용을 복사해서 넣고
    }else{
    movie_copy_tmp = movie_copy_tmp -> movie_next; // next로 넘겨서
    movie_copy_tmp -> title = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후
    strcpy(movie_copy_tmp -> title, colon_change(tmp2)); // 내용을 복사해서 넣고
      }
    }
  }
  lint_movie_to_actor(public_actor, public_first_movie); //링크
  free(tmp);
  update_check *= 7; //변경 진행
  break;

  default:
  break;
  }

  i++;
  }

    fprintf(write_in_log,"update:%d",serial_num); //이제 파일에 기록

   if((update_check % 2 != 0)){  // update_check가 2,3,5,7 등의 소수의 곱으로 구성되어 nsbm간 요소가 겹치지 않고 업데이트 여부를 확인할 수 있음
     fprintf(write_in_log, ":=");
   }else{ //0이면 나누어 떨어졌다는 뜻이므로 업데이트가 진행됨을 의미
     fprintf(write_in_log,":%s", actor->name);
   }
//이하 다른 3가지 또한 동일
   if((update_check % 3 != 0)){
     fprintf(write_in_log, ":=");
   }else{
     if(actor->sex)
    fprintf(write_in_log,":M");
     else
    fprintf(write_in_log,":F");

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
  fprint_list_movie_director_actor('A', public_first_movie, public_director, public_actor); // director_list.현재시간 에 파일저장
}


ACTOR move_serial_actor(int serial, ACTOR origin){  // actor 함수를 n번 시리얼로 이동시킴
  ACTOR new;
  new = origin;

  while((serial != new -> serial_number) && (new != NULL))// 시리얼이 같을때까지 혹은 NULL 전까지
  {
    new = new->actor_next; // next로 넘긴 후
    if(new == NULL){ // 없으면 NULL 리턴
      return NULL;
    }
  }

  return new; // 있으면 그 시리얼 구조체를 리턴
}

void update_list_movie(char *option, char *serial, struct movie *movies){

  int i = 0;
  int serial_num = atoi(serial); // 시리얼 문자열 정수화

  if(serial_num != 1)
  movies = move_serial_movie(serial_num, movies); // 이동

  if(movies == NULL){ // 없으면
    printf("No Such Record\n"); // 리턴
    return;
  }

  char option_letter = *option;
  char *tmp;
  char *tmp2 = (char*)malloc(sizeof(char)*100);
  int update_check = 1;

  struct linked_list_actor *actor_copy_tmp = movies -> actor; // actor 구조체 저장용
  struct linked_list_actor *actor_write_tmp = movies -> actor; // actor 파일 입력용

  FILE *write_in_log;

  if(!strcmp(option, "ALL COMMANDS")){
    strcpy(option, "tgdyra");
  }

  write_in_log = fopen("movie_log.txt","a");

  while(i < strlen(option)){

  option_letter = *(option+i); // option을 한글자씩

  tmp = (char *)calloc(1,sizeof(char)*100);

  switch(option_letter){

  case 't':
  printf("Movie title > ");
  gets(tmp);
  if(movie_overlap(colon_change(tmp))){ // same record 체크 후 변경여부 묻고
      return; //no일때
  }
  movies -> title = (char*)malloc(strlen(tmp)+1); // 할당
  strcpy(movies -> title, colon_change(tmp)); // 복사
  free(tmp);
  update_check *= 2; // 변경 확인
  break;
// g,d 또한 똑같음
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
  link_director_to_movie(); // 이후 링크
  lint_movie_to_director(public_director, public_first_movie);
  update_check *= 5;
  break;

  case 'y':
  printf("Movie year > ");
  gets(tmp);
  movies->year = atoi(tmp); // tmp를 정수로 변환하여 저장
  free(tmp);
  update_check *= 7;
  break;

  case 'r':
  printf("Movie time > ");
  gets(tmp);
  movies->time = atoi(tmp); // tmp를 정수로 변환하여 저장
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
    if(actor_copy_tmp -> actor_next == NULL){//else 이후 실행, 공간이 더 필요하면
      struct linked_list_actor *next_actor = (struct linked_list_actor*)malloc(sizeof(struct linked_list_actor)); // 새로 만들어서
      actor_copy_tmp -> actor_next = next_actor; // 연결
      next_actor -> actor_name = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후 <- 에러
      strcpy(next_actor -> actor_name, colon_change(tmp2)); // 내용을 복사해서 넣고
    }else{
    actor_copy_tmp = actor_copy_tmp -> actor_next; // next로 넘겨서
    actor_copy_tmp -> actor_name = (char*)malloc(strlen(tmp2)+5); // title에 공간을 할당한 후
    strcpy(actor_copy_tmp -> actor_name, colon_change(tmp2)); // 내용을 복사해서 넣고
      }
    }
  }
  lint_movie_to_actor(public_actor, public_first_movie); // 링크
  free(tmp);
  update_check *= 13;
  break;

  default:
  break;
  }

  i++;
  }
    fprintf(write_in_log,"update:%d",serial_num); // 파일 입력

   if((update_check % 2 != 0)){ //update는 2,3,5,7,11,13 의 소수곱으로 구성, 항목 별 겹침이 없음
     fprintf(write_in_log, ":=");
   }else{
     fprintf(write_in_log,":%s", movies->title); // 나머지 0 = 배수, 다음 항목이 변경됨을 의미, fprintf 실행
   }
//나머지 또한 동일
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
    while(actor_write_tmp != NULL){ //actor의 모든 데이터를 입력
    fprintf(write_in_log,"%s", actor_write_tmp->actor_name);
    actor_write_tmp = actor_write_tmp -> actor_next;
    if(actor_write_tmp   != NULL)
    fprintf(write_in_log,",");
    }
  }
     fprintf(write_in_log, "\n");
     fclose(write_in_log);
    fprint_list_movie_director_actor('M', public_first_movie, public_director, public_actor); // movie_list.현재시간 저장
}


struct movie* move_serial_movie(int serial, struct movie *origin){
  struct movie *new;
  new = origin;

  while((serial != new -> Serial_number) && (new != NULL)) // 시리얼넘버 같을때까지 or 없어서 NULL까지 갈때까지
  {
    new = new->movie_next; //next로 이동

    if(new == NULL){ //NULL이면(없으면)
      return NULL; // NULL 리턴
    }

  }
  return new; // 아니면 해당 시리얼 포인터 리턴
}


int director_overlap(char *tmp){ // same record 체크

  char* Y_N = (char *)malloc(sizeof(char));
  DIRECTOR check_overlap = public_director;
  while(check_overlap -> name != NULL){ // 이름 겹치는거 있는지 비교
  if(!strcmp(tmp ,check_overlap -> name)){
    break; //겹치면 break로 아래 실행
  }else{
    check_overlap = check_overlap -> director_next; // 아니면 넘기고
  }
  if(check_overlap == NULL){
    return 0; // 없으면 리턴 0으로 종료
  }
}
    printf("You have the same record\n"); // same record의 데이터 출력
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
  printf("Do you want to change the record? (Y/N) : "); //변경할지 물어봄
  gets(Y_N);
  while(1){
  if(!strcmp(Y_N, "Y") || !strcmp(Y_N, "y")){ // y면 0으로 리턴
    return 0;
  }else if(!strcmp(Y_N, "N") || !strcmp(Y_N, "n")){ // 아니면 1 리턴
    return 1;
  }else{
    printf("y or n please\n");
    continue;
    }
  }
}

int actor_overlap(char *tmp){ // same record actor용
  char* Y_N = (char *)malloc(sizeof(char));
  ACTOR check_overlap = public_actor;
  while(check_overlap -> name != NULL){ // 이름 끝까지 비교
  if(!strcmp(tmp ,check_overlap -> name)){
    break; //같으면 아래 문장 실행
  }else{
    check_overlap = check_overlap -> actor_next;
  }
  if(check_overlap == NULL){
    return 0; // 없으면 리턴 0
  }
}
    printf("You have the same record\n"); //정보 출력
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
  printf("Do you want to change the record? (Y/N) : "); //변경할지 물어봄
  gets(Y_N);
  while(1){
  if(!strcmp(Y_N, "Y") || !strcmp(Y_N, "y")){
    return 0;// Y면 리턴 0으로 하고
  }else if(!strcmp(Y_N, "N") || !strcmp(Y_N, "n")){
    return 1;// N이면 리턴 1으로 변경안함
  }else{
    printf("y or n please\n");
    continue;
    }
  }
}

int movie_overlap(char *tmp){ // movie버전
  char* Y_N = (char *)malloc(sizeof(char));
  int i = 1;
  struct movie *check_overlap = public_first_movie;
  while(check_overlap -> title != NULL){ // 끝까지
  if(!strcmp(tmp ,check_overlap -> title)){//비교해서 같으면
    break;// break로 아래내용 실행
  }else{
    check_overlap = check_overlap -> movie_next; // 아니면 넘김
  }
  if(check_overlap == NULL){
    return 0;//없으면 리턴0으로 나머지 실행
  }
}
    printf("You have the same record\n"); // 정보 출력
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
  printf("Do you want to change the record? (Y/N) : "); //변경할지
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
void print_list_director(DIRECTOR director, char *serial){ //출력함수

  int serial_num = atoi(serial);

  if(serial_num != 1)
  director = move_serial_director(serial_num, director); //시리얼 이동
  if(director == NULL){ //없으면 출력안함
    printf("No Such Record\n");
    return;
  }
    MOVIE movie_printonly = director->movie;
    printf("%d : ", director-> serial_number); // 정보 출력 시작
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
void print_list_actor(ACTOR actor, char *serial){ // 출력함수

  int serial_num = atoi(serial);

  if(serial_num != 1)
  actor = move_serial_actor(serial_num, actor); // 시리얼 이동
  if(actor == NULL){ // 없으면 출력안함
    printf("No Such Record\n");
    return;
  }
    MOVIE actor_printonly = actor -> movie;
    printf("%d : ", actor -> serial_number); // 정보 출력 시작
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
void print_list_movie(struct movie *movie, char *serial){ // 출력함수

  int serial_num = atoi(serial);

  if(serial_num != 1)
  movie = move_serial_movie(serial_num, movie); // 시리얼 이동
  if(movie == NULL){ // 없으면 출력안함
    printf("No Such Record\n");
    return;
  }
    struct linked_list_actor *movie_printonly = movie -> actor;
    printf("%d : ", movie -> Serial_number); // 정보 출력 시작
    colon_rchange(movie -> title);
    putchar('\n');
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
  inMovie = malloc(sizeof(struct movie));//구조체 동적 할당
  char* tmp_char = (char*)malloc(sizeof(char)*200);

  printf("title > ");
  gets(tmp_char);
  struct movie *tmp_head_movie = movie;
  inMovie -> title = (char*)malloc(sizeof(char)*strlen(tmp_char+5));
  strcpy(inMovie -> title , colon_change(tmp_char));//콜론 처리 하면서 구조체에 title 넣음

  printf("genre > ");
  gets(tmp_char);
  inMovie -> genre = (char*)malloc(sizeof(char)*strlen(tmp_char+5));
  // inMovie -> genre = colon_change(tmp_char);
  strcpy(inMovie -> genre , colon_change(tmp_char));//콜론 처리 하면서 구조체에 genre 넣음

  printf("director > ");
  gets(tmp_char);
  inMovie -> director.name = (char*)malloc(sizeof(char)*strlen(tmp_char)+5);
  // inMovie -> director.name = colon_change(tmp_char);
  strcpy(inMovie -> director.name , colon_change(tmp_char));//콜론 처리 하면서 구조체에 director name 넣음

  printf("year > ");
  gets(tmp_char);
  inMovie -> year = atoi(tmp_char);//year 구조체에 추가

  printf("time > ");
  gets(tmp_char);
  inMovie -> time = atoi(tmp_char); //time 구조체에 추가

  printf("actor > ");
  gets(tmp_char);
  // fseek(mv_log_read,0,SEEK_END);
  // int file_size = ftell(mv_log_read);
  // printf("\n==\n%d\n=\n", file_size);



  inMovie -> actor = create_actor_struct(tmp_char);//actor 추가해주는 함수. head 를 inMovie -> actor 에 연결
  int tmp_flag_for_overlap_check = 0;
  while(tmp_head_movie != NULL){ //같은거 있나 채크.
    if(!strcmp(tmp_head_movie -> title, inMovie -> title)){
      // printf("%s", tmp_head_movie -> title);
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
      if(*(tmp_char+0) == 'y' || *(tmp_char+0) == 'Y'){//같은거 있을시 yes 받으면 저장하고 아니면 안함
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
  inMovie -> movie_next = NULL;
  lastMovie = search_last_movie(movie);
  if(lastMovie == NULL){//아예 빈 log 파일이였으면
    public_first_movie = inMovie;//전역변수 movie 에 inMovie 를 끼워넣음.
    inMovie -> Serial_number = 1 ;
    // printf("first!!!!0\n");
  }else{
    lastMovie -> movie_next = inMovie;//아니면 전 꺼 next 에 연결하고 시리얼 넘버 추가해줌
    inMovie -> Serial_number = (lastMovie -> Serial_number) +1 ;
  }
  if(1){
    fprintf(mv_log_write, "add:%d:%s:%s:%s:%d:%d:", inMovie -> Serial_number, inMovie -> title, inMovie -> genre, inMovie -> director.name, inMovie -> year, inMovie -> time);//log 파일에 추가하기
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
  fprint_list_movie_director_actor('M', public_first_movie, public_director, public_actor);//list 에 쓰기 movie_list
  lint_movie_to_actor(public_actor, public_first_movie);//링크
  lint_movie_to_director(public_director, public_first_movie);
}
void option_add_director(DIRECTOR public_first_director){//director add
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
  strcpy(director -> name , colon_change(tmp_char));//콜론 채인지 적용해서 name 에 director 구조체에 넣음
  DIRECTOR tmp_head_director = public_first_director;
  int tmp_flag_for_overlap_check = 0;
  while(tmp_head_director != NULL){//같은거 있는지 채크
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
      if(*(tmp_char+0) == 'y' || *(tmp_char+0) == 'Y'){//yes 면 저장 아니면 저장 X
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
  director -> sex = tmp_char[0];//성별 저장

  printf("birth > ");
  gets(tmp_char);
  director -> birth = (char*)malloc(sizeof(char)*strlen(tmp_char)+5);
  // inMovie -> director.name = colon_change(tmp_char);
  strcpy(director -> birth , colon_change(tmp_char));//콜론처리까지 해서 생일 저장

  printf("best movie > ");
  gets(tmp_char);
  // fseek(director_log_read,0,SEEK_END);
  // int file_size = ftell(director_log_read);

  char* split = strtok(tmp_char, ",");

  MOVIE movie;
  movie = list_movie_director(split);
  director -> movie = movie;

  while((split = strtok(NULL, ",")) != NULL){//best movie 저장해주는 함수 호출.
    if(*split+0 == ' '){
      strcpy(split, split+1);
    }
    MOVIE movie_tmp = list_movie_director(split);
    movie = put_list_movie_director(movie, movie_tmp);
  }

  director -> director_next = NULL;
  LastDirector = serach_last_director(public_first_director);//마지막꺼 채크. 없으면 NULL 반환
  if(LastDirector == NULL){//앞에 아무것도 없으면
    public_director = director;//이번꺼가 head 가 됨
        director -> serial_number = 1 ;
  }else{
    LastDirector -> director_next = director;//아니면 director 앞에꺼랑 연결
    director -> serial_number = (LastDirector -> serial_number) +1 ;//시리얼 넘버 추가
  }



  if(1){
    fprintf(director_log_write, "add:%d:%s:%c:%s:", director -> serial_number, director -> name, director -> sex, director -> birth);//director_log 에 add 한거 추가
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
  fprint_list_movie_director_actor('D', public_first_movie, public_director, public_actor);//list 업데이트해줌
  link_director_to_movie();//링크 다시만듬
}
DIRECTOR serach_last_director(DIRECTOR public_first_director){//마지막 director 찾는함수. 아무것도 없으면 NULL 있으면 마지막꺼 주소 반환.
  DIRECTOR director = public_first_director;
  if(public_first_director == NULL){
    return NULL;
  }
  while((director -> director_next) != NULL){
    director = director -> director_next;
  }
  return director;
}
void fprint_list_movie_director_actor(char isMovie_DIrector_Actor, struct movie *movie, DIRECTOR director, ACTOR actor){//movie, director, actor list 에 업데이트 해주는 함수. 이미 list 파일이 있으면 현재 시간 받아서 백업본 만듬.

  FILE* tmp_mv_list, *tmp_director_list, *tmp_actor_list;
  FILE* mv_list, *director_list, *actor_list;

  if(isMovie_DIrector_Actor == 'M'){//movie list 저장
    if((tmp_mv_list = fopen("movie_list.txt", "r")) == NULL){//movie_list 가 없으면 list 파일 만들고 저장
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
    }else{//이미 list 파일이 있으면 백업본을 만듬
      FILE * create_tmp_mv_list;
      char* time_string = now_time_string();//현재 날짜 시간 불러와서
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
      strcat(file_name, time_string);//백업본 이름 만들고
      if((create_tmp_mv_list = fopen(file_name, "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
      char chch;
      while((chch=fgetc(tmp_mv_list)) != EOF){//백업본에 원래꺼 복사
        // printf("%c", chch);
        fputc(chch, create_tmp_mv_list);
      }
      fclose(create_tmp_mv_list);

      if((mv_list = fopen("movie_list.txt", "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
      while(movie != NULL){//list 파일 작성
        fprintf(mv_list, "%d:%s:%s:%s:%d:%d:", movie -> Serial_number, movie -> title, movie -> genre, movie -> director.name, movie -> year, movie -> time);//list 저장
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

  }else if(isMovie_DIrector_Actor == 'D'){//director list 작성
    if((tmp_director_list = fopen("director_list.txt", "r")) == NULL){//director_list 가 없으면 list 파일 만들고 저장
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
    }else{//director_list 가 있으면
      FILE * create_tmp_director_list;
      char* time_string = now_time_string();//현재 날짜 시간 불러와서
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
      strcat(file_name, time_string);//백업본 이름 만들고
      if((create_tmp_director_list = fopen(file_name, "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
      char chch;
      while((chch=fgetc(tmp_director_list)) != EOF){//거기에 원래꺼 백업본에 복사함
        // printf("%c", chch);
        fputc(chch, create_tmp_director_list);
      }
      fclose(create_tmp_director_list);

      if((director_list = fopen("director_list.txt", "w")) == NULL){
        printf("File Open Error");
        exit(1);
      }
      while(director != NULL){//list 파일 작성
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

  }else if(isMovie_DIrector_Actor == 'A'){//actor_list 작성
    if((tmp_actor_list = fopen("actor_list.txt", "r")) == NULL){//actor_list 가 없으면 list 파일 만들고 list 작성
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
    }else{//list 파일 있으면
      FILE * create_tmp_actor_list;
      char* time_string = now_time_string();//현재 날짜 시간 받고
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
      while((chch=fgetc(tmp_actor_list)) != EOF){//원본꺼 복사해서 붙여넣기
        //printf("%c", chch);
        fputc(chch, create_tmp_actor_list);
      }
      fclose(create_tmp_actor_list);
      if((actor_list = fopen("actor_list.txt", "w")) == NULL){
        printf("actor_list in two File Open Error");
        exit(1);
      }
      while(actor != NULL){//list 파일 작성
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
void option_add_actor(ACTOR public_actor_ho){
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
  strcpy(actor -> name , colon_change(tmp_char));//콜론 채인지 적용해서 actor 구조체에 name 에 넣음

  ACTOR tmp_head_actor = public_actor_ho;
  int tmp_flag_for_overlap_check = 0;
  while(tmp_head_actor != NULL){//같은거 있는지 채크
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
      if(*(tmp_char+0) == 'y' || *(tmp_char+0) == 'Y'){//yes 면 그대로 저장 아니면 스탑
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
  printf("sex > ");
  gets(tmp_char);
  // director -> sex = (char*)malloc(sizeof(char)*strlen(tmp_char+5));
  // inMovie -> genre = colon_change(tmp_char);
  // strcpy(inMovie -> genre , colon_change(tmp_char));

  if(tmp_char[0] =='M'){//성별 bool 형으로 저장
    actor -> sex = true;
  }else{
    actor -> sex = false;
  }

  printf("birth > ");
  gets(tmp_char);
  actor -> birth = (char*)malloc(sizeof(char)*strlen(tmp_char)+5);//콜론 채인지 적용해서 actor 구조체에 birth 에 넣음
  // inMovie -> director.name = colon_change(tmp_char);
  strcpy(actor -> birth , colon_change(tmp_char));

  printf("best movie > ");
  gets(tmp_char);
  // printf("%s", tmp_char);
  // fseek(actor_log_read,0,SEEK_END);
  char* split = strtok(tmp_char, ",");
  MOVIE movie;
  movie = list_movie_director(split);//best_movie 추가해주는 함수 호출
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
  if(public_actor_ho == NULL){
    LastActor = NULL;
  }else{
    LastActor = serach_last_actor(public_actor_ho);//마지막거 찾음
  }
  if(LastActor == NULL){//아예 없으면 이걸 head 로함
    public_actor = actor;
    actor -> serial_number = 1;
  }else{
    LastActor -> actor_next = actor;
    actor -> serial_number = (LastActor -> serial_number) +1 ;
  }

  if(1){
    if(actor -> sex){//log 쓰기
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
  fprint_list_movie_director_actor('A', public_first_movie, public_director, public_actor);//list 쓰기
  link_actor_to_movie();//링크 걸기
}
ACTOR serach_last_actor(ACTOR public_actor){
  ACTOR actor = public_actor;
  while((actor -> actor_next) != NULL){
    actor = actor -> actor_next;
  }
  // printf("%d\n", actor -> serial_number);
  return actor;
}


int option_search_meta_search(char* string_orign, char* string_search){//서치 함수
  int string_search_length = strlen(string_search);
  int string_origin_length = strlen(string_orign);

  if(*(string_search+0) == '*'){//맨 앞에 * 있을때
    if(*(string_search+string_search_length-1) == '*'){//맨 뒤도 * 있을떄
      int tmp_string_length = string_search_length - 1;
      int last_flag = 0;
      int flag = 0;
      for(int i=1; i<tmp_string_length; i++){//두 문자열 비교하면서
        for(int j=0; j<string_origin_length; j++){
          if(*(string_orign+j) == *(string_search+i)){//같은거 있으면
            // printf("\n==\n%s     :      %s\n==\n", (string_orign+j), (string_search+i));
            int search_last_meta_cnt = tmp_string_length - 2;
            int origin_cnt = 0;
            for(int k=i; k<tmp_string_length-1; k++){//서치 함수 끝까지 돌면서 *바로 전까지 같으면 같은걸로 침
              if(*(string_search+k) == '?'){//'?'는 비교 안하고 넘어가면됨
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
    }else{//맨 앞에만 * 있을때
      // printf("ho?");
      int tmp_string_length = string_search_length;
      int last_flag = 0;
      int flag = 0;
      for(int i=1; i<tmp_string_length; i++){//문자 하나 하나 비교해서 같은거 나올떄까지 비교.
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
              for(z = 0; z< tmp_string_length; z++){//같은걸로 판별나있는데 여기서 문자열 개수가 안맞으면 예외이므로 여기서 채크해줌
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
  }else if(*(string_search+string_search_length-1) == '*'){//맨 뒤에만 * 있을떄
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
            if(z == tmp_string_length){//같은걸로 판별나있는데 여기서 문자열 개수가 안맞으면 예외이므로 여기서 채크해줌
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
    int tmp_string_length = string_search_length;//완벽히 같은거만 채크하면됨 ?표는 비교안하고 continue
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

int option_search_movie(struct movie* movie, char* search_string){//서치 함수 불러옴
  int flag = 0;//flag 에서 option_search_meta_search 리턴이 1이면 search 성공 이므로 1 일때 해당 구조체 출력해주면됨.
  int tmp_flag = 0;
  while(movie != NULL){
    int inWhile_tmp_flag = 0;//flag 에 search 성공여부 저장.
    tmp_flag = option_search_meta_search(movie -> title, search_string);
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    tmp_flag = option_search_meta_search(movie -> genre, search_string);//flag 에 search 성공여부 저장.
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    tmp_flag = option_search_meta_search(movie -> director.name, search_string);//flag 에 search 성공여부 저장.
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    struct linked_list_actor* actor = movie -> actor;
    while(actor != NULL){
      tmp_flag = option_search_meta_search(actor -> actor_name, search_string);//flag 에 search 성공여부 저장.
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
  int flag = 0;//flag 에서 option_search_meta_search 리턴이 1이면 search 성공 이므로 1 일때 해당 구조체 출력해주면됨.
  int tmp_flag = 0;
  while(director != NULL){
    int inWhile_tmp_flag = 0;
    tmp_flag = option_search_meta_search(director -> name, search_string);//flag 에 search 성공여부 저장.
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    tmp_flag = option_search_meta_search(director -> birth, search_string);//flag 에 search 성공여부 저장.
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    MOVIE movie_in_director = director -> movie;
    while(movie_in_director != NULL){
      tmp_flag = option_search_meta_search(movie_in_director -> title, search_string);//flag 에 search 성공여부 저장.
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
char* now_time_string(){//현재 시간 문자열로 만들어서 리턴해주는 함수
      time_t timer;
      struct tm *t_time;
      timer = time(NULL);
      t_time = localtime(&timer);
      char* time_string = (char*)malloc(sizeof(char)*100);
      sprintf(time_string, "%d", (t_time->tm_year+1900));
      if((t_time->tm_mon+1) < 10){
        *(time_string+1) = '0';
        time_string++;
        sprintf(time_string+strlen(time_string), "%d", (t_time->tm_mon+1));//sprintf 써서 정수형을 문자열로 바꿔줌
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
      return time_string;//날짜와 시간 합친 문자열 리턴
}

int option_search_actor(ACTOR actor, char* search_string){
  int flag = 0;//flag 에서 option_search_meta_search 리턴이 1이면 search 성공 이므로 1 일때 해당 구조체 출력해주면됨.
  int tmp_flag = 0;
  while(actor != NULL){
    int inWhile_tmp_flag = 0;
    tmp_flag = option_search_meta_search(actor -> name, search_string);//flag 에 search 성공여부 저장.
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    tmp_flag = option_search_meta_search(actor -> birth, search_string);//flag 에 search 성공여부 저장.
    if(inWhile_tmp_flag == 0){
      inWhile_tmp_flag = tmp_flag;
    }
    if(flag == 0){
      flag = tmp_flag;
    }
    MOVIE movie_in_actor = actor -> movie;
    while(movie_in_actor != NULL){
      tmp_flag = option_search_meta_search(movie_in_actor -> title, search_string);//flag 에 search 성공여부 저장.
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

 // 옵션 중 - 체크
  if(*option == '-')
  {
    strcpy(option, option+1);
  }

 // filename 있으면 변경
  if(option2 == NULL)
  {
    strcpy(filename, "movie_list.txt");
  }
  else
  {
    strcpy(filename, option2);
  }
  fp = fopen(filename, "w");

// 전체 옵션 실행
  if(!strcmp(option, "ALL COMMANDS"))
   {
      strcpy(option, "tgdyra");
   }

    while(strlen(option))
    {
      switch(*option)
      {
        // 옵션 t
        case 't' :
        if(size == 0)
        {
          // 파일이 비어 있을 경우 format 생성
          while(save_movie)
          {
            fprintf(fp ,"%d:%s:=:=:=:=:=\n", save_movie->Serial_number, save_movie->title);
            save_movie = save_movie->movie_next;
          }
        }
        // 파일이 비어 있지 않을 경우
        else
        {
          tmp = fopen(filename, "r");
          tmp_print = fopen("filename_list_tmp.txt", "w");

          movie_list_str = (char*)malloc(size + 100);

          while(fgets(movie_list_str, size, tmp))
          {
            size = ftell(tmp) + 1;
            *(movie_list_str+strlen(movie_list_str)-1) = '\0';

            // 콜론 위치 기준으로 데이터 삽입
            int collon_cnt = 0;
            for(int i = 0; i < strlen(movie_list_str); i++)
            {
              if(*(movie_list_str + i) == ':')
              {
                collon_cnt++;
              }
              // 콜론 위치 일치
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
        // 옵션 g
        case 'g' :
        if(size == 0)
        {
          // 파일이 비어 있는 경우 format 생성
          while(save_movie)
          {
            fprintf(fp ,"%d:=:%s:=:=:=:=\n", save_movie->Serial_number, save_movie->genre);
            save_movie = save_movie->movie_next;
          }
        }
        // 파일이 비어 있지 않은 경우 데이터 삽입
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
              // 콜론 체크하여 데이터 위치 결정
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
        // 옵션 d
        case 'd' :
        if(size == 0)
        {
          // 파일이 비어 있을 때 format 생성
          while(save_movie)
          {
            fprintf(fp ,"%d:=:=:%s:=:=:=\n", save_movie->Serial_number, save_movie->director.name);
            save_movie = save_movie->movie_next;
          }
        }
        // 파일이 비어 있지 않을 때 데이터 삽입
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
              // 콜론 위치가 일치하면 데이터 삽입
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
        // 옵션 y
        case 'y' :
        if(size == 0)
        {
          // 파일이 비어 있을 때 format 생성
          while(save_movie)
          {
            fprintf(fp ,"%d:=:=:=:%d:=:=\n", save_movie->Serial_number, save_movie->year);
            save_movie = save_movie->movie_next;
          }
        }
        // 파일이 비어 있지 않을 때 데이터 삽입
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
              // 콜론 개수가 일치하면 데이터 삽입
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
        // 옵션 r
        case 'r' :
        if(size == 0)
        {
          // 파일이 비어 있을 때 format 생성
          while(save_movie)
          {
            fprintf(fp ,"%d:=:=:=:=:%d:=\n", save_movie->Serial_number, save_movie->time);
            save_movie = save_movie->movie_next;
          }
        }
        // 파일이 비어 있지 않을 때 데이터 삽입
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
              // 콜론 개수가 일치하면 데이터 삽입
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
        // 옵션 a
        case 'a' :
        if(size == 0)
        {
          // 파일이 비어 있으면 format 생성
          while(save_movie)
          {
            struct linked_list_actor* actor_tmp = save_movie->actor;

            fprintf(fp ,"%d:=:=:=:=:=:%s", save_movie->Serial_number, save_movie->actor->actor_name);
            // actor 리스트 출력
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
        // 파일이 비어 있지 않으면 데이터 삽입
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
              //  콜론 개수 일치하면 데이터 삽입
              if(collon_cnt == 6)
              {
                struct linked_list_actor* actor_tmp = save_movie->actor;

                movie_list_str = insert_string(movie_list_str, save_movie->actor->actor_name, i+1);
                fprintf(tmp_print, "%s", movie_list_str);
                fflush(tmp_print);
                // actor 삽입
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
        // 존재 하지 않은 옵션
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
  // - 체크
  if(*option == '-')
  {
    strcpy(option, option+1);
  }
  // filename 체크
  if(option2 == NULL)
  {
    strcpy(filename, "director_list.txt");
  }
  else
  {
    strcpy(filename, option2);
  }
  fp = fopen(filename, "w");
  // 옵션 전체 실행
  if(!strcmp(option, "ALL COMMANDS"))
   {
      strcpy(option, "nsbm");
   }

    while(strlen(option))
    {
      switch(*option)
      {
        // 옵션 n
        case 'n' :
        if(size == 0)
        {
          // 파일이 비어 있다면 format 생성
          while(save_director)
          {
            fprintf(fp ,"%d:%s:=:=:=\n", save_director->serial_number, save_director->name);
            save_director = save_director->director_next;
          }
        }
        // 파일이 비어 있지 않다면 데이터 삽입
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
              // 콜론 개수 체크 일치하면 데이터 삽입
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
        // 옵션 s
        case 's' :
        if(size == 0)
        {
          // 파일이 비어 있다면 format 생성
          while(save_director)
          {
            fprintf(fp ,"%d:=:%c:=:=\n", save_director->serial_number, save_director->sex);
            save_director = save_director->director_next;
          }
        }
        // 파일이 비어 있지 않다면 데이터 삽입
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
              // 콜론 개수 일치하면 데이터 삽입
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
        // 옵션 b
        case 'b' :
        if(size == 0)
        {
          // 파일이 비어 있다면 format 생성
          while(save_director)
          {
            fprintf(fp ,"%d:=:=:%s:=\n", save_director->serial_number, save_director->birth);
            save_director = save_director->director_next;
          }
        }
        // 파일이 비어 있지 않다면 데이터 삽입
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
              // 콜론 개수 일치하면 데이터삽입
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
        // 옵션 m
        case 'm' :
        if(size == 0)
        {
          // 파일이 비어 있다면 format 생성
          while(save_director)
          {
            struct best_movie* movie_tmp = save_director->movie;

            fprintf(fp, "%d:=:=:=:%s", save_director->serial_number, save_director->movie->title);

            // best_movie 출력
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
        // 파일이 비어 있지 안다면 데이터 삽입
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
              // 콜론 개수 일치하면 데이터 삽입
              if(collon_cnt == 4)
              {
                struct best_movie* movie_tmp = save_director->movie;

                director_list_str = insert_string(director_list_str, save_director->movie->title, i+1);
                fprintf(tmp_print, "%s", director_list_str);
                fflush(tmp_print);
                // best movie 출력
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
        // 존재 하지 않는 옵션
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
  // - 체크
  if(*option == '-')
  {
    strcpy(option, option+1);
  }
  // filename 체크
  if(option2 == NULL)
  {
    strcpy(filename, "actor_list.txt");
  }
  else
  {
    strcpy(filename, option2);
  }
  fp = fopen(filename, "w");
  // 옵션 전체 실행
  if(!strcmp(option, "ALL COMMANDS"))
   {
      strcpy(option, "nsbm");
   }

    while(strlen(option))
    {
      switch(*option)
      {
        // 옵션 n
        case 'n' :
        if(size == 0)
        {
          // 파일이 비어 있다면 format 생성
          while(save_actor)
          {
            fprintf(fp ,"%d:%s:=:=:=\n", save_actor->serial_number, save_actor->name);
            save_actor = save_actor->actor_next;
          }
        }
        // 파일이 비어 있지 않다면 데이터 삽입
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
              // 콜론 개수 일치하면 데이터 삽입
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
        // 옵션 s
        case 's' :
        if(size == 0)
        {
          // 파일이 비어 있다면 format 생성
          while(save_actor)
          {
            char sex;
            // 성별 구분
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
        // 파일이 비어 있지 않다면 데이터 삽입
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
              // 콜론 개수 일치하면 데이터 삽입
              if(collon_cnt == 2)
              {
                // 성별 구분
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
        // 옵션 b
        case 'b' :
        if(size == 0)
        {
          // 파일이 비어 있다면 format 셍성
          while(save_actor)
          {
            fprintf(fp ,"%d:=:=:%s:=\n", save_actor->serial_number, save_actor->birth);
            save_actor = save_actor->actor_next;
          }
        }
        // 파일이 비어 있지 않다면 데이터 삽입
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
              // 콜론 개수 일치하면 데이터 삽입
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
        // 옵션 m
        case 'm' :
        if(size == 0)
        {
          // 파일이 비어 있다면 format 생성
          while(save_actor)
          {
            struct best_movie* movie_tmp = save_actor->movie;

            fprintf(fp, "%d:=:=:=:%s", save_actor->serial_number, save_actor->movie->title);
            // best movie 출력
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
        // 파일이 비어 있지 않다면 데이터 삽입
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
              // 콜론 개수 일치하면 데이터 삽입
              if(collon_cnt == 4)
              {
                struct best_movie* movie_tmp = save_actor->movie;

                actor_list_str = insert_string(actor_list_str, save_actor->movie->title, i+1);
                fprintf(tmp_print, "%s", actor_list_str);
                fflush(tmp_print);
                // best movie 출력
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
        // 존재 하지 않은 옵션
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
  // string 2개의 길이 합침
  size = strlen(origin) + strlen(insert) + 1;
  str = (char*)malloc(size + 100);
  strncpy(str, origin, pos);
  strcpy(origin, origin+pos+1);

  // string 2개 연결
  strcat(str, insert);
  strcat(str, origin);

  return str;
}

void colon_rchange(char *tmp_char){ // ??; => : 출력용
  int tmp_char_length = strlen(tmp_char)+1;
  for(int i=0; i<tmp_char_length; i++){
    if(*(tmp_char+i) == '?'){ // 문장을 한글자씩 출력하다 ??;가 있으면 : 출력 후 건너뜀
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

void colon_frchange(FILE* fm,char *tmp_char){ // ??; => : 파일출력용
  int tmp_char_length = strlen(tmp_char);
  for(int i=0; i<tmp_char_length; i++){
    if(*(tmp_char+i) == '?'){// 문장을 한글자씩 출력하다 ??;가 있으면 : 출력 후 건너뜀
      if(*(tmp_char+i+1) == '?'){
        if(*(tmp_char+i+2) == ';'){
          fprintf(fm,":");
          i += 3;
        }
      }
    }
    fprintf(fm,"%c",*(tmp_char+i));
  }
}

int cmp_actor_n(const void* a,const void* b)//배우 이름 기준 정렬
{
	ACTOR a_tmp=(ACTOR)a;
	ACTOR b_tmp=(ACTOR)b;

	return strcmp(a_tmp->name,b_tmp->name);
}


int cmp_actor_s(const void* a,const void* b)//배우 성별 기준 정렬
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

int cmp_actor_b(const void* a,const void* b)//배우 생년월일 기준 정렬
{
	ACTOR a_tmp=(ACTOR)a;
	ACTOR b_tmp=(ACTOR)b;

	return strcmp(a_tmp->birth,b_tmp->birth);
}


int cmp_actor_m(const void* a,const void* b)//배우 영화 기준 정렬
{
	ACTOR a_tmp=(ACTOR)a;
	ACTOR b_tmp=(ACTOR)b;

	return strcmp(a_tmp->movie->title,b_tmp->movie->title);
}

int cmp_director_n(const void* a,const void* b)//감독 이름 기준 정렬
{
	DIRECTOR a_tmp=(DIRECTOR)a;
	DIRECTOR b_tmp=(DIRECTOR)b;

	return strcmp(a_tmp->name,b_tmp->name);
}


int cmp_director_s(const void* a,const void* b)//감독 성별 기준 정렬
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

int cmp_director_b(const void* a,const void* b)//감독 생년월일 기준 정렬
{
	DIRECTOR a_tmp=(DIRECTOR)a;
	DIRECTOR b_tmp=(DIRECTOR)b;

	return strcmp(a_tmp->birth,b_tmp->birth);
}


int cmp_director_m(const void* a,const void* b)//감독 영화 기준 정렬
{
	DIRECTOR a_tmp=(DIRECTOR)a;
	DIRECTOR b_tmp=(DIRECTOR)b;

	return strcmp(a_tmp->movie->title,b_tmp->movie->title);
}

int cmp_movie_tt(const void* a,const void* b)//영화 제목 기준 정렬
{
	struct movie* a_tmp=(struct movie*)a;
	struct movie* b_tmp=(struct movie*)b;

	return strcmp(a_tmp->title,b_tmp->title);
}

int cmp_movie_g(const void* a,const void* b)//영화 장르 기준 정렬
{
  struct movie* a_tmp=(struct movie*)a;
	struct movie* b_tmp=(struct movie*)b;

	return strcmp(a_tmp->genre,b_tmp->genre);
}

int cmp_movie_d(const void* a,const void* b)//영화 감독 기준 정렬
{
  struct movie* a_tmp=(struct movie*)a;
	struct movie* b_tmp=(struct movie*)b;

	return strcmp(a_tmp->director.name,b_tmp->director.name);
}

int cmp_movie_y(const void* a,const void* b)//영화 년도 기준 정렬
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

int cmp_movie_r(const void* a,const void* b)//영화 시간 기준 정렬
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

int cmp_movie_a(const void* a,const void* b)//영화 배우 기준 정렬
{
  struct movie* a_tmp=(struct movie*)a;
	struct movie* b_tmp=(struct movie*)b;

	return strcmp(a_tmp->actor->actor_name,b_tmp->actor->actor_name);
}

void sort_actor(char option, ACTOR actor,char* option2)//actor 정렬 함수
{
  FILE *fm;
  if (option2!=NULL)
  {
    fm=fopen("filename_sort_tmp.txt","w");
  }

  if (option==0)//option내용이 비었을경우
    option='n';//이름 옵션으로 변경
	int n=count_actor_list(actor);//구조체 연결 수 확인
	ACTOR actor_tmp=actor;

	ACTOR sort_list=(ACTOR)malloc(sizeof(struct actor)*n);

	int cnt=0;

	while(actor_tmp->actor_next!=NULL)//연결된 리스트를 배열로 만듬
	{
		(*(sort_list+cnt))= *actor_tmp;
		cnt++;
		actor_tmp=actor_tmp->actor_next;
	}
	(*(sort_list+cnt))= *actor_tmp;

  //정렬
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
    if (option2==NULL)//파일 이름이 지정되지 않았을 경우
    {
  		printf("%d:%s:",(sort_list+i)->serial_number,(sort_list+i)->name);
  		if ((sort_list+i)->sex)
  			printf("M:");
  		else
  			printf("F:");
  		printf("%s:",(sort_list+i)->birth);
  		while((sort_list+i)->movie->movie_next!=NULL)
  		{
  			colon_rchange((sort_list+i)->movie->title);
        printf(", ");
  			(sort_list+i)->movie=(sort_list+i)->movie->movie_next;
  		}
  		colon_rchange((sort_list+i)->movie->title);
      printf("\n");
    }
    else//파일 이름이 지정되었을 경우
    {
      fprintf(fm,"%d:%s:",(sort_list+i)->serial_number,(sort_list+i)->name);

  		if ((sort_list+i)->sex)
  			fprintf(fm,"M:");
  		else
  			fprintf(fm,"F:");

  		fprintf(fm,"%s:",(sort_list+i)->birth);
  		while((sort_list+i)->movie->movie_next!=NULL)
  		{
  			colon_frchange(fm,(sort_list+i)->movie->title);
        fprintf(fm,", ");
  			(sort_list+i)->movie=(sort_list+i)->movie->movie_next;
  		}
  		colon_frchange(fm,(sort_list+i)->movie->title);
      fprintf(fm,"\n");
    }
	}

  fclose(fm);

  if (option2!=NULL)
  {
    char* opt2=(char*)malloc(sizeof(char)*100);
    strcpy(opt2,option2);
    rename("filename_sort_tmp.txt",opt2);
  }

	printf("Sort Complete!\n");

	free(sort_list);

}

void sort_director(char option, DIRECTOR director,char* option2)//director 정렬 함수
{
  FILE *fm;
  if (option2!=NULL)
  {
    fm=fopen("filename_sort_tmp.txt","w");
  }

  if (option==0)//옵션이 들어오지 않았을 경우
    option='n';//이름 옵션으로 변경
  int cnt=0;
	int n=count_director_list(director);//구조체 연결 수 확인
	DIRECTOR director_tmp=director;

	DIRECTOR sort_list=(DIRECTOR)malloc(sizeof(struct director)*n);

	while(director_tmp->director_next!=NULL)//연결된 리스트를 배열로 만듬
	{
		(*(sort_list+cnt))=*director_tmp;
		cnt++;
    director_tmp=director_tmp->director_next;
	}
	(*(sort_list+cnt))=*director_tmp;

  //정렬
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
      if (option2==NULL)//파일 이름이 지정되지 않았을 경우
      {
    		printf("%d:%s:",(sort_list+i)->serial_number,(sort_list+i)->name);
        printf("%c:",(sort_list+i)->sex);
    		printf("%s:",(sort_list+i)->birth);
    		while((sort_list+i)->movie->movie_next!=NULL)
    		{
          colon_rchange((sort_list+i)->movie->title);
          printf(", ");
    			(sort_list+i)->movie=(sort_list+i)->movie->movie_next;
    		}
    		colon_rchange((sort_list+i)->movie->title);
        printf("\n");
      }
      else//파일 이름이 지정되었을 경우
      {

        fprintf(fm,"%d:%s:",(sort_list+i)->serial_number,(sort_list+i)->name);
    		fprintf(fm,"%c:",(sort_list+i)->sex);
    		fprintf(fm,"%s:",(sort_list+i)->birth);
    		while((sort_list+i)->movie->movie_next!=NULL)
    		{
          colon_frchange(fm,(sort_list+i)->movie->title);
          fprintf(fm,", ");
    			(sort_list+i)->movie=(sort_list+i)->movie->movie_next;
    		}
        colon_frchange(fm,(sort_list+i)->movie->title);
        fprintf(fm,"\n");
      }
  	}

    fclose(fm);

    if (option2!=NULL)
    {
      char* opt2=(char*)malloc(sizeof(char)*100);
      strcpy(opt2,option2);
      rename("filename_sort_tmp.txt",opt2);
    }

  	printf("Sort Complete!\n");

  	free(sort_list);

}

void sort_movie(char option, struct movie* movie,char* option2)//movie 정렬 함수
{
  if (option==0)//옵션이 들어오지 않았을 경우
    option='t';//제목 옵션으로 변경
  int cnt=0;
	int n=count_movie_list(movie);//연결된 리스트 수 확인
	struct movie* movie_tmp=movie;
	struct movie* sort_list=(struct movie*)malloc(sizeof(struct movie)*n);

  FILE *fm;
  if (option2!=NULL)
  {
    fm=fopen("filename_sort_tmp.txt","w");
  }

	while(movie_tmp->movie_next!=NULL)//연결된 리스트를 배열로 만듬
	{
		(*(sort_list+cnt))=(*movie_tmp);
		cnt++;
    movie_tmp=movie_tmp->movie_next;
	}
	(*(sort_list+cnt))=(*movie_tmp);

  //정렬
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
      if (option2==NULL)//파일 이름이 지정되지 않았을 경우
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
      else//파일 이름이 지정되었을 경우
      {
        fprintf(fm,"%d:%s:",(sort_list+i)->Serial_number,(sort_list+i)->title);
        fprintf(fm,"%s:",(sort_list+i)->genre);
    		fprintf(fm,"%s:",(sort_list+i)->director.name);
        fprintf(fm,"%d:%d:",(sort_list+i)->year,(sort_list+i)->time);
    		while((sort_list+i)->actor->actor_next!=NULL)
    		{
    			fprintf(fm,"%s,",(sort_list+i)->actor->actor_name);
    			(sort_list+i)->actor=(sort_list+i)->actor->actor_next;
    		}
    		fprintf(fm,"%s\n",(sort_list+i)->actor->actor_name);
      }
  	}

    fclose(fm);
    if (option2!=NULL)
    {
      char* opt2=(char*)malloc(sizeof(char)*100);
      strcpy(opt2,option2);
      rename("filename_sort_tmp.txt",opt2);
    }


  	printf("Sort Complete!\n");

  	free(sort_list);

}

int count_actor_list(ACTOR actor)//연결된 actor 리스트 수 확인
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

int count_director_list(DIRECTOR director)//연결된 director 리스트 수 확인
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

int count_movie_list(struct movie* movie)//연결된 movie 리스트 수 확인
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

void option_delete_actor(int num,ACTOR actor,bool from_where)//actor 삭제 함수
{
  ACTOR actor_tmp=actor;
  ACTOR actor_tmp2=actor;
  bool break_flag=false;
  ACTOR actor_next_tmp;
  ACTOR public_actor_next_tmp;
  int n=count_actor_list(actor);//연결된 리스트 수 확인
  int cnt=0;
  struct best_movie* movie_next_tmp;

  while (actor_tmp->actor_next!=NULL)
  {
    if (actor_tmp->serial_number==num)//삭제할 시리얼 넘버가 있는지 확인
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

  if (break_flag)//시리얼 넘버가 있을경우
  {
    if (cnt==0 && n!=1)//2명 이상의 배우가 존재하는 상태에서 첫 번째 배우를 지울경우
    {
      //public_actor 구조체를 수정함
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
    else if (cnt==0 && n==1)//배우가 1명 존재할 경우
    {
      //public_actor 구조체에 NULL값을 넣음
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
    else//2명 이상의 배우가 존재하고 첫 번째가 아닌 배우를 지울경우
    {
      //이전 구조체와 다음 구조체를 연결해줌
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

    link_actor_to_movie();//변경 사항을 movie 구조체에 연결

    printf("Delete Complete!\n");

    if (!from_where)//명령어로 들어왔을 경우
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

void option_delete_director(int num,DIRECTOR director,bool from_where)//director 삭제 함수
{
  DIRECTOR director_tmp=director;
  DIRECTOR director_tmp2=director;
  bool break_flag=false;
  DIRECTOR director_next_tmp;
  DIRECTOR public_director_next_tmp;
  int n=count_director_list(director);//연결된 리스트 수 확인
  int cnt=0;
  struct best_movie* movie_next_tmp;

  while (director_tmp->director_next!=NULL)
  {
    if (director_tmp->serial_number==num)//삭제할 시리얼 넘버가 있는지 확인
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

  if (break_flag)//시리얼 넙버가 있을경우
  {
    if (cnt==0 && n!=1)//2명 이상의 감독이 존재하는 상태에서 첫 번째 감독을 지울경우
    {
      //public_director 구조체를 수정함
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
    else if (cnt==0 && n==1)//감독이 1명 존재할 경우
    {
      //public_director 구조체에 NULL값을 넣음
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
    else//2명 이상의 감독이 존재하고 첫 번째가 아닌 감독을 지울경우
    {
      //이전 구조체와 다음 구조체를 연결해줌
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

    link_director_to_movie();//변경 사항을 movie 구조체에 연결

    printf("Delete Complete!\n");

    if (!from_where)//명령어로 들어왔을 경우
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

void option_delete_movie(int num,struct movie* movie,bool from_where)//movie 삭제 함수
{
  struct movie* movie_tmp=movie;
  struct movie* movie_tmp2=movie;
  bool break_flag=false;
  struct movie* movie_next_tmp;
  struct movie* public_first_movie_next_tmp;
  int n=count_movie_list(movie);//연결된 리스트 수 확인
  int cnt=0;
  struct linked_list_actor* actor_next_tmp;

  while (movie_tmp->movie_next!=NULL)
  {
    if (movie_tmp->Serial_number==num)//삭제할 시리얼 넘버가 존재하는지 확인
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

  if (break_flag)//삭제할 시리얼 넘버가 존재할 경우
  {
    if (cnt==0 && n!=1)//2편 이상의 영화가 존재하는 상태에서 첫 번째 영화를 지울경우
    {
      //public_first_movie 구조체를 수정함
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
    else if (cnt==0 && n==1)//영화가 1편 존재할 경우
    {
      //public_first_movie 구조체에 NULL값을 넣음
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
    else//2편 이상의 영화가 존재하고 첫 번째가 아닌 영화를 지울경우
    {
      //이전 구조체와 다음 구조체를 연결해줌
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

    lint_movie_to_actor(public_actor,public_first_movie);//변경 사항을 actor 구조체와 연결
    lint_movie_to_director(public_director,public_first_movie);//변경 사항을 director 구조체와 연결

    printf("Delete Complete!\n");

    if (!from_where)//명령어로 들어왔을 경우
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
