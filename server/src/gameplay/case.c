/*
** case.c for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:36:48 2014 otoshigami
** Last update Sun Jul 13 18:43:46 2014 otoshigami
*/

#include <stdlib.h>
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

void		case_randomize(t_case *this, int x, int y)
{
  case_initialize(this, x, y);
  this->food = rand() % 2;
  if (rand() % 4)
    {
      this->linemate = rand() % 2;
      this->deraumere = rand() % 2;
      this->sibur = rand() % 2;
    }
  if (rand() % 3)
    {
      this->mendiane = rand() % 2;
      this->phiras = rand() % 2;
      this->thystame = rand() % 2;
    }
}
