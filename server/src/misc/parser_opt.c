/*
** parser_opt.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:06:09 2014 otoshigami
** Last update Sun Jul 13 17:08:01 2014 otoshigami
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

#include "parser.h"
#include "team.h"

int		opt_n(int argc, char **argv, t_config* config)
{
  optind--;
  while (optind < argc && *argv[optind] != '-')
    {
      list_push_back(config->team_names, argv[optind]);
      optind++;
    }
  return (0);
}

int		opt_p(int argc, char **argv, t_config* config)
{
  optind--;
  while (optind < argc && *argv[optind] != '-')
    {
      errno = 0;
      config->port = strtol (argv[optind], (char**)NULL, 10);
      if ((errno == ERANGE && (config->port == LONG_MAX ||
			       config->port == LONG_MIN)) ||
	  config->port < 1024 || config->port > 65535 ||
	  errno != 0)
	{
	  printf("%s: invalid port %s\n", argv[0], argv[optind]);
	  return (1);
	}
      optind++;
    }
  return (0);
}

int		opt_x(int argc, char **argv, t_config* config)
{
  optind--;
  while (optind < argc && *argv[optind] != '-')
    {
      errno = 0;
      config->width = strtol (argv[optind], (char**)NULL, 10);
      if ((errno == ERANGE && (config->width == LONG_MAX ||
			       config->width == LONG_MIN)) ||
	  config->width > INT_MAX  ||
	  errno != 0)
	{
	  printf("%s: invalid width %s\n", argv[0], argv[optind]);
	  return (1);
	}
      optind++;
    }
  return (0);
}

int		opt_y(int argc, char **argv, t_config* config)
{
  optind--;
  while (optind < argc && *argv[optind] != '-')
    {
      errno = 0;
      config->height = strtol (argv[optind], (char**)NULL, 10);
      if ((errno == ERANGE && (config->height == LONG_MAX ||
			       config->height == LONG_MIN)) ||
	  config->height > INT_MAX ||
	  errno != 0)
	{
	  printf("%s: invalid height %s\n", argv[0], argv[optind]);
	  return (1);
	}
      optind++;
    }
  return (0);
}
