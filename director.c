#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct best_movie{
  char *title;
  struct best_movie *movie_next;
};

struct director{
  int serial_number;
  char *name;
  char sex;
  char *birth;
  struct best_movie *movie;
  struct director *director_next;
};

typedef struct best_movie* MOVIE;
typedef struct director* DIRECTOR;

void init();

MOVIE list_movie(char* title);
MOVIE put_list_movie(MOVIE origin, MOVIE tmp);
void print_director(DIRECTOR director);

DIRECTOR list_director(char* serial_number, char* name, char* sex, char* birth, MOVIE movie);
DIRECTOR put_list_director(DIRECTOR origin, DIRECTOR tmp);
void print_movie(MOVIE movie);

void init()
{
  DIRECTOR director = NULL;
  MOVIE movie = NULL;

  FILE *list, *log;

  char *line;
  int size;

  if((log = fopen("director_log.txt", "r+")) == NULL)
  {
    printf("FILE ERROR");
    exit(-1);
  }

  fseek(log, SEEK_SET, SEEK_END);
  size = ftell(log);
  line = (char*)malloc(size+1);
  fseek(log, 0, SEEK_SET);

  while(fgets(line, size, log))
  {
    if(strlen(line) != 1)
    {
      DIRECTOR director_tmp;
      MOVIE movie_tmp;
      char *split;
      char *tag, *serial_number, *name, *sex, *birth, *title;
      // printf("입력받은 문장 > %s" , line);

      // tag
      split = strtok(line, ":");
      tag = (char*)malloc(strlen(split)+1);
      strcpy(tag, split);
      // printf(">>> tag : %s\n", tag);
      // serial_number
      split = strtok(NULL, ":");
      serial_number = (char*)malloc(strlen(split)+1);
      strcpy(serial_number, split);
      // printf(">>> serial_number : %s\n", serial_number);
      // name
      split = strtok(NULL, ":");
      name = (char*)malloc(strlen(split)+1);
      strcpy(name, split);
      // printf(">>> name : %s\n", name);
      // sex
      split = strtok(NULL, ":");
      sex = (char*)malloc(strlen(split)+1);
      strcpy(sex, split);
      // printf(">>> sex : %s\n", sex);
      // birth
      split = strtok(NULL, ":");
      birth = (char*)malloc(strlen(split)+1);
      strcpy(birth, split);
      // printf(">>> birth : %s\n", birth);
      // title
      split = strtok(NULL, ":");
      title = (char*)malloc(strlen(split)+1);
      strcpy(title, split);
      // printf(">>> title : %s\n", title);

      // title
      split = strtok(title, ",");
      // printf("MOVIE TITLE : %s \n", split);
      if(movie == NULL)
      {
        movie = list_movie(split);
      }
      while(split = strtok(NULL, ","))
      {
        strcpy(split, split+1);
        // printf("MOVIE TITLE : %s \n", split);

        movie_tmp = list_movie(split);
        movie = put_list_movie(movie, movie_tmp);
      }

      if(director == NULL)
      {
        director = list_director(serial_number, name, sex, birth, movie);
      }
      else
      {
        director_tmp = list_director(serial_number, name, sex, birth, movie);
        director = put_list_director(director, director_tmp);
      }
      
      /*****************************/
      printf("DIRECTOR LIST > \n");
      print_director(director);
      printf("\n");
      printf("MOVIE LIST > \n");
      print_movie(movie);
      printf("\n");
      /*****************************/

      movie = NULL;

      free(tag);
      free(serial_number);
      free(sex);
      free(name);
      free(birth);
      free(title);
    }
  }
  fclose(log);

  free(line);
  free(director);
  free(movie);
}

MOVIE list_movie(char* title){
   MOVIE movie;

   if(movie == NULL)
   {
     return NULL;
   }
   else
   {
      movie = (MOVIE)malloc(sizeof(struct best_movie));
      movie->title = (char*)malloc(strlen(title)+1);
      strcpy(movie->title, title);
      movie->movie_next = NULL;

      return movie;
   }
}

DIRECTOR list_director(char* serial_number, char* name, char* sex, char* birth, MOVIE movie){
   DIRECTOR director;

   if(director == NULL)
   {
     return NULL;
   }
   else
   {
      director = (DIRECTOR)malloc(sizeof(struct director));
      director->name = (char*)malloc(strlen(name)+1);
      director->birth = (char*)malloc(strlen(birth)+1);

      director->serial_number = atoi(serial_number);
      director->sex = *sex;
      strcpy(director->name, name);
      strcpy(director->birth, birth);
      director->movie = movie;
      director->director_next = NULL;

      return director;
   }
}

MOVIE put_list_movie(MOVIE origin, MOVIE tmp){
  MOVIE new;
  new = origin;
  while(new->movie_next != NULL)
  {
    new = new->movie_next;
  }
  new->movie_next = tmp;

  return origin;
}

DIRECTOR put_list_director(DIRECTOR origin, DIRECTOR tmp){
  DIRECTOR new;
  new = origin;

  while(new->director_next != NULL)
  {
    new = new->director_next;
  }
  new->director_next = tmp;

  return origin;
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

void print_movie(MOVIE movie){
   if(movie == NULL)
   {
     printf("NULL\n");
   }
   else
   {
      printf("%s->", movie->title);
      print_movie(movie->movie_next);
   }
}

int main()
{
  init();

  return 0;
}

// if((list = fopen("director_list.txt", "r+")) == NULL)
// {
//   printf("FILE ERROR");
//   return -1;
// }
//
// fclose(list);
