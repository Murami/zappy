#ifndef SERVER_CORE_H
# define SERVER_CORE_H

void	server_initialize(t_server *this, t_config config);
void	server_release(t_server *this);
void	server_launch(t_server *this);
void	server_accept(t_server *this);

void	server_add_monitor(t_server *this, struct s_client *client);
void	server_add_player(t_server *this, struct s_client *client, struct s_team* team);
void	server_remove(t_server *this, struct s_client* client);
void	server_add_player_command(t_server* this, struct s_player_command* command);
void	server_add_monitor_command(t_server* this, struct s_monitor_command* command);

#endif /* SERVER_CORE_H */
