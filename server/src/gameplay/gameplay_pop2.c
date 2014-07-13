/*
** gameplay_pop2.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 18:07:44 2014 otoshigami
** Last update Sun Jul 13 18:07:45 2014 otoshigami
*/

#include <stdlib.h>
#include "gameplay.h"
#include "map.h"
#include "case.h"

void	gameplay_pop_mendiane(t_gameplay* this)
{
  int	x;
  int	y;

  x = rand() % this->map.width;
  y = rand() % this->map.height;
  this->map.map[x + y * this->map.width].mendiane++;
  if (this->map.map[x + y * this->map.width].mendiane > 10)
    this->map.map[x + y * this->map.width].mendiane = 10;
  gameplay_send_case_all2(this, x, y);
}

void	gameplay_pop_phiras(t_gameplay* this)
{
  int	x;
  int	y;

  x = rand() % this->map.width;
  y = rand() % this->map.height;
  this->map.map[x + y * this->map.width].phiras++;
  if (this->map.map[x + y * this->map.width].phiras > 10)
    this->map.map[x + y * this->map.width].phiras = 10;
  gameplay_send_case_all2(this, x, y);
}

void	gameplay_pop_thystame(t_gameplay* this)
{
  int	x;
  int	y;

  x = rand() % this->map.width;
  y = rand() % this->map.height;
  this->map.map[x + y * this->map.width].thystame++;
  if (this->map.map[x + y * this->map.width].thystame > 10)
    this->map.map[x + y * this->map.width].thystame = 10;
  gameplay_send_case_all2(this, x, y);
}
