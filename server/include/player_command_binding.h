#ifndef PLAYER_COMMAND_BINDING_H
# define PLAYER_COMMAND_BINDING_H

# include <sys/time.h>

struct s_gameplay;
struct s_server;

typedef struct		s_player_command_binding
{
  int			time;
  const char*		request;
  void			(*callback)(struct s_gameplay*, struct s_server*);
}			t_player_command_binding;

#endif /* PLAYER_COMMAND_BINDING_H */
