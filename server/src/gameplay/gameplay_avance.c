/*
** gameplay_avance.c for $ in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:05:48 2014 otoshigami
** Last update Sun Jul 13 18:05:49 2014 otoshigami
*/

#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "map.h"
#include "client.h"

void			gameplay_command_avance(t_gameplay* this, t_player_command* command)
{
  command->player->y +=
    (command->player->direction == NORTH) ? 1 :
    (command->player->direction == SOUTH) ? -1 : 0;
  command->player->x +=
    (command->player->direction == EAST) ? 1 :
    (command->player->direction == WEST) ? -1 : 0;
  if (command->player->y >= this->map.height)
    command->player->y = 0;
  if (command->player->y < 0)
    command->player->y = this->map.height;
  if (command->player->x >= this->map.width)
    command->player->x = 0;
  if (command->player->x < 0)
    command->player->x = this->map.width;
  gameplay_send_res(command->player->client, true);
  gameplay_send_pos(this, command->player);
}
