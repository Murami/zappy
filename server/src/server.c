#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "server.h"

bool			g_alive;

void			sighandler(int signum)
{
  write(1, "\b\b  \b\b", 6);
  g_alive = false;
}

void			server_initialize(t_server *this)
{
  signal(SIGINT, &sighandler);
  g_alive = true;
  memset(this, 0, sizeof(t_server));
  // GESTION DU PORT
  create_socket(this, 4243);
  create_queue(this);
}

void			server_release(t_server *this)
{
  /* socketstream_release(this->client); */
  close(this->socket);
}

void			server_accept(t_server *this)
{
  int			len;
  int			socket;
  struct sockaddr_in	sin;

  len = 1;
  socket = accept(this->socket, (struct sockaddr *)&sin, (socklen_t *)&len);
  if (socket == -1)
    perror("accept");
  /* socketstream_initialize(this->client, socket); */
  printf("new client socket [%d]\n", socket);
  this->client[this->nb_connexions] = socket;
}

void			server_launch(t_server *this)
{
  fd_set		rfds;
  int			retval;
  char			buff[256];

  while (42)
    {
      if (g_alive == false)
	{
	  server_release(this);
	  return;
	}
      printf("select\n");
      printf("socket [%d]\n", this->socket);
      FD_SET(this->socket, &rfds);
      retval = select(this->socket + 1 + this->nb_connexions,
		      &rfds, NULL, NULL, NULL);
      if (retval == -1)
	{
	  if (g_alive == false)
	    {
	      server_release(this);
	      return;
	    }
	  if (g_alive == true)
	    perror("select()");
	}
      else if (retval)
	{
	  if (FD_ISSET(this->socket, &rfds))
	    {
	      printf("add client\n");
	      server_accept(this);
	      this->nb_connexions++;
	    }
	  else
	    {

	      if (FD_ISSET(this->client[0], &rfds))
		{
		  if (read(this->client[0], &buff, 256) == 0)
		    {
		      printf("client disconnect\n");
		      this->nb_connexions = 0;
		    }
		}
	      /* process_cmd(this, rfds); */
	    }
	  reset_rfds(this, &rfds);
	}
    }
}
