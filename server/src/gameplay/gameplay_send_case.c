/*
** gameplay_send_case.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:37:51 2014 otoshigami
** Last update Sun Jul 13 17:37:52 2014 otoshigami
*/

#include <stdio.h>
#include "player.h"
#include "gameplay.h"
#include "client.h"

void			gameplay_send_case(t_client *monitor, t_case *c)
{
  char			buff[4096];

  sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n",
	  c->x, c->y, c->food, c->linemate, c->deraumere, c->sibur, c->mendiane,
	  c->phiras, c->thystame);
  client_send_msg(monitor, buff);
}

void			gameplay_send_case_all(t_gameplay *this, t_player *player)
{
  t_list_iterator	it;
  t_client*		monitor;

  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      gameplay_send_case(monitor,
			 &this->map.map[player->x + player->y * this->map.width]);
      it = list_iterator_next(it);
    }
}

void			gameplay_send_case_all2(t_gameplay *this, int x, int y)
{
  t_list_iterator	it;
  t_client*		monitor;

  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      monitor = it->data;
      gameplay_send_case(monitor,
			 &this->map.map[x + y * this->map.width]);
      it = list_iterator_next(it);
    }
}
