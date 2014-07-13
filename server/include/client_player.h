/*
** client_player.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:28:47 2014 otoshigami
** Last update Sun Jul 13 17:28:47 2014 otoshigami
*/

#ifndef CLIENT_PLAYER_H
# define CLIENT_PLAYER_H

# include "client.h"

t_client_vtable client_player_vtable;

typedef struct		s_client_player
{
  t_client		parent_client;
  struct s_player*	player;
}			t_client_player;

void			client_player_initialize(t_client_player*,
						 struct s_socketstream*);
void			client_player_release(t_client_player*);

void			client_player_run_input(t_client_player*, struct s_server*);
void			client_player_remove(t_client_player*, struct s_server*);

t_client_player*	client_player_new(struct s_socketstream*);
void			client_player_delete(t_client_player*);

#endif /* CLIENT_PLAYER_H */
