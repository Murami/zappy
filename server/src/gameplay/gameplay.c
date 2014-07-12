#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameplay.h"
#include "socketstream.h"
#include "client.h"
#include "player.h"
#include "server.h"
#include "monitors.h"
#include "player_command.h"
#include "monitor_command.h"
#include "client_player.h"
#include "client_graphic.h"
#include "player.h"
#include "team.h"
#include "time_val.h"
#include "egg.h"

bool			egg_need_update(t_egg* egg, struct timeval currenttime)
{
  if (timeval_comp(currenttime, egg->time) >= 0)
    return (true);
  return (false);
}

void		       egg_hatch(t_gameplay* gameplay, t_egg* egg)
{
  (void) gameplay;
  (void) egg;
  /* MAKE HATCH EGG */
}

struct timeval		gameplay_update_eggs(t_gameplay* this, struct timeval currenttime)
{
  struct timeval	waiting_time;
  t_list_iterator	it;

  waiting_time.tv_sec = 0;
  waiting_time.tv_usec = 0;
  it = list_begin(this->eggs);
  while (it != list_end(this->eggs) &&
	 egg_need_update(it->data, currenttime))
    {
      egg_hatch(this, it->data);
      it = list_erase(this->eggs, it->data);
      it = list_iterator_next(it);
    }
  if (!list_empty(this->eggs))
    return (timeval_sub(((t_egg*)list_front(this->eggs))->time, currenttime));
  return (waiting_time);
}

struct timeval		gameplay_update_players(t_gameplay* this, struct timeval currenttime)
{
  struct timeval	waiting_time;
  t_player*		player;
  t_list_iterator	it;

  waiting_time.tv_sec = 0;
  waiting_time.tv_usec = 0;
  it = list_begin(this->players);
  while (it != list_end(this->players) && player_need_update(it->data, currenttime))
    {
      player = it->data;
      if (player_is_dead(it->data, currenttime))
	it = gameplay_kill_player(this, it->data);
      else
	{
	  if (player_make_action(player, this, currenttime))
	    {
	      it = list_iterator_prev(it);
	      while (player_make_action(player, this, currenttime));
	      gameplay_update_player_position(this, player);
	    }
	}
      it = list_iterator_next(it);
    }
  if (!list_empty(this->players))
    waiting_time = player_get_next_action_time(list_front(this->players));
  if (waiting_time.tv_sec == 0 && waiting_time.tv_usec == 0)
    return (waiting_time);
  return (timeval_sub(waiting_time, currenttime));
}

struct timeval		gameplay_update(t_gameplay *this, struct timeval currenttime)
{
  struct timeval	waiting1;
  struct timeval	waiting2;

  waiting1 = gameplay_update_players(this, currenttime);
  waiting2 = gameplay_update_eggs(this, currenttime);
  if (timeval_comp(waiting1, waiting2) > 0)
    return (waiting2);
  return (waiting1);
}

void			gameplay_update_player_position(t_gameplay* this, t_player* player)
{
  t_list_iterator	it;
  struct timeval	time_tomove;
  struct timeval	time_current;

  printf("ON RENTRE DANS UPDATE POS PLAYER !\n");
  list_erase(this->players, player->it);
  it = list_begin(this->players);
  time_tomove = player_get_next_action_time(player);
  while (it != list_end(this->players))
    {
      time_current = player_get_next_action_time(it->data);
      if (timeval_comp(time_current, time_tomove) < 0)
	{
	  player->it = list_insert(this->players, it, player);
	  return;
	}
      it = list_iterator_next(it);
    }
  player->it = list_insert(this->players, it, player);
}

t_list_iterator		gameplay_kill_player(t_gameplay* this, t_player* player)
{
  /* JUST SEND THE MSG FOR THE DEATH IS NOT DONE */
  t_list_iterator	it;

  printf("%p\n", player->it);
  it = list_iterator_prev(player->it);
  printf("%p -- %p\n", it, it->prev);
  client_remove(player->client, this->server);
  server_remove(this->server, player->client);
  return (it);
}
