#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "client.h"
#include "team.h"
#include "gameplay.h"
#include "socketstream.h"
#include "client_player.h"

/* INIT DU DEAHT TIME EN BRUT A FAIRE EN FONCTION DE LA BOUFE ET DU DELAY */

void		player_initialize(t_player *this, t_gameplay *gameplay,
				  t_client *client, t_team *team)
{
  char		buffer[4096];

  ((t_client_player*)client)->player = this;
  this->death_time.tv_sec = gameplay->time.tv_sec + 10;
  this->death_time.tv_usec = gameplay->time.tv_usec;
  this->id = client->socketstream->socket;
  this->direction = rand() % 4 + 1;
  this->x = rand() % gameplay->map.width;
  this->y = rand() % gameplay->map.height;
  this->level = 1;
  this->team = team;
  team->nb_slots--;
  case_initialize(&this->inventory, this->x, this->y);
  sprintf(buffer, "%d\n", team->nb_slots);
  client_send_msg(client, buffer);
  sprintf(buffer, "%d %d\n", this->x, this->y);
  client_send_msg(client, buffer);


  printf("[NEW PLAYER]\n");
  printf("pos x [%d] --- pos y [%d]\n", this->x, this->y);
  printf("level [%d]\n", this->level);
  printf("team [%s] - nb slot [%d]\n", this->team->name, this->team->nb_slots);
}

t_player*	player_new(t_gameplay *gameplay, t_client *client,
			   t_team *team)
{
  t_player	*player;

  player = malloc(sizeof(t_player));
  if (player == NULL)
    return (NULL);
  player_initialize(player, gameplay, client, team);
  return (player);
}

struct timeval	player_get_next_action_time(t_player* this)
{
  return (this->death_time);
}

bool			player_make_action(t_player* this, t_gameplay* gameplay,
					   struct timeval time)
{
  t_player_command*	command;

  command = list_front(this->command_queue);
  if (command == NULL)
    return (false);
  if (command->expiration_time.tv_sec < time.tv_sec ||
      (command->expiration_time.tv_sec == time.tv_sec &&
       command->expiration_time.tv_usec < time.tv_usec))
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
  if (this->death_time.tv_sec < time.tv_sec ||
      (this->death_time.tv_sec == time.tv_sec &&
       this->death_time.tv_usec < time.tv_usec))
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
  if (command->expiration_time.tv_sec < time.tv_sec ||
      (command->expiration_time.tv_sec == time.tv_sec &&
       command->expiration_time.tv_usec < time.tv_usec))
    return (true);
  return (player_is_dead(this, time));
}

void			player_release(t_player* this)
{
  while (!list_empty(this->command_queue))
    {
      player_command_delete(list_back(this->command_queue));
      list_pop_back(this->command_queue);
    }
  list_delete(this->command_queue);
}

void			player_delete(t_player* player)
{
  player_release(player);
  free(player);
}
