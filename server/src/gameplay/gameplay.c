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

struct timeval		gameplay_update(t_gameplay *this, struct timeval currenttime)
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
  return (waiting_time);
}

void			gameplay_command_avance(t_gameplay* this, t_player_command* command)
{
  command->player->y +=
    (command->player->direction == NORTH) ? 1 :
    (command->player->direction == SOUTH) ? -1 : 0;
  command->player->x +=
    (command->player->direction == EAST) ? 1 :
    (command->player->direction == WEST) ? -1 : 0;
  if (command->player->y >= this->map.height)
    command->player->y = 0;
  if (command->player->y < 0)
    command->player->y = this->map.height;
  if (command->player->x >= this->map.width)
    command->player->x = 0;
  if (command->player->x < 0)
    command->player->x = this->map.width;
}

void			gameplay_command_droite(t_gameplay* this, t_player_command* command)
{
  (void)this;
  command->player->direction += 1;
  if (command->player->direction >= 5)
    command->player->direction = 0;
  client_send_msg(command->player->client, "ok");
}

void			gameplay_command_gauche(t_gameplay* this, t_player_command* command)
{
  (void)this;
  command->player->direction -= 1;
  if (command->player->direction <= 0)
    command->player->direction = 4;
  client_send_msg(command->player->client, "ok");
}

void			gameplay_command_voir(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}


void			gameplay_command_move(t_gameplay* this, t_player* player)
{
  player->y +=
    (player->direction == NORTH) ? 1 :
    (player->direction == SOUTH) ? -1 : 0;
  player->x +=
    (player->direction == EAST) ? 1 :
    (player->direction == WEST) ? -1 : 0;
  if (player->y >= this->map.height)
    player->y = 0;
  if (player->y < 0)
    player->y = this->map.height;
  if (player->x >= this->map.width)
    player->x = 0;
  if (player->x < 0)
    player->x = this->map.width;
}

void			gameplay_command_expulse(t_gameplay* this, t_player_command* command)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(this->players);
  sprintf(buffer, "deplacement: %d\n", ((command->player->direction + 2) % 4));
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->x == command->player->x && player->y == command->player->y &&
	  player->id != command->player->id)
	{
	  gameplay_command_move(this, player);
	  client_send_msg(player->client, buffer);
	}
      it = list_iterator_next(it);
    }
}

void			gameplay_command_broadcast(t_gameplay* this, t_player_command* command)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(this->players);
  // le 1 est a changer par la direction mais faut voir avec guerot
  sprintf(buffer, "message %d,%s\n", 1, command->data);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->id != command->player->id)
	{
	  client_send_msg(player->client, command->data);
	}
      it = list_iterator_next(it);
    }
}

void			gameplay_command_incantation(t_gameplay* this,
						     t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_fork(t_gameplay* this,
					      t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_connect_nbr(t_gameplay* this,
						     t_player_command* command)
{
  char			buffer[4096];

  (void) this;
  sprintf(buffer, "%d", command->player->team->nb_slots);
  client_send_msg(command->player->client, buffer);
}

void			gameplay_add_player_command(t_gameplay* this, t_player_command* command)
{
  player_add_action(command->player, command);
  if (list_size(command->player->command_queue) == 1)
    gameplay_update_player_position(this, command->player);
}

void			gameplay_command_msz(t_gameplay* this, struct s_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_bct(t_gameplay* this, struct s_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_mct(t_gameplay* this, struct s_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_tna(t_gameplay* this, struct s_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_ppo(t_gameplay* this, struct s_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_plv(t_gameplay* this, struct s_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_pin(t_gameplay* this, struct s_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_sgt(t_gameplay* this, struct s_monitor_command* command)
{
  (void) this;
  (void) command;
}

void			gameplay_command_sst(t_gameplay* this, struct s_monitor_command* command)
{
  (void) this;
  (void) command;
}


void			gameplay_update_player_position(t_gameplay* this, t_player* player)
{
  t_list_iterator	it;
  struct timeval	time_tomove;
  struct timeval	time_current;

  list_erase(this->players, player->it);
  it = list_begin(this->players);
  time_tomove = player_get_next_action_time(player);
  while (it != list_end(this->players))
    {
      time_current = player_get_next_action_time(it->data);
      if (time_current.tv_sec < time_tomove.tv_sec ||
	  (time_current.tv_sec == time_tomove.tv_sec &&
	   time_current.tv_usec < time_tomove.tv_usec))
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

  it = list_iterator_prev(player->it);
  client_remove(player->client, this->server);
  return (it);
}
