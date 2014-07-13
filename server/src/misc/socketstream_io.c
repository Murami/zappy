/*
** socketstream_io.c for  in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/misc
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 18:04:45 2014 quentin desabre
** Last update Sun Jul 13 19:56:37 2014 otoshigami
*/

#include <stdbool.h>
#include <string.h>
#include "socketstream.h"

int	socketstream_read(t_socketstream* this, char* buffer, int size)
{
  int	delta;
  int	delta_request;

  delta = SOCKETSTREAM_BUFFER_SIZE - this->begin_input;
  if (this->size_input < delta)
    delta = this->size_input;
  if (size < delta)
    delta = size;
  memset(buffer, 0, size);
  memcpy(buffer, this->buffer_input + this->begin_input, delta);
  memcpy(buffer + delta, this->buffer_input, this->size_input - delta);
  if (!strchr(buffer, '\n'))
    {
      this->size_input = 0;
      this->begin_input = 0;
      return (0);
    }
  else
    {
      delta_request = MIN(strchr(buffer, '\n') - buffer + 1, this->size_input);
      this->begin_input += delta_request;
      this->size_input -= delta_request;
      this->begin_input %= SOCKETSTREAM_BUFFER_SIZE;
      return (delta_request);
    }
}

int	socketstream_peek(t_socketstream* this, char* buffer, int size)
{
  int	delta;
  int	delta_request;

  delta = SOCKETSTREAM_BUFFER_SIZE - this->begin_input;
  if (this->size_input < delta)
    delta = this->size_input;
  if (size < delta)
    delta = size;
  memcpy(buffer, this->buffer_input + this->begin_input, delta);
  memcpy(buffer + delta, this->buffer_input, this->size_input - delta);
  buffer[size -  1] = '\0';
  if (!strchr(buffer, '\n'))
    return (0);
  else
    {
      delta_request = MIN(strchr(buffer, '\n') - buffer + 1, this->size_input);
      return (delta_request);
    }
}

int	socketstream_write(t_socketstream* this, char* buffer, int size)
{
  int	delta;

  if (size > SOCKETSTREAM_BUFFER_SIZE - this->size_output)
    return (0);
  delta = size;
  memcpy(this->buffer_output + this->size_output, buffer, delta);
  this->size_output += size;
  return (size);
}
