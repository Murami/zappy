/*
** gameplay_phiras.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:35:55 2014 otoshigami
** Last update Sun Jul 13 17:35:56 2014 otoshigami
*/

#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			gameplay_take_phiras(t_gameplay *this,
					     t_player_command *command)
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
      gameplay_pop_phiras(this);
    }
  else
    gameplay_send_res(command->player->client, false);
}

void			gameplay_drop_phiras(t_gameplay *this,
					     t_player_command *command)
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
