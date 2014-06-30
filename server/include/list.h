#ifndef LIST_H
# define LIST_H

# include <stdbool.h>

typedef struct		s_list_elm
{
  struct s_list_elm*	prev;
  struct s_list_elm*	next;
  void*			data;
}			t_list_elm, *t_list_iterator;

typedef struct	s_list
{
  int		size;
  t_list_elm*	root;
}		t_list;

/* METHODS */

void	list_initialize(t_list* this);
void	list_release(t_list* this);
bool	list_push_back(t_list* this, void* data);
bool	list_push_front(t_list* this, void* data);
void	list_pop_back(t_list* this);
void	list_pop_front(t_list* this);
int	list_size(t_list* this);
bool	list_empty(t_list* this);
void*	list_front(t_list* this);
void*	list_back(t_list* this);

/* ITERATORS */

t_list_iterator		list_begin(t_list* this);
t_list_iterator		list_end(t_list* this);

t_list_iterator		list_iterator_next(t_list_iterator list_iterator);
t_list_iterator		list_iterator_prev(t_list_iterator list_iterator);

/* INSERT/ERASE */

t_list_iterator		list_erase(t_list* this, t_list_iterator list_iterator);
bool			list_insert(t_list* this, t_list_iterator list_iterator, void* data);

/* OPERATORS */

t_list*	list_new();
void	list_delete(t_list* list);

#endif /* LIST_H */
