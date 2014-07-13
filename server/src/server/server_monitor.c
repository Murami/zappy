#include <stdio.h>
#include <string.h>
#include "server.h"
#include "client.h"
#include "client_graphic.h"
#include "socketstream.h"
#include "gameplay.h"
#include "team.h"
#include "monitor.h"

void			server_add_monitor(t_server *this, t_client *client)
{
  list_push_back(this->clients, client);
  gameplay_add_monitor(this->gameplay, client);
}

void			server_add_player(t_server *this, t_client *client,
					  t_team *team)
{
  list_push_back(this->clients, client);
  gameplay_add_player(this->gameplay, client, team);
}

void			server_remove_monitor(t_server *this, t_client *client)
{
  t_list_iterator	it;
  t_client*		tmp;

  it = list_begin(this->clients);
  while (it != list_end(this->clients))
    {
      tmp = it->data;
      if (tmp == client)
	it = list_erase(this->clients, it);
      it = list_iterator_next(it);
    }
  gameplay_remove_monitor(this->gameplay, client);
  client_delete(client);
}

void			server_remove_player(t_server *this, t_client *client)
{
  gameplay_remove_player(this->gameplay, client);
}
