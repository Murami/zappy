#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			gameplay_take_phiras(t_gameplay *this, t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (this->map.map[x + command->player->y * this->map.width].phiras != 0)
    {
      this->map.map[x + y * this->map.width].phiras--;
      command->player->inventory.phiras++;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 5);
      gameplay_send_res(command->player->client, true);
    }
  else
    gameplay_send_res(command->player->client, false);
}

void			gameplay_drop_phiras(t_gameplay *this, t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (command->player->inventory.phiras > 0)
    {
      this->map.map[x + command->player-> y * this->map.width].phiras ++;
      command->player->inventory.phiras--;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 5);
      gameplay_send_res(command->player->client, true);
    }
  else
    gameplay_send_res(command->player->client, false);
}
