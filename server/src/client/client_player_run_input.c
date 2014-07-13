/*
** client_player_run_input.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 18:03:38 2014 quentin desabre
** Last update Sun Jul 13 19:32:59 2014 otoshigami
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client_player.h"
#include "socketstream.h"
#include "server.h"
#include "player_command.h"

static char*		get_data(char* buffer, char* buffer_original)
{
  strtok(buffer, "\n");
  strcpy(buffer_original, buffer);
  strtok(buffer, " ");
  return (strtok(NULL, " "));
}

static t_player_command*	get_command(t_server* server,
					    t_client_player* client,
					    char* buffer, int size)
{
  int		i;
  char*		data;
  char		buffer_original[4096];

  i = 0;
  data = get_data(buffer, buffer_original);
  while (g_player_commands[i].request &&
	 strncmp(buffer, g_player_commands[i].request, size))
    i++;
  if (g_player_commands[i].request)
    {
      if (strncmp(g_player_commands[i].request, "broadcast", size) == 0)
	return (player_command_new(client, server->gameplay,
				   buffer_original + strlen("broadcast") + 1, i));
      printf("player command : %s\n", buffer_original);
      if ((g_player_commands[i].has_data == 1 && data != NULL) ||
	  (g_player_commands[i].has_data == 0 && data == NULL))
	return (player_command_new(client, server->gameplay, data, i));
    }
  return (NULL);
}

void			client_player_run_input(t_client_player* this,
						t_server* server)
{
  char			buffer[4096];
  t_player_command*	command;
  int			size;

  while ((size = socketstream_read(this->parent_client.socketstream,
				   buffer, 4096)))
    {
      if ((command = get_command(server, this, buffer, size)))
	server_add_player_command(server, command);
      else
	{
	  printf("error: invalid command send by a client player!\n");
	  gameplay_send_res(&this->parent_client, false);
	}
    }
}
