#ifndef		_SERVER_H_
# define	_SERVER_H_

# include	<netinet/in.h>
# include	<sys/select.h>

# include	"list.h"

struct s_client;

typedef struct		s_server
{
  int			socket_max;
  int			socket;
  t_list*		new_clients;
  t_list*		clients;
}			t_server;

/* public functions */

void			server_initialize(t_server *this, int port);
void			server_release(t_server *this);
void			server_launch(t_server *this);
void			server_accept(t_server *this);
void			server_process_clients(t_server* this, fd_set* fd_set_in, fd_set* fd_set_out);
void			server_process_new_clients(t_server* this, fd_set* fd_set_in, fd_set* fd_set_out);

void			server_add_monitor(t_server *this, struct s_client *client);
void			server_add_player(t_server *this, struct s_client *client);

void			server_remove_monitor(t_server *this, struct s_client *client);
void			server_remove_player(t_server *this, struct s_client *client);

/* private functions */

void			create_socket(t_server *this, int port);
void			bind_socket(t_server *this, struct sockaddr_in *sin);
void			create_queue(t_server *this);
void			reset_rfds(t_server *this, fd_set *fd_set_in, fd_set* fd_set_out);

#endif	/* _SERVER_H_ */
