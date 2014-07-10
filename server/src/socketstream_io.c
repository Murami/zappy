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
