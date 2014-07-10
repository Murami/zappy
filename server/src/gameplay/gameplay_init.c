#include <stdlib.h>
#include <string.h>
#include "gameplay.h"
#include "server.h"

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
  this->teams = config.teams;
  map_initialize(&this->map, config.width, config.height);
  this->delay = config.delay;
  this->server = server;
  gettimeofday(&this->time, NULL);
}

void			gameplay_release(t_gameplay *this)
{
  list_delete(this->teams);
  list_delete(this->players);
  map_release(&this->map);
}

void			gameplay_delete(t_gameplay *this)
{
  gameplay_release(this);
  free(this);
}
