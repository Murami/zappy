/*
** gameplay_monitor_update.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:17:53 2014 quentin desabre
** Last update Sun Jul 13 16:39:34 2014 Desabre Quentin
*/

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
