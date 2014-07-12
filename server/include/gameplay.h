#ifndef		_GAMEPLAY_H_
# define	_GAMEPLAY_H_

# include	<sys/time.h>
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
struct s_case;

typedef struct		s_gameplay
{
  t_list*		teams;
  t_list*		players;
  t_list*		monitors;
  t_list*		eggs;
  t_map			map;
  int			delay;
  struct timeval	time;
  struct s_server*	server;
}			t_gameplay;

typedef struct		s_object_binding
{
  void			(*put)(t_gameplay*, struct s_player_command*);
  void			(*take)(t_gameplay*, struct s_player_command*);
  char*			object;
}			t_object_binding;

void			gameplay_initialize(t_gameplay *this, t_config config, struct s_server* server);
void			gameplay_release(t_gameplay *this);

struct timeval		gameplay_update(t_gameplay *this, struct timeval currenttime);
void			gameplay_remove_player(t_gameplay* this, struct s_client* client);
void			gameplay_add_player(t_gameplay* this, struct s_client* client, struct s_team *team);
void			gameplay_remove_monitor(t_gameplay* this, struct s_client* client);
void			gameplay_add_monitor(t_gameplay* this, struct s_client* client);

void			gameplay_add_player_command(t_gameplay* this, struct s_player_command* command);
void			gameplay_add_monitor_command(t_gameplay* this, struct s_monitor_command* command);

void			bind_command_move(t_gameplay *this, struct s_player_command *command);
void			bind_command_take(t_gameplay *this, struct s_case *c);

void			gameplay_command_move(t_gameplay *this, struct s_player *player);
void			gameplay_command_avance(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_droite(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_gauche(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_voir(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_inventaire(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_prend(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_pose(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_expulse(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_broadcast(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_incantation(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_fork(t_gameplay* this, struct s_player_command* command);
void			gameplay_command_connect_nbr(t_gameplay* this, struct s_player_command* command);

void			gameplay_take_food(t_gameplay* this, struct s_player_command* command);
void			gameplay_take_linemate(t_gameplay* this, struct s_player_command* command);
void			gameplay_take_deraumere(t_gameplay* this, struct s_player_command* command);
void			gameplay_take_sibur(t_gameplay* this, struct s_player_command* command);
void			gameplay_take_mendiane(t_gameplay* this, struct s_player_command* command);
void			gameplay_take_phiras(t_gameplay* this, struct s_player_command* command);
void			gameplay_take_thystame(t_gameplay* this, struct s_player_command* command);
void			gameplay_drop_food(t_gameplay* this, struct s_player_command* command);
void			gameplay_drop_linemate(t_gameplay* this, struct s_player_command* command);
void			gameplay_drop_deraumere(t_gameplay* this, struct s_player_command* command);
void			gameplay_drop_sibur(t_gameplay* this, struct s_player_command* command);
void			gameplay_drop_mendiane(t_gameplay* this, struct s_player_command* command);
void			gameplay_drop_phiras(t_gameplay* this, struct s_player_command* command);
void			gameplay_drop_thystame(t_gameplay* this, struct s_player_command* command);


void			gameplay_command_msz(t_gameplay* this, struct s_monitor_command* command);
void			gameplay_command_bct(t_gameplay* this, struct s_monitor_command* command);
void			gameplay_command_mct(t_gameplay* this, struct s_monitor_command* command);
void			gameplay_command_tna(t_gameplay* this, struct s_monitor_command* command);
void			gameplay_command_ppo(t_gameplay* this, struct s_monitor_command* command);
void			gameplay_command_plv(t_gameplay* this, struct s_monitor_command* command);
void			gameplay_command_pin(t_gameplay* this, struct s_monitor_command* command);
void			gameplay_command_sgt(t_gameplay* this, struct s_monitor_command* command);
void			gameplay_command_sst(t_gameplay* this, struct s_monitor_command* command);
void			gameplay_update_player_position(t_gameplay* this, struct s_player* player);
t_list_iterator		gameplay_kill_player(t_gameplay* this, struct s_player* player);

bool			check_incant(t_gameplay* this, struct s_player_command* command);

t_gameplay*		gameplay_new(t_config config, struct s_server* server);
void			gameplay_delete(t_gameplay *this);

#endif /* _GAMEPLAY_H_ */
