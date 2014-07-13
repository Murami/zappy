/*
** gameplay.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:37:29 2014 otoshigami
** Last update Sun Jul 13 21:39:41 2014 Desabre Quentin
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameplay.h"
#include "socketstream.h"
#include "client.h"
#include "player.h"
#include "server.h"
#include "monitor.h"
#include "player_command.h"
#include "monitor_command.h"
#include "client_player.h"
#include "client_graphic.h"
#include "player.h"
#include "team.h"
#include "time_val.h"
#include "egg.h"

t_list_iterator		gameplay_make_actions(t_gameplay* this,
					      struct timeval currenttime,
					      t_list* list, t_list_iterator it)
{
  t_list_iterator	it_prev;

  if (player_make_action(it->data, this, currenttime))
    {
      it_prev = list_iterator_prev(it);
      while (player_make_action(it->data, this, currenttime));
      gameplay_update_player_position(this, it->data, list);
    }
  return (it_prev);
}

struct timeval		gameplay_update_players(t_gameplay* this,
						struct timeval currenttime,
						t_list* list, kill_func kill_player)
{
  struct timeval	waiting_time;
  t_list_iterator	it;

  waiting_time.tv_sec = 0;
  waiting_time.tv_usec = 0;
  it = list_begin(list);
  while (it != list_end(list) && player_need_update(it->data, currenttime))
    {
      if (player_is_dead(it->data, currenttime))
	it = kill_player(this, it->data);
      else
	it = gameplay_make_actions(this, currenttime, list, it);
      it = list_iterator_next(it);
    }
  if (!list_empty(list))
    waiting_time = player_get_next_action_time(list_front(list));
  if (waiting_time.tv_sec == 0 && waiting_time.tv_usec == 0)
    return (waiting_time);
  return (timeval_sub(waiting_time, currenttime));
}

struct timeval		gameplay_update(t_gameplay *this,
					struct timeval currenttime)
{
  struct timeval	waiting1;
  struct timeval	waiting2;

  waiting1 = gameplay_update_players(this, currenttime,
				     this->players, gameplay_kill_player);
  waiting2 = gameplay_update_players(this, currenttime,
				     this->ghosts, gameplay_kill_ghost);
  waiting1 = timeval_min_nz(waiting1, waiting2);
  waiting2 = gameplay_update_eggs(this, currenttime);
  return (timeval_min_nz(waiting1, waiting2));
}

void			gameplay_update_player_position(t_gameplay* this,
							t_player* player,
							t_list* list)
{
  t_list_iterator	it;
  struct timeval	time_tomove;
  struct timeval	time_current;

  (void) this;
  if (player->it)
    list_erase(list, player->it);
  it = list_begin(list);
  time_tomove = player_get_next_action_time(player);
  while (it != list_end(list))
    {
      time_current = player_get_next_action_time(it->data);
      if (timeval_comp(time_current, time_tomove) < 0)
	{
	  player->it = list_insert(list, it, player);
	  return;
	}
      it = list_iterator_next(it);
    }
  player->it = list_insert(list, it, player);
}
