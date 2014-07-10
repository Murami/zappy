#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "client_graphic.h"
#include "socketstream.h"
#include "server.h"
#include "monitor_command.h"

t_client_vtable client_graphic_vtable =
  {
    (t_client_run_input_ptr)client_graphic_run_input,
    (t_client_remove_ptr)client_graphic_remove,
    (t_client_delete_ptr)client_graphic_delete
  };

void			client_graphic_initialize(t_client_graphic* this, t_socketstream* sockstream)
{
  client_initialize(&this->parent_client, sockstream);
  this->parent_client.vtable = &client_graphic_vtable;
}

void			client_graphic_release(t_client_graphic* this)
{
  client_release(&this->parent_client);
}

void			client_graphic_run_input(t_client_graphic* this, t_server* server)
{
  char			buffer[4096];
  char*			datas[2];
  int			i;
  int			size;
  t_monitor_command*	command;

  while ((size = socketstream_read(this->parent_client.socketstream, buffer, 4096)))
    {
      command = NULL;
      i = 0;
      strtok(buffer, "\n");
      strtok(buffer, " ");
      datas[0] = strtok(NULL, " ");
      datas[1] = strtok(NULL, " ");
      while (g_monitor_commands[i].request && strncmp(buffer, g_monitor_commands[i].request, size))
	i++;
      if (g_monitor_commands[i].request)
	{
	  if ((g_monitor_commands[i].has_data == 1 && datas[0] != NULL && datas[1] == NULL) ||
	      (g_monitor_commands[i].has_data == 2 && datas[0] != NULL && datas[1] != NULL) ||
	      (g_monitor_commands[i].has_data == 0 && datas[0] == NULL && datas[1] == NULL))
	    command = monitor_command_new(this, datas, i);
	}
      if (command)
	server_add_monitor_command(server, command);
      else
      	printf("error: invalid command send by a client monitor!\n");
    }
}

void			client_graphic_remove(t_client_graphic* this, t_server* server)
{
  gameplay_remove_monitor(server->gameplay, (t_client*)this);
}

t_client_graphic*	client_graphic_new(t_socketstream* sockstream)
{
  t_client_graphic*	client_graphic;

  client_graphic = malloc(sizeof(t_client_graphic));
  if (client_graphic == NULL)
    return (NULL);
  client_graphic_initialize(client_graphic, sockstream);
  return (client_graphic);
}

void			client_graphic_delete(t_client_graphic* client_graphic)
{
  client_graphic_release(client_graphic);
  free(client_graphic);
}
