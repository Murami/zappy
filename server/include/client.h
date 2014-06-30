#ifndef CLIENT_H
# define CLIENT_H

# include "socketstream.h"

typedef enum	e_client_type
  {
    UNKNOWN,
    AI,
    GRAPHIC
  }		t_client_type;

typedef struct		s_client
{
  t_client_type		type;
  t_socketstream*	socketstream;
}			t_client;

void	client_initialize(t_client* this, int socket);
void	client_release(t_client* this);

t_client*	client_new(int socket);
void		client_delete(t_client* client);

#endif /* CLIENT_H */
