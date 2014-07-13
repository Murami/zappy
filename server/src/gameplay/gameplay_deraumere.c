#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			gameplay_take_deraumere(t_gameplay *this,
						t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (this->map.map[x + command->player->y * this->map.width].deraumere != 0)
    {
      this->map.map[x + y * this->map.width].deraumere--;
      command->player->inventory.deraumere++;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 2);
      gameplay_send_res(command->player->client, true);
      gameplay_pop_deraumere(this);
    }
  else
    gameplay_send_res(command->player->client, false);
}

void			gameplay_drop_deraumere(t_gameplay *this,
						t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (command->player->inventory.deraumere > 0)
    {
      this->map.map[x + command->player-> y * this->map.width].deraumere ++;
      command->player->inventory.deraumere--;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 2);
      gameplay_send_res(command->player->client, true);
    }
  else
    gameplay_send_res(command->player->client, false);
}
