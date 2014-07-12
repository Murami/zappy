#include <stdlib.h>
#include "gameplay.h"
#include "team.h"
#include "player.h"
#include "monitors.h"
#include "client.h"
#include "client_player.h"
#include "client_graphic.h"
#include "monitor_command.h"

void			bind_add_player(t_gameplay *this, t_player *player)
{
 t_list_iterator	it;
 t_client*		monitor;

  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      monitor_send_player(player, monitor);
      it = list_iterator_next(it);
    }
}

void			gameplay_add_player(t_gameplay* this, t_client* client, t_team *team)
{
  t_player*	player;

  player = player_new(this, client, team);
  list_push_back(this->players, player);
  monitor_send_player(this, player);
  player->it = this->players->root->prev;
}

void			gameplay_remove_player(t_gameplay* this, t_client* client)
{
  t_player*		player;

  player = ((t_client_player*)client)->player;
  list_erase(this->players, player->it);
  client_delete(client);
  free(player);
}
