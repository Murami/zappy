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
	  errno != 0)
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
