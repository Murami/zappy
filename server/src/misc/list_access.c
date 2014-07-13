/*
** list_acces.c for access in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/misc
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:12:48 2014 quentin desabre
** Last update Sun Jul 13 16:12:55 2014 Desabre Quentin
*/

#include <stdlib.h>
#include "list.h"

void*	list_front(t_list* this)
{
  if (list_empty(this))
    return (NULL);
  return (this->root->next->data);
}

void*	list_back(t_list* this)
{
  if (list_empty(this))
    return (NULL);
  return (this->root->prev->data);
}
