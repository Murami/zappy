#ifndef CLIENT_GRAPHICAL_H
# define CLIENT_GRAPHICAL_H

# include "client.h"
# include "server.h"

t_client_vtable client_graphic_vtable;

typedef struct		s_client_graphic
{
  t_client		parent_client;
}			t_client_graphic;

void			client_graphic_initialize(t_client_graphic* this, t_socketstream* sockstream);
void			client_graphic_release(t_client_graphic* this);

void			client_graphic_run(t_client_graphic* this, t_server* server);

t_client_graphic*	client_graphic_new(t_socketstream* sockstream);
void			client_graphic_delete(t_client_graphic* client_graphic);

#endif /* CLIENT_GRAPHICAL_H */
