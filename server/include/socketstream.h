#ifndef SOCKETSTREAM_H
# define SOCKETSTREAM_H

# include <stdbool.h>

# define SOCKETSTREAM_BUFFER_SIZE	4096
# define MIN(a, b)	((a > b) ? b : a)

typedef struct	s_socketstream
{
  int		socket;
  int		begin_input;
  int		size_input;
  char		buffer_input[SOCKETSTREAM_BUFFER_SIZE];
  int		begin_output;
  int		size_output;
  char		buffer_output[SOCKETSTREAM_BUFFER_SIZE];
}		t_socketstream;

void			socketstream_initialize(t_socketstream* this, int socket);
void			socketstream_release(t_socketstream* this);
int			socketstream_read(t_socketstream* this, char* buffer, int size);
int			socketstream_peek(t_socketstream* this, char* buffer, int size);
int			socketstream_write(t_socketstream* this, char* buffer,
					   int size);
bool			socketstream_flush_output(t_socketstream* this);
bool			socketstream_flush_input(t_socketstream* this);
int			socketstream_get_socket(t_socketstream* this);
t_socketstream*		socketstream_new(int socket);
void			socketstream_delete(t_socketstream* sockstream);

#endif /* SOCKETSTREAM_H */
