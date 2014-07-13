#include <stdlib.h>
#include "gameplay.h"
#include "list.h"
#include "team.h"
#include "player.h"

t_player*	gameplay_get_ghost(t_gameplay* gameplay, t_team* team)
{
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(gameplay->ghosts);
  while (it != list_end(gameplay->ghosts))
    {
      player = it->data;
      if (player->team == team)
	{
	  list_erase(gameplay->ghosts, it);
	  return (player);
	}
      it = list_iterator_next(it);
    }
  return (NULL);
}
