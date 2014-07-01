#include <stdlib.h>
#include "client.h"

void		client_initialize(t_client* this, t_socketstream* sockstream)
{
  this->vtable = NULL;
  this->socketstream = sockstream;
}

void		client_release(t_client* this)
{
  socketstream_delete(this->socketstream);
}

void		client_run(t_client* this, t_server* server)
{
  this->vtable->run(this, server);
}

void		client_delete(t_client* client)
{
  client->vtable->delete(client);
}
