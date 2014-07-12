#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			gameplay_take_deraumere(t_gameplay *this, t_player_command *command)
{
  char			buffer[4096];

  if (this->map.map[command->player->x + command->player->y *
		    this->map.width].deraumere != 0)
    {
      this->map.map[command->player->x + command->player->y *
		    this->map.width].deraumere--;
      command->player->inventory.deraumere++;
      bind_command_take(this,
			&this->map.map[command->player->x + this->map.width * command->player->y]);
      sprintf(buffer, "ok\n");
      client_send_msg(command->player->client, buffer);
    }
  else
    {
      sprintf(buffer, "ko\n");
      client_send_msg(command->player->client, buffer);
    }
}

void			gameplay_drop_deraumere(t_gameplay *this, t_player_command *command)
{
  char			buffer[4096];

  if (command->player->inventory.deraumere > 0)
    {
      this->map.map[command->player->x + command->player-> y *
		    this->map.width].deraumere ++;
      command->player->inventory.deraumere--;
      bind_command_take(this,
			&this->map.map[command->player->x + this->map.width * command->player->y]);
      sprintf(buffer, "ok\n");
      client_send_msg(command->player->client, buffer);
    }
  else
    {
      sprintf(buffer, "ko\n");
      client_send_msg(command->player->client, buffer);
    }
}
