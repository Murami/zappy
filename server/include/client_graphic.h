/*
** client_graphic.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:26:55 2014 otoshigami
** Last update Sun Jul 13 17:26:56 2014 otoshigami
*/

#ifndef CLIENT_GRAPHIC_H
# define CLIENT_GRAPHIC_H

# include "client.h"
# include "monitor_command.h"

t_client_vtable client_graphic_vtable;

typedef struct		s_client_graphic
{
  t_client		parent_client;
}			t_client_graphic;

void			client_graphic_initialize(t_client_graphic*,
						  struct s_socketstream*);
void			client_graphic_release(t_client_graphic*);

void			client_graphic_run_input(t_client_graphic*, struct s_server*);
void			client_graphic_remove(t_client_graphic*, struct s_server*);

t_client_graphic*	client_graphic_new(struct s_socketstream*);
void			client_graphic_delete(t_client_graphic*);

#endif /* CLIENT_GRAPHIC_H */
