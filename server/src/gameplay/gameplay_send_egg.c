/*
** gameplay_send_egg.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:03:45 2014 otoshigami
** Last update Sun Jul 13 18:03:46 2014 otoshigami
*/

#include <stdio.h>
#include "gameplay.h"
#include "player.h"
#include "client.h"
#include "egg.h"

void			gameplay_send_egg(t_gameplay *this, t_player *player)
{
  t_list_iterator	it;
  t_client*		monitor;
  char			buffer[4096];

  printf("player [%d] fork\n", player->id);
  sprintf(buffer, "pfk %d\n", player->id);
  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}

void			gameplay_send_egg_lay(t_gameplay *this, t_player *player,
					      t_egg *egg)
{
  t_list_iterator	it;
  t_client*		monitor;
  char			buffer[4096];

  printf("new egg [%d] : by player [%d] on [%d, %d]\n",
	 egg->id, player->id, egg->x, egg->y);
  sprintf(buffer, "enw %d %d %d %d\n", egg->id, player->id, egg->x, egg->y);
  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}

void			gameplay_send_egg_hatch(t_gameplay *this, t_egg *egg)
{
  t_list_iterator	it;
  t_client*		monitor;
  char			buffer[4096];

  printf("egg [%d] hatch\n", egg->id);
  sprintf(buffer, "eht %d\n", egg->id);
  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      client_send_msg(monitor, buffer);
      it = list_iterator_next(it);
    }
}
