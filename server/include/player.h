#ifndef		_PLAYER_H_
# define	_PLAYER_H_

#include <sys/time.h>

#include "list.h"
#include "player_command.h"

struct s_team;
struct s_client;
struct s_gameplay;

typedef struct		s_player
{
  int			id;
  int			orientation;
  int			x;
  int			y;
  int			level;
  t_list*		command_queue;
  t_list_iterator	it;
  struct s_client*     	client;
  struct s_team*       	team;
  struct timeval	death_time;
}			t_player;

void			player_initialize(t_player *this, struct s_gameplay *gameplay,
					  struct s_client *client, struct s_team* team);
t_player*		player_new(struct s_gameplay *gameplay,
				   struct s_client *client, struct s_team* team);
struct timeval		player_get_next_action_time(t_player* this);
bool			player_make_action(t_player* this, struct s_gameplay* gameplay, struct timeval time);
bool			player_is_dead(t_player* this, struct timeval time);
void			player_add_action(t_player* this, t_player_command* command);

#endif		/* _PLAYER_H_ */
