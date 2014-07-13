#ifndef SERVER_IO_H
# define SERVER_IO_H

void	server_process_new_clients(t_server* this, fd_set* fd_set_in, fd_set* fd_set_out);
void	server_process_clients(t_server* this, fd_set* fd_set_in, fd_set* fd_set_out);
void	server_process_deads(t_server* this, fd_set* fd_set_in);

bool	server_process_clients_input(t_server* this, fd_set* fd_set_in, struct s_client* client);
bool	server_process_clients_output(t_server* this, fd_set* fd_set_in, struct s_client* client);
bool	server_process_new_clients_input(t_server* this, fd_set* fd_set_in, struct s_socketstream* new_client);
bool	server_process_new_clients_output(t_server* this, fd_set* fd_set_in, struct s_socketstream* new_client);
bool	server_read_new_clients_input(t_server* this, struct s_socketstream* new_client);

#endif /* SERVER_IO_H */
