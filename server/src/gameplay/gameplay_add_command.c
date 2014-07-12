#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "monitor_command.h"
#include "client.h"
#include "player.h"

void			send_incantation_start(t_gameplay* this, t_player_command* command)
{
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->x == command->player->x && player->y == command->player->y)
	client_send_msg(player->client, "elevation en cours\n");
      it = list_iterator_next(it);
    }
}

void			gameplay_add_player_command(t_gameplay* this,
						    t_player_command* command)
{
  if ((strcmp(g_player_commands[command->id_command].request, "incantation") == 0 &&
       check_incant(this, command)) ||
      strcmp(g_player_commands[command->id_command].request, "incantation") != 0
      )
    {
      if (strcmp(g_player_commands[command->id_command].request, "fork") == 0)
	gameplay_send_egg(this, command->player)
      if (strcmp(g_player_commands[command->id_command].request, "incantation") == 0)
	send_incantation_start(this, command);
      player_add_action(command->player, command);
      if (list_size(command->player->command_queue) == 1)
	gameplay_update_player_position(this, command->player, this->players);
    }
  else
    client_send_msg(command->player->client, "ko");
}

void			gameplay_add_monitor_command(t_gameplay* this,
						     t_monitor_command* command)
{
  monitor_command_execute(command, this);
  monitor_command_delete(command);
}
