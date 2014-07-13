#include <stdbool.h>
#include <stdlib.h>
#include "list.h"
#include "gameplay.h"
#include "egg.h"
#include "player.h"
#include "time_val.h"

bool	egg_need_update(t_egg* egg, struct timeval currenttime)
{
  if (timeval_comp(currenttime, egg->time) >= 0)
    return (true);
  return (false);
}

void			gameplay_remove_egg(t_gameplay* this, t_egg* egg)
{
  t_list_iterator	it;

  it = list_begin(this->eggs);
  while (it != list_end(this->eggs))
    {
      if (egg == it->data)
	free(it->data);
      it = list_iterator_next(it);
    }
}

void		gameplay_egg_hatch(t_gameplay* this, t_egg* egg)
{
  t_player*	player;

  player = player_new(this, NULL, egg->team);
  player->id_egg = egg->id;
  player->it = NULL;
  player->is_egg = true;
  gameplay_update_player_position(this, player, this->ghosts);
  gameplay_send_egg_hatch(this, egg);
}

struct timeval		gameplay_update_eggs(t_gameplay* this,
					     struct timeval currenttime)
{
  struct timeval	waiting_time;
  t_list_iterator	it;

  waiting_time.tv_sec = 0;
  waiting_time.tv_usec = 0;
  it = list_begin(this->eggs);
  while (it != list_end(this->eggs) &&
	 egg_need_update(it->data, currenttime))
    {
      gameplay_egg_hatch(this, it->data);
      free(it->data);
      it = list_erase(this->eggs, it);
      it = list_iterator_next(it);
    }
  if (!list_empty(this->eggs))
    return (timeval_sub(((t_egg*)list_front(this->eggs))->time,
			currenttime));
  return (waiting_time);
}
