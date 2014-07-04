#include <stdlib.h>
#include <string.h>
#include "gameplay.h"

void		gameplay_initialize(t_gameplay *this, t_config config)
{
  memset(this, 0, sizeof(t_gameplay));
  this->players = list_new();
  this->monitors = list_new();
  this->requests = list_new();
  this->output = list_new();
  this->teams = config.teams;
  map_initialize(&this->map, config.width, config.height);
  this->delay = config.delay;
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

void		gameplay_release(t_gameplay *this)
{
  list_release(this->teams);
  list_release(this->players);
  list_release(this->requests);
  list_release(this->output);
  map_release(&this->map);
  free(this->teams);
  free(this->players);
  free(this->requests);
  free(this->output);
}

void		gameplay_delete(t_gameplay *this)
{
  gameplay_release(this);
  free(this);
}
