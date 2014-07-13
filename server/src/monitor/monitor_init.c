/*
** monitor_init.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:34:00 2014 otoshigami
** Last update Sun Jul 13 17:34:05 2014 otoshigami
*/

#include <stdio.h>
#include "player.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"
#include "socketstream.h"
#include "gameplay.h"

void			monitor_initialize(t_gameplay *this, t_client *client)
{
  printf("new monitor connected [%d]\n", client->socketstream->socket);
  monitor_send_size(this, client);
  monitor_send_delay(this, client);
  monitor_send_map(this, client);
  monitor_send_teams(this, client);
  monitor_send_players(this, client);
  monitor_send_eggs(this, client);
}
