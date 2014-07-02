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
#include "client_graphic.h"
#include "client_player.h"
#include "socketstream.h"

bool			g_alive;

void			sighandler(int signum)
{
  (void) signum;
  write(1, "\b\b  \b\b", 6);
  g_alive = false;
}

void			server_initialize(t_server *this, int port)
{
  signal(SIGINT, &sighandler);
  g_alive = true;
  memset(this, 0, sizeof(t_server));
  /* gestion du port*/
  create_socket(this, port);
  create_queue(this);
  this->clients = list_new();
  this->new_clients = list_new();
  this->socket_max = this->socket;
}

void			server_release(t_server *this)
{
  t_client*		client;
  t_socketstream*	new_client;

  printf("release\n");
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
  printf("new client socket [%d]\n", socket);
}

bool			server_process_clients_input(t_server* this,
						     fd_set* fd_set_in,
						     t_client* client)
{
  if (!FD_ISSET(client->socketstream->socket, fd_set_in))
    return (true);
  else if (!socketstream_flush_input(client->socketstream))
    return (false);
  else
    client_run_input(client, this);
  return (true);
}

bool			server_process_clients_output(t_server* this,
						      fd_set* fd_set_out,
						      t_client* client)
{
  (void) this;

  if (FD_ISSET(client->socketstream->socket, fd_set_out))
    if (!socketstream_flush_output(client->socketstream))
      return (false);
  if (!list_empty(client->requests_output))
    client_run_output(client, this);
  return (true);
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

bool			server_read_new_clients_input(t_server* this,
						      t_socketstream* new_client)
{
  char			buffer[4096];
  int			size;
  t_client*		client;

  printf("server read ne clients input\n");
  while ((size = socketstream_peek(new_client, buffer, 4096)))
    {
      printf("in dat while [%s]\n", buffer);
      if (strncmp("GRAPHIC\n", buffer, size) == 0)
	{
	  printf("add d'un monitor\n");
	  client = (t_client*)client_graphic_new(new_client);
	  list_push_back(this->clients, client);
	  socketstream_read(new_client, buffer, 4096);
	  return (false);
	}
      else
	{
	  client = (t_client*)client_player_new(new_client);
	  list_push_back(this->clients, client);
	  return (false);
	}
    }
  return (true);
}

bool			server_process_new_clients_input(t_server* this,
							 fd_set* fd_set_in,
							 t_socketstream* new_client)
{
  if (!FD_ISSET(new_client->socket, fd_set_in))
    return (true);
  else if (!socketstream_flush_input(new_client))
    return (false);
  else
    return (server_read_new_clients_input(this, new_client));
  return (true);
}

bool			server_process_new_clients_output(t_server* this,
							  fd_set* fd_set_out,
							  t_socketstream* new_client)
{
  (void) this;

  if (FD_ISSET(new_client->socket, fd_set_out))
    if (!socketstream_flush_output(new_client))
      return (false);
  return (true);
}

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
      printf("select\n");
      printf("socket [%d]\n", this->socket);
      reset_rfds(this, &set_fd_in, &set_fd_out);
      retval = select(1 + this->socket_max,
		      &set_fd_in, &set_fd_out, NULL, NULL);
      printf("-- SELECT END --\n");
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
	      printf("add client\n");
	      server_accept(this);
	    }
	  else
	    {
	      server_process_clients(this, &set_fd_in, &set_fd_out);
	      server_process_new_clients(this, &set_fd_in, &set_fd_out);
	    }
	}
      /* process gameplay */
    }
}
