/*
** main.c for main in /home/desabr_q/Desktop/zappy/PSU_2013_zappy
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Wed Jun 25 12:03:10 2014 quentin desabre
** Last update Mon Jun 30 10:33:43 2014 otoshigami
*/

#include "server.h"

int		main()
{
  t_server	server;

  server_initialize(&server);
  server_launch(&server);
  return (0);
}
