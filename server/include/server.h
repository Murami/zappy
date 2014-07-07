#ifndef		_SERVER_H_
# define	_SERVER_H_

# include	<netinet/in.h>
# include	<sys/select.h>

# include	"config.h"
# include	"gameplay.h"
# include	"list.h"

struct s_client;
struct s_socketstream;

typedef struct		s_server
{
  int			socket_max;
  int			socket;
  t_gameplay*    	gameplay;
  t_list*		new_clients;
  t_list*		clients; /* ia et monitor */
}			t_server;

void			sighandler(int);

/* public functions */

void			server_initialize(t_server *this, t_config config);
void			server_release(t_server *this);
void			server_launch(t_server *this);
void			server_accept(t_server *this);

void			server_add_monitor(t_server *this, struct s_client *client, char *buffer);
void			server_add_player(t_server *this, struct s_client *client);
void			server_remove_monitor(t_server *this, struct s_client *client);
void			server_remove_player(t_server *this, struct s_client *client);

/* functions input output */

void			server_process_new_clients(t_server* this, fd_set* fd_set_in, fd_set* fd_set_out);
void			server_process_clients(t_server* this, fd_set* fd_set_in, fd_set* fd_set_out);

bool			server_process_clients_input(t_server* this, fd_set* fd_set_in, struct s_client* client);
bool			server_process_clients_output(t_server* this, fd_set* fd_set_in, struct s_client* client);
bool			server_process_new_clients_input(t_server* this, fd_set* fd_set_in, struct s_socketstream* new_client);
bool			server_process_new_clients_output(t_server* this, fd_set* fd_set_in, struct s_socketstream* new_client);
bool			server_read_new_clients_input(t_server* this, struct s_socketstream* new_client);

/* private functions */

void			create_socket(t_server *this, int port);
void			bind_socket(t_server *this, struct sockaddr_in *sin);
void			create_queue(t_server *this);
void			reset_rfds(t_server *this, fd_set *fd_set_in, fd_set* fd_set_out);

#endif	/* _SERVER_H_ */
