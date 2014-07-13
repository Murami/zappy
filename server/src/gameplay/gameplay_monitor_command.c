/*
** gameplay_monitor_command.c for monitor command in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:17:19 2014 quentin desabre
** Last update Sun Jul 13 16:17:26 2014 Desabre Quentin
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

void			gameplay_command_msz(t_gameplay* this,
					     t_monitor_command* command)
{
  monitor_send_size(this, &command->client->parent_client);
}

void			gameplay_command_bct(t_gameplay* this,
					     t_monitor_command* command)
{
  int			x;
  int			y;
  char*			ptr;

  ptr = command->data[0];
  x = strtol(command->data[0], &ptr, 10);
  if (*ptr == '\0')
    {
      gameplay_send_sbp(&command->client->parent_client);
      return;
    }
  ptr = command->data[1];
  y = strtol(command->data[1], &ptr, 10);
  if (ptr == '\0')
    {
      gameplay_send_sbp(&command->client->parent_client);
      return;
    }
  monitor_send_case(&command->client->parent_client,
		    &this->map.map[x + y * this->map.width]);
}

void			gameplay_command_mct(t_gameplay* this,
					     t_monitor_command* command)
{
  monitor_send_map(this, &command->client->parent_client);
}

void			gameplay_command_tna(t_gameplay* this,
					     t_monitor_command* command)
{
  monitor_send_teams(this, &command->client->parent_client);
}

void			gameplay_command_ppo(t_gameplay* this,
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
	  sprintf(buffer, "ppo %d %d %d %d\n",
		  player->id,
		  player->x,
		  player->y,
		  player->direction);
	  client_send_msg(&command->client->parent_client, buffer);
	  return;
	}
      it = list_iterator_next(it);
    }
  gameplay_send_sbp(&command->client->parent_client);
}
