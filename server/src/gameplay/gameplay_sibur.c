#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			gameplay_take_sibur(t_gameplay *this,
					    t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (this->map.map[x + command->player->y * this->map.width].sibur != 0)
    {
      this->map.map[x + y * this->map.width].sibur--;
      command->player->inventory.sibur++;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 3);
      gameplay_send_res(command->player->client, true);
      gameplay_pop_sibur(this);
    }
  else
    gameplay_send_res(command->player->client, false);
}

void			gameplay_drop_sibur(t_gameplay *this,
					    t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (command->player->inventory.sibur > 0)
    {
      this->map.map[x + command->player-> y * this->map.width].sibur ++;
      command->player->inventory.sibur--;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 3);
      gameplay_send_res(command->player->client, true);
    }
  else
    gameplay_send_res(command->player->client, false);
}
