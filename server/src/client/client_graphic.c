/*
** client_graphic.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:03:26 2014 otoshigami
** Last update Sun Jul 13 23:19:51 2014 otoshigami
*/

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

void			client_graphic_remove(t_client_graphic* this,
					      t_server* server)
{
  gameplay_remove_monitor(server->gameplay, (t_client*)this);
}

void			client_data_init(char *buffer, char **d)
{
  strtok(buffer, "\n");
  strtok(buffer, " ");
  d[0] = strtok(NULL, " ");
  d[1] = strtok(NULL, " ");
}

void			client_graphic_run_input(t_client_graphic* this,
						 t_server* server)
{
  char			buffer[4096];
  char*			d[2];
  int			i;
  int			size;
  t_monitor_command*	command;

  while ((size = socketstream_read(this->parent_client.socketstream,
				   buffer, 4096)))
    {
      i = 0;
      command = NULL;
      client_data_init(buffer, d);
      while (g_monitor_commands[i].request &&
	     strncmp(buffer, g_monitor_commands[i].request, size))
	i++;
      if (g_monitor_commands[i].request &&
	  ((g_monitor_commands[i].has_data == 1 && d[0] && !d[1]) ||
	   (g_monitor_commands[i].has_data == 2 && d[0] && d[1]) ||
	   (!g_monitor_commands[i].has_data == 0 && d[0] && !d[1])))
	command = monitor_command_new(this, d, i);
      if (command)
	server_add_monitor_command(server, command);
      else
	gameplay_send_suc(&this->parent_client);
    }
}
