#include "map.h"
#include "gameplay.h"

bool			check_stone1(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 1 &&
	  this->map.map[x + y * this->map.width].deraumere == 0 &&
	  this->map.map[x + y * this->map.width].sibur == 0 &&
	  this->map.map[x + y * this->map.width].mendiane == 0 &&
	  this->map.map[x + y * this->map.width].phiras == 0 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}

bool			check_stone2(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 1 &&
	  this->map.map[x + y * this->map.width].deraumere == 1 &&
	  this->map.map[x + y * this->map.width].sibur == 1 &&
	  this->map.map[x + y * this->map.width].mendiane == 0 &&
	  this->map.map[x + y * this->map.width].phiras == 0 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}

bool			check_stone3(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 2 &&
	  this->map.map[x + y * this->map.width].deraumere == 0 &&
	  this->map.map[x + y * this->map.width].sibur == 1 &&
	  this->map.map[x + y * this->map.width].mendiane == 0 &&
	  this->map.map[x + y * this->map.width].phiras == 2 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}

bool			check_stone4(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 1 &&
	  this->map.map[x + y * this->map.width].deraumere == 1 &&
	  this->map.map[x + y * this->map.width].sibur == 2 &&
	  this->map.map[x + y * this->map.width].mendiane == 0  &&
	  this->map.map[x + y * this->map.width].phiras == 1 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}

bool			check_stone5(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 1 &&
	  this->map.map[x + y * this->map.width].deraumere == 2 &&
	  this->map.map[x + y * this->map.width].sibur == 1 &&
	  this->map.map[x + y * this->map.width].mendiane == 3 &&
	  this->map.map[x + y * this->map.width].phiras == 0 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}
