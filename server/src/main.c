#include <stdlib.h>
#include "list.h"
#include "team.h"
#include "config.h"
#include "server.h"
#include "parser.h"

int		main(int ac, char **av)
{
  t_config	config;
  t_server	server;

  parser(ac, av, &config);
  server_initialize(&server, config);
  server_launch(&server);
  return (0);
}
