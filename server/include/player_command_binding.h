#ifndef PLAYER_COMMAND_BINDING_H
# define PLAYER_COMMAND_BINDING_H

# include <sys/time.h>

struct s_player_command;
struct s_gameplay;

typedef struct		s_player_command_binding
{
  int			has_data;
  int			time;
  const char*		request;
  void			(*callback)(struct s_gameplay*, struct s_player_command*);
}			t_player_command_binding;

#endif /* PLAYER_COMMAND_BINDING_H */
