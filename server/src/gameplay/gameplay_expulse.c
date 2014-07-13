/*
** gameplay_expulse.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:38:30 2014 otoshigami
** Last update Sun Jul 13 17:38:31 2014 otoshigami
*/

#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "player_command.h"
#include "client.h"

void			bind_command_expulse(t_gameplay *this,
					     t_player_command *command)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_client*		monitor;

  sprintf(buffer, "pex %d\n", command->player->id);
  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}

void			gameplay_command_expulse(t_gameplay* this,
						 t_player_command* command)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_player*		player;
  bool			b;

  b = false;
  it = list_begin(this->players);
  sprintf(buffer, "deplacement: %d\n", ((command->player->direction + 2) % 4));
  bind_command_expulse(this, command);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->x == command->player->x && player->y == command->player->y &&
	  player->id != command->player->id)
	{
	  b = true;
	  gameplay_command_move(this, player);
	  gameplay_send_pos(this, player);
	  client_send_msg(player->client, buffer);
	}
      it = list_iterator_next(it);
    }
  gameplay_send_res(player->client, b);
}
