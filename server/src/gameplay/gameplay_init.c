#include <stdlib.h>
#include <string.h>
#include "gameplay.h"
#include "server.h"
#include "player.h"

t_gameplay*    	gameplay_new(t_config config, t_server* server)
{
  t_gameplay	*gameplay;

  gameplay = malloc(sizeof(t_gameplay));
  if (!gameplay)
    return (NULL);
  gameplay_initialize(gameplay, config, server);
  return (gameplay);
}

void		gameplay_initialize(t_gameplay *this, t_config config, t_server* server)
{
  memset(this, 0, sizeof(t_gameplay));
  this->players = list_new();
  this->monitors = list_new();
  this->eggs = list_new();
  this->teams = config.teams;
  map_initialize(&this->map, config.width, config.height);
  this->delay = config.delay;
  this->server = server;
  gettimeofday(&this->time, NULL);
}

void			gameplay_release(t_gameplay *this)
{
  list_delete(this->teams);
  while (!list_empty(this->players))
    {
      player_delete(list_back(this->players));
      list_pop_back(this->players);
    }
  while (!list_empty(this->eggs))
    {
      free(this->eggs);
      list_pop_back(this->eggs);
    }
  list_delete(this->eggs);
  list_delete(this->players);
  list_delete(this->monitors);
  map_release(&this->map);
}

void			gameplay_delete(t_gameplay *this)
{
  gameplay_release(this);
  free(this);
}
