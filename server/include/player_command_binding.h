/*
** player_command_binding.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:25:44 2014 otoshigami
** Last update Sun Jul 13 17:25:45 2014 otoshigami
*/

#ifndef PLAYER_COMMAND_BINDING_H
# define PLAYER_COMMAND_BINDING_H

# include <sys/time.h>

struct s_player_command;
struct s_gameplay;

typedef struct		s_player_command_binding
{
  int			has_data;
  long int	       	time;
  const char*		request;
  void			(*callback)(struct s_gameplay*, struct s_player_command*);
}			t_player_command_binding;

#endif /* PLAYER_COMMAND_BINDING_H */
