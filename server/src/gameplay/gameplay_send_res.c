/*
** gameplay_send_res.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:04:10 2014 otoshigami
** Last update Sun Jul 13 18:04:11 2014 otoshigami
*/

#include <stdbool.h>
#include <stdio.h>
#include "client.h"
#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "client_player.h"

void			gameplay_send_res(t_client *client, bool b)
{
  char			buffer[4096];

  if (b == true)
    sprintf(buffer, "ok\n");
  else
    sprintf(buffer, "ko\n");
  client_send_msg(client, buffer);
}

void			gameplay_send_res_incant(t_gameplay *this,
						 t_player_command *command, bool b)
{
  t_list_iterator	it;
  t_client*		monitor;
  char			buffer[4096];

  if (b)
    sprintf(buffer, "pie %d %d 1\n", command->player->x, command->player->y);
  else
    sprintf(buffer, "pie %d %d 0\n", command->player->x, command->player->y);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}
