/*
** gameplay_send_err.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:23:11 2014 quentin desabre
** Last update Sun Jul 13 16:23:12 2014 Desabre Quentin
*/

#include <stdio.h>
#include <string.h>
#include "client.h"

void	gameplay_send_sbp(t_client* client)
{
  char	buffer[4096];

  sprintf(buffer, "spb\n");
  client_send_msg(client, buffer);
}

void	gameplay_send_suc(t_client* client)
{
  char	buffer[4096];

  sprintf(buffer, "suc\n");
  client_send_msg(client, buffer);
}
