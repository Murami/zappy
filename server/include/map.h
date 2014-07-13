/*
** map.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:22:57 2014 otoshigami
** Last update Sun Jul 13 17:22:58 2014 otoshigami
*/

#ifndef		_MAP_H_
# define	_MAP_H_

# include	<stdbool.h>
# include	"case.h"

typedef struct	s_map
{
  int		width;
  int		height;
  t_case*	map;
}		t_map;

t_map*		map_new(int width, int height);
bool		map_initialize(t_map *this, int width, int height);
void		map_release(t_map *this);
void		map_delete(t_map *this);

#endif	/* _MAP_H_ */
