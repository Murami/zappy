#include <stdio.h>
#include <stdlib.h>
#include "gameplay.h"
#include "team.h"
#include "player.h"
#include "monitor.h"
#include "client.h"
#include "client_player.h"
#include "client_graphic.h"
#include "monitor_command.h"
#include "time_val.h"

int			gameplay_get_new_id(t_gameplay* this)
{
  this->last_id++;
  return (this->last_id);
}

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

t_player*		gameplay_add_new_player(t_gameplay* this, t_client* client, t_team* team)
{
  t_player*		player;

  player = player_new(this, client, team);
  gameplay_update_player_position(this, player, this->players);
  return (player);
}

void			gameplay_add_player(t_gameplay* this, t_client* client, t_team *team)
{
  t_player*	player;

  if (!list_empty(this->ghosts))
    {
      player = list_front(this->ghosts);
      list_erase(this->ghosts, player->it);
      player->it = NULL;
      player->client = client;
      ((t_client_player*)client)->player = player;
      gameplay_update_player_position(this, player, this->players);
      if (player->is_egg)
	/**/;
      else
	/**/;
      player->is_egg = false;
    }
  else
    {
      player = gameplay_add_new_player(this, client, team);
      bind_add_player(this, player);
    }
}

void			gameplay_remove_player(t_gameplay* this, t_client* client) /* MAKE THE PLAYER GHOST */
{
  t_player*		player;
  t_list_iterator	it;
  struct timeval	time_tomove;
  struct timeval	time_current;

  player = ((t_client_player*)client)->player;
  client_delete(client);
  player->client = NULL;
  list_erase(this->players, player->it);
  it = list_begin(this->ghosts);
  time_tomove = player_get_next_action_time(player);
  while (it != list_end(this->ghosts))
    {
      time_current = player_get_next_action_time(it->data);
      if (timeval_comp(time_current, time_tomove) < 0)
	{
	  player->it = list_insert(this->ghosts, it, player);
	  return;
	}
      it = list_iterator_next(it);
    }
  player->it = list_insert(this->ghosts, it, player);
  player->is_egg = false;
}
