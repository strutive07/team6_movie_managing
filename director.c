#include "director.h"
#include "movie.h"

void init_director()
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

  if((list = fopen("director_list.txt", "w")) == NULL)
  {
    printf("FILE ERROR");
    exit(-1);
  }

  fseek(log, SEEK_SET, SEEK_END);
  size = ftell(log);
  line = (char*)malloc(size+3);
  fseek(log, 0, SEEK_SET);

  while(fgets(line, size, log))
  {
    if(strlen(line) != 1)
    {
      DIRECTOR director_tmp;
      MOVIE movie_tmp;
      char *split, *origin;
      char *tag, *serial_number, *name, *sex, *birth, *title;
      int serial_number_integer;
      // printf("입력받은 문장 > %s" , line);
      origin = (char*)malloc(size+3);
      strcpy(origin, line);

      // tag
      split = strtok(line, ":");
      tag = (char*)malloc(strlen(split)+3);
      strcpy(tag, split);
      // printf(">>> tag : %s\n", tag);
      // serial_number
      split = strtok(NULL, ":");
      serial_number = (char*)malloc(strlen(split)+3);
      strcpy(serial_number, split);
      serial_number_integer = atoi(serial_number);
      // printf(">>> serial_number : %s\n", serial_number);
      if(!strcmp(tag, "add"))
      {
        add_list_director(list, origin+4);

        // name
        split = strtok(NULL, ":");
        name = (char*)malloc(strlen(split)+3);
        strcpy(name, split);
        // printf(">>> name : %s\n", name);
        // sex
        split = strtok(NULL, ":");
        sex = (char*)malloc(strlen(split)+3);
        strcpy(sex, split);
        // printf(">>> sex : %s\n", sex);
        // birth
        split = strtok(NULL, ":");
        birth = (char*)malloc(strlen(split)+3);
        strcpy(birth, split);
        // printf(">>> birth : %s\n", birth);
        // title
        split = strtok(NULL, ":");
        title = (char*)malloc(strlen(split)+3);
        strcpy(title, split);
        *(title + strlen(title) - 1) = '\0';

        // title
        split = strtok(title, ",\n");
        // printf("MOVIE TITLE : %s \n", split);
        if(movie == NULL)
        {
          movie = list_movie_director(split);
        }
        while(split = strtok(NULL, ",\n"))
        {
          strcpy(split, split+1);
          // printf("MOVIE TITLE : %s \n", split);

          movie_tmp = list_movie_director(split);
          movie = put_list_movie_director(movie, movie_tmp);
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
      }
      else if(!strcmp(tag, "delete"))
      {
        DIRECTOR delete_director = director;
        option_delete_director(serial_number_integer, delete_director, true);
        continue;
      }
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
        if(strcmp(name, "="))
        {
          free(update_director->name);
          update_director->name= (char*)malloc(strlen(name)+3);
          strcpy(update_director->name, name);
        }
        // printf(">>> name : %s\n", name);
        // sex
        split = strtok(NULL, ":");
        sex = (char*)malloc(strlen(split)+3);
        strcpy(sex, split);
        if(*sex != '=')
        {
          update_director->sex = *sex;
        }
        // printf(">>> sex : %s\n", sex);
        // birth
        split = strtok(NULL, ":");
        birth = (char*)malloc(strlen(split)+3);
        strcpy(birth, split);
        if(strcmp(birth, "="))
        {
          free(update_director->birth);
          update_director->birth= (char*)malloc(strlen(birth)+3);
          strcpy(update_director->birth, birth);
        }
        // printf(">>> birth : %s\n", birth);
        // title
        split = strtok(NULL, ":");
        title = (char*)malloc(strlen(split)+3);
        strcpy(title, split);
        *(title + strlen(title) - 1) = '\0';

        if(!strlen(title))
        {
          continue;
        }
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


      /*****************************/
      printf("DIRECTOR LIST > \n");
      print_director(director);
      printf("\n");
      printf("MOVIE LIST > \n");
      print_movie_director(movie);
      printf("\n");

      /*****************************/

      movie = NULL;

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

  // printf("@@@@@@@@%s\n", director->director_next->movie->title);

  public_director = director;

  free(line);
  // free(director);
  // free(movie);
}

void add_list_director(FILE *list, char* origin)
{
  fprintf(list, "%s", origin);
}

MOVIE list_movie_director(char* title){
   MOVIE movie;

   if(movie == NULL)
   {
     return NULL;
   }
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

   if(director == NULL)
   {
     return NULL;
   }
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

  while(LINK != NULL)
  {
    if(!strcmp(title, LINK->title))
    {
      // printf("@@@@@@@@@@@@@@@@@@@@@@@@ SEARCH COMPLETE! %s /// %s\n", title, LINK->title);

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

  while(BEST_MOVIE != NULL)
  {
    result = search_director_to_movie_title(BEST_MOVIE->title);
    // printf("@@@@@@@@@@@@@@@@@@@@@@@ %d %s ///\n", strlen(tmp->movie->title), tmp->movie->title);

    if(result != NULL)
    {
      // printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SUCCESS\n");
      // printf("@@@@@@@@@@@@@@@@@@@@@@@@ SEARCH COMPLETE! %s /// %s\n", tmp->movie->title, result->title);
      BEST_MOVIE->movie_link = result;
      printf("MOVIE and DIRECOTR CONNECTED > %s\n", BEST_MOVIE->movie_link->title);

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
