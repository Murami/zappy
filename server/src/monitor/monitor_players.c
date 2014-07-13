#include <stdio.h>
#include "player.h"
#include "team.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"
#include "gameplay.h"

void			monitor_send_egg_connect(t_player *player, t_client *client)
{
 char			buffer[4096];

  sprintf(buffer, "ebo %d\n",
	  player->id_egg);
  client_send_msg(client, buffer);
}

void			monitor_send_player(t_player *player, t_client* client)
{
  char			buffer[4096];

  sprintf(buffer, "pnw %d %d %d %d %d %s\n",
	  player->id,
	  player->x,
	  player->y,
	  player->direction,
	  player->level,
	  player->team->name);
  client_send_msg(client, buffer);
}

void			monitor_send_players(t_gameplay *this, t_client *client)
{
  t_list_iterator	it;
  t_player*		player;

  (void)client;
  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      monitor_send_player(player, client);
      it = list_iterator_next(it);
    }
  it = list_begin(this->ghosts);
  while (it != list_end(this->ghosts))
    {
      player = it->data;
      if (!player->is_egg)
	monitor_send_player(player, client);
      it = list_iterator_next(it);
    }
}

void			monitor_send_pdi(t_gameplay *this, t_player* player)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_client*		client;

  sprintf(buffer, "pdi %d\n", player->id);
  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      client = it->data;
      client_send_msg(client, buffer);
      it = list_iterator_next(it);
    }
}
