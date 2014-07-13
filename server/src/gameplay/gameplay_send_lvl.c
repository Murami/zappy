/*
** gameplay_send_lvl.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:06:41 2014 otoshigami
** Last update Sun Jul 13 22:37:15 2014 Desabre Quentin
*/

#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "client_graphic.h"
#include "gameplay.h"
#include "player.h"

void			gameplay_send_lvl_all(t_gameplay *this, t_player *player)
{
  t_list_iterator	it;
  t_client*		monitor;
  char			buffer[4096];

  sprintf(buffer, "plv %d %d\n", player->id, player->level);
  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}

void			gameplay_command_plv(t_gameplay* this,
					     t_monitor_command* command)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->id == atoi(command->data[0]))
	{
	  sprintf(buffer, "plv %d %d\n",
		  player->id,
		  player->level);
	  client_send_msg(&command->client->parent_client, buffer);
	  return;
	}
      it = list_iterator_next(it);
    }
  gameplay_send_sbp(&command->client->parent_client);
}
