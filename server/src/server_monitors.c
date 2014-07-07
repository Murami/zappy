#include <stdio.h>
#include <string.h>
#include "server.h"
#include "client.h"
#include "client_graphic.h"
#include "socketstream.h"

void			server_add_monitor(t_server *this, t_client *client)
{
  char			buff[4096];

  printf("add d'un monitor\n");
  list_push_back(this->clients, client);
  socketstream_read(client->socketstream, buff, 4096);
  sprintf(buff, "smz %d %d\n", this->gameplay.map.width, this->gameplay.map.height);
  socketstream_write(client->socketstream, buff, strlen(buff));
  gameplay_add_monitor(&this->gameplay, client);
}

void			server_add_player(t_server *this, t_client *client)
{
  list_push_back(this->clients, client);
  gameplay_add_player(&this->gameplay, client);
}

void			server_remove_monitor(t_server *this, t_client *client)
{
  // arreter la boucle plus tot
  // supprimer de la liste du t_ser et du t_gameplay
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
  gameplay_remove_monitor(&this->gameplay, client);
  // itere la boucle gameplay
  /* it = list_begin(this->clients); */
  /* while (it != list_end(this->clients)) */
  /*   { */
  /*     tmp = it->data; */
  /*     if (client == client) */
  /* 	it = list_erase(this->clients, it); */
  /*     it = list_iterator_next(it); */
  /*   } */

  client_delete(client);
}

void			server_remove_player(t_server *this, t_client *client)
{
  gameplay_remove_player(&this->gameplay, client);
}
