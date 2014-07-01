#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "server.h"
#include "client.h"

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
  /* gestion du port*/
  create_socket(this, 4243);
  create_queue(this);
  this->clients = list_new();
  this->new_clients = list_new();
  this->socket_max = this->socket;
}

void			server_release(t_server *this)
{
  t_client*		client;
  t_socketstream*	new_client;

  shutdown(this->socket, SHUT_RDWR);
  close(this->socket);
  while (!list_empty(this->clients))
    {
      client = list_back(this->clients);
      client_delete(client);
      list_pop_back(this->clients);
    }
  while (!list_empty(this->clients))
    {
      new_client = list_back(this->new_clients);
      socketstream_delete(new_client);
      list_pop_back(this->new_clients);
    }
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
  printf("new client socket [%d]\n", socket);
}

void			server_process_clients(t_server* this, fd_set* fd_set)
{
  t_list_iterator	it;
  t_client*		client;

  char			buffer[4096];
  int			size;

  it = list_begin(this->clients);
  while (it != list_end(this->clients))
    {
      client = it->data;
      if (FD_ISSET(client->socketstream->socket, fd_set))
	{
	  if (!socketstream_flush_input(client->socketstream))
	    {
	      /* VERIFIER SI IL Y A D'AUTRE COMMANDES DANS LE BUFFER AVANT DE QUITTER */
	      /* OU ALORS IL N'Y AURA PAS DE COMMANDES VUE QUE ELLE SONT TOUTES EXECUTÉ */
	      /* DÉS QUE DISPONIBLE */
	      it = list_erase(this->clients, it);
	    }
	  else
	    {
	      while ((size = socketstream_read(client->socketstream, buffer, 4096)))
		{
		  /* PARSING ET AJOUT DANS LA PRIORITY QUEUE */
		}
	    }
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
