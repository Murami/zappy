#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "client.h"
#include "gameplay.h"
#include "player.h"
#include "server.h"
#include "monitor.h"

t_list_iterator		gameplay_kill_player(t_gameplay* this, t_player* player)
{
  t_list_iterator	it;

  printf("player [%d] killed (starved to death)\n", player->id);
  it = list_iterator_prev(player->it);
  server_remove(this->server, player->client);
  list_erase(this->players, player->it);
  monitor_send_pdi(this, player);
  client_send_msg(player->client, "mort\n");
  server_remove(this->server, player->client);
  free(player);
  return (it);
}

t_list_iterator		gameplay_kill_ghost(t_gameplay* this, t_player* player)
{
  t_list_iterator	it;

  printf("ghost player [%d] killed (starved to death)\n", player->id);
  it = list_iterator_prev(player->it);
  list_erase(this->ghosts, player->it);
  if (player->is_egg)
    monitor_send_edi(this, player);
  else
    monitor_send_pdi(this, player);
  free(player);
  return (it);
}
