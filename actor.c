#include "actor.h"

MOVIE list_movie_actor(char* title)
{
   MOVIE movie;

   if (movie == NULL)
      return NULL;
   else
   {
      movie = (MOVIE)malloc(sizeof(struct best_movie));
      movie->title = (char*)malloc(strlen(title) + 1);
      strcpy(movie->title, title);
      movie->movie_next = NULL;
      return movie;
   }
}

MOVIE put_list_movie_actor(struct best_movie *origin, struct best_movie *tmp)
{
   struct best_movie *new;
    new=(MOVIE)malloc(sizeof(struct best_movie));
   new = origin;

   while (new->movie_next != NULL)
                new = new->movie_next;
    new->movie_next=(MOVIE)malloc(sizeof(struct best_movie));
   new->movie_next = tmp;

   return origin;
}

ACTOR list_actor(int serial_number, char* name, bool sex, char* birth, MOVIE movie)
{
   ACTOR actor;

   if (actor == NULL)
      return NULL;
   else
   {
      actor = (ACTOR)malloc(sizeof(struct actor));
      actor->name = (char*)malloc(strlen(name) + 1);
      actor->birth = (char*)malloc(strlen(birth) + 1);

      actor->serial_number = serial_number;
      actor->sex = sex;
      strcpy(actor->name, name);
      strcpy(actor->birth, birth);
      actor->movie = movie;
      actor->actor_next = NULL;

      return actor;
   }
}

ACTOR put_list_actor(ACTOR origin, ACTOR tmp)
{
   ACTOR NEW;
   NEW = origin;

   while (NEW->actor_next != NULL)
      NEW = NEW->actor_next;

   NEW->actor_next = tmp;

   return origin;
}

void print_movie_actor(MOVIE movie)
{
  if (movie == NULL)
  {
     // fprintf(actor_list,"NULL\n");
  }
  else
  {

    if(movie->movie_next == NULL)
    {
      fprintf(actor_list, "%s", movie->title);
    }
    else
    {
      fprintf(actor_list,"%s, ", movie->title);
    }
     print_movie_actor(movie->movie_next);
  }
   // if (movie == NULL)
   // {
   //    // fprintf(actor_list,"NULL\n");
   // }
   // else
   // {
   //
		//  if(movie->movie_next == NULL)
		//  {
		// 	 fprintf(actor_list,"%s", movie->title);
		//  }
		//  else
		//  {
		// 	 fprintf(actor_list,"%s, ", movie->title);
		//  }
   //    print_movie_actor(movie->movie_next);
   // }
}

void print_actor(ACTOR actor)
{
  while(actor != NULL){
    fprintf(actor_list, "%d:", actor->serial_number);
    fprintf(actor_list, "%s:", actor->name);
    if (actor->sex)
       fprintf( actor_list, "M:");
    else
       fprintf(actor_list, "F:");

    fprintf(actor_list, "%s:", actor->birth);
    print_movie_actor(actor->movie);

    actor = actor -> actor_next;
    // fprintf(actor_list, "%d:", actor->serial_number);
    // fprintf(actor_list, "%s:", actor->name);
    // if (actor->sex)
    //    fprintf(actor_list, "M:");
    // else
    //    fprintf(actor_list, "F:");
    //
    // fprintf(actor_list, "%s:", actor->birth);
    // print_movie_actor(actor->movie);
    // actor = actor -> actor_next;
  }
   // if (actor == NULL)
   // {
   //    // printf("NULL\n");
   // }
   // else
   // {
   //    // fprintf(actor_list, "%d:", actor->serial_number);
   //    // fprintf(actor_list, "%s:", actor->name);
   //    // if (actor->sex)
   //    //    fprintf(actor_list, "M:");
   //    // else
   //    //    fprintf(actor_list, "F:");
   //    //
   //    // fprintf(actor_list, "%s:", actor->birth);
   //    // print_movie_actor(actor->movie);
   //    // print_actor(actor->actor_next);
   // }
}
void actor_rtol(char* actor_str)
{
   MOVIE movie_tmp=NULL;
   ACTOR actor = NULL, actor_tmp=NULL;
   char* tag = strtok(actor_str, ":");

   if (!(strcmp(tag, "add")))
   {
      struct actor *actor_info;
      actor_info = (struct actor*)malloc(sizeof(struct actor));
      char *tmp;
      char *best_movie_tmp;

      tmp = strtok(NULL, ":");
      actor_info->serial_number = atoi(tmp);

      tmp = strtok(NULL, ":");
      actor_info->name = (char*)malloc(sizeof(char)*(strlen(tmp) + 1));
      strcpy(actor_info->name, tmp);

      tmp = strtok(NULL, ":");
      if (!strcmp(tmp, "M"))
         actor_info->sex = true; //남자일경우 true
      else
         actor_info->sex = false; //여자일경우 false

      tmp = strtok(NULL, ":");
      actor_info->birth = (char*)malloc(sizeof(char)*(strlen(tmp) + 1));
      strcpy(actor_info->birth, tmp);

      tmp = strtok(NULL, ":");
      best_movie_tmp = strtok(tmp, ",");
         printf("%s\n", best_movie_tmp);
      if (actor_info->movie == NULL)
         actor_info->movie = list_movie_actor(best_movie_tmp);

      while (best_movie_tmp = strtok(NULL, ","))
      {
         printf("%s\n", best_movie_tmp);
         strcpy(best_movie_tmp, best_movie_tmp + 1);
         movie_tmp = list_movie_actor(best_movie_tmp);
         actor_info->movie = put_list_movie_actor(actor_info->movie, movie_tmp);
      }
      if (public_actor == NULL){
         // actor = list_actor(actor_info->serial_number, actor_info->name, actor_info->sex, actor_info->birth, actor_info->movie);
         public_actor = actor_info;
      }
      else
      {
         // actor_tmp = list_actor(actor_info->serial_number, actor_info->name, actor_info->sex, actor_info->birth, actor_info->movie);
         put_list_actor(public_actor, actor_info);
      }
   }
}

void init_actor()
{

   actor_log_read = fopen("actor_log.txt", "ra");
    actor_list = fopen("actor_list.txt", "w");

   if (actor_log_read == NULL)
   {
      printf("File Open Error\n");
      exit(0);
   }

   char *actor_str = (char*)malloc(sizeof(char) * 200);

   while (fgets(actor_str, 200, actor_log_read) != NULL)
   {
      actor_rtol(actor_str);
   }
    print_actor(public_actor);
   fclose(actor_log_read);
}
