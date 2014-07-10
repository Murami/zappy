#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			gameplay_command_inventaire(t_gameplay* this, t_player_command* command)
{
  char			buffer[4096];
  (void) this;

  sprintf(buffer, "{nourriture %d, linemate %d, deraumere %d, "
	  "sibur %d, mendiane %d, phiras %d, thystame %d}",
	  command->player->inventory.food,
	  command->player->inventory.linemate,
	  command->player->inventory.deraumere,
	  command->player->inventory.sibur,
	  command->player->inventory.mendiane,
	  command->player->inventory.phiras,
	  command->player->inventory.thystame);
  client_send_msg(command->player->client, buffer);
}

void			gameplay_command_pose(t_gameplay* this, t_player_command* command)
{
  if (strcmp(command->data, "nourriture") == 0)
    gameplay_drop_food(this, command);
  else if (strcmp(command->data, "linemate") == 0)
    gameplay_drop_linemate(this, command);
  else if (strcmp(command->data, "deraumere") == 0)
    gameplay_drop_deraumere(this, command);
  else if (strcmp(command->data, "sibur") == 0)
    gameplay_drop_sibur(this, command);
  else if (strcmp(command->data, "mendiane") == 0)
    gameplay_drop_mendiane(this, command);
  else if (strcmp(command->data, "phiras") == 0)
    gameplay_drop_phiras(this, command);
  else if (strcmp(command->data, "thystame") == 0)
    gameplay_drop_thystame(this, command);
}

void			gameplay_command_prend(t_gameplay* this, t_player_command* command)
{
  if (strcmp(command->data, "nourriture") == 0)
    gameplay_take_food(this, command);
  else if (strcmp(command->data, "linemate") == 0)
    gameplay_take_linemate(this, command);
  else if (strcmp(command->data, "deraumere") == 0)
    gameplay_take_deraumere(this, command);
  else if (strcmp(command->data, "sibur") == 0)
    gameplay_take_sibur(this, command);
  else if (strcmp(command->data, "mendiane") == 0)
    gameplay_take_mendiane(this, command);
  else if (strcmp(command->data, "phiras") == 0)
    gameplay_take_phiras(this, command);
  else if (strcmp(command->data, "thystame") == 0)
    gameplay_take_thystame(this, command);
}
