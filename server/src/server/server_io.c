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
  (void) this;

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

t_team*			server_check_teams(t_server *this, char *name, int size)
{
  t_list_iterator	it;
  t_team		*team;

  it = list_begin(this->gameplay->teams);
  while (it != list_end(this->gameplay->teams))
    {
      team = it->data;
      if (strncmp(team->name, name, size - 1) == 0 &&
	  team->nb_slots - count_taken_slot(this->gameplay, team) != 0)
	{
	  printf("cet équipe existe\n");
	  return (team);
	}
      it = list_iterator_next(it);
    }
  return (NULL);
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
	  /* sockstream tjrs présent les new client ? */
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
