#ifndef		_SERVER_H_
# define	_SERVER_H_

# include	<netinet/in.h>
# include	<sys/select.h>
# include	<sys/time.h>

# include	"config.h"
# include	"gameplay.h"
# include	"list.h"

struct s_client;
struct s_team;
struct s_socketstream;
struct s_client_command;
struct s_player_command;
struct s_monitor_command;

typedef struct		s_server
{
  int			socket_max;
  int			socket;
  t_gameplay*    	gameplay;
  t_list*		new_clients;
  t_list*		clients;
  t_list*		deads;
}			t_server;

void			sighandler(int);

/* public functions */

void			server_initialize(t_server *this, t_config config);
void			server_release(t_server *this);
void			server_launch(t_server *this);
void			server_accept(t_server *this);

void			server_add_monitor(t_server *this, struct s_client *client);
void			server_add_player(t_server *this, struct s_client *client, struct s_team* team);
void			server_remove(t_server *this, struct s_client* client);
void			server_add_player_command(t_server* this, struct s_player_command* command);
void			server_add_monitor_command(t_server* this, struct s_monitor_command* command);

/* functions input output */

void			server_process_new_clients(t_server* this, fd_set* fd_set_in, fd_set* fd_set_out);
void			server_process_clients(t_server* this, fd_set* fd_set_in, fd_set* fd_set_out);
void			server_process_deads(t_server* this, fd_set* fd_set_in);

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
