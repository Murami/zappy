#include <stdio.h>
#include <stdlib.h>
#include "gameplay.h"
#include "player.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"
#include "monitor_command.h"

void			gameplay_command_msz(t_gameplay* this, t_monitor_command* command)
{
  monitor_send_size(this, &command->client->parent_client);
}

void			gameplay_command_bct(t_gameplay* this, t_monitor_command* command)
{
  monitor_send_case(&command->client->parent_client,
		    &this->map.map[atoi(command->data[0])
				   + atoi(command->data[1]) * this->map.width]);
}

void			gameplay_command_mct(t_gameplay* this, t_monitor_command* command)
{
  monitor_send_map(this, &command->client->parent_client);
}

void			gameplay_command_tna(t_gameplay* this, t_monitor_command* command)
{
  monitor_send_teams(this, &command->client->parent_client);
}

void			gameplay_command_ppo(t_gameplay* this, t_monitor_command* command)
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
  // wrong arugment to do
}


void			gameplay_command_pin(t_gameplay* this, t_monitor_command* command)
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
		  player->id, player->x,
		  player->y,
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
}

void			gameplay_command_sgt(t_gameplay* this, t_monitor_command* command)
{
  monitor_send_delay(this, &command->client->parent_client);
}

void			gameplay_command_sst(t_gameplay* this, t_monitor_command* command)
{
  this->delay = atoi(command->data[0]);
  monitor_send_delay(this, &command->client->parent_client);
}
