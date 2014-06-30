#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

void			create_socket(t_server *this, int port)
{
  struct sockaddr_in	sin;
  struct protoent 	*pe;

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

void			reset_rfds(t_server *this, fd_set *rfds)
{
  t_list_iterator	it;

  FD_ZERO(rfds);
  FD_SET(this->socket, rfds);
  it = list_begin(this->clients);
  while (it != list_end(this->clients))
    {
      FD_SET(((t_socketstream*)it->data)->socket, rfds);
      it = list_iterator_next(it);
    }
}
