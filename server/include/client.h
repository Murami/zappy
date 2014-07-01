#ifndef CLIENT_H
# define CLIENT_H

# include "socketstream.h"

/* CLIENT VIRTUAL TABLE DEFINITION FOR INHERITANCE */

typedef struct	s_client_vtable
{
  void		(*run)(struct s_client);
}		t_client_vtable;

/* INHERITS FROM SOCKETSTREAM */
typedef struct		s_client
{
  t_socketstream	socketstream;
  t_client_vtable*     	vtable;
}			t_client;

void		client_initialize(t_client* this, int socket);
void		client_release(t_client* this);

/* VIRTUAL METHODS */
void		client_run(t_client* this);

t_client*	client_new(int socket);
void		client_delete(t_client* client);

#endif /* CLIENT_H */
