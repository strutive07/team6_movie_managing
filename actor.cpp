#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct best_movie
{
	char* title;
	struct best_movie *movie_next;
};

struct actor
{
	int serial_number;
	char *name;
	bool sex;
	char* birth;
	struct best_movie *movie;
	struct actor *actor_next;
};

typedef struct best_movie* MOVIE;
typedef struct actor* ACTOR;

MOVIE list_movie(char* title)
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

MOVIE put_list_movie(MOVIE origin, MOVIE tmp)
{
	MOVIE NEW;
	NEW = origin;

	while (NEW->movie_next != NULL)
		NEW = NEW->movie_next;

	NEW->movie_next = tmp;

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

void print_movie(MOVIE movie) {
	if (movie == NULL)
	{
		printf("NULL\n");
	}
	else
	{
		printf("%s->", movie->title);
		print_movie(movie->movie_next);
	}
}

void print_actor(ACTOR actor) {
	if (actor == NULL)
	{
		printf("NULL \n");
	}
	else
	{
		printf("%d / ", actor->serial_number);
		printf("%s / ", actor->name);
		if (actor->sex)
			printf("M / ");
		else
			printf("F / ");
		printf("%s / movie_list -> ", actor->birth);
		print_actor(actor->actor_next);
	}
}
void actor_rtol(char* actor_str)
{

	MOVIE movie = NULL, movie_tmp;
	ACTOR actor = NULL, actor_tmp;
	char* tag = strtok(actor_str, ":");

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
		actor_info->sex = true; //남자일 경우 true
	else
		actor_info->sex = false; //여자일 경우 false 

	tmp = strtok(NULL, ":");
	actor_info->birth = (char*)malloc(sizeof(char)*(strlen(tmp) + 1));
	strcpy(actor_info->birth, tmp);

	tmp = strtok(NULL, ":");
	best_movie_tmp = strtok(tmp, ",");
	if (movie == NULL)
		list_movie(best_movie_tmp);
	while (best_movie_tmp = strtok(NULL, ","))
	{
		strcpy(best_movie_tmp, best_movie_tmp + 1);
		movie_tmp = list_movie(best_movie_tmp);
		movie = put_list_movie(movie, movie_tmp);
	}

	if (actor == NULL)
		actor = list_actor(actor_info->serial_number, actor_info->name, actor_info->sex, actor_info->birth, actor_info->movie);
	else
	{
		actor_tmp = list_actor(actor_info->serial_number, actor_info->name, actor_info->sex, actor_info->birth, actor_info->movie);
		actor = put_list_actor(actor, actor_tmp);
	}

	print_actor(actor);
	print_movie(movie);
}

void init_actor()
{
	FILE *actor_log_read, *actor_log_add, *actor_list;
	
	actor_log_read = fopen("actor_log.txt", "r+");

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

	fclose(actor_log_read);
}
int main()
{
	init_actor();

	return 0;
}

