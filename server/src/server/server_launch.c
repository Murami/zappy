/*
** server_launch.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:27:37 2014 quentin desabre
** Last update Sun Jul 13 16:27:59 2014 Desabre Quentin
*/

#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include "server.h"
#include "gameplay.h"
#include "client.h"
#include "team.h"
#include "client_graphic.h"
#include "client_player.h"
#include "socketstream.h"
#include "player_command.h"
#include "monitor_command.h"

void			server_launch(t_server *this)
{
  struct timeval	waiting_time;
  int			retval;
  fd_set		set_fd_in;
  fd_set		set_fd_out;

  waiting_time.tv_sec = 0;
  waiting_time.tv_usec = 0;
  while (!this->gameplay->winner)
    {
      if (g_alive == false)
	{
	  server_release(this);
	  return;
	}
      reset_rfds(this, &set_fd_in, &set_fd_out);
      retval = select(1 + this->socket_max,
		      &set_fd_in, &set_fd_out, NULL,
		      (waiting_time.tv_sec || waiting_time.tv_usec) ?
		      &waiting_time : NULL);
      if (g_alive == false)
	{
	  server_release(this);
	  return;
	}
      else if (retval == -1)
	{
	  perror("select()");
	  exit(-1);
	}
      gettimeofday(&this->gameplay->time, NULL);
      if (FD_ISSET(this->socket, &set_fd_in))
	server_accept(this);
      else
	{
	  server_process_new_clients(this, &set_fd_in, &set_fd_out);
	  server_process_clients(this, &set_fd_in, &set_fd_out);
	  server_process_deads(this, &set_fd_out);
	}
      waiting_time = gameplay_update(this->gameplay, this->gameplay->time);
      server_delete_deads(this);
    }
  printf("we have a winner : %s\n", this->gameplay->winner->name);
  gameplay_send_seg(this->gameplay);
}
