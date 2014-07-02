#ifndef		PARSER_H_
# define	PARSER_H_

# include "config.h"

typedef struct  s_func
{
  char key;
  int  (*func)(int argc, char **argv, t_config* config);
}               t_func;

int		opt_p(int argc, char **argv, t_config* config);
int		opt_x(int argc, char **argv, t_config* config);
int		opt_y(int argc, char **argv, t_config* config);
int		opt_n(int argc, char **argv, t_config* config);
int		opt_c(int argc, char **argv, t_config* config);
int		opt_t(int argc, char **argv, t_config* config);

int		parser(int argc, char **argv, t_config* config);

#endif		/* PARSER_H_ */
