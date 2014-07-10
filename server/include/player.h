#ifndef		_PLAYER_H_
# define	_PLAYER_H_

# include	"case.h"

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
  int			x;
  int			y;
  int			level;
  t_inventory		inventory;
}			t_player;

void			player_initialize(t_player *this, struct s_gameplay *gameplay,
					  struct s_client *client, struct s_team* team);
t_player*		player_new(struct s_gameplay *gameplay,
				   struct s_client *client, struct s_team* team);

#endif		/* _PLAYER_H_ */
