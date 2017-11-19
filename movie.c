#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//전역 변수
struct movie *public_next_movie;
struct movie *public_first_movie;
//구조체
struct linked_list_actor{
  char* actor_name;
  struct linked_list_actor *actor_next;
  struct actor *actor_pointer;
};

struct director_in_movie{
  char* name;
  struct director *director_pointer;
};

struct movie{
  int Serial_number;
  char* title;
  char* genre;
  struct director_in_movie director;
  int year;
  int time;
  struct linked_list_actor *actor;
  struct movie *movie_next;
};

struct director{
  int Serial_number;
};
struct actor{
  int Serial_number;
};

//함수 원형
void print_actor(struct linked_list_actor *actor);
void print_movie(struct movie *movie, FILE* mv_log_write);
struct linked_list_actor *create_actor_struct(char * actor_parse);
struct movie *parse_movie(char* buffer, int isFirst);
void add_movie(struct movie *movie, FILE *mv_log_write, FILE *mv_log_read);
struct movie *search_last_movie(struct movie *movie);
void update_movie(struct movie* movie, FILE *mv_log);
//함수
struct linked_list_actor *create_actor_struct(char * actor_parse){
  char *p;
  p=strtok(actor_parse,",");
  struct linked_list_actor *actor = malloc(sizeof(struct linked_list_actor));
  actor -> actor_name = (char*)malloc(sizeof(char)*strlen(p));
  strcpy(actor -> actor_name, p);
  actor -> actor_next = NULL;
  struct linked_list_actor *Tmp_Actor_pointer = actor;
  while((p=strtok(NULL,","))!=NULL){
    struct linked_list_actor *next_actor = malloc(sizeof(struct linked_list_actor));
    next_actor -> actor_name = (char*)malloc(sizeof(char)*strlen(p));
    strcpy(next_actor -> actor_name, p);

    next_actor -> actor_next = NULL;
    Tmp_Actor_pointer -> actor_next = next_actor;
    Tmp_Actor_pointer = next_actor;
  }
  return actor;
}

struct movie *parse_movie(char* buffer, int isFirst){
  char* parse_char;
  parse_char = strtok(buffer,":");
  if(!strcmp(parse_char, "add")){
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
    //그리고 여기 director 탐생해서 director 같은 이름 strcmp 로 검색한후 있으면 그 구조체의 주소 inMovie -> director.director_pointer 에 대입
    parse_char = strtok(NULL,":\n,");
    inMovie -> year = atoi(parse_char);
    parse_char = strtok(NULL,":\n,");
    inMovie -> time = atoi(parse_char);
    parse_char = strtok(NULL,":\n");
    char* actor_parse = (char*)malloc(sizeof(char)*strlen(parse_char));
    strcpy(actor_parse,parse_char);
    if(isFirst){
      inMovie -> movie_next = NULL;
      public_next_movie = inMovie;
    }else{
      inMovie -> movie_next = NULL;
      public_next_movie -> movie_next = inMovie;
      public_next_movie = inMovie;
    }
    inMovie -> actor = create_actor_struct(actor_parse);
    return inMovie;
  }else if(!strcmp(parse_char, "update")){

  }else if(!strcmp(parse_char, "delete")){

  }

}
void add_movie(struct movie *movie, FILE *mv_log_write, FILE *mv_log_read){
  struct movie *inMovie;
  struct movie *lastMovie;
  int text_size = 0;
  inMovie = malloc(sizeof(struct movie));
  char* tmp_char = (char*)malloc(sizeof(char)*100);
  printf("title > ");
  gets(tmp_char);
  inMovie -> title = (char*)malloc(sizeof(char)*strlen(tmp_char));
  strcpy(inMovie -> title , tmp_char);
  printf("genre > ");
  gets(tmp_char);
  inMovie -> genre = (char*)malloc(sizeof(char)*strlen(tmp_char));
  strcpy(inMovie -> genre , tmp_char);
  printf("director > ");
  gets(tmp_char);
  inMovie -> director.name = (char*)malloc(sizeof(char)*strlen(tmp_char));
  strcpy(inMovie -> director.name , tmp_char);
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
  if(file_size){
    fprintf(mv_log_write, "\nadd:%d:%s:%s:%s:%d:%d:%s", inMovie -> Serial_number, inMovie -> title, inMovie -> genre, inMovie -> director.name, inMovie -> year, inMovie -> time, tmp_char);
  }else{
    fprintf(mv_log_write, "add:%d:%s:%s:%s:%d:%d:%s", inMovie -> Serial_number, inMovie -> title, inMovie -> genre, inMovie -> director.name, inMovie -> year, inMovie -> time, tmp_char);
  }
  inMovie -> actor = create_actor_struct(tmp_char);
  free(tmp_char);
}
void update_movie(struct movie* movie, FILE *mv_log){

}
void print_movie(struct movie *movie, FILE* mv_list){
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
}
struct movie *search_last_movie(struct movie *movie){
  while((movie -> movie_next)!=NULL){
    movie = movie -> movie_next;
  }
  return movie;
}
int main(){
  FILE *mv_log_read,*mv_log_add, *mv_list;
  int file_size;
  char *buffer;
  if((mv_log_read = fopen("movie_log.txt", "r")) == NULL){
    printf("File Open Error");
    return 1;
  }
  if((mv_log_add = fopen("movie_log.txt", "a")) == NULL){
    printf("File Open Error");
    return 1;
  }
  if((mv_list = fopen("movie_list.txt", "w")) == NULL){
    printf("File Open Error");
    return 1;
  }
  char *one_line = (char*)malloc(sizeof(char)*200);
  int main_isFirst = 1;
  while(fgets(one_line, 200, mv_log_read) != NULL){
    printf("%s", one_line);
    if(main_isFirst == 1){
      public_first_movie = parse_movie(one_line, main_isFirst);
      main_isFirst = 0;
    }else{
      parse_movie(one_line, main_isFirst);
    }
  }
  printf("\n==\n");
  add_movie(public_first_movie, mv_log_add, mv_log_read);
  print_movie(public_first_movie,mv_list);
  fclose(mv_log_read);
  fclose(mv_log_add);
  fclose(mv_list);
  return 0;
}
