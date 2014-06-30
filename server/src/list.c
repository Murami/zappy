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

void		list_pop_back(t_list* this)
{
  t_list_elm*	elm;

  elm = (t_list_elm*)this->root->prev;
  elm->prev->next = this->root;
  this->root->prev = elm->prev;
  free(elm);
  this->size--;
}

void	list_pop_front(t_list* this)
{
  t_list_elm*	elm;

  elm = (t_list_elm*)this->root->prev;
  elm->prev->next = this->root;
  this->root->prev = elm->prev;
  free(elm);
  this->size--;
}

int	list_size(t_list* this)
{
  return (this->size);
}

bool	list_empty(t_list* this)
{
  return (this->size == 0);
}

void*	list_front(t_list* this)
{
  return (this->root->next->data);
}

void*	list_back(t_list* this)
{
  return (this->root->prev->data);
}

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

bool			list_insert(t_list* this, t_list_iterator list_iterator, void* data)
{
  t_list_elm*		elm;

  elm = (t_list_elm*)malloc(sizeof(t_list_elm));
  if (elm == NULL)
    return (false);
  elm->next = list_iterator->next;
  elm->prev = list_iterator;
  elm->data = data;
  list_iterator->next->prev = elm;
  list_iterator->next = elm;
  this->size++;
  return (true);
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
