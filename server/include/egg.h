/*
** egg.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:27:42 2014 otoshigami
** Last update Sun Jul 13 17:27:44 2014 otoshigami
*/

#ifndef EGG_H
# define EGG_H

# include <sys/time.h>

struct s_team;

typedef struct		s_egg
{
  int			x;
  int			y;
  struct s_team*	team;
  struct timeval	time;
  int			id_player;
  int			id;
}			t_egg;

#endif /* EGG_H */
