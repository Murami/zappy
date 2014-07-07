#include "case.h"

void		case_initialize(t_case *this, int x, int y)
{
  this->x = x;
  this->y = y;
  this->food = 0;
  this->linemate = 0;
  this->deraumere = 0;
  this->sibur = 0;
  this->mendiane = 0;
  this->phiras = 0;
  this->thystame = 0;
}
