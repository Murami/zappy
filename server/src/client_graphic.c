#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "client_graphic.h"
#include "socketstream.h"
#include "server.h"

t_client_vtable client_graphic_vtable =
  {
    (t_client_run_input_ptr)client_graphic_run_input,
    (t_client_remove_ptr)client_graphic_remove,
    (t_client_delete_ptr)client_graphic_delete
  };

void	client_graphic_initialize(t_client_graphic* this, t_socketstream* sockstream)
{
  client_initialize(&this->parent_client, sockstream);
  this->parent_client.vtable = &client_graphic_vtable;
}

void	client_graphic_release(t_client_graphic* this)
{
  client_release(&this->parent_client);
}

void	client_graphic_run_input(t_client_graphic* this, t_server* server)
{
  (void) this;
  char			buffer[4096];
  int			size;

  (void) server;
  while ((size = socketstream_read(this->parent_client.socketstream, buffer, 4096)))
    {
      if (strncmp("data\n", buffer, size) == 0)
	{
	  printf("received data\n");
	}
      else
	{

	}
    }
  /* printf("A client graphic just received some data"); */
}

void			client_graphic_remove(t_client_graphic* client, t_server* server)
{
  t_list_iterator	it;
  t_client_graphic*	tmp;

  it = list_begin(server->clients);
  while (it != list_end(server->clients))
    {
      tmp = it->data;
      if (tmp == client)
	{
	  it = list_erase(server->clients, it);
	  return;
	}
      it = list_iterator_next(it);
    }
}

t_client_graphic*	client_graphic_new(t_socketstream* sockstream)
{
  t_client_graphic*	client_graphic;

  client_graphic = malloc(sizeof(t_client_graphic));
  if (client_graphic == NULL)
    return (NULL);
  client_graphic_initialize(client_graphic, sockstream);
  return (client_graphic);
}

void			client_graphic_delete(t_client_graphic* client_graphic)
{
  client_graphic_release(client_graphic);
  free(client_graphic);
}
