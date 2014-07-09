#ifndef		_GAMEPLAY_H_
# define	_GAMEPLAY_H_

# include	"config.h"
# include	"map.h"
# include	"list.h"

struct s_player_command;
struct s_monitor_command;
struct s_client;
struct s_monitor;
struct s_player;
struct s_server;
struct s_team;

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

void			gameplay_initialize(t_gameplay *this, t_config config);
void			gameplay_release(t_gameplay *this);

void			gameplay_update(t_gameplay *this);
void			gameplay_remove_player(t_gameplay* this, struct s_client* client);
void			gameplay_add_player(t_gameplay* this, struct s_client* client, struct s_team *team);
void			gameplay_remove_monitor(t_gameplay* this, struct s_client* client);
void			gameplay_add_monitor(t_gameplay* this, struct s_client* client);

void			gameplay_add_player_command(t_gameplay* this, struct s_player_command* command);
void			gameplay_add_monitor_command(t_gameplay* this, struct s_monitor_command* command);

void			gameplay_command_avance(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_droite(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_gauche(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_voir(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_inventaire(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_prend_objet(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_expulse(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_broadcast(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_incantation(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_fork(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_connect_nbr(t_gameplay* this, struct s_player_command* command);

t_gameplay*		gameplay_new(t_config config);
void			gameplay_delete(t_gameplay *this);

#endif /* _GAMEPLAY_H_ */
