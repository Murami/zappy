#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			gameplay_take_mendiane(t_gameplay *this,
					       t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (this->map.map[x + command->player->y * this->map.width].mendiane != 0)
    {
      this->map.map[x + y * this->map.width].mendiane--;
      command->player->inventory.mendiane++;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 4);
      gameplay_send_res(command->player->client, true);
      gameplay_pop_mendiane(this);
    }
  else
    gameplay_send_res(command->player->client, false);
}

void			gameplay_drop_mendiane(t_gameplay *this,
					       t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (command->player->inventory.mendiane > 0)
    {
      this->map.map[x + command->player-> y * this->map.width].mendiane ++;
      command->player->inventory.mendiane--;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 4);
      gameplay_send_res(command->player->client, true);
    }
  else
    gameplay_send_res(command->player->client, false);
}
