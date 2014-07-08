#ifndef PLAYER_COMMAND_H
# define PLAYER_COMMAND_H

# include <sys/time.h>
# include <player_command_binding.h>

struct s_player;
struct s_server;
struct s_client_player;

/*
** TYPEDEF SUR LE PTR FUNC POUR LA NORME
*/

typedef struct		s_player_command
{
  struct timeval	reception_time;
  struct s_player*	player;
  char*			data;
  int			id_command;
}			t_player_command;

extern t_player_command_binding	g_player_commands[];

void			player_command_execute(t_player_command* this, struct s_server* server);
struct timeval		player_command_remaining_time(t_player_command* this, struct timeval time);
t_player_command*	player_command_new(struct s_client_player* client,
					   struct timeval reception_time,
					   char* data,
					   int id_command);
void			player_command_delete(t_player_command* client);

#endif /* PLAYER_COMMAND_H */
