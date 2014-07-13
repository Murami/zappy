#ifndef SERVER_CORE_H
# define SERVER_CORE_H

void	server_initialize(t_server*, t_config);
void	server_release(t_server*);
void	server_launch(t_server*);
void	server_accept(t_server*);
void	server_add_monitor(t_server*, struct s_client*);
void	server_add_player(t_server*, struct s_client* , struct s_team*);
void	server_remove(t_server*, struct s_client*);
void	server_add_player_command(t_server*, struct s_player_command*);
void	server_add_monitor_command(t_server*, struct s_monitor_command*);

#endif /* SERVER_CORE_H */
