#include <stdlib.h>
#include <string.h>
#include "gameplay.h"
#include "client.h"

void		gameplay_initialize(t_gameplay *this, t_config config)
{
  memset(this, 0, sizeof(t_gameplay));
  this->players = list_new();
  this->monitors = list_new();
  /* this->requests = list_new(); */
  /* this->output = list_new(); */
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

/* modifer le champs client->player/monitor !!! */

void		gameplay_remove_player(t_gameplay* this, t_client* client)
{
  (void)this;
  (void)client;
}

void		gameplay_add_player(t_gameplay* this, t_client* client)
{
  (void)this;
  (void)client;
}

void		gameplay_remove_monitor(t_gameplay* this, t_client* client)
{
  (void)this;
  (void)client;
}

void		gameplay_add_monitor(t_gameplay* this, t_client* client)
{
  (void)this;
  (void)client;
}

void		gameplay_run(t_gameplay* this)
{
  /* GESTION DU TEMPS
  ** DE LA PRIORIYTY QUEUES
  ** EXECTUTION DES REQUEST (go partie full gameplay)
  */
  (void) this;
}

void		gameplay_release(t_gameplay *this)
{
  list_delete(this->teams);
  list_delete(this->players);
  /* list_release(this->requests); */
  /* list_release(this->output); */
  map_release(&this->map);
  /* free(this->requests); */
  /* free(this->output); */
}

void		gameplay_delete(t_gameplay *this)
{
  gameplay_release(this);
  free(this);
}
