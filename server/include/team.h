/*
** team.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:29:02 2014 otoshigami
** Last update Sun Jul 13 17:29:02 2014 otoshigami
*/

#ifndef		_TEAM_H_
# define	_TEAM_H_

typedef struct	s_team
{
  int		nb_slots;
  int		nb_lvl8;
  char		*name;
}		t_team;

void		team_initialize(t_team *this, int nb_slots, char *name);
t_team*		team_new(int nb_slots, char *name);
void		team_release(t_team *this);
void		team_delete(t_team *this);

#endif	/* _TEAM_H_ */
