#ifndef GAMEPLAY_CORE_H
#define GAMEPLAY_CORE_H

void	gameplay_initialize(t_gameplay*, t_config, struct s_server*);
void	gameplay_release(t_gameplay*);
void	gameplay_remove_player(t_gameplay*, struct s_client*);
void	gameplay_add_player(t_gameplay*, struct s_client*, struct s_team*);
void	gameplay_remove_monitor(t_gameplay*, struct s_client*);
void	gameplay_add_monitor(t_gameplay*, struct s_client*);
int	gameplay_get_new_id(t_gameplay*);
void	gameplay_add_player_command(t_gameplay*, struct s_player_command*);
void	gameplay_add_monitor_command(t_gameplay*, struct s_monitor_command*);
void	gameplay_update_player_position(t_gameplay*, struct s_player*,
					t_list*);
bool	check_incant(t_gameplay*, struct s_player_command*);
int	count_taken_slot(t_gameplay*, struct s_team*);
void	bind_command_object(t_gameplay*, struct s_player_command*,
			    t_case*, int);

t_gameplay*	gameplay_new(t_config, struct s_server*);
void		gameplay_delete(t_gameplay*);
t_list_iterator	gameplay_kill_player(t_gameplay*, struct s_player*);
t_list_iterator	gameplay_kill_ghost(t_gameplay*, struct s_player*);
struct timeval	gameplay_update(t_gameplay*, struct timeval);
struct timeval	gameplay_update_players(t_gameplay*, struct timeval,
					t_list*, kill_func);

#endif /* GAMEPLAY_CORE_H */
