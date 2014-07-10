#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "socketstream.h"
#include "list.h"
#include "server.h"

void		client_send_msg(t_client *client, char *msg)
{
  char		*str;

  str = strdup(msg);
  list_push_back(client->requests_output, str);
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
      if (socketstream_write(this->socketstream,
			     request, strlen(request)) == 0)
	can_write = false;
      else
	{
	  free(request);
	  list_pop_front(this->requests_output);
	}
    }
}
