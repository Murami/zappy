/*
** server_io.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:25:02 2014 quentin desabre
** Last update Sun Jul 13 16:25:02 2014 Desabre Quentin
*/

#include <stdio.h>
#include <string.h>
#include "config.h"
#include "server.h"
#include "socketstream.h"
#include "client.h"
#include "client_graphic.h"
#include "client_player.h"
#include "team.h"

bool			server_process_clients_input(t_server* this,
						     fd_set* fd_set_in,
						     t_client* client)
{
  if (!FD_ISSET(client->socketstream->socket, fd_set_in))
    return (true);
  if (!socketstream_flush_input(client->socketstream))
    {
      client_remove(client, this);
      return (false);
    }
  client_run_input(client, this);
  return (true);
}

bool			server_process_clients_output(t_server* this,
						      fd_set* fd_set_out,
						      t_client* client)
{
  if (FD_ISSET(client->socketstream->socket, fd_set_out))
    if (!socketstream_flush_output(client->socketstream))
      {
	client_remove(client, this);
	return (false);
      }
  FD_CLR(client->socketstream->socket, fd_set_out);
  if (!list_empty(client->requests_output))
    client_run_output(client, this);
  return (true);
}

bool			server_process_new_clients_input(t_server* this,
							 fd_set* fd_set_in,
							 t_socketstream* new_client)
{
  if (!FD_ISSET(new_client->socket, fd_set_in))
    return (true);
  if (!socketstream_flush_input(new_client))
    {
      socketstream_delete(new_client);
      return (false);
    }
  FD_CLR(new_client->socket, fd_set_in);
  return (server_read_new_clients_input(this, new_client));
}

bool			server_process_new_clients_output(t_server* this,
							  fd_set* fd_set_out,
							  t_socketstream* new_client)
{
  (void) this;

  if (FD_ISSET(new_client->socket, fd_set_out))
    if (!socketstream_flush_output(new_client))
      {
	socketstream_delete(new_client);
	return (false);
      }
  return (true);
}

bool			server_read_new_clients_input(t_server* this,
						      t_socketstream* new_client)
{
  char			buffer[4096];
  int			size;
  t_client*		client;
  t_team*		team;

  while ((size = socketstream_read(new_client, buffer, 4096)))
    {
      if (strncmp("GRAPHIC\n", buffer, size) == 0)
	{
	  client = (t_client*)client_graphic_new(new_client);
	  server_add_monitor(this, client);
	  return (false);
	}
      else
	{
	  if ((team = server_check_teams(this, buffer, size)))
	    {
	      client = (t_client*)client_player_new(new_client);
	      server_add_player(this, client, team);
	      return (false);
	    }
	  return (true);
	}
    }
  return (true);
}
