/*
** list_misc.c for list in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/misc
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:10:56 2014 quentin desabre
** Last update Sun Jul 13 16:12:57 2014 Desabre Quentin
*/

#include <stdlib.h>
#include "list.h"

int	list_size(t_list* this)
{
  return (this->size);
}

bool	list_empty(t_list* this)
{
  return (this->size == 0);
}
