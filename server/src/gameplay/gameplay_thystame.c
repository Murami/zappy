/*
** gameplay_thystame.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:39:35 2014 otoshigami
** Last update Sun Jul 13 17:39:36 2014 otoshigami
*/

#include <stdio.h>
#include <string.h>
#include "gameplay.h"
#include "player_command.h"
#include "player.h"
#include "client.h"

void			gameplay_take_thystame(t_gameplay *this,
					       t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (this->map.map[x + command->player->y * this->map.width].thystame != 0)
    {
      this->map.map[x + y * this->map.width].thystame--;
      command->player->inventory.thystame++;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 6);
      gameplay_send_res(command->player->client, true);
      gameplay_pop_thystame(this);
    }
  else
    gameplay_send_res(command->player->client, false);
}

void			gameplay_drop_thystame(t_gameplay *this,
					       t_player_command *command)
{
  int			x;
  int			y;

  x = command->player->x;
  y = command->player->y;
  if (command->player->inventory.thystame > 0)
    {
      this->map.map[x + command->player-> y * this->map.width].thystame ++;
      command->player->inventory.thystame--;
      bind_command_object(this, command,
			  &this->map.map[x + this->map.width * y], 6);
      gameplay_send_res(command->player->client, true);
    }
  else
    gameplay_send_res(command->player->client, false);
}
