#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client_player.h"
#include "socketstream.h"
#include "server.h"

t_client_vtable client_player_vtable =
  {
    (t_client_run_input_ptr)client_player_run_input,
    (t_client_delete_ptr)client_player_delete
  };

void	client_player_initialize(t_client_player* this, t_socketstream* sockstream)
{
  client_initialize(&this->parent_client, sockstream);
  this->parent_client.vtable = &client_player_vtable;
  this->player = NULL;
}

void	client_player_release(t_client_player* this)
{
  client_release(&this->parent_client);
}

void	client_player_run_input(t_client_player* this, t_server* server)
{
  char			buffer[4096];
  t_player_command*	command;
  int			size;
  int			i;

  (void) server;
  printf("A client player just received some data");
  memset(buffer, 0, 4096);
  while ((size = socketstream_read(this->parent_client.socketstream, buffer, 4096)))
    {
      strtok(buffer, "\n");
      i = 0;
      while (command[i] && strcmp(buffer, commands[i].request) != 0)
      	i++;
      if (!command[i])
      	printf("error: invalid command send by a client player!\n");
      else
	{
	  command = player_command_new(this, commands[i].time, commands[i].callback);
	  server_add_player_command(server, command);
	}

    }
}

t_client_player*	client_player_new(t_socketstream* sockstream)
{
  t_client_player*	client_player;

  client_player = malloc(sizeof(t_client_player));
  if (client_player == NULL)
    return (NULL);
  client_player_initialize(client_player, sockstream);
  return (client_player);
}

void			client_player_delete(t_client_player* client_player)
{
  client_player_release(client_player);
  free(client_player);
}
