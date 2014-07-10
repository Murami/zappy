#include "server.h"
#include "socketstream.h"
#include "client.h"

void			server_process_new_clients(t_server* this,
						   fd_set* fd_set_in, fd_set* fd_set_out)
{
  t_list_iterator	it;
  t_socketstream*	new_client;

  it = list_begin(this->new_clients);
  while (it != list_end(this->new_clients))
    {
      new_client = it->data;
      if (!server_process_new_clients_input(this, fd_set_in, new_client) ||
	  !server_process_new_clients_output(this, fd_set_out, new_client))
	{
	  socketstream_delete(new_client);
	  it = list_erase(this->new_clients, it);
	}
      it = list_iterator_next(it);
    }
}

void			server_process_clients(t_server* this,
					       fd_set* fd_set_in, fd_set* fd_set_out)
{
  t_list_iterator	it;
  t_client*		client;

  it = list_begin(this->clients);
  while (it != list_end(this->clients))
    {
      client = it->data;
      if (!server_process_clients_input(this, fd_set_in, client) ||
	  !server_process_clients_output(this, fd_set_out, client))
	it = server_remove(this, it);
      it = list_iterator_next(it);
    }
}
