#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "client.h"
#include "socketstream.h"

void			create_socket(t_server *this, int port)
{
  struct sockaddr_in	sin;
  struct protoent 	*pe;
  int			val;

  pe = getprotobyname("TCP");
  this->socket = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (this->socket == -1)
    {
      perror("socket");
      exit(EXIT_FAILURE);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  val = 1;
  setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
  bind_socket(this, &sin);
}

void			bind_socket(t_server *this, struct sockaddr_in *sin)
{
  int			rbind;

  rbind = bind(this->socket, (const struct sockaddr *)sin, sizeof(*sin));
  if (rbind == -1)
    {
      close(this->socket);
      perror("bind");
      exit(EXIT_FAILURE);
    }
}

void			create_queue(t_server *this)
{
  int			rlisten;

  rlisten = listen(this->socket, 42);
  if (rlisten == -1)
    {
      close(this->socket);
      perror("listen");
    }
}

void			reset_rfds(t_server *this, fd_set *fd_set_in, fd_set* fd_set_out)
{
  t_list_iterator	it;
  t_client*		client;
  t_socketstream*	sockstream;

  FD_ZERO(fd_set_in);
  FD_ZERO(fd_set_out);
  FD_SET(this->socket, fd_set_in);
  /* CLIENTS LOOP */
  it = list_begin(this->clients);
  while (it != list_end(this->clients))
    {
      client = it->data;
      if (SOCKETSTREAM_BUFFER_SIZE - client->socketstream->size_input > 0)
	FD_SET(client->socketstream->socket, fd_set_in);
      if (client->socketstream->size_output != 0)
	FD_SET(client->socketstream->socket, fd_set_out);
      it = list_iterator_next(it);
    }
  /* NEW CLIENTS LOOP */
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
