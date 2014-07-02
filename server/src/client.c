#include <stdlib.h>
#include <string.h>
#include "client.h"

void		client_initialize(t_client* this, t_socketstream* sockstream)
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

void		client_run_input(t_client* this, t_server* server)
{
  this->vtable->run_input(this, server);
}

void		client_run_output(t_client* this, t_server* server)
{
  (void) server;
  bool			can_write;
  char*			request;

  can_write = true;
  while (can_write && !list_empty(this->requests_output))
    {
      request = list_front(this->requests_output);
      if (socketstream_write(this->socketstream, request, strlen(request) == 0))
	can_write = false;
      else
	{
	  free(request);
	  list_pop_front(this->requests_output);
	}
    }
}

void		client_delete(t_client* client)
{
  client->vtable->delete(client);
}
