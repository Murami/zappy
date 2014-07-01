#include "map.h"

bool		map_initialize(t_map *this, int width, int height)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  this->width = width;
  this->height = height;
  this->map = malloc(width * height * sizeof(t_case));
  while (i != width)
    {
      while (j != height)
	{
	  case_initialize(this->map[i + j * width]);
	  j++;
	}
      i++;
    }
  if (this->map == NULL)
    return (false);
  return (true);
}

t_map*		map_new(int width, int height)
{
  t_map		*map;

  if (map = malloc(sizeof(t_map)) != NULL)
    return (NULL);
  map_initialize(map, width, height);
  return (map);
}

void		map_release(t_map *this)
{
  free(this->map)
}

void		map_delete(t_map *this)
{
  map_release(this);
  free(this);
}
