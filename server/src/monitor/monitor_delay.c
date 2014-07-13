/*
** monitor_delay.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:33:35 2014 otoshigami
** Last update Sun Jul 13 17:33:36 2014 otoshigami
*/

#include <stdio.h>
#include "player.h"
#include "client.h"
#include "client_graphic.h"
#include "monitor.h"
#include "gameplay.h"

void			monitor_send_delay(t_gameplay *this, t_client *client)
{
  char			buff[4096];

  sprintf(buff, "sgt %d\n", this->delay);
  client_send_msg(client, buff);
}
