/*
** team.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:35:10 2014 otoshigami
** Last update Sun Jul 13 17:35:11 2014 otoshigami
*/

#include <string.h>
#include <stdlib.h>
#include "team.h"

void		team_initialize(t_team *this, int nb_slots, char *name)
{
  this->nb_slots = nb_slots;
  this->nb_lvl8 = 0;
  this->name = strdup(name);
}

t_team*		team_new(int nb_slots, char *name)
{
  t_team	*team;

  team = malloc(sizeof(t_team));
  if (team == NULL)
    return (NULL);
  team_initialize(team, nb_slots, name);
  return (team);
}

void		team_release(t_team *this)
{
  free(this->name);
}

void		team_delete(t_team *this)
{
  team_release(this);
  free(this);
}
