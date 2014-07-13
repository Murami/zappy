/*
** player_init.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:00:47 2014 otoshigami
** Last update Sun Jul 13 17:00:47 2014 otoshigami
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

void		player_initialize(t_player *this, t_gameplay *gameplay,
				  t_client *client, t_team *team)
{
  char		buffer[4096];

  this->death_time.tv_usec = (1200 * 1000000) / gameplay->delay;
  this->death_time.tv_sec = 0;
  this->death_time = timeval_add(gameplay->time, this->death_time);
  this->id = gameplay_get_new_id(gameplay);
  this->direction = rand() % 4 + 1;
  this->x = rand() % gameplay->map.width;
  this->y = rand() % gameplay->map.height;
  this->level = 1;
  this->team = team;
  this->id_egg = 0;
  this->is_egg = false;
  this->command_queue = list_new();
  case_initialize(&this->inventory, this->x, this->y);
  this->inventory.food = 10;
  this->client = client;
  if (this->client)
    {
      ((t_client_player*)client)->player = this;
      sprintf(buffer, "%d\n", team->nb_slots);
      client_send_msg(client, buffer);
      sprintf(buffer, "%d %d\n", this->x, this->y);
      client_send_msg(client, buffer);
    }
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
