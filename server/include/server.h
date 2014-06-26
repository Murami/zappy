#ifndef		_SERVER_H_
# define	_SERVER_H_

# include	<netdb.h>
# include	<sys/select.h>
# include	<netinet/in.h>
# include	<arpa/inet.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<string.h>

typedef struct		s_server
{
  fd_set		rfds;
  int			socket;
  int			nb_connexions;
}			t_server;

/* public functions */

void			server_initialize(t_server *this);
void			server_release(t_server *this);
void			server_launch(t_server *this);

/* private functions */

void			create_socket(t_server *this, int port);
void			bind_socket(t_server *this, struct sockaddr_in *sin);
void			create_queue(t_server *this);
void			reset_rfds(t_server *this);

#endif	/* _SERVER_H_ */
