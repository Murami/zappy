#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include "server.h"
#include "gameplay.h"
#include "client.h"
#include "client_graphic.h"
#include "client_player.h"
#include "socketstream.h"
#include "player_command.h"
#include "monitor_command.h"

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
  this->deads = list_new();
  this->socket_max = this->socket;
  this->gameplay = gameplay_new(config, this);
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
  while (!list_empty(this->deads))
    {
      free(list_back(this->deads));
      list_pop_back(this->deads);
    }
  list_delete(this->deads);
  shutdown(this->socket, SHUT_RDWR);
  close(this->socket);
  list_delete(this->clients);
  gameplay_delete(this->gameplay);
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


void			server_delete_deads(t_server* this)
{
  t_list_iterator	it;
  t_client*		client;

  it = list_begin(this->deads);
  while (it != list_end(this->deads))
    {
      client = it->data;
      if (list_empty(client->requests_output) &&
	  client->socketstream->size_output == 0)
	{
	  printf("dead deleted\n");
	  client_delete(client);
	  it = list_erase(this->deads, it);
	}
      it = list_iterator_next(it);
    }
}

void			server_launch(t_server *this)
{
  struct timeval	waiting_time;
  int			retval;
  fd_set		set_fd_in;
  fd_set		set_fd_out;

  waiting_time.tv_sec = 0;
  waiting_time.tv_usec = 0;
  while (42)
    {
      if (g_alive == false)
	{
	  server_release(this);
	  return;
	}
      reset_rfds(this, &set_fd_in, &set_fd_out);
      printf("[SELECT] %ld -- %ld\n", waiting_time.tv_sec, waiting_time.tv_usec);
      retval = select(1 + this->socket_max,
		      &set_fd_in, &set_fd_out, NULL,
		      (waiting_time.tv_sec || waiting_time.tv_usec) ? &waiting_time : NULL);
      if (g_alive == false)
	{
	  server_release(this);
	  return;
	}
      else if (retval == -1)
	perror("select()");
      gettimeofday(&this->gameplay->time, NULL);
      if (FD_ISSET(this->socket, &set_fd_in))
	server_accept(this);
      else
	{
	  server_process_new_clients(this, &set_fd_in, &set_fd_out);
	  server_process_clients(this, &set_fd_in, &set_fd_out);
	  server_process_deads(this, &set_fd_out);
	}
      waiting_time = gameplay_update(this->gameplay, this->gameplay->time);
      server_delete_deads(this);
    }
}

void			server_add_player_command(t_server* this, t_player_command* command)
{
  gameplay_add_player_command(this->gameplay, command);
}

void			server_add_monitor_command(t_server* this, t_monitor_command* command)
{
  gameplay_add_monitor_command(this->gameplay, command);
}

void			server_remove(t_server* this, t_client* client)
{
  t_list_iterator	it;

  it = list_begin(this->clients);
  while (it != list_end(this->clients))
    {
      if (it->data == client)
	{
	  list_erase(this->clients, it);
	  return;
	}
      it = list_iterator_next(it);
    }
  list_push_back(this->deads, client);
}

void			sighandler(int signum)
{
  (void) signum;
  write(1, "\b\b  \b\b", 6);
  g_alive = false;
}
