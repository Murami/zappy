#include "gameplay.h"

void		gameplay_initialize(t_gameplay *this);
{
  memset(this, 0, sizeof(t_gameplay));
}

t_gameplay*    	gameplay_new()
{
  t_gameplay	*gameplay;

  gameplay = malloc(sizeof(t_gameplay));
  if (!gameplay)
    return (NULL);
  gameplay_initialize(gameplay);
  return (gameplay);
}

void		gameplay_release(t_gameplay *this)
{
  list_release(this->teams);
  list_release(this->players);
  list_release(this->requests);
  list_release(this->output);
  map_release(this->map);
  free(this->teams);
  free(this->players);
  free(this->requests);
  free(this->output);
  free(this->map);
}

void		gameplay_delete(t_gameplay *this)
{
  gameplay_release(this);
  free(this);
}
