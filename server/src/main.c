/*
** main.c for main in /home/desabr_q/Desktop/zappy/PSU_2013_zappy
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Wed Jun 25 12:03:10 2014 quentin desabre
** Last update Wed Jun 25 12:16:27 2014 Desabre Quentin
*/

#include "server.h"

int		main()
{
  t_server	server;

  server_initialize(&server);
  server_launch(&server);
}
