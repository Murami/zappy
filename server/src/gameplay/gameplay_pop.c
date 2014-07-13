#include <stdlib.h>
#include "gameplay.h"
#include "map.h"
#include "case.h"

void	gameplay_pop_food(t_gameplay* this)
{
  int	x;
  int	y;

  x = rand() % this->map.width;
  y = rand() % this->map.height;
  this->map.map[x + y * this->map.width].food++;
  if (this->map.map[x + y * this->map.width].food > 10)
    this->map.map[x + y * this->map.width].food = 10;
  gameplay_send_case_all2(this, x, y);
}

void	gameplay_pop_linemate(t_gameplay* this)
{
  int	x;
  int	y;

  x = rand() % this->map.width;
  y = rand() % this->map.height;
  this->map.map[x + y * this->map.width].linemate++;
  if (this->map.map[x + y * this->map.width].linemate > 10)
    this->map.map[x + y * this->map.width].linemate = 10;
  gameplay_send_case_all2(this, x, y);
}

void	gameplay_pop_deraumere(t_gameplay* this)
{
  int	x;
  int	y;

  x = rand() % this->map.width;
  y = rand() % this->map.height;
  this->map.map[x + y * this->map.width].deraumere++;
  if (this->map.map[x + y * this->map.width].deraumere > 10)
    this->map.map[x + y * this->map.width].deraumere = 10;
  gameplay_send_case_all2(this, x, y);
}

void	gameplay_pop_sibur(t_gameplay* this)
{
  int	x;
  int	y;

  x = rand() % this->map.width;
  y = rand() % this->map.height;
  this->map.map[x + y * this->map.width].sibur++;
  if (this->map.map[x + y * this->map.width].sibur > 10)
    this->map.map[x + y * this->map.width].sibur = 10;
  gameplay_send_case_all2(this, x, y);
}
