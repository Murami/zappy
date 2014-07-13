/*
** socketstream.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/misc
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 18:04:29 2014 quentin desabre
** Last update Sun Jul 13 18:04:30 2014 Desabre Quentin
*/

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include "socketstream.h"

void			socketstream_initialize(t_socketstream* this, int socket)
{
  memset(this, 0, sizeof(t_socketstream));
  this->socket = socket;
}

void			socketstream_release(t_socketstream* this)
{
  shutdown(this->socket, SHUT_RDWR);
  close(this->socket);
}

int			socketstream_get_socket(t_socketstream* this)
{
  return (this->socket);
}

t_socketstream*		socketstream_new(int socket)
{
  t_socketstream*	sockstream;

  sockstream = malloc(sizeof(t_socketstream));
  if (sockstream == NULL)
    return (NULL);
  socketstream_initialize(sockstream, socket);
  return (sockstream);
}

void			socketstream_delete(t_socketstream* sockstream)
{
  socketstream_release(sockstream);
  free(sockstream);
}
