#include "movie.h"
#include "director.h"
#include "actor.h"

int main()
{
  printf("\n\n\n (MOVIE) Success Contact!!! \n\n\n");
  init_movie();
  printf("\n\n\n (DIRECTOR) Success Contact!!! \n\n\n");
  init_director();
  printf("\n\n\n (ACTOR) Success Contact!!! \n\n\n");
  init_actor();

  printf("\n\n\n (ALL) Success Contact!!! \n\n\n");
  lint_movie_to_director(public_director, public_first_movie);
  lint_movie_to_actor(public_actor, public_first_movie);
  // search_actor_in_movie(public_actor, "char* argument_actor_name");
  // search_director_in_movie(public_director, "Ridley Scott");
}
