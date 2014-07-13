/*
** config.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:26:08 2014 otoshigami
** Last update Sun Jul 13 17:26:09 2014 otoshigami
*/

#ifndef		_CONFIG_H_
# define	_CONFIG_H_

# include	"list.h"

typedef struct	s_config
{
  long int		port;
  long int		width;
  long int		height;
  long int		delay;
  long int		nbr;
  t_list		*team_names;
  t_list		*teams;
}		t_config;

#endif	/* _CONFIG_H_ */
