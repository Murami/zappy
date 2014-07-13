/*
** server.c for server in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:25:12 2014 quentin desabre
** Last update Sun Jul 13 19:58:31 2014 otoshigami
*/

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
#include "team.h"
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
  while (!list_empty(this->clients))
    {
      client_delete(list_back(this->clients));
      list_pop_back(this->clients);
    }
  while (!list_empty(this->new_clients))
    {
      socketstream_delete(list_back(this->new_clients));
      list_pop_back(this->new_clients);
    }
  while (!list_empty(this->deads))
    {
      client_delete(list_back(this->deads));
      list_pop_back(this->deads);
    }
  list_delete(this->deads);
  list_delete(this->clients);
  list_delete(this->new_clients);
  shutdown(this->socket, SHUT_RDWR);
  close(this->socket);
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
  if (socket > this->socket_max)
    this->socket_max = socket;
  socketstream_write(socketstream, "BIENVENUE\n", strlen("BIENVENUE\n"));
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
