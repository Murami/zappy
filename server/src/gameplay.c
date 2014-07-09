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
#include "player.h"
#include "team.h"

void		gameplay_initialize(t_gameplay *this, t_config config)
{
  memset(this, 0, sizeof(t_gameplay));
  this->players = list_new();
  this->monitors = list_new();
  this->teams = config.teams;
  map_initialize(&this->map, config.width, config.height);
  this->delay = config.delay;
  gettimeofday(&this->time, NULL);
}

t_gameplay*    	gameplay_new(t_config config)
{
  t_gameplay	*gameplay;

  gameplay = malloc(sizeof(t_gameplay));
  if (!gameplay)
    return (NULL);
  gameplay_initialize(gameplay, config);
  return (gameplay);
}

void			gameplay_remove_player(t_gameplay* this, t_client* client)
{
  (void)this;
  (void)client;
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
  (void)this;
  (void)client;
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
  (void) command;
  (void) this;
  printf("le début de la fin du serveur\n");
}

void			gameplay_command_droite(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_gauche(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_voir(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_inventaire(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_prend_objet(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_expulse(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_broadcast(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_incantation(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_fork(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
}

void			gameplay_command_connect_nbr(t_gameplay* this, t_player_command* command)
{
  (void) command;
  (void) this;
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
  (void) this;
  (void) command;
  /* EXECUTE LA COMMANDE DIRECTE TT LE TEMPS */
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

  it = player->it;
  client_delete(player->client);
  free(player);
  return (list_erase(this->players, it));
}
