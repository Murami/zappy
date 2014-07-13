/*
** check_stone6_7.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:36:28 2014 otoshigami
** Last update Sun Jul 13 17:36:29 2014 otoshigami
*/

#include "map.h"
#include "gameplay.h"

bool			check_stone6(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 1 &&
	  this->map.map[x + y * this->map.width].deraumere == 2 &&
	  this->map.map[x + y * this->map.width].sibur == 3 &&
	  this->map.map[x + y * this->map.width].mendiane == 0 &&
	  this->map.map[x + y * this->map.width].phiras == 1 &&
	  this->map.map[x + y * this->map.width].thystame == 0);
}

bool			check_stone7(t_gameplay* this, int x, int y)
{
  return (this->map.map[x + y * this->map.width].linemate == 2 &&
	  this->map.map[x + y * this->map.width].deraumere == 2 &&
	  this->map.map[x + y * this->map.width].sibur == 2 &&
	  this->map.map[x + y * this->map.width].mendiane == 2 &&
	  this->map.map[x + y * this->map.width].phiras == 2 &&
	  this->map.map[x + y * this->map.width].thystame == 1);
}
