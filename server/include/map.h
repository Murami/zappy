#ifndef		_MAP_H_
# define	_MAP_H_

# include	"case.h"

typedef struct	s_map
{
  int		width;
  int		height;
  t_case*	map;
}		t_map;

t_map*		map_new(int width, int height);
void		map_initialize(t_map *this, int width, int height);
void		map_release(t_map *this);
void		map_delete(t_map *this);

#endif	/* _MAP_H_ */
