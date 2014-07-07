#ifndef CLIENT_PLAYER_H
# define CLIENT_PLAYER_H

# include "client.h"

t_client_vtable client_player_vtable;

typedef struct	s_client_player
{
  t_client	parent_client;
}		t_client_player;

void			client_player_initialize(t_client_player* this, struct s_socketstream* sockstream);
void			client_player_release(t_client_player* this);

void			client_player_run_input(t_client_player* this, struct s_server* server);
void			client_player_remove(t_client_player* this, struct s_server* server);

t_client_player*	client_player_new(struct s_socketstream* sockstream);
void			client_player_delete(t_client_player* client_player);

#endif /* CLIENT_PLAYER_H */
