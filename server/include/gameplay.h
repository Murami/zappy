/*
** gameplay.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:23:12 2014 otoshigami
** Last update Sun Jul 13 17:23:14 2014 otoshigami
*/

#ifndef		_GAMEPLAY_H_
# define	_GAMEPLAY_H_

# include	<sys/time.h>
# include	"config.h"
# include	"map.h"
# include	"list.h"

struct s_player_command;
struct s_monitor_command;
struct s_client;
struct s_monitor;
struct s_player;
struct s_server;
struct s_team;
struct s_case;
struct s_gameplay;
struct s_egg;

typedef t_list_iterator (*kill_func)(struct s_gameplay*, struct s_player*);

typedef struct		s_gameplay
{
  t_list*		teams;
  t_list*		players;
  t_list*		ghosts;
  t_list*		monitors;
  t_list*		eggs;
  t_map			map;
  int			delay;
  struct timeval	time;
  struct s_server*	server;
  int			last_id;
  struct s_team*	winner;
}			t_gameplay;

typedef struct		s_object_binding
{
  void			(*put)(t_gameplay*, struct s_player_command*);
  void			(*take)(t_gameplay*, struct s_player_command*);
  char*			object;
}			t_object_binding;

# include "gameplay_core.h"
# include "gameplay_send.h"
# include "gameplay_ia_callbacks.h"
# include "gameplay_monitor_callbacks.h"
# include "gameplay_pop.h"
# include "gameplay_misc.h"

#endif /* _GAMEPLAY_H_ */
