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

void		gameplay_initialize(t_gameplay *this, t_config config, t_server* server)
{
  memset(this, 0, sizeof(t_gameplay));
  this->players = list_new();
  this->monitors = list_new();
  this->teams = config.teams;
  map_initialize(&this->map, config.width, config.height);
  this->delay = config.delay;
  this->server = server;
  gettimeofday(&this->time, NULL);
}

t_gameplay*    	gameplay_new(t_config config, t_server* server)
{
  t_gameplay	*gameplay;

  gameplay = malloc(sizeof(t_gameplay));
  if (!gameplay)
    return (NULL);
  gameplay_initialize(gameplay, config, server);
  return (gameplay);
}

void			gameplay_remove_player(t_gameplay* this, t_client* client)
{
  t_player*		player;

  (void) this;
  player = ((t_client_player*)client)->player;
  client_delete(client);
  free(player);
}

void			gameplay_add_player(t_gameplay* this, t_client* client, t_team *team)
{
  t_player*	player;

  player = player_new(this, client, team);
  list_push_back(this->players, player);
  player->it = list_back(this->players);
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

void			gameplay_add_monitor(t_gameplay* this, t_client* client)
{
  list_push_back(this->monitors, client);
  monitor_initialize(this, client);
}

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

void			gameplay_command_inventaire(t_gameplay* this, t_player_command* command)
{
  char			buffer[4096];
  (void) this;

  sprintf(buffer, "{nourriture %d, linemate %d, deraumere %d, "
	  "sibur %d, mendiane %d, phiras %d, thystame %d}",
	  command->player->inventory.food,
	  command->player->inventory.linemate,
	  command->player->inventory.deraumere,
	  command->player->inventory.sibur,
	  command->player->inventory.mendiane,
	  command->player->inventory.phiras,
	  command->player->inventory.thystame);
  client_send_msg(command->player->client, buffer);
}

void			gameplay_command_prend(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_pose(t_gameplay* this, t_player_command* command)
{
  char			buffer[4096];

  if (strcmp(command->data, "nourriture") == 0)
    {
      if (this->map.map[command->player->x + command->player->y *
			this->map.width].food != 0)
	{
	  command->player->inventory.food++;
	  sprintf(buffer, "ok");
	  client_send_msg(command->player->client, buffer);
	  return;
	}
    }
  else if (strcmp(command->data, "linemate") == 0)
    {
      if (this->map.map[command->player->x + command->player->y *
			this->map.width].linemate != 0)
	{
	  command->player->inventory.linemate++;
	  sprintf(buffer, "ok");
	  client_send_msg(command->player->client, buffer);
	  return;
	}
    }
  else if (strcmp(command->data, "deraumere") == 0)
    {
      if (this->map.map[command->player->x + command->player->y *
			this->map.width].deraumere != 0)
	{
	  command->player->inventory.deraumere++;
	  sprintf(buffer, "ok");
	  client_send_msg(command->player->client, buffer);
	  return;
	}
    }
  else if (strcmp(command->data, "sibur") == 0)
    {
      if (this->map.map[command->player->x + command->player->y *
			this->map.width].sibur != 0)
	{
	  command->player->inventory.sibur++;
	  sprintf(buffer, "ok");
	  client_send_msg(command->player->client, buffer);
	  return;
	}
    }
  else if (strcmp(command->data, "mendiane") == 0)
    {
      if (this->map.map[command->player->x + command->player->y *
			this->map.width].mendiane != 0)
	{
	  command->player->inventory.mendiane++;
	  sprintf(buffer, "ok");
	  client_send_msg(command->player->client, buffer);
	  return;
	}
    }
  else if (strcmp(command->data, "phiras") == 0)
    {
      if (this->map.map[command->player->x + command->player->y *
			this->map.width].phiras != 0)
	{
	  command->player->inventory.phiras++;
	  sprintf(buffer, "ok");
	  client_send_msg(command->player->client, buffer);
	  return;
	}
    }
  else if (strcmp(command->data, "thystame") == 0)
    {
      if (this->map.map[command->player->x + command->player->y *
			this->map.width].thystame != 0)
	{
	  command->player->inventory.thystame++;
	  sprintf(buffer, "ok");
	  client_send_msg(command->player->client, buffer);
	  return;
	}
    }
  sprintf(buffer, "ko");
  client_send_msg(command->player->client, buffer);
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
  (void) command;
  (void) this;
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

void			gameplay_add_monitor_command(t_gameplay* this, t_monitor_command* command)
{
  monitor_command_execute(command, this);
}

void			gameplay_release(t_gameplay *this)
{
  list_delete(this->teams);
  list_delete(this->players);
  map_release(&this->map);
}

void			gameplay_delete(t_gameplay *this)
{
  gameplay_release(this);
  free(this);
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
