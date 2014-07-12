#include <stdio.h>
#include "player_command.h"
#include "player.h"
#include "client.h"

void	       	gameplay_send_inventory(t_client *monitor,
					t_player_command *command)
{
  char		buffer[4096];

  sprintf(buffer, "pin %d %d %d %d %d %d %d %d %d %d\n",
	  command->player->id,
	  command->player->x,
	  command->player->y,
	  command->player->inventory.food,
	  command->player->inventory.linemate,
	  command->player->inventory.deraumere,
	  command->player->inventory.sibur,
	  command->player->inventory.mendiane,
	  command->player->inventory.phiras,
	  command->player->inventory.thystame);
  client_send_msg(monitor, buffer);
}
