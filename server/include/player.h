#ifndef		_PLAYER_H_
# define	_PLAYER_H_

struct s_team;
struct s_client;
struct s_gameplay;

typedef struct		s_player
{
  struct s_client*     	client;
  struct s_team*       	team;
  int			orientation;
  int			x;
  int			y;
  int			level;
}			t_player;

void			player_initialize(t_player *this, struct s_gameplay *gameplay,
					  struct s_client *client, struct s_team* team);
t_player*		player_new(struct s_gameplay *gameplay,
				   struct s_client *client, struct s_team* team);

#endif		/* _PLAYER_H_ */
