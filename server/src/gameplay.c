#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameplay.h"
#include "socketstream.h"
#include "client.h"
#include "server.h"
#include "monitors.h"
#include "player_command.h"
#include "monitor_command.h"
#include "player.h"
#include "team.h"

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

/* modifer le champs client->player !!! */

void		gameplay_remove_player(t_gameplay* this, t_client* client)
{
  (void)this;
  (void)client;
}

void		gameplay_add_player(t_gameplay* this, t_client* client, t_team *team)
{
  t_player*	player;

  player = player_new(this, client, team);
  list_push_back(this->players, player);
}

void		gameplay_remove_monitor(t_gameplay* this, t_client* client)
{
  (void)this;
  (void)client;
}

void		gameplay_add_monitor(t_gameplay* this, t_client* client)
{
  list_push_back(this->monitors, client);
  monitor_initialize(this, client);
}

void			gameplay_update(t_gameplay *this)
{
  (void)this;
}

void			gameplay_command_avance(t_gameplay* this)
{
  (void) this;
  printf("le début de la fin du serveur\n");
}

void			gameplay_command_droite(t_gameplay* this)
{
  (void) this;
}

void			gameplay_command_gauche(t_gameplay* this)
{
  (void) this;
}

void			gameplay_command_voir(t_gameplay* this)
{
  (void) this;
}

void			gameplay_command_inventaire(t_gameplay* this)
{
  (void) this;
}

void			gameplay_command_prend_objet(t_gameplay* this)
{
  (void) this;
}

void			gameplay_command_expulse(t_gameplay* this)
{
  (void) this;
}

void			gameplay_command_broadcast(t_gameplay* this)
{
  (void) this;
}

void			gameplay_command_incantation(t_gameplay* this)
{
  (void) this;
}

void			gameplay_command_fork(t_gameplay* this)
{
  (void) this;
}

void			gameplay_command_connect_nbr(t_gameplay* this)
{
  (void) this;
}

void			gameplay_add_player_command(t_gameplay* this, t_player_command* command)
{
  (void) this;
  (void) command;

  /* EXECUTE LA COMMANDE DIRECT POUR L'INSTANT */
  player_command_execute(command, this);
}

void			gameplay_add_monitor_command(t_gameplay* this, t_monitor_command* command)
{
  (void) this;
  (void) command;
  /* EXECUTE LA COMMANDE DIRECTE TT LE TEMPS */
}

void			gameplay_release(t_gameplay *this)
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
