/*
** server_add.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:28:08 2014 quentin desabre
** Last update Sun Jul 13 16:39:33 2014 Desabre Quentin
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

void			server_add_player_command(t_server* this,
						  t_player_command* command)
{
  gameplay_add_player_command(this->gameplay, command);
}

void			server_add_monitor_command(t_server* this,
						   t_monitor_command* command)
{
  gameplay_add_monitor_command(this->gameplay, command);
}
