#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "server.h"

bool			g_alive;

void			sighandler(int signum)
{
  (void) signum;
  write(1, "\b\b  \b\b", 6);
  g_alive = false;
}

void			server_initialize(t_server *this)
{
  signal(SIGINT, &sighandler);
  g_alive = true;
  memset(this, 0, sizeof(t_server));
  // GESTION DU PORT
  create_socket(this, 4243);
  create_queue(this);
  this->clients = list_new();
  this->socket_max = this->socket;
}

void			server_release(t_server *this)
{
  t_socketstream*	client;

  shutdown(this->socket, SHUT_RDWR);
  close(this->socket);
  while (!list_empty(this->clients))
    {
      client = list_back(this->clients);
      socketstream_delete(client);
      list_pop_back(this->clients);
    }
  list_delete(this->clients);
}

void			server_accept(t_server *this)
{
  int			len;
  int			socket;
  struct sockaddr_in	sin;
  t_socketstream*	client;

  len = 1;
  socket = accept(this->socket, (struct sockaddr *)&sin, (socklen_t *)&len);
  if (socket == -1)
    perror("accept");
  client = socketstream_new(socket);
  list_push_back(this->clients, client);
  if (socket > this->socket_max)
    this->socket_max = socket;
  printf("new client socket [%d]\n", socket);
}

void			server_process_clients(t_server* this, fd_set* fd_set)
{
  t_list_iterator	it;

  it = list_begin(this->clients);
  while (it != list_end(this->clients))
    {
      if (FD_ISSET(((t_socketstream*)it->data)->socket, fd_set))
	{
	  /* gestion */
	}
      it = list_iterator_next(it);
    }
}

void			server_launch(t_server *this)
{
  int			retval;
  fd_set		rfds;

  while (42)
    {
      if (g_alive == false)
	{
	  server_release(this);
	  return;
	}
      printf("select\n");
      printf("socket [%d]\n", this->socket);
      FD_SET(this->socket, &rfds);
      retval = select(this->socket + 1 + this->socket_max,
		      &rfds, NULL, NULL, NULL);
      printf("-- SELECT END --\n");
      if (retval == -1)
	{
	  if (g_alive == false)
	    {
	      server_release(this);
	      return;
	    }
	  if (g_alive == true)
	    perror("select()");
	}
      else if (retval)
	{
	  if (FD_ISSET(this->socket, &rfds))
	    {
	      printf("add client\n");
	      server_accept(this);
	    }
	  else
	    {
	      server_process_clients(this, &rfds);
	    }
	  reset_rfds(this, &rfds);
	}
    }
}
