#ifndef CLIENT_H
# define CLIENT_H

/* # include "server.h" */
/* # include "socketstream.h" */

struct s_sockstream;
struct s_server;
struct s_list;

typedef void (*t_client_run_input_ptr)(void*, struct s_server*);
typedef void (*t_client_remove_ptr)(void*, struct s_server*);
typedef void (*t_client_delete_ptr)(void*);

typedef struct			s_client_vtable
{
  t_client_run_input_ptr	run_input;
  t_client_remove_ptr		remove;
  t_client_delete_ptr		delete;
}				t_client_vtable;

typedef struct		s_client
{
  struct s_socketstream*	socketstream;
  t_client_vtable*		vtable;
  struct s_list*		requests_output;
}			t_client;

void		client_initialize(t_client* this,
				  struct s_socketstream* sockstream);
void		client_release(t_client* this);

void		client_run_input(t_client* this, struct s_server* server);
void		client_run_output(t_client* this, struct s_server* server);
void		client_remove(t_client* this, struct s_server* server);

void		client_delete(t_client* client);

void		client_send_msg(t_client *client, char *msg);

#endif /* CLIENT_H */
