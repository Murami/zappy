/*
** player_command.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:24:43 2014 otoshigami
** Last update Sun Jul 13 17:24:43 2014 otoshigami
*/

#ifndef PLAYER_COMMAND_H
# define PLAYER_COMMAND_H

# include <sys/time.h>
# include <player_command_binding.h>

struct s_player;
struct s_gameplay;
struct s_client_player;

/*
** TYPEDEF SUR LE PTR FUNC POUR LA NORME
*/

typedef struct	       	s_player_command
{
  struct timeval	expiration_time;
  struct s_player*	player;
  char*			data;
  int			id_command;
}			t_player_command;

extern t_player_command_binding	g_player_commands[];

void			player_command_execute(t_player_command* this,
					       struct s_gameplay* gameplay);
struct timeval		player_command_remaining_time(t_player_command* this,
						      struct timeval time);
t_player_command*	player_command_new(struct s_client_player* client,
					   struct s_gameplay* gameplay,
					   char* data,
					   int id_command);
void			player_command_delete(t_player_command* client);

#endif /* PLAYER_COMMAND_H */
