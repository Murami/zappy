/*
** gameplay_add_monitor.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:40:56 2014 otoshigami
** Last update Sun Jul 13 17:40:57 2014 otoshigami
*/

#include <stdlib.h>
#include "gameplay.h"
#include "team.h"
#include "player.h"
#include "monitor.h"
#include "client.h"
#include "client_player.h"
#include "client_graphic.h"
#include "monitor_command.h"

void			gameplay_add_monitor(t_gameplay* this, t_client* client)
{
  list_push_back(this->monitors, client);
  monitor_initialize(this, client);
}

void			gameplay_remove_monitor(t_gameplay* this, t_client* client)
{
  t_list_iterator	it;
  t_client_graphic*	tmp;

  it = list_begin(this->monitors);
  while (it != list_end(this->monitors))
    {
      tmp = it->data;
      if ((t_client*)tmp == client)
  	{
  	  it = list_erase(this->monitors, it);
  	  return;
  	}
      it = list_iterator_next(it);
    }
}
