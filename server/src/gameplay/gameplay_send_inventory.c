/*
** gameplay_send_inventory.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:36:05 2014 otoshigami
** Last update Sun Jul 13 17:36:06 2014 otoshigami
*/

#include <stdio.h>
#include "player_command.h"
#include "player.h"
#include "client.h"

void	       	gameplay_send_inventory(t_client *monitor,
					t_player_command *command)
{
  char		buffer[4096];

  sprintf(buffer, "pin %d %d %d %d %d %d %d %d %d %d\n",
	  command->player->id,
	  command->player->x,
	  command->player->y,
	  command->player->inventory.food,
	  command->player->inventory.linemate,
	  command->player->inventory.deraumere,
	  command->player->inventory.sibur,
	  command->player->inventory.mendiane,
	  command->player->inventory.phiras,
	  command->player->inventory.thystame);
  client_send_msg(monitor, buffer);
}
