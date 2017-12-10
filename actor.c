#include "actor.h"
#include "movie.h"

MOVIE list_movie_actor(char* title)//대표영화를 삽입하는 함수
{
   MOVIE movie;

   if (movie == NULL)//영화가 비어있을경우
   {
      return NULL;
    }
   else//영화가 비어있지 않을경우
   {
      movie = (MOVIE)malloc(sizeof(struct best_movie));
      movie->title = (char*)malloc(strlen(title) + 1);
      strcpy(movie->title, title);
      movie->movie_next = NULL;
      return movie;
   }
}

MOVIE put_list_movie_actor(struct best_movie *origin, struct best_movie *tmp)//대표영화를 연결하는 함수
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

ACTOR list_actor(int serial_number, char* name, bool sex, char* birth, MOVIE movie)//actor구조체에 삽입하는 함수
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

void print_movie_actor(MOVIE movie)//대표영화를 list파일에 출력
{
  if (movie == NULL)
  {

  }
  else
  {

    if(movie->movie_next == NULL)
    {
      fprintf(actor_list, "%s\n", movie->title);
    }
    else
    {
      fprintf(actor_list,"%s, ", movie->title);
    }
     print_movie_actor(movie->movie_next);
  }
}

void print_actor(ACTOR actor)//actor구조체를 list파일에 출력
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
  }
}

void actor_rtol(char* actor_str)//log파일 내용을 구조체로 넣음
{
   MOVIE movie_tmp=NULL;
   ACTOR actor = NULL, actor_tmp=NULL;
   char* tag = strtok(actor_str, ":");// :을 기준으로 문자를 자름
   char *tmp;

   if (!(strcmp(tag, "add")))//태그가 add일 경우
   {
      struct actor *actor_info;
      actor_info = (struct actor*)malloc(sizeof(struct actor));
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
      best_movie_tmp = strtok(tmp, ",\n");
         //printf("%s\n", best_movie_tmp);
      if (actor_info->movie == NULL)//actor구조체의 movie가 비어있을경우
         actor_info->movie = list_movie_actor(best_movie_tmp);//

      while (best_movie_tmp = strtok(NULL, ",\n"))//,가 있을경우 반복
      {
         //printf("%s\n", best_movie_tmp);
         strcpy(best_movie_tmp, best_movie_tmp + 1);
         movie_tmp = list_movie_actor(best_movie_tmp);//tmp구조체에 영화를 넣음
         actor_info->movie = put_list_movie_actor(actor_info->movie, movie_tmp);//구조체에 tmp구조체 내용 삽입
      }
      if (public_actor == NULL){
         public_actor = actor_info;//public구조에가 비었을 경우 public 구조체에 정보 삽입
      }
      else
      {
         put_list_actor(public_actor, actor_info);//public구조체가 비지 않았을 경우 연결하며 삽입
      }
   }
   else if (!(strcmp(tag, "delete")))//태그가 delete일 경우
   {
     tmp=strtok(NULL,":");
     int num=atoi(tmp);
     option_delete_actor(num,public_actor,true);//delete함수 호출
   }
   else if (!(strcmp(tag,"update")))//태그가 update일 경우
   {
      ACTOR actor=public_actor;
      tmp=strtok(NULL,":");
      int num=atoi(tmp);//시리얼넘버 입력

      if (num!=1)//시리얼넘버가 1번이 아닐경우
        actor=move_serial_actor(num,actor);//구조체에서 이동

      if (actor==NULL)//actor구조체가 비었을 경우
      {
        printf("No Such Record while loading actor_log.txt\n");
        exit(1);
      }

      tmp=strtok(NULL,":");//이름
      if (strlen(tmp)==0)//비었을경우
      {

      }
      else if (strlen(tmp)==1 && *(tmp+0)=='=')// =일 경우
      {

      }
      else
      {
        free(actor->name);
        actor->name=(char*)malloc(strlen(tmp)+5);
        strcpy(actor->name,colon_change(tmp));
      }

      tmp=strtok(NULL,":");//성별
      if (strlen(tmp)==0)
      {

      }
      else if (strlen(tmp)==1 && *(tmp+0)=='=')
      {

      }
      else
      {
        if (!strcmp(tmp,"M"))
          actor->sex=true;
        else
          actor->sex=false;
      }

      tmp=strtok(NULL,":");//생년월일
      if (strlen(tmp)==0)
      {

      }
      else if (strlen(tmp)==1 && *(tmp+0)=='=')
      {

      }
      else
      {
        free(actor->birth);
        actor->birth=(char*)malloc(strlen(tmp)+5);
        strcpy(actor->birth,colon_change(tmp));
      }

      tmp=strtok(NULL,":\n");//대표영화
      if (strlen(tmp)==0)
      {

      }
      else if (strlen(tmp)==1 && *(tmp+0)=='=')
      {

      }
      else
      {
        char *best_movie_tmp;

        best_movie_tmp = strtok(tmp, ",\n");

        actor->movie = list_movie_actor(best_movie_tmp);

        while (best_movie_tmp = strtok(NULL, ",\n"))
        {
           strcpy(best_movie_tmp, best_movie_tmp + 1);
           movie_tmp = list_movie_actor(best_movie_tmp);
           actor->movie = put_list_movie_actor(actor->movie, movie_tmp);
        }
      }

   }
}

void init_actor()//프로그램 시작시 actor 구조체 초기화
{

   actor_log_read = fopen("actor_log.txt", "ra");
    actor_list = fopen("actor_list.txt", "w");

   if (actor_log_read == NULL)
   {
      printf("File Open Error\n");
      exit(0);
   }

   char *actor_str = (char*)malloc(sizeof(char) * 200);//한줄 입력 준비

   while (fgets(actor_str, 200, actor_log_read) != NULL)//한줄씩 입력받음
   {
      actor_rtol(actor_str);//로그 파일을 구조체에 저장하는 함수
   }
    print_actor(public_actor);//log파일 내용을 list파일로 변환함
    fprint_list_movie_director_actor('A',public_first_movie,public_director,public_actor);//log파일 내용을 list파일로 변환함
   fclose(actor_log_read);
}

struct movie* search_actor_to_movie_title(char* title)
{
	struct movie* LINK=public_first_movie;

	while(LINK!=NULL)
	{
		if (!strcmp(title,LINK->title))//대표영화와 movie구조체에 같은 영화가 있는지 확인
		{
			return LINK;
		}
		LINK=LINK->movie_next;

	}

	return NULL;
}


int search_actor_to_movie(ACTOR public_actor_tmp)
{
	struct movie* result=NULL;
	struct best_movie* BEST_MOVIE=public_actor_tmp->movie;

	while (BEST_MOVIE->movie_next!=NULL)
	{
		result=search_actor_to_movie_title(BEST_MOVIE->title);//이름으로 확인

		if (result!=NULL)//대표영화와 같은 영화가 movie구조체에 있을경우
		{
			BEST_MOVIE->movie_link=result;//연결
			printf("MOVIE and ACOTR CONNECTED > %s\n", BEST_MOVIE->movie_link->title);
			return 1;
		}

		if(BEST_MOVIE->movie_next != NULL)
		{
			BEST_MOVIE = BEST_MOVIE->movie_next;
		}

	}
	return 0;
}


void link_actor_to_movie()//actor구조체 내 대표영화 정보를 movie구조체와 연결
{
	int result;
	ACTOR public_actor_tmp=public_actor;

	while(public_actor_tmp!=NULL)
	{
		result=search_actor_to_movie(public_actor_tmp);//actor 구조체의 대표 영화가 movie구조체에 있나 확인

		if (result)//영화가 없을경우 break
		{
			break;
		}

		public_actor_tmp=public_actor_tmp->actor_next;
	}
}
