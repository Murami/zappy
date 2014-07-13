/*
** parser.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:23:26 2014 otoshigami
** Last update Sun Jul 13 17:23:27 2014 otoshigami
*/

#ifndef		PARSER_H_
# define	PARSER_H_

# include "config.h"

typedef struct  s_func
{
  char key;
  int  (*func)(int argc, char **argv, t_config* config);
}               t_func;

extern t_func  options[];

int		opt_p(int argc, char **argv, t_config* config);
int		opt_x(int argc, char **argv, t_config* config);
int		opt_y(int argc, char **argv, t_config* config);
int		opt_n(int argc, char **argv, t_config* config);
int		opt_c(int argc, char **argv, t_config* config);
int		opt_t(int argc, char **argv, t_config* config);

int		parser(int argc, char **argv, t_config* config);

#endif		/* PARSER_H_ */
