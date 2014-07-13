/*
** gameplay_send_take.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:08:02 2014 otoshigami
** Last update Sun Jul 13 18:11:32 2014 otoshigami
*/

#include <stdio.h>
#include "client.h"
#include "player_command.h"
#include "player.h"

void		gameplay_send_take(t_client *monitor,
				   t_player_command *command, int id)
{
  char		buffer[4096];

  sprintf(buffer, "pgt %d %d\n", command->player->id, id);
  client_send_msg(monitor, buffer);
}
