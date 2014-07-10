#include <stdlib.h>
#include "gameplay.h"
#include "team.h"
#include "player.h"
#include "monitors.h"
#include "client.h"
#include "client_player.h"
#include "client_graphic.h"
#include "monitor_command.h"

void			gameplay_add_player(t_gameplay* this, t_client* client, t_team *team)
{
  t_player*	player;

  player = player_new(this, client, team);
  list_push_back(this->players, player);
  player->it = list_back(this->players);
}

void			gameplay_remove_player(t_gameplay* this, t_client* client)
{
  t_player*		player;

  (void) this;
  player = ((t_client_player*)client)->player;
  client_delete(client);
  free(player);
}

void			gameplay_add_monitor(t_gameplay* this, t_client* client)
{
  list_push_back(this->monitors, client);
  monitor_initialize(this, client);
}

void			gameplay_remove_monitor(t_gameplay* this, t_client* client)
{
  t_list_iterator	it;
  t_client_graphic*	tmp;

  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      tmp = it->data;
      if ((t_client*)tmp == client)
  	{
  	  it = list_erase(this->monitors, it);
  	  return;
  	}
      it = list_iterator_next(it);
    }
}
