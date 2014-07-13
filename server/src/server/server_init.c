/*
** server_init.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 18:06:24 2014 quentin desabre
** Last update Sun Jul 13 18:06:25 2014 Desabre Quentin
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
