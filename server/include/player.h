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
  struct s_client*     	client;
  struct s_team*       	team;
  t_direction		direction;
  t_inventory		inventory;
  int			level;
  int			x;
  int			y;
  int			id_egg;
  t_list*		command_queue;
  /* t_list*		eggs; */
  t_list_iterator	it;
  struct timeval	death_time;
  bool			ghost;
}			t_player;

void			player_initialize(t_player *this, struct s_gameplay *gameplay,
					  struct s_client *client, struct s_team* team);
t_player*		player_new(struct s_gameplay *gameplay,
				   struct s_client *client, struct s_team* team);
struct timeval		player_get_next_action_time(t_player* this);
bool			player_make_action(t_player* this, struct s_gameplay* gameplay, struct timeval time);
bool			player_is_dead(t_player* this, struct timeval time);
void			player_add_action(t_player* this, t_player_command* command);
bool			player_need_update(t_player* this, struct timeval time);
void			player_release(t_player* this);
void			player_delete(t_player* player);

#endif		/* _PLAYER_H_ */
