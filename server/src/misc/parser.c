/*
** parser.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:06:05 2014 otoshigami
** Last update Sun Jul 13 23:06:39 2014 pinon
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include "parser.h"
#include "team.h"

t_func  options[] =
{
  {'p', &opt_p},
  {'x', &opt_x},
  {'y', &opt_y},
  {'n', &opt_n},
  {'c', &opt_c},
  {'t', &opt_t},
  {'\0', NULL}
};

int		opt_c(int argc, char **argv, t_config* config)
{
  optind--;
  while (optind < argc && *argv[optind] != '-')
    {
      errno = 0;
      config->nbr = strtol (argv[optind], (char**)NULL, 10);
      if ((errno == ERANGE && (config->nbr == LONG_MAX ||
			       config->nbr == LONG_MIN)) ||
	  config->nbr > INT_MAX ||
	  errno != 0)
	{
	  printf("%s: invalid number of client by teams %s\n",
		 argv[0], argv[optind]);
	  return (1);
	}
      optind++;
    }
  return (0);
}

int		opt_t(int argc, char **argv, t_config* config)
{
  optind--;
  while (optind < argc && *argv[optind] != '-')
    {
      errno = 0;
      config->delay = strtol (argv[optind], (char**)NULL, 10);
      if ((errno == ERANGE && (config->delay == LONG_MAX ||
			       config->delay == LONG_MIN)) ||
	  config->delay > INT_MAX ||
	  errno != 0 || config->delay == 0)
	{
	  printf("%s: invalid delay %s\n", argv[0], argv[optind]);
	  return (1);
	}
      optind++;
    }
  return (0);
}

void		init_config(t_config* config)
{
  config->team_names = list_new();
  config->teams = list_new();
  config->port = 4242;
  config->width = 20;
  config->height = 20;
  config->delay = 100;
  config->nbr = 3;
  list_push_back(config->teams, team_new(config->nbr, "team1"));
  list_push_back(config->teams, team_new(config->nbr, "team2"));
}

int		parser(int argc, char **argv, t_config* config)
{
  char			optch;
  extern int		opterr;
  char			format[] = "p:x:y:n:c:t:";
  int			i;
  t_list_iterator	it;

  init_config(config);
  opterr = 1;
  while ((optch = getopt(argc, argv, format)) != -1)
    {
      i = 0;
      while (options[i].func != NULL)
  	{
  	  if (options[i].key == optch && options[i].func(argc, argv, config))
  	    return (1);
  	  i++;
  	}
    }
  it = list_begin(config->team_names);
  while (it != list_end(config->team_names))
    {
      list_push_back(config->teams, team_new(config->nbr, it->data));
      it = list_iterator_next(it);
    }
  return (0);
}
