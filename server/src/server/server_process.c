/*
** server_process.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 18:06:35 2014 quentin desabre
** Last update Sun Jul 13 18:06:35 2014 Desabre Quentin
*/

#include "server.h"
#include "socketstream.h"
#include "client.h"

void			server_process_new_clients(t_server* this,
						   fd_set* fd_set_in, fd_set* fd_set_out)
{
  t_list_iterator	it;
  t_socketstream*	new_client;

  it = list_begin(this->new_clients);
  while (it != list_end(this->new_clients))
    {
      new_client = it->data;
      if (!server_process_new_clients_input(this, fd_set_in, new_client) ||
	  !server_process_new_clients_output(this, fd_set_out, new_client))
	it = list_erase(this->new_clients, it);
      it = list_iterator_next(it);
    }
}

void			server_process_clients(t_server* this,
					       fd_set* fd_set_in, fd_set* fd_set_out)
{
  t_list_iterator	it;
  t_client*		client;

  it = list_begin(this->clients);
  while (it != list_end(this->clients))
    {
      client = it->data;
      if (!server_process_clients_input(this, fd_set_in, client) ||
	  !server_process_clients_output(this, fd_set_out, client))
	it = list_erase(this->clients, it);
      it = list_iterator_next(it);
    }
}

bool			server_process_deads_output(t_server* this,
						    fd_set* fd_set_out,
						    t_client* client)
{
  (void) this;

  if (FD_ISSET(client->socketstream->socket, fd_set_out))
    if (!socketstream_flush_output(client->socketstream))
      {
	client_delete(client);
	return (false);
      }
  FD_CLR(client->socketstream->socket, fd_set_out);
  if (!list_empty(client->requests_output))
    client_run_output(client, this);
  return (true);
}

void			server_process_deads(t_server* this,
					     fd_set* fd_set_out)
{
  t_list_iterator	it;
  t_client*		client;

  it = list_begin(this->deads);
  while (it != list_end(this->deads))
    {
      client = it->data;
      if (!server_process_deads_output(this, fd_set_out, client))
	it = list_erase(this->deads, it);
      it = list_iterator_next(it);
    }
}
