#ifndef		_GAMEPLAY_H_
# define	_GAMEPLAY_H_

# include	"config.h"
# include	"map.h"
# include	"list.h"

typedef struct	s_gameplay
{
  t_list*	teams;

  t_list*	players;
  t_list*	monitors;

  t_list*	requests;
  t_list*	output;
  t_map		map;
  int		delay;
}		t_gameplay;


void		gameplay_initialize(t_gameplay *this, t_config config);
t_gameplay*    	gameplay_new(t_config config);
void		gameplay_release(t_gameplay *this);
void		gameplay_delete(t_gameplay *this);
void		gameplay_update(t_gameplay *this);



#endif /* _GAMEPLAY_H_ */
