#include "director.h"
#include "movie.h"

void init_director()
{
  DIRECTOR director = NULL;
  MOVIE movie = NULL;

  FILE *list, *log;

  char *line;
  int size;

 // 파일 에러 체크
  if((log = fopen("director_log.txt", "r+")) == NULL)
  {
    printf("FILE ERROR");
    exit(-1);
  }

// 파일 에러 체크
  if((list = fopen("director_list.txt", "w")) == NULL)
  {
    printf("FILE ERROR");
    exit(-1);
  }

// 파일 사이즈
  fseek(log, SEEK_SET, SEEK_END);
  size = ftell(log);
  line = (char*)malloc(size+3);
  fseek(log, 0, SEEK_SET);

// log 파일에서 한 줄씩 읽어 들임
  while(fgets(line, size, log))
  {
    if(strlen(line) != 1)
    {
      DIRECTOR director_tmp;
      MOVIE movie_tmp;
      char *split, *origin;
      char *tag, *serial_number, *name, *sex, *birth, *title;
      int serial_number_integer;
      // 읽어 들인 문장
      origin = (char*)malloc(size+3);
      strcpy(origin, line);

      // tag
      split = strtok(line, ":");
      tag = (char*)malloc(strlen(split)+3);
      strcpy(tag, split);

      // serial_number
      split = strtok(NULL, ":");
      serial_number = (char*)malloc(strlen(split)+3);
      strcpy(serial_number, split);
      serial_number_integer = atoi(serial_number);

      // tag 체크
      if(!strcmp(tag, "add"))
      {
        add_list_director(list, origin+4);

        // name
        split = strtok(NULL, ":");
        name = (char*)malloc(strlen(split)+3);
        strcpy(name, split);

        // sex
        split = strtok(NULL, ":");
        sex = (char*)malloc(strlen(split)+3);
        strcpy(sex, split);

        // birth
        split = strtok(NULL, ":");
        birth = (char*)malloc(strlen(split)+3);
        strcpy(birth, split);

        // title
        split = strtok(NULL, ":");
        title = (char*)malloc(strlen(split)+3);
        strcpy(title, split);
        *(title + strlen(title) - 1) = '\0';

        // title
        split = strtok(title, ",\n");

        // best movie 구조체 생성
        if(movie == NULL)
        {
          movie = list_movie_director(split);
        }
        while(split = strtok(NULL, ",\n"))
        {
          strcpy(split, split+1);

          movie_tmp = list_movie_director(split);
          movie = put_list_movie_director(movie, movie_tmp);
        }

        // director 구조체 생성
        if(director == NULL)
        {
          director = list_director(serial_number, name, sex, birth, movie);
        }
        else
        {
          director_tmp = list_director(serial_number, name, sex, birth, movie);
          director = put_list_director(director, director_tmp);
        }
      }
      // delete tag
      else if(!strcmp(tag, "delete"))
      {
        DIRECTOR delete_director = director;
        option_delete_director(serial_number_integer, delete_director, true);
        continue;
      }
      // update tag
      else if(!strcmp(tag, "update"))
      {
        DIRECTOR update_director = director;
        MOVIE update_movie;
        update_director = move_serial_director(serial_number_integer, update_director);
        update_movie = update_director->movie;

        // name
        split = strtok(NULL, ":");
        name = (char*)malloc(strlen(split)+3);
        strcpy(name, split);
        // =이 아닐 때 update
        if(strcmp(name, "="))
        {
          free(update_director->name);
          update_director->name= (char*)malloc(strlen(name)+3);
          strcpy(update_director->name, name);
        }

        // sex
        split = strtok(NULL, ":");
        sex = (char*)malloc(strlen(split)+3);
        strcpy(sex, split);
        // =이 아닐 때 update
        if(*sex != '=')
        {
          update_director->sex = *sex;
        }

        // birth
        split = strtok(NULL, ":");
        birth = (char*)malloc(strlen(split)+3);
        strcpy(birth, split);
        // =이 아닐 때 update
        if(strcmp(birth, "="))
        {
          free(update_director->birth);
          update_director->birth= (char*)malloc(strlen(birth)+3);
          strcpy(update_director->birth, birth);
        }

        // title
        split = strtok(NULL, ":");
        title = (char*)malloc(strlen(split)+3);
        strcpy(title, split);
        *(title + strlen(title) - 1) = '\0';

        // best movie가 1개 일때 continue
        if(!strlen(title))
        {
          continue;
        }
        // best movie가 여러 개 일때 update
        else
        {
          split = strtok(title, ",\n");
          update_movie = list_movie_director(split);
          while(split = strtok(NULL, ",\n"))
          {
            MOVIE update_movie_next = NULL;
            strcpy(split, split+1);
            update_movie_next = list_movie_director(split);
            update_movie = put_list_movie_director(update_movie, update_movie_next);

            update_director = list_director(serial_number, name, sex, birth, update_movie);
          }
        }
        continue;
      }

      // best movie 초기화
      movie = NULL;

      // free
      free(tag);
      free(origin);
      free(serial_number);
      free(sex);
      free(name);
      free(birth);
      free(title);
    }
  }
  fclose(log);
  fclose(list);

  public_director = director;

  free(line);
}

void add_list_director(FILE *list, char* origin)
{
  // list 파일 생성
  fprintf(list, "%s", origin);
}

MOVIE list_movie_director(char* title){
   MOVIE movie;

   // best movie가 비어 있을 때
   if(movie == NULL)
   {
     return NULL;
   }
   // best movie가 비어 있지 않을 때
   else
   {
      movie = (MOVIE)malloc(sizeof(struct best_movie));
      movie->title = (char*)malloc(strlen(title)+5);
      strcpy(movie->title, colon_change(title));
      movie->movie_link = NULL;
      movie->movie_next = NULL;

      return movie;
   }
}

DIRECTOR list_director(char* serial_number, char* name, char* sex, char* birth, MOVIE movie){
   DIRECTOR director;

   // director가 비어 있을 때
   if(director == NULL)
   {
     return NULL;
   }
   // director가 비어 있지 않을 때
   else
   {
      director = (DIRECTOR)malloc(sizeof(struct director));
      director->name = (char*)malloc(strlen(name)+3);
      director->birth = (char*)malloc(strlen(birth)+3);

      director->serial_number = atoi(serial_number);
      director->sex = *sex;
      strcpy(director->name, name);
      strcpy(director->birth, birth);
      director->movie = movie;
      director->director_next = NULL;

      return director;
   }
}

MOVIE put_list_movie_director(MOVIE origin, MOVIE tmp){
  MOVIE new;
  new = origin;
  // best movie의 노드 값을 마지막 값으로 변경
  while(new->movie_next != NULL)
  {
    new = new->movie_next;
  }
  // 마지막 노드에 삽입
  new->movie_next = tmp;

  return origin;
}

DIRECTOR put_list_director(DIRECTOR origin, DIRECTOR tmp){
  DIRECTOR new;
  new = origin;
 // director 노드 값을 마지막 값으로 변경
  while(new->director_next != NULL)
  {
    new = new->director_next;
  }
  // 마지막 노드에 삽입
  new->director_next = tmp;

  return origin;
}

void print_movie_director(MOVIE movie){
   if(movie == NULL)
   {
     printf("NULL\n");
   }
   else
   {
      printf("%s->", movie->title);
      print_movie_director(movie->movie_next);
   }
}

void print_director(DIRECTOR director){
   if(director == NULL)
   {
     printf("NULL \n");
   }
   else
   {
      printf("%d / ", director->serial_number);
      printf("%s / ", director->name);
      printf("%c / ", director->sex);
      printf("%s / movie_list -> ", director->birth);
      print_director(director->director_next);
   }
}

struct movie* search_director_to_movie_title(char* title)
{
  struct movie* LINK = public_first_movie;

  // movie 구조체와 일치하는 title 값을 검색
  while(LINK != NULL)
  {
    if(!strcmp(title, LINK->title))
    {
      return LINK;
    }

    LINK = LINK->movie_next;
  }

  return NULL;
}

int search_director_to_movie(DIRECTOR tmp)
{
  struct movie* result = NULL;
  struct best_movie* BEST_MOVIE = tmp->movie;

  // best movie에서 movie 연결
  while(BEST_MOVIE != NULL)
  {
    result = search_director_to_movie_title(BEST_MOVIE->title);
    if(result != NULL)
    {
      BEST_MOVIE->movie_link = result;
      return 1;
    }
    BEST_MOVIE = BEST_MOVIE->movie_next;
  }

  return 0;
}

void link_director_to_movie()
{
  DIRECTOR tmp = public_director;
  int result;

  // movie 구조체의 title 값과 일치하는 director를 검색
  while(tmp != NULL)
  {
    result = search_director_to_movie(tmp);

    if(result)
    {
      break;
    }

    tmp = tmp->director_next;
  }
}
