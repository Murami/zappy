#ifndef CLIENT_H
# define CLIENT_H

# include "socketstream.h"

typedef void (*t_client_run_input_ptr)(void*, t_server*);
typedef void (*t_client_delete_ptr)(void*);

typedef struct			s_client_vtable
{
  t_client_run_input_ptr	run_input;
  t_client_delete_ptr		delete;
}				t_client_vtable;

typedef struct		s_client
{
  t_socketstream*	socketstream;
  t_client_vtable*     	vtable;
  t_list*		requests_output;
}			t_client;

# include "server.h"

void		client_initialize(t_client* this, t_socketstream* sockstream);
void		client_release(t_client* this);

void		client_run_input(t_client* this, t_server* server);
void		client_run_output(t_client* this, t_server* server);

void		client_delete(t_client* client);

void		client_send_msg(t_client *client, char *msg);




#endif /* CLIENT_H */
