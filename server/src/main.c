/*
** main.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 18:06:50 2014 quentin desabre
** Last update Sun Jul 13 20:08:07 2014 otoshigami
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"
#include "team.h"
#include "config.h"
#include "server.h"
#include "parser.h"

void		release_config(t_config* config)
{
  while (!list_empty(config->team_names))
    {
      free(list_back(config->team_names));
      list_pop_back(config->team_names);
    }
  list_delete(config->team_names);
}

int		main(int ac, char **av)
{
  t_config	config;
  t_server	server;

  if (ac < 2)
    {
      printf("usage: ./zappy-server-linux [[[-p port] -p port] ...] "
	     "[-x world_x] [-y world_y] [-c max_clients] [-t speed]"
	     "-n team_name_1 team_name_2 ...\n");
      return (EXIT_FAILURE);
    }
  srand(time(NULL));
  if (parser(ac, av, &config))
    return (EXIT_FAILURE);
  server_initialize(&server, config);
  server_launch(&server);
  release_config(&config);
  return (EXIT_SUCCESS);
}
