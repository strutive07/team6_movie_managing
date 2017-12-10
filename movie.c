#include "movie.h"

//함수
void init_movie(){//movie 초기화

  int file_size;
  char *buffer;
  if((mv_log_read = fopen("movie_log.txt", "r")) == NULL){
    printf("File Open Error");
    exit(1);
  }
  if((mv_log_add = fopen("movie_log.txt", "a")) == NULL){
    printf("File Open Error");
    exit(1);
  }
  // if((mv_list = fopen("movie_list.txt", "w")) == NULL){
  //   printf("File Open Error");
  //   exit(1);
  // }
  char *one_line = (char*)malloc(sizeof(char)*200);
  int main_isFirst = 1;
  while(fgets(one_line, 200, mv_log_read) != NULL){//log 파일에서 한줄씩 읽음
    printf("%s", one_line);
    if(main_isFirst == 1){
      public_first_movie = parse_movie(one_line, main_isFirst);//head 에 연결해줌. 첫번쨰꺼는 무조건 add 일태니까 오류날수 없음
      main_isFirst = 0;
    }else{
      parse_movie(one_line, main_isFirst);//계속 자르면서 구조체 수정, 추가. 삭제 함.
    }
  }
  // add_movie(public_first_movie, mv_log_add, mv_log_read);
  fclose(mv_log_read);
  fclose(mv_log_add);
  // fclose(mv_list);
}
struct director* search_director_in_movie(DIRECTOR argument_director, char* argument_name){//link 를 걸기위한 함수. director 에서 같은 감독 이름 찾음
  while(argument_director != NULL){
    // printf("%s %s\n", argument_director -> name, argument_name);
    if(!strcmp(argument_director -> name, argument_name)){
      return argument_director;
    }else{
      argument_director = argument_director -> director_next;
    }
  }
  return NULL;
}

void lint_movie_to_director(DIRECTOR argument_director, struct movie* argument_movie){//director 에서 name 과 movie 의  director name 이 같으면 링크해주는 함수
  while(argument_movie != NULL){
    argument_movie -> director.director_pointer = search_director_in_movie(argument_director, argument_movie -> director.name);
    if(argument_movie -> director.director_pointer != NULL){
    }
    argument_movie = argument_movie -> movie_next;
  }
}

//================================

struct actor* search_actor_in_movie(ACTOR argument_actor, char* argument_actor_name){//link 를 걸기위한 함수. actor 에서 같은 감독 이름 찾음
  // printf("%s", argument_actor -> name);
  while(argument_actor != NULL){
    // printf("%s %s\n", argument_actor -> name, argument_actor_name);
    if(!strcmp(argument_actor -> name, argument_actor_name)){
      return argument_actor;
    }else{
      argument_actor = argument_actor -> actor_next;
    }
  }
  // printf("\n\n");
  return NULL;
}

void lint_movie_to_actor(ACTOR argument_actor, struct movie* argument_movie){//actor 에서 name 과 movie 의  actor name 이 같으면 링크해주는 함수
  while(argument_movie != NULL){
    struct linked_list_actor* actor = argument_movie -> actor;
    while(actor != NULL){
      actor -> actor_pointer = search_actor_in_movie(argument_actor, actor -> actor_name);
      actor = actor -> actor_next;
    }
    argument_movie = argument_movie -> movie_next;
  }
}

//================================


struct linked_list_actor *create_actor_struct(char * actor_parse){//movie 에서 actor , 기준으로 잘라서 구조체에 저장해주는 함수. 리턴은 가장 첫번쨰 구조체의 주소.
  char *p;
  p=strtok(actor_parse,",\n");
  struct linked_list_actor *actor = malloc(sizeof(struct linked_list_actor));
  actor -> actor_name = (char*)malloc(sizeof(char)*strlen(p+5));
  // actor -> actor_name = colon_change(p);
    strcpy(actor -> actor_name, colon_change(p));


  actor -> actor_next = NULL;
  struct linked_list_actor *Tmp_Actor_pointer = actor;
  while((p=strtok(NULL,",\n"))!=NULL){
    if(*p+0 == ' '){
      strcpy(p, p+1);
    }
    struct linked_list_actor *next_actor = malloc(sizeof(struct linked_list_actor));
    next_actor -> actor_name = (char*)malloc(sizeof(char)*strlen(p+5));
    // next_actor -> actor_name = colon_change(p);
    strcpy(next_actor -> actor_name, colon_change(p));

    next_actor -> actor_next = NULL;
    Tmp_Actor_pointer -> actor_next = next_actor;
    Tmp_Actor_pointer = next_actor;
  }
  return actor;
}

struct movie *parse_movie(char* buffer, int isFirst){//한줄씩 받아서 add update delete 처리해주는 함수
  char* parse_char;
  parse_char = strtok(buffer,":");//: 기준으로 자름
  if(!strcmp(parse_char, "add")){//add 처리
    struct movie *next_movie_tmp_pointer;
    struct movie *inMovie;
    parse_char = strtok(NULL,":");
    inMovie = malloc(sizeof(struct movie));
    inMovie -> Serial_number = atoi(parse_char);
    parse_char = strtok(NULL,":\n,");
    inMovie -> title = (char*)malloc(sizeof(char)*strlen(parse_char));
    strcpy(inMovie -> title, parse_char);
    parse_char = strtok(NULL,":\n,");
    inMovie -> genre = (char*)malloc(sizeof(char)*strlen(parse_char));
    strcpy(inMovie -> genre, parse_char);
    parse_char = strtok(NULL,":\n,");
    inMovie -> director.name = (char*)malloc(sizeof(char)*strlen(parse_char));
    strcpy(inMovie -> director.name, parse_char);
    inMovie -> director.director_pointer = NULL;
    parse_char = strtok(NULL,":\n,");
    inMovie -> year = atoi(parse_char);
    parse_char = strtok(NULL,":\n,");
    inMovie -> time = atoi(parse_char);
    parse_char = strtok(NULL,":\n");
    char* actor_parse = (char*)malloc(sizeof(char)*strlen(parse_char));
    strcpy(actor_parse,parse_char);
    if(isFirst){//처음꺼면 head 에 연결해줌.
      inMovie -> movie_next = NULL;
      public_next_movie = inMovie;
    }else{
      inMovie -> movie_next = NULL;
      public_next_movie -> movie_next = inMovie;
      public_next_movie = inMovie;
    }
    inMovie -> actor = create_actor_struct(actor_parse);
    return inMovie;
  }else if(!strcmp(parse_char, "update")){//update 처리
    struct movie *movies = public_first_movie;
    parse_char = strtok(NULL,":");
    int serial_num = atoi(parse_char);
    if(serial_num != 1){
      movies = move_serial_movie(serial_num, movies);
    }
    if(movies == NULL){
      printf("No Such Record while loading movie_log.txt\n");
      exit(1);
    }
    parse_char = strtok(NULL,":");
    if(strlen(parse_char) == 0){

    }else if(strlen(parse_char) == 1 && *(parse_char+0) == '='){//콜론사이가 비어있거나 = 만 있으면 update 안하는거로 인식함.

    }else{
      free(movies -> title);
      movies -> title = (char*)malloc(strlen(parse_char)+5);
      strcpy(movies -> title, colon_change(parse_char));
    }
    parse_char = strtok(NULL,":");
    if(strlen(parse_char) == 0){

    }else if(strlen(parse_char) == 1 && *(parse_char+0) == '='){

    }else{
      free(movies -> genre);
      movies -> genre = (char*)malloc(strlen(parse_char)+5);
      strcpy(movies -> genre, colon_change(parse_char));
    }
    parse_char = strtok(NULL,":");
    if(strlen(parse_char) == 0){

    }else if(strlen(parse_char) == 1 && *(parse_char+0) == '='){

    }else{
      free(movies -> director.name);
      movies -> director.name = (char*)malloc(strlen(parse_char)+5);
      strcpy(movies -> director.name, colon_change(parse_char));
    }
    parse_char = strtok(NULL,":");
    if(strlen(parse_char) == 0){

    }else if(strlen(parse_char) == 1 && *(parse_char+0) == '='){

    }else{
      movies -> year = atoi(parse_char);
    }
    parse_char = strtok(NULL,":");
    if(strlen(parse_char) == 0){

    }else if(strlen(parse_char) == 1 && *(parse_char+0) == '='){

    }else{
      movies -> time = atoi(parse_char);
    }
    parse_char = strtok(NULL,":");

    movies -> actor = create_actor_struct(parse_char);
  }else if(!strcmp(parse_char, "delete")){//delete 처리
    parse_char = strtok(NULL,":");
    int serial_num = atoi(parse_char);
    option_delete_movie(serial_num, public_first_movie, true);
  }
}
char* colon_change(char* tmp_char){//   :   ->   ??;   로 변환해주는 함수
  if(strchr(tmp_char, ':') != NULL){
    int total_size = strlen(tmp_char);
    char *check_colon = strchr(tmp_char, ':');
    char *inserted_char;
    while(check_colon != NULL){//콜론 개수 채크
      total_size += 2;//콜론 있으면 콜론 하나당 문자열 2씩 증가하므로 2증가시켜줌
      check_colon = strchr(check_colon+1, ':');//다음 콜론 탐색
    }
    inserted_char = (char*)malloc(sizeof(char)*total_size+1);
    strcpy(inserted_char, tmp_char);
		for (int i = total_size - 1 ; i >= 0 ; i--) {
			if (*(inserted_char + i) == ':') {//콜론을 찾으면
				for (int j = total_size; j > i; j--) {//콜론 전까지 꺼 다 2칸씩 뒤로 밀고
					*(inserted_char + j + 2) = *(inserted_char + j);
				}
				*(inserted_char + i) = '?';//??; 대입
				*(inserted_char + i + 1) = '?';
				*(inserted_char + i + 2) = ';';
			}
		}
    return inserted_char;
  }else{
    return tmp_char;
  }
}

void update_movie(struct movie* movie, FILE *mv_log){

}

struct movie *search_last_movie(struct movie *movie){//마지막꺼 movie 탐색. movie 구조체가 없으면 NULL 반환하고 있으면 마지막 movie 구조체 주소 반환.
  if(movie == NULL){
    return NULL;
  }
  while((movie -> movie_next)!=NULL){
    movie = movie -> movie_next;
  }
  return movie;
}
