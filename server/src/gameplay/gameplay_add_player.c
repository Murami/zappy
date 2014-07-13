/*
** gameplay_add_player.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:05:43 2014 otoshigami
** Last update Sun Jul 13 21:31:32 2014 otoshigami
*/

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
      if (player->id_egg)
	monitor_send_egg_connect(player, monitor);
      monitor_send_player(player, monitor);
      it = list_iterator_next(it);
    }
}

t_player*		gameplay_add_new_player(t_gameplay* this,
						t_client* client, t_team* team)
{
  t_player*		player;
  int			nb;

  nb = 0;
  player = player_new(this, client, team);
  while (nb != this->map.width * this->map.height / 8)
    {
      gameplay_pop_food(this);
      nb++;
    }
  gameplay_update_player_position(this, player, this->players);
  return (player);
}

void			gameplay_add_player(t_gameplay* this,
					    t_client* client, t_team *team)
{
  t_player*	player;

  if ((player = gameplay_get_ghost(this, team)))
    {
      player->it = NULL;
      player->client = client;
      player->is_egg = false;
      ((t_client_player*)client)->player = player;
      gameplay_update_player_position(this, player, this->players);
      if (player->id_egg)
	{
	  printf("new player [%d] connected on egg slot [%d]\n",
		 player->id, player->id_egg);
	  bind_add_player(this, player);
	}
    }
  else
    {
      player = gameplay_add_new_player(this, client, team);
      printf("new player [%d]\n", player->id);
      bind_add_player(this, player);
    }
}

void			gameplay_remove_player(t_gameplay* this,
					       t_client* client)
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
}
