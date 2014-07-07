#include <stdio.h>
#include <string.h>
#include "server.h"
#include "client.h"
#include "client_graphic.h"
#include "socketstream.h"
#include "gameplay.h"
#include "monitors.h"

/* CONNEXION d'un MONITEUR

  size of the map
  "msz X Y\n"

  unité de temps
  "sgt T\n"

  contenu d'une case .. de la map
  "bct 0 0 q q q q q q q\n"
  .....
  "bct X Y q q q q q q q\n"

  nom équipe .. s
  "tna N\n"
  ...
  "tna N\n"

  connexion d'un nouveau player
  "pnw #n X Y O L N\n"  O = orientation L = level n = numéro de l'équipe
  ...

  oeuf a été pondu
  "enw #e #n X Y\n"
  ...

*/

void			server_add_monitor(t_server *this, t_client *client, char *buffer)
{
  list_push_back(this->clients, client);
  list_push_back(this->gameplay->monitors, client);
  socketstream_read(client->socketstream, buffer, 4096);
  monitor_initialize(this, client);
}

void			server_add_player(t_server *this, t_client *client)
{
  list_push_back(this->clients, client);
}

void			server_remove_monitor(t_server *this, t_client *client)
{
  // arreter la boucle plus tot
  // supprimer de la liste du t_ser et du t_gameplay
  /* itere la boucle gameplay */
  (void) this;
  client_delete(client);
}

void			server_remove_player(t_server *this, t_client *client)
{
  (void)this;
  (void)client;
}
