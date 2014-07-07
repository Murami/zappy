#ifndef		_GAMEPLAY_H_
# define	_GAMEPLAY_H_

# include	"config.h"
# include	"map.h"
# include	"list.h"

struct s_client;

typedef struct	s_gameplay
{
  t_list*	teams;

  t_list*	players;
  t_list*	monitors;

  /* t_list*	requests; */
  /* t_list*	output; */
  t_map		map;
  int		delay;
}		t_gameplay;

void		gameplay_initialize(t_gameplay *this, t_config config);
t_gameplay*    	gameplay_new(t_config config);

void		gameplay_remove_player(t_gameplay* this, struct s_client* client);
void		gameplay_add_player(t_gameplay* this, struct s_client* client);
void		gameplay_remove_monitor(t_gameplay* this, struct s_client* client);
t_monitor*	gameplay_add_monitor(t_gameplay* this, struct s_client* client);

t_player*	gameplay_add_player_command(t_gameplay* this, struct s_client_command* command);
void		gameplay_add_monitor_command(t_gameplay* this, struct s_monitor_command* command);

void		gameplay_run(t_gameplay* this);

void		gameplay_release(t_gameplay *this);
void		gameplay_delete(t_gameplay *this);

#endif /* _GAMEPLAY_H_ */
