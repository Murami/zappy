#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "socketstream.h"
#include "list.h"
#include "server.h"

void		client_initialize(t_client* this,
				  t_socketstream* sockstream)
{
  this->vtable = NULL;
  this->socketstream = sockstream;
  this->requests_output = list_new();
}

void		client_release(t_client* this)
{
  char*		request;

  socketstream_delete(this->socketstream);
  while (!list_empty(this->requests_output))
    {
      request = list_back(this->requests_output);
      free(request);
      list_pop_back(this->requests_output);
    }
  list_delete(this->requests_output);
}

void		client_remove(t_client* this, struct s_server* server)
{
  this->vtable->remove(this, server);
}

void		client_delete(t_client* client)
{
  client->vtable->delete(client);
}
