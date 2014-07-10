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
	     "[-x world_x] [-y world_y] [-c max_clients] [-t speed] -n team_name_1 team_name_2 ...\n");
      return (EXIT_FAILURE);
    }
  srand(time(NULL));
  parser(ac, av, &config);
  server_initialize(&server, config);
  server_launch(&server);
  release_config(&config);
  return (EXIT_SUCCESS);
}
