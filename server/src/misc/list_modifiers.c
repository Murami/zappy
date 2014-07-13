/*
** list_modifiers.c for list in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/misc
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:11:40 2014 quentin desabre
** Last update Sun Jul 13 16:15:03 2014 Desabre Quentin
*/

#include <stdlib.h>
#include "list.h"

t_list_iterator		list_erase(t_list* this, t_list_iterator list_iterator)
{
  t_list_elm*		prev;

  if (this->size == 0 || list_iterator == this->root)
    return (this->root);
  list_iterator->next->prev = list_iterator->prev;
  list_iterator->prev->next = list_iterator->next;
  prev = list_iterator->prev;
  free(list_iterator);
  this->size--;
  return (prev);
}

t_list_iterator			list_insert(t_list* this,
					    t_list_iterator list_iterator,
					    void* data)
{
  t_list_elm*		elm;

  elm = (t_list_elm*)malloc(sizeof(t_list_elm));
  if (elm == NULL)
    return (this->root);
  list_iterator = list_iterator_prev(list_iterator);
  elm->next = list_iterator->next;
  elm->prev = list_iterator;
  elm->data = data;
  list_iterator->next->prev = elm;
  list_iterator->next = elm;
  this->size++;
  return (elm);
}
