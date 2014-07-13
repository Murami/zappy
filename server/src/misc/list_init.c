/*
** list_init.c for list_init in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/misc
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:08:15 2014 quentin desabre
** Last update Sun Jul 13 16:09:29 2014 Desabre Quentin
*/

#include <stdlib.h>
#include "list.h"

void	list_initialize(t_list* this)
{
  this->size = 0;
  this->root = malloc(sizeof(t_list_elm));
  this->root->next = this->root;
  this->root->prev = this->root;
}

void	list_release(t_list* this)
{
  while (this->size)
    list_pop_back(this);
  free(this->root);
}

t_list*		list_new()
{
  t_list*	list;

  list = malloc(sizeof(t_list));
  if (list == NULL)
    return (NULL);
  list_initialize(list);
  return (list);
}

void	list_delete(t_list* list)
{
  list_release(list);
  free(list);
}
