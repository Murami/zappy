#ifndef SERVER_IO_H
# define SERVER_IO_H

void	server_process_new_clients(t_server*, fd_set*, fd_set*);
void	server_process_clients(t_server*, fd_set*, fd_set*);
void	server_process_deads(t_server*, fd_set*);

bool	server_process_clients_input(t_server*, fd_set*, struct s_client*);
bool	server_process_clients_output(t_server*, fd_set*, struct s_client*);
bool	server_process_new_clients_input(t_server*, fd_set*,
					 struct s_socketstream*);
bool	server_process_new_clients_output(t_server*, fd_set*,
					  struct s_socketstream*);
bool	server_read_new_clients_input(t_server*, struct s_socketstream*);

#endif /* SERVER_IO_H */
