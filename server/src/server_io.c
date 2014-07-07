#include <string.h>
#include "config.h"
#include "server.h"
#include "socketstream.h"
#include "client.h"
#include "client_graphic.h"
#include "client_player.h"


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

bool			server_read_new_clients_input(t_server* this,
						      t_socketstream* new_client)
{
  char			buffer[4096];
  int			size;
  t_client*		client;

  while ((size = socketstream_peek(new_client, buffer, 4096)))
    {
      if (strncmp("GRAPHIC\n", buffer, size) == 0)
	{
	  client = (t_client*)client_graphic_new(new_client);
	  server_add_monitor(this, client, buffer);
	  return (false);
	}
      else
	{
	  client = (t_client*)client_player_new(new_client);
	  server_add_player(this, client);
	  return (false);
	}
    }
  return (true);
}