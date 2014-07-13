/*
** server_check.c for check in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:24:38 2014 quentin desabre
** Last update Sun Jul 13 16:39:37 2014 Desabre Quentin
*/

#include <stdio.h>
#include <string.h>
#include "config.h"
#include "server.h"
#include "socketstream.h"
#include "client.h"
#include "client_graphic.h"
#include "client_player.h"
#include "team.h"

t_team*			server_check_teams(t_server *this, char *name, int size)
{
  t_list_iterator	it;
  t_team		*team;

  it = list_begin(this->gameplay->teams);
  while (it != list_end(this->gameplay->teams))
    {
      team = it->data;
      if (strncmp(team->name, name, size - 1) == 0 &&
	  team->nb_slots - count_taken_slot(this->gameplay, team) != 0)
	return (team);
      it = list_iterator_next(it);
    }
  return (NULL);
}
