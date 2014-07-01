#ifndef		_TEAM_H_
# define	_TEAM_H_

typedef struct	s_team
{
  int		nb_slots;
  char		*name;
}		t_team;

void		team_initialize(t_team *this, int nb_slots, char *name);
t_team*		team_new(int nb_slots, char *name);
void		team_release(t_team *this);
void		team_delete(t_team *this);

#endif	/* _TEAM_H_ */
