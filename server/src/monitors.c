#include <stdio.h>
#include "team.h"
#include "client.h"
#include "client_graphic.h"
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


void		monitor_initialize(t_server *this, t_client *client)
{
  monitor_send_size(this, client);
  monitor_send_delay(this, client);
  monitor_send_teams(this, client);
  monitor_send_map(this, client);
}

void		monitor_send_size(t_server *this, t_client *client)
{
  char		buff[4096];

  sprintf(buff, "msz %d %d\n", this->gameplay->map.width, this->gameplay->map.height);
  client_send_msg(client, buff);

}

void		monitor_send_delay(t_server *this, t_client *client)
{
  char		buff[4096];

  sprintf(buff, "sgt %d\n", this->gameplay->delay);
  client_send_msg(client, buff);
}

void			monitor_send_teams(t_server *this, t_client *client)
{
  char			buff[4096];
  t_team		*team;
  t_list_iterator	it;

  it = list_begin(this->gameplay->teams);
  while (it != list_end(this->gameplay->teams))
    {
      team = it->data;
      sprintf(buff, "tna %s\n", team->name);
      client_send_msg(client, buff);
      it = list_iterator_next(it);
    }
}

void		monitor_send_players(t_server *this, t_client *client)
{
  char		buff[4096];

  (void)buff;
  (void)this;
  (void)client;
  /* pas de players pour l'instant */
}

void		monitor_send_eggs(t_server *this, t_client *client)
{
  char		buff[4096];

  (void)buff;
  (void)this;
  (void)client;
  /* no eggs for the moment */
}

void		monitor_send_case(t_server *this, t_client *client, t_case *c)
{
  char		buff[4096];

  (void)this;
  sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n",
	  c->x, c->y, c->food, c->linemate, c->deraumere, c->sibur, c->mendiane,
	  c->phiras, c->thystame);
  client_send_msg(client, buff);
}

void		monitor_send_map(t_server *this, t_client *client)
{
  int		x;
  int		y;

  y = 0;
  while (y != this->gameplay->map.height)
    {
      x = 0;
      while (x != this->gameplay->map.width)
	{
	  monitor_send_case(this, client,
			    &this->gameplay->map.map[x + y * this->gameplay->map.width]);
	  x++;
	}
      y++;
    }
}
