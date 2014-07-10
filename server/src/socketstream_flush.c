#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "socketstream.h"

bool		socketstream_flush_output(t_socketstream* this)
{
  char		buffer[SOCKETSTREAM_BUFFER_SIZE];
  int		cpysize;

  cpysize = MIN(this->size_output,
		SOCKETSTREAM_BUFFER_SIZE - this->begin_output);
  memcpy(buffer, this->buffer_output + this->begin_output, cpysize);
  if (cpysize - this->size_output)
    memcpy(buffer + cpysize, this->buffer_output + this->begin_output,
	   cpysize - this->size_output);
  /* write(1, "buffer [", 8); */
  /* write(1, buffer, strlen(buffer) - 1); */
  /* write(1, "]\n", 2); */
  if (write(this->socket, buffer, cpysize) == -1)
    return (false);
  this->begin_output = 0;
  this->size_output = 0;
  return (true);
}

bool		socketstream_flush_input(t_socketstream* this)
{
  char		buffer[SOCKETSTREAM_BUFFER_SIZE];
  int		cpysize;
  int		n;
  int		end;

  end = (this->begin_input + this->size_input) % SOCKETSTREAM_BUFFER_SIZE;
  n = read(this->socket, buffer, SOCKETSTREAM_BUFFER_SIZE - this->size_input);
  if (n <= 0)
    return (false);
  cpysize = MIN(n, SOCKETSTREAM_BUFFER_SIZE - end);
  memcpy(this->buffer_input + end, buffer, cpysize);
  if (n - cpysize > 0)
    memcpy(this->buffer_input, buffer + cpysize, n - cpysize);
  this->size_input += n;
  return (true);
}
