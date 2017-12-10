#include "movie.h"
#include "director.h"
#include "actor.h"
#include "option.h"

int main()
{
  init_movie();
  init_director();
  init_actor();

  lint_movie_to_director(public_director, public_first_movie);
  lint_movie_to_actor(public_actor, public_first_movie);
  link_director_to_movie();
  lint_movie_to_director(public_director, public_first_movie);
  lint_movie_to_actor(public_actor, public_first_movie);
  fprint_list_movie_director_actor('M', public_first_movie, public_director, public_actor);
  
  whats_up_commander();
}
