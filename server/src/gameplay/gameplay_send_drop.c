/*
** gameplay_send_drop.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:05:02 2014 otoshigami
** Last update Sun Jul 13 18:06:30 2014 otoshigami
*/

#include <stdio.h>
#include "client.h"
#include "player_command.h"
#include "player.h"

void		gameplay_send_drop(t_client *monitor,
				   t_player_command *command, int id)
{
  char		buffer[4096];

  sprintf(buffer, "pdr %d %d\n", command->player->id, id);
  client_send_msg(monitor, buffer);
}
