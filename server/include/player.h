#ifndef		_PLAYER_H_
# define	_PLAYER_H_

# include	<stdbool.h>
# include	<sys/time.h>
# include	"case.h"
# include	"list.h"
# include	"player_command.h"

struct s_team;
struct s_client;
struct s_gameplay;

typedef enum	e_direction
  {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
  }		t_direction;

typedef struct		s_player
{
  int			id;
  int			level;
  int			x;
  int			y;
  int			id_egg;
  bool			is_egg;
  bool			ghost;
  t_direction		direction;
  t_inventory		inventory;
  struct s_client*     	client;
  struct s_team*       	team;
  struct timeval	death_time;
  t_list*		command_queue;
  t_list_iterator	it;
}			t_player;

void		player_initialize(t_player*, struct s_gameplay*,
				  struct s_client*, struct s_team*);
t_player*	player_new(struct s_gameplay *, struct s_client *,
			   struct s_team*);
struct timeval	player_get_next_action_time(t_player*);
bool		player_make_action(t_player*, struct s_gameplay*, struct timeval);
bool		player_is_dead(t_player*, struct timeval);
void		player_add_action(t_player*, t_player_command*);
bool		player_need_update(t_player*, struct timeval);
void		player_release(t_player*);
void		player_delete(t_player*);

#endif		/* _PLAYER_H_ */
