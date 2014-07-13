/*
** gameplay_ia_callbacks.h for  in /home/otoshigami/Workspace/Epitech/git/PSU_2013_zappy/server
**
** Made by otoshigami
** Login   <otoshigami@epitech.net>
**
** Started on  Sun Jul 13 17:27:06 2014 otoshigami
** Last update Sun Jul 13 17:27:18 2014 otoshigami
*/

#ifndef GAMEPLAY_IA_CALLBACKS
# define GAMEPLAY_IA_CALLBACKS

# include "gameplay_object_callback.h"

void	gameplay_command_move(t_gameplay*,
			      struct s_player*);
void	gameplay_command_avance(t_gameplay*,
				struct s_player_command*);
void	gameplay_command_droite(t_gameplay* this,
				struct s_player_command* command);
void	gameplay_command_gauche(t_gameplay* this,
				struct s_player_command* command);
void	gameplay_command_voir(t_gameplay* this,
			      struct s_player_command* command);
void	gameplay_command_inventaire(t_gameplay* this,
				    struct s_player_command* command);
void	gameplay_command_prend(t_gameplay* this,
			       struct s_player_command* command);
void	gameplay_command_pose(t_gameplay* this,
			      struct s_player_command* command);
void	gameplay_command_expulse(t_gameplay* this,
				 struct s_player_command* command);
void	gameplay_command_broadcast(t_gameplay* this,
				   struct s_player_command* command);
void	gameplay_command_incantation(t_gameplay* this,
				     struct s_player_command* command);
void	gameplay_command_fork(t_gameplay* this,
			      struct s_player_command* command);
void	gameplay_command_connect_nbr(t_gameplay* this,
				     struct s_player_command* command);

#endif /* GAMEPLAY_IA_CALLBACKS */
