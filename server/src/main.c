/*
** main.c for main in /home/desabr_q/Desktop/zappy/PSU_2013_zappy
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Wed Jun 25 12:03:10 2014 quentin desabre
** Last update Wed Jul  2 15:36:33 2014 pinon
*/

#include "server.h"
#include "parser.h"

int		main(int ac, char** av)
{
  t_server	server;
  t_config	option;

  parser(ac, av, &option);

  if (ac == 2)
    server_initialize(&server, atoi(av[1]));
  else
    server_initialize(&server, 4242);
  server_launch(&server);
  return (0);
}
