/*
** monitor_size.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:34:26 2014 otoshigami
** Last update Sun Jul 13 17:34:27 2014 otoshigami
*/

#include <stdio.h>
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"
#include "gameplay.h"

void			monitor_send_size(t_gameplay *this, t_client *client)
{
  char			buff[4096];

  sprintf(buff, "msz %d %d\n", this->map.width, this->map.height);
  client_send_msg(client, buff);
}
