/*
** server_io.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:28:37 2014 otoshigami
** Last update Sun Jul 13 17:28:39 2014 otoshigami
*/

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
