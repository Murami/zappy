#include <stdio.h>
#include <stdlib.h>
#include "gameplay.h"
#include "player.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"
#include "monitor_command.h"
#include "time_val.h"
#include "egg.h"

void			gameplay_command_msz(t_gameplay* this,
					     t_monitor_command* command)
{
  monitor_send_size(this, &command->client->parent_client);
}

void			gameplay_command_bct(t_gameplay* this,
					     t_monitor_command* command)
{
  int			x;
  int			y;
  char*			ptr;

  ptr = command->data[0];
  x = strtol(command->data[0], &ptr, 10);
  if (*ptr == '\0')
    {
      gameplay_send_sbp(&command->client->parent_client);
      return;
    }
  ptr = command->data[1];
  y = strtol(command->data[1], &ptr, 10);
  if (ptr == '\0')
    {
      gameplay_send_sbp(&command->client->parent_client);
      return;
    }
  monitor_send_case(&command->client->parent_client,
		    &this->map.map[x + y * this->map.width]);
}

void			gameplay_command_mct(t_gameplay* this,
					     t_monitor_command* command)
{
  monitor_send_map(this, &command->client->parent_client);
}

void			gameplay_command_tna(t_gameplay* this,
					     t_monitor_command* command)
{
  monitor_send_teams(this, &command->client->parent_client);
}

void			gameplay_command_ppo(t_gameplay* this,
					     t_monitor_command* command)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->id == atoi(command->data[0]))
	{
	  sprintf(buffer, "ppo %d %d %d %d\n",
		  player->id,
		  player->x,
		  player->y,
		  player->direction);
	  client_send_msg(&command->client->parent_client, buffer);
	  return;
	}
      it = list_iterator_next(it);
    }
  gameplay_send_sbp(&command->client->parent_client);
}

void			gameplay_command_pin(t_gameplay* this,
					     t_monitor_command* command)
{
  char			buffer[4096];
  t_list_iterator	it;
  t_player*		player;

  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      player = it->data;
      if (player->id == atoi(command->data[0]))
	{
	  sprintf(buffer, "pin %d %d %d %d %d %d %d %d %d %d\n",
		  player->id, player->x, player->y,
		  player->inventory.food,
		  player->inventory.linemate,
		  player->inventory.deraumere,
		  player->inventory.sibur,
		  player->inventory.mendiane,
		  player->inventory.phiras,
		  player->inventory.thystame);
	  client_send_msg(&command->client->parent_client, buffer);
	  return;
	}
      it = list_iterator_next(it);
    }
  gameplay_send_sbp(&command->client->parent_client);
}

void			gameplay_command_sgt(t_gameplay* this,
					     t_monitor_command* command)
{
  monitor_send_delay(this, &command->client->parent_client);
}

struct timeval		get_updated_time(struct timeval currenttime,
					 struct timeval time,
					 int old_delay, int new_delay)
{
  struct timeval	diff;

  diff = timeval_sub(time, currenttime);
  diff.tv_usec += diff.tv_sec * 1000000;
  diff.tv_usec *= old_delay;
  diff.tv_usec /= new_delay;
  diff.tv_sec = diff.tv_usec / 1000000;
  diff.tv_usec %= 1000000;
  return (timeval_add(currenttime, diff));
}

void			update_egg_time(t_gameplay* this, int old_delay, t_egg* egg)
{
  egg->time = get_updated_time(this->time, egg->time, old_delay, this->delay);
}

void			update_command_time(t_gameplay* this, int old_delay,
					    t_player_command* command)
{
  command->expiration_time = get_updated_time(this->time,
					      command->expiration_time,
					      old_delay, this->delay);
}

void			update_player_times(t_gameplay* this,
					    int old_delay, t_player* player)
{
  t_list_iterator	it;

  it = list_begin(player->command_queue);
  while (it != list_end(player->command_queue))
    {
      update_command_time(this, old_delay, it->data);
      it = list_iterator_next(it);
    }
  player->death_time = get_updated_time(this->time,
					player->death_time, old_delay, this->delay);
}

void			gameplay_update_all_times(t_gameplay* this, int old_delay)
{
  t_list_iterator	it;

  it = list_begin(this->players);
  while (it != list_end(this->players))
    {
      update_player_times(this, old_delay, it->data);
      it = list_iterator_next(it);
    }
  it = list_begin(this->ghosts);
  while (it != list_end(this->ghosts))
    {
      update_player_times(this, old_delay, it->data);
      it = list_iterator_next(it);
   }
  it = list_begin(this->eggs);
  while (it != list_end(this->eggs))
    {
      update_egg_time(this, old_delay, it->data);
      it = list_iterator_next(it);
    }
}

void			gameplay_command_sst(t_gameplay* this,
					     t_monitor_command* command)
{
  int			old_delay;
  char*			ptr;

  old_delay = this->delay;
  ptr = command->data[0];
  this->delay = strtol(command->data[0], &ptr, 10);
  if (ptr == '\0' || this->delay == 0)
    {
      this->delay = old_delay;
      gameplay_send_sbp(&command->client->parent_client);
      return;
    }
  monitor_send_delay(this, &command->client->parent_client);
  gameplay_update_all_times(this, old_delay);
}
