#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "monitor_command.h"
#include "client.h"
#include "player.h"

void			send_incantation_start(t_gameplay* this, t_player_command* command)
{
  char			buffer[4096];
  char			temp[64];
  t_list_iterator	it;
  t_player*		player;

  sprintf(buffer, "pic %d %d %d",
	  command->player->x, command->player->y,
	  command->player->level);
  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->x == command->player->x && player->y == command->player->y)
	client_send_msg(player->client, "elevation en cours\n");
      sprintf(temp, " %d", player->id);
      strcat(buffer, temp);
      it = list_iterator_next(it);
    }
  strcat(buffer, "\n");
  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      client_send_msg(it->data, buffer);
      it = list_iterator_next(it);
    }
}

void			gameplay_add_player_command(t_gameplay* this,
						    t_player_command* command)
{
  if ((strcmp(g_player_commands[command->id_command].request,
	      "incantation") == 0 &&
       check_incant(this, command)) ||
      strcmp(g_player_commands[command->id_command].request,
	     "incantation") != 0
      )
    {
      if (strcmp(g_player_commands[command->id_command].request, "fork") == 0)
	gameplay_send_egg(this, command->player);
      if (strcmp(g_player_commands[command->id_command].request,
		 "incantation") == 0)
	send_incantation_start(this, command);
      player_add_action(command->player, command);
      if (list_size(command->player->command_queue) == 1)
	gameplay_update_player_position(this, command->player, this->players);
    }
  else
    client_send_msg(command->player->client, "ko\n");
}

void			gameplay_add_monitor_command(t_gameplay* this,
						     t_monitor_command* command)
{
  monitor_command_execute(command, this);
  monitor_command_delete(command);
}
