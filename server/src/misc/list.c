/*
** list.c for list in /home/desabr_q/Desktop/zappy/PSU_2013_zappy/server/src/misc
**
** Made by quentin desabre
** Login   <desabr_q@epitech.net>
**
** Started on  Sun Jul 13 16:08:04 2014 quentin desabre
** Last update Sun Jul 13 16:12:58 2014 Desabre Quentin
*/

#include <stdlib.h>
#include "list.h"

bool		list_push_back(t_list* this, void* data)
{
  t_list_elm*	elm;

  elm = (t_list_elm*)malloc(sizeof(t_list_elm));
  if (elm == NULL)
    return (false);
  elm->next = this->root;
  elm->prev = this->root->prev;
  elm->data = data;
  this->root->prev->next = elm;
  this->root->prev = elm;
  this->size++;
  return (true);
}

bool		list_push_front(t_list* this, void* data)
{
  t_list_elm*	elm;

  elm = (t_list_elm*)malloc(sizeof(t_list_elm));
  if (elm == NULL)
    return (false);
  elm->next = this->root->next;
  elm->prev = this->root;
  elm->data = data;
  this->root->next->prev = elm;
  this->root->next = elm;
  this->size++;
  return (true);
}

void		list_pop_front(t_list* this)
{
  t_list_elm*	elm;

  if (list_empty(this))
    return;
  elm = (t_list_elm*)this->root->next;
  elm->next->prev = this->root;
  this->root->next = elm->next;
  free(elm);
  this->size--;
}

void	list_pop_back(t_list* this)
{
  t_list_elm*	elm;

  if (list_empty(this))
    return;
  elm = (t_list_elm*)this->root->prev;
  elm->prev->next = this->root;
  this->root->prev = elm->prev;
  free(elm);
  this->size--;
}
