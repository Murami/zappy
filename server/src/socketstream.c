#include "socketstream.h"

void		socketstream_initialize(t_socketstream* this, int socket)
{
  memset(this, 0, sizeof(t_socketstream));
  this->socket = socket;
}

void		socketstream_release(t_socketstream* this)
{
  close(this->socket);
}

int		socketstream_read(t_socketstream* this, char* buffer, int size)
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
      this->begin_input %= SOCKSTREAM_BUFFER_SIZE;
      return (delta_request);
    }
}

int		socketstream_write(t_socketstream* this, char* buffer, int size)
{
  int	delta;

  if (size > SOCKETSTREAM_BUFFER_SIZE - this->size_output)
    return (0);
  delta = SOCKETSTREAM_BUFFER_SIZE - this->begin_output;
  memcpy(this->buffer_output + this->begin_output, buffer, delta);
  if (size - delta > 0)
    memcpy(this->buffer_output, buffer + delta, size - delta);
  this->begin_output += size;
  this->size_output -= size;
  this->begin_output %= SOCKSTREAM_BUFFER_SIZE;
  return (size);
}

bool		socketstream_flush_output(t_socketstream* this)
{
  char		buffer[SOCKSTREAM_BUFFER_SIZE];
  int		cpysize;

  cpysize = MIN(this->size_output,
		SOCKSTREAM_BUFFER_SIZE - this->begin_output);
  memcpy(buffer, this->buffer_output + this->begin_ouput, cpysize);
  if (cpysize - this->size_output)
    memcpy(buffer + cpysize, this->buffer_output + this->begin_ouput,
	   cpysize - this->size_outpout);
  write(this->socket, buffer, cpysize);
  this->begin_output = 0;
  this->size_output = 0;
}

bool		socketstream_flush_input(t_socketstream* this)
{
  char		buffer[SOCKSTREAM_BUFFER_SIZE];
  int		cpysize;
  int		n;

  n = read(this->socket, buffer, SOCKSTREAM_BUFFER_SIZE - this->size_input);
  if (n <= 0)
    return (false);
  cpysize = MIN(n, SOCKSTREAM_BUFFER_SIZE - this->begin_input);
  memcpy(this->buffer_input + this->begin_input, buffer, cpysize);
  if (n - cpysize > 0)
    memcpy(this->buffer_input, buffer + cpysize, n - cpysize);
  this->size_input += n;
  return (true);
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