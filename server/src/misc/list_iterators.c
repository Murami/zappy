/*
** list_iterators.c for iterators in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/misc
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:09:48 2014 quentin desabre
** Last update Sun Jul 13 16:10:34 2014 Desabre Quentin
*/

#include <stdlib.h>
#include "list.h"

t_list_iterator		list_begin(t_list* this)
{
  return (this->root->next);
}

t_list_iterator		list_end(t_list* this)
{
  return (this->root);
}

t_list_iterator		list_iterator_next(t_list_iterator this)
{
  return (this->next);
}

t_list_iterator		list_iterator_prev(t_list_iterator this)
{
  return (this->prev);
}
