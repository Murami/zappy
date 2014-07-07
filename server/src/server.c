#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "server.h"
#include "gameplay.h"
#include "client.h"
#include "client_graphic.h"
#include "client_player.h"
#include "socketstream.h"

bool			g_alive;

void			server_initialize(t_server *this, t_config config)
{
  g_alive = true;
  signal(SIGINT, &sighandler);
  memset(this, 0, sizeof(t_server));
  create_socket(this, config.port);
  create_queue(this);
  this->clients = list_new();
  this->new_clients = list_new();
  this->socket_max = this->socket;
  this->gameplay = gameplay_new(config);
}

void			server_release(t_server *this)
{
  t_client*		client;
  t_socketstream*	new_client;

  printf("realse [%d] [%d]\n", list_size(this->clients), list_size(this->new_clients));

  while (!list_empty(this->clients))
    {
      printf("release d'un client identifié\n");
      client = list_back(this->clients);
      client_delete(client);
      list_pop_back(this->clients);
    }
  while (!list_empty(this->new_clients))
    {
      printf("release d'un client non - identifié\n");
      new_client = list_back(this->new_clients);
      socketstream_delete(new_client);
      list_pop_back(this->new_clients);
    }
  shutdown(this->socket, SHUT_RDWR);
  close(this->socket);
  list_delete(this->clients);
}

void			server_accept(t_server *this)
{
  int			len;
  int			socket;
  struct sockaddr_in	sin;
  t_socketstream*	socketstream;

  len = 1;
  socket = accept(this->socket, (struct sockaddr *)&sin, (socklen_t *)&len);
  if (socket == -1)
    perror("accept");
  socketstream = socketstream_new(socket);
  list_push_back(this->new_clients, socketstream);
  /* HERE WE HAD BETTER GO TROUGH ALL THE OPENED SOCKET TO FIND THE HIGEST AFTER EACH CONNECTION/DISCONNECTION ! */
  if (socket > this->socket_max)
    this->socket_max = socket;
  socketstream_write(socketstream, "BIENVENUE\n", strlen("BIENVENUE\n"));
}

void			server_launch(t_server *this)
{
  int			retval;
  fd_set		set_fd_in;
  fd_set		set_fd_out;

  while (42)
    {
      if (g_alive == false)
	{
	  server_release(this);
	  return;
	}
      reset_rfds(this, &set_fd_in, &set_fd_out);
      printf("[SELECT]\n");
      retval = select(1 + this->socket_max,
		      &set_fd_in, &set_fd_out, NULL, NULL);
      if (g_alive == false)
	{
	  server_release(this);
	  return;
	}
      if (retval == -1)
	{
	  perror("select()");
	}
      else if (retval)
	{
	  if (FD_ISSET(this->socket, &set_fd_in))
	    {
	      server_accept(this);
	    }
	  else
	    {
	      server_process_new_clients(this, &set_fd_in, &set_fd_out);
	      server_process_clients(this, &set_fd_in, &set_fd_out);
	    }
	}
    }
}

void			sighandler(int signum)
{
  (void) signum;
  write(1, "\b\b  \b\b", 6);
  g_alive = false;
}
