#include <stdio.h>
#include <stdlib.h>

#include "client_graphic.h"

t_client_vtable client_graphic_vtable =
  {
    (t_client_run_input_ptr)client_graphic_run_input,
    (t_client_delete_ptr)client_graphic_delete
  };

void	client_graphic_initialize(t_client_graphic* this, t_socketstream* sockstream)
{
  client_initialize(&this->parent_client, sockstream);
}

void	client_graphic_release(t_client_graphic* this)
{
  client_release(&this->parent_client);
}

void	client_graphic_run_input(t_client_graphic* this, t_server* server)
{
  (void) this;
  (void) server;
  printf("A client graphic just received some data");
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
