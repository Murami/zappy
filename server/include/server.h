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

# include "server_core.h"
# include "server_io.h"

void	create_socket(t_server *this, int port);
void	bind_socket(t_server *this, struct sockaddr_in *sin);
void	create_queue(t_server *this);
void	reset_rfds(t_server *this, fd_set *fd_set_in, fd_set* fd_set_out);

#endif	/* _SERVER_H_ */
