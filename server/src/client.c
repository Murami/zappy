#include <stdlib.h>
#include "client.h"

void		client_initialize(t_client* this, int socket)
{
  this->socketstream = socketstream_new(socket);
  this->type = UNKNOWN;
}

void		client_release(t_client* this)
{
  socketstream_delete(this->socketstream);
}

t_client*	client_new(int socket)
{
  t_client*	client;

  client = malloc(sizeof(t_client));
  if (client == NULL)
    return (NULL);
  client_initialize(client, socket);
  return (client);
}

void		client_delete(t_client* client)
{
  client_release(client);
  free(client);
}
