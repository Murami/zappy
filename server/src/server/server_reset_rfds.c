/*
** server_reset_rfds.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:37:02 2014 quentin desabre
** Last update Sun Jul 13 16:41:49 2014 Desabre Quentin
*/

#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "client.h"
#include "socketstream.h"

void			reset_client(t_server *this, fd_set* fd_set_in,
				     fd_set* fd_set_out)
{
  t_list_iterator	it;
  t_socketstream*	sockstream;

  it = list_begin(this->new_clients);
  while (it != list_end(this->new_clients))
    {
      sockstream = it->data;
      if (SOCKETSTREAM_BUFFER_SIZE - sockstream->size_input > 0)
	FD_SET(sockstream->socket, fd_set_in);
      if (sockstream->size_output != 0)
	FD_SET(sockstream->socket, fd_set_out);
      it = list_iterator_next(it);
    }
}

void			reset_deads(t_server *this, fd_set* fd_set_out)
{
  t_list_iterator	it;
  t_client*		client;

  it = list_begin(this->deads);
  while (it != list_end(this->deads))
    {
      client = it->data;
      if (client->socketstream->size_output != 0 ||
	  !list_empty(client->requests_output))
	FD_SET(client->socketstream->socket, fd_set_out);
      it = list_iterator_next(it);
    }
}

void			reset_rfds(t_server *this, fd_set *fd_set_in,
				   fd_set* fd_set_out)
{
  t_list_iterator	it;
  t_client*		client;

  FD_ZERO(fd_set_in);
  FD_ZERO(fd_set_out);
  FD_SET(this->socket, fd_set_in);
  it = list_begin(this->clients);
  while (it != list_end(this->clients))
    {
      client = it->data;
      if (SOCKETSTREAM_BUFFER_SIZE - client->socketstream->size_input > 0)
	FD_SET(client->socketstream->socket, fd_set_in);
      if (client->socketstream->size_output != 0 ||
	  !list_empty(client->requests_output))
	FD_SET(client->socketstream->socket, fd_set_out);
      it = list_iterator_next(it);
    }
  reset_client(this, fd_set_in, fd_set_out);
  reset_deads(this, fd_set_out);
}
