#ifndef		_SERVER_H_
# define	_SERVER_H_

# include	<netinet/in.h>
# include	<sys/select.h>
# include	"socketstream.h"

typedef struct		s_server
{
  int			client[4096];
  int			socket;
  int			nb_connexions;
}			t_server;

/* public functions */

void			server_initialize(t_server *this);
void			server_release(t_server *this);
void			server_launch(t_server *this);
void			server_accept(t_server *this);

/* private functions */

void			create_socket(t_server *this, int port);
void			bind_socket(t_server *this, struct sockaddr_in *sin);
void			create_queue(t_server *this);
void			reset_rfds(t_server *this, fd_set *rfds);

#endif	/* _SERVER_H_ */
