#include <string.h>
#include <stdlib.h>
#include "team.h"

void		team_initialize(t_team *this, int nb_slots, char *name)
{
  this->nb_slots = nb_slots;
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
