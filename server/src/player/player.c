/*
** player.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:00:50 2014 otoshigami
** Last update Sun Jul 13 17:00:56 2014 otoshigami
*/

#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "client.h"
#include "team.h"
#include "gameplay.h"
#include "socketstream.h"
#include "client_player.h"
#include "time_val.h"
#include "list.h"

struct timeval		player_get_next_action_time(t_player* this)
{
  t_player_command*	command;

  command = list_front(this->command_queue);
  if (!command)
    return (this->death_time);
  if (timeval_comp(command->expiration_time, this->death_time) < 0)
    return (command->expiration_time);
  return (this->death_time);
}

bool			player_make_action(t_player* this, t_gameplay* gameplay,
					   struct timeval time)
{
  t_player_command*	command;

  command = list_front(this->command_queue);
  if (command == NULL)
    return (false);
  if (timeval_comp(command->expiration_time, time) < 0)
    {
      list_pop_front(this->command_queue);
      player_command_execute(command, gameplay);
      player_command_delete(command);
      return (true);
    }
  return (false);
}

bool			player_is_dead(t_player* this, struct timeval time)
{
  if (timeval_comp(this->death_time, time) < 0)
    return (true);
  return (false);
}

void			player_add_action(t_player* this,
					  t_player_command* command)
{
  if (list_size(this->command_queue) < 10)
    list_push_back(this->command_queue, command);
}

bool			player_need_update(t_player* this,
					   struct timeval time)
{
  t_player_command*	command;

  command = list_front(this->command_queue);
  if (command == NULL)
    return (player_is_dead(this, time));
  if (timeval_comp(command->expiration_time, time) < 0)
    return (true);
  return (player_is_dead(this, time));
}
