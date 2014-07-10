#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void		gameplay_take_sibur(t_gameplay *this, t_player_command *command)
{
  char			buffer[4096];

  if (this->map.map[command->player->x + command->player->y *
		    this->map.width].sibur != 0)
    {
      this->map.map[command->player->x + command->player->y *
		    this->map.width].sibur--;
      command->player->inventory.sibur++;
      sprintf(buffer, "ok");
      client_send_msg(command->player->client, buffer);
    }
  else
    {
      sprintf(buffer, "ko");
      client_send_msg(command->player->client, buffer);
    }
}

void		gameplay_drop_sibur(t_gameplay *this, t_player_command *command)
{
  char			buffer[4096];

  if (command->player->inventory.sibur > 0)
    {
      this->map.map[command->player->x + command->player-> y *
		    this->map.width].sibur ++;
      command->player->inventory.sibur--;
      sprintf(buffer, "ok");
      client_send_msg(command->player->client, buffer);
    }
  else
    {
      sprintf(buffer, "ko");
      client_send_msg(command->player->client, buffer);
    }
}