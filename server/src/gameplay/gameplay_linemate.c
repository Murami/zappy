#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			gameplay_take_linemate(t_gameplay *this,
					       t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (this->map.map[x + command->player->y * this->map.width].linemate != 0)
    {
      this->map.map[x + y * this->map.width].linemate--;
      command->player->inventory.linemate++;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 1);
      gameplay_send_res(command->player->client, true);
      gameplay_pop_linemate(this);
    }
  else
    gameplay_send_res(command->player->client, false);
}

void			gameplay_drop_linemate(t_gameplay *this,
					       t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (command->player->inventory.linemate > 0)
    {
      this->map.map[x + command->player-> y * this->map.width].linemate ++;
      command->player->inventory.linemate--;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 1);
      gameplay_send_res(command->player->client, true);
    }
  else
    gameplay_send_res(command->player->client, false);
}
