#include "server.h"

void			server_initialize(t_server *this)
{
  memset(this, 0, sizeof(t_server));
  FD_ZERO(&this->rfds);
  // GESTION DU PORT
  create_socket(this, 4242);
  create_queue(this);
}

void			server_release(t_server *this)
{
  close(this->socket);
}

void			server_launch(t_server *this)
{
  while (42)
    {
      printf("select\n");
      printf("socket [%d]\n", this->socket);
      FD_SET(this->socket, &this->rfds);

      int			retval;

      retval = select(this->socket + 1 + this->nb_connexions,
		      &this->rfds, NULL, NULL, NULL);
      if (retval == -1)
	perror("select()");
      else if (retval)
	{
	  if (FD_ISSET(this->socket, &this->rfds))
	    {
	      printf("add client\n");
	      this->nb_connexions++;
	    }
	  else
	    {
	      /* process_cmd(this, rfds); */
	    }
	  reset_rfds(this);
	}
    }
}
