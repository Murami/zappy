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

bool	egg_need_update(t_egg* egg, struct timeval currenttime)
{
  if (timeval_comp(currenttime, egg->time) >= 0)
    return (true);
  return (false);
}

void	egg_hatch(t_gameplay* gameplay, t_egg* egg)
{
  /* FREE THE EGG !!! */
  (void) gameplay;
  (void) egg;

  t_player*	player;

  player = malloc(sizeof(player));
  player->is_egg = true;
  player->client = NULL;
  player->it = NULL;
  gameplay_update_player_position(gameplay, player, gameplay->ghosts);
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

struct timeval		gameplay_update_players(t_gameplay* this, struct timeval currenttime,
						t_list* list,
						t_list_iterator (*kill_player)(t_gameplay*, struct s_player*))
{
  struct timeval	waiting_time;
  t_player*		player;
  t_list_iterator	it;

  waiting_time.tv_sec = 0;
  waiting_time.tv_usec = 0;
  it = list_begin(list);
  while (it != list_end(list) && player_need_update(it->data, currenttime))
    {
      player = it->data;
      if (player_is_dead(it->data, currenttime))
	it = kill_player(this, it->data);
      else
	{
	  if (player_make_action(player, this, currenttime))
	    {
	      it = list_iterator_prev(it);
	      while (player_make_action(player, this, currenttime));
	      gameplay_update_player_position(this, player, list);
	    }
	}
      it = list_iterator_next(it);
    }
  if (!list_empty(list))
    waiting_time = player_get_next_action_time(list_front(list));
  if (waiting_time.tv_sec == 0 && waiting_time.tv_usec == 0)
    return (waiting_time);
  return (timeval_sub(waiting_time, currenttime));
}

struct timeval		gameplay_update(t_gameplay *this, struct timeval currenttime)
{
  struct timeval	waiting1;
  struct timeval	waiting2;

  waiting1 = gameplay_update_players(this, currenttime, this->players, gameplay_kill_player);
  waiting2 = gameplay_update_players(this, currenttime, this->ghosts, gameplay_kill_ghost);
  waiting1 = timeval_min_nz(waiting1, waiting2);
  waiting2 = gameplay_update_eggs(this, currenttime);
  return (timeval_min_nz(waiting1, waiting2));
}

void			gameplay_update_player_position(t_gameplay* this, t_player* player, t_list* list)
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

/* FREE SLOTS ???? */

t_list_iterator		gameplay_kill_player(t_gameplay* this, t_player* player)
{
  /* JUST SEND THE MSG FOR THE DEATH IS NOT DONE */
  t_list_iterator	it;

  it = list_iterator_prev(player->it);
  server_remove(this->server, player->client);
  list_erase(this->players, player->it);
  client_delete(player->client);
  free(player);
  return (it);
}

t_list_iterator		gameplay_kill_ghost(t_gameplay* this, t_player* player)
{
  /* JUST SEND THE MSG FOR THE DEATH IS NOT DONE */
  t_list_iterator	it;

  it = list_iterator_prev(player->it);
  list_erase(this->ghosts, player->it);
  free(player);
  return (it);
}
