#ifndef EGG_H
#define EGG_H

#include <sys/time.h>
struct s_team;

typedef struct		s_egg
{
  int			x;
  int			y;
  struct s_team*	team;
  struct timeval	time;
  int			id_player;
  int			id;
}			t_egg;

#endif /* EGG_H */
