/*
** monitor_command_binding.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:26:00 2014 otoshigami
** Last update Sun Jul 13 17:26:01 2014 otoshigami
*/

#ifndef MONITOR_BINDING_H
# define MONITOR_BINDING_H

struct s_monitor_command;
struct s_gameplay;

typedef struct		s_monitor_command_binding
{
  int			has_data;
  const char*		request;
  void			(*callback)(struct s_gameplay*, struct s_monitor_command*);
}			t_monitor_command_binding;

#endif /* MONITOR_BINDING_H */
