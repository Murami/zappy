#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client_player.h"
#include "socketstream.h"
#include "server.h"
#include "player_command.h"

t_client_vtable client_player_vtable =
  {
    (t_client_run_input_ptr)client_player_run_input,
    (t_client_remove_ptr)client_player_remove,
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
  char			buffer_original[4096];
  t_player_command*	command;
  int			size;
  int			i;
  char*			data;

  memset(buffer, 0, 4096);
  memset(buffer_original, 0, 4096);
  while ((size = socketstream_read(this->parent_client.socketstream, buffer, 4096)))
    {
      command = NULL;
      i = 0;
      strtok(buffer, "\n");
      strcpy(buffer_original, buffer);
      strtok(buffer, " ");
      data = strtok(NULL, " ");
      while (g_player_commands[i].request && strcmp(buffer, g_player_commands[i].request))
	i++;
      if (g_player_commands[i].request)
	{
	  if (strcmp(g_player_commands[i].request, "broadcast"))
	    command = player_command_new(this, server->gameplay,
					 buffer_original + strlen("broadcast") + 1, i);
	  if ((g_player_commands[i].has_data == 1 && data != NULL) ||
	      (g_player_commands[i].has_data == 0 && data == NULL))
	    command = player_command_new(this, server->gameplay, data, i);
	}
      if (command)
	server_add_player_command(server, command);
      else
      	printf("error: invalid command send by a client player!\n");
      memset(buffer, 0, 4096);
      memset(buffer_original, 0, 4096);
    }
}

void			client_player_remove(t_client_player* client, t_server* server)
{
  t_list_iterator	it;
  t_client_player*	tmp;

  it = list_begin(server->clients);
  while (it != list_end(server->clients))
    {
      tmp = it->data;
      if (client == tmp)
	{
	  it = list_erase(server->clients, it);
	  return;
	}
      it = list_iterator_next(it);
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
