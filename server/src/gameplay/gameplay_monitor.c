/*
** gameplay_monitor.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:22:57 2014 quentin desabre
** Last update Sun Jul 13 16:22:59 2014 Desabre Quentin
*/

#include <stdio.h>
#include <stdlib.h>
#include "gameplay.h"
#include "player.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"
#include "monitor_command.h"
#include "time_val.h"
#include "egg.h"

void			gameplay_command_pin(t_gameplay* this,
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
	  sprintf(buffer, "pin %d %d %d %d %d %d %d %d %d %d\n",
		  player->id, player->x, player->y,
		  player->inventory.food,
		  player->inventory.linemate,
		  player->inventory.deraumere,
		  player->inventory.sibur,
		  player->inventory.mendiane,
		  player->inventory.phiras,
		  player->inventory.thystame);
	  client_send_msg(&command->client->parent_client, buffer);
	  return;
	}
      it = list_iterator_next(it);
    }
  gameplay_send_sbp(&command->client->parent_client);
}

void			gameplay_command_sgt(t_gameplay* this,
					     t_monitor_command* command)
{
  monitor_send_delay(this, &command->client->parent_client);
}

void			gameplay_command_sst(t_gameplay* this,
					     t_monitor_command* command)
{
  int			old_delay;
  char*			ptr;

  old_delay = this->delay;
  ptr = command->data[0];
  this->delay = strtol(command->data[0], &ptr, 10);
  if (ptr == '\0' || this->delay == 0)
    {
      this->delay = old_delay;
      gameplay_send_sbp(&command->client->parent_client);
      return;
    }
  monitor_send_delay(this, &command->client->parent_client);
  gameplay_update_all_times(this, old_delay);
}
