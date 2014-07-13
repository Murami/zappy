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

extern bool		g_alive;

void			sighandler(int);

# include "server_core.h"
# include "server_io.h"

void		create_socket(t_server*, int);
void		bind_socket(t_server*, struct sockaddr_in*);
void		create_queue(t_server*);
void		reset_rfds(t_server*, fd_set*, fd_set*);
void		server_delete_deads(t_server*);
void		server_add_player_command(t_server*, struct s_player_command*);
void		server_add_monitor_command(t_server*, struct s_monitor_command*);
struct s_team*	server_check_teams(struct s_server*, char*, int);

#endif	/* _SERVER_H_ */
